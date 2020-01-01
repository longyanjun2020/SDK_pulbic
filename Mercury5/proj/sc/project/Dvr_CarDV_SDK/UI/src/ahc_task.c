/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_task.h"
#include "ahc_os.h"
#include "all_fw.h"
#include "ahc_debugex.h"

/*===========================================================================
 * Global variable
 *===========================================================================*/
UINT32  MidTaskStack[TASK_MID_WORK_STK_SIZE];
UINT32  LowTaskStack[TASK_LOW_WORK_STK_SIZE];
UINT32  KeyPadStack[TASK_KEYPAD_STK_SIZE];
UINT32  AhcMotorStack[TASK_MOTOR_STK_SIZE];
UINT32  MotorWorkStack[TASK_MOTOR_STK_SIZE];
UINT32  MotorCtrlStack[TASK_MOTOR_STK_SIZE];
UINT32  AhcRtcUpdate[TASK_AHC_RTC_UPDATE_SIZE];
UINT32  AhcWork2Stack[TASK_AHC_WORK_STK_SIZE];
UINT32  UARTLogTxStack[TASK_UART_LOG_STK_SIZE];
UINT32  JobDispatchStack[TASK_JOB_DISPATCH_STK_SIZE];

#if (FW_DCF_BACKGROUND == 1)
UINT32  AhcDcfStack[TASK_AHC_DCF_STK_SIZE];
#endif

#if (KEYPAD_DETECT_METHOD == KEYPAD_DETECT_TASK)
UINT32  RealIDKeyPadStack[TASK_REALIDKEYPAD_STK_SIZE];
#endif

UINT32  UARTCtrlStack[TASK_UARTCRTL_STK_SIZE];
UINT32  GsensorCtrlStack[TASK_UARTCRTL_STK_SIZE];

//Wifi
#if (WIFI_PORT == 1)
UINT32  NETWORK_Task_Stk[TASK_NETWORK_STK_SIZE];
#endif

//MDTC/ADAS
UINT32  FDTC_Task_Stk[TASK_FDTC_STK_SIZE];

#define TASK_CYCLE_JOB_STK_SIZE (512)
UINT32  CyclicJobStack[TASK_CYCLE_JOB_STK_SIZE];

/*===========================================================================
 * Extern function
 *===========================================================================*/

extern  void AHC_RtcUpdate_Task(void *p_arg);
extern  void UIKeyTask(void);
extern  void AHC_WorkJob_Task(void *p_arg);
extern 	void Mid_Work_Task(void);
extern 	void Low_Work_Task(void);

#if (FW_DCF_BACKGROUND == 1)
extern  void AHC_DCF_Task(void *p_arg);
#endif

#if(KEYPAD_DETECT_METHOD == KEYPAD_DETECT_TASK)
extern  void RealIDKeyPadTask(void *p_arg);
extern  void RealIDUIKeyTask(void);
#endif
extern  void CyclicJobTask(void);

/*===========================================================================
 * Main body
 *===========================================================================*/

void KeyPadTask_init(void *p_arg)
{
    UIKeyTask_init();
}
void KeyPadTask(void *p_arg)
{
    UIKeyTask();
}

void AhcRtcUpdate_init(void *p_arg)
{
    AHC_RtcUpdate_Task_init(p_arg);
}

void AhcRtcUpdateTask(void *p_arg)
{
    AHC_RtcUpdate_Task(p_arg);
}

void AhcWorkJobTask_init(void *p_arg)
{
    AHC_WorkJob_Task_init(p_arg);
}
void AhcWorkJobTask(void *p_arg)
{
    AHC_WorkJob_Task(p_arg);
}

void AhcUARTLogTxTask_init(void *p_arg)
{
    AHC_UARTLogTxTask_Task_init(p_arg);
}

void AhcUARTLogTxTask(void *p_arg)
{
    AHC_UARTLogTx_Task(p_arg);
}

#if (FW_DCF_BACKGROUND == 1)
void AhcDcfTask(void *p_arg)
{
    AHC_DCF_Task(p_arg);
}
#endif

void CyclicJobTaskHandler_init(void *p_arg)
{
    CyclicJobTask_init();
}
void CyclicJobTaskHandler(void *p_arg)
{
    CyclicJobTask();
}

void JobdispatchTask_init(void)
{
    extern AHC_BOOL  gAHC_InitialDone;
    extern MMP_ULONG glAhcBootComplete;

    MMP_ULONG ulInitFs = 32000;
    //MMP_USHORT uwFwMajorVersion;
    //MMP_USHORT uwFwMediumVersion;
    //MMP_USHORT uwFwMinorVersion;

    //AHC_GetFwVersion(&uwFwMajorVersion, &uwFwMediumVersion, &uwFwMinorVersion, NULL, NULL, NULL);
    //AHC_DBG_MSG(1, "FW Version:%4x %4x %4x",uwFwMajorVersion,uwFwMediumVersion,uwFwMinorVersion);

    //Get gsensor interrupt status  move to AHC_Main_Task
    //InitGsensorAhead();

    // Save the booting information ASAP
    InitOSD(); //Move to CE_JOB_DISPATCH_Task for fast boot.

    Customer_init();

    MMPS_System_AllocateFSBuffer(1);
    glAhcBootComplete = AHC_TRUE;

    MMPS_AUDIO_PreDACPowerOn(ulInitFs); //Move to CE_JOB_DISPATCH_Task for fast boot.

    InitKeyPad(); //Move to CE_JOB_DISPATCH_Task for fast boot.
    AHC_DCF_Init();

    gAHC_InitialDone = AHC_TRUE; //Start key/device detection after init done.
}

void CE_JOB_DISPATCH_Task(void)
{
    // Never run to here.
    while (1) {
        MMPF_OS_Sleep(1000);
    }
}

void JobdispatchTaskHandler_init(void *p_arg)
{
    JobdispatchTask_init();
}

void JobdispatchHandler(void *p_arg)
{
    CE_JOB_DISPATCH_Task();
}

#if(KEYPAD_DETECT_METHOD == KEYPAD_DETECT_TASK)
void RealIDKeyPadTask_init(void *p_arg)
{
    RealIDUIKeyTask_init();
}

void RealIDKeyPadTask(void *p_arg)
{
    RealIDUIKeyTask();
}

void AHC_SWPACK_TaskInit(void)
{
    AHC_OS_TASK_CFG task_cfg;

    //Note: Initaial priority is TASK_AHC_INIT_PRIO which higher than any other AHC tasks.
    task_cfg.ubPriority = TASK_MID_WORK_PRIO;
    task_cfg.pbos = (MMP_ULONG)&MidTaskStack[0];
    task_cfg.ptos = (MMP_ULONG)&MidTaskStack[TASK_MID_WORK_STK_SIZE-1];
    task_cfg.TaskiInit = NULL;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"MidTask");
    AHC_OS_CreateTask(Mid_Work_Task, &task_cfg, (void *)"MidTask");

    task_cfg.ubPriority = TASK_LOW_WORK_PRIO;
    task_cfg.pbos = (MMP_ULONG)&LowTaskStack[0];
    task_cfg.ptos = (MMP_ULONG)&LowTaskStack[TASK_LOW_WORK_STK_SIZE-1];
    task_cfg.TaskiInit = NULL;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"LowTask");
    AHC_OS_CreateTask(Low_Work_Task, &task_cfg, (void *)"LowTask");

    task_cfg.ubPriority = TASK_KEYPAD_PRIO;
    task_cfg.pbos = (MMP_ULONG)&KeyPadStack[0];
    task_cfg.ptos = (MMP_ULONG)&KeyPadStack[TASK_KEYPAD_STK_SIZE-1];
    task_cfg.TaskiInit = KeyPadTask_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"KeyPad");
    AHC_OS_CreateTask(KeyPadTask, &task_cfg, (void *)"KeyPad");

    #if (KEYPAD_DETECT_METHOD == KEYPAD_DETECT_TASK)
    task_cfg.ubPriority = TASK_REALIDKEYPAD_PRIO;
    task_cfg.pbos = (MMP_ULONG)&RealIDKeyPadStack[0];
    task_cfg.ptos = (MMP_ULONG)&RealIDKeyPadStack[TASK_REALIDKEYPAD_STK_SIZE-1];
    task_cfg.TaskiInit = RealIDKeyPadTask_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"RealIDKeyPad");
    AHC_OS_CreateTask(RealIDKeyPadTask, &task_cfg, (void *)"RealIDKeyPad");
    #endif

    task_cfg.ubPriority = TASK_AHC_WORK_PRIO;
    task_cfg.pbos = (MMP_ULONG)&AhcRtcUpdate[0];
    task_cfg.ptos = (MMP_ULONG)&AhcRtcUpdate[TASK_AHC_RTC_UPDATE_SIZE-1];
    task_cfg.TaskiInit = AhcRtcUpdate_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"AhcRtcUpdate");
    AHC_OS_CreateTask(AhcRtcUpdateTask, &task_cfg, (void *)"AhcRtcUpdate");

    task_cfg.ubPriority = TASK_AHC_WORK2_PRIO;
    task_cfg.pbos = (MMP_ULONG)&AhcWork2Stack[0];
    task_cfg.ptos = (MMP_ULONG)&AhcWork2Stack[TASK_AHC_WORK_STK_SIZE-1];
    task_cfg.TaskiInit = AhcWorkJobTask_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"AhcWorkJob");
    AHC_OS_CreateTask(AhcWorkJobTask, &task_cfg, (void *)"AhcWorkJob");

    task_cfg.ubPriority = TASK_UART_LOG_TX_PRIO;
    task_cfg.pbos = (MMP_ULONG)&UARTLogTxStack[0];
    task_cfg.ptos = (MMP_ULONG)&UARTLogTxStack[TASK_UART_LOG_STK_SIZE-1];
    task_cfg.TaskiInit = AhcUARTLogTxTask_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"UARTLog");
    AHC_OS_CreateTask(AhcUARTLogTxTask, &task_cfg, (void *)"UARTLog");

    #if (WIFI_PORT == 1)
    task_cfg.ubPriority = TASK_NETWORK_PRIO;
    task_cfg.pbos = (MMP_ULONG)&NETWORK_Task_Stk[0];
    task_cfg.ptos = (MMP_ULONG)&NETWORK_Task_Stk[TASK_NETWORK_STK_SIZE-1];
    task_cfg.TaskiInit = NETWORK_TaskHandler_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"NETWORK");
    AHC_OS_CreateTask(NETWORK_TaskHandler, &task_cfg, (void *)"NETWORK");
    #endif

    task_cfg.ubPriority = TASK_FDTC_PRIO;
    task_cfg.pbos = (MMP_ULONG)&FDTC_Task_Stk[0];
    task_cfg.ptos = (MMP_ULONG)&FDTC_Task_Stk[TASK_FDTC_STK_SIZE-1];
    task_cfg.TaskiInit = FDTC_TaskHandler_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"FDTC");
    AHC_OS_CreateTask(FDTC_TaskHandler, &task_cfg, (void *)"FDTC");

    /**
    @brief  dcf background
    */
#if (FW_DCF_BACKGROUND == 1)
    task_cfg.ubPriority = TASK_AHC_DCF_PRIO;
    task_cfg.pbos = (MMP_ULONG)&AhcDcfStack[0];
    task_cfg.ptos = (MMP_ULONG)&AhcDcfStack[TASK_AHC_DCF_STK_SIZE-1];
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"AhcDcf");
    AHC_OS_CreateTask(AhcDcfTask, &task_cfg, (void *)"AhcDcf");
#endif

    task_cfg.ubPriority = TASK_UART_CTRL_PRIO;
    task_cfg.pbos = (MMP_ULONG)&UARTCtrlStack[0];
    task_cfg.ptos = (MMP_ULONG)&UARTCtrlStack[TASK_UARTCRTL_STK_SIZE-1];
    task_cfg.TaskiInit = UARTCtrl_TaskHandler_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"UARTCtrl");
    AHC_OS_CreateTask(UARTCtrl_TaskHandler, &task_cfg, (void *)"UARTCtrl");

#if (GSENSOR_CONNECT_ENABLE)
    task_cfg.ubPriority = TASK_UART_CTRL_PRIO;
    task_cfg.pbos = (MMP_ULONG)&GsensorCtrlStack[0];
    task_cfg.ptos = (MMP_ULONG)&GsensorCtrlStack[TASK_UARTCRTL_STK_SIZE-1];
    task_cfg.TaskiInit = GsensorCtrl_TaskHandler_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"GsensorCtrl");
    AHC_OS_CreateTask(GsensorCtrl_TaskHandler, &task_cfg, (void *)"GsensorCtrl");
#endif

    task_cfg.ubPriority = TASK_CYCLIC_JOB_PRIO;
    task_cfg.pbos = (MMP_ULONG)&CyclicJobStack[0];
    task_cfg.ptos = (MMP_ULONG)&CyclicJobStack[TASK_CYCLE_JOB_STK_SIZE-1];
    task_cfg.TaskiInit = CyclicJobTaskHandler_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"CyclicJob");
    AHC_OS_CreateTask(CyclicJobTaskHandler, &task_cfg, (void *)"CyclicJob");

    task_cfg.ubPriority = TASK_JOB_DISPATCH_PRIO;
    task_cfg.pbos = (MMP_ULONG)&JobDispatchStack[0];
    task_cfg.ptos = (MMP_ULONG)&JobDispatchStack[TASK_JOB_DISPATCH_STK_SIZE-1];
    task_cfg.TaskiInit = JobdispatchTaskHandler_init;
    AHC_OS_SetTaskName(task_cfg.ubPriority, (UINT8 *)"JobDispatch");
    AHC_OS_CreateTask(JobdispatchHandler, &task_cfg, (void *)"JobDispatch");

    //AHC_OS_ChangeTaskPriority(TASK_AHC_INIT_PRIO, TASK_AHC_PRIO);
}

#endif
