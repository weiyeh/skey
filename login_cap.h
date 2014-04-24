/*
 * *BSD login_cap.h emulation
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

#ifdef HAVE_SYS_CDEFS_H
#   include <sys/cdefs.h>
#else
#   include "cdefs.h"
#endif
__BEGIN_DECLS
struct passwd;

#define LOGIN_SETGROUP          0x0001  /* Set group */
#define LOGIN_SETLOGIN          0x0002  /* Set login */
#define LOGIN_SETPATH           0x0004  /* Set path */
#define LOGIN_SETPRIORITY       0x0008  /* Set priority */
#define LOGIN_SETRESOURCES      0x0010  /* Set resource limits */
#define LOGIN_SETUMASK          0x0020  /* Set umask */
#define LOGIN_SETUSER           0x0040  /* Set user */
#define LOGIN_SETALL            0x007f  /* Set all. */

typedef struct {
	char    *lc_class;
	char    *lc_cap;
	char    *lc_style;
} login_cap_t;

int     setusercontext __P((login_cap_t *, struct passwd *, uid_t, u_int));

