#ifndef FRAMING_H
#define FRAMING_H

#include <stdint.h>
#include "avp_mvc_decoder.h"
#include "avp_parsing.h"

// FIXME: duplicated
#ifdef SUPPORT_WMV
#define WMV_SIM_VOP
#endif

#define START_CODE_MP4V    1
#define START_CODE_MP2V    2
#define START_CODE_AVC1    3
#define START_CODE_H263    4
#define START_CODE_WMVX    5
#define START_CODE_AVC1_NEXT_0    6
#define START_CODE_MP2V_NEXT_0    7
#define START_CODE_RV30    8
#define START_CODE_RV40    9
#define START_CODE_RVCH    11
#define START_CODE_VLDX    10
#define START_CODE_FLV1    12
#define START_CODE_CAVS    13
#define START_CODE_VP6X    14
#define START_CODE_VP7X    15
#define START_CODE_VP8X    16

#ifdef SUPPORT_AVC
#define AVC_START_CODE1 0x000001

#define NALU_TYPE_SLICE   1
#define NALU_TYPE_DPA     2
#define NALU_TYPE_DPB     3
#define NALU_TYPE_DPC     4
#define NALU_TYPE_IDR     5
#define NALU_TYPE_SEI     6
#define NALU_TYPE_SPS     7
#define NALU_TYPE_PPS     8
#define NALU_TYPE_AUD     9
#define NALU_TYPE_EOSEQ   10
#define NALU_TYPE_EOSTREAM 11
#define NALU_TYPE_FILLER  12

#endif

#define M2V_START_CODE1 0x000001

#define M2V_VOP_START_CODE  0x100  /* MPEG2 : PICTURE_START_CODE */
#define M2V_VOL_START_CODE  0x1b3

#define M4V_VOP_START_CODE  0x1b6
#define M4V_VOL_START_CODE1  0x120
#define M4V_VOL_START_CODE2  0x12f

#define RV30_VOP_START_CODE 0x000001     // only 3 bytes are used
#define RV40_VOP_START_CODE 0x55555555

#define VLDX_VOP_START_CODE 0x94909090

#define bswap(a) (((((a)&0xff) << 24) | (((a)&0xff00) << 8) | (((a)&0xff0000) >> 8) | (((a)&0xff000000) >> 24)))

uint8_t *scan_picture_backward(uint8_t *buf, int len
#ifdef WMV_SIM_VOP
                             , uint1 sim_header
#endif
                             , int c_type
                             , int nextauinterval
                             );


uint8_t *scan_picture_forward(uint8_t *buf, int len
#ifdef WMV_SIM_VOP
                                       , uint1 sim_header
#endif
                                       , int c_type
                                       , int *pLen
                                       , int nextauinterval
                                       );

#ifdef TM_MAIN

#define TMNull NULL
#define PROGRESSIVE_FRAME  0
#define INTERLACE_FIELD    1
#define INTERLACE_FRAME    2

#if 1//defined(WIN32) || defined(MIPSDEV)
#define DATAINFUNC DATAINFUNC
#define PARENT 0
#define VIDINSTANCE    fi[unitNumber].instance
#else
#define DATAINFUNC     ivp->setup->defaultSetup->datainFunc
#define PROGRESSFUNC   ivp->setup->defaultSetup->progressFunc
#define PARENT         ivp->setup->defaultSetup->parentId
#define VIDINSTANCE    vidInstance
#endif

#define ViDecProgressFlagPutEmptyPacket 0x02

#define MY_VBUF_SIZE VIDEC_IBUF_SIZE//512*1024

uchar *scan_picture_forward_2_tm(uchar *buf, int len, uint8 c_type, uchar **vol_ptr);

uchar *scan_picture_forward_tm(uchar *buf, int len, uint8 c_type, int* p_pic_type, int vidInstance
#if defined(SUPPORT_AVC) || defined(SUPPORT_M2V) || defined(USE_VDECMPEG)
                                      , int *p_frame_num, int *bottom_field, uchar *isRef, uint32 *pictype, int *cur_frame_num
#endif
#ifdef SUPPORT_RVC
                                      , int *header_size, int *frame_size
#endif
                                      );

#define get_inpkt_inplace(ivp, rval, inpkt) { \
    /* DP(("ViDec: %d GetFull\n", __LINE__)); */ \
    rval = DATAINFUNC(PARENT, tsaDatainGetFull | tsaDatainWait | tsaDatainCheckControl, &my_pkt_i[unitNumber].di_args); \
    /* DP(("ViDec: %d GetFull done %08x\n", __LINE__, rval)); */ \
    if ((rval == TM_OK) || (rval == TM_ERR_NEW_FORMAT)) { \
        inpkt = (ptmAvPacket_t)my_pkt_i[unitNumber].di_args.packet; \
        inpkt->buffersInUse = 1;               \
        /*DP(("ViDec: get inpkt (%d) %08x %p %x pts=%d\n", __LINE__, rval, inpkt, inpkt->header->id, U64LOCASTU32(inpkt->header->time))); */\
    } \
}

#define ret_inpkt_inplace(ivp, rval, inpkt, prog_args) { \
    tmAssert(inpkt != TMNull, inpkt);\
    /*DP(("ViDec: %d ret inpkt %x\n", __LINE__, inpkt->header->id));  */\
    prog_args.progressCode =  inpkt->buffers [0].bufSize;                       \
    PROGRESSFUNC(PARENT, ViDecProgressFlagPutEmptyPacket, &prog_args); \
    /*inpkt->buffers[0].bufSize = 0;*/                                               \
    my_pkt_i[unitNumber].di_args.packet = inpkt;                                                      \
    inpkt->buffersInUse = 0;                                                     \
    rval = DATAINFUNC(PARENT, tsaDatainPutEmpty | tsaDatainCheckControl, &my_pkt_i[unitNumber].di_args); \
    tmAssert(rval == TM_OK, rval); \
    inpkt = TMNull; \
}

#define ret_inpkt_inplace2(ivp, rval, inpkt, prog_args) { \
    tmAssert(inpkt != TMNull, inpkt);\
    /*DP(("ViDec: %d ret inpkt %x\n", __LINE__, inpkt->header->id));  */\
    prog_args.progressCode =  inpkt->buffers [0].bufSize;                       \
    PROGRESSFUNC(PARENT, ViDecProgressFlagPutEmptyPacket, &prog_args); \
    inpkt->buffers[0].bufSize = 0;                                               \
    my_pkt_i[unitNumber].di_args.packet = my_pkt_i[unitNumber].my_curpkt;                                                      \
    inpkt->buffersInUse = 0;                                                     \
    rval = DATAINFUNC(PARENT, tsaDatainPutEmpty | tsaDatainCheckControl, &my_pkt_i[unitNumber].di_args); \
    tmAssert(rval == TM_OK, rval); \
    inpkt = TMNull; \
}

//Sean
/*
1. The minimum bits needed to get frame width and height in FLV1, H263, H263PP
   FLV1:   PSC(17)+Version(5)+TR(8)+Picture Size(3) = 33 bits
   H263:   PSC(22)+TR(8)+PTYPE(8) = 38 bits
   H263PP: PSC(22)+TR(8)+PTYPE(8)+UFEP(3)+OPPTYPE(18)+MPPTYPE(9)+CPM(1)+PSBI(2)+CPFMT(23) = 96 bits
   
   Therefore, we get first 8 bytes of FLV1, H263, H263PP files to detect their width and height.
*/
#define get_inpkt_with_find_startcode(ivp, rval, inpkt, x) { \
    uchar *ptr; int size; \
    rval = TM_OK; \
    if (my_pkt_i[unitNumber].my_curpkt_pt == TMNull) { \
        rval = DATAINFUNC(PARENT, tsaDatainGetFull | tsaDatainWait | tsaDatainCheckControl, &my_pkt_i[unitNumber].di_args); \
        if ((rval == TM_OK) || (rval == TM_ERR_NEW_FORMAT)) { \
            my_pkt_i[unitNumber].my_curpkt = my_pkt_i[unitNumber].di_args.packet; \
            my_pkt_i[unitNumber].last_time_in_pkt[1] = my_pkt_i[unitNumber].my_curpkt->header->time; \
            MY_MEMCPY(&my_pkt_i[unitNumber].my_packet, my_pkt_i[unitNumber].my_curpkt, sizeof(tmAvPacket_t)); \
            my_pkt_i[unitNumber].my_packet.buffers[0].data    = my_vbuf[unitNumber]+my_vbuf_start_offset; \
            my_pkt_i[unitNumber].my_packet.buffers[0].bufSize = MY_VBUF_SIZE; \
            my_pkt_i[unitNumber].my_curpkt_pt = my_pkt_i[unitNumber].my_curpkt->buffers[0].data; \
            if (my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize == 0) { \
                my_pkt_i[unitNumber].my_packet.buffers[0].dataSize = 0; goto special_packet##x; } \
            if ((rval == TM_ERR_NEW_FORMAT) OR my_pkt_i[unitNumber].reInitDecoder) { \
                uchar *vol_ptr; \
                uchar *tmp = my_pkt_i[unitNumber].my_curpkt_pt; \
                int AVCorMP2V = (my_pkt_i[unitNumber].codec_type==START_CODE_AVC1) OR (my_pkt_i[unitNumber].codec_type==START_CODE_MP2V); \
                int H263orFLV1 = (my_pkt_i[unitNumber].codec_type==START_CODE_H263) OR (my_pkt_i[unitNumber].codec_type==START_CODE_FLV1); \
                ptr = scan_picture_forward_2_tm(my_pkt_i[unitNumber].my_curpkt_pt, my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize, my_pkt_i[unitNumber].codec_type, &vol_ptr); \
                tmAssert(ptr!=TMNull, 0); \
                my_pkt_i[unitNumber].my_curpkt_pt = vol_ptr; \
                my_pkt_i[unitNumber].my_vbuf_size = ptr + MUX(AVCorMP2V OR (my_pkt_i[unitNumber].codec_type==START_CODE_RVCH), 0, MUX(H263orFLV1, 12, 4) ) - my_pkt_i[unitNumber].my_curpkt_pt; \
                MY_MEMCPY(my_vbuf[unitNumber]+my_vbuf_start_offset, my_pkt_i[unitNumber].my_curpkt_pt, my_pkt_i[unitNumber].my_vbuf_size); \
                my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize -= my_pkt_i[unitNumber].my_vbuf_size+(vol_ptr-tmp); \
                my_pkt_i[unitNumber].my_curpkt_pt += my_pkt_i[unitNumber].my_vbuf_size; \
                my_pkt_i[unitNumber].last_time_in_pkt[0] = my_pkt_i[unitNumber].last_time_in_pkt[1]; \
                my_pkt_i[unitNumber].last_time_in_pkt[1] = -1; \
            } else if (my_pkt_i[unitNumber].my_vbuf_size==0) { \
                my_pkt_i[unitNumber].last_time_in_pkt[0] = my_pkt_i[unitNumber].last_time_in_pkt[1]; \
                my_pkt_i[unitNumber].last_time_in_pkt[1] = -1; \
            } \
            rval = TM_ERR_NEED_MORE_DATA; \
        } else if (rval == TM_ERR_NOT_STARTED) { \
            my_pkt_i[unitNumber].my_vbuf_size = 0; \
        } \
    } \
/*for video with one frame only, move special_packet##x label here */ \
    my_pkt_i[unitNumber].my_packet.buffers[0].dataSize = my_pkt_i[unitNumber].my_vbuf_size; \
    if ((rval != TM_ERR_NEED_MORE_DATA) OR my_pkt_i[unitNumber].reInitDecoder) { \
        my_pkt_i[unitNumber].my_vbuf_size = 0; \
        my_pkt_i[unitNumber].au_count = 0; \
    } \
special_packet##x:  \
    tmAssert(inpkt==TMNull, 0/*inpkt->header->id*/); \
    if (rval != TM_ERR_NOT_STARTED) { \
        inpkt = (ptmAvPacket_t)&my_pkt_i[unitNumber].my_packet; \
        inpkt->buffersInUse = 1;               \
        /*DP (("ViDec: %d get inpkt %x %d\n", __LINE__, inpkt->header->id, my_pkt_i[unitNumber].my_vbuf_size));*/ \
    } \
}

#ifdef SUPPORT_RVC
#define RVC_PARA , &my_pkt_i[unitNumber].header_size, &my_pkt_i[unitNumber].frame_size
#else
#define RVC_PARA 
#endif

#if defined(SUPPORT_AVC) || defined(SUPPORT_M2V)
#define AVC_PARA , &next_frame_num, &next_bottom_field, &next_isRef, &next_pic_type, &cur_frame_num
#else
#define AVC_PARA
#endif

#define ret_inpkt_with_find_startcode(ivp, rval, inpkt, prog_args) { \
    uchar *ptr; \
    int cur_pic_type; \
    uint32 next_frame_num = 0; \
    uint32 next_bottom_field = -1; \
    uint32 next_pic_type = 1; \
    uchar next_isRef = 1; \
    uint32 cur_frame_num; \
    int au_count_max; \
    int AVCorMP2V = (my_pkt_i[unitNumber].codec_type==START_CODE_AVC1) OR (my_pkt_i[unitNumber].codec_type==START_CODE_MP2V); \
    rval = TM_OK; \
    if (my_pkt_i[unitNumber].my_curpkt_pt != TMNull) { \
        do { \
            uchar *tmp = my_pkt_i[unitNumber].my_curpkt_pt; \
            uchar *vol_ptr; \
            if (my_pkt_i[unitNumber].reInitDecoder) { \
                ptr = scan_picture_forward_2_tm(my_pkt_i[unitNumber].my_curpkt_pt, my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize, my_pkt_i[unitNumber].codec_type, &vol_ptr); \
                my_pkt_i[unitNumber].my_curpkt_pt = vol_ptr; \
            } else { \
                int offset = MUX(AVCorMP2V OR (my_pkt_i[unitNumber].codec_type==START_CODE_RVCH) OR (my_pkt_i[unitNumber].my_vbuf_size>0), 0, 4); \
                int start_code_next = MUX(my_pkt_i[unitNumber].codec_type==START_CODE_AVC1, START_CODE_AVC1_NEXT_0, MUX(my_pkt_i[unitNumber].codec_type==START_CODE_MP2V, START_CODE_MP2V_NEXT_0, my_pkt_i[unitNumber].codec_type)); \
                ptr = scan_picture_forward_tm(my_pkt_i[unitNumber].my_curpkt_pt+offset, \
                                              my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize-offset, \
                                              MUX(AVCorMP2V AND (my_pkt_i[unitNumber].au_count&1), start_code_next, my_pkt_i[unitNumber].codec_type),  \
                                              &cur_pic_type, VIDINSTANCE \
                                              AVC_PARA \
                                              RVC_PARA \
                                              ); \
            } \
            if (AVCorMP2V AND (my_pkt_i[unitNumber].au_count&1)) { \
                cur_frame_num = my_pkt_i[unitNumber].pic_num; \
                cur_pic_type = my_pkt_i[unitNumber].pic_type; \
            } \
            au_count_max = MUX(AVCorMP2V AND (cur_pic_type != PROGRESSIVE_FRAME), 4, 2); \
            if (ptr == -1) { \
                if ((my_pkt_i[unitNumber].au_count&1) AND (cur_pic_type == INTERLACE_FRAME)) { \
                    my_pkt_i[unitNumber].au_count += 2; \
                } \
                ptr = TMNull; \
                my_pkt_i[unitNumber].au_count |= 1; \
            } \
            if (ptr == TMNull) { \
                prog_args.progressCode = my_pkt_i[unitNumber].my_curpkt->buffers[0].bufSize;                       \
                inpkt->buffers[0].bufSize = 0; \
                assert(my_vbuf_start_offset+my_pkt_i[unitNumber].my_vbuf_size+my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize<=MY_VBUF_SIZE); \
                MY_MEMCPY(my_vbuf[unitNumber]+my_vbuf_start_offset+my_pkt_i[unitNumber].my_vbuf_size, my_pkt_i[unitNumber].my_curpkt_pt, my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize); \
                my_pkt_i[unitNumber].my_vbuf_size += my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize; \
                my_pkt_i[unitNumber].my_curpkt_pt = TMNull; \
                PROGRESSFUNC(PARENT, ViDecProgressFlagPutEmptyPacket, &prog_args); \
                my_pkt_i[unitNumber].di_args.packet = my_pkt_i[unitNumber].my_curpkt;                     \
                my_pkt_i[unitNumber].di_args.packet->buffersInUse = 0; \
                my_pkt_i[unitNumber].pic_type = cur_pic_type; \
                my_pkt_i[unitNumber].pic_num = cur_frame_num; \
                rval = DATAINFUNC(PARENT, tsaDatainPutEmpty | tsaDatainCheckControl, &my_pkt_i[unitNumber].di_args); \
                tmAssert(rval == TM_OK, rval); \
                break; \
            } else { \
                int new_seg_size = ptr - my_pkt_i[unitNumber].my_curpkt_pt; \
                if (my_pkt_i[unitNumber].reInitDecoder) { \
                    new_seg_size += MUX(AVCorMP2V, 0, 4); \
                    my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize -= (vol_ptr-tmp); \
                } \
                assert(my_vbuf_start_offset+my_pkt_i[unitNumber].my_vbuf_size+new_seg_size<=MY_VBUF_SIZE); \
                MY_MEMCPY(my_vbuf[unitNumber]+my_vbuf_start_offset+my_pkt_i[unitNumber].my_vbuf_size, my_pkt_i[unitNumber].my_curpkt_pt, new_seg_size); \
                my_pkt_i[unitNumber].my_vbuf_size += new_seg_size; \
                my_pkt_i[unitNumber].my_curpkt->buffers[0].dataSize -= new_seg_size; \
                my_pkt_i[unitNumber].my_curpkt_pt = ptr; \
                my_pkt_i[unitNumber].au_count &= ~1; \
                my_pkt_i[unitNumber].au_count += 2; \
                if (cur_pic_type == INTERLACE_FRAME) { \
                    my_pkt_i[unitNumber].au_count += 2; \
                } \
                if (my_pkt_i[unitNumber].au_count < au_count_max) { \
                    /*printf("frame_num = (%d %d),  pic_type = (%d %d)\n", next_frame_num, cur_frame_num, next_pic_type, my_pkt_i[unitNumber].pic_type); \
                    printf("bottom_field = (%d %d), isRef = (%d %d)\n", next_bottom_field, my_pkt_i[unitNumber].bottom_field, next_isRef, my_pkt_i[unitNumber].isRef); */\
                    if ((next_frame_num != cur_frame_num) OR (next_pic_type != my_pkt_i[unitNumber].pic_type) OR (next_bottom_field == my_pkt_i[unitNumber].bottom_field) OR (next_isRef != my_pkt_i[unitNumber].isRef)) { \
                        my_pkt_i[unitNumber].au_count = au_count_max; \
                        MY_PRINTF("parse error in ret_inpkt()\n"); \
                    } \
                } \
                if (my_pkt_i[unitNumber].au_count >= au_count_max) { \
                    assert(my_pkt_i[unitNumber].au_count == au_count_max); \
                    my_pkt_i[unitNumber].my_packet.header->time = my_pkt_i[unitNumber].last_time_in_pkt[0]; \
                    my_pkt_i[unitNumber].last_time_in_pkt[0] = my_pkt_i[unitNumber].last_time_in_pkt[1]; \
                    my_pkt_i[unitNumber].last_time_in_pkt[1] = -1; \
                } \
            } \
            /*my_pkt_i[unitNumber].pic_num = next_frame_num; */\
            my_pkt_i[unitNumber].pic_type = next_pic_type; \
            my_pkt_i[unitNumber].bottom_field = next_bottom_field; \
            my_pkt_i[unitNumber].isRef = next_isRef; \
            \
        } while (my_pkt_i[unitNumber].au_count < au_count_max);\
    } \
    inpkt = TMNull; \
}
#endif // TM_MAIN
#endif // FRAMING_H
