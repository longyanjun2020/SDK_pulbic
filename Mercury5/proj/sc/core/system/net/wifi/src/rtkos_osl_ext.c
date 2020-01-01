/*
 * RTK-OS OS Support Extension Layer
 *
 * Copyright (C) 2011, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 * $Id: nucleus_osl_ext.c,v 1.5 2009-10-05 01:44:48 Exp $
 */

/* ---- Include Files ---------------------------------------------------- */

#include "wlantypedefs.h"
#include "osl_ext.h"
#include <stdlib.h>
#include <stdarg.h>
#include "net_cfg.h"
#include "ahc_fs.h"

/* ---- Public Variables ------------------------------------------------- */
/* ---- Private Constants and Types -------------------------------------- */

/* RTK-OS-specific task priorities. */
#ifndef RTK_OS_TASK_IDLE_PRIORITY
#define RTK_OS_TASK_IDLE_PRIORITY                   188
#endif

#ifndef RTK_OS_TASK_LOW_PRIORITY
#define RTK_OS_TASK_LOW_PRIORITY                    189
#endif

#ifndef RTK_OS_TASK_LOW_NORMAL_PRIORITY
#define RTK_OS_TASK_LOW_NORMAL_PRIORITY             190
#endif

#ifndef RTK_OS_TASK_NORMAL_PRIORITY
#define RTK_OS_TASK_NORMAL_PRIORITY                 191
#endif

#ifndef RTK_OS_TASK_HIGH_NORMAL_PRIORITY
#define RTK_OS_TASK_HIGH_NORMAL_PRIORITY            192
#endif

#ifndef RTK_OS_TASK_HIGHEST_PRIORITY
#define RTK_OS_TASK_HIGHEST_PRIORITY                193
#endif

#ifndef RTK_OS_TASK_SUPER_HIGH_PRIORITY
#define RTK_OS_TASK_SUPER_HIGH_PRIORITY             194
#endif

#ifndef RTK_OS_TASK_SUPER_PRIORITY
#define RTK_OS_TASK_SUPER_PRIORITY                  195
#endif

#ifndef RTK_OS_TASK_TIME_CRITICAL_PRIORITY
#define RTK_OS_TASK_TIME_CRITICAL_PRIORITY          196
#endif

#ifndef RTK_OS_TASK_SUPER_CRITICAL_PRIORITY
#define RTK_OS_TASK_SUPER_CRITICAL_PRIORITY         197
#endif
//#define OSL_LOG(a)    osl_ext_printf a

#define RTK_OS_OSL_EXT_MAX_STACK_SIZE               (4096)

/* ---- Private Variables ------------------------------------------------ */
/* ---- Private Function Prototypes -------------------------------------- */


void osl_ext_uc_task_entry(void* argv);

uint32 m_uiSdioPad = 3;

__align(4) OS_STK   OSL_Task_Stk[OSL_EXT_TASK_NUM_PRIORITES][RTK_OS_OSL_EXT_MAX_STACK_SIZE];

/* ---- Functions -------------------------------------------------------- */

/* --------------------------------------------------------------------------
** Sleep/Delay
*/

/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_os_sleep(unsigned int Ms)
{
    MsSleep(Ms);
    return OSL_EXT_SUCCESS;
}

/* --------------------------------------------------------------------------
** Semaphores
*/

/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_sem_create(char *name, int init_cnt, osl_ext_sem_t *sem)
{
    memset(sem, 0xff, sizeof(osl_ext_sem_t));

    if(ERR_OK == sys_sem_new(sem,init_cnt)) {
        return OSL_EXT_SUCCESS;
    }
    return OSL_EXT_ERROR;
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_sem_delete(osl_ext_sem_t *sem)
{
    sys_sem_free(sem);
    return OSL_EXT_SUCCESS;
}

/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_sem_set(osl_ext_sem_t *sem, unsigned short cnt)
{
    if(ERR_OK == sys_sem_set(sem,cnt)) {
        return OSL_EXT_SUCCESS;
    }
    return OSL_EXT_ERROR;
}

/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_sem_give(osl_ext_sem_t *sem)
{
    if(ERR_OK == sys_sem_signal(sem))
        return OSL_EXT_SUCCESS;

    return OSL_EXT_ERROR;
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_sem_take(osl_ext_sem_t *sem, osl_ext_time_ms_t timeout_msec)
{
    uint32  ret;
    uint    timeout_ticks;

    if (timeout_msec == 0)
        timeout_ticks = 1;
    else if (timeout_msec == OSL_EXT_TIME_FOREVER)
        timeout_ticks = 0;
    else
        timeout_ticks = OSL_MSEC_TO_TICKS(timeout_msec);

    ret = sys_arch_sem_wait(sem, timeout_ticks);

    if(timeout_ticks == 0 && ret == SYS_ARCH_TIMEOUT)
        return OSL_EXT_ERROR;
    else if (ret == SYS_ARCH_TIMEOUT)
        return OSL_EXT_TIMEOUT;
    else
        return OSL_EXT_SUCCESS;
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_sem_query(osl_ext_sem_t *sem, uint16 *count)
{
    if(ERR_OK == sys_arch_sem_query(sem,count))
        return OSL_EXT_SUCCESS;
    return OSL_EXT_ERROR;
}


/* --------------------------------------------------------------------------
** Mutex
*/

/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_mutex_create(char *name, osl_ext_mutex_t *mutex)
{
    return (osl_ext_sem_create(name, 1, mutex));
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_mutex_delete(osl_ext_mutex_t *mutex)
{
    return (osl_ext_sem_delete(mutex));
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_mutex_acquire(osl_ext_mutex_t *mutex, osl_ext_time_ms_t timeout_msec)
{
    return (osl_ext_sem_take(mutex, timeout_msec));
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_mutex_release(osl_ext_mutex_t *mutex)
{
    return (osl_ext_sem_give(mutex));
}

/* --------------------------------------------------------------------------
** Timers
*/

/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_timer_create(char *name, osl_ext_time_ms_t timeout_msec, osl_ext_timer_mode_t mode,
                 osl_ext_timer_callback func, osl_ext_timer_arg_t arg, osl_ext_timer_t *timer)
{
    uint32 init_ticks;

    memset(timer, 0, sizeof(osl_ext_timer_t));
    init_ticks = OSL_MSEC_TO_TICKS(timeout_msec);

    *timer = MMPF_OS_StartTimer(init_ticks,
                      (mode == OSL_EXT_TIMER_MODE_REPEAT) ? MMPF_OS_TMR_OPT_PERIODIC : MMPF_OS_TMR_OPT_ONE_SHOT,
                      (MMPF_OS_TMR_CALLBACK)func,arg);

    if(*timer == MMPF_OS_CREATE_TMR_INT_ERR)
        return OSL_EXT_ERROR;

    return OSL_EXT_SUCCESS;
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_timer_delete(osl_ext_timer_t *timer)
{
    if(MMPF_OS_StopTimer(*timer, MMPF_OS_TMR_OPT_NONE) == 0)
        return OSL_EXT_SUCCESS;

    return OSL_EXT_ERROR;
}


/* --------------------------------------------------------------------------
** Tasks
*/

#if defined(__RTK_OS__)

typedef struct osl_ext_int_task_t
{
    u8                  taskid;
    u8                  priority;
    osl_ext_task_entry  func;
    void                *arg;
} osl_ext_int_task_t;

static osl_ext_int_task_t gosltask[OSL_EXT_TASK_NUM_PRIORITES];

#else
uint32 dhd_stack[8192] = {0x00};
uint32 WPSMainTask_stack[8192] = {0x00};
#ifdef WD_TASK
uint32 wdog_stack[8192] = {0x00};
#endif
#endif

/* Map generic task priorities to Nucleus-specific priorities. */
static int g_task_priority_table[OSL_EXT_TASK_NUM_PRIORITES] =
{
    RTK_OS_TASK_IDLE_PRIORITY,
    RTK_OS_TASK_LOW_PRIORITY,
    RTK_OS_TASK_LOW_NORMAL_PRIORITY,
    RTK_OS_TASK_NORMAL_PRIORITY,
    RTK_OS_TASK_HIGH_NORMAL_PRIORITY,
    RTK_OS_TASK_HIGHEST_PRIORITY,
    RTK_OS_TASK_SUPER_HIGH_PRIORITY,
    RTK_OS_TASK_SUPER_PRIORITY,
    RTK_OS_TASK_TIME_CRITICAL_PRIORITY,
    RTK_OS_TASK_SUPER_CRITICAL_PRIORITY
};

/****************************************************************************
* Function:   osl_ext_uc_task_entry
*
* Purpose:    RTK_OS specific task entry function. Invokes the user registered
*             task entry function.
*
* Parameters: argc, argv (in) Task entry arguments.
*
* Returns:    Nothing.
*****************************************************************************
*/
void
osl_ext_uc_task_entry(void* argv)
{
#if defined(__RTK_OS__)

    Msg_t *msg;
    osl_ext_int_task_t * ptThreadArg;

    msg = argv;
    ptThreadArg = (osl_ext_int_task_t *)msg->Body.userdata;

    if(ptThreadArg->func) {
        ptThreadArg->func(ptThreadArg->arg);
        ptThreadArg->func = NULL;
    }
#else
    osl_ext_task_entry  func;
    osl_ext_task_arg_t  arg;
    osl_ext_task_t      *task;

    /* 'argv' is actually a pointer to an OSL task object. */
    task = (osl_ext_task_t*)argv;
    func = (osl_ext_task_entry) task->func;
    arg = task->arg;

    /* Invoke the user register task entry function. */
    (*func)(arg);
#endif
}

/****************************************************************************
* Function:   osl_ext_task_init
*
* Purpose:    initial & prepare task
*
* Returns:    Nothing.
*****************************************************************************
*/
void
osl_ext_task_init()
{
    int i;

    for(i = 0 ; i < OSL_EXT_TASK_NUM_PRIORITES ; i++) {

        u8 TaskId;
        MsTaskCreateArgs_t TaskArgs = {0};

        memset(&gosltask[i],0,sizeof(osl_ext_int_task_t));

        TaskArgs.TaskName[0] = 0;
        sprintf(TaskArgs.TaskName,"OSLE_T%d",i);

        TaskArgs.AppliInit          = NULL;
        TaskArgs.AppliParser        = osl_ext_uc_task_entry;
        TaskArgs.ImmediatelyStart   = TRUE;
        TaskArgs.StackSize          = RTK_OS_OSL_EXT_MAX_STACK_SIZE << 2;
        TaskArgs.Priority           = RTK_OS_TASK_IDLE_PRIORITY + i;
        TaskArgs.pInitArgs          = &gosltask[i];
        TaskArgs.TaskId             = &TaskId;
        TaskArgs.pStackTop          = OSL_Task_Stk[i];
        //TaskArgs.TimeSliceLeft = 5;
        //TaskArgs.TimeSliceMax = 5;

#if defined(__TIME_SLICE_SCHEDULE__)
        if(MS_OK != MsCreateTaskMs(&TaskArgs)) {
#else
        if(MS_OK != MsCreateTask(&TaskArgs)) {
#endif
            osl_ext_printf( "osl_ext_task_init: init task failed!!\n");
            return;
        }
        RtkSetTaskMonitorMaxTimeout(TaskId,RTK_MAX_TASK_TIMEOUT_DISABLE);
        gosltask[i].taskid = TaskId;
        gosltask[i].priority = i;
    }
}

int osl_ext_task_get_task_idx()
{
    int i;
    MsTaskId_e taskid = MsCurrTask();

    for(i = 0; i < OSL_EXT_TASK_NUM_PRIORITES; i++){
        if(gosltask[i].taskid == taskid)
            return i;
    }
    return -1;
}
/* ----------------------------------------------------------------------- */
osl_ext_status_t osl_ext_task_create_ex(char* name, unsigned int stack_size,
                             osl_ext_task_priority_t priority,
                             osl_ext_time_ms_t timeslice_msec,
                             osl_ext_task_entry func, osl_ext_task_arg_t arg,
                             osl_ext_task_t *task)
{
#if defined(__RTK_OS__)
    Msg_t *msg = NULL;
    osl_ext_int_task_t *ptthread;

    if(priority >= OSL_EXT_TASK_NUM_PRIORITES) {
        task->uc_task = 0xFE;
        osl_ext_printf("osl_ext_task_create_ex : invalid priority %d\n",priority);
        return OSL_EXT_ERROR;
    }
    /* Map from the generic OSL priority to a RTK_OS specific priority. */
    /* index(priority) reference osl_ext_task_priority in osl_ext.h */
    if(gosltask[priority].func) {
        task->uc_task = 0xFE;
        osl_ext_printf("osl_ext_task_create_ex : priority[%d] has been created!\n",priority);
        return OSL_EXT_ERROR;
    }

    if(stack_size > RTK_OS_OSL_EXT_MAX_STACK_SIZE)  {
        task->uc_task = 0xFE;
        osl_ext_printf("osl_ext_task_create_ex : stack size[%d] too is large\n",stack_size);
        return OSL_EXT_ERROR;
    }

    memset(task, 0, sizeof(osl_ext_task_t));
    ptthread = &gosltask[priority];
    ptthread->func = func;
    ptthread->arg = arg;

    task->stack = (uint8*)&OSL_Task_Stk[priority][0];
    task->stack_size = stack_size;

    /* Save the user registered task entry function and argument. */
    task->func = (void*) func;
    task->arg = arg;
    /* Save the task ID */
    task->uc_task = ptthread->taskid;

    msg = (Msg_t*)MsAllocateMem(sizeof(Msg_t));
    msg->Header.TypMsg = 1;
    msg->Header.MbxSrc = RTK_FIRST_CUSTOMER_MAILBOXID;
    msg->Header.MbxDst = ptthread->taskid;
    msg->Header.Length = sizeof(msg->Body.userdata);
    msg->Body.userdata = (u32)ptthread;

    MsSend(ptthread->taskid, (void*)msg);

#else
    MMPF_TASK_CFG task_cfg;

    memset(task, 0, sizeof(osl_ext_task_t));

    /* Map from the generic OSL priority to a RTK_OS specific priority. */
    /* idex(priority) reference osl_ext_task_priority in osl_ext.h */
    task_cfg.ubPriority = g_task_priority_table[priority];

#if 1
    if(memcmp(name, "dhd", 3) == 0) {
        memset(&dhd_stack[0], 0x00, sizeof(dhd_stack));
        task_cfg.pbos = (uint32)&dhd_stack[0];
        task_cfg.ptos = (uint32)&dhd_stack[stack_size/4 - 1];
    } else if(memcmp(name, "WPSMainTask", 11) == 0) {
        memset(&WPSMainTask_stack[0], 0x00, sizeof(WPSMainTask_stack));
        task_cfg.pbos = (uint32)&WPSMainTask_stack[0];
        task_cfg.ptos = (uint32)&WPSMainTask_stack[stack_size/4 - 1];
#ifdef WD_TASK
    } else {
        memset(&wdog_stack[0], 0x00, sizeof(wdog_stack));
        task_cfg.pbos = (uint32)&wdog_stack[0];
        task_cfg.ptos = (uint32)&wdog_stack[stack_size/4 - 1];
#endif
    }
    ASSERT(task_cfg.pbos);

    task->stack = (uint8*)task_cfg.pbos;
    task->stack_size = stack_size;
    ASSERT(task->stack);
#else
    /* Dynamically allocate a stack. */
    task->stack = (uint8*)MALLOC(NULL, stack_size+4);
    task->stack_size = stack_size;
    ASSERT(task->stack);

    memset(task->stack, 0x00, stack_size+4);

    /* make it 4-byte aligned */
    task_cfg.pbos = (uint32)((uint32)task->stack & ~(size_t)0x03);
    task_cfg.ptos = (uint32)(task_cfg.pbos + stack_size/4 - 1);
    ASSERT(task_cfg.pbos);
#endif

    /* Save the user registered task entry function and argument. */
    task->func = (void*) func;
    task->arg = arg;

    /* Save the task ID */
    task->uc_task = MMPF_OS_CreateTask(osl_ext_uc_task_entry, &task_cfg, (void*) task);
    MMPF_OS_SetTaskName(task_cfg.ubPriority, (INT8U *)name);

    if(task->uc_task == 0xFE || task->uc_task == 0xFF)
        return OSL_EXT_ERROR;
#endif
    return OSL_EXT_SUCCESS;
}


/* ----------------------------------------------------------------------- */
static osl_ext_status_t task_delete(osl_ext_task_t *task)
{
    int i = 0;
    for(i ; i < OSL_EXT_TASK_NUM_PRIORITES; i++) {
        if(gosltask[i].taskid == task->uc_task){
            gosltask[i].func = NULL;
            break;
        }
    }
    return OSL_EXT_SUCCESS;
}

/* ----------------------------------------------------------------------- */
osl_ext_status_t osl_ext_task_delete(osl_ext_task_t *task)
{
    if (task->uc_task == 0xFE || task->uc_task == 0xFF)
        return OSL_EXT_ERROR;

    return (task_delete(task));
}

/* ----------------------------------------------------------------------- */
osl_ext_status_t osl_ext_task_suspend(osl_ext_task_t *task)
{
    if (task->uc_task == 0xFE || task->uc_task == 0xFF)
        return OSL_EXT_ERROR;
    MsSuspendTask(1,task->uc_task);
    return OSL_EXT_SUCCESS;
}

/* ----------------------------------------------------------------------- */
osl_ext_status_t osl_ext_task_resume(osl_ext_task_t *task)
{
    if (task->uc_task == 0xFE || task->uc_task == 0xFF)
        return OSL_EXT_ERROR;
    MsResumeTask(1,task->uc_task);
    return OSL_EXT_SUCCESS;
}

/* --------------------------------------------------------------------------
** Queue
*/

/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_queue_create(char *name, unsigned int size, osl_ext_queue_t *queue)
{
    sys_mbox_t mbox;

    memset(queue, 0, sizeof(osl_ext_queue_t));
    queue->uc_queue = 0xff;

    if(ERR_OK != sys_mbox_new(&mbox,size))
        return OSL_EXT_ERROR;

    queue->uc_queue = mbox->QId;

    return OSL_EXT_SUCCESS;
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_queue_delete(osl_ext_queue_t *queue)
{
    sys_mbox_t mbox;

    mbox = sys_mbox_find_by_id(queue->uc_queue);
    sys_mbox_free(&mbox);
    return OSL_EXT_SUCCESS;
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_queue_bind(osl_ext_queue_t *queue, osl_ext_task_t *task)
{
    return OSL_EXT_SUCCESS;
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_queue_send(osl_ext_queue_t *queue, void *data)
{
    sys_mbox_t mbox;

    mbox = sys_mbox_find_by_id(queue->uc_queue);
    sys_mbox_post(&mbox,data);
    return OSL_EXT_SUCCESS;
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_queue_send_synchronous(osl_ext_queue_t *queue, void *data)
{
    /* RTK_OS doesn't support blocking, so use osl_ext_queue_send instead */
    return (osl_ext_queue_send(queue, data));
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_queue_receive(osl_ext_queue_t *queue, osl_ext_time_ms_t timeout_msec, void **data)
{
    u32 res;
    sys_mbox_t mbox;
    uint32 timeout_ticks;

    if (timeout_msec == 0)
        timeout_ticks = 1;
    else if (timeout_msec == OSL_EXT_TIME_FOREVER)
        timeout_ticks = 0;
    else
        timeout_ticks = OSL_MSEC_TO_TICKS(timeout_msec);

    mbox = sys_mbox_find_by_id(queue->uc_queue);

    res = sys_arch_mbox_fetch(&mbox, data, timeout_ticks);

    if(SYS_ARCH_TIMEOUT == res) {
        if(timeout_ticks == 0)
            return OSL_EXT_ERROR;
        else
            return OSL_EXT_TIMEOUT;
    }
    else {
        return OSL_EXT_SUCCESS;
    }
}


/* ----------------------------------------------------------------------- */
osl_ext_status_t
osl_ext_task_yield(void)
{
    MsSelfYield();
    return (OSL_EXT_SUCCESS);
}


/* ----------------------------------------------------------------------- */
void*
osl_ext_malloc(uint32 size)
{
    return mem_malloc(size);
}


/* ----------------------------------------------------------------------- */
void
osl_ext_free(void* rmem)
{
    mem_free(rmem);
}

#if(0)
/* ----------------------------------------------------------------------- */
void
osl_ext_printf(char* fmt, ...)
{
#if 0
//Fred's.
    char dbg_str[256];
    va_list args;

    va_start(args, fmt);
    vsprintf(dbg_str, fmt, args);
    va_end(args);

    printc(fmt);
#else
    void* pBufPtr;
    int n;

    va_list arg_list;
    //depends on AHC and hacking AHC_BOOL & MMP_ULONG
    unsigned char    AHC_UART_Write(char *pWrite_Str, unsigned int ulLength);

    pBufPtr = osl_ext_malloc(2048);

    va_start( arg_list, fmt );

    n = vsprintf( pBufPtr, fmt, arg_list );
    //n = vsprintc( pBufPtr, fmt, arg_list );

    va_end( arg_list );

    AHC_UART_Write(pBufPtr, n );

    osl_ext_free(pBufPtr);
#endif
}
#endif


void
osl_ext_sdio_internal_set_id(uint32 uiDevID)
{
    m_uiSdioPad = uiDevID;
}


uint32
osl_ext_sdio_internal_get_id(void)
{
    return m_uiSdioPad;
}

/* ----------------------------------------------------------------------- */
void
osl_ext_sdio_reg_sdio_isr(uint32 uiDevID, SDIOISRCallBack *Func)
{
    AHC_SDIO_RegSDIOISR(osl_ext_sdio_internal_get_id(), Func);
}


/* ----------------------------------------------------------------------- */
bool
osl_ext_sdio_set_dev_id(uint32 uiDevID)
{
    return AHC_SDIO_SetDeviceID(osl_ext_sdio_internal_get_id());
}


/* ----------------------------------------------------------------------- */
bool
osl_ext_sdio_get_dev_id(UINT32* puiDevID)
{
    //return AHC_SDIO_GetDeviceID(puiDevID);
    return osl_ext_sdio_internal_get_id();
}


/* ----------------------------------------------------------------------- */
bool
osl_ext_sdio_init_dev(UINT32 uiDevID)
{
    return AHC_SDIO_InitializeDevice(osl_ext_sdio_internal_get_id());
}


/* ----------------------------------------------------------------------- */
bool
osl_ext_sdio_reset_dev(UINT32 uiDevID)
{
    return AHC_SDIO_ResetDevice(osl_ext_sdio_internal_get_id());
}


/* ----------------------------------------------------------------------- */
bool
osl_ext_sdio_write_reg(UINT32 uiDevID, UINT8 byFuncNum, UINT32 uiRegAddr, UINT8 bySrc)
{
    return AHC_SDIO_WriteReg(osl_ext_sdio_internal_get_id(), byFuncNum, uiRegAddr, bySrc);
}


/* ----------------------------------------------------------------------- */
bool
osl_ext_sdio_read_reg(UINT32 uiDevID, UINT8 byFuncNum, UINT32 uiRegAddr, UINT8 *pbyDst)
{
    return AHC_SDIO_ReadReg(osl_ext_sdio_internal_get_id(), byFuncNum, uiRegAddr, pbyDst);
}


/* ----------------------------------------------------------------------- */
bool
osl_ext_sdio_write_multi_reg(UINT32 uiDevID,UINT8 byFuncNum,UINT8 byBlkMode,UINT8 byOpCode,UINT32 uiRegAddr,UINT32 uiCount,UINT32 uiBlkSize,UINT8 * pbySrc)
{
    return AHC_SDIO_WriteMultiReg(osl_ext_sdio_internal_get_id(), byFuncNum, byBlkMode, byOpCode, uiRegAddr, uiCount, uiBlkSize, pbySrc);
}


/* ----------------------------------------------------------------------- */
bool osl_ext_sdio_read_multi_reg(UINT32 uiDevID,UINT8 byFuncNum,UINT8 byBlkMode,UINT8 byOpCode,UINT32 uiRegAddr,UINT32 uiCount,UINT32 uiBlkSize,UINT8 * pbyDst)
{
    return AHC_SDIO_ReadMultiReg(osl_ext_sdio_internal_get_id(), byFuncNum, byBlkMode, byOpCode, uiRegAddr, uiCount, uiBlkSize, pbyDst);
}


/* ----------------------------------------------------------------------- */
void
osl_ext_sdio_enable_isr(uint32 uiDevID, bool bEnable)
{
    AHC_SDIO_EnableISR(osl_ext_sdio_internal_get_id(), bEnable);
}

/*read MAC address which stored in the host flash*/
bool osl_ext_read_mac(uint8 *pMac)
{
#if(WIFI_MAC_ON_HOST)
    AHC_ERR     err;
    UINT32      ulFileId;

    if(!pMac) return 0;

    if ((err = AHC_FS_FileOpen(SF_MAC_FILENAME, strlen(SF_MAC_FILENAME),"rb", sizeof("rb"), &ulFileId)) == AHC_ERR_NONE)
    {
        UINT32 ulReadCount = 0;

        err = AHC_FS_FileRead(ulFileId, pMac, 6, &ulReadCount);
        AHC_FS_FileClose(ulFileId);

        if (err != AHC_ERR_NONE || ulReadCount != 6)
        {
            //osl_ext_printf("No MAC in the host flash ,err=%d ,ulReadCount=%d \r\n",err,ulReadCount);
            return 0;
        }
    }
    else
    {
        return 0;
    }

    return 1;
#else
    return 0;
#endif
}
