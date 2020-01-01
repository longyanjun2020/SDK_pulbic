/**
* @file mmi_mae_widgethandler.h
*
* This file defines the handler structure and related macros used in widget objects.
*
* @version $Id: mmi_mae_widgethandler.h 8741 2008-04-08 13:22:30Z paul.ouyang $
*/

#ifndef	__MMI_MAE_WIDGETHANDELER_H__
#define __MMI_MAE_WIDGETHANDELER_H__

/*=============================================================*/
// header files
/*=============================================================*/
#include "mmi_mae_common_def.h"

/*=============================================================*/
// types and macros
/*=============================================================*/
/// defines the function prototype for the event handler of widget objects
typedef boolean (*WHANDLER_HDL_FUNC_PTR) (void *, MAEEvent_t, u32, u32);
/// defines the function prototype to free the context data used in widgets' event handling
typedef void (*WHANDLER_FREE_FUNC_PTR) (void *);

typedef struct
{
	void *pData; ///< pointer to the context data which will be passed into handler function and free function.
	WHANDLER_HDL_FUNC_PTR pfHandle; ///< the handler function which will be called in WHANDLER_CALL().
	WHANDLER_FREE_FUNC_PTR pfFree;	///< the free function which will be called in WHANDLER_FREE().
} WidgetHandler_t;

/**
* WHANDLER_INIT
* @brief	This macro initializes a structure of the WidgetHandler_t.
*
* @param	pHdlData	A pointer of WidgetHandler_t sturcture.
* @param	HdlFuncPtr	A function pointer of handle event function.
* @param	DataPtr		A pointer to private context data.
* @param	FreeFuncPtr	A function pointer for free context data.
*
* @retval	None
*/
#define WHANDLER_INIT(pHdlData, HdlFuncPtr, DataPtr, FreeFuncPtr) \
	(pHdlData)->pfHandle = (WHANDLER_HDL_FUNC_PTR)(HdlFuncPtr), \
	(pHdlData)->pData = (void*)(DataPtr), \
	(pHdlData)->pfFree = (WHANDLER_FREE_FUNC_PTR)(FreeFuncPtr)

/**
* WHANDLER_CALL
* @brief	This macro passes the event to handler function which is kept in WidgetHandler_t sturcture.
*
* @param	pHdlData	A pointer of WidgetHandler_t sturcture which keeps handler function to handle events.
* @param	evt			Event Id.
* @param	p1			Parameter 1 of 32-bits specific data.
* @param	p2			Parameter 2 of 32-bits specific data.
*
* @retval	TRUE		This event was handled.
* @retval	FALSE		This event was NOT handled.
*/
#define WHANDLER_CALL(pHdlData,evt,p1,p2) \
	(((pHdlData)->pfHandle)? (pHdlData)->pfHandle((pHdlData)->pData, (evt), (p1), (p2)): FALSE)

/**
* WHANDLER_FREE
* @brief	This macro frees the data by calling free function which is kept in HanlderData_t structure.
*
* @param	pHdlData	A pointer of WidgetHandler_t sturcture which keeps the context data pointer
*						and its free function.
*
* @retval	None
*/
#define WHANDLER_FREE(pHdlData) \
{if ((pHdlData)->pfFree) (pHdlData)->pfFree((pHdlData)->pData);}


#endif //__MAE_WIDGETHANDELER_H__
// end of file
