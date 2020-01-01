/**
* @file mmi_coresrv_priv.h
*
* Service without using State Machine - DIALOGSRV
*
* Class Id: CLSID_DIALOGSRV
* Interface Id: IID_DIALOGSRV
*
* @version $Id$
*/
#ifndef __MMI_DIALOGSRV_PRIV_H__
#define __MMI_DIALOGSRV_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_notifier.h"
#include "mmi_dialogsrv.h"
#include "mmi_dialogapp.h"

/**
 * Application structure
 */
typedef struct MMI_DIALOGSRV_TAG
{
    DECLARE_FUNCTBL(IDIALOGSRV);    // function table pointer
    u32 refCnt;     // reference count

    /* Add custom fields below */
    MAE_Notifier_t *pNotifier;
    boolean bTerminated; 
} MMI_DIALOGSRV;

typedef struct
{
    MMI_DIALOGSRV *pThis;
    DialogApp_DialogInfo_t *pDialogInfo;
}DialogSrv_DialogStratCB_Data_t;

/*The data structure used internally to pass to handler*/
typedef struct
{
    boolean bIsTopDialog;
    DialogSrvDialogSetting_t tDialogSetting;
    DialogSrvDialogCallback_t tDialogCB;
    boolean bIsDefault;
}DialogSrvDialogData_t;





#endif /* __MMI_CORESRV_PRIV_H__ */
