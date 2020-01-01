#ifndef __MMI_WDG_VOLUME_PRIV_H__
#define __MMI_WDG_VOLUME_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_abscontainerbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum
{
	IMAGE_VOL_FIRST,
	IMAGE_VOL_NORMAL = IMAGE_VOL_FIRST,            
	IMAGE_VOL_SILENT,            
	IMAGE_VOL_OFF,               
	IMAGE_VOL_LEVEL_BG,          
	IMAGE_VOL_LEVEL,             
#ifdef __TOUCH_SCREEN_MMI__
	IMAGE_VOL_DECREASE_DISABLE,  
	IMAGE_VOL_DECREASE_PRESSED,  
	IMAGE_VOL_DECREASE_UNPRESSED,
	IMAGE_VOL_INCREASE_DISABLE,  
	IMAGE_VOL_INCREASE_PRESSED,  
	IMAGE_VOL_INCREASE_UNPRESSED,
	IMAGE_VOL_OFF_DISABLE,       
	IMAGE_VOL_OFF_PRESSED,       
	IMAGE_VOL_OFF_UNPRESSED,	
#endif
    IMAGE_VOL_NORMAL_BG,
    IMAGE_VOL_SILENT_BG,
	IMAGE_VOL_LAST = IMAGE_VOL_SILENT_BG
}VOL_IMAGE_ELEMENT_e;



enum
{
	VOLUME_WDG_FLAG_START = 0,
	VOLUME_WDG_FLAG_SILENT = WDG_BASE_FLAG_START,   ///< To keep whether this widget is silent.
	VOLUME_WDG_FLAG_DISABLE_MUTE_BUTTON,
	VOLUME_WDG_FLAG_NOT_ALLOW_MUTE_LEVEL,
	VOLUME_WDG_FLAG_END
};


/**
* Flag Mask
*/
#define VOLUME_WDG_MASK_SILENT						(1<<VOLUME_WDG_FLAG_SILENT)
#define VOLUME_WDG_MASK_DISABLE_MUTE_BUTTON         (1<<VOLUME_WDG_FLAG_DISABLE_MUTE_BUTTON)
#define VOLUME_WDG_MASK_NOT_ALLOW_MUTE_LEVEL         (1<<VOLUME_WDG_FLAG_NOT_ALLOW_MUTE_LEVEL)


/**
* Macro to get flag value
*/
#define VOLUME_WDG_IS_SILENT(_pVolWdg) \
	(boolean)(((_pVolWdg)->Flags&VOLUME_WDG_MASK_SILENT)>>VOLUME_WDG_FLAG_SILENT)
#define VOLUME_WDG_IS_DISABLE_MUTE_BUTTON(_pVolWdg) \
	(boolean)(((_pVolWdg)->Flags&VOLUME_WDG_MASK_DISABLE_MUTE_BUTTON)>>VOLUME_WDG_FLAG_DISABLE_MUTE_BUTTON)
#define VOLUME_WDG_IS_NOT_ALLOW_MUTE_LEVEL(_pVolWdg) \
	(boolean)(((_pVolWdg)->Flags&VOLUME_WDG_MASK_NOT_ALLOW_MUTE_LEVEL)>>VOLUME_WDG_FLAG_NOT_ALLOW_MUTE_LEVEL)

/**
* Macro to Set flag value
*/
#define VOLUME_WDG_SET_SILENT(_pVolWdg, _b) \
	(_pVolWdg)->Flags = ((_pVolWdg)->Flags&(~VOLUME_WDG_MASK_SILENT))|(((u32)_b)<<VOLUME_WDG_FLAG_SILENT)
#define VOLUME_WDG_SET_DISABLE_MUTE_BUTTON(_pVolWdg, _b) \
	(_pVolWdg)->Flags = ((_pVolWdg)->Flags&(~VOLUME_WDG_MASK_DISABLE_MUTE_BUTTON))|(((u32)_b)<<VOLUME_WDG_FLAG_DISABLE_MUTE_BUTTON)
#define VOLUME_WDG_SET_NOT_ALLOW_MUTE_LEVEL(_pVolWdg, _b) \
	(_pVolWdg)->Flags = ((_pVolWdg)->Flags&(~VOLUME_WDG_MASK_NOT_ALLOW_MUTE_LEVEL))|(((u32)_b)<<VOLUME_WDG_FLAG_NOT_ALLOW_MUTE_LEVEL)

typedef struct {

	AbsContainerBase_t	AbsCntrBase;				///< Using AbsContainer_t as base structure.
	IWidget			*pVolumeImageWdg;			///< An Bitmap-widget to display Volume sybmol image
	IWidget			*pEmptyLevImageWdg;		/// < An Bitmap-widget to display empty volume level image
	IWidget			*pFullLevImageWdg;			/// < An Bitmap-widget to display full volume level image
	IWidget			*pIncrButtonWdg;			/// < An Button-widget to display Increase indicator image
	IWidget			*pDecrButtonWdg;			/// < An Button-widget to display Decrease indicator image
	IWidget			*pMuteButtonWdg;			/// < An Button-widget to display mute indicator image

	//ModelListener_t 	IncrButtonWdgMdlLsn;	///< Model listener for listening the data model change.
	//ModelListener_t 	DecrButtonWdgMdlLsn;	///< Model listener for listening the data model change.
	//ModelListener_t 	MuteButtonWdgMdlLsn;	///< Model listener for listening the data model change.
	ModelListener_t 	MdlLsn;					///< Model listener for listening the data model change.

	VolumeWdgInfo_t volumeInfo;
	u32             Flags;						///< Abilities and settings flag.

    IImage *pIImage[IMAGE_VOL_LAST+1];
	boolean          bAudioSettingOnly;
	
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
	boolean                                     nCreatedTimer;
} WdgVolume_t;

// RELOAD flag
enum
{
	VOLUME_WDG_RELOAD_FLAG_START = 0,
	VOLUME_WDG_RELOAD_FLAG_SILENT = VOLUME_WDG_RELOAD_FLAG_START,
	VOLUME_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define VOLUME_WDG_RELOAD_MASK_SILENT         (1<<VOLUME_WDG_RELOAD_FLAG_SILENT)
/**
* Macro to get flag value
*/
#define VOLUME_WDG_SILENT_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&VOLUME_WDG_RELOAD_MASK_SILENT)>>VOLUME_WDG_RELOAD_FLAG_SILENT)
/**
* Macro to Set flag value
*/
#define VOLUME_WDG_SILENT_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~VOLUME_WDG_RELOAD_MASK_SILENT))|(((u32)_b)<<VOLUME_WDG_RELOAD_FLAG_SILENT)
/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret VolumeWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgVolumeDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgVolumeConstructor(WdgVolume_t *pThis );
void _WdgVolumeDestructor(WdgVolume_t *pThis);

void _WdgVolumeSetImage2ImageWidget(IWidget *pIImageWidget,  VOL_IMAGE_ELEMENT_e BitmapElement, IBase* pThis);
void _WdgVolumeSetImage2ButtonWidget(IWidget *pIButtonWidget, VOL_IMAGE_ELEMENT_e UnpressedImgID, VOL_IMAGE_ELEMENT_e PressedImgId,IBase* pThis);
void _WdgVolumeNoPress_TimeoutCB(void* data);
void _WdgVolumeEventNotify(WdgVolume_t *pThis, ModelEvtCode_t evt);
boolean _WdgVolumeSetProperty(WdgVolume_t *pThis, u32 P1, u32 P2);
boolean _WdgVolumeGetProperty(WdgVolume_t *pThis, u32 P1, u32 P2);
void _WdgVolumeUpdateLevel(WdgVolume_t *pThis);

void _WdgVolumeDecrButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void _WdgVolumeIncrButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void _WdgVolumeMuteButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

MAE_Ret _WdgVolumeLoadImageResource(WdgVolume_t *pThis);
void _WdgVolumeReleaseImageResource(WdgVolume_t *pThis);
boolean _WdgVolumeCheckMuteNotAllow(WdgVolume_t *pThis);

static void _WdgVolume_ReloadRC(WdgVolume_t *pThis, DisplayMode_e nDispMode);

#endif //__MMI_WDG_VOLUME_PRIV_H__
/*=============================================================*/
// end of file













