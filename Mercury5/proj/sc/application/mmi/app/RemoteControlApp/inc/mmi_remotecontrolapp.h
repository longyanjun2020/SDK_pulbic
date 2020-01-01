/**
* @file mmi_remotecontrolapp.h
*
*
* @version $Id: mmi_remotecontrolapp.h  
*/
#ifndef __MMI_REMOTECONTROLAPP_H__
#define __MMI_REMOTECONTROLAPP_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_applet.h"
#include "mmi_base_util.h"

//#define ANTISTEAL_MAXPASSWORDLENGTH (8)
//#define ANTISTEAL_MINPASSWORDLENGTH (4)
//#define ANTISTEAL_DIALOG_SCREEN_TIMER (1000)
//#define ANTISTEAL_MAXNOTIFYCONTENTLENGTH (20)
#define REMOTECONTROL_MAXNOTIFYNUMBERLENGTH (40)

/*-------------------------------------------------------------------------*/

MAE_Ret RemoteControlAppNew(MAE_ClsId nClsId, void **ppObj);
#endif /* __MMI_REMOTECONTROLAPP_H__ */
