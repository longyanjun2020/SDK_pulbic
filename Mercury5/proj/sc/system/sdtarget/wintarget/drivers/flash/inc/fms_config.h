#ifndef __FMS_CONFIG__H__
#define __FMS_CONFIG__H__

#include "vm_types.ht"
#include "fms_e2p.hi"

#define KB(n) ((n) << 10)

#define FMS_E2P_E2PSIZE    KB(8)

extern const e2p_write_t FMS_E2P_DEFAULT_WRITE_METHOD;
/*
  * back trace size. The size will be expanded to occupy all small sectors automatically
  */
extern u32 FMS_TRACE_SIZE;

/* RAI size. Will be aligned to sector-aligned */
extern u32 FMS_RAI_SIZE;

extern const u32 FMS_RAINUMBEROFENTRIES;

extern const u32 FMS_E2PONRAI_CACHE_FLUSH_PERIOD; // in terms of seconds

extern u32 FMS_E2PONRAI_RECORD_BASE_SIZE_POWER_OF_2;

extern u32 E2P_RECORD_BASE_SIZE;

#endif

