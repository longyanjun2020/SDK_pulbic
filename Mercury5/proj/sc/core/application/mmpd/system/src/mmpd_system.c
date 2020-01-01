/// @ait_only
//==============================================================================
//
//  File        : mmpd_system.c
//  Description : Ritian System Control Device Driver Function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmpd_system.c
 *  @brief The header File for the Host System Control Device Driver Function
 *  @author Penguin Torng
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "os_wrap.h"
#include "lib_retina.h"
#include "mmpd_system.h"
#include "mmph_hif.h"
#include "mmpf_system.h"

/** @addtogroup MMPD_System
 *  @{
 */

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_System_ResetSystem
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used for system reset

The function is used for system reset
@return It reports the status of the operation.
*/
MMP_ERR MMPD_System_ResetSystem(void)
{
    //Mercury5 TBD. There is no sys task anymore.
    UartSendTrace("[%s] Fix me in Mercury5 code.\n", __FUNCTION__);
    return MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);
    MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_SYSTEM_RESET | SYSTEM_SOFTWARE_RESET);
    MMPH_HIF_ReleaseSem(GRP_IDX_SYS);

	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_System_SetWakeUpEvent
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to set wake-up event for self sleep mode.

The function is used to set wake-up event for self sleep mode.

@param[bEnable] bEnable : enable/disable the wake up event
@param[bEnable] event : wake up event that AIT suppot
@param[bEnable] piopin : used in GPIO wake up event, to select GPIO
@param[bEnable] polarity : used in GPIO wake up event, to set high level/low level wake up. 0 is for high level
@return It reports the status of the operation.
*/
MMP_ERR MMPD_System_SetWakeUpEvent(MMP_BOOL bEnable, MMPD_SYSTEM_WAKEUP_EVNET event, MMP_GPIO_PIN piopin, MMP_UBYTE polarity)
{
	MMP_ERR	mmpstatus;
    //Mercury5 TBD. There is no sys task anymore.
    UartSendTrace("[%s] Fix me in Mercury5 code.\n", __FUNCTION__);
    return MMP_ERR_NONE;

	MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);
	
	MMPH_HIF_SetParameterL(GRP_IDX_SYS, 0, bEnable);
    MMPH_HIF_SetParameterL(GRP_IDX_SYS, 4, event);
    MMPH_HIF_SetParameterL(GRP_IDX_SYS, 8, piopin);
    MMPH_HIF_SetParameterL(GRP_IDX_SYS, 12, polarity);
    MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_SELF_SLEEP | SET_WAKE_EVENT);
    
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_SYS, 0);
    
	MMPH_HIF_ReleaseSem(GRP_IDX_SYS);

	return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_System_SetSelfSleepMode
//  Description :
//------------------------------------------------------------------------------
/** @brief The function sets standalone platform to enter self-sleep mode

The function sets standalone platform to enter self-sleep mode
@return It reports the status of the operation.
*/
MMP_ERR MMPD_System_SetSelfSleepMode(void)
{
    //Mercury5 TBD. There is no sys task anymore.
    UartSendTrace("[%s] Fix me in Mercury5 code.\n", __FUNCTION__);
    return MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);
	MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_SELF_SLEEP | SYSTEM_ENTER_SLEEP);
	MMPH_HIF_ReleaseSem(GRP_IDX_SYS);

	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_System_SetPSMode
//  Description :
//------------------------------------------------------------------------------
/** @brief The function sets the power saving mode

The function sets the power saving mode
@param[in] psmode the power saving mode
@return It reports the status of the operation.
*/
MMP_ERR MMPD_System_SetPSMode(MMPD_SYSTEM_PS_MODE psmode)
{
    //Mercury5 TBD. There is no sys task anymore.
    UartSendTrace("[%s] Fix me in Mercury5 code.\n", __FUNCTION__);
    return MMP_ERR_NONE;

    if (psmode == MMPD_SYSTEM_ENTER_PS) {
    
        MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);
        MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_SET_PS_MODE | ENTER_PS_MODE);
        MMPH_HIF_ReleaseSem(GRP_IDX_SYS);
    }
    else {

        MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);
        MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_SET_PS_MODE | EXIT_PS_MODE);
        MMPH_HIF_ReleaseSem(GRP_IDX_SYS);
    }
    
    MMPF_OS_Sleep_MS(100);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_System_ReadCoreID
//  Description :
//------------------------------------------------------------------------------
/** @brief Check the chip code ID

This function Get the code ID of the chip
@return It reports the status of the operation.
*/
MMP_UBYTE MMPD_System_ReadCoreID(void)
{
	return MMPF_SYS_ReadCoreID();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_System_TVInitialize
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_System_TVInitialize(MMP_BOOL bInit)
{
    MMP_ERR mmpstatus = MMP_ERR_NONE;
    
    //Mercury5 TBD. There is no sys task anymore.
    UartSendTrace("[%s] Fix me in Mercury5 code.\n", __FUNCTION__);
    return MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);
    
    if (bInit) {
	    MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_CONFIG_TV | TVENC_INIT);
    }
    else {
	    MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_CONFIG_TV | TVENC_UNINIT);
    }
    
    MMPH_HIF_ReleaseSem(GRP_IDX_SYS);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_System_TVColorBar
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_System_TVColorBar(MMP_TV_TYPE tvType, MMP_BOOL turnOn, MMP_UBYTE colorBarType)
{
    MMP_ERR mmpstatus = MMP_ERR_NONE;
    
    //Mercury5 TBD. There is no sys task anymore.
    UartSendTrace("[%s] Fix me in Mercury5 code.\n", __FUNCTION__);
    return mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);
    
    MMPH_HIF_SetParameterL(GRP_IDX_SYS, 0, (MMP_ULONG) tvType);
    MMPH_HIF_SetParameterL(GRP_IDX_SYS, 4, (MMP_ULONG) turnOn);
    MMPH_HIF_SetParameterL(GRP_IDX_SYS, 8, (MMP_ULONG) colorBarType);
    MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_CONFIG_TV | TV_COLORBAR);
    
    MMPH_HIF_ReleaseSem(GRP_IDX_SYS);

    return mmpstatus;
}

#if (EN_AUTO_TEST_LOG == 1)
//------------------------------------------------------------------------------
//  Function    : MMPD_System_ClrAutoTestLog
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_System_ClrAutoTestLog(void)
{
    MMP_ERR mmpstatus = MMP_ERR_NONE;

    //Mercury5 TBD. There is no sys task anymore.
    UartSendTrace("[%s] Fix me in Mercury5 code.\n", __FUNCTION__);
    return MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_CLR_AUTOTEST_LOG);

    MMPH_HIF_ReleaseSem(GRP_IDX_SYS);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_System_DumpAutoTestLog
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_System_DumpAutoTestLog(void)
{
    MMP_ERR mmpstatus = MMP_ERR_NONE;

    //Mercury5 TBD. There is no sys task anymore.
    UartSendTrace("[%s] Fix me in Mercury5 code.\n", __FUNCTION__);
    return MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_DUMP_AUTOTEST_LOG);

    MMPH_HIF_ReleaseSem(GRP_IDX_SYS);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_System_SetUserDefCmdNum
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_System_SetUserDefCmdNum(MMP_LONG ulUserDefNum)
{
    MMP_ERR	mmpstatus = MMP_ERR_NONE;

    //Mercury5 TBD. There is no sys task anymore.
    UartSendTrace("[%s] Fix me in Mercury5 code.\n", __FUNCTION__);
    return MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_SYS, 0);
    
    MMPH_HIF_SetParameterL(GRP_IDX_SYS, 0, ulUserDefNum);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_SYS, HIF_SYS_CMD_SET_USER_DEF_CMD_NUM);

    MMPH_HIF_ReleaseSem(GRP_IDX_SYS);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_System_IsAutoTestCmdLFull
//  Description :
//------------------------------------------------------------------------------
MMP_UBYTE MMPD_System_IsAutoTestCmdLFull(MMP_ULONG ulAhcSysMode)
{
#if defined(ALL_FW)
    return MMPF_SYS_IsAutoTestCmdLFull(ulAhcSysMode);
#else
    return 0;
#endif
}
#endif

/// @}
/// @end_ait_only

