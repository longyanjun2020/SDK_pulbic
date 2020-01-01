#ifndef _BEE_KERNEL_H_
#define _BEE_KERNEL_H_

#ifdef __CRASH_NOTIFY_SMS__

#include "sys_bee.hi"

void bee_StartExecReq(ReqItem_st *psReq);
void bee_KerExecCnf(bool bRslt);

#endif
#endif
