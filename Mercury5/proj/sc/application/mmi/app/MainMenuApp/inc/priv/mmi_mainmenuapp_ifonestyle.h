/*
 *	file: "mmi_mainmenuapp_ifonestyle.h"
 *	author: sunny wang
*/
#ifndef __MMI_MAINMENUAPP_IFONESTYLE__
#define __MMI_MAINMENUAPP_IFONESTYLE__
#if defined (__UI_STYLE_MMI_IFONE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)
#include "mmi_mainmenuapp_priv.h"
#include "mmi_mainmenuapp.h"
#include "mmi_mainmenuapp_view_id.h"
#include "mmi_mae_interfacemodel.h"
#include "mmi_wdg_image_text_image.h"
#include "mmi_mae_helper.h"
#include "mmi_wdg_transition.h"
#include "mmi_wdg_list.h"
#include "mmi_offapp.h"
#include "mmi_keyguardapp.h"
#include "mmi_mae_vectormodel.h"
#include "mae_decoratorbase.h"
#include "mae_widget_common.h"

//Ifone common options
#define     MAINMENUAPP_IFONEMENUFOCUS_INDEX_NULL       (-1)		//
#define     MAINMENUAPP_IFONEMENUFOCUS_INDEX_FOLDER     (-2)

#define IFONE_MENU_TRANS_DURATION		300
#define IFONE_MENU_SWITCHPAGE_TRANS_DURATION		300
#define IFONE_MENU_RELEASEICON_ANIM_DURATION	20
#define IFONE_MENU_RELEASEICON_ANIM_PHASE		2
#define IFONE_MENU_RELEASEICON_ANIM_MAXNUM	2
#define MISS_EVENT_INDICATOR_MAX_TEXT	3
#define IFONE_MOVE_AINM_DURATION	20
#define IFONE_MOVE_ANIM_PHASE	2
#define IFONE_FLYINEFFECT_ANIMATION_PHASE 4
#define IFONE_FLYINEFFECT_ANIMATION_TIMER 1

#define IFONE_SHAKE_TIME_INTERVAL 	50 // for IFONEWDG_ANIMSTYLE_MOVE, 200 for IFONEWDG_ANIMSTYLE_CHANGEANGLE
#define IFONE_FOCUS_TIME_INTERVAL 	500
#define IFONE_FOLDER_OPENCLOSE_ANIM_TIMER 1
//Ifone layout options:
#define MAINMENU_IMG_GLASS_WIDTH	125
#define MAINMENU_IMG_GLASS_HEIGHT	107
#define MAINMENU_IMG_GLASS_SHIFT_X 61
#define MAINMENU_IMG_GLASS_SHIFT_Y 47

#ifdef __LCM_HVGA_320_480__
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_WIDTH  MAIN_DEFVIEW_WIDTH
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_HEIGHT  42
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_X  0
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_Y  5
#define MAINMENUAPP_IFONE_FOLDERNAME_PADDING MAKE_PADDING_SIZE(20,0,0,0)
#elif defined(__LCM_WVGA__)
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_WIDTH  MAIN_DEFVIEW_WIDTH
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_HEIGHT  50
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_X  0
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_Y  0
#define MAINMENUAPP_IFONE_FOLDERNAME_PADDING MAKE_PADDING_SIZE(20,0,0,0)
#else
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_WIDTH  MAIN_DEFVIEW_WIDTH
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_HEIGHT  30
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_X  0
#define MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_Y  0
#define MAINMENUAPP_IFONE_FOLDERNAME_PADDING MAKE_PADDING_SIZE(20,0,0,0)
#endif

#define MAINMENUAPP_IFONE_CLOSEFOLDER_BUTTONWDG_WIDTH  30
#define MAINMENUAPP_IFONE_CLOSEFOLDER_BUTTONWDG_HEIGHT  30
#define MAINMENUAPP_IFONE_CLOSEFOLDER_BUTTONWDG_X  280
#define MAINMENUAPP_IFONE_CLOSEFOLDER_BUTTONWDG_Y  10

#define MAINMENUAPP_IFONE_INDICATE_IMAGEWDG_WIDTH 24
#define MAINMENUAPP_IFONE_INDICATE_IMAGEWDG_HEIGHT 13

#define MAINMENUAPP_IFONE_FOLDER_WDGOFFSET_Y    (MAINMENUAPP_IFONE_FOLDERNAME_INPUTWDG_HEIGHT - RS_MAINMENUAPP_IFONE_GRID_Y_OFFSET)
#define MAINMENUAPP_IFONE_FOLDER_BUTTOM_LIMIT_Y    (RS_MAINMENUAPP_IFONE_GRID_Y_OFFSET+RS_IFONEWIDGET_HEIGHT+MAINMENUAPP_IFONE_FOLDER_WDGOFFSET_Y+RS_MAINMENUAPP_IFONE_GRID_Y_OFFSET+(RS_IFONEWIDGET_HEIGHT+MAINMENUAPP_IFONE_GRID_ROW_GAP)*3)

#define OPENCLOSE_FOLDER_STEP_HEIGHT 20

enum
{
	IFONE_STYLE_MAIN_FRAME,
	IFONE_STYLE_SHORTCUT_FRAME
};
typedef u8 MainMenuIFoneFrameType_e;

typedef struct
{
    boolean bOpenFolder;
    s32 nUpImagePos_Y;
    s32 nDownImagePos_Y;
}IfoneOpenCloseFloderData_t;

typedef struct
{
    IWidget* pIWidget;
    IWidget* pITargetContainer;
    Pos_t tTargetPos;
    u8 nPhase;
}IfonMovePosAnimData_t;

void MainMenuConfigItemUpdateCB(void *pUserData, SrvCfgItemStatusChangeType_e eChangeType, SrvCfgItemUpdateResult_t uResult);

void MainMenuIfoneCalcSCItemPos(MMI_MAINMENUAPP* pThis);
void MainMenuIfoneFreeWdgInfo(void *pData, IBase *pOwner);
void MainMenuIfoneLoadMenuItem(MMI_MAINMENUAPP *pThis);
void MainMenuIfoneShowMenuItem(MMI_MAINMENUAPP *pThis, u32 nPageIndex);
void MainMenuIfoneReleaseMenuItem(MMI_MAINMENUAPP *pThis);

boolean MainMenuIfoneDefaultHandler(MAEEvent_t Evt, u32 lParam, u32 dParam);
boolean MainMenuIfoneEndKeyEvtHdl(MMI_MAINMENUAPP *pThis, s32 nKeyCode);
void MainMenuIfoneKeyPressEvtHdl(MMI_MAINMENUAPP *pThis, s32 param1, s32 param2);
void MainMenuIfoneTSMoveEvtHdl(MMI_MAINMENUAPP *pThis, s32 param1, s32 param2);
void MainMenuIfoneTSReleaseEvtHdl(MMI_MAINMENUAPP *pThis, s32 param1, s32 param2);
void MainMenuIfoneTSPressEvtHdl(MMI_MAINMENUAPP *pThis, s32 param1, s32 param2);

void MainMenuIfoneSetPageInfo(MMI_MAINMENUAPP *pThis);
void MainMenuIfonePrepareNewIfonePage(MMI_MAINMENUAPP *pThis,u32 nPageIndex, IWidget** pITargetContainer);
void MainMenuIfonePageInfoEvtHdlFree(MMI_MAINMENUAPP *pThis);
u32 MainMenuIfoneCalculateTotalPage(MMI_MAINMENUAPP *pThis);
boolean MainMenuIfonePageInfoEvtHdl(void *pUserData, MAE_EventId evt, u32 param1, u32 param2);

void MainMenuIfoneReleaseiFoneViewObject(MMI_MAINMENUAPP *pThis);


void MainMenuIfonePrepareMainFrameWidget(MMI_MAINMENUAPP *pThis,u32 nPageIndex);
#ifndef __WIDGET_DISABLE_TRANSITION__
void MainMenuIfoneTransitionModelListener(void *pUserData, ModelEvent_t *pMdlEvent);
#endif
void MainMenuIfoneMoveWidgetPositonAnim(void*pOwner);
void MainMenuIfoneSetFocusByKeyEvent(MMI_MAINMENUAPP *pThis, u32 KeyID);
void MainMenuIfoneUpdateBGImage(MMI_MAINMENUAPP *pThis);
void MainMenuIfoneRefreshMenuItems(MMI_MAINMENUAPP *pThis);
void MainMenuIfoneMoveWidgetToContainer(MMI_MAINMENUAPP *pThis,IWidget* pWidget, IWidget* pIDestContainer, Pos_t * tPos);
boolean MainMenuIfoneTransWdgEvtHdl(void *pUserData, MAE_EventId evt, u32 param1, u32 param2);
void MainMenuIfoneBreakGlassEntry(MMI_MAINMENUAPP *pThis,s32 Posx, s32 Posy);
void MainMenuIfoneFallDownEntry(MMI_MAINMENUAPP *pThis);
void MainMenuIfoneFallDownExit(void* pOwner);
void MainMenuIfoneGetSrvCfg(MMI_MAINMENUAPP *pThis);
void MainMenuIfoneInit(MMI_MAINMENUAPP *pThis);
boolean MainMenuIfoneStopCB(MMI_MAINMENUAPP *pThis);
MAE_Ret MainmenuIfoneUpdateWallpaper(MMI_MAINMENUAPP* pThis, IWidget* pIDestWdg);
void MainmenuIfone_StopAllMenuEffect(MMI_MAINMENUAPP* pThis);
void MainmenuIfoneFlyInEffectEntry(MMI_MAINMENUAPP *pThis);
boolean MainmenuIfoneFolderHandleEvent(IApplet *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
void MainmenuIfone_StartLoadMenuItem(MMI_MAINMENUAPP* pThis, MainmenuIfoneInitWndData_t* pIfoneInitWndData);
void MainmenuAppIfoneHandleTsMoveEvtCB(void* pUser);
void _MainmenuIfone_LoadMenuItemCB(void * pUser, void* pData);
boolean MainMenuIfoneUpdataFolderName(MMI_MAINMENUAPP *pThis);
void MainMenuIfoneInfoDialogTimerCB(void *pUserData);
MAE_Ret MainMenuIfoneInfoDialogCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
#endif //__UI_STYLE_MMI_IFONE__
#endif /*__MMI_MAINMENUAPP_IFONESTYLE__*/
