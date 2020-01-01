#ifndef PLAIN_H
#define PLAIN_H

#define DUMP(x)   QUOTE(##x)
#define QUOTE(x)   printf(##x);

#define FDUMP(fp,x)   FQUOTE(fp,x)
#define FQUOTE(fp,x)   fprintf(fp,#x);

#define _PACK_VLD_FORMAT_

#define DONE()
#define RUN_LEVEL_LAST      0
#define RUN_LEVEL_ESCAPE3   1

#define VLD_BUF_SIZE        (160*1024)
#define VLD_DUMMY_SIZE      (MAX_MBC*MAX_MBR*14)
#define OUTPUT_FILENAME     "outfile-xxxx.txt"
#define OUTPUT_FILENAME2    "outfile-xxxx-2.txt"

#define OUT_VLD_FILENAME    "vld_out.bin"
#define IN_VLD_FILENAME     "vld_in.bin"

#define VLD_FINI_START_CODE 0x90909095
#define VLD_VOP_START_CODE 0x90909094
#define VLD_VOL_START_CODE 0x90909091
#define VLD_REF_START_CODE 0x90909092
#define VLD_MV_START_CODE  0x90909093

#define BITSTREAM_CONDITION (times == 1)
#define SWAP32(x) x = (((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x & 0xFF0000) >> 8) | ((x & 0xFF000000) >> 24));
#define SWAP16(x) x = (((x & 0xFF) << 8) | ((x & 0xFF00) >> 8));

extern int      times;

#ifdef _WRITE_VLD_OUTPUT_

#include "avp_ms_io.h"

extern uint8     *outbuff_ptr, *outbuff_end;
extern uint8     *outbuff_begin;

#if _PROCESSOR_NUMBER_ == 1
extern MSFILE     vld_out_file;
extern MSFILE     vld_out_file2;
extern MSFILE     vld_out_file3;
extern int32    outbuff[];

#define INIT_SEQ_PUT_BUFFER \
{ \
    vld_out_file = fopen(OUT_VLD_FILENAME, "wb"); \
}

#define FINI_SEQ_PUT_BUFFER \
{ \
    fclose(vld_out_file); \
}

#define INIT_FRAME_PUT_BUFFER \
{ \
    outbuff_ptr = (uint8 *) outbuff; \
}

#define FINI_FRAME_PUT_BUFFER \
{ \
    int temp; \
    temp = VLD_VOP_START_CODE; \
    fwrite(&temp, 1, 4, vld_out_file); \
    temp = outbuff_ptr - (uint8*)&outbuff[0]; \
    fwrite(&temp, 1, 4, vld_out_file); \
    fwrite(&outbuff, 1, temp, vld_out_file); \
}

#define FINI_VOL_PUT_BUFFER \
{ \
    int temp; \
    temp = VLD_VOL_START_CODE; \
    fwrite(&temp, 1, 4, vld_out_file); \
    temp = outbuff_ptr - (uint8*)&outbuff[0]; \
    fwrite(&temp, 1, 4, vld_out_file); \
    fwrite(&outbuff, 1, temp, vld_out_file); \
}

#define INIT_REF_MV_PUT_BUFFER(mba_size) \
{ \
    int temp; \
    temp = VLD_REF_START_CODE; \
    fwrite(&temp, 1, 4, vld_out_file); \
    outbuff_ptr += mba_size<<2; \
    temp = VLD_MV_START_CODE; \
    fwrite(&temp, 1, 4, vld_out_file); \
    outbuff_ptr += mba_size<<6; \
}

#define CHK_VLD_OVERFLOW ;

#elif _PROCESSOR_NUMBER_ == 2
extern MSFILE     vld_out_file2;
extern MSFILE     vld_out_file3;
#define INIT_SEQ_PUT_BUFFER ;
#define FINI_SEQ_PUT_BUFFER ;

#define INIT_VOL_PUT_BUFFER \
{ \
    outbuff_ptr = pic->vld_buf_ptr; \
    PUT_SYMBOL(VLD_VOL_START_CODE, 4); \
    PUT_SYMBOL(0, 4); \
}

#define FINI_VOL_PUT_BUFFER \
{ \
    pic->vld_buf_size = outbuff_ptr - pic->vld_buf_ptr; \
    outbuff_ptr = pic->vld_buf_ptr + 4; \
    PUT_SYMBOL(pic->vld_buf_size-8, 4); \
}

#define INIT_FRAME_PUT_BUFFER \
{ \
    outbuff_ptr = pic->vld_buf_ptr+pic->vld_buf_size; \
    outbuff_begin = outbuff_ptr; \
    PUT_SYMBOL(VLD_VOP_START_CODE, 4); \
    PUT_SYMBOL(0, 4); \
}

#define FINI_FRAME_PUT_BUFFER \
{ \
    pic->vld_buf_size = outbuff_ptr - pic->vld_buf_ptr; \
    outbuff_ptr = pic->vld_buf_ptr + 4; \
    PUT_SYMBOL(pic->vld_buf_size-8, 4); \
}

#define INIT_REF_MV_PUT_BUFFER(mba_size) \
{ \
    PUT_SYMBOL(VLD_REF_START_CODE, 4); \
    outbuff_ptr += mba_size<<2; \
    PUT_SYMBOL(VLD_MV_START_CODE, 4); \
    outbuff_ptr += mba_size<<6; \
}

#define CHK_VLD_OVERFLOW \
{ \
    uint8_t vld_overflow = 0; \
    if ((outbuff_ptr - outbuff_begin + VLD_DUMMY_SIZE) > VLD_BUF_SIZE) { \
        vld_overflow = 1; \
    } \
    PUT_SYMBOL(vld_overflow, 1); \
    if (vld_overflow) \
        return ERR_VLD_OVERFLOW; \
}
#endif


#ifdef _PACK_VLD_FORMAT_
#if 1
#define PUT_SYMBOL(x, n) \
{ \
    /*printf("%04x\n", x); */\
    /*fprintf(vld_out_file2,"%04x\n",(uint16)x); */\
    \
    /*fprintf(vld_out_file3,"0x%8x\t\t%dn\t\t",x,n);*/ \
    /*fprintf(vld_out_file3,"%04x\t\t",(uint16)x); \
    FDUMP(vld_out_file3, x); \
    fprintf(vld_out_file3,"\n"); \
    fflush(vld_out_file3); */\
    PUT_SYMBOL_##n(x); \
    outbuff_ptr += n; \
}

#define PUT_SYMBOL_1(x) \
{ \
    *((uint8 *) outbuff_ptr) = x; \
}

#ifdef _UAMEM_ACCESS_
#define PUT_SYMBOL_2(x) \
{ \
    *((uint16 *) outbuff_ptr) = x; \
}

#define PUT_SYMBOL_4(x) \
{ \
    *((uint32 *) outbuff_ptr) = x; \
}

#else
#define PUT_SYMBOL_2(x) \
{ \
    *(outbuff_ptr  ) = UBYTESEL(x, 0); \
    *(outbuff_ptr+1) = IBYTESEL(x, 1); \
}

#define PUT_SYMBOL_4(x) \
{ \
    *(outbuff_ptr  ) = UBYTESEL(x, 0); \
    *(outbuff_ptr+1) = UBYTESEL(x, 1); \
    *(outbuff_ptr+2) = UBYTESEL(x, 2); \
    *(outbuff_ptr+3) = UBYTESEL(x, 3); \
}

#endif

#else

#define PUT_SYMBOL(x, n) \
{ \
    if (n==1) \
        *(outbuff_ptr) = x; \
    else if (n==2) { \
        *(outbuff_ptr  ) = UBYTESEL(x, 0); \
        *(outbuff_ptr+1) = IBYTESEL(x, 1); \
    } else if (n==4) { \
        *(outbuff_ptr  ) = UBYTESEL(x, 0); \
        *(outbuff_ptr+1) = UBYTESEL(x, 1); \
        *(outbuff_ptr+2) = UBYTESEL(x, 2); \
        *(outbuff_ptr+3) = UBYTESEL(x, 3); \
    } else { \
        assert(0); \
    } \
    outbuff_ptr += n; \
}
#endif
#else //_PACK_VLD_FORMAT_
#define PUT_SYMBOL(x, n) \
{ \
    assert(((uint32)outbuff_ptr & 0x3) == 0); \
    *((int32 *) outbuff_ptr) = x; \
    outbuff_ptr += 4; \
}
#endif //_PACK_VLD_FORMAT_
#else //_WRITE_VLD_OUTPUT_
#define INIT_SEQ_PUT_BUFFER ;
#define FINI_SEQ_PUT_BUFFER ;
#define INIT_VOL_PUT_BUFFER ;
#define FINI_VOL_PUT_BUFFER ;
#define INIT_FRAME_PUT_BUFFER ;
#define FINI_FRAME_PUT_BUFFER ;
#define CHK_VLD_OVERFLOW \
{ \
    uint8_t vld_overflow = 0; \
    GET_SYMBOL(vld_overflow, 1); \
    if (vld_overflow) \
        return ERR_VLD_OVERFLOW; \
}
#define PUT_SYMBOL(x, n)
#endif //_WRITE_VLD_OUTPUT_

#ifdef _READ_VLD_OUTPUT_

#include "avp_ms_io.h"

extern uint8     *inbuff_ptr, *inbuff_end;

#if _PROCESSOR_NUMBER_ == 1
extern MSFILE     vld_in_file;
extern int32    inbuff[];
#endif

#if _PROCESSOR_NUMBER_ == 2
#define _VLD_INSTREAM_
#endif

#ifdef _VLD_INSTREAM_
#define INIT_SEQ_GET_BUFFER ;
#define FINI_SEQ_GET_BUFFER ;

#define INIT_VOL_GET_BUFFER \
{ \
    int i, temp; \
    bp = setup->bitstream; \
    assert(((int32)bp&3)==0); \
    temp = *(uint32*)bp; \
    bp += 4; \
    assert(temp == VLD_VOL_START_CODE); \
    temp = *(uint32*)bp; \
    bp += 4; \
    assert(temp > 0); \
    inbuff_ptr = (uint8 *) bp; \
    inbuff_end = inbuff_ptr + temp; \
    bp += temp; \
}

#define INIT_FRAME_GET_BUFFER \
{ \
    int i, temp; \
    inbuff_ptr = setup->bitstream; \
    GET_PUT_SYMBOL_V(temp, 4); \
    assert(temp == VLD_VOP_START_CODE); \
    GET_PUT_SYMBOL_V(temp, 4); \
    assert(temp >= 0); \
    inbuff_end = inbuff_ptr + temp; \
}

#define FINI_FRAME_GET_BUFFER ;

#else //_VLD_INSTREAM_
#define INIT_SEQ_GET_BUFFER \
{ \
    vld_in_file = fopen(IN_VLD_FILENAME, "rb"); \
}

#define FINI_SEQ_GET_BUFFER \
{ \
    fclose(vld_in_file); \
}

#define INIT_VOL_GET_BUFFER \
{ \
    int i, temp; \
    fread(&temp, 1, 4, vld_in_file); \
    assert(temp == VLD_VOL_START_CODE); \
    fread(&temp, 1, 4, vld_in_file); \
    assert(temp > 0); \
    fread(inbuff, 1, temp, vld_in_file); \
    inbuff_ptr = (uint8 *) inbuff; \
    inbuff_end = inbuff_ptr + temp; \
}

#define INIT_FRAME_GET_BUFFER \
{ \
    int i, temp; \
    fread(&temp, 1, 4, vld_in_file); \
    assert(temp == VLD_VOP_START_CODE); \
    fread(&temp, 1, 4, vld_in_file); \
    /*temp = SWAPBYTES(temp);*/ \
    assert(temp > 0); \
    fread(inbuff, 1, temp, vld_in_file); \
    /*for (i=0; i<temp>>2; i++) {*/ \
        /*inbuff[i] = SWAPBYTES(inbuff[i]);*/ \
    /*}*/ \
    inbuff_ptr = (uint8 *) inbuff; \
    inbuff_end = inbuff_ptr + temp; \
}

#define FINI_FRAME_GET_BUFFER ;

#endif //_VLD_INSTREAM_

#ifdef _PACK_VLD_FORMAT_

#if 1

#define GET_SYMBOL(x, n) \
{ \
    GET_SYMBOL_##n(x); \
    inbuff_ptr += n; \
}

#define GET_SYMBOL_V(x, n) \
{ \
    GET_SYMBOL_##n_V(x); \
    inbuff_ptr += ##n; \
}

#define GET_SYMBOL_1(x) \
{ \
    x = *((uint8 *) inbuff_ptr); \
}

#define GET_SYMBOL_1_V(x) \
{ \
    assert(x == *((uint8 *) inbuff_ptr)); \
}

#ifdef _UAMEM_ACCESS_
#define GET_SYMBOL_2(x) \
{ \
    x = *((uint16 *) inbuff_ptr); \
}

#define GET_SYMBOL_4(x) \
{ \
    x = *((uint32 *) inbuff_ptr); \
}

#define GET_SYMBOL_2_V(x) \
{ \
    assert(x == *((uint16 *) inbuff_ptr)); \
}

#define GET_SYMBOL_4_V(x) \
{ \
    assert(x == *((uint32 *) inbuff_ptr)); \
}

#else
#define GET_SYMBOL_2(x) \
{ \
    x = (int32)(int16)PACKBYTES(*(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr)); \
}

#define GET_SYMBOL_4(x) \
{ \
    x = make_uint32(*(((uint8 *) inbuff_ptr)+3), *(((uint8 *) inbuff_ptr)+2), *(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr)); \
}

#define GET_SYMBOL_2_V(x) \
{ \
    assert(x == (int32)(int16)PACKBYTES(*(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr))); \
}

#define GET_SYMBOL_4_V(x) \
{ \
    assert(x == make_uint32(*(((uint8 *) inbuff_ptr)+3), *(((uint8 *) inbuff_ptr)+2), *(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr))); \
}

#endif

#else

#define GET_SYMBOL(x, n) \
{ \
    if (n==1) { \
        x = *((uint8 *) inbuff_ptr); \
    } else if (n==2) { \
        x = (int32)(int16)PACKBYTES(*(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr)); \
    } else if (n==4) { \
        x = make_uint32(*(((uint8 *) inbuff_ptr)+3), *(((uint8 *) inbuff_ptr)+2), *(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr)); \
    } else { \
        assert(0); \
    } \
    inbuff_ptr += n; \
}

#define GET_SYMBOL_V(x, n) \
{ \
    if (n==1) { \
        assert(x == *((uint8 *) inbuff_ptr)); \
        x = *((uint8 *) inbuff_ptr); \
    } else if (n==2) { \
        assert(x == (int32)(int16)PACKBYTES(*(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr))); \
        x = (int32)(int16)PACKBYTES(*(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr)); \
    } else if (n==4) { \
        assert(x == make_uint32(*(((uint8 *) inbuff_ptr)+3), *(((uint8 *) inbuff_ptr)+2), *(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr))); \
        x = make_uint32(*(((uint8 *) inbuff_ptr)+3), *(((uint8 *) inbuff_ptr)+2), *(((uint8 *) inbuff_ptr)+1), *((uint8 *) inbuff_ptr)); \
    } else { \
        assert(0); \
    } \
    inbuff_ptr += n; \
}
#endif

#else //_PACK_VLD_FORMAT_
#define GET_SYMBOL(x, n) \
{ \
    assert (((uint32)inbuff_ptr & 0x3) == 0); \
    x = *((int32 *) inbuff_ptr); \
    inbuff_ptr += 4; \
}

#define GET_SYMBOL_V(x, n) \
{ \
    assert (((uint32)inbuff_ptr & 0x3) == 0); \
    assert(x == *((int32 *) inbuff_ptr)); \
    x = *((int32 *) inbuff_ptr); \
    inbuff_ptr += 4; \
}
#endif //_PACK_VLD_FORMAT_

#else //_READ_VLD_OUTPUT_
#define INIT_SEQ_GET_BUFFER ;
#define FINI_SEQ_GET_BUFFER ;
#define INIT_VOL_GET_BUFFER ;
#define INIT_FRAME_GET_BUFFER ;
#define FINI_FRAME_GET_BUFFER ;
#define GET_SYMBOL(x, n)
#define GET_SYMBOL_V(x, n)
#endif //_READ_VLD_OUTPUT_

#define INIT_SEQ_GET_PUT_BUFFER \
{ \
    INIT_SEQ_PUT_BUFFER; \
    INIT_SEQ_GET_BUFFER; \
}

#define FINI_SEQ_GET_PUT_BUFFER \
{ \
    FINI_SEQ_PUT_BUFFER; \
    FINI_SEQ_GET_BUFFER; \
}

#define INIT_VOL_GET_PUT_BUFFER \
{ \
    INIT_VOL_PUT_BUFFER; \
    INIT_VOL_GET_BUFFER; \
}

#define FINI_VOL_GET_PUT_BUFFER \
{ \
    FINI_VOL_PUT_BUFFER; \
}

#define INIT_FRAME_GET_PUT_BUFFER \
{ \
    INIT_FRAME_PUT_BUFFER; \
    INIT_FRAME_GET_BUFFER; \
}

#define FINI_FRAME_GET_PUT_BUFFER \
{ \
    FINI_FRAME_PUT_BUFFER; \
    FINI_FRAME_GET_BUFFER; \
}

#define GET_PUT_SYMBOL(x, n) \
{ \
    PUT_SYMBOL(x, n); \
    GET_SYMBOL(x, n); \
}

#ifdef _SYN_DEC_
#define GET_PUT_SYMBOL_V(x, n) \
{ \
    PUT_SYMBOL(x, n); \
    GET_SYMBOL_V(x, n); \
}
#else //_SYN_DEC_
#define GET_PUT_SYMBOL_V GET_PUT_SYMBOL
#endif //_SYN_DEC_

#define GETBITS(bs, data, n) data = getbits (bs, n);

#define GET32BITS(data) \
{ \
    data = *fsl0; \
    ++ fsl0; \
}

#endif // PLAIN_H
