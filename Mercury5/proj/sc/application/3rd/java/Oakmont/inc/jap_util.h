
#ifndef JAP_UTIL_HEADER
#define JAP_UTIL_HEADER
/**
*
* @file    jap_util.h
* @brief
*
* @author  Jim.Lee
* @version $Id: jap_util.h 46000 2009-11-18 08:20:01Z owen.lee $
*
*/

#include "JkTypes.h"
#include "ven_common_def.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
*  jap_tool_getContent
*
*  @brief  Get matched value in file (File name is "content.inf" in "java_root")
*
*  @param  attr          [in] The target string you want to find.
*  @param  attrlen       [in] The length of attr.
*  @param  buffer        [out]The buffer to store the result string value.
*  @param  buffSize      [in] The length of attr.
*
*  @retval string length of the match string.
*          0 target string not find.
*		  -1 internal error.
*/
JKSint32 jap_util_getTCKAttr(JKUint8* attr, JKUint32 attrlen, JKUint8* buffer, JKUint32 buffSize);

void jap_utl_clean_screen(void);

void jap_utl_terminate_err(int errType);

void jap_utl_show_err(int errType, bool repaint);

void jap_Util_Int64Multiple(u32 m1H, u32 m1L, u32 m2H, u32 m2L, u32 * retH, u32 * retL);
void jap_Util_Int64Add(u32 a1H, u32 a1L, u32 a2H, u32 a2L, u32 * retH, u32 * retL);
void jap_Util_Int64Sub(u32 a1H, u32 a1L, u32 a2H, u32 a2L, u32 * retH, u32 * retL);

/* Set resync flag to sync file manager DB in jv_fini_resource */
extern void jap_utl_ReSyncDB(void);

/* Create MStar full path from UTF8 string */
extern u16 * jap_createFullPath(const char* path);

extern u8* JavaJap_GetVersionInfo(void);

extern void Jap_PrintWString(JKWChar* pWchar);

#ifdef __cplusplus
}
#endif

#endif /* JAP_UTIL_HEADER */

