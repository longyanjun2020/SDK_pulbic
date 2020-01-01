//==============================================================================
//
//  File        : mmpd_ptz.c
//  Description : PTZ Control driver function
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_ptz.h"
#include "mmpf_ptz.h"
 
 //==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_InitPtzRange
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_PTZ_InitPtzRange(MMP_SCAL_PIPEID pipeID,
                              MMP_USHORT usMaxZoomRatio, 	MMP_USHORT usMaxZoomSteps,  
                              MMP_SHORT  sMaxPanSteps,		MMP_SHORT  sMinPanSteps,
                              MMP_SHORT  sMaxTiltSteps, 	MMP_SHORT  sMinTiltSteps)
{
	return MMPF_PTZ_InitPtzRange(pipeID, 
								 usMaxZoomRatio,	usMaxZoomSteps,
								 sMaxPanSteps, 		sMinPanSteps,
								 sMaxTiltSteps,		sMinTiltSteps);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_InitPtzInfo
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_PTZ_InitPtzInfo(MMP_SCAL_PIPEID 	pipeID,
							 MMP_SCAL_FIT_MODE 	sFitMode,
                           	 MMP_USHORT usInputW,	MMP_USHORT usInputH, 
                          	 MMP_USHORT usOutputW, 	MMP_USHORT usOutputH)
{
	return MMPF_PTZ_InitPtzInfo(pipeID, sFitMode, usInputW, usInputH, usOutputW, usOutputH);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_GetCurPtzInfo
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_PTZ_GetCurPtzInfo(MMP_SCAL_PIPEID pipeID, MMP_SCAL_FIT_RANGE *pFitRange, MMP_SCAL_GRAB_CTRL *pGrabCtl)
{
    return MMPF_PTZ_GetCurPtzInfo(pipeID, pFitRange, pGrabCtl);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_GetCurPtzStep
//  Description : 
//------------------------------------------------------------------------------
MMP_ERR MMPD_PTZ_GetCurPtzStep(MMP_SCAL_PIPEID pipeID, MMP_SHORT* sDir, 
							   MMP_USHORT* usZoomStep, MMP_SHORT* sPanStep, MMP_SHORT* sTiltStep)
{
	return MMPF_PTZ_GetCurPtzStep(pipeID, sDir, usZoomStep, sPanStep, sTiltStep);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_GetCurPtzStatus
//  Description :
//------------------------------------------------------------------------------
MMP_UBYTE MMPD_PTZ_GetCurPtzStatus(void)
{
	return MMPF_PTZ_GetCurZoomStatus();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_SetTargetPtzStep
//  Description : 
//------------------------------------------------------------------------------
MMP_ERR MMPD_PTZ_SetTargetPtzStep(MMP_SCAL_PIPEID pipeID, MMP_SHORT sDir, 
								  MMP_USHORT usZoomStep, MMP_SHORT sPanStep, MMP_SHORT sTiltStep)
{
	return MMPF_PTZ_SetTargetPtzStep(pipeID, sDir, usZoomStep, sPanStep, sTiltStep);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_CalculatePtzInfo
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_PTZ_CalculatePtzInfo(MMP_SCAL_PIPEID 	pipeID, 
								  MMP_USHORT 		usZoomStep,
                                  MMP_SHORT  		sPanStep,
                                  MMP_SHORT  		sTiltStep)
{
	return MMPF_PTZ_CalculatePtzInfo(pipeID, usZoomStep, sPanStep, sTiltStep);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_ReCalculateGrabRange
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_PTZ_ReCalculateGrabRange(MMP_SCAL_FIT_RANGE	*pFitrange, 
                            		  MMP_SCAL_GRAB_CTRL	*pGrabctl)
{
	return MMPF_PTZ_ReCalculateGrabRange(pFitrange, pGrabctl);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_SetDigitalZoom
//  Description :
//------------------------------------------------------------------------------
/** @brief The function enables the digital zoom operation

The function enables the digital zoom operation with the input of zoom direction

@param[in] direction the zoom in or zoom out
@param[in] pipeID the Scaler pipeID
@param[in] usZoomRateNum set the N increase or decrease in each ISR occured
@param[in] bZoomStart set zoom start to operate
@return It reports the status of the operation.
*/
MMP_ERR MMPD_PTZ_SetDigitalZoom(MMP_SCAL_PIPEID 	pipeID, 
                                MMP_PTZ_ZOOM_DIR	zoomdir,
                                MMP_BOOL   	 		bZoomStart)
{
    return MMPF_PTZ_SetDigitalZoom(pipeID, zoomdir, bZoomStart);;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_SetDigitalZoomOP
//  Description :
//------------------------------------------------------------------------------
/** @brief The function enables the digital zoom operation

The function enables the digital zoom operation with the input of zoom direction

@param[in] direction the zoom in or zoom out
@param[in] pipeID the Scaler pipeID
@return It reports the status of the operation.
*/
MMP_ERR MMPD_PTZ_SetDigitalZoomOP(MMP_UBYTE         ubSnrSel,
                                  MMP_SCAL_PIPEID 	pipeID, 
                                  MMP_PTZ_ZOOM_DIR	zoomdir,
                                  MMP_BOOL    		bZoomStart)
{
    return MMPF_PTZ_SetDigitalZoomOP(ubSnrSel, pipeID, zoomdir, bZoomStart);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_PTZ_CheckZoomComplete
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_PTZ_CheckZoomComplete(MMP_SCAL_PIPEID pipeID, MMP_BOOL *pbComplete)
{    
  	return MMPF_PTZ_GetZoomStatus(pipeID, pbComplete);
}
