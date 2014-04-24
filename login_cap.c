/*
 * *BSD login_cap functions...
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

#ifndef HAVE_SETUSERCONTEXT
 
#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <syslog.h>

/* 
 * We do not try to include system login_cap.h because we know 
 * it doesn't contain our function...
 */
#include "login_cap.h"


int setusercontext(lc, pwd, uid, flags)
	login_cap_t *lc;
	struct passwd *pwd;
	uid_t uid;
	u_int flags;
{

	/*
	 * Without the pwd entry being passed we cannot set either
	 * the group or the login.  We could complain about it.
	 */
	if (pwd == NULL)
		flags &= ~(LOGIN_SETGROUP|LOGIN_SETLOGIN);

	if (flags & LOGIN_SETRESOURCES) {
		/* Do nothing for now */
	}

	if (flags & LOGIN_SETPRIORITY) {
		/* Do nothing for now */
	}

	if (flags & LOGIN_SETUMASK) {
		/* Do nothing for now */
	}

	if (flags & LOGIN_SETGROUP) {
		(void) setegid(pwd->pw_gid);
		if(setgid(pwd->pw_gid) < 0) {
			syslog(LOG_ERR, "setgid(%d): %m", pwd->pw_gid);
			return (-1);
		}

		if(initgroups(pwd->pw_name, pwd->pw_gid) < 0) {
			syslog(LOG_ERR, "initgroups(%s,%d): %m",
					pwd->pw_name, pwd->pw_gid);
			return (-1);
		}

	}

	if (flags & LOGIN_SETLOGIN) {
#ifdef HAVE_SETLOGIN
		if(setlogin(pwd->pw_name) < 0) {
			syslog(LOG_ERR, "setlogin(%s) failure: %m",
					pwd->pw_name);
			return (-1);
		}
#else
		/* Do nothing for now */
#endif
	}

	if (flags & LOGIN_SETUSER) {
		(void) seteuid(uid);
		if(setuid(uid) < 0) {
			syslog(LOG_ERR, "setuid(%d): %m", uid);
			return (-1);
		}
	}

	if (flags & LOGIN_SETPATH) {
		/* Do nothing for now */
	}

	return (0);

}


#endif

