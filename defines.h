#ifndef _DEFINES_H
#define _DEFINES_H

/* Necessary headers */

#include <sys/types.h> 

#ifdef HAVE_SYS_BITYPES_H
# include <sys/bitypes.h> /* For u_intXX_t */
#endif 

#ifdef HAVE_PATHS_H
# include <paths.h> /* For _PATH_XXX */
#endif

#ifdef HAVE_SYS_CDEFS_H
# include <sys/cdefs.h>  /* For __P() */
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
#ifndef PASS_MAX
#define PASS_MAX 255
#endif

/* If sys/types.h does not supply intXX_t, supply them ourselves */
/* (or die trying) */
#ifndef HAVE_INTXX_T
# if (SIZEOF_CHAR == 1)
typedef char int8_t;
# else
#  error "8 bit int type not found."
# endif
# if (SIZEOF_SHORT_INT == 2)
typedef short int int16_t;
# else
#  error "16 bit int type not found."
# endif
# if (SIZEOF_INT == 4)
typedef int int32_t;
# else
#  error "32 bit int type not found."
# endif
# if (SIZEOF_LONG_INT == 8)
typedef long int int64_t;
# else
#  if (SIZEOF_LONG_LONG_INT == 8)
typedef long long int int64_t;
#   define HAVE_INTXX_T 1
#  else
#   error "64 bit int type not found."
#  endif
# endif
#endif

/* If sys/types.h does not supply u_intXX_t, supply them ourselves */
#ifndef HAVE_U_INTXX_T
# ifdef HAVE_UINTXX_T
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef  uint64_t u_int64_t;
# define HAVE_U_INTXX_T 1
# else
#  if (SIZEOF_CHAR == 1)
typedef unsigned char u_int8_t;
#  else
#   error "8 bit int type not found."
#  endif
#  if (SIZEOF_SHORT_INT == 2)
typedef unsigned short int u_int16_t;
#  else
#   error "16 bit int type not found."
#  endif
#  if (SIZEOF_INT == 4)
typedef unsigned int u_int32_t;
#  else
#   error "32 bit int type not found."
#  endif
#  if (SIZEOF_LONG_INT == 8)
typedef unsigned long int u_int64_t;
#  else
#   if (SIZEOF_LONG_LONG_INT == 8)
typedef unsigned long long int u_int64_t;
#    define HAVE_U_INTXX_T 1
#   else
#    error "64 bit int type not found."
#   endif
#  endif
# endif
#endif


/* Paths */
#ifndef _PATH_MEM
#  define _PATH_MEM "/dev/mem"
#endif


#ifndef __P
#define __P(x) x
#endif


#endif /* _DEFINES_H */
