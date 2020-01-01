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
#ifndef __MDL_RFID_H__
#define __MDL_RFID_H__

#ifdef __RFID__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "srv_resmgr_mmlrfid_types.h"


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
typedef enum
{
    MDL_RFID_MSG_BASE = (VM_CUS56_BASE),

	/* Related to JSR-257 */
    MDL_RFID_INIT= MDL_RFID_MSG_BASE,                     				///<  Open
    MDL_RFID_ADD_TARGET_LISTENER,                     					///<  Add target listener
    MDL_RFID_REMOVE_TARGET_LISTENER,                                     ///<  Remove target listener
    MDL_RFID_CONNECT_TARGET,                                             ///<  Connect target
    MDL_RFID_DISCONNECT_TARGET,                                          ///<  Disconnect target
    MDL_RFID_READ_TARGET,                                                ///<  Read target
    MDL_RFID_WRITE_TARGET,                                               ///<  Write target
    MDL_RFID_ISO443_EXCHANGE_DATA,                                       ///<  ISO443 exchange data
    MDL_RFID_TRANSCEIVE,                                                 ///<  Transceive
	MDL_RFID_AUTO_SCAN,

	/* Related to non-JSR-257 */
    MDL_RFID_GET_READER_INFO,
    MDL_RFID_GET_SIM_CONTROL,
    MDL_RFID_SET_SIM_CONTROL,
    MDL_RFID_MF_COMMAND,
    MDL_RFID_OPEN_TAG,
    MDL_RFID_CLOSE_TAG,
    MDL_RFID_READ_TAG,
    MDL_RFID_WRITE_TAG,
    MDL_RFID_LOCK_TAG,
    MDL_RFID_UPGRADE_FIRMWARE,
    MDL_RFID_READ_BARCODE,

} MdlRfidMsgId_e;


/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef struct Mdl_Rfid_Msg_Body_s
{
  MmlRfidUCParam_t   *pPara;
}Mdl_Rfid_Msg_Body_t;

typedef struct Mdl_Rfid_Msg_Header_s
{
    u8  MbxSrc;
    u8  ModuleID;
    u16  MbxDst;
    s16  Length;
    u16  TypMsg;
} Mdl_Rfid_Msg_Header_t;

/* Structure of the Message */
typedef struct Mdl_Rfid_Msg_s
{
    Mdl_Rfid_Msg_Header_t   	Header;
    Mdl_Rfid_Msg_Body_t  		Body;
} Mdl_Rfid_Msg_t;


/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
EXTERN void MDL_RFID_Task_Init(void);
EXTERN void MDL_RFID_Task_Event_Handler(const void *pMessage);
EXTERN u32 MDL_RFID_Get_MSR3110_FW_Addr(void);


#undef EXTERN

#endif //__RFID__

#endif  /* __MDL_RFID_H__ */

