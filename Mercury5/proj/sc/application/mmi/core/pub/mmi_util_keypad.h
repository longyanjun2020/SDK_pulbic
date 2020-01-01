#ifndef __MMI_UTIL_KEYPAD_H__
#define __MMI_UTIL_KEYPAD_H__

#include "mmi_mae_common_def.h"

/**
 * mmi_keypad_SetKeypadMappingTbl()
 *
 * @brief       An interface to set the keypad mapping table defined in \proj\sc\customer\product\cust\drv\keypad\src\cust_keypad_xxx.c.
 * @param pKeypadTbl      keypad table name
 * @retval MAE_RET_SUCCESS      Success
 * @retval MAE_RET_FAILED       Undefined kayped table.
 */
MAE_Ret mmi_keypad_SetKeypadMappingTbl(const char *pKeypadTbl);

/**
 * mmi_keypad_SetDefaultKeypadMappingTbl()
 *
 * @brief   An interface to set the keypad mapping table to default.
 * @retval MAE_RET_SUCCESS      Success
 * @retval MAE_RET_FAILED       Undefined kayped table.
 */
MAE_Ret mmi_keypad_SetDefaultKeypadMappingTbl(void);

#endif // __MMI_UTIL_KEYPAD_H__
