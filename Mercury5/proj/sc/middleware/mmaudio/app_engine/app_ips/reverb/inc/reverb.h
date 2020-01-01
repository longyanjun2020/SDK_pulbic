////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    : reverb.h
* @version :
* @author  :wendy.lin
* @brief   : Artificial Reverberation
*/

#ifndef __REVERB_H__
#define __REVERB_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "app_datatype.h"

/*============================================================================*/
// Extern definition
/*============================================================================*/
/*----------------- Print Message Switch ----------------*/
#define ENABLE_REVERB_PARSER_PRINTF

/*============================================================================*/
// Macro definition
/*============================================================================*/
#define SHIFTBIT  15//Q15
#define Q_ONE 32767
#define delaybuf_length 3300
#define TEMPBUF_LEN 512

#define DYNAMIC_ALLOC
#define HIGH_Q
//#define MID_Q
//#define LOW_Q
#ifdef HIGH_Q
#define DEFAULT_COMBNUM 4
#define DEFAULT_APNUM 4
#define COMB_DELAY_LEN (1144+1215+1390+1695)
#define AP_Delay_LEN (245+605+480+371)
#endif
#ifdef MID_Q  
#define DEFAULT_COMBNUM 3
#define DEFAULT_APNUM 4
#define COMB_DELAY_LEN (1215+1390+1695)
#define AP_Delay_LEN (245+605+480+371)
#endif

#ifdef LOW_Q
#define DEFAULT_COMBNUM 3
#define DEFAULT_APNUM 3
#define COMB_DELAY_LEN (1215+1390+1695)
#define AP_Delay_LEN (605+480+371)

#endif

#define RVB_TOTAL_MEM_SIZE  (sizeof(STR_MEMDELAY)*(DEFAULT_COMBNUM + DEFAULT_APNUM)) + (COMB_DELAY_LEN*4) +(AP_Delay_LEN*4) + (delaybuf_length*2) + (TEMPBUF_LEN*4)

#define MUL_SHIFT_15(x,y) (tS32)(((x) * (y) + (1 << (SHIFTBIT-1))) >> SHIFTBIT)

#ifdef ENABLE_REVERB_DBG_PRINTF
#define REVERB_DBG_MSG     Diag_printf
#else
#define REVERB_DBG_MSG     printf
#endif

#define SIZEOF_REVERB_DATA      (sizeof(tU8) + sizeof(tU8))

typedef struct
{
	tS32* p32_base_addr;
	tS32* tail;
	tS32* head;
	tS16 s16length;
	tS32* p32_end_addr;
	tS32 s32b;
	tS32 s32a1;
	tS32 s32a2;
}STR_MEMDELAY;
typedef struct
{
	tU8 bEn;
	tU8 u8mode;
}STR_SETREVERB;

typedef struct
{
	tS16 s16ch_num;
	tS32 s32_smprate;
	tS16 s16comb_num;
	tS16 s16AP_num;
	tS16* p16combTapNum;
	tS16* p16APTapNum;
	STR_MEMDELAY* str_combfilter;
	STR_MEMDELAY* str_APfilter;
	STR_SETREVERB str_set_reverb;
	tS32* p32combbuf_addr;
	tS32* p32APbuf_addr;
	tS32 s32ori_gain;
	tS32 s32rvb_gain;
	tS16* p16delaybuf;
	tS16 s16delaylength;
	tU8 updateflag;
       tU8 buf_allocflag;
	tU16 u16SmpRtIdx;
	tS16 delayline_H;
	tS16 delayline_T;
	tS32* proc_tempbuf;
}STR_REVERB;
/*============================================================================*/
// Global function definition
/*============================================================================*/

tBOOL Reverb_Allocate(void* void_str_rvb, tU8* alloc_buf);
tBOOL Reverb_Init(void* void_str_rvb, void* void_set_rvb, tS16 s16ch_num, tS32 sample_rate);
tBOOL Reverb_Check(void* void_str_rvb, void* void_set_rvb, tU8* checkflag);
tBOOL Reverb_update(void* void_str_rvb, void* void_set_rvb);
tBOOL Reverb_SetMode(void* void_set_rvb, tU8 u8mode);
tBOOL Reveb_SetOnOFF(void* void_set_rvb, tU8 enb);
tBOOL Reverb_Proc(void* void_str_rvb, tS16* s16in_buf, tS32 s32in_size_perCh, tS32 S32ch_num);
tBOOL Reverb_close(void* void_str_rvb, void* void_set_rvb);
tBOOL Reveb_SetPower(void* void_set_rvb, tU8 enb);
tBOOL Reveb_GetPower(void* void_set_rvb, tU8* enb);
tBOOL Reverb_GetMode(void* void_set_rvb, tU8* u8mode);
tBOOL Reverb_GetMemSize(tS32* s32Bufsize);
tS32 POSTPROCMGR_ATTR_16BITS AUD_ReverbPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_ReverbPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_ReverbPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);

#endif /* __REVERB_H__ */


