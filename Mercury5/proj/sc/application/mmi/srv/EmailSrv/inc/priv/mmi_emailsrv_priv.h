#ifndef __MMI_EMAILSRV_PRIV_H__
#define __MMI_EMAILSRV_PRIV_H__

#include "mmi_mae_vectormodel.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_notifier.h"

#include "mmi_common_sim.h"
#include "mmi_srv_usb.h"

#include "mmi_emailsrv.h"

#include "email_app.h"

#include "nccemail.h"
#include "ven_setting.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EMAIL_SRV_TIMER_INTERVAL    300    // milliseconds
#define EMAIL_MAX_FILENAME_LEN  265

/**
 * Application structure
 */
typedef struct MMI_EMAILSRV_TAG
{
    DECLARE_FUNCTBL(IEMAILSRV); // function table pointer
    u32 refCnt;     // reference count

    /* Add custom fields below */
    MAE_Notifier_t *pNotifier;

    MMI_EMAIL_EmailAccountInfo *pCurEmailAccountInfo; // the current email account info

    IUSBSRV *pUSBSRV;

    // the information of sending or receiving emails
    EMAILSRV_AccountStatusInfo_t sendRecvStatusInfo;

    ModelListener_t usbMdlListener;
    boolean isTerminated; // Flag for checking whether or not EmailSrv has been terminated.
} MMI_EMAILSRV;

#ifdef __cplusplus
}
#endif

#endif
