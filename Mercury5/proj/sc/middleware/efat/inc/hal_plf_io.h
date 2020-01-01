#ifndef ONCE_PLF_IO_H
#define ONCE_PLF_IO_H
////////////////////////////////////////////////////////////////////////////////
///@file hal_plf_io.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>
#include <hal_hal_misc.h>
//#include <hal_hal_arch.h>
#include <hal_plf_intr.h>

#ifdef __ASSEMBLER__
#define HAL_REG(x)              x
#define HAL_REG8(x)             x
#define HAL_REG16(x)            x
#else
#define HAL_REG(x)              (volatile EFAT_WORD *)(x)
#define HAL_REG8(x)             (volatile EFAT_BYTE *)(x)
#define HAL_REG16(x)            (volatile EFAT_WORD16 *)(x)
#endif

#if defined(HWR_HAL_MIPS_MSTAR_PLATFORM_MONTAGE3) && !defined(__ASSEMBLER__)
#define ARC_EMI_BANK_NUM         6
#define ARC_EMI_BANK_SIZE        0x04000000
#define ARC_EMI_BANK_MASK        0x1C000000
#define ARC_EMI_BANK_BITSHIFT    26
#define ARC_EMI_MEM_SIZE         (ARC_EMI_BANK_NUM * ARC_EMI_BANK_SIZE)
#define ARC_MIU0_MEM_SIZE        0x00028000
#define HAL_IS_ADDR_ATDRAM(x) \
        (ARC_PHYSICAL_ADDRESS((EFAT_ADDRESS)(x)) >= ARC_KSEG_SDRAM_BASE && \
         ARC_PHYSICAL_ADDRESS((EFAT_ADDRESS)(x)) < ARC_KSEG_SDRAM_BASE+ARC_EMI_MEM_SIZE)
#define HAL_IS_ADDR_ATSRAM(x) \
        (ARC_PHYSICAL_ADDRESS((EFAT_ADDRESS)(x)) < ARC_MIU0_MEM_SIZE)
#endif  // HWR_HAL_MIPS_MSTAR_PLATFORM_MONTAGE3

#include <pkgconf_platform_io.h>

//-----------------------------------------------------------------------------
// end of plf_io.h
#endif // ONCE_PLF_IO_H
