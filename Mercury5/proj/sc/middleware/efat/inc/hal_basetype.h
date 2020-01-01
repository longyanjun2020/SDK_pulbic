#ifndef ONCE_HAL_BASETYPE_H
#define ONCE_HAL_BASETYPE_H
////////////////////////////////////////////////////////////////////////////////
///@file hal_basetypes.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>

//-----------------------------------------------------------------------------
// Characterize the architecture
#define PKG_HAL_MIPS_LSBFIRST

#if defined(PKG_HAL_MIPS_MSBFIRST)
#define EFAT_BYTEORDER           EFAT_MSBFIRST    // Big endian
#elif defined(PKG_HAL_MIPS_LSBFIRST)
#define EFAT_BYTEORDER           EFAT_LSBFIRST    // Little endian
#else
//# error MIPS endianess not defined by configuration
#endif

#if defined(PKG_HAL_MIPS_DOUBLE_MSBFIRST)
#define EFAT_DOUBLE_BYTEORDER    EFAT_MSBFIRST    // Big endian
#elif defined(PKG_HAL_MIPS_DOUBLE_LSBFIRST)
#define EFAT_DOUBLE_BYTEORDER    EFAT_LSBFIRST    // Little endian
#else
#define EFAT_DOUBLE_BYTEORDER EFAT_BYTEORDER      // default to CPU endianess
#endif

//-----------------------------------------------------------------------------
#endif // ONCE_HAL_BASETYPE_H
// End of basetype.h
