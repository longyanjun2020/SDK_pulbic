#ifndef _MDW_AUD_CLK_H_
#define _MDW_AUD_CLK_H_

#include "vm_types.ht"
#include "mdl_cpu_pub.h"

extern MdlCpuSpeed_e geCodecCLK, geAUDPlayCLK;

void MDLAudPlayerPostProcClkMgr(void *pInst, MdlCpuSpeed_e eCodecCLK , MdlCpuSpeed_e *SetCLK);

#endif

