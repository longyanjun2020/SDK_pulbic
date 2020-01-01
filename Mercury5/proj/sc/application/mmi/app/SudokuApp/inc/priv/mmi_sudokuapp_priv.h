#ifndef __MMI_SUDOKUAPP_PRIV_H__
#define __MMI_SUDOKUAPP_PRIV_H__

#include "mmi_baseapplet.h"
#include "mmi_sudokuapp_id.h"
#include "sudokuapp_resource.h"
#include "mmi_common_rai_id.h"
#include "mmi_wdg_common_interface.h"

#define SUDOKU_TIME_INTERVAL 1000
#define SUDOKU_TIME_MAX 1800

/*=============================================================*/
// Global function definition
/*=============================================================*/
typedef struct
{
    IWidget *pMainQuitButtonWidget;
	IWidget *pPlayCubeListWidget;
    IWidget *pPlayCubeTextWidget;
    IWidget *pMainStartButtonWidget;
    IWidget *pPlaySucessWidget;
    IWidget *pPlayFailWidget;
    IWidget *pPlayTimerTxtWdg;
    IWidget *pMainNo1ImgWidget;
    IWidget *pMainNooTxtWidget;
    IWidget *pOperandListWidget;
    IWidget *pOperandButtonWidget;
    IWidget *pPlayQuitButtonWidget;
	IWidget *pPlayFadeOutWidget;
}SudokuViewWdgList_t;

typedef struct
{
    SudokuViewWdgList_t tWdgList;
}SudokuWndData_t;

typedef struct
{
    SudokuViewWdgList_t tWdgPlayList;	
    MAE_WChar strCurrentInput[20];
}SudokuWndPlayData_t;    

typedef struct
{
    APPLET_BASE_ELEMENTS;
} SudokuAppData_t;

boolean SudokuStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret SudokuConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret SudokuDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SudokuStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SudokuSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SudokuResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SudokuKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
static MAE_Ret _SudokuWndCreateMainView(void *pCusHandle, SudokuViewWdgList_t *pWdgList);
//static MAE_Ret _SudokuWndSetMainView(void *pCusHandle, SUDOKU_WND_MAIN_t *pViewRC , SudokuViewWdgList_t *pWdgList);
static MAE_Ret _SudokuWndCreatePlayView(void *pCusHandle, SudokuViewWdgList_t *pWdgList);
//static MAE_Ret _SudokuWndSetPlayView(void *pCusHandle, SUDOKU_WND_PLAY_t *pViewRC , SudokuViewWdgList_t *pWdgList);
MAE_Ret SudokuPlayWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SudokuMainWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SudokuWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret SudokuWndCreatePlay(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#endif /*__MMI_HELLOWORLDAPP_PRIV_H__*/
