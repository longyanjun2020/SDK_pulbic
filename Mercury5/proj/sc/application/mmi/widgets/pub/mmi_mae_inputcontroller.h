/**
 * @file    mmi_mmi_mae_inputcontroller.h
 * @brief   Implementation of inputcontroller
 * @version $Id: mmi_mmi_mae_inputcontroller.h 32761 2009-06-06 10:20:16Z bill.pan $
 */
#ifndef __MMI_MAE_INPUTCONTROLLER_H__
#define __MMI_MAE_INPUTCONTROLLER_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_controller.h"
#include "mmi_mae_interface_def.h"
#include "mmi_wdg_common_interface.h"
//#define __MMI_ENDKEY_AS_CLEAR__
//#define __MMI_SOFTKEY_AS_CLEAR__
/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum {
	IINPUTCONTROLLER_CallBackEvent_Update_TextModel_Start,
	IINPUTCONTROLLER_CallBackEvent_Update_TextModel_End,
	IINPUTCONTROLLER_CallBackEvent_Hide_Cursor,
	IINPUTCONTROLLER_CallBackEvent_Disable_Draw_Selection_InOneLine,
	IINPUTCONTROLLER_CallBackEvent_Multiline_Display,
	IINPUTCONTROLLER_CallBackEvent_Cursor_FromXY,
	IINPUTCONTROLLER_CallBackEvent_Cursor_MoveUp,
	IINPUTCONTROLLER_CallBackEvent_Cursor_MoveDown,
	IINPUTCONTROLLER_CallBackEvent_LeftToRight_Editor
} IInputColtrollerCallBackEvent_E;


typedef struct{
	u32 nValue;
}CallbackData_General_t;

typedef struct{
	u32 PosX_in;
	u32 PosY_in;
	boolean bHandled_out;
}CallbackData_Cursor_FromXY_t;


typedef struct{
	IInputColtrollerCallBackEvent_E eCallBackEvent;
	union{
		CallbackData_General_t tCallbackDataGeneral;
		CallbackData_Cursor_FromXY_t tCallBackDataCursorFromXY;
	}CallBackParam;
}InputControllerCallbackData;

#ifdef __QWERTY_KEYPAD_INPUTMETHOD__
#define QWERTY_KEY_NUM      (29)
#define QWERTY_GENERAL_CHAR_INPUTKEY_NUM   (28)
#endif /*__QWERTY_KEYPAD_INPUTMETHOD__*/

//symbols
#define MAE_PAUSE_WCHAR            0x0070
#define MAE_INTERNATIONALDIAL_WCAHR 0x002B
#define MAE_WILDCARD_WCAHR          0x0057
#define MAE_WILDCARD_QUESTION_WCHAR 0x003F
#define MAE_RATE_ERROR_WCHAR		0x0045

//input mode
#define MAE_INPUTMODE_NUMERIC  0x10000000
#define MAE_INPUTMODE_DIALING  0x20000000
#define MAE_INPUTMODE_RATE     0x40000000
#ifdef __IME_MMI_CSTAR__
#define MAE_INPUTMODE_LOCAL_NUMERIC  0x50000000
#endif
#define MAE_INPUTMODE_MT_Abc   0x01000001
#define MAE_INPUTMODE_MT_abc   0x01000002
#define MAE_INPUTMODE_MT_ABC   0x01000004
#define MAE_INPUTMODE_SMART_Abc   0x02000001
#define MAE_INPUTMODE_SMART_abc   0x02000002
#define MAE_INPUTMODE_SMART_ABC   0x02000004
#define MAE_INPUTMODE_STROKE    0x00010000
#define MAE_INPUTMODE_PINYIN    0x00020000
#define MAE_INPUTMODE_BPMF      0x00040000
#define MAE_INPUTMODE_VIEWONLY  0x00001000
#define MAE_INPUTMODE_TYPE_STROKE 0x00002000
#define MAE_INPUTMODE_INVALID  0x00000000   // for reset input mode

// mode mask
#define MAE_MODEMASK_GENERAL   0x93070007
#define MAE_MODEMASK_LATINONLY   0x93000007
#define MAE_MODEMASK_NUMERIC   0x70000000
#define MAE_MODEMASK_MT        0x01000000
#define MAE_MODEMASK_SMART        0x02000000
#define MAE_MODEMASK_CHINESE   0x00070000
#define MAE_MODEMASK_ENGLISH   0x80000000
#ifdef __IME_MMI_CSTAR__
#ifdef __UNICODE_TO_STROKE__
#define MAE_MODEMASK_PHB_SEARCH_KMX   0x93072003
#else
#define MAE_MODEMASK_PHB_SEARCH_KMX   0x93070003
#endif
#endif

#ifdef __UNICODE_TO_STROKE__
#define MAE_MODEMASK_PHB_SEARCH   0x91072002
#else
#define MAE_MODEMASK_PHB_SEARCH   0x91070002
#endif
#ifdef __IME_MMI_CSTAR__
#define MAE_MODEMASK_VDO_PASSWORD   0x81000006
#define MAE_MODEMASK_VDO_PASSWORD_EXT   0x93000007
#endif

//The following input mode is only for Inputcontroller's inner using.
#define MAE_INPUTMODE_MASK        0x80000000
#define MAE_INPUTMODE_MT_Abc_EN   0x81000001
#define MAE_INPUTMODE_MT_abc_EN   0x81000002
#define MAE_INPUTMODE_MT_ABC_EN   0x81000004
#define MAE_INPUTMODE_SMART_Abc_EN   0x82000001
#define MAE_INPUTMODE_SMART_abc_EN   0x82000002
#define MAE_INPUTMODE_SMART_ABC_EN   0x82000004

//ShiftMode and mask
#define IME_SHIFTMODE_Abc       0x00000001
#define IME_SHIFTMODE_abc       0x00000002
#define IME_SHIFTMODE_ABC       0x00000004
#define IME_SHIFTMODE_PHONEBOOK 0x00000008	//Phonebook only

#define IME_SHIFTMODE_MASK      0x0000000F
#define IME_INPUT_MODE_MASK		0xFFFFFFF0

typedef enum
{
    SmartShiftMode_Paragraph = 0,
    SmartShiftMode_Name
}SmartShiftMode_e;

typedef enum
{
    Encode_UCS2 = 0,
    Encode_UTF8,
    Encode_SIM,
    Encode_SMS,
    Encode_ASC_UCS2
}InputEnncode_e;

#ifdef __SMS_3GPP_R8_SUPPORT__
typedef enum
{
	SMSEnncode_7BIT,
	SMSEnncode_UCS2
}SMSEnncode_e;
#else //__SMS_3GPP_R8_SUPPORT__
typedef enum
{
    SMSEnncode_7BIT,
	SMSEnncode_GSMEXT,
    SMSEnncode_UCS2
}SMSEnncode_e;
#endif //__SMS_3GPP_R8_SUPPORT__

// Defined for Chinese selection Widget, Chinese input mode
typedef enum
{
    CHINESE_ON_SPELL = 0,
    CHINESE_ON_CANDIDATE,
    CHINESE_ON_ASSOCIATION
}ChineseInputState_e;

#ifdef __IME_MMI_SG__
// Defined for Smart selection Widget, Smart input mode
typedef enum
{
	SMART_ON_SPELL = 0,
	SMART_ON_CANDIDATE	
}SmartInputState_e;
#endif //__IME_MMI_SG__

//Input Method Setting

//Do not change order and data type
//Mapping with mmi_setting_cfg.h SetChineseInputMode_e
enum
{
 	CHINESE_INPUTMODE_SCHINESE_STROKE = 0 ,
	CHINESE_INPUTMODE_SCHINESE_PINYIN	  ,
	CHINESE_INPUTMODE_TCHINESE_PINYIN	  ,
	CHINESE_INPUTMODE_TCHINESE_BPMF
};
typedef u8 ChineseInputMode_e;

//Do not change order and data type
//Mapping with mmi_setting_cfg.h SetDefaultInputModeABC_e
enum
{
 	DEFAULT_INPUT_MODE_NOT_ABC	= 0,
	DEFAULT_INPUT_MODE_ABC
};
typedef u8 DefaultInputModeABC_e;

//Do not change order and data type
//Mapping with mmi_setting_cfg.h SetSmartInput_e
enum
{
 	SMART_INPUT_MODE_OFF	= 0,
	SMART_INPUT_MODE_ON
};
typedef u8 SmartInput_e;

//Do not change order and data type
//Mapping with mmi_setting_cfg.h SetSoftKeyboard_e
enum
{
 	 SOFT_KEYBOARD_MODE_OFF	= 0,
	 SOFT_KEYBOARD_MODE_ON
};
typedef u8 SoftKeyboard_e;


typedef struct {
	u32 nRSKID;
	u32 nMSKID;
	u32 nLSKID;
} InputSoftkeyID_t;

typedef struct {
	u32 ePressImgID;
	u32 eUnpressImgID;
	u32 eItemType;
} CusToolBoxItem_t;

typedef struct {
	u32 nStartPos;
	u32 nEndPos;
} InputSelection_t;

/*=============================================================*/
// macro property interface
/*=============================================================*/

typedef void (*PFNINPUTCOLTROLLERCALLBACK)(void *, InputControllerCallbackData *);

#define INHERIT_IInputController(IName) \
	INHERIT_IController(IName); \
	MAE_Ret (*RegisterCallback)	(IName *pIInputController, PFNINPUTCOLTROLLERCALLBACK fn)


//Here define IInputController interface
DEFINE_INTERFACE(IInputController);

/*=============================================================*/
// functions
/*=============================================================*/
/**
*  IINPUTCONTROLLER_RegisterCallBackFunc
*  @brief  Set call back function to controller
*
*  @param  pFunc		           Pointer to the call back function
*  @retval MAE_RET_SUCCESS         Success
*  @retval MAE_RET_FAILED          Failed
*  @retval MAE_BAD_PARAM           Invalid paramter.
*/
#define IINPUTCONTROLLER_RegisterCallBack(pIInputController, fn)\
	GET_FUNCTBL((pIInputController),IInputController)->RegisterCallback(pIInputController, fn)


/*=============================================================*/
// functions
/*=============================================================*/
/**
*  IINPUTCONTROLLER_SetWidget
*  @brief  Set widget to controller
*
*  @param  pW					   Pointer to widget
*  @param  pOwner				   Pointer to owner
*  @retval MAE_RET_SUCCESS         Success
*  @retval MAE_RET_FAILED          Failed
*  @retval MAE_BAD_PARAM           Invalid paramter.
*/
#define IINPUTCONTROLLER_SetWidget(pICtlr,pW,pOwner) \
			GET_FUNCTBL((pICtlr),IInputController)->SetWidget(pICtlr,pW,pOwner)

/*=============================================================*/
// functions
/*=============================================================*/
/**
*  IINPUTCONTROLLER_HandleEvent
*  @brief  Set call back function to controller
*
*  @param  e		               event
*  @param  p1					   param1
*  @param  p2					   param2
*  @retval TRUE				       handled
*  @retval FALSE				   unhandled
*/
#define IINPUTCONTROLLER_HandleEvent(pICtlr,e,p1,p2) \
		GET_FUNCTBL((pICtlr),IInputController)->HandleEvent(pICtlr,e,p1,p2)
/*
=======================================================================================================
How to add input menu into option menu
------------------------------------------------------------------------------------------------------
The menu items in input menu are "input method", "insert symbol", "smart input on/Off", "mark for copy", "mark for cut" and "paste".
There are three properties which are related to launch input menu.

PROP_INPUT_WDG_ENTRY_OPTION_MENU
Illustration: After creating option menu widget, AP has to pass the pointer of option menu to input widget if the menu item of input menu is in option menu.
Input widget will register the view model listener to second layer option menu.
WdgCommonSetProperty(pThis->pInputWidget, PROP_INPUT_WDG_ENTRY_OPTION_MENU, (u32)pThis-> pOptionMenu->pOptionMenuWidget);

PROP_INPUT_WDG_LAUNCH_INPUT_MENU
Illustration: When user select input menu in option menu, AP has to pass this property to input widget to ask input widget to prepare the input menu items.
The menu mode of input menu items will be sent to option menu directly.
@Please add following statement at the callback function of the view model listener  for first layer of option menu widget.
WdgCommonSetProperty(pThis->pInputWidget, PROP_INPUT_WDG_LAUNCH_INPUT_MENU,(u32)pThis->pOptionMenu->pOptionMenuWidget);

PROP_INPUT_WDG_EXIT_OPTION_MENU
Illustration: Before releasing option menu widget, AP has to pass this property to note input widget to cancel view model listener.
WdgCommonSetProperty(pThis->pInputWidget, PROP_INPUT_WDG_EXIT_OPTION_MENU,(u32)pThis->pOptionMenu->pOptionMenuWidget);


The properties to adjust the menu items in input menu.
@PROP_INPUT_WDG_DISABLE_SYMBOL_TABLE
==>Disable symbol table
WdgCommonSetProperty(pThis->pInputWidget, PROP_INPUT_WDG_DISABLE_SYMBOL_TABLE,(u32)TRUE);

@PROP_INPUT_WDG_CANNOT_SWITCH_INPUT_MODE
==>Turn off the ability to change input method.
WdgCommonSetProperty(pThis->pInputWidget, PROP_INPUT_WDG_CANNOT_SWITCH_INPUT_MODE,(u32)TRUE);

@PROP_INPUT_WDG_SMARTINPUT_OFF
==>Remove the menu item "Smart Input On/Off"
WdgCommonSetProperty(pThis->pInputWidget, PROP_INPUT_WDG_SMARTINPUT_OFF,(u32)TRUE);

@PROP_INPUT_WDG_DISABLE_MARK_FUNCTIONS
==>Remove the menu item "Mark for copy", "Mark for cut" and "Paste". User can not use mark function
WdgCommonSetProperty(pThis->pInputWidget, PROP_INPUT_WDG_DISABLE_MARK_FUNCTIONS,(u32)TRUE);
===============================================================================================================
*/
#ifdef __QWERTY_KEYPAD_INPUTMETHOD__            //add by luo ren 20091016
u32  InputController_GetKeyIndex(u8 nkeyID);
#endif  /*__QWERTY_KEYPAD_INPUTMETHOD__*/

#endif //__MAE_INPUTCONTROLLER_H__
/*=============================================================*/
// end of file
