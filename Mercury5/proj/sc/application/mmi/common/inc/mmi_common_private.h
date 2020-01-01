#ifndef __MMI_COMMON_PRIVATE_H__
#define __MMI_COMMON_PRIVATE_H__

#include "mmi_mae_common_def.h"
#include "mmi_common_custom.h"
#include "mmi_common_cfg.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_window.h"
#include "mmi_mae_widget.h"

#define  APP_WINDOW_MAX        1000
#define  PRIVATE_APP_KEYGUARD  4  //超过PRIVATE_APP_COUNT的数量就是KeyGuard
enum
{
    PRIVATE_INPUT_WND = WND_ID_APP_BASE+APP_WINDOW_MAX,
    WDG_INPUT_PASSWORD,
};

enum
{
    RETURN_TRUE = 0,
    RETURN_FALSE,
    RETURN_START_APP,
    RETURN_KEYGUARD, //返回到KeyGuard，需要在KeyGuardAPP处理
    RETURN_NOT_INPUT_PASSWORD_WND
};

typedef u8 PRIVATE_APP_NAME_e;
typedef u8 PRIVATE_APP_PRESS_RETURN_e;

typedef struct PrivateInputWndData_t_
{
    IWidget *pInputWdgPassword;
    boolean bIsKeyGuard;
}PrivateInputWndData_t;

//检查私有APP是否需要输入密码
LockApp_t PrivateCheckPassword(IApplet *pApplet, PRIVATE_APP_NAME_e appName,boolean bIsKeyGuard);

//设置所有私有APP为密码未验证,OnApp和KeyGuardApp需要该接口
void PrivateSetAllUnverify(void);

//设置打开私有APP次数为0,OnApp需要设置该接口
void PrivateSetAllAppStop(void); 

//输入密码框在最前面拦截按键事件
PRIVATE_APP_PRESS_RETURN_e PrivateInputKetPress(IApplet * pApplet,MAEEvent_t nEvt,u32 param1,u32 param2,PRIVATE_APP_NAME_e appName);

//记录私有APP被调用的次数：Constructor 增加一次；Destructor：减少一次
void PrivateCallAppTimes(PRIVATE_APP_NAME_e appName,CallApp_t tAppState);

//KeyGuard回来后私有APP的处理 TRUE:需要输密码 FALSE:不需要输密码
boolean PrivateKeyGuardResume(IApplet *pApplet);

//长按挂机键显示关机画面
boolean PrivateInputKetLongPress(IApplet * pApplet,MAEEvent_t nEvt,u32 param1,u32 param2);

#endif
