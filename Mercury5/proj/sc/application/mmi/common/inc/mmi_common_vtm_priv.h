#ifndef __MMI_COMMON_VTM_H__
#define __MMI_COMMON_VTM_H__

#include "mmi_common_wdgvar.h"

#define CHECK_VTMPARAM(pWndHdl, pWdgList, pData) \
	do \
	{ \
	if(pWndHdl == NULL) { \
	ASSERT(pWndHdl != NULL); \
	return MAE_RET_BAD_PARAM; \
	} \
		else if (pWdgList == NULL) \
		{ \
		ASSERT(pWdgList != NULL); \
		return MAE_RET_BAD_PARAM; \
		} \
		else if (pData == NULL) \
		{ \
		ASSERT(pData != NULL); \
		return MAE_RET_BAD_PARAM; \
		}\
	}while(0); \

#define USE_DEFVALUE(pData, pDefData) \
	do \
	{ \
	if(pData == NULL) \
		{ \
		pData = pDefData; \
		} \
	}while(0); \


#endif //__MMI_COMMON_VTM_H__
