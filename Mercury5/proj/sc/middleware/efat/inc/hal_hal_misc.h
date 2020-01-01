#ifndef ONCE_HAL_HAL_MISC_H
#define ONCE_HAL_HAL_MISC_H
////////////////////////////////////////////////////////////////////////////////
///@file hal_misc.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


#ifndef __ASSEMBLER__
#include <infra_type.h>         // types & externC

//=============================================================================
externC efat_bool efat_hal_is_break(char *buf, int size);
externC void efat_hal_user_break( EFAT_ADDRWORD *regs );
#endif

//=============================================================================
#endif // ONCE_HAL_HAL_MISC_H
// End of hal_misc.h
