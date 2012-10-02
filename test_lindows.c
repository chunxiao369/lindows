#include <yun_files.h>
#include <yun_socket.h>
#include <yun_sys.h>
#include <yun_time.h>

int test_files(void)
{
    yun_dir_t dir;
    yun_fd_t fd;
    u_char buf[16];
    int ret = 0;
    int size = 128;
    int offset = 0;

    /* open dir not valid */
    ret = yun_open_dir("notexit", &dir);
    if (ret == 0) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }

    /* read valid dir and open it */
    ret = yun_open_dir("unix", &dir);
    if (ret) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }
    ret = yun_read_dir(&dir);
    if (ret) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }

    /* open noexit file readonly */
    fd = yun_open_file("notexit", YUN_FILE_RDONLY, 0);
    if (fd != YUN_INVALID_FILE) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }

    /* open noexit file writeonly; write something; close file */
    fd = yun_open_file("notexit", YUN_FILE_WRONLY, 0);
    if (fd == YUN_INVALID_FILE) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }
    while (offset < 256) {
        strcpy(buf, "0123456789abcdef");
        ret = yun_write_file(fd, buf, 16, offset);
        if (ret) {
            printf("error! func: %s, line: %d.\n", __func__, __LINE__);
            return 1;
        }
        offset += 16;
    }
    yun_close_file(&fd);

    /* open noexit file writeonly; write something; close file */
    fd = yun_open_file("notexit", YUN_FILE_RDONLY, 0);
    if (fd == YUN_INVALID_FILE) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }
    offset = 0;
    while (1) {
        ret = yun_read_file(fd, buf, 16, offset);
        printf("buf: %s.\n", (char *)buf);
        if (ret) {
            break;
        }
        offset += 16;
    }
    yun_close_file(&fd);
    return 0;
}

int test_socket(void)
{
    return 0;
}

int test_sys(void)
{
    return 0;
}

int test_time(void)
{
    return 0;
}

int main(int argc, char *argv[])
{
    if (test_files()) {
        printf("test files not passed.\n");
    }
    if (test_socket()) {
        printf("test sockets not passed.\n");
    }
    if (test_sys()) {
        printf("test system not passed.\n");
    }
    if (test_time()) {
        printf("test time not passed.\n");
    }
    printf("test passed.\n");
    return 0;
}

