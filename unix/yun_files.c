/**
 * @file yun_files.c
 * @Synopsis
 * @author xu.chunxiao@embedway.com
 * @version 0.1.1
 * @date 2014-09-24
 */
#include <yun_files.h>

int yun_open_dir(const char *name, yun_dir_t *dir)
{
    dir->dir = opendir((const char *)name);

    if (dir->dir == NULL) {
        return 1;
    }
    return 0;
}

int yun_read_dir(yun_dir_t *dir)
{
    dir->de = readdir(dir->dir);
    if (dir->de) {
        return 0;
    }
    return 1;
}

int yun_file_access(const char *name)
{
    return access(name, 0);
}

int yun_read_file(yun_fd_t fd, u_char *buf, size_t size, off_t offset)
{
    int n;
    if (lseek(fd, offset, SEEK_SET) == -1) {
        return -1;
    }
    n = read(fd, buf, size);
    if (n == -1) {
        return -1;
    }
    return n;
}

int yun_write_file(yun_fd_t fd, u_char *buf, size_t size, off_t offset)
{
    ssize_t  n, written;
    if (lseek(fd, offset, SEEK_SET) == -1) {
        return -1;
    }
    written = 0;
    for ( ;; ) {
        n = write(fd, buf + written, size);

        if (n == -1) {
            return -1;
        }

        written += n;

        if ((size_t) n == size) {
            return written;
        }

        size -= n;
    }
    return -1;
}

uint64_t yun_fs_busy_size(const char *name)
{
    struct statfs diskInfo;
    uint64_t disk_size;
    statfs(name, &diskInfo);
    disk_size = (uint64_t)(diskInfo.f_blocks - diskInfo.f_bavail) * (uint64_t)diskInfo.f_bsize;
    return disk_size;
#if 0
    struct statvfs  fs;

    if (statvfs((char *) name, &fs) == -1) {
        return 512;
    }

    if ((fs.f_bsize % 512) != 0) {
        return 512;
    }

    return (size_t) fs.f_bsize;
#endif
}

uint64_t yun_fs_free_size(const char *name)
{
    struct statfs diskInfo;
    uint64_t disk_size;
    statfs(name, &diskInfo);
    disk_size = (uint64_t)diskInfo.f_bavail * (uint64_t)diskInfo.f_bsize;
    return disk_size;
}
