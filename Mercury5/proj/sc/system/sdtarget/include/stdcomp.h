/******************************************************************************/
/*  File    : stdcomp.h                                                       */
/*----------------------------------------------------------------------------*/
/*  Scope   :                                                                 */
/*                                                                            */
/******************************************************************************/

#ifndef __STDCOMP_H__
#define __STDCOMP_H__

//------------------------------------------------------------------------------
// Portable types
//------------------------------------------------------------------------------

#ifdef __arm

typedef unsigned char   bool;
typedef unsigned char   u8;
typedef signed   char   s8;
typedef          char   ascii;
typedef unsigned short  u16;
typedef          short  s16;
typedef unsigned long   u32;
typedef          long   s32;
typedef unsigned long long u64;

#endif


#define FALSE   0
#define TRUE    1


#ifndef NULL
# define    NULL    0
#endif

#ifndef false
# define    false   0
#endif

#ifndef true
# define    true    (!false)
#endif

#ifndef offsetof
#define offsetof(S,F)           (u32) (((u8*)&(((S *) 0)->F))-((u8*)0))
#endif

#define _PROTO(X)               X

/* CLK frequencies */
#define CLK_312MHZ          312000000
#define CLK_208MHZ          208000000
#define CLK_156MHZ          156000000
#define CLK_124M80HZ        124800000
#define CLK_104MHZ          104000000
#define CLK_96MHZ           96000000
#define CLK_89M14HZ         89140000
#define CLK_78MHZ           78000000
#define CLK_69M33HZ         69330000
#define CLK_62M40HZ         62400000
#define CLK_60MHZ           60000000
#define CLK_56M73HZ         56730000
#define CLK_52MHZ           52000000
#define CLK_48MHZ           48000000
#define CLK_44M57HZ         44570000
#define CLK_39MHZ           39000000
#define CLK_34M67HZ         34670000
#define CLK_31M20HZ         31200000
#define CLK_30MHZ           30000000
#define CLK_26MHZ           26000000
#define CLK_24MHZ           24000000
#define CLK_22M29HZ         22290000
#define CLK_20M80HZ         20800000
#define CLK_19M50HZ         19500000
#define CLK_15M60HZ         15600000
#define CLK_15MHZ           15000000
#define CLK_13MHZ           13000000
#define CLK_12MHZ           12000000
#define CLK_10M40HZ         10400000
#define CLK_6MHZ            6000000
#define CLK_1M02HZ          1020000
#define CLK_750KHZ          750000
#define CLK_190KHZ          190000
#define CLK_OFF             0


// -------------------------------------------------------------------------
// Allow creation of procedure-like macros that are a single statement,
// and must be followed by a semi-colon

#define SYS_MACRO_START do {
#define SYS_MACRO_END   } while (0)

#define SYS_EMPTY_STATEMENT CYG_MACRO_START CYG_MACRO_END

#endif /* __STDCOMP_H__ */
