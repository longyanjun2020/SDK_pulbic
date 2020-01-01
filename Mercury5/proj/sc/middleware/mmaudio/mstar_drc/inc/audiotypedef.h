
#ifndef _AUDIOTYPEDEF_H_
#define _AUDIOTYPEDEF_H_

typedef unsigned int    U32;
typedef   signed int    S32;
typedef unsigned short  U16;
typedef   signed short  S16;
typedef unsigned char   U8;
typedef   signed char   S8;
typedef long long       S64;


#define MIN_32  (0x80000000)
#define MAX_32  (0x7fffffff)

static __inline void f_DIV_31 (S32 *r, S32 dividend, S32 divisor)
{
    int negative_quotient;
    S32 result;
    int ii;

    /* FPARITH_TRAP_IF (divisor == 0, DSP_FIX_DIVISION_BY_ZERO); */

    if (divisor == 0 || dividend == 0)
    {
        *r = 0;
        return;
    }

    negative_quotient = (dividend&0x80000000) ^ (divisor&0x80000000);

    /* note that if the value being negated is MIN_32, the result is
    * still negative if treated as Signed.  So be careful to cast to
    * an unsigned value where it matters */

    if (dividend < 0)
    {
        dividend = -dividend;
    }

    if (divisor < 0)
    {
        divisor = -divisor;
    }

    if ((U32) divisor <= (U32) dividend)
    {
        *r = negative_quotient ? MIN_32 : MAX_32;
        return;
    }

    result = 0;

    /* note that this loop truncates result (i.e. rounds downwards) */
    for (ii = 0; ii < 31; ++ii)
    {
        result <<= 1;
        dividend <<= 1;

        if ( (U32) dividend >= (U32) divisor)
        {
            dividend -= divisor;
            ++ result;
        }
    }

    if (negative_quotient)
    {
        result = -result;
        /* but inverting the sign of the result means we've rounded upwards */
        /* so if result is not exact, round it back down                    */
        if (dividend != 0)
        {
            /* subtract one from LSB to round down */
            -- result;
        }
    }

    *r = result;
}

#define DIV_31(q,divid,divis)   f_DIV_31(&q, divid, divis)

static __inline void f_SHR_16b0 (S16 *r, S16 a, S16 b)
{
    /*FPARITH_TRAP_IF (b < 0, DSP_FIX_INVALID_ARG_OR_LEFT_SHIFT);*/

    if (b >= 15)
    {
        *r = (S16) ((a < 0) ? -1 : 0);
    }
    else
    {
        *r = (S16) (a >> b);
    }
}

#define SHR_16b0(r,a,b)     f_SHR_16b0(&r, a, b)

#endif/*_AUDIOTYPEDEF_H_*/