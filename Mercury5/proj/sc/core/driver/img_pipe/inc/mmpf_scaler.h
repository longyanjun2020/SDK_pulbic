//==============================================================================
//
//  File        : mmpf_scaler.h
//  Description : INCLUDE File for the Firmware Scaler Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_SCALER_H_
#define _MMPF_SCALER_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_scal_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define	SCALER_PATH0_MAX_WIDTH	    	(4608)
#define	SCALER_PATH1_MAX_WIDTH	        (1920)
#define	SCALER_PATH2_MAX_WIDTH	        (1280)
#define	SCALER_PATH3_MAX_WIDTH	        (1920)
#define	SCALER_PATH4_MAX_WIDTH	        (1920)
#define	LPF_MAX_WIDTH			        (SCALER_PATH0_MAX_WIDTH)

#define SCALER_ISR_EN                   (1)

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/* Scaler Function */
MMP_USHORT Greatest_Common_Divisor(MMP_USHORT a, MMP_USHORT b);

MMP_ERR MMPF_Scaler_ResetModule(MMP_SCAL_PIPEID pipeID);
MMP_ERR MMPF_Scaler_RegisterIntrCallBack(MMP_SCAL_PIPEID scalpath, MMP_SCAL_EVENT event, ScalCallBackFunc *pCallBack, void *pArgument);
MMP_ERR MMPF_Scaler_EnableInterrupt(MMP_SCAL_PIPEID pipeID, MMP_SCAL_EVENT event, MMP_BOOL bEnable);

MMP_ERR MMPF_Scaler_SetEngine(MMP_SCAL_USER_DEF_TYPE	bUserdefine, 
							  MMP_SCAL_PIPEID 			pipeID,
                        	  MMP_SCAL_FIT_RANGE 		*fitrange, 
                        	  MMP_SCAL_GRAB_CTRL 		*grabctl);
MMP_ERR MMPF_Scaler_SetOutputFormat(MMP_SCAL_PIPEID pipeID, MMP_SCAL_COLORMODE outcolor);
MMP_ERR MMPF_Scaler_SetOutColorTransform(MMP_SCAL_PIPEID pipeID, MMP_BOOL bEnable, MMP_SCAL_COLRMTX_MODE MatrixMode);
MMP_ERR MMPF_Scaler_SetEnable(MMP_SCAL_PIPEID pipeID, MMP_BOOL bEnable);
MMP_ERR MMPF_Scaler_GetEnable(MMP_SCAL_PIPEID pipeID, MMP_BOOL* bEnable);
MMP_ERR MMPF_Scaler_SetPath(MMP_SCAL_PIPEID pipeID, MMP_SCAL_SOURCE source);

MMP_ERR MMPF_Scaler_SetGrabPosition(MMP_SCAL_PIPEID 		pipeID,
									MMP_SCAL_GRAB_STAGE 	grabstage,
									MMP_USHORT 				usHStartPos, 
									MMP_USHORT 				usHEndPos, 
									MMP_USHORT 				usVStartPos, 
									MMP_USHORT 				usVEndPos);
MMP_ERR MMPF_Scaler_GetGrabPosition(MMP_SCAL_PIPEID pipeID, MMP_SCAL_GRAB_STAGE 	grabstage,
									MMP_USHORT *usHStartPos, MMP_USHORT *usHEndPos, 
									MMP_USHORT *usVStartPos, MMP_USHORT *usVEndPos);
MMP_ERR MMPF_Scaler_GetGrabRange(	MMP_SCAL_PIPEID 		pipeID,
									MMP_SCAL_GRAB_STAGE 	grabstage,
									MMP_USHORT 				*usWidth, 
									MMP_USHORT 				*usHeight);
MMP_ERR MMPF_Scaler_GetScalingRatio(MMP_SCAL_PIPEID 	pipeID, 
									MMP_USHORT *usHN, MMP_USHORT *usHM,
									MMP_USHORT *usVN, MMP_USHORT *usVM);

MMP_ERR MMPF_Scaler_GetAttributes(MMP_SCAL_PIPEID pipeID);
MMP_ERR MMPF_Scaler_SetAttributes(MMP_SCAL_PIPEID pipeID);
MMP_UBYTE MMPF_Scaler_MapDispColorToScalerColor(MMP_UBYTE ubDispColor);

/* Flow Function */
MMP_ERR MMPF_Scaler_GetGCDBestFitScale(MMP_SCAL_FIT_RANGE *fitrange, MMP_SCAL_GRAB_CTRL *grabctl);
MMP_ERR MMPF_Scaler_BestFitOutOfRangeHandler(MMP_SCAL_FIT_RANGE *fitrange, MMP_SCAL_GRAB_CTRL *grabctl, MMP_USHORT usMaxMNVal, MMP_BOOL ubIsDirY);

#ifdef SCAL_FUNC_DBG
MMP_ERR MMPF_Scaler_DumpSetting(MMP_UBYTE           *pFuncName,
								MMP_SCAL_FIT_RANGE  *fitrange,
                                MMP_SCAL_GRAB_CTRL  *grabctl);
#endif

#endif // _MMPF_SCALER_H_
