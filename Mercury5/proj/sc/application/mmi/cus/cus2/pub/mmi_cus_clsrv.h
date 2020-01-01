#ifndef __MMI_CUS_CLSRV_H__
#define __MMI_CUS_CLSRV_H__

/*include path*/
#include "mmi_cus_clsrv.h"
#include "mmi_clsrv.h"

/*===========================================*/
/*Customer define start*/
/*===========================================*/
#define CALLERLOCATION_DB_FILENAME  L"uxCL_0086.seg"
/*-------------------------------------------------------------------------*/

MAE_WChar * mmi_CUS_CLSRV_GetZoneName(s8* codestr, MAE_WChar * pwFullFilePath, u32 * msgidOut);

/*-------------------------------------------------------------------------*/

/*===========================================*/
/*Customer define End*/
/*===========================================*/

#endif /* __MMI_CUS_CLSRV_H__ */
