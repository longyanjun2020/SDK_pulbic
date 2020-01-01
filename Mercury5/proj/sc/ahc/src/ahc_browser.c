/**
 @file AHC_Broswer.c
 @brief AHC browser control Function
 @author
 @version 1.0
*/

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_modectl.h"
#include "ahc_browser.h"
#include "ahc_display.h"
#include "ahc_gui.h"
#include "ahc_uf.h"
#include "ahc_dcf.h"
#include "aihc_dcf.h"
#include "aihc_browser.h"
#include "aihc_gui.h"
#include "mmps_dsc.h"
#include "mmps_vidplay.h"
#include "mmps_audio.h"
#include "mmps_system.h"
#include "ahc_parameter.h"
#include "IconDefine.h"
#include "mmpd_dma.h"
#include "mmp_graphics_inc.h"
#include "ColorDefine.h"
#include "lcd_common.h"
#include "drvMVOP.h"
#include "drv_dec_scl_hvsp_st.h"
#include "lcd_common.h"
#include "halPnl.h"
#include "drv_pnl.h"
#include "drv_bdma_pub_types.h"

/** @addtogroup AHC_BROWSER
@{
*/

/*===========================================================================
 * Macro Define
 *===========================================================================*/

#define YUV_BLACK   0x80108010

#define AHC_BROWSER_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define AHC_BROWSER_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

/*===========================================================================
 * Global variable
 *===========================================================================*/

UINT32 m_ulDrawingThumbOSD          = THUMBNAIL_OSD_FRONT_ID;

#if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)
UINT32 m_ulCCIR656buf = 0;
UINT16 m_ulWidth = 0, m_ulHeight = 0;
static volatile AHC_BOOL m_bThumbnailDMADone = AHC_FALSE;
#endif

static AHC_THUMB_ATTRIBUTE m_stThumbAttr =
{
    3,                          // u16ThumbPerRow
    3,                          // u16ThumbPerCol
    12,                         // u16ThumbHGap
    32,                         // u16ThumbVGap
    0,                          // u16TgtThumbW
    0,                          // u16TgtThumbH
    0,                          // u16CurIdx
    0x101010,                   // u32BkColor
    0x0000FF,                   // u32FocusColor
    0,                          // u32DispStartX
    0,                          // u32DispStartY
    240,                        // u32DispAreaW
    180,                        // u32DispAreaH
};

static AHC_THUMB_DRAW_FOCUS m_stThumbDrawFocus =
{
    6,                          // usThumbDrawFocusMaxCount
    94,                         // usFocusWidth
    68,                         // usFocusHeight
    {                           // pFocusStart
        {79, 49},
        {79 + 114, 49},
        {79 + 114*2, 49},
        {79, 49 + 77},
        {79 + 114, 49 + 77},
        {79 + 114*2, 49 + 77}
    },
};

/*
0~n-1, n pages
*/
static INT32  m_uiCurPage               = -1;
static INT32  m_uiMaxIdx                = -1;

static GUI_BITMAP* m_ProtectKeyTypeMenu = NULL;
static GUI_BITMAP* m_ProtectKeyTypeG    = NULL;
static GUI_BITMAP* m_ProtectKeyTypeMove = NULL;
static GUI_BITMAP* m_pBmpFileDamage     = NULL;
static GUI_BITMAP* m_pBmpEmergIcon      = NULL;

/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern AHC_BOOL gbAhcDbgBrk;
extern AHC_BOOL m_ubPlaybackRearCam;

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void _____Browser_Internal_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AIHC_Thumb_GetCurrentIdx
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get the current thumbnail index

 Retrieve the index of current displayed thumbnail.
 Parameters:
 @param[out] *pwIndex The position of current displayed thumbnail index.
 @retval AHC_TRUE Success.
*/
static AHC_BOOL AIHC_Thumb_GetCurrentIdx(UINT32 *pwIndex)
{
    *pwIndex = m_stThumbAttr.u16CurIdx;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_Thumb_SetCurrentIdx
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set the current thumbnail index

 Set the index of current displayed thumbnail.
 Parameters:
 @param[in] pwIndex The position of current displayed thumbnail index.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AIHC_Thumb_SetCurrentIdx(UINT32 pwIndex)
{
    m_stThumbAttr.u16CurIdx = (UINT16)pwIndex;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_Thumb_SetIdxByPos
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Keep the index of the DCF object

The mapping between the position and DCF index.

 Parameters:
 @param[in] uwPos   The position of the select thumbnail.
 @param[in] uiIdx   The index of the select thumbnail.

 @retval AHC_TRUE Success.
*/
static AHC_BOOL AIHC_Thumb_SetIdxByPos(UINT16 uwPos, UINT32 uiIdx)
{
    if (uwPos >= MAX_DCF_IN_THUMB) {
        return AHC_FALSE;
    }

    m_stThumbAttr.uiIdxMap[uwPos] = uiIdx;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_Thumb_CalculateRatio
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_Thumb_CalculateRatio(  UINT32 u32SrcImgW, UINT32 u32SrcImgH,
                                            UINT32 u32TgtWidth, UINT32 u32TgtHeight,
                                            UINT16* pu16ThumbW, UINT16* pu16ThumbH)
{
    MMP_BOOL  bSquarePixel = MMP_TRUE;
    MMP_ULONG ulPixelWidth = 0;
    UINT64    u64Width = 0, u64Height = 0;

#if defined(CCIR656_OUTPUT_ENABLE )&& (CCIR656_OUTPUT_ENABLE)
    AHC_DISPLAY_OUTPUTPANEL sOutputDevice;
    AHC_GetDisplayOutputDev(&sOutputDevice);

    if (AHC_DISPLAY_CCIR == sOutputDevice) {
        *puiThumbWidth = uiTargetWidth;
        *puiThumbHeight = uiTargetHeight;
        return AHC_TRUE;
    }
#endif

    MMPS_Display_CheckPixelRatio(MMP_DISPLAY_PRM_CTL, &bSquarePixel, &ulPixelWidth);

    u64Width = u32TgtHeight * u32SrcImgW / u32SrcImgH;

    // If not square pixel, calculate resolution domain value.
    if (bSquarePixel == MMP_FALSE) {
        u64Width = (u64Width << 16) / ulPixelWidth;
    }

    // Make sure width is less equal to u32TgtWidth
    if (u64Width > u32TgtWidth) {
        u64Width = u32TgtWidth;
    }

    // Calculate height
    u64Height = u64Width * u32SrcImgH / u32SrcImgW;

    // If not square pixel, calculate resolution domain value.
    if (bSquarePixel == MMP_FALSE) {
        u64Height = (u64Height * ulPixelWidth) >> 16;
    }

#if 1 // CHECK, Not Use u64Width, u64Height?
    *pu16ThumbW = (UINT16)u32TgtWidth;
    *pu16ThumbH = (UINT16)u32TgtHeight;
#else
    *pu16ThumbW = (UINT16)u64Width;
    *pu16ThumbH = (UINT16)u64Height;
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_Thumb_InitMVOP
//  Description :
//------------------------------------------------------------------------------
static void AIHC_Thumb_InitMVOP(AHC_BOOL bstart)
{
    MVOP_InputCfg               stInputCfg;
    ST_DEC_HVSP_SCALING_CONFIG  stHvspScalCfg;
    UINT32                      u32YAddr = 0, u32UVAddr = 0;
    AHC_BOOL                    b422pack = 0, bProgressive = 1;
    UINT16                      u16DispW = 0, u16DispH = 0;

    u16DispW = RTNA_LCD_GetAttr()->usPanelW;
    u16DispH = RTNA_LCD_GetAttr()->usPanelH;

    AIHC_GUI_GetOSDBufAddr(m_ulDrawingThumbOSD, &u32YAddr);

    #if 1 // YUV plane
    b422pack = 1;
    #else
    b422pack = 0;
    #endif

    if (bstart) {

        MDrv_MVOP_SetBlackBG(bstart);


        #if 1 // YUV plane
        stInputCfg.bYUV_RGB_SEL = 1;
        stInputCfg.bYUV422      = 1;
        stInputCfg.b422pack     = 1;
        stInputCfg.bDramRdContd = 1;
        #else // RGB plane
        stInputCfg.bYUV_RGB_SEL = 0;
        stInputCfg.bYUV422      = 0;
        stInputCfg.b422pack     = 0;
        stInputCfg.bDramRdContd = 0;
        #endif
        stInputCfg.u16HSize     = u16DispW;
        stInputCfg.u16VSize     = u16DispH;
        stInputCfg.u16StripSize = u16DispW;

        MDrv_MVOP_SetInputCfg(/*MVOP_INPUT_DRAM*/ 0, &stInputCfg);

        // Scaling Config
        stHvspScalCfg.u16Src_Width  = u16DispW;
        stHvspScalCfg.u16Src_Height = u16DispH;
        stHvspScalCfg.u16Dsp_Width  = u16DispW;
        stHvspScalCfg.u16Dsp_Height = u16DispH;
        stHvspScalCfg.bScl_H_Bypass = 0;
        stHvspScalCfg.bScl_V_Bypass = 0;

        Drv_DEC_HVSP_SetScaling(E_DEC_HVSP_ID_1, stHvspScalCfg, NULL);

        AHC_OS_Sleep(30);
    }

    MDrv_MVOP_SetBaseAdd((MMP_ULONG)u32YAddr,
                         (MMP_ULONG)u32UVAddr,
                         (MMP_BOOL)bProgressive,
                         (MMP_BOOL)b422pack);

    if(!bstart){
        MDrv_MVOP_SetBlackBG(bstart);
    }
    DrvLCDRefresh();
}

//------------------------------------------------------------------------------
//  Function    : AIHC_Thumb_ClearBackGround
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_Thumb_ClearBackGround(void)
{
    GUI_COLOR   eOriGUIColor;
    UINT8       bID0 = 0, bID1 = 0;
    UINT32      x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    UINT32      u32DuplW = 0, u32DuplH = 0;
    UINT32      u32BorderWidth = 1;
    UINT8       i = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0);
        return AHC_TRUE;
    }

    AHC_OSDGetDuplicateWH(bID0, &u32DuplW, &u32DuplH);

    x0 = m_stThumbDrawFocus.pFocusStart[0].PointX - u32BorderWidth-1;//REF:AIHC_Thumb_DrawFocus		u32BorderWidth-1
    y0 = m_stThumbDrawFocus.pFocusStart[0].PointY - u32BorderWidth;
    x1 = x0 + m_stThumbAttr.u16ThumbPerRow * (m_stThumbAttr.u16TgtThumbW + m_stThumbAttr.u16ThumbHGap) / (u32DuplW + 1);
    y1 = y0 + m_stThumbAttr.u16ThumbPerCol * (m_stThumbAttr.u16TgtThumbH + m_stThumbAttr.u16ThumbVGap) / (u32DuplH + 1);

    OSDDraw_EnterDrawing(&bID0, &bID1);

    AHC_DBG_MSG(0, "# ClearBackGround [%d][%d][%d][%d][%d]\r\n", bID0, x0, y0, x1, y1);

    BEGIN_LAYER(bID0);
    AIHC_DrawReservedOSD(AHC_TRUE);

    eOriGUIColor = AHC_OSDGetColor(bID0);

    AHC_OSDSetColor(bID0, m_stThumbAttr.u32BkColor /*OSD_THUMB_BACKGROUND*/);

    AHC_OSDDrawFillRect(bID0, x0, y0, x1, y1);

    AHC_OSDSetColor(bID0, eOriGUIColor);

    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);

    return AHC_TRUE;
}

AHC_BOOL AIHC_Thumb_DrawFocus(UINT16 uwFocusIndex, AHC_BOOL bClear)
{
    UINT32          u32BorderWidth = 1;
    UINT32          u32FocusRectW = 0;
    UINT32          u32FocusRectH = 0;
    UINT32          u32FocusRectStartX = 0;
    UINT32          u32FocusRectStartY = 0;
    UINT32          u32ThumbPerPage = 0;
    UINT32          u32CurPos = 0;
    UINT32          u32CurPage = 0;
    GUI_COLOR       eOriGUIColor;
    UINT8           bID0 = 0, bID1 = 0;
    UINT8           i;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0);
        return AHC_TRUE;
    }

    if (m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0) {
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    u32ThumbPerPage = m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol;
    u32CurPage      = uwFocusIndex / u32ThumbPerPage;
    u32CurPos       = uwFocusIndex - (u32CurPage * u32ThumbPerPage);

    u32FocusRectStartX  = m_stThumbDrawFocus.pFocusStart[u32CurPos].PointX;
    u32FocusRectStartY  = m_stThumbDrawFocus.pFocusStart[u32CurPos].PointY;
    u32FocusRectW       = m_stThumbDrawFocus.usFocusWidth;
    u32FocusRectH       = m_stThumbDrawFocus.usFocusHeight;

    OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);
    AIHC_DrawReservedOSD(AHC_TRUE);

    AHC_OSDSetPenSize(bID0, u32BorderWidth);

    eOriGUIColor = AHC_OSDGetColor(bID0);

    if (bClear) {
        AHC_OSDSetColor(bID0, m_stThumbAttr.u32BkColor /*OSD_THUMB_BACKGROUND*/);
    }
    else {
        AHC_OSDSetColor(bID0, m_stThumbAttr.u32FocusColor);
    }

    AHC_OSDDrawFillRect( bID0,
                         u32FocusRectStartX,
                         u32FocusRectStartY - u32BorderWidth,
                         u32FocusRectStartX + u32FocusRectW,
                         u32FocusRectStartY);

    AHC_OSDDrawFillRect( bID0,
                         u32FocusRectStartX - u32BorderWidth-1,
                         u32FocusRectStartY,
                         u32FocusRectStartX-1,
                         u32FocusRectStartY + u32FocusRectH+1);

    AHC_OSDDrawFillRect( bID0,
                         u32FocusRectStartX + u32FocusRectW + (u32BorderWidth/2),
                         u32FocusRectStartY,
                         u32FocusRectStartX + u32FocusRectW + (u32BorderWidth/2) + u32BorderWidth,
                         u32FocusRectStartY + u32FocusRectH + (u32BorderWidth/2));

    AHC_OSDDrawFillRect( bID0,
                         u32FocusRectStartX,
                         u32FocusRectStartY + u32FocusRectH + (u32BorderWidth/2),
                         u32FocusRectStartX + u32FocusRectW,
                         u32FocusRectStartY + u32FocusRectH + (u32BorderWidth/2) + u32BorderWidth);

    AHC_OSDSetColor(bID0, eOriGUIColor);

    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);

    return AHC_TRUE;
}

AHC_BOOL AIHC_Thumb_DrawYuvFillPattern(u32 nPattern)
{
    UINT32 ThumbPipAddr = 0;
    UINT16 ThumbPipWidth, ThumbPipHeight,ThumbPipColor;
    UINT8  testS[16] = {0};
    UINT8  testD[16] = {0};

    AHC_OSDGetBufferAttr(m_ulDrawingThumbOSD, &ThumbPipWidth, &ThumbPipHeight, &ThumbPipColor, &ThumbPipAddr);

    /* Workaround For Green Screen Issus */
    DrvBdma_Transfer(DRV_BDMA_MIU2MIU, testS, (UINT32)testD, 16);

    DrvBdma_FillPattern((u32)ThumbPipAddr, ThumbPipWidth*ThumbPipHeight*2, nPattern);

    return AHC_TRUE;
}

#if (AHC_BROWSER_DRAW_PROTECT_KEY)
/**
@brief  draw the icon of the attribute of the file protection
 Parameters:
 @param[in] ThumbIndex  The key of the select DCF object.
 @param[in] IconType 0:Normal lock 1:M lock 2:G lock

 @retval AHC_TRUE Success.
*/
AHC_BOOL AIHC_Thumb_DrawProtectKey(UINT16 ThumbIndex, AHC_PROTECT_TYPE IconType)
{
    GUI_BITMAP* psProtectIcon;
    UINT8       bDrawThumbIndex;
    UINT8       bID0 = 0, bID1 = 0;
    UINT8       i = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0);
        return AHC_TRUE;
    }

    switch(IconType) {
    case AHC_PROTECT_MENU:
        psProtectIcon = m_ProtectKeyTypeMenu;
        break;
    case AHC_PROTECT_G:
        psProtectIcon = m_ProtectKeyTypeG;
        break;
    default:
        psProtectIcon = NULL;
        return AHC_TRUE;
        break;
    }

    // Draw the select focus rectangle
    bDrawThumbIndex = ThumbIndex % (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    if (psProtectIcon) {
        OSDDraw_EnterDrawing(&bID0, &bID1);

        BEGIN_LAYER(bID0);
        AHC_OSDDrawBitmap(bID0,  psProtectIcon, m_stThumbDrawFocus.pFocusStart[bDrawThumbIndex].PointX+2, m_stThumbDrawFocus.pFocusStart[bDrawThumbIndex].PointY+2);
        END_LAYER(bID0);

        OSDDraw_ExitDrawing(&bID0, &bID1);
    }

    return AHC_TRUE;
}
#endif

AHC_BOOL AHC_Thumb_DrawEmptyPage(void)
{
    UINT32                  MaxDcfObjIdx = 0;
    UINT16                  OSDWidth, OSDHeight;
    AHC_DISPLAY_OUTPUTPANEL OutputDevice;
    UINT8                   bID0 = 0, bID1 = 0;
    UINT8                   i;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0);
        return AHC_TRUE;
    }

    AHC_GetDisplayOutputDev(&OutputDevice);

    if (OutputDevice == MMP_DISPLAY_SEL_MAIN_LCD) {
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        {
            UINT16  ulOSDTemp = 0;
            //Swap width/height. Rotate OSD by GUI.
            ulOSDTemp = OSDWidth;
            OSDWidth = OSDHeight;
            OSDHeight = ulOSDTemp;
        }
#endif
    }
    if (MaxDcfObjIdx == 0) {

        OSDDraw_EnterDrawing(&bID0, &bID1);

        BEGIN_LAYER(bID0);

        AHC_OSDSetColor(bID0, m_stThumbAttr.u32BkColor);
        AHC_OSDDrawFillRect(bID0,
                            m_stThumbDrawFocus.pFocusStart[0].PointX-2,
                            m_stThumbDrawFocus.pFocusStart[0].PointY-2,
                            m_stThumbDrawFocus.pFocusStart[m_stThumbAttr.u16ThumbPerCol*m_stThumbAttr.u16ThumbPerRow-1].PointX + m_stThumbDrawFocus.usFocusWidth + 2,
                            m_stThumbDrawFocus.pFocusStart[m_stThumbAttr.u16ThumbPerCol*m_stThumbAttr.u16ThumbPerRow-1].PointY + m_stThumbDrawFocus.usFocusHeight + 2);

        END_LAYER(bID0);

        OSDDraw_ExitDrawing(&bID0, &bID1);

        AIHC_DrawReservedOSD(AHC_TRUE); // TBD
        AIHC_Thumb_DrawYuvFillPattern(YUV_BLACK);
        AIHC_DrawReservedOSD(AHC_FALSE);

        m_uiCurPage = -1;
        m_uiMaxIdx  = -1;

        return AHC_TRUE;
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_Thumb_DrawPage(AHC_BOOL bForce)
{
    AHC_BOOL                    ahc_ret = AHC_TRUE;
    UINT32                      u32CurIdx = 0;
    UINT32                      u32CurPage = 0;
    UINT32                      u32MaxIdx = 0;
    UINT32                      u32ThumbPerPage = 0;
    UINT32                      uiPosY, uiPosX;
    UINT32                      u32DecodeIdx = 0;

    UINT8                       u8FileType = 0;
    INT8                        s8FilePathName[MAX_FULL_FILENAME_SIZE];
    UINT16                      OSDWidth, OSDHeight, OSDColor, u16TgtThumbW, u16TgtThumbH;
    UINT16                      usTmpW, usTmpH;
    UINT32                      OSDAddr;
    UINT32                      TargetThumbAddr = 0, ThumbPosX, ThumbPosY;
    UINT32                      u32ThumbSrcBufAddr = 0;
    UINT32                      u32ThumbOutBufAddr = 0;
    UINT16                      ThumbIndex;
    MMP_ULONG                   u32TargetThumbSize;
    #if (AHC_BROWSER_DRAW_GRAY_BORDER)
    UINT32                      BorderWidth = 4;
    UINT32                      CurrRectWidth;
    UINT32                      CurrRectHeight;
    UINT32                      CurrRectStartX;
    UINT32                      CurrRectStartY;
    UINT32                      tmpThumbPosX;
    UINT32                      tmpThumbPosY;
    #endif
    AHC_DISPLAY_OUTPUTPANEL     OutputDevice;
#if (SUPPORT_VR_THUMBNAIL)
    UINT32                      ulCurIdx = 0xFFFFFFFF;
    AHC_BOOL                    bFoundThumbInVideo = 0;
    UINT32                      u32VRThumbBufSize = 0;
    void*                       pvVRThumbBufVirt = NULL;
#endif
    UINT32                      ulVRThumbJpgW = 160, ulVRThumbJpgH = 120;
    UINT8                       bID0 = 0, bID1 = 0;
    UINT8                       i = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0);
        return AHC_TRUE;
    }

    ahc_ret = AIHC_Thumb_ClearBackGround();

    AIHC_DrawReservedOSD(AHC_TRUE);

    AHC_OSDGetBufferAttr(m_ulDrawingThumbOSD, &OSDWidth, &OSDHeight, &OSDColor, &OSDAddr);

    if (m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0) {
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    if (AHC_FALSE == AHC_UF_GetTotalFileCount(&u32MaxIdx))
    {
        if (AHC_UF_IsDBMounted()) {

            AIHC_DrawReservedOSD(AHC_FALSE);

            return AHC_FALSE;
        }
    }

    /*
    There is no dcf file in the db.
    */
    if (u32MaxIdx == 0) {
        // No DCF obj

        AIHC_Thumb_DrawYuvFillPattern(YUV_BLACK);

        AIHC_DrawReservedOSD(AHC_FALSE);

        m_uiCurPage = -1;
        m_uiMaxIdx  = -1;

        return AHC_TRUE;
    }

    AHC_GetDisplayOutputDev(&OutputDevice);

    if (OutputDevice == MMP_DISPLAY_SEL_MAIN_LCD) {

        #define HORIZONTAL_RATIO    (4)
        #define VERTICAL_RATIO      (3)

        #if (AHC_BROWSER_THUMBNAIL_STYLE == AHC_BROWSER_THUMBNAIL_STYLE_1)
        {
            UINT32 uiX = 0;
            UINT32 uiY = 0;

            uiX = (m_stThumbAttr.u32DispAreaW  - (m_stThumbAttr.u16ThumbPerRow + 1) * (m_stThumbAttr.u16ThumbHGap))
                    / (HORIZONTAL_RATIO * m_stThumbAttr.u16ThumbPerRow);

            uiY = (m_stThumbAttr.u32DispAreaH - (m_stThumbAttr.u16ThumbPerCol + 1) * (m_stThumbAttr.u16ThumbVGap))
                    / (VERTICAL_RATIO * m_stThumbAttr.u16ThumbPerCol);

            if (uiX > uiY) {
                u16TgtThumbW = HORIZONTAL_RATIO * uiY;
                u16TgtThumbH = VERTICAL_RATIO * uiY;
            }
            else {
                u16TgtThumbW = HORIZONTAL_RATIO * uiX;
                u16TgtThumbH = VERTICAL_RATIO * uiX;
            }
        }
        #else
        {
            u16TgtThumbW = (m_stThumbAttr.u32DispAreaW  - (m_stThumbAttr.u16ThumbPerRow + 1) * (m_stThumbAttr.u16ThumbHGap))
                            / m_stThumbAttr.u16ThumbPerRow;

            u16TgtThumbH = (m_stThumbAttr.u32DispAreaH - (m_stThumbAttr.u16ThumbPerCol + 1) * (m_stThumbAttr.u16ThumbVGap))
                            / m_stThumbAttr.u16ThumbPerCol;
        }
        #endif
    }
    else {
        u16TgtThumbW = (m_stThumbAttr.u32DispAreaW - (m_stThumbAttr.u16ThumbPerRow + 1) * (m_stThumbAttr.u16ThumbHGap))
                       / m_stThumbAttr.u16ThumbPerRow;

        u16TgtThumbH = (m_stThumbAttr.u32DispAreaH - (m_stThumbAttr.u16ThumbPerCol + 1) * (m_stThumbAttr.u16ThumbVGap))
                        / m_stThumbAttr.u16ThumbPerCol;

        if (AHC_DISPLAY_CCIR == OutputDevice) {
            u16TgtThumbW = (u16TgtThumbW >> 3) << 3; // Align 8
            u16TgtThumbH = (u16TgtThumbH >> 3) << 3; // Align 8
        }
    }

    m_stThumbAttr.u16TgtThumbW  = u16TgtThumbW;
    m_stThumbAttr.u16TgtThumbH  = u16TgtThumbH;

#if (SUPPORT_VR_THUMBNAIL)
    if (MMPS_3GPRECD_GetVRThumbEn()) {
        MMPS_3GPRECD_GetVRThumbResol(&ulVRThumbJpgW, &ulVRThumbJpgH);
    }
#endif

    AIHC_Thumb_CalculateRatio(ulVRThumbJpgW, ulVRThumbJpgH, u16TgtThumbW, u16TgtThumbH, &usTmpW, &usTmpH);

    #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90 || VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    AHC_Utility_SwapVal_Short(&usTmpW, &usTmpH);
    #endif

    AHC_Thumb_SetFocusWH(ALIGN16(usTmpW), ALIGN16(usTmpH));

    MMPS_VIDPLAY_SetThumbSize(ALIGN16(usTmpW), ALIGN16(usTmpH));

#if (SUPPORT_VR_THUMBNAIL)
    if (MMPS_3GPRECD_GetVRThumbEn()) {
        if (ulVRThumbJpgW && ulVRThumbJpgH) {

            u32VRThumbBufSize = ulVRThumbJpgW * ulVRThumbJpgH * 2; // Max YUV422

            CamOsDirectMemAlloc("VRThumb", u32VRThumbBufSize, &pvVRThumbBufVirt, NULL, NULL);

            u32ThumbSrcBufAddr = (UINT32)pvVRThumbBufVirt;

            AHC_DBG_MSG(0, "Thumb Addr %x TW %d TH %d\r\n", u32ThumbSrcBufAddr, ulVRThumbJpgW, ulVRThumbJpgH);
        }
        else {
            AHC_DBG_ERR(1, "Thumb Size = 0\r\n");
        }
    }
#endif

    // The current dcf index in the db.
    AHC_UF_GetCurrentIndex(&u32CurIdx);

    // The boundary check of index.
    if (u32CurIdx >= (u32MaxIdx - 1)) {
        u32CurIdx = (u32MaxIdx - 1);
    }

    // The max index in the db
    u32MaxIdx -= 1;

    // The max number per page
    u32ThumbPerPage = m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol;

    // The current page => 0~n-1, n pages
    u32CurPage = u32CurIdx / u32ThumbPerPage;

    // The first index of the current page.
    u32DecodeIdx = u32CurPage * u32ThumbPerPage;

    /*
       The boundary check of index.
    */
    if (u32DecodeIdx > u32MaxIdx) {

        u32ThumbPerPage = (u32MaxIdx + 1) % (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

        if (u32ThumbPerPage == 0)
            u32ThumbPerPage = (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

        u32DecodeIdx = u32MaxIdx;
    }

    //Redraw the thumbnail only if not the same page or some DCF items are removed
    /*
    The max number of file is not the same as the previous enter.
    */
    if ((u32MaxIdx != m_uiMaxIdx) || (m_uiCurPage != u32CurPage) || bForce)
    {
        UINT32 k, idx;

        #ifdef WMSG_SHOW_WAIT
        AHC_WMSG_Draw(AHC_TRUE, WMSG_OPENFILE_WAIT, 0);
        #endif

        AIHC_Thumb_DrawYuvFillPattern(YUV_BLACK);

        AIHC_Thumb_InitMVOP(AHC_TRUE);

        k = 1;
        idx = 0;

        do {
            MMP_ERR error = MMP_ERR_NONE;

            if ((k % m_stThumbAttr.u16ThumbPerRow) == 0) {
                uiPosY = k / m_stThumbAttr.u16ThumbPerRow ;
                uiPosX = m_stThumbAttr.u16ThumbPerRow;
            }
            else {
                uiPosY = k / m_stThumbAttr.u16ThumbPerRow + 1;
                uiPosX = k % m_stThumbAttr.u16ThumbPerRow;
            }

            #if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)
            #else
            AIHC_Thumb_CalculateRatio( ulVRThumbJpgW, ulVRThumbJpgH, u16TgtThumbW, u16TgtThumbH, &usTmpW, &usTmpH);
            #endif

            /* Get the file information */
            MEMSET(s8FilePathName, 0, sizeof(s8FilePathName));

            if (m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0) {
                AHC_UF_SetRearCamPathFlag(AHC_TRUE);
            }

            AHC_UF_GetFileTypebyIndex(u32DecodeIdx, &u8FileType);
            AHC_UF_GetFilePathNamebyIndex(u32DecodeIdx, s8FilePathName);

            AHC_DBG_MSG(1, "Idx [%d] Name [%s]\r\n", u32DecodeIdx, s8FilePathName);

            if (m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0) {
                AHC_UF_SetRearCamPathFlag(AHC_FALSE);
            }

            AIHC_Thumb_SetIdxByPos((uiPosY - 1) * m_stThumbAttr.u16ThumbPerRow + (uiPosX - 1), u32DecodeIdx);

            ThumbPosX = m_stThumbAttr.u32DispStartX + uiPosX * m_stThumbAttr.u16ThumbHGap + (uiPosX - 1) * u16TgtThumbW;
            ThumbPosY = m_stThumbAttr.u32DispStartY + uiPosY * m_stThumbAttr.u16ThumbVGap   + (uiPosY - 1) * u16TgtThumbH;
            ThumbPosY = (((ThumbPosY) >> 2) << 2) +2; //for YUV format

            AHC_Thumb_SetFocus_Point(idx++, ThumbPosX, ThumbPosY);

        #if (SUPPORT_VR_THUMBNAIL)
            if (MMPS_3GPRECD_GetVRThumbEn())
            {

                bFoundThumbInVideo = MMP_FALSE;

                if (u32DecodeIdx != ulCurIdx) {

                    ulCurIdx = u32DecodeIdx;
                    if (u8FileType == DCF_OBG_TS) {
                        error = MMPS_VIDPLAY_GetTsThumbnail(  s8FilePathName,
                                                              STRLEN(s8FilePathName),
                                                              u32VRThumbBufSize,
                                                              (MMP_UBYTE**)&u32ThumbSrcBufAddr,
                                                              &u32TargetThumbSize);
                    }
                    else {
                        error = MMPS_VIDPLAY_GetThumbnail(  s8FilePathName,
                                                            STRLEN(s8FilePathName),
                                                            u32VRThumbBufSize,
                                                            (MMP_UBYTE**)&u32ThumbSrcBufAddr,
                                                            &u32TargetThumbSize);
                    }
                    bFoundThumbInVideo = (MMP_ERR_NONE == error) ? MMP_TRUE : MMP_FALSE;

                    if (error) {
                        AHC_DBG_ERR(0, FG_YELLOW("# VRThumb Err = %x\r\n"), error);
                    }
                }
            }

            if (u8FileType == DCF_OBG_JPG || bFoundThumbInVideo)
        #else
            if ( u8FileType == DCF_OBG_JPG )
        #endif
            {
                MMP_DSC_JPEG_INFO stJpegInfo;

                MEMSET(&stJpegInfo, 0, sizeof(MMP_DSC_JPEG_INFO));

            #if (SUPPORT_VR_THUMBNAIL)
                if (bFoundThumbInVideo) {
                    DBG_AutoTestPrint(ATEST_ACT_BROW_VID_0x0006, ATEST_STS_START_0x0001, 0, 0, gbAhcDbgBrk);
                }
                else
            #endif
                {
                    DBG_AutoTestPrint(ATEST_ACT_BROW_PHOTO_0x0007, ATEST_STS_START_0x0001, 0, 0, gbAhcDbgBrk);
                }

                stJpegInfo.bDecodeThumbnail     = MMP_TRUE;
                #if (DSC_SUPPORT_BASELINE_MP_FILE)
                stJpegInfo.bDecodeLargeThumb    = MMP_TRUE;
                #endif
                stJpegInfo.bValid               = MMP_FALSE;
                stJpegInfo.bReEncodeThumb       = MMP_FALSE;

            #if (SUPPORT_VR_THUMBNAIL == 0)
                STRCPY(stJpegInfo.bJpegFileName, s8FilePathName);
                stJpegInfo.usJpegFileNameLength = STRLEN(s8FilePathName);
                stJpegInfo.ulJpegBufAddr        = 0;
                stJpegInfo.ulJpegBufSize        = 0;
            #else
                if (!bFoundThumbInVideo) {
                    STRCPY(stJpegInfo.bJpegFileName, s8FilePathName);
                    stJpegInfo.usJpegFileNameLength   = STRLEN(s8FilePathName);
                    stJpegInfo.ulJpegBufAddr          = 0;
                    stJpegInfo.ulJpegBufSize          = 0;
                    stJpegInfo.bDecVRThumb            = MMP_FALSE;
                }
                else {

                    stJpegInfo.usJpegFileNameLength   = 0;
                    stJpegInfo.ulJpegBufAddr          = u32ThumbSrcBufAddr;
                    stJpegInfo.ulJpegBufSize          = u32TargetThumbSize;
                    stJpegInfo.bDecVRThumb            = MMP_TRUE;
                    stJpegInfo.ePrimaryFormat         = MMP_DSC_JPEG_FMT444;
                    stJpegInfo.usPrimaryWidth         = ulVRThumbJpgW;
                    stJpegInfo.usPrimaryHeight        = ulVRThumbJpgH;
                }
            #endif

                if ((OSDColor == OSD_COLOR_RGB565 ) || ( OSDColor == OSD_COLOR_RGB888))
                {
                    UINT16 uwBufWidth = 0;
                    UINT16 uwBufHeight = 0;

                    #if (AHC_BROWSER_THUMBNAIL_STYLE == AHC_BROWSER_THUMBNAIL_STYLE_1)
                    uwBufWidth =  ((usTmpW) >> 2) << 2;
                    uwBufHeight = ((usTmpH) >> 2) << 2;
                    #else
                    uwBufWidth =  ((usTmpW+15) >> 4) << 4;
                    uwBufHeight = ((usTmpH+15) >> 4) << 4;
                    #endif

                    uwBufWidth  = ALIGN16(usTmpW);
                    uwBufHeight = ALIGN16(usTmpH);

                    error = MMPS_DSC_DecodeThumbnail(&stJpegInfo,
                                                     uwBufWidth,
                                                     uwBufHeight);

                    if (error == MMP_ERR_NONE) {

                        MMPS_VIDPLAY_GetTumbnaiInfo(&u32ThumbOutBufAddr, &u32TargetThumbSize);

                        while (u32ThumbOutBufAddr == 0)
                        {
                            MMPS_VIDPLAY_GetTumbnaiInfo(&u32ThumbOutBufAddr, &u32TargetThumbSize);
                            AHC_OS_SleepMs(2);
                        }

                        if (stJpegInfo.usThumbHeight == 0) {
                            AIHC_Thumb_CalculateRatio(stJpegInfo.usPrimaryWidth, stJpegInfo.usPrimaryHeight, u16TgtThumbW, u16TgtThumbH, &usTmpW, &usTmpH);
                        }

                        {
                            UINT16 u16RotPosX = 0, u16RotPosY = 0;

                            #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90 || VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
                            AHC_Utility_SwapVal_Short(&usTmpW, &usTmpH);
                            #endif

                            #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90)
                            u16RotPosX = OSDWidth - ThumbPosY - ALIGN16(usTmpW);
                            u16RotPosY = ThumbPosX;
                            #elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
                            u16RotPosX = ThumbPosY;
                            u16RotPosY = OSDHeight - ThumbPosX - ALIGN16(usTmpH);
                            #endif

                            #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90 || VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
                            AHC_OSDDrawBuffer(m_ulDrawingThumbOSD,
                                              (UINT8*)u32ThumbOutBufAddr,
                                              u16RotPosX,
                                              u16RotPosY,
                                              ALIGN16(usTmpW),
                                              ALIGN16(usTmpH),
                                              OSDColor);
                            #else
                            AHC_OSDDrawBuffer(m_ulDrawingThumbOSD,
                                              (UINT8*)u32ThumbOutBufAddr,
                                              ThumbPosX,
                                              ThumbPosY,
                                              ALIGN16(usTmpW),
                                              ALIGN16(usTmpH),
                                              OSDColor);
                            #endif
                        }
                    }
                    else {
                        #if (SUPPORT_VR_THUMBNAIL)
                        if (MMPS_3GPRECD_GetVRThumbEn() && bFoundThumbInVideo) {
                            u32DecodeIdx--;
                            k--;
                            AHC_DBG_ERR(1, FG_YELLOW("DecThumbnailErr Fail!\r\n"));
                        }
                        else
                        #endif
                        {
                            if (m_pBmpFileDamage == NULL) {

                                OSDDraw_EnterDrawing(&bID0, &bID1);

                                BEGIN_LAYER(bID0);

                                AHC_OSDSetColor(bID0, GUI_GREEN);
                                AHC_OSDDrawFillRect(bID0,
                                                    m_stThumbDrawFocus.pFocusStart[k-1].PointX,
                                                    m_stThumbDrawFocus.pFocusStart[k-1].PointY,
                                                    m_stThumbDrawFocus.pFocusStart[k-1].PointX + m_stThumbDrawFocus.usFocusWidth,
                                                    m_stThumbDrawFocus.pFocusStart[k-1].PointY + m_stThumbDrawFocus.usFocusHeight);

                                END_LAYER(bID0);

                                OSDDraw_ExitDrawing(&bID0, &bID1);
                            }
                            else {

                                ThumbPosX = m_stThumbDrawFocus.pFocusStart[k-1].PointX;
                                ThumbPosY = m_stThumbDrawFocus.pFocusStart[k-1].PointY;
                                ThumbPosX += (m_stThumbDrawFocus.usFocusWidth - m_pBmpFileDamage->XSize) >> 1;
                                ThumbPosY += (m_stThumbDrawFocus.usFocusHeight - m_pBmpFileDamage->YSize) >> 1;

                                OSDDraw_EnterDrawing(&bID0, &bID1);

                                BEGIN_LAYER(bID0);
                                AHC_OSDDrawBitmap(bID0, m_pBmpFileDamage, ThumbPosX, ThumbPosY);
                                END_LAYER(bID0);

                                OSDDraw_ExitDrawing(&bID0, &bID1);
                            }
                       }
                    }

                    MMPS_DSC_ExitThumbDecodeMode(&stJpegInfo);

                    MMPS_VIDPLAY_SetTumbnaiInfo(0, 0);
                }

                #if (SUPPORT_VR_THUMBNAIL)
                if (MMPS_3GPRECD_GetVRThumbEn() && bFoundThumbInVideo) {
                    DBG_AutoTestPrint(ATEST_ACT_BROW_VID_0x0006,
                                      ATEST_STS_RSOL_SIZE_0x0004,
                                      stJpegInfo.usPrimaryWidth,
                                      stJpegInfo.usPrimaryHeight,
                                      gbAhcDbgBrk);
                    DBG_AutoTestPrint(ATEST_ACT_BROW_VID_0x0006, ATEST_STS_END_0x0003, 0, error, gbAhcDbgBrk);
                }
                else
                #endif
                {
                    DBG_AutoTestPrint(ATEST_ACT_BROW_PHOTO_0x0007, ATEST_STS_RSOL_SIZE_0x0004, stJpegInfo.usPrimaryWidth, stJpegInfo.usPrimaryHeight, gbAhcDbgBrk);
                    DBG_AutoTestPrint(ATEST_ACT_BROW_PHOTO_0x0007, ATEST_STS_END_0x0003, 0, error, gbAhcDbgBrk);
                }
            }
            else if ((u8FileType == DCF_OBG_MOV) ||
                     (u8FileType == DCF_OBG_MP4) ||
                     (u8FileType == DCF_OBG_AVI) ||
                     (u8FileType == DCF_OBG_3GP) ||
                     (u8FileType == DCF_OBG_TS ) ||
                     (u8FileType == DCF_OBG_WMV))
            {
                DBG_AutoTestPrint(ATEST_ACT_BROW_VID_0x0006, ATEST_STS_START_0x0001, 0, 0, gbAhcDbgBrk);

                #if 0// TBD (AHC_BROWSER_DRAW_GRAY_BORDER)
                {
                    tmpThumbPosX = k-((k-1)/m_stThumbAttr.u16ThumbPerRow)*m_stThumbAttr.u16ThumbPerRow;
                    tmpThumbPosY = 1+(k-1)/m_stThumbAttr.u16ThumbPerRow;

                    CurrRectWidth = u16TgtThumbW + BorderWidth + BorderWidth/2;
                    CurrRectHeight = u16TgtThumbH + BorderWidth + BorderWidth/2;
                    CurrRectStartX = m_stThumbAttr.u32DispStartX + (tmpThumbPosX-1)*(m_stThumbAttr.u16ThumbHGap + u16TgtThumbW) + m_stThumbAttr.u16ThumbHGap - BorderWidth;
                    CurrRectStartY = m_stThumbAttr.u32DispStartY + (tmpThumbPosY-1)*(m_stThumbAttr.u16ThumbVGap + u16TgtThumbH) + m_stThumbAttr.u16ThumbVGap - BorderWidth;

                    AHC_OSDSetColor(m_ulDrawingThumbOSD, GUI_GRAY);

                    AHC_OSDDrawFillRoundedRect( m_ulDrawingThumbOSD,
                                         CurrRectStartX,
                                         CurrRectStartY,
                                         CurrRectStartX + CurrRectWidth,
                                         CurrRectStartY + BorderWidth, 2);
                    AHC_OSDDrawFillRoundedRect( m_ulDrawingThumbOSD,
                                         CurrRectStartX-1,
                                         CurrRectStartY,
                                         CurrRectStartX+BorderWidth-1,
                                         CurrRectStartY + CurrRectHeight+1, 2);
                    AHC_OSDDrawFillRoundedRect( m_ulDrawingThumbOSD,
                                         CurrRectStartX + CurrRectWidth + (BorderWidth/2)-BorderWidth,
                                         CurrRectStartY,
                                         CurrRectStartX + CurrRectWidth + (BorderWidth/2),
                                         CurrRectStartY + CurrRectHeight + (BorderWidth/2), 2);
                    AHC_OSDDrawFillRoundedRect( m_ulDrawingThumbOSD,
                                         CurrRectStartX,
                                         CurrRectStartY + CurrRectHeight + (BorderWidth/2)-BorderWidth,
                                         CurrRectStartX + CurrRectWidth,
                                         CurrRectStartY + CurrRectHeight + (BorderWidth/2),2);
                }
                #endif

                if ((OSDColor == OSD_COLOR_RGB565 ) || ( OSDColor == OSD_COLOR_RGB888))
                {
                    MMP_GRAPHICS_COLORDEPTH GraphicColorFormat;
                    MMPS_VIDEO_CONTAINER_INFO info;

                    if ( OSDColor == OSD_COLOR_RGB565 ) {
                        GraphicColorFormat = MMP_GRAPHICS_COLORDEPTH_16;
                    }
                    else if ( OSDColor == OSD_COLOR_RGB888 ) {
                        GraphicColorFormat = MMP_GRAPHICS_COLORDEPTH_24;
                    }

                    error = MMPS_VIDPLAY_GetContainerInfo(s8FilePathName, STRLEN(s8FilePathName), &info);

                    if (error == MMP_ERR_NONE)
                    {
                        MMPS_VIDPLAY_SCALERCONFIG sScalerCfg;
                        UINT16 usTemp = 0;
                        //MMPS_VIDPLAY_SetScalerCfg(&sScalerCfg, MMP_FALSE, 0, 0, 0, 0);
                        //MMPS_VIDPLAY_SetDisplayMode(VIDEOPLAY_MODE_MAX, MMP_DISPLAY_ROTATE_NO_ROTATE, MMP_FALSE, NULL, &sScalerCfg);
                    #if !(EN_SPEED_UP_VID & BROWSER_CASE)
                        AIHC_Thumb_CalculateRatio( info.video_info[0].width,
                                                   info.video_info[0].height,
                                                   u16TgtThumbW,
                                                   u16TgtThumbH,
                                                   &usTmpW,
                                                   &usTmpH );
                    #else
                        #if 1//(VERTICAL_LCD == VERTICAL_LCD_DEGREE_90 || VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
                        usTemp = usTmpH;
                        usTmpH = usTmpW;
                        usTmpW = usTemp;
                        #endif
                    #endif

                        error = MMPS_VIDPLAY_GetFrame(s8FilePathName,
                                                      STRLEN(s8FilePathName),
                                                      &usTmpW,
                                                      &usTmpH,
                                                      GraphicColorFormat,
                                                      &TargetThumbAddr,
                                                      &u32TargetThumbSize,
                                                      MMPS_VIDPLAY_GETFRAME_FIRST);

                        DBG_AutoTestPrint(ATEST_ACT_BROW_VID_0x0006,
                                            ATEST_STS_RSOL_SIZE_0x0004,
                                            MMPS_VIDPLAY_Get3gpConTnerVidInf()->width,
                                            MMPS_VIDPLAY_Get3gpConTnerVidInf()->height,
                                            gbAhcDbgBrk);
                        DBG_AutoTestPrint(ATEST_ACT_BROW_VID_0x0006, ATEST_STS_END_0x0003, 0, error, gbAhcDbgBrk);
                    }

                    // Check the return value of MMPS_VIDPLAY_GetContainerInfo or MMPS_VIDPLAY_GetFrame
                    if (error == MMP_ERR_NONE) {

                        AHC_BOOL ret;
                        UINT16 u16RotPosX = 0, u16RotPosY = 0;

                        #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90)
                        u16RotPosX = OSDWidth - ThumbPosY - usTmpW;
                        u16RotPosY = ThumbPosX;
                        #elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
                        u16RotPosX = ThumbPosY;
                        u16RotPosY = OSDHeight - ThumbPosX - usTmpH;
                        #endif

                        #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90 || VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
                        ret = AHC_OSDDrawBuffer(m_ulDrawingThumbOSD,
                                                (UINT8*)TargetThumbAddr,
                                                u16RotPosX,
                                                u16RotPosY,
                                                usTmpW,
                                                usTmpH,
                                                OSDColor);
                        #else
                        ret = AHC_OSDDrawBuffer(m_ulDrawingThumbOSD,
                                                (UINT8*)TargetThumbAddr,
                                                ThumbPosX,
                                                ThumbPosY,
                                                usTmpW,
                                                usTmpH,
                                                OSDColor);
                        #endif

                        #if 0 // TBD
                        if (m_pBmpEmergIcon) {
                            if (AHC_UF_GetDB() == DCF_DB_TYPE_DB2_EVENT)
                                AHC_OSDDrawBitmap(m_ulDrawingThumbOSD, m_pBmpEmergIcon, ThumbPosX, ThumbPosY);
                        }
                        #endif
                    }
                    else
                    {
                        AHC_DBG_ERR(1, "error MMPS_VIDPLAY_GetFrame : 0x%x\r\n", error);

                        if (error == MMP_VIDPSR_ERR_CONTENT_CORRUPT)
                        {
                            AHC_DBG_ERR(1, FG_RED("MMP_VIDPSR_ERR_CONTENT_CORRUPT BREAK\r\n"));
                            break;
                        }

                        if(m_pBmpFileDamage == NULL) {

                            OSDDraw_EnterDrawing(&bID0, &bID1);

                            BEGIN_LAYER(bID0);

                            AHC_OSDSetColor(bID0, GUI_GREEN);
                            AHC_OSDDrawFillRect(bID0,
                                                m_stThumbDrawFocus.pFocusStart[k-1].PointX,
                                                m_stThumbDrawFocus.pFocusStart[k-1].PointY,
                                                m_stThumbDrawFocus.pFocusStart[k-1].PointX + m_stThumbDrawFocus.usFocusWidth,
                                                m_stThumbDrawFocus.pFocusStart[k-1].PointY + m_stThumbDrawFocus.usFocusHeight);

                            END_LAYER(bID0);

                            OSDDraw_ExitDrawing(&bID0, &bID1);
                        }
                        else {

                            ThumbPosX = m_stThumbDrawFocus.pFocusStart[k-1].PointX;
                            ThumbPosY = m_stThumbDrawFocus.pFocusStart[k-1].PointY;
                            ThumbPosX += (m_stThumbDrawFocus.usFocusWidth - m_pBmpFileDamage->XSize) >> 1;
                            ThumbPosY += (m_stThumbDrawFocus.usFocusHeight - m_pBmpFileDamage->YSize) >> 1;

                            OSDDraw_EnterDrawing(&bID0, &bID1);

                            BEGIN_LAYER(bID0);
                            AHC_OSDDrawBitmap(bID0, m_pBmpFileDamage, ThumbPosX, ThumbPosY);
                            END_LAYER(bID0);

                            OSDDraw_ExitDrawing(&bID0, &bID1);

                            #if 0// TBD (AHC_BROWSER_DRAW_GRAY_BORDER)
                            {
                                AHC_OSDSetColor(m_ulDrawingThumbOSD, GUI_GRAY);

                                AHC_OSDDrawFillRoundedRect( m_ulDrawingThumbOSD,
                                                     CurrRectStartX,
                                                     CurrRectStartY,
                                                     CurrRectStartX + CurrRectWidth,
                                                     CurrRectStartY + BorderWidth, 2);
                                AHC_OSDDrawFillRoundedRect( m_ulDrawingThumbOSD,
                                                     CurrRectStartX-1,
                                                     CurrRectStartY,
                                                     CurrRectStartX+BorderWidth-1,
                                                     CurrRectStartY + CurrRectHeight+1, 2);
                                AHC_OSDDrawFillRoundedRect( m_ulDrawingThumbOSD,
                                                     CurrRectStartX + CurrRectWidth + (BorderWidth/2)-BorderWidth,
                                                     CurrRectStartY,
                                                     CurrRectStartX + CurrRectWidth + (BorderWidth/2),
                                                     CurrRectStartY + CurrRectHeight + (BorderWidth/2), 2);
                                AHC_OSDDrawFillRoundedRect( m_ulDrawingThumbOSD,
                                                     CurrRectStartX,
                                                     CurrRectStartY + CurrRectHeight + (BorderWidth/2)-BorderWidth,
                                                     CurrRectStartX + CurrRectWidth,
                                                     CurrRectStartY + CurrRectHeight + (BorderWidth/2),2);
                            }
                            #endif
                        }
                    }
                }
            }
            else if ((u8FileType == DCF_OBG_MP3) ||
                     (u8FileType == DCF_OBG_WAV) ||
                     (u8FileType == DCF_OBG_OGG) ||
                     (u8FileType == DCF_OBG_WMA))
            {
            #if 0 // TBD
                AHC_OSDSetColor(m_ulDrawingThumbOSD, GUI_BLUE);
                AHC_OSDDrawFillRect(m_ulDrawingThumbOSD,
                                    ThumbPosX,
                                    ThumbPosY,
                                    ThumbPosX + u16TgtThumbW,
                                    ThumbPosY + u16TgtThumbH);
            #endif
            }
            else
            {
                //TBD, Not supported file
                if (m_pBmpFileDamage == NULL) {

                    OSDDraw_EnterDrawing(&bID0, &bID1);

                    BEGIN_LAYER(bID0);

                    AHC_OSDSetColor(bID0, GUI_GREEN);
                    AHC_OSDDrawFillRect(bID0,
                                        m_stThumbDrawFocus.pFocusStart[k-1].PointX,
                                        m_stThumbDrawFocus.pFocusStart[k-1].PointY,
                                        m_stThumbDrawFocus.pFocusStart[k-1].PointX + m_stThumbDrawFocus.usFocusWidth,
                                        m_stThumbDrawFocus.pFocusStart[k-1].PointY + m_stThumbDrawFocus.usFocusHeight);

                    END_LAYER(bID0);

                    OSDDraw_ExitDrawing(&bID0, &bID1);
                }
                else {

                    ThumbPosX = m_stThumbDrawFocus.pFocusStart[k].PointX;
                    ThumbPosY = m_stThumbDrawFocus.pFocusStart[k].PointY;
                    ThumbPosX += (m_stThumbDrawFocus.usFocusWidth - m_pBmpFileDamage->XSize) >> 1;
                    ThumbPosY += (m_stThumbDrawFocus.usFocusHeight - m_pBmpFileDamage->YSize) >> 1;

                    OSDDraw_EnterDrawing(&bID0, &bID1);

                    BEGIN_LAYER(bID0);
                    AHC_OSDDrawBitmap(bID0, m_pBmpFileDamage, ThumbPosX, ThumbPosY);
                    END_LAYER(bID0);

                    OSDDraw_ExitDrawing(&bID0, &bID1);
                }
            }

            if (u32DecodeIdx == u32MaxIdx)
                break;

            u32DecodeIdx++;
            k++;

        } while (k <= u32ThumbPerPage);

        #ifdef WMSG_SHOW_WAIT
        AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);
        #endif

    }

    ThumbIndex = m_stThumbAttr.uiIdxMap[ (u32CurIdx % (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol)) ];
    AIHC_Thumb_DrawFocus(ThumbIndex, AHC_FALSE);
    m_stThumbAttr.u16CurIdx = ThumbIndex;

    #if (AHC_BROWSER_DRAW_PROTECT_KEY)
    AHC_Thumb_ProtectKey();
    #endif

    AIHC_Thumb_InitMVOP(AHC_FALSE);

#if (SUPPORT_VR_THUMBNAIL)
    if (u32ThumbSrcBufAddr) {
        CamOsDirectMemRelease(u32ThumbSrcBufAddr);
    }
#endif

    m_uiCurPage = u32CurPage;
    m_uiMaxIdx  = u32MaxIdx;
    AIHC_DrawReservedOSD(AHC_FALSE);

    #if (EN_AUTO_TEST_LOG == 1)
    DBG_AutoTestPrint(ATEST_ACT_LOG_0xFFFE, ATEST_STS_DUMP_LOG_0xFFFE, 0, 0, gbAhcDbgBrk);
    #endif

    return AHC_TRUE;
}

#if 0
void _____Browser_Public_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_Thumb_LoadProtectKeyIcon
//  Description :
//------------------------------------------------------------------------------
void AHC_Thumb_LoadProtectKeyIcon(AHC_PROTECT_TYPE Type, GUI_BITMAP* psKeyIcon)
{
    switch(Type){

    case AHC_PROTECT_G:
        m_ProtectKeyTypeG    = psKeyIcon;
        break;
    case AHC_PROTECT_MENU:
        m_ProtectKeyTypeMenu = psKeyIcon;
        break;
    case AHC_PROTECT_MOVE:
        m_ProtectKeyTypeMove = psKeyIcon;
        break;
    default:
        break;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_Thumb_LoadEmergIcon
//  Description :
//------------------------------------------------------------------------------
void AHC_Thumb_LoadEmergIcon(GUI_BITMAP* psEmrIcon)
{
    m_pBmpEmergIcon = psEmrIcon;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Thumb_LoadFileDamageIcon
//  Description :
//------------------------------------------------------------------------------
void AHC_Thumb_LoadFileDamageIcon(GUI_BITMAP* psFileDamageIcon)
{
    m_pBmpFileDamage = psFileDamageIcon;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Thumb_SetConfig
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Config thumbnail mode

 This API configures the playback thumbnail mode.
 Parameters:
 @param[in] *pConfig The thumbnail configurations.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Thumb_SetConfig(AHC_THUMB_CFG *pConfig, AHC_BOOL bKeepThumbIndex)
{
    m_stThumbAttr.u16ThumbPerRow    = pConfig->uwTHMPerLine;
    m_stThumbAttr.u16ThumbPerCol    = pConfig->uwTHMPerColume;
    m_stThumbAttr.u16ThumbHGap      = pConfig->uwHGap;
    m_stThumbAttr.u16ThumbVGap      = pConfig->uwVGap;
    m_stThumbAttr.u32BkColor        = pConfig->byBkColor;
    m_stThumbAttr.u32FocusColor     = pConfig->byFocusColor;
    m_stThumbAttr.u32DispStartX     = pConfig->u32DispStartX;
    m_stThumbAttr.u32DispStartY     = pConfig->u32DispStartY;
    m_stThumbAttr.u32DispAreaW      = pConfig->u32DispAreaW;
    m_stThumbAttr.u32DispAreaH      = pConfig->u32DispAreaH;

    m_stThumbDrawFocus.usThumbDrawFocusMaxCount = m_stThumbAttr.u16ThumbPerRow*m_stThumbAttr.u16ThumbPerCol;

    if (!bKeepThumbIndex) {
        m_stThumbAttr.u16CurIdx = 0;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Thumb_GetConfig
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Thumb_GetConfig(AHC_THUMB_CFG *pConfig)
{
    pConfig->uwTHMPerLine   = m_stThumbAttr.u16ThumbPerRow;
    pConfig->uwTHMPerColume = m_stThumbAttr.u16ThumbPerCol;
    pConfig->uwHGap         = m_stThumbAttr.u16ThumbHGap;
    pConfig->uwVGap         = m_stThumbAttr.u16ThumbVGap;
    pConfig->byBkColor      = m_stThumbAttr.u32BkColor;
    pConfig->byFocusColor   = m_stThumbAttr.u32FocusColor;
    pConfig->u32DispStartX  = m_stThumbAttr.u32DispStartX;
    pConfig->u32DispStartY  = m_stThumbAttr.u32DispStartY;
    pConfig->u32DispAreaW   = m_stThumbAttr.u32DispAreaW;
    pConfig->u32DispAreaH   = m_stThumbAttr.u32DispAreaH;

    return AHC_TRUE;
}

void AHC_Thumb_SetFocusWH(int w,int h)
{
    UINT8 bID0;
    AHC_OSD_ROTATE_DRAW_MODE ulRotateByGUI;
    UINT32 u32DuplW,u32DuplH;

    OSDDraw_GetOvlDrawBuffer(&bID0);
    ulRotateByGUI = AHC_OSDGetGuiRotateByGUI(bID0);
    AHC_OSDGetDuplicateWH(bID0,&u32DuplW,&u32DuplH);

    if (ulRotateByGUI) {
        m_stThumbDrawFocus.usFocusWidth  = h;
        m_stThumbDrawFocus.usFocusHeight = w;
    }
    else{
        m_stThumbDrawFocus.usFocusWidth  = w;
        m_stThumbDrawFocus.usFocusHeight = h;
    }

    if (u32DuplH) {
        m_stThumbDrawFocus.usFocusHeight /= (u32DuplH + 1);
    }
    if (u32DuplW) {
        m_stThumbDrawFocus.usFocusWidth /= (u32DuplW + 1);
    }
}

void AHC_Thumb_SetFocus_Point(int i, int x, int y)
{
    UINT8 bID0;
    UINT32 u32DuplW,u32DuplH;

    OSDDraw_GetOvlDrawBuffer(&bID0);
    AHC_OSDGetDuplicateWH(bID0,&u32DuplW,&u32DuplH);

    if ((i < m_stThumbDrawFocus.usThumbDrawFocusMaxCount) && (i >= 0)) {

        m_stThumbDrawFocus.pFocusStart[i].PointX  = x;
        m_stThumbDrawFocus.pFocusStart[i].PointY  = y;

        if (u32DuplH) {
            m_stThumbDrawFocus.pFocusStart[i].PointY /= (u32DuplH + 1);
        }
        if (u32DuplW) {
            m_stThumbDrawFocus.pFocusStart[i].PointX /= (u32DuplW + 1);
        }
    }
}

#if (AHC_BROWSER_DRAW_PROTECT_KEY)
AHC_BOOL AHC_Thumb_ProtectKey(void)
{
    extern void MMPF_MMU_CleanDCache(void);

    UINT16   ThumbIndex;
    UINT16   TempDcfObjIdx;
    UINT16   ulFirstIndex;
    UINT16   ulObjCount;
    UINT16   i;
    AHC_BOOL bReadOnly = AHC_FALSE;
    AHC_BOOL bCharLock = AHC_FALSE;

    AHC_Thumb_GetFirstIdxCurPage(&ulFirstIndex);
    AHC_Thumb_GetCountCurPage(&ulObjCount);

    for (i = 0; i < ulObjCount; i++){

        TempDcfObjIdx = ulFirstIndex + i;

        AHC_UF_IsCharLockbyIndex(TempDcfObjIdx, &bCharLock);
        AHC_UF_IsReadOnlybyIndex(TempDcfObjIdx, &bReadOnly);

        if ((bReadOnly == AHC_TRUE) || (bCharLock == AHC_TRUE))
        {
            ThumbIndex = m_stThumbAttr.uiIdxMap[ (TempDcfObjIdx % (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol)) ];

            if (bReadOnly == AHC_TRUE)
            {
                AIHC_Thumb_DrawProtectKey(ThumbIndex, AHC_PROTECT_MENU);
            }
            else if (bCharLock == AHC_TRUE)
            {
                AIHC_Thumb_DrawProtectKey(ThumbIndex, AHC_PROTECT_G);
            }
        }
    }

    MMPF_MMU_CleanDCache();

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif

    return AHC_TRUE;
}
#endif

AHC_BOOL AHC_Thumb_SetCurrentIdx(UINT16 uiIndex)
{
    m_stThumbAttr.u16CurIdx = uiIndex;
    AHC_UF_SetCurrentIndex((UINT32)uiIndex);

    return AHC_TRUE;
}

/**
 @brief Thumbnail shift up

 Shift the selected displayed thumbnail up.
 Parameters:
 @param[in] byNum The number of thumbnail to shift.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Thumb_Rewind(UINT8 byNum)
{
    UINT32 uiIdx;
    UINT32 u32MaxIdx = 0;
    UINT32 u32CurPage = 0;
    UINT32 uiNextPage = 0;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if( u32MaxIdx == 0 )
    {
        return AHC_FALSE;
    }

    u32MaxIdx -= 1;

    if (m_stThumbAttr.u16CurIdx >= byNum)
        uiIdx = m_stThumbAttr.u16CurIdx - byNum;
    else
        uiIdx = u32MaxIdx;//

    u32CurPage  = (m_stThumbAttr.u16CurIdx) / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    uiNextPage = (uiIdx) / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    if (u32CurPage ==  uiNextPage) {

        if ( uiIdx != m_stThumbAttr.u16CurIdx ) {
            AIHC_Thumb_DrawFocus(m_stThumbAttr.u16CurIdx, AHC_TRUE);
            AIHC_Thumb_DrawFocus(uiIdx, AHC_FALSE);
            AHC_OSDRefresh();
            m_stThumbAttr.u16CurIdx = uiIdx;
            AHC_UF_SetCurrentIndex(uiIdx);
        }
    }
    else {
        m_stThumbAttr.u16CurIdx = uiIdx;
        AHC_UF_SetCurrentIndex(uiIdx);
        AHC_Thumb_DrawPage(AHC_FALSE);
    }

    return AHC_TRUE;
}

/**
 @brief Thumbnail shift down

 Shift the selected displayed thumbnail down.
 Parameters:
 @param[in] byNum The number of thumbnail to shift.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Thumb_Forward(UINT8 byNum)
{
    UINT32 uiIdx;
    UINT32 u32MaxIdx   = 0;
    UINT32 u32CurPage  = 0;
    UINT32 uiNextPage = 0;

    if (m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0) {
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if (u32MaxIdx == 0 )
    {
        return AHC_FALSE;
    }

    u32MaxIdx -= 1;

    if (m_stThumbAttr.u16CurIdx + byNum > u32MaxIdx)
        uiIdx = 0;
    else
        uiIdx = m_stThumbAttr.u16CurIdx + byNum;

    u32CurPage  = (m_stThumbAttr.u16CurIdx) / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);
    uiNextPage = (uiIdx               ) / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    if (u32CurPage ==  uiNextPage) {
        if (uiIdx != m_stThumbAttr.u16CurIdx) {
            AIHC_Thumb_DrawFocus(m_stThumbAttr.u16CurIdx, AHC_TRUE);
            AIHC_Thumb_DrawFocus(uiIdx, AHC_FALSE);
            AHC_OSDRefresh();
            m_stThumbAttr.u16CurIdx = uiIdx;
            AHC_UF_SetCurrentIndex(uiIdx);
        }
    }
    else {
        m_stThumbAttr.u16CurIdx = uiIdx;
        AHC_UF_SetCurrentIndex(uiIdx);

        AHC_Thumb_DrawPage(AHC_FALSE);
    }

    return AHC_TRUE;
}

/**
 @brief Thumbnail Previous page

 Shift to previous page in Browser Mode.
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Thumb_RewindPage(void)
{
    UINT32 uiIdx;
    UINT32 u32MaxIdx     = 0;
    UINT32 u32CurPage    = 0;
    UINT32 uiTotalPage  = 0;

    if (m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0) {
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if (u32MaxIdx == 0)
    {
        return AHC_FALSE;
    }

    u32MaxIdx -= 1;

    uiTotalPage = u32MaxIdx / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    u32CurPage = (m_stThumbAttr.u16CurIdx) / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    if (u32CurPage > 0)
    {
        // rewind page
        u32CurPage--;// 0~n-1, n pages.
    }
    else
    {
        u32CurPage = uiTotalPage;
    }

    uiIdx = u32CurPage*(m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    m_stThumbAttr.u16CurIdx = uiIdx;
    AHC_UF_SetCurrentIndex(uiIdx);

    AHC_Thumb_DrawPage(AHC_FALSE);

    return AHC_TRUE;
}

/**
 @brief Thumbnail Previous page

 Shift to next page in Browser Mode.
 Parameters:
 @param[in]
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Thumb_ForwardPage(void)
{
    UINT32 uiIdx        = 0;
    UINT32 u32MaxIdx    = 0;
    UINT32 u32CurPage   = 0;
    UINT32 uiTotalPage  = 0;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if( u32MaxIdx == 0 )
    {
        return AHC_FALSE;
    }

    u32MaxIdx -= 1;

    uiTotalPage  = u32MaxIdx / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    u32CurPage  = (m_stThumbAttr.u16CurIdx) / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    if( uiTotalPage > u32CurPage)
    {
        u32CurPage++;
    }
    else
    {
        u32CurPage = 0;
    }

    uiIdx = u32CurPage*(m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    m_stThumbAttr.u16CurIdx = uiIdx;

    AHC_UF_SetCurrentIndex(uiIdx);

    AHC_Thumb_DrawPage(AHC_FALSE);

    return AHC_TRUE;
}

AHC_BOOL AHC_Thumb_SetCurIdx(UINT32 uiIdx)
{
    AIHC_Thumb_SetCurrentIdx(uiIdx);
    AHC_UF_SetCurrentIndex(uiIdx);

    return AHC_TRUE;
}

AHC_BOOL AHC_Thumb_GetCurIdx(UINT32 *puiIdx)
{
    UINT32 u32MaxIdx;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if( u32MaxIdx == 0 )
    {
        *puiIdx = 0;
        return AHC_FALSE;
    }

    *puiIdx = m_stThumbAttr.u16CurIdx;

    return AHC_TRUE;
}

AHC_BOOL AHC_Thumb_GetCurPos(UINT32 *puiPos)
{
    UINT32 u32MaxIdx;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if( u32MaxIdx == 0 )
    {
        *puiPos = 0;
        return AHC_FALSE;
    }

    u32MaxIdx -= 1;

    *puiPos = m_stThumbAttr.u16CurIdx;

    return AHC_TRUE;
}
/**
1~n
*/
AHC_BOOL AHC_Thumb_GetCurPage(UINT16 *puwPage)
{
    UINT32 u32MaxIdx;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if( u32MaxIdx == 0 )
    {
        *puwPage = 0;
        return AHC_FALSE;
    }

    u32MaxIdx -= 1;

    *puwPage = m_stThumbAttr.u16CurIdx/(m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    *puwPage += 1;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Thumb_GetTotalPages
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Thumb_GetTotalPages(UINT16 *puwPages)
{
    UINT32 uiCount;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&uiCount);

    if (uiCount == 0) {
        *puwPages = 0;
        return AHC_FALSE;
    }

    *puwPages = uiCount / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_Thumb_GetMaxNumPerPage
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Thumb_GetMaxNumPerPage(UINT32  *ObjNumPerPage)
{
    *ObjNumPerPage = m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol;

    return AHC_TRUE;
}

/**
 @brief This API get the max DCF objects in current page.

 Parameters:
 @param[in]
 @param[out] *ulObjCount   the DCF Obj Count in the current page.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Thumb_GetCountCurPage(UINT16 *ulObjCount)
{
    UINT16 uiCount  = 0;
    UINT32 u32MaxIdx    = 0;
    UINT32 u32CurPage   = 0;
    UINT32 uiTotalPage = 0;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if( u32MaxIdx == 0 )
    {
        *ulObjCount = 0;
        return AHC_FALSE;
    }

    u32MaxIdx -= 1;

    uiTotalPage  = u32MaxIdx / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    u32CurPage  = (m_stThumbAttr.u16CurIdx) / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    if( uiTotalPage > u32CurPage)
    {
        // 0~n-2 pages
        uiCount = m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol;

    }
    else{
        // n-1 page => the last page
        uiCount = u32MaxIdx - u32CurPage*(m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol) + 1;
    }

    *ulObjCount = uiCount;

    return AHC_TRUE;
}

/**
 @brief This API get the current thumbnail index in current page.

 Parameters:
 @param[in]
 @param[out] *ulObjCount   the current Obj index in the current page.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Thumb_GetCurPosCurPage(UINT16 *ulObjIndex)
{
    UINT32 uiIdx;
    UINT32 u32MaxIdx = 0;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if( u32MaxIdx == 0 )
    {
        return AHC_FALSE;
    }
    u32MaxIdx -= 1;

    AIHC_Thumb_GetCurrentIdx(&uiIdx);

    uiIdx = uiIdx%(m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    *ulObjIndex = uiIdx;

    return AHC_TRUE;
}

/**
 @brief Get first thumbnail index

 Retrieve the index of the fist displayed thumbnail in playback thumbnail.
 Parameters:
 @param[out] *pwIndex The position of first displayed thumbnail index.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_Thumb_GetFirstIdxCurPage(UINT16 *pwIndex)
{
    UINT32 temp;
    UINT32 u32MaxIdx;

    if (m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&u32MaxIdx);

    if( u32MaxIdx == 0 )
    {
        return AHC_FALSE;
    }
    u32MaxIdx -= 1;

    temp = m_stThumbAttr.u16CurIdx / (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    *pwIndex = temp * (m_stThumbAttr.u16ThumbPerRow * m_stThumbAttr.u16ThumbPerCol);

    return AHC_TRUE;
}
