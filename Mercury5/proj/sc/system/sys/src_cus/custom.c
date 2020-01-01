/****************************************************************************/
/*  File    : CUSTOM.C                                                      */
/*--------------------------------------------------------------------------*/
/*  Scope   : Customers concerns.                                           */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/

#include "comdefs.hc"
#include "stdcomp.h"
#include "osdefs.hc"
#include "sys_rtk_ho.h"
#include "kernel.h"
#include "e2p_defs.hi"
#include "fms_insd.hi"
#include "fms_init.h"
#define __E2P_CUST_VAR__
#include "e2p_cust.ho"
#undef __E2P_CUST_VAR__

#include "sys_traces.ho"            /* for trc_CustomXXX prototypes          */

#include "sys_ftr.ho"

//#include "drv_batt_types.h"
//#include "drv_batt_api.h"
#include "drv_timer_types.h"
#include "drv_timer_api.h"

#include "sys_traces.ho"
#include "kernel.h"
#include "remote.ho"

#include "sys_fcm.hi"
#include "sys_reset.h"
#include "drv_emi_sram_nor_pub.h"
#include "sys_mem.h"
#include "sys_tools.h"
#include "sys_queue.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_sys_isw_uart.h" // UartSendTrace
#include "fms_atcmd.h"
#include "drv_clkgen_cmu.h"
#include "sys_speed_profile.h"
#include "sys_rel.hp"

#ifdef __ENABLE_REDIRECT_DEFAULT_TRC__
#include "cus_trace.h"
#endif
#ifndef __CORE_SW_VERSION__
#include "vm_e2p_app.ho"
#endif
#include "sys_rtk_backtrace.h"
//#include "mdl_rai_cache_pub.h"
//#include "hwldsp_getpatch.h"

#ifndef __CORE_SW_VERSION__
#include "vm_e2p_app.ho"
#include "mdl_vfs_fat_parser.h"
#endif

#include "sys_dbg.h"
//#include "mdl_bat_pars_pub.h"

#ifdef __UPGRADE_NVRAM__
#include "fms_nvram.h"
#endif //__UPGRADE_NVRAM__
#ifdef __MBAS__
#include "drv_mbas.h"
#endif //__MBAS__

#include "sys_MsWrapper_cus_os_sem.h"

#if defined (__DPM__) || defined (__MMAP__)
#include "sys_sys_dpm_mgr.h"
#include "sys_arm_copro.h"
#endif
#if defined (__RTK_OVER_ARM_SLDLM__) || defined (__RTK_OVER_ARM_NAND_IMI_SLDLM__)
#include "sys_sys_dlm_mgr.h"
#include "sys_arm_copro.h"
#endif
#include "sys_sys_mmap_mgr.h"
#include "sys_time.h"
#include "sys_sys_bootinit.h"

//#include "sim_glob.h"
//#include "sys_sys_bootinit.h"



#ifdef __FIXME__
/* ------------------------ Memory Pools ------------------------------ */

const cus_InitPool_t cus_InitPool[] =
{
    /* Nb of clusters    ,    Cluster size  ,   NeedProtect */
#ifndef __EMI_POOL_PROTECT__
    { GPRS_NB_CLUST_POOL0,    GPRS_SIZE_CLUST_POOL0, 0 },
    { GPRS_NB_CLUST_POOL1,    GPRS_SIZE_CLUST_POOL1, 0 },
    { GPRS_NB_CLUST_POOL2,    GPRS_SIZE_CLUST_POOL2, 0 },
    { GPRS_NB_CLUST_POOL3,    GPRS_SIZE_CLUST_POOL3, 0 },
    { GPRS_NB_CLUST_POOL4,    GPRS_SIZE_CLUST_POOL4, 0 },
    { GPRS_NB_CLUST_POOL5,    GPRS_SIZE_CLUST_POOL5, 0 }
#else
    { GPRS_NB_CLUST_POOL0,    GPRS_SIZE_CLUST_POOL0, 1 },
    { GPRS_NB_CLUST_POOL1,    GPRS_SIZE_CLUST_POOL1, 1 },
    { GPRS_NB_CLUST_POOL2,    GPRS_SIZE_CLUST_POOL2, 1 },
    { GPRS_NB_CLUST_POOL3,    GPRS_SIZE_CLUST_POOL3, 1 },
    { GPRS_NB_CLUST_POOL4,    GPRS_SIZE_CLUST_POOL4, 1 },
    { GPRS_NB_CLUST_POOL5,    GPRS_SIZE_CLUST_POOL5, 1 }
#endif
};

const u8  cus_NbPool     = sizeof(cus_InitPool) / sizeof(cus_InitPool_t);
#endif

/* ------------------------- E2prom constants --------------------------- */
#define offsetof16(S,F)           (u32) (((u8*)&(((S *) 0)->F))-((u8*)0))

const u16 e2p_FirstErrorStoredOffset = offsetof(Eeprom_t, FirstErrorStored);

/* List of E2prom parameters to be taken into acount for check sum calculation */
const e2p_Field_t e2p_ParamForChkSum [] =
{
//     {E2P_HARDCAPABILITY},
    {E2P_REQUIREDPATCHES},
//     {E2P_TXEN2START},
//     {E2P_TXEN2STOP},
    {E2P_HRUFITHRES},
//     {E2P_ROUGHDACVALUE },
    {E2P_E2PTSTPATTERN },
    {E2P_CLASSMK2      },
    {E2P_IMEI          },
#ifdef __MSTAR_DUAL_SIM_E2P__
    {E2P_IMEI_2        },
#endif
    {E2P_SIGNATURE_PCK },
    {E2P_SIGNATURE_NCK },
    {E2P_SIGNATURE_NSCK},
    {E2P_SIGNATURE_SPCK},
    {E2P_SIGNATURE_CCK },
    {E2P_SIGNATURE_PARAM},
    //{E2P_ADCBATCOEFF}
};
const u8 e2p_NbParamForChkSum = sizeof(e2p_ParamForChkSum) / sizeof(e2p_Field_t);

u32 sys_ExtendedCapability;

u8 sys_lastJtagState = 0;

extern bool bIsUartPrintfEnable;


__ONCE_CALL_ON_BOOT__
void sys_ModuleInit(void)
{
    CusVersion[0] = '\0';
    strcpy((char*)CoreVersion, (const char*)CoreRelease);
}


/**
 * \brief Detect customer binary
 */
__ONCE_CALL_ON_BOOT__ void sys_BinaryInit(void)
{
    /* Detection of binary type */
#ifndef __NAND__

#if defined(__SUPPORT_BUS_FSP_SPI__)
    fms_CoreInit(MEM3_START_ADDRESS);
#else
    fms_CoreInit(MEM0_START_ADDRESS);
#endif

    sys_CustomRomSize = fms_GetDeviceSize();
    //fms_MapInitMainServices(); // in fms_map.c //used for "fms_E2pRawRead" and uses semaphore

    //fms_MapLocateCode();

#endif

    sys_ModuleInit();
    /* Speed profile for CPU and DSP initialization */
    sys_initSpeedProfile();
}

/****************************************************************************/
/*  Function  : trc_CustomErrorProcDiag                                     */
/*--------------------------------------------------------------------------*/
/*  Scope     : Customer fatal error.                                       */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*                    |   |   |   |                                         */
/****************************************************************************/
void trc_CustomErrorProcDiag(u32 id)
{
#ifdef __NEW_AUTO_TESTING__
    extern bool g_bAutoTestingControl;
    extern bool rm_DriverInitialized;
#endif
    extern void backtrace_shutdown_sd(void);

    /* allow 5 seconds for traces */
    sys_DelayWatchDogReset();

#ifdef __NEW_AUTO_TESTING__
    if((rm_DriverInitialized == TRUE) && ((rm_DisableInBacktrace_b & (1 << RM_TXBUFFER1_ERROR)) == 0))
    {
        if(TRUE == v24_UserModeIsUart())    //trace is in UART mode
        {
            if(g_bAutoTestingControl)
            {
#define AUTO_TEST_RESET_PATTERN     ("__RESET____RESET____RESET____RESET____RESET____RESET____RESET____RESET__")
#define AUTO_TEST_RESET_PATTERN_LEN (sizeof(AUTO_TEST_RESET_PATTERN))
#include "string.h"

                //u32 log_auto_test_ourge_ret = 0 ;
                u8 temp[sizeof(u32)/*sizeof(cmdType)*/ + AUTO_TEST_RESET_PATTERN_LEN] = {0};
                TestCmdRes * cmdRes = (TestCmdRes *)&temp[0];

                cmdRes->cmdType = TEST_CMD_GET_RES_BUF ;
                /*lint -e419*/
                strncpy((char*)(&(cmdRes->body)), AUTO_TEST_RESET_PATTERN, AUTO_TEST_RESET_PATTERN_LEN) ;
                /*lint +e419*/

                rm_DisableInBacktraceBitClean(RM_BACKTRACE_ENTRY); //temp enable trace
                rm_UserSend(cmdRes, INFO_AUTOTEST_CMD, AUTO_TEST_RESET_PATTERN_LEN + sizeof(u32), 0);

                //_DBGINFO((_SYS|LEVEL_0,"log_auto_test_ourge_ret=0x%x", log_auto_test_ourge_ret));
                _DBGINFO((_MMI | LEVEL_0, AUTO_TEST_RESET_PATTERN));

                // Go into low user mode (no more UART interrupts) and purge trace buffer
                v24_ForceUserMode();   //purge last INT trace
            }
        }
    }
#endif

#if defined(__RTK_DIAGNOSE_ENHANCE__)
    backtrace_shutdown_sd();
#endif

    ke_FullReset();
}


/****************************************************************************/
/*  Function  : trc_CustomErrorProcNoDiag                                   */
/*--------------------------------------------------------------------------*/
/*  Scope     : Customer fatal error w/o diagnose mode.                     */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*                    |   |   |   |                                         */
/****************************************************************************/
void trc_CustomErrorProcNoDiag(u32 id)
{
    /* Enter low user mode and poll 'till watch dog */
    v24_ForceUserMode();
    for(;;)
    {
        v24_PollRxTx();
    }
}


__ONCE_CALL_ON_BOOT__ void sys_CustomInitProcError(int line)
{
    _ERROR((_SYS | FATAL, "Custom.c sys_CustomInitProc __LINE__ [%d]", line));
}


/****************************************************************************/
/*  Function  : sys_CustomInitProc                                          */
/*--------------------------------------------------------------------------*/
/*  Scope     : Customer variables initialisation.                          */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*                    |   |   |   |                                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
__ONCE_CALL_ON_BOOT__ void sys_CustomInitProc(int argc, char **argv)
{
    u32 sysFeature;
    u16 nIsUartPrintfEnable;
    u8 nTimeZone;

#ifndef __CORE_SW_VERSION__
    u8       nMMIRunMode = 0;
    u8       e2p_DisableErrorTraceInFacMode = 1;
#endif
#if defined (__DPM__) || defined (__MMAP__) || (defined (__RTK_OVER_ARM_SLDLM__) && !defined(__BOOT_SLDLM__)) || defined (__RTK_OVER_ARM_NAND_IMI_SLDLM__)
    u32 vaddr;
#endif
#if defined (__DPM__) || defined (__MMAP__)
    extern u32 sys_dp_reset_coarse_page_table(u32 vAddr);
    u32 ret_dp;
#endif
#if defined (__EMMI_SLDPM__)
    extern DpmCusInfo_t g_stEmmiSldpmCusInfo;
    extern u32 DpmEmmiSldpmRaiObjects[];
    u8 nRet;
    pDpmCtrlBlk_t pDpmCtrlBlk;
#endif
#if defined (__EMMI_SLDPM__) || defined (__CUS_WHOLE_PACKAGE_COMPRESS__)
    bool bRet;
#endif

#ifdef __G1__
    fms_NvramInterfaceInit();
#endif //__UPGRADE_NVRAM__

    /*
    ** Initialisation of rm (hapc)
    */
    rtk_MbxHook = rm_MbxHook;

    sys_HwWdtDebugData.nBootUpSequence = 200;

    rm_InitTraceDrivers();

    sys_HwWdtDebugData.nBootUpSequence = 201;

    rm_Init();

    sys_HwWdtDebugData.nBootUpSequence = 202;

#ifndef __MCP_WITHOUT_NOR__
    //fms_ServicesInit();
#ifndef __CORE_SW_VERSION__

    sys_HwWdtDebugData.nBootUpSequence = 203;

#if !defined(__CORE_SOFTWARE__)
    /*lint -e611 */
#ifdef __FIXME__
    rai_cacheMemoryInit((pFuncToFlush *)((void*)fat_ready_to_flush_rai));
#endif
    /*lint +e611 */
#endif

    sys_HwWdtDebugData.nBootUpSequence = 204;

#endif
#endif // __MCP_WITHOUT_NOR__


#ifdef __FIXME__

#if defined(__TARGET_DSP_PATCH_SOLO_BIN__)
    /*
     * Load DSP patch info table into memory
     */
    hwldsp_LoadPatchInfoTable();
#endif

    sys_HwWdtDebugData.nBootUpSequence = 205;

    SysQueueRtInit();
    MsmmapRtInit();
    {
        extern u32 sys_RAMSize;
        u32 nSize;

        nSize = (sys_RAMSize >> 2);

        if((1 << 20) > nSize)
            nSize = (1 << 20);
        else
            nSize = (nSize + (1 << 20) - 1) & ~((1 << 20) - 1);

        MsHMEMVMACreate(ms_memoryhandle, VMALLOC_START_ADDRESS, nSize, VMA_PAGE_1K);
    }

    sys_HwWdtDebugData.nBootUpSequence = 206;

#if defined (__DPM__) && !defined (__RTK_OVER_R2__)
    for(vaddr = DPM_START_ADDR; vaddr < DPM_END_ADDR; vaddr += 0x100000)
    {
        ret_dp = sys_paging_reset_coarse_page_table(vaddr, DPM_PAGING);
        if(!(ret_dp == ERR_MMU_NO_ERROR))
            sys_CustomInitProcError(__LINE__);
    }
#endif
#if defined (__MMAP__) && !defined (__RTK_OVER_R2__)
    for(vaddr = MMAP_START_ADDRESS; vaddr < MMAP_END_ADDRESS; vaddr += 0x100000)
    {
        ret_dp = sys_paging_reset_coarse_page_table(vaddr, MMAP_PAGING);
        if(!(ret_dp == ERR_MMU_NO_ERROR))
            sys_CustomInitProcError(__LINE__);
    }
#endif
#if defined (__EMMI_SLDPM__)
    bRet = DpmInitRaiObjects(M_DPM_APP_EMMI_SLDPM_START, M_DPM_APP_EMMI_SLDPM_END, &DpmEmmiSldpmRaiObjects[0]);
    if(!(bRet == TRUE))
        sys_CustomInitProcError(__LINE__);

    /* EMMI SLDPM Init Here */
    bRet = DpmInitCusInfo(DPM_APP_EMMI_SLDPM, &g_stEmmiSldpmCusInfo);
    if(!(bRet == TRUE))
        sys_CustomInitProcError(__LINE__);
    pDpmCtrlBlk = DpmSetEmmiSldpmDpmCtrlBlk();
    nRet = DpmLoadModule(DPM_APP_EMMI_SLDPM, pDpmCtrlBlk);
    if(!(nRet == DPM_OK))
        sys_CustomInitProcError((__LINE__));
#endif

#if (defined (__RTK_OVER_ARM_SLDLM__) && !defined(__BOOT_SLDLM__)) || defined (__RTK_OVER_ARM_NAND_IMI_SLDLM__)
    {
        extern u32 sys_sldlm_reset_coarse_page_table(u32 vAddr/* 1MB aligned */, u8 type);
        u32 ret_sldlm;

        for(vaddr = USR_SLDLM_START_ADDR; vaddr < USR_SLDLM_END_ADDR; vaddr += 0x100000)
        {
            ret_sldlm = sys_sldlm_reset_coarse_page_table(vaddr, USR_SLDLM);
            if(!(ret_sldlm == ERR_MMU_NO_ERROR))
                sys_CustomInitProcError((__LINE__));
        }
        for(vaddr = SYS_SLDLM_START_ADDR; vaddr < SYS_SLDLM_END_ADDR; vaddr += 0x100000)
        {
            ret_sldlm = sys_sldlm_reset_coarse_page_table(vaddr, SYS_SLDLM);
            if(!(ret_sldlm == ERR_MMU_NO_ERROR))
                sys_CustomInitProcError((__LINE__));
        }
    }
#endif

#if defined (__DPM__) || defined (__MMAP__) || defined (__RTK_OVER_ARM_SLDLM__) || defined (__RTK_OVER_ARM_NAND_IMI_SLDLM__)
    MsInitSemExtend(DPM_SCHED_SEM, 512, 0);
    MsInitSemExtend(DPM_KERNEL_SEM, 1, 1);
    MsInitSemExtend(DPM_SERIAL_SEM, 1, 1);
    MsInitSemExtend(DPM_CONF_SEM, 1, 1);
#endif

#if defined (__CUS_WHOLE_PACKAGE_COMPRESS__)
    bRet = sys_CusLangPackDecompress();
    if(!(TRUE == bRet))
        sys_CustomInitProcError((__LINE__));
#endif

    sys_HwWdtDebugData.nBootUpSequence = 207;

    /* init of FTR must be done before testing Quick Off and after initialising E2P and sys_ModuleInit */
    sys_InitFtrCtx();

#endif // __FIXME__

    e2p_Read(E2P_SYSFEATURE, &sysFeature);

    UartSendTrace("E2P_SYSFEATURE = 0x%x\n", sysFeature);

    /*  2011/05/02 Introduce SysFeature Bit[3] for debugging HW WDT RESET PR.
    **      |-----------------------------------------------------------------------------------------------
    **      | SysFeature          |           0x0          |         0x1           |        0x9           |
    **      |-----------------------------------------------------------------------------------------------
    **      | Exception & Assert  |  Backtrace & Reset     | Backtrace & No Reset  |   Backtrace & Reset   |
    **      | HW WDT Expired      |  Backtrace & Reset     |        No Reset       |   Backtrace & Reset   |
    **      | HW WDT RESET        |  Reset then backtrace  |        No Reset         |       No Reset        |
    **      | JTAG Power          |          OFF           |           ON          |           OFF         |
    **      | Sleep/Wakeup (G1)   |          ON            |           ON          |           ON          |
    **      | Sleep/Wakeup (B3)   |          ON            |           OFF         |           ON          |
    **      ------------------------------------------------------------------------------------------------
    */

    // Bit[0] of E2P_SYSFEATURE enables (if 1) or disables (if 0) usage of JTAG
    // in fact, it just disables Watchdog Reset to enable JTAG breakpoints
    sys_SetJtagState(sysFeature & SYS_FEATURE_JTAG_ENA);
#if 1 //ken: marked here to use JTAG?
    sys_lastJtagState = sys_GetJtagState();
#if 1 //TBD //defined(__MV5_FPGA__) //Disable watchdog in FPGA environment.
    sys_lastJtagState = 1;
#endif
    if(sys_lastJtagState == 0)
    {
        DrvWDTimer0Enable(TRUE);
        DrvWDTimer1Enable(TRUE);
        // cut CPU_DBG and DSP_DBG in CMU to save power if not used
        DrvClkgenEnablePower(PERIPH_JTAG, FALSE);

#if defined (__MBAS__)
        /* Init MMP MBAS instance 0: snoop EMI data */
        DrvMbasMmpInstInit(0);
        p_mbas_st mbas_0_ptr = (p_mbas_st)(MMP_MBAS_0_BASE);

        /* Basic detection strategy: Text section and rodata is set to read-only */
        HalMbasSetRegion(mbas_0_ptr, 0, TEXT_LMA_START - MMP_MBAS0_BASE, TEXT_LMA_END - MMP_MBAS0_BASE, PERM_RD, 1);
        HalMbasSetRegion(mbas_0_ptr, 1, RODATA_LMA_START - MMP_MBAS0_BASE, RODATA_LMA_END - MMP_MBAS0_BASE, PERM_RD, 1);
#endif //__MBAS__
    }
    else
#endif
    {
        if(sysFeature & SYS_FEATURE_WDT_ISSUE_DBG_ENA) //don't enable JTAG when bit 3 is set
        {
            DrvClkgenEnablePower(PERIPH_JTAG, FALSE);
#if defined(__R2_WATCHDOG__)
            HalWDTimer0IntEnable(TRUE);
#endif
        }

        DrvWDTimer0Enable(FALSE);
        DrvWDTimer1Enable(FALSE);
    }

    sys_HwWdtDebugData.nBootUpSequence = 208;

    // Bit[1] of E2P_SYSFEATURE enables (if 1) or disables (if 0) Synchronous burst access to NOR and PSRAM
    // (if allowed by the memory itself of course)
    if(sysFeature & SYS_FEATURE_MCP_SYNC_ACCESS_ENA)
    {
        sys_ActivateBurstNor(TRUE);
        sys_ActivateBurstRam(TRUE);
    }

    // Bit[2] of E2P_SYSFEATURE enables (if 0) or disables (if 1) Enhanced Backtrace
    if(sysFeature & SYS_FEATURE_ENHANCED_BACKTRACE_ENA)
    {
        EnhancedBacktraceEnable = FALSE;
    }

    // Bit[3] of E2P_SYSFEATURE enables (if 0) or disables (if 1) Enalbe HW WDT RESET in ke_FullReset()
    if(sysFeature & SYS_FEATURE_WDT_ISSUE_DBG_ENA)
        sys_SetHwWdtDbgState(TRUE);
    else
        sys_SetHwWdtDbgState(FALSE);

    if(sysFeature & SYS_FEATURE_MALLOC_FAIL_FATAL_ENA)
        sys_SetMallocFailState(1);

    if(sysFeature & SYS_FEATURE_MALLOC_FAIL_DOWALK_ENA)
        sys_SetMallocFailState(2);

    if(sysFeature & SYS_FEATURE_NOT_FREE_RM_BUFFER1)
        rm_FreeBuffer1 = FALSE;

    sys_HwWdtDebugData.nBootUpSequence = 209;

#ifdef __FIXME__
    /*
    ** FCM init
    */
    fcm_Init();
#endif

    sys_HwWdtDebugData.nBootUpSequence = 210;

    /*
     * Diagnostic levels initialisation
     */
    vm_dbgTrcResetLevelFromE2p();

    /*
    ** Default serial handler state (can be overwritten by ATI / MMI)
    */
    e2p_Read(E2P_V24_SERIALON, &v24_SerialOn);
    e2p_Read(E2P_V24_NOMINALMODE, &v24_NominalMode);
    e2p_Read(E2P_EXTENDEDCAPABILITY, &sys_ExtendedCapability);

    #if defined( __MV5_FPGA__)
    v24_SerialOn = 0;
    #else
    v24_SerialOn = 1;
    #endif
    sys_HwWdtDebugData.nBootUpSequence = 214;

#ifndef __CORE_SW_VERSION__
    vm_e2pRead(E2P_MMI_RUNMODE, &nMMIRunMode);   /* 0: business mode, 1: factory mode */
    UartSendTrace("E2P_MMI_RUNMODE(nMMIRunMode) = %d (default 0)\n", nMMIRunMode);
    if(1 == nMMIRunMode)
    {
        e2p_Read(E2P_DISABLEERRORTRACEINFACMODE, &e2p_DisableErrorTraceInFacMode); /* 1: TRACE disabled, 0: TRACE enabled */

        UartSendTrace("E2P_DISABLEERRORTRACEINFACMODE = %d\n", e2p_DisableErrorTraceInFacMode);

        if(e2p_DisableErrorTraceInFacMode == 1)
            rm_DisableErrorTrace(TRUE);
        else
            rm_DisableErrorTrace(FALSE);
    }
#endif

    sys_HwWdtDebugData.nBootUpSequence = 215;

#if defined(__ENABLE_REDIRECT_DEFAULT_TRC__)
#if !defined(__CORE_SOFTWARE__)
    //cus_TrcEnableDef();
#endif
#endif

    sys_HwWdtDebugData.nBootUpSequence = 216;

    /*
    * Check for a watchdog reset and trace it
    */
    sys_StatusRegister();

    sys_HwWdtDebugData.nBootUpSequence = 255;

    DrvRtcCheckReset(); //Get Rtc Timer for e2p

    e2p_Read(E2P_ENABLE_UARTPRINTF, &nIsUartPrintfEnable);
    UartSendTrace("E2P_ENABLE_UARTPRINTF = %d (default 0)\n", nIsUartPrintfEnable);

    if(nIsUartPrintfEnable == 0)
        bIsUartPrintfEnable = FALSE;

    e2p_Read(E2P_SYSTIMEZONE, &nTimeZone);
    UartSendTrace("E2P_SYSTIMEZONE! %d \n", nTimeZone);

#if !defined(__CORE_SOFTWARE__)
    SysTimeSetTZ((SysTimeTZ_e)nTimeZone);
#endif

    /*Init file mgr semaphore, due to mmi will call file mgr api before filemgr init semahpore*/
    MsInitSem(FILEMGR_SEM_MARK_FOLDER, 1);
    MsInitSem(FILEMGR_SEM_DELETE_ALL, 1);
    MsInitSem(FILEMGR_SEM_1, 1);
    MsInitSem(FILEMGR_SEM_2, 1);
    MsInitSem(FILEMGR_SEM_3, 1);
    MsInitSem(FILEMGR_SEM_4, 1);
    MsInitSem(FILEMGR_SEM_5, 1);
    MsInitSem(FILEMGR_SEM_6, 1);
    MsInitSem(FILEMGR_SEM_7, 1);

    MsConsumeSem(FILEMGR_SEM_1); //FILE_MGR_SEM__MMI_WAIT_LIST
    MsConsumeSem(FILEMGR_SEM_4); //FILE_MGR_SEM__LIST
    MsConsumeSem(FILEMGR_SEM_2); //FILE_MGR_SEM__DELETE
    MsConsumeSem(FILEMGR_SEM_5); //FILE_MGR_SEM__MAILBOX
    MsConsumeSem(FILEMGR_SEM_7); //FILE_MGR_SEM__MOVE_EX

    MsInitSem(GPD_SYNC_SEM, 1); /* for MDL Synchronization Interface */
    MsInitSem(GPD_REENTRY_LOCK_SEM, 1);
    MsConsumeSem(GPD_SYNC_SEM);
}

/****************************************************************************/
/*  Function  : sys_CustomFrameIntProc                                      */
/*--------------------------------------------------------------------------*/
/*  Scope     : Frame interrupt procedure.                                  */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*                    |   |   |   |                                         */
/****************************************************************************/
void sys_CustomFrameIntProc(u16 SleepedFrames)
{
#if !defined(__CORE_SOFTWARE__)
    extern void MdlBatAcquireBatteryData(u16 NbSleepedFrames);
    MdlBatAcquireBatteryData(SleepedFrames);
#endif
}


/***************************************************************************/
/*  Function   : sys_CustomIdleProc                                        */
/*-------------------------------------------------------------------------*/
/*  Scope      : user idle function                                        */
/*               This function is called by the idle task. Every time it   */
/*               returns, a loop is made in the idle task and it called    */
/*               again. The arm chip is put in power down after each call. */
/*               Note that if this function DOES NOT return for a while    */
/*               (more than 4 sec), a watchdog reset occurs.               */
/*               The V24 link is also managed in the idle task, so no data */
/*               will be processed if this cus_IdleCall does not return.   */
/*               It is possible (but highly deconseille) to workaround the */
/*               watchdog reset by writing every less than 4 seconds TRUE  */
/*               to the variable WDogCountRstExpected.                     */
/*               It is also possible to enable V24 management by inserting */
/*               the following lines :                                     */
/*                      while (v24_PollRxTx());                            */
/*                                                                         */
/*               To manage the hapc stuff, call the rm_GetRequest function */
/*                                                                         */
/*  Return     :                                                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Utilisation                           */
/*--------------------+---+---+---+----------------------------------------*/
/*                    |   |   |   |                                        */
/***************************************************************************/
bool sys_CustomIdleProc(void)
{
    bool rm_prodrequest = 0;

    if(v24_SerialOn != 0)
        rm_prodrequest = rm_GetRequest();

    return rm_prodrequest;
}

void sys_CustomIdleProc2(void)
{

#if __MCP_VALIDATION_TEST__
    fms_e2p_stress_test();
    fms_rai_stress_test();
#endif

    fms_Cleaner();

#ifdef __MEM_SHORT_POLLING_CHECK__
    if(SysGetMPFlag() == 0)
    {
        if(RtkGetAvailableHeapSize() < 10 * 1024) //check available less than 10KB
        {
            _ERROR((_SYS | FATAL, "Idle polling: memory short"));
        }
    }
#endif

// Add more idle hook functions here after...

}


