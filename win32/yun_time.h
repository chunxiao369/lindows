
#ifndef __YUN_TIME_H__
#define __YUN_TIME_H__
#include "yun_win32.h"
void yun_gettimeofday(struct timeval *tp);
#define yun_msleep            Sleep
#define yun_sleep(x)          Sleep(1000 * (x))
#endif
