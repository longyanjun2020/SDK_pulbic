/*------------------------------------------------------------------------------
	Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
    PROJECT:
    DESCRIPTION:
          Timer functions

    HISTORY:
         <Date>     <Author>    <Modification Description>
       2009/04/07   Ralf Chen   Initial revision

-------------------------------------------------------------------------------*/


#ifndef __SYS_MSWRAPPER_CUS_OS_TIMER_H__
#define __SYS_MSWRAPPER_CUS_OS_TIMER_H__


/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/

#include "sys_MsWrapper_cus_os_type.h"


/*------------------------------------------------------------------------------
    EXTERN definition
-------------------------------------------------------------------------------*/

#if defined (__COARSE_TIMER__)
#define __COARSE_TIMER_TEST__
#define __DEBUG_TRACE__
#endif

/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef struct MsCbTimer_t_
{
	MsTimerId_e eTimerID;
	u32 UserData;
	void (*pfCB)(MsTimerId_e eTimerID, u32 UserData);
} MsCbTimer_t;

#if defined (__COARSE_TIMER__)
typedef struct CoarseTimerStructure
{
	MsTimerId_e UserTimerId;
	MsTimerId_e eCBTimerID;
	MsMailbox_e eMailbox;
	u16 CoarseTimerId;
	u32 CoarseTimerValue;
	u32 CoarseTimerTolerance;
	u32 CoarseTimerInterval;
	bool DbbOnFire;
	bool MmpOnFire;
} MsCoarseTimer_t;

#endif

/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/
#if defined (__COARSE_TIMER__)
extern MsCoarseTimer_t *MsCoarseTimerList;
#endif


/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/

#if defined (__COARSE_TIMER__)
#define LEN_MS_COARSE_TIMER_t sizeof(MsCoarseTimer_t)

#else
#define LEN_MS_COARSE_TIMER_t 0

#endif



/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
/** \addtogroup TimerMan
 *  @{
 */

/**
 * \fn MsOsErr_e MsStartTimer(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32TimerValue)
 * \brief The MsStartTimer primitive starts or restarts a timer. If the timer referenced by eTimerId is active, it is restarted. The u32TimerValue parameter corresponds to the delay (in system ticks) before the timer expires. When a timer expires, its reference (eTimerId) is sended as a message to the mailbox referenced by the eMailbox parameter. A timer can be used to activate a task after a delay.
 *
 * Programming hint: Note that the TimerID must be registerd and not overlapped with other Timer ID
 * \param[in] eTimerId The Timer ID
 * \param[in] eMailbox The mailbox ID for sending message as the timer expires.
 * \param[in] u32TimerValue Number of ticks before the timer expires
 * \return Always RTK_OK
 */
MsOsErr_e MsStartTimer(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32TimerValue);

/**
 * \fn MsOsErr_e MsStartTimerMs(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32ms)
 * \brief Start a timer in mili second
 * \param[in] eTimerId Timer ID
 * \param[in] eMailbox The mail box to which the timer expiry event will be sent
 * \param[in] u32ms The period of the timer in ms
 * \return MSOS_OK if the action is successful
 */
MsOsErr_e MsStartTimerMs(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32ms);

/**
 * \fn MsOsErr_e MsStartStrictTimer(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32TimerValue)
 * \brief In RTK kernel, the strict timer is not implemented, and MsStartStrictTimer primitive is the same as MsStartTimer primitive
 * \param[in] eTimerId The Timer ID
 * \param[in] eMailbox The mailbox ID for sending message as the timer expires.
 * \param[in] u32TimerValue Number of ticks before the timer expires
 * \return Always RTK_OK
 */
MsOsErr_e MsStartStrictTimer(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32TimerValue);


/**
 * \fn MsOsErr_e MsStartPeriodicTimer(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32TimerValue)
 * \brief The MsStartPeriodicTimer primitive almost the same as MsStartTimer except the timer would queue to timer queue again and again after sending message in the timer expired event. This primitive is used for producing a periodic time out event and the timer never stop until calling MsStopTimer primitive to stop the timer
 * \param[in] eTimerId The Timer ID
 * \param[in] eMailbox The mailbox ID for sending message as the timer expires.
 * \param[in] u32TimerValue Number of ticks before the timer expires. It is also the period of the timer expire event.
 * \return Always RTK_OK
 */
MsOsErr_e MsStartPeriodicTimer(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32TimerValue);

/**
 * \fn MsOsErr_e MsStartPeriodicTimerMs(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32ms)
 * \brief Start a periodic timer in mini second
 * \param[in] eTimerId Timer ID
 * \param[in] eMailbox The mail box to which the timer expiry event will be sent
 * \param[in] u32ms The period of the timer in ms
 * \return MSOS_OK if the action is successful
 */
MsOsErr_e MsStartPeriodicTimerMs(MsTimerId_e eTimerId, MsMailbox_e eMailbox, u32 u32ms);

/**
 * \fn u32 MsStopTimer(MsTimerId_e eTimerId)
 * \brief The MsStopTimer primitive stops the timer identified by eTimerId
 * \param[in] eTimerId The Timer ID
 * \return The number of time ticks that were left when the timer was stopped
 */
u32 MsStopTimer(MsTimerId_e eTimerId);


/**
 * \fn bool MsIsTimerActive(MsTimerId_e eTimerId)
 * \brief The MsIsTimerActive primitive check whether a timer is active or not
 * \param[in] eTimerId The Timer ID
 * \return TRUE is the timer is actived; otherwise, FALSE is return.
 */
bool MsIsTimerActive(MsTimerId_e eTimerId);


/**
 * \fn MsOsErr_e MsStartCbTimer( MsTimerId_e *eTimerID, void (*pfCB)(MsTimerId_e eTimerID, u32 UserData), u32 UserData, u32 trigger, u32 interval)
 * \brief The MsStartCbTimer primitive allow user to active a periodic timer and assign a corrpseonding callback function to handle time exprire event. The trigger is the offset against current tick time that causes timer event to occur. The interval value decides the period of timer events; if interval is zero, the timer event only occurs once.
 *
 * Note that the timer ID (eTimerId) is assign by our system, and the callback timer is performed by a dedicated task, not the calling task.
 *
 * For callback timer, it's recommanded to zero init the tID after invoke timer stop. It's to ensure the same timer ID won't be reused hence influences the next user who gets the same tID by kernel.
 *
 * Sugesstion:
 *
 * MsStartCbTimer(&tID, ...);
 *
 * if (tID != 0)
 *
 * {
 *
 *   MsStopTimer(tID);
 *
 *   tID = 0;
 *
 *}
 * \param[out] eTimerID Timer ID which be assigned dynamically.
 * \param[in] pfCB The callback function to execute as the periodic timer expired.
 * \param[in] UserData User data passed in callback
 * \param[in] trigger Tick value which is offset against current tick time that causes timer to occur.
 * \param[in] interval Tick value which is offset against current tick time that causes timer to reoccur. zero means that it occurs once
 * \return TRUE is the timer is actived; otherwise, FALSE is return.
 */
MsOsErr_e MsStartCbTimer(
	MsTimerId_e *eTimerID,
	void (*pfCB)(MsTimerId_e eTimerID, u32 UserData),
	u32 UserData,
	u32 trigger,
	u32 interval
);

/**
 * \fn MsOsErr_e MsStartCbTimerMs(
	MsTimerId_e *eTimerID,
	void (*pfCB)(MsTimerId_e eTimerID, u32 UserData),
	u32 UserData,
	u32 triggerMs,
	u32 intervalMs
   )
 * \brief Start a callback timer with duration as mini second
 * \param[in|out] Timer ID
 * \param[in] call back
 * \param[in] user data used in call back
 * \param[in] ms value which is offset against current tick time that causes timer to occur
 * \param[in] ms value which is offset against current tick time that causes timer to reoccur
		      zero means that it occurs once
 * \return MSOS_OK if the action is successful
 */
MsOsErr_e MsStartCbTimerMs(
	MsTimerId_e *eTimerID,
	void (*pfCB)(MsTimerId_e eTimerID, u32 UserData),
	u32 UserData,
	u32 triggerMs,
	u32 intervalMs
);

/**
 * \fn MsOsErr_e MsStartCbTimerNative(MsTimerId_e *eTimerID, void (*pfCB)(MsTimerId_e eTimerID, u32 UserData), u32 UserData, u32 trigger, u32 interval)
 * \brief Start a callback timer with duration as HW tick
 * \param[in|out] eTimerID Timer ID
 * \param[in] pfCB call back
 * \param[in] UserData user data used in call back
 * \param[in] trigger value which is offset against current HW tick time that causes timer to occur
 * \param[in] interval value which is offset against current HW tick time that causes timer to reoccur
		      zero means that it occurs once
 * \return MSOS_OK if the action is successful
 */
MsOsErr_e MsStartCbTimerNative(
	MsTimerId_e *eTimerID,
	void (*pfCB)(MsTimerId_e eTimerID, u32 UserData),
	u32 UserData,
	u32 trigger,
	u32 interval
);

/**
 *   \fn u32 MsTimeToExpireFirstTimer(void);
 *   \brief remaining time to expire first timer
 *   \param[in| none
 *   \return: 0 if timer is already expired to be handled
 *             : 0xFFFFFFFF if no timer
 *             : otherwise return remaining time to expire first timer
 */
u32 MsTimeToExpireFirstTimer(void);

/** @}*/

#if defined (__COARSE_TIMER__)
/**
 * \brief Start a coarse timer
 * \param[in] UserTimerId: Timer ID
 * \param[in] eMailbox: The mail box to which the timer expiry event will be sent
 * \param[in] UserTimerValue: The period of the timer in mili-second
 * \param[in] UserTimerTolerance: maximum tolerance of time-out value in ms. i.e. max time-out value would be UserTimerValue + UserTimerTolerance.
 * \param[in] RegularInterval: tick value which is offset against current tick time that causes timer to reoccur
		      zero means that it occurs once
 * \return MSOS_OK if the action is successful
 */
MsOsErr_e MsCoarseTimerStart(MsTimerId_e UserTimerId, MsMailbox_e eMailbox, u32 UserTimerValue, u32 UserTimerTolerance, u32 RegularInterval);

/**
 * \brief Stop a coarse timer
 * \param[in] UserTimerId: Timer ID
 * \return MSOS_OK if the action is successful
 */
MsOsErr_e MsCoarseTimerStop(MsTimerId_e UserTimerId);

/**
 * \brief handle expired coarse timer
 * \param[in] u32 CoarseTimerIdBitField: 	this element is a bitmap, each bit represents if the timerID had been expired. 1 means expired, 0, not expired
 * \param[in] eIsDbb: TRUE mean DBB, FALSE means MMP
 * \return MSOS_OK if the action is successful
 */
MsOsErr_e MsCoarseTimerHandler(u32 CoarseTimerIdBitField, bool eIsDbb);

/**
 * \brief configure the mode of coarse timer
 * \param[in] AvailableDbbCoarseTimerAmount: 0 means dbb coarse timer is NOT in service. others mean available amount of  DBB coarse timer.
 * \return MSOS_OK if the action is successful
 */
MsOsErr_e MsCoarseTimerConfig(u32 AvailableDbbCoarseTimerAmount);

/**
 * \brief repoet error of dbb coarse timer
 * \param[in] CoarseTimerId: coarse timer id
 * \param[in] ErrorValue: error indication
 * \return none
 */
void MsCoarseTimerErrorReport(u16 CoarseTimerId, MsOsErr_e ErrorValue);
#endif

#endif  /* __SYS_MSWRAPPER_CUS_OS_TIMER_H__ */


