#ifndef __mobile_alliance_main_h__
#define __mobile_alliance_main_h__

#include "zm_typedef.h"

/*
 * 程序入口
 */
zm_extern zm_void zm_main(zm_void);

/**
 * 特定类别入口
 */
zm_extern zm_void zm_extra_main_entry(zm_int idx, const zm_uint16* caption);

/**
 * 单独启动某个应用
 * @appId ,应用编号
 */
zm_extern zm_void zm_start_app(const zm_int8* appId, const zm_uint16* app_name);

/*
 * 程序退出
 */
zm_extern zm_void zm_exit(zm_void);

/*
 * 重新绘制
 */
zm_extern zm_void zm_repaint(zm_void);

/*
 * 当被别的应用窗口覆盖的时候调用此窗口
 */
zm_extern zm_void zm_wnd_inactive(zm_void);

/*
 * 按键事件处理
 */
zm_extern zm_void zm_offer_key_event(ZM_KeyEvent event, ZM_KeyCode code);

/*
 * 触笔事件处理
 */
zm_extern zm_void zm_offer_pen_event(ZM_PenEvnent event, zm_point* pt);

/*
 * 判断当前系统是否正在运行
 */
zm_extern zm_bool zm_is_runing(zm_void);

/*
 * 通知系统进入了IDLE界面,通知系统处理信息
 */
zm_extern zm_void zm_enter_idle_screen_notify(zm_void);

#endif//__mobile_alliance_main_h__
