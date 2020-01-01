#ifndef __MMI_WLAN_MSGDEF_H__
#define __MMI_WLAN_MSGDEF_H__

#include "ABL_WiFi.h"

#define WLANSRV_CERT_FORMAT_PATHPAIR                (2)                                 /* We can support a pair of *.cer format */

#ifdef __NAND_MMI__
#define WLANSRV_MAX_CERT_NUM                        (20)                                /* We can install 20 CERTs in NAND case */
#else
#define WLANSRV_MAX_CERT_NUM                        (3)                                 /* We can install ONLY 3 CERTs in NOR case */
#endif


typedef struct
{
    ABL_WiFiErrCode_e   eErrCode;
    ABL_WiFi_Event_e    eEvent;
    ABL_WiFiScanResultData_t    *ptScanResultData;
} mmi_WLANMsgBody_t;

typedef struct
{
    ABL_WiFiErrCode_e     eErrCode;
    ABL_WiFi_Event_e      eEvent;
    ABL_WiFiScanResult_t *ptBSSData;
} mmi_WLANMsgBSSData_t;

typedef struct
{
    ABL_WiFiErrCode_e  eErrCode;
    ABL_WiFi_Event_e   eEvent;
    ABL_WiFiAQUVer_t  *ptAQUVer;
} mmi_WLANMsgAQUVer_t;
//1 For EM App
typedef struct
{
    ABL_WiFiErrCode_e      eErrCode;
    ABL_EventInfo_t        tEventInfo;
    ABL_WifiFwTestResult_t tWifiFwTestResult;
    union
    {
        ABL_WifiRxFilterResult_t  tRxFilterResult;
        ABL_WifiHwReg_t tWifiHwReg;
        ABL_WiFiAQUVer_t tWifiGetAquVer;
        ABL_WiFiGetRfReg_t tWifiRfReg;
        ABL_WiFiGetAQUMem_t tWifiRfAQUMem;
    }uRspData;
} mmi_WLANMsgEMData_t;

#endif /* __MMI_WLAN_MSGDEF_H__ */
