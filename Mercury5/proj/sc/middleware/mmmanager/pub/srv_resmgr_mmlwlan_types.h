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
* @file    srv_resmgr_mmlwlan_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLWLAN_TYPES_H__
#define __SRV_RESMGR_MMLWLAN_TYPES_H__

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
#include "srv_resmgr_mmlcommon_types.h"
#include "esl_wifi_itf.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerWlan
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseWlanId_e_)
{
    /* Wlan Init */
    MML_UCID_WLAN_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_WLAN),
    MML_UCID_WLAN_REG_NOTIFY_CALLBACK = MML_UCID_WLAN_INIT_BASE,            ///< 000B0000 = Reg notify callback
    MML_UCID_WLAN_UNREG_NOTIFY_CALLBACK,                                    ///< 000B0001 = Unreg notify callback
    MML_UCID_WLAN_OPEN,                                                     ///< 000B0002 = Open
    MML_UCID_WLAN_CLOSE,                                                    ///< 000B0003 = Close
    MML_UCID_WLAN_INIT_FIFO,                                                ///< 000B0004 = InitFIFO
    MML_UCID_WLAN_DELETE_FIFO,                                              ///< 000B0005 = DelFIFO
    MML_UCID_WLAN_INIT_CATEGORY,

    /* Wlan Get */
    MML_UCID_WLAN_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_WLAN),
    MML_UCID_WLAN_GET_CONFIGURATION = MML_UCID_WLAN_GET_BASE,               ///< 000B0100 = Get configuration
    MML_UCID_WLAN_GET_SCAN_RESULT,                                          ///< 000B0101 = Get scan result
    MML_UCID_WLAN_GET_BSS,                                                  ///< 000B0102 = Get BSS
    MML_UCID_WLAN_GET_FW_TEST_RESULT,                                       ///< 000B0103 = Get FW Test Result( for EM mode )
    MML_UCID_WLAN_GET_HW_REG,                                               ///< 000B0104 = Get HW Register( for EM mode )
    MML_UCID_WLAN_GET_RX_FILTER_RESULT,                                     ///< 000B0105 = Get Rx Filter Result( for EM mode )
    MML_UCID_WLAN_GET_AQU_VER,                                              ///< 000B0106 = Get GET_AQU_VER
    MML_UCID_WLAN_GET_RF_REG,                                               ///< 000B0107 = Get RF Register ( for EM mode )
    MML_UCID_WLAN_GET_AQU_MEM,                                              ///< 000B0108 = Get AQU memory ( for EM mode )
    MML_UCID_WLAN_GET_CATEGORY,
    
    /* Wlan Set */
    MML_UCID_WLAN_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_WLAN),
    MML_UCID_WLAN_SET_CONFIGURATION = MML_UCID_WLAN_SET_BASE,               ///< 000B0200 = Set configuration
    MML_UCID_WLAN_POWER_SAVING,                                             ///< 000B0201 = Set power saving
    MML_UCID_WLAN_BLUETOOTH_STATUS,                                         ///< 000B0202 = Set bluetooth status
    MML_UCID_WLAN_SET_FW_TEST,                                              ///< 000B0203 = Set FW Test ( for EM mode )
    MML_UCID_WLAN_SET_HW_REG,                                               ///< 000B0204 = Set HW Register ( for EM mode )
    MML_UCID_WLAN_SET_RX_FILTER,                                            ///< 000B0205 = Set Rx Filter ( for EM mode )
    MML_UCID_WLAN_SET_GSM_STATUS,                                           ///< 000B0206 = Set GSM STATUS
    MML_UCID_WLAN_SET_RF_REG,                                               ///< 000B0207 = Set RF Register ( for EM mode )
    MML_UCID_WLAN_SET_TX_SIN_TONE,                                          ///< 000B0208 = Set Tx Sin Tone ( for EM mode )
    MML_UCID_WLAN_SET_AQU_MEM,                                              ///< 000B0209 = Set AQU memory ( for EM mode )
    MML_UCID_WLAN_SET_CATEGORY,
    
    /* Wlan Execute */
    MML_UCID_WLAN_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_WLAN),
    MML_UCID_WLAN_SCAN_NETWORK = MML_UCID_WLAN_EXECUTE_BASE,                ///< 000B0300 = Scan network
    MML_UCID_WLAN_STOP_SCAN,                                                ///< 000B0301 = Stop scan
    MML_UCID_WLAN_CONNECT_NETWORK,                                          ///< 000B0302 = Connect network
    MML_UCID_WLAN_DISCONNECT_NETWORK,                                       ///< 000B0303 = Disconnect network
    MML_UCID_WLAN_RESET,                                                    ///< 000B0304 = Reset
    MML_UCID_WLAN_STOP_CONT_TX,                                             ///< 000B0305 = Stop Continuous TX ( for EM mode )
    MML_UCID_WLAN_EXECUTE_CATEGORY,
    
    /* Force ID to be at least 32-bits */
    MML_UCID_WLAN_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerWlan
    @brief      Response results
*/
typedef enum
{
    /* Common */
    WLAN_ERROR_SUCCESS = 0,
    WLAN_ERROR_FAIL,
    WLAN_ERROR_PARAMETER_INVALID,
    WLAN_ERROR_STATE_CHANGE,
    WLAN_ERROR_ACCEPT,
    WLAN_ERROR_IGNORE,
    WLAN_ERROR_REJECT,
    WLAN_ERROR_MEM_ALLOC,
    /* */
    WLAN_ERROR_NUM
} MmlWlanResult_e;

/** @ingroup    MMLayerWlan
    @brief      States
*/
typedef enum
{
    /* WiFi */
    WLAN_STATE_CLOSED = 0,
    WLAN_STATE_OPENED,
    WLAN_STATE_CONNECTED,
    /* */
    WLAN_STATE_DONTCARE,
    WLAN_STATE_NUM
} MmlWlanState_e;

/** @ingroup    MMLayerWlan
    @brief      Events
*/
typedef enum
{
    /* Common */
    WLAN_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_WLAN),
    WLAN_EVENT_RUNTIME_ERROR,
    /* WiFi */
    WLAN_EVENT_ON,
    WLAN_EVENT_OFF,
    WLAN_EVENT_SCAN_NETWORK_COMPLETE,
    WLAN_EVENT_CONNECTED,
    WLAN_EVENT_CONNECTION_FAILED,
    WLAN_EVENT_DISCONNECTED,
    WLAN_EVENT_ROMMING,
    WLAN_EVENT_FW_TEST_DONE,
    WLAN_EVENT_CERT_FAIL,
    WLAN_EVENT_CERT_UNKNOWN_ISSUER,
    WLAN_EVENT_CERT_UNTRUSTED_ROOT,
    WLAN_EVENT_CERT_INVALID_TIME,
    WLAN_EVENT_CERT_INVALID_SIGNATURE,
    WLAN_EVENT_CERT_REVOKED,
    WLAN_EVENT_CERT_INVALID_USAGE,
    WLAN_EVENT_CERT_FAIL_UNKNOW,

    /* */
    WLAN_EVENT_DONTCARE,
    WLAN_EVENT_ALL,
    WLAN_EVENT_NUM
} MmlWlanEvent_e;

typedef enum
{
    WLAN_OPENMODE_OFF = 0,
    WLAN_OPENMODE_NORMAL,
    WLAN_OPENMODE_ENGINEERING,
    WLAN_OPENMODE_NUM
} MmlWlanOpenMode_e;

/** @ingroup    MMLayerWlan
    @brief      WPA command response data (ESL legacy)
*/
typedef     esl_WifiEvent_t                 MmlWlanWpaCommandResponse_t;

/** @ingroup    MMLayerWlan
    @brief      Configuration (ESL legacy)
*/
typedef     MmlWlanWpaCommandResponse_t     MmlWlanConfiguration_t;

/** @ingroup    MMLayerWlan
    @brief      Scan network result
*/
typedef     MmlWlanWpaCommandResponse_t     MmlWlanScanResult_t;

/** @ingroup    MMLayerWlan
    @brief      BSS
*/
typedef     MmlWlanWpaCommandResponse_t     MmlWlanBss_t;

/** @ingroup    MMLayerWlan
    @brief      AQUVer
*/
typedef     MmlWlanWpaCommandResponse_t     MmlWlanAQUVer_t;

/** @ingroup    MMLayerWlan
    @brief      Fw Test Result
*/
typedef     MmlWlanWpaCommandResponse_t     MmlWlanFwTestResult_t;

/** @ingroup    MMLayerWlan
    @brief      HW Reg
*/
typedef     MmlWlanWpaCommandResponse_t     MmlWlanHwReg_t;

/** @ingroup    MMLayerWlan
    @brief      Rx Filter
*/
typedef     MmlWlanWpaCommandResponse_t     MmlWlanRxFilter_t;

/** @ingroup    MMLayerWlan
    @brief      Rf Reg
*/
typedef     MmlWlanWpaCommandResponse_t     MmlWlanRfReg_t;

/** @ingroup    MMLayerWlan
    @brief      Rf Reg
*/
typedef     MmlWlanWpaCommandResponse_t     MmlWlanAQUMem_t;



/** @ingroup    MMLayerWlan
    @brief      Cert input type
*/
typedef enum
{
    CERT_STORE_IN_FILE = 0,
    CERT_STORE_IN_RAI,
} MmlWlanCertSourceType_e;

/** @ingroup    MMLayerWlan
    @brief      x509 Name
*/
typedef	struct{
	S8  *cn;             /* commonName */
	S8  *c;              /* countryName */
	S8  *l;              /* localityName */
	S8  *st;             /* stateOrProvinceName */
	S8  *o;              /* organizationName */
	S8  *ou;             /* organizationalUnitName */
	S8  *email;          /* emailAddress */
}MmlWlanX509Name_t;

#define CERT_TIME_Z_LEN 15          //GeneralizedTime: YYYYMMDDHHMMSSZ

typedef struct
{
    u16 *wszFilePath;
    u16 nLen;
}MmlWlanCertSourceFile_t;

typedef struct
{
    u32 nRaiId;
    u32 nSize;
}MmlWlanCertSourceRai_t;

typedef struct
{
    MmlWlanCertSourceType_e     type;
    union
    {
        MmlWlanCertSourceFile_t tSourceFile;
        MmlWlanCertSourceRai_t tSourceRai;
    }MmlWlanCertSource_u;
}MmlWlanCertScoure_t;


/** @ingroup    MMLayerWlan
    @brief      akm_cert_info
*/
typedef	struct
{
    U32                     status;
    MmlWlanX509Name_t       issuer;
    MmlWlanX509Name_t       subject;
    U32                     serial_number;
    U8                      not_before[CERT_TIME_Z_LEN];
    U8                      not_after[CERT_TIME_Z_LEN];
}MmlAKMCertInfo_t;

typedef	struct
{
    MmlWlanCertScoure_t     tCertSource;
}MmlWlanGetCertInfo_t;

/**
    @brief      State change info
*/
typedef	struct
{
    MmlWlanState_e    eState;    ///< The new state after the transition
    MmlWlanEvent_e    eCause;    ///< The cause of state change, if any
} MmlWlanStateChange_t;

/** @ingroup    MMLayerWlan
    @brief      Notification payload
*/
typedef struct
{
    MmlWlanEvent_e            eEvent;    ///< Specify the event you want to notify

    /// union of MmlWlanNotify_t parameters
    union
    {
        MmlWlanStateChange_t              tStateChange;    ///< Used with WLAN_EVENT_STATE_CHANGE event
        MmlWlanResult_e                   eErrCode;        ///< Used with WLAN_EVENT_RUNTIME_ERROR event
	} uParam;
} MmlWlanNotify_t;

/** @ingroup    MMLayerWlan
    @brief      Notification callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      pWlanNotify       Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlWlanNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlWlanNotify_t *pWlanNotify);

/** @ingroup    MMLayerWlan
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                             nSenderID;            ///< Sender's mailbox ID
    u32                             nUserValue;           ///< Interface self-reference
    PfnMmlWlanNotifyCallback        pfnNotifyCallback;    ///< Callback function your want to register
} MmlWlanNotifyCallback_t;

/** @ingroup    MMLayerWlan
    @brief      Response callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      eErrCode          Returned result (error code)
    @param      pWlanResponse     Pointer to the returned response payload
*/
struct MmlWlanResponse_t_;
typedef void (*PfnMmlWlanResponseCallback)(u16 nSenderID, u32 nUserValue, MmlWlanResult_e eErrCode, struct MmlWlanResponse_t_ *pWlanResponse);

/** @ingroup    MMLayerWlan
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                             nSenderID;              ///< Sender's mailbox ID
    u32                             nUserValue;             ///< Interface self-reference
    PfnMmlWlanResponseCallback      pfnResponseCallback;    ///< Callback function your want to register
} MmlWlanResponseCallback_t;

/** @ingroup    MMLayerWlan
    @brief      Register notification callback
*/
typedef struct
{
    MmlWlanEvent_e                 eEvent;            ///< Specify which event you want to handle
    MmlWlanNotifyCallback_t        tNotifyCallback;   ///< Callback function you want to register
} MmlWlanRegNotifyCallback_t;

typedef struct
{
    MmlWlanOpenMode_e               eOpenMode;        ///< Specify which mode of wlan open
} MmlWlanOpen_t;


/** @ingroup    MMLayerWlan
    @brief      Get configuration
*/
typedef     esl_WifiEvent_t             MmlWlanGetConfiguration_t;

/** @ingroup    MMLayerWlan
    @brief      Get scan result
*/
typedef     esl_WifiEvent_t             MmlWlanGetScanResult_t;

/** @ingroup    MMLayerWlan
    @brief      Get BSS
*/
typedef     esl_WifiEvent_t             MmlWlanGetBSS_t;

/** @ingroup    MMLayerWlan
    @brief      Get AQU VER
*/
typedef     esl_WifiEvent_t             MmlWlanGetAQUVer_t;

/** @ingroup    MMLayerWlan
    @brief      Set GAM Status
*/
typedef     esl_WifiSetGSMStatus_t      MmlWlanSetGSMStatus_t;

/** @ingroup    MMLayerWlan
    @brief      Set configuration (ESL legacy)
*/
typedef     esl_WifiSetConfiguration_t  MmlWlanSetConfiguration_t;

/** @ingroup    MMLayerWlan
    @brief      Set bluetooth status (ESL legacy)
*/
typedef     esl_WifiSetBTStatus_t       MmlWlanSetBluetoothStatus_t;

/** @ingroup    MMLayerWlan
    @brief      Connect network (ESL legacy)
*/
typedef     esl_WifiConnectData_t       MmlWlanConnectNetwork_t;

/** @ingroup    MMLayerWlan
    @brief      Set Fw Test (ESL legacy)
*/
typedef     esl_WifiFwTstConf_t         MmlWlanSetFwTestConfig_t;

/** @ingroup    MMLayerWlan
    @brief      Get Fw Test Result(ESL legacy)
*/
typedef     esl_WifiEvent_t             MmlWlanGetFwTestResult_t;

/** @ingroup    MMLayerWlan
    @brief      Set HW Reg (ESL legacy)
*/
typedef     esl_WifiHwReg_t             MmlWlanSetHwReg_t;

/** @ingroup    MMLayerWlan
    @brief      Get HW Reg (ESL legacy)
*/
//typedef     esl_WifiEvent_t             MmlWlanGetHwReg_t;
typedef struct
{
    MmlWlanSetHwReg_t           tHwReg;
    esl_WifiEvent_t             tEvent;
} MmlWlanGetHwReg_t;


/** @ingroup    MMLayerWlan
    @brief      Set Rx Filter (ESL legacy)
*/
typedef     esl_WifiRxFilter_t          MmlWlanSetRxFilter_t;

/** @ingroup    MMLayerWlan
    @brief      Get Rx Filter (ESL legacy)
*/
typedef     esl_WifiEvent_t             MmlWlanGetRxFilter_t;

/** @ingroup    MMLayerWlan
    @brief      Set Rx Filter (ESL legacy)
*/
typedef     esl_WifiRfReg_t             MmlWlanSetRfReg_t;

/** @ingroup    MMLayerWlan
    @brief      Get Rf Reg (ESL legacy)
*/
//typedef     esl_WifiEvent_t             MmlWlanGetRfReg_t;
typedef struct
{
    MmlWlanSetRfReg_t           tRfReg;
    esl_WifiEvent_t             tEvent;
} MmlWlanGetRfReg_t;



/** @ingroup    MMLayerWlan
    @brief      Set Tx Sin Tone (ESL legacy)
*/
typedef     esl_WifiTxSinTone_t         MmlWlanSetTxSinTone_t;

/** @ingroup    MMLayerWlan
    @brief      Set AQU Memory (ESL legacy)
*/
typedef     esl_WifiAQUMem_t            MmlWlanSetAQUMem_t;

/** @ingroup    MMLayerWlan
    @brief      Get AQU Memory (ESL legacy)
*/
typedef struct
{
    MmlWlanSetAQUMem_t          tAQUMem;
    esl_WifiEvent_t             tEvent;
} MmlWlanGetAQUMem_t;


/** @ingroup    MMLayerWlan
    @brief      Response payload
*/
typedef struct MmlWlanResponse_t_
{
    MmlWlanState_e        eState;        ///< Current state

    union
    {
        MmlWlanConfiguration_t  tConfiguration;        ///< Used with 'Get configuration'
        MmlWlanScanResult_t     tScanResult;           ///< Used with 'Get scan result'
        MmlWlanBss_t            tBss;                  ///< Used with 'Get BSS'
        MmlWlanStateChange_t    tStateChange;          ///< Used with 'WLAN_ERROR_STATE_CHANGE' result
        MmlWlanAQUVer_t         tAQUVer;               ///< Used with 'Get AQU Ver'
        MmlWlanFwTestResult_t   tFwTestResult;         ///< Used with 'Get FW Test Result'
        MmlWlanHwReg_t          tHwReg;                ///< Used with 'Get HW Reg '
        MmlWlanRxFilter_t       tRxFilter;             ///< Used with 'Get Rx Filter'
        MmlWlanRfReg_t          tRfReg;                ///< Used with 'Get Rf Reg'
        MmlAKMCertInfo_t        tCertInfo;             ///< Used with 'Get Cert Infor'
        MmlWlanAQUMem_t         tAQUMem;               ///< Used with 'Get AQU Memory'
    } uParam;
} MmlWlanResponse_t;

/** @ingroup    MMLayerWlan
    @brief      Wlan use case parameters
*/
typedef struct
{
    u32                             nUseCaseID;
    MmlWlanResponseCallback_t       *pResponseCallback;
    MmlWlanResponse_t               *pResponse;

    union
    {
   	    /* No parameter: 'Open, Close, Get configuration, Get scan result, Get BSS, Set power saving'
   	                     'Scan network, Stop scan, Disconnect network'
   	    */
        MmlWlanOpen_t                  tOpen;                  /* Open */
        MmlWlanGetConfiguration_t      tGetConfiguration;      /* Get configuration */
        MmlWlanGetScanResult_t         tGetScanResult;         /* Get scan result */
        MmlWlanGetBSS_t                tGetBSS;                /* Get BSS */
        MmlWlanSetConfiguration_t      tSetConfiguration;      /* Set configuration */
        MmlWlanSetBluetoothStatus_t    tSetBluetoothStatus;    /* Set bluetooth status */
        MmlWlanConnectNetwork_t        tConnectNetwork;        /* Connect network */
        MmlWlanGetAQUVer_t             tGetAQUVer;             /* Get AQU Ver */
        MmlWlanSetGSMStatus_t          tSetGSMStatus;          /* Set GSM Status */
        MmlWlanSetFwTestConfig_t       tSetFwTestConfig;       /* Set FW Test Config*/
        MmlWlanGetFwTestResult_t       tGetFwTestResult;       /* Get FW Test Result*/
        MmlWlanSetHwReg_t              tSetHwReg;              /* Set HW Reg */
        MmlWlanGetHwReg_t              tGetHwReg;              /* Get HW Reg */
        MmlWlanSetRxFilter_t           tSetRxFilter;           /* Set Rx Filter */
        MmlWlanGetRxFilter_t           tGetRxFilter;           /* Get Rx Filter */
        MmlWlanSetRfReg_t              tSetRfReg;              /* Set Rf Reg */
        MmlWlanGetRfReg_t              tGetRfReg;              /* Get Rf Reg */
        MmlWlanGetCertInfo_t           tGetCertInfo;           /* Get Cert Info */
        MmlWlanSetTxSinTone_t          tSetTxSinTone;          /* Set Tx Sin Tone */
        MmlWlanSetAQUMem_t             tSetAQUMem;             /* Set AQU Memory */
        MmlWlanGetAQUMem_t             tGetAQUMem;             /* Get AQU Memory */
    } uParam;
} MmlWlanUCParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
MmlErrCode_e MmlWlanNotifyCallbackDispatch
(
    struct MmlMultimediaGroup_t_    *pGroup,
    u32                             nEvent,
    void                            *pNotifyPayload
);

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLWLAN_TYPES_H__
