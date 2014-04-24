/*
 * *BSD compatibility functions: flock
 * 
 * Yuri Yudin <jjb@sparc.spb.su>
 *
 * Copyright 2000 Yuri Yudin
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT.  IN NO EVENT SHALL DAMIEN MILLER OR INTERNET
 * BUSINESS SOLUTIONS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "config.h"

#ifndef HAVE_FLOCK

#ifdef HAVE_SYS_FILE_H
#include <sys/file.h>
#else
#include "file.h"
#endif

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#include "file.h"

#include <errno.h>
#include <string.h>

#  ifdef HAVE_FCNTL
int flock(int fd, int operation) {
    struct flock flck;
    int cmd, rc;

    memset((char *)&flck, 0x00, sizeof(struct flock));

    if (operation & LOCK_NB) {
	cmd = F_SETLK;
	operation &= ~LOCK_NB;  
    } else
	cmd = F_SETLKW;
    
    switch(operation) {
    case LOCK_UN:
	flck.l_type |= F_UNLCK;
	break;
    case LOCK_SH:
	flck.l_type |= F_RDLCK;
	break;
    case LOCK_EX:
	flck.l_type |= F_WRLCK;
	break;
    default:
	errno = EINVAL;
	return (-1);
    }

    if((rc = fcntl(fd, cmd, &flck)) == -1 && errno == EACCES)
	errno = EWOULDBLOCK;

    return (rc);
}

#  else

#    error "Panic: Do not have either flock or fcntl"

#  endif  /* HAVE_FCNTL */

#endif /* HAVE_FLOCK */
