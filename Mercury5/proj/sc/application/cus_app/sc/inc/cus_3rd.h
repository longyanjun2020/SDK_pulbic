#ifndef __CUS_3RD_H__
#define __CUS_3RD_H__

#include "vm_types.ht"
#include "ven_common_def.h"

void CusVen_Init(VenApp_TaskId_e taskID);
void CusPlatformVen_Init(u16 mailBox);
bool CusVen_Parser(void* pMessage);

bool CusVen_getMbxIdFromVenId(iVen_App_ID VenId, u16 *pMbx);

bool CusVen_start(iVen_App_ID VenId, void *pData, u32 len, bool bSessionOpen);
bool CusVen_stop(iVen_App_ID VenId);
bool CusVen_suspend(iVen_App_ID VenId);
bool CusVen_resume(iVen_App_ID VenId);
bool CusVen_background(iVen_App_ID VenId, void *pData, u32 len);
bool CusVen_foreground(iVen_App_ID VenId, void *pData, u32 len);

#endif /* __CUS_3RD_H__ */
