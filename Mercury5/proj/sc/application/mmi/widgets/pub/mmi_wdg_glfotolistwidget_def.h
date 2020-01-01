/**
* @file 	mae_glfotolistwidgetbase.h
* @brief   
*
* @version $Id: mae_glfotolistwidgetbase.h 37664 2010-02-12 09:36:01Z Elvis.Chen $
*/

#ifndef __MMI_WDG_GLFOTOLISTWIDGETBASE_DEF_H__
#define __MMI_WDG_GLFOTOLISTWIDGETBASE_DEF_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_wdg_image_text_image.h"	// for ImageTextInfo, temporary

/*=============================================================*/
// type and define
/*=============================================================*/
#define GLFOTOLIST_LISTSIZE_UNAVAILABLE	0xFFFFFFFF

// deprecated temporary, use HistoryInfo_t


// deprecated temporary, use FocusInfo_t


enum {
	GLFOTOLIST_CHECKSTYLE_NONE,
	GLFOTOLIST_CHECKSTYLE_CHECK,
	GLFOTOLIST_CHECKSTYLE_RADIO,
	GLFOTOLIST_CHECKSTYLE_END
};
typedef u8 GlFotoListFocusInfo_e;

enum {
	GLFOTOLIST_EFFECT_NONE,
	GLFOTOLIST_EFFECT_OPENING,	//opening effect
	GLFOTOLIST_EFFECT_REACTIVE,	//re-active widget effect
	GLFOTOLIST_EFFECT_END
};
typedef u8 GlFotoListEffect_e;

typedef ImageTextInfo GlFotoListWdgData_t;

typedef struct {
	u32 nChangedIdx;		/* the absolutely index of changed item */
	s32 nOldSize;			/* the size of old datamodel (GLFOTOLIST_LISTSIZE_UNAVAILABLE means users set a new Model with the same size) */
	u32 nNewSize;			/* the size of new datamodel, zero based */
} GlFotoListDataChangedEvt_t;
/*=============================================================*/
// functions
/*=============================================================*/

#endif // __MAE_GLFOTOLISTWIDGETBASE_DEF_H__
