//==============================================================================
//
//  File        : mmpf_ptz.h
//  Description : INCLUDE File for the Firmware PTZ Control driver function
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_PTZ_H_
#define _MMPF_PTZ_H_

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

MMP_ERR MMPF_PTZ_InitPtzRange(MMP_SCAL_PIPEID pipeID,
                              MMP_USHORT usMaxZoomRatio, 	MMP_USHORT usMaxZoomSteps,  
                              MMP_SHORT  sMaxPanSteps, 		MMP_SHORT  sMinPanSteps,
                              MMP_SHORT  sMaxTiltSteps, 	MMP_SHORT  sMinTiltSteps);
MMP_ERR MMPF_PTZ_InitPtzInfo(MMP_SCAL_PIPEID 	pipeID,
							 MMP_SCAL_FIT_MODE 	sFitMode,
                       		 MMP_USHORT usInputW,	MMP_USHORT usInputH, 
                         	 MMP_USHORT usOutputW, 	MMP_USHORT usOutputH);
MMP_ERR MMPF_PTZ_GetCurPtzInfo(MMP_SCAL_PIPEID path, MMP_SCAL_FIT_RANGE *fitrange, MMP_SCAL_GRAB_CTRL *grabctl);
MMP_ERR MMPF_PTZ_GetCurPtzStep(MMP_SCAL_PIPEID PathSel, MMP_SHORT* sDir, 
							   MMP_USHORT* usZoomStep, MMP_SHORT* sPanStep, MMP_SHORT* sTiltStep);
MMP_UBYTE MMPF_PTZ_GetCurZoomStatus(void);
MMP_ERR MMPF_PTZ_SetTargetPtzStep(MMP_SCAL_PIPEID PathSel, MMP_SHORT sDir, 
								  MMP_USHORT usZoomStep, MMP_SHORT sPanStep, MMP_SHORT sTiltStep);
MMP_ERR MMPF_PTZ_CalculatePtzInfo(MMP_SCAL_PIPEID 	pipeID, 
								  MMP_USHORT 		usZoomStep,
                                  MMP_SHORT  		sPanStep,  
                                  MMP_SHORT  		sTiltStep);
MMP_ERR MMPF_PTZ_ReCalculateGrabRange(MMP_SCAL_FIT_RANGE	*pFitrange, 
                            		  MMP_SCAL_GRAB_CTRL	*pGrabctl);

/* Common PTZ Function */
MMP_ERR MMPF_PTZ_SetDigitalZoom(MMP_SCAL_PIPEID 	pipeID, 
								MMP_PTZ_ZOOM_DIR 	zoomdir, 
                                MMP_BOOL   			bStartOP);
MMP_ERR MMPF_PTZ_SetDigitalZoomOP(MMP_UBYTE         ubSnrSel,
                                  MMP_SCAL_PIPEID 	pipeID,
                                  MMP_PTZ_ZOOM_DIR	zoomdir, 
                                  MMP_BOOL    		bStartOP);

MMP_ERR MMPF_PTZ_ExecutePTZ(MMP_UBYTE ubSnrSel);
MMP_ERR MMPF_PTZ_GetZoomStatus(MMP_SCAL_PIPEID pipeID, MMP_BOOL *pbZoomStatus);

#endif //_MMPF_PTZ_H_