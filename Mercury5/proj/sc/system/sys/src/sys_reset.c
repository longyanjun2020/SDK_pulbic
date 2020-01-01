#include "vm_types.ht"
#include "v24.hi"
#include "sys_premain.h"
#include "sys_dbg.h"
#include "kernel.h"
#include "sys.ho"
#include "sys_tools.h"
#include "sys_arm.h"
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "drv_emi_sram_nor_pub.h"
#include "sys_sys_mem.h"

#include "drv_timer_types.h"
#include "drv_timer_api.h"
#include "drv_power_api.h"
#include "sys_sys_bootinit.h"
#include "drv_flash_lowl_ht_pub.h"


void asm_ke_Reset(void);
void Ke_FullReset_Config_WDT(void);

extern void hwldsp_BeforeReset(void);
extern void sys_PsramReset(void);
extern bool sysIsDwlMode(void);
extern s8 UartSendTrace(const char *strFormat, ...);

/****************************************************************************/
/*  Function: ke_FullReset                                                  */
/*--------------------------------------------------------------------------*/
/*  Scope: Full core reset                                                  */
/*  This function makes warm reset that tries to be as close as */
/* possible to a hardware reset, i.e. something that resets */
/* as much hardware blocks as possible. */
/*                                                                          */
/* Carl: There is still a "branch instruction", which branch to Ke_FullReset_Config_WDT(),  */
/* after sys_Disable_cache(). Therefore, we need to place this function in section "RoCodeOnBootStage2" */
/*                                                                          */
/*  Return: N/A                                                             */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
__RO_CODE_ON_BOOT_STAGE2__ void ke_FullReset(void)
{

#if defined(__CHIPDRV_R2_WDT__)
#warning L1 related function is missed // TODO: FIXME
#elif defined(__CHIPDRV_INFINITY_WDT__)
// TODO: FIXME
    UartSendTrace("ke_FullReset\n");
#else  // defined(__CHIPDRV_R2_WDT__)
    hwldsp_BeforeReset();

    // set clock as I3 reset value since I3 won't reset while HW watchdog
    DrvClkgenDrvClockCtl(CLKGEN_DRV_CORE, CLKGEN_CLK_REQ_ON);
#endif // defined(__CHIPDRV_R2_WDT__)

    /* expect watch dog reset */
    sys_set_WDogRstFlag(0x13572468);
    SysDebugStruct.powerOffFlag = 0;

    // force to disable irq to prevent interrupt happening in cache operation
    MsDisableInterrupt();

    sys_Disable_cache();

    Ke_FullReset_Config_WDT();

}


/****************************************************************************/
/*  Function: Ke_FullReset_Config_WDT                                       */
/*--------------------------------------------------------------------------*/
/*  Scope: Full core reset                                                  */
/* We collect the code after sys_Disable_cache() to this dedicated function,*/
/* so it could be traced by call graph                                      */
/*                                                                          */
/*  Return: N/A                                                             */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
__RO_CODE_ON_BOOT_STAGE2__ void Ke_FullReset_Config_WDT(void)
{
    extern bool CusIsNandEnabled(void);
    bool WatchDog0Enable = 0;

#if !defined(__CHIPDRV_R2_WDT__) && !defined(__CHIPDRV_INFINITY_WDT__)  //__G1__
    bool WatchDog1Enable = 0;
    sys_McpOpMode mcp_OpMode;
#ifdef __RTK_WATCHDOG_DIAGNOSE_ENHANCE__
    int i = 0;
#endif
#endif

// G1 backtrace
#if defined(__CHIPDRV_R2_WDT__) || defined(__CHIPDRV_INFINITY_WDT__) //__G1__

    DrvWDTimer0IsEnable(&WatchDog0Enable);
    if(WatchDog0Enable || sys_GetHwWdtDbgState())
    {
        // Act watchdog, set new time interval and full reset capacity
        DrvWDTimer0Ack();
        DrvWDTimer0Enable(FALSE);

        DrvWDTimer0SetTimeoutTicks(1);
        DrvWDTimer0IntEnable(FALSE);
        DrvWDTimer0Enable(TRUE);

    }
#else
    // if the HW WDT is enabled, we need to prepare mandatory settings to trigger hardware reset
    // if not, we just enter the endless loop to wait for RD debugging
    DrvWDTimer0IsEnable(&WatchDog0Enable);
    DrvWDTimer1IsEnable(&WatchDog1Enable);
    if(WatchDog0Enable || WatchDog1Enable || sys_GetHwWdtDbgState())
    {
        DrvPmCpuRomPD();

        if(sysIsDwlMode() == TRUE)
        {
            DrvFlashResetProcedure();
        }

        // Added to turn off RAM BURST/PAGE mode
        if(CusIsNandEnabled() == FALSE)  // TODO: remove to EMI/flash drv/hal // <-@@@
        {
            sys_GetMcpInformation(&mcp_OpMode);
            if(mcp_OpMode.flash_type != FLASH_SPI)
            {
                sys_PsramReset();

                g_ptKeEmiSmc->direct_addr = 0xE51F;
                g_ptKeEmiSmc->direct_addr_h = 0x1008;
                g_ptKeEmiSmc->direct_cmd_cfg = 0x3;
                g_ptKeEmiSmc->direct_cmd_issue = 0x1;
            }
        } // TODO: remove to EMI/flash drv/hal // <-@@@
        // Set watchdog duration to 0 to reset immediatly
#ifdef __RTK_WATCHDOG_DIAGNOSE_ENHANCE__
        DrvWDTimer0Enable(FALSE);
        for(i = 0; i < 10000; i++);
        DrvWDTimer0SetTimeoutTicks(1);
        for(i = 0; i < 10000; i++);
        DrvWDTimer0IntEnable(FALSE);
        for(i = 0; i < 10000; i++);
        DrvWDTimer0Enable(TRUE);
#else
        DrvWDTimer0SetTimeoutTicks(1);
        DrvWDTimer0Ack();
#endif

        DrvWDTimer1SetTimeoutTicks(1);
        DrvWDTimer1Ack();
    }
#endif

    while(1);
}

/* SIM reset: special type of SW reset.
    Branch to 0 directly and
        1. Skip the LCD controller init in DrvPowerMmpIo
        2. Skip reset pin handling in LCD_Init_first() function
        3. Skip LCD init in LCD_Init_first() function
 */
void ke_SimReset(void)
{
}

/*  Special extended type of ke_FullReset.
    Set a special flag then trigger HW reset. Upon next power session
    the On cause is not reported as RESET, which as if normal boot.
*/
void ke_FullReset_Ext(void)
{
    /* indicate this is specific use of ke_FullReset */
    sys_set_WDogRstExtFlag(0x8642753a);

    // Force enable WDT for special use of Ke_FullResetExt
    DrvWDTimer0Enable(TRUE);
    DrvWDTimer1Enable(TRUE);

    /* gone with the wind */
    ke_FullReset();
}


/****************************************************************************/
/*  Function: ke_Reset                                                      */
/*--------------------------------------------------------------------------*/
/*  Scope: Warm start of the software, branching to its entry point         */
/*                                                                          */
/*  Return: n/a                                                             */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void ke_Reset(void)
{
#if defined(__CHIPDRV_R2_WDT__)

#warning L1 related function is missed // TODO: FIXME
#elif defined(__CHIPDRV_INFINITY_WDT__)
// TODO: FIXME
#else  // defined(__CHIPDRV_R2_WDT__)

    hwldsp_BeforeReset();
    sys_ResetPattern = SOFT_RESET_PATTERN;
    asm_ke_Reset();

#endif // defined(__CHIPDRV_R2_WDT__)
}

/****************************************************************************/
/*  Function: sys_DieOnError                                                */
/*--------------------------------------------------------------------------*/
/*  Scope: Terminates the software execution                                */
/*                                                                          */
/*  Return: n/a                                                             */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i_u32_ErrorStatus | X |   |   |  Reset status to write in Dbg Data Area */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void sys_DieOnError(u32 i_u32_ErrorStatus)
{
    /* Write pattern in DDA */
    //_sys_Dda_SetResetStatus(i_u32_ErrorStatus);
    /* Flush traces */
    v24_ForceUserMode();
    /* Bye */
    ke_FullReset();
}



/****************************************************************************/
/*  Function: sys_DieOnDoubleFault                                          */
/*--------------------------------------------------------------------------*/
/*  Scope: Double fault occured, bail out immediately                       */
/*                                                                          */
/*  Return: n/a                                                             */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void sys_DieOnDoubleFault(void)
{
    /* Write pattern in DDA */
    //_sys_Dda_SetResetStatus(SYS_DDA_FATAL_REENTRANT_ERROR);
    /* Bye */
    ke_FullReset();
}


/****************************************************************************/
/*  Function: sys_PerformSoftReset                                          */
/*--------------------------------------------------------------------------*/
/*  Scope: Warm restart                                                     */
/*                                                                          */
/*  Return: n/a                                                             */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void sys_PerformSoftReset(void)
{
    /* Write pattern in Debug Area */
    SysDebugStruct.ResetCause = SYS_DDA_CUSTOMER_RESET;

    /* Flush traces */
    v24_ForceUserMode();

    /* expect watch dog reset */
    sys_set_WDogRstFlag(0x13572468);

    /* Bye */
    ke_FullReset();
}

