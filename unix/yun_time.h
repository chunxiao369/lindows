/**
 * @file yun_time.h
 * @Synopsis  time realization in unix
 * @author xuchunxiao369@gmail.com
 * @version 0.9.6
 * @date 2012-09-01
 */

#ifndef __YUN_TIME_H__
#define __YUN_TIME_H__
#include <sys/time.h>

#define yun_gettimeofday(tp)  (void) gettimeofday(tp, NULL);
#define yun_msleep(ms)        (void) usleep(ms * 1000)
#define yun_sleep(s)          (void) sleep(s)
#endif
