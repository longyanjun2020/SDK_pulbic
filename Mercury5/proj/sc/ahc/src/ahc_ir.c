/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ir_ctrl.h"
#include "ahc_common.h" 
#include "ahc_ir.h"

/*===========================================================================
 * Main body
 *===========================================================================*/

//------------------------------------------------------------------------------
//  Function    : AHC_IR_ConfigI2cmAttr
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_IR_ConfigI2cmAttr(IR_I2CM_ATTRIBUTE *psI2cmAttr)
{	
    return IR_Ctrl_Config_I2C(psI2cmAttr);
}

//------------------------------------------------------------------------------
//  Function    : AHC_IR_ReadRegister
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_IR_ReadRegister(UINT16 reg, UINT16* pval)
{
    MMP_ERR ret_val;
    
    ret_val = IR_Ctrl_ReadRegister((MMP_UBYTE)reg, (MMP_UBYTE *)pval);
    
    AHC_IR_CHECK_RETURE_VALUE(ret_val, AHC_IR_NO_ERROR, AHC_IR_RET_TRUE, AHC_IR_RET_FALSE)
}

//------------------------------------------------------------------------------
//  Function    : AHC_IR_WriteRegister
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_IR_WriteRegister(UINT16 reg, UINT16 pval)
{
    MMP_ERR ret_val;
    
    ret_val = IR_Ctrl_WriteRegister((MMP_UBYTE)reg, (MMP_UBYTE)pval);
    
    AHC_IR_CHECK_RETURE_VALUE(ret_val, AHC_IR_NO_ERROR, AHC_IR_RET_TRUE, AHC_IR_RET_FALSE)
}

//------------------------------------------------------------------------------
//  Function    : AHC_IR_ModuleAttached
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_IR_ModuleAttached(void)
{	
    MMP_ERR ret_val;
    
    ret_val = IR_Ctrl_Attached();
    
    AHC_IR_CHECK_RETURE_VALUE(ret_val, AHC_IR_NO_ERROR, AHC_IR_RET_TRUE, AHC_IR_RET_FALSE)
}

//------------------------------------------------------------------------------
//  Function    : AHC_IR_GetIrData
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_IR_GetIrData(IR_DATA *pData)
{
    MMP_ERR ret_val;
    
    ret_val = IR_Ctrl_GetIrData(pData);
    
    AHC_IR_CHECK_RETURE_VALUE(ret_val, AHC_IR_NO_ERROR, AHC_IR_RET_TRUE, AHC_IR_RET_FALSE)
}

//------------------------------------------------------------------------------
//  Function    : AHC_IR_GetIntStatus
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_IR_GetIntStatus(UINT8* pstatus)
{
    MMP_ERR ret_val;
    
    ret_val = IR_Ctrl_GetIntStatus(pstatus);
    
    AHC_IR_CHECK_RETURE_VALUE(ret_val, AHC_IR_NO_ERROR, AHC_IR_RET_TRUE, AHC_IR_RET_FALSE)
}

//------------------------------------------------------------------------------
//  Function    : AHC_IR_GetIntStatus
//  Description : 
//------------------------------------------------------------------------------
AHC_BOOL AHC_IR_Initial(void)
{       
    MMP_ERR ret_val;
    
    ret_val = IR_Ctrl_Initial();
    
    AHC_IR_CHECK_RETURE_VALUE(ret_val, AHC_IR_NO_ERROR, AHC_IR_RET_TRUE, AHC_IR_RET_FALSE)
}

