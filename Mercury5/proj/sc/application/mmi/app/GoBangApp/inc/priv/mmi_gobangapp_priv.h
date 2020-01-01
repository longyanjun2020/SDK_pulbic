#ifndef __MMI_GOBANGAPP_PRIV_H__
#define __MMI_GOBANGAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_gobangapp_id.h"
#include "mmi_gobangapp.h"
#include "gobangapp_resource.h"
#include "mmi_wdg_common_interface.h"

// CELL CONTENT
#define C_EMPTY  	0
#define C_MARKX  	1	///player is X
#define C_MARKO     2	///robot is O
#define C_EDGE  	3

#define WINNER_NONE 0xFF

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;
	IImage *pWhitePiece,*pBlackPiece;
	IImage *pWhiteWin,*pBlackWin;
	IImage *pBlackFocus;
	u32 lastBlackIdx;
	u32 nTotalRow;
	u32 nTotalCol;
    void* pVoid;
} GoBangAppData_t;

typedef struct
{
    IWidget *pGridMenu;
    IWidget *pRegBtn;
    IWidget *pOppoFirstBtn;
    IWidget *pQuitBtn;
    IWidget *pResetBtn;
    IWidget *pInfoTxt;
}GoBangMainWdgList;


boolean GoBangStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret GoBangDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
static void GoBangPressCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret GoBangMainWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret GoBangMainWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
void _PieceAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void _GoBangLoadRes(GoBangAppData_t *pThis);

void _GoBangGridSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _GoBangRegreBtnClick(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void _GoBangOppoFirstBtnClick(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void _GoBangQuitBtnClick(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void _GoBangResetBtnClick(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

int _GoBangRobotMove(GoBangAppData_t* pThis,u8 *nHor,u8 *nVer);
void _GoBangRobotInit(GoBangAppData_t* pThis);
void _GoBangRobotReset(GoBangAppData_t* pThis);
void _GoBangRobotDestroy(GoBangAppData_t* pThis);
unsigned int _GoBangRobotFirst(GoBangAppData_t* pThis);
int _GoBangGet(GoBangAppData_t* pThis,int x, int y);
int _GoBangPlayerMove(GoBangAppData_t* pThis,int x, int y);
int _GoBangWinner(GoBangAppData_t* pThis);
unsigned char _GoBangInWinSeq(GoBangAppData_t* pThis, u32 idx);
void _GoBangRegret(GoBangAppData_t* pThis);

#endif /*__MMI_GOBANGAPP_PRIV_H__*/
