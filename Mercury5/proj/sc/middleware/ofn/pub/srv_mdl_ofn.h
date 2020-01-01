/**
* @file    srv_mdl_ofn.h
* @version
* @brief   ofn middleware interface.
*
*/

#ifndef __PUBLIC_MDL_OFN_H__
#define __PUBLIC_MDL_OFN_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 *  @brief The enumeration defines the return code of the keypad middle interface
 */
typedef enum
{
    MDL_OFN_OK,                 /**< Function complete successfully */
    MDL_OFN_FAIL,               /**< Function common fail */
    MDL_OFN_MEM_ALLOC_ERROR
} MdlOfnErrCode_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** MdlOfnParser
* @brief        Translate the Ofn  to virtual key code and send to
*               subscribor
* @param[in]    Ofn key message.
* @retval       MDL_OFN_OK,   key processed
*               MDL_OFN_FAIL, key is not processed
*/
MdlOfnErrCode_e  MdlOfnParser(void* pMessage);

/** MdlOfnSubscribe
* @brief        Used to subscribe to the Ofn middleware
* @param[in]    nMailbox       register mailbox ID.
* @param[out]   pnPreMailbox   to get the previous registered mailbox. 0xFF means no mailbox is registered.
*
* @retval       MDL_OFN_OK
*               MDL_OFN_FAIL
*/
MdlOfnErrCode_e MdlOfnSubscribe(u8 nMailbox, u8 *pnPreMailbox);


#endif//__MDL_OFN_H__

