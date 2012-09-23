#include <yun_files.h>
#include <yun_socket.h>
#include <yun_sys.h>
#include <yun_time.h>

int test_files(void)
{
    yun_dir_t dir;
    int ret = 0;
    ret = yun_open_dir("notexit", &dir);
    if (ret == 0) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }
    ret = yun_open_dir("unix", &dir);
    if (ret) {
        printf("error! func: %s, line: %d.\n", __func__, __LINE__);
        return 1;
    }
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

