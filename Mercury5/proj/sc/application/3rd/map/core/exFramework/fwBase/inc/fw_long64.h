#ifndef FW_LONG64_H
#define FW_LONG64_H

#ifdef USE_LONG64
    #ifdef SUPPORT_LONG64
#if 1
        #include "vm_types.ht"
#endif
        #define ll_setZero(a)           ((a)=0)
        #define ll_inc(a,b)             ((a)+=(b))
        #define ll_dec(a,b)             ((a)-=(b))
        #define ll_negate(a)            ((a)=(-a))

        #define ll_uint_to_long(a,b)    ((a)=(U64)((U32)(b)))
        #define ll_int_to_long(a,b)     ((a)=(S64)b)
        #define ll_long_to_uint(a,b)    ((b)=(U32)(a))

        #define ll_compare_lt(a,b)      ((a)<(b))
        #define ll_compare_eq(a,b)      ((a)==(b))
        #define ll_compare_gt(a,b)      ((a)>(b))

        #define ll_zero_lt(a)           (a<0)
        #define ll_zero_eq(a)           (a==0)
        #define ll_zero_gt(a)           (a>0)

        #define ll_shr(a,n)             ((S64)(a)>>(n))
        #define ll_shl(a,n)             ((S64)(a)<<(n))
        #define ll_ushr(a,n)            ((U64)(a)>>(n))
        #define ll_ushl(a,n)            ((U64)(a)<<(n))
        #define ll_mul(a,b)             ((S64)(a)*(S64)(b))
        #define ll_div(a,b)             ((S64)(a)/(S64)(b))
        #define ll_rem(a,b)             ((S64)(a)%(S64)(b))
        #define ll_add(a,b)             ((S64)(a)+(S64)(b))
        #define ll_sub(a,b)             ((S64)(a)-(S64)(b))
    #else    /* !defined(SUPPORT_LONG64) */
        #ifdef LONG64_BIG_ENDIAN    /* big endian */
            typedef struct T_LONG64_TAG
            {
                U32 high;
                U32 low;
            } S64,*PS64;

            typedef struct T_ULONG64_TAG
            {
                U32 high;
                U32 low;
            } U64,*PU64;
        #else    /* little endian */
            typedef struct T_LONG64_TAG
            {
                U32 low;
                U32 high;
            } S64,*PS64;

            typedef struct T_ULONG64_TAG
            {
                U32 low;
                U32 high;
            } U64,*PU64;
        #endif    /* end of #ifdef LONG64_BIG_ENDIAN */

        #define ll_setZero(a)           ((a).high=(a).low=0)
        #define ll_inc(a,b)             ((a).low+=(b).low,(a).high+=((b).high+((a).low<(b).low)))
        #define ll_dec(a,b)             ((a).high-=((b).high+((a).low<(b).low)),(a).low-=(b).low)
        #define ll_negate(a)            ((a).low=(unsigned)(-((signed)(a).low)),(a).high=(unsigned)(-((signed)((a).high+((a).low!=0)))))
        #define ll_copy(a,b)            ((a).high=(b).high,(a).low=(b).low)

        #define ll_uint_to_long(a,b)    ((a).high=0,(a).low=(b))
        #define ll_int_to_long(a,b)     ((a).low=(b),(a).high=((S32)(b))>>31)
        #define ll_long_to_uint(a,b)    ((b)=(U32)((a).low))

        #define ll_compare_lt(a, b)     (((a).high<(b).high)||(((a).high==(b).high)&&((a).low<(b).low)))
        #define ll_compare_eq(a, b)     (((a).high==(b).high)&&((a).low==(b).low))
        #define ll_compare_gt(a, b)     ll_compare_lt(b,a)

        #define ll_zero_lt(a)           (((a).high&0x80000000)==0x80000000)
        #define ll_zero_eq(a)           (((a).high|(a).low)==0)
        #define ll_zero_gt(a)           (!(ll_zero_lt(a)||ll_zero_eq(a)))

        /* extern */
        #ifdef __cplusplus
        extern "C" {
        #endif    /* end of #ifdef __cplusplus */

            S64 ll_shr(S64 s64A,S32 s32N);
            S64 ll_shl(S64 s64A,S32 s32N);
            S64 ll_ushr(S64 s64A,S32 s32N);
            S64 ll_ushl(S64 s64A,S32 s32N);
            S64 ll_mul(S64 s64A,S64 s64B);
            S64 ll_div(S64 s64A,S64 s64B);
            S64 ll_rem(S64 s64A,S64 s64B);
            S64 ll_add(S64 s64A,S64 s64B);
            S64 ll_sub(S64 s64A,S64 s64B);

        #ifdef __cplusplus
        }
        #endif    /* end of #ifdef __cplusplus */
    #endif    /* end of #ifdef SUPPORT_LONG64 */

    #define ll_compare_le(a,b)    (!ll_compare_gt(a,b))
    #define ll_compare_ne(a,b)    (!ll_compare_eq(a,b))
    #define ll_compare_ge(a,b)    (!ll_compare_lt(a,b))

    #define ll_zero_le(a)         (!ll_zero_gt(a))
    #define ll_zero_ne(a)         (!ll_zero_eq(a))
    #define ll_zero_ge(a)         (!ll_zero_lt(a))

#endif    /* end of #ifdef USE_LONG64 */
#endif    /* end of #ifndef FW_LONG64_H */
