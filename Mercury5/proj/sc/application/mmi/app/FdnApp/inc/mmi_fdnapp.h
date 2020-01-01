#ifndef __MMI_FDNAPP_H__
#define __MMI_FDNAPP_H__

#ifdef __FDN_MMI__
/*-------------------------------------------------------------------------*/
#include "mmi_srv_header.h"
void FdnPreNew(void);
MAE_Ret FDNAPP_New(MAE_ClsId id, void **ppObj);
#endif //__FDN_MMI__
#endif /* __MMI_FDNAPP_H__ */
