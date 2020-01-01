
#ifndef __MMI_IDLEAPP_CFG__H__
#define __MMI_IDLEAPP_CFG__H__

// Allow Mater Reset
//#define CONFIG_DEFINE(cfgId, type, name, value)

//Android style begin
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__

typedef struct
{
    u8  u8PosIndex;
    u8  u8MenuID;
} ItemOrderInfo_t;

#ifndef __UI_STYLE_MMI_ANDROID_IDLE_MUTEX__
typedef struct
{
    u16  Pos_x;
    u16  Pos_y;
    u8  u8MenuID;
} DeskTopWdgInfo_t;
#endif

#ifdef __LCM_QVGA__
    #define CONFIG_AMR_IDLEAPP_ICON_ORDER                 CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_ORDER, ItemOrderInfo_t, (4 + 12*4), \
    {/*1 Page max is 4*/{0,0},{0,0},{0,0},{0,0},\
     /*2 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*3 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*4 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*5 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}})
#elif defined(__LCM_WQVGA_240_400__)
    /*Total page is 5,and firt page item number is 3, other page item num is 12*/
    #ifdef __UI_STYLE_MMI_ANDROID_4_0__
    #define CONFIG_AMR_IDLEAPP_ICON_ORDER                 CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_ORDER, ItemOrderInfo_t, (8 + 16*4), \
    {/*1 Page max is 8*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*2 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*3 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*4 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*5 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}})
    #else // !__UI_STYLE_MMI_ANDROID_4_0__
    #define CONFIG_AMR_IDLEAPP_ICON_ORDER                 CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_ORDER, ItemOrderInfo_t, (3 + 12*4), \
    {/*1 Page max is 3*/{0,0},{0,0},{0,0},\
     /*2 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*3 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*4 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*5 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}})
    #endif // __UI_STYLE_MMI_ANDROID_4_0__
#elif defined(__LCM_HVGA_320_480__)
    #ifdef __UI_STYLE_MMI_ANDROID_4_0__
    #define CONFIG_AMR_IDLEAPP_ICON_ORDER                 CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_ORDER, ItemOrderInfo_t, (8 + 16*4), \
    {/*1 Page max is 8*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*2 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*3 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*4 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*5 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}})
    #else
    #define CONFIG_AMR_IDLEAPP_ICON_ORDER                 CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_ORDER, ItemOrderInfo_t, (8 + 20*4), \
    {/*1 Page max is 8*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*2 Page max is 20*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*3 Page max is 20*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*4 Page max is 20*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*5 Page max is 20*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}})
    #endif
#elif defined(__LCM_WVGA__)
    #ifdef __UI_STYLE_MMI_ANDROID_4_0__
    #define CONFIG_AMR_IDLEAPP_ICON_ORDER                 CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_ORDER, ItemOrderInfo_t, (8 + 16*4), \
    {/*1 Page max is 8*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*2 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*3 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*4 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*5 Page max is 16*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}})
    #else
    /*Total page is 5,and firt page item number is 3, other page item num is 12*/
    #define CONFIG_AMR_IDLEAPP_ICON_ORDER                 CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_ORDER, ItemOrderInfo_t, (3 + 12*4), \
    {/*1 Page max is 3*/{0,0},{0,0},{0,0},\
     /*2 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*3 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*4 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*5 Page max is 12*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}})
    #endif
#else
/*Total page is 5,and firt page item number is 8,other page item num is 20*/
    #define CONFIG_AMR_IDLEAPP_ICON_ORDER                 CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_ORDER, ItemOrderInfo_t, (8 + 20*4), \
    {/*1 Page max is 8*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*2 Page max is 20*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*3 Page max is 20*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*4 Page max is 20*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},\
     /*5 Page max is 20*/{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}})

#endif

#define CONFIG_AMR_IDLEAPP_ICON_CURRENT_PAGE          CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_CURRENT_PAGE,s8,1,{-1})

#define CONFIG_AMR_IDLEAPP_ICON_NUM_AT_EVERY_PAGE          CONFIG_DEFINE(CFGIT_IDLEAPP_ICON_NUM_AT_EVERY_PAGE,u8,5,{0,0,0,0,0})

#ifndef __UI_STYLE_MMI_ANDROID_IDLE_MUTEX__
/*Because not mutex,so need devide the CFG Info between drag wdg and desktop wdg */
/*Sotto item is for desktop Wdg and CONFIG_AMR_IDLEAPP_ICON_ORDER above is for drag wdg*/
/*The every page max desktop wdg num is ANDROID_EVERYPAGE_DESKTOPWDG_MAX_NUM*/
#define CONFIG_AMR_IDLEAPP_DESKTOPWDG_ICON_ORDER                 CONFIG_DEFINE(CFGIT_IDLEAPP_DESKTOPWDG_ICON_ORDER, DeskTopWdgInfo_t, (10*5), \
{/*1 Page max is 10*/{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},\
 /*2 Page max is 10*/{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},\
 /*3 Page max is 10*/{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},\
 /*4 Page max is 10*/{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},\
 /*5 Page max is 10*/{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}})
#endif

#ifndef __UI_STYLE_MMI_ANDROID_IDLE_MUTEX__
#define IDLEAPP_AMR_ALL_CONFIG \
                        CONFIG_AMR_IDLEAPP_ICON_ORDER \
                        CONFIG_AMR_IDLEAPP_ICON_CURRENT_PAGE \
                        CONFIG_AMR_IDLEAPP_ICON_NUM_AT_EVERY_PAGE\
                        CONFIG_AMR_IDLEAPP_DESKTOPWDG_ICON_ORDER
#else
#define IDLEAPP_AMR_ALL_CONFIG \
                        CONFIG_AMR_IDLEAPP_ICON_ORDER \
                        CONFIG_AMR_IDLEAPP_ICON_CURRENT_PAGE \
                        CONFIG_AMR_IDLEAPP_ICON_NUM_AT_EVERY_PAGE
#endif

#elif defined(__3D_UI_IDLE_MULTIPAGE__) //__3D_UI_IDLE_MULTIPAGE__

#include "mmi_layout.h"
#include "mmi_clstbl.h"

#define CONFIG_AMR_IDLEAPP_WDG_ACLOCK_POS                    CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_ACLOCK_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_ACLOCK_POS              CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_ACLOCK_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_DCLOCK_POS                    CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_DCLOCK_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_DCLOCK_POS              CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_DCLOCK_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_PAGE_DCLOCK_POS               CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_PAGE_DCLOCK_POS, s16, 2, {IDLEAPP_DEFAULT_POS_WIDGET_PAGECLOCK_X,IDLEAPP_DEFAULT_POS_WIDGET_PAGECLOCK_Y} )
#define CONFIG_AMR_IDLEAPP_WDG_CALENDAR_POS                  CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_CALENDAR_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_CALENDAR_POS            CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_CALENDAR_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_FMRADIO_POS                   CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_FMRADIO_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_FMRADIO_POS             CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_FMRADIO_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_MPLAYER_POS                   CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_MPLAYER_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_MPLAYER_POS             CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_MPLAYER_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_PHOTO_POS                     CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_PHOTO_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_MESSAGE_POS                   CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_MESSAGE_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_PHONEBOOK_POS                 CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_PHONEBOOK_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_OPERATOR_POS                  CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_OPERATOR_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK01_POS              CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_WORLDCLOCK01_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK02_POS              CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_WORLDCLOCK02_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK03_POS              CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_WORLDCLOCK03_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK04_POS              CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_WORLDCLOCK04_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_NOTEPAD_POS                   CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_NOTEPAD_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SEARCH_POS                    CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SEARCH_POS, s16, 2, {0,0} )

#define CONFIG_AMR_IDLEAPP_WDG_ACLOCK_STYLE                  CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_ACLOCK_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_ACLOCK_STYLE            CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_ACLOCK_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_DCLOCK_STYLE                  CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_DCLOCK_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_DCLOCK_STYLE            CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_DCLOCK_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_PAGE_DCLOCK_STYLE             CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_PAGE_DCLOCK_STYLE, s16, 2, {CLSID_DCLOCKDESKTOPWIDGET, 6} )    ///DCLOCK_WDG_STYLE_PAGE
#define CONFIG_AMR_IDLEAPP_WDG_CALENDAR_STYLE                CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_CALENDAR_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_CALENDAR_STYLE          CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_CALENDAR_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_FMRADIO_STYLE                 CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_FMRADIO_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_FMRADIO_STYLE           CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_FMRADIO_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_MPLAYER_STYLE                 CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_MPLAYER_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SMALL_MPLAYER_STYLE           CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SMALL_MPLAYER_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_PHOTO_STYLE                   CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_PHOTO_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_MESSAGE_STYLE                 CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_MESSAGE_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_PHONEBOOK_STYLE               CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_PHONEBOOK_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_OPERATOR_STYLE                CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_OPERATOR_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK01_STYLE            CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_WORLDCLOCK01_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK02_STYLE            CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_WORLDCLOCK02_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK03_STYLE            CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_WORLDCLOCK03_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK04_STYLE            CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_WORLDCLOCK04_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_NOTEPAD_STYLE                 CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_NOTEPAD_STYLE, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_WDG_SEARCH_STYLE                  CONFIG_DEFINE(CFGIT_IDLEAPP_WDG_SEARCH_STYLE, s16, 2, {0,0} )

#define CONFIG_AMR_IDLEAPP_PHONEBOOK_POS                     CONFIG_DEFINE(CFGIT_IDLEAPP_PHONEBOOK_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_PHONEBOOK_HIGHLIGHT_IDX           CONFIG_DEFINE(CFGIT_IDLEAPP_PHONEBOOK_HIGHLIGHT_IDX, u8, 1, 0 )
#define CONFIG_AMR_IDLEAPP_MESSAGE_POS                       CONFIG_DEFINE(CFGIT_IDLEAPP_MESSAGE_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_PHOTO_WIDGET_CURIDX               CONFIG_DEFINE(CFGIT_IDLEAPP_PHOTO_WIDGET_CURIDX, u32, 1, 0 )
#define CONFIG_AMR_IDLEAPP_PHOTO_WIDGET_IMGURL               CONFIG_DEFINE(CFGIT_IDLEAPP_PHOTO_WIDGET_IMGURL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L"ad:/IMAGE/3001.jpg"})
#define CONFIG_AMR_IDLEAPP_MULTIPAGE_CURIDX                  CONFIG_DEFINE(CFGIT_IDLEAPP_MULTIPAGE_CURIDX, u8, 1, 0x02 )

#define CONFIG_AMR_IDLEAPP_CUT_01_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_01_POS, s16, 2, {IDLEAPP_DEFAULT_POS_SHORTCUT_1_X,IDLEAPP_DEFAULT_POS_SHORTCUT_1_Y} )
#define CONFIG_AMR_IDLEAPP_CUT_02_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_02_POS, s16, 2, {IDLEAPP_DEFAULT_POS_SHORTCUT_2_X,IDLEAPP_DEFAULT_POS_SHORTCUT_2_Y} )
#define CONFIG_AMR_IDLEAPP_CUT_03_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_03_POS, s16, 2, {IDLEAPP_DEFAULT_POS_SHORTCUT_3_X,IDLEAPP_DEFAULT_POS_SHORTCUT_3_Y} )
#define CONFIG_AMR_IDLEAPP_CUT_04_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_04_POS, s16, 2, {IDLEAPP_DEFAULT_POS_SHORTCUT_4_X,IDLEAPP_DEFAULT_POS_SHORTCUT_4_Y} )
#define CONFIG_AMR_IDLEAPP_CUT_05_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_05_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_06_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_06_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_07_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_07_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_08_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_08_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_09_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_09_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_10_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_10_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_11_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_11_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_12_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_12_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_13_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_13_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_14_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_14_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_15_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_15_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_16_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_16_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_17_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_17_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_18_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_18_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_19_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_19_POS, s16, 2, {0,0} )
#define CONFIG_AMR_IDLEAPP_CUT_20_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_20_POS, s16, 2, {0,0} )

#define CONFIG_AMR_IDLEAPP_CUT_01_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_01_PROP, s32, 1, {SHORTCUTS_FUNC_PROFILES} )
#define CONFIG_AMR_IDLEAPP_CUT_02_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_02_PROP, s32, 1, {SHORTCUTS_FUNC_CALENDAR} )
#define CONFIG_AMR_IDLEAPP_CUT_03_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_03_PROP, s32, 1, {SHORTCUTS_FUNC_INBOX} )
#define CONFIG_AMR_IDLEAPP_CUT_04_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_04_PROP, s32, 1, {SHORTCUTS_FUNC_PHONEBOOK} )
#define CONFIG_AMR_IDLEAPP_CUT_05_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_05_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_06_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_06_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_07_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_07_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_08_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_08_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_09_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_09_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_10_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_10_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_11_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_11_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_12_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_12_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_13_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_13_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_14_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_14_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_15_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_15_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_16_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_16_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_17_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_17_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_18_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_18_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_19_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_19_PROP, s32, 1, {0} )
#define CONFIG_AMR_IDLEAPP_CUT_20_PROP                       CONFIG_DEFINE(CFGIT_IDLEAPP_CUT_20_PROP, s32, 1, {0} )

#define CONFIG_AMR_IDLEAPP_WIDGET_STATUS                     CONFIG_DEFINE(CFGIT_IDLEAPP_WIDGET_STATUS, u8, DESKTOP_WIDGET_NUM, \
{/* WDG_ACLOCK */          IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_SMALL_ACLOCK */    IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_DCLOCK */          IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_SMALL_DCLOCK */    IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_PAGE_DCLOCK */     IDLEAPP_DEFAULT_WIDGET_PAGECLOCK_EXIST_PAGE, \
 /* WDG_CALENDAR */        IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_SMALL_CALENDAR */  IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_FMRADIO */         IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_SMALL_FMRADIO */   IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_MPLAYER */         IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_SMALL_MPLAYER */   IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_PHOTO */           IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_MESSAGE */         IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_PHONEBOOK */       IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_OPERATOR */        IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_WORLDCLOCK01 */    IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_WORLDCLOCK02 */    IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_WORLDCLOCK03 */    IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_WORLDCLOCK04 */    IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_NOTEPAD */         IDLEAPP_WIDGET_NOT_EXIST, \
 /* WDG_SEARCH */          IDLEAPP_WIDGET_NOT_EXIST } )

#define CONFIG_AMR_IDLEAPP_SHORTCUT_STATUS                   CONFIG_DEFINE(CFGIT_IDLEAPP_SHORTCUT_STATUS, u8, DESKTOP_SHORTCUT_NUM, \
{/* CUT_01 */   IDLEAPP_DEFAULT_SHORTCUT_1_EXIST_PAGE,  \
 /* CUT_02 */   IDLEAPP_DEFAULT_SHORTCUT_2_EXIST_PAGE,  \
 /* CUT_03 */   IDLEAPP_DEFAULT_SHORTCUT_3_EXIST_PAGE,  \
 /* CUT_04 */   IDLEAPP_DEFAULT_SHORTCUT_4_EXIST_PAGE,  \
 /* CUT_05 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_06 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_07 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_08 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_09 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_10 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_11 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_12 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_13 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_14 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_15 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_16 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_17 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_18 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_19 */   IDLEAPP_SHORTCUT_NOT_EXIST,             \
 /* CUT_20 */   IDLEAPP_SHORTCUT_NOT_EXIST } )

#define IDLEAPP_AMR_ALL_CONFIG \
/*Idle Multipage BEGIN*/ \
                        CONFIG_AMR_IDLEAPP_WDG_ACLOCK_POS            \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_ACLOCK_POS      \
                        CONFIG_AMR_IDLEAPP_WDG_DCLOCK_POS            \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_DCLOCK_POS      \
                        CONFIG_AMR_IDLEAPP_WDG_PAGE_DCLOCK_POS       \
                        CONFIG_AMR_IDLEAPP_WDG_CALENDAR_POS          \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_CALENDAR_POS    \
                        CONFIG_AMR_IDLEAPP_WDG_FMRADIO_POS           \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_FMRADIO_POS     \
                        CONFIG_AMR_IDLEAPP_WDG_MPLAYER_POS           \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_MPLAYER_POS     \
                        CONFIG_AMR_IDLEAPP_WDG_PHOTO_POS             \
                        CONFIG_AMR_IDLEAPP_WDG_MESSAGE_POS           \
                        CONFIG_AMR_IDLEAPP_WDG_PHONEBOOK_POS         \
                        CONFIG_AMR_IDLEAPP_WDG_OPERATOR_POS          \
                        CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK01_POS      \
                        CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK02_POS      \
                        CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK03_POS      \
                        CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK04_POS      \
                        CONFIG_AMR_IDLEAPP_WDG_NOTEPAD_POS           \
                        CONFIG_AMR_IDLEAPP_WDG_SEARCH_POS            \
                        CONFIG_AMR_IDLEAPP_WDG_ACLOCK_STYLE          \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_ACLOCK_STYLE    \
                        CONFIG_AMR_IDLEAPP_WDG_DCLOCK_STYLE          \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_DCLOCK_STYLE    \
                        CONFIG_AMR_IDLEAPP_WDG_PAGE_DCLOCK_STYLE     \
                        CONFIG_AMR_IDLEAPP_WDG_CALENDAR_STYLE        \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_CALENDAR_STYLE  \
                        CONFIG_AMR_IDLEAPP_WDG_FMRADIO_STYLE         \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_FMRADIO_STYLE   \
                        CONFIG_AMR_IDLEAPP_WDG_MPLAYER_STYLE         \
                        CONFIG_AMR_IDLEAPP_WDG_SMALL_MPLAYER_STYLE   \
                        CONFIG_AMR_IDLEAPP_WDG_PHOTO_STYLE           \
                        CONFIG_AMR_IDLEAPP_WDG_MESSAGE_STYLE         \
                        CONFIG_AMR_IDLEAPP_WDG_PHONEBOOK_STYLE       \
                        CONFIG_AMR_IDLEAPP_WDG_OPERATOR_STYLE        \
                        CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK01_STYLE    \
                        CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK02_STYLE    \
                        CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK03_STYLE    \
                        CONFIG_AMR_IDLEAPP_WDG_WORLDCLOCK04_STYLE    \
                        CONFIG_AMR_IDLEAPP_WDG_NOTEPAD_STYLE         \
                        CONFIG_AMR_IDLEAPP_WDG_SEARCH_STYLE          \
                        CONFIG_AMR_IDLEAPP_PHONEBOOK_POS             \
                        CONFIG_AMR_IDLEAPP_PHOTO_WIDGET_CURIDX       \
                        CONFIG_AMR_IDLEAPP_PHOTO_WIDGET_IMGURL       \
                        CONFIG_AMR_IDLEAPP_MULTIPAGE_CURIDX          \
                        CONFIG_AMR_IDLEAPP_WIDGET_STATUS             \
                        CONFIG_AMR_IDLEAPP_CUT_01_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_02_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_03_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_04_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_05_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_06_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_07_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_08_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_09_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_10_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_11_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_12_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_13_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_14_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_15_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_16_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_17_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_18_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_19_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_20_POS                \
                        CONFIG_AMR_IDLEAPP_CUT_01_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_02_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_03_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_04_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_05_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_06_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_07_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_08_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_09_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_10_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_11_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_12_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_13_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_14_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_15_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_16_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_17_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_18_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_19_PROP               \
                        CONFIG_AMR_IDLEAPP_CUT_20_PROP               \
                        CONFIG_AMR_IDLEAPP_PHONEBOOK_HIGHLIGHT_IDX   \
                        CONFIG_AMR_IDLEAPP_MESSAGE_POS               \
                        CONFIG_AMR_IDLEAPP_SHORTCUT_STATUS

#else

#define IDLEAPP_AMR_ALL_CONFIG

#endif //__3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_IDLEAPP_CFG__H__
