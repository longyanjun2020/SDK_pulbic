#ifndef _BEE_API_H_
#define _BEE_API_H_

#ifdef __CRASH_NOTIFY_SMS__

#include "sys_bee.hi"
#include "vm_types.ht"

#ifdef __SDK_SIMULATION__
#include <assert.h>
#define BEE_ASSERT(X) assert(X)
#else
#include "cus_os.hc"
#include "sys_traces.ho"
#define BEE_ASSERT(X) _WARNING(X)
#endif

void *bee_AllocMem(u32	u32Size);
void bee_FreeMem(void	*pvData);
#endif
#endif
