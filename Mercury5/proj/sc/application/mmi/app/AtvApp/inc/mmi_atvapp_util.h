/**
* @file    mmi_gtvapp_util.h
* @version
* @brief   general television utility header file.
*
*/
#ifndef __MMI_ATVAPP_UTIL_H__
#define __MMI_ATVAPP_UTIL_H__

#include "mmi_atvapp_priv.h"
#include "mmi_atvapp.h"

#define MMI_CMMB_ESG_XML_MAX_DATA_LEN	204800

MAE_Ret _AtvEsgDataBufferParse(AtvAppData_t *pThis, u8 *pESGBuff, u32 nESGBuffLength);

MAE_Ret _AtvCatParserGetEmm(AtvAppData_t *pThis, u8 *u8Buff,u16 u16Len);

MAE_Ret _AtvEsgDataXmlBufferParse(AtvAppData_t *pThis, AtvDataType_e eDataType, const u8 *pXmlBuffer, const u32 nXmlBufferLen);

void _AtvParseSearchInfo(AtvAppData_t *pThis, u8 *pESGBuff, u32 nESGBuffLength, AtvSearchType_e eSearchType);

#endif

