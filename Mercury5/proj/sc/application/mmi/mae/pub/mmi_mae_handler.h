/**
 * @file mmi_mae_handler.h
 *
 * This file defines the IHandler interface.
 *
 * IHandler interface is the base of IApplet and IService interfaces. It has a HandleEvent method
 * to process events sent to it. The HandleEvent method shall not be called by other components
 * in MAE directly. Events shall be sent using shell's methods and be processed under shell's
 * control.
 *
 * @version $Id: mmi_mae_handler.h 291 2009-02-27 13:08:01Z kenny.wu $
 */

#ifndef __MMI_MAE_HANDELER_H__
#define __MMI_MAE_HANDELER_H__
//
// header files
//
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"

//
// IHandler interface
//
// methods of IHandler interface
#define INHERIT_IHandler(IName) \
	INHERIT_IBase(IName); \
	boolean (*HandleEvent)(IName *pHandler, MAEEvent_t nEvt, u32 nLParam, u32 nDParam)

// define the base structure of an IHandler object
DEFINE_INTERFACE(IHandler);

//
// types and definitions
//
/**
 * Prototype of the HandleEvent function. It will be called when shell processes the event.
 */
typedef boolean (*PfnEventHandler)(IHandler *pObj, MAEEvent_t nEvt, u32 nLParam, u32 nDParam);

//
// macros to run the methods of an IHandler object
//
/**
 * IHANDLER_HandleEvent
 *
 * It handles the event passed from Shell.
 *
 * @param pHandler	Pointer to the IHandler object.
 * @param nEvt		The event to be processed.
 * @param nLParam	First 32-bit parameter of the event.
 * @param nDParam	Second 32-bit parameter of the event.
 *
 * @retval TRUE		The event is handled by the object.
 * @retval FALSE	The event is not handled by the object.
 */
#define IHANDLER_HandleEvent(pHandler, nEvt, nLParam, nDParam) \
	GET_FUNCTBL(pHandler, IHandler)->HandleEvent(pHandler, nEvt, nLParam, nDParam)

/**
 * IHANDLER_GetProperty
 *
 * It calls shell's SendEvent method to send MAE_EVT_GET_PROPERTY event to the specified object
 * to get the required property.
 *
 * It is defined as a macro and uses SH_SendEvent directly; include "mmi_mae_shell.h" also to use it.
 *
 * @param pHandler	Pointer to the IHandler object.
 * @param PropId	The property to get.
 * @param pValue	The address of the variable to store the property value.
 */
#define IHANDLER_GetProperty(pHandler, PropId, pValue) \
	SH_SendEvent(pHandler, MAE_EVT_GET_PROPERTY, (u32)(PropId), (u32)(pValue))

/**
 * IHANDLER_SetProperty
 *
 * It calls shell's SendEvent method to send MAE_EVT_SET_PPROPERTY event to the specified object
 * to set the object's property.
 *
 * It is defined as a macro and uses SH_SendEvent directly; include "mmi_mae_shell.h" also to use it.
 *
 * @param pHandler	Pointer to the IHandler object.
 * @param PropId	The property to set.
 * @param Value		The property value.
 */
#define IHANDLER_SetProperty(pHandler, PropId, Value) \
	SH_SendEvent(pHandler, MAE_EVT_SET_PROPERTY, (u32)(PropId), (u32)(Value))

#endif //__MAE_HANDELER_H__
// end of file

