#ifndef __SYS_UTILITY_H__
#define __SYS_UTILITY_H__

#ifdef __UTILITY_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE void panic(const char *fmt, ...);
INTERFACE int diag_printf(const char *fmt, ...);

#undef INTERFACE
#endif

