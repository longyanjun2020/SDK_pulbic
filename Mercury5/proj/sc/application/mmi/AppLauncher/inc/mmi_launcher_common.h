#ifndef __APP_COMMON_H__
#define __APP_COMMON_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_apm.h"
#include "mmi_mae_helper.h"
#include "mmi_UrlSrvCommonSchemeTbl.h"
#include "mmi_common_transition.h"


typedef unsigned int AppLaunchMode_e;

typedef void (*CmnLaunchAppRspCb)(void *pvUserData, MAE_Ret nRspCode);
typedef void (*CmnRspDataFreeCb)(void *pvRspData);
typedef void (*CmnLaunchAppDataRspCb)(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);

typedef enum
{
	SIM_ID_MIN = 0,
    SIM_ID_SIM1 = SIM_ID_MIN,
	SIM_ID_SIM2,
    SIM_ID_MAX = SIM_ID_SIM2,
	SIM_ID_INVALID,
}SimID_e;

typedef struct
{
    void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
    CmnLaunchAppDataRspCb pfnDataRspCb;
}CmnAppLaunchRspCbInfo_t;


typedef struct
{
    u32 eTransIn;
    u32 eTransOut;
}LaunchAppTransParam_t;


/// 0 == NORMAL
/// 1 == INTERRUPTIVE
/// 2 == EMBEDDED
///0x40000 == APML_AUTO_RELEASE
#define IS_VALID_APP_LAUNCH_MODE(MODE) \
    ((MODE == APM_LAUNCH_NORMAL) || (MODE & APM_LAUNCH_INTERRUPTIVE) || (MODE & APM_LAUNCH_EMBEDDED) || (MODE & APML_AUTO_RELEASE))

 MAE_Ret LaunchApp
 (
   UrlSrvUrlScheme_e eScheme,
   MAE_WChar         *pwStrUrlParam,
   CmnAppLaunchRspCbInfo_t *psRspCbInfo
 );


 #define DefaultAppLauncher(APM_MODE, SCHEME_ID, PS_RSPCBINFO)   \
     do  \
 {   \
     MAE_Ret _nRet = MAE_RET_SUCCESS; \
     MAE_WChar _wStrUrlParam[32] = {0}; \
     mae_swprintf(_wStrUrlParam, 32, L"Default?APM_Mode=%d", APM_MODE); \
     _nRet = LaunchApp(SCHEME_ID, _wStrUrlParam, PS_RSPCBINFO); \
     ASSERT(MAE_RET_SUCCESS == _nRet);    \
 }while(FALSE);

#define DefaultAppLauncherEx(APM_MODE, SCHEME_ID, PS_TRANSPARAM_IN, PS_TRANSPARAM_OUT, PS_RSPCBINFO)   \
    do  \
{   \
    MAE_Ret _nRet = MAE_RET_SUCCESS; \
    MAE_WChar _wStrUrlParam[32+25] = {0}; \
    mae_swprintf(_wStrUrlParam, 32+25, L"Default?APM_Mode=%d&TransInId=%d&TransOutId=%d", APM_MODE,PS_TRANSPARAM_IN,PS_TRANSPARAM_OUT); \
    _nRet = LaunchApp(SCHEME_ID, _wStrUrlParam, PS_RSPCBINFO); \
    ASSERT(MAE_RET_SUCCESS == _nRet);    \
}while(FALSE);

void CloseCurEmbeddedApp
(
  UrlSrvUrlScheme_e eAppScheme
);

void DefaultAppLauncherDataFreeCb(void *pvRspData);

#define AddLauncherHandler(SCHEME_ID, USER_DATA, HDLR)\
	do	\
	{	\
	UrlSrvRegHdlrRspInfo_t sCmnRegHdlrRspInfo = {0};	\
	UrlSrvUrlHandlerInfo_t sCmnRegUrlHdlr = {SRV_URLHANDLER_TYPE_HOOK,0};	\
	sCmnRegUrlHdlr.pvUserData = USER_DATA;	\
	sCmnRegUrlHdlr.eHandlerType = SRV_URLHANDLER_TYPE_ALL;	\
	sCmnRegUrlHdlr.pfnUrlHandler = (UrlSrvUrlHandler)HDLR;	\
	sCmnRegHdlrRspInfo.pvUserData = NULL;	\
	sCmnRegHdlrRspInfo.pfnRegHdlrRspCb = UrlSrvCmnRegUrlRspCb;	\
	UrlSrvClientAddUrlHandler(SCHEME_ID, &sCmnRegUrlHdlr, &sCmnRegHdlrRspInfo);\
	}while(FALSE)

#endif/* __APP_COMMON_H__ */
