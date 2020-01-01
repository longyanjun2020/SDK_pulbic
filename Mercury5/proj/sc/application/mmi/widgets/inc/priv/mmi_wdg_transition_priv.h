#ifndef __MMI_WDG_TRANSITION_PRIV_H__
#define __MMI_WDG_TRANSITION_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_transition.h"
#include "mae_decoratorbase.h"

/*************************************************************************/
/*   Type/Structure/Enum definitions                                     */
/*************************************************************************/
#define TRANSIT_INTRVAL        50
#define TRANSIT_END_WAIT_TIME  50
#define TRANSIT_BLOCKSIZE      30

#define TRANSIT_FADE_STEPS      8
#define TRANSIT_FADE_INTERVAL 100

#define TRANSIT_FLASH_STEPS      5
#define TRANSIT_FLASH_INTERVAL 100

#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
#define TRANSIT_IFONE_STEPS	6
#define TRANSIT_IFONE_DURATION 60
#define TRANSIT_IFONE_SHORT_STEPS	2
#define TRANSIT_IFONE_SHORT_DURATION 120

#define TRANSIT_IFONE_LONG_STEPS	TRANSIT_IFONE_STEPS
#define TRANSIT_IFONE_LONG_DURATION TRANSIT_IFONE_DURATION
#endif /* __UI_STYLE_MMI_IFONE__ */

#define TRANSIT_SLIP_STEPS	6
#define TRANSIT_SLIP_DURATION 60

enum
{
	TRANS_INVALIDATE_NONE = 0,
	TRANS_INVALIDATE_ALL,
	TRANS_INVALIDATE_PRATIAL
};

typedef u8 TransInvalidateType_t;

struct WdgTransition_t;
typedef void                  (* PFN_TRAN_INIT) (struct WdgTransition_t*, TransitionDirection_t, u32);
typedef TransInvalidateType_t (* PFN_TRAN_DO)   (struct WdgTransition_t*);
typedef void                  (* PFN_TRAN_DRAW) (struct WdgTransition_t*, IDispCanvas*, s32, s32);
typedef void                  (* PFN_TRAN_END)  (struct WdgTransition_t*);

typedef struct TransFunc_tag
{
	TransitionType_t type;
	PFN_TRAN_INIT    pFnInitTrans;
	PFN_TRAN_DO      pFnDoTrans;
	PFN_TRAN_DRAW    pFnDraw;
	PFN_TRAN_END     pFnEndTrans;
}TransFunc_t;

typedef struct
{
	TransitionDirection_t dir;
}EffectDataPush_t;

#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
typedef struct
{
	TransitionDirection_t dir;
}EffectDataIphone_t;
#endif

typedef struct
{
    TransitionDirection_t dir;
}EffectDataSlip_t;

typedef struct
{
	u32 NextFadeLevel;
}EffectDataFade_t;

typedef struct
{
	TransitionDirection_t dir;
}EffectDataBlinds_t;

typedef struct
{
	u32 mask;
}EffectDataDissolve_t;

typedef struct
{
	u16 MaskWidth;
	u16 MaskHeight;
	TransitionDirection_t  dir;
}EffectDataIris_t;

typedef struct
{
	u32 times;
}EffectDataFlash_t;

typedef struct
{
	TransitionDirection_t dir;
}EffectDataBarn_t;

typedef struct
{
	TransitionDirection_t dir;
}EffectDataStretch_t;

typedef struct
{
	s16 xDiff;
	s16 yDiff;
}EffectDataSqueeze_t;

typedef struct
{
	u32 angle;
}EffectDataRotate_t;

typedef struct
{
	u32 rate;
}EffectDataZoom_t;

typedef struct
{
    TransitionDirection_t dir;
}EffectDataRolling_t;

typedef union
{
	EffectDataPush_t     Push;
	EffectDataFade_t     Fade;
	EffectDataBlinds_t   Blinds;
	EffectDataDissolve_t Dissolve;
	EffectDataIris_t     Iris;
	EffectDataFlash_t    Flash;
	EffectDataBarn_t     Barn;
	EffectDataStretch_t  Stretch;
	EffectDataSqueeze_t  Squeeze;
	EffectDataRotate_t   Rotate;
    EffectDataZoom_t     Zoom;
    EffectDataRolling_t  Rolling;
#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
	EffectDataIphone_t   Iphone;
#endif
    EffectDataSlip_t    Slip;
}EffectData_t;

typedef struct
{
	const TransFunc_t     *ptTransFunc;
	EffectData_t     Effect;
}TranData_t;

typedef struct WdgTransition_t
{
	DecoratorEx_t    DecBase;           ///< Use this as a base structure.
	TranData_t       Transition;
	IWidget         *pWdg2;
	TransitionType_t type;
	u16              interval;
	u16              UsrDefInterval;
	u16              BlockSize;
    u16              AnimOffset;
	s16              xOffset1;
	s16              yOffset1;
	s16              xOffset2;
	s16              yOffset2;
	u32				nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
	u8               TotalSteps;
	u8               CurStep;
	u8               bTransiting;

    s16                       xstart;
    s16                       ystart;
    boolean                   bEndTransition;
    IWidget                   *pTargetWdg;
#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
    IWidget                   *pWdg3;
    s16                       xOffset3;
	s16                       yOffset3;
	TransitionChildWdgExist_t CurExistWdg;
    boolean                   bFastTransition;
#endif /* __UI_STYLE_MMI_IFONE__*/    /* for ifone style main menu end */
    WdgTransitionTransitDoneData_t tTransitDoneData;
} WdgTransition_t;

// RELOAD flag
enum
{
	TRANSITION_WDG_RELOAD_FLAG_START = 0,
	TRANSITION_WDG_RELOAD_FLAG_USRDEFINTERVAL = TRANSITION_WDG_RELOAD_FLAG_START,   ///< UsrDefInterval
	TRANSITION_WDG_RELOAD_FLAG_BLOCKSIZE,	///< BlockSize
	TRANSITION_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define TRANSITION_WDG_RELOAD_MASK_USRDEFINTERVAL         (1<<TRANSITION_WDG_RELOAD_FLAG_USRDEFINTERVAL)
#define TRANSITION_WDG_RELOAD_MASK_BLOCKSIZE         (1<<TRANSITION_WDG_RELOAD_FLAG_BLOCKSIZE)
/**
* Macro to get flag value
*/
#define TRANSITION_WDG_USRDEFINTERVAL_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TRANSITION_WDG_RELOAD_MASK_USRDEFINTERVAL)>>TRANSITION_WDG_RELOAD_FLAG_USRDEFINTERVAL)
#define TRANSITION_WDG_BLOCKSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&TRANSITION_WDG_RELOAD_MASK_BLOCKSIZE)>>TRANSITION_WDG_RELOAD_FLAG_BLOCKSIZE)
/**
* Macro to Set flag value
*/
#define TRANSITION_WDG_USRDEFINTERVAL_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TRANSITION_WDG_RELOAD_MASK_USRDEFINTERVAL))|(((u32)_b)<<TRANSITION_WDG_RELOAD_FLAG_USRDEFINTERVAL)
#define TRANSITION_WDG_BLOCKSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~TRANSITION_WDG_RELOAD_MASK_BLOCKSIZE))|(((u32)_b)<<TRANSITION_WDG_RELOAD_FLAG_BLOCKSIZE)

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret TranWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean TranWidget_HandleEvent(IDecorator*, MAE_EventId, u32, u32);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgTransitionConstructor(WdgTransition_t*);
void    _WdgTransitionDestructor(WdgTransition_t *pThis);

void _WdgTransitionGetSize(IDecorator*, WidgetSize_t*);
void _WdgTransitionSetSize(IDecorator*, WidgetSize_t*);
void _WdgTransitionIntersectOpaque(IDecorator*, Wdg_IntersectOpaque_Check_t*);
void _WdgTransitionDraw(IDecorator*, Wdg_Draw_Req_t*);
void _WdgTransitionInvalidate(IDecorator*, WdgContainer_WdgInvalidate_t*);
MAE_Ret _WdgTransitionLocate(IDecorator*, WdgContainer_WdgLocate_t*);
void _WdgTransitionSetDecWidget(IDecorator*, IWidget*);

const TransFunc_t* _WdgTransitionGetEffectFunc(TransitionType_t type);

void _WdgTransitionInitPush(WdgTransition_t*, TransitionDirection_t, u32);
void _WdgTransitionInitFade(WdgTransition_t*, TransitionDirection_t, u32);
void _WdgTransitionInitBlinds(WdgTransition_t*, TransitionDirection_t, u32);
void _WdgTransitionInitIris(WdgTransition_t*, TransitionDirection_t, u32);
void _WdgTransitionInitFlash(WdgTransition_t*, TransitionDirection_t, u32);
void _WdgTransitionInitBarn(WdgTransition_t*, TransitionDirection_t, u32);
void _WdgTransitionInitStretch(WdgTransition_t*, TransitionDirection_t, u32);
void _WdgTransitionInitRolling(WdgTransition_t*, TransitionDirection_t, u32);
#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
void _WdgTransitionInitIphone(WdgTransition_t *, TransitionDirection_t, u32 );
#endif
void _WdgTransitionInitSlip(WdgTransition_t *, TransitionDirection_t, u32);

TransInvalidateType_t _WdgTransitionGeneralDo(WdgTransition_t*);
TransInvalidateType_t _WdgTransitionDoPush(WdgTransition_t*);
TransInvalidateType_t _WdgTransitionDoIris(WdgTransition_t*);


void _WdgTransitionDrawPush(WdgTransition_t*, IDispCanvas*, s32, s32);
void _WdgTransitionDrawFade(WdgTransition_t*, IDispCanvas*, s32, s32);
void _WdgTransitionDrawBlinds(WdgTransition_t*, IDispCanvas*, s32, s32);
void _WdgTransitionDrawIris(WdgTransition_t*, IDispCanvas*, s32, s32);
void _WdgTransitionDrawFlash(WdgTransition_t*, IDispCanvas*, s32, s32);
void _WdgTransitionDrawBarn(WdgTransition_t*, IDispCanvas*, s32, s32);
void _WdgTransitionDrawStretch(WdgTransition_t*, IDispCanvas*, s32, s32);
#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
void _WdgTransitionDrawIphone(WdgTransition_t *, IDispCanvas*, s32, s32);
#endif
void _WdgTransitionDrawSlip(WdgTransition_t *, IDispCanvas*, s32, s32);

void _WdgTransitionTranEndTimeout(WdgTransition_t*);
#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
void _WdgTransitionTranEndIfoneTimeout(WdgTransition_t*);
#endif
void _WdgTransitionTranEndSlipTimeout(WdgTransition_t*);

void _WdgTransitionEffectTimeout(WdgTransition_t *pThis, void *pData);
void _WdgTransitionFinalizeTransition(WdgTransition_t*);
#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
void _WdgTransitionFinalizeIfoneTransition(WdgTransition_t*);
#endif
void _WdgTransitionFinalizeSlipTransition(WdgTransition_t*);
void _WdgTransitionFinalizeSlipChangeTransition(WdgTransition_t *pThis);

#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _TransitionWidget_ReloadRC(WdgTransition_t *pThis, DisplayMode_e nDispMode);
#endif // __AUTO_ROTATE_DISPLAY__

#endif //__MMI_WDG_TRANSITION_PRIV_H__
/*=============================================================*/
// end of file
