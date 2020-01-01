#ifndef __SRV_RESMGR_WIFI_H__
#define __SRV_RESMGR_WIFI_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "esl_wifi_itf.h"
#include "ResMgr_Common.h"
#include "srv_resmgr_mmlwlan_types.h"
/*=============================================================*/
// Type Declarations
/*=============================================================*/

#if defined(__TARGET__) && defined(__arm)
#define PACK __packed
#else
#define PACK
#endif


#define ABL_MAX_SSID_LEN        (32)
#define ABL_MAX_KEY_LEN         (64)
#define ABL_MAX_BSSID_LEN       (6)
#define ABL_MAX_SCAN_RESULT_NUM (50)

// Command param. data struct
typedef     MmlWlanSetFwTestConfig_t    ABL_WiFiSetFwTestConfig_t;
typedef     MmlWlanGetFwTestResult_t    ABL_WiFiGetFwTestResult_t;
typedef     MmlWlanSetHwReg_t           ABL_WiFiSetHwReg_t;
typedef     MmlWlanGetHwReg_t           ABL_WiFiGetHwReg_t;
typedef     MmlWlanSetRxFilter_t        ABL_WiFiSetRxFilter_t;
typedef     MmlWlanGetRxFilter_t        ABL_WiFiGetRxFilter_t;
typedef     MmlWlanSetRfReg_t           ABL_WiFiSetRfReg_t;
typedef     MmlWlanGetRfReg_t           ABL_WiFiGetRfReg_t;
typedef     MmlWlanGetAQUVer_t          ABL_WiFiGetAQUVer_t;

typedef     esl_WifiFwTstResult_t       ABL_WifiFwTestResult_t;
typedef     esl_WifiRxFilterResult_t    ABL_WifiRxFilterResult_t;
typedef     esl_WifiHwReg_t             ABL_WifiHwReg_t;

typedef     MmlWlanGetCertInfo_t        ABL_WiFiGetCertInfo_t;
typedef     MmlWlanCertScoure_t         ABL_WiFiCertScoure_t;
typedef     MmlWlanX509Name_t           ABL_WiFiX509Name_t;
typedef     MmlAKMCertInfo_t            ABL_WiFiAKMCertInfo_t;

typedef     MmlWlanSetTxSinTone_t       ABL_WiFiSetTxSinTone_t;
typedef     MmlWlanSetAQUMem_t          ABL_WiFiSetAQUMem_t;
typedef     MmlWlanGetAQUMem_t          ABL_WiFiGetAQUMem_t;


typedef enum ABL_WiFiErrCode_e_
{
    ABL_WIFI_OK=0,
    ABL_WIFI_FAIL,
    ABL_WIFI_PARAM_ERROR,
    ABL_WIFI_MEM_ALLOC_ERROR,
    ABL_WIFI_REJECT,
    ABL_WIFI_ABORT,
    ABL_WIFI_TIMEOUT,
    ABL_WIFI_FIFO_INIT_FAIL,
    ABL_WIFI_NOT_READY,
    ABL_WIFI_NULL_MAC
}ABL_WiFiErrCode_e;

typedef enum
{
    ABL_WIFI_EVENT__CONNECT_FAIL=ESL_WIFI_EVENT_CONNECT_FAIL, /* 0x00044001 */
    ABL_WIFI_EVENT__CONNECTED,                                /* 0x00044002 */
    ABL_WIFI_EVENT__DISCONNECTED,                             /* 0x00044003 */
    ABL_WIFI_EVENT__ROAMING,                                  /* 0x00044004 */
    ABL_WIFI_EVENT__SCAN_DONE,                                /* 0x00044005 */
    ABL_WIFI_EVENT__PASSWORD_FAIL,                            /* 0x00044006 */
    ABL_WIFI_EVENT__FW_TEST_DONE,                             /* 0x00044007 */
    ABL_WIFI_EVENT__CERT_FAIL,                                /* 0x00044008 */
    ABL_WIFI_EVENT__CERT_UNKNOWN_ISSUER,                      /* 0x00044009 */
    ABL_WIFI_EVENT__CERT_UNTRUSTED_ROOT,                      /* 0x0004400A */
    ABL_WIFI_EVENT__CERT_INVALID_TIME,                        /* 0x0004400B */
    ABL_WIFI_EVENT__CERT_INVALID_SIGNATURE,                   /* 0x0004400C */
    ABL_WIFI_EVENT__CERT_REVOKED,                             /* 0x0004400D */
    ABL_WIFI_EVENT__CERT_INVALID_USAGE,                       /* 0x0004400E */
    ABL_WIFI_EVENT__CERT_FAIL_UNKNOW,                         /* 0x0004400F */
    ABL_WIFI_EVENT__ON,
    ABL_WIFI_EVENT__OFF,
    ABL_WIFI_EVENT__GETIP_OK,
    ABL_WIFI_EVENT__GETIP_FAIL,
    ABL_WIFI_EVENT__AIRPLANE_ON
}ABL_WiFi_Event_e;

#ifdef __GNUC__
typedef struct PACK ABL_WiFiScanResult_t_
#else
typedef PACK struct ABL_WiFiScanResult_t_
#endif
{
    u8  uSSID[ABL_MAX_SSID_LEN];
    u32 uSSIDLen;
    u32 uSecurity;
    u32 uChannel;
    s32 sQual;
    s32 sNoise;
    s32 sLevel;
    u32 uMode;
    u32 uSpeed;
    u8  uBSSID[ABL_MAX_BSSID_LEN];
}ABL_WiFiScanResult_t;

#ifdef __GNUC__
typedef struct PACK ABL_WiFiScanResultData_t_
#else
typedef PACK struct ABL_WiFiScanResultData_t_
#endif
{
    u32                  num;
    ABL_WiFiScanResult_t sScanResult[ABL_MAX_SCAN_RESULT_NUM];
}ABL_WiFiScanResultData_t;

typedef struct ABL_WiFiRspInfo_t
{
    union
    {
        ABL_WiFiScanResultData_t *psScanResultData;
        ABL_WiFiScanResult_t     *psBSSData;
        ABL_WifiFwTestResult_t   *pFwTestResult;
        ABL_WifiRxFilterResult_t *pRxFilterResult;
        ABL_WiFiGetRfReg_t       *pRfReg;
        ABL_WiFiGetAQUMem_t      *pRfAQUMem;
    }uRspData;
}ABL_WiFiRspInfo_t;

typedef struct ABL_EventInfo_t_
{
	ABL_WiFi_Event_e eEvent;
}ABL_EventInfo_t;

typedef void (*ABL_WiFiCb)     (u16 uSenderID,u32 uUserData,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
typedef void (*ABL_WiFiEventCb)(u16 uSenderID,u32 uUserData,ABL_EventInfo_t *psEventInfo);

typedef struct ABL_WiFiCbInfo_t
{
    u16        uSenderID;
    u32        uUserData;
    ABL_WiFiCb pWiFiCb;
}ABL_WiFiCbInfo_t;

typedef struct ABL_EventCbInfo_t_
{
    u32             uSenderID;
    u32             uUserData;
    ABL_WiFiEventCb pEventCb;
}ABL_EventCbInfo_t;

typedef enum
{
    ABL_WIFI_SECURITY__NONE  =0x0001,
    ABL_WIFI_SECURITY__WEP40 =0x0002,
    ABL_WIFI_SECURITY__WEP104=0x0004,
    ABL_WIFI_SECURITY__WEP   =0x0006,
    ABL_WIFI_SECURITY__WPA       =0x0008,
    ABL_WIFI_SECURITY__WPA_PSK   =ABL_WIFI_SECURITY__WPA,
    ABL_WIFI_SECURITY__WPA2      =0x0010,
    ABL_WIFI_SECURITY__WPA2_PSK  =ABL_WIFI_SECURITY__WPA2,
    ABL_WIFI_SECURITY__WAPI_PSK  =0x0020,
    ABL_WIFI_SECURITY__WPA_CERT  =0x0040,
    ABL_WIFI_SECURITY__WPA2_CERT =0x0080,
    ABL_WIFI_SECURITY__WAPI_CERT =0x0100
}ABL_WiFi_Security_e;

#ifdef __GNUC__
typedef struct PACK ABL_WiFiConnect_Param_t_
#else
typedef PACK struct ABL_WiFiConnect_Param_t_
#endif
{
    u8  uSSID[ABL_MAX_SSID_LEN];
    u32 uSSIDLen;
    u32 uSecurity;
    u32 uKeyIdx;
    u8  uPassWd[ABL_MAX_KEY_LEN];
    u32 nCaRaiId;
    u32 nClientRaiId;
    u16 nCaRaiSize;
    u16 nClientRaiSize;
    u8  uBSSID[ABL_MAX_BSSID_LEN];
}ABL_WiFiConnect_Param_t;

#ifdef __GNUC__
typedef struct PACK ABL_WiFiSetConfiguration_Param_t_
#else
typedef PACK struct ABL_WiFiSetConfiguration_Param_t_
#endif
{
    u8 own_addr[6];    /* own MAC address */
    u8 pad[2];         /* for alignment   */
}ABL_WiFiSetConfiguration_Param_t;

typedef MmlWlanSetBluetoothStatus_t ABL_WiFiSetBTStatus_Param_t;

typedef esl_WifiGetAQUVer_t     ABL_WiFiAQUVer_t;

#ifdef __GNUC__
typedef struct PACK ABL_WiFiSetGSMStatus_Param_t_
#else
typedef PACK struct ABL_WiFiSetGSMStatus_Param_t_
#endif
{
    u32 u32GSMStatus;    /* the GSM/GPRS status */
}ABL_WiFiSetGSMStatus_Param_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

ABL_WiFiErrCode_e ABL_WiFiInit(void);
ABL_WiFiErrCode_e ABL_WiFiUnInit(void);
ABL_WiFiErrCode_e ABL_WiFiTurnOn          (ResMgr_AppId_e eAppId,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiTurnOff         (ResMgr_AppId_e eAppId,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiReSet           (ResMgr_AppId_e eAppId,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiPowerSaving     (ResMgr_AppId_e eAppId,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetScan         (ResMgr_AppId_e eAppId,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiStopScan        (ResMgr_AppId_e eAppId,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiDisconnect      (ResMgr_AppId_e eAppId,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiConnect         (ResMgr_AppId_e eAppId,ABL_WiFiConnect_Param_t *psConnectParam,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetConfiguration(ResMgr_AppId_e eAppId,ABL_WiFiSetConfiguration_Param_t *psConfigParam,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetConfiguration(ResMgr_AppId_e eAppId,ABL_WiFiSetConfiguration_Param_t *psConfigData,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetFwTest(ResMgr_AppId_e eAppId, ABL_WiFiSetFwTestConfig_t *pSetFwTestConfig, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetFwTestResult(ResMgr_AppId_e eAppId, ABL_WiFiGetFwTestResult_t *pGetFwTestResult, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetHWReg(ResMgr_AppId_e eAppId, ABL_WiFiSetHwReg_t *pSetHwReg, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetHWReg(ResMgr_AppId_e eAppId, ABL_WiFiGetHwReg_t *pGetHwReg, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetRxFilter(ResMgr_AppId_e eAppId, ABL_WiFiSetRxFilter_t *pSetRxFilter, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetRxFilterResult(ResMgr_AppId_e eAppId, ABL_WiFiGetRxFilter_t *pGetRxFilter, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetRFReg(ResMgr_AppId_e eAppId, ABL_WiFiSetRfReg_t *pSetHfReg, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetRFReg(ResMgr_AppId_e eAppId, ABL_WiFiGetRfReg_t *pGetHfReg, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiRegEvent        (ResMgr_AppId_e eAppId,ABL_EventCbInfo_t *psEventCbInfo);
ABL_WiFiErrCode_e ABL_WiFiUnRegEvent      (ResMgr_AppId_e eAppId);
ABL_WiFiErrCode_e ABL_WiFiInitFifo        (ResMgr_AppId_e eAppId,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiDeleteFifo      (ResMgr_AppId_e eAppId,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetScanResult   (ResMgr_AppId_e eAppId,ABL_WiFiScanResultData_t *psScanResultData,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetBSS          (ResMgr_AppId_e eAppId,ABL_WiFiScanResult_t *psBSSData,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetBTStatus     (ResMgr_AppId_e eAppId,ABL_WiFiSetBTStatus_Param_t *psBTStatusParam,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetAQUVer       (ResMgr_AppId_e eAppId,ABL_WiFiAQUVer_t *psAQUVer,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetGSMStatus    (ResMgr_AppId_e eAppId,ABL_WiFiSetGSMStatus_Param_t *psGSMStatusParam,ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetCertInfo(ABL_WiFiCertScoure_t *pWiFiCertScoure, ABL_WiFiAKMCertInfo_t *pWiFiAKMCertInfo);
void              ABL_WiFiCertFree(ABL_WiFiAKMCertInfo_t *pWiFiAKMCertInfo);
ABL_WiFiErrCode_e ABL_WiFiStopContTx(ResMgr_AppId_e eAppId, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetTxSinTone(ResMgr_AppId_e eAppId, ABL_WiFiSetTxSinTone_t *pSetTxSinTone, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiSetAquMem(ResMgr_AppId_e eAppId, ABL_WiFiSetAQUMem_t *pSetAQUMem, ABL_WiFiCbInfo_t *psCbInfo);
ABL_WiFiErrCode_e ABL_WiFiGetAquMem(ResMgr_AppId_e eAppId, ABL_WiFiGetAQUMem_t *pGetAQUMem, ABL_WiFiCbInfo_t *psCbInfo);


#endif/* __ABL_WIFI_H__ */
