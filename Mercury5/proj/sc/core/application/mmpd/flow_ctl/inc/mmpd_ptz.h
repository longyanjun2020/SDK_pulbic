//==============================================================================
//
//  File        : mmpd_ptz.h
//  Description : INCLUDE File for the Host PTZ Driver.
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPD_PTZ_H_
#define _MMPD_PTZ_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_scal_inc.h"
#include "mmp_ptz_inc.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPD_PTZ_InitPtzRange(MMP_SCAL_PIPEID pipeID,
                              MMP_USHORT usMaxZoomRatio, 	MMP_USHORT usMaxZoomSteps,  
                              MMP_SHORT  sMaxPanSteps,  	MMP_SHORT  sMinPanSteps,
                              MMP_SHORT  sMaxTiltSteps, 	MMP_SHORT  sMinTiltSteps);
MMP_ERR MMPD_PTZ_InitPtzInfo(MMP_SCAL_PIPEID 	pipeID,
							 MMP_SCAL_FIT_MODE 	sFitMode,
                           	 MMP_USHORT usInputW,	MMP_USHORT usInputH, 
                          	 MMP_USHORT usOutputW, 	MMP_USHORT usOutputH);
MMP_ERR MMPD_PTZ_GetCurPtzInfo(MMP_SCAL_PIPEID pipeID, MMP_SCAL_FIT_RANGE *pFitRange, MMP_SCAL_GRAB_CTRL *pGrabCtl);
MMP_ERR MMPD_PTZ_GetCurPtzStep(MMP_SCAL_PIPEID pipeID, MMP_SHORT* sDir, 
							   MMP_USHORT* usZoomStep, MMP_SHORT* sPanStep, MMP_SHORT* sTiltStep);
MMP_UBYTE MMPD_PTZ_GetCurPtzStatus(void);
MMP_ERR MMPD_PTZ_SetTargetPtzStep(MMP_SCAL_PIPEID pipeID, MMP_SHORT sDir, 
								  MMP_USHORT usZoomStep, MMP_SHORT sPanStep, MMP_SHORT sTiltStep);
MMP_ERR MMPD_PTZ_CalculatePtzInfo(MMP_SCAL_PIPEID 	pipeID, 
								  MMP_USHORT 		usZoomStep,
                                  MMP_SHORT  		sPanStep,  
                                  MMP_SHORT  		sTiltStep);
MMP_ERR MMPD_PTZ_ReCalculateGrabRange(MMP_SCAL_FIT_RANGE	*pFitrange, 
                            		  MMP_SCAL_GRAB_CTRL	*pGrabctl);

MMP_ERR MMPD_PTZ_SetDigitalZoom(MMP_SCAL_PIPEID 	pipeID, 
                                MMP_PTZ_ZOOM_DIR 	zoomdir,
                                MMP_BOOL   	 		bZoomStart);
MMP_ERR MMPD_PTZ_SetDigitalZoomOP(MMP_UBYTE         ubSnrSel,
                                  MMP_SCAL_PIPEID 	pipeID, 
                              	  MMP_PTZ_ZOOM_DIR	zoomdir,
                              	  MMP_BOOL    		bZoomStart);
MMP_ERR MMPD_PTZ_CheckZoomComplete(MMP_SCAL_PIPEID pipeID, MMP_BOOL *pbComplete);

#endif //_MMPD_PTZ_H_