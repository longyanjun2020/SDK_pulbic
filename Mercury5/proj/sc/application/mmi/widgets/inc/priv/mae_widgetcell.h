/**
* @file    mae_widgetcell.h
* @brief   This file is the collection of widget property definitions.
* 
* @version $Id: mae_widgetcell.h 26654 2009-03-25 11:43:00Z steve.lee $
*/
#ifndef __MAE_WIDGETCELL_H__
#define __MAE_WIDGETCELL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_widgetcell_type.h"

/*=============================================================*/
// type and define
/*=============================================================*/



//cell initialize
#define WIDGETCELL_INIT(p)      (p)->WidgetPtr = NULL, \
	(p)->Before = (p), \
	(p)->After = (p)

//add p(widget cell) before cr(widget cell),
//then, the p would be on the top of cr
#define WIDGETCELL_ADD_ABOVE(p, cr)    (p)->Before = (cr)->Before, \
	(p)->After = (cr), \
	(cr)->Before->After = (p), \
	(cr)->Before = (p)

//add p(widget cell) after cr(widget cell)
//then, the p would be on the bottom of cr
#define WIDGETCELL_ADD_BELOW(p, cr)     (p)->After = (cr)->After, \
	(p)->Before = (cr), \
	(cr)->After->Before = (p), \
	(cr)->After = (p)

#define MOSTTOP_WIDGET_CELL(RootPtr)   ((RootPtr)->After)
#define MOSTBOTTOM_WIDGET_CELL(RootPtr)    ((RootPtr)->Before)

#define UPPER_WIDGET_CELL(p)        ((p)->Before)
#define LOWER_WIDGET_CELL(p)        ((p)->After)

#define WIDGETCELL_REMOVE(p)        (p)->After->Before = (p)->Before, \
	(p)->Before->After = (p)->After , \
	(p)->After = (p), \
	(p)->Before = (p)
/*=============================================================*/
// functions
/*=============================================================*/
MAE_Ret WidgetCell_New(WidgetCell_t **ppObj);

void WidgetCell_Delete(WidgetCell_t *pRoot, WidgetCell_t *pDeleteCell);

void WidgetCell_Ctor(WidgetCell_t *pThis, IWidget *piWidget, Rect_t *prc, boolean isVisible);

void WidgetCell_Dtor(WidgetCell_t *pThis);

MAE_Ret WidgetCell_FindByWidget(WidgetCell_t *pRoot, IWidget *pWidget, WidgetCell_t **ppo);

IWidget *WidgetCell_GetWidget(WidgetCell_t *pRoot, IWidget *piRefWidget, boolean isUpper, boolean isWrap);

boolean WidgetCell_IntersectOpaque(WidgetCell_t *pThis, const Rect_t *pInRect, Rect_t *pOutRect);

boolean WidgetCell_IsFullOpaque(WidgetCell_t *pThis, Rect_t *pInRect);

boolean WidgetCell_CanBeFocused(WidgetCell_t *pThis);




#endif //__MAE_WIDGETCELL_H__
/*=============================================================*/
// end of file
