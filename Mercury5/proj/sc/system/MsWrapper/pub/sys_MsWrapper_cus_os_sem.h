/**
 *
 * @file    cus_os.h
 *
 * @brief   This file defines the OS semaphore interface for customer layer
 *          where the implementation might different between platforms.
 *          The OS related interfaces includes memory allocation, task inter-
 *          communication.
 *          ** Note **
 *          The file is new created, new add related functions should be
 *          added here!!
 *
 * @author  Xavier Fan
 * @version $Id: cus_os.h 15678 2008-10-29 06:59:18Z xavier.fan $
 *
 */

#ifndef __SYS_MSWRAPPER_CUS_OS_SEM_H__
#define __SYS_MSWRAPPER_CUS_OS_SEM_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "sys_MsWrapper_cus_os_hc.h"
#include "sys_MsWrapper_cus_os_type.h"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/******* Structure d'un mutex *******/
// Note that this is 1-1 mapping with mutex definition in sys_rtk_ht.h
typedef struct _MutexStructure
{
    bool bLocked;
    u8 uMutexCount;
    struct TaskStructure* pTaskOwner;       // Owner
    rtk_Envelop_t* PtrTaskQueue;            // Queue
    rtk_Prio_Invr_e protocol;

    // Elements for priority inversion
    u8 original_priority;
    bool priority_inherited;
} Ms_Mutex_t ;

typedef enum
{
    MS_PRIO_INVR_NONE = 0,
    MS_PRIO_INVR_INHERIT,
    MS_PRIO_INVR_CEILING
}Ms_Prio_Invr_e;

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION PROTOTYPE                                                */
/*--------------------------------------------------------------------------*/
/** \addtogroup SenMan
 *  @{
 */

/**
 * \fn u8 MsInitSem (MsSemId_e semID,u16 rtkCounterInitialValue)
 * \brief The MsInitSem primitive initializes a semaphore. After initialization, the initial valuie and current velue set to rtkCounterInitialValue. The scheduler is not activated
 * \param[in] semID The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \param[in] rtkCounterInitialValue Initial number and current number of tokens owned by the semaphore
 * \return Return True if the mailbox ID is inside the range [0; rtkNbOfMailBox-1]
 */
u8 MsInitSem (MsSemId_e semID,u16 rtkCounterInitialValue);
/**
 * \fn u8 MsInitSemExtend(MsSemId_e rtkSemaphorNumber, s16 rtkCounterInitialValue, s16 rtkCurrentValue)
 * \brief The MsInitSemExtend primitive initializes a semaphore. After initialization, the initial valuie and current velue set to rtkCounterInitialValue and rtkCurrentValue, respectively. The scheduler is not activated
 * \param[in] rtkSemaphorNumber The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \param[in] rtkCounterInitialValue Initial number of tokens owned by the semaphore
 * \param[in] rtkCurrentValue Current number of tokens owned by the semaphore
 * \return Return True if the mailbox ID is inside the range [0; rtkNbOfMailBox-1]
 */
u8 MsInitSemExtend(MsSemId_e rtkSemaphorNumber, s16 rtkCounterInitialValue, s16 rtkCurrentValue);

/**
 * \fn cus_ErrCode_e MsProduceSem(MsSemId_e semID)
 * \brief The RtkSemProduce primitive adds a new token to the semaphore.If there are one or more tasks waiting on this semaphore, the highest priority task is de-queued and the state is changed to Ready. If there are no tasks waiting on this semaphore, the semaphore value is incremented by one unit and the calling task is re-activated
 * \param[in] semID The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \return Return RTK_OK if produce SEM token successfully.
 */
cus_ErrCode_e MsProduceSem(MsSemId_e semID);
/**
 * \fn cus_ErrCode_e MsProduceIntSem(MsSemId_e semID)
 * \brief The MsProduceIntSem primitive almost the same as MsProduceSem except this function is designed for calling in ISR. Be careful of using this primitive
 * \param[in] semID The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \return Return RTK_OK if produce SEM token successfully.
 */
cus_ErrCode_e MsProduceIntSem(MsSemId_e semID);
/**
 * \fn cus_ErrCode_e MsConsumeSem(MsSemId_e semID)
 * \brief The MsConsumeSem primitive is used by a task to wait for a semaphore to be in the signaled state. If the semaphore referenced by semID contains at least one token, the token counter is decremented and control is returned to the calling task. If the semaphore referenced by semID contains no tokens, the calling task is queued to the semaphore¡¦s task queue
 * \param[in] semID The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \return Return RTK_OK if concume SEM token successfully.
 */
cus_ErrCode_e MsConsumeSem(MsSemId_e semID);
/**
 * \fn cus_ErrCode_e MsPollSem(MsSemId_e semID)
 * \brief The MsPollSem primitive is used by a task to test if a semaphore is in the signaled state. If the semaphore referenced by semID contains at least one token, the token counter is decremented and the primitive returns RTK_OK. If the semaphore referenced by semID contains no tokens, the primitive immediately returns RTK_UNIT_NOAVAIL (the token counter is not decremented). As the scheduler is never activated, this primitive can be called from a critical section
 * \param[in] semID The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \return Return RTK_OK if concume SEM token successfully; otherwise, return RTK_UNIT_NOAVAIL
 */
cus_ErrCode_e MsPollSem(MsSemId_e semID);
/**
 * \fn cus_ErrCode_e MsConsumeSemDelay(MsSemId_e semID, u32 SemTimeOut)
 * \brief The RtkSemConsumeDelay primitive is almost the sam as MsConsumeSem primitive except the task at most wait SemTimeOut time in tick, if task waits more than SemTimeOut time, then task will be re-activated. For the task, there is no difference between timer expiration and a semaphore production
 * \param[in] semID The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \param[in] SemTimeOut The waiting time(system ticks) for a task to wait the semaphore
 * \return CUS_OS_NO_MESSAGE if timeout; otherwise, retuen RTK_OK.
 */
cus_ErrCode_e MsConsumeSemDelay(MsSemId_e semID, u32 SemTimeOut);
/**
 * \fn cus_ErrCode_e MsProduceSemRtkReady(MsSemId_e semID)
 * \brief The MsProduceSemRtkReady primitive almost the same as MsProduceSem except this function would check is OS has finished initialization before consuming the semaphore. If OS is ready, the primitive executed as MsProduceSem; otherwise, it returns CUS_OS_OK immediately
 * \param[in] semID The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \return Always RTK_OK
 */
cus_ErrCode_e MsProduceSemRtkReady(MsSemId_e semID);
/**
 * \fn cus_ErrCode_e MsConsumeSemRtkReady(MsSemId_e semID)
 * \brief The MsConsumeSemRtkReady primitive almost the same as MsConsumeSem except this function would check is OS has finished initialization before producing the semaphore. If OS is ready, the primitive executed as MsConsumeSem; otherwise, it returns CUS_OS_OK immediately
 * \param[in] semID The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \return Always RTK_OK
 */
cus_ErrCode_e MsConsumeSemRtkReady(MsSemId_e semID);
/**
 * \fn cus_ErrCode_e MsGetSemCount(MsSemId_e semID, s16* pSemCount)
 * \brief The MsGetSemCount primitive returns the current number of available tokerns in the semaphore
 * \param[in] semID The semaphore ID. 0 <= Semaphore ID. <= rtkNbOfSemaphor-1
 * \param[out] pSemCount The current number of available tokerns in the semaphore
 * \return Always RTK_OK
 */
cus_ErrCode_e MsGetSemCount(MsSemId_e semID, s16* pSemCount);

/**
 * \fn u8 MsInitMutex (Ms_Mutex_t* mutex)
 * \brief It initializes the given mutex control block
 * \param[in] mutex control block ptr
 * \return Always RTK_OK
 */
u8 MsInitMutex (Ms_Mutex_t* mutex);
/**
 * \fn cus_ErrCode_e MsMutexLock(Ms_Mutex_t* mutex)
 * \brief It locks the given mutex control block
 * \param[in] mutex control block ptr
 * \return Error code cus_ErrCode_e
 */
cus_ErrCode_e MsMutexLock(Ms_Mutex_t* mutex);
/**
 * \fn cus_ErrCode_e MsMutexUnlock(Ms_Mutex_t* mutex)
 * \brief It unlocks the given mutex control block
 * \param[in] mutex control block ptr
 * \return Error code cus_ErrCode_e
 */
cus_ErrCode_e MsMutexUnlock(Ms_Mutex_t* mutex);
/**
 * \fn cus_ErrCode_e MsMutexTryLock(Ms_Mutex_t* mutex)
 * \brief If mutex available, lock it, or return immediately
 * \param[in] mutex control block ptr
 * \return Error code cus_ErrCode_e
 */
cus_ErrCode_e MsMutexTryLock(Ms_Mutex_t* mutex);
/**
 * \fn cus_ErrCode_e MsMutexSetProtocol(Ms_Mutex_t* mutex, Ms_Prio_Invr_e protocol)
 * \brief Set protocol used to resolve priority inversion
 * \param[in] mutex control block ptr
 * \param[in] protocol, only support PRIO_INVR_INHERIT now
 * \return Error code cus_ErrCode_e
 */
cus_ErrCode_e MsMutexSetProtocol(Ms_Mutex_t* mutex, Ms_Prio_Invr_e protocol);

/** @}*/
#endif



