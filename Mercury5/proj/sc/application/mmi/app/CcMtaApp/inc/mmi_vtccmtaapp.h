/**
* @file mmi_vtccmtaapp.h
*
* Class Id: CLSID_CCMTA
*
*/
#ifndef __MMI_VTCCMTAAPP_H__
#define __MMI_VTCCMTAAPP_H__

#include "mmi_srv_header.h"

#ifdef __APP_VIDEO_TELEPHONY__
MAE_Ret VTCCMTA_New(MAE_ClsId id, void **ppObj);
#endif
#endif /* __MMI_CCMTAAPP_H__ */
