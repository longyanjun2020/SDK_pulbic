/**
* @file Simu_VdoChat.h
*
* This header file defines the interface of lower layer device simulation for video chat
*
*/
#ifndef __VENDOR_SMALLROM__
#ifndef __SIMU_VDOCHAT_H__
#define __SIMU_VDOCHAT_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "Simu_Cmn.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Simu_VdoChatInitCb(void *pUserData);
void Simu_VdoChatExitCb(void *pUserData);
void Simu_VdoChatPreviewStartCb(void *pUserData);
void Simu_VdoChatPreviewStopCb(void *pUserData);
void Simu_VdoChatPreviewGetFrameCb(void *pUserData);
void Simu_VdoChatConvertImageCb(void *pUserData);
void Simu_VdoChatSetFrameBuffSizeCb(void *pUserData);
#endif //__SIMU_VDOCHAT_H__
#endif