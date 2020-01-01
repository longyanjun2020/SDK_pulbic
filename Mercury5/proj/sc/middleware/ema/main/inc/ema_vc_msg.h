/**
 *
 * @file    ema_vc_msg.h
 *
 * @brief   This module defines the EMA camera message struct type for Video Chat interface using.
 *
 * @author  Kurt Chen
 * @version $Id $
 *
 */
#ifndef __EMA_VC_MSG_H__
#define __EMA_VC_MSG_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_vc_itf.h"




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define DefExtern
#else
#define DefExtern extern
#endif




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

typedef struct{
  esl_VcCamID_e   camId;
}ema_VcPower_t;

typedef struct{
	esl_Vc_Index_e				index;
  esl_Vc_Control_e      ctrl;
  esl_Vc_Size_t         frame_size;
  esl_Vc_Colorformat_e  color_format;
  esl_Vc_Buff_t         buffer_info;
}ema_VcPreviewCmd_t;


typedef struct{
  esl_Vc_Source_t 			source;
  esl_Vc_Destination_t  destination;
}ema_VcColorConversion_t;

typedef struct{
//  esl_CamCb_t     *pCamDoneCB;
  ema_TransType_t TransType;
  esl_VcCb_t     *pVcDoneCB;
  union
  {
    ema_VcPower_t           vcPowerCmd;
    ema_VcPreviewCmd_t      vcPreviewCmd;
    ema_VcColorConversion_t vcCoversionCmd;
  } cmdType;
} ema_VC_Cmd_t;






/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/




#endif /* __EMA_CAM_MSG_H__ */

