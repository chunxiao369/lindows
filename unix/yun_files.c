#include <yun_unix.h>
#include <yun_files.h>

int yun_open_dir(char *name, yun_dir_t *dir)
{
    dir->dir = opendir((const char *)name);

    if (dir->dir == NULL) {
        return 1;
    }
    return 0;
}

size_t
yun_fs_bsize(u_char *name)
{
    struct statvfs  fs;

    if (statvfs((char *) name, &fs) == -1) {
        return 512;
    }

    if ((fs.f_bsize % 512) != 0) {
        return 512;
    }

    return (size_t) fs.f_bsize;
}

