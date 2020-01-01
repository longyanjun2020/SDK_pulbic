#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
/**
* @file    mae_softkeyboard_highlightwidget.h
* @brief   The document describes the interface of Softkeyboard HighlightWidget
* @author  kim.chuang@mstarsemi.com
*
* @version $Id: mae_softkeyboard_highlightwidget.h 8741 2009-09-15 13:22:30Z kim.chuang $
*/
#ifndef __MMI_MAE_SOFTKEYBOARD_HIGHLIGHTWIDGET_H__
#define __MMI_MAE_SOFTKEYBOARD_HIGHLIGHTWIDGET_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define LARGECHAR_NUM 10
#define CANDIDATE_NUM 11

typedef enum
{
    SKB_HIGHLIGHT_NORMAL = 0,
	SKB_HIGHLIGHT_FUNC_MT_ABC, //same as SKB_HIGHLIGHT_NORMAL_MIDDLE, landscape =11 COLs
	SKB_HIGHLIGHT_FUNC_STROKE, //landscape =5 COLs
	SKB_HIGHLIGHT_FUNC_SYMBOL, //landscape =10 COLs
    SKB_HIGHLIGHT_DIALING, //landscape =6 COLs
	SKB_HIGHLIGHT_FORMAT, //landscape =5 COLs
    SKB_HIGHLIGHT_NUM, //landscape =6 COLs
    SKB_HIGHLIGHT_SMART_ABC_NUMBER01,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER02,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER03,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER04,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER05,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER06,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER07,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER08,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER09,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER10,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER11,
    SKB_HIGHLIGHT_SMART_ABC_NUMBER12
} Softkeyboard_HighlightStyle_t;

enum
{
    HIGHLIGHT_LEFT_CURVE = 0,
    HIGHLIGHT_RIGHT_CURVE,
    HIGHLIGHT_LEFT_BOTTOM,
    HIGHLIGHT_RIGHT_BOTTOM,
    HIGHLIGHT_LEFT_CURVE2,
    HIGHLIGHT_RIGHT_CURVE2,    
    HIGHLIGHT_LIST_MAX 
};
typedef u8 SKB_CandidateImageList_e;

typedef struct {
    MAE_WChar nChar;
    u8 SKBCodeType_e;
} SKBHighlightWidget_NotifyData_t;


/**
 * ISKBHighlightWdg Interfaces
 */

__INLINE void WdgHighlightSkbUpdate
(
 IWidget                 *pWDGHighlightSkb,
 u32		              nValue
)
{
	WdgCommonSetProperty(pWDGHighlightSkb, PROP_SKBHIGHLIGHT_WDG_UPDATE, (u32)nValue);
}

__INLINE void WdgHighlightSkbSetCandidate
(
 IWidget                 *pWDGHighlightSkb,
 u32		              nValue
)
{
	WdgCommonSetProperty(pWDGHighlightSkb, PROP_SKBHIGHLIGHT_WDG_CANDIDATE, (u32)nValue);
}

__INLINE void WdgHighlightSkbSetTextChar
(
 IWidget                 *pWDGHighlightSkb,
 u32		              nValue
)
{
	WdgCommonSetProperty(pWDGHighlightSkb, PROP_SKBHIGHLIGHT_WDG_TEXT, (u32)nValue);
}

__INLINE void WdgHighlightSkbGetHighlightStyle
(
 IWidget                 *pWDGHighlightSkb,
 u32		             *pValue
 )
{
	WdgCommonGetProperty(pWDGHighlightSkb, PROP_SKBHIGHLIGHT_WDG_STYLE, (u32*)pValue);
}

#endif /*__MAE_SOFTKEYBOARD_HIGHLIGHTWIDGET_H__ */
#endif
