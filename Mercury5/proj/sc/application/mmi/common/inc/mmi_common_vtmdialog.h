/*****************************************************************************************
* @common_dialog.h
*
* Comment: 
*
* @version:0.0.1  @ 2009.11.17 
*****************************************************************************************/
#ifndef __common_dialog__H
#define __common_dialog__H
//*******************************************************************//
#include "mmi_mae_common_def.h"
#include "mmi_mae_widget.h"
enum //VolumeSetDialog_enum
{
    eCOMMON_VOLUMEDIALOG_BGWIDGET2=0x1100,
    eCOMMON_VOLUMEWIDGET3,
    VolumeSetDialog_End
}; //VolumeSetDialog_enum
typedef struct VolumeSetDialogWdgList_t_
{
    IWidget *pBgWdg;
    IWidget *pVolumeWdg;
}VolumeSetDialogWdgList_t;

typedef struct VolumeSetDialogData_t_
{
    u32 nBGImgId;
    u32 nVolumeImgId;
}VolumeSetDialogData_t;

typedef struct VolumeSetDialogCB_t_
{
    void* pCB;
}VolumeSetDialogCB_t;

//MAE_Ret CreateVolumeSetDialog(WndHandle_t *pWndHdl, VolumeSetDialogWdgList_t *pWdgList, VolumeSetDialogData_t *pData, VolumeSetDialogCB_t *pCB);
//*******************************************************************//
enum //RedialDialog_enum
{
    eCOMMON_REDIALDIALOG_BGWIDGET4=0x1100,
    eCOMMON_REDIALDIALOG_IMAGEWIDGET5,
    eCOMMON_DIALOG_TEXTWIDGET6,
    eCOMMON_REDIALDIALOG_PROGRESSWDG7,
    RedialDialog_End
}; //RedialDialog_enum
typedef struct RedialDialogWdgList_t_
{
    IWidget *pBgWdg;
    IWidget *pImageWdg;
    IWidget *pTextWdg;
    IWidget *pProgressWdg;
}RedialDialogWdgList_t;

typedef struct RedialDialogData
{
    u32 nBGImgId;
    u32 nVolumeImgId;
}RedialDialogData_t;

typedef struct RedialDialogCB
{
    void* pCB;
}RedialDialogCB_t;
//MAE_Ret CreateRedailDialog(WndHandle_t *pWndHdl, RedailDialog_WdgList *pWdgList,RedailDialogData_t *pData, RedailDialogCB_t *pCB);

//*******************************************************************//
enum //NormalDialog_enum
{
    eCOMMON_DIALOG_BGWIDGET8=0x1100,
    eCOMMON_DIALOG_IMAGEWIDGET9,
    eCOMMON_DIALOG_TEXTWIDGET10,
    NormalDialog_End
}; //NormalDialog_enum
typedef struct NormalDialogWdgList_t_
{
    IWidget *pBgWdg;
    IWidget *pImageWdg;
    IWidget *pTextWdg;
}NormalDialogWdgList_t;

typedef struct NormalDialogData_t_
{
    u32 nBGImgId;
    u32 nVolumeImgId;
}NormalDialogData_t;

typedef struct NormalDialogCB_t_
{
    void* pCB;
}NormalDialogCB_t;
//MAE_Ret CreateNormalDialog(WndHandle_t *pWndHdl, NormalDialogWdgList_t *pWdgList,NormalDialogData_t *pData, NormalDialogCB_t *pCB);

//*******************************************************************//
enum //WaitingDialog_enum
{
    eCOMMON_DIALOG_BGWIDGET11=0x1100,
    eCOMMON_DIALOG_TITLETEXTWIDGET12,
    eCOMMON_DIALOG_IMAGEWIDGET13,
    eCOMMON_DIALOG_TEXTWIDGET14,
    WaitingDialog_End
}; //WaitingDialog_enum
typedef struct WaitingDialogWdgList_t_
{
    IWidget *pBgWdg;
    IWidget *pTitleWdg;
    IWidget *pImageWdg;
    IWidget *pTextWdg;
}WaitingDialogWdgList_t;

typedef struct WaitingDialogData
{
    u32 nBGImgId;
    u32 nVolumeImgId;
}WaitingDialogData_t;

typedef struct WaitingDialogCB
{
    void* pCB;
}WaitingDialogCB_t;
//MAE_Ret CreateWaitingDialog(WndHandle_t *pWndHdl, WaitingDialog_WdgList *pWdgList,WaitingDialogData_t *pData, WaitingDialogCB_t *pCB);

//*******************************************************************//
enum //ProcessDialog_enum
{
    eCOMMON_DIALOG_BGWIDGET15=0x1100,
    eCOMMON_DIALOG_TITLETEXTWIDGET16,
    eCOMMON_DIALOG_PROGRESSWIDGET17,
    eCOMMON_DIALOG_TEXTWIDGET18,
    ProcessDialog_End
}; //ProcessDialog_enum
typedef struct ProcessDialogWdgList_t_
{
    IWidget *pBgWdg;
    IWidget *pImageWdg;
    IWidget *pTitleWdg;
    IWidget *pProgressWdg;
    IWidget *pTextWdg;
}ProcessDialogWdgList_t;

typedef struct ProcessDialogData
{
    u32 nBGImgId;
    u32 nVolumeImgId;
}ProcessDialogData_t;

typedef struct ProcessDialogCB
{
    void* pCB;
}ProcessDialogCB_t;
//MAE_Ret CreateProcessDialog(WndHandle_t *pWndHdl, ProcessDialog_WdgList *pWdgList,ProcessDialogData_t *pData, ProcessDialogCB_t *pCB);

//*******************************************************************//
enum //RecordingDialog_enum
{
    eCOMMON_DIALOG_BGWIDGET19=0x1100,
    eCOMMON_DIALOG_IMAGEWIDGET20,
    eCOMMON_RECORDINGDIALOG_INFOTEXTWIDGET21,
    eCOMMON_DIALOG_TIMEWIDGET22,
    RecordingDialog_End
}; //RecordingDialog_enum
typedef struct RecordingDialogWdgList_t_
{
    IWidget *pBgWdg;
    IWidget *pImageWdg;
    IWidget *pTextWdg;
    IWidget *pRecordingWdg;
}RecordingDialogWdgList_t;

typedef struct RecordingDialogData
{
    u32 nBGImgId;
    u32 nVolumeImgId;
}RecordingDialogData_t;

typedef struct RecordingDialogCB
{
    void* pCB;
}RecordingDialogCB_t;
//MAE_Ret CreateRecordingDialog(WndHandle_t *pWndHdl, RecordingDialog_WdgList *pWdgList,RecordingDialogData_t *pData, RecordingDialogCB_t *pCB);

//*******************************************************************//
#endif //__common_dialog__H

