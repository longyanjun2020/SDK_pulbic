//==============================================================================
//
//  File        : ahc_gui.h
//  Description : INCLUDE File for the AHC GUI function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_GUI_H_
#define _AHC_GUI_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "GUI.h"
#include "AHC_Config_SDK.h"
#include "ahc_os.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define MENU_OSD_FIRST_ID   16
#define MENU_OSD_END_ID     17

#define THUMBNAIL_OSD_FRONT_ID              (MAX_OSD_NUM)
#define THUMBNAIL_OSD_BACK_ID               (MAX_OSD_NUM + 1)
#define DATESTAMP_PRIMARY_OSD_ID            (MAX_OSD_NUM + 2)
#define DATESTAMP_THUMB_OSD_ID              (MAX_OSD_NUM + 3)
#define DATESTAMP_PRIMARY_OSD_ID_SUB        (MAX_OSD_NUM + 4)
#define DATESTAMP_THUMB_OSD_ID_SUB          (MAX_OSD_NUM + 5)
#define DATESTAMP_PRIMARY_OSD_ID_SUB_DUAL   (MAX_OSD_NUM + 6)
#define DATESTAMP_THUMB_OSD_ID_SUB_DUAL     (MAX_OSD_NUM + 7)

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum _AHC_OSD_ROTATE_TYPE 
{
    AHC_OSD_ROTATE_NONE = 0,
    AHC_OSD_ROTATE_RIGHT_90,
    AHC_OSD_ROTATE_RIGHT_180,
    AHC_OSD_ROTATE_RIGHT_270
} AHC_OSD_ROTATE_TYPE;

typedef enum _AHC_OSD_SEMITP_TYPE
{
    AHC_OSD_SEMITP_AVG = (0x00 << 2),
    AHC_OSD_SEMITP_AND = (0x01 << 2),
    AHC_OSD_SEMITP_OR  = (0x02 << 2),
    AHC_OSD_SEMITP_INV = (0x03 << 2)
} AHC_OSD_SEMITP_TYPE;

typedef enum _AHC_OSD_ALPHA_FMT
{
    AHC_OSD_ALPHA_RGBA = 0,
    AHC_OSD_ALPHA_ARGB,
    AHC_OSD_ALPHA_GLOBAL,
} AHC_OSD_ALPHA_FMT;

typedef enum _AHC_OSD_ATTR 
{
    AHC_OSD_ATTR_MIRROR = 0,
    AHC_OSD_ATTR_ROTATE, //Rotated by AIT HW window. Currently we are not using it due to performance issue.
    AHC_OSD_ATTR_TRANSPARENT_ENABLE,
    AHC_OSD_ATTR_SEMI_TRANSPARENT_ENABLE,
    AHC_OSD_ATTR_ALPHA_BLENDING_ENABLE,
    AHC_OSD_ATTR_DISPLAY_OFFSET,
    AHC_OSD_ATTR_DISPLAY_SCALE,
    AHC_OSD_ATTR_ROTATE_BY_GUI, //Rotated by GUI.
    AHC_OSD_ATTR_FLIP_BY_GUI //fliped by GUI.    
} AHC_OSD_ATTR;

typedef enum _AHC_OSD_COLOR_FMT 
{
    OSD_COLOR_RGB332 = GUI_COLOR_RGB332,
    OSD_COLOR_RGB565 = GUI_COLOR_RGB565,
    OSD_COLOR_RGB888 = GUI_COLOR_RGB888,
    OSD_COLOR_ARGB32 = GUI_COLOR_ARGB32,
    OSD_COLOR_ALPHA_START = OSD_COLOR_ARGB32,
    OSD_COLOR_ARGB3454 = GUI_COLOR_ARGB3454,
    // Need New GUI.a
    OSD_COLOR_ARGB32_CCW = GUI_COLOR_ARGB32_CCW,
    OSD_COLOR_RGB565_CCW = GUI_COLOR_RGB565_CCW,
    OSD_COLOR_YUV422, //For CCIR output   

    OSD_COLOR_MAX
} AHC_OSD_COLOR_FMT;

typedef enum _AHC_STICKER_ID 
{
    AHC_STICKER_PIPE0_ID0 = 0,
    AHC_STICKER_PIPE0_ID1,
    AHC_STICKER_PIPE1_ID0,
    AHC_STICKER_PIPE1_ID1,
    AHC_STICKER_ID_NUM
} AHC_STICKER_ID;

typedef enum _AHC_OSD_ROTATE_DRAW_MODE 
{
    OSD_ROTATE_DRAW_NONE        = GUI_ROTATE_DRAWING_0,
    OSD_ROTATE_DRAW_RIGHT_90    = GUI_ROTATE_DRAWING_90,
    OSD_ROTATE_DRAW_RIGHT_180   = GUI_ROTATE_DRAWING_180,
    OSD_ROTATE_DRAW_RIGHT_270   = GUI_ROTATE_DRAWING_270
} AHC_OSD_ROTATE_DRAW_MODE;

typedef enum _AHC_OSD_FILP_DRAW_MODE 
{
    OSD_FLIP_DRAW_NONE_ENABLE   = GUI_FLIP_DRAWING_NONE_ENABLE,
    OSD_FLIP_DRAW_LR_ENABLE     = GUI_FLIP_DRAWING_LR_ENABLE,
    OSD_FLIP_DRAW_UD_ENABLE     = GUI_FLIP_DRAWING_UD_ENABLE
} AHC_OSD_FILP_DRAW_MODE;

/* GUI in MultiTask */
#define BEGIN_LAYER(l)  {   extern AHC_OSD_INSTANCE *m_OSD[]; \
                            if (m_OSD[l] && (m_OSD[l]->gui.gui_semi < 0xFE)) { \
                                if (AHC_OS_AcquireSem(m_OSD[l]->gui.gui_semi, 10000) != MMPF_OS_ERR_NONE) \
                                    {AHC_DBG_ERR(1, "ERROR:%s %d Lock fail, OSD-ID[%d]!!\r\n", __FUNCTION__, __LINE__, l);} \
                            } \
                            else {AHC_DBG_ERR(1, "ERROR:%s %d GUI layer error\r\n", __FUNCTION__, __LINE__);} \
                        }

#define END_LAYER(l)    {   extern AHC_OSD_INSTANCE *m_OSD[]; \
                            if (m_OSD[l] && (m_OSD[l]->gui.gui_semi < 0xFE)) { \
                                AHC_OS_ReleaseSem(m_OSD[l]->gui.gui_semi); \
                            } \
                            else {AHC_DBG_ERR(1, "ERROR:%s %d GUI layer error\r\n", __FUNCTION__, __LINE__);} \
                        }

#define WMSG_LAYER_WIN_COLOR_FMT    (OSD_COLOR_RGB565)//(OSD_COLOR_ARGB32)

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

typedef struct _AHC_GUI_CONTEXT{
    GUI_FONT*               gui_pfont;
    GUI_COLOR               gui_fnclr;
    GUI_COLOR               gui_bkclr;
    UINT8                   gui_pen;
    AHC_OS_SEMID            gui_semi;

    AHC_OSD_ROTATE_DRAW_MODE ulRotateByGUI;
    AHC_OSD_FILP_DRAW_MODE ulFlipByGUI;
} AHC_GUI_CONTEXT;

typedef struct _AHC_OSD_INSTANCE {
    UINT32                  id;
    UINT32                  ColorFormat;
    UINT32                  Color;
    UINT32                  size;
    UINT32                  width;
    UINT32                  height;
    UINT32                  line_offset;
    UINT32                  bMirror;
    UINT32                  rotate_type;
    UINT32                  TransparentEnable;
    UINT32                  TransparentColor;
    UINT32                  SemiTpEnable;
    UINT32                  SemiTpType;
    UINT32                  SemiTpWeight;
    UINT32                  AlphaBlendingEnable;
    UINT32                  AlphaFormat;
    UINT32                  DisplayOffsetX;
    UINT32                  DisplayOffsetY;
    UINT8                   AlphaWeight;    ///< The alpha blending weight for all layers
    UINT8                   palette[256*4]; ///< ARGB32 x 256 entries
    AHC_GUI_CONTEXT         gui;
    UINT8                   *data;

    UINT32                  DuplicateW;
    UINT32                  DuplicateH;
} AHC_OSD_INSTANCE;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

AHC_BOOL        AIHC_GetOSDInitStatus(void);
AHC_BOOL        AIHC_DrawReservedOSD(AHC_BOOL bDrawReserved);

AHC_BOOL        AHC_OSDInit(    U32 OSDWidth,
                                U32 OSDHeight,
                                U32 ThumbWidth,
                                U32 ThumbHeight,
                                U32 PrimaryDateWidth,
                                U32 PrimaryDateHeight,
                                U32 ThumbDateWidth,
                                U32 ThumbDateHeight,
                                U32 ColorFormat,
                                AHC_BOOL MainBuffFull,
                                AHC_OSD_ROTATE_DRAW_MODE ahcOSDRotateDraw);
AHC_BOOL        AHC_OSDUninit(void);
AHC_BOOL        AHC_OSDCreateBuffer(UINT16 uwDisplayID,UINT16 uiWidth,UINT16 uiHeight,AHC_OSD_COLOR_FMT uiColorFormat);
AHC_BOOL        AHC_OSDDestroyBuffer(UINT16 uwDisplayID);
AHC_BOOL        AHC_OSDDuplicateBuffer(UINT16 uwSrcIndex, UINT16 uwDesIndex);
AHC_BOOL        AHC_OSDDuplicateAttr(UINT16 uwSrcIndex, UINT16 uwDesIndex);
AHC_BOOL        AHC_OSDRefresh(void);
AHC_BOOL        AHC_OSDRefresh_PLCD(void);
AHC_BOOL        AHC_OSDGetBufferAttr(UINT8 uwDisplayID, UINT16 *puiWidth, UINT16 *puiHeight,UINT16 *puiColorFormat,UINT32 *pulBufferAddr);
AHC_BOOL        AHC_OSDSetDisplayAttr(UINT8 byDisplayID, AHC_OSD_ATTR byAttr, UINT32 uwParam[]);
AHC_BOOL        AHC_OSDClearBuffer(UINT16 uwDisplayID);
AHC_BOOL        AHC_OSDUpdateAddrOnly(AHC_BOOL OSDUpdateAddrOnly) ;
AHC_BOOL        AHC_OSDSetActive(UINT16 uwDisplayID, UINT8 bActive);
AHC_BOOL        AHC_OSDSetCurrentDisplay(UINT16 uwDisplayID);
AHC_BOOL        AHC_OSDLoadWinPalette(UINT16 uwDisplayID);
AHC_BOOL        AHC_OSDLoadIconIndexColorTable(UINT16 uwDisplayID, AHC_STICKER_ID stickerID, UINT8 byColorFormat);
AHC_BOOL        AHC_OSDLoadIconIndexColorTable2(AHC_STICKER_ID stickerID, UINT8 byColorFormat, UINT16* uwLutTable, int nNum);

const GUI_FONT* AHC_OSDSetFont(UINT8 id, const GUI_FONT *pNewFont);
const GUI_FONT* AHC_OSDGetFont(UINT8 id);
UINT8           AHC_OSDSetPenSize(UINT8 id, UINT8 byPenSize);
UINT8           AHC_OSDGetPenSize(UINT8 id);
AHC_OSD_ROTATE_DRAW_MODE AHC_OSDGetGuiRotateByGUI(UINT8 id);
AHC_BOOL        AHC_OSDGetDuplicateWH(UINT8 id,UINT32 *W, UINT32 *H);
void            AHC_OSDSetBkColor(UINT8 id, GUI_COLOR Color);
GUI_COLOR       AHC_OSDGetBkColor(UINT8 id);
void            AHC_OSDSetColor(UINT8 id, GUI_COLOR Color);
GUI_COLOR       AHC_OSDGetColor(UINT8 id);

AHC_BOOL        AHC_OSDGetCurPos(UINT32* curX, UINT32* curY);
UINT32          AHC_OSDGetFontDistY(void);

AHC_BOOL        AHC_OSDDrawGradientH(UINT16 uwDisplayID,UINT16 uwUpLeftX,UINT16 uwUpLeftY,UINT16 uwLowRightX,UINT16 uwLowRightY,UINT32 ulStartColor,UINT32 ulGradientColor);
AHC_BOOL        AHC_OSDDrawGradientV(UINT16 uwDisplayID,UINT16 uwUpLeftX,UINT16 uwUpLeftY,UINT16 uwLowRightX,UINT16 uwLowRightY,UINT32 ulStartColor,UINT32 ulGradientColor);
AHC_BOOL        AHC_OSDDrawPixel(UINT16 uwDisplayID,UINT16 uwX,UINT16 uwY);
AHC_BOOL        AHC_OSDDrawPoint(UINT16 uwDisplayID,UINT16 uwX,UINT16 uwY);
AHC_BOOL        AHC_OSDClearRect(UINT16 uwDisplayID,UINT16 uwUpLeftX,UINT16 uwUpLeftY,UINT16 uwLowRightX,UINT16 uwLowRightY);
AHC_BOOL        AHC_OSDDrawRect(UINT16 uwDisplayID,UINT16 uwUpLeftX,UINT16 uwUpLeftY,UINT16 uwLowRightX,UINT16 uwLowRightY);
AHC_BOOL        AHC_OSDDrawRect2(UINT16 uwDisplayID, PRECT pRect);
AHC_BOOL        AHC_OSDDrawFillRect(UINT16 uwDisplayID,UINT16 uwUpLeftX,UINT16 uwUpLeftY,UINT16 uwLowRightX,UINT16 uwLowRightY);
AHC_BOOL        AHC_OSDDrawFillRect2(UINT16 uwDisplayID, PRECT pRect);
AHC_BOOL        AHC_OSDDrawFillRectEx2(UINT16 uwDisplayID, PRECT pRect, PRECTOFFSET pOff);
AHC_BOOL        AHC_OSDDrawInvertRect(UINT16 uwDisplayID,UINT16 uwUpLeftX,UINT16 uwUpLeftY,UINT16 uwLowRightX,UINT16 uwLowRightY);
AHC_BOOL        AHC_OSDDrawBitmap(UINT16 uwDisplayID,const GUI_BITMAP *pBmp,UINT16 uwX,UINT16 uwY);
AHC_BOOL        AHC_OSDDrawBitmapEx(UINT16 uwDisplayID,const GUI_BITMAP *pBmp,UINT16 uwX,UINT16 uwY,UINT16 uwXCenter,UINT16 uwYCenter,UINT16 uwXMag,UINT16 uwYMag);
AHC_BOOL        AHC_OSDDrawBitmapMag(UINT16 uwDisplayID,const GUI_BITMAP *pBmp,UINT16 uwX,UINT16 uwY,UINT16 uwXMul,UINT16 uwYMul);
AHC_BOOL        AHC_OSDDrawLine(UINT16 uwDisplayID,UINT16 uwXStart,UINT16 uwXEnd,UINT16 uwYStart,UINT16 uwYEnd);
AHC_BOOL        AHC_OSDDrawRoundedRect(UINT16 uwDisplayID,UINT16 uwUpLeftX,UINT16 uwUpLeftY,UINT16 uwLowRightX,UINT16 uwLowRightY, UINT16 uwRadius);
AHC_BOOL        AHC_OSDDrawRoundedRect2(UINT16 uwDisplayID, PRECT pRect, UINT16 uwRadius);
AHC_BOOL        AHC_OSDDrawFillRoundedRect(UINT16 uwDisplayID,UINT16 uwUpLeftX,UINT16 uwUpLeftY,UINT16 uwLowRightX,UINT16 uwLowRightY, UINT16 uwRadius);
AHC_BOOL        AHC_OSDDrawFillRoundedRect2(UINT16 uwDisplayID, PRECT pRect, UINT16 uwRadius);
AHC_BOOL        AHC_OSDDrawPolygon(UINT16 uwDisplayID,const GUI_POINT *pPoints,UINT16 uwNumPoints,UINT16 uwX,UINT16 uwY);
AHC_BOOL        AHC_OSDDrawFillPolygon(UINT16 uwDisplayID,const GUI_POINT *pPoints,UINT16 uwNumPoints,UINT16 uwX,UINT16 uwY);
AHC_BOOL        AHC_OSDDrawCircle(UINT16 uwDisplayID,UINT16 uwX,UINT16 uwY,UINT16 uwRadius);
AHC_BOOL        AHC_OSDDrawFillCircle(UINT16 uwDisplayID,UINT16 uwX,UINT16 uwY,UINT16 uwRadius);
AHC_BOOL        AHC_OSDDrawEllipse(UINT16 uwDisplayID,UINT16 uwX,UINT16 uwY,UINT16 uwRadiusX,UINT16 uwRadiusY);
AHC_BOOL        AHC_OSDDrawFillEllipse(UINT16 uwDisplayID,UINT16 uwX,UINT16 uwY,UINT16 uwRadiusX,UINT16 uwRadiusY);
AHC_BOOL        AHC_OSDDrawArc(UINT16 uwDisplayID,UINT16 uwXCenter,UINT16 uwYCenter,UINT16 uwRadiusX,UINT16 uwRadiusY,UINT16 uwAngle1,UINT16 uwAngle2);
AHC_BOOL        AHC_OSDDrawPie(UINT16 uwDisplayID,UINT16 uwX,UINT16 uwY,UINT16 uwRadius,UINT16 uwAngle1,UINT16 uwAngle2);
AHC_BOOL        AHC_OSDDrawJpeg(UINT16 uwDisplayID,const void* pData,UINT16 uwDataSize,UINT16 uwX,UINT16 uwY);
AHC_BOOL        AHC_OSDDrawJpegScale(UINT16 uwDisplayID,const void* pData,UINT16 uwDataSize,UINT16 uwX,UINT16 uwY,UINT16 uwNum,UINT16 uwDenom);
AHC_BOOL        AHC_OSDDrawGif(UINT16 uwDisplayID,const void* pData,UINT16 uwDataSize,UINT16 uwX,UINT16 uwY);
AHC_BOOL        AHC_OSDDrawText(UINT8 byDisplayID, UINT8 *pStrPtr, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwLength);
AHC_BOOL        AHC_OSDDrawTextEx(UINT8 uwDisplayID, UINT8 *pStrPtr, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwLength, UINT16 uwMag);
AHC_BOOL        AHC_OSDDrawDec(UINT8 uwDisplayID, INT32 uwVal, UINT16 uwStartX, UINT16 uwStartY, UINT8 uwLength);
AHC_BOOL        AHC_OSDDrawTextInRect(UINT8 uwDisplayID, UINT8 *pStrPtr, GUI_RECT* pRect, INT16 wTextAlign);
AHC_BOOL        AHC_OSDDrawTextInRectWrap(UINT8 uwDisplayID, UINT8 *pStrPtr, GUI_RECT* rc, GUI_COLOR color, INT16 wTextAlign, GUI_WRAPMODE WrapMode);
AHC_BOOL        AHC_OSDDrawTextInRectSlide(UINT8 uwDisplayID, UINT8 *pStrPtr, GUI_RECT* pRect, INT16 wTextAlign, int *ps);

AHC_BOOL        AHC_OSDDisableDrawFontBk(AHC_BOOL bDisable);
AHC_BOOL        AHC_OSDDrawChar(UINT8 uwDisplayID, UINT8 u8Char, UINT16 uwStartX, UINT16 uwStartY);
AHC_BOOL        AHC_OSDDrawString(UINT8 uwDisplayID, UINT8* pStr);
AHC_BOOL        AHC_OSDDrawTextInRectEx(UINT8 uwDisplayID, UINT8 *pStrPtr, UINT32 uwStartX, UINT32 uwStartY, UINT32 uwEndX, UINT32 uwEndY, INT16 wTextAlign, UINT16 uwLength, UINT32 ulRotate);
AHC_BOOL        AHC_OSDDrawBuffer(UINT8 uwDisplayID, UINT8 *InBuffer, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwWidth, UINT16 uwHeight, AHC_OSD_COLOR_FMT uiColorFormat);
AHC_BOOL        AHC_OSDDrawTextEdgeInRect(UINT8 uwDisplayID, GUI_RECT* pRect, GUI_COLOR edgeColor, GUI_COLOR bkColor);

void            AHC_OSDSetFlipDrawMode(UINT8 id, AHC_OSD_FILP_DRAW_MODE byMode);
AHC_BOOL        AHC_OSDDrawHex(UINT8 uwDisplayID, INT32 uwVal, UINT16 uwStartX, UINT16 uwStartY, UINT8 uwLength);
AHC_BOOL        AHC_OSDDrawFloat(UINT8 uwDisplayID, double uwVal, UINT8 uwLength);

AHC_BOOL        AHC_OSDDrawText_Transparent(UINT8 uwDisplayID, UINT8 *pStrPtr, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwLength);
AHC_BOOL        AHC_OSDDrawDec_Transparent(UINT8 uwDisplayID, INT32 uwVal, UINT16 uwStartX, UINT16 uwStartY, UINT8 uwLength);
AHC_BOOL        AHC_OSDDrawHex_Transparent(UINT8 uwDisplayID, INT32 uwVal, UINT16 uwStartX, UINT16 uwStartY, UINT8 uwLength);
AHC_BOOL        AHC_OSDDrawFloat_Transparent(UINT8 uwDisplayID, double uwVal, UINT8 uwLength);

/* For Unicode */
int             AHC_UC_ConvertUC2UTF8   (const UINT16  * s, int Len, char * pBuffer, int BufferSize);
int             AHC_UC_ConvertUTF82UC   (const char  * s, int Len, UINT16 * pBuffer, int BufferSize);
int             AHC_UC_Encode           (char* s, UINT16 Char);
int             AHC_UC_GetCharSize      (const char  * s);
UINT16          AHC_UC_GetCharCode      (const char  * s);
void            AHC_UC_SetEncodeNone    (void);
void            AHC_UC_SetEncodeUTF8    (void);
AHC_BOOL        AHC_UC_OSDDrawText(UINT8 uwDisplayID,const UINT16  *pStrPtr, UINT16 uwStartX, UINT16 uwStartY, UINT16 uwLength);
AHC_BOOL        AHC_UC_DispString(UINT8 uwDisplayID, const UINT16  *s);
void            AHC_UC2DB (UINT16 Code, UINT8* pOut);
UINT16          AHC_DB2UC (UINT8 Byte0, UINT8 Byte1);

/* For Dot-Matrix Panel */
AHC_BOOL        AHC_DisplayAll(UINT16 uwDisplayID);
void            AHC_SetDispX_Mirror(void);
void            AHC_DisplayOff(void);
AHC_ERR         AHC_OSD_BufConvert(UINT16 uwDisplayID);

/* GUI in MultiTask */
void            AHC_LockGUI(void);
void            AHC_UnlockGUI(void);

UINT16          AHC_GET_ATTR_OSD_W(UINT16 uwId);
UINT16          AHC_GET_ATTR_OSD_H(UINT16 uwId);
AHC_BOOL        AHC_OSDChangeDimetion(UINT16 uwDisplayID, UINT16 uwWidth, UINT16 uwHeight);
void            AHC_OSD_ExternalFillRectCB(unsigned long ulDst, int iXSize, int iYSize, int iLineOffset, int iColorDepth, int iX0, int iY0, int iX1, int iY1, unsigned long usPixelIndex);
void            AHC_OSD_RegisterInitOSDCustomCB(void *pInitOSDCustomCB);

#endif  // _AHC_GUI_H_
