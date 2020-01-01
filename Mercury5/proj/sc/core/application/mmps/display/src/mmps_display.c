//==============================================================================
//
//  File        : mmps_display.c
//  Description : Ritian Display Control host function, including LCD/TV/Win
//  Author      : Alan Wu
//  Revision    : 1.0
//
//==============================================================================

/**
*  @file mmps_display.c
*  @brief The Display control functions
*  @author Alan Wu
*  @version 1.0
*/

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmp_vidplay_inc.h"
#include "mmps_display.h"
#include "mmps_3gprecd.h"
#include "mmpd_ccir.h"
#include "mmpd_system.h"
#include "mmpf_scaler.h"
#include "mmpf_sensor.h"

#include "mmp_component_ctl.h"
#include "component_cfg.h"
#include "component_raws.h"
#include "component_dip.h"
#include "component_pip.h"
#include "component_display.h"
#include "cust_component_cfg.h"
#include "snr_cfg.h"


/** @addtogroup MMPS_DISPLAY
@{
*/

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define PIP_WIN_1ST_SCALE_OUT_W   (320*2)
#define PIP_WIN_1ST_SCALE_OUT_H   256

#define TEST_2IN1_SAME_SOURCE (RAWS_COMP_IDX & RAWS_COMP_IDX2)

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

/**@brief The system display mode

Use @ref MMPS_Display_SetOutputPanel to assign the field value of it.
*/
static MMPS_DISPLAY_CONFIG      m_displayConfig;

/**@brief The display type in each controller

Use @ref MMPS_Display_SetOutputPanel to set it.
And use @ref MMPS_Display_GetOutputPanel to get the current mode.
*/
static MMP_DISPLAY_OUTPUT_SEL   m_displayCurOutput[MMP_DISPLAY_CTL_MAX] = {MMP_DISPLAY_SEL_NONE, MMP_DISPLAY_SEL_NONE};
MMP_DISPLAY_RGB_IF              m_RGBLCDInterface   =   MMP_DISPLAY_RGB_IF1;
MMP_DISPLAY_RGB_IF              m_HDMIInterface     =   MMP_DISPLAY_RGB_IF1;


//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_GetConfig
//  Description :
//------------------------------------------------------------------------------
/** @brief The function gets the Display configuration for the host application

The function gets the current Display configuration for reference by the host application.

@return It return the pointer of the Display configuration data structure.
*/
MMPS_DISPLAY_CONFIG* MMPS_Display_GetConfig(void)
{
    return &m_displayConfig;
}

#if 0
void ____Output_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetOutputPanel
//  Description :
//------------------------------------------------------------------------------
/** @brief The function designates the output display device

The function designates the output device
@param[in] controller  the display controller
@param[in] dispOutSel the display type
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Display_SetOutputPanel(MMP_DISPLAY_CONTROLLER controller, MMP_DISPLAY_OUTPUT_SEL dispOutSel)
{
#if 1
    MMP_DISPLAY_WIN_ID      winID;
    MMP_DISPLAY_CONTROLLER  winBindController;
    MMP_LCD_ATTR            lcdAttr;

    if (m_displayCurOutput[controller] == dispOutSel) {
        // To reset the LCD width/height and some important things. In bypass mode, customer maybe
        // use the partial LCD refresh and change the LCD width/height by LCD command. So when AIT
        // is active, we have to change the LCD width/height back.
        switch (dispOutSel) {
        case MMP_DISPLAY_SEL_MAIN_LCD:
            if (m_displayConfig.mainlcd.reinitialfx)
                m_displayConfig.mainlcd.reinitialfx(MMP_FALSE);
            break;
        case MMP_DISPLAY_SEL_SUB_LCD:
            if (m_displayConfig.sublcd.reinitialfx)
                m_displayConfig.sublcd.reinitialfx(MMP_FALSE);
            break;
        default:
            break;
        }

        return MMP_ERR_NONE;
    }

    /* Inactive all windows */
    for (winID = MMP_DISPLAY_WIN_MAIN; winID < MMP_DISPLAY_WIN_MAX; winID++) {

        MMPF_Display_GetWinBindController(winID, &winBindController);

        if (winBindController == controller)
            MMPF_Display_SetWinActive(winID, MMP_FALSE);
    }

    /* Disable the orignal output and config new output */
    switch (dispOutSel) {
    case MMP_DISPLAY_SEL_NONE:
    case MMP_DISPLAY_SEL_CCIR:
        if ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV) ||
            (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_PAL_TV)) {

            MMPD_TV_EnableDisplay(MMP_FALSE);

            if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV)
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_NTSC);
            else
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_PAL);
        }

        #if (HDMI_OUTPUT_EN)
        if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_HDMI) {
            MMPD_HDMI_DisableHDMI(m_HDMIInterface);
        }
        #endif

        if ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_MAIN_LCD && m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) ||
            (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_SUB_LCD && m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_RGB_LCD)) {
            MMPF_Display_DisableRGBOutput(controller, m_RGBLCDInterface);
        }

        if (dispOutSel == MMP_DISPLAY_SEL_NONE)
            MMPF_Display_SetNoneOutput(controller);
        #if 0//defined(ALL_FW)
        else
            MMPF_Display_SetCCIROutput(controller, m_displayConfig.ccir);
        #endif
        break;

    case MMP_DISPLAY_SEL_MAIN_LCD:

        if ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV) ||
            (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_PAL_TV)) {

            MMPD_TV_EnableDisplay(MMP_FALSE);

            if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV)
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_NTSC);
            else
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_PAL);
        }

        #if (HDMI_OUTPUT_EN)
        if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_HDMI) {
            MMPD_HDMI_DisableHDMI(m_HDMIInterface);
        }
        #endif

        if ((m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_P_LCD) ||
            (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) ||
            (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_P_LCD_FLM)) {

            if (m_displayConfig.mainlcd.initialfx) {
                m_displayConfig.mainlcd.initialfx(MMP_TRUE);
            }

            lcdAttr.usWidth     = m_displayConfig.mainlcd.usWidth;
            lcdAttr.usHeight    = m_displayConfig.mainlcd.usHeight;
            lcdAttr.colordepth  = m_displayConfig.mainlcd.colordepth;
            lcdAttr.ulBgColor   = m_displayConfig.mainlcd.ulBgColor;
            lcdAttr.bFLMType    = m_displayConfig.mainlcd.bFLMType;

            if ((m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_P_LCD) ||
                (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_P_LCD_FLM)) {

                MMPF_Display_SetPLCDOutput(controller, m_displayConfig.mainlcd.cssel, &lcdAttr);
            }
            else if (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) {

                 MMPF_Display_SetRGBLCDOutput(controller, &lcdAttr, m_RGBLCDInterface);            }
        }
        else if (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_NONE) {

            if (m_displayConfig.mainlcd.initialfx) {
                m_displayConfig.mainlcd.initialfx(MMP_FALSE);
            }
            MMPF_Display_SetNoneOutput(controller);
        }
        break;

    case MMP_DISPLAY_SEL_SUB_LCD:

        if  ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV) ||
             (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_PAL_TV)) {

            MMPD_TV_EnableDisplay(MMP_FALSE);

            if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV)
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_NTSC);
            else
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_PAL);
        }

        #if (HDMI_OUTPUT_EN)
        if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_HDMI) {
            MMPD_HDMI_DisableHDMI(m_HDMIInterface);
        }
        #endif

        if ((m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_P_LCD) ||
            (m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_RGB_LCD) ||
            (m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_P_LCD_FLM)) {

            if (m_displayConfig.sublcd.initialfx) {
                m_displayConfig.sublcd.initialfx(MMP_TRUE);
            }

            lcdAttr.usWidth     = m_displayConfig.sublcd.usWidth;
            lcdAttr.usHeight    = m_displayConfig.sublcd.usHeight;
            lcdAttr.colordepth  = m_displayConfig.sublcd.colordepth;
            lcdAttr.ulBgColor   = m_displayConfig.sublcd.ulBgColor;
            lcdAttr.bFLMType    = m_displayConfig.sublcd.bFLMType;

            if ((m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_P_LCD) ||
                (m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_P_LCD_FLM)) {

                MMPF_Display_SetPLCDOutput(controller, m_displayConfig.sublcd.cssel, &lcdAttr);
            }
            else if (m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_RGB_LCD) {

                MMPF_Display_SetRGBLCDOutput(controller, &lcdAttr, m_RGBLCDInterface);
            }
        }
        else if (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_NONE) {

            MMPF_Display_SetNoneOutput(controller);
        }
        break;

    case MMP_DISPLAY_SEL_NTSC_TV:
    case MMP_DISPLAY_SEL_PAL_TV:

        #if (HDMI_OUTPUT_EN)
        if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_HDMI) {
            MMPD_HDMI_DisableHDMI(m_HDMIInterface);
        }
        #endif

        if ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_MAIN_LCD && m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) ||
            (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_SUB_LCD && m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_RGB_LCD)) {
            MMPF_Display_DisableRGBOutput(controller, m_RGBLCDInterface);
        }
#if 0
        if (dispOutSel == MMP_DISPLAY_SEL_NTSC_TV)
            MMPF_Display_SetTVOutput(controller, &m_displayConfig.ntsctv, m_RGBLCDInterface);
        else
            MMPF_Display_SetTVOutput(controller, &m_displayConfig.paltv, m_RGBLCDInterface);
#endif
        break;

    case MMP_DISPLAY_SEL_HDMI:

        if ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV) ||
            (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_PAL_TV)) {

            MMPD_TV_EnableDisplay(MMP_FALSE);

            if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV)
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_NTSC);
            else
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_PAL);
        }

        if ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_MAIN_LCD && m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) ||
            (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_SUB_LCD && m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_RGB_LCD)) {
            MMPF_Display_DisableRGBOutput(controller, m_RGBLCDInterface);
        }
        if((m_displayCurOutput[MMP_DISPLAY_PRM_CTL] == MMP_DISPLAY_SEL_MAIN_LCD && m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) ||
           (m_displayCurOutput[MMP_DISPLAY_SCD_CTL] == MMP_DISPLAY_SEL_MAIN_LCD && m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD)) {
            if(m_RGBLCDInterface == m_HDMIInterface) {
                MMPF_Display_DisableRGBOutput(controller, m_HDMIInterface);
            }
        }
#if 0
        MMPF_Display_SetHDMIOutput(controller, &m_displayConfig.hdmi, m_HDMIInterface);
#endif
        break;
    default:
        break;
    }

    m_displayCurOutput[controller] = dispOutSel;
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetOutputPanelMediaError
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetOutputPanelMediaError(MMP_DISPLAY_CONTROLLER controller, MMP_DISPLAY_OUTPUT_SEL dispOutSel)
{
    MMP_LCD_ATTR    lcdAttr;

    if (m_displayCurOutput[controller] == dispOutSel) {
        // To reset the LCD width/height and some important things. In bypass mode, customer maybe
        // use the partial LCD refresh and change the LCD width/height by LCD command. So when AIT
        // is active, we have to change the LCD width/height back.
        switch (dispOutSel) {
        case MMP_DISPLAY_SEL_MAIN_LCD:
            if (m_displayConfig.mainlcd.reinitialfx)
                m_displayConfig.mainlcd.reinitialfx(MMP_FALSE);
            break;
        case MMP_DISPLAY_SEL_SUB_LCD:
            if (m_displayConfig.sublcd.reinitialfx)
                m_displayConfig.sublcd.reinitialfx(MMP_FALSE);
            break;
        default:
            break;
        }

        return  MMP_ERR_NONE;
    }

    /* Disable the orignal output and config new output */
    switch (dispOutSel) {
    case MMP_DISPLAY_SEL_NONE:
    case MMP_DISPLAY_SEL_CCIR:

        if ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV) ||
            (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_PAL_TV)) {

            MMPD_TV_EnableDisplay(MMP_FALSE);

            if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV)
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_NTSC);
            else
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_PAL);
        }

        #if (HDMI_OUTPUT_EN)
        if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_HDMI) {
            MMPD_HDMI_DisableHDMI(m_HDMIInterface);
        }
        #endif

        if ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_MAIN_LCD && m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) ||
            (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_SUB_LCD && m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_RGB_LCD)) {

            MMPF_Display_DisableRGBOutput(controller, MMP_DISPLAY_RGB_IF1);
        }

        if (dispOutSel == MMP_DISPLAY_SEL_NONE)
            MMPF_Display_SetNoneOutput(controller);
        #if defined(ALL_FW)
        else
            MMPF_Display_SetCCIROutput(controller, m_displayConfig.ccir);
        #endif
        break;

    case MMP_DISPLAY_SEL_MAIN_LCD:

        if ((m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_P_LCD) ||
            (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) ||
            (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_P_LCD_FLM)) {

            if (m_displayConfig.mainlcd.initialfx) {
                m_displayConfig.mainlcd.initialfx(MMP_TRUE);
            }

            lcdAttr.usWidth     = m_displayConfig.mainlcd.usWidth;
            lcdAttr.usHeight    = m_displayConfig.mainlcd.usHeight;
            lcdAttr.colordepth  = m_displayConfig.mainlcd.colordepth;
            lcdAttr.ulBgColor   = m_displayConfig.mainlcd.ulBgColor;
            lcdAttr.bFLMType    = m_displayConfig.mainlcd.bFLMType;

            if ((m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_P_LCD) ||
                (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_P_LCD_FLM)) {

                MMPF_Display_SetPLCDOutput(controller, m_displayConfig.mainlcd.cssel, &lcdAttr);
            }
            else if (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) {

                MMPF_Display_SetRGBLCDOutput(controller, &lcdAttr, MMP_DISPLAY_RGB_IF1);
            }
        }
        else if (m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_NONE) {

            if (m_displayConfig.mainlcd.initialfx) {
                m_displayConfig.mainlcd.initialfx(MMP_FALSE);
            }
            MMPF_Display_SetNoneOutput(controller);
        }
        break;

    case MMP_DISPLAY_SEL_HDMI:

        if  ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV) ||
             (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_PAL_TV)) {

            MMPD_TV_EnableDisplay(MMP_FALSE);

            if (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_NTSC_TV)
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_NTSC);
            else
                MMPD_TV_Initialize(MMP_FALSE, MMP_TV_TYPE_PAL);
        }

        if ((m_displayCurOutput[controller] == MMP_DISPLAY_SEL_MAIN_LCD && m_displayConfig.mainlcd.lcdtype == MMP_DISPLAY_RGB_LCD) ||
            (m_displayCurOutput[controller] == MMP_DISPLAY_SEL_SUB_LCD && m_displayConfig.sublcd.lcdtype == MMP_DISPLAY_RGB_LCD)) {

            MMPF_Display_DisableRGBOutput(controller, MMP_DISPLAY_RGB_IF1);
        }

        MMPF_Display_SetHDMIOutput(controller, &m_displayConfig.hdmi, MMP_DISPLAY_RGB_IF1);
        break;
    default:
        break;
    }

    m_displayCurOutput[controller] = dispOutSel;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_GetOutputPanel
//  Description :
//------------------------------------------------------------------------------
/** @brief The function retrives the current output display device

The function retrives the current output display device
@param[in] controller   The display controller
@param[out] dispOutSel  The display type
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Display_GetOutputPanel(MMP_DISPLAY_CONTROLLER controller, MMP_DISPLAY_OUTPUT_SEL *pDispOutSel)
{
    *pDispOutSel = m_displayCurOutput[controller];

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetDisplayRefresh
//  Description :
//------------------------------------------------------------------------------
/** @brief Refresh display data from the frame buffer to LCD

@return It reports the total effect number
*/
MMP_ERR MMPS_Display_SetDisplayRefresh(MMP_DISPLAY_CONTROLLER controller)
{
    MMP_M_STATE     state;
    MMP_BOOL        bAvail = MMP_FALSE;
    MMP_BOOL        bInStreaming = MMP_FALSE;

    #if 0 // TBD defined(WIFI_PORT) && (WIFI_PORT == 1)
    if (ns_get_streaming_status() & NETAPP_STREAM_PLAY) {
        bInStreaming = MMP_TRUE;
    }
    #endif

    MMPS_VIDPLAY_GetState(&state);

    if (state == MMP_M_STATE_EXECUTING) {
        MMPS_VIDPLAY_GetVideoAvailable(&bAvail);
        if (bAvail) {
            return MMP_ERR_NONE;
        }
    }

    MMPS_DSC_GetPreviewPipeStatus(0/*PRM_SENSOR*/, &bAvail);
    if (bAvail && (MMP_FALSE == bInStreaming)) {
        return MMP_ERR_NONE;
    }

    MMPS_3GPRECD_GetPreviewPipeStatus(0/*PRM_SENSOR*/, &bAvail);
    if (bAvail && (MMP_FALSE == bInStreaming)) {
        return MMP_ERR_NONE;
    }

    DrvLCDRefresh();

    return MMP_ERR_NONE;
}

#if 0
void ____Window_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_GetWinAttributes
//  Description :
//------------------------------------------------------------------------------
/** @brief The function gets current window attributes

The function gets current window attributes from the specified window. The function can be used
for dual panels.

@param[in] winID the window ID
@param[out] winattribute the attribute buffer
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Display_GetWinAttributes(MMP_DISPLAY_WIN_ID    winID,
                                      MMP_DISPLAY_WIN_ATTR  *pWinAttr)
{
    return MMPF_Display_GetWinAttributes(winID, pWinAttr);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetWinSemiTransparent
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetWinSemiTransparent(MMP_DISPLAY_WIN_ID       winID,
                                           MMP_BOOL                 bSemiTpActive,
                                           MMP_DISPLAY_SEMITP_FUNC  semifunc,
                                           MMP_USHORT               usSemiWeight)
{
    if (usSemiWeight >= 256) {
        return MMP_DISPLAY_ERR_PARAMETER;
    }

    return MMPF_Display_SetWinSemiTransparent(winID, bSemiTpActive, semifunc, usSemiWeight);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_GetWinSemiTransparent
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_GetWinSemiTransparent(MMP_DISPLAY_WIN_ID winID, MMP_USHORT* usSemiWeight)
{
    return MMPF_Display_GetWinSemiTransparent(winID, usSemiWeight);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetWinActive
//  Description :
//------------------------------------------------------------------------------
/** @brief The function activates or deactivates the window

The function activates or deactivates the window from the input parameter, winID. The function can be
used for dual panels.

@param[in] winID the window ID
@param[in] bActive activate or de-activate the window
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Display_SetWinActive(MMP_DISPLAY_WIN_ID winID, MMP_BOOL bActive)
{
    return MMPF_Display_SetWinActive(winID, bActive);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetWinDuplicate
//  Description :
//------------------------------------------------------------------------------
/** @brief The function do duplication of a window

The function do duplication of a window and it only support RGB format, before do
this function, the MMPF_Display_SetWinAttributes and MMPF_Display_SetWinToDisplay
must be done. the flow is MMPF_Display_SetWinAttributes->MMPF_Display_SetWinToDisplay
->MMPS_Display_SetWinDuplicate

@param[in] winID    The window ID
@param[in] h_ratio  Scaling factor for width.
@param[in] v_ratio  Scaling factor for height.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Display_SetWinDuplicate(MMP_DISPLAY_WIN_ID     winID,
                                     MMP_DISPLAY_DUPLICATE  h_ratio,
                                     MMP_DISPLAY_DUPLICATE  v_ratio)
{
    return MMPF_Display_SetWinDuplicate(winID, h_ratio, v_ratio);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetWinTransparent
//  Description :
//------------------------------------------------------------------------------
MMP_ULONG MMPS_Display_SetWinTransparent(MMP_DISPLAY_WIN_ID winID,
                                         MMP_BOOL           bTranspEnable,
                                         MMP_ULONG          ulTranspColor)
{
    return MMPF_Display_SetWinTransparent(winID, bTranspEnable, ulTranspColor);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetAlphaBlending
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetAlphaBlending(  MMP_DISPLAY_WIN_ID          winID,
                                                MMP_DISPLAY_WIN_ALPHA_ATTR*     pAlphaAttr)
{
    return MMPF_Display_SetAlphaBlending(winID, pAlphaAttr);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetAlphaWeight
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetAlphaWeight(MMP_UBYTE ubAlphaWeight)
{
    return MMPF_Display_SetAlphaWeight(ubAlphaWeight);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetWindowAttrToDisp
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetWindowAttrToDisp(MMP_DISPLAY_WIN_ID     winID,
                                         MMP_DISPLAY_WIN_ATTR   winAttr,
                                         MMP_DISPLAY_DISP_ATTR  dispAttr)
{
    MMPF_Display_SetWinAttributes(winID, &winAttr);
    MMPF_Display_SetWinToDisplay(winID, &dispAttr);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_LoadWinPalette
//  Description :
//------------------------------------------------------------------------------
/** @brief The function activates transparent operation by its transparent color with weight

The function activates transparent operation by its transparent color with weight from the input parameter

@param[in] winID the window ID
@param[in] ubPalette palette data
@param[in] usPaletteSize define the number of palette. Unit: ARGB
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Display_LoadWinPalette(MMP_DISPLAY_WIN_ID winID, MMP_UBYTE *ubPalette, MMP_USHORT usPaletteSize)
{
    return MMPF_Display_LoadWinPalette(winID, ubPalette, usPaletteSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_UpdateWinAddr
//  Description : Set window address
//------------------------------------------------------------------------------
/**
@brief     Update the base address of a window
@param[in]  winID       The window that address will be update
@param[in]  ulBaseAddr  New address (address of Y if YUV420)
@param[in]  ulBaseUAddr New address of U if YUV420
@param[in]  ulBaseVAddr new address of V if YUV420
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Display_UpdateWinAddr(MMP_DISPLAY_WIN_ID   winID,
                                   MMP_ULONG            ulBaseAddr,
                                   MMP_ULONG            ulBaseUAddr,
                                   MMP_ULONG            ulBaseVAddr)
{
    return MMPF_Display_UpdateWinAddr(winID, ulBaseAddr, ulBaseUAddr, ulBaseVAddr);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetYuvAttribute
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetYuvAttribute(MMP_BYTE ubU2U,
                                     MMP_BYTE ubV2U,
                                     MMP_BYTE ubU2V,
                                     MMP_BYTE ubV2V,
                                     MMP_BYTE ubYGain,
                                     MMP_BYTE ubYoffset)
{
    return MMPF_Display_SetYuvAttribute(ubU2U, ubV2U, ubU2V, ubV2V, ubYGain, ubYoffset);
}

#if 0
void ____Preview_Function____(){ruturn;} //dummy
#endif

MMP_ERR MMPS_Display_SetPrmPreviewPipeAttr_Raw2I2O(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PREVIEW_TYPE ePrevType)
{
    MMP_UBYTE           ubDipBufCnt = DIP_COMP_PREVW_BUF_COUNT;
    MMP_ULONG           ulAlignPrevW = 0, ulAlignPrevH = 0;
    MMP_ULONG           ulDispWidth = 0, ulDispHeight = 0;
    MMP_ULONG           ulDispStartX = 0, ulDispStartY = 0;
    MMP_ULONG           ulAlignDispW = 0, ulAlignDispH = 0;
    MMP_UBYTE           ubDipSUseIdx, ubDipRUseIdx;
    MMP_UBYTE           ubCamSel = PRM_SENSOR;
    MMP_UBYTE           ubDipMirrorType = DIP_COMP_MIRROR_DIS;
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    DIP_COMP_COLOR_FMT  ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
    MMPF_SENSOR_YUV_ORDER   order = MMPF_SENSOR_YUV_ORDER_YC;


    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        ubDipSUseIdx = DIP_S_COMP_VR_FCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_VR_FCAM_PREVIEW;
    }
    else {
        ubDipSUseIdx = DIP_S_COMP_DSC_FCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_DSC_FCAM_PREVIEW;
    }

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        MMPS_3GPRECD_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);
        MMPS_3GPRECD_GetDisplayRes(ubCamSel, &ulDispWidth, &ulDispHeight);
        MMPS_3GPRECD_GetDisplayPosition(ubCamSel, &ulDispStartX, &ulDispStartY);
    }
    else {
        MMPS_DSC_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);
        MMPS_DSC_GetDisplayRes(ubCamSel, &ulDispWidth, &ulDispHeight);
        MMPS_DSC_GetDisplayPosition(ubCamSel, &ulDispStartX, &ulDispStartY);
    }

    //get YUV order from sensor, and select input color format
    eRetErr = MMPF_Sensor_GetSensorYuvOrder(SCD_SENSOR, &order);
    if (eRetErr == MMP_ERR_NONE){
        //mapping
        switch(order)
        {
            case MMPF_SENSOR_YUV_ORDER_YC:
                ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_UYVY;
            break;
            case MMPF_SENSOR_YUV_ORDER_CY:
            default:
                ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
            break;
        }
    }

    //ulAlignPrevW = 1280;//Fixed width for test
    //ulAlignPrevH = 720;

    ulAlignDispW = ALIGN_X(ulDispWidth, DIP_R_COMP_ALIGN_BASE);
    ulAlignDispH = ALIGN_X(ulDispHeight, DIP_R_COMP_ALIGN_BASE);

    //if (ePrevType == MMPS_DISPLAY_PREVIEW_HALF_SCREEN)YUV422_YUYV
    {
        if (gbLCDRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        #if defined(PRM_CAM_FULL_VIEW_ONPANEL)
                                        0, 0, ulAlignPrevW, ulAlignPrevH, //full view
                                        #else
                                        0, 0, ulAlignDispH, ulAlignDispW, //part of
                                        #endif
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        ubDIPSCLInColor,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);

            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                        ubDipRUseIdx,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }
        else {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetPrmPreviewPipeAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetPrmPreviewPipeAttr(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PREVIEW_TYPE ePrevType)
{
    MMP_UBYTE           ubDipBufCnt = DIP_COMP_PREVW_BUF_COUNT;
    MMP_ULONG           ulAlignPrevW = 0, ulAlignPrevH = 0;
    MMP_ULONG           ulDispWidth = 0, ulDispHeight = 0;
    MMP_ULONG           ulDispStartX = 0, ulDispStartY = 0;
    MMP_ULONG           ulAlignDispW = 0, ulAlignDispH = 0;
    MMP_UBYTE           ubDipSUseIdx, ubDipRUseIdx;
    MMP_UBYTE           ubCamSel = PRM_SENSOR;
    MMP_UBYTE           ubDipMirrorType = DIP_COMP_MIRROR_DIS;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        ubDipSUseIdx = DIP_S_COMP_VR_FCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_VR_FCAM_PREVIEW;
    }
    else {
        ubDipSUseIdx = DIP_S_COMP_DSC_FCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_DSC_FCAM_PREVIEW;
    }

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        MMPS_3GPRECD_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);
        MMPS_3GPRECD_GetDisplayRes(ubCamSel, &ulDispWidth, &ulDispHeight);
        MMPS_3GPRECD_GetDisplayPosition(ubCamSel, &ulDispStartX, &ulDispStartY);
    }
    else {
        MMPS_DSC_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);
        MMPS_DSC_GetDisplayRes(ubCamSel, &ulDispWidth, &ulDispHeight);
        MMPS_DSC_GetDisplayPosition(ubCamSel, &ulDispStartX, &ulDispStartY);
    }

    ulAlignDispW = ALIGN_X(ulDispWidth, DIP_R_COMP_ALIGN_BASE);
    ulAlignDispH = ALIGN_X(ulDispHeight, DIP_R_COMP_ALIGN_BASE);

    if (ePrevType == MMPS_DISPLAY_PREVIEW_FULL_SCREEN) {
        if (gbLCDRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                        ubDipRUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        (ulAlignPrevW - ulAlignDispH)>>1, (ulAlignPrevH - ulAlignDispW)>>1, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);

            MMPS_Display_SetDispCompAttr(   0, 0, ulAlignDispW, ulAlignDispH,
                                            0, 0, ulAlignDispW, ulAlignDispH,
                                            0, 0, ulDispWidth, ulDispHeight,
                                            0, 0, ulDispWidth, ulDispHeight,
                                            MMP_FALSE, MMP_FALSE);
        }
        else {
            MMPS_Display_SetDispCompAttr(   0, 0, ulAlignPrevW, ulAlignPrevH,
                                            0, 0, ulAlignPrevW, ulAlignPrevH,
                                            0, 0, ulDispWidth, ulDispHeight,
                                            0, 0, ulDispWidth, ulDispHeight,
                                            MMP_FALSE, MMP_FALSE);
        }
    }
    else if (ePrevType == MMPS_DISPLAY_PREVIEW_HALF_SCREEN) {
        if (gbLCDRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);

            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                        ubDipRUseIdx,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }
        else {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }

        if (!gbLCDRotate) {
            MMPS_Display_SetPIPCompAttr(    PIP_COMP_PIP_PREVIEW,
                                            0, 0, ulAlignDispW, ulAlignDispH,
                                            RTNA_LCD_GetAttr()->usPanelW >> 1, 0, RTNA_LCD_GetAttr()->usPanelW >> 1, RTNA_LCD_GetAttr()->usPanelH,
                                            MMP_FALSE, MMP_FALSE);
        }
        else {
            MMPS_Display_SetPIPCompAttr(    PIP_COMP_PIP_PREVIEW,
                                            0, 0, ulAlignDispW, ulAlignDispH,
											0, RTNA_LCD_GetAttr()->usPanelH >> 1, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH >> 1,
                                            MMP_FALSE, MMP_FALSE);
        }
    }
    else if (ePrevType == MMPS_DISPLAY_PREVIEW_PIP_WIN) {
        if (gbLCDRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);

            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                        ubDipRUseIdx,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }
        else {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }

        {
        MMP_ULONG ulPipBgWidth  = (ulAlignDispW > RTNA_LCD_GetAttr()->usPanelW)? RTNA_LCD_GetAttr()->usPanelW : ulAlignDispW;
        MMP_ULONG ulPipBgHeight = (ulAlignDispH > RTNA_LCD_GetAttr()->usPanelH)? RTNA_LCD_GetAttr()->usPanelH : ulAlignDispH;

        MMPS_Display_SetPIPCompAttr(PIP_COMP_PIP_PREVIEW,
                                    0, 0, ulAlignDispW, ulAlignDispH,
                                    ulDispStartX, ulDispStartY, ulPipBgWidth, ulPipBgHeight,
                                    MMP_FALSE, MMP_FALSE);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetScdAnaDecPreviewPipeAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetScdAnaDecPreviewPipeAttr(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PREVIEW_TYPE ePrevType)
{
    MMP_UBYTE           ubCamSel = SCD_SENSOR;
    MMP_UBYTE           ubDipBufCnt = DIP_COMP_PREVW_BUF_COUNT;
    MMP_ULONG           ulDispWidth = 0, ulDispHeight = 0;
    MMP_ULONG           ulDispStartX = 0, ulDispStartY = 0;
    MMP_ULONG           ulAlignDispW = 0, ulAlignDispH = 0;
    MMP_ULONG           ulScaleInW = 0, ulScaleInH = 0;
    MMP_ULONG           ulScaleInAlignedX = 0, ulScaleInAlignedY = 0;
    MMP_ULONG           ulScaleInAlignedW = 0, ulScaleInAlignedH = 0;
    MMP_ULONG           ulCropAlignedW = 0, ulCropAlignedH = 0;
    MMP_UBYTE           ubSigType = RAWS_COMP_SIG_TYPE_INTERLACE;
    MMP_UBYTE           ubDipSUseIdx = 0, ubDipSReUseIdx = 0, ubDipRUseIdx = 0;
    MMP_BOOL            bMirror = MMP_FALSE;
    MMP_UBYTE           ubDipMirrorType = DIP_COMP_MIRROR_DIS;
    MMP_BOOL            ubReScalBypass = MMP_TRUE;
    MMP_SNR_ANADEC_SRC_TYPE eAnaDecSrc = MMP_SNR_ANADEC_SRC_NO_READY;
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_UBYTE           ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_YUYV; //if YUV sensor, the order may be diff
    MMPF_SENSOR_YUV_ORDER order = MMPF_SENSOR_YUV_ORDER_CY;
    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        ubDipSUseIdx = DIP_S_COMP_VR_RCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_VR_RCAM_PREVIEW;
        ubDipSReUseIdx = DIP_S_COMP_VR_RCAM_RESCAL_PREV;
    }
    else {
        ubDipSUseIdx = DIP_S_COMP_DSC_RCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_DSC_RCAM_PREVIEW;
        ubDipSReUseIdx = DIP_S_COMP_DSC_RCAM_RESCAL_PREV;
    }

    if ((CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) ||
        (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR))) {

        MMPS_Sensor_GetAnaDecSrcType(&eAnaDecSrc);

        MMPS_Sensor_GetCurPrevScalInputRes(ubCamSel, &ulScaleInW, &ulScaleInH);

        if (eAnaDecSrc == MMP_SNR_ANADEC_SRC_PAL) {
            ubSigType = RAWS_COMP_SIG_TYPE_INTERLACE;
            ulScaleInAlignedX = 0;
            ulScaleInAlignedY = 2;
            ulScaleInAlignedW = 672;
            ulScaleInAlignedH = (ulScaleInH == 288) ? (ulScaleInH - 32) : ulScaleInH;
            //ulScaleInAlignedH -= 2;
        }
        else if (eAnaDecSrc == MMP_SNR_ANADEC_SRC_NTSC) {
            ubSigType = RAWS_COMP_SIG_TYPE_INTERLACE;
            ulScaleInAlignedX = 0;
            ulScaleInAlignedY = 2;
            ulScaleInAlignedW = 672;
            ulScaleInAlignedH = 240;
            //ulScaleInAlignedH -= 2;
        }
        else if (eAnaDecSrc == MMP_SNR_ANADEC_SRC_FHD ||
                 eAnaDecSrc == MMP_SNR_ANADEC_SRC_HD) {
            ubSigType = RAWS_COMP_SIG_TYPE_PROGRESSIVE;
            ulScaleInAlignedW = ulScaleInW;
            ulScaleInAlignedH = ulScaleInH;
        }
        else {
            MMP_DBG_ERR(1, "SetScdPreviewPipeAttr Wrong Src %d\r\n", eAnaDecSrc);
            return MMP_ERR_NONE;
        }

        ulScaleInAlignedH = FLOOR_X(ulScaleInAlignedH, DIP_R_COMP_ALIGN_BASE);
    }

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        MMPS_3GPRECD_GetDisplayRes(ubCamSel, &ulDispWidth, &ulDispHeight);
        MMPS_3GPRECD_GetDisplayPosition(ubCamSel, &ulDispStartX, &ulDispStartY);
        MMPS_3GPRECD_GetPreviewMirror(ubCamSel, &bMirror);
    }
    else {
        MMPS_DSC_GetDisplayRes(ubCamSel, &ulDispWidth, &ulDispHeight);
        MMPS_DSC_GetDisplayPosition(ubCamSel, &ulDispStartX, &ulDispStartY);
        MMPS_DSC_GetPreviewMirror(ubCamSel, &bMirror);
    }

    ubDipMirrorType = (bMirror) ? (DIP_COMP_MIRROR_EN) : (DIP_COMP_MIRROR_DIS);

    ulAlignDispW = ALIGN_X(ulDispWidth, DIP_R_COMP_ALIGN_BASE);
    ulAlignDispH = ALIGN_X(ulDispHeight, DIP_R_COMP_ALIGN_BASE);

    if (gbLCDRotate) {
        if (ulAlignDispH / ulAlignDispW >= 2) {
            ulCropAlignedW = ulScaleInAlignedW;
            ulCropAlignedH = ulCropAlignedW * ulAlignDispW / ulAlignDispH;
        }
        else {
            ulCropAlignedW = ulScaleInAlignedW;
            ulCropAlignedH = ulScaleInAlignedH;
        }
    }
    else {
        if (ulAlignDispW / ulAlignDispH >= 2) {
            ulCropAlignedW = ulScaleInAlignedW;
            ulCropAlignedH = ulCropAlignedW * ulAlignDispH / ulAlignDispW;
        }
        else {
            ulCropAlignedW = ulScaleInAlignedW;
            ulCropAlignedH = ulScaleInAlignedH;
        }
    }

    if (ulCropAlignedH > ulScaleInAlignedH) {
        ulCropAlignedH = ulScaleInAlignedH;
    }

    //Set DIP ROT Attr
    if (gbLCDRotate) {
        if ((ePrevType == MMPS_DISPLAY_PREVIEW_FULL_SCREEN) || (ePrevType == MMPS_DISPLAY_PREVIEW_HALF_SCREEN)) {
            eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_ROT,
                                                ubDipRUseIdx,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                0, 0, ulAlignDispW, ulAlignDispH,
                                                DIP_COMP_COLOR_FMT_YUV420_UV,
                                                DIP_COMP_COLOR_FMT_YUV420_UV,
                                                DIP_COMP_MIRROR_DIS,
                                                0,
                                                ubDipBufCnt);
        }
        else if (ePrevType == MMPS_DISPLAY_PREVIEW_PIP_WIN) {
            eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_ROT,
                                                ubDipRUseIdx,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                0, 0, ulAlignDispW, ulAlignDispH,
                                                DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                                DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                                DIP_COMP_MIRROR_DIS,
                                                0,
                                                ubDipBufCnt);
        }
        else {
            MMP_DBG_ERR(1, "Strange PIP setting\n");
        }
    }
    //get YUV order from sensor, and select input color format
    eRetErr = MMPF_Sensor_GetSensorYuvOrder(ubCamSel, &order);
    if (eRetErr != MMP_ERR_NONE){
        return eRetErr;
    }
    //mapping
    switch(order)
    {
        case MMPF_SENSOR_YUV_ORDER_YC:
            ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_UYVY;
        break;
        case MMPF_SENSOR_YUV_ORDER_CY:
        default:
            ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
        break;
    }
    //Set DIP SCL Atrr
    if (ePrevType == MMPS_DISPLAY_PREVIEW_FULL_SCREEN) {
        if (gbLCDRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulScaleInW, ulScaleInH,
                                        0, ulScaleInAlignedY ? ulScaleInAlignedY:(ulScaleInAlignedH - ulCropAlignedH) >> 1, ulCropAlignedW, ulCropAlignedH,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        ubDIPSCLInColor,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }
        else {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulScaleInW, ulScaleInH,
                                        0, ulScaleInAlignedY ? ulScaleInAlignedY:(ulScaleInAlignedH - ulCropAlignedH) >> 1, ulCropAlignedW, ulCropAlignedH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        ubDIPSCLInColor,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }

        MMPS_Display_SetDispCompAttr(   0, 0, ulAlignDispW, ulAlignDispH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        0, 0, ulDispWidth, ulDispHeight,
                                        0, 0, ulDispWidth, ulDispHeight,
                                        MMP_FALSE, MMP_FALSE);
    }
    else if (ePrevType == MMPS_DISPLAY_PREVIEW_HALF_SCREEN) {
        if (gbLCDRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulScaleInW, ulScaleInH,
                                        ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        ubDIPSCLInColor,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }
        else {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulScaleInW, ulScaleInH,
                                        ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        ubDIPSCLInColor,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }

        MMPS_Display_SetDispCompAttr(   0, 0, ulAlignDispW, ulAlignDispH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        0, 0, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH,
                                        0, 0, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH,
                                        MMP_TRUE, MMP_TRUE);
    }
    else if (ePrevType == MMPS_DISPLAY_PREVIEW_PIP_WIN) {
        if (gbLCDRotate) {
            MMP_ULONG ulAlignDispH_Orig = ulAlignDispH;

            if (MMP_GetANACamType() == ANA_CAM_2I1O){
                ulAlignDispH /= 2;
            }

            if (ulScaleInW * 1000 / ulAlignDispH > DIP_S_COMP_WIDTH_MAX_RATIO ||
                ulScaleInH * 1000 / ulAlignDispW > DIP_S_COMP_HEIGHT_MAX_RATIO) {
                ubReScalBypass = MMP_FALSE;
            }

            ulAlignDispH = ulAlignDispH_Orig;

            if (ubReScalBypass) {
                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                            ubDipSUseIdx,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                            0, 0, ulAlignDispH, ulAlignDispW,
                                            ubDIPSCLInColor,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            ubDipMirrorType,
                                            0,
                                            ubDipBufCnt);
            }
            else {
                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                            ubDipSUseIdx,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                            0, 0, PIP_WIN_1ST_SCALE_OUT_W, PIP_WIN_1ST_SCALE_OUT_H,
                                            ubDIPSCLInColor,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            ubDipMirrorType,
                                            0,
                                            ubDipBufCnt);

                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                            ubDipSReUseIdx,
                                            0, 0, PIP_WIN_1ST_SCALE_OUT_W, PIP_WIN_1ST_SCALE_OUT_H,
                                            0, 0, PIP_WIN_1ST_SCALE_OUT_W, PIP_WIN_1ST_SCALE_OUT_H,
                                            0, 0, ulAlignDispH, ulAlignDispW,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            ubDipMirrorType,
                                            0,
                                            ubDipBufCnt);
            }
        }
        else {
            MMP_ULONG ulAlignDispW_Orig = ulAlignDispW;

            if (MMP_GetANACamType() == ANA_CAM_2I1O){
                ulAlignDispW /= 2;
            }

            if (ulScaleInW * 1000 / ulAlignDispW > DIP_S_COMP_WIDTH_MAX_RATIO ||
                ulScaleInH * 1000 / ulAlignDispH > DIP_S_COMP_HEIGHT_MAX_RATIO) {
                ubReScalBypass = MMP_FALSE;
            }

            ulAlignDispW = ulAlignDispW_Orig;

            if (ubReScalBypass) {
                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                            ubDipSUseIdx,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                            0, 0, ulAlignDispW, ulAlignDispH,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            ubDipMirrorType,
                                            0,
                                            ubDipBufCnt);
            }
            else {
                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                            ubDipSUseIdx,
                                            0, 0, ulScaleInW, ulScaleInH,
                                            ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                            0, 0, PIP_WIN_1ST_SCALE_OUT_W, PIP_WIN_1ST_SCALE_OUT_H,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            ubDipMirrorType,
                                            0,
                                            ubDipBufCnt);

                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                            ubDipSReUseIdx,
                                            0, 0, PIP_WIN_1ST_SCALE_OUT_W, PIP_WIN_1ST_SCALE_OUT_H,
                                            0, 0, PIP_WIN_1ST_SCALE_OUT_W, PIP_WIN_1ST_SCALE_OUT_H,
                                            0, 0, ulAlignDispW, ulAlignDispH,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                            ubDipMirrorType,
                                            0,
                                            ubDipBufCnt);
            }
        }

        Component_DIP_SetParam(&Component_DIP_Scale[ubDipSReUseIdx], DIP_COMP_PARAM_SCL_BYPASS, (void*)&ubReScalBypass);

        {
            MMP_ULONG ulPipBgWidth  = (ulAlignDispW > RTNA_LCD_GetAttr()->usPanelW)? RTNA_LCD_GetAttr()->usPanelW : ulAlignDispW;
            MMP_ULONG ulPipBgHeight = (ulAlignDispH > RTNA_LCD_GetAttr()->usPanelH)? RTNA_LCD_GetAttr()->usPanelH : ulAlignDispH;

            MMPS_Display_SetPIPCompAttr(PIP_COMP_PIP_PREVIEW,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        ulDispStartX, ulDispStartY, ulPipBgWidth, ulPipBgHeight,
                                        MMP_FALSE, MMP_FALSE);
        }
    }

    if (MMP_GetANACamType() == ANA_CAM_2I1O){
        MMP_ULONG ulAlignDispW_2In1 = PIP_WIN_1ST_SCALE_OUT_W;
        MMP_ULONG ulAlignDispH_2In1 = PIP_WIN_1ST_SCALE_OUT_H;

        if (gbLCDRotate) {
            if (ubReScalBypass) {
                ulAlignDispW_2In1 = ulAlignDispH;
                ulAlignDispH_2In1 = ulAlignDispW;
            }
        }
        else {
            if (ubReScalBypass) {
                ulAlignDispW_2In1 = ulAlignDispW;
                ulAlignDispH_2In1 = ulAlignDispH;
            }
        }

        MMPD_Fctl_SetDIPCompAttr_LineOffset(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INA, ubDipSUseIdx, // Left image
                                    0, 0, ulScaleInW, ulScaleInH, ulScaleInW,
                                    ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                    0, 0, ulAlignDispW_2In1 / 2, ulAlignDispH_2In1, ulAlignDispW_2In1,
                                    ubDIPSCLInColor,  // It will be updated by Component_DIP_S_AllocateMemory_LineOffset()::inFormat
                                    DIP_COMP_COLOR_FMT_YUV422_YUYV,  // It will be updated by Component_DIP_S_AllocateMemory_LineOffset()::outFormat
                                    ubDipMirrorType,
                                    0,
                                    0 /*ubDipBufCnt*/); // Buffers will be allocated in DIP_S_COMP_VR_RCAM_PREVIEW


        MMPD_Fctl_SetDIPCompAttr_LineOffset(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INB,  ubDipSUseIdx, // Right image
                                    0, 0, ulScaleInW, ulScaleInH, ulScaleInW,
                                    ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                    ulAlignDispW_2In1 / 2, 0, ulAlignDispW_2In1 / 2, ulAlignDispH_2In1, ulAlignDispW_2In1,
                                    ubDIPSCLInColor,   // It will be updated by Component_DIP_S_AllocateMemory_LineOffset()::inFormat
                                    DIP_COMP_COLOR_FMT_YUV422_YUYV,  // It will be updated by Component_DIP_S_AllocateMemory_LineOffset()::outFormat
                                    ubDipMirrorType,
                                    0,
                                    0 /*ubDipBufCnt*/); // Buffers will be allocated in DIP_S_COMP_VR_RCAM_PREVIEW
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetScdBayerPreviewPipeAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetScdBayerPreviewPipeAttr(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PREVIEW_TYPE ePrevType)
{
    MMP_UBYTE           ubDipBufCnt = DIP_COMP_PREVW_BUF_COUNT;
    MMP_ULONG           ulAlignPrevW = 0, ulAlignPrevH = 0;
    MMP_ULONG           ulDispWidth = 0, ulDispHeight = 0;
    MMP_ULONG           ulDispStartX = 0, ulDispStartY = 0;
    MMP_ULONG           ulAlignDispW = 0, ulAlignDispH = 0;
    MMP_UBYTE           ubDipSUseIdx, ubDipRUseIdx;
    MMP_UBYTE           ubDipSclBypass = MMP_TRUE;
    MMP_UBYTE           ubDipMirrorType = DIP_COMP_MIRROR_DIS;
    MMP_UBYTE           ubCamSel = SCD_SENSOR;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        ubDipSUseIdx = DIP_S_COMP_VR_RCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_VR_RCAM_PREVIEW;
    }
    else {
        ubDipSUseIdx = DIP_S_COMP_DSC_RCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_DSC_RCAM_PREVIEW;
    }

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        MMPS_3GPRECD_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);
        MMPS_3GPRECD_GetDisplayRes(ubCamSel, &ulDispWidth, &ulDispHeight);
        MMPS_3GPRECD_GetDisplayPosition(ubCamSel, &ulDispStartX, &ulDispStartY);
    }
    else {
        MMPS_DSC_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);
        MMPS_DSC_GetDisplayRes(ubCamSel, &ulDispWidth, &ulDispHeight);
        MMPS_DSC_GetDisplayPosition(ubCamSel, &ulDispStartX, &ulDispStartY);
    }

    ulAlignDispW = ALIGN_X(ulDispWidth, DIP_R_COMP_ALIGN_BASE);
    ulAlignDispH = ALIGN_X(ulDispHeight, DIP_R_COMP_ALIGN_BASE);

    if (ePrevType == MMPS_DISPLAY_PREVIEW_FULL_SCREEN) {
        ubDipSclBypass = MMP_TRUE;
        Component_DIP_SetParam(&Component_DIP_Scale[ubDipSUseIdx], DIP_COMP_PARAM_SCL_BYPASS, (void*)&ubDipSclBypass);

        if (gbLCDRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                        ubDipRUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        (ulAlignPrevW - ulAlignDispH)>>1, (ulAlignPrevH - ulAlignDispW)>>1, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);

            MMPS_Display_SetDispCompAttr(   0, 0, ulAlignDispW, ulAlignDispH,
                                            0, 0, ulAlignDispW, ulAlignDispH,
                                            0, 0, ulDispWidth, ulDispHeight,
                                            0, 0, ulDispWidth, ulDispHeight,
                                            MMP_FALSE, MMP_FALSE);
        }
        else {
            MMPS_Display_SetDispCompAttr(   0, 0, ulAlignPrevW, ulAlignPrevH,
                                            0, 0, ulAlignPrevW, ulAlignPrevH,
                                            0, 0, ulDispWidth, ulDispHeight,
                                            0, 0, ulDispWidth, ulDispHeight,
                                            MMP_FALSE, MMP_FALSE);
        }
    }
    else if (ePrevType == MMPS_DISPLAY_PREVIEW_HALF_SCREEN) {
        ubDipSclBypass = MMP_FALSE;
        Component_DIP_SetParam(&Component_DIP_Scale[ubDipSUseIdx], DIP_COMP_PARAM_SCL_BYPASS, (void*)&ubDipSclBypass);

        if (gbLCDRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);

            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                        ubDipRUseIdx,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }
        else {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }

        MMPS_Display_SetDispCompAttr(   0, 0, ulAlignDispW, ulAlignDispH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        0, 0, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH,
                                        0, 0, RTNA_LCD_GetAttr()->usPanelW, RTNA_LCD_GetAttr()->usPanelH,
                                        MMP_TRUE, MMP_TRUE);
    }
    else if (ePrevType == MMPS_DISPLAY_PREVIEW_PIP_WIN) {
        ubDipSclBypass = MMP_FALSE;
        Component_DIP_SetParam(&Component_DIP_Scale[ubDipSUseIdx], DIP_COMP_PARAM_SCL_BYPASS, (void*)&ubDipSclBypass);

        if (gbLCDRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);

            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                        ubDipRUseIdx,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispH, ulAlignDispW,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }
        else {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        ubDipSUseIdx,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignPrevW, ulAlignPrevH,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        ubDipMirrorType,
                                        0,
                                        ubDipBufCnt);
        }

        {
            MMP_ULONG ulPipBgWidth  = (ulAlignDispW > RTNA_LCD_GetAttr()->usPanelW)? RTNA_LCD_GetAttr()->usPanelW : ulAlignDispW;
            MMP_ULONG ulPipBgHeight = (ulAlignDispH > RTNA_LCD_GetAttr()->usPanelH)? RTNA_LCD_GetAttr()->usPanelH : ulAlignDispH;

            MMPS_Display_SetPIPCompAttr(PIP_COMP_PIP_PREVIEW,
                                        0, 0, ulAlignDispW, ulAlignDispH,
                                        ulDispStartX, ulDispStartY, ulPipBgWidth, ulPipBgHeight,
                                        MMP_FALSE, MMP_FALSE);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetUsbhPreviewPipeAttr
//  Description : Set USBH Cam Component Parameters
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetUsbhPreviewPipeAttr(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PREVIEW_TYPE ePrevType)
{
    MMP_DSC_JPEG_FMT    eJpegFmt = MMP_DSC_JPEG_FMT444; // TBD
    MMP_UBYTE           ubDipBufCnt = DIP_COMP_PREVW_BUF_COUNT;
    MMP_USHORT          usDispWidth = 0, usDispHeight = 0;
    MMP_ULONG           ulAlignDispW = 0, ulAlignDispH = 0;
    MMP_ULONG           ulCropAlignedW = 0, ulCropAlignedH = 0;
    MMP_USHORT          usJpegSrcW = 0, usJpegSrcH = 0;
    MMP_BOOL            bUserConfig;
    MMP_BOOL            bMirror = MMP_FALSE;
    MMP_UBYTE           ubDipMirrorType = DIP_COMP_MIRROR_DIS;
    MMP_UBYTE           ubFitMode;
    DIP_COMP_COLOR_FMT  eDipColor = DIP_COMP_COLOR_FMT_YUV420_UV;
    MMP_USHORT          usBufWidth,   usBufHeight;
    MMP_USHORT          usStartX,     usStartY;
    MMP_USHORT          usWinWidth,   usWinHeight;
    MMP_UBYTE           ubPipFrmDropCnt = 5;
    MMP_UBYTE           ubDipSUseIdx, ubDipRUseIdx;
    MMP_ERR             eRetErr = MMP_ERR_NONE;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        ubDipSUseIdx = DIP_S_COMP_VR_RCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_VR_RCAM_PREVIEW;
    }
    else {
        ubDipSUseIdx = DIP_S_COMP_DSC_RCAM_PREVIEW;
        ubDipRUseIdx = DIP_R_COMP_DSC_RCAM_PREVIEW;
    }

    /* Get DIP or Scaler format setting */
    if ((eJpegFmt >= MMP_DSC_JPEG_FMT420) &&
        (eJpegFmt <= MMP_DSC_JPEG_FMT411_V))
        eDipColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
    else
        eDipColor = DIP_COMP_COLOR_FMT_UNSUPPORT;

    if (eDipColor == DIP_COMP_COLOR_FMT_UNSUPPORT) {
        MMPS_HUVC_DBG_ERR(1, "InitDecMjpegToPreview => DIP UnSupport Color\r\n");
        return eRetErr;
    }

    MMPS_HUVC_GetDecMjpegToPreviewSrcAttr(&usJpegSrcW, &usJpegSrcH);
    MMPS_HUVC_GetCustomedPrevwAttr( &bUserConfig,
                                    &bMirror,
                                    &ubFitMode,
                                    &usBufWidth, &usBufHeight,
                                    &usStartX, &usStartY,
                                    &usDispWidth, &usDispHeight);

    ulAlignDispW = ALIGN_X(usDispWidth, DIP_S_COMP_WIDTH_ALIGN_BASE);
    ulAlignDispH = usDispHeight;

    if (gbLCDRotate) {
        if (DIP_R_COMP_ALIGN_CHECK(usDispWidth)) {
            ulAlignDispW = ALIGN_X(usDispWidth, DIP_R_COMP_ALIGN_BASE);
        }
        if (DIP_R_COMP_ALIGN_CHECK(usDispHeight)) {
            ulAlignDispH = ALIGN_X(usDispHeight, DIP_R_COMP_ALIGN_BASE);
        }
    }

    if (gbLCDRotate) {
        if (ulAlignDispH / ulAlignDispW >= 2) {
            ulCropAlignedW = usJpegSrcW;
            ulCropAlignedH = ulCropAlignedW * ulAlignDispW / ulAlignDispH;
        }
        else {
            ulCropAlignedW = usJpegSrcW;
            ulCropAlignedH = usJpegSrcH;
        }
    }
    else {
        if (ulAlignDispW / ulAlignDispH >= 2) {
            ulCropAlignedW = usJpegSrcW;
            ulCropAlignedH = ulCropAlignedW * ulAlignDispH / ulAlignDispW;
        }
        else {
            ulCropAlignedW = usJpegSrcW;
            ulCropAlignedH = usJpegSrcH;
        }
    }

    ubDipMirrorType = (bMirror) ? (DIP_COMP_MIRROR_EN) : (DIP_COMP_MIRROR_DIS);

    if (ePrevType == MMPS_DISPLAY_PREVIEW_FULL_SCREEN) {

        if (gbLCDRotate) {
            eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                                ubDipSUseIdx,
                                                0, 0, usJpegSrcW, usJpegSrcH,
                                                0, (usJpegSrcH - ulCropAlignedH) >> 1, ulCropAlignedW, ulCropAlignedH,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                eDipColor,
                                                DIP_COMP_COLOR_FMT_YUV420_UV,
                                                ubDipMirrorType,
                                                0,
                                                ubDipBufCnt);

            eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_ROT,
                                                ubDipRUseIdx,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                0, 0, ulAlignDispW, ulAlignDispH,
                                                DIP_COMP_COLOR_FMT_YUV420_UV,
                                                DIP_COMP_COLOR_FMT_YUV420_UV,
                                                DIP_COMP_MIRROR_DIS,
                                                0,
                                                ubDipBufCnt);
        }
        else {
            eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                                ubDipSUseIdx,
                                                0, 0, usJpegSrcW, usJpegSrcH,
                                                0, (usJpegSrcH - ulCropAlignedH) >> 1, ulCropAlignedW, ulCropAlignedH,
                                                0, 0, ulAlignDispW, ulAlignDispH,
                                                eDipColor,
                                                DIP_COMP_COLOR_FMT_YUV420_UV,
                                                ubDipMirrorType,
                                                0,
                                                ubDipBufCnt);
        }
    }
    else if (ePrevType == MMPS_DISPLAY_PREVIEW_PIP_WIN) {
        if (gbLCDRotate) {
            eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                                ubDipSUseIdx,
                                                0, 0, usJpegSrcW, usJpegSrcH,
                                                0, 0, usJpegSrcW, usJpegSrcH,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                eDipColor,
                                                DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                                ubDipMirrorType,
                                                0,
                                                ubDipBufCnt);

            eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_ROT,
                                                ubDipRUseIdx,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                0, 0, ulAlignDispH, ulAlignDispW,
                                                0, 0, ulAlignDispW, ulAlignDispH,
                                                DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                                DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                                DIP_COMP_MIRROR_DIS,
                                                0,
                                                ubDipBufCnt);
        }
        else {
            eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                                ubDipSUseIdx,
                                                0, 0, usJpegSrcW, usJpegSrcH,
                                                0, 0, usJpegSrcW, usJpegSrcH,
                                                0, 0, ulAlignDispW, ulAlignDispH,
                                                eDipColor,
                                                DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                                ubDipMirrorType,
                                                0,
                                                ubDipBufCnt);
        }

        /* Update component PIP window setting */
        {
            MMP_ULONG ulPipBgWidth  = (ulAlignDispW > RTNA_LCD_GetAttr()->usPanelW)? RTNA_LCD_GetAttr()->usPanelW : ulAlignDispW;
            MMP_ULONG ulPipBgHeight = (ulAlignDispH > RTNA_LCD_GetAttr()->usPanelH)? RTNA_LCD_GetAttr()->usPanelH : ulAlignDispH;

            eRetErr = MMPS_Display_SetPIPCompAttr(  PIP_COMP_PIP_PREVIEW,
                                                    0, 0, ulAlignDispW, ulAlignDispH,
                                                    usStartX, usStartY, ulPipBgWidth, ulPipBgHeight,
                                                    MMP_FALSE, MMP_FALSE);
        }
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetScdAnaDecPreviewPIPType_2In1
//  Description : Set PRM & SCD CAM PIP type
//------------------------------------------------------------------------------
void MMPS_Display_SetScdAnaDecPreviewPIPType_2In1(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PRM_SCD_PIP_TYPE ePipType)
{
    MMP_UBYTE ubCompScriptIdx_Prm_Full      = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Prm_Pip       = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scd_Full      = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scd_Pip       = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scd_2In1_InA  = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scd_2In1_InB  = COMPO_SCRIPT_INVALID;

    MMP_UBYTE ubPortScriptIdx_Prm_Full      = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_Prm_Pip       = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_Scd_PrevwSrc_2In1_InA  = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_Scd_PrevwSrc_2In1_InB  = PORT_SCRIPT_INVALID;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {

        ubPortScriptIdx_Prm_Full            = PORT_SCRIPT_VR_PREV_PRM_BAYER_FULL;
        ubPortScriptIdx_Prm_Pip             = PORT_SCRIPT_VR_PREV_PRM_BAYER_PIP;

        ubPortScriptIdx_Scd_PrevwSrc_2In1_InA        = PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_INA;
        ubPortScriptIdx_Scd_PrevwSrc_2In1_InB        = PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_INB;

        if (gbLCDRotate) {
            ubCompScriptIdx_Prm_Full        = COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_FULL;
            ubCompScriptIdx_Prm_Pip         = COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_PIP;
            ubCompScriptIdx_Scd_Full        = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_FULL_2IN1_OUT;
            ubCompScriptIdx_Scd_Pip         = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_PIP_2IN1_OUT;
            ubCompScriptIdx_Scd_2In1_InA    = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_2IN1_INA;
            ubCompScriptIdx_Scd_2In1_InB    = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_2IN1_INB;
        }
        else {
            UartSendTrace(FG_RED("WARNING!!! Not implemented no rotate case for 2In1 preview !!!\r\n"));
            #if 0 //TODO
            ubCompScriptIdx_Prm_Full        = COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_FULL;
            ubCompScriptIdx_Prm_Pip         = COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_PIP;
            ubCompScriptIdx_Scd_Full        = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_Scd_Pip         = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_PIP;
            #endif
        }
    }
    else {
        #if 0 //TODO
        ubPortScriptIdx_Prm_Full            = PORT_SCRIPT_DSC_PREV_PRM_FULL;
        ubPortScriptIdx_Prm_Pip             = PORT_SCRIPT_DSC_PREV_PRM_PIP;

        ubPortScriptIdx_Scd_PrevwSrc        = PORT_SCRIPT_DSC_PREV_SCD_ANADEC_SRC;

        if (gbLCDRotate) {
            ubCompScriptIdx_Prm_Full        = COMPO_SCRIPT_DSC_R_PREV_PRM_FULL;
            ubCompScriptIdx_Prm_Pip         = COMPO_SCRIPT_DSC_R_PREV_PRM_PIP;
            ubCompScriptIdx_Scd_Full        = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_Scd_Pip         = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_PIP;
        }
        else {
            ubCompScriptIdx_Prm_Full        = COMPO_SCRIPT_DSC_N_PREV_PRM_FULL;
            ubCompScriptIdx_Prm_Pip         = COMPO_SCRIPT_DSC_N_PREV_PRM_PIP;
            ubCompScriptIdx_Scd_Full        = COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_Scd_Pip         = COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_PIP;
        }
        #endif
    }

    /* Close All Port Scripts */
    ClosePortScript(ubPortScriptIdx_Prm_Full);
    ClosePortScript(ubPortScriptIdx_Prm_Pip);
    #if (TEST_2IN1_SAME_SOURCE)
    {
        MMP_COMPONENT_BASE  *pComp = &Component_RawS[RAWS_COMP_IDX];
        pComp->pOutPort[0].State = PORT_CLOSE; //RawS --> DIP_Scale[Prev_InA]
        pComp->pOutPort[1].State = PORT_CLOSE; //RawS --> DIP_Scale[Prev_InB]
    }
    #else
    ClosePortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InA);
    ClosePortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InB);
    #endif

    /* Close All Scripts */
    CloseScript(ubCompScriptIdx_Prm_Full);
    CloseScript(ubCompScriptIdx_Scd_Full);
    CloseScript(ubCompScriptIdx_Prm_Pip);
    CloseScript(ubCompScriptIdx_Scd_Pip);
    CloseScript(ubCompScriptIdx_Scd_2In1_InA);
    CloseScript(ubCompScriptIdx_Scd_2In1_InB);

    if (ePipType == MMPS_DISPLAY_PRM_FULL_SCD_PIP) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);
        MMPS_Display_SetScdAnaDecPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_PIP_WIN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Full);
        OpenScript(ubCompScriptIdx_Scd_Pip);
        OpenScript(ubCompScriptIdx_Scd_2In1_InA);
        OpenScript(ubCompScriptIdx_Scd_2In1_InB);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Full);
        #if (TEST_2IN1_SAME_SOURCE)
        //OpenPortScript(PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_TEST); // Useless because OpenPortScript() only can open 1 port
        {
            MMP_COMPONENT_BASE  *pComp = &Component_RawS[RAWS_COMP_IDX];
            pComp->pOutPort[0].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InA]
            pComp->pOutPort[1].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InB]
        }
        #else
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InA);
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InB);
        #endif
    }
    else if (ePipType == MMPS_DISPLAY_PRM_PIP_SCD_FULL) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_PIP_WIN);
        MMPS_Display_SetScdAnaDecPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Pip);
        OpenScript(ubCompScriptIdx_Scd_Full);
        OpenScript(ubCompScriptIdx_Scd_2In1_InA);
        OpenScript(ubCompScriptIdx_Scd_2In1_InB);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Pip);
        #if (TEST_2IN1_SAME_SOURCE)
        //OpenPortScript(PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_TEST); // Useless because OpenPortScript() only can open 1 port
        {
            MMP_COMPONENT_BASE  *pComp = &Component_RawS[RAWS_COMP_IDX];
            pComp->pOutPort[0].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InA]
            pComp->pOutPort[1].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InB]
        }
        #else
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InA);
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InB);
        #endif

    }
    else if (ePipType == MMPS_DISPLAY_PRM_FULL_SCD_NONE) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Full);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_NONE_SCD_FULL) {
        MMPS_Display_SetScdAnaDecPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Scd_Full);
        OpenScript(ubCompScriptIdx_Scd_2In1_InA);
        OpenScript(ubCompScriptIdx_Scd_2In1_InB);

        /* Open Port Scripts */
        #if (TEST_2IN1_SAME_SOURCE)
        //OpenPortScript(PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_TEST); // Useless because OpenPortScript() only can open 1 port
        {
            MMP_COMPONENT_BASE  *pComp = &Component_RawS[RAWS_COMP_IDX];
            pComp->pOutPort[0].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InA]
            pComp->pOutPort[1].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InB]
        }
        #else
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InA);
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InB);
        #endif
    }
    else if (ePipType == MMPS_DISPLAY_PRM_HALF_SCD_HALF) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_HALF_SCREEN);
        MMPS_Display_SetScdAnaDecPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_HALF_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Pip);
        OpenScript(ubCompScriptIdx_Scd_Full);
        OpenScript(ubCompScriptIdx_Scd_2In1_InA);
        OpenScript(ubCompScriptIdx_Scd_2In1_InB);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Pip);
        #if (TEST_2IN1_SAME_SOURCE)
        //OpenPortScript(PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_TEST); // Useless because OpenPortScript() only can open 1 port
        {
            MMP_COMPONENT_BASE  *pComp = &Component_RawS[RAWS_COMP_IDX];
            pComp->pOutPort[0].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InA]
            pComp->pOutPort[1].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InB]
        }
        #else
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InA);
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc_2In1_InB);
        #endif
    }
}


//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetScdAnaDecPreviewPIPType
//  Description : Set PRM & SCD CAM PIP type
//------------------------------------------------------------------------------
void MMPS_Display_SetScdAnaDecPreviewPIPType(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PRM_SCD_PIP_TYPE ePipType)
{
    MMP_UBYTE ubCompScriptIdx_Prm_Full      = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Prm_Pip       = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scd_Full      = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scd_Pip       = COMPO_SCRIPT_INVALID;

    MMP_UBYTE ubPortScriptIdx_Prm_Full      = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_Prm_Pip       = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_Scd_PrevwSrc  = PORT_SCRIPT_INVALID;

    if (MMP_GetANACamType() == ANA_CAM_2I1O){
        if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
            return MMPS_Display_SetScdAnaDecPreviewPIPType_2In1( ubUiMode, ePipType );
        }
        else {
            UartSendTrace(FG_PURPLE("Note: Now RearCam_2In1 doesn't support DSC mode !!\r\n"));
            return;
        }
    }

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {

        ubPortScriptIdx_Prm_Full            = PORT_SCRIPT_VR_PREV_PRM_BAYER_FULL;
        ubPortScriptIdx_Prm_Pip             = PORT_SCRIPT_VR_PREV_PRM_BAYER_PIP;

        ubPortScriptIdx_Scd_PrevwSrc        = PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC;

        if (gbLCDRotate) {
            ubCompScriptIdx_Prm_Full        = COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_FULL;
            ubCompScriptIdx_Prm_Pip         = COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_PIP;
            ubCompScriptIdx_Scd_Full        = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_Scd_Pip         = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_PIP;
        }
        else {
            ubCompScriptIdx_Prm_Full        = COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_FULL;
            ubCompScriptIdx_Prm_Pip         = COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_PIP;
            ubCompScriptIdx_Scd_Full        = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_Scd_Pip         = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_PIP;
        }
    }
    else {

        ubPortScriptIdx_Prm_Full            = PORT_SCRIPT_DSC_PREV_PRM_FULL;
        ubPortScriptIdx_Prm_Pip             = PORT_SCRIPT_DSC_PREV_PRM_PIP;

        ubPortScriptIdx_Scd_PrevwSrc        = PORT_SCRIPT_DSC_PREV_SCD_ANADEC_SRC;

        if (gbLCDRotate) {
            ubCompScriptIdx_Prm_Full        = COMPO_SCRIPT_DSC_R_PREV_PRM_FULL;
            ubCompScriptIdx_Prm_Pip         = COMPO_SCRIPT_DSC_R_PREV_PRM_PIP;
            ubCompScriptIdx_Scd_Full        = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_Scd_Pip         = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_PIP;
        }
        else {
            ubCompScriptIdx_Prm_Full        = COMPO_SCRIPT_DSC_N_PREV_PRM_FULL;
            ubCompScriptIdx_Prm_Pip         = COMPO_SCRIPT_DSC_N_PREV_PRM_PIP;
            ubCompScriptIdx_Scd_Full        = COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_Scd_Pip         = COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_PIP;
        }
    }

    /* Close All Port Scripts */
    ClosePortScript(ubPortScriptIdx_Prm_Full);
    ClosePortScript(ubPortScriptIdx_Prm_Pip);
    ClosePortScript(ubPortScriptIdx_Scd_PrevwSrc);

    /* Close All Scripts */
    CloseScript(ubCompScriptIdx_Prm_Full);
    CloseScript(ubCompScriptIdx_Scd_Full);
    CloseScript(ubCompScriptIdx_Prm_Pip);
    CloseScript(ubCompScriptIdx_Scd_Pip);

    if (ePipType == MMPS_DISPLAY_PRM_FULL_SCD_PIP) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);
        MMPS_Display_SetScdAnaDecPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_PIP_WIN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Full);
        OpenScript(ubCompScriptIdx_Scd_Pip);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Full);
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_PIP_SCD_FULL) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_PIP_WIN);
        MMPS_Display_SetScdAnaDecPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Pip);
        OpenScript(ubCompScriptIdx_Scd_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Pip);
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_FULL_SCD_NONE) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Full);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_NONE_SCD_FULL) {
        MMPS_Display_SetScdAnaDecPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Scd_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_HALF_SCD_HALF) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_HALF_SCREEN);
        MMPS_Display_SetScdAnaDecPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_HALF_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Pip);
        OpenScript(ubCompScriptIdx_Scd_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Pip);
        OpenPortScript(ubPortScriptIdx_Scd_PrevwSrc);
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetScdBayerPreviewPIPType
//  Description : Set PRM & SCD CAM PIP type
//------------------------------------------------------------------------------
void MMPS_Display_SetScdBayerPreviewPIPType(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PRM_SCD_PIP_TYPE ePipType)
{
    MMP_UBYTE ubCompScriptIdx_Prm_Full  = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Prm_Pip   = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scd_Full  = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scd_Pip   = COMPO_SCRIPT_INVALID;

    MMP_UBYTE ubPortScriptIdx_Prm_Full  = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_Prm_Pip   = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_Scd       = PORT_SCRIPT_INVALID;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {

        ubPortScriptIdx_Prm_Full        = PORT_SCRIPT_VR_PREV_PRM_BAYER_FULL;
        ubPortScriptIdx_Prm_Pip         = PORT_SCRIPT_VR_PREV_PRM_BAYER_PIP;

        ubPortScriptIdx_Scd             = PORT_SCRIPT_VR_PREV_SCD_BAYER;

        if (gbLCDRotate) {
            ubCompScriptIdx_Prm_Full    = COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_FULL;
            ubCompScriptIdx_Prm_Pip     = COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_PIP;
            ubCompScriptIdx_Scd_Full    = COMPO_SCRIPT_VR_R_PREV_SCD_BAYER_FULL;
            ubCompScriptIdx_Scd_Pip     = COMPO_SCRIPT_VR_R_PREV_SCD_BAYER_PIP;
        }
        else {
            ubCompScriptIdx_Prm_Full    = COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_FULL;
            ubCompScriptIdx_Prm_Pip     = COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_PIP;
            ubCompScriptIdx_Scd_Full    = COMPO_SCRIPT_VR_N_PREV_SCD_BAYER_FULL;
            ubCompScriptIdx_Scd_Pip     = COMPO_SCRIPT_VR_N_PREV_SCD_BAYER_PIP;
        }
    }
    else {
        ubPortScriptIdx_Prm_Full        = PORT_SCRIPT_DSC_PREV_PRM_FULL;
        ubPortScriptIdx_Prm_Pip         = PORT_SCRIPT_DSC_PREV_PRM_PIP;

        ubPortScriptIdx_Scd             = PORT_SCRIPT_DSC_PREV_SCD_BAYER;

        if (gbLCDRotate) {
            ubCompScriptIdx_Prm_Full    = COMPO_SCRIPT_DSC_R_PREV_PRM_FULL;
            ubCompScriptIdx_Prm_Pip     = COMPO_SCRIPT_DSC_R_PREV_PRM_PIP;
            ubCompScriptIdx_Scd_Full    = COMPO_SCRIPT_DSC_R_PREV_SCD_BAYER_FULL;
            ubCompScriptIdx_Scd_Pip     = COMPO_SCRIPT_DSC_R_PREV_SCD_BAYER_PIP;
        }
        else {
            ubCompScriptIdx_Prm_Full    = COMPO_SCRIPT_DSC_N_PREV_PRM_FULL;
            ubCompScriptIdx_Prm_Pip     = COMPO_SCRIPT_DSC_N_PREV_PRM_PIP;
            #if 0 // TODO jeff
            ubCompScriptIdx_Scd_Full    = COMPO_SCRIPT_DSC_N_PREV_SCD_BAYER_FULL;
            ubCompScriptIdx_Scd_Pip     = COMPO_SCRIPT_DSC_N_PREV_SCD_BAYER_PIP;
            #endif
        }
    }

    /* Close All Port Scripts */
    ClosePortScript(ubPortScriptIdx_Prm_Full);
    ClosePortScript(ubPortScriptIdx_Prm_Pip);
    ClosePortScript(ubPortScriptIdx_Scd);

    /* Close All Scripts */
    CloseScript(ubCompScriptIdx_Prm_Full);
    CloseScript(ubCompScriptIdx_Scd_Full);
    CloseScript(ubCompScriptIdx_Prm_Pip);
    CloseScript(ubCompScriptIdx_Scd_Pip);

    if (ePipType == MMPS_DISPLAY_PRM_FULL_SCD_PIP) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);
        MMPS_Display_SetScdBayerPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_PIP_WIN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Full);
        OpenScript(ubCompScriptIdx_Scd_Pip);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Full);
        OpenPortScript(ubPortScriptIdx_Scd);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_PIP_SCD_FULL) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_PIP_WIN);
        MMPS_Display_SetScdBayerPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Pip);
        OpenScript(ubCompScriptIdx_Scd_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Pip);
        OpenPortScript(ubPortScriptIdx_Scd);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_FULL_SCD_NONE) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Full);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_NONE_SCD_FULL) {
        MMPS_Display_SetScdBayerPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Scd_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Scd);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_HALF_SCD_HALF) {
        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_HALF_SCREEN);
        MMPS_Display_SetScdBayerPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_HALF_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Pip);
        OpenScript(ubCompScriptIdx_Scd_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Pip);
        OpenPortScript(ubPortScriptIdx_Scd);
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetUsbCamPreviewPIPType
//  Description : Set PRM & USBH CAM PIP type
//------------------------------------------------------------------------------
void MMPS_Display_SetUsbCamPreviewPIPType(MMP_UBYTE ubUiMode, MMPS_DISPLAY_PRM_USBH_PIP_TYPE ePipType)
{
    MMP_UBYTE ubCompScriptIdx_Prm_Full  = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Prm_Pip   = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Usbh_Full = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Usbh_Pip  = COMPO_SCRIPT_INVALID;

    MMP_UBYTE ubPortScriptIdx_Prm_Full  = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_Prm_Pip   = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_Usbh      = PORT_SCRIPT_INVALID;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {

        ubPortScriptIdx_Prm_Full        = PORT_SCRIPT_VR_PREV_PRM_BAYER_FULL;
        ubPortScriptIdx_Prm_Pip         = PORT_SCRIPT_VR_PREV_PRM_BAYER_PIP;
        ubPortScriptIdx_Usbh            = PORT_SCRIPT_VR_PREV_USBH_SRC;

        if (gbLCDRotate) {
            ubCompScriptIdx_Prm_Full    = COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_FULL;
            ubCompScriptIdx_Prm_Pip     = COMPO_SCRIPT_VR_R_PREV_PRM_BAYER_PIP;
            ubCompScriptIdx_Usbh_Full   = COMPO_SCRIPT_VR_R_PREV_USBH_FULL;
            ubCompScriptIdx_Usbh_Pip    = COMPO_SCRIPT_VR_R_PREV_USBH_PIP;
        }
        else {
            ubCompScriptIdx_Prm_Full    = COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_FULL;
            ubCompScriptIdx_Prm_Pip     = COMPO_SCRIPT_VR_N_PREV_PRM_BAYER_PIP;
            ubCompScriptIdx_Usbh_Full   = COMPO_SCRIPT_VR_N_PREV_USBH_FULL;
            ubCompScriptIdx_Usbh_Pip    = COMPO_SCRIPT_VR_N_PREV_USBH_PIP;
        }
    }
    else {
        ubPortScriptIdx_Prm_Full        = PORT_SCRIPT_DSC_PREV_PRM_FULL;
        ubPortScriptIdx_Prm_Pip         = PORT_SCRIPT_DSC_PREV_PRM_PIP;
        ubPortScriptIdx_Usbh            = PORT_SCRIPT_DSC_PREV_USBH;

        if (gbLCDRotate) {
            ubCompScriptIdx_Prm_Full    = COMPO_SCRIPT_DSC_R_PREV_PRM_FULL;
            ubCompScriptIdx_Prm_Pip     = COMPO_SCRIPT_DSC_R_PREV_PRM_PIP;
            ubCompScriptIdx_Usbh_Full   = COMPO_SCRIPT_DSC_R_PREV_USBH_FULL;
            ubCompScriptIdx_Usbh_Pip    = COMPO_SCRIPT_DSC_R_PREV_USBH_PIP;
        }
        else {
            ubCompScriptIdx_Prm_Full    = COMPO_SCRIPT_DSC_N_PREV_PRM_FULL;
            ubCompScriptIdx_Prm_Pip     = COMPO_SCRIPT_DSC_N_PREV_PRM_PIP;
            ubCompScriptIdx_Usbh_Full   = COMPO_SCRIPT_DSC_N_PREV_USBH_FULL;
            ubCompScriptIdx_Usbh_Pip    = COMPO_SCRIPT_DSC_N_PREV_USBH_PIP;
        }
    }

    /* Close All Port Scripts */
    ClosePortScript(ubPortScriptIdx_Prm_Full);
    ClosePortScript(ubPortScriptIdx_Prm_Pip);
    ClosePortScript(ubPortScriptIdx_Usbh);

    /* Close All Scripts */
    CloseScript(ubCompScriptIdx_Prm_Full);
    CloseScript(ubCompScriptIdx_Usbh_Full);
    CloseScript(ubCompScriptIdx_Prm_Pip);
    CloseScript(ubCompScriptIdx_Usbh_Pip);

    if (ePipType == MMPS_DISPLAY_PRM_FULL_USBH_PIP) {

        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);
        MMPS_Display_SetUsbhPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_PIP_WIN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Full);
        OpenScript(ubCompScriptIdx_Usbh_Pip);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Full);
        OpenPortScript(ubPortScriptIdx_Usbh);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_PIP_USBH_FULL) {

        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_PIP_WIN);
        MMPS_Display_SetUsbhPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Pip);
        OpenScript(ubCompScriptIdx_Usbh_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Pip);
        OpenPortScript(ubPortScriptIdx_Usbh);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_FULL_USBH_NONE) {

        MMPS_Display_SetPrmPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Prm_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Prm_Full);
    }
    else if (ePipType == MMPS_DISPLAY_PRM_NONE_USBH_FULL) {

        MMPS_Display_SetUsbhPreviewPipeAttr(ubUiMode, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

        /* Open Scripts */
        OpenScript(ubCompScriptIdx_Usbh_Full);

        /* Open Port Scripts */
        OpenPortScript(ubPortScriptIdx_Usbh);
    }
}

MMP_ERR MMPS_Display_EnableScdAnaDecSnrPreview_2IN2OUT(MMP_UBYTE ubUiMode, MMP_BOOL bEnablePreview)
{
    MMP_UBYTE ubCompScriptIdx_RecdScalOsd_2In2_Out1      = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_RecdScalOsd_2In2_Out2   = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scr_2In2_Raw1             = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Scr_2In2_Raw2             = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Prevw_2In2_Out         = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_RecdSrc_2In1_InA       = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_PrevwSrc_Raw1_Fcam     = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_PrevwSrc_Raw2_Rcam     = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_RecdSrcRaw2                = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_RecdSrcRaw1                = PORT_SCRIPT_INVALID;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        //Fcam
        ubPortScriptIdx_PrevwSrc_Raw1_Fcam      = PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW1;              //RAWS_CH1 open port0=DIP_S0
        ubCompScriptIdx_Scr_2In2_Raw1           = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW1;      //RAWS_CH1->DIP_S0+DIP_S14+DIP_S8     (prev+Frec+wifi)
        ubCompScriptIdx_RecdScalOsd_2In2_Out1   = COMPO_SCRIPT_VR_PRM_ANADEC_RECD_SCAL_OSD_RAW1;        //RAW1<-DIP_S14_RREC->MFE0/JPE3_PRIMARY/DIP_S5_RTHUMB
        ubPortScriptIdx_RecdSrcRaw1             = PORT_SCRIPT_VR_PRM_ANADEC_RECD_SRC_2IN2_RAW1;         //PRM_RECD_SRC:RAW1 opp1 DIP_S14
        UartSendTrace(BG_BLUE("2IN2O TODO:%s,%d init DIP_S14\n"),__FUNCTION__, __LINE__);

        //Rcam
        ubPortScriptIdx_PrevwSrc_Raw2_Rcam      = PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW2;              //RAWS_CH2 open port0=DIP_S1
        ubPortScriptIdx_RecdSrcRaw2             = PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC_2IN2_RAW2;          //RAWS_CH2 open port1=DIP_S3   record
        ubCompScriptIdx_RecdScalOsd_2In2_Out2   = COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN2_OUT;    //DIP_S3*RREC->MFE1/JPE4_PRIMARY/DIP_S6_RTHUMB
        ubCompScriptIdx_Scr_2In2_Raw2           = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW2;      //RAWS_CH2->DIP_S1/DIP_S3/DIP_S8
        if (gbLCDRotate) {
            ubCompScriptIdx_Prevw_2In2_Out      = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_PIP_2IN2_OUT;       //DIP_S1->DIP_S2->DIP_R1->PIP0
        }
        else {
            UartSendTrace(FG_RED("WARNING!!! Not implemented no rotate case for 2In2o preview !!!\r\n"));
        }
    }
    else {
        //Fcam
        ubPortScriptIdx_PrevwSrc_Raw1_Fcam      = PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW1;              //RAWS_CH1 open port0=DIP_S0
        ubCompScriptIdx_Scr_2In2_Raw1           = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_SRC_2IN2_RAW1;     //DSC:RAW1->DIP_S0+DIP_S9    (prev+Fcap)
        ubPortScriptIdx_RecdSrcRaw1             = PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC_2IN2_RAW1;//RAWS_CH1 open port1=DIP_S9

        //Rcam
        ubPortScriptIdx_PrevwSrc_Raw2_Rcam      = PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW2;              //RAWS_CH2 open port0=DIP_S1
        ubPortScriptIdx_RecdSrcRaw2                 = PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC_2IN2_RAW2;     //RAWS_CH2 open port1=DIP_S3

        //ubCompScriptIdx_RecdScalOsd_2In2_Out    = COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_OUT;    //DIP_S3*RREC->MFE1/JPE4_PRIMARY/DIP_S4_RTHUMB
        ubCompScriptIdx_RecdScalOsd_2In2_Out1    = COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN2_RAW1; //DIP_S9_cap->JPE3_PRIMARY/DIP_S10_RTHUMB
        ubCompScriptIdx_RecdScalOsd_2In2_Out2    = COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN2_RAW2; //DIP_S3_cap->JPE4_PRIMARY/DIP_S4_RTHUMB
        ubCompScriptIdx_Scr_2In2_Raw2           = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN2_RAW2;      //RAWS_CH2->DIP_S1/DIP_S3/DIP_S8
        if (gbLCDRotate) {
            ubCompScriptIdx_Prevw_2In2_Out      = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_PIP_2IN2_OUT;       //DIP_S1->DIP_S2->DIP_R1->PIP0
        }
        else {
            UartSendTrace(FG_RED("WARNING!!! Not implemented no rotate case for 2In2o preview !!!\r\n"));
        }
    }

    if (bEnablePreview) {

        OpenScript(ubCompScriptIdx_Scr_2In2_Raw1);
        OpenPortScript(ubPortScriptIdx_PrevwSrc_Raw1_Fcam);
        OpenScript(ubCompScriptIdx_RecdScalOsd_2In2_Out1);
        OpenPortScript(ubPortScriptIdx_RecdSrcRaw1);

        OpenScript(ubCompScriptIdx_Scr_2In2_Raw2);
        MMPF_Sensor_SetChannelAttr(SCD_SENSOR, MMP_TRUE); // Set Raw Channel Attribute after RawS component is opened.
        cameraPreviewSetChannel((u32)RAWS_COMP_IDX2,MMP_TRUE);
        OpenScript(ubCompScriptIdx_RecdScalOsd_2In2_Out2);

        OpenPortScript(ubPortScriptIdx_RecdSrcRaw2);
        OpenScript(ubCompScriptIdx_Prevw_2In2_Out);
        OpenPortScript(ubPortScriptIdx_PrevwSrc_Raw2_Rcam);

    }
    else {
        ClosePortScript(ubPortScriptIdx_PrevwSrc_Raw1_Fcam);
        ClosePortScript(ubPortScriptIdx_PrevwSrc_Raw2_Rcam);
        ClosePortScript(ubPortScriptIdx_RecdSrcRaw1);
        ClosePortScript(ubPortScriptIdx_RecdSrcRaw2);

        cameraPreviewSetChannel((u32)RAWS_COMP_IDX2,MMP_FALSE);
        CloseScript(ubCompScriptIdx_Scr_2In2_Raw1);
        CloseScript(ubCompScriptIdx_Scr_2In2_Raw2);
        CloseScript(ubCompScriptIdx_Prevw_2In2_Out);
        CloseScript(ubCompScriptIdx_RecdScalOsd_2In2_Out1);
        CloseScript(ubCompScriptIdx_RecdScalOsd_2In2_Out2);
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_Display_EnableScdAnaDecSnrPreview_2IN1
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_EnableScdAnaDecSnrPreview_2IN1(MMP_UBYTE ubUiMode, MMP_BOOL bEnablePreview)
{
    MMP_UBYTE ubCompScriptIdx_RecdScalOsd_2In1_Out   = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_RecdScalOsd_2In1_InA   = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_RecdScalOsd_2In1_InB   = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_PrevwSrc_2In1_InA      = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_PrevwSrc_2In1_InB      = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Prevw_2In1_Out         = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Prevw_2In1_InA         = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_Prevw_2In1_InB         = COMPO_SCRIPT_INVALID;

    MMP_UBYTE ubPortScriptIdx_RecdSrc_2In1_InA       = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_PrevwSrc_Raw1_Fcam     = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_RecdSrc_2In1_InB       = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_PrevwSrc_2In1_InA      = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_PrevwSrc_2In1_InB      = PORT_SCRIPT_INVALID;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        ubPortScriptIdx_RecdSrc_2In1_InA        = PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC_2IN1_INA;
        ubPortScriptIdx_RecdSrc_2In1_InB        = PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC_2IN1_INB;
        ubPortScriptIdx_PrevwSrc_2In1_InA       = PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_INA;
        ubPortScriptIdx_PrevwSrc_2In1_InB       = PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_INB;
        ubPortScriptIdx_PrevwSrc_Raw1_Fcam      = PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW1;//RAWS_CH1 open port4=DIP_S0

        ubCompScriptIdx_RecdScalOsd_2In1_Out    = COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_OUT;
        ubCompScriptIdx_RecdScalOsd_2In1_InA    = COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INA;
        ubCompScriptIdx_RecdScalOsd_2In1_InB    = COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD_2IN1_INB;

        ubCompScriptIdx_PrevwSrc_2In1_InA       = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN1_INA;//RAWS_CH1->DIP_S10+DIP_S12+DIP_S8+DIP_S0
        ubCompScriptIdx_PrevwSrc_2In1_InB       = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN1_INB;

        ubCompScriptIdx_Prevw_2In1_InA          = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_2IN1_INA;
        ubCompScriptIdx_Prevw_2In1_InB          = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_2IN1_INB;
        if (gbLCDRotate) {
            ubCompScriptIdx_Prevw_2In1_Out      = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_PIP_2IN1_OUT;
        }
        else {
            UartSendTrace(FG_RED("WARNING!!! Not implemented no rotate case for 2In1 preview !!!\r\n"));
            #if 0 //TODO
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_PIP;
            #endif
        }
    }
    else {
        ubPortScriptIdx_RecdSrc_2In1_InA        = PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC_2IN1_INA;      //RAWS_CH1 open port1=DIP_S12
        ubPortScriptIdx_RecdSrc_2In1_InB        = PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC_2IN1_INB;      //RAWS_CH1 open port2=DIP_S13
        ubPortScriptIdx_PrevwSrc_2In1_InA       = PORT_SCRIPT_DSC_PREV_SCD_ANADEC_SRC_2IN1_INA;     //RAWS_CH1 open port1=DIP_S10
        ubPortScriptIdx_PrevwSrc_2In1_InB       = PORT_SCRIPT_DSC_PREV_SCD_ANADEC_SRC_2IN1_INB;     //RAWS_CH2 open port2=DIP_S11
        ubPortScriptIdx_PrevwSrc_Raw1_Fcam      = PORT_SCRIPT_DSC_PREV_PRM_ANADEC_SRC_RAW;           //RAWS_CH1 open port3=DIP_S0

        ubCompScriptIdx_RecdScalOsd_2In1_Out    = COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_OUT;//DIP_S3*RREC->MFE1/JPE4_PRIMARY/DIP_S4_RTHUMB
        ubCompScriptIdx_RecdScalOsd_2In1_InA    = COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INA;//RAWS_CH1<-DIP_S12 ---|
        ubCompScriptIdx_RecdScalOsd_2In1_InB    = COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD_2IN1_INB;//RAWS_CH2<-DIP_S13 ___|--->DIP_S3

        ubCompScriptIdx_PrevwSrc_2In1_InA       = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INA;//RAWS_CH1->DIP_S10/DIP_S12/DIP_S0
        ubCompScriptIdx_PrevwSrc_2In1_InB       = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_SRC_2IN1_INB;//RAWS_CH2->DIP_S11/DIP_S13

        ubCompScriptIdx_Prevw_2In1_InA          = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_2IN1_INA;//RAWS_CH1<-DIP_S10        ---|
        ubCompScriptIdx_Prevw_2In1_InB          = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_2IN1_INB;  //RAWS_CH2<-DIP_S11      ___|--->DIP_S1
        if (gbLCDRotate) {
            ubCompScriptIdx_Prevw_2In1_Out      = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_PIP_2IN1_OUT;//DIP_S1->DIP_S2->DIP_R1->PIP0
        }
        else {
            UartSendTrace(FG_RED("WARNING!!! Not implemented no rotate case for 2In1 preview !!!\r\n"));
            #if 0 //TODO
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_PIP;
            #endif
        }
    }

    if (bEnablePreview) {
        #if (TEST_2IN1_SAME_SOURCE)
        UartSendTrace("MMPS_Display_EnableScdAnaDecSnrPreview_2IN1: TEST_2IN1_SAME_SOURCE\r\n");
        OpenScript(COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN1_TEST);
        #else
        OpenScript(ubCompScriptIdx_PrevwSrc_2In1_InA);
        OpenScript(ubCompScriptIdx_PrevwSrc_2In1_InB);
        #endif

        MMPF_Sensor_SetChannelAttr(SCD_SENSOR, MMP_TRUE); // Set Raw Channel Attribute after RawS component is opened.
        #if (!TEST_2IN1_SAME_SOURCE)
        cameraPreviewSetChannel((u32)RAWS_COMP_IDX2,MMP_TRUE);
        #endif

        OpenScript(ubCompScriptIdx_RecdScalOsd_2In1_Out);
        OpenScript(ubCompScriptIdx_RecdScalOsd_2In1_InA);
        OpenScript(ubCompScriptIdx_RecdScalOsd_2In1_InB);

        OpenScript(ubCompScriptIdx_Prevw_2In1_Out);
        OpenScript(ubCompScriptIdx_Prevw_2In1_InA);
        OpenScript(ubCompScriptIdx_Prevw_2In1_InB);

        #if (TEST_2IN1_SAME_SOURCE)
        //OpenPortScript(PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_TEST); // Useless because OpenPortScript() only can open 1 port
        {
            MMP_COMPONENT_BASE  *pComp = &Component_RawS[RAWS_COMP_IDX];
            pComp->pOutPort[0].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InA]
            pComp->pOutPort[1].State = PORT_OPEN; //RawS --> DIP_Scale[Prev_InB]
            pComp->pOutPort[2].State = PORT_OPEN; //RawS --> DIP_Scale[Recd_InA]
            pComp->pOutPort[3].State = PORT_OPEN; //RawS --> DIP_Scale[Recd_InB]
        }
        #else
        OpenPortScript(ubPortScriptIdx_PrevwSrc_2In1_InA);
        OpenPortScript(ubPortScriptIdx_PrevwSrc_2In1_InB);
        OpenPortScript(ubPortScriptIdx_RecdSrc_2In1_InA);
        OpenPortScript(ubPortScriptIdx_RecdSrc_2In1_InB);
        #endif
        if(MMP_GetANACamType() == ANA_CAM_2I2O){
            OpenPortScript(ubPortScriptIdx_PrevwSrc_Raw1_Fcam);//RAWS_CH1 open portx=DIP_S0
        }
    }
    else {
        #if (TEST_2IN1_SAME_SOURCE)
        //ClosePortScript(PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC_2IN1_TEST);
        {
            MMP_COMPONENT_BASE  *pComp = &Component_RawS[RAWS_COMP_IDX];
            pComp->pOutPort[0].State = PORT_CLOSE; //RawS --> DIP_Scale[Prev_InA]
            pComp->pOutPort[1].State = PORT_CLOSE; //RawS --> DIP_Scale[Prev_InB]
            pComp->pOutPort[2].State = PORT_CLOSE; //RawS --> DIP_Scale[Recd_InA]
            pComp->pOutPort[3].State = PORT_CLOSE; //RawS --> DIP_Scale[Recd_InB]
        }
        #else
        cameraPreviewSetChannel((u32)RAWS_COMP_IDX2,MMP_FALSE);
        ClosePortScript(ubPortScriptIdx_PrevwSrc_2In1_InA);
        ClosePortScript(ubPortScriptIdx_PrevwSrc_2In1_InB);
        ClosePortScript(ubPortScriptIdx_RecdSrc_2In1_InA);
        ClosePortScript(ubPortScriptIdx_RecdSrc_2In1_InB);
        #endif

        if(MMP_GetANACamType() == ANA_CAM_2I2O){
            ClosePortScript(ubPortScriptIdx_PrevwSrc_Raw1_Fcam);//RAWS_CH1 close port4=DIP_S0
        }

        CloseScript(ubCompScriptIdx_Prevw_2In1_Out);
        CloseScript(ubCompScriptIdx_Prevw_2In1_InA);
        CloseScript(ubCompScriptIdx_Prevw_2In1_InB);

        CloseScript(ubCompScriptIdx_RecdScalOsd_2In1_Out);
        CloseScript(ubCompScriptIdx_RecdScalOsd_2In1_InA);
        CloseScript(ubCompScriptIdx_RecdScalOsd_2In1_InB);

        #if (TEST_2IN1_SAME_SOURCE)
        CloseScript(COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC_2IN1_TEST);
        #else
        CloseScript(ubCompScriptIdx_PrevwSrc_2In1_InA);
        CloseScript(ubCompScriptIdx_PrevwSrc_2In1_InB);
        #endif
    }

    return MMP_ERR_NONE;
}

MMP_ERR MMPS_Display_EnableScdAnaDecSnrPreview_Normal(MMP_UBYTE ubUiMode, MMP_BOOL bEnablePreview)
{
    MMP_UBYTE ubCompScriptIdx_RecdScalOsd   = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_PrevwSrc      = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_PrevwFull     = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_PrevwPip      = COMPO_SCRIPT_INVALID;

    MMP_UBYTE ubPortScriptIdx_RecdSrc       = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_PrevwSrc      = PORT_SCRIPT_INVALID;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        ubPortScriptIdx_RecdSrc         = PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC;
        ubPortScriptIdx_PrevwSrc        = PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC;

        ubCompScriptIdx_RecdScalOsd     = COMPO_SCRIPT_VR_SCD_ANADEC_RECD_SCAL_OSD;

        if (gbLCDRotate) {
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_VR_R_PREV_SCD_ANADEC_PIP;
        }
        else {
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_VR_N_PREV_SCD_ANADEC_PIP;
        }
    }
    else {
        ubPortScriptIdx_RecdSrc         = PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC;
        ubPortScriptIdx_PrevwSrc        = PORT_SCRIPT_DSC_PREV_SCD_ANADEC_SRC;

        ubCompScriptIdx_RecdScalOsd     = COMPO_SCRIPT_DSC_SCD_ANADEC_CAPT_SCAL_OSD;

        if (gbLCDRotate) {
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_DSC_R_PREV_SCD_ANADEC_PIP;
        }
        else {
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_DSC_N_PREV_SCD_ANADEC_PIP;
        }
    }

    if (bEnablePreview) {

        OpenScript(ubCompScriptIdx_PrevwSrc);
        MMPF_Sensor_SetChannelAttr(SCD_SENSOR, MMP_TRUE); // Set Raw Channel Attribute after RawS component is opened.
        OpenScript(ubCompScriptIdx_RecdScalOsd);
        OpenPortScript(ubPortScriptIdx_RecdSrc);

        OpenScript(ubCompScriptIdx_PrevwPip);
        OpenPortScript(ubPortScriptIdx_PrevwSrc);
    }
    else {

        ClosePortScript(ubPortScriptIdx_PrevwSrc);
        CloseScript(ubCompScriptIdx_PrevwFull);
        CloseScript(ubCompScriptIdx_PrevwPip);

        ClosePortScript(ubPortScriptIdx_RecdSrc);
        CloseScript(ubCompScriptIdx_RecdScalOsd);
        CloseScript(ubCompScriptIdx_PrevwSrc);
    }

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_Display_EnableScdAnaDecSnrPreview
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_EnableScdAnaDecSnrPreview(MMP_UBYTE ubUiMode, MMP_BOOL bEnablePreview)
{
    if (MMP_GetANACamType() == ANA_CAM_2I1O){
        Component_RearCam_2In1_Enable( MMP_TRUE );
        return MMPS_Display_EnableScdAnaDecSnrPreview_2IN1( ubUiMode, bEnablePreview );
    }else if(MMP_GetANACamType() == ANA_CAM_2I2O){
        return MMPS_Display_EnableScdAnaDecSnrPreview_2IN2OUT( ubUiMode, bEnablePreview );
    }else{
        MMPS_Display_EnableScdAnaDecSnrPreview_Normal( ubUiMode, bEnablePreview );
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_EnableScdAnaDecSnrPreviewWindow
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_EnableScdAnaDecSnrPreviewWindow(MMP_UBYTE ubUiMode, MMP_BOOL bEnablePreview)
{
    MMP_UBYTE ubPortScriptIdx_RecdSrc       = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_PrevwSrc      = PORT_SCRIPT_INVALID;
    MMP_UBYTE ubPortScriptIdx_PrevwSrc2     = PORT_SCRIPT_INVALID;

    if(MMP_GetANACamType() == ANA_CAM_2I2O){
        //Fcam
        ubPortScriptIdx_PrevwSrc    = PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW1;              //RAWS_CH1 open port0=DIP_S0    display fcam
        ubPortScriptIdx_PrevwSrc2   = PORT_SCRIPT_VR_PREV_PRM_ANADEC_SRC_RAW2;              //RAWS_CH2 open port0=DIP_S1    display rcam
        ubPortScriptIdx_RecdSrc     = PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC_2IN2_RAW2;          //RAWS_CH2 open port1=DIP_S3   record
        UartSendTrace(BG_BLUE("2IN2O TODO:%s,%d\n"),__FUNCTION__, __LINE__);
    }
    else{
        if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
            ubPortScriptIdx_RecdSrc     = PORT_SCRIPT_VR_SCD_ANADEC_RECD_SRC;
            ubPortScriptIdx_PrevwSrc    = PORT_SCRIPT_VR_PREV_SCD_ANADEC_SRC;
        }
        else {
            ubPortScriptIdx_RecdSrc     = PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_SRC;
            ubPortScriptIdx_PrevwSrc    = PORT_SCRIPT_DSC_PREV_SCD_ANADEC_SRC;
        }
    }

    if (bEnablePreview) {
        OpenPortScript(ubPortScriptIdx_RecdSrc);
        OpenPortScript(ubPortScriptIdx_PrevwSrc);
        if(MMP_GetANACamType() == ANA_CAM_2I2O)
            OpenPortScript(ubPortScriptIdx_PrevwSrc2);

    }
    else {
        ClosePortScript(ubPortScriptIdx_PrevwSrc);
        ClosePortScript(ubPortScriptIdx_RecdSrc);
        if(MMP_GetANACamType() == ANA_CAM_2I2O)
            ClosePortScript(ubPortScriptIdx_PrevwSrc2);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_EnableScdBayerSnrPreview
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_EnableScdBayerSnrPreview(MMP_UBYTE ubUiMode, MMP_BOOL bEnablePreview)
{
    MMP_UBYTE ubCompScriptIdx_PrevwSrc      = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_PrevwFull     = COMPO_SCRIPT_INVALID;
    MMP_UBYTE ubCompScriptIdx_PrevwPip      = COMPO_SCRIPT_INVALID;

    MMP_UBYTE ubPortScriptIdx_PrevwBayer    = PORT_SCRIPT_INVALID;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {

        ubPortScriptIdx_PrevwBayer      = PORT_SCRIPT_VR_PREV_SCD_BAYER;

        if (gbLCDRotate) {
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_VR_R_PREV_SCD_BAYER_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_VR_R_PREV_SCD_BAYER_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_VR_R_PREV_SCD_BAYER_PIP;
        }
        else {
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_VR_N_PREV_SCD_BAYER_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_VR_N_PREV_SCD_BAYER_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_VR_N_PREV_SCD_BAYER_PIP;
        }
    }
    else {
        ubPortScriptIdx_PrevwBayer      = PORT_SCRIPT_DSC_PREV_SCD_BAYER;

        if (gbLCDRotate) {
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_DSC_R_PREV_SCD_BAYER_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_DSC_R_PREV_SCD_BAYER_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_DSC_R_PREV_SCD_BAYER_PIP;
        }
        else {
            #if 0 // TODO jeff
            ubCompScriptIdx_PrevwSrc    = COMPO_SCRIPT_DSC_N_PREV_SCD_BAYER_SRC;
            ubCompScriptIdx_PrevwFull   = COMPO_SCRIPT_DSC_N_PREV_SCD_BAYER_FULL;
            ubCompScriptIdx_PrevwPip    = COMPO_SCRIPT_DSC_N_PREV_SCD_BAYER_PIP;
            #endif
        }
    }

    if (bEnablePreview) {
        OpenScript(ubCompScriptIdx_PrevwSrc);
        OpenScript(ubCompScriptIdx_PrevwPip);

        OpenPortScript(ubPortScriptIdx_PrevwBayer);
    }
    else {
        ClosePortScript(ubPortScriptIdx_PrevwBayer);

        CloseScript(ubCompScriptIdx_PrevwFull);
        CloseScript(ubCompScriptIdx_PrevwPip);
        CloseScript(ubCompScriptIdx_PrevwSrc);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetPrmCropWinAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetPrmCropWinAttr(MMP_UBYTE ubUiMode, MMP_LONG lStepX, MMP_LONG lStepY)
{
    MMP_ULONG   ulInW = 0, ulInH = 0;
    MMP_LONG    lCropX = 0, lCropY = 0;
    MMP_ULONG   ulCropW = 0, ulCropH = 0;
    MMP_LONG    lNewCropX = 0, lNewCropY = 0;
    MMP_UBYTE   ubDipRUseIdx = 0;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        ubDipRUseIdx = DIP_R_COMP_VR_FCAM_PREVIEW;
    }
    else {
        ubDipRUseIdx = DIP_R_COMP_DSC_FCAM_PREVIEW;
    }

    if (gbLCDRotate) {
        MMPD_Fctl_GetDIPCompWin( DIP_COMP_TYPE_ID_ROT,
                                 ubDipRUseIdx,
                                 NULL, NULL, &ulInW, &ulInH,
                                 &lCropX, &lCropY, &ulCropW, &ulCropH);

        lNewCropX = lCropX + lStepX;
        if (lNewCropX < 0) {
            lNewCropX = 0;
        }
        else if (lNewCropX + ulCropW > ulInW) {
            lNewCropX = ulInW - ulCropW;
        }

        lNewCropY = lCropY + lStepY;
        if (lNewCropY < 0) {
            lNewCropY = 0;
        }
        else if (lNewCropY + ulCropH > ulInH) {
            lNewCropY = ulInH - ulCropH;
        }

        MMPD_Fctl_SetDIPCompCropWin( DIP_COMP_TYPE_ID_ROT,
                                     ubDipRUseIdx,
                                     lNewCropX, lNewCropY, ulCropW, ulCropH);
    }
    else {
        // TBD
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetScdCropWinAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetScdCropWinAttr(MMP_UBYTE ubUiMode, MMP_LONG lStepX, MMP_LONG lStepY)
{
    MMP_ULONG   ulInW = 0, ulInH = 0;
    MMP_LONG    lCropX = 0, lCropY = 0;
    MMP_ULONG   ulCropW = 0, ulCropH = 0;
    MMP_LONG    lNewCropX = 0, lNewCropY = 0;
    MMP_UBYTE   ubDipSUseIdx = 0;

    if (ubUiMode == MMPS_PREVIEW_UI_MODE_VR) {
        ubDipSUseIdx = DIP_S_COMP_VR_RCAM_PREVIEW;
    }
    else {
        ubDipSUseIdx = DIP_S_COMP_DSC_RCAM_PREVIEW;
    }

    MMPD_Fctl_GetDIPCompWin( DIP_COMP_TYPE_ID_SCL,
                             ubDipSUseIdx,
                             NULL, NULL, &ulInW, &ulInH,
                             &lCropX, &lCropY, &ulCropW, &ulCropH);

    lNewCropX = lCropX + lStepX;
    if (lNewCropX < 0) {
        lNewCropX = 0;
    }
    else if (lNewCropX + ulCropW > ulInW) {
        lNewCropX = ulInW - ulCropW;
    }

    lNewCropY = lCropY + lStepY;
    if (lNewCropY < 0) {
        lNewCropY = 0;
    }
    else if (lNewCropY + ulCropH > ulInH) {
        lNewCropY = ulInH - ulCropH;
    }

    MMPD_Fctl_SetDIPCompCropWin( DIP_COMP_TYPE_ID_SCL,
                                 ubDipSUseIdx,
                                 lNewCropX, lNewCropY, ulCropW, ulCropH);

    return MMP_ERR_NONE;
}

#if 0
void ____Ratio_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_GetDevWidthHeight
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_GetDevWidthHeight( MMP_DISPLAY_OUTPUT_SEL  ePanelType,
                                        MMP_ULONG               *pulWidth,
                                        MMP_ULONG               *pulHeight)
{
    switch (ePanelType) {
    case MMP_DISPLAY_SEL_MAIN_LCD:
        if (gbLCDRotate) {
            *pulWidth       = m_displayConfig.mainlcd.usHeight;
            *pulHeight      = m_displayConfig.mainlcd.usWidth;
        }
        else {
            *pulWidth       = m_displayConfig.mainlcd.usWidth;
            *pulHeight      = m_displayConfig.mainlcd.usHeight;
        }
        break;
    case MMP_DISPLAY_SEL_SUB_LCD:
        if (gbLCDRotate) {
            *pulWidth       = m_displayConfig.sublcd.usHeight;
            *pulHeight      = m_displayConfig.sublcd.usWidth;
        }
        else {
            *pulWidth       = m_displayConfig.sublcd.usWidth;
            *pulHeight      = m_displayConfig.sublcd.usHeight;
        }
        break;
    case MMP_DISPLAY_SEL_NTSC_TV:
        *pulWidth           = m_displayConfig.ntsctv.usDisplayWidth;
        *pulHeight          = m_displayConfig.ntsctv.usDisplayHeight;
        break;
    case MMP_DISPLAY_SEL_PAL_TV:
        *pulWidth           = m_displayConfig.paltv.usDisplayWidth;
        *pulHeight          = m_displayConfig.paltv.usDisplayHeight;
        break;
    case MMP_DISPLAY_SEL_HDMI:
        *pulWidth           = m_displayConfig.hdmi.usDisplayWidth;
        *pulHeight          = m_displayConfig.hdmi.usDisplayHeight;
        break;
    case MMP_DISPLAY_SEL_CCIR:
        *pulWidth           = m_displayConfig.ccir.usDisplayWidth;
        *pulHeight          = m_displayConfig.ccir.usDisplayHeight;
        break;
    default:
        return MMP_DISPLAY_ERR_NOT_SUPPORT;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_GetPixelXYRatio
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_GetPixelXYRatio(MMP_DISPLAY_OUTPUT_SEL PanelType,
                                     MMP_ULONG      *ulXRatio,  MMP_ULONG *ulYRatio,
                                     MMP_ULONG      *ulWidth,   MMP_ULONG *ulHeight,
                                     MMP_ULONG64    *ulPixelWidth,
                                     MMP_BOOL       *bRotateVerticalLCD)
{
    switch (PanelType) {
    case MMP_DISPLAY_SEL_MAIN_LCD:
        if (m_displayConfig.mainlcd.bRotateVerticalLCD) {
            *ulXRatio   = m_displayConfig.mainlcd.ulPanelYratio;
            *ulYRatio   = m_displayConfig.mainlcd.ulPanelXratio;
            *ulWidth    = m_displayConfig.mainlcd.usHeight;
            *ulHeight   = m_displayConfig.mainlcd.usWidth;
        }
        else {
            *ulXRatio   = m_displayConfig.mainlcd.ulPanelXratio;
            *ulYRatio   = m_displayConfig.mainlcd.ulPanelYratio;
            *ulWidth    = m_displayConfig.mainlcd.usWidth;
            *ulHeight   = m_displayConfig.mainlcd.usHeight;
        }
        *ulPixelWidth       = ((*ulXRatio * (*ulHeight)) << 16) / (*ulYRatio * (*ulWidth));
        *bRotateVerticalLCD = m_displayConfig.mainlcd.bRotateVerticalLCD;
        break;
    case MMP_DISPLAY_SEL_SUB_LCD:
        if (m_displayConfig.sublcd.bRotateVerticalLCD) {
            *ulXRatio   = m_displayConfig.sublcd.ulPanelYratio;
            *ulYRatio   = m_displayConfig.sublcd.ulPanelXratio;
            *ulWidth    = m_displayConfig.sublcd.usHeight;
            *ulHeight   = m_displayConfig.sublcd.usWidth;
        }
        else {
            *ulXRatio   = m_displayConfig.sublcd.ulPanelXratio;
            *ulYRatio   = m_displayConfig.sublcd.ulPanelYratio;
            *ulWidth    = m_displayConfig.sublcd.usWidth;
            *ulHeight   = m_displayConfig.sublcd.usHeight;
        }
        *ulPixelWidth       = ((*ulXRatio * (*ulHeight)) << 16) / (*ulYRatio * (*ulWidth));
        *bRotateVerticalLCD = m_displayConfig.sublcd.bRotateVerticalLCD;
        break;
    case MMP_DISPLAY_SEL_NTSC_TV:
        *ulXRatio           = 3;
        *ulYRatio           = 2;
        *ulWidth            = m_displayConfig.ntsctv.usDisplayWidth;
        *ulHeight           = m_displayConfig.ntsctv.usDisplayHeight;
        *ulPixelWidth       = 1 << 16;
        *bRotateVerticalLCD = MMP_FALSE;
        break;
    case MMP_DISPLAY_SEL_PAL_TV:
        *ulXRatio           = 5;
        *ulYRatio           = 4;
        *ulWidth            = m_displayConfig.paltv.usDisplayWidth;
        *ulHeight           = m_displayConfig.paltv.usDisplayHeight;
        *ulPixelWidth       = 1 << 16;
        *bRotateVerticalLCD = MMP_FALSE;
        break;
    case MMP_DISPLAY_SEL_HDMI:
        *ulXRatio           = 16;
        *ulYRatio           = 9;
        *ulWidth            = m_displayConfig.hdmi.usDisplayWidth;
        *ulHeight           = m_displayConfig.hdmi.usDisplayHeight;
        *ulPixelWidth       = 1 << 16;
        *bRotateVerticalLCD = MMP_FALSE;
        break;
    case MMP_DISPLAY_SEL_CCIR:
        *ulXRatio           = 3;
        *ulYRatio           = 2;
        *ulWidth            = m_displayConfig.ccir.usDisplayWidth;
        *ulHeight           = m_displayConfig.ccir.usDisplayHeight;
        *ulPixelWidth       = 1 << 16;
        *bRotateVerticalLCD = MMP_FALSE;
        break;
    default:
        return MMP_DISPLAY_ERR_NOT_SUPPORT;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_CheckPixelRatio
//  Description : Check if panel pixel is square or not. And get the pixel width-height ratio.
//------------------------------------------------------------------------------
/**
@brief Check if panel pixel is square or not

@param[in]  controller    the display controller
@param[out] bSquarePixel  Square pixel or not
@param[out] ulPixelWidth  XY ratio 16.16
*/
MMP_ERR MMPS_Display_CheckPixelRatio(MMP_DISPLAY_CONTROLLER controller, MMP_BOOL *bSquarePixel, MMP_ULONG *ulPixelWidth)
{
    MMP_ULONG                   ulPanelXratio       = m_displayConfig.mainlcd.ulPanelXratio;
    MMP_ULONG                   ulPanelYratio       = m_displayConfig.mainlcd.ulPanelYratio;
    MMP_ULONG                   panel_width         = m_displayConfig.mainlcd.usWidth;
    MMP_ULONG                   panel_height        = m_displayConfig.mainlcd.usHeight;
    MMP_ULONG64                 pixel_width         = ((ulPanelXratio * panel_height) << 16) / (ulPanelYratio * panel_width);
    MMP_BOOL                    bRotateVerticalLCD  = m_displayConfig.mainlcd.bRotateVerticalLCD;
    MMP_DISPLAY_OUTPUT_SEL      displaypanel        = m_displayCurOutput[controller];

    MMPS_Display_GetPixelXYRatio(displaypanel, &ulPanelXratio, &ulPanelYratio, &panel_width, &panel_height, &pixel_width, &bRotateVerticalLCD);

    if (pixel_width == (1 << 16)) {
        *bSquarePixel = MMP_TRUE;
    }
    else {
        *bSquarePixel = MMP_FALSE;
    }
    *ulPixelWidth = (MMP_ULONG)pixel_width;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_AdjustScaleInSize
//  Description : According to the given input buffer width/height and the requested display width/height,
//                calculate the suggest width/height for the display buffer
//------------------------------------------------------------------------------
/**
@brief     According to the given input buffer width/height and the requested display width/height,
           calculate the suggest width/height for the display buffer

@param[in]  controller      the display controller
@param[in]  InputWidth      Input buffer width
@param[in]  InputHeight     Input buffer height
@param[in]  RequiredWidth   Required display width
@param[in]  RequiredHeight  Required display height
@param[out] SuggestWidth    Suggest buffer width
@param[out] SuggestHeight   Suggest buffer height
*/
MMP_ERR MMPS_Display_AdjustScaleInSize( MMP_DISPLAY_CONTROLLER  controller,
                                        MMP_ULONG               InputWidth,
                                        MMP_ULONG               InputHeight,
                                        MMP_ULONG               RequiredWidth,
                                        MMP_ULONG               RequiredHeight,
                                        MMP_ULONG               *SuggestWidth,
                                        MMP_ULONG               *SuggestHeight)
{
    MMP_ULONG                   ulPanelXratio       = m_displayConfig.mainlcd.ulPanelXratio;
    MMP_ULONG                   ulPanelYratio       = m_displayConfig.mainlcd.ulPanelYratio;
    MMP_ULONG                   panel_width         = m_displayConfig.mainlcd.usWidth;
    MMP_ULONG                   panel_height        = m_displayConfig.mainlcd.usHeight;
    MMP_ULONG64                 pixel_width         = ((ulPanelXratio * panel_height) << 16) / (ulPanelYratio * panel_width);
    MMP_BOOL                    bRotateVerticalLCD  = m_displayConfig.mainlcd.bRotateVerticalLCD;
    MMP_DISPLAY_OUTPUT_SEL      displaypanel        = MMP_DISPLAY_SEL_MAIN_LCD;//m_displayCurOutput[controller];

    MMPS_Display_GetPixelXYRatio(displaypanel, &ulPanelXratio, &ulPanelYratio, &panel_width, &panel_height, &pixel_width, &bRotateVerticalLCD);

    switch(displaypanel)
    {
        case MMP_DISPLAY_SEL_MAIN_LCD:
        case MMP_DISPLAY_SEL_SUB_LCD:
            *SuggestWidth  = ((RequiredWidth * InputWidth * ulPanelYratio) / (InputHeight * ulPanelXratio)) & 0xFFFFFFFE;
            *SuggestHeight = RequiredHeight & 0xFFFFFFFE;

            if (*SuggestWidth > RequiredWidth) {
                *SuggestWidth  = RequiredWidth & 0xFFFFFFFE;
                *SuggestHeight = ((RequiredHeight * InputHeight * ulPanelXratio) / (InputWidth * ulPanelYratio)) & 0xFFFFFFFE;
            }
        break;
        case MMP_DISPLAY_SEL_NTSC_TV:
        case MMP_DISPLAY_SEL_PAL_TV:
        case MMP_DISPLAY_SEL_HDMI:
        case MMP_DISPLAY_SEL_CCIR:
            *SuggestWidth  = RequiredWidth & 0xFFFFFFFE;
            *SuggestHeight = RequiredHeight & 0xFFFFFFFE;
        break;
        default:
        return MMP_DISPLAY_ERR_NOT_SUPPORT;
    }

    #if defined(ALL_FW) && defined(SCAL_FUNC_DBG)
    {
    extern void printc( char* szFormat, ... );

    printc("%s,IW:%d,IH:%d,RW:%d,RH:%d,SW:%d,SH:%d\r\n",
            __func__, InputWidth, InputHeight, RequiredWidth, RequiredHeight, *SuggestWidth, *SuggestHeight);
    }
    #endif

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_PureAdjustScaleInSize
//  Description : According to the given input buffer width/height and the requested display width/height,
//                calculate the suggest width/height for the buffer independ display device
//------------------------------------------------------------------------------
/**
@brief     According to the given input buffer width/height and the requested display width/height,
           calculate the suggest width/height for the buffer independ display device

@param[in]  bScaleUpAvail   Can use the scaler or not
@param[in]  InputWidth      Input buffer width
@param[in]  InputHeight     Input buffer height
@param[in]  RequiredWidth   Required display width
@param[in]  RequiredHeight  Required display height
@param[out] SuggestWidth    Suggest buffer width
@param[out] SuggestHeight   Suggest buffer height
*/
MMP_ERR MMPS_Display_PureAdjustScaleInSize( MMP_BOOL    bScaleUpAvail,
                                            MMP_ULONG   InputWidth,
                                            MMP_ULONG   InputHeight,
                                            MMP_ULONG   RequiredWidth,
                                            MMP_ULONG   RequiredHeight,
                                            MMP_ULONG   *SuggestWidth,
                                            MMP_ULONG   *SuggestHeight)
{
    if (InputHeight == 1088) {
        InputHeight = 1080; // For keep 1920 X 1080 16 : 9 ratio
    }

    if ((InputWidth * RequiredHeight) >= (InputHeight * RequiredWidth)) {
        // 16:9 => 4:3 or same ratio => fit width
        if (InputWidth >= RequiredWidth) {
            *SuggestWidth = ALIGN16(RequiredWidth & ~(1));
            *SuggestHeight = (*SuggestWidth * InputHeight / InputWidth) & ~(1);
        }
        else {
            if (bScaleUpAvail) {
                *SuggestWidth = ALIGN16(RequiredWidth & ~(1));
                *SuggestHeight = (*SuggestWidth * InputHeight / InputWidth) & ~(1);
            }
            else {
                *SuggestWidth = ALIGN16(InputWidth & ~(1));
                *SuggestHeight = InputHeight & ~(1);
            }
        }
    }
    else
    {
        // 4:3 => 16:9 => fit height
        if (InputHeight >= RequiredHeight) {
            *SuggestHeight = RequiredHeight & ~(1);
            *SuggestWidth = ALIGN16((*SuggestHeight * InputWidth / InputHeight) & ~(1));
        }
        else {
            if (bScaleUpAvail) {
                *SuggestHeight = RequiredHeight & ~(1);
                *SuggestWidth = ALIGN16((*SuggestHeight * InputWidth / InputHeight) & ~(1));
            }
            else {
                *SuggestWidth = ALIGN16(InputWidth & ~(1));
                *SuggestHeight = InputHeight & ~(1);
            }
        }
    }

    return MMP_ERR_NONE;
}

#if 0
void ____CCIR_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_CCIR_SetDisplayBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_CCIR_SetDisplayBuf(MMP_ULONG ulBaseAddr)
{
    return MMPD_CCIR_SetDisplayBufAddr(ulBaseAddr);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_CCIR_SetDisplayRefresh
//  Description :
//------------------------------------------------------------------------------
/** @brief Enable display refresh

The function check if CCIR output is enabled. If not, CCIR output will be
enabled. Otherwise, do nothing.

@return It reports the status of the operation.
*/
MMP_ERR MMPS_CCIR_SetDisplayRefresh(void)
{
    return MMPD_CCIR_SetDisplayRefresh();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_CCIR_DisableDisplay
//  Description :
//------------------------------------------------------------------------------
/** @brief Disable CCIR display refresh

The function disables the CCIR display.

@return It reports the status of the operation.
*/
MMP_ERR MMPS_CCIR_DisableDisplay(void)
{
    return MMPD_CCIR_DisableDisplay();
}

#if 0
void ____Component_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetDispCompAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetDispCompAttr(   MMP_ULONG ulInX,    MMP_ULONG ulInY,    MMP_ULONG ulInW,    MMP_ULONG ulInH,
                                        MMP_ULONG ulCropX,  MMP_ULONG ulCropY,  MMP_ULONG ulCropW,  MMP_ULONG ulCropH,
                                        MMP_ULONG ulOutX,   MMP_ULONG ulOutY,   MMP_ULONG ulOutW,    MMP_ULONG ulOutH,
                                        MMP_ULONG ulBkColorX, MMP_ULONG ulBkColorY, MMP_ULONG ulBkColorW, MMP_ULONG ulBkColorH,
                                        MMP_BOOL bSclHBypass, MMP_BOOL bSclVBypass)
{
    MMP_ERR              eRetErr = MMP_ERR_NONE;
    DISPLAY_COMP_RECT    stDispRect;
    DISPLAY_COMP_SCL_CFG stDispSclCfg;
    void                 *pvHandler;

    pvHandler = &Component_Display;

    stDispRect.ulX = ulInX;
    stDispRect.ulY = ulInY;
    stDispRect.ulW = ulInW;
    stDispRect.ulH = ulInH;
    eRetErr |= Component_Display_SetParameter(pvHandler, DISPLAY_COMP_PARAM_IN_RECT, &stDispRect);

    stDispRect.ulX = ulCropX;
    stDispRect.ulY = ulCropY;
    stDispRect.ulW = ulCropW;
    stDispRect.ulH = ulCropH;
    eRetErr |= Component_Display_SetParameter(pvHandler, DISPLAY_COMP_PARAM_CROP_RECT, &stDispRect);

    stDispRect.ulX = ulOutX;
    stDispRect.ulY = ulOutY;
    stDispRect.ulW = ulOutW;
    stDispRect.ulH = ulOutH;
    eRetErr |= Component_Display_SetParameter(pvHandler, DISPLAY_COMP_PARAM_OUT_RECT, &stDispRect);

    stDispRect.ulX = ulBkColorX;
    stDispRect.ulY = ulBkColorY;
    stDispRect.ulW = ulBkColorW;
    stDispRect.ulH = ulBkColorH;
    eRetErr |= Component_Display_SetParameter(pvHandler, DISPLAY_COMP_PARAM_BK_COLOR_RECT, &stDispRect);

    stDispSclCfg.bSclHBypass = bSclHBypass;
    stDispSclCfg.bSclVBypass = bSclVBypass;
    eRetErr |= Component_Display_SetParameter(pvHandler, DISPLAY_COMP_PARAM_SCL_CFG, &stDispSclCfg);

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Display_SetPIPCompAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Display_SetPIPCompAttr(MMP_UBYTE ubPipUseIdx,
                                    MMP_ULONG ulFgX, MMP_ULONG ulFgY, MMP_ULONG ulFgW, MMP_ULONG ulFgH,
                                    MMP_ULONG ulBgX, MMP_ULONG ulBgY, MMP_ULONG ulBgW, MMP_ULONG ulBgH,
                                    MMP_BOOL  bHMirror, MMP_BOOL bVFlip)
{
    MMP_ERR         eRetErr = MMP_ERR_NONE;
    PIP_COMP_RECT   stPipRect;

    stPipRect.ulX = ulFgX;
    stPipRect.ulY = ulFgY;
    stPipRect.ulW = ulFgW;
    stPipRect.ulH = ulFgH;
    eRetErr |= Component_PIP_SetParam(&Component_PIP[ubPipUseIdx], PIP_COMP_PARAM_FG_RECT, (void*)&stPipRect);

    stPipRect.ulX = ulBgX;
    stPipRect.ulY = ulBgY;
    stPipRect.ulW = ulBgW;
    stPipRect.ulH = ulBgH;
    eRetErr |= Component_PIP_SetParam(&Component_PIP[ubPipUseIdx], PIP_COMP_PARAM_BG_RECT, (void*)&stPipRect);

    eRetErr |= Component_PIP_SetParam(&Component_PIP[ubPipUseIdx], PIP_COMP_PARAM_H_MIRROR, (void*)&bHMirror);
    eRetErr |= Component_PIP_SetParam(&Component_PIP[ubPipUseIdx], PIP_COMP_PARAM_V_FLIP, (void*)&bVFlip);

    return eRetErr;
}
