/**
* @file mmi_drmagentsrv_priv.h
*
*
* Class Id: CLSID_DRMAGENTSRV
*
*
* @version $Id$
*/

#ifndef __MMI_DRMAGENTSRV_PRIV_H__
#define __MMI_DRMAGENTSRV_PRIV_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_notifier.h"
#include "mmi_drmagentsrv.h"
#include "mmi_drmagentsrv_util.h"
#include "mmi_mae_rightsdb.h"
#include "mmi_mae_clock.h"


/**
 * Application structure
 */
typedef struct MMI_DRMAGENTSRV_TAG {
    DECLARE_FUNCTBL(IDRMAGENTSRV);  // function table pointer
    u32 refCnt;                                    // reference count
//--------------------------------------------------------//
    MAE_Notifier_t* pNotifier;
    IRightsDB*     pIRightsDB;
    IClock*        pIClock;

} MMI_DRMAGENTSRV;

#endif /* __MMI_DRMAGENTSRV_PRIV_H__ */
