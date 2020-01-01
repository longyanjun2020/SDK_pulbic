////////////////////////////////////////////////////////////////////////////////

/**
* @file    MML_Tv.h
* @version
* @brief
*
*/

#ifndef __MML_TV_H__
#define __MML_TV_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup MMLayerTv TV
    Analog TV, Digital TV
    @{
*/
    /** @defgroup MMLayerAnalogTv Analog TV
        Analog TV
        @{
    */
    /** @} */

    /** @defgroup MMLayerDigitalTv Digital TV
        Digital TV
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
#include "srv_resmgr_mmltv_types.h" // Lib release stage1's workaround

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
MmlErrCode_e MmlTvNotifyCallbackDispatch
(
    MmlMultimediaGroup_t            *pGroup,
    u32                             nEvent,
    void                            *pNotifyPayload
);

#ifdef __cplusplus
}
#endif

#endif //__MML_TV_H__
