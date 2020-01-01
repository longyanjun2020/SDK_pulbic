/*------------------------------------------------------------------------------
	Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
    PROJECT:
    DESCRIPTION:
          System service functions

    HISTORY:
         <Date>     <Author>    <Modification Description>
       2009/04/07   Ralf Chen   Initial revision

-------------------------------------------------------------------------------*/


#ifndef __SYS_MSWRAPPER_CUS_OS_FLAG_H__
#define __SYS_MSWRAPPER_CUS_OS_FLAG_H__


/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/

#include "sys_MsWrapper_cus_os_type.h"


/*------------------------------------------------------------------------------
    EXTERN definition
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

typedef enum {
  MS_FLAG_WAITMODE_AND = (1<<0),             ///< wake up if all bits specified in the mask are set in the flag.
  MS_FLAG_WAITMODE_OR = (1<<1),              ///< wake up if any bits specified in the mask are set in the flag.
  MS_FLAG_WAITMODE_CLR = (1<<2),             ///< clear all bits in the flag when the condition is met. Typically,only the bits that are set in the pattern parameter are cleared.
  MS_FLAG_WAITMODE_CLR_SET = (1<<3)          ///< clear bits specified in the mask are set in the flag when the condition is met. Typically,only the bits that are set in the pattern parameter are cleared.
} _ms_flag_mode_e;

typedef u8 Ms_flag_mode_t;
typedef s32 Ms_flag_value_t;
typedef u32 Ms_tick_count_t;

/******* Structure d'un flag *******/
typedef struct MsFlagStructure
{
	s32 FlagGuard;
	Ms_flag_value_t FlagValue;
	void *PtrFirstTask;
	s32 FlagState;
	u8 FlagId;
} Ms_Flag_t ;


/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
/** \addtogroup FlagMan
 *  @{
 */

/**
 * \fn void MsFlagInit(Ms_Flag_t *PtrFlag)
 * \brief This function initializes a specified flag object
 * \param[out] *PtrFlag Pointer of flag object which would be initialized
 */
void MsFlagInit(Ms_Flag_t *PtrFlag);

/**
 * \fn void MsFlagDestroy(Ms_Flag_t *PtrFlag)
 * \brief This function destroys the specified flag object. Flag objects that are being waited on must not be destroyed
 * \param[in] *PtrFlag Pointer of flag object which would be destroyed
 */
void MsFlagDestroy (Ms_Flag_t *PtrFlag);

/**
 * \fn void MsFlagSetbits(Ms_Flag_t *PtrFlag, Ms_flag_value_t value)
 * \brief This function sets the bits in the flag value of the value parameter to one. Note that only this function could wakeup waiting task
 * \param[out] *PtrFlag Pointer of flag object
 * \param[in] value The bits that are set to one in this parameter are set along with the current bits set in the flag
 */
void MsFlagSetbits (Ms_Flag_t *PtrFlag, Ms_flag_value_t value);

/**
 * \fn void MsFlagMaskbits(Ms_Flag_t *PtrFlag, Ms_flag_value_t value)
 * \brief This function sets the bits in the flag value of the value parameter to zero. Note that no threads are wakeup by this function
 * \param[out] *PtrFlag Pointer of flag object
 * \param[in] value The bits that are set to zero in this parameter are cleared in the flag
 */
void MsFlagMaskbits (Ms_Flag_t *PtrFlag, Ms_flag_value_t value);

/**
 * \fn Ms_flag_value_t MsFlagWait(Ms_Flag_t *PtrFlag, Ms_flag_value_t pattern, Ms_flag_mode_t mode)
 * \brief This function suspends the calling task if condition (pattern) does not meet the flag value of the specified flag. The calling task wakes up as the condition is met.
 *
 * If the mode parameter is set to RTK_FLAG_WAITMODE_AND, the function will wait for all bits in the pattern parameter to be set in the flag value. If the mode parameter is set to RTK_FLAG_WAITMODE_OR, the function will wait for any bits in the pattern parameter to be set in the flag value. If the mode is RTK_FLAG_WAITMODE_CLR, all bits of flag value would be clear when the condition is met. Note that RTK_FLAG_WAITMODE_CLR is bitwise combined with either RTK_FLAG_WAITMODE_AND or RTK_FLAG_WAITMODE_OR flags.
 * \param[out] *PtrFlag Pointer of flag object
 * \param[in] pattern The bit setting that will cause the calling thread to be woken up
 * \param[in] mode The conditions for wake up threads
 */
Ms_flag_value_t MsFlagWait (Ms_Flag_t *PtrFlag, Ms_flag_value_t pattern, Ms_flag_mode_t mode);

/**
 * \fn Ms_flag_value_t MsFlagTimedWait (Ms_Flag_t *PtrFlag, Ms_flag_value_t pattern, Ms_flag_mode_t mode, Ms_tick_count_t relativetime)
 * \brief The function suspends the calling task if condition (pattern) does not meet the flag value of the flag. The calling task wakes up as the condition is met or the waiting time exceeds the specified time (relativetime parameter)
 *
 * The effect of wait mode is the same as MsFlagWait
 * \param[out] *PtrFlag Pointer of flag object
 * \param[in] pattern The bit setting that will cause the calling thread to be woken up
 * \param[in] mode The conditions for wake up threads
 * \param[in] relativetime The waiting time for the flag to meet the conditions
 * \return If the timeout occurs before the conditions are met, zero is returned; otherwise, the flag value is returned as the conditiob is met
 */
Ms_flag_value_t MsFlagTimedWait (Ms_Flag_t *PtrFlag, Ms_flag_value_t pattern, Ms_flag_mode_t mode, Ms_tick_count_t relativetime);

/**
 * \fn Ms_flag_value_t MsFlagPoll (Ms_Flag_t *PtrFlag, Ms_flag_value_t pattern, Ms_flag_mode_t mode)
 * \brief In MsFlagPoll primitive, if the conditions required by the pattern and mode parameters are met, the flag value is returned; otherwise, zero is returned immediately.
 *
 * The effectof wait mode is the same as MsFlagWait
 * \param[out] *PtrFlag Pointer of flag object
 * \param[in] pattern The bit setting that will cause the calling thread to be woken up
 * \param[in] mode The conditions for wake up threads
 * \return If the conditions required by the pattern and mode parameters are met, the flag value is returned; otherwise, zero is returned immediately
 */
Ms_flag_value_t MsFlagPoll (Ms_Flag_t *PtrFlag, Ms_flag_value_t pattern, Ms_flag_mode_t mode);

/**
 * \fn Ms_flag_value_t MsFlagPeek (Ms_Flag_t *PtrFlag)
 * \brief This function returns the current value of the specified flag
 * \param[out] *PtrFlag Pointer of flag object
 * \return The current value of the specified flag
 */
Ms_flag_value_t MsFlagPeek (Ms_Flag_t *PtrFlag);

/**
 * \fn bool MsFlagWaiting (Ms_Flag_t *PtrFlag)
 * \brief This function eturns TRUE if there are any threads waiting on the specified flag; otherwise, return FALSE
 * \param[out] *PtrFlag Pointer of flag object
 * \return The vlue is TRUE if there are any threads waiting on the specified flag; otherwise, return FALSE
 */
bool MsFlagWaiting (Ms_Flag_t *PtrFlag);

void MsFlagDisableService(bool bDisable);

bool MsFlagQueryService(void);


/** @}*/

#endif  /* __SYS_MSWRAPPER_CUS_OS_FLAG_H__ */


