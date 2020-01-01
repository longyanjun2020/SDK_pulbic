#ifndef _DRV_MFE_MODULE_H_
#define _DRV_MFE_MODULE_H_

#include "drv_mfe_kernel.h"

#define MFE_OFFSET  0x00264800
#define MFE_SIZE    0x200

mmfe_ctx*   MfeOpen(mmfe_dev* mdev, mmfe_ctx* mctx, int strm_id);
int         MfeRelease(mmfe_dev* mdev, mmfe_ctx* mctx);
mmfe_dev*   MfeProbe(mmfe_dev* mdev, void* pCBFunc);
int         MfeRemove(mmfe_dev* mdev);

#endif //_DRV_MFE_MODULE_H_
