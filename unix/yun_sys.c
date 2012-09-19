#include <yun_unix.h>
void *yun_memalign(size_t boundary, size_t size)
{
    return memalign(boundary, size);
}
