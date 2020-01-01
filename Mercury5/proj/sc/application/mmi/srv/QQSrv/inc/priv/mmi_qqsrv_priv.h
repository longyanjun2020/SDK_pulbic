#ifndef __MMI_QQSRV_PRIV_H__
#define __MMI_QQSRV_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_notifier.h"
#include "mmi_base_util.h"


#include "mmi_qqsrv.h"
#include "mmi_audiosrv.h"
#include "mmi_accessorysrv.h"
#include "mmi_usbsrv.h"

#include "Srv_filemgr_fstream.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VIBRATE_TIME 2000

/**
 * Application structure
 */

typedef struct MMI_QQSRV_TAG
{
    DECLARE_FUNCTBL(IQQSRV); // function table pointer
    u32 refCnt;     // reference count

    IAUDIOSRV               *pAudioSrv;
    IACCESSORYSRV           *pIAccessorySrv;
    IUSBSRV                 *pUSBSrv;
    ModelListener_t         AccessoryMdlListener;
    ModelListener_t         UsbMdlListener;

    /* Add custom fields below */
    MAE_Notifier_t          *pNotifier;

    QQSrvQQConfig_t         *pQQConfig;
    VectorClass_t           *pQQClientVector; // QQSrvQQClient_t

    /*for history message read begin*/
    u8                      *pChatHistoryBuf;
    FileMgr_Stream_t        *pStream;
    u32                     size;
    u32                     nCurSize;
    VectorClass_t           *pMsgVector;
    /*for history message read end*/

	u32                     activeAccountID;
    QQSrvStatus_e           status;
    QQSrvErrCode_e          errCode;
    boolean                 bHasSDCard;
    boolean                 isTerminated; // Flag for checking whether or not QQSrv has been terminated.
} MMI_QQSRV;

#ifdef __cplusplus
}
#endif

#endif
