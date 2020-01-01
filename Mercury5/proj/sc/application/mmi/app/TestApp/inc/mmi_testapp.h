/**
* @file mmi_helloworld.h
*
* Class Id:
*
*
* @version $Id$
*/
#ifndef __MMI_HELLOWORLD_H__
#define __MMI_HELLOWORLD_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"

MAE_Ret HelloworldStartCB(IApplet* pApplet, U32 nEvt, u32 param1, u32 param2);
MAE_Ret HelloworldKeyPressCB(IApplet* pApplet, U32 nEvt, u32 param1, u32 param2);
MAE_Ret HelloworldWndHandler(void* pWndHandle, WindowMsg_t *pWndMsg, void *pWndData, u32 nInitParam);


#endif /* __MMI_BMI_H__ */
