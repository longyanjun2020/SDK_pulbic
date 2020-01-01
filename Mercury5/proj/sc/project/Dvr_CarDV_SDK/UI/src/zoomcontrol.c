/*===========================================================================
 * Include file 
 *===========================================================================*/
 
#include "ahc_common.h"
#include "ahc_capture.h"
#include "ahc_video.h"
#include "zoomcontrol.h"

/*===========================================================================
 * Main body
 *===========================================================================*/

//------------------------------------------------------------------------------
//  Function    : ZoomCtrl_GetVideoDigitalZoomLevel
//  Description :
//------------------------------------------------------------------------------
UINT16 ZoomCtrl_GetVideoDigitalZoomLevel(void)
{
    UINT16 usCurZoomStep = 0;
    
    AHC_VIDEO_GetCurZoomStep(&usCurZoomStep);
    
    return usCurZoomStep;
}

//------------------------------------------------------------------------------
//  Function    : ZoomCtrl_GetVideoDigitalZoomMax
//  Description :
//------------------------------------------------------------------------------
UINT16 ZoomCtrl_GetVideoDigitalZoomMax(void)
{
    UINT16 usMaxZoomStep = 0;
    
    AHC_VIDEO_GetMaxZoomStep(&usMaxZoomStep);
    
    return usMaxZoomStep;
}

//------------------------------------------------------------------------------
//  Function    : ZoomCtrl_GetStillDigitalZoomLevel
//  Description :
//------------------------------------------------------------------------------
UINT16 ZoomCtrl_GetStillDigitalZoomLevel(void)
{
    UINT16 usCurZoomStep;
    
    AHC_Capture_GetCurZoomStep(&usCurZoomStep);
    
    return usCurZoomStep;
}

//------------------------------------------------------------------------------
//  Function    : ZoomCtrl_GetStillDigitalZoomMax
//  Description :
//------------------------------------------------------------------------------
UINT16 ZoomCtrl_GetStillDigitalZoomMax(void)
{
	UINT16 usZoomMaxStep;
	
	AHC_Capture_GetMaxZoomStep(&usZoomMaxStep);

	return usZoomMaxStep;
}

//------------------------------------------------------------------------------
//  Function    : ZoomCtrl_DigitalZoom
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL ZoomCtrl_DigitalZoom(AHC_CAPTURE_MODE iMode, AHC_ZOOM_DIRECTION bZoomDir)
{
    return AHC_SetPreviewZoom(iMode, bZoomDir, 1);
}

//------------------------------------------------------------------------------
//  Function    : ZoomCtrl_GetDigitalZoomRatio
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL ZoomCtrl_GetDigitalZoomRatio(UINT32 *ZoomRatio)
{
	AHC_BOOL ahc_ret = AHC_TRUE;
	UINT32   CurMode;
   
	AHC_GetSystemStatus(&CurMode);
	CurMode >>= 16;
   
	if ((CurMode == AHC_MODE_CAPTURE_PREVIEW)) {
		ahc_ret = AHC_Capture_GetDigitalZoomRatio(ZoomRatio);
	}
	else if((CurMode == AHC_MODE_VIDEO_RECORD)||
			(CurMode == AHC_MODE_RECORD_PRERECD)||
			(CurMode == AHC_MODE_RECORD_PREVIEW)) {
		ahc_ret = AHC_VIDEO_GetDigitalZoomRatio(ZoomRatio);
	}
   
	return ahc_ret;
}
