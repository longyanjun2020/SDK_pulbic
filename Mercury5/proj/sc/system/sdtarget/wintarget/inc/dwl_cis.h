#ifndef __DWL_CIS_H__
#define __DWL_CIS_H__

#include "stdcomp.h"
#include "dwl_medium.h"

#ifdef __DWL_CIS_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE bool dwl_cisOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
INTERFACE bool dwl_cisRead(dwl_handle_t phandle, void *pdata, u32 u32len);
INTERFACE bool dwl_cisClose(dwl_handle_t phandle);
INTERFACE void prg_recv_cis(void);
INTERFACE bool ReloadE2PfromCIS(u8 *pdata);
INTERFACE bool CheckE2P0inCIS(void);
INTERFACE bool BackupE2PtoCIS(void);
INTERFACE bool EraseLastTwoGoodBlocks(void);

#undef INTERFACE

#endif // __DWL_CIS_H__

