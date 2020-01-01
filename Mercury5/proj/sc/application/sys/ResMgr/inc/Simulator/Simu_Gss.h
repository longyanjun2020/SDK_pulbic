/**
* @file Simu_Gss.h
*
* This header file defines the interface of lower layer device simulation for codec
*
*/
#ifndef __SIMU_GSS_H__
#define __SIMU_GSS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "Simu_Cmn.h"
#include "ABL_Gss.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Simu_GssSetEXIFCb(void *pUserData);
void Simu_GssDecodeRegionCb(void *pUserData);
void Simu_GssDecodeExtCb(void *pUserData);
void Simu_GssEncodeCb(void *pUserData, ABL_GssEncodeSetting_t *pEncodeParams);
void Simu_MmlGssEncodeCb(void *pUserData, MmlImageEncodeImage_t *pEncodeParams);
void Simu_GssRenderStarCb(void *pUserData);
void Simu_GssRenderStopCb(void *pUserData);
void Simu_GssRenderInputCb(void *pUserData);
void Simu_GssRenderGetInfoCb(void *pUserData);
void Simu_GssRenderGetCapabilityCb(void *pUserData);
void Simu_GssImageGetDecodingCapabilityCb(void *pUserData);
#endif //__SIMU_GSS_H__
