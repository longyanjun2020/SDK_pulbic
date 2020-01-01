/*
 * Copyright (C) 2010 Beijing Komoxo Inc.
 * All rights reserved.
 * @author ghd
 * @version  1
 */
#ifdef __MMI_SCRIPT_EASY_EDITOR__

#ifndef __KMX_WDG_INPUT_H__
#define __KMX_WDG_INPUT_H__
#endif

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_retcode.h"
#include "mae_window.h"
#include "mmi_mae_langcode.h"

#include "mae_inputcontroller.h"
#include "mmi_wdg_common_interface.h"
#include "mae_widget_priv_properties.h"

#include "mmi_wdg_input_priv.h"
#include "scripteasy.h"


/*=============================================================*/
// type and define
/*=============================================================*/

typedef void (*kmx_PfnWdgInputSMSLengthEncoding) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, SMSData_t *pSMSData, IWidget *pWidget);
// Non-interface functions
/*=============================================================*/

MAE_Ret kmx_WdgInputConstructor(InputWidget_t *pThis);
void kmx_WdgInputDestructor(InputWidget_t *pThis);

//for IWidget interface
void kmx_WdgInputDraw(IWidget *pIWidget, Wdg_Draw_Req_t *pReq);
MAE_Ret kmx_InputWidget_SetModel(IWidget *pIWidget, IModel *pIModel, IBase* pOwner);


void kmx_InputWidget_ModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);

boolean kmx_InputWidget_HandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 param1, u32 param2);

static void kmx_InputWidget_BlinkTimerCallBack(InputWidget_t *pThis, void* pData);
void kmx_start_caret_blink(IWidget *pIWidget);
void kmx_stop_caret_blink(IWidget *pIWidget);

/*notify function*/
static void kmx_InputWidget_NoifyScroll(IWidget *pIWidget, u32 nTotalLines, u32 nFirstLine, u32 nVisibleLines);

static void kmx_InputWidget_LoadResource(InputWidget_t *pThis);

#endif/*__MMI_SCRIPT_EASY_EDITOR__*/
