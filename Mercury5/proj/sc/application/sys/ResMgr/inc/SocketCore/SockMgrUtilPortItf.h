#ifndef _SOCKMGR_UTIL_PORT_ITF_H_
#define _SOCKMGR_UTIL_PORT_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/


/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

u32 SockMgr_Util_Strlen(u8 *strSrc) ;
s8 SockMgr_Util_Stricmp(u8 *str1, u8 *str2);
s8 SockMgr_Util_Strcmp(u8 *str1, u8 *str2);
bool SockMgr_Util_IsIPAddress(const u8 *inputStr);
void SockMgr_Util_PrintAsciiString(u8 *s);

#endif/* _SOCKMGR_UTIL_PORT_ITF_H_ */
