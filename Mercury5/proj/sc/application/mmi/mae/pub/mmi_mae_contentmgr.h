/**
 * @file    mmi_mae_contentmgr.h
 * @brief   The document describes the class definition of contentmgr which may be accessed other functions.
 * @author  kenny.wu@mstarsemi.com
 * @version $Id: mmi_mae_contentmgr.h $
 */
 
#ifndef __MMI_MAE_CONTENTMGR_H__
#define __MMI_MAE_CONTENTMGR_H__

/*------------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"

/* 
* In fact, when ContentDB is not supported, MAEContentMgr is only one of the utility function in MAE,
* but not an MAE_Object anymore!
*/

/**
*	@fn MAEContentMgr_InitRAM(void)
*	@brief	It must be the 1st command that is using to load DB to RAM.
*
*	@param	None.
*	
*	@retval	None.
*/
void MAEContentMgr_InitRAM(void);

/**
*	@fn MAEContentMgr_InitDB(void)
*	@brief	GeneralDB contains 3 parts: EventDB, TaskDB and LogDB, users have to initial these DBs before use it.  
*
*	@param	None.
*	
*	@retval	MAE_RET_SUCCESS				 
*   @retval MAE_RET_FAILED		Fail to get DB handler.
*/
MAE_Ret MAEContentMgr_InitGeneralDB(void);

#endif /* __MMI_MAE_CONTENTMGR_H__ */

