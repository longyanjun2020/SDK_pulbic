#ifndef __MMI_CB_WLAN_H__
#define __MMI_CB_WLAN_H__

/*=============================================================*/
/* Include Files                                               */
/*=============================================================*/
#include "ABL_WiFi.h"

/*=============================================================*/
/* Function Declarations                                       */
/*=============================================================*/
void WLAN_WiFiEventCB        (u16 nSenderID,u32 nUserData, ABL_EventInfo_t *ptEventInfo);
void WLAN_WiFiTurnOnCB       (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiTurnOffCB      (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiResetCB        (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiPowerSavingCB  (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiStartScanCB    (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiStopScanCB     (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiGetScanResultCB(u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiGetBSSCB       (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiConnectCB      (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiDisconnectCB   (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiInitFifoCB     (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiDeleteFifoCB   (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiSetConfigCB    (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiSetBTStatusCB  (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiGetAQUVer      (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
void WLAN_WiFiSetGSMStatusCB (u16 nSenderID,u32 nUserValue,ABL_WiFiErrCode_e eErrCode,ABL_WiFiRspInfo_t *pRspInfo);
//For EM
void WLAN_WiFiEMOnCB             (u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiInfo);
void WLAN_WiFiEMSendProductionCB (u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiInfo);
void WLAN_WiFiEMRegNotifyCB      (u16 nSenderID,u32 nUserValue, ABL_EventInfo_t *pWifiNotifyInfo);
void WLAN_WiFiEMGetFwTestResultCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiInfo);
void WLAN_WiFiEMGetAquariudSwVersionCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMGetRxCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMSetRxCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMReadRegCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMWriteRegCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMSendTxCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMStopTxCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMCommonCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo,u32 TypMsg);
void WLAN_WiFiEMSetSinToneCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMWriteRFRegCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMReadRfRegCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMWriteAQUMemCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
void WLAN_WiFiEMReadAQUMemCB(u16 nSenderID,u32 nUserValue, ABL_WiFiErrCode_e eErrCode, ABL_WiFiRspInfo_t *pWifiRspInfo);
#endif /* __MMI_CB_WLAN_H__ */
