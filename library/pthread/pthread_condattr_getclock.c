/*
  $Id: pthread_condattr_getclock.c,v 1.00 2022-09-20 12:09:49 clib2devs Exp $
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
pthread_condattr_getclock(const pthread_condattr_t *restrict a, clockid_t *restrict clk) {
    *clk = a->pshared & 0x7fffffff;
    return 0;
}