/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright MSTAR SAS (c) 2007
*/

/***************************************************************************/
/*  File       : SYS_SYS_MATH.H                                                */
/*-------------------------------------------------------------------------*/
/*  Scope      : Useful math functions and macros                          */
/*                                                                         */
/*  Content    :                                                           */
/*                                                                         */
/*  Change     :                                                           */
/*-------------------------------------------------------------------------*/ 
/***************************************************************************
 * --------------------------------------------------------------------------
 *  Date     | Author | Revision       | Description
 * ----------+--------+----------------+-------------------------------------
 *  25.07.07 | OLA    | 1.0            | Initial revision.               
 * ----------+--------+----------------+-------------------------------------
 ***************************************************************************/

#ifndef __SYS_SYS_MATH_H__
#define __SYS_SYS_MATH_H__

//**************************************************************************************
// Note : these macros and functions were written using document "Bit Twiddling Hacks",*
//        available at http://graphics.stanford.edu/~seander/bithacks.html             *
//        as well as GNU gmp lib available at http://gmplib.org/                       *
//**************************************************************************************

//=======================================================================
// Headers
//=======================================================================
#ifdef _WIN32

// Windows necessary include files
#include "limits.h"
#include <stdlib.h>

// Our own types
typedef unsigned long long  u64;
typedef long long           s64;
typedef unsigned int        u32;
typedef signed int          s32;
typedef unsigned short      u16;
typedef signed short        s16;
typedef unsigned char       u8;
typedef signed char         s8;
typedef char                bool;

#else

#include "stdcomp.h"
#include "limits.h"

#endif


//=======================================================================
// Macros
//=======================================================================

/*
 * Useful macros
 */
#define ARRAY_CNT(array,type)    (sizeof(array)/sizeof(type))        // Array element count

/*
 * Min, max
 */
#ifndef MIN
#define MIN(a,b)                 ((a)<(b)?(a):(b))                   // Min of anything
#endif
#define IMIN(a,b)                ((b) + (((a) - (b)) & -((a) < (b))))// Integer minimum

#ifndef MAX
#define MAX(a,b)                 ((a)>=(b)?(a):(b))                  // Max of anything
#endif
#define IMAX(a,b)                ((a) - (((a) - (b)) & -((a) < (b))))// Integer maximum

#define MINMAX(var,a,b)          (var<(a)?(a):(var>(b)?(b):var))     // Bound anything
#define IMINMAX(var,a,b)         (IMIN(IMAX(var,a),b))               // Bound integers

/*
 * Average
 */
#define AVG(a,b)                 (((a)+(b))/2)                       // Average of anything

/*
 * Absolute values
 */
#ifndef ABS
#define ABS(a)                   ((a)<(0)?-(a):(a))                                    // Absolute value of anything
#endif
#define IABS(a)                  (((a) ^ ((a) >> (sizeof(a) * CHAR_BIT - 1))) - \
                                  ((a) >> (sizeof(a) * CHAR_BIT - 1)))                 // Integer absolute value
/*
 * Sign
 */
#define ISIGN(a)                 (+1 | ((a) >> (sizeof(a) * CHAR_BIT - 1)))            // Integer sign

/*
 * Modulo
 */
#define MOD(a,mod)              (ISIGN(a)<0 ? ((a)%(mod))+(mod) : (a)%(mod))           // Modulo for negative number
                                                                                       // Result is between 0 and mod-1
                                                                                       // whatever its sign (remind : 0<x<y => (-x%y)=-x)

/*
 * Round float value
 */
#define ROUND(a)                 ((int)(a) + ((int)(a*2.0) & 0x1)*ISIGN((int)(a)))    // Round a float to the nearest integer value

/*
 * Unsigned substraction (useful for time counters...)
 */
#define _SUB(a,b,max)            (a>=b?a-b:max-b+a+1)                         // Internal use only !
#define USUB(a,b,max)            _SUB((u32)(a),(u32)(b),(u32)(max))           // Compute unsigned a-b
#define TSUB(a,b)                USUB(a,b,(U32_MAX>>(32-(sizeof(b)<<3))))     // Compute unsigned a-b. For integer variables only, not expressions

/*
 * Swap
 */
#define ISWAP(a,b)               {a^=b; b=b^a; a^=b;}                   // Swap integers with 3 XOR !!!
#define SWAP(a,b,type)           {type temp=(b); (b)=(a); (a)=temp;}    // Swap anything, using the obvious way

/*
 * Power/Log
 */
#define POWER10(p)               sys_Power10(p)                         // Res = 10^p
#define INTLOG10(p)              sys_IntLog10(p)                        // Integer log base 10

/*
 * Fixed point Operations
 */
#define MAX_DECIMAL_NB           5                                      // 5 decimal maximum

// Notes on decimals numbers :
//   1) When using multiplication, integer and fractional part must be 16 bit wide, not more
//      otherwise overflow can occur and results would be inaccurate.
//      Use function "sys_MulReady" to know whether a decimal variable is ready for safe multiplication
//   2) The parameter "p" is the number of decimals to be computed
//      The parameter "f" is a precision factor

#define MUL_DEC2INT(a,b)         sys_MulDec2Int(a,b)                    // Multiply 2 decimals, give int result.
#define MUL_DEC2DEC(a,b)         sys_MulDec2Dec(a,b)                    // Multiply 2 decimals, give decimal result
#define DIV_INT2DEC(a,b,p)       sys_DivInt2Dec(a,b,p)                  // Divide 2 integers, give decimal result

#define DIV_INT2FRAC(a,b,f)      ( ((a*f)/b) - ((a/b)*f) )              // Get the fractionnal part of a/b
#define DIV_N_CEIL(a,b,f)        ( (((a*f)/b)+f-1) / f )                // Integer division with ceiling
#define DIV_N_ROUND(a,b,f)       ( (((a*f)/b)+f/2-1) / f )              // Integer division with rounding up or down, 
                                                                        // depending on the fractional part.

#define MAX_DECIMAL(a,b)         sys_MaxDec(a,b)                        // Get max of 2 decimal nb
#define MIN_DECIMAL(a,b)         sys_MinDec(a,b)                        // Get min of 2 decimal nb

#define GETDEC(a,b,p)            sys_GetDecimal(a,b,p)
#define INT2DEC(a)               GETDEC(a,0,0)
#define DEC2INT(a)               a.nInt
/*
 * Fixed point decimal number representation
 */
typedef struct decimal_s
{
   s32 nInt;
   s32 nFrac;
   u8  nbDec;
} decimal_t;

//=======================================================================
// Functions prototypes
//=======================================================================
u8                sys_IntLog10(const u32 v);
u32               sys_Power10(const u8 p);

bool              sys_MulReady(const decimal_t* const num);
s32               sys_MulDec2Int(decimal_t a, decimal_t b);
decimal_t         sys_MulDec2Dec(decimal_t a, decimal_t b);
decimal_t         sys_DivInt2Dec(s32 a, s32 b, u8 p);

const decimal_t*  sys_MinDec(const decimal_t* const a, const decimal_t* const b);
const decimal_t*  sys_MaxDec(const decimal_t* const a, const decimal_t* const b);

void              sys_SetNbDecimal(decimal_t* const num, u8 p);
u8                sys_SetMinNbDecimal(decimal_t* const a, decimal_t* const b);
u8                sys_SetMaxNbDecimal(decimal_t* const a, decimal_t* const b);

#endif // __SYS_SYS_MATH_H__

// END OF FILE

