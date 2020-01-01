/* ===========================================================*/
// Description 
/* ===========================================================*/
/**
*    There are two types of Progress widget: one is repeated rotation and the other is 
*    non-repeated rotation. Repeated rotation is to display a progress of a task which 
*    has been completed. Non-repeated rotation is to let users know the progress is not
*    yet completed and is executing now, which needs users to wait for. The sketch are as 
*    shown belows: 
*
*     ex: Progress widget
*    +---------------------+          
*    |#|#|#|#| | | | | | | |   -->  non-repeated rotation type 
*    +---------------------+          
*       ^: The current executed stage.
*
*    +----------------------+
*    | | | |#|#|#| | | | |  |   -->  repeated rotation type
*    +----------------------+
*              ^: It does not mean the progress has been completed, 
*                  because it will be repeated back to the original position.
*/

#ifndef __MMI_WDG_PROGRESS_H__
#define __MMI_WDG_PROGRESS_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_retcode.h"
#include "mmi_mae_window.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/** WdgProgressCfgData_t
*
* @brief    bRepeat:        Set True or False for auto repeat mode, refer to the comment of WdgProgressSetRepeat.
*           bAutoProgress:  Set True or False for auto progress, refer to the comment of WdgProgressSetAutoOnOff.
*           nTotalPNum:     Set Total Progress Number, ex 10 tasks need to process, the value is 10.
*           nCellWidth:     Set width of one progress cell.
*           nCellTotalNum:  Set total number of progress cell.
*           nCellRepeatNum: Set repeat cell number we need.
*
*           1, Rule 1: The length of progress bar depends on CellTotalNum and nCellWidth(nCellTotalNum * nCellWidth).
*           2, Rule 2: Cell display mode is replaced by FG and BG if set image.
*           3, Rule 3: If bRepeat is true, nTotalPNum is not functional.
*           4, Example:
*           While nCellTotalNum = 10, nCellWidth = 4, we get a progress bar with 40 pixel length.
*           Case (1) bAutoProgress is TRUE, bRepeat is FALSE, nTotalPNum is 20 ==> progress move 20 times reach 100%.
*           Case (2) bAutoProgress is TRUE, bRepeat is FALSE, nTotalPNum is 10 ==> progress move 10 times reach 100%.
*
*/
typedef struct
{
    boolean bRepeat;
    boolean bAutoProgress;
    u16     nTotalPNum;
    u16     nCellWidth;
    u16     nCellTotalNum;
    u16     nCellRepeatNum;
}WdgProgressCfgData_t;

typedef enum e_Progress_Status
{
    PROGRESS_E_NEXT_STEP=0x01,
    PROGRESS_E_FINAL=0x02,
    PROGRESS_E_TOTAL_CHANGED=0x04,
    PROGRESS_E_CURPOS_CHANGED=0x08,
    PROGRESS_E_STOP=0x10,
}ProgressStatus_e;

/** ProgressData_t
*
* @brief               
*
*/
typedef struct{
    u8 ProgressStatus;
    u16 ProgressType;
    u16 nTotal;         ///< Progress total       
    u16 nPos;           ///< current position 0-based
}ProgressData_t;

/** ColorData_t
*
* @brief    
*
*/
typedef struct{
	u32 nColorR;
	u32 nColorG;
	u32 nColorB;
}ColorData_t;

/** ProgressCellInfo
*
* @brief    
*
*/
typedef struct{
    u16 CellWidth;
    u16 CellNum;
    u16 RepeatNum;
}ProgressCellInfo;

enum e_Progress_Type
{
    PROGRESS_E_START=0x00,
    PROGRESS_E_MANUAL=0x00, //MANUAL Progress, no repeat
    PROGRESS_E_AUTO=0x01,   //Auto Progress
    PROGRESS_E_REPEAT=0x02, //Repeat Progress
    PROGRESS_E_TOTAL=0x04
};

#define PROGRESSWDG_DEF_CELL_NUM    10
#define PROGRESSWDG_DEF_CELL_WIDTH  10
#define PROGRESSWDG_DEF_MIN_CELL_WIDTH  5
#define PROGRESSWDG_DEF_REPEAT_NUM  3


#define PROGRESSDATA_Init(PD, PS, PT, nT, nP) \
	do{ \
		(PD)->ProgressStatus=PS; \
		(PD)->ProgressType=PT; \
		(PD)->nTotal=nT; \
		(PD)->nPos=nP; }while(0)

/** PfnWdgProgressChange
* @brief      CB register by "PfnWdgProgressChange"
*             and will be triggered when widget change the progress.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pProgressData     The info can get when widget change the progress, refer to ProgressData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgProgressChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ProgressData_t *pProgressData, IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/

/** WdgProgressCreateForWnd
* @brief        Progress widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWdgId              The widget unique ID of window
* @param[in]    pData               Widget Common Data, refer to WdgProgressCfgData_t.
*                                   If set pSize = NULL : means you want Default Value;
*
* @retval       The pointer of Progress      Success.
* @retval       NULL                         Failed.
*
*/
IWidget* WdgProgressCreateForWnd
(
    HWIN                hWin,
    Pos_t                      *pPos,
    WidgetSize_t               *pSize,
    u16                         nWdgId,
    WdgProgressCfgData_t       *pData
);

/*=============================================================*/
/** WdgProgressCreate
* @brief        Create Progress widget
*
* @retval       The pointer of Progress     Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgProgressCreate
(
    void
);

/** WdgProgressSetRepeat
* @brief         Set the property for auto repeat progress;
*                Repeat is TRUE means progress percentage will go to 0% while reach 100%.
*                Repeat is FALSE means progress percentage won't go to 0% while reach 100%.
*                While in auto repeat mode, AP developer need to stop progress manually.
*
* @param[in]     pProgress         The pointer of IWidget interface object
* @param[in]     bProgressRepeat   Set True or False for auto repeat progress
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetRepeat
(
    IWidget                 *pProgress,
    boolean                 bProgressRepeat
);

/** WdgProgressSetFgImage
* @brief         Set the foreground IImage
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     pImage            The foreground IImage
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgProgressSetFgImage
(
    IWidget                 *pProgress,
    IImage                  *pImage
);

/** WdgProgressSetBgImage
* @brief         Set the background IImage
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     pImage         The background IImage
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetBgImage
(
    IWidget                 *pProgress,
    IImage                  *pImage
);

/** WdgProgressSetFgImageFileName
* @brief         Set the foreground Image Filename
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     pFGImageFile   The foreground Image Filename
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetFgImageFileName
(
    IWidget                 *pProgress,
    u16                      *pFGImageFile
);

/** WdgProgressSetBgImageFileName
* @brief         Set the background Image Filename
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     pBGImageFile   The background Image Filename
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetBgImageFileName
(
    IWidget                 *pProgress,
    u16                      *pBGImageFile
);

/** WdgProgressSetFgBorderColor
* @brief         Set the foreground rectangle Border Color
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     nColor         The foreground rect Border Color; can be set by MAKE_RGB or MAKE_RGBA.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetFgBorderColor
(
    IWidget                 *pProgress,
    RGBColor_t              nColor
);

/** WdgProgressSetBgBorderColor
* @brief         Set the background rectangle Border Color
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     nColor         The background rect Border Color; can be set by MAKE_RGB or MAKE_RGBA.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetBgBorderColor
(
    IWidget                 *pProgress,
    RGBColor_t              nColor
);

/** WdgProgressSetFgFillColor
* @brief         Set the foreground rectangle Fill Color
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     nColor         The foreground rect Fill Color; can be set by MAKE_RGB or MAKE_RGBA.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetFgFillColor
(
    IWidget                 *pProgress,
    RGBColor_t              nColor
);

/** WdgProgressSetBgFillColor
* @brief         Set the background rectangle Fill Color
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     nColor         The background rect Fill Color; can be set by MAKE_RGB or MAKE_RGBA.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetBgFillColor
(
    IWidget                 *pProgress,
    RGBColor_t              nColor
);

/** WdgProgressSetFgRectFlag
* @brief         Set Flag of rectangle for the foreground.
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     nFlag          the foreground rect Flag, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetFgRectFlag
(
    IWidget                 *pProgress,
    u32                     nFlag
);

/** WdgProgressSetBgRectFlag
* @brief         Set Flag of rectangle for the background.
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     nFlag          the background rect Flag, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetBgRectFlag
(
    IWidget                 *pProgress,
    u32                     nFlag
);

/** WdgProgressSetTotal
* @brief         Set the total number of work should be carried out,
*                for example: To delete a total of 10 files, and set the Total to 10
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     nTotalPNum     The Total Progress Number
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetTotal
(
    IWidget                 *pProgress,
    u16                     nTotalPNum
);

/** WdgProgressSetCurPos
* @brief         Set Current Progress Position,
*                for example: The number of  deleted files is 6, and set the nCurpos to 6
*
* @param[in]     pProgress      The pointer of IWidget interface object
* @param[in]     nCurpos        The Current Progress Position
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgProgressSetCurPos
(
    IWidget                 *pProgress,
    u16                     nCurpos
);

/** WdgProgressSetPreferCellWidth
* @brief         Set the prefer width of each cell rect in the progress bar
*
* @param[in]     pProgress         The Progress widget which want to set
* @param[in]     nPreferCellWidth  The prefer width of each cell rect in the progress bar (unit is pixel)
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetPreferCellWidth
(
    IWidget                 *pProgress,
    u16                     nPreferCellWidth
);

/** WdgProgressSetPreferCellTotalNum
* @brief         Set the prefer total number of cell rect in the progress bar
*
* @param[in]     pProgress               The Progress widget which want to set
* @param[in]     nPreferCellTotalNum     The prefer total number of cell rect in the progress bar
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetPreferCellTotalNum
(
    IWidget                 *pProgress,
    u16                     nPreferCellTotalNum
);

/** WdgProgressSetPreferCellRepeatlNum
* @brief         Set if the progress type is auto repeat, the prefer repeat cell number.
*                The repeat Cell Number in foreground should not be larger than the actual Cell Total Number,
*                so User's setting is the preferred value.
*
* @param[in]     pProgress               The Progress widget which want to set
* @param[in]     nPreferCellRepeatNum    The prefer repeat cell number >0
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetPreferCellRepeatlNum
(
    IWidget                 *pProgress,
    u16                     nPreferCellRepeatNum
);

/** WdgProgressSetAutoOnOff
* @brief         Set the property of turn On/Off the auto progress,
*                TRUE : means Current progress Position is automatically changed.
*
* @param[in]     pProgress             The pointer of IWidget interface object
* @param[in]     bAutoProgressOnOff    The property of turn On/Off the auto progress
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgProgressSetAutoOnOff
(
    IWidget                 *pProgress,
    boolean                 bAutoProgressOnOff
);

/** WdgProgressIsRepeat
* @brief         Get the property for auto repeat progress
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval        boolean        result of the property for auto repeat progress
*
*/
boolean WdgProgressIsRepeat
(
    IWidget                 *pProgress
);

/** WdgProgressGetFgBorderColor
* @brief         Get the foreground rect Border Color
*
* @param[in]     pProgress      The pointer of IWidget interface object

* @retval        RGBColor_t     result of the foreground rect Border Color
*
*/
RGBColor_t WdgProgressGetFgBorderColor
(
    IWidget                 *pProgress
);

/** WdgProgressGetBgBorderColor
* @brief         Get the background rect Border Color
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @return        RGBColor_t
*
*/
RGBColor_t WdgProgressGetBgBorderColor
(
    IWidget                 *pProgress
);

/** WdgProgressGetFgFillColor
* @brief         Get the foreground rect Fill Color
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval        RGBColor_t     RGBColor_t with result of the foreground rect Fill Color
*/
RGBColor_t WdgProgressGetFgFillColor
(
    IWidget                 *pProgress
);

/** WdgProgressGetBgFillColor
* @brief         Get the background rect Fill Color
*
* @param[in]    pProgress      The pointer of IWidget interface object
*
* @retval       RGBColor_t    result of the background rect Fill Color
*
*/
RGBColor_t WdgProgressGetBgFillColor
(
    IWidget                 *pProgress
);

/** WdgProgressGetFgRectFlag
* @brief         Get the foreground rect Flag
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval        u32            result of the foreground rect Flag
*/
u32 WdgProgressGetFgRectFlag
(
    IWidget                 *pProgress
);

/** WdgProgressGetBgRectFlag
* @brief         Get the background rect Flag
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval        u32            result of the background rect Flag
*
*/
u32 WdgProgressGetBgRectFlag
(
    IWidget                 *pProgress
);

/** WdgProgressGetTotal
* @brief         Get Total Progress Number
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval        u16            result of the Total Progress Number
*/
u16 WdgProgressGetTotal
(
    IWidget                 *pProgress
);

/** WdgProgressGetCurPos
* @brief         Get Current Progress Position
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval        u16            Current Progress Position
*
*/
u16 WdgProgressGetCurPos
(
    IWidget                 *pProgress
);

/** WdgProgressGetCellWidth
* @brief         Get the width of each cell rect in the progress bar
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval       u16             result of the Cell Width
*/
u16 WdgProgressGetCellWidth
(
    IWidget                 *pProgress
);

/** WdgProgressGetCellTotalNum
* @brief         Get the total number of cell rect in the progress bar
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval        u16            result of the Cell Total Num
*/
u16 WdgProgressGetCellTotalNum
(
    IWidget                 *pProgress
);

/** WdgProgressGetCellRepeatNum
* @brief         Get if the progress type is auto repeat, the repeat cell number
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval        u16            result of the Cell Repeat Num
*
*/
u16 WdgProgressGetCellRepeatNum
(
    IWidget                 *pProgress
);

/** WdgProgressIsAutoProgress
* @brief         Get the property of turn On/Off the auto progress
*
* @param[in]     pProgress      The pointer of IWidget interface object
*
* @retval        boolean        result of the property of turn On/Off the auto progress
*
*/
boolean WdgProgressIsAutoProgress
(
    IWidget                 *pProgress
);

/** WdgProgressRegProgressChangeCb
* @brief         Register callback : CB will be triggered for widget change the progress.
*
* @param[in]     pProgress      The Progress widget which want to set callback
* @param[in]     pfn            callback function
* @param[in]     pUserData       User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgProgressRegProgressChangeCb
(
    IWidget                 *pProgress,
    PfnWdgProgressChange     pfn,
    void                    *pUserData
);

/** WdgProgressDeregProgressChangeCb
* @brief         Deregister callback
*
* @param[in]     pProgress      The Progress widget which want to unregister callback
* @param[in]     pfn            callback function
* @param[in]     pUserData       User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgProgressDeregProgressChangeCb
(
    IWidget                 *pProgress,
    PfnWdgProgressChange     pfn,
    void                    *pUserData
);

#endif //__MMI_WDG_PROGRESS_H__
/*=============================================================*/
// end of file
