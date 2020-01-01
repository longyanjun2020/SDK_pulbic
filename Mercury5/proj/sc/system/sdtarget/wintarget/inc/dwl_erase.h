#ifndef __DWL_ERASE_H__
#define __DWL_ERASE_H__

#include "stdcomp.h"

#ifdef __DWL_ERASE_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

/**
 * Erase procedure for NOR
 *
 * @param none
 *
 * @retval 0 is success
 * @retval <0 if failed
 */
s32 dwl_NOREraseProcedure(void);

/**
 * Erase procedure for NAND
 *
 * @param none
 *
 * @retval 0 is success
 * @retval <0 if failed
 */

s32 dwl_NANDEraseProcedure(void);

#undef INTERFACE
#endif

