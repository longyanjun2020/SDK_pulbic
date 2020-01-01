#ifndef __MMI_MAE_CONTAINERBASE_TYPE_H__
#define __MMI_MAE_CONTAINERBASE_TYPE_H__

#include "mmi_mae_widgetbase_type.h" //for WidgetBaseEx_t
#include "mmi_mae_widgetcell_type.h" //for WidgetCell_t

/* 
* This is Base structure for all containers.
*/
typedef struct ContainerBase_Tag ContainerBase_t;

//This is function prototype for each kind of container to make a widget cell for himself
typedef MAE_Ret (*CELL_MADE_FUNC_PTR) (IWidget*, const void*, WidgetCell_t**);

//This is a layout function prototype for each kind of container
typedef void (*LAYOUT_FUNC_PTR) (ContainerBase_t*, WidgetCell_t*, Rect_t*);

//base structure for all container
struct ContainerBase_Tag {
	WidgetBaseEx_t      WdgBase;			///< Use WidgetBaseEx_t as base structure, border inside.

	//Here keeps the widgets stay in this container.
	WidgetCell_t      WidgetStackRoot;      /*!< A root of double link list which is used to keep all widgets in this container
											the widget after WidgetStackRoot is the topmost widget; 
											the widget before WidgetStackRoot is the bottom most widget. */
	WidgetCell_t      *WdgCellFocusedPtr;   ///< A pointer of WidgetCell_t to keep which widget is the focused widget.
	CELL_MADE_FUNC_PTR  CellMdFuncPtr;      ///< A function to make a new widget cell, every kind of container should own their widget cell made function
	LAYOUT_FUNC_PTR     LayoutFuncPtr;      ///< A function to do layout, every kind of container should have their layout function for themself
    boolean bChildActionOnFocus;
	//Flags for container
	/*u32             nCntrBaseFlags;*/         /*!< bit 1, indicate this container is focused or not.
												bit 2, enable do layout or disable do layout.
												bit 3, indicate this container is doing layout or not.
												bit 4, broadcast flag */
};

#endif // __MMI_MAE_CONTAINERBASE_TYPE_H__
