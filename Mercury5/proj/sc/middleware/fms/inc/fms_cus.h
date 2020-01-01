#ifndef __FMS_CUS_H__
#define __FMS_CUS_H__

#include "mdl_fms_cus.h"

#ifdef __FMS_CUS_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

/**
 * @brief Iterate through all of the CUS with `id'
 *
 * @param handle   : a pointer the a CUS handle
 *
 * @retval         : < 0 failure code
 * @retval         : 0   OK
 */
INTERFACE s32 fms_CusClose(fms_CusHandle_t *handle);

#undef INTERFACE
#endif

