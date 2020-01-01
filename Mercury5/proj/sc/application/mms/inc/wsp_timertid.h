
#ifndef __WSP_TIMERTID_H__
#define __WSP_TIMERTID_H__

#include <wsp_pub.h>

typedef struct T_WTP_Timer T_WTP_Timer;

#define WTP_TID_WINDOW_SIZE 16384

#ifdef __cplusplus
extern  "C" {
#endif

struct T_WTP_Timer {
    int8_t interval;        /**< Timer state. -1 unused;0 timeout;>0  not timeout */
    int8_t event;           /**< Event */
    uint8_t Boundary[2];    /**< Boundary */
    T_WAP_MCB *machine;     /**< MCB(Machine Control Block) */
    struct T_WTP_Timer *next;/**< Next element */
};

struct T_WTP_Tid{
    T_WAP_AddrTuple addr;   /**< Address Tuple */
    uint16_t tid;           /**< Tid */
    uint8_t Boundary[2];    /**< Boundary */
    struct T_WTP_Tid *next; /**< Next element */
};

/**
 * Call this function to do some initialization on timer and TID of WTP.
 *
 *   \param  hc  a wsp instance handle.
 *   \return
 */
 void fnWTP_InitTimerTid(void *hc);

/**
 * Stop timer .
 *
 *   \param  timer the timer to stop.
 *   \return
 */
 void fnWTP_StopTimer(struct T_WTP_Timer *timer);

/**
 * Update timer.If no data transmission or receiving,close timer.
 *           or decrease  the interval of timer .
 *
 *   \param  hc  a wsp instance handle.
 *   \return
 */
 void fnWTP_CheckTimer(void *hc);

/**
 * Call this functiont to add a timer to the timer list.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  timer the timer to add.
 *   \return
 */
 void fnWTP_AddTimer(void *hc,struct T_WTP_Timer *timer);

/**
 * Call this function to delete a timer from the timer list.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  timer the timer to delete.
 *   \return
 */
 void fnWTP_KillTimer(void *hc,struct T_WTP_Timer *timer);

/**
 * Check if the TID is valid.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  m  the MCB to check TID.
 *   \return  Return FALSE if the MCB is NULL or (MCB->tid_new is set and
 *           the cached TID is not NULL) or (MCB->tid_new is not
 *           set and the cached TID is not NULL and the cached TID
 *           is not in window);els return TRUE;
 */
 int32_t fnWTP_IsTidValid(void *hc,T_WAP_MCB *m);

/**
 * Get the cached TID.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  m we need the MCB for address of current session.
 *   \return Return the cached TID if found;or return NULL.
 */struct T_WTP_Tid  *fnWTP_TidCached(void *hc,T_WAP_MCB *m);

/**
 * Add the received TID to the TID list.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  m the MCB.
 *   \param  rcv_tid the received TID.
 *   \return
 */
 void fnWTP_AddTid(void *hc,T_WAP_MCB *m,uint16_t rcv_tid);

/**
 * Set Tid cache to a new value.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  m the source of the TID.
 *   \return
 */void fnWTP_SetTid(void *hc,T_WAP_MCB *m);

/**
 * Check if the TID is in the window.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  rcv_tid the received TID;
 *   \param  last_tid the last TID.
 *   \return If the TID is valid ,return TRUE;else return FALSE.
 */int32_t fnWTP_TidInWindow(uint16_t rcv_tid,uint16_t last_tid);

#ifdef __cplusplus
}
#endif

#endif /* __WSP_TIMERTID_H__ */

