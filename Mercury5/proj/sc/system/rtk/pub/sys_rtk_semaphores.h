#ifndef __SYS_RTK_SEMAPHORES_H__
#define __SYS_RTK_SEMAPHORES_H__

/*!
 *  \file rtk_semaphores.h
 *
 *  declaration of dynamically allocated semaphores functions
 */


/*!
 *  \page DYNSEM Dynamic semaphores
 *
 *  RTK offers dynamically allocated semaphores functions.
 *
 *  The hidden type \ref rtk_SemaphoreHandle_t defines a dynamically allocated semaphore.
 *
 *  Application can get this kind of semaphore handles through the \ref RtkDynSemCreate function.
 *
 *  The manipulation of this kind of semaphores can be done through the following functions :
 *
 *  - \ref RtkDynSemProduce to give back (produce) the semaphore
 *  - \ref RtkDynSemConsume to take (consume) the semaphore
 *  - \ref RtkDynSemConsumeDelay to try to take the semaphore for a time-period
 *  - \ref RtkDynSemTryConsume   to take the semaphore if it is ready to be taken
 *
 */

#include "vm_types.ht"
#include "sys_rtk_ho.h"

/*!
 *   \brief Semaphore handle type
 */
typedef void * rtk_SemaphoreHandle_t;

typedef struct vm_Semaphore_s {
  s32                  value;
  s32                  initValue;
  rtk_Envelop_t*       ptrFirstTask;
  rtk_SemaphoreHandle_t handle;
}rtk_Dyn_Semaphor_t ;

/*!
 *    \fn rtk_SemaphoreHandle_t  RtkDynSemCreate(u32 initialValue)
 *
 *    \brief creates a semaphore
 *
 *    \param initialValue the initial value of the semaphore counter
 *
 */
extern rtk_SemaphoreHandle_t  RtkDynSemCreate(u32 initialValue);

/*!
 *    \fn u32 RtkDynSemDestroy( rtk_SemaphoreHandle_t sem )
 *
 *    Destroys all resources allocated for the specified semaphore.
 *    All tasks waiting on this semaphore are released.
 *    This semaphore can no more be used after a call to this function
 *
 *    \param sem the semaphore handle (as returned by RtkDynSemCreate)
 *
 *    \return void
 *
 */
extern void RtkDynSemDestroy(rtk_SemaphoreHandle_t sem);


/*!
 *    \fn u32 RtkDynSemProduce( rtk_SemaphoreHandle_t sem )
 *
 * Give back the Semaphore  (Produce) 
 *
 * \param sem the semaphore handle (as returned by RtkDynSemCreate)
 *
 * \return RTKOK
 */

extern u32 RtkDynSemProduce( rtk_SemaphoreHandle_t sem );


/*!
 *   \fn u32 RtkDynSemConsume( rtk_SemaphoreHandle_t sem);
 *
 *   \brief take Semaphore  (Consume) 
 *
 *   \param sem the semaphore handle
 *   \return RTKOK
 */
extern u32 RtkDynSemConsume( rtk_SemaphoreHandle_t sem);


/*!
 *  \brief Take the semaphore if available or wait for a bounded time.
 *
 *  If the semaphore is already available, take it and return immediately.
 *  Otherwise wait on it. If the caller was not woken up after a certain
 *  amount of time, make the call return. \ref RtkSemProduce needs not
 *  and should not be called even if the return value indicates that the
 *  semaphore could not be obtained before the timer expired.
 *
 *  \param sem               the semaphore handle
 *  \param SemTimeOut        max time to wait for the semaphore
 *
 *  \return - RTK_OK if the semaphore is obtained
 *          - RTK_NO_MESSAGE if the timer expired
 */
extern u8 RtkDynSemConsumeDelay( rtk_SemaphoreHandle_t sem, u32 SemTimeOut );

/*!
 *   \fn u32 RtkDynSemTryConsume( rtk_SemaphoreHandle_t sem)
 *
 *   \brief take Semaphore (Consume) if semaphore not free do not wait. 
 *   \param sem the semaphore handle
 *   \return 
 *         - RTKOK if the semaphore was consumed
 *         - RTKUnitNonAvail if the semaphore was not free
 */
extern u32 RtkDynSemTryConsume( rtk_SemaphoreHandle_t sem);


#endif // __SYS_RTK_SEMAPHORES_H__

