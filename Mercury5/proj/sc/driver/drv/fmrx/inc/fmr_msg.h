/**
 *
 * @file    fmr_msg.h
 *
 * @brief   This module defines the EMA audio message struct type for camera interface using.
 *
 * @author  Roger Lai
 * @version $Id: ema_aud_msg.h 446 2008-03-07 14:03:44Z roger.lai $
 *
 */
#ifndef __FMR_MSG_H__
#define __FMR_MSG_H__



#if 0
/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_fmr_itf.h"



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

typedef struct{
    esl_FmrAreaConfig_t fmrAreaConfig;
  }fmrAreaConfig_t;
#endif

typedef struct 
{
	esl_FmrCb_t  *pFmrCb;
	//esl_FmrInfo_t *pFmrGetRsp;
	union
	{
    u8            powerOnOff;
    u8            muteOnOff;
    u8            stereoOnOff;
    u32           frequency;  
    esl_FmrBand_e band; 
    
    struct{
		  u8            onOff;         /**< seek channel on/off */
      u8            direction;     /**< seek channel direction up/down */
	  } seek;
    
    #ifdef __ONCHIP_FMRX_ENABLE__
    struct{
      u8   carrierOn;             /**< Carrier Lock threshold */
      u8   carrierOff;            /**< Carrier Unlock threshold */
	  } carrierThreshold;    

    fmrAreaConfig_t fmrAreaConfigCmd;

    
    ema_FmrRegNotify_t         fmrRegNotifyParam;
    ema_FmrRecParam_t          recFile;
    ema_FmrRecGetMedium_t      recMedium;
    #endif    
	} param;
} dev_FmrCmd_t;

typedef union
{
    vm_osTimerMsgBody_t             timerMsg;
  dev_FmrCmd_t fmrCmd;

} vm_msgBody_t;


#endif

#endif

