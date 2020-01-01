#ifndef ONCE_IO_H
#define ONCE_IO_H
////////////////////////////////////////////////////////////////////////////////
///@file io.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>
#include <pkgconf_hal.h>
#include <infra_type.h>

#define __EFAT_DEBUG_ON_RTK__
#ifdef __EFAT_DEBUG_ON_RTK__
#include "sys_sys_dbg.h"
extern sys_HwWdtDebugData_t sys_HwWdtDebugData;
#endif

#ifdef PKG_ERROR
#include <error_codes.h>
#else
#error I/O subsystem requires 'error' package
#endif

// typedef int Efat_ErrNo;

#ifdef __cplusplus
extern "C" {
#endif

typedef void *efat_io_handle_t;

// Lookup a device and return it's handle
Efat_ErrNo efat_io_lookup(const char *name,
                        efat_io_handle_t *handle);
// Write data to a device
Efat_ErrNo efat_io_write(efat_io_handle_t handle,
                       const void *buf,
                       efat_uint32 *len);
// Read data from a device
Efat_ErrNo efat_io_read(efat_io_handle_t handle,
                      void *buf,
                      efat_uint32 *len);
// Write data to a block device
#if 1
Efat_ErrNo efat_io_bwrite(efat_io_handle_t handle,
                       const void *buf,
                       efat_uint32 *len,
                       efat_uint32 pos);
// Read data from a block device
#endif

Efat_ErrNo efat_io_bread(efat_io_handle_t handle,
                      void *buf,
                      efat_uint32 *len,
                      efat_uint32 pos);

// Get the configuration of a device
Efat_ErrNo efat_io_get_config(efat_io_handle_t handle,
                            efat_uint32 key,
                            void *buf,
                            efat_uint32 *len);
// Change the configuration of a device
Efat_ErrNo efat_io_set_config(efat_io_handle_t handle,
                            efat_uint32 key,
                            const void *buf,
                            efat_uint32 *len);
// Test a device for readiness
efat_bool efat_io_select(efat_io_handle_t handle,
                       efat_uint32 which,
                       EFAT_ADDRWORD info);

#if defined(__EFAT_DEBUG_ON_RTK__)
#define SET_FS_PROTECT_STEP(_STEP_)                     \
  {                                                     \
    if (!sys_HwWdtDebugData.BacktraceOver1Time)         \
      sys_HwWdtDebugData.Backtrace1stFlow = (u8)_STEP_; \
  }
#else
#define SET_FS_PROTECT_STEP(_STEP_)
#endif

#ifdef __cplusplus
}
#endif

#endif  /* ONCE_IO_H */
/* EOF io.h */
