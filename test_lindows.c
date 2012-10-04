#include <yun_files.h>
#include <yun_socket.h>
#include <yun_sys.h>
#include <yun_time.h>

int test_files(void)
{
    yun_dir_t dir;
    yun_fd_t fd;
    u_char buf[18];
    int ret = 0;
    int len;
    int offset = 0;

    /* open dir not valid */
    ret = yun_open_dir("notexit", &dir);
    if (ret == 0) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }

    /* read valid dir and open it */
    memset(&dir, 0, sizeof(yun_dir_t));
    ret = yun_open_dir("win32", &dir);
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
        memset(buf, 0, 17);
        sprintf((char*)buf, "%d\n", offset);
        len = strlen((char*)buf);
        ret = yun_write_file(fd, buf, len, offset);
        if (ret <= 0) {
            printf("error! func: %s, line: %d.\n", __func__, __LINE__);
            return 1;
        }
        offset += len;
    }
    yun_close_file(fd);

    /* open noexit file writeonly; write something; close file */
    fd = yun_open_file("notexit", YUN_FILE_RDONLY, 0);
    if (fd == YUN_INVALID_FILE) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }
    offset = 0;
    while (1) {
        ret = yun_read_file(fd, buf, 16, offset);
        //printf("%s", (char *)buf);
        if (ret <= 0) {
            break;
        }
        offset += 16;
    }
    yun_close_file(fd);
    printf("used: %llu, free: %llu.\n", yun_fs_busy_size("D:"),
           yun_fs_free_size("D:"));
    printf("used: %llu, free: %llu.\n", yun_fs_busy_size("E:"),
           yun_fs_free_size("E:"));
#if 0
    printf("used: %llu, free: %llu.\n", yun_fs_busy_size("/run"),
           yun_fs_free_size("/run"));
    printf("used: %llu, free: %llu.\n", yun_fs_busy_size("/mnt/virtual-disk"),
           yun_fs_free_size("/mnt/virtual-disk"));
    printf("used: %llu, free: %llu.\n", yun_fs_busy_size("/mnt/E-disk"),
           yun_fs_free_size("/mnt/E-disk"));
#endif
    return 0;
}

int test_socket(void)
{
    printf("local ip: %s.\n", get_local_ip_address());
    return 0;
}

int test_sys(void)
{
    return 0;
}

int test_time(void)
{
	struct timeval tv;
	yun_gettimeofday(&tv);
	printf("second: %ld, usecond: %ld.\n", tv.tv_sec, tv.tv_usec);
    yun_msleep(1);
	yun_gettimeofday(&tv);
	printf("second: %ld, usecond: %ld.\n", tv.tv_sec, tv.tv_usec);
    yun_sleep(1);
	yun_gettimeofday(&tv);
	printf("second: %ld, usecond: %ld.\n", tv.tv_sec, tv.tv_usec);
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

