//==============================================================================
//
//  File        : mmpf_uart_touch.c
//  Description : uart touch Control function
//  Author      : Welly chen
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "includes_fw.h"
#include "Touch_uart_ctrl.h"

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

struct _3RD_PARTY_TOUCH_UART *gpTouch_Uart_obj = NULL;
MMP_UART_ATTR uartattribute={0};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

MMP_ERR Touch_Uart_Ctrl_Init(void)
{
    if(gpTouch_Uart_obj && Touch_Uart_Ctrl_Attached()){
        return gpTouch_Uart_obj->pTouch_Uart_Initialize(gpTouch_Uart_obj,uartattribute);
    }    
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : Touch_Uart_Ctrl_GetString
//  Description : 
//------------------------------------------------------------------------------
MMP_ERR Touch_Uart_Ctrl_GetString(MMP_BYTE *data,MMP_ULONG *length)
{
    if(gpTouch_Uart_obj && Touch_Uart_Ctrl_Attached()){
        return gpTouch_Uart_obj->pTouch_Uart_GetString(gpTouch_Uart_obj,data,length);
    }    
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : Touch_Uart_Ctrl_SetString
//  Description : 
//------------------------------------------------------------------------------
MMP_ERR Touch_Uart_Ctrl_SetString(MMP_BYTE *data,MMP_ULONG length)
{
    if(gpTouch_Uart_obj && Touch_Uart_Ctrl_Attached()){
        return gpTouch_Uart_obj->pTouch_Uart_SetString(gpTouch_Uart_obj,data,length);
    }   
    return MMP_SYSTEM_ERR_HW;
}


//------------------------------------------------------------------------------
//  Function    : Touch_Uart_Ctrl_IOControl
//  Description : 
//------------------------------------------------------------------------------
MMP_ERR Touch_Uart_Ctrl_IOControl(MMP_UBYTE cmd, MMP_UBYTE* arg)
{
    if (gpTouch_Uart_obj && Touch_Uart_Ctrl_Attached()) {
        return gpTouch_Uart_obj->pTouch_Uart_IOControl(gpTouch_Uart_obj, cmd, arg);
    }
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : Touch_Uart_Ctrl_Attached
//  Description : 
//------------------------------------------------------------------------------
MMP_BOOL Touch_Uart_Ctrl_Attached(void)
{
    if(gpTouch_Uart_obj){
        return gpTouch_Uart_obj->pTouch_Uart_ModuleAttached(gpTouch_Uart_obj);
    }
    
    return MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : Touch_Uart_Ctrl_Register
//  Description : 
//------------------------------------------------------------------------------
void Touch_Uart_Ctrl_Register(struct _3RD_PARTY_TOUCH_UART*pdev_obj)
{

    gpTouch_Uart_obj = (struct _3RD_PARTY_TOUCH_UART *)pdev_obj;

	uartattribute.bParityEn 		= MMP_FALSE;
	uartattribute.parity 			= MMP_UART_PARITY_NONE;
	uartattribute.bFlowCtlEn 		= MMP_FALSE;
	uartattribute.ubFlowCtlSelect 	= 0;
    uartattribute.padset 			= NULL;
    uartattribute.ulMasterclk 		= NULL ;
	uartattribute.ulBaudrate 		= NULL;

}

//------------------------------------------------------------------------------
//  Function    : Touch_Uart_CtrlUnregister
//  Description : 
//------------------------------------------------------------------------------
void Touch_Uart_CtrlUnregister(void)
{
    gpTouch_Uart_obj = NULL;
	memset(&uartattribute,0,sizeof(MMP_UART_ATTR));
}



/// @}
