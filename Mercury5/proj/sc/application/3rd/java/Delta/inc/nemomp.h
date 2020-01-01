#ifndef __NEMOMP_H__
#define __NEMOMP_H__

#define JAVA_LIB_VERSION "j9midp: 1.0.0.62"

//add by Delta
#include "nemomp_comp_opt.h"
#include "ven_setting.h" //.2009.09.11 for l10n
#include <setjmp.h> // 20081124: Added
//#include "ven_std.h"
//#include <assert.h>
#define ASSERT(expr) //nemomp_assert(expr, __FILE__, __LINE__);


#define JAMLIST_MEM_POOL_SIZE	 102400	// 100K

#define NO_JAVA_LOGO


#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN	1
#endif

#define TCK_UART_PORT 1 // 20081127: Added, Moved from nemomp_jam_tck.c

typedef enum
{
  NM_FALSE,
  NM_TRUE
} nm_bool;

typedef unsigned char           nm_uint8;
typedef signed char             nm_int8;
typedef char                    nm_char;
typedef unsigned short          nm_wchar;
typedef unsigned short int      nm_uint16;
typedef signed short int        nm_int16;
typedef unsigned int            nm_uint32;
typedef signed int              nm_int32;
#ifndef WIN32
typedef unsigned long long   nm_uint64;
typedef signed long long     nm_int64;
#else
typedef __int64 nm_int64;
typedef unsigned __int64 nm_uint64;
#endif
typedef signed long    INT32;
typedef unsigned long           UNSIGNED;

typedef unsigned int			UINT;

extern jmp_buf java_jmpbuf; // 20081124: Added

extern void nemomp_sleep(unsigned int time_in_ticks);
extern char* nemomp_get_osType(void);
extern char* nemomp_get_os_version(void);
extern int nemomp_get_prcess_id(void);

extern char* nemomp_get_current_locale_code(void); // 20090910: Added

extern void nemomp_logging(char *s);

extern int nemomp_wsprintf(nm_wchar* buffer, char *fmt, ...);
extern const u8* JavaDelta_GetVersionInfo(void);

#endif /* __NEMOMP_H__ */

