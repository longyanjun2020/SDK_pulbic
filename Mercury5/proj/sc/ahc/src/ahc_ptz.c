/**
 @file ahc_ptz.c
 @brief ahc ptz(pan tilt zoom) control Function
 @author 
 @version 1.0
*/
/*===========================================================================
 * Include files
 *===========================================================================*/ 
#include "ahc_ptz.h"
#include "mmps_dsc.h"
#include "mmpd_ptz.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

/*===========================================================================
 * Extern function
 *===========================================================================*/ 
extern MMP_USHORT               gsAhcPrmSensor;

/*===========================================================================
 * Main body
 *===========================================================================*/ 
 
#if 0
void _____PTZ_Function_________(){} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_SetPreviewZoomConfig
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This API configures the abilities of digital zoom.

 This function configures the abilities of digital zoom. System calculates each
 zoom interval between steps according to the max multiplier. Currently, the zoom can
 only based on center of scene.

 Parameters:

 @param[in] bySteps        Max Zoom Step
 @param[in] byMaxRatio     Max Zoom Ratio
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_SetPreviewZoomConfig(UINT16 bySteps, UINT8 byMaxRatio)
{
    MMPS_DSC_SetZoomConfig(bySteps, byMaxRatio);
    MMPS_3GPRECD_SetZoomConfig(bySteps, byMaxRatio);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetPreviewZoom
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This API set Zoom-In / Zoom-Out

 This function set Zoom-In / Zoom-Out. Currently, the zoom can
 only based on center of scene.

 Parameters:

 @param[in] CaptureMode     Video mode or DSC mode
 @param[in] byDirection     Zoom-In or Zoom Out
 @param[in] byDirection     Zoom Step

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_SetPreviewZoom(AHC_CAPTURE_MODE CaptureMode, AHC_ZOOM_DIRECTION byDirection, UINT8 bySteps)
{
    MMP_BOOL        bInPreview  = MMP_FALSE;
    MMP_BOOL        bInRecord   = MMP_FALSE;
    MMP_ERR         error       = MMP_ERR_NONE;
    MMP_UBYTE 	    ubPipe      = 0;
    MMP_SHORT       sCurDir;
    MMP_USHORT      usCurZoomStep;

    if (VIDEO_CAPTURE_MODE == CaptureMode) {
        MMPS_3GPRECD_GetPreviewPipeStatus(gsAhcPrmSensor, &bInPreview);
        //MMPS_3GPRECD_GetPreviewPipe(gsAhcPrmSensor, &ubPipe);
        MMPS_3GPRECD_GetRecordPipeStatus(MMPS_VR_PRM_RECD, &bInRecord);
        
        if (!bInPreview) {
            return AHC_FALSE;
        }
    }
    else if (STILL_CAPTURE_MODE == CaptureMode) {
        MMPS_DSC_GetPreviewPipeStatus(gsAhcPrmSensor, &bInPreview);
        //MMPS_DSC_GetPreviewPipe(&ubPipe);

        if (!bInPreview) {
            return AHC_FALSE;
        }
    }

    if (byDirection != AHC_SENSOR_ZOOM_STOP) {

        MMPD_PTZ_GetCurPtzStep(ubPipe, &sCurDir, &usCurZoomStep, NULL, NULL);
        
        if (byDirection == AHC_SENSOR_ZOOM_IN) {
            sCurDir = MMP_PTZ_ZOOM_INC_IN;
        }
        else if (byDirection == AHC_SENSOR_ZOOM_OUT) {
            sCurDir = MMP_PTZ_ZOOM_INC_OUT;
        }
        
        if (((MMP_SHORT)usCurZoomStep + sCurDir * 1) <= 0)
            usCurZoomStep = 0;
        else
            usCurZoomStep += (sCurDir * 1);
    }
    
    if (byDirection == AHC_SENSOR_ZOOM_IN) {
        
        if (CaptureMode == STILL_CAPTURE_MODE) {
            error = MMPS_DSC_SetPreviewZoom(MMP_PTZ_ZOOMIN, usCurZoomStep);
        }
        else {
            if (bInRecord)
                error = MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH_BOTH, MMP_PTZ_ZOOMIN, usCurZoomStep);
            else
                error = MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH_PREV, MMP_PTZ_ZOOMIN, usCurZoomStep);
        }
    }
    else if (byDirection == AHC_SENSOR_ZOOM_OUT) {

        if (CaptureMode == STILL_CAPTURE_MODE) {
            error = MMPS_DSC_SetPreviewZoom(MMP_PTZ_ZOOMOUT, usCurZoomStep);
        }
        else {
            if (bInRecord)
                error = MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH_BOTH, MMP_PTZ_ZOOMOUT, usCurZoomStep);
            else
                error = MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH_PREV, MMP_PTZ_ZOOMOUT, usCurZoomStep);
        }
    }
    else if (byDirection == AHC_SENSOR_ZOOM_STOP) {

    	if (CaptureMode == STILL_CAPTURE_MODE) {
            error = MMPS_DSC_SetPreviewZoom(MMP_PTZ_ZOOMSTOP, usCurZoomStep);
        }
        else {
            if (bInRecord)
                error = MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH_BOTH, MMP_PTZ_ZOOMSTOP, usCurZoomStep);
            else
                error = MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH_PREV, MMP_PTZ_ZOOMSTOP, usCurZoomStep);
        }
    }
    else {
        return AHC_FALSE;
    }

    return (error == MMP_ERR_NONE) ? AHC_TRUE : AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PlaybackZoom
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set playback zoom

 Performs zoom during still image playback.
 Parameters:
 @param[in] uwStartX The top-left corner's X of the zoom window.
 @param[in] uwStartY The top-left corner' Y of the zoom window.
 @param[in] uwWidth The width of zoom window.
 @param[in] uwHeight The height of zoom window.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_PlaybackZoom(UINT16 uwStartX, UINT16 uwStartY, UINT16 uwWidth, UINT16 uwHeight)
{
    MMP_ERR error;

    error = MMPS_DSC_PlaybackExecutePTZ(uwStartX, uwStartY, uwWidth, uwHeight);

    if (MMP_ERR_NONE == error)
        return AHC_TRUE;
    else
        return AHC_FALSE;
}


