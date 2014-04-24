#include <stdarg.h>
void errx __P((int eval, const char *fmt, ...));
void warnx __P((const char *fmt, ...));
void err __P((int eval,const char *fmt,...));
void warn __P((const char *fmt,...));
