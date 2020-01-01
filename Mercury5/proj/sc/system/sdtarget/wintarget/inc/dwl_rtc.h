#ifndef __DWL_RTC_H__
#define __DWL_RTC_H__

#include "stdcomp.h"

#ifdef __DWL_RTC_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE s32 dwl_SyncRTC(void);

#undef INTERFACE
#endif // #ifndef __DWL_RTC_H__

