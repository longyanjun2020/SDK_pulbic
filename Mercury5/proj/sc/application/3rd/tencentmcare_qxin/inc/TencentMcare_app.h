#ifndef __TECENT_MCARE_APP_H__
#define __TECENT_MCARE_APP_H__
/*
================IMPORTANT================
This macro is control TENCENT SOFTWARE Multiple Entry.
If you do not want multiple entry, please mark this macro.
If you want to keep this macro, before you must know very clearly this effect.
Sometime the MSTAR shortcuts your did not configured right,
this macro will cause you phone SCREEN BLACK OUT.
2011-09-07 KEL.
================IMPORTANT================
*/
//#define __TENCENT_MULTIPLE_ENTRY__


#include "ven_sdk.h"
#include "ven_os.h"
#include "ven_stc.h"
#include "ven_kpd.h"
#include "ven_ts.h"
#include "ven_ui.h"
#include "ven_handle.h"
#include "ven_graphics.h"
#include "McfCommon_priv.h"
#include "ven_graphics.h"

// Using help send command. KEL.
#define BG_RSP		(1) // Background RSP.
#define STOP_IND	(2)	
#define FG_RSP		(3)	// Foreground RSP.


//多入口入口类型，by fad
typedef enum __MultiEntryType
{
    E_ENTRY_DEFAULT = 0,            //默认进入腾讯软件中心
    E_ENTRY_QQB,                    //QQ浏览器
    E_ENTRY_QQDDZ,                  //NOT SUPPORT NOW
    E_ENTRY_QZONE,                  //手机QQ空间
    E_ENTYR_QQBOOKMALL   ,          //QQ书城NOT SUPPORT NOW
    E_ENTRY_QQBOOKMALL_FREE,        //QQ书城（免费版）
    E_ENTRY_QQMICROBLOG,            //腾讯微博
    E_ENTRY_SOSO,                   //腾讯soso
    E_ENTRY_FRIEND,                 //腾讯朋友网
    E_ENTRY_QQMAIL,                 //QQ邮箱
    E_ENTRY_QQNEWS,                 //腾讯新闻
    E_ENTRY_QQSTOCK,                //腾讯股票
    E_ENTRY_QQENTERTAINMENT,        //腾讯娱乐
    E_ENTRY_QQSPORTS,               //腾讯体育
    E_ENTRY_QQFARM,                 //QQ农场
    E_ENTRY_QQPASTURE,              //QQ牧场
    E_ENTRY_QQHOUSELAND,            //QQ家园
    E_ENTRY_QQMAGICGARDEN,          //魔法花园
    E_ENTRY_QQSUNNYPASTURE,         //阳光牧场
    E_ENTRY_QQJINGWUTANG,           //精武堂
    E_ENTRY_QQDELICIOUSTOWN,        //美味小镇
    E_ENTRY_QQANIMALHERO,           //神兽英雄
    E_ENTRY_QQLOVEPET,              //爱宠国
    E_ENTRY_QQMUSIC,                //QQ音乐
    E_ENTRY_CAIFUTONG,              //财付通
    E_ENTRY_QQGAME,                 //QQ游戏
    E_ENTRY_FRIENDDEAL,             //好友买卖
    E_ENTRY_SUPERQQ,                //超级QQ
    E_ENTER_3RD_BAIDU,              //百度
    E_ENTER_3RD_RENRENWANG,         //人人网
    E_ENTER_3RD_SINAWEIBO,           //新浪微博
    E_ENTER_QQMESSAGE               //Q信
}MultiEntryType;



#endif
