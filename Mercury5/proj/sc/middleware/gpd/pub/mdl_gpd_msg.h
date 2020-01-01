////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
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
* @file    mdl_gpd_msg.h
* @version
* @brief   MDL header file of GPD; message data type
*
*/

#ifndef __MDL_GPD_MSG_H__
#define __MDL_GPD_MSG_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "mdl_gpd_pub.h"
#include "sys_rtk_vmoshi.h"
//#include "mdl_aud_types.h"
//#include "vm_audio_api.h"

//#include "cus_msg.hc"
#include "drv_abb_pub.h"
#include "mdl_stg2gpd.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#define  vm_msg_t  vm_msg_t

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "mdl_gpd_message_define__.hi"
};

#define GPD_SYNC_BLOCK      MsConsumeSem(GPD_SYNC_SEM)
#define GPD_SYNC_UNBLOCK    MsProduceSem(GPD_SYNC_SEM)

#define GPD_REENTRY_LOCK    MsConsumeSem(GPD_REENTRY_LOCK_SEM)
#define GPD_REENTRY_UNLOCK  MsProduceSem(GPD_REENTRY_LOCK_SEM)


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief This enumeration defines the synchronous/asynchronous primtive mechanism
 */
typedef enum
{
    GPD_SYNC,         /**< Synchronous transaction */
    GPD_ASYNC         /**< Asynchronous transaction */
} gps_TransType_t;


/**
 *  @brief This structure defines the message container
 */
typedef struct
{
    MdlGpdCb_t       *ptGpdCb;                 /**< Callback structure */
    gps_TransType_t   TransType;               /**< Transaction type */
    MdlGpdErrCode_e  *pErrCode;                /**< Error code pointer */

    union
    {
        struct
        {
            MdlGpdOp_e           eOperation;
            MdlGpdDuration_t    *ptDurSetting;
        } VibratorSwitch;

        struct
        {
            u8                   nLevel;
        } VibratorSetLevel;

        struct
        {
            MdlGpdLedId_e        eLedId;
            MdlGpdOp_e           eOperation;
            MdlGpdDuration_t    *ptDurSetting;
        } LedSwitch;

        struct
        {
            MdlGpdBlId_e         eBlId;
            u8                   nRange;
            u8                   nLevel;
            MdlGpdDuration_t    *ptDurSetting;
        } BacklightSwitch;

        struct
        {
            MdlGpdBlId_e         eBlId;
            u8                   nRange;
            u8                   nLevel_1;
            u8                   nLevel_2;
            MdlGpdDuration_t    *ptDurSetting;
        } BacklightFlash;

        struct
        {
            MdlGpdBlId_e         eBlId;
        } BacklightRestore;

        struct
        {
            MdlGpdGsensorOp_e    eOperation;
            u32                  nPollingTime;
        } GsensorSwitch;

        struct
        {
            MdlGpdAcsType_e      eAcsType;
            MdlGpdAcsStatus_e   *peAcsStatus;
        } GetAcsStatus;

        struct
        {
            MdlGpdAcsType_e      eAcsType;
            MdlGpdAcsNotifyCb_t  tNotifyCb;
        } RegAcsNotify;

        struct
        {
            MdlGsensorNotifyCb_t tNotifyCb;
        } RegGsensorNotify;

        struct
        {
            MdlGpdPwrOnCause_e  *pePwrOnCause;
        } PowerOnCause;

        struct
        {
            MdlGpdVerType_e       eVerType;
            char                 *pVersion;
        } GetVersion;

        struct
        {
            MdlGpdAcsType_e      eAcsType;
            MdlGpdAcsStatus_e    eAcsStatus;
        } AcsIndication;

        struct
        {
            MdlGpdDevice_e       eDevice;
            bool                 bOnOff;
        } DeviceConfig;

        struct
        {
            MdlGpdDevPowerType_e  eDevPowerType;
            MdlGpdOp_e            eOperation;
        } DeivcePowerSwitch;

#ifdef __FLASHLIGHT_DRV__
        struct
        {
            MdlGpdOp_e           eOperation;
        } FlashlightSwitch;
#endif

#ifdef __FILLLIGHT_DRV__
        struct
        {
            MdlGpdOp_e           eOperation;
        } FilllightSwitch;
#endif

#ifdef __UPGRADE_NVRAM__
        struct
        {
            MdlGpdNvramType_e           eNvramType;
            u8	 *pAddr;
            u32	 nLen;
        } NvramUpdate;
#ifdef __UPGRADE_NVRAM_ENHANCED__
        struct
        {
            MdlGpdNvramType_e   eNvramType;
            u8	                *pAddr;
            u16	                nLen;
        } NvramRestore;
        struct
        {
            MdlGpdNvramType_e   eNvramType;
            MdlGpdNvramCause_e  causeValue;
            u8                 	*pAddr;
            u16                 nLen;
            u8                 	*pUpdateAddr;
            u16                 nUpdateLen;
        } NvramRestoreCmp;
        #ifdef __UPGRADE_NVRAM_ENHANCED_TEST_ONLY__
        struct
        {
            MdlGpdNvramITContent_t   *tNvramITContent;
        } NvramITModify;
        #endif //__UPGRADE_NVRAM_ENHANCED_TEST_ONLY__
#endif  // __UPGRADE_NVRAM_ENHANCED__
#endif  // __UPGRADE_NVRAM__

#ifdef __BREATHLIGHT_DRV__
        struct {
            MdlGpdDevType_e    DevType;
            MdlGpdOp_e         Operation;
            u16                Cycle;
            MdlGpdLedPattern_t *Pattern;
        } DevPatternSwitch;
#endif

#ifdef __PROXIMITY_SENSOR_DRV__
        struct
        {
            MdlProximitySensorNotifyCb_t tNotifyCb;
        } ProximitySensorRegNotify;

        struct
        {
            MdlProximitySensorOp_e       eOperation;
            u32                          nPollingTime;
        } ProximitySensorSwitch;

        struct
        {
            u32                          nValue;
        } ProximitySensorADC;

	struct
        {
            u16   eOperation;
            u16   nGetData;
        } PaiSensorInd;
#endif

        struct
        {
            u32	 Port;
        } InfoLcdReq;

        struct
        {
            MdlGpdSysDbgType_e    Type;
			union {
				MdlGpdSysStkUsgInfo_t* pStkInfo;
			} Info;
        } SysDbgInfo;
    } param;

} gpd_Cmd_t;


/**
 *  @brief This structure defines the message body
 */
typedef union
{
    gpd_Cmd_t                 GpdCmd;        /**< GPD command container */
    vm_osTimerMsgBody_t       GpdTimerId;    /**< GPD Timer Id */
    //vm_AudioManagerMsgType_e  AudioMsgType;  /**< Audio message type */
    MdlStgMsgBody_t           tStgMsgBody;
    DrvAbbMsgCode_e           eAbbMsgCode;
} vm_msgBody_t;

#include "vm_msgt.ht"


void MdlGpdTriggerMemCardChange(void);

#endif /* __MDL_GPD_MSG_H__ */
