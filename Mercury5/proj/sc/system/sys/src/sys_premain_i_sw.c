////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


/****************************************************************************/
/*  $Workfile::   sys_premain.c                                           $ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  System software support routines                             */
/*             pre-main initialisation routine                              */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/* STANDARD PROTOTYPES                                                      */
/****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "drv_emi_sram_nor_pub.h"
#include "sys_mem.h"

#include "sys_rtk_incl.h"
#include "stdcomp.h"
#include "kernel.h"
#include "sys.ho"
#include "sys_premain.h"
#include "sys_arm.h"
#include "drv_clkgen_cmu.h"
#include "drv_power_types.h"
#include "drv_power_api.h"
#include "drv_rtc.h"
#include "drv_keypad_pub_types.h"
#include "drv_keypad_pub_api.h"
#include "sys_irq_ctrl_pub_types.h"
#include "sys_irq_ctrl_pub_api.h"
#include "sys_dbg.h"
//#include "l1c_ext.hi"
#include "sys_rm_trc.ho"
#include "sys_speed_profile.h"
#include "sys_power_mngt.h"
#include "sys_tools.h"
#ifdef __FIXME__
#include "hal_pmu_itf.h"
#endif
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "drv_int_ctrl_pub_api.h"
#include "sys_MsWrapper_cus_os_int_ctrl.h"


#include "drv_io_chip_pub_types.h"
#include "drv_io_chip_pub_api.h"
#include "drv_timer_types.h"
#include "drv_timer_api.h"

#include "drv_uart_api.h"

// TODO :> hal here ??
#include "hal_drv_util.h"
#include "hal_fuart.h"
#include "sys_sys_bootinit.h"
#include "sys_sys_isw_uart.h"


#ifdef __SPI_RESET_BY_OFF_VMEM__
#define WDOG_FLAG_TO_IMI_WA
#endif

#ifndef WDOG_FLAG_TO_IMI_WA //flag declared in PSRAM

#if !defined(__GNUC__)
#pragma arm section rwdata = "SysNonZI"
#endif
__section__(SysNonZI) volatile u32 sys_ExpectedWDogRst;		//expected from backtrace end
__section__(SysNonZI) volatile u32 sys_ExpectedWDogRstExt;	//expected from specific use
#if !defined(__GNUC__)
#pragma arm section rwdata
#endif
#endif

u8 preBootUpSequence;

#ifdef __RTK_WATCHDOG_DIAGNOSE_ENHANCE__

void sys_watchDogHandler(void)
{
#if defined(__CHIPDRV_R2_WDT__)
    u8 wdt_src = HalWDTimer0IntSrcGet();
    u16 reg_wdt_int = HalWDTimer0IntLenGet();
    u32 picsr = mfspr(SPR_PICSR);
    u32 fiq_raw_status = 0;
    u32 etmi_0a_clear_status = 0;
    extern u32 HalEtmiGetClearStatus(u32 bank);

    sys_watchDogHandler_time = DrvTimerGlobalTimerGetTick();
    etmi_0a_clear_status = HalEtmiGetClearStatus(ETMI_BANK_0_A);
    fiq_raw_status = HalIntcGetFiqRawIdx();
    reg_wdt_int = HalWDTimer0IntLenGet();

    DrvWDTimer0Ack();

    if(etmi_0a_clear_status & (1 << ETMI0_CHIPTOP_WDT_INT_POS))
    {
        // If in NMI, need to clear FIQ source
        HalWDTimer0IntEnable(FALSE);

        _DBGINFO((_SYS, "Hardware watchdog exipres, last touch WD sys_delay_wd_stamp = (%d)ms, current time = (%d)ms, wdt_src = (%d)"
                  , DrvTimerGlobalTimerTick2Ms(sys_delay_wd_stamp), DrvTimerGlobalTimerTick2Ms(sys_watchDogHandler_time), wdt_src));
        _DBGINFO((_SYS, "g_ptKePiuWdt->reg_wdt_int=(0x%X), picsr=(0x%X), etmi_0a_clear_status=(0x%X), fiq_raw_status=(0x%X)"
                  , reg_wdt_int, picsr, etmi_0a_clear_status, fiq_raw_status));
        _ERROR((_SYS | FATAL, "Hardware watchdog exipres, current Task:%d", MsCurrTask()));
    }
    // else DBB WDT INT will be done in etmi0[15]

#elif defined(__CHIPDRV_INFINITY_WDT__)
    extern u32 GetSpsr(void);
    u32 spsrRet = 0;
    DrvWDTimer0Enable(FALSE);
    DrvWDTimer0IntEnable(FALSE);
    DrvWDTimer0Enable(TRUE);

    spsrRet = GetSpsr();

    UartSendTrace("Hardware watchdog exipres, current Task:%d, Spsr = 0x%0.8x\n", Rtk_CurrentTask,  spsrRet);

    _DBGINFO((_SYS, "Last disable interrupt, CPSR = 0x%0.8x, LR = <SYMBOL> (0x%0.8x), SP = 0x%0.8x", RtkRegisters[3], RtkRegisters[1], RtkRegisters[0]));
    _ERROR((_SYS | FATAL, "Hardware watchdog exipres, current Task:%d, Spsr = 0x%0.8x", Rtk_CurrentTask,  spsrRet));



#else //__CHIPDRV_R2_WDT__
    extern u32 GetSpsr(void);
    u32 spsrRet = 0;
    bool wdtimeout;
    u32 status;

    DrvWDTimer0IsTimeout(&wdtimeout);
    if(wdtimeout)
    {
        /* After watchdog timeout, it must disable watchdog. And then timeout flag can be cleared. */
        DrvWDTimer0Enable(FALSE);
        DrvWDTimer0ClearTimeout();
        DrvWDTimer0GetStatus(&status);

        spsrRet = GetSpsr();

        _DBGINFO((_RTK, "Last disable interrupt, CPSR = 0x%0.8x, LR = <SYMBOL> (0x%0.8x), SP = 0x%0.8x", RtkRegisters[3], RtkRegisters[1], RtkRegisters[0]));
        _DBGINFO((_SYS, "Hardware watchdog exipres, Mask1 = 0x%0.8x, Rawstatus1 = 0x%0.8x, Service1 = 0x%0.8x",
                  g_ptW5IrqControl->u32_Mask1, g_ptW5IrqControl->u32_RawStatus1, g_ptW5IrqControl->u32_Service1));
        _ERROR((_SYS | FATAL, "Hardware watchdog exipres, current Task:%d, reg = 0x%0.8x, Spsr = 0x%0.8x, Mask0 = 0x%0.8x, Rawstatus0 = 0x%0.8x, Service0 = 0x%0.8x",
                Rtk_CurrentTask, status, spsrRet, g_ptW5IrqControl->u32_Mask0, g_ptW5IrqControl->u32_RawStatus0, g_ptW5IrqControl->u32_Service0));
    }
#endif //__CHIPDRV_R2_WDT__
}


void sys_WatchDogIrqInit(void)
{
    DrvWDTimerIsrReg(sys_watchDogHandler);
}

#endif


/****************************************************************************/
/*  Function  : sys_InitINTC                                                */
/*--------------------------------------------------------------------------*/
/*  Scope     : Interrupt controller initialisation INTC                    */
/*                                                                          */
/*  Return    :  none                                                       */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*                    |   |   |   |                                         */
/****************************************************************************/
static void sys_InitINTC(void)
{
    DrvInitInterruptController();

    RtkConnectTimerInterrupt(NULL);
}

/****************************************************************************/
/*  Function  : sys_InitSYSTIM                                              */
/*--------------------------------------------------------------------------*/
/*  Scope     : SYS TIMER initialisation                                    */
/*                                                                          */
/*  Return    :  none                                                       */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*                    |   |   |   |                                         */
/****************************************************************************/

static void sys_InitSYSTIM(void)
{
    DrvSysTimerInit();

#if defined(__CHIPDRV_R2_WDT__) // for __G1__
    DrvWDTimer0IntEnable(TRUE);
#elif defined(__CHIPDRV_INFINITY_WDT__)
#ifdef __RTK_WATCHDOG_DIAGNOSE_ENHANCE__
    DrvWDTimer0IntEnable(TRUE);
#else
    DrvWDTimer0IntEnable(FALSE);
#endif
#else //__CHIPDRV_R2_WDT__
#ifdef __SOFTWARE_WATCHDOG__
    rtk_SoftwareWatchDogCounts = SysTimerWdogctrlLen;      // reset software watch dog counter
#endif //__SOFTWARE_WATCHDOG__

#ifdef __RTK_WATCHDOG_DIAGNOSE_ENHANCE__
    DrvWDTimer0IntEnable(TRUE);
    DrvWDTimer1IntEnable(TRUE);
#else
    DrvWDTimer0IntEnable(FALSE);
    DrvWDTimer1IntEnable(FALSE);
#endif

    DrvWDTimer1IntEnable(FALSE);
#endif // __CHIPDRV_R2_WDT__
}

/**
 * \fn     const static void sys_AnalogBaseBandInit(void);
 * \brief Initializes the Analog Base Band Driver and does some basic pre - settings
 * \return 	none
 */
/****************************************************************************/
/*  Function: sys_HardwareInit                                              */
/*--------------------------------------------------------------------------*/
/*  Scope   : Boot time HW related initializations                          */
/*                                                                          */
/*                                                                          */
/*  Return    :                                                             */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
static void sys_HardwareInit(void)
{
    hal_uart_hw_init();
#ifndef __DBG_PORT_UART2__
    hal_uart_debug_init(1);
#else
    hal_uart_debug_init(2);
#endif

    //UartSendTrace("\n***sys_premain_first:CPU(312MHz)/EMI(Burst/Burst 156MHz)***\n");
}

// this part is to get target version infor
// It's not mandatory for the code flow, but we still need this to avoid
// target tool info's are removed from linking

#ifdef __FIXME__
#include "acc_msg_pub_types.h"   /* For send message */

extern const char sw_verInfo[64];
extern const u8 sw_toolInfo_header[6];
extern const u8 sw_toolItem_number;
extern const u8 sw_toolItem_format;
extern const u8 sw_toolItem_header_1[8];
extern const u8 sw_toolItem_version_1[8];
extern const u8 sw_toolItem_header_2[8];
extern const u8 sw_toolItem_version_2[8];
extern const u8 sw_toolItem_header_3[8];
extern const u8 sw_toolItem_version_3[8];
extern const u8 sw_toolItem_header_4[8];
extern const u8 sw_toolItem_version_4[8];
extern const u8 sw_toolItem_header_5[8];
extern const u8 sw_toolItem_version_5[8];
extern const dev_sw_toolInfo_S sw_toolInfo[];


u8 * swVersionTemp = NULL;
u8 * swToolInfoHeader = NULL;
u8 swToolItemNumber = 0;
u8 swToolItemformat = 0;
u8 * swBootVectors = NULL;
u8 * swResectVectors = NULL;

dev_sw_toolInfo_S * swToolInfoPtr = NULL;

extern u8 * __BootEntry;
//extern u8 * __ResetVector;

void getSwVersion(void)
{
    swVersionTemp = (u8 *) sw_verInfo;
    swToolInfoHeader = (u8 *) sw_toolInfo_header;
    swToolItemNumber = (u8) sw_toolItem_number;
    swToolItemformat = (u8) sw_toolItem_format;

    swToolInfoPtr = (dev_sw_toolInfo_S *) sw_toolInfo;

    swBootVectors = __BootEntry;
//	swResectVectors = __ResetVector;
}
#endif

#ifdef __ISW_NORBOOT__
__RO_CODE_ON_BOOT__ void _do_decompress( u32 u32_cmpr )
{
    extern u32 __start_BSS_RESET;
    extern u32 __stop_BSS_RESET;
    extern u32 __bss_start__;
    extern u32 __bss_end__;
    extern u32 __load_start_copy;
    extern u32 __load_size_copy;
    extern u32 Image$$XRAM0$$Base;

    /* init bss */
    memset((u32*)&__start_BSS_RESET, 0, ((u32)&__stop_BSS_RESET - (u32)&__start_BSS_RESET));
    memset((u32*)&__bss_start__, 0, ((u32)&__bss_end__ - (u32)&__bss_start__));

    memcpy(&Image$$XRAM0$$Base, &__load_start_copy, (u32)&__load_size_copy);

}
#endif

u32* sys_get_heap_start_address()
{
#if !defined(__COMPRESS_SELECTED_BIN__)
    return (u32 *) &Image__ZI__Limit;
#else
    //return _take_memory_from_uninitial_heap( BOOT_MEM_HEAP_START_ADDR );
#endif
}

// pls be careful to use this function at the sys premain stage!
// The imi2 end address will be occupied by 2 words WDT flags
// check WDOG_FLAG_TO_IMI_WA option for details
__RO_CODE_ON_BOOT__ u32 sys_get_imi2_end_address(void)
{
    return (IMI2_END_ADDRESS);
}

__RO_CODE_ON_BOOT__ void sys_set_WDogRstFlag(u32 value)
{
#ifndef WDOG_FLAG_TO_IMI_WA
    sys_ExpectedWDogRst = value;
#else
    u32 *redirect_addr = (u32 *)(sys_get_imi2_end_address() - sizeof(u32) + 1);
    *redirect_addr = value;
#endif
}

__RO_CODE_ON_BOOT__ u32 sys_get_WDogRstFlag(void)
{
#ifndef WDOG_FLAG_TO_IMI_WA
    return (sys_ExpectedWDogRst);
#else
    u32 *redirect_addr = (u32 *)(sys_get_imi2_end_address() - sizeof(u32) + 1);
    return (*redirect_addr);
#endif
}

__RO_CODE_ON_BOOT__ void sys_set_WDogRstExtFlag(u32 value)
{
#ifndef WDOG_FLAG_TO_IMI_WA
    sys_ExpectedWDogRstExt = value;
#else
    u32 *redirect_addr = (u32 *)(sys_get_imi2_end_address() - 2 * sizeof(u32) + 1);
    *redirect_addr = value;
#endif
}

__RO_CODE_ON_BOOT__ u32 sys_get_WDogRstExtFlag(void)
{
#ifndef WDOG_FLAG_TO_IMI_WA
    return (sys_ExpectedWDogRstExt);
#else
    u32 *redirect_addr = (u32 *)(sys_get_imi2_end_address() - 2 * sizeof(u32) + 1);
    return (*redirect_addr);
#endif
}


#if 1 //for test

#define REG_GPIO_OEN (1<<5)
#define REG_GPIO_OUT (1<<4)
#define RIU_BASE_ADDR 0x1F000000
#define BANK_PAD_TOP 0x103C00

enum
{
    REG_GPIO0       = 0x00,
    REG_GPIO1       = 0x01,
    REG_GPIO2       = 0x02,
    REG_GPIO3       = 0x03,
    REG_GPIO4       = 0x04,
    REG_GPIO5       = 0x05,
    REG_GPIO6       = 0x06
};


#define READ_WORD(_reg)             (*(volatile unsigned short*)(_reg))
#define WRITE_WORD(_reg, _val)      (*((volatile unsigned short*)(_reg))) = (unsigned short)(_val)



void InfinityWriteReg(unsigned char nAddr, unsigned short regMsk, unsigned short nValue)
{
    unsigned short nConfigValue;
    nConfigValue = READ_WORD(RIU_BASE_ADDR + (BANK_PAD_TOP << 1)  + ((nAddr) << 2));
    nConfigValue &= ~regMsk;
    nConfigValue |= (nValue & regMsk);
    //WriteBank1Reg(nAddr, nConfigValue);
    WRITE_WORD(RIU_BASE_ADDR + (BANK_PAD_TOP << 1)  + ((nAddr) << 2), nConfigValue);
}

unsigned short InfinityReadReg(unsigned char nAddr)
{
    return READ_WORD(RIU_BASE_ADDR + (BANK_PAD_TOP << 1) + ((nAddr) << 2));
}

void vParTestInitialise(void)
{
    int i;
    for(i = 0; i < 6; i++)
        InfinityWriteReg((unsigned char)i, REG_GPIO_OEN, 0);

}

void vParTestToggleLED(unsigned long ulLED)
{
    unsigned short nConfigValue;
    nConfigValue = InfinityReadReg((unsigned char)ulLED);
    nConfigValue &= REG_GPIO_OUT;
    InfinityWriteReg((unsigned char)ulLED, REG_GPIO_OUT, (nConfigValue) ? 0 : REG_GPIO_OUT);
}
#endif

volatile u32 count = 0;

void vTestHandler(void)
{
#ifdef MS_IRQ_TEST
    UartSendTrace("vTestHandler in %d!!!!!\n", READ_WORD(RIU_BASE_ADDR + (0x100900 << 1) + (0x5E << 2)));
    WRITE_WORD(RIU_BASE_ADDR + (0x100900 << 1) + (0x52 << 2), 0);
#else
    UartSendTrace("vTestHandler in %d!!!!!\n", READ_WORD(RIU_BASE_ADDR + (0x100900 << 1) + (0x4C << 2)));
    WRITE_WORD(RIU_BASE_ADDR + (0x100900 << 1) + (0x40 << 2), 0);
#endif

    if(count == 0)
        count = 1;
    else
        count = 0;
}

/****************************************************************************/
/*  Function: i_sw_main                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : This function is called from the sys_premain_second           */
/*            and launches the i_sw main function.                          */
/*            This function is one simple entry to init UART and            */
/*            hardware testing functions.                                   */
/*                                                                          */
/*  Return    : (s32) main's return code                                    */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/

/*s32 i_sw_main()
{
	extern void menu_Task(void);

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION>120000)
    //Initialization of the locale
    setlocale(LC_ALL,"C");
#endif

	sys_Enable_cache();

#ifdef __FIXME__
	getSwVersion();
#endif
	menu_Task();

	return 0;
}*/

s32 i_sw_main()
{
    //extern void menu_Task(void);
    volatile u32 ul;
    volatile u32 ulLoop = 0;
    const u32 ulMax = 0xffffff;
    IntInitParam_u uIntcParam;
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION>120000)
    //Initialization of the locale   setlocale(LC_ALL,"C");
#endif
#ifdef MS_IRQ_TEST
    uIntcParam.intc.eMap = INTC_MAP_IRQ;
    uIntcParam.intc.ePriority = INTC_PRIORITY_7;
    uIntcParam.intc.pfnIsr = vTestHandler;
    MsInitInterrupt(&uIntcParam, MS_INT_NUM_IRQ_BACH);
    MsUnmaskInterrupt(MS_INT_NUM_IRQ_BACH);
#else
    uIntcParam.intc.eMap = INTC_MAP_FIQ;
    uIntcParam.intc.ePriority = INTC_PRIORITY_7;
    uIntcParam.intc.pfnIsr = vTestHandler;
    MsInitInterrupt(&uIntcParam, MS_INT_NUM_FIQ_TIMER_0);
    MsUnmaskInterrupt(MS_INT_NUM_FIQ_TIMER_0);
#endif
    UartSendTrace("i_sw_main!!!!!\n");
    //getSwVersion();
    vParTestInitialise();
    //menu_Task();
    for(;;)
    {
        for(ul = 0; ul < ulMax; ul++)
        {
        }

        if(count == 0)
        {
            vParTestToggleLED(0);
            vParTestToggleLED(1);
            vParTestToggleLED(2);
            vParTestToggleLED(3);
            vParTestToggleLED(4);
            vParTestToggleLED(5);
            vParTestToggleLED(6);
        }
        ulLoop++;
        if(ulLoop == 20)
        {
            UartSendTrace("interrupt!!!!!\n");
#ifdef MS_IRQ_TEST
            WRITE_WORD(RIU_BASE_ADDR + (0x100900 << 1) + (0x52 << 2), 1 << 10); //bach
#else
            WRITE_WORD(RIU_BASE_ADDR + (0x100900 << 1) + (0x40 << 2), 1);
#endif
            ulLoop = 0;
        }
    }
    return 0;
}


/****************************************************************************/
/*  Function: sys_SetRamSizeVariables                                       */
/*--------------------------------------------------------------------------*/
/*  Scope   : Set sys_RAMSize                                               */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/

#if !defined(__INFINITY__)
#if defined(__FPGA__)
const u32 limitRAMsSize = 0x1F0000;
#else
const u32 limitRAMsSize = 0x4000000;//64 MB //0x680000;
#endif

void sys_SetRamSizeVariables(void)
{
    u32 top;
    //u32 size = 0x2000000; // 32 MB;
    u32 size = 0x8000000; // 128 MB;
    u32 next;

    // the princple is to write after the end of the memory (located in MEM1 space
    // if we read the same value at the same adress divided by two, it means that the MSB
    // bit is not used, so we can divide the size by two
    // if the value is different, it means that we have reached the RAM size.
#ifndef __NAND__
    top = MEM1_START_ADDRESS + size;
    *(u32*)(top - 4) = (u32) top;
    next = MEM1_START_ADDRESS + size / 2;
    while(*(u32*)(top - 4) == *(u32*)(next - 4))
    {
        size /= 2;
        top = MEM1_START_ADDRESS + size;
        *(u32*)(top - 4) = (u32) top;
        next = MEM1_START_ADDRESS + size / 2;
    }
#else
    top = SDRAM_START_ADDRESS + size;
    *(u32*)(top - 4) = (u32)top;
    next = SDRAM_START_ADDRESS + size / 2;
    while(*(u32*)(top - 4) == *(u32*)(next - 4))
    {
        size /= 2;
        top = SDRAM_START_ADDRESS + size;
        *(u32*)(top - 4) = (u32)top;
        next = SDRAM_START_ADDRESS + size / 2;
    }
#endif
    sys_RAMSize = (u32) size;

#ifndef __HWL_TINY__
#if defined(__3M_RAM_BUFFER__)
    if(sys_RAMSize == 0x400000)
    {
        while(1)
        {
            DrvRtcPowerCtrl(FALSE);
        }
    }

#endif

#if defined(__512K_RAM_BUFFER__)
    if(sys_RAMSize == 0x800000)
    {
        while(1)
        {
            DrvRtcPowerCtrl(FALSE);
        }
    }

#endif
#endif

    if(sys_RAMSize > limitRAMsSize)
    {
        sys_RAMSize = limitRAMsSize;
    }
}

#else
#define REG_DRAM_SIZE_MSK 0xF
#define REG_DRAM_SIZE_OFFSET 12
u32 limitRAMsSize = SYS_PHY_RAM_SIZE_SETTING;
__RO_CODE_ON_BOOT__ void sys_SetRamSizeVariables(void)
{
    u16 nConfigValue = *(u16*)GET_REG_ADDR(MS_BASE_REG_MIU_PA, 0x69);
    nConfigValue =(nConfigValue & (REG_DRAM_SIZE_MSK<<REG_DRAM_SIZE_OFFSET))>>REG_DRAM_SIZE_OFFSET;

    switch(nConfigValue)
    {
        case 9:
            sys_RAMSize = 0x20000000;
            break;
        case 8:
            sys_RAMSize = 0x10000000;
            break;
        case 7:
            sys_RAMSize = 0x8000000;
            break;
        case 6:
            sys_RAMSize = 0x4000000;
            break;
        case 5:
            sys_RAMSize = 0x2000000;
            break;
        default:
            //sys_RAMSize = 0x2000000;
            sys_RAMSize = 0x8000000;
    }
    //Protect calculated ram size over limited ram size
    if (sys_RAMSize > limitRAMsSize)
    {
         sys_RAMSize = limitRAMsSize;
    }
    else
        limitRAMsSize = sys_RAMSize;

    UartSendTrace("RAM Size %dMB\n",sys_RAMSize>>20);
    UartSendTrace("git:289dc6600449c768798e74d77111d49a47df6cc5\n");
}
#endif

/****************************************************************************/
/*  Function: sys_premain                                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   : This function is called from the boot routine                 */
/*            and launches the main function.                               */
/*            This function can be used to perform initialisations          */
/*            (esp. HW related) before entering the main entry point.       */
/*                                                                          */
/*  Return    : (s32) main's return code                                    */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void sys_premain_first(void)
{
    bool WatchDogStatus;
    bool WatchDogStatus1;
    // Bravo U01 patch
    //    sys_ChipId_e revision_id;

    preBootUpSequence = sys_HwWdtDebugData.nBootUpSequence;

#if 1
    /* System Timer initialization */
    sys_InitSYSTIM();

#ifndef __FPGA__
    DrvClkgenInit(CLKGEN_800MHZ);
#endif

#if 0   // Bravo U01 patch
    revision_id = sys_GetChipRevisionId();

    if(CHIP_ID(BRAVO, U01) == revision_id)  // U01
    {
        //--Rex RTC 32K Workaround
        *(volatile u16 *)(0x3400002C) = 0x03;

        //--Liang BootRom Workaround
        *(volatile u16 *)(0x74007D3C) = 0xFFFF;
    }
    else    // U02 or latest
    {
        // do nothing
    }
#endif

#ifdef __I_SW_BOOTFAST__
    /* EMI initialization */
    //DrvEmiInitEmi();
#ifndef __NAND__
    /* EMI NOR initialization */
    //DrvEmiInitNor(CLKGEN_156MHZ, NULL);

    /* EMI SRAM initialization */
    //DrvEmiInitSram(CLKGEN_156MHZ, NULL);

    // Set EMI clock to 156MHz
    //*(volatile u32 *)(0x74007d78) = 0x00000058;
#endif

    //sys_SetRamSizeVariables(); // TODO: check where to issue this function is better

    /* Call Hardware Init */
    sys_HardwareInit();

#endif //__I_SW_BOOTFAST__

    // Check Debug
    // Reset Debug Area markers
    SysDebugStruct.WatchdogResetOccured = FALSE;
    SysDebugStruct.ExpectedWatchdogReset = FALSE;

    // Get Watchdog Reset Status
    DrvWDTimer0IsTimeout(&WatchDogStatus);
    DrvWDTimer1IsTimeout(&WatchDogStatus1);

    sys_HwWdtDebugData.nBootUpSequence = 17;

    if(0x8642753a == sys_get_WDogRstExtFlag())
    {
        DrvWDTimer0ClearTimeout();
        DrvWDTimer1ClearTimeout();
        SysDebugStruct.LastUsedHapcPort = 0;
        SysDebugStruct.ResetCause = SYS_DDA_FAKE_SHUTDOWN_BY_WDT;
        return;

    }

    sys_HwWdtDebugData.nBootUpSequence = 18;

    // If Watchdog Reset has not happened, return;
    if(!WatchDogStatus && !WatchDogStatus1)
    {
        SysDebugStruct.LastUsedHapcPort = 0;
        SysDebugStruct.ResetCause = SYS_DDA_NO_RESET;
        return;
    }

    sys_HwWdtDebugData.nBootUpSequence = 19;

    // Otherwise clear it
    DrvWDTimer0ClearTimeout();
    DrvWDTimer1ClearTimeout();

    SysDebugStruct.WatchdogResetOccured = TRUE;

    SysDebugStruct.CustomerWatchdogReset = sys_CustomerWDogRst;
    // Check if Watchdog Reset was expected
    if(sys_get_WDogRstFlag() == 0x13572468)
    {
        SysDebugStruct.ExpectedWatchdogReset = TRUE;
        return;
    }

    // Not Expected Watchdog Reset
    SysDebugStruct.ResetCause = SYS_DDA_UNWANTED_RESET;
    //- Save debug data after watchdog reset
#if defined(__RTK_DBG_INFO__)
    SysDebugStruct.hac_GlobalFn = 0;//hac_GlobalFn; //
    SysDebugStruct.RtkRegisters[0] = RtkRegisters[0];
    SysDebugStruct.RtkRegisters[1] = RtkRegisters[1];
    SysDebugStruct.RtkRegisters[2] = RtkRegisters[2];
    SysDebugStruct.RtkRegisters[3] = RtkRegisters[3];
#endif
    SysDebugStruct.Rtk_CurrentTask = Rtk_CurrentTask; //

#ifdef __REAL_TIME_PROBLEM_DIAGNOSE__
    {
        SysDebugStruct.sys_LastPcDisablingIt[0] = g_apSysLastPcDisablingIt[0];
        SysDebugStruct.sys_LastPcDisablingIt[1] = g_apSysLastPcDisablingIt[1];
        SysDebugStruct.sys_LastPcDisablingIt[2] = g_apSysLastPcDisablingIt[2];
        SysDebugStruct.sys_LastPcDisablingIt[3] = g_apSysLastPcDisablingIt[3];

        SysDebugStruct.sys_LastPcDisablingItCpsr[0] = g_anSysLastPcDisablingItCpsr[0];
        SysDebugStruct.sys_LastPcDisablingItCpsr[1] = g_anSysLastPcDisablingItCpsr[1];
        SysDebugStruct.sys_LastPcDisablingItCpsr[2] = g_anSysLastPcDisablingItCpsr[2];
        SysDebugStruct.sys_LastPcDisablingItCpsr[3] = g_anSysLastPcDisablingItCpsr[3];

        SysDebugStruct.sys_LastPcDisablingItIndex = g_nSysLastPcDisablingItIndex;
    }
    SysDebugStruct.sys_ActiveIsr = g_pSysActiveIsr;
    SysDebugStruct.sys_CpsrSnapShot = g_nSysCpsrSnapShot;
#endif

    // Store registers in data debug area
    StoreARMRegisters((u32) & (SysDebugStruct.ARMRegisters[0]));

    sys_HwWdtDebugData.nBootUpSequence = 20;

    sys_HwWdtDebugData.nBootUpSequence = preBootUpSequence;

#ifdef __FIXME__
    sys_BackTrace_analysis_HWD();
#endif

    sys_HwWdtDebugData.nBootUpSequence = 49;

#endif

}

/****************************************************************************/
/*  Function: sys_premain                                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   : This function is called from the boot routine                 */
/*            and launches the main function.                               */
/*            This function can be used to perform initialisations          */
/*            (esp. HW related) before entering the main entry point.       */
/*                                                                          */
/*  Return    : (s32) main's return code                                    */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/


s32 sys_premain_second(void)
{
    sys_SetRamSizeVariables(); // TODO: check where to issue this function is better

#if 1//#ifdef __MV5_FPGA__
    DrvClkgenInit(CLKGEN_800MHZ);
#endif
    DrvClkgenInitSec();

    /* Interrupt controller initialization */
    sys_InitINTC();
    // DrvRiuSwInterruptInit();

#ifndef __FPGA__
    //if (HALUTIL_IS_BOOT_ROM2NOR())
    {
        sys_MemInit();
    }
#endif
    // init Power Down manager
    //sys_PowerDownModeInit();
#ifndef __I_SW_BOOTFAST__
    /* Call Hardware Init */
    sys_HardwareInit();
    /* Allocation table initialization */
    //DrvIoRcmInit();
#endif

#ifdef __RTK_WATCHDOG_DIAGNOSE_ENHANCE__
    sys_WatchDogIrqInit();
#if defined(__G1__)
    sys_WatchDogDbbIrqInit();
#endif
#endif
    /* Internal ram initialization */
    //sys_iram_allocate();
    //sys_init_dynamic_mem_iram();

    /* Tail continuation with the actual main function */
    // sys_Enable_cache();
    //__enable_irqfiq();

    UartSendTrace("nBootUpSequence = %d", sys_HwWdtDebugData.nBootUpSequence);
   // UartSendTrace("\n***sys_premain_second:CPU(312MHz)/EMI(Burst/Burst 156MHz)***\n");

//#define INREG16(addr)       (*(volatile u16 *)(addr))
//    UartSendTrace("0xh53 =0x%x\n", (u32)INREG16(0x1f203d4c));
//    UartSendTrace("0xh03 =0x%x\n", (u32)INREG16(0x1f203c0c));

#ifdef __I_SW_OS__
    return main();
#else
    return i_sw_main();
#endif
}

void __rt_raise(u32 signal, u32 type)
{
    while(1) ;
}

s32 hac_GlobalFn = 0;

#include "sys_irq_ctrl_pub_types.h"
#include "sys_irq_ctrl_pub_api.h"

// The dependency of I-SW is a total chaos
// Dummy function put here to pass building: FIXME or REMOVEME
//void frai_SetProtection(void){}
//void frai_UnsetProtection(void){}
#ifndef __NAND__
//void * frai_store_alloc (int w_size){return 0;}
//void frai_store_free (int    w_size, void * address){}
//void frai_store_stats (int * stats){}
//void frai_recycle (void){}
//int fms_rai_gc (int * opaque){return 0;}
//void fms_E2pCleaner(void){}
//void frai_store_init(void * base_addr,     // base address of the sectors
//                     int    sector_size,  // size of a sector
//                     int    num_sectors,  // number of sectors
//                     void * private_mem){}  // externally allocated storage
//int frai_store_query_size (unsigned int num_sectors) {return 0;}
//s32 vm_e2pRead(u32 E2pToReadAdress, u32 Size, void *pDest){return 0;}
//s32 vm_e2pWrite(u32 E2pToWriteAdress,  u32 Size, const void *pSrc){return 0;}
//const int fms_rai_gc_preventive;
#endif
//void fms_E2pInterfaceInit(void *i__p_Buffer, u32 i__u32_BufferSize){}
//void rm_InterfaceStoreMsg (char OverWriting){}
//char rm_GetInterfaceStoreMsg ( void){return (char)0;}
//void rm_DisableStoreMsg ( void){}
//u32 rm_GetTxBufferPart (u8 **buf, u32 start_pos,  u32 max_size, u32 *effective_size ){return 0;}
//void *rm_UserSend (void *Msg, u8 TargetInfo, u16 Size, u32 Port){return 0;}
void cn_Encode(u8 *cnBackTrace) {}
//s32 fms_E2pRead(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void* o__p_Buffer){return 0;}
//s32 fms_E2pWrite(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void *i__p_Buffer){return 0;}
//char v24_PollRxTx(void){return 0;}
//u32 v24_RequestExt(int Req, u32 Arg, u32 Port){return 0;}

//void trc_CustomErrorProcDiag(u32 id) {}
//void trc_CustomErrorProcNoDiag(u32 id) {}
//void cus_DumpHighSpeedCPUUsage(){}
//void sys_CustomInitProc( int argc, char **argv ){}
//void sys_CustomFrameIntProc ( u16 SleepedFrames ){}
//u8 sys_CustomIdleProc(void){return 0;}
//void sys_CustomIdleProc2(void){}

int CnBackTraceAuxBuf_s;
//const u8 e2p_NbParamForChkSum;
//const e2p_Field_t e2p_ParamForChkSum [];
//u8 v24_SerialOn;
//int Watch1L1c [];
//int Watch2L1c [];
s16 l1c_Watch;
u8 hwl_MaskedIt;
u16 hac_NbSleepedFrames;

// dummy end
