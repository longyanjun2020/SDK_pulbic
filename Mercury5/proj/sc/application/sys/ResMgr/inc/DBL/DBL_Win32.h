/**
* @file DBL_Win32.h
*
* Driver Bridge Layer defines the bridge functions between drivers 
* and Resource Manager.
*
* This header file defines the declaration of camera win32 simulations.
* 
*/

#ifndef __DBL_WIN32_H__
#define __DBL_WIN32_H__

#ifdef __SDK_SIMULATION__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "esl_aud_itf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void CamGetConfig(u8 *pPath, u16 *pPathLen);
void CamGetAttribution(u8 camAttrType, void *pValue);
esl_AudErrCode_e esl_AudGetPositionReq(esl_AudCb_t *pAudDoneCB);

#endif //__SDK_SIMULATION__
#endif //__DBL_WIN32_H__
