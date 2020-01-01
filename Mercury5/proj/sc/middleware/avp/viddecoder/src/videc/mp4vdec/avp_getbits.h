#ifndef GETBITS_H
#define GETBITS_H

#include "avp_bitsbuf.h"
#include "avp_mi_stdlib.h"

#define getbits(bs, n)          MY_BSGETBITS(bs, n)
#define showbits(bs, nbits)     MY_BSSHOWBITS(bs, nbits)
#define flushbits(bs, nbits)    MY_BSFLUSHBITS(bs, nbits)
#define getbits_short(bs, n)    MY_BSGETBITS_SHORT(bs, n)
#define flushbits_short(bs, n)  MY_BSFLUSHBITS_SHORT(bs, n)

#define bytealign(bs)          bsByteAlign(bs)
#define bytealigned(bs)        bsByteAligned(bs)
#define nbits4bytealigned(bs)  bsNBits4ByteAligned(bs)

#define nextbits(bs, nbits)    showbits(bs, nbits)

#define next_start_code(bs)                 \
    flushbits_short(bs, 1); /* 1 : '0' */   \
    if (! bytealigned(bs)) {                \
        bytealign(bs);  /* 1 to 7 : '1' */  \
    }

#if 0
#define check_stuffing_bits(bs) (showbits(bs, bsNBits4ByteAligned(bs))==\
    ((0xffffffff >> (33-bsNBits4ByteAligned(bs)))))
#define check_stuffing_bits(bs) (showbits(bs, bsNBits4ByteAligned(bs))==\
    ((0xff >> (9-bsNBits4ByteAligned(bs)))))
#endif

int check_stuffing_bits_0x7f(BITSBUF *bs);
int check_stuffing_bits_0x80(BITSBUF *bs);

int nextbits_bytealigned_0x7f(BITSBUF *bs, int nbit);
int nextbits_bytealigned_0x80(BITSBUF *bs, int nbit);

#define flushbytes(b,n) ((b)+=n)
#define show1byte(b)    ( (uint32)((b)[0]) )
#define get1byte(b)     show1byte(b); flushbytes(b,1)
#define show2bytes(b)   ( (((uint32)((b)[0]))<<8) | ((uint32)((b)[1])) )
#define get2bytes(b)    show2bytes(b); flushbytes(b,2)
#define show3bytes(b)   ( (((uint32)((b)[0]))<<16) | (((uint32)((b)[1]))<<8) | ((uint32)((b)[2])) )
#define get3bytes(b)    show3bytes(b); flushbytes(b,3)
#define show4bytes(b)   ( (((uint32)((b)[0]))<<24) | (((uint32)((b)[1]))<<16) | (((uint32)((b)[2]))<<8) | ((uint32)((b)[3])) )
#define get4bytes(b)    show4bytes(b); flushbytes(b,4)
#define show4bytes_a(b)   SWAPBYTES(*((uint32*)(b)))
#define get4bytes_a(b)  show4bytes_a(b); flushbytes(b,4)
#define show4bytes_a_r(b)   (*((uint32*)(b)))
#define get4bytes_a_r(b)  show4bytes_a_r(b); flushbytes(b,4)

#endif /* GETBITS_H */
