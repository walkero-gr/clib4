/*
  $Id: pthread_condattr_setclock.c,v 1.00 2022-09-20 12:09:49 clib2devs Exp $
*/

#ifndef _TIME_HEADERS_H
#include "time_headers.h"
#endif /* _TIME_HEADERS_H */

#ifndef _STDIO_HEADERS_H
#include "stdio_headers.h"
#endif /* _STDIO_HEADERS_H */

#ifndef _UNISTD_HEADERS_H
#include "unistd_headers.h"
#endif /* _UNISTD_HEADERS_H */

#include "common.h"
#include "pthread.h"

int
pthread_condattr_setclock(pthread_condattr_t *a, clockid_t clk) {
    if (clk < 0 || clk - 2U < 2)
        return EINVAL;
    a->pshared &= 0x80000000;
    a->pshared |= clk;
    return 0;
}
