
#ifndef __YUN_FILES_H__
#define __YUN_FILES_H__

#include <yun_unix.h>
typedef struct {
    DIR                         *dir;
    struct dirent               *de;
    struct stat                  info;
} yun_dir_t;

int yun_open_dir(char *name, yun_dir_t *dir);
#define yun_close_dir(d)         closedir((d)->dir);
size_t yun_fs_bsize(u_char *name);
#define yun_getcwd(buf, size)    (getcwd((char *) buf, size) != NULL)
#endif
