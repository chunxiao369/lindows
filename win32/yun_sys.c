
#include <windows.h>
void *yun_memalign(size_t boundary, size_t size)
{
    return malloc(size);
}
