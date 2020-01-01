//==============================================================================
//
//  File        : AHC_GUI.c
//  Description : AHC GUI function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "Customer_config.h"

#include "GUI.h"
#include "ait_utility.h"
#include "mmps_display.h"
#include "mmp_display_inc.h"
#include "mmps_dma.h"
#include "mmps_system.h"
#include "mmps_vidplay.h"
#include "ahc_gui.h"
#include "ahc_os.h"
#include "ahc_hdmi.h"
#include "ahc_display.h"
#include "ahc_parameter.h"
#include "aihc_gui.h"
#include "MenuSetting.h"
#include "disp_drv.h"
#if !defined(UPDATER_FW) // for CarDV memory mapping
#include "cdvmem.h"
#endif
#include "drv_bdma_pub_api.h"
#include "drv_bdma_pub_types.h"
#include "drv_bdma_pub_forward.h"
#include "mmu.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

// 2 for Thumbnail, 2 for JPEG date
#define MAX_OSD_LAYER       (MAX_OSD_NUM + 8)//(MAX_OSD_NUM + 4)

#define GUI_SEM_WAIT_TIME   (Sleep_MS(500))

#define AHC_GUI_DEBUG       (0)


typedef void (*AHC_OSD_InitOSDCustomCB)(U32 colorFormat, AHC_OSD_ROTATE_DRAW_MODE ahcOSDRotateDraw);

/*===========================================================================
 * Global variable
 *===========================================================================*/

AHC_OSD_INSTANCE        *m_OSD[MAX_OSD_LAYER]   = {0};
static AHC_BOOL         m_bOSDConfig[MAX_OSD_LAYER];
static UINT32           m_StickerPalette[]      = {0x000000, 0xFF8000, 0xFF0000, 0x0000FF}; // Transparent, Orange, Red, Blue (Format: RGB32)

/*
Display ID is between 0 and 15.
*/
static UINT32           m_ulOSDLayer1BufAddr    = 0x00000000;
static INT32            m_lCurrentLayer1ID      = -1;
/*
Display ID is between 16 and 31.
*/
static UINT32           m_ulOSDLayer2BufAddr    = 0x00000000;
static INT32            m_lCurrentLayer2ID      = -1;
/*
Display ID is large than 31.
*/
static UINT32           m_ulOSDLayer3BufAddr    = 0x00000000;
static INT32            m_lCurrentLayer3ID      = -1;

static UINT32           m_ulInitGUI             = 0;

/*
AHC_OSDInit() resets this paramter.
AHC_OSDCreateBuffer() increases this parameter.
AHC_OSDDestroyBuffer() decreases this parameter.
*/
static UINT32           m_ulOSDLayerCount       = 0;

static UINT32           m_ulCurrentOSDID        = 0;
static AHC_BOOL         m_bDrawReserved         = AHC_FALSE;
static AHC_BOOL         m_OSDUpdateAddrOnly     = AHC_FALSE;

static AHC_OS_SEMID     m_GUIDMASemID           = -1;
static AHC_OS_SEMID     m_GUISemID              = -1;

//#define BEGIN_GUI_DRAW(id)    AIHC_GUILock(id, __MODULE__, __LINE__)
#define BEGIN_GUI_DRAW(id)  AIHC_GUILock(id, __FILE__, __LINE__)

#define END_GUI_DRAW(id)    AIHC_GUIUnLock(id, __FILE__, __LINE__)
//#define BEGIN_GUI_DRAW(id)    AIHC_GUILock(id, __FILE__, __LINE__)

static volatile MMP_BOOL m_bGUIDMADone = MMP_FALSE;

AHC_OSD_InitOSDCustomCB gAHC_OSD_InitOSDCustomCB = NULL;
AHC_OS_SEMID gulDrawingSemID = -1;

/*===========================================================================
 * Extern varible
 *===========================================================================*/
extern AHC_BOOL         gbAhcDbgBrk;
//extern AHC_BOOL           bHaveInitOsdHdmi;

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void _____Internal_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AIHC_GUILock
//  Description :
//------------------------------------------------------------------------------
static void AIHC_GUILock(MMP_USHORT id, char* func, MMP_LONG line)
{
    if (m_OSD[id]) {

        if (AHC_OS_AcquireSem(m_GUISemID, GUI_SEM_WAIT_TIME) != MMPF_OS_ERR_NONE) {
            UartSendTrace("ASSERT:%s %d GUI LOCKED\r\n", func, line);
        }

//        GUI_SetRotateDrawMode(m_OSD[id]->gui.ulRotateByGUI);
//        GUI_SetFlipDrawMode(m_OSD[id]->gui.ulFlipByGUI);

        GUI_SetColor(m_OSD[id]->gui.gui_fnclr);

        if (sizeof(GUI_COLOR) == 4) {
            GUI_SetAlphaValue(m_OSD[id]->gui.gui_fnclr >> 24);
        }

        GUI_SetBkColor(m_OSD[id]->gui.gui_bkclr);
        GUI_SetFont(m_OSD[id]->gui.gui_pfont);
        GUI_SetPenSize(m_OSD[id]->gui.gui_pen);

    }
}

//------------------------------------------------------------------------------
//  Function    : AIHC_GUIUnLock
//  Description :
//------------------------------------------------------------------------------
static void AIHC_GUIUnLock(MMP_USHORT id, char* func, MMP_LONG line)
{
    if (m_OSD[id]) {

        if (AHC_OS_ReleaseSem(m_GUISemID) != MMPF_OS_ERR_NONE) {
            UartSendTrace("ASSERT:%s %d GUI UNLOCKED\r\n", func, line);
        }
    }
}

//------------------------------------------------------------------------------
//  Function    : AIHC_GetOSDInitStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AIHC_GetOSDInitStatus(void)
{
    return m_ulInitGUI;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_GUIMalloc
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Allocate memory pool for GUI APIs
    @param[in] ptr memory pointer
    @return MMP_ERR_NONE
*/
static void* AIHC_GUIMalloc(UINT32 size)
{
    return CamOsMemAlloc(size);
}

//------------------------------------------------------------------------------
//  Function    : AIHC_GUIFree
//  Description :
//------------------------------------------------------------------------------
/**
    @brief  Release memory pool for GUI APIs
    @param[in] ptr memory pointer
*/
static void AIHC_GUIFree(void *ptr)
{
    CamOsMemRelease(ptr);
}

//------------------------------------------------------------------------------
//  Function    : AIHC_GUI_ReleaseDma
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Callback function to release DMA sem.
*/
static void AIHC_GUI_ReleaseDma(void)
{
    if (AHC_OS_ReleaseSem(m_GUIDMASemID) != MMPF_OS_ERR_NONE) {
        UartSendTrace("m_GUIDMASemID OSSemPost: Fail \r\n");
    }
}

//------------------------------------------------------------------------------
//  Function    : AIHC_DrawReservedOSD
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DrawReservedOSD(AHC_BOOL bDrawReserved)
{
    m_bDrawReserved = bDrawReserved;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_OSDGetParam
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This API gets parameters for OSD

 This API gets parameters for OSD

 @param[in] wParamID     Parameter ID
 @param[out] Param       Parameter
 @retval AHC_TRUE Success.
*/
AHC_BOOL AIHC_OSDGetParam(AHC_PARAM_ID wParamID, UINT32 *Param)
{
    switch (wParamID) {
    case PARAM_ID_OSD_WIDTH:
        *Param = m_OSD[m_ulCurrentOSDID]->width;
        break;
    case PARAM_ID_OSD_HEIGHT:
    #if (SUPPORT_HDMI)
#if 0
        if (HDMIFunc_GetStatus() == AHC_HDMI_MENU_STATUS) {
            switch(MenuSettingConfig()->uiHDMIOutput) {
            case HDMI_OUTPUT_1080I:
                *Param = m_OSD[m_ulCurrentOSDID]->height * 5;
            break;
            case HDMI_OUTPUT_720P:
                *Param = m_OSD[m_ulCurrentOSDID]->height >> 2;
            break;
            case HDMI_OUTPUT_480P:
                *Param = m_OSD[m_ulCurrentOSDID]->height;
            break;
            default:
            case HDMI_OUTPUT_1080P:
                *Param = m_OSD[m_ulCurrentOSDID]->height;
            break;
            }
        }
        else
#endif
        {
            *Param = m_OSD[m_ulCurrentOSDID]->height;
        }
    #else
        *Param = m_OSD[m_ulCurrentOSDID]->height;
    #endif
        break;
    default:
        break;
    }

    return AHC_TRUE;
}

void AHC_GUI_DMADone(void)
{
    m_bGUIDMADone = AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_GUI_GetOSDBufAddr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get OSD buffer address

 Get OSD buffer address

 Parameters:

 @param[in]  uwDisplayID Buffer ID
 @param[out]  Addr Buffer Address

 @retval TRUE or FALSE.
*/
AHC_BOOL AIHC_GUI_GetOSDBufAddr(UINT16 uwDisplayID, UINT32 *Addr)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (uwDisplayID >= MAX_OSD_LAYER) {
        return AHC_FALSE;
    }

    *Addr = (UINT32)(m_OSD[uwDisplayID]->data);

    return AHC_TRUE;
}

#if 0
void _____GUI_Draw_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_OSDSetFont
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Sets the font to be used for text output

 Sets the font to be used for text output

 Parameters:
 @param[in] pNewFont the font to be selected and used
 @retval previous font.
*/
const GUI_FONT* AHC_OSDSetFont(UINT8 id, const GUI_FONT *pNewFont)
{
    const GUI_FONT* old = NULL;

    if (!m_ulInitGUI) {
        return NULL;
    }

    if (m_OSD[id]) {
        old = m_OSD[id]->gui.gui_pfont;
        m_OSD[id]->gui.gui_pfont = (GUI_FONT *)pNewFont;
    }
    else {
        UartSendTrace("--E-- %s: m_OSD[%d] is NULL pointer\r\n", __FUNCTION__, id);
    }

    return old;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDGetFont
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Gets the font to be used for text output

 Gets the font to be used for text output

 @retval current font.
*/
const GUI_FONT* AHC_OSDGetFont(UINT8 id)
{
    if (!m_ulInitGUI) {
        return NULL;
    }

    if (m_OSD[id]) {
        return m_OSD[id]->gui.gui_pfont;
    }
    else {
        return NULL;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDSetPenSize
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set the pen size to be used for futher drawing operations

 Set the pen size to be used for futher drawing operations

 Parameters:
 @param[in] byPenSize pen size in pixels to be used
 @retval previous pen size.
*/
UINT8 AHC_OSDSetPenSize(UINT8 id, UINT8 byPenSize)
{
    UINT8 old = 0;

    if (!m_ulInitGUI) {
        return 0;
    }

    if (m_OSD[id]) {
        old = m_OSD[id]->gui.gui_pen;
        m_OSD[id]->gui.gui_pen = byPenSize;
    }
    else {
        UartSendTrace("--E-- %s: m_OSD[%d] is NULL pointer\r\n", __FUNCTION__, id);
    }

    return old;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDGetPenSize
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_OSDGetPenSize(UINT8 id)
{
    if (!m_ulInitGUI) {
        return 0;
    }

    if (m_OSD[id]) {
        return m_OSD[id]->gui.gui_pen;
    }
    else {
        return 0;
    }
}

AHC_OSD_ROTATE_DRAW_MODE AHC_OSDGetGuiRotateByGUI(UINT8 id)
{
    if (!m_ulInitGUI) {
        return 0;
    }

    if (m_OSD[id]) {
        return m_OSD[id]->gui.ulRotateByGUI;
    }
    else {
        return 0;
    }
}

AHC_BOOL AHC_OSDGetDuplicateWH(UINT8 id,UINT32 *W, UINT32 *H)
{
    if (!m_ulInitGUI) {
        return 0;
    }

    if (m_OSD[id]) {
        *W = m_OSD[id]->DuplicateW;
        *H = m_OSD[id]->DuplicateH;
        return AHC_TRUE;
    }
    else {
        return 0;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDSetBkColor
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set the current background color

 Set the current background color

 Parameters:
 @param[in] Color background color
 @retval the selected background color.
*/
void AHC_OSDSetBkColor(UINT8 id, GUI_COLOR Color)
{
    if (!m_ulInitGUI) {
        return;
    }

    if (m_OSD[id]) {
        m_OSD[id]->gui.gui_bkclr = Color;
    }
    else {
        UartSendTrace("--E-- %s: m_OSD[%d] is NULL pointer\r\n", __FUNCTION__, id);
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDGetBkColor
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get the current background color

 Get the current background color

 Parameters:
 @retval the current background color.
*/
GUI_COLOR AHC_OSDGetBkColor(UINT8 id)
{
    if (!m_ulInitGUI) {
        return 0;
    }

    if (m_OSD[id]) {
        return m_OSD[id]->gui.gui_bkclr;
    }
    else {
        return 0;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDSetColor
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get the current foreground color

 Set the current foreground color

 Parameters:
 @param[in] Color foreground color
 @retval None.
*/
void AHC_OSDSetColor(UINT8 id, GUI_COLOR Color)
{
    if (!m_ulInitGUI) {
        return;
    }

    if (m_OSD[id]) {
        m_OSD[id]->gui.gui_fnclr = Color;
    }
    else {
        UartSendTrace("--E-- %s: m_OSD[%d] is NULL pointer\r\n", __FUNCTION__, id);
        return;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDGetColor
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get the current foreground color

 Get the current foreground color

 @retval the current foreground color.
*/
GUI_COLOR AHC_OSDGetColor(UINT8 id)
{
    if (!m_ulInitGUI) {
        return 0;
    }

    if (m_OSD[id])
        return m_OSD[id]->gui.gui_fnclr;
    else
        return 0xFFFFFFFF;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDSetFlipDrawMode
//  Description :
//------------------------------------------------------------------------------
/**
 @brief set the OSD flip drawing mode.

  Set the OSD flip drawing mode to draw right-left or up-down flip.

 @retval the current foreground color.
*/
void AHC_OSDSetFlipDrawMode(UINT8 id, AHC_OSD_FILP_DRAW_MODE byMode)
{
    UINT32 iVal[10];

    if (!m_ulInitGUI) {
        return;
    }

    if (m_OSD[id]){
        iVal[0] = byMode;
        AHC_OSDSetDisplayAttr(id,  AHC_OSD_ATTR_FLIP_BY_GUI, iVal);
    }
    else{
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0);
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDGetFontDistY
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_OSDGetFontDistY(void)
{
    return GUI_GetFontDistY();
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDGetCurPos
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDGetCurPos(UINT32* pCurX, UINT32* pCurY)
{
    *pCurX = GUI_GetDispPosX();
    *pCurY = GUI_GetDispPosY();

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDSetCurPos
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set text position.

Set text position in pixels.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] newX            New X position
 @param[in] newY            New Y position
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDSetCurPos(UINT16 uwDisplayID, UINT32 newX, UINT32 newY)
{
    GUI_GotoXY(newX, newY);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDCheckDrawLayer
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Check the OSD drawing layer is valid or not.

  Check the OSD drawing layer is valid or not.

 @retval the validation of OSD layer.
*/
AHC_BOOL AHC_OSDCheckDrawLayer(UINT16 uwLayer)
{
    if (m_bDrawReserved == AHC_FALSE) {

        if (uwLayer >= MAX_OSD_NUM) {
            UartSendTrace("--E-- Input OSD Layer exceed to MAX_OSD_NUM\r\n");
            return AHC_FALSE;
        }
    }
    else {

        if (uwLayer >= MAX_OSD_LAYER) {
            UartSendTrace("--E-- Input OSD Layer exceed to MAX_OSD_LAYER\r\n");
            return AHC_FALSE;
        }
    }

    if (!m_OSD[uwLayer]) {
        UartSendTrace("--E-- m_OSD[%d] is NULL\r\n", uwLayer);
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawGradientH
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a rectangle filled with a horizontal color gradient

 Draw a rectangle filled with a horizontal color gradient

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwUpLeftX       Upper left x position
 @param[in] uwUpLeftY       Upper left y position
 @param[in] uwLowRightX     Lower right x position
 @param[in] uwLowRightY     Lower right y position
 @param[in] ulStartColor    Color to be drawned at the leftmost side of the rectangle
 @param[in] ulGradientColor Color to be drawned at the rightmost side of the rectangle

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawGradientH(UINT16 uwDisplayID, UINT16 uwUpLeftX, UINT16 uwUpLeftY, UINT16 uwLowRightX, UINT16 uwLowRightY, UINT32 ulStartColor, UINT32 ulGradientColor)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawGradientH(uwUpLeftX, uwUpLeftY, uwLowRightX, uwLowRightY, ulStartColor, ulGradientColor);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawGradientV
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a rectangle filled with a vertical color gradient

 Draw a rectangle filled with a vertical color gradient

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwUpLeftX       Upper left x position
 @param[in] uwUpLeftY       Upper left y position
 @param[in] uwLowRightX     Lower right x position
 @param[in] uwLowRightY     Lower right y position
 @param[in] ulStartColor    Color to be drawned at the toppest side of the rectangle
 @param[in] ulGradientColor Color to be drawned at the lowest side of the rectangle

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawGradientV(UINT16 uwDisplayID, UINT16 uwUpLeftX, UINT16 uwUpLeftY, UINT16 uwLowRightX, UINT16 uwLowRightY, UINT32 ulStartColor, UINT32 ulGradientColor)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawGradientV(uwUpLeftX, uwUpLeftY, uwLowRightX, uwLowRightY, ulStartColor, ulGradientColor);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawPixel
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a pixel at (X,Y) in the current window

 Draw a pixel at (X,Y) in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwX             x position
 @param[in] uwY             y position

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawPixel(UINT16 uwDisplayID, UINT16 uwX, UINT16 uwY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawPixel(uwX, uwY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawPoint
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a point of the current pen size at (X,Y) in the current window

 Draw a point of the current pen size at (X,Y) in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwX             x position
 @param[in] uwY             y position

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawPoint(UINT16 uwDisplayID, UINT16 uwX, UINT16 uwY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawPoint(uwX, uwY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDClearRect
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Clear a rectangle area at a specified position in the current window by filling it with the background color

 Clear a rectangle area at a specified position in the current window by filling it with the background color

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwUpLeftX       Upper left x position
 @param[in] uwUpLeftY       Upper left y position
 @param[in] uwLowRightX     Lower right x position
 @param[in] uwLowRightY     Lower right y position

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDClearRect(UINT16 uwDisplayID, UINT16 uwUpLeftX, UINT16 uwUpLeftY, UINT16 uwLowRightX, UINT16 uwLowRightY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_ClearRect(uwUpLeftX, uwUpLeftY, uwLowRightX, uwLowRightY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawRect
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a rectangle area at a specified position in the current window

 Draw a rectangle area at a specified position in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwUpLeftX       Upper left x position
 @param[in] uwUpLeftY       Upper left y position
 @param[in] uwLowRightX     Lower right x position
 @param[in] uwLowRightY     Lower right y position

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawRect(UINT16 uwDisplayID, UINT16 uwUpLeftX, UINT16 uwUpLeftY, UINT16 uwLowRightX, UINT16 uwLowRightY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawRect(uwUpLeftX, uwUpLeftY, uwLowRightX, uwLowRightY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawRect2
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a rectangle area at a specified position in the current window

 Draw a rectangle area at a specified position in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pRect           point of RECT

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawRect2(UINT16 uwDisplayID, PRECT pRect)
{
    return AHC_OSDDrawRect(uwDisplayID, pRect->uiLeft, pRect->uiTop, pRect->uiLeft + pRect->uiWidth , pRect->uiTop + pRect->uiHeight );
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFillRect
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a filled rectangle at a specified position in the current window

 Draw a filled rectangle at a specified position in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwUpLeftX       Upper left x position
 @param[in] uwUpLeftY       Upper left y position
 @param[in] uwLowRightX     Lower right x position
 @param[in] uwLowRightY     Lower right y position

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawFillRect(UINT16 uwDisplayID, UINT16 uwUpLeftX, UINT16 uwUpLeftY, UINT16 uwLowRightX, UINT16 uwLowRightY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_FillRect(uwUpLeftX, uwUpLeftY, uwLowRightX, uwLowRightY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFillRect2
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a filled rectangle at a specified position in the current window

 Draw a filled rectangle at a specified position in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwUpLeftX       Upper left x position
 @param[in] uwUpLeftY       Upper left y position
 @param[in] uwLowRightX     Lower right x position
 @param[in] uwLowRightY     Lower right y position

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawFillRect2(UINT16 uwDisplayID, PRECT pRect)
{
    return AHC_OSDDrawFillRect(uwDisplayID, pRect->uiLeft, pRect->uiTop, pRect->uiLeft + pRect->uiWidth , pRect->uiTop + pRect->uiHeight );
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFillRectEx2
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawFillRectEx2(UINT16 uwDisplayID, PRECT pRect, PRECTOFFSET pOff)
{
    return AHC_OSDDrawFillRect( uwDisplayID,
                                pRect->uiLeft + pOff->uiOffX,
                                pRect->uiTop  + pOff->uiOffY,
                                pRect->uiLeft + pRect->uiWidth  + pOff->uiOffW,
                                pRect->uiTop  + pRect->uiHeight + pOff->uiOffH);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawInvertRect
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a inverted rectangle at a specified position in the current window

 Draw a filled rectangle at a specified position in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwUpLeftX       Upper left x position
 @param[in] uwUpLeftY       Upper left y position
 @param[in] uwLowRightX     Lower right x position
 @param[in] uwLowRightY     Lower right y position

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawInvertRect(UINT16 uwDisplayID, UINT16 uwUpLeftX, UINT16 uwUpLeftY, UINT16 uwLowRightX, UINT16 uwLowRightY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_InvertRect(uwUpLeftX, uwUpLeftY, uwLowRightX, uwLowRightY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawLine
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a line from a specified starting position to another specified endpoint in the current window

 Draw a line from a specified starting position to another specified endpoint in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwXStart        Start X
 @param[in] uwXEnd          End X
 @param[in] uwYStart        Start Y
 @param[in] uwYEnd          End Y

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawLine(UINT16 uwDisplayID, UINT16 uwXStart, UINT16 uwXEnd, UINT16 uwYStart, UINT16 uwYEnd)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawLine(uwXStart, uwYStart, uwXEnd, uwYEnd);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawRoundedRect
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw the rounded rectangle.

 Draw the outline of a rounded rectangle.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwUpLeftX       Upper left x position
 @param[in] uwUpLeftY       Upper left y position
 @param[in] uwLowRightX     Lower right x position
 @param[in] uwLowRightY     Lower right y position
 @param[in] uwRadius        radius
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawRoundedRect(UINT16 uwDisplayID, UINT16 uwUpLeftX, UINT16 uwUpLeftY, UINT16 uwLowRightX, UINT16 uwLowRightY, UINT16 uwRadius)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawRoundedRect(uwUpLeftX, uwUpLeftY, uwLowRightX, uwLowRightY, uwRadius);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawRoundedRect2
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawRoundedRect2(UINT16 uwDisplayID, PRECT pRect, UINT16 uwRadius)
{
    return AHC_OSDDrawRoundedRect(uwDisplayID, pRect->uiLeft, pRect->uiTop, pRect->uiLeft + pRect->uiWidth , pRect->uiTop + pRect->uiHeight, uwRadius);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFillRoundedRect
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a filled rounded rectangle.

 Draw a filled rounded rectangle.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwUpLeftX       Upper left x position
 @param[in] uwUpLeftY       Upper left y position
 @param[in] uwLowRightX     Lower right x position
 @param[in] uwLowRightY     Lower right y position
 @param[in] uwRadius        radius
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawFillRoundedRect(UINT16 uwDisplayID, UINT16 uwUpLeftX, UINT16 uwUpLeftY, UINT16 uwLowRightX, UINT16 uwLowRightY, UINT16 uwRadius)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_FillRoundedRect(uwUpLeftX, uwUpLeftY, uwLowRightX, uwLowRightY, uwRadius);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFillRoundedRect2
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawFillRoundedRect2(UINT16 uwDisplayID, PRECT pRect, UINT16 uwRadius)
{
    return AHC_OSDDrawFillRoundedRect(uwDisplayID, pRect->uiLeft, pRect->uiTop, pRect->uiLeft + pRect->uiWidth , pRect->uiTop + pRect->uiHeight, uwRadius);
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawPolygon
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw the outline of a polygon defined by a list of points in the current window

 Draw the outline of a polygon defined by a list of points in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pPoints         Pointer to the polygon to display
 @param[in] uwNumPoints     Number of points
 @param[in] uwX             X position
 @param[in] uwY             Y position

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawPolygon(UINT16 uwDisplayID, const GUI_POINT *pPoints, UINT16 uwNumPoints, UINT16 uwX, UINT16 uwY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawPolygon(pPoints, uwNumPoints, uwX, uwY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFillPolygon
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a filled polygon defined by a list of points in the current window

 Draw a filled polygon defined by a list of points in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pPoints         Pointer to the polygon to display
 @param[in] uwNumPoints     Number of points
 @param[in] uwX             X position
 @param[in] uwY             Y position

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawFillPolygon(UINT16 uwDisplayID, const GUI_POINT *pPoints, UINT16 uwNumPoints, UINT16 uwX, UINT16 uwY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_FillPolygon(pPoints, uwNumPoints, uwX, uwY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawCircle
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw the outline of a circle

 Draw the outline of a circle

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwX             X position of the center of circle
 @param[in] uwY             Y position of the center of circle
 @param[in] uwRadius        radius
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawCircle(UINT16 uwDisplayID, UINT16 uwX, UINT16 uwY, UINT16 uwRadius)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawCircle(uwX, uwY, uwRadius);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFillCircle
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a filled circle

 Draw a filled circle

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwX             X position of the center of circle
 @param[in] uwY             Y position of the center of circle
 @param[in] uwRadius        radius
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawFillCircle(UINT16 uwDisplayID, UINT16 uwX, UINT16 uwY, UINT16 uwRadius)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_FillCircle(uwX, uwY, uwRadius);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawEllipse
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw the outline of an ellipse

 Draw the outline of an ellipse

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwX             X position of the center of ellipse
 @param[in] uwY             Y position of the center of ellipse
 @param[in] uwRadiusX       X-radius
 @param[in] uwRadiusY       Y-radius
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawEllipse(UINT16 uwDisplayID, UINT16 uwX, UINT16 uwY, UINT16 uwRadiusX, UINT16 uwRadiusY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawEllipse(uwX, uwY, uwRadiusX, uwRadiusY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFillEllipse
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw an filled ellipse

 Draw an filled ellipse

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwX             X position of the center of ellipse
 @param[in] uwY             Y position of the center of ellipse
 @param[in] uwRadiusX       X-radius
 @param[in] uwRadiusY       Y-radius
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawFillEllipse(UINT16 uwDisplayID, UINT16 uwX, UINT16 uwY, UINT16 uwRadiusX, UINT16 uwRadiusY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_FillEllipse(uwX, uwY, uwRadiusX, uwRadiusY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawArc
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw an arc

 Draw an arc

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwXCenter       X position of the center
 @param[in] uwYCenter       Y position of the center
 @param[in] uwRadiusX       X-radius
 @param[in] uwRadiusY       Y-radius
 @param[in] uwAngle1        starting angle
 @param[in] uwAngle1        end angle
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawArc(UINT16 uwDisplayID, UINT16 uwXCenter, UINT16 uwYCenter, UINT16 uwRadiusX, UINT16 uwRadiusY, UINT16 uwAngle1, UINT16 uwAngle2)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawArc(uwXCenter, uwYCenter, uwRadiusX, uwRadiusY, uwAngle1, uwAngle2);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawPie
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a circle sector

 Draw a circle sector

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwXCenter       X position of the center of a circle
 @param[in] uwYCenter       Y position of the center of a circle
 @param[in] uwRadius        radius
 @param[in] uwAngle1        starting angle
 @param[in] uwAngle1        end angle
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawPie(UINT16 uwDisplayID, UINT16 uwX, UINT16 uwY, UINT16 uwRadius, UINT16 uwAngle1, UINT16 uwAngle2)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawPie(uwX, uwY, uwRadius, uwAngle1, uwAngle2, 0);
    END_GUI_DRAW(uwDisplayID);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawBitmap
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a bitmap image at the specified position in the current window

 Draw a bitmap image at the specified position in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pBmp            pointer to the bitmap
 @param[in] uwX             X position
 @param[in] uwY             Y position
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawBitmap(UINT16 uwDisplayID, const GUI_BITMAP *pBmp, UINT16 uwX, UINT16 uwY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    if (!pBmp)
        return AHC_FALSE;

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawBitmap(pBmp, uwX, uwY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawBitmapEx
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This routine makes it possible to scale and/or to mirror a bitmap on the display

 This routine makes it possible to scale and/or to mirror a bitmap on the display

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pBmp            pointer to the bitmap
 @param[in] uwX             X position of the anker point in the display
 @param[in] uwY             Y position of the anker point in the display
 @param[in] uwXCenter       X position of the anker point in the bitmap
 @param[in] uwYCenter       Y position of the anker point in the bitmap
 @param[in] uwXMag          scale factor of X-direction
 @param[in] uwYMag          scale factor of Y-direction
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawBitmapEx(UINT16 uwDisplayID, const GUI_BITMAP *pBmp, UINT16 uwX, UINT16 uwY, UINT16 uwXCenter, UINT16 uwYCenter, UINT16 uwXMag, UINT16 uwYMag)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawBitmapEx(pBmp, uwX, uwY, uwXCenter, uwYCenter, uwXMag, uwYMag);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawBitmapMag
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This routine makes it possible to magnify a bitmap on the display

 This routine makes it possible to scale and/or to mirror a bitmap on the display

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pBmp            pointer to the bitmap
 @param[in] uwX             X position of the upper-left corner of the bitmap in the display
 @param[in] uwY             Y position of the upper-left corner of the bitmap in the display
 @param[in] uwXMul          Magnification factor of X-direction
 @param[in] uwYMul          Magnification factor of Y-direction
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawBitmapMag(UINT16 uwDisplayID, const GUI_BITMAP *pBmp, UINT16 uwX, UINT16 uwY, UINT16 uwXMul, UINT16 uwYMul)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DrawBitmapMag(pBmp, uwX, uwY, uwXMul,uwYMul);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawJpeg
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a JPEG file, which has beed loaded into memory, at a specified position in the current window

 Draw a JPEG file, which has beed loaded into memory, at a specified position in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pData           pointer to the jpeg data
 @param[in] uwDataSize      Jpeg size
 @param[in] uwX             X position
 @param[in] uwY             Y position
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawJpeg(UINT16 uwDisplayID, const void* pData, UINT16 uwDataSize, UINT16 uwX, UINT16 uwY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);

    if (GUI_JPEG_Draw(pData, uwDataSize, uwX, uwY)) {
        END_GUI_DRAW(uwDisplayID);
        return AHC_FALSE;
    }
    else {
        END_GUI_DRAW(uwDisplayID);
        return AHC_TRUE;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawJpegScale
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a JPEG file, which has beed loaded into memory, at a specified position in the current window using scaling

 Draw a JPEG file, which has beed loaded into memory, at a specified position in the current window using scaling

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pData           pointer to the jpeg data
 @param[in] uwDataSize      Jpeg size
 @param[in] uwX             X position
 @param[in] uwY             Y position
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawJpegScale(UINT16 uwDisplayID, const void* pData, UINT16 uwDataSize, UINT16 uwX, UINT16 uwY, UINT16 uwNum, UINT16 uwDenom)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);

    if (GUI_JPEG_DrawScaled(pData, uwDataSize, uwX, uwY, uwNum, uwDenom)) {
        END_GUI_DRAW(uwDisplayID);
        return AHC_FALSE;
    }
    else {
        END_GUI_DRAW(uwDisplayID);
        return AHC_TRUE;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawGif
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a GIF file, which has beed loaded into memory, at a specified position in the current window

 Draw a GIF file, which has beed loaded into memory, at a specified position in the current window

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pData           pointer to the jpeg data
 @param[in] uwDataSize      Jpeg size
 @param[in] uwX             X position
 @param[in] uwY             Y position
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawGif(UINT16 uwDisplayID, const void* pData, UINT16 uwDataSize, UINT16 uwX, UINT16 uwY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);

    if (GUI_GIF_Draw(pData, uwDataSize, uwX, uwY)) {
        END_GUI_DRAW(uwDisplayID);
        return AHC_FALSE;
    }
    else {
        END_GUI_DRAW(uwDisplayID);
        return AHC_TRUE;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawChar
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw char at specific position.

 Draw char at specific position. All other parameters (color, font size and font) are following current UI setting.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] u8Char          String to be drawn
 @param[in] uwStartX        x-coordinate of display window
 @param[in] uwStartY        y-coordinate of display window
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawChar(UINT8 uwDisplayID, UINT8 u8Char, UINT16 uwStartX, UINT16 uwStartY)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispCharAt(u8Char, uwStartX, uwStartY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawString
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw text at current position.

 Draw text at current position. All other parameters (color, font size and font) are following current UI setting.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pStr            String to be drawn
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawString(UINT8 uwDisplayID, UINT8* pStr)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispString((const char*)pStr);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawText
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a given string at specific location

 Draw a given string at specific location. All other parameters (color, font size and font) are following current UI setting.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pStrPtr         String
 @param[in] uwStartX        x-coordinate of display window
 @param[in] uwStartY        y-coordinate of display window
 @param[in] uwStrlen        The length of string
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawText(UINT8 uwDisplayID, UINT8 *pStrPtr, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwLength)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispStringAt((char*)pStrPtr, uwStartX, uwStartY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawTextEx
//  Description :
//------------------------------------------------------------------------------
/*
 * AHC_OSDDrawTextEx
 *  uwMag: to enlarge string (2 for x2, 3 for x3)
 */
AHC_BOOL AHC_OSDDrawTextEx(UINT8 uwDisplayID, UINT8 *pStrPtr, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwLength, UINT16 uwMag)
{
    GUI_FONT *pFont;

    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);

    pFont = (GUI_FONT*)AHC_OSDGetFont(uwDisplayID);

    pFont->XMag = uwMag;
    pFont->YMag = uwMag;
    GUI_DispStringAt((char*)pStrPtr, uwStartX, uwStartY);
    pFont->XMag = 1;
    pFont->YMag = 1;

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawText_Transparent
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawText_Transparent(UINT8 uwDisplayID, UINT8 *pStrPtr, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwLength)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    AHC_OSDDisableDrawFontBk(AHC_TRUE);
    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispStringAt((char*)pStrPtr, uwStartX, uwStartY);
    AHC_OSDDisableDrawFontBk(AHC_FALSE);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawTextInRect
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a given string in specific Rectangle

 Draw a given string in a specific Rectangle. All other parameters (color, font size and font) are following current UI setting.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pStrPtr         String
 @param[in] uwStartX        start x position of display rectangle
 @param[in] uwStartY        stary y position of display rectangle
 @param[in] uwEndX          end x position of display rectangle
 @param[in] uwEndY          end y position of display rectangle
 @param[in] uwStrlen        The length of string
 @param[in] wTextAlign      string alignment.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawTextInRect(UINT8 uwDisplayID, UINT8 *pStrPtr, GUI_RECT* pRect, INT16 wTextAlign)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispStringInRect((char*)pStrPtr, pRect, wTextAlign);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawTextInRectSlide
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawTextInRectSlide(UINT8 uwDisplayID, UINT8 *pStrPtr, GUI_RECT* pRect, INT16 wTextAlign, int *ps)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispStringInRectSlide((const char*)pStrPtr, pRect, wTextAlign, ps);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawTextEdgeInRect
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawTextEdgeInRect(UINT8 uwDisplayID, GUI_RECT* pRect, GUI_COLOR edgeColor, GUI_COLOR bkColor)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    if (OSD_COLOR_RGB565 == m_OSD[uwDisplayID]->Color) {

        BEGIN_GUI_DRAW(uwDisplayID);

        if ((pRect->x0 < m_OSD[uwDisplayID]->width) &&
            (pRect->x1 < m_OSD[uwDisplayID]->width) &&
            (pRect->y0 < m_OSD[uwDisplayID]->height) &&
            (pRect->y1 < m_OSD[uwDisplayID]->height) ) {

            UINT32    x, y, ColorDepth = 2, newEdgeColor, newBkColor;
            MMP_UBYTE *Addr = (MMP_UBYTE *) m_OSD[uwDisplayID]->data;

            newEdgeColor  = (edgeColor & 0x00F80000) >> 8;
            newEdgeColor |= (edgeColor & 0x0000FC00) >> 5;
            newEdgeColor |= (edgeColor & 0x000000F8) >> 3;

            newBkColor  = (bkColor & 0x00F80000) >> 8;
            newBkColor |= (bkColor & 0x0000FC00) >> 5;
            newBkColor |= (bkColor & 0x000000F8) >> 3;

            for (y = pRect->y0; y < pRect->y1; y++) {
                for (x = pRect->x0; x < pRect->x1; x++) {

                    if (newBkColor == *(UINT16 *) (Addr + (y * m_OSD[uwDisplayID]->width + x) * ColorDepth)) {
                        if (((*(UINT16 *) (Addr + ((y - 1) * m_OSD[uwDisplayID]->width + (x - 1))  * ColorDepth) != newBkColor) && (*(UINT16 *) (Addr + ((y - 1) * m_OSD[uwDisplayID]->width + (x - 1)) * ColorDepth) != newEdgeColor)) ||
                            ((*(UINT16 *) (Addr + ((y - 1) * m_OSD[uwDisplayID]->width +  x     )  * ColorDepth) != newBkColor) && (*(UINT16 *) (Addr + ((y - 1) * m_OSD[uwDisplayID]->width +  x     ) * ColorDepth) != newEdgeColor)) ||
                            ((*(UINT16 *) (Addr + ((y - 1) * m_OSD[uwDisplayID]->width + (x + 1))  * ColorDepth) != newBkColor) && (*(UINT16 *) (Addr + ((y - 1) * m_OSD[uwDisplayID]->width + (x + 1)) * ColorDepth) != newEdgeColor)) ||
                            ((*(UINT16 *) (Addr + ( y      * m_OSD[uwDisplayID]->width + (x - 1))  * ColorDepth) != newBkColor) && (*(UINT16 *) (Addr + ( y      * m_OSD[uwDisplayID]->width + (x - 1)) * ColorDepth) != newEdgeColor)) ||
                            ((*(UINT16 *) (Addr + ( y      * m_OSD[uwDisplayID]->width + (x + 1))  * ColorDepth) != newBkColor) && (*(UINT16 *) (Addr + ( y      * m_OSD[uwDisplayID]->width + (x + 1)) * ColorDepth) != newEdgeColor)) ||
                            ((*(UINT16 *) (Addr + ((y + 1) * m_OSD[uwDisplayID]->width + (x - 1))  * ColorDepth) != newBkColor) && (*(UINT16 *) (Addr + ((y + 1) * m_OSD[uwDisplayID]->width + (x - 1)) * ColorDepth) != newEdgeColor)) ||
                            ((*(UINT16 *) (Addr + ((y + 1) * m_OSD[uwDisplayID]->width +  x     )  * ColorDepth) != newBkColor) && (*(UINT16 *) (Addr + ((y + 1) * m_OSD[uwDisplayID]->width +  x     ) * ColorDepth) != newEdgeColor)) ||
                            ((*(UINT16 *) (Addr + ((y + 1) * m_OSD[uwDisplayID]->width + (x + 1))  * ColorDepth) != newBkColor) && (*(UINT16 *) (Addr + ((y + 1) * m_OSD[uwDisplayID]->width + (x + 1)) * ColorDepth) != newEdgeColor)) )
                        {
                           *(UINT16 *) (Addr + (y * m_OSD[uwDisplayID]->width + x) * ColorDepth) = newEdgeColor;
                        }
                    }
                }
            }
        }
        else {
            UartSendTrace(FG_RED("[GUI ERROR] %s - Wrong RECT range %d,%d - %d,%d")"\r\n", __FUNCTION__, pRect->x0, pRect->y0, pRect->x1, pRect->y1);
        }

        END_GUI_DRAW(uwDisplayID);

        return AHC_TRUE;
    }

    UartSendTrace(FG_RED("[GUI ERROR] %s - Color Format is not support - %d")"\r\n", __FUNCTION__, m_OSD[uwDisplayID]->Color);
    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawTextInRectEx
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a given string in specific Rectangle

 Draw a given string in a specific Rectangle. All other parameters (color, font size and font) are following current UI setting.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] pStrPtr         String
 @param[in] uwStartX        start x position of display rectangle
 @param[in] uwStartY        stary y position of display rectangle
 @param[in] uwEndX          end x position of display rectangle
 @param[in] uwEndY          end y position of display rectangle
 @param[in] uwStrlen        The length of string
 @param[in] wTextAlign      string alignment.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawTextInRectEx(UINT8 uwDisplayID, UINT8 *pStrPtr, UINT32 uwStartX, UINT32 uwStartY, UINT32 uwEndX, UINT32 uwEndY, INT16 wTextAlign, UINT16 uwLength, UINT32 ulRotate)
{
    const GUI_ROTATION *uGuiRotate;
    GUI_RECT GuiRECT;

    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    GuiRECT.x0 = uwStartX;
    GuiRECT.y0 = uwStartY;
    GuiRECT.x1 = uwEndX;
    GuiRECT.y1 = uwEndY;

    if (AHC_OSD_ROTATE_NONE == ulRotate)
        uGuiRotate = GUI_ROTATE_0;
    else if (AHC_OSD_ROTATE_RIGHT_90 == ulRotate)
        uGuiRotate = GUI_ROTATE_CW;
    else if (AHC_OSD_ROTATE_RIGHT_180 == ulRotate)
        uGuiRotate = GUI_ROTATE_180;
    else
        uGuiRotate = GUI_ROTATE_CCW;

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispStringInRectEx((char*)pStrPtr, &GuiRECT, wTextAlign, uwLength, uGuiRotate);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawTextInRectWrap
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawTextInRectWrap(UINT8 uwDisplayID, UINT8 *pStrPtr, GUI_RECT* rc, GUI_COLOR color, INT16 wTextAlign, GUI_WRAPMODE WrapMode)
{
    UINT32 oldTextMode, oldColor;

    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);

    oldTextMode = GUI_GetTextMode();
    oldColor = GUI_GetColor();

    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(color);

    GUI_DispStringInRectWrap((char*)pStrPtr, rc, wTextAlign, WrapMode);

    GUI_SetTextMode(oldTextMode);
    GUI_SetColor(oldColor);

    END_GUI_DRAW(uwDisplayID);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawDec
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Draw a given variable at specific location

 Draw a given string at specific location. All other parameters (color, font size and font) are following current UI setting.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] uwVal           Variable Val
 @param[in] uwStartX        x-coordinate of display window
 @param[in] uwStartY        y-coordinate of display window
 @param[in] uwStrlen        The length of Value
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawDec(UINT8 uwDisplayID, INT32 uwVal, UINT16 uwStartX, UINT16 uwStartY, UINT8 uwLength)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispDecAt(uwVal, uwStartX, uwStartY, uwLength);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawDec_Transparent
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawDec_Transparent(UINT8 uwDisplayID, INT32 uwVal, UINT16 uwStartX, UINT16 uwStartY, UINT8 uwLength)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }
    BEGIN_GUI_DRAW(uwDisplayID);

    AHC_OSDDisableDrawFontBk(AHC_TRUE);
    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispDecAt(uwVal, uwStartX, uwStartY, uwLength);
    AHC_OSDDisableDrawFontBk(AHC_FALSE);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawHex
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawHex(UINT8 uwDisplayID, INT32 uwVal, UINT16 uwStartX, UINT16 uwStartY, UINT8 uwLength)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispHexAt(uwVal, uwStartX, uwStartY, uwLength);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawHex_Transparent
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawHex_Transparent(UINT8 uwDisplayID, INT32 uwVal, UINT16 uwStartX, UINT16 uwStartY, UINT8 uwLength)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }
    BEGIN_GUI_DRAW(uwDisplayID);

    AHC_OSDDisableDrawFontBk(AHC_TRUE);
    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispHexAt(uwVal, uwStartX, uwStartY, uwLength);
    AHC_OSDDisableDrawFontBk(AHC_FALSE);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFloat
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawFloat(UINT8 uwDisplayID, double uwVal, UINT8 uwLength)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispFloat(uwVal, uwLength);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawFloat_Transparent
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDDrawFloat_Transparent(UINT8 uwDisplayID, double uwVal, UINT8 uwLength)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }
    BEGIN_GUI_DRAW(uwDisplayID);

    AHC_OSDDisableDrawFontBk(AHC_TRUE);
    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_DispFloat(uwVal, uwLength);
    AHC_OSDDisableDrawFontBk(AHC_FALSE);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDrawBuffer
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Overwrite OSD buffer with input buffer

 Overwrite OSD buffer with input buffer.

 Parameters:
 @param[in] uwDisplayID     Display ID
 @param[in] InBuffer        String
 @param[in] uwStartX        x-coordinate of display window
 @param[in] uwStartY        y-coordinate of display window
 @param[in] uwWidth         buffer width
 @param[in] uwHeight        buffer height
 @param[in] uiColorFormat   OSD color format
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDrawBuffer(UINT8 uwDisplayID, UINT8 *InBuffer, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwWidth, UINT16 uwHeight, AHC_OSD_COLOR_FMT uiColorFormat)
{
    UINT32 ColorDepth = 0;
    UINT8 *dest;
    MMP_ULONG ulTimeOutTick = 0x500000;
    m_bGUIDMADone = MMP_FALSE;

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    if (uiColorFormat != m_OSD[uwDisplayID]->Color) {
        return AHC_FALSE;
    }

    if ((uwStartX + uwWidth) > m_OSD[uwDisplayID]->width) {
        RTNA_DBG_Str(0, FG_RED("AHC_OSDDrawBuffer Parameter error 1\r\n"));
    }

    if ((uwStartY + uwHeight) > m_OSD[uwDisplayID]->height) {
        RTNA_DBG_Str(0, FG_RED("AHC_OSDDrawBuffer Parameter error 2\r\n"));
    }

    switch(uiColorFormat) {
    case OSD_COLOR_ARGB3454:
    case OSD_COLOR_RGB565:
        ColorDepth = 2;
        break;
    case OSD_COLOR_RGB888:
        ColorDepth = 3;
        break;
    case OSD_COLOR_ARGB32:
        ColorDepth = 4;
        break;
    case OSD_COLOR_YUV422:
        ColorDepth = 2;
        break;
    default:
        return AHC_FALSE;
        break;
    }

    dest = m_OSD[uwDisplayID]->data + (uwStartY * m_OSD[uwDisplayID]->width + uwStartX) * ColorDepth;

    {
        MMP_DMA_LINE_OFST LineOfst;
        LineOfst.ulSrcWidth  = uwWidth * ColorDepth; //Unit: byte
        LineOfst.ulSrcOffset = uwWidth * ColorDepth;
        LineOfst.ulDstWidth  = uwWidth * ColorDepth; //Unit: byte
        LineOfst.ulDstOffset = m_OSD[uwDisplayID]->width * ColorDepth;
        MMPF_DMA_MoveData(InBuffer, dest, uwWidth * uwHeight * ColorDepth, AHC_GUI_DMADone, NULL, MMP_TRUE, &LineOfst);
    }

    // Waiting the DMA move buf to buf done.
    while((!m_bGUIDMADone) && (--ulTimeOutTick > 0));

    if (ulTimeOutTick == 0) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDisableDrawFontBk
//  Description :
//------------------------------------------------------------------------------
/*
    AHC_OSDDisableDrawFontBk

    bDisable - AHC_TRUE    If setting to TRUE, while drawing string, the string background would not be drawn.
               AHC_FALSE   Normal
*/
AHC_BOOL AHC_OSDDisableDrawFontBk(AHC_BOOL bDisable)
{
    GUI_SetFontBkDisable(bDisable);
    GUI_SetTextMode((bDisable) ? GUI_TM_TRANS : GUI_TM_NORMAL);
    return AHC_TRUE;
}

#if 0
void _____OSD_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_OSDInit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Init OSD/GUI and prepare two OSD buffer for further usage, it must be called before any OSD operation.

 This API init OSD/GUI and prepare two OSD buffer for further usage, it must be called before any OSD operation.

 @param[in] OSDWidth     OSD width
 @param[in] OSDHeight    OSD height
 @param[in] ColorFormat  OSD color format
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDInit(   U32 OSDWidth,
                        U32 OSDHeight,
                        U32 ThumbWidth,
                        U32 ThumbHeight,
                        U32 PrimaryDateWidth,
                        U32 PrimaryDateHeight,
                        U32 ThumbDateWidth,
                        U32 ThumbDateHeight,
                        U32 ColorFormat,
                        AHC_BOOL MainBuffFull,
                        AHC_OSD_ROTATE_DRAW_MODE ahcOSDRotateDraw)
{
    U32                         u32GUIMemSize  = AHC_GUI_STRUCT_MEMORY_SIZE;
    static U32                  u32GUIMem = 0;
    U32                         i;
    AHC_DISPLAY_OUTPUTPANEL     OutputDevice;
    UINT32                      iVal[10];

    if (m_ulInitGUI) {
        return AHC_FALSE;
    }

    GUI_ReInit();

    if (u32GUIMem == 0) {
        u32GUIMem = (UINT32)CamOsMemAlloc(u32GUIMemSize);
    }

    if (!u32GUIMem) {
        return AHC_FALSE;
    }

    GUI__Config_Ex((U32)u32GUIMem, u32GUIMemSize);

    /* Reset OSD attribute */
    for (i = 0; i < MAX_OSD_LAYER; i++) {
        m_OSD[i]        = NULL;
        m_bOSDConfig[i] = AHC_FALSE;
    }

    m_ulOSDLayerCount = 0;

    /* Create Semaphore */
    m_GUISemID      = AHC_OS_CreateSem(1);
    m_GUIDMASemID   = AHC_OS_CreateSem(1);
    gulDrawingSemID = AHC_OS_CreateSem(1);

    if (m_GUISemID == 0xFF || m_GUISemID == 0xFE)
    {
        UartSendTrace("CREATE GUI SEM ERROR!\r\n");
        m_GUISemID = -1;
    }

    /* Allocate Warning MSG Buffer */
    if (MainBuffFull) {
        U32 rc;

        if((OSD_ROTATE_DRAW_NONE == ahcOSDRotateDraw) || (OSD_ROTATE_DRAW_RIGHT_180 == ahcOSDRotateDraw)){
            rc = ColorFormat;
        }
        else if((OSD_ROTATE_DRAW_RIGHT_90 == ahcOSDRotateDraw) || (OSD_ROTATE_DRAW_RIGHT_270 == ahcOSDRotateDraw)){
            rc = (ColorFormat == OSD_COLOR_RGB565) ? OSD_COLOR_RGB565_CCW : OSD_COLOR_ARGB32_CCW;
        }

        if (AHC_FALSE == AHC_OSDCreateBuffer(0, OSDWidth, OSDHeight, rc)) {
            return AHC_FALSE;
        }

        iVal[0] = ahcOSDRotateDraw;
        AHC_OSDSetDisplayAttr(0,  AHC_OSD_ATTR_ROTATE_BY_GUI, iVal);
        iVal[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        AHC_OSDSetDisplayAttr(0,  AHC_OSD_ATTR_FLIP_BY_GUI, iVal);
    }
    else {
        // For HDMI/TV warning MSG
        if (AHC_FALSE == AHC_OSDCreateBuffer(0, TV_HDMI_WMG_WIDTH, TV_HDMI_WMG_HEIGHT, ColorFormat)) {
            return AHC_FALSE;
        }
        iVal[0] = OSD_ROTATE_DRAW_NONE;
        AHC_OSDSetDisplayAttr(0,  AHC_OSD_ATTR_ROTATE_BY_GUI, iVal);
        iVal[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        AHC_OSDSetDisplayAttr(0,  AHC_OSD_ATTR_FLIP_BY_GUI, iVal);
    }

    GUI_Init_Ex();

    /* Set Display Attribute */
    AHC_GetDisplayOutputDev(&OutputDevice);

    MMPS_Display_SetOutputPanel(MMP_DISPLAY_PRM_CTL, OutputDevice);

    MMPF_Display_BindWinToController(WMSG_LAYER_WINDOW_ID, MMP_DISPLAY_PRM_CTL);

    /* Allocate Extra OSD Buffer */
    AIHC_DrawReservedOSD(AHC_TRUE);

    if (PrimaryDateWidth && PrimaryDateHeight) {
        if (AHC_FALSE == AHC_OSDCreateBuffer(   DATESTAMP_PRIMARY_OSD_ID,
                                                PrimaryDateWidth,
                                                PrimaryDateHeight,
                                                PRIMARY_DATESTAMP_COLOR_FORMAT)) {
            AIHC_DrawReservedOSD(AHC_FALSE);
            return AHC_FALSE;
        }

        #if (AHC_SHAREENC_SUPPORT == 0)
        // Create buffer for Sub time stamp. Use for sub stream.
        if (AHC_FALSE == AHC_OSDCreateBuffer(   DATESTAMP_PRIMARY_OSD_ID_SUB,
                                                PrimaryDateWidth,
                                                PrimaryDateHeight,
                                                PRIMARY_DATESTAMP_COLOR_FORMAT)) {
            AIHC_DrawReservedOSD(AHC_FALSE);
            return AHC_FALSE;
        }
        #endif

        //Sticker is always not roated.
        iVal[0] = OSD_ROTATE_DRAW_NONE;
        AHC_OSDSetDisplayAttr(DATESTAMP_PRIMARY_OSD_ID,  AHC_OSD_ATTR_ROTATE_BY_GUI, iVal);

        iVal[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        AHC_OSDSetDisplayAttr(DATESTAMP_PRIMARY_OSD_ID,  AHC_OSD_ATTR_FLIP_BY_GUI, iVal);
    }

    if (ThumbDateWidth && ThumbDateHeight) {
        if (AHC_FALSE == AHC_OSDCreateBuffer(   DATESTAMP_THUMB_OSD_ID,
                                                ThumbDateWidth,
                                                ThumbDateHeight,
                                                THUMB_DATESTAMP_COLOR_FORMAT)) {
            AIHC_DrawReservedOSD(AHC_FALSE);
            return AHC_FALSE;
        }

        #if (AHC_SHAREENC_SUPPORT == 0)
        // Create buffer for Sub time stamp. Use for sub stream.
        if (AHC_FALSE == AHC_OSDCreateBuffer(   DATESTAMP_THUMB_OSD_ID_SUB,
                                                ThumbDateWidth,
                                                ThumbDateHeight,
                                                THUMB_DATESTAMP_COLOR_FORMAT)) {
            AIHC_DrawReservedOSD(AHC_FALSE);
            return AHC_FALSE;
        }
        #endif

        //Sticker is always not roated.
        iVal[0] = OSD_ROTATE_DRAW_NONE;
        AHC_OSDSetDisplayAttr(DATESTAMP_THUMB_OSD_ID,  AHC_OSD_ATTR_ROTATE_BY_GUI, iVal);

        iVal[0] = OSD_FLIP_DRAW_NONE_ENABLE;
        AHC_OSDSetDisplayAttr(DATESTAMP_THUMB_OSD_ID,  AHC_OSD_ATTR_FLIP_BY_GUI, iVal);
    }

    #if (AHC_SHAREENC_SUPPORT == 1)
    {
        U32 dualdatewidth = DATESTAMP_DUALENC_WIDTH;    //640;
        U32 dualdateheight = DATESTAMP_DUALENC_HEIGHT;  //28;

        if (dualdatewidth && dualdateheight) {
            if (AHC_FALSE == AHC_OSDCreateBuffer(   DATESTAMP_PRIMARY_OSD_ID_SUB,
                                                dualdatewidth,
                                                dualdateheight,
                                                OSD_COLOR_RGB565/*PRIMARY_DATESTAMP_COLOR_FORMAT*/)) {
                AIHC_DrawReservedOSD(AHC_FALSE);
                return AHC_FALSE;
            }

            if (AHC_FALSE == AHC_OSDCreateBuffer(   DATESTAMP_THUMB_OSD_ID_SUB,
                                                dualdatewidth,
                                                dualdateheight,
                                                THUMB_DATESTAMP_COLOR_FORMAT)) {
                AIHC_DrawReservedOSD(AHC_FALSE);
                return AHC_FALSE;
            }

            if (AHC_FALSE == AHC_OSDCreateBuffer(   DATESTAMP_PRIMARY_OSD_ID_SUB_DUAL,
                                                dualdatewidth,
                                                dualdateheight,
                                                PRIMARY_DATESTAMP_COLOR_FORMAT)) {
                AIHC_DrawReservedOSD(AHC_FALSE);
                return AHC_FALSE;
            }

            if (AHC_FALSE == AHC_OSDCreateBuffer(   DATESTAMP_THUMB_OSD_ID_SUB_DUAL,
                                                dualdatewidth,
                                                dualdateheight,
                                                THUMB_DATESTAMP_COLOR_FORMAT)) {
                AIHC_DrawReservedOSD(AHC_FALSE);
                return AHC_FALSE;
            }

        }
    }
    #endif

    AIHC_DrawReservedOSD(AHC_FALSE);

    AHC_OSDSetCurrentDisplay(0);

    if(gAHC_OSD_InitOSDCustomCB){
        gAHC_OSD_InitOSDCustomCB(ColorFormat, ahcOSDRotateDraw);
    }

    m_ulInitGUI = 1;
    AHC_OSDClearBuffer(0);

    AHC_OSDUpdateAddrOnly(AHC_TRUE);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDUninit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Uninit OSD/GUI and release OSD buffers.

 The API uninit OSD/GUI and release OSD buffers.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDUninit(void)
{
    U32 i;

    #if (HDMI_ENABLE)
    //bHaveInitOsdHdmi = AHC_FALSE;
    #endif

    if (m_ulInitGUI != 1) {
        return AHC_FALSE;
    }

    // Destroy reserved OSD layer
    AIHC_DrawReservedOSD(AHC_TRUE);

    // Destroy all layer
    for (i = 0; i < MAX_OSD_NUM; i++){
        if(m_OSD[i]!= NULL) {
            AHC_OSDDestroyBuffer(i);
        }
    }

    // Destroy extra layer
    if (m_OSD[THUMBNAIL_OSD_FRONT_ID])
        AHC_OSDDestroyBuffer(THUMBNAIL_OSD_FRONT_ID);
    if (m_OSD[THUMBNAIL_OSD_BACK_ID])
        AHC_OSDDestroyBuffer(THUMBNAIL_OSD_BACK_ID);
    if (m_OSD[DATESTAMP_PRIMARY_OSD_ID])
        AHC_OSDDestroyBuffer(DATESTAMP_PRIMARY_OSD_ID);
    if (m_OSD[DATESTAMP_THUMB_OSD_ID])
        AHC_OSDDestroyBuffer(DATESTAMP_THUMB_OSD_ID);
    if (m_OSD[DATESTAMP_PRIMARY_OSD_ID_SUB])
        AHC_OSDDestroyBuffer(DATESTAMP_PRIMARY_OSD_ID_SUB);
    if (m_OSD[DATESTAMP_THUMB_OSD_ID_SUB])
        AHC_OSDDestroyBuffer(DATESTAMP_THUMB_OSD_ID_SUB);
    if (m_OSD[DATESTAMP_PRIMARY_OSD_ID_SUB_DUAL])
        AHC_OSDDestroyBuffer(DATESTAMP_PRIMARY_OSD_ID_SUB_DUAL);
    if (m_OSD[DATESTAMP_THUMB_OSD_ID_SUB_DUAL])
        AHC_OSDDestroyBuffer(DATESTAMP_THUMB_OSD_ID_SUB_DUAL);
    // Reset OSD attribute
    for (i = 0; i < MAX_OSD_LAYER; i++) {
        m_OSD[i]        = NULL;
        m_bOSDConfig[i] = AHC_FALSE;
    }

    m_ulOSDLayerCount = 0;

    // Inactive windows layer
    AHC_SetDisplayMode(DISPLAY_MODE_DISABLE);

    // Delete semaphore
    AHC_OS_DeleteSem(m_GUIDMASemID);
    m_GUIDMASemID = 0xFF;

    AHC_OS_DeleteSem(m_GUISemID);
    m_GUISemID = -1;

    AHC_OS_DeleteSem(gulDrawingSemID);
    gulDrawingSemID = -1;

    // Clear Init Status
    m_ulInitGUI = 0;

    // Disable drawing reserved osd layer
    AIHC_DrawReservedOSD(AHC_FALSE);

    AHC_OSDUpdateAddrOnly(AHC_FALSE);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDCreateBuffer
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Create OSD buffer

 This API create a buffer for OSD which will inherit the attributes of current displaying one,

 @param[in] uwDisplayID     The buffer index for OSD buffer creation
 @param[in] uwWidth         The width of the buffer
 @param[in] uwHeight        The height of the buffer
 @param[in] uiColorFormat   The color format of the buffer
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDCreateBuffer(UINT16 uwDisplayID, UINT16 uwWidth, UINT16 uwHeight, AHC_OSD_COLOR_FMT uiColorFormat)
{
    UINT32                      size, byte, i;
    UINT32                      AlphaFormat;
    MMP_DISPLAY_WIN_COLORDEPTH  color;
    AHC_DISPLAY_OUTPUTPANEL     device;

    if (!m_bDrawReserved) {
        if (uwDisplayID >= MAX_OSD_NUM)
            return AHC_FALSE;
    }
    else {
        if (uwDisplayID >= MAX_OSD_LAYER)
            return AHC_FALSE;
    }

    if (m_OSD[uwDisplayID]) {
        return AHC_FALSE;
    }

    AHC_GetDisplayOutputDev(&device);
    if(device == AHC_DISPLAY_MAIN_LCD){
        if ((uwDisplayID < MAX_OSD_NUM) && ((uwWidth * OSD_DISPLAY_SCALE_LCD > DISP_WIDTH) || (uwHeight * OSD_DISPLAY_SCALE_LCD > DISP_HEIGHT)))
        {
            RTNA_DBG_Str(0, FG_GREEN("OSD_DISPLAY_SCALE_LCD & DISP_WIDTH & DISP_HEIGHT  not match, it may cause OSD error\r\n"));
            // return AHC_FALSE;
        }
    }
    switch(uiColorFormat) {
    case OSD_COLOR_RGB332:
        color = MMP_DISPLAY_WIN_COLORDEPTH_8;
        byte  = 1;
        AlphaFormat = AHC_OSD_ALPHA_GLOBAL;
        break;
    case OSD_COLOR_ARGB3454:
        color = MMP_DISPLAY_WIN_COLORDEPTH_16;
        byte = 2;
        AlphaFormat = AHC_OSD_ALPHA_ARGB;
        break;
    case OSD_COLOR_RGB565:
    case OSD_COLOR_RGB565_CCW:
        color = MMP_DISPLAY_WIN_COLORDEPTH_16;
        byte  = 2;
        AlphaFormat = AHC_OSD_ALPHA_GLOBAL;
        break;
    case OSD_COLOR_RGB888:
        color = MMP_DISPLAY_WIN_COLORDEPTH_24;
        byte  = 3;
        AlphaFormat = AHC_OSD_ALPHA_GLOBAL;
        break;
    case OSD_COLOR_ARGB32:
    case OSD_COLOR_ARGB32_CCW:
        color = MMP_DISPLAY_WIN_COLORDEPTH_32;
        byte  = 4;
        AlphaFormat = AHC_OSD_ALPHA_ARGB;
        break;
    default:
        return AHC_FALSE;
        break;
    }

    size = uwWidth * uwHeight * byte;

    /* Allocate OSD Instance */
    m_OSD[uwDisplayID] = (AHC_OSD_INSTANCE*)CamOsMemAlloc(sizeof(AHC_OSD_INSTANCE));

    if (!m_OSD[uwDisplayID]) {
        return AHC_FALSE;
    }

    MEMSET(m_OSD[uwDisplayID], 0, sizeof(AHC_OSD_INSTANCE));

    /* Set OSD Window ID */
    if (uwDisplayID < 16) {
        m_OSD[uwDisplayID]->id = WMSG_LAYER_WINDOW_ID;
    }
    else if (uwDisplayID < 32) {
        m_OSD[uwDisplayID]->id = OSD_LAYER_WINDOW_ID;
    }
    else if ((uwDisplayID == DATESTAMP_PRIMARY_OSD_ID) ||
             (uwDisplayID == DATESTAMP_THUMB_OSD_ID)) {
        m_OSD[uwDisplayID]->id = OSD_LAYER_WINDOW_ID;
    }
    else {
        m_OSD[uwDisplayID]->id = LOWER_IMAGE_WINDOW_ID;
    }

    /* Set OSD Attribute */
    if (uiColorFormat == OSD_COLOR_ARGB32_CCW)
        m_OSD[uwDisplayID]->Color   = OSD_COLOR_ARGB32;
    else if (uiColorFormat == OSD_COLOR_RGB565_CCW)
        m_OSD[uwDisplayID]->Color   = OSD_COLOR_RGB565;
    else
        m_OSD[uwDisplayID]->Color   = uiColorFormat;

    m_OSD[uwDisplayID]->ColorFormat  = color;
    m_OSD[uwDisplayID]->size         = size;
    m_OSD[uwDisplayID]->width        = uwWidth;
    m_OSD[uwDisplayID]->height       = uwHeight;
    m_OSD[uwDisplayID]->line_offset  = uwWidth * byte;
    m_OSD[uwDisplayID]->data         = (UINT8*)AIHC_GUIMalloc(size);

    if (!m_OSD[uwDisplayID]->data) {
        return AHC_FALSE;
    }

    MEMSET(m_OSD[uwDisplayID]->data,0,size);

    //UartSendTrace("buf[%02d] %08X %dx%dx%d\r\n", uwDisplayID, (UINT32)(m_OSD[uwDisplayID]->data), uwWidth, uwHeight, byte);

    /* Default Setting */
    m_OSD[uwDisplayID]->bMirror                 = 0;
    m_OSD[uwDisplayID]->rotate_type             = AHC_OSD_ROTATE_NONE;
    m_OSD[uwDisplayID]->TransparentEnable       = 0;
    m_OSD[uwDisplayID]->TransparentColor        = 0x00000000;
    m_OSD[uwDisplayID]->SemiTpEnable            = 0;
    m_OSD[uwDisplayID]->SemiTpType              = AHC_OSD_SEMITP_AVG;
    m_OSD[uwDisplayID]->SemiTpWeight            = 0;
    m_OSD[uwDisplayID]->AlphaBlendingEnable     = 0;
    m_OSD[uwDisplayID]->AlphaFormat             = AlphaFormat;
    m_OSD[uwDisplayID]->DisplayOffsetX          = 0;
    m_OSD[uwDisplayID]->DisplayOffsetY          = 0;
    m_OSD[uwDisplayID]->AlphaWeight             = 0;

#if (TVOUT_PREVIEW_EN)
    if(AHC_IsTVConnectEx()){
        m_OSD[uwDisplayID]->DuplicateW              = MMP_DISPLAY_DUPLICATE_1X;
        m_OSD[uwDisplayID]->DuplicateH              = MMP_DISPLAY_DUPLICATE_1X;
    }
    else
#endif
#if (HDMI_PREVIEW_EN)
    if (AHC_IsHdmiConnect()){
        m_OSD[uwDisplayID]->DuplicateW              = MMP_DISPLAY_DUPLICATE_1X;
        m_OSD[uwDisplayID]->DuplicateH              = MMP_DISPLAY_DUPLICATE_1X;
    }
    else
#endif
    {
        #if (OSD_DISPLAY_SCALE_LCD == 1 || OSD_DISPLAY_SCALE_LCD == 0)
        m_OSD[uwDisplayID]->DuplicateW              = MMP_DISPLAY_DUPLICATE_1X;
        m_OSD[uwDisplayID]->DuplicateH              = MMP_DISPLAY_DUPLICATE_1X;
        #elif (OSD_DISPLAY_SCALE_LCD > 5)
        m_OSD[uwDisplayID]->DuplicateW              = MMP_DISPLAY_DUPLICATE_6X;
        m_OSD[uwDisplayID]->DuplicateH              = MMP_DISPLAY_DUPLICATE_6X;
        UartSendTrace(FG_RED("ERR_OSD: duplicate ratio exceed 6X!\r\n"));
        #else //TBD
        m_OSD[uwDisplayID]->DuplicateW              = OSD_DISPLAY_SCALE_LCD - 1; // Map to MMP_DISPLAY_DUPLICATE
        m_OSD[uwDisplayID]->DuplicateH              = OSD_DISPLAY_SCALE_LCD - 1;
        #endif
    }

    if ((uwDisplayID == DATESTAMP_PRIMARY_OSD_ID) ||
        (uwDisplayID == DATESTAMP_THUMB_OSD_ID))
    {
        MMP_ULONG ulColor;

        #if (STICKER_PATTERN)
        ulColor = STICKER_PATTERN_COLOR;
        #else
        ulColor = DATESTAMP_COLOR;
        #endif

        for (i = 0; i < (256*4); i+=4)
        {
            m_OSD[uwDisplayID]->palette[i]      = (ulColor) & 0xFF;       //B
            m_OSD[uwDisplayID]->palette[i+1]    = (ulColor >> 8) & 0xFF;  //G
            m_OSD[uwDisplayID]->palette[i+2]    = (ulColor >> 16) & 0xFF; //R
            m_OSD[uwDisplayID]->palette[i+3]    = (ulColor >> 24) & 0xFF; //A
        }

        ulColor = DATESTAMP_COLOR;
        m_OSD[uwDisplayID]->palette[255*4]      = (ulColor) & 0xFF;       //B
        m_OSD[uwDisplayID]->palette[255*4+1]    = (ulColor >> 8) & 0xFF;  //G
        m_OSD[uwDisplayID]->palette[255*4+2]    = (ulColor >> 16) & 0xFF; //R
        m_OSD[uwDisplayID]->palette[255*4+3]    = (ulColor >> 24) & 0xFF; //A

        #if (STICKER_DRAW_EDGE)
        m_OSD[uwDisplayID]->palette[4]          = 0xFF; //B
        m_OSD[uwDisplayID]->palette[4+1]        = 0xFF; //G
        m_OSD[uwDisplayID]->palette[4+2]        = 0xFF; //R
        m_OSD[uwDisplayID]->palette[4+3]        = 0xFF; //A
        #endif
    }
    else {
#if 1 //For better performance.
        MEMSET((void *)&m_OSD[uwDisplayID]->palette[0], 0, 256*4);
#else
        for (i = 0; i < (256*4); i++) {
            m_OSD[uwDisplayID]->palette[i]      = 0;
        }
#endif
    }

    GUI_CreateLayer(MsPA2VA((U32)m_OSD[uwDisplayID]->data), uwWidth, uwHeight, uiColorFormat, uwDisplayID);

    m_bOSDConfig[uwDisplayID] = AHC_TRUE;

    /* Initial GUI attribute */
    //m_OSD[uwDisplayID]->gui.gui_drawmode = OSD_FLIP_DRAW_NONE_ENABLE;

    m_OSD[uwDisplayID]->gui.gui_semi     = AHC_OS_CreateSem(1);

    if (m_OSD[uwDisplayID]->gui.gui_semi >= 0xFE) {
        UartSendTrace(">>>The Semaphore Resource is not enough (%d)!!!\r\n", uwDisplayID);
    }

    m_ulOSDLayerCount++;

    return AHC_TRUE;
}

AHC_BOOL AHC_OSDChangeDimetion(UINT16 uwDisplayID, UINT16 uwWidth, UINT16 uwHeight)
{
    UINT32 size, byte;
    MMP_DISPLAY_WIN_COLORDEPTH  color;

    if(  m_OSD[uwDisplayID] == NULL ){
        return AHC_FALSE;
    }

    switch(m_OSD[uwDisplayID]->Color) {
    case OSD_COLOR_RGB332:
        color = MMP_DISPLAY_WIN_COLORDEPTH_8;
        byte  = 1;
        break;
    case OSD_COLOR_ARGB3454:
    case OSD_COLOR_RGB565:
    case OSD_COLOR_RGB565_CCW:
        color = MMP_DISPLAY_WIN_COLORDEPTH_16;
        byte  = 2;
        break;
    case OSD_COLOR_RGB888:
        color = MMP_DISPLAY_WIN_COLORDEPTH_24;
        byte  = 3;
        break;
    case OSD_COLOR_ARGB32:
    case OSD_COLOR_ARGB32_CCW:
        color = MMP_DISPLAY_WIN_COLORDEPTH_32;
        byte  = 4;
        break;
    default:
        return AHC_FALSE;
        break;
    }

    size = uwWidth * uwHeight * byte;

    if( (uwWidth * uwHeight * byte) > m_OSD[uwDisplayID]->size ){
        // size is too big.
        return AHC_FALSE;
    }

    m_OSD[uwDisplayID]->width        = uwWidth;
    m_OSD[uwDisplayID]->height       = uwHeight;
    m_OSD[uwDisplayID]->line_offset  = uwWidth * byte;

  //  GUI_CreateLayer((U32)(m_OSD[uwDisplayID]->data),m_OSD[uwDisplayID]->width, m_OSD[uwDisplayID]->height,color, uwDisplayID);
    GUI_SetLayerSizeEx(uwDisplayID, uwWidth, uwHeight);
    GUI_SetLayerVSizeEx(uwDisplayID, uwWidth,  uwHeight);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDestroyBuffer
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Destroy OSD buffer

 This API destroy OSD buffer,

 @param[in] uwDisplayID         The buffer index for OSD buffer.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDestroyBuffer(UINT16 uwDisplayID)
{
    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        UartSendTrace("--E-- %s: Wrong uwDisplayID - %d!!!\r\n", __FUNCTION__, uwDisplayID);
        return AHC_FALSE;
    }

    #if 0
    if (m_GUISemID >= 0xFE) {
        UartSendTrace("--E-- %s: Wrong m_GUISemID - %d!!!\r\n", __FUNCTION__, m_GUISemID);
        return AHC_FALSE;
    }

    if (AHC_OS_AcquireSem(m_GUISemID, GUI_SEM_WAIT_TIME) != MMPF_OS_ERR_NONE) {
        UartSendTrace("--E-- %s:%d Wait m_GUISemID semiphore timeout !!!\r\n", __FUNCTION__, uwDisplayID);
        return AHC_FALSE;
    }
    #endif

    if (m_OSD[uwDisplayID]->data) {
        AIHC_GUIFree(m_OSD[uwDisplayID]->data);
    }

    m_OSD[uwDisplayID]->data = 0;

    AHC_OS_DeleteSem(m_OSD[uwDisplayID]->gui.gui_semi);

    ///////////////////////////////////////////////////////////////////
    // Keep at last
    CamOsMemRelease(m_OSD[uwDisplayID]);
    m_OSD[uwDisplayID] = 0;
    ///////////////////////////////////////////////////////////////////

    m_ulOSDLayerCount--;

    #if 0
    if (AHC_OS_ReleaseSem(m_GUISemID) != MMPF_OS_ERR_NONE) {
        UartSendTrace("--E-- %s:%d AHC_OS_ReleaseSem !!!\r\n", __FUNCTION__, uwDisplayID);
        return AHC_FALSE;
    }
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDSetDisplayAttr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set OSD attributes

 This API set OSD attributes,

 @param[in] byDisplayID    The buffer index for OSD buffer creation
 @param[in] byAttr         OSD attribute type
 @param[in] ulParam        OSD attribute parameters

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDSetDisplayAttr(UINT8 byDisplayID, AHC_OSD_ATTR byAttr, UINT32 ulParam[])
{
    U32 i;

    if (AHC_OSDCheckDrawLayer(byDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    switch(byAttr)
    {
    case AHC_OSD_ATTR_MIRROR:
        m_OSD[byDisplayID]->bMirror = ulParam[0];
        break;
    case AHC_OSD_ATTR_ROTATE:
        m_OSD[byDisplayID]->rotate_type = ulParam[0];
        break;
    case AHC_OSD_ATTR_TRANSPARENT_ENABLE:
        m_OSD[byDisplayID]->TransparentEnable = ulParam[0];
        m_OSD[byDisplayID]->TransparentColor = ulParam[1];
        break;
    case AHC_OSD_ATTR_SEMI_TRANSPARENT_ENABLE:

        if ( (AHC_OSD_SEMITP_AVG == ulParam[1]) ||
             (AHC_OSD_SEMITP_AND == ulParam[1]) ||
             (AHC_OSD_SEMITP_OR  == ulParam[1]) ||
             (AHC_OSD_SEMITP_INV == ulParam[1])) {

             m_OSD[byDisplayID]->SemiTpType = ulParam[1];

             if (ulParam[2] <= 255) {
                m_OSD[byDisplayID]->SemiTpWeight = ulParam[2];
             }
             else {
                return AHC_FALSE;
             }
        }
        else {
            return AHC_FALSE;
        }

        m_OSD[byDisplayID]->SemiTpEnable = ulParam[0];
        break;
    case AHC_OSD_ATTR_ALPHA_BLENDING_ENABLE:
        {
            MMP_BOOL NewAlphaEn = ulParam[0];
            AHC_OSD_ALPHA_FMT NewAlphaFmt = ulParam[1];
            MMP_BYTE NewAlphaWeight = ulParam[2];

            if (m_OSD[byDisplayID]->Color == OSD_COLOR_RGB332 ||
                m_OSD[byDisplayID]->Color == OSD_COLOR_RGB565 ||
                m_OSD[byDisplayID]->Color == OSD_COLOR_RGB565_CCW ||
                m_OSD[byDisplayID]->Color == OSD_COLOR_RGB888 ||
                m_OSD[byDisplayID]->Color == OSD_COLOR_YUV422) {

                if ((NewAlphaFmt == AHC_OSD_ALPHA_ARGB ||
                    NewAlphaFmt == AHC_OSD_ALPHA_RGBA) &&
                    NewAlphaEn == AHC_TRUE) {
                    // The color format doesn't contains alpha value.
                    // Therefore, it is not allow to set the alpha mode to AHC_OSD_ALPHA_ARGB or AHC_OSD_ALPHA_RGBA.
                    return FALSE;
                }
            }

            m_OSD[byDisplayID]->AlphaBlendingEnable = NewAlphaEn;
            m_OSD[byDisplayID]->AlphaFormat = NewAlphaFmt;
            m_OSD[byDisplayID]->AlphaWeight = NewAlphaWeight;
        }
        break;
    case AHC_OSD_ATTR_DISPLAY_OFFSET:
        m_OSD[byDisplayID]->DisplayOffsetX = ulParam[0];
        m_OSD[byDisplayID]->DisplayOffsetY = ulParam[1];
        break;
    case AHC_OSD_ATTR_DISPLAY_SCALE:
        m_OSD[byDisplayID]->DuplicateW = ulParam[0];
        m_OSD[byDisplayID]->DuplicateH = ulParam[1];
        break;

    case AHC_OSD_ATTR_ROTATE_BY_GUI:
        m_OSD[byDisplayID]->gui.ulRotateByGUI = ulParam[0];
        break;

    case AHC_OSD_ATTR_FLIP_BY_GUI:
        m_OSD[byDisplayID]->gui.ulFlipByGUI = ulParam[0];
        break;
    }

    m_bOSDConfig[byDisplayID] = AHC_TRUE;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDuplicateBuffer
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Duplicate OSD buffer

 This API duplicate OSD buffer,

 @param[in] uwSrcIndex         The source buffer index for OSD buffer
 @param[in] uwDesIndex         The destination buffer index for OSD buffer
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDuplicateBuffer(UINT16 uwSrcIndex, UINT16 uwDesIndex)
{
    if (uwSrcIndex == uwDesIndex) {
        return AHC_TRUE;
    }

    if (!m_bDrawReserved) {
        if (uwSrcIndex >= MAX_OSD_NUM)
            return AHC_FALSE;
        if (uwDesIndex >= MAX_OSD_NUM)
            return AHC_FALSE;
    }
    else {
        if (uwSrcIndex >= MAX_OSD_LAYER)
            return AHC_FALSE;
        if (uwDesIndex >= MAX_OSD_LAYER)
            return AHC_FALSE;
    }

    if (!m_OSD[uwSrcIndex])
        return AHC_FALSE;
    if (!m_OSD[uwDesIndex])
        return AHC_FALSE;

    if ((m_OSD[uwSrcIndex]->size        != m_OSD[uwDesIndex]->size) ||
        (m_OSD[uwSrcIndex]->ColorFormat != m_OSD[uwDesIndex]->ColorFormat))
    {
        return AHC_FALSE;
    }

    DrvBdma_Transfer(DRV_BDMA_MIU2MIU, (u8*)MsPA2VA(m_OSD[uwSrcIndex]->data), (UINT32)MsPA2VA(m_OSD[uwDesIndex]->data), m_OSD[uwDesIndex]->size);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDRefresh
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Refresh OSD

 This API refreshes the current OSD buffer to display. This refresh includes both OSD layer 1 and 2.
 Parameters:
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDRefresh(void)
{

    MMPS_Display_SetDisplayRefresh();

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDRefresh_PLCD
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Refresh OSD for PLCD / PLCD-FLM

 This API refreshes the current OSD buffer to display. This refresh includes both OSD layer 1 and 2.
 Parameters:
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDRefresh_PLCD(void)
{
    AHC_DISPLAY_OUTPUTPANEL outputDevice;

    AHC_GetDisplayOutputDev(&outputDevice);

    switch (outputDevice)
    {
    case AHC_DISPLAY_MAIN_LCD:
    case AHC_DISPLAY_SUB_LCD:
        switch (RTNA_LCD_GetAttr()->ubDevType)
        {
        case LCD_TYPE_PLCD:
        case LCD_TYPE_PLCD_FLM:
            AHC_OSDRefresh();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDGetBufferAttr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get OSD attributes

 This API get OSD attributes,

 @param[in] uwDisplayID     The buffer index for OSD buffer creation
 @param[in] puiWidth        OSD width
 @param[in] puiHeight       OSD height
 @param[in] puiColorFormat  OSD color format
 @param[in] pulBufferAddr   OSD data address

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDGetBufferAttr(UINT8 uwDisplayID, UINT16 *puiWidth, UINT16 *puiHeight, UINT16 *puiColorFormat, UINT32 *pulBufferAddr)
{
    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    *puiWidth = m_OSD[uwDisplayID]->width;
    *puiHeight = m_OSD[uwDisplayID]->height;

    if (MMP_DISPLAY_WIN_COLORDEPTH_16 == m_OSD[uwDisplayID]->ColorFormat)
        *puiColorFormat = OSD_COLOR_RGB565;
    else if (MMP_DISPLAY_WIN_COLORDEPTH_24 == m_OSD[uwDisplayID]->ColorFormat)
        *puiColorFormat = OSD_COLOR_RGB888;
    else if (MMP_DISPLAY_WIN_COLORDEPTH_32 == m_OSD[uwDisplayID]->ColorFormat)
        *puiColorFormat = OSD_COLOR_ARGB32;
    else if (MMP_DISPLAY_WIN_COLORDEPTH_8 == m_OSD[uwDisplayID]->ColorFormat)
        *puiColorFormat = OSD_COLOR_RGB332;

    *pulBufferAddr  = (MMP_ULONG)m_OSD[uwDisplayID]->data;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDDuplicateAttr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Duplicate OSD attributes

 This API duplicate OSD attributes,

 @param[in] uwSrcIndex     The source index for OSD buffer
 @param[in] uwDesIndex     The destination index for OSD buffer

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDDuplicateAttr(UINT16 uwSrcIndex, UINT16 uwDesIndex)
{
    if (!m_bDrawReserved) {
        if (uwSrcIndex >= MAX_OSD_NUM)
            return AHC_FALSE;
        if (uwDesIndex >= MAX_OSD_NUM)
            return AHC_FALSE;
    }
    else {
        if (uwSrcIndex >= MAX_OSD_LAYER)
            return AHC_FALSE;
        if (uwDesIndex >= MAX_OSD_LAYER)
            return AHC_FALSE;
    }

    if (!m_OSD[uwSrcIndex])
        return AHC_FALSE;
    if (!m_OSD[uwDesIndex])
        return AHC_FALSE;

    MEMCPY(m_OSD[uwDesIndex], m_OSD[uwSrcIndex], sizeof(AHC_OSD_INSTANCE));

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDClearBuffer
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Clear OSD buffer

 This API clear OSD buffer,

 @param[in] uwDisplayID     The buffer index for OSD buffer

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDClearBuffer(UINT16 uwDisplayID)
{
    int iColorDepth = 0;

    if (!m_ulInitGUI) {
        //During InitOSDCustom_Lcd, it is called without m_ulInitGUI.
        //return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);

    switch(m_OSD[uwDisplayID]->ColorFormat) {
    case MMP_DISPLAY_WIN_COLORDEPTH_8:
        iColorDepth  = 1;
        break;
    case MMP_DISPLAY_WIN_COLORDEPTH_16:
        iColorDepth  = 2;
        break;
    case MMP_DISPLAY_WIN_COLORDEPTH_24:
        iColorDepth  = 3;
        break;
    case MMP_DISPLAY_WIN_COLORDEPTH_32:
        iColorDepth  = 4;
        break;
    default:
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0);
        return AHC_FALSE;
        break;
    }

    DrvBdma_FillPattern((u32)MsPA2VA(m_OSD[uwDisplayID]->data), m_OSD[uwDisplayID]->size, 0);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDSetActive
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Active the OSD window

 This API active the OSD window,

 @param[in] uwDisplayID     The buffer index for OSD buffer
 @param[in] bActive         active or not

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDSetActive(UINT16 uwDisplayID, UINT8 bActive)
{
    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    if (bActive) {
        if (uwDisplayID < 16)
            m_lCurrentLayer1ID = uwDisplayID;
        else if (uwDisplayID < 32)
            m_lCurrentLayer2ID = uwDisplayID;
        else
            m_lCurrentLayer3ID = uwDisplayID;
    }
    else {
        if (uwDisplayID < 16)
            m_lCurrentLayer1ID = -1;
        else if (uwDisplayID < 32)
            m_lCurrentLayer2ID = -1;
        else
            m_lCurrentLayer3ID = -1;
    }

    MMPS_Display_SetWinActive(m_OSD[uwDisplayID]->id, bActive);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDUpdateAddrOnly
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDUpdateAddrOnly(AHC_BOOL OSDUpdateAddrOnly)
{
    m_OSDUpdateAddrOnly = OSDUpdateAddrOnly;
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDSetCurrentDisplay
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set the OSD attributes to the display window

 This API set the OSD attributes to the display window.

 @param[in] uwDisplayID     The buffer index for OSD buffer

 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_OSDSetCurrentDisplay(UINT16 uwDisplayID)
{
    MMP_DISPLAY_WIN_ATTR    winAttr;
    MMP_DISPLAY_DISP_ATTR   dispAttr;
    MMP_DISPLAY_WIN_ALPHA_ATTR  alphaAttr;
    AHC_DISPLAY_OUTPUTPANEL OutputDevice;

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    if (uwDisplayID < 16) {
        m_ulOSDLayer1BufAddr = (UINT32)m_OSD[uwDisplayID]->data;
    }
    else if (uwDisplayID < 32) {
        m_ulOSDLayer2BufAddr = (UINT32)m_OSD[uwDisplayID]->data;
    }
    else {
        m_ulOSDLayer3BufAddr = (UINT32)m_OSD[uwDisplayID]->data;
    }

    m_ulCurrentOSDID = uwDisplayID;

    if ((m_bOSDConfig[uwDisplayID] == AHC_TRUE) && (!m_OSDUpdateAddrOnly)) {

        uwDisplayID                     = m_ulCurrentOSDID;

        /* Set Window Attribute */
        winAttr.usLineOffset            = m_OSD[uwDisplayID]->line_offset;
        winAttr.usWidth                 = m_OSD[uwDisplayID]->width;

        #if (SUPPORT_HDMI)
        {
            winAttr.usHeight            = m_OSD[uwDisplayID]->height;
        }
        #else
        winAttr.usHeight                = m_OSD[uwDisplayID]->height;
        #endif

        //winAttr.colordepth                = m_OSD[uwDisplayID]->ColorFormat;
        switch (m_OSD[uwDisplayID]->Color) {
            case OSD_COLOR_RGB565:
            case OSD_COLOR_RGB565_CCW:
                winAttr.ColorFmt = MMP_DISPLAY_WIN_COLOR_RGB565;
                break;
            case OSD_COLOR_ARGB32:
            case OSD_COLOR_ARGB32_CCW:
                winAttr.ColorFmt = MMP_DISPLAY_WIN_COLOR_ARGB8888;
                break;
            case OSD_COLOR_YUV422:
                winAttr.ColorFmt = MMP_DISPLAY_WIN_COLOR_YUV422;
                break;
            case OSD_COLOR_RGB332:
            case OSD_COLOR_RGB888:
            case OSD_COLOR_ARGB3454:
            default:
                // GOP not support
                return AHC_FALSE;
        }

        #if (SUPPORT_HDMI)
#if 0
        if (HDMIFunc_GetStatus() == AHC_HDMI_MENU_STATUS) {
            winAttr.ulBaseAddr          = (UINT32)m_OSD[uwDisplayID]->data+320*240*2;   // TBD, do not used hard code, like 320x240
        }
        else
#endif
        {
            winAttr.ulBaseAddr          = (UINT32)m_OSD[uwDisplayID]->data;
        }
        #else
        winAttr.ulBaseAddr              = (UINT32)m_OSD[uwDisplayID]->data;
        #endif

        /* Set Display Attribute */
        dispAttr.usStartX               = 0;
        dispAttr.usStartY               = 0;

        if ((AHC_OSD_ROTATE_NONE      == m_OSD[uwDisplayID]->rotate_type) ||
            (AHC_OSD_ROTATE_RIGHT_180 == m_OSD[uwDisplayID]->rotate_type))
        {
            dispAttr.usDisplayWidth     = m_OSD[uwDisplayID]->width;

            #if (SUPPORT_HDMI)
#if 0
            if (HDMIFunc_GetStatus() == AHC_HDMI_MENU_STATUS){

                switch(MenuSettingConfig()->uiHDMIOutput) {
                    case HDMI_OUTPUT_1080I:
                        dispAttr.usDisplayHeight   = m_OSD[uwDisplayID]->height*4/5;
                    break;
                    case HDMI_OUTPUT_720P:
                        dispAttr.usDisplayHeight   = m_OSD[uwDisplayID]->height*3/4;
                    break;
                    case HDMI_OUTPUT_480P:
                        dispAttr.usDisplayHeight   = m_OSD[uwDisplayID]->height*3/4;
                    break;
                    default:
                    case HDMI_OUTPUT_1080P:
                        dispAttr.usDisplayHeight   = m_OSD[uwDisplayID]->height*3/4;
                    break;
                }
            }
            else
#endif
            {
                dispAttr.usDisplayHeight = m_OSD[uwDisplayID]->height;
            }
            #else
            dispAttr.usDisplayHeight   = m_OSD[uwDisplayID]->height;
            #endif
        }
        else {
            dispAttr.usDisplayWidth    = m_OSD[uwDisplayID]->height;
            dispAttr.usDisplayHeight   = m_OSD[uwDisplayID]->width;
        }

        dispAttr.usDisplayOffsetX      = m_OSD[uwDisplayID]->DisplayOffsetX;
        dispAttr.usDisplayOffsetY      = m_OSD[uwDisplayID]->DisplayOffsetY;
        dispAttr.bMirror               = m_OSD[uwDisplayID]->bMirror;
        dispAttr.rotatetype            = m_OSD[uwDisplayID]->rotate_type;

        AHC_GetDisplayOutputDev(&OutputDevice);
        MMPS_Display_SetOutputPanel(MMP_DISPLAY_PRM_CTL, OutputDevice);

        // Rogers@20110811: Patch for OSD display to HDMI1080I
        if( (OutputDevice == MMP_DISPLAY_SEL_HDMI) &&
            (MMPS_Display_GetConfig()->hdmi.ubOutputMode == MMP_HDMI_OUTPUT_1920X1080I)) {

            winAttr.usLineOffset       = winAttr.usLineOffset << 1;
            winAttr.usHeight           = winAttr.usHeight >> 1;
            dispAttr.usDisplayHeight   = dispAttr.usDisplayHeight >> 1;
        }

        // Load palette, TBD
        //if (OSD_COLOR_RGB332 == m_OSD[uwDisplayID]->Color) {
        //    MMPS_Display_LoadWinPalette (m_OSD[uwDisplayID]->id,
        //                                (MMP_UBYTE*)m_OSD[uwDisplayID]->palette, 256);
        //}

        //MMPS_Display_SetWinTransparent( m_OSD[uwDisplayID]->id,
        //                                m_OSD[uwDisplayID]->TransparentEnable,
        //                                m_OSD[uwDisplayID]->TransparentColor);
        winAttr.bTransColorEn = m_OSD[uwDisplayID]->TransparentEnable;
        winAttr.ulTransColor = m_OSD[uwDisplayID]->TransparentColor;

        // Set alpha blending attributes.
        if (m_OSD[uwDisplayID]->AlphaBlendingEnable) {
            winAttr.AlphaAttr.fmt = m_OSD[uwDisplayID]->AlphaFormat == AHC_OSD_ALPHA_ARGB ? MMP_DISPLAY_ALPHA_ARGB :
                                    m_OSD[uwDisplayID]->AlphaFormat == AHC_OSD_ALPHA_RGBA ? MMP_DISPLAY_ALPHA_RGBA :
                                    MMP_DISPLAY_ALPHA_GLOBAL;
            winAttr.AlphaAttr.ubAlphaWeight = m_OSD[uwDisplayID]->AlphaWeight;
            //MMPS_Display_SetAlphaBlending(m_OSD[uwDisplayID]->id, &(winAttr.AlphaAttr));
        }
        else {
            winAttr.AlphaAttr.fmt = MMP_DISPLAY_ALPHA_NONE;
            winAttr.AlphaAttr.ubAlphaWeight = 0;
            //MMPS_Display_SetAlphaBlending(m_OSD[uwDisplayID]->id, &(winAttr.AlphaAttr));
        }

        // Set scaling up ratio.
        MMPS_Display_SetWinDuplicate(m_OSD[uwDisplayID]->id, m_OSD[uwDisplayID]->DuplicateW, m_OSD[uwDisplayID]->DuplicateH);

        MMPS_Display_SetWindowAttrToDisp(m_OSD[uwDisplayID]->id, winAttr, dispAttr);
        MMPS_Display_UpdateWinAddr(m_OSD[uwDisplayID]->id, (MMP_ULONG)m_OSD[uwDisplayID]->data, 0, 0);
    }
    else {
        MMPS_Display_UpdateWinAddr(m_OSD[uwDisplayID]->id, (MMP_ULONG)m_OSD[uwDisplayID]->data, 0, 0);
    }

    if (!m_OSDUpdateAddrOnly)
    {
        if ((uwDisplayID == THUMBNAIL_OSD_FRONT_ID) ||
            (uwDisplayID == THUMBNAIL_OSD_BACK_ID)) {
            // NOP
        }
        else {
            UINT16 usWinDupMode = AIHC_GetWinDupMode();

            if (MMP_DISPLAY_DUPLICATE_2X == usWinDupMode ||
                MMP_DISPLAY_DUPLICATE_4X == usWinDupMode) {
                MMPS_Display_SetWinDuplicate(m_OSD[uwDisplayID]->id, usWinDupMode, usWinDupMode);
            }
            else if (AHC_DISPLAY_DUPLICATE_4X_1X == usWinDupMode) {
                MMPS_Display_SetWinDuplicate(m_OSD[uwDisplayID]->id, MMP_DISPLAY_DUPLICATE_4X, MMP_DISPLAY_DUPLICATE_1X);
            }
        }
    #if (AHC_TV_HDMI_MENU_WIN_DUPLICTE)
    // CarDV - TV / HDMI Menu
    MMPS_Display_SetWinDuplicate(m_OSD[uwDisplayID]->id, m_OSD[uwDisplayID]->DuplicateW, m_OSD[uwDisplayID]->DuplicateH);
    #endif
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDLoadWinPalette
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDLoadWinPalette(UINT16 uwDisplayID)
{
    MMPS_Display_LoadWinPalette (m_OSD[uwDisplayID]->id,
                                (MMP_UBYTE*)m_OSD[uwDisplayID]->palette, 256);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : _AIHC_OSDColorArgbToRgb565
//  Description : Color table format transformation: from ARGB 8888 to RGB565
//------------------------------------------------------------------------------
static AHC_BOOL _AIHC_OSDColorArgbToRgb565(UINT32* uiColorArgbTable, UINT16* uwColorRgb565Table, int nNum)
{
    int    i;

    for (i = 0; i < nNum; i++)
    {
        UINT32  uiColor;

        uiColor               = uiColorArgbTable[i];
        uwColorRgb565Table[i] = (uiColor & 0xF80000) >> (24-16) |
                                (uiColor & 0x00FC00) >> (16-11) |
                                (uiColor & 0x0000F8) >> ( 8- 5) ;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDLoadIconIndexColorTable
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDLoadIconIndexColorTable(UINT16 uwDisplayID, AHC_STICKER_ID stickerID, UINT8 byColorFormat)
{
    if (byColorFormat == MMP_ICON_COLOR_INDEX8)
    {
        UINT16 uwLut[256] = {0};

        // Transfer color format
        _AIHC_OSDColorArgbToRgb565((UINT32*)m_OSD[uwDisplayID]->palette, uwLut, 256);
        MMPF_Icon_LoadIndexColorTable(stickerID, MMP_ICON_COLOR_INDEX8, uwLut, 256);
    }
    else
    {
        UINT16 uwLut[4] = {0};

        // Transfer color format
        _AIHC_OSDColorArgbToRgb565(m_StickerPalette, uwLut, 4);
        MMPF_Icon_LoadIndexColorTable(stickerID, byColorFormat, uwLut, 4);
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSDLoadIconIndexColorTable2
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSDLoadIconIndexColorTable2(AHC_STICKER_ID stickerID, UINT8 byColorFormat, UINT16* uwLutTable, int nNum)
{
    if (MMP_ERR_NONE != MMPF_Icon_LoadIndexColorTable(stickerID, byColorFormat, uwLutTable, nNum))
    {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

#if 0
void _____Unicode_GUI_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_UC_ConvertUC2UTF8
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Convert Unicode string to UTF8 string.

 @param[in] s           Input Unicode sting
 @param[in] Len         Input Unicode sting length.
 @param[out] pBuffer    Output UTF8 pBuffer
 @param[in]  BufferSize Size of UTF8 buffer

 @retval output string length.
*/
int AHC_UC_ConvertUC2UTF8(const UINT16 GUI_UNI_PTR * s, int Len, char * pBuffer, int BufferSize)
{
    return GUI_UC_ConvertUC2UTF8(s, Len, pBuffer, BufferSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_UC_ConvertUTF82UC
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Convert UTF8 string to Unicode string.

 @param[in] s           Input UTF8 sting
 @param[in] Len         Input UTF8 sting length.
 @param[out] pBuffer    Output Unicode pBuffer
 @param[in]  BufferSize Size of Unicode buffer

 @retval output string length.
*/
int AHC_UC_ConvertUTF82UC(const char GUI_UNI_PTR * s, int Len, UINT16 * pBuffer, int BufferSize)
{
    return GUI_UC_ConvertUTF82UC(s, Len, pBuffer, BufferSize );
}

//------------------------------------------------------------------------------
//  Function    : AHC_UC_Encode
//  Description :
//------------------------------------------------------------------------------
int AHC_UC_Encode(char* s, UINT16 Char)
{
    return GUI_UC_Encode(s, Char);
}

//------------------------------------------------------------------------------
//  Function    : AHC_UC_GetCharSize
//  Description :
//------------------------------------------------------------------------------
int AHC_UC_GetCharSize(const char GUI_UNI_PTR * s)
{
    return GUI_UC_GetCharSize(s);
}

//------------------------------------------------------------------------------
//  Function    : AHC_UC_GetCharCode
//  Description :
//------------------------------------------------------------------------------
UINT16 AHC_UC_GetCharCode(const char GUI_UNI_PTR * s)
{
    return GUI_UC_GetCharCode(s);
}

//------------------------------------------------------------------------------
//  Function    : AHC_UC_SetEncodeNone
//  Description :
//------------------------------------------------------------------------------
void AHC_UC_SetEncodeNone(void)
{
    GUI_UC_SetEncodeNone();
}

//------------------------------------------------------------------------------
//  Function    : AHC_UC_SetEncodeUTF8
//  Description :
//------------------------------------------------------------------------------
void AHC_UC_SetEncodeUTF8(void)
{
    GUI_UC_SetEncodeUTF8();
}

//------------------------------------------------------------------------------
//  Function    : AHC_UC_OSDDrawText
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_UC_OSDDrawText(UINT8 uwDisplayID, const UINT16 GUI_UNI_PTR *pStrPtr, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwLength)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (uwDisplayID >= MAX_OSD_NUM) {
        return AHC_FALSE;
    }

    if (!m_OSD[uwDisplayID]) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_UC_DispStringAt(pStrPtr, uwStartX, uwStartY);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_UC_DispString
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_UC_DispString(UINT8 uwDisplayID, const UINT16 GUI_UNI_PTR *s)
{
    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (uwDisplayID >= MAX_OSD_NUM) {
        return AHC_FALSE;
    }

    if (!m_OSD[uwDisplayID]) {
        return AHC_FALSE;
    }

    BEGIN_GUI_DRAW(uwDisplayID);

    GUI_SelectLayer(uwDisplayID);
    GUI_SetRotateDrawMode(m_OSD[uwDisplayID]->gui.ulRotateByGUI);
    GUI_SetFlipDrawMode(m_OSD[uwDisplayID]->gui.ulFlipByGUI);
    GUI_UC_DispString(s);

    END_GUI_DRAW(uwDisplayID);
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_UC2DB
//  Description :
//------------------------------------------------------------------------------
void AHC_UC2DB (UINT16 Code, UINT8* pOut)
{
    GUI_UC2DB(Code, pOut);
}

//------------------------------------------------------------------------------
//  Function    : AHC_DB2UC
//  Description :
//------------------------------------------------------------------------------
UINT16 AHC_DB2UC(UINT8 Byte0, UINT8 Byte1)
{
    return GUI_DB2UC( Byte0, Byte1 );
}

#if 0
void _____DotMatrix_GUI_Functions_____(){}
#endif

#ifdef DOT_MATRIX_PANEL

extern void RTNA_LCD_DispALL(MMP_UBYTE* map);
extern void RTNA_LCD_DisplayDis(void);
extern void RTNA_LCD_SetLCDInvPara(MMP_UBYTE para);

//------------------------------------------------------------------------------
//  Function    : AHC_DisplayAll
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_DisplayAll(UINT16 uwDisplayID)
{
    UINT16  puiWidth;
    UINT16  puiHeight;
    UINT16  puiColorFormat;
    UINT32  pulBufferAddr;

    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    AHC_OSDGetBufferAttr(uwDisplayID, &puiWidth, &puiHeight, &puiColorFormat, &pulBufferAddr);

    RTNA_LCD_DispALL((UINT8*)pulBufferAddr);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetDispX_Mirror
//  Description :
//------------------------------------------------------------------------------
void AHC_SetDispX_Mirror(void)
{
    RTNA_LCD_SetLCDInvPara(1);
}

//------------------------------------------------------------------------------
//  Function    : AHC_DisplayOff
//  Description :
//------------------------------------------------------------------------------
void AHC_DisplayOff(void)
{
    RTNA_LCD_DisplayDis();
}

//------------------------------------------------------------------------------
//  Function    : AHC_OSD_BufConvert
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_OSD_BufConvert(UINT16 uwDisplayID)
{
    UINT16  puiWidth;
    UINT16  puiHeight;
    UINT16  puiColorFormat;
    UINT32  pulDstBufferAddr;
    UINT8   ubPixelByte;
    UINT8   ubCol=0, ubRow=0;
    UINT8   *ubAddr, *ubDrawAddr;
    UINT16  uiDrawWidth, uiDrawHeight;

    if (!m_ulInitGUI) {
        return AHC_FALSE;
    }

    if (AHC_OSDCheckDrawLayer(uwDisplayID) == AHC_FALSE) {
        return AHC_FALSE;
    }

    AHC_OSDGetBufferAttr(uwDisplayID, &puiWidth, &puiHeight, &puiColorFormat, &pulDstBufferAddr);

    uiDrawWidth  = (puiWidth > 128) ? (128) : (puiWidth);
    uiDrawHeight = (puiHeight > 64) ? (64) : (puiHeight);

    // Find Bytes per Pixel
    switch(puiColorFormat)
    {
        case OSD_COLOR_RGB332:
            ubPixelByte  = 1;
        break;
        case OSD_COLOR_ARGB3454:
        case OSD_COLOR_RGB565:
            ubPixelByte  = 2;
        break;
        case OSD_COLOR_RGB888:
            ubPixelByte  = 3;
        break;
        case OSD_COLOR_ARGB32:
            ubPixelByte  = 4;
        break;
        default:
            ubPixelByte  = 1;
        break;
    }

    for (ubRow = 0; ubRow < uiDrawHeight; ubRow++)//Redraw to format of UC1705
    {
        ubAddr     = (UINT8*) (((UINT32)pulDstBufferAddr) + (ubRow * puiWidth * ubPixelByte));
        ubDrawAddr = (UINT8*) (((UINT32)pulDstBufferAddr) + (ubRow * uiDrawWidth * 1));

        for (ubCol = 0; ubCol < uiDrawWidth; ubCol++)
        {
            if (*(ubAddr + ubPixelByte * ubCol) != 0xFF)
            {
                *(ubDrawAddr + ubCol) = 1;//Not White Color
            }
            else
            {
                *(ubDrawAddr + ubCol) = 0;//White Color
            }
        }
    }

    return AHC_TRUE;
}
#endif

/*
 * the SEM support GUI in multitask environment
 */
void AHC_LockGUI(void)
{
    if (m_GUISemID != -1)
        AHC_OS_AcquireSem(m_GUISemID, 0);
}

void AHC_UnlockGUI(void)
{
    if (m_GUISemID != -1)
        AHC_OS_ReleaseSem(m_GUISemID);
}

UINT16 AHC_GET_ATTR_OSD_W(UINT16 uwId)
{
    AHC_DISPLAY_OUTPUTPANEL OutputDevice;

    AHC_GetDisplayOutputDev(&OutputDevice);

    if (OutputDevice == MMP_DISPLAY_SEL_MAIN_LCD ||
    OutputDevice == MMP_DISPLAY_SEL_SUB_LCD){
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        return m_OSD[uwId]->width;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        return  m_OSD[uwId]->height;
#endif
    }

    return m_OSD[uwId]->width;
}

UINT16 AHC_GET_ATTR_OSD_H(UINT16 uwId)
{
    AHC_DISPLAY_OUTPUTPANEL OutputDevice;

    AHC_GetDisplayOutputDev(&OutputDevice);

    if (OutputDevice == MMP_DISPLAY_SEL_MAIN_LCD ||
    OutputDevice == MMP_DISPLAY_SEL_SUB_LCD){

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
         return m_OSD[uwId]->height;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        return  m_OSD[uwId]->width;
#endif
    }

    return m_OSD[uwId]->height;
}

void AHC_OSD_ExternalFillRectCB(unsigned long ulDst, int iXSize, int iYSize, int iLineOffset, int iColorDepth, int iX0, int iY0, int iX1, int iY1, unsigned long usPixelIndex)
{
    switch(iColorDepth)
    {
        case MMP_DISPLAY_WIN_COLORDEPTH_8:
            iColorDepth  = 1;
            break;
        case MMP_DISPLAY_WIN_COLORDEPTH_16:
            iColorDepth  = 2;
            break;
        case MMP_DISPLAY_WIN_COLORDEPTH_24:
            iColorDepth  = 3;
            break;
        case MMP_DISPLAY_WIN_COLORDEPTH_32:
            iColorDepth  = 4;
            break;
        default:
            AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0);
            return;
    }
    if(!(iXSize*iYSize == (iX1-iX0+1)*(iY1-iY0+1)))
    {
        int iLoopX, iLoopY, iOffset;
        if(iColorDepth == 1)
        { // 8bpp SW fill rect
            u8* ptr8 = (u8*)ulDst;
            for (iLoopY = iY0; iLoopY <= iY1; iLoopY++) {
                iOffset = iLoopY * iXSize;
                for (iLoopX = iX0; iLoopX <= iX1; iLoopX++) {
                    *(ptr8 + iOffset + iLoopX) = usPixelIndex;
                }
            }
        }
        else if(iColorDepth == 2)
        { // 16bpp SW fill rect
            u16* ptr16 = (u16*)ulDst;
            for (iLoopY = iY0; iLoopY <= iY1; iLoopY++) {
                iOffset = iLoopY * iXSize;
                for (iLoopX = iX0; iLoopX <= iX1; iLoopX++) {
                    *(ptr16 + iOffset + iLoopX) = usPixelIndex;
                }
            }
        }
        else if(iColorDepth == 3)
        { // 24bpp SW fill rect
            u8* ptr8 = (u8*)ulDst;
            for (iLoopY = iY0; iLoopY <= iY1; iLoopY++) {
                iOffset = iLoopY * iXSize;
                for (iLoopX = iX0; iLoopX <= iX1; iLoopX++) {
                    *(ptr8 + iOffset * 3 + iLoopX * 3) = usPixelIndex;
                }
            }
        }
        else if(iColorDepth == 4)
        { // 32bpp SW fill rect
            u32* ptr32 = (u32*)ulDst;
            for (iLoopY = iY0; iLoopY <= iY1; iLoopY++) {
                iOffset = iLoopY * iXSize;
                for (iLoopX = iX0; iLoopX <= iX1; iLoopX++) {
                    *(ptr32 + iOffset + iLoopX) = usPixelIndex;
                }
            }
        }
    }
    else
    {
        DrvBdmaErr_e tRet;
        unsigned long ulSize;
        ulSize = iXSize*iYSize*iColorDepth;
        if(iColorDepth == 2)
            usPixelIndex = (0X0000FFFF&usPixelIndex)|(usPixelIndex<<16);
        tRet = DrvBdma_FillPattern((u32)(ulDst), ulSize, usPixelIndex);
        if(tRet != DRV_BDMA_PROC_DONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,tRet); }
    }
}

void AHC_OSD_RegisterInitOSDCustomCB(void *pInitOSDCustomCB)
{
    gAHC_OSD_InitOSDCustomCB = (AHC_OSD_InitOSDCustomCB)pInitOSDCustomCB;
}
