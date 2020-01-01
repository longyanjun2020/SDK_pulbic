#if defined(__ZYUE_ENGINE__)
#if !defined(_PBK_LAUNCHER_H_)
#define _PBK_LAUNCHER_H_
#include "pbk_config.h"

#define PBK_SCRN_STACK_SIZE      5

typedef struct __PBK_SCRN
{
    c_int32    id;
    void		(*show)(void);/* 显示 */
    void		(*hide)(void);/* 隐藏 */
    void		(*exit)(void);/* 退出屏幕 */
}PBK_SCRN;

typedef struct __PBK_SCRN_MGR
{
    PBK_SCRN    scrn[PBK_SCRN_STACK_SIZE];
    c_uint32       count;//入栈的scrn的个数
}PBK_SCRN_MGR;

void pbk_scrn_stack_clear(void);
c_int32 pbk_scrn_push(c_int32 id, void (*show)(void), void (*hide)(void), void (*exit)(void));
c_int32 pbk_scrn_pop(void);
c_int32 pbk_scrn_top_id_get(void);
c_int32 pbk_scrn_top_exit(void);
c_int32 pbk_scrn_top_hide(void);
c_int32 pbk_scrn_top_show(void);

/////////////////////////////////////////////////////////////////////////////
typedef enum __PBK_PLATFORM_STATE
{
    PBK_PLATFORM_FOR_RUN,/* 前台运行中 */
    PBK_PLATFORM_BG_RUN,/* 后台运行中 */
    PBK_PLATFORM_FOR_BG_RUN,/* 前后台都在跑 */
    PBK_PLATFORM_NO_RUN/* 没有运行 */
}PBK_PLATFORM_STATE;

typedef enum __PBK_PLATFORM_TYPE
{
    PBK_PLATFORM_FOR,
    PBK_PLATFORM_BG,
    PBK_PLATFORM_MAX
}PBK_PLATFORM_TYPE;

typedef enum __PBK_PLATFORM_ACTION
{
    PBK_PLATFORM_START,
    PBK_PLATFORM_STOP,
    PBK_PLATFORM_ACTION_MAX
}PBK_PLATFORM_ACTION;


c_int32 pbk_platform_start(void);/* 平台初始化 */

c_int32 pbk_platform_resume(void);
c_int32 pbk_platform_suspend(void);
c_int32 pbk_platform_stop(void);/* 一般停止 */
c_int32 pbk_platform_force_stop(void);/* 挂机键的停止 */

void pbk_platform_init_state(void);
void pbk_platform_curr_state_set(int state);
void pbk_platform_switch_state_set(int state);
int pbk_platform_curr_state_get(void);
int pbk_platform_switch_state_get(void);
int pbk_platform_is_state_locked(void);
c_int32 pbk_platform_start_bg(void);
c_int32 pbk_platform_stop_bg(void);
int pbk_platform_state_switch(int run_type, int action);
void pbk_platform_state_group_set(int state);

c_int32 pbk_applet_launch(c_int32 id);/* 平台应用的运行 */
c_int32 pbk_applet_launch_failed(void);//加载失败
c_int32 pbk_applet_launch_waiting(void);//提示
c_int32 pbk_applet_launch_ok(void);//加载OK


//////////////////////////////////////////
c_int32 pbk_GetActiveScreenId(void);
c_int32 pbk_EntryNewScreen(c_int32 screen_id, void (*focus_on)(void), void (*foucs_off)(void), void (*exit)(void));
void pbk_GoBackHistory(void);
void pbk_GoBackHistoryEX(void);
//////////////////////////////////////////
void pbk_ms_set_sldlm_status(u8 status);
u8 pbk_ms_get_sldlm_status(void);
#endif
#endif
