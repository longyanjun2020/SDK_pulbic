//==============================================================================
//
//  File        : mmpd_display.h
//  Description : INCLUDE File for the Host Display Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPD_DISPLAY_H_
#define _MMPD_DISPLAY_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_display_inc.h"

/** @addtogroup MMPD_Display
 *  @{
 */

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

// HDMI Function
MMP_ERR MMPD_Display_SetHDMIOutput(MMP_DISPLAY_CONTROLLER controller, MMP_HDMI_ATTR *hdmiattribute,
                                   MMP_DISPLAY_RGB_IF rgbIf);
MMP_ERR MMPD_HDMI_DisableHDMI(MMP_DISPLAY_RGB_IF ubRgbIf);
MMP_ERR MMPD_HDMI_InitDigital(MMP_HDMI_ATTR *hdmiAttr);
MMP_ERR MMPD_HDMI_InitAnalog(MMP_HDMI_ATTR *hdmiAttr);
MMP_ERR MMPD_HDMI_Initialize(MMP_HDMI_ATTR *hdmiAttr, MMP_DISPLAY_RGB_IF rgbIf);
MMP_ERR MMPD_HDMI_ParseEDID(MMP_UBYTE *pEDID, MMP_ULONG *pSpportFormat, MMP_ULONG *pEDIDType);

// TV Function
MMP_ERR MMPD_Display_SetTVOutput(MMP_DISPLAY_CONTROLLER controller, MMP_TV_ATTR *tvattribute,
                                 MMP_DISPLAY_RGB_IF rgbIf);
MMP_ERR MMPD_TV_Initialize(MMP_BOOL bInit,MMP_TV_TYPE output_panel);
MMP_ERR MMPD_TV_EnableDisplay(MMP_UBYTE enable);
MMP_ERR MMPD_TV_SetInterface(MMP_TV_ATTR *tvAttr);
MMP_ERR MMPD_TV_EncRegSet(MMP_ULONG addr, MMP_ULONG data);
MMP_ERR MMPD_TV_EncRegGet(MMP_ULONG addr, MMP_ULONG *data);
MMP_ERR MMPD_TV_SetBrightLevel(MMP_UBYTE ubLevel);
MMP_ERR MMPD_TV_SetContrast(MMP_USHORT usLevel);
MMP_ERR MMPD_TV_SetSaturation(MMP_UBYTE ubUlevel, MMP_UBYTE ubVlevel);
MMP_ERR MMPD_TV_SetInterlaceMode(MMP_BOOL bEnable);
MMP_ERR MMPD_TV_GetBrightLevel(MMP_UBYTE *pubLevel);
MMP_ERR MMPD_TV_GetContrast(MMP_USHORT *pusLevel);
MMP_ERR MMPD_TV_GetSaturation(MMP_UBYTE *pubUlevel, MMP_UBYTE *pubVlevel);
MMP_ERR MMPD_TV_GetGamma(MMP_DISPLAY_TV_GAMMA *DspyGamma);

/// @}
#endif // _MMPD_DISPLAY_H_
