/**
 * \file            lwmem_sys_win32.c
 * \brief           System functions for WIN32
 */

/*
 * Copyright (c) 2022 Tilen MAJERLE
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of LwMEM - Lightweight dynamic memory manager library.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 * Version:         v2.0.0
 */
#include "system/lwmem_sys.h"

#if LWMEM_CFG_OS && !__DOXYGEN__

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t
lwmem_sys_mutex_create(LWMEM_CFG_OS_MUTEX_HANDLE* m) {
	 *m = malloc(sizeof(pthread_mutex_t));
	    if (*m == NULL) {
	        return 0;
	    }

	    if (pthread_mutex_init(*m, NULL) != 0) {
	        free(*m);
	        return 0;
	    }
	    return 1;
}

uint8_t
lwmem_sys_mutex_isvalid(LWMEM_CFG_OS_MUTEX_HANDLE* m) {
    if (m == NULL || *m == NULL) {
	        return 0;
	    }
	    return 1;
}

uint8_t
lwmem_sys_mutex_wait(LWMEM_CFG_OS_MUTEX_HANDLE* m) {
	pthread_mutex_t *mutex = (pthread_mutex_t *) m;
	struct timespec abstime;

	/* set absolute time to now + 5 seconds */
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += 5;

    /* try to relock the first mutex */
    pthread_mutex_timedlock(mutex, &abstime);
	
    return 1;
}

uint8_t
lwmem_sys_mutex_release(LWMEM_CFG_OS_MUTEX_HANDLE* m) {
	pthread_mutex_t *mutex = (pthread_mutex_t *) m;
    pthread_mutex_unlock(mutex);
    return 1;
}

#endif /* LWMEM_CFG_OS && !__DOXYGEN__ */
