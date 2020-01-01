/**
* @file    mmi_wdg_image_text_image.h
* @version $Id: mmi_wdg_image_text_image.h 39576 2009-09-07 08:54:00Z steve.lee $
* @brief   This is the private header file for mmi_wdg_image_text_image.c
*/
#ifndef __MMI_WDG_IMAGE_TEXT_IMAGE_PRIV_H
#define __MMI_WDG_IMAGE_TEXT_IMAGE_PRIV_H

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_propcontainerbase.h"
#include "mmi_wdg_image.h"
#include "mmi_wdg_text.h"
#include "mmi_layout.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define KEEP_WIDGET_PADDING    0xFFFF

///structure for a ImageTextImage
typedef struct {
	PropContainerBase_t PCntrBase;
	IWidget * pPreImgWdg;
	IWidget * pTextWdg;
	IWidget * pPostImgWdg;
	ModelListener_t    MdlListener;
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
	u8 nLangDirection; //default is L to R	
} _ImageTextImageWdg_t;

// RELOAD flag
enum
{
	ITI_WDG_RELOAD_FLAG_START = 0,
	ITI_WDG_RELOAD_FLAG_PROP = ITI_WDG_RELOAD_FLAG_START,   ///< Prop
	ITI_WDG_RELOAD_FLAG_PREIMGSIZE,	///< PreImgSize
	ITI_WDG_RELOAD_FLAG_POSTIMGSIZE,	///< PostImgSize
	ITI_WDG_RELOAD_FLAG_PREIMGPADDING,	///< PreImgPadding
	ITI_WDG_RELOAD_FLAG_POSTIMGPADDING,	///< PostImgPadding
	ITI_WDG_RELOAD_FLAG_TEXTPADDING,	///< TextPadding
	ITI_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define ITI_WDG_RELOAD_MASK_PROP         (1<<ITI_WDG_RELOAD_FLAG_PROP)
#define ITI_WDG_RELOAD_MASK_PREIMGSIZE        (1<<ITI_WDG_RELOAD_FLAG_PREIMGSIZE)
#define ITI_WDG_RELOAD_MASK_POSTIMGSIZE         (1<<ITI_WDG_RELOAD_FLAG_POSTIMGSIZE)
#define ITI_WDG_RELOAD_MASK_PREIMGPADDING         (1<<ITI_WDG_RELOAD_FLAG_PREIMGPADDING)
#define ITI_WDG_RELOAD_MASK_POSTIMGPADDING         (1<<ITI_WDG_RELOAD_FLAG_POSTIMGPADDING)
#define ITI_WDG_RELOAD_MASK_TEXTPADDING         (1<<ITI_WDG_RELOAD_FLAG_TEXTPADDING)
/**
* Macro to get flag value
*/
#define ITI_WDG_PROP_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&ITI_WDG_RELOAD_MASK_PROP)>>ITI_WDG_RELOAD_FLAG_PROP)
#define ITI_WDG_PREIMGSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&ITI_WDG_RELOAD_MASK_PREIMGSIZE)>>ITI_WDG_RELOAD_FLAG_PREIMGSIZE)
#define ITI_WDG_POSTIMGSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&ITI_WDG_RELOAD_MASK_POSTIMGSIZE)>>ITI_WDG_RELOAD_FLAG_POSTIMGSIZE)
#define ITI_WDG_PREIMGPADDING_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&ITI_WDG_RELOAD_MASK_PREIMGPADDING)>>ITI_WDG_RELOAD_FLAG_PREIMGPADDING)
#define ITI_WDG_POSTIMGPADDING_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&ITI_WDG_RELOAD_MASK_POSTIMGPADDING)>>ITI_WDG_RELOAD_FLAG_POSTIMGPADDING)
#define ITI_WDG_TEXTPADDING_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&ITI_WDG_RELOAD_MASK_TEXTPADDING)>>ITI_WDG_RELOAD_FLAG_TEXTPADDING)
/**
* Macro to Set flag value
*/
#define ITI_WDG_PROP_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~ITI_WDG_RELOAD_MASK_PROP))|(((u32)_b)<<ITI_WDG_RELOAD_FLAG_PROP)
#define ITI_WDG_PREIMGSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~ITI_WDG_RELOAD_MASK_PREIMGSIZE))|(((u32)_b)<<ITI_WDG_RELOAD_FLAG_PREIMGSIZE)
#define ITI_WDG_POSTIMGSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~ITI_WDG_RELOAD_MASK_POSTIMGSIZE))|(((u32)_b)<<ITI_WDG_RELOAD_FLAG_POSTIMGSIZE)
#define ITI_WDG_PREIMGPADDING_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~ITI_WDG_RELOAD_MASK_PREIMGPADDING))|(((u32)_b)<<ITI_WDG_RELOAD_FLAG_PREIMGPADDING)
#define ITI_WDG_POSTIMGPADDING_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~ITI_WDG_RELOAD_MASK_POSTIMGPADDING))|(((u32)_b)<<ITI_WDG_RELOAD_FLAG_POSTIMGPADDING)
#define ITI_WDG_TEXTPADDING_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~ITI_WDG_RELOAD_MASK_TEXTPADDING))|(((u32)_b)<<ITI_WDG_RELOAD_FLAG_TEXTPADDING)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret ImageTextImageWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean ImageTextImageWdg_DefHandleEvent(IPropContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret ImageTextImageWidget_Ctor(_ImageTextImageWdg_t* pThis, MAE_ClsId ClsID);
void ImageTextImageWidget_Dtor(_ImageTextImageWdg_t* pThis);

MAE_Ret ImageTextImageWidget_SetModel(IPropContainer *pIContainer, IModel *pIModel, IBase* pOwner);

MAE_Ret ImageTextImageWidget_Move(IPropContainer *pIContainer, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isAbove);

#endif //__MMI_WDG_IMAGE_TEXT_IMAGE_PRIV_H
/*=============================================================*/
// end of file

