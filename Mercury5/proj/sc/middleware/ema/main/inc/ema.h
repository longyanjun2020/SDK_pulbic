/**
 *
 * @file    ema.h
 *
 * @brief   This file defines the common header for EMA task
 *
 * @author  Pauli Leong
 * @version $Id: ema.h 14050 2008-09-11 11:34:44Z pauli.leong $
 *
 */
#ifndef __EMA_H__
#define __EMA_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_stdio.ho"
#include "sys_rtk_vmrtkho.h"
#include "sys_vm_dbg.ho"
#include "sys_rtk_vmoshi.h"
#include "vm_osdef.hc"
#include "vm_msgof.hc"
#include "cus_os.hc"
#include "ema_util.h"
#include "ema.ht"
#include "ema.hc"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_util.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif

#define __EMA_DEBUG__

/* This definition is used to load OSD before starting preview */
#define __EMA_CAM_PRE_OSD__

/* This definition is used to enable sticker capture */
#define __EMA_CAM_STICKER_SHOOT__

/* This definition is used to fix Op Amp notification problem */
/* Because M2 will trigger a lot of INTs in short time and let VOC task mail box overflow */
/* Ref. PR 0040768 */
#define __EMA_FIX_OPAMP_INT_BUG__

#ifdef __EMA_FIX_OPAMP_INT_BUG__ /* Ref. PR 0040768 */
#define M2_OPAMP_NOTIFY 0xA5 /* (0xFF <<24) | (0xA5 <<16) | 0x200 */
#define M2_OPAMP_CNT    0x02
#endif /* End of __EMA_FIX_OPAMP_INT_BUG__ */

#define	__BACKUP_MMP_EFS_INFO__

/* This definition is used to enable MMP power management test */
//#define __MMP_PWR_SELF_TEST__

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/
#define EMA_SYNC_RETRIEVE_EVENT   {_TRACE((_CUS2|LEVEL_3, "SYNC LOCK")); MsConsumeSem(EMA_SYNC_RSP_SEM); _TRACE((_CUS2|LEVEL_3, "SYNC BE UNLOCKED"));}
#define EMA_SYNC_SET_EVENT        {_TRACE((_CUS2|LEVEL_3, "SYNC UNLOCK")); MsProduceSem(EMA_SYNC_RSP_SEM);}

#define NRAI_SYNC_RETRIEVE_EVENT   {_TRACE((_CUS2|LEVEL_3, "SYNC LOCK")); MsConsumeSem(NRAI_SYNC_RSP_SEM); _TRACE((_CUS2|LEVEL_3, "SYNC BE UNLOCKED"));}
#define NRAI_SYNC_SET_EVENT        {_TRACE((_CUS2|LEVEL_3, "SYNC UNLOCK")); MsProduceSem(NRAI_SYNC_RSP_SEM);}

#define EMA_CMD_RETRIEVE_EVENT    {_TRACE((_CUS2|LEVEL_3, "CMD LOCK")); MsConsumeSem(EMA_SEM); _TRACE((_CUS2|LEVEL_3, "CMD BE UNLOCKED"));}
#define EMA_CMD_SET_EVENT         {_TRACE((_CUS2|LEVEL_3, "CMD UNLOCK")); MsProduceSem(EMA_SEM);}

#define EMA_REENTRY_LOCK   				{_TRACE((_CUS2|LEVEL_3, "Re-Entry LOCK")); MsConsumeSem(EMA_REENTRY_LOCK_SEM); _TRACE((_CUS2|LEVEL_3, "Re-Entry BE UNLOCKED"));}
#define EMA_REENTRY_UNLOCK        {_TRACE((_CUS2|LEVEL_3, "Re-Entry UNLOCK")); MsProduceSem(EMA_REENTRY_LOCK_SEM);}

#ifdef __EMA_ENHANCEMENT__
#define EMA_RETRIEVE_EVENT        {_TRACE((_CUS2|LEVEL_3, "EMA STATE LOCK, tid  = %d", MsCurrTask())); MsConsumeSem(MULTI_TASK_EMA_SEM); _TRACE((_CUS2|LEVEL_3, "EMA STATE BE UNLOCKED, tid  = %d", MsCurrTask()));}
#define EMA_SET_EVENT             {_TRACE((_CUS2|LEVEL_3, "EMA STATE UNLOCK, tid  = %d", MsCurrTask())); MsProduceSem(MULTI_TASK_EMA_SEM);}
//#define GSS_CMD_RETRIEVE_EVENT    {_TRACE((_CUS2|LEVEL_3, "GSS CMD LOCK, tid  = %d", MsCurrTask())); MsConsumeSem(GSS_CMD_SEM); _TRACE((_CUS2|LEVEL_3, "GSS CMD BE UNLOCKED, tid  = %d", MsCurrTask()));}
//#define GSS_CMD_SET_EVENT         {_TRACE((_CUS2|LEVEL_3, "GSS CMD UNLOCK, tid  = %d", MsCurrTask())); MsProduceSem(GSS_CMD_SEM);}
#define EFS_CMD_RETRIEVE_EVENT    {_TRACE((_CUS2|LEVEL_3, "EFS CMD LOCK, tid  = %d", MsCurrTask())); MsConsumeSem(EFS_CMD_SEM); _TRACE((_CUS2|LEVEL_3, "EFS CMD BE UNLOCKED, tid  = %d", MsCurrTask()));}
#define EFS_CMD_SET_EVENT         {_TRACE((_CUS2|LEVEL_3, "EFS CMD UNLOCK, tid  = %d", MsCurrTask())); MsProduceSem(EFS_CMD_SEM);}
#else
#define EMA_RETRIEVE_EVENT
#define EMA_SET_EVENT
#define EFS_CMD_RETRIEVE_EVENT    {_TRACE((_CUS2|LEVEL_3, "CMD LOCK")); MsConsumeSem(EMA_SEM); _TRACE((_CUS2|LEVEL_3, "CMD BE UNLOCKED"));}
#define EFS_CMD_SET_EVENT         {_TRACE((_CUS2|LEVEL_3, "CMD UNLOCK")); MsProduceSem(EMA_SEM);}
#endif


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/
DefExtern	u32								emaMmpCommand;
DefExtern	u32								lastMmpCommand;

#ifdef __EMA_ENHANCEMENT__
//DefExtern	u32								gssMmpCommand;
DefExtern	u32								nEfsMmpCommand;
#define efsMmpCommand       nEfsMmpCommand
#else
#define efsMmpCommand       emaMmpCommand
#endif



/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/



/**
 * @brief EMA Handler task mailbox message parser
 *
 * @param  pMessage		: EMA task message information
 *
 * @return NONE
 */
void ema_Parse(void *pMessage);


/**
 * @brief This function is used to set the EMA state
 *        For EMA_STATE_NOT_READY, EMA_STATE_SETUP and EMA_STATE_IDLE,
 *        This function will directly change the state value if authorized.
 *        For other function state, this API will set the related BIT to indicate
 *        related MMP function is set to active flag as following table.
 *
 * FUNCTION
 * ========
 *     CAM ----------------------------------------|
 *     AUD ---------------------------------------||
 * AUD-STM --------------------------------------|||
 *     VDO -------------------------------------||||
 *  VDO-SW ------------------------------------|||||
 *     USB -----------------------------------||||||
 * USB-CDC ----------------------------------|||||||
 *    DISP ---------------------------------||||||||
 *      IP -------------------------------| ||||||||
 *      FS ------------------------------|| ||||||||
 * USB-MSC -----------------------------||| ||||||||
 *     SYS ----------------------------|||| ||||||||
 *                                     |||| ||||||||
 *              XX0000000 00000000 00000000 00000000
 *  STAGE       ||
 * =======      ||
 * NOT_READY ---||
 *     SETUP ----|
 *      IDLE => '0x0000'
 *
 * @param  state              : EMA state to set
 *
 * @retval EMA_SUCCESS        : Set state success
 * @retval EMA_FAIL           : Set state fail because of unacceptable setting EMA state to IDLE/SETUP/NOT_READY
 * @retval EMA_STATE_ERROR    : Set state fail state/function confliction
 * @retval EMA_PARAM_ERROR    : Set state fail becuase of directly setting EMA state to incorrect function combined state
 */
ema_ErrCode_e ema_SetState(ema_StateMachine_t state);


/**
 * @brief This function is used to clear the input EMA state
 *
 * @param  state  : Flag of state is going to clear as following table
 *
 * FUNCTION
 * ========
 *     CAM ----------------------------------------|
 *     AUD ---------------------------------------||
 * AUD-STM --------------------------------------|||
 *     VDO -------------------------------------||||
 *  VDO-SW ------------------------------------|||||
 *     USB -----------------------------------||||||
 * USB-CDC ----------------------------------|||||||
 *    DISP ---------------------------------||||||||
 *      IP -------------------------------| ||||||||
 *      FS ------------------------------|| ||||||||
 * USB-MSC -----------------------------||| ||||||||
 *     SYS ----------------------------|||| ||||||||
 *                                     |||| ||||||||
 *              XX0000000 00000000 00000000 00000000
 *  STAGE       ||
 * =======      ||
 * NOT_READY ---||
 *     SETUP ----|
 *      IDLE => '0x0000'
 *
 * @retval EMA_SUCCESS        : Clear state success
 * @retval EMA_FAIL           : Clear state fail becuase the input state is not in 'active' condition
 * @retval EMA_PARAM_ERROR    : Clear state error becuase of input state is not allowed to BIT clear
 * @retval EMA_STATE_ERROR    : Clear state error becuase of current state is not allowed to clear any function state
 */
ema_ErrCode_e ema_ClearState(ema_StateMachine_t state);


/**
 * @brief This function is used to query current active state flags ( '1' = Active )
 *
 * @param  None
 *
 * @return ema_StateMachine_t    : Current EMA flag as following description
 *
 * FUNCTION
 * ========
 *     CAM ----------------------------------------|
 *     AUD ---------------------------------------||
 * AUD-STM --------------------------------------|||
 *     VDO -------------------------------------||||
 *  VDO-SW ------------------------------------|||||
 *     USB -----------------------------------||||||
 * USB-CDC ----------------------------------|||||||
 *    DISP ---------------------------------||||||||
 *      IP -------------------------------| ||||||||
 *      FS ------------------------------|| ||||||||
 * USB-MSC -----------------------------||| ||||||||
 *     SYS ----------------------------|||| ||||||||
 *                                     |||| ||||||||
 *              XX0000000 00000000 00000000 00000000
 *  STAGE       ||
 * =======      ||
 * NOT_READY ---||
 *     SETUP ----|
 *      IDLE => '0x0000'
 */
ema_StateMachine_t ema_GetState(void);


/**
 * @brief This function is used to query the properly buffer length for file read/write
 *
 * @param  None
 *
 * @return u32    : The properly buffer size for Current EMA state
 */
u32 ema_GetProperlyBufferLength(void);


/**
 * @brief This function is used to set if SD card has been changed or not
 *
 * @param  None
 *
 * @return 0
 */
u32 ema_SetSdCardChangeFlag(void);



/**
 *	@brief	This function is used to query EMA is ready to accept requirement
 *
 *	@param	None
 *
 *	@retval	TRUE	EMA ready to accept requirement
 *					FALSE	EMA is not ready to accept requirement
 */
bool ema_QueryReadyToAccept(void);


/**
 *	@brief	This function is used to query EMA is ready to accept requirement
 *
 *	@param	None
 *
 *	@retval	TRUE	EMA ready to accept requirement
 *					FALSE	EMA is not ready to accept requirement
 */
bool ema_QueryReadyToReceiveFsRequest(void);


#ifdef __EMA_FIX_OPAMP_INT_BUG__ /* Ref. PR 0040768 */
/**
 * @brief Reset EMA handlers state.
 *
 * @param  None
 *
 * @return None
 */
void ema_ResetHandlerState(void);

/**
 * @brief EMA notify reset.
 *
 * @param  None
 *
 * @return None
 */
void ema_NotifyReset(void);

#endif /* End of __EMA_FIX_OPAMP_INT_BUG__ */

#endif /*__EMA_H__ */

