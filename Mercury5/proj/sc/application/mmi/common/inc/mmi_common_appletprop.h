/**
* @file    mmi_common_appletprop.h
* @brief   This file is the collection of applet property definitions.
* 
* @version $Id: mmi_common_appletprop.h 35359 2009-07-08 07:50:24Z william.lien $
*/
#ifndef __MMI_COMMON_APPLETPROP_H__
#define __MMI_COMMON_APPLETPROP_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_applet_types.h"

/*=============================================================*/
// type and define
/*=============================================================*/

// common applet properties
typedef enum AppTransitionProp_e_
{
	PROP_APPLET_ENTRY_TRANSITION_ID = MMI_PROP_BASE,
	PROP_APPLET_EXIT_TRANSITION_ID,
	PROP_APPLET_ORIENTATION_ID
}AppTransitionProp_e;


#endif //__MMI_COMMON_APPLETPROP_H__
/*=============================================================*/
// end of file
