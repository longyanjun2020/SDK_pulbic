/**
* @file    mmi_util_ati.h
* @brief   This file
*
* @version $Id: mmi_util_ati.h 28068 2009-04-10 15:47:23Z zinc.chen $
*/

#ifndef __MMI_UTIL_ATI_H__
#define __MMI_UTIL_ATI_H__
#include "mmi_mae_common_def.h"


#include "vm_types.ht"

typedef enum
{
	MMI_AT_MMI_MODE,          /* MMI sends AT command */
	MMI_AT_EM_MODE,           /* EM sends AT command */
} MMI_AT_MODE;

typedef enum
{
	
	MMI_ATI_INVALID_MSG           /* The Invalid AT commad mode */
} MMI_AT_MSG;

typedef u32 MmiATHdl;


/**
* \brief Initiate the MMI AT
*/
void mmi_ATInit(void);


/**
* \brief Allocation of AT command port
* \return The handle of the AT port
* \param [in] MMI or EM use the AT port 
*/
MmiATHdl mmi_CreateATPort( MMI_AT_MODE mode, u8 u8DualMode);

/**
* \brief Deallocation of AT command command port
* \return None
* \param [in] The handle of the AT command port
*/
boolean mmi_DestoryATPort( MmiATHdl ATHdl, u8 u8DualMode);

/**
* \brief send an AT command to ATI
*
* \return non-null if errors occurred
* \param [in] The handle of the AT port.\n 
* \param [in] AtString Pointer to AT command string.\n
* \param [in] AtString Pointer to AT command string.\n
* command string must be CR+LF characters terminated.\n
* \param [in] AtStringSize Size of the AT string to send (including CRLF characters).
*/
s32 mmi_SendATCmd( MmiATHdl ATHdl, const ascii *AtString, u16 AtStringSize, u8 u8DualMode);

/**
* \brief Get the text content of an message received from AT
*
* \return boolean, true if message is from AT
* \param [in] msg pointer to system message.\n
* \param [out] AtString pointer to copy message content to.\n
* text starts and ends with CR/LF sequences.\n
* \param [out] AtLen pointer to response length, can be NULL
*/
boolean mmi_GetATStr( const struct vm_msg *msg, ascii ** AtString, u16 *AtLen );

/**
* \brief Get MMI AT Message
*
* \return The mode of the AT command
* \param [in] msg pointer to system message.\n
*/
MAE_EventId mmi_ATCheckMsg( const struct vm_msg *msg);

/**
* \brief Match input string from sub string. If matched, token string in front of the sub string and return the remain part
*
* \return TRUE if match, FALSE if not match
* \param [in]  szString    Input string
* \param [in]  szMatch     sub string
* \param [out] szPointer   token buffer
* \param [out] szPointer   return string
*/
bool mmi_StringToken(u8* szString, u8* szMatch, u8** rszToken, u8** rszPointer);


/**
* \brief send Wcus command response to ATI with specific port id.
*
* \param [in] AtString Pointer to AT command string.\n
* command string must be CR+LF characters terminated.\n
* \param [in] AtStringSize Size of the AT string to send (including CRLF characters).
* \param [in] Source mailbox id.\n 
* \param [in] Known AT port id.\n 
* \param [in] Known SIM mode.\n 
*/
void mmi_SendWcusCommandRsp(const u8 *AtString,u16 AtStringSize, u16 nSrcMailbox, u32 nATPort, u8 u8DualMode);

/**
* \brief send Wcus command status to ATI with specific port id.
*
* \param [in] Status.\n 
* \param [in] Source mailbox id.\n 
* \param [in] Known AT port id.\n 
*/
void mmi_SendWcusStatusRsp(u8 u8Status, u8 u8PortId, u16 nSrcMailbox, u8 u8DualMode);

/**
* \Remove String Quotes
*
* \return Remove Quotes String
* \param [in]  szString    Input string
*/
u8* mmi_RemoveStringQuotes(u8* pszString);

/**
 * \brief Get the port id of an message received from AT
 *
 * \return The port id of AT command.
 * \param [in] msg pointer to system message.
 */
u8 mmi_GetATPort( const struct vm_msg *msg);

void mmi_SendWCUSRStatusRsp(u8 u8Status, u16 nSrcMailbox, u32 nATPort, u8 u8DualMode);


/* Count the number of digits of an integer. */
#ifndef COUNT_DIGITS
#define COUNT_DIGITS(nInteger, nLength) { \
    u32 nTemp; \
    nTemp = (nInteger); \
    nLength = 0; \
    do { \
    nTemp /=10; \
    nLength++; \
    } while(0 != nTemp); \
}
#endif

#ifdef ATSYNC_ATCMD_AUTOTEST
/**
* \brief send an AT command to ATI
*
* \return non-null if errors occurred
* \param [in] The handle of the AT port.\n 
* \param [in] AtString Pointer to AT command string.\n
* \param [in] AtString Pointer to AT command string.\n
* command string must be CR+LF characters terminated.\n
* \param [in] AtStringSize Size of the AT string to send (including CRLF characters).
*/
s32 mmi_SendATCmdToRIL( MmiATHdl ATHdl, const ascii *AtString, u16 AtStringSize, u8 u8DualMode);
#endif

#endif /*__MMI_UTIL_ATI_H__*/
