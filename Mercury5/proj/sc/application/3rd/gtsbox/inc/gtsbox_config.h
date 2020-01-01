#ifndef __GTSBOX_CONFIG_H__
#define __GTSBOX_CONFIG_H__

#include "gts_device_attribute.h"

///////////////////////////////////////////////////////////////////////////////////////////
// 可配置选项

//屏幕旋转
#define GTSBOX_SCREEN_ROTATE SCREEN_ROTATE_NONE

//下载界面使用java logo
//#define GTSBOX_JAVA_DOWNLOAD_INTERFACE

//开启应用选项菜单(开始、介绍、删除)
//#define GTSBOX_APP_OPTION_MENU

///////////////////////////////////////////////////////////////////////////////////////////
//
// 自动配置宏，请不要手动修改
//
///////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// 屏幕宽高
#if defined(__MMI_MAINLCD_128X160__)
#define GTSBOX_SW 128
#define GTSBOX_SH 160
#elif defined(__MMI_MAINLCD_176X220__)
#define GTSBOX_SW 176
#define GTSBOX_SH 220
#elif defined(__MMI_MAINLCD_240X320__)
#define GTSBOX_SW 240
#define GTSBOX_SH 320
#elif defined(__MMI_MAINLCD_240X400__)
#define GTSBOX_SW 240
#define GTSBOX_SH 400
#else
#endif

/////////////////////////////////////////////////////////////////////////////////
// 应用的入口函数，动态加载的应用固定为gtsbox_app_start

#if defined(__MMI_GTSBOX_PRO_STATIC__)
	extern void gts_gbxpro_start(void);
#	define GTSBOX_PRO_ENTRY gts_gbxpro_start
#else
#	define GTSBOX_PRO_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_TANTANTU_STATIC__)
// edit by wolf
	extern void gts_CuteRabit_start(void);
#	define GTSBOX_TANTANTU_ENTRY gts_CuteRabit_start
// end by wolf
#else
#	define GTSBOX_TANTANTU_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_MOSHIZHANJI_STATIC__)
// edit by wolf
	extern void gts_tianshan_start(void);
#	define GTSBOX_MOSHIZHANJI_ENTRY gts_tianshan_start
// end by wolf
#else
#	define GTSBOX_MOSHIZHANJI_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_MEINVMAJIANG_STATIC__)
// edit by wolf
	extern void gts_majon_start(void);
#	define GTSBOX_MEINVMAJIANG_ENTRY gts_majon_start
// end by wolf
#else
#	define GTSBOX_MEINVMAJIANG_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_SHUIJINGWUYU_STATIC__)
// edit by wolf
	extern void gts_crystalglory_start(void);
#	define GTSBOX_SHUIJINGWUYU_ENTRY gts_crystalglory_start
// end by wolf
#else
#	define GTSBOX_SHUIJINGWUYU_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_HAIDIAOWANG_STATIC__)
// edit by wolf
	extern void gts_fish_start(void);
#	define GTSBOX_HAIDIAOWANG_ENTRY gts_fish_start
// end by wolf
#else
#	define GTSBOX_HAIDIAOWANG_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_HUANXIANGMOFA_STATIC__)
// edit by wolf
	extern void gts_pantem_start(void);
#	define GTSBOX_HUANXIANGMOFA_ENTRY gts_pantem_start
// end by wolf
#else
#	define GTSBOX_HUANXIANGMOFA_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_HUIDAOYADIAN_STATIC__)
// edit by wolf
	extern void gts_athens_start(void);
#	define GTSBOX_HUIDAOYADIAN_ENTRY gts_athens_start
// end by wolf
#else
#	define GTSBOX_HUIDAOYADIAN_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_MOFABATTLE_STATIC__)
// edit by wolf
	extern void gts_MagicBattle_start(void);
#	define GTSBOX_MOFABATTLE_ENTRY gts_MagicBattle_start
// end by wolf
#else
#	define GTSBOX_MOFABATTLE_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_MOJIANTIANSHI_STATIC__)
// edit by wolf
	extern void gts_ramiel_start(void);
#	define GTSBOX_MOJIANTIANSHI_ENTRY gts_ramiel_start
// end by wolf
#else
#	define GTSBOX_MOJIANTIANSHI_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_TANKBATTLE_STATIC__)
// edit by wolf
	extern void gts_tank_start(void);
#	define GTSBOX_TANKBATTLE_ENTRY gts_tank_start
// end by wolf
#else
#	define GTSBOX_TANKBATTLE_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_WANGZICHUANSHUO_STATIC__)
// edit by wolf
	extern void gts_mota_start(void);
#	define GTSBOX_WANGZICHUANSHUO_ENTRY gts_mota_start
// end by wolf
#else
#	define GTSBOX_WANGZICHUANSHUO_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_GANGTIE_STATIC__)
// edit by wolf
	extern void gts_tankforce2_start(void);
#	define GTSBOX_GANGTIE_ENTRY gts_tankforce2_start
// end by wolf
#else
#	define GTSBOX_GANGTIE_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_SHUIJINGQIU_STATIC__)
// edit by wolf
	extern void gts_crystalball_start(void);
#	define GTSBOX_SHUIJINGQIU_ENTRY gts_crystalball_start
// end by wolf
#else
#	define GTSBOX_SHUIJINGQIU_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_DADISHU_STATIC__)
// edit by wolf
	extern void gtsbox_app_hamsterfight_start(void);
#	define GTSBOX_DADISHU_ENTRY gtsbox_app_hamsterfight_start
// end by wolf
#else
#	define GTSBOX_DADISHU_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_SHINANREN_STATIC__)
// edit by wolf
	extern void gtsbox_app_realman_start(void);
#	define GTSBOX_SHINANREN_ENTRY gtsbox_app_realman_start
// end by wolf
#else
#	define GTSBOX_SHINANREN_ENTRY 0
#endif

// add by wolf
#if defined(__MMI_GTSBOX_TANCHIYU_STATIC__)
	extern void gtsbox_app_fish_start(void);
#	define GTSBOX_TANCHIYU_ENTRY gtsbox_app_fish_start
#else
#	define GTSBOX_TANCHIYU_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_REQIQIU_STATIC__)
	extern void gts_balloon_start(void);
#	define GTSBOX_REQIQIU_ENTRY gts_balloon_start
#else
#	define GTSBOX_REQIQIU_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_TANCHISHE_STATIC__)
	extern void gtsbox_snake_start(void);
#	define GTSBOX_TANCHISHE_ENTRY gtsbox_snake_start
#else
#	define GTSBOX_TANCHISHE_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_CHOUQIAN_STATIC__)
	extern void gtsbox_app_sortition_start(void);
#	define GTSBOX_CHOUQIAN_ENTRY gtsbox_app_sortition_start
#else
#	define GTSBOX_CHOUQIAN_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_ZHITOUZI_STATIC__)
	extern void gts_dice_start(void);
#	define GTSBOX_ZHITOUZI_ENTRY gts_dice_start
#else
#	define GTSBOX_ZHITOUZI_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_KOF_STATIC__)
	extern void gtsbox_app_kof_start(void);
#	define GTSBOX_KOF_ENTRY gtsbox_app_kof_start
#else
#	define GTSBOX_KOF_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_HUANGDI_STATIC__)
	extern void gts_BrickWall_start(void);
#	define GTSBOX_HUANGDI_ENTRY gts_BrickWall_start
#else
#	define GTSBOX_HUANGDI_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_PAOKU_STATIC__)
	extern void gts_parkour2_start(void);
#	define GTSBOX_PAOKU_ENTRY gts_parkour2_start
#else
#	define GTSBOX_PAOKU_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_WIRE_STATIC__)
	extern void gts_wire_start(void);
#	define GTSBOX_WIRE_ENTRY gts_wire_start
#else
#	define GTSBOX_WIRE_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_CRAZYRABIT_STATIC__)
	extern void gts_crazyrabit_start(void);
#	define GTSBOX_CRAZYRABIT_ENTRY gts_crazyrabit_start
#else
#	define GTSBOX_CRAZYRABIT_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_CIBA_STATIC__)
	extern void gts_ciba_start(void);
#	define GTSBOX_CIBA_ENTRY gts_ciba_start
#else
#	define GTSBOX_CIBA_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_NTB_STATIC__)
	extern void gts_ntb_start(void);
#	define GTSBOX_NTB_ENTRY gts_ntb_start
#else
#	define GTSBOX_NTB_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_MBLOG_STATIC__)
	extern void gts_mblog_start(void);
#	define GTSBOX_MBLOG_ENTRY gts_mblog_start
#else
#	define GTSBOX_MBLOG_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_PIGRUN_STATIC__)
	extern void gts_pigrun_start(void);
#	define GTSBOX_PIGRUN_ENTRY gts_pigrun_start
#else
#	define GTSBOX_PIGRUN_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_WANGCUO_STATIC__)
	extern void gtsbox_app_fg_start (void);
#define GTSBOX_WANGCUO_ENTRY gtsbox_app_fg_start
#else
#define GTSBOX_WANGCUO_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_BUYUDAREN_STATIC__)
	extern void gtsbox_fishingjoy_start (void);
#define GTSBOX_BUYUDAREN_ENTRY gtsbox_fishingjoy_start
#else
#define GTSBOX_BUYUDAREN_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_MEINVCHAOCHA_STATIC__)
	extern void gts_girlhunt_start (void);
#define GTSBOX_MEINVCHAOCHA_ENTRY gts_girlhunt_start
#else
#define GTSBOX_MEINVCHAOCHA_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_CHAOREN_STATIC__)
	extern void gts_SuperMan_start (void);
#define GTSBOX_CHAOREN_ENTRY gts_SuperMan_start
#else
#define GTSBOX_CHAOREN_ENTRY 0
#endif

#if defined(__MMI_GTSBOX_CHUIQUNZI_STATIC__)
	extern void gtsbox_puff_start (void);
#define GTSBOX_CHUIQUNZI_ENTRY gtsbox_puff_start
#else
#define GTSBOX_CHUIQUNZI_ENTRY 0
#endif
// end by wolf


//////////////////////////////////////////////////////////////////////////////////////////
// 应用的app id(game id)

#define GTSBOX_PRO_APP_ID						20001
#define GTSBOX_PRO_RES_APP_ID					20003

//add after this line

#define GTSBOX_MOSHIZHANJI_APP_ID 			85
#define GTSBOX_MEINVMAJIANG_APP_ID 			83
#define GTSBOX_SHUIJINGWUYU_APP_ID 			87
#define GTSBOX_HAIDIAOWANG_APP_ID 			78
#define GTSBOX_HUANXIANGMOFA_APP_ID 			79
#define GTSBOX_HUIDAOYADIAN_APP_ID 			82
#define GTSBOX_MOFABATTLE_APP_ID 				84
#define GTSBOX_MOJIANTIANSHI_APP_ID			80
#define GTSBOX_TANKBATTLE_APP_ID 				88
#define GTSBOX_WANGZICHUANSHUO_APP_ID 		81
#define GTSBOX_GANGTIE_APP_ID					89
#define GTSBOX_SHUIJINGQIU_APP_ID				86
#define GTSBOX_DADISHU_APP_ID					90
#define GTSBOX_SHINANREN_APP_ID				91
#define GTSBOX_TANCHIYU_APP_ID				69
#define GTSBOX_REQIQIU_APP_ID					73
#define GTSBOX_TANCHISHE_APP_ID				72
#define GTSBOX_CHOUQIAN_APP_ID				70
#define GTSBOX_ZHITOUZI_APP_ID				71
#define GTSBOX_KOF_APP_ID						74
#define GTSBOX_TANTANTU_APP_ID 				105
#define GTSBOX_HUANGDI_APP_ID					102
#define GTSBOX_PAOKU_APP_ID					106
#define GTSBOX_WIRE_APP_ID					110
#define GTSBOX_CRAZYRABIT_APP_ID				111
#define GTSBOX_CIBA_APP_ID						113
#define GTSBOX_NTB_APP_ID						115
#define GTSBOX_MBLOG_APP_ID					114
#define GTSBOX_PIGRUN_APP_ID					99
#define GTSBOX_WANGCUO_APP_ID				107
#define GTSBOX_BUYUDAREN_APP_ID				117
#define GTSBOX_MEINVCHAOCHA_APP_ID			118
#define GTSBOX_CHAOREN_APP_ID					104
#define GTSBOX_CHUIQUNZI_APP_ID				116
#endif
