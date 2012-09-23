#include "yun_win32.h"
void *yun_memalign(size_t boundary, size_t size)
{
    return malloc(size);
}
