//==============================================================================
//
//  File        : mmps_display.h
//  Description : INCLUDE File for the Host Display Control driver function
//  Author      : Alan Wu
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPS_DISPLAY_H_
#define _MMPS_DISPLAY_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmp_display_inc.h"
#include "mmp_snr_inc.h"

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _MMPS_DISPLAY_CONFIG {
    MMP_LCD_ATTR                mainlcd;        ///< Main LCD attribute
    MMP_LCD_ATTR                sublcd;         ///< Sub LCD attribute
    MMP_TV_ATTR                 ntsctv;         ///< NTSC TV attribute
    MMP_TV_ATTR                 paltv;          ///< NTSC PAL attribute
    MMP_HDMI_ATTR               hdmi;           ///< HDMI attribute
    MMP_CCIR_ATTR               ccir;           ///< CCIR attribute
    MMP_DISPLAY_OUTPUT_SEL      OutputPanel;
} MMPS_DISPLAY_CONFIG;

//===============================================================================
//
//                               ENUMERATION
//
//===============================================================================

typedef enum _MMPS_DISPLAY_PRM_SCD_PIP_TYPE {
    MMPS_DISPLAY_PRM_FULL_SCD_PIP = 0x00,
    MMPS_DISPLAY_PRM_PIP_SCD_FULL,
    MMPS_DISPLAY_PRM_FULL_SCD_NONE,
    MMPS_DISPLAY_PRM_NONE_SCD_FULL,
    MMPS_DISPLAY_PRM_HALF_SCD_HALF,
    MMPS_DISPLAY_PRM_SCD_PIP_TYPE_MAX_NUM
} MMPS_DISPLAY_PRM_SCD_PIP_TYPE;

typedef enum _MMPS_DISPLAY_PRM_USBH_PIP_TYPE {
    MMPS_DISPLAY_PRM_FULL_USBH_PIP = 0x00,
    MMPS_DISPLAY_PRM_PIP_USBH_FULL,
    MMPS_DISPLAY_PRM_FULL_USBH_NONE,
    MMPS_DISPLAY_PRM_NONE_USBH_FULL,
    MMPS_DISPLAY_PRM_USBH_PIP_TYPE_MAX_NUM
} MMPS_DISPLAY_PRM_USBH_PIP_TYPE;

typedef enum _MMPS_DISPLAY_PREVIEW_TYPE {
    MMPS_DISPLAY_PREVIEW_FULL_SCREEN = 0x00,
    MMPS_DISPLAY_PREVIEW_HALF_SCREEN,
    MMPS_DISPLAY_PREVIEW_PIP_WIN,
    MMPS_DISPLAY_PREVIEW_TYPE_MAX_NUM
} MMPS_DISPLAY_PREVIEW_TYPE;

typedef enum _MMPS_PREVIEW_UI_MODE {
    MMPS_PREVIEW_UI_MODE_VR = 0,
    MMPS_PREVIEW_UI_MODE_DSC,
    MMPS_PREVIEW_UI_MODE_NUM
} MMPS_PREVIEW_UI_MODE;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

// Output Function
MMPS_DISPLAY_CONFIG* MMPS_Display_GetConfig(void);
MMP_ERR MMPS_Display_SetOutputPanel(MMP_DISPLAY_CONTROLLER controller, MMP_DISPLAY_OUTPUT_SEL dispOutSel);
MMP_ERR MMPS_Display_SetOutputPanelMediaError(MMP_DISPLAY_CONTROLLER controller, MMP_DISPLAY_OUTPUT_SEL dispOutSel);
MMP_ERR MMPS_Display_GetOutputPanel(MMP_DISPLAY_CONTROLLER controller, MMP_DISPLAY_OUTPUT_SEL *pDispOutSel);

// Window function
MMP_ERR MMPS_Display_GetWinAttributes(MMP_DISPLAY_WIN_ID    winID,
                                      MMP_DISPLAY_WIN_ATTR  *pWinAttr);
MMP_ERR MMPS_Display_SetWinSemiTransparent(MMP_DISPLAY_WIN_ID       winID,
                                           MMP_BOOL                 bSemiTpActive,
                                           MMP_DISPLAY_SEMITP_FUNC  semifunc,
                                           MMP_USHORT               usSemiWeight);
MMP_ERR MMPS_Display_GetWinSemiTransparent(MMP_DISPLAY_WIN_ID winID, MMP_USHORT* usSemiWeight);
MMP_ERR MMPS_Display_SetWinActive(MMP_DISPLAY_WIN_ID winID, MMP_BOOL bActive);
MMP_ERR MMPS_Display_SetWinDuplicate(MMP_DISPLAY_WIN_ID     winID,
                                     MMP_DISPLAY_DUPLICATE  h_ratio,
                                     MMP_DISPLAY_DUPLICATE  v_ratio);
MMP_ULONG MMPS_Display_SetWinTransparent(MMP_DISPLAY_WIN_ID winID,
                                         MMP_BOOL           bTranspEnable,
                                         MMP_ULONG          ulTranspColor);
MMP_ERR MMPS_Display_SetAlphaBlending(  MMP_DISPLAY_WIN_ID          winID,
                                                MMP_DISPLAY_WIN_ALPHA_ATTR*     pAlphaAttr);
MMP_ERR MMPS_Display_SetAlphaWeight(MMP_UBYTE ubAlphaWeight);
MMP_ERR MMPS_Display_SetWindowAttrToDisp(MMP_DISPLAY_WIN_ID     winID,
                                         MMP_DISPLAY_WIN_ATTR   winAttr,
                                         MMP_DISPLAY_DISP_ATTR  dispAttr);
MMP_ERR MMPS_Display_LoadWinPalette(MMP_DISPLAY_WIN_ID winID, MMP_UBYTE *ubPalette, MMP_USHORT usPaletteSize);
MMP_ERR MMPS_Display_UpdateWinAddr(MMP_DISPLAY_WIN_ID   winID,
                                   MMP_ULONG            ulBaseAddr,
                                   MMP_ULONG            ulBaseUAddr,
                                   MMP_ULONG            ulBaseVAddr);
MMP_ERR MMPS_Display_SetWinScaleAndOffset(MMP_DISPLAY_WIN_ID    winID,
                                          MMP_UBYTE             sFitMode,
                                          MMP_ULONG             ulInputW,
                                          MMP_ULONG             ulInputH,
                                          MMP_ULONG             ulOutputW,
                                          MMP_ULONG             ulOutputH,
                                          MMP_USHORT            usWinOffsetX,
                                          MMP_USHORT            usWinOffsetY);
MMP_ERR MMPS_Display_AdjustWinColorMatrix(MMP_DISPLAY_WIN_ID        winID,
                                          MMP_DISPLAY_WIN_COLRMTX   *DspyColrMtx,
                                          MMP_BOOL                  bApplyColMtx);
MMP_ERR MMPS_Display_SetYuvAttribute(MMP_BYTE ubU2U,        // default 32
                                     MMP_BYTE ubV2U,        // default 0
                                     MMP_BYTE ubU2V,        // default 0
                                     MMP_BYTE ubV2V,        // default 32
                                     MMP_BYTE ubYGain,      // default 16  range 0~31
                                     MMP_BYTE ubYoffset);   // default 0

// Ratio Function
MMP_ERR MMPS_Display_GetPixelXYRatio(MMP_DISPLAY_OUTPUT_SEL PanelType,
                                     MMP_ULONG      *ulXRatio,  MMP_ULONG *ulYRatio,
                                     MMP_ULONG      *ulWidth,   MMP_ULONG *ulHeight,
                                     MMP_ULONG64    *ulPixelWidth,
                                     MMP_BOOL       *bRotateVerticalLCD);
MMP_ERR MMPS_Display_CheckPixelRatio(MMP_DISPLAY_CONTROLLER controller, MMP_BOOL *bSquarePixel, MMP_ULONG *ulPixelWidth);

MMP_ERR MMPS_Display_AdjustScaleInSize( MMP_DISPLAY_CONTROLLER      controller,
                                        MMP_ULONG                   InputWidth,
                                        MMP_ULONG                   InputHeight,
                                        MMP_ULONG                   RequiredWidth,
                                        MMP_ULONG                   RequiredHeight,
                                        MMP_ULONG                   *SuggestWidth,
                                        MMP_ULONG                   *SuggestHeight);

MMP_ERR MMPS_Display_PureAdjustScaleInSize( MMP_BOOL                bScaleUpAvail,
                                            MMP_ULONG               InputWidth,
                                            MMP_ULONG               InputHeight,
                                            MMP_ULONG               RequiredWidth,
                                            MMP_ULONG               RequiredHeight,
                                            MMP_ULONG               *SuggestWidth,
                                            MMP_ULONG               *SuggestHeight);

// CCIR Function
MMP_ERR MMPS_CCIR_SetDisplayBuf(MMP_ULONG ulBaseAddr);
MMP_ERR MMPS_CCIR_SetDisplayRefresh(void);
MMP_ERR MMPS_CCIR_DisableDisplay(void);

// Component Function
MMP_ERR MMPS_Display_SetDispCompAttr(   MMP_ULONG ulInX,    MMP_ULONG ulInY,    MMP_ULONG ulInW,    MMP_ULONG ulInH,
                                        MMP_ULONG ulCropX,  MMP_ULONG ulCropY,  MMP_ULONG ulCropW,  MMP_ULONG ulCropH,
                                        MMP_ULONG ulOutX,   MMP_ULONG ulOutY,   MMP_ULONG ulOutW,    MMP_ULONG ulOutH,
                                        MMP_ULONG ulBkColorX, MMP_ULONG ulBkColorY, MMP_ULONG ulBkColorW, MMP_ULONG ulBkColorH,
                                        MMP_BOOL bSclHBypass, MMP_BOOL bSclVBypass);

MMP_ERR MMPS_Display_SetPIPCompAttr(MMP_UBYTE ubPipUseIdx,
                                    MMP_ULONG ulFgX, MMP_ULONG ulFgY, MMP_ULONG ulFgW, MMP_ULONG ulFgH,
                                    MMP_ULONG ulBgX, MMP_ULONG ulBgY, MMP_ULONG ulBgW, MMP_ULONG ulBgH,
                                    MMP_BOOL  bHMirror, MMP_BOOL bVFlip);

MMP_ERR MMPS_Display_SetPrmPreviewPipeAttr(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PREVIEW_TYPE ePrevType);
MMP_ERR MMPS_Display_SetScdAnaDecPreviewPipeAttr(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PREVIEW_TYPE ePrevType);
MMP_ERR MMPS_Display_SetScdBayerPreviewPipeAttr(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PREVIEW_TYPE ePrevType);
MMP_ERR MMPS_Display_SetUsbhPreviewPipeAttr(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PREVIEW_TYPE ePrevType);

void    MMPS_Display_SetScdAnaDecPreviewPIPType(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PRM_SCD_PIP_TYPE ePipType);
void    MMPS_Display_SetScdBayerPreviewPIPType(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PRM_SCD_PIP_TYPE ePipType);
void    MMPS_Display_SetUsbCamPreviewPIPType(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PRM_USBH_PIP_TYPE ePipType);

MMP_ERR MMPS_Display_EnableScdAnaDecSnrPreview(MMP_UBYTE ubUiMode, MMP_BOOL bEnablePreview);
MMP_ERR MMPS_Display_EnableScdAnaDecSnrPreviewWindow(MMP_UBYTE ubUiMode, MMP_BOOL bEnablePreview);

#endif //_MMPS_DISPLAY_H_
