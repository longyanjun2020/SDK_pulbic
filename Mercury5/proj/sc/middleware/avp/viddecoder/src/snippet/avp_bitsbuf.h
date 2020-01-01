#ifndef BITSBUF_H
#define BITSBUF_H

#include "avp_mvc_decoder.h"
#include "avp_common.h"

/*lint -emacro(504, bsShowBits_define_g32, bsFlushBits_without_escape_define, bsFlushBits_define)*/

//#define REMOVE_ESCAPE_BY_HOST

#define _NEW_BITS_OP_

#define LOG_PRINTF //printf

//#define NO_BITA // To reduce memory access, not update bs->bit_a when refilling bitsbuf in bits cache mode.


// Check the range of input length. When testing error resilience, it may be
// desirable to disable the check, for example when a decoder implementation
// does error check after the invalid call to bs function returns. Note that
// it is still better to check range before calling bs functions.
#define BS_ASSERT_INPUT

#ifdef BS_ASSERT_INPUT
#define BS_ASSERT(expr) assert(expr)
#else
#define BS_ASSERT(expr) \
    if (!(expr)) \
        printf("!!!!!!!! BS_ASSERT at Line %d \n", __LINE__);
#endif

typedef struct bs_s BITSBUF;
typedef struct bs_func_s bs_func_st;

struct bs_func_s {
    void          (* bsInitBits_p) (BITSBUF *bs, uchar *stream, int length);
    unsigned int (* bsFlushBits_p) (BITSBUF *bs, int n);
#ifdef _NEW_BITS_OP_
    void  (* bsFlushBits_refill_p) (BITSBUF *bs, uint32 *p1, uint32 p2, int n);
#else
    void  (* bsFlushBits_refill_p) (BITSBUF *bs, uint32 *p1, uint32 p2);
#endif
    unsigned int   (* bsGetBits_p) (BITSBUF *bs, int n);
};

struct bs_s {
    uint32 bit_a, bit_b;
    int    bitcnt;
    uint32 state;
    uchar  *rdptr;
    uchar  *buf1;
    int    len1;
    uchar *endptr;
    bs_func_st func;
};

//extern uint32 bsMask[33];
#define bsMask(a) (0xffffffff>>(32-(a)))

#if defined(__GNUC__) && defined(__i386__)

#define bsSWAP(a,b) \
    b=*(int*)a; \
    __asm__ ( "bswapl %0\n" : "=r" (b) : "0" (b) )

#elif defined(__GNUC__) && defined(ARM__)

#define bsSWAP(a,b) \
    { \
    register unsigned int temp; \
    b = *(int*)(a); \
    __asm__ ( " EOR %0, %1, %2, ROR #16" : "=r" (temp) : "r" (b), "r" (b)); \
    __asm__ ( " BIC %0, %1, #0x00FF0000" : "=r" (temp) : "r" (temp)); \
    __asm__ ( " MOV %0, %1, ROR #8"      : "=r" (b) : "r" (b)); \
    __asm__ ( " EOR %0, %1, %2, LSR #8"  : "=r" (b) : "r" (b), "r" (temp)); \
    }

#elif defined(WIN32)

#define bsSWAP(a,b) b = SWAPBYTES(*(uint32*)a)
/*#define bsSWAP(a,b) \
    {   \
    register unsigned int * c = &b; \
    b=*(int*)a; __asm mov ecx, c __asm mov eax, [ecx] __asm bswap eax __asm mov [ecx], eax  \
    }*/

#elif defined(__TCS__)

//#include <ops/custom_defs.h>

#ifdef _UAMEM_ACCESS_
#define bsSWAP(a, b)   b = SWAPBYTES(*(uint32*)a)
#else
#define bsSWAP(a, b)   b = PACK16LSB(PACKBYTES((a[0]), (a[1])), PACKBYTES((a[2]), (a[3])))
#endif

#else

#define bsSWAP(a,b) (b=((a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3]))

#endif

int bsFiniBits(BITSBUF *bs);
#define bsShowBits bsShowBits_inline
#define bsShowBits_inline(bs, n)   (((uint32)((BITSBUF *) (bs))->bit_a) >> (32 - (n)))

void bsInitBits_without_escape(BITSBUF *bs, uchar *stream, int length);
void bsFlushBits_without_escape(BITSBUF *bs, int n);
void bsFlushBits_refill_without_escape(BITSBUF *bs, uint32 *p1, uint32 p2, int n);
unsigned int bsGetBits_without_escape(BITSBUF *bs, int n);
uint32 bsGetBits_short_without_escape(BITSBUF *bs, int n);

void bsInitBits_with_escape(BITSBUF *bs, uchar *stream, int length);
void bsFlushBits_with_escape(BITSBUF *bs, int n);
void bsFlushBits_refill_with_escape(BITSBUF *bs, uint32 *p1, uint32 p2, int n);
unsigned int bsGetBits_with_escape(BITSBUF *bs, int n);

#define bsFlushBits_without_escape          bsGetBits_without_escape
#define bsFlushBits_short_without_escape    bsGetBits_short_without_escape
#define bsFlushBits_with_escape             bsGetBits_with_escape

#ifdef WITH_ESCAPE_POINTER
#define bsInitBits(bs, s, l)                (bs)->func.bsInitBits_p(bs, s, l)
#define bsFlushBits(bs, n)                  (bs)->func.bsFlushBits_p(bs, n)
#define bsFlushBits_short(bs, n)            (bs)->func.bsFlushBits_p(bs, n)
#define bsGetBits(bs, n)                    (bs)->func.bsGetBits_p(bs, n)
#define bsGetBits_short(bs, n)              (bs)->func.bsGetBits_p(bs, n)
#define bsFlushBits_inline_p3               bsFlushBits
#define bsFlushBits_inline_p2               bsFlushBits
#define bsFlushBits_refill(bs, p1, p2, n)   (bs)->func.bsFlushBits_refill_p(bs, p1, p2, n)
#elif defined(WITH_ESCAPE)
#define bsInitBits                          bsInitBits_with_escape
#define bsFlushBits                         bsFlushBits_with_escape
#define bsFlushBits_short                   bsFlushBits_with_escape
#define bsGetBits                           bsGetBits_with_escape
#define bsGetBits_short                     bsGetBits_with_escape
#define bsFlushBits_inline_p3               bsFlushBits_with_escape_define
#define bsFlushBits_inline_p2(a, b)         bsFlushBits_with_escape_define(a, b, EMPTY_SEGMENT)
#define bsFlushBits_refill                  bsFlushBits_refill_with_escape_define
#else
#define bsInitBits                          bsInitBits_without_escape
#define bsFlushBits                         bsFlushBits_without_escape
#define bsFlushBits_short                   bsFlushBits_short_without_escape
#define bsGetBits                           bsGetBits_without_escape
#define bsGetBits_short                     bsGetBits_short_without_escape
#define bsFlushBits_inline_p3               bsFlushBits_without_escape_define
#define bsFlushBits_inline_p2(a, b)         bsFlushBits_without_escape_define(a, b, EMPTY_SEGMENT)
#define bsFlushBits_refill                  bsFlushBits_refill_without_escape_define
#endif

void bsSetFunPtr(bs_func_st *bs_func, int with_escape);

/* return nbits for bytealigned */
#define bsNBits4ByteAligned(bs) (((bs)->bitcnt) & 7) /* for bytealign() */
#define bsByteAlign(bs)         if (bsNBits4ByteAligned(bs))  bsFlushBits_short(bs, bsNBits4ByteAligned(bs));

#define bsBufPtr(bs)  ( (bs)->rdptr - 8 )  /* assert(rdptr-8>=buf1) */

#define bsByteAligned(bs) ( (((bs)->bitcnt) & 7) == 0 )

#define EMPTY_SEGMENT ;


// dump AC bitstream for DECO simulation
#ifdef DUMP_BITSTREAM

#include <stdarg.h>
#include <stdio.h>

extern int dump_bits;
extern FILE *fp_ac_bits_l;
extern FILE *fp_ac_bits_b;

#define _DUMP_BITS \
{ \
    if (dump_bits) { \
    size_t size; \
    size = fwrite (p1, sizeof(uint32), 1, fp_ac_bits_b); /* big endian */ \
        assert (size == 1); \
    size = fwrite (&(bs1->bit_b), sizeof(uint32), 1, fp_ac_bits_l); /* little endian */ \
        assert (size == 1); \
    } \
}

#else // DUMP_BITSTREAM
#define _DUMP_BITS
#endif // DUMP_BITSTREAM

/* read n bits --define version--*/

#define bsGetBits_without_escape_define(bits, bs, n) \
{ \
    /* bs1 cannot be "RESTRICT" */ \
    /*BITSBUF * bs1 = (BITSBUF *)_bs;*/ \
    uint32 * RESTRICT p1 = (uint32 *)bs->rdptr; \
 \
    assert((n)<=32); \
    assert((n)>0); \
    bits = bs->bit_a >> (32 - (n)); \
    bs->bitcnt = bs->bitcnt - (n); \
    bs->bit_a = LSHIFTL32(bs->bit_a, (n)) | (bs->bit_b>>(32-(n))); \
    bs->bit_b = LSHIFTL32(bs->bit_b, (n)); \
    assert(((uint32)p1&0x03) == 0); \
    if (bs->bitcnt<=0) { \
        uint32 t; \
        int32 new_bitcnt; \
        t = BSWAP(p1[0]); \
        new_bitcnt = bs->bitcnt + 32; \
        bs->bit_a  |= LSHIFTR32(t, new_bitcnt); \
        bs->bit_b  = t << INEG(bs->bitcnt); \
        bs->rdptr  = (uchar *)((uint32) p1+4); \
        bs->bitcnt = new_bitcnt; \
    } \
}

#define bsGetBits_with_escape_define(bits, bs, n) \
{ \
    bits = bsGetBits_with_escape(bs, n); \
}

#define bsFlushBits_without_escape_define(bs, n, padding_code)      \
    do {                                                            \
        register uint32 bit_a, bit_b;                               \
                                                                    \
        assert((n) > 0);                                            \
                                                                    \
        if ((n) == 32) {                                            \
            bsGetBits_without_escape(bs, n);                        \
        } else {                                                    \
            bit_a = (bs)->bit_a;                                    \
            bit_b = (bs)->bit_b;                                    \
            bit_a = (bit_a << (n)) | (bit_b >> SH_PLUS32(-(int)(n)));\
            bit_b <<= (n);                                          \
            (bs)->bitcnt -= (n);                                    \
                                                                    \
            if ((bs)->bitcnt < 0) {                                 \
                bit_b = BSWAP(*(uint32 *) (bs)->rdptr);             \
                (bs)->rdptr += 4;                                   \
                bit_a |= bit_b >> SH_PLUS32((bs)->bitcnt);          \
                bit_b <<= -(bs)->bitcnt;                            \
                (bs)->bitcnt += 32;                                 \
            }                                                       \
            (bs)->bit_a = bit_a;                                    \
            (bs)->bit_b = bit_b;                                    \
        }                                                           \
    } while (0)

#define bsFlushBits_without_escape_define_reg(bit_a, bit_b, bitcnt, rdptr, state, n, padding_code) \
{ \
    uint32 * p1 = (uint32 *)rdptr; \
    /*assert(n>0);*/ \
    assert(n<=32); \
 \
    /* faster due to guard operation */ \
    bitcnt = bitcnt - (n); \
    bit_a = LSHIFTL32(bit_a, (n)) | LSHIFTR32(bit_b,(32-(n))); \
    bit_b = LSHIFTL32(bit_b, (n)); \
    assert(((uint32)p1&0x03) == 0); \
    if (bitcnt <= 0) { \
        uint32 t; \
        int32 new_bitcnt; \
        t = BSWAP(p1[0]); \
        new_bitcnt  = bitcnt + 32; \
        bit_a  |= LSHIFTR32(t, new_bitcnt); \
        bit_b  = t << INEG(bitcnt); \
        rdptr  = (uchar *)((uint32) p1+4); \
        bitcnt = new_bitcnt; \
        _DUMP_BITS; \
        padding_code; \
    } else { \
        padding_code; \
    } \
    LOG_PRINTF("flushbits %x %x %x %x\n", n, bitcnt, bit_a, bit_b); \
}

#define bsFlushBits_without_escape_define_reg_g32(bit_a, bit_b, bitcnt, rdptr, state, n, padding_code) \
{ \
    uint32 * p1 = (uint32 *)rdptr; \
    /*assert(n>0);*/ \
    /*assert(n<=32);*/ \
 \
    /* faster due to guard operation */ \
    bitcnt = bitcnt - (n); \
    bit_a = LSHIFTL32(bit_a, (n)) | MUX(32-(n)>=0, LSHIFTR32(bit_b,(32-(n))), LSHIFTL32(bit_b, (n)-32)); \
    bit_b = LSHIFTL32(bit_b, (n)); \
    assert(((uint32)p1&0x03) == 0); \
    if (bitcnt <= 0) { \
        uint32 t; \
        int32 new_bitcnt; \
        t = BSWAP(p1[0]); \
        new_bitcnt  = bitcnt + 32; \
        bit_a  |= LSHIFTR32(t, new_bitcnt); \
        bit_b  = t << INEG(bitcnt); \
        rdptr  = (uchar *)((uint32) p1+4); \
        bitcnt = new_bitcnt; \
        _DUMP_BITS; \
        padding_code; \
    } else { \
        padding_code; \
    } \
    LOG_PRINTF("flushbits %x %x %x %x\n", n, bitcnt, bit_a, bit_b); \
}

void readBits_with_escape(uint32 *bit_a, uint32 *bit_b, int *bitcnt, uchar **rdptr, uint32 *state,
                          int c1, int c2, int c3, int c4, uint32 t1);

#define bsFlushBits_with_escape_define(bs, n, padding_code) \
{ \
    bsGetBits_with_escape(bs, n); \
    padding_code; \
}

#define bsFlushBits_with_escape_define_reg(bit_a, bit_b, _bitcnt, rdptr, state, n, padding_code) \
{ \
    /* faster due to guard operation */ \
    _bitcnt = _bitcnt - (n); \
    bit_a = LSHIFTL32(bit_a, (n)) | MUX(32-(n)>=0, LSHIFTR32(bit_b,(32-(n))), LSHIFTL32(bit_b, (n)-32)); \
    bit_b = LSHIFTL32(bit_b, (n)); \
    if (_bitcnt<=0) { \
        int32 new_bitcnt; \
        int   c1,c2,c3,c4,c5; \
        uint32 t1; \
        \
        t1 = *(rdptr); \
        c1 = (((state << 8) | t1)==0x3); \
        t1 = (t1 << 8) | (*(rdptr+1)); \
        c2 = (((PACK16LSB(state, t1)) & 0xffffff)==0x3); \
        t1 = (t1 << 8) | (*(rdptr+2)); \
        c3 = (t1==0x3); \
        t1 = (t1 << 8) | (*(rdptr+3)); \
        c4 = ((t1 << 8)==0x300); \
        if ((c1 | c2 | c3 | c4) == 0) { \
            state = PACK16LSB(0, t1); \
            rdptr += 4; \
            new_bitcnt  = bitcnt + 32; \
            bit_a  |= LSHIFTR32(t1, new_bitcnt); \
            bit_b  = t1 << INEG(bitcnt); \
            bitcnt = new_bitcnt; \
            \
            padding_code; \
        } else { \
            readBits_with_escape(&bit_a, &bit_b, &bitcnt, &rdptr, &state, \
                                 c1, c2, c3, c4, t1); \
            padding_code; \
        } \
    } else { \
        padding_code; \
    } \
}

#define bsFlushBits_with_escape_define_reg_g32(bit_a, bit_b, bitcnt, rdptr, state, n, padding_code) \
{ \
    /* faster due to guard operation */ \
    bitcnt = bitcnt - (n); \
    bit_a = LSHIFTL32(bit_a, (n)) | MUX(32-(n)>=0, LSHIFTR32(bit_b,(32-(n))), LSHIFTL32(bit_b, (n)-32)); \
    bit_b = LSHIFTL32(bit_b, (n)); \
    if (bitcnt <= 0) { \
        uint32 t; \
        int32 new_bitcnt; \
 \
        uint32 A1,A2,A3,A4,A5,A6; \
        uint32 s1,s2,s3,s4,s5,s6; \
        int    c1,c2,c3,c4,c5; \
 \
        A1 = *(rdptr); \
        A2 = *(rdptr+1); \
        A3 = *(rdptr+2); \
        A4 = *(rdptr+3); \
 \
        A5 = *(rdptr+4); \
        A6 = *(rdptr+5); \
 \
        s1 = MERGELSB(state, A1); \
        s2 = MERGELSB(s1, A2); \
        s3 = MERGELSB(s2, A3); \
        s4 = MERGELSB(s3, A4); \
        s5 = MERGELSB(s4, A5); \
        s6 = MERGELSB(s5, A6); \
 \
        c1 = (s1==0x3); \
        c2 = (s2==0x3); \
        c3 = (s3==0x3); \
        c4 = (s4==0x3); \
        c5 = (s5==0x3); \
 \
        A1 = MUX(c1, A2, A1); \
        A2 = MUX((c1|c2), A3, A2); \
        A3 = MUX((c1|c2|c3), MUX((c1&c4), A5, A4), A3); \
        A4 = MUX((c1|c2|c3|c4), MUX(((c1|c2)&(c4|c5)), A6, A5), A4); \
 \
        t = PACK16LSB(PACKBYTES(A1, A2), PACKBYTES(A3, A4)); \
        new_bitcnt  = bitcnt + 32; \
        bit_a  |= LSHIFTR32(t, new_bitcnt); \
        bit_b  = t << INEG(bitcnt); \
        state = MUX((c1|c2|c3|c4), MUX(((c1|c2)&(c4|c5)), s6, s5), s4); \
        rdptr += 4+(c1|c2|c3|c4)+((c1|c2)&(c4|c5)); \
        bitcnt = new_bitcnt; \
 \
        padding_code; \
    } else { \
        padding_code; \
    } \
}

#define bsFlushBits_no_refill(bs, n) \
{ \
    bs->bitcnt = bs->bitcnt - (n); \
    bs->bit_a  = LSHIFTL32(bs->bit_a, (n)) | (bs->bit_b>>(32-(n))); \
    bs->bit_b  = LSHIFTL32(bs->bit_b, (n)); \
}

#define bsFlushBits_refill_without_escape_define(bs, p1, p2, n) \
{ \
    uint32 t; \
    int32 new_bitcnt; \
 \
    assert(((uint32)p1&0x03) == 0); \
    t = BSWAP(p2); \
    new_bitcnt = bs->bitcnt + 32; \
    bs->bit_a  |= LSHIFTR32(t, new_bitcnt); \
    bs->bit_b  = t << INEG(bs->bitcnt); \
    bs->rdptr  = (uchar *)((uint32) p1+4); \
    bs->bitcnt = new_bitcnt; \
}

#define bsFlushBits_refill_with_escape_define(bs, p1, p2, n) \
{ \
    bsFlushBits_with_escape(bs, n); \
}

#define bsShowBits_define_neg_reg(code, bit_a, bit_b, bitcnt, n, flushcnt) \
{ \
    int nbit_; \
    \
    nbit_ = (flushcnt) + (n) - 32; \
    code = MUX(nbit_<0, bit_a>>INEG(nbit_), LSHIFTL32(bit_a, nbit_) | LSHIFTR32(bit_b, 64-((flushcnt) + (n)))) & bsMask(n); \
    LOG_PRINTF("showbits_neg %x %x %x %x %x\n", code, n, flushcnt, bit_a, bit_b); \
}

#define bsShowBits_n2_define_neg_reg(code, code2, bit_a, bit_b, bitcnt, n, n2, flushcnt) \
{ \
    int nbit_; \
    \
    nbit_ =  (flushcnt) + (n2) - 32; \
    code2 = MUX(nbit_<0, bit_a>>INEG(nbit_), LSHIFTL32(bit_a, nbit_) | LSHIFTR32(bit_b, 64-((flushcnt) + (n2)))) & bsMask(n2); \
    nbit_ = (flushcnt) + (n) - 32; \
    code = MUX(nbit_<0, bit_a>>INEG(nbit_), LSHIFTL32(bit_a, nbit_) | LSHIFTR32(bit_b, 64-((flushcnt) + (n)))) & bsMask(n); \
    LOG_PRINTF("showbits_neg %x %x %x %x %x\n", code, n, flushcnt, bit_a, bit_b); \
}


#define bsShowBits_define_reg(show_ret, bit_a, bit_b, bitcnt, n) \
{ \
    assert((n)<=32); \
    assert((n)>0); \
    show_ret = bit_a >> (32 - (n)); \
    LOG_PRINTF("showbits %x %x %x %x %x\n", show_ret, n, bitcnt, bit_a, bit_b); \
}

#define bsShowBits_n2_define_reg(show_ret, show_ret2, bit_a, bit_b, bitcnt, n, n2) \
{ \
    assert((n)<=32); \
    assert((n2)<=32); \
    assert((n)>0); \
    assert((n2)>0); \
    assert((n)>(n2)); \
    show_ret2 = bit_a >> (32 - (n2)); \
    show_ret = bit_a >> (32 - (n)); \
    LOG_PRINTF("showbits %x %x %x %x %x\n", show_ret, n, bitcnt, bit_a, bit_b); \
}

#define bsShowBits_define(show_ret, bs, n) \
{ \
    assert((n)<=32); \
    show_ret = bs##p->bit_a >> (32 - (n)); \
}

/* TODO: remove usage */
#define bsShowBits_define_g32(show_ret, bs, n) \
{ \
    int nbit_; \
 \
    nbit_ = 32 - (n); \
    show_ret = MUX(nbit_>=0, (bs->bit_a>>nbit_), (bs->bit_a<<INEG(nbit_)) | (bs->bit_b >> (32+(nbit_)))); \
}

#define begin_bitsbuf(bitsbuf, bits_len) \
{ \
    bitsbuf = bsShowBits_inline(bs, 32); \
    bits_len = 32; \
}

#define end_bitsbuf(bits_len) \
{ \
    if (bits_len < 32) { \
        flushbits(bs, 32-bits_len); \
    } \
}

#define refill_bitsbuf(bitsbuf, bits_len, len) \
    if (bits_len<(len)) { \
        bsFlushBits_inline_p2(bs, 32-bits_len); \
        bitsbuf = bsShowBits_inline(bs, 32); \
        bits_len = 32; \
    }

#define refill_bitsbuf_v2(bitsbuf, bits_len, len) \
    if (bits_len<(len)) { \
        int temp_bits_len = 32-bits_len; \
        bits_len = 32;           \
        bsFlushBits_inline_p3(bs, temp_bits_len, bitsbuf = bsShowBits_inline(bs, 32)); \
    }

#define force_refill_bitsbuf(bitsbuf, bits_len/*, len*/) \
    if (bits_len < 32) { \
        bsFlushBits_inline_p2(bs, 32-bits_len); \
        bitsbuf = bsShowBits_inline(bs, 32); \
        bits_len = 32; \
    }

#define force_refill_bitsbuf_v2(bitsbuf, bits_len/*, len*/) \
    /*assert(bits_len<32);*/ \
    int temp_bits_len = 32-bits_len; \
    bits_len = 32;           \
    bsFlushBits_inline_p3(bs, temp_bits_len, bitsbuf = bsShowBits_inline(bs, 32));

#define get_bitsbuf(bitsbuf, bits_len, len) \
    ((bitsbuf)>>(32-(len))); \
    BS_ASSERT(bits_len >= (len)); \
    bits_len -= (len); \
    bitsbuf <<= (len);

#define get_bitsbuf_var(bitsbuf, bits_len, len) \
    ((bitsbuf) >> SH_PLUS32(-len)); \
    BS_ASSERT(bits_len >= (len)); \
    bits_len -= (len); \
    bitsbuf <<= (len);

#define show_bitsbuf(bitsbuf, bits_len, len) \
    ((bitsbuf)>>(32-(len))); \
    BS_ASSERT(bits_len >= (len));

#define show_bitsbuf_var(bitsbuf, bits_len, len) \
    ((bitsbuf) >> SH_PLUS32(-len)); \
    BS_ASSERT(bits_len >= (len));

#define flush_bitsbuf(bitsbuf, bits_len, len) \
    BS_ASSERT(bits_len >= (len)); \
    bits_len -= (len); \
    bitsbuf <<= (len);

#define nextbits_bytealigned_0x80_define(ret, bs, nbit) \
{ \
    int code; \
    int skipcnt; \
 \
    skipcnt = nbits4bytealigned(bs); \
    if (bytealigned(bs)) { \
        /* stuffing bits */ \
        code = bsShowBits_inline(bs, 8); \
        if (code/*showbits(bs, 8)*/ == 0x80) { \
            skipcnt = 8; \
        } \
    } \
 \
    bsShowBits_define_g32(code, bs, (nbit) + skipcnt);  /*will nbit+skipcnt <= 32 ?*/ \
    ret = code & bsMask(nbit); \
}


#define bsFlushBits_define(bs, bitsbuf, n) \
{ \
    register uint32 bit_a, bit_b; \
    register int bitcnt; \
    \
    assert((n) > 0 && (n) <= 32); \
    bit_b = bs->bit_b; \
    bitcnt = bs->bitcnt; \
    \
    bit_a = bitsbuf; \
    bit_a = bit_a | (bit_b >> SH_PLUS32(-((int) (n)))); \
    bit_b <<= (n); \
    bitcnt -= (n); \
    if (bitcnt < 0) { \
        bit_b = BSWAP(*(uint32 *) bs->rdptr); \
        bs->rdptr += 4; \
        bit_a |= bit_b >> SH_PLUS32(bitcnt); \
        bit_b <<= -bitcnt; \
        bitcnt += 32; \
    } \
    bs->bit_a = bit_a; \
    bs->bit_b = bit_b; \
    bs->bitcnt = bitcnt; \
}

#ifdef _SYN_DEC_

#define BITS_CACHE_INIT(bs, bitsbuf, bitslen) \
    do { \
        bitsbuf = bsShowBits_inline(bs, 32); \
        bitslen = 32; \
    } while (0)

#define BITS_CACHE_SHOW(val, bitsbuf, bitslen, len) \
    do { \
        assert(bitslen >= (len)); \
        val = (bitsbuf) >> (32 - (len)); \
    } while (0)

#define BITS_CACHE_GET(val, bitsbuf, bitslen, len) \
    do { \
        assert(bitslen >= (len)); \
        val = (bitsbuf) >> (32 - (len)); \
        bitsbuf <<= (len); \
        bitslen  -= (len); \
    } while (0)

#define BITS_CACHE_FLUSH(bitsbuf, bitslen, len) \
    do { \
        assert(bitslen >= (len)); \
        bitsbuf <<= (len); \
        bitslen  -= (len); \
    } while (0)

#ifdef NO_BITA
#define BITS_CACHE_FILL(bs, bitsbuf, bitslen, len) \
    while (bitslen < len) { \
        register int bitcnt = bs->bitcnt; \
        register uint32 bit_b = bs->bit_b; \
        int shiftcnt; \
        if (bitcnt == 0) { \
            bit_b = BSWAP(*(uint32 *) bs->rdptr); \
            bs->rdptr += 4; \
            bitcnt = 32; \
        } \
        shiftcnt = bitcnt < 32-bitslen ? bitcnt : 32-bitslen; \
        bitsbuf |= bit_b >> bitslen; \
        bitslen += shiftcnt; \
        bit_b <<= shiftcnt; \
        bitcnt -= shiftcnt; \
        bs->bit_b = bit_b; \
        bs->bitcnt = bitcnt; \
    }

#define BITS_CACHE_CLOSE(bs, bitsbuf, bitslen) \
    if (bitslen < 32) { \
        bsFlushBits_define(bs, bitsbuf, 32 - (bitslen)); \
    } \
    else { \
        assert(bitslen == 32); \
        bs->bit_a = bitsbuf; \
    }
#else
#define BITS_CACHE_FILL(bs, bitsbuf, bitslen, len) \
    do { \
        if (bitslen < (len)) { \
            bsFlushBits_inline_p2(bs, 32 - (bitslen)); \
            bitsbuf = bsShowBits_inline(bs, 32); \
            bitslen = 32; \
        } \
    } while (0)

#define BITS_CACHE_CLOSE(bs, bitsbuf, bitslen) \
    do { \
        if (bitslen < 32) { \
            bsFlushBits_define(bs, bitsbuf, 32 - (bitslen)); \
        } \
    } while (0)
#endif

#else

#define BITS_CACHE_INIT(bs, bitsbuf, bitslen)       ((void) 0)
#define BITS_CACHE_SHOW(val, bitsbuf, bitslen, len) ((void) 0)
#define BITS_CACHE_GET(val, bitsbuf, bitslen, len)  ((void) 0)
#define BITS_CACHE_FLUSH(bitsbuf, bitslen, len)     ((void) 0)
#define BITS_CACHE_FILL(bs, bitsbuf, bitslen, len)  ((void) 0)
#define BITS_CACHE_CLOSE(bs, bitsbuf, bitslen)      ((void) 0)

#endif

#endif /* BITSBUF_H */
