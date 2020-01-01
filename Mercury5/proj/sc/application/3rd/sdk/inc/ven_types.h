#ifndef __VEN_TYPES_H__
#define __VEN_TYPES_H__

#if defined(__arm) || defined(__aeon__)

#include "vm_types.ht"

#elif (defined __SDK_SIMULATION__)

typedef unsigned _int8          u8;
typedef unsigned _int16         u16;
typedef unsigned _int32         u32;

typedef _int8                   s8;
typedef _int16                  s16;
typedef _int32                  s32;

typedef          char           ascii;

#else

/* ERROR */

#endif

#ifndef __cplusplus
#ifndef __bool_defined
#define  __bool_defined
typedef unsigned char bool;
#endif
#endif

#define FALSE 0
#define TRUE  1

#ifndef NULL
#define NULL                     0
#endif  // NULL

#endif /* __VEN_TYPES_H__ */
