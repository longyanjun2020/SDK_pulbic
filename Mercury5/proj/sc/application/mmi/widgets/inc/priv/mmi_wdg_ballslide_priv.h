/**
 * @file    mmi_wdg_ballslide_priv.h
 * @brief   Private structure and definitions of keyguard ballslide widget
 * @version $Id: mmi_wdg_ballslide_priv.h  $
 */
#ifndef __MMI_WDG_BALLSLIDE_PRIV_H__
#define __MMI_WDG_BALLSLIDE_PRIV_H__

#ifdef __MMI_BALLSLIDE_WDG_SUPPORT__

#include "mmi_wdg_ballslide.h"
#include "mmi_wdg_keyguard_type.h"

typedef enum
{
    BALLSLIDE_NULL,
    BALLSLIDE_SLIDEIMG,
    BALLSLIDE_DIALERIMG,
#ifndef __UI_STYLE_MMI_ANDROID_4_0__
    BALLSLIDE_MSGIMG,
#endif // !__UI_STYLE_MMI_ANDROID_4_0__
    BALLSLIDE_LOCKIMG
} BallSlideWdgID_e;

#ifdef __UI_STYLE_MMI_ANDROID_4_0__
typedef enum
{
	SLIDECIRCLE_ST_READY,
	SLIDECIRCLE_ST_ANI_PLAYING,
	SLIDECIRCLE_ST_STOPPED,
	SLIDECIRCLE_ST_NUM
} SlideCircleStatus_e;
typedef struct
{
	SlideCircleStatus_e eStatus;
	u16	nFadeOutCurrentFrame;
	u16	nFadeOutTotalFrame;
} SlideCircleAnim_t;
#define BALLSLIDE_SLIDECIRCLE_FADEOUT_TOTALFRAME (6)
#define BALLSLIDE_SLIDECIRCLE_FADEOUT_FIRSTFRAME (0)
typedef enum
{
	SLIDEWAVE_ST_READY,
	SLIDEWAVE_ST_ANI_PLAY1,
	SLIDEWAVE_ST_ANI_PLAY2,
	SLIDEWAVE_ST_ANI_PLAY3,
	SLIDEWAVE_ST_ANI_PLAY4,
	SLIDEWAVE_ST_ANI_PLAY5,
	SLIDEWAVE_ST_ANI_PLAY6,
	SLIDEWAVE_ST_STOPPED,
	SLIDEWAVE_ST_NUM
} SlideWaveImageStatus_e;
#endif // __UI_STYLE_MMI_ANDROID_4_0__

typedef struct {
    AbsContainerBase_t AbsCntrBase;
#ifdef __UI_STYLE_MMI_ANDROID_4_0__
    SlideCircleAnim_t		tSlideCircleAnim;
    IWidget*                pSlideCircleImageWdg;
    IBitmap*				pSlideCircleImageBitmap;
    IWidget*                pSlideWaveImageWdg;
    IBitmap*                pDialerImageBitmap;
#endif // __UI_STYLE_MMI_ANDROID_4_0__
    IWidget*                pDialerImageWdg;
    IWidget*                pFadeOutBgWdg;
    IWidget*                pSlideImageWdg;
    IWidget*                pMissCallImageBgWdg;
    IWidget*                pMissCallTextWdg;
    IWidget*                pMsgImageWdg;
    IWidget*                pUnreadMsgImageBgWdg;
    IWidget*                pUnreadMsgTextWdg;
    IWidget*                pLockImageWdg;
#ifdef __UI_STYLE_MMI_ANDROID_4_0__
    IBitmap*                pLockImageBitmap;
#endif // __UI_STYLE_MMI_ANDROID_4_0__

    ITouchSrv          		*pITouchSrv;
    MissCallInfo_t       	tSim1MissCallInfo;
    MissCallInfo_t       	tSim2MissCallInfo;
    UnReadMsgInfo_t  		tUnReadInfo;

    boolean                 bPickSlideWdg;    ///flag the slide wdg is been picked.
    boolean                 bSlideImgIsDefault;
    s32                     sTimer;
#ifdef __UI_STYLE_MMI_ANDROID_4_0__
    SlideWaveImageStatus_e	eSlideWaveImageStatus;
    boolean					bSlideComplete;
#endif // __UI_STYLE_MMI_ANDROID_4_0__

} BallSlideWidget_t;

MAE_Ret BallSlideWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean BallSlideWidget_HandleEvent(IContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);
static  boolean _WdgBallSlide_HandleTouchEvents(BallSlideWidget_t *pThis, MAEEvent_t evt, s32 x, s32 y);

MAE_Ret _WdgBallSlideConstructor(BallSlideWidget_t *pThis);
void 	_WdgBallSlideDestructor(BallSlideWidget_t *pThis);
boolean _WdgBallSlideCheckPosInWhichArea(BallSlideWidget_t *pThis,s32 x,s32 y,BallSlideWdgID_e *pWdgName);
boolean _WdgBallSlideResetSlideImgWdgPos(BallSlideWidget_t *pThis,s32 x,s32 y);
void  	_WdgBallSlideResetIconWdgPos(BallSlideWidget_t *pThis);
static void _WdgBallSlideTimerCB(void *pOnwer);

#endif //__MMI_BALLSLIDE_WDG_SUPPORT__
#endif //__MMI_WDG_BALLSLIDE_PRIV_H__

