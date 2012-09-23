
#ifndef __YUN_FILES_H__
#define __YUN_FILES_H__

#include "yun_win32.h"
typedef struct {
    HANDLE                          dir;
    WIN32_FIND_DATA                 finddata;
} yun_dir_t;

int yun_open_dir(const char *name, yun_dir_t *dir);
int yun_read_dir(yun_dir_t *dir);

#define yun_de_name(dir)            ((u_char *) (dir)->finddata.cFileName)
#define yun_de_namelen(dir)         strlen((dir)->finddata.cFileName)
#define yun_close_dir(d)            FindClose((d)->dir)

#define YUN_FILE_RDONLY             GENERIC_READ
#define YUN_FILE_WRONLY             GENERIC_WRITE
#define YUN_FILE_RDWR               GENERIC_READ|GENERIC_WRITE
#define YUN_FILE_APPEND             FILE_APPEND_DATA|SYNCHRONIZE

#define YUN_FILE_DEFAULT_ACCESS     0
#define YUN_FILE_OWNER_ACCESS       0

#define YUN_INVALID_FILE            INVALID_HANDLE_VALUE
#define YUN_FILE_ERROR              0

typedef HANDLE yun_fd_t;
yun_fd_t yun_open_file(const char *name, u_long mode, u_long access);
#define yun_close_file              CloseHandle
#define yun_file_access(fi) 0

int yun_read_file(yun_fd_t fd, u_char *buf, size_t size, off_t offset);
int yun_write_file(yun_fd_t fd, u_char *buf, size_t size, off_t offset);

size_t yun_fs_free_size(u_char *name);
#define yun_getcwd(buf, size)       GetCurrentDirectory(size, (char *) buf)
#endif
