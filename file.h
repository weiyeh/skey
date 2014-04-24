#ifndef _SYS_FILE_H
#define _SYS_FILE_H

#ifndef _FCNTL_H
# include <fcntl.h>
#endif

#ifndef LOCK_SH
#define LOCK_SH  1               /* Shared lock. */
#endif
#ifndef LOCK_EX
#define LOCK_EX  2               /* Exclusive lock. */
#endif
#ifndef LOCK_UN
#define LOCK_UN  8               /* Unlock. */
#endif
#ifndef LOCK_NB
#define LOCK_NB  4               /* Don't block when locking. */
#endif


extern int flock(int fd, int operation);


#endif  /* _SYS_FILE_H */
