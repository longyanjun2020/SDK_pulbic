#ifndef _PCAM_USB_H_
#define _PCAM_USB_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "pCam_api.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_BOOL   USB_IsPreviewActive(void);
MMP_USHORT USB_SetSaturation(MMP_USHORT val);
MMP_USHORT USB_SetContrast(MMP_USHORT val);
MMP_USHORT USB_SetBrightness(MMP_SHORT val);
MMP_USHORT USB_SetHue(MMP_SHORT val);
MMP_USHORT USB_SetGamma(MMP_USHORT val);
MMP_USHORT USB_SetBacklight(MMP_USHORT val);
MMP_USHORT USB_SetSharpness(MMP_USHORT val);
MMP_USHORT USB_SetLensPosition(MMP_USHORT val);
MMP_USHORT USB_EnableAF(MMP_BOOL val);
MMP_USHORT USB_EnableAE(MMP_BOOL val);
MMP_USHORT USB_SetAWBMode(MMP_UBYTE val);
MMP_USHORT USB_SetAWBTemp(MMP_USHORT val);
MMP_USHORT USB_SetPowerLineFreq(MMP_UBYTE val);
MMP_USHORT USB_SetH264Resolution(PCAM_USB_VIDEO_RES pCamRes);
MMP_USHORT USB_SetVideoFormat(PCAM_USB_VIDEO_FORMAT pCamVidFmt);
MMP_USHORT USB_SetVideoQuality(PCAM_USB_VIDEO_QUALITY pCamQ);
MMP_USHORT USB_SetVideoResolution(PCAM_USB_VIDEO_RES pCamRes);
MMP_USHORT USB_SetDigitalZoom(MMP_UBYTE dir,MMP_UBYTE range_min,MMP_UBYTE range_max,MMP_UBYTE range_step);
MMP_USHORT USB_SetDigitalPanTilt(MMP_LONG pan_min,MMP_LONG pan_max,MMP_LONG tilt_min,MMP_LONG tilt_max,MMP_USHORT total_step);
MMP_USHORT USB_SetAsyncVideoControl(MMP_UBYTE bOriginator,MMP_UBYTE bSelector,MMP_UBYTE bAttribute,MMP_UBYTE bValUnit);
MMP_UBYTE  USB_GetInternalStreamId(MMP_UBYTE commitedsId);

#endif //_PCAM_USB_H_
