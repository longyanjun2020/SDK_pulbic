/*------------------------------------------------------------------------------
	Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
    PROJECT:
    DESCRIPTION:
          RFID Middleware


    HISTORY:
         <Date>     	<Author>    	<Modification Description>
         2011.9.1	Rock		Initial

-------------------------------------------------------------------------------*/
#ifndef __MDL_RFID_MSG_H__
#define __MDL_RFID_MSG_H__

#ifdef __RFID__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "Mae_common_def.h"
//#include "Cus_os_mem.h"
//#include "mml_manager.h"
#include "esl_rfid_itf.h"
#include "Vm_msgof.hc"
#include "sys_MsWrapper_cus_os_msg.h"

/*------------------------------------------------------------------------------
    EXTERN definition
-------------------------------------------------------------------------------*/
#ifdef __MDL_RFID_C__
#define EXTERN
#else   /* __MDL_RFID_C__ */
#define EXTERN  extern
#endif  /* __MDL_RFID_C__ */


/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum __RFID_Drv_Msg_Id_E
{
	VM_MSG_DEF(RFID_API_REQ=VM_CUS53_BASE, void DUMMY)	   /**< Activate RFID device request */
#ifdef __SUPPORT_JSR257__
	VM_MSG_DEF(RFID_LISTENER_REG_REQ, void DUMMY)	  /**< Activate RFID device request  */
	VM_MSG_DEF(RFID_LISTENER_START_REQ, void DUMMY) 	/**< Activate RFID device request  */
#endif	/* __SUPPORT_JSR257__ */
} RFID_Drv_Msg_Id_E;


/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/


#undef EXTERN

#endif //__RFID__

#endif  /* __MDL_RFID_MSG_H__ */

