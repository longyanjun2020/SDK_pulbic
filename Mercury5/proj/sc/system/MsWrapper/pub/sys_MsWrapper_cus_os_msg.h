/*------------------------------------------------------------------------------
	Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
    PROJECT:
    DESCRIPTION:
          Functions to send and receive messages

    HISTORY:
         <Date>     <Author>    <Modification Description>
       2009/04/07   Ralf Chen   Initial revision

-------------------------------------------------------------------------------*/


#ifndef __SYS_MSWRAPPER_CUS_OS_MSG_H__
#define __SYS_MSWRAPPER_CUS_OS_MSG_H__


/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/

#include "sys_MsWrapper_cus_os_type.h"
#include "sys_rtk_vmoshi.h"
#include "msgtyp.ht"

/*------------------------------------------------------------------------------
    EXTERN definition
-------------------------------------------------------------------------------*/
#define MsGetMsgAsTimerID(msg) ((MsMsg_t*)(msg))->Body.TimerMsgBody.Ident


/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef union
{
    vm_osTimerMsgBody_t TimerMsgBody;

} UBody_t;

typedef struct
{
    Header_t            Header;
    UBody_t              Body;

} MsMsg_t;

typedef struct
{
	u32 Type;
	void *Msg;
} MsObj_t;


/* Type of the function that converts the timer expiry event to a message. The first
   parameter is the timer ID and the second paramer is the converted message */
typedef void MsTimerExpConvFunc_pfn(MsTimerId_e, void **);


/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
/** \addtogroup MailMan
 *  @{
 */

/**
 * \fn MsOsErr_e MsSend(MsMailbox_e eMailbox, void *pvMsg)
 * \brief The MsSend primitive sends one message to specified mailbox. If no task waits the message, then the message is queued to the message queue. Control is then returned to the calling task without activating the schedule
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[in] pvMsg Pointer of the message
 * \return Always RTK_OK
 */
MsOsErr_e MsSend(MsMailbox_e eMailbox, void *pvMsg);


/**
 * \fn MsOsErr_e MsSendExt(MsMailbox_e eMailbox, void *pvMsg, u32 nParam)
 * \brief The functionality of MsSendExt primitive is almost the same as MsSend primitive, but user can specify a tick count for the task to suspend in sending message if the message box is full of message.
 *
 * Note that the specified time must be inside the range [0x00000000; 0xFFFFFFFF].  Range:
 * - 0x00000000: RTK_MAILBOX_FULL is return immediately
 * - [0x00000001; 0xFFFFFFFD]: suspend for this time ticks. If the message is still waiting after passing specified time, RTK_MAILBOX_FULL is return.
 * - 0xFFFFFFFE: throw RTK_MAILBOX_OVERFLOW exception
 * - 0xFFFFFFFF: suspend until message is sent.
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[in] pvMsg Pointer of the message
 * \param[in] nParam The specified time for task to wait.
 * \return Always RTK_OK
 */
MsOsErr_e MsSendExt(MsMailbox_e eMailbox, void *pvMsg, u32 nParam);


/**
 * \fn MsOsErr_e MsSendWithPrio(MsMailbox_e eMailbox, void *pvMsg)
 * \brief The MsSendWithPrio primitive is almost the same as MsSend except the message has highest priority in the message queue as there is no task waits on the message
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[in] pvMsg Pointer of the message
 * \return Always RTK_OK
 */
MsOsErr_e MsSendWithPrio(MsMailbox_e eMailbox, void *pvMsg);


/**
 * \fn MsOsErr_e MsSendWithPrioExt(MsMailbox_e eMailbox, void *pvMsg, u32 nParam)
 * \brief The functionality of MsSendWithPrioExt primitive is almost the same as MsSendWithPrio primitive except user can specify a tick count for the task to suspend in sending message if the message box is full of message.
 *
 * Note that the specified time must be inside the range [0x00000000; 0xFFFFFFFF].  The Range definition is the same as MsSendExt.
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[in] pvMsg Pointer of the message
 * \param[in] nParam The specified time for task to wait
 * \return Always RTK_OK
 */
MsOsErr_e MsSendWithPrioExt(MsMailbox_e eMailbox, void *pvMsg, u32 nParam);


/**
 * \fn MsOsErr_e MsSendInt(MsMailbox_e eMailbox, void *pvMsg)
 * \brief The MsSendInt primitive almost the same as MsSend except this function is designed for calling in interrupt routine. Be careful of using this primitive
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[in] pvMsg Pointer of the message
 * \return Always RTK_OK
 */
MsOsErr_e MsSendInt(MsMailbox_e eMailbox, void *pvMsg);


/**
 * \fn MsOsErr_e MsSendWithPrioInt(MsMailbox_e eMailbox, void *pvMsg)
 * \brief The MsSendWithPrioInt primitive almost the same as MsSendWithPrio except this function is designed for calling in interrupt routine. Be careful of using this primitive
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[in] pvMsg Pointer of the message
 * \return Always RTK_OK
 */
MsOsErr_e MsSendWithPrioInt(MsMailbox_e eMailbox, void *pvMsg);

/**
 * \fn MsOsErr_e MsSetMbxThreshold(MsMailbox_e eMailbox, u8 threshold);
 * \brief The MsSetMbxThreshold primitive would assign new threshold to the message box, the threshold determines sending the message or not in calling MsSendWithThreshold. Note that only the owner of the message box can assign new threshold
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[in] threshold New threshold value
 * \return MS_OK if threshold of the mailbox changed successfully
 */
MsOsErr_e MsSetMbxThreshold(MsMailbox_e eMailbox, u8 threshold);


/**
 * \fn MsOsErr_e MsSendWithThreshold(MsMailbox_e eMailbox, void *pvMsg)
 * \brief In MsSendWithThreshold primitive, if the current number of message in the mailbox more than the threads of the mailbox which assigned by MsSetMbxThreshold primitive, then the message is send to the maixlox; otherwise, return MS_MAILBOX_OVER_THRESHOLD
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[in] pvMsg Pointer of the message
 * \return RTK_OK if the message is send successfully; otherwise, MS_MAILBOX_OVER_THRESHOLD is return.
 */
MsOsErr_e MsSendWithThreshold(MsMailbox_e eMailbox, void *pvMsg);


/**
 * \fn bool MsReceive(MsMailbox_e eMailbox, MsObj_t *pMsg, MsTimerExpConvFunc_pfn *pfnConv);
 * \brief The MsReceive primitive is used for a task to wait for an object in a mailbox. The received object can be either a message or a timer expiration event. If the mailbox referenced by eMailbox contains at least one pending object, that object is returned to the calling task and the scheduler is not activated. Otherwise the task state is set to waiting, the task is queued to the mailbox¡¦s task queue and the scheduler is activated.
 *
 * The object returned to the calling task can be either a message or an expired timer. If the object is a message, its pMsg->Type field contains the value RTK_OBJ_MESSAGE and its pMsg->Msg field contains the message (void * Msg). If the object is a timer expiration event, its pMsg->Type field contains the value RTK_OBJ_TIMER, and the pfnConv function would determine the content of pMsg->Msg field. If pfnConv is not specified (NULL), default function "MsTimerExpConvFuncDefault" would be used to fill the content of the message.
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[out] pvMsg Pointer of the message
 * \param[in] pfnConv The pointer to the function for handling timer expiration event
 * \return Return True if received successfully; otherwise, return False
 */
bool MsReceive(MsMailbox_e eMailbox, MsObj_t *pMsg, MsTimerExpConvFunc_pfn *pfnConv);


/**
 * \fn bool MsReceiveNoWait(MsMailbox_e eMailbox, MsObj_t *pMsg, MsTimerExpConvFunc_pfn *pfnConv)
 * \brief The MsReceiveNoWaitMsReceive primitive is for a task to test whether a mailbox contains an object. If the mailbox referenced by eMailbox contains at least one pending object, that object is returned to the calling task. Otherwise the primitive returns False. As the scheduler is never activated, this primitive can be used in an interrupt routine.
 *
 * The received object is processed as MsReceive
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[out] pvMsg Pointer of the message
 * \param[in] pfnConv The pointer to the function for handling timer expiration event
 * \return Return True if received successfully; otherwise, return False
 */
bool MsReceiveNoWait(MsMailbox_e eMailbox, MsObj_t *pMsg, MsTimerExpConvFunc_pfn *pfnConv);

/**
 * \fn bool MsMboxStatus(MsMailbox_e MboxNo, u32 *limit, u32 * max, u32 * current)
 * \brief The MsMboxStatus primitive returns the states of the specified mailbox
 * \param[in] eMailbox The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[out] limit The size of the mailbox
 * \param[out] max The maximum message usage of the mailbox
 * \param[out] current The current message usage of the mailbox
 * \return Return True if the mailbox ID is inside the range [0; rtkNbOfMailBox-1]; otherwise, return False.
 */
bool MsMboxStatus(MsMailbox_e MboxNo, u32 *limit, u32 * max, u32 * current);

/**
 * \fn void MsTimerExpConvFuncDefault(MsTimerId_e eTimerId, void **ppvMsg)
 * \brief The MsTimerExpConvFuncDefault primitive is an internal function for filling the content of the message if a timer expiration event happened and the pfnConv function is not specified (NULL) by the message owner.
 *
 * The content of the message is filling as following:
 * - Header.MbxSrc = 0xFF;
 * - Header.ModuleID = 0xFF;
 * - Header.MbxDst = 0xFFFF;
 * - Header.Length = sizeof(vm_osTimerMsgBody_t);
 * - Header.TypMsg = VM_OS_TIMER_EXPIRED;
 * - Body.TimerMsgBody.Ident = eTimerId;
 * \param[in] eTimerId The mailbox ID. 0 <= eMailbox <= rtkNbOfMailBox-1
 * \param[out] ppvMsg Pointer of the message
 * \return Return True if the mailbox ID is inside the range [0; rtkNbOfMailBox-1]; otherwise, return False.
 */
void MsTimerExpConvFuncDefault(MsTimerId_e eTimerId, void **ppvMsg);
/** @}*/
#endif  /* __SYS_MSWRAPPER_CUS_OS_MSG_H__ */


