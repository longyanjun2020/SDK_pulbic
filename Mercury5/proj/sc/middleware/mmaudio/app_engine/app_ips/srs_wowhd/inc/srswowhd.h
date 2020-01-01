////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-20011 MStar Semiconductor, Inc.
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
* @file    : srs_wowhd.h
* @version : 1.0
* @author  :
* @brief   : SRS 3D speaker and headphone wrapper header
*/

#ifndef __SRSWOWHD_H__
#define __SRSWOWHD_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "app_datatype.h"
#include "srs_wowhd_api.h"
#include "srs_wowhd_api.h"
#include "srs_fxp.h"
/*============================================================================*/
// Extern definition
/*============================================================================*/
//...

/*============================================================================*/
// Macro definition
/*============================================================================*/
/*---------------- Print Message Switch -----------------*/
#define ENABLE_WOWHD_PARSER_PRINTF

/*---------------------- Interface ----------------------*/

typedef struct
{
    tS32 *Left;
    tS32 *Right;
}M_SRS_AudioIO;

typedef struct
{
    tU8 bEn;
    // SRS 3D par
    tS32 s32_3Denable;
    tS16 s163DSpaceCtrl;
    tS16 s163DCenterCtrl;
    tS32 s32_3DHeadphone;
    tU8 u83DMode;
    tS32 s32hbrate;
    //TRUE BASS par
    tS32 s32TBEnable;
    tS16 s16TBCtrl;
    tS32 s32TBSpeakerSz_Audio;
    tS32 s32TBSpeakerSz_Analysis;
    tU8 u8TBMode;
    tS16 s16TBCompressCtrl;
    tS32 s32TBSplitAnalysisEnable;
    //Definition par
    tS32 s32DefEnable;
    tS16 s16DefFactor;
    // focus par
    tS32 s32FocusEnable;
    tS16 FocusFactor;
    //Limiter par
    tS32 s32minGain;
    tS32 s32LmtEnable;
    // common par
    tS16 s16InputGain; //i16.1 0.0-1.0
    tS16 s16Outputgain; //i16.1 0.0-1.0
    tS16 s16BypassGain; //i16.1 0.0-1.0

}M_WOWHD_PAR_s;

#define SIZEOF_SRSWOWHD_DATA (sizeof(tS32)*11 +sizeof(tS16)*9+sizeof(tU8)*3)


typedef struct
{
    tS32 s32SampleRate;
    M_SRS_AudioIO AudioIO;
    tU8* pu8mem;
    tS16* queue_buf;
    tS8* wowhdobj_buf;  //SRS_WOWHD_OBJ_SIZE is 704 bytes
    tS8* cshpobj_buf;   //SRS_CSHP_OBJ_SIZE  is 1804 bytes
    tBOOL bUpdateFlag;
    M_WOWHD_PAR_s setpar;

    SRSWowhdObj wowhdObj;  //WowhdObj is 4 bytes
    tS32 SRS_SetPath;
    tS32 queue_size;       //MAX is 256 sample of one channel
}M_WOWHD_MAIN_s;


/*============================================================================*/
// Variable definition
/*============================================================================*/
#define SRS_BLKSZ		256		//processing block size
#define SRS_WOWHD_WORKSPACE_SIZES(blksize)	(sizeof(tS32)*6*(blksize)+128)
#define SRS_CSHP_WORKSPACE_SIZES  24*1024 //23568 base on blksize is 256
/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif

// Parser

// Par
// Main
tBOOL AUD_WOWHDMain_Init(void* void_pIP, void* void_set_ip, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_WOWHDMain_Proc(void* void_pIP, tS16* ptProcBuf, tS32* ps32ProcSizePerCh);
tBOOL AUD_WOWHDMain_Close(void* void_pIP);
tBOOL AUD_WOWHD_SetMode(void* void_set_ip,tS32 s32mode);
tBOOL AUD_WOWHD_SetPath(void* void_set_ip,tS32 s32path);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_WOWHDPar_SetPower(void *void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_WOWHDPar_GetPower(void* void_pSet, tU8* pbEn);
tBOOL AUD_WOWHDMain_Check(void* void_pIP, void* void_pSet, tU8* pbUpdateFlag);
tBOOL AUD_WOWHDMain_Update(void* void_pIP,  void* void_pSet);
tBOOL AUD_WOWHD_Set3DEnable(void* void_set_ip,tS32 s32_3Denable);
tBOOL AUD_WOWHD_Set3DSpaceCtrl(void* void_set_ip,tS16 s16_3DSpaceCtrl);
tBOOL AUD_WOWHD_Set3DCenterCtrl(void* void_set_ip,tS16 s16_3DCenterCtrl);
tBOOL AUD_WOWHD_Set3DModeCtrl(void* void_set_ip,tU8 u8_3DModeCtrl);
tBOOL AUD_WOWHD_SetTBEnable(void* void_set_ip,tS32 s32TBEnable);
tBOOL AUD_WOWHD_SetTBCtrl(void* void_set_ip,tS16 s16TBCtrl);
tBOOL AUD_WOWHD_SetTBSpeakerSz(void* void_set_ip,tS16 s16TBSpeakerSz_Audio,tS16 s16TBSpeakerSz_Analysis );
tBOOL AUD_WOWHD_SetTBMode(void* void_set_ip,tS16 s16TBMode);
tBOOL AUD_WOWHD_SetTBCompressCtrl(void* void_set_ip,tS16 s16TBCompressCtrl);
tBOOL AUD_WOWHD_SetDefEnable(void* void_set_ip,tS32 s32DefEnable);
tBOOL AUD_WOWHD_SetDefFactor(void* void_set_ip,tS32 s16DefFactor);
tBOOL AUD_WOWHD_SetFocusEnable(void* void_set_ip,tS32 s32FocusEnable);
tBOOL AUD_WOWHD_SetFocusFactor(void* void_set_ip,tS16 FocusFactor);
tBOOL AUD_WOWHD_SetLmtMinGain(void* void_set_ip,tS32 s32minGain);
tBOOL AUD_WOWHD_SetLmtEnable(void* void_set_ip,tS32 s32LmtEnable);
tBOOL AUD_WOWHD_SetInputGain(void* void_set_ip,tS16 s16InputGain);
tBOOL AUD_WOWHD_SetOutputGain(void* void_set_ip,tS16 s16OutputGain);
tBOOL AUD_WOWHD_SetByPassGain(void* void_set_ip,tS16 s16BypassGain);
tS32 POSTPROCMGR_ATTR_16BITS AUD_SRSWOWHDPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_SRSWOWHDPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_SRSWOWHDPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);
tBOOL AUD_WOWHD_Sethbrate(void* void_set_ip,tS32 s32hbrate);
tBOOL AUD_WOWHD_SetsTBSplitAnalysisEnable(void* void_set_ip,tS32 s32TBSplitAnalysisEnable);



#ifdef __cplusplus
}
#endif

#endif /* __DM2_H__ */


