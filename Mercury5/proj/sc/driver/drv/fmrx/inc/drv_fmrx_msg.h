////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
 *
 * @file    drv_fmrx_msg.h
 * @brief   This module defines the EMA audio message struct type for camera interface using.
 */
#ifndef __DRV_FMRX_MSG_H__
#define __DRV_FMRX_MSG_H__
#if 0
/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#define  vm_msg_t  vm_msg_t


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
#ifdef __ONCHIP_FMRX_ENABLE__
typedef struct							
{
	esl_FmrRecParam_t recParam;  
} ema_FmrRecParam_t;

typedef struct							/*Get sample rate*/
{
  esl_FmrFileParam_t fileParam;
} ema_FmrRecGetMedium_t;

typedef struct{
  esl_FmrNotifyType_e       notifyType;
  esl_FmrNotifyCb_t         notifyCb;
}ema_FmrRegNotify_t;
#endif

typedef struct
{
    esl_FmrCb_t *pFmrCb;
    //esl_FmrInfo_t *pFmrGetRsp;
    union
    {
        u8 powerOnOff;
        u8 muteOnOff;
        u8 stereoOnOff;
        u32 frequency;
#ifdef __ONCHIP_FMRX_ENABLE__
        //esl_FmrArea_e area;  //XXXXX FIX ME! 
#endif
        esl_FmrBand_e band;
    
    struct{
            u8 onOff; /**< seek channel on/off */
            u8 direction; /**< seek channel direction up/down */
        } seek;
    #ifdef __ONCHIP_FMRX_ENABLE__
    ema_FmrRegNotify_t         fmrRegNotifyParam;
    ema_FmrRecParam_t          recFile;
    ema_FmrRecGetMedium_t      recMedium;   
    struct{
      u8   carrierOn;             /**< Carrier Lock threshold */
      u8   carrierOff;            /**< Carrier Unlock threshold */
	  } carrierThreshold;    
    #endif
    } param;
} dev_FmrCmd_t;

typedef union
{
    dev_FmrCmd_t fmrCmd;

} vm_msgBody_t;
#endif

#endif //#ifndef __DRV_FMRX_MSG_H__
