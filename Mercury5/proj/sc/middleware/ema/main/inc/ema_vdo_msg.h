/**
 *
 * @file    ema_vdo_msg.h
 *
 * @brief   This file defines the message related type of video service
 *
 * @author  Pauli Leong
 * @version $Id: ema_vdo_msg.h 13835 2008-09-03 02:31:46Z jack.hsieh $
 *
 */
#ifndef __EMA_VDO_MSG_H__
#define __EMA_VDO_MSG_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_vdo_itf.h"
#include "ema.h"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The structure defines the video media file parameter for playback operation message
 */
typedef struct{
	esl_VdoFileParam_t  fileParam;
  u32                 position;
} ema_vdoPlayFile_t;

typedef struct{
	esl_VdoMemInfo_t 		 memInfo;
  esl_VdoRotateAngle_e rotateAngle;      /**< Video rotation angle */
  esl_VdoRegion_t      playRegion;       /**< Video playback region */
  u8                   transLevel;       /**< Video playback OSD transparency level (0~255) 0: transparent 255: opaque*/
	u32									 position;
} ema_vdoPlayMem_t;

typedef struct{
  esl_VdoNotifyCb_t    notify;
  esl_VdoNotifyType_e  notifyType;
} ema_vdoNotifyCmd_t;

typedef struct{
	esl_VdoRegion_t        region;
  esl_VdoRotateAngle_e   rotateAngle;
} ema_vdoResetWindow_t;

/**
 *  @brief The structure defines the video media message body for playback operation message
 */
typedef struct {
	ema_TransType_t	TransType;
	esl_VdoCb_t     *pVdoCb;
	union
	{
		ema_vdoPlayFile_t      vdoPlayFileCmd;
		ema_vdoPlayMem_t			 vdoPlayMemCmd;
		esl_VdoFileInfo_t      vdoGetPlayInfoCmd;		
		esl_VdoMemInfo_t	  	 vdoGetInfoFromMemCmd;
    esl_VdoFileParam_t     vdoPlayfirstFrameCmd;
    esl_VdoPlaySpeed_e     vdoSetSpeedCmd;
    u32                    vdoSetPositionCmd;
	  ema_vdoNotifyCmd_t     vdoNotifyCmd;
    esl_VdoNotifyInfo_t    vdoNotifyEMACmd;
    esl_VdoDecodeParam_t   vdoDecodeFirstFrameCmd;
		esl_VdoDecodeMemParam_t vdoDecodeFirstFrameMemCmd;
    ema_vdoResetWindow_t   vdoResetWindowCmd;
    esl_VdoStreamParam_t   vdoPlayStreamCmd;
    esl_VdoFileInfo_t      vdoPlayInitCmd;
	} cmdType;
} ema_VdoCmd_t;

/**
 *  @brief The structure defines the video media response message for playback operation message
 */
typedef struct {
	u16             sender;
	ema_TransType_t	TransType;
	ema_ErrCode_e   errorStatus;	
} ema_VdoRsp_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_VDO_MSG_H__ */




