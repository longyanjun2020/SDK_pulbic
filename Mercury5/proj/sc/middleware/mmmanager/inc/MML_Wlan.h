// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    MML_Wlan.h
* @version
* @brief
*
*/

#ifndef __MML_WLAN_H__
#define __MML_WLAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup MMLayerWlan WLAN
    WiFi
    @{
*/
    /** @defgroup MMLayerWiFi WiFi
        WiFi
        @{
    */
    /** @} */

/** @} */

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlwlan_types.h" // Lib release stage1's workaround

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
MmlWlanResult_e MmlAkmCertParsar(MmlWlanCertScoure_t *pMmlWlanCertScoure, MmlAKMCertInfo_t *pMmlAKMCertInfo);
void MmlAkmCertFree(MmlAKMCertInfo_t *pMmlAKMCertInfo);


MmlErrCode_e MmlWlanNotifyCallbackDispatch
(
    MmlMultimediaGroup_t            *pGroup,
    u32                             nEvent,
    void                            *pNotifyPayload
);

#ifdef __cplusplus
}
#endif

#endif //__MML_WLAN_H__
