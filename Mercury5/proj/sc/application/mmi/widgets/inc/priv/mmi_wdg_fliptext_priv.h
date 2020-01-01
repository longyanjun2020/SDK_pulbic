/**
 * @file    mmi_wdg_glowtext_priv.h
 *
 */

#ifndef __MMI_WDG_FLIPTEXT_PRIV_H__
#define __MMI_WDG_FLIPTEXT_PRIV_H__

#if defined(__APP_MMI_FM_RADIO__) && defined(__3D_UI_FMRADIO__)

#include "mae_abscontainerbase.h"
#include "mae_animation.h"
#include "mgl_core_types.h"
#include "mgl_utility_common.h"
#include "mmi_wdg_fliptext.h"

#define TIMES                           1
#define FLIPTEXT_ANIMATION_TIMER        (65*TIMES)

#if defined(__LCM_HVGA_320_480_MMI__) || defined(__LCM_LANDSCAPE_HVGA_MMI__)
#define STYLE_LARGE_TEXT_PADDING        4
#define STYLE_LARGE_TEXT_W              32
#define STYLE_LARGE_TEXT_H              66
#define STYLE_LARGE_DOT_W               10

#else
#define STYLE_LARGE_TEXT_PADDING        3
#define STYLE_LARGE_TEXT_W              24
#define STYLE_LARGE_TEXT_H              48
#define STYLE_LARGE_DOT_W               10

#endif //__LCM_HVGA_320_480_MMI__

#define FLIPTEXT_IMAGE_COUNT 5
#define DIGIT_MAX 4

/*  Declarations */
typedef enum
{
    FLIPTEXT_ANI_NONE = 0,

    FLIPTEXT_ANI_TYPE_DECIMAL1,
    FLIPTEXT_ANI_TYPE_DECIMAL2,
    FLIPTEXT_ANI_TYPE_DECIMAL3,
    FLIPTEXT_ANI_TYPE_DECIMAL4,
    FLIPTEXT_ANI_TYPE_DECIMAL5,
    FLIPTEXT_ANI_TYPE_DECIMAL6,
    FLIPTEXT_ANI_TYPE_END,
    FLIPTEXT_ANI_TYPE_INTEGER_END,

    FLIPTEXT_ANI_TYPE_CONTINUE,

    FLIPTEXT_ANI_COUNT
} eFLIPTEXT_ANI_TYPE;

typedef enum
{
    FLIPTEXT_ROTATE_NONE = 0,

    // decimal place
    FLIPTEXT_ROTATE_DECIMAL1, // startA 7 frames (n)
    FLIPTEXT_ROTATE_DECIMAL2, // startB 4 frames (n+1)
    FLIPTEXT_ROTATE_DECIMAL3, // 3 frames
    FLIPTEXT_ROTATE_DECIMAL4, // fast 0, 90, 90
    FLIPTEXT_ROTATE_DECIMAL5, // end 1 (n-1)
    FLIPTEXT_ROTATE_DECIMAL6, // end 2 (n)
    FLIPTEXT_ROTATE_DECIMAL7, // startC DOWN
    FLIPTEXT_ROTATE_DECIMAL8, // startC UP
    FLIPTEXT_ROTATE_DECIMAL_FAST, // dynamic fast 0, 90, 90
    FLIPTEXT_ROTATE_DECIMAL9,
    FLIPTEXT_ROTATE_DECIMAL_END,

    FLIPTEXT_ROTATE_DECIMAL_CONTINUE,

    FLIPTEXT_ROTATE_DECIMAL_MAX = FLIPTEXT_ROTATE_DECIMAL_CONTINUE + 1,

    FLIPTEXT_ROTATE_COUNT
} eFLIPTEXT_ROTATE_TYPE;

typedef struct
{
    Vertex2D vTextSize;
    Vertex2D vDotSize;
    Vertex3D vPos[FLIPTEXT_IMAGE_COUNT];
    u32      nTextImgId[10];
    u32      nDotImgId;
}_FlipTextStyleInfo;

typedef struct
{
    AbsContainerBase_t AbsCntrBase;
    eFLIPTEXT_TEXTSTYLE eTextStyle;
    MAE_WChar   pStrText[FLIPTEXT_IMAGE_COUNT+1];
    MAE_WChar   pNextStrText[FLIPTEXT_IMAGE_COUNT+1];

    float       fStrTextAngle[FLIPTEXT_IMAGE_COUNT];
    s8          sFlipTextInc[FLIPTEXT_IMAGE_COUNT];
    boolean     bAnimating;

    u32         nCurFreq;
    u32         nNextFreq;
    s16         sDigitDistance[DIGIT_MAX];
    u8          nDigitSMIdx[DIGIT_MAX];
    s8          nDigitInc[DIGIT_MAX];
    s8          sDecMax[DIGIT_MAX];
    s8          sDigitStartCycle[DIGIT_MAX];
    s8          sStartDigitIdx;
    s16         sValueDiff;
    u8          pnDigitValue[DIGIT_MAX];

    s8          eAni;
    s8          eAniDigit[DIGIT_MAX];
    boolean     bFlipBoundary; // for 9->0 or 0->9

    u8          nLoopCycleCount;
    float       fdigitAngle[DIGIT_MAX];
    s16         digitAngleCycle[DIGIT_MAX];
    boolean     bAniContinue;
    mgl_u16	    u16SceneHandleId; ///< MGL scene id
    u32         nNodeId;

    u32         nReloadRCFlag;  ///< the flag record which rc property has been modified outside, those are not reload
}_MAE_FlipTextWidget;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/

MAE_Ret FlipTextWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean FlipTextWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/

MAE_Ret _WdgFlipTextConstructor(_MAE_FlipTextWidget *pThis);
void _WdgFlipTextDestructor(_MAE_FlipTextWidget *pThis);
static void WdgFlipTextDrawText(_MAE_FlipTextWidget *pThis, mgl_u32 nodeID, u8 nIdx, s32 x, s32 y);
static void WdgFlipTextDraw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
static void _FlipTextWidget_ReloadRC(_MAE_FlipTextWidget *pThis, DisplayMode_e nDispMode);
static void _FlipTextWidgetAniFlipToStrCb(void * pUser);
static MAE_Ret _SMUpdateTextImage(_MAE_FlipTextWidget *pThis);
#endif //#if defined(__APP_MMI_FM_RADIO__) && defined(__3D_UI_FMRADIO__)

#endif /* __MMI_WDG_FLIPTEXT_PRIV_H__ */

