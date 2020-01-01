//==============================================================================
//
//  File        : AHC_TouchPanel.c
//  Description : AHC TouchPanel control function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 
#include "Customer_config.h"
#include "ahc_common.h" 
#include "mmpf_touchpanel.h"
#include "ahc_touchpanel.h"
#include "dsc_Key.h"

/*===========================================================================
 * Main body
 *===========================================================================*/

#if (DSC_TOUCH_PANEL == TOUCH_PANEL_FT6X36 || DSC_TOUCH_PANEL == TOUCH_PANEL_GT911)
static MMP_BOOL bFirstTouch = 0;
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_TouchPanel_Module_Attached
//  Description : 
//------------------------------------------------------------------------------ 
AHC_BOOL AHC_TouchPanel_Module_Attached(void)
{
    return MMPF_3RDParty_TouchPanel_Attached();
}

//------------------------------------------------------------------------------
//  Function    : AHC_TouchPanel_Init
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_TouchPanel_Init(void)
{
    MMP_ERR ret_val;

    ret_val = MMPF_3RDParty_TouchPanel_Init();

    AHC_TOUCHPANEL_CHECK_RETURE_VALUE(ret_val, AHC_TOUCHPANEL_NO_ERROR, AHC_TOUCHPANEL_RET_TRUE, AHC_TOUCHPANEL_RET_FALSE)
}

//------------------------------------------------------------------------------
//  Function    : AHC_TouchPanel_ReadPosition
//  Description : 
//------------------------------------------------------------------------------
int AHC_TouchPanel_ReadPosition(MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir)
{
    int ret_val;
    
    ret_val = MMPF_3RDParty_TouchPanel_ReadPosition(pX, pY, dir);
    
    return ret_val;
}

//------------------------------------------------------------------------------
//  Function    : AHC_TouchPanel_ReadVBAT1
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_TouchPanel_ReadVBAT1(MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir)
{
    MMP_ERR ret_val;
    
    ret_val = MMPF_3RDParty_TouchPanel_ReadVBAT1(pX, pY, dir);
    
    AHC_TOUCHPANEL_CHECK_RETURE_VALUE(ret_val, AHC_TOUCHPANEL_NO_ERROR, AHC_TOUCHPANEL_RET_TRUE, AHC_TOUCHPANEL_RET_FALSE)
}

//------------------------------------------------------------------------------
//  Function    : AHC_TouchPanel_IOControl
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_TouchPanel_IOControl(UINT8 cmd, void* arg)
{
    MMP_ERR ret_val;
    
    ret_val = MMPF_3RDParty_TouchPanel_IOControl((MMP_UBYTE)cmd, (MMP_UBYTE*)arg);
    
    AHC_TOUCHPANEL_CHECK_RETURE_VALUE(ret_val, AHC_TOUCHPANEL_NO_ERROR, AHC_TOUCHPANEL_RET_TRUE, AHC_TOUCHPANEL_RET_FALSE)
}

AHC_BOOL AHC_TouchPanel_GetKeyValue(MMP_ULONG* pulKeyEvent, MMP_ULONG* pulPosition, MMP_UBYTE dir, MMP_UBYTE* finger)
{
    MMP_ERR status = AHC_TOUCHPANEL_NO_ERROR;
    static MMP_ULONG ulPosition = 0;

    if (*pulKeyEvent == TOUCH_KEY_PRESS   ||
        *pulKeyEvent == TOUCH_KEY_MOVE 	||
        *pulKeyEvent == TOUCH_KEY_REL)
    {
        // Read position
        MMP_USHORT uwX =0;
        MMP_USHORT uwY =0;
        
        *finger = AHC_TouchPanel_ReadPosition(&uwX, &uwY, dir);
        *pulKeyEvent = uwX;
		*pulPosition = 0;
		#if 0
        if (*finger == 0 && *pulKeyEvent != TOUCH_PANEL_REL)
        {
            *pulPosition = 0;
            status = AHC_TOUCHPANEL_RET_FALSE;
        }
        else if (*pulKeyEvent != TOUCH_PANEL_REL)
        {
            ulPosition = uwY;
            ulPosition = (ulPosition << 16) + uwX;

            *pulPosition = ulPosition;
            status = AHC_TOUCHPANEL_RET_TRUE;
        }
		#endif
    }
    
    AHC_TOUCHPANEL_CHECK_RETURE_VALUE(status, AHC_TOUCHPANEL_NO_ERROR, AHC_TOUCHPANEL_RET_TRUE, AHC_TOUCHPANEL_RET_FALSE)
}

//------------------------------------------------------------------------------
//  Function    : AHC_TouchPanel_CheckUpdate
//  Description : 
//------------------------------------------------------------------------------
#if (DSC_TOUCH_PANEL == TOUCH_PANEL_FT6X36 || DSC_TOUCH_PANEL == TOUCH_PANEL_GT911)
static MMPF_OS_TMRID    g_DtcTimerID = 0xFF;
unsigned int    gulTouchOpModeDtcTimeOut = 100;

void AHC_TOUCH_DetectMode(void *ptmr, void *parg)
{
    //MMP_ULONG  ulNow;

    //printc("AHC_TOUCH send event\r\n");

    SetKeyPadEvent(TOUCH_PANEL_REL);
}


void AHC_TOUCH_ActiveModeDetect(void)
{
    g_DtcTimerID = MMPF_OS_StartTimer(gulTouchOpModeDtcTimeOut,
                                        MMPF_OS_TMR_OPT_ONE_SHOT,
                                        AHC_TOUCH_DetectMode, NULL);

	if (g_DtcTimerID >= MMPF_OS_TMRID_MAX) {
    	RTNA_DBG_Str(0, "Error !! : AHC_TOUCH_ActiveModeDetect Get OS Timer error !");
    }
}

void AHC_TOUCH_InActiveMode(void)
{
    MMP_UBYTE ret;
    
    if(g_DtcTimerID != 0xff)
        ret = MMPF_OS_StopTimer(g_DtcTimerID, MMPF_OS_TMR_OPT_NONE);
    
    if(ret != 0)
        RTNA_DBG_Str(0, "Stop OS Timer error !!\r\n");
}

AHC_BOOL AHC_TouchPanel_CheckUpdate(MMP_ULONG* pulKeyEvent, MMP_ULONG* pulPosition, MMP_UBYTE dir, MMP_UBYTE* finger)
{
    MMP_ERR status = MMP_ERR_NONE;
    static MMP_ULONG ulPosition = 0;
    
    if (*pulKeyEvent == TOUCH_PANEL_PRESS   ||
        *pulKeyEvent == TOUCH_PANEL_REL 	||
        *pulKeyEvent == TOUCH_PANEL_MOVE)
    {
        // Read position
        MMP_USHORT uwX =0;
        MMP_USHORT uwY =0;
        
        *finger = AHC_TouchPanel_ReadPosition(&uwX, &uwY, dir);

        if((*pulKeyEvent == TOUCH_PANEL_REL)||((bFirstTouch == 1)&& (*finger == 0)))
        {
            printc("[touch]finger release\r\n");
            //*pulKeyEvent == TOUCH_PANEL_REL;
            bFirstTouch = 0;

            AHC_TOUCH_InActiveMode();
        }
        else if(*finger != 0)
        {
            if(bFirstTouch == 1)
            {
                printc("[touch]finger move\r\n");
                *pulKeyEvent = TOUCH_PANEL_MOVE;
                AHC_TOUCH_InActiveMode();
                AHC_TOUCH_ActiveModeDetect();
            }
            else
            {
                bFirstTouch = 1;
                printc("[touch]finger down\r\n");
                *pulKeyEvent = TOUCH_PANEL_PRESS;

                AHC_TOUCH_ActiveModeDetect();
            }

            //reset timeout value of event&flag
            
        }
        else
        {
            //printc("[touch]finger dummy event\n");
            *pulKeyEvent = KEYPAD_NONE;
            bFirstTouch = 0;
        }

        if(*pulKeyEvent != KEYPAD_NONE)
        {
            ulPosition = uwY;
            ulPosition = (ulPosition << 16) + uwX;

            *pulPosition = ulPosition;
            status = AHC_TOUCHPANEL_RET_TRUE;
        }
        else
        {
            *pulPosition = 0;
            status = AHC_TOUCHPANEL_RET_FALSE;
        }

    }
    
    AHC_TOUCHPANEL_CHECK_RETURE_VALUE(status, AHC_TOUCHPANEL_NO_ERROR, AHC_TOUCHPANEL_RET_TRUE, AHC_TOUCHPANEL_RET_FALSE)
}
#else
AHC_BOOL AHC_TouchPanel_CheckUpdate(MMP_ULONG* pulKeyEvent, MMP_ULONG* pulPosition, MMP_UBYTE dir, MMP_UBYTE* finger)
{
    MMP_ERR status = MMP_ERR_NONE;
    static MMP_ULONG ulPosition = 0;

    if (*pulKeyEvent == TOUCH_PANEL_PRESS   ||
        *pulKeyEvent == TOUCH_PANEL_REL 	||
        *pulKeyEvent == TOUCH_PANEL_MOVE)
    {
        // Read position
        MMP_USHORT uwX =0;
        MMP_USHORT uwY =0;
        
        *finger = AHC_TouchPanel_ReadPosition(&uwX, &uwY, dir);
        
        if (*finger == 0 && *pulKeyEvent != TOUCH_PANEL_REL)
        {
            *pulPosition = 0;
            status = AHC_TOUCHPANEL_RET_FALSE;
        }
        else if (*pulKeyEvent != TOUCH_PANEL_REL)
        {
            ulPosition = uwY;
            ulPosition = (ulPosition << 16) + uwX;

            *pulPosition = ulPosition;
            status = AHC_TOUCHPANEL_RET_TRUE;
        }
    }
    
    AHC_TOUCHPANEL_CHECK_RETURE_VALUE(status, AHC_TOUCHPANEL_NO_ERROR, AHC_TOUCHPANEL_RET_TRUE, AHC_TOUCHPANEL_RET_FALSE)
}
#endif
