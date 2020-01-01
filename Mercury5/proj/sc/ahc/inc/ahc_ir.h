#ifndef _AHC_IR_H_
#define _AHC_IR_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ahc_common.h"
//#include "ahc_general.h" 
#include "mmpf_i2cm.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define AHC_IR_RET_FALSE    (AHC_FALSE)
#define AHC_IR_RET_TRUE     (AHC_TRUE)
#define AHC_IR_NO_ERROR     (MMP_ERR_NONE)
#define AHC_IR_CHECK_RETURE_VALUE(RET_VAL, NO_ERROR, YES, NO) return (RET_VAL == NO_ERROR) ? YES : NO;

/*===========================================================================
 * Function prototype
 *===========================================================================*/
 
AHC_BOOL AHC_IR_ConfigI2cmAttr(IR_I2CM_ATTRIBUTE *psI2cmAttr);
AHC_BOOL AHC_IR_ReadRegister(UINT16 reg,  UINT16* pval);
AHC_BOOL AHC_IR_WriteRegister(UINT16 reg, UINT16 pval);
AHC_BOOL AHC_IR_ModuleAttached(void);
AHC_BOOL AHC_IR_GetIrData(IR_DATA *pData);
AHC_BOOL AHC_IR_GetIntStatus(UINT8 *pstatus);
AHC_BOOL AHC_IR_Initial(void);

#endif // _AHC_IR_H_
