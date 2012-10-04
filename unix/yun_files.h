
#ifndef __YUN_FILES_H__
#define __YUN_FILES_H__

#include <yun_unix.h>
typedef struct {
    DIR                         *dir;
    struct dirent               *de;
    struct stat                  info;
} yun_dir_t;

int yun_open_dir(const char *name, yun_dir_t *dir);
int yun_read_dir(yun_dir_t *dir);
#define yun_close_dir(d)         closedir((d)->dir);

#define YUN_INVALID_FILE         -1
#define YUN_FILE_DEFAULT_ACCESS  0644
#define YUN_FILE_RDONLY          O_RDONLY
#define YUN_FILE_WRONLY          (O_WRONLY | O_CREAT)
#define YUN_FILE_RDWR            O_RDWR
#define YUN_FILE_CREATE          O_CREAT
typedef int                      yun_fd_t;
#define yun_open_file(name, mode, access) \
    open((const char *) name, mode, access)

int yun_read_file(yun_fd_t fd, u_char *buf, size_t size, off_t offset);
int yun_write_file(yun_fd_t fd, u_char *buf, size_t size, off_t offset);
#define yun_close_file           close
#define yun_de_name(dir)         ((u_char *) (dir)->de->d_name)
int yun_file_access(const char* name);
#define yun_getcwd(buf, size)    (getcwd((char *) buf, size) != NULL)
uint64_t yun_fs_busy_size(const char *name);
uint64_t yun_fs_free_size(const char *name);
#endif
