#include <yun_files.h>
int yun_open_dir(const char *name, yun_dir_t *dir)
{
    char dir_name[257] = {0};
    strcpy(dir_name, name);
    strcat(dir_name, "\\*");
    dir->dir = FindFirstFile(dir_name, &dir->finddata);

    if (dir->dir == INVALID_HANDLE_VALUE) {
        return 1;
    }

    return 0;
}

int yun_read_dir(yun_dir_t *dir)
{
    if (FindNextFile(dir->dir, &dir->finddata) != 0) {
        return 0;
    }
    return 1;
}

static int convertUTF8UTF16(const char* name, int size8, char* utf16, int *size16)
{
    unsigned char *utf8 = (unsigned char *)name;
    int count =0, i;
    unsigned short integer = 0;
    unsigned short *p;

    for(i = 0; i < size8; i++) { 
        p = (unsigned short int*)&utf16[i];
        if( utf8[count] < 0x80) {
            // <0x80
            integer = utf8[count];           
            count++;
        } else if( (utf8[count] < 0xDF) && (utf8[count]>=0x80)) {
            integer = utf8[count] & 0x1F;
            integer = integer << 6;
            integer += utf8[count+1] &0x3F;
            count+=2;
        } else if( (utf8[count] <= 0xEF) && (utf8[count]>=0xDF)) {
            integer = utf8[count] & 0x0F;
            integer = integer << 6;
            integer += utf8[count+1] &0x3F;
            integer = integer << 6;
            integer += utf8[count+2] &0x3F;
            count+=3;
        } else {
            printf("error!/n");
        }
        *p = integer;
    }
    *size16 = i;

    return *size16;
}

#define YUN_UTF16_BUFLEN  256
yun_fd_t yun_open_file(const char *name, u_long mode, u_long access)
{
    yun_fd_t fd;
    u_short  *u;
    int len;
    u_short  utf16[YUN_UTF16_BUFLEN];

    len = YUN_UTF16_BUFLEN;
    convertUTF8UTF16(name, strlen(name), (char *)utf16, &len);
    u = utf16;
    if (mode == YUN_FILE_RDONLY && PathFileExists(name) == 0) {
        return INVALID_HANDLE_VALUE;
    }
    //fd = CreateFileW((const wchar_t *)utf16, mode,
    fd = CreateFile(name, mode,
                     FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
                     NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    return fd;
}

int yun_read_file(yun_fd_t fd, u_char *buf, size_t size, off_t offset)
{
    u_long      n;
    OVERLAPPED  ovlp, *povlp;

    ovlp.Internal = 0;
    ovlp.InternalHigh = 0;
    ovlp.Offset = (u_long)offset;
    ovlp.OffsetHigh = 0;//(u_long)(offset >> 32);
    ovlp.hEvent = NULL;

    povlp = &ovlp;

    if (ReadFile(fd, buf, size, &n, povlp) == 0) {
        return -1;
    }

    return n;
}

int yun_write_file(yun_fd_t fd, u_char *buf, size_t size, off_t offset)
{
    u_long      n;
    OVERLAPPED  ovlp, *povlp;

    ovlp.Internal = 0;
    ovlp.InternalHigh = 0;
    ovlp.Offset = (u_long) offset;
    ovlp.OffsetHigh = 0;//(u_long) (offset >> 32);
    ovlp.hEvent = NULL;

    povlp = &ovlp;

    if (WriteFile(fd, buf, size, &n, povlp) == 0) {
        return -1;
    }

    if (n != size) {
        return -1;
    }

    return n;
}

int yun_close_file(yun_fd_t fd)
{
    return CloseHandle(&fd);
}

uint64_t yun_fs_free_size(const char *name)
{
    char  root[4];
    u_long  sc, bs, nfree, ncl;

    if (name[2] == ':') {
        strncpy(root, (char*)name, 4);
        name = root;
    }

    if (GetDiskFreeSpace((const char *) name, &sc, &bs, &nfree, &ncl) == 0) {
        return 512;
    }

    return sc * bs * (uint64_t)nfree;
}

uint64_t yun_fs_busy_size(const char *name)
{
    char  root[4];
    u_long  sc, bs, nfree, ncl;

    if (name[2] == ':') {
        strncpy(root, (char*)name, 4);
        name = root;
    }

    if (GetDiskFreeSpace((const char *) name, &sc, &bs, &nfree, &ncl) == 0) {
        return 512;
    }

    return sc * bs * (uint64_t)(ncl - nfree);
}

