#ifndef __DWL_AD_H__
#define __DWL_AD_H__

#include "stdcomp.h"
#include "dwl_medium.h" // for dwl_handle_t, dwl_TellStatus_t

#ifdef __DWL_AD_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE s32 dwl_NorAdProcessInit(dwl_handle_t *handle, u32 cus_action_param_addr, u32 size, dwl_TellStatus_t pf_tellStatus);
INTERFACE s32 dwl_NorAdProcessComplete(dwl_handle_t *handle, u32 *dummy, const dwl_TellStatus_t pf_tellStatus);

INTERFACE s32 dwl_NorAdProcessInit(dwl_handle_t *handle, u32 cus_action_param_addr, u32 size, dwl_TellStatus_t pf_tellStatus);

INTERFACE s32 dwl_NandAdfAllocate(dwl_handle_t *pHandle, u32 sig, u32 u32len, u32 u32CellSize, u8 *fileName, dwl_TellStatus_t pf_tellStatus);
INTERFACE s32 dwl_NandAdfFinalize(dwl_handle_t phandle, u32 *pu32chksum, dwl_TellStatus_t pf_tellStatus);

INTERFACE bool dwl_adpOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
INTERFACE bool dwl_adpRead(dwl_handle_t phandle, void *pdata, u32 u32len);
INTERFACE bool dwl_adpClose(dwl_handle_t phandle);

#undef INTERFACE
#endif // #ifndef __DWL_AD_H__

