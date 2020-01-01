#ifndef __MMI_MAE_WIDGETCELL_TYPE_H__
#define __MMI_MAE_WIDGETCELL_TYPE_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_widget.h" //for IWidget
#include "mmi_mae_graphic_forward.h" //for Rect_t

//structure for a widget cell
typedef struct WidgetCell_Tag {
	IWidget                 *WidgetPtr;     //pointer to a widget
	Rect_t                  WidgetRect;     //a rectangle for pointed widget
	u32                     Visible : 1;         ///< is visible or not
	u32                     Draw : 1 ;           ///< does this widget need draw or not
	u32                     bIsLifting : 1 ;     ///< is a lifting widget.
	u32                     bWasFocused : 1 ;     ///< was focused before lifting widget added.
	struct WidgetCell_Tag   *Before;        //before widget(the more top widget)
	struct WidgetCell_Tag   *After;         //after widget(the more bottom widget)
} WidgetCell_t;

#endif // __MMI_MAE_WIDGETCELL_TYPE_H__
