
#include "config_fw.h"
#include "mmpf_i2cm.h"
#include "os_wrap.h"
#include "mmpf_pio.h"
#include "mmpf_timer.h"
#include "lib_retina.h"
#include "ahc_utility.h"
#include "ait_utility.h"
#include "AHC_Config_SDK.h"

#include "ir_ctrl.h"

static struct _3RD_PARTY_IR *psIR_obj = NULL;
static IR_ATTRIBUTE         sIR_Attribute = {0}; 

MMP_ERR IR_Ctrl_Config_I2C(IR_I2CM_ATTRIBUTE *psI2cmAttr_ir)
{
    if(psIR_obj && IR_Ctrl_Attached())
	{
        return psIR_obj->pIR_Config_I2C(psIR_obj, psI2cmAttr_ir);
    }    
    return MMP_SYSTEM_ERR_HW;
}

MMP_ERR IR_Ctrl_ReadRegister(MMP_UBYTE reg , MMP_UBYTE *pval)
{
    if (psIR_obj && IR_Ctrl_Attached())
	{
        return psIR_obj->pIR_ReadRegister(psIR_obj,reg, pval);
    }    
    return MMP_SYSTEM_ERR_HW;
}

MMP_ERR IR_Ctrl_WriteRegister(MMP_UBYTE reg , MMP_UBYTE val)
{
    if (psIR_obj && IR_Ctrl_Attached()){
        return psIR_obj->pIR_WriteRegister(psIR_obj,reg, val);
    }   
    return MMP_SYSTEM_ERR_HW;
}

MMP_BOOL IR_Ctrl_Attached(void)
{
	if (psIR_obj)
	{
		return psIR_obj->pIR_ModuleAttached(psIR_obj);
	}
	
	return MMP_FALSE;
}

MMP_ERR IR_Ctrl_GetIrData(IR_DATA *pData)
{
	if(psIR_obj && IR_Ctrl_Attached()){
		return psIR_obj->pIR_GetIrData(psIR_obj, pData);
	}
	
    return MMP_SYSTEM_ERR_HW;
}

MMP_ERR IR_Ctrl_GetIntStatus(MMP_UBYTE  *pstatus)
{
    if(psIR_obj && IR_Ctrl_Attached()){
        return psIR_obj->pIR_GetIntStatus(psIR_obj, pstatus);
    }
    return MMP_SYSTEM_ERR_HW;
}

MMP_ERR IR_Ctrl_IDCheck(IR_DATA *pData, MMP_UBYTE  *pstatus)
{
	MMP_USHORT ubReadID;

    ubReadID = (pData->data0<<8) | pData->data1;

    RTNA_DBG_Str(0, "IR ID:");
    RTNA_DBG_Short(0, ubReadID);
    RTNA_DBG_Str(0, ", IR_CUSTOMER_ID:");
    RTNA_DBG_Short(0, IR_CUSTOMER_ID);
    RTNA_DBG_Str(0, "\r\n");

    if ( ubReadID != IR_CUSTOMER_ID )
    	return MMP_SYSTEM_ERR_HW;
    else
    	return MMP_ERR_NONE;
}

MMP_ERR IR_Ctrl_Initial(void)
{
    if(psIR_obj && IR_Ctrl_Attached()){
        return psIR_obj->pIR_Initial(psIR_obj, &sIR_Attribute);
    }    
    return MMP_SYSTEM_ERR_HW;
}

void IR_Ctrl_Register(struct _3RD_PARTY_IR *pdev_obj)
{
    psIR_obj = (struct _3RD_PARTY_IR *)pdev_obj;

    sIR_Attribute.data_updated = 0;
}

void IR_Ctrl_Unregister(void)
{
    psIR_obj = NULL;
    memset(&sIR_Attribute, 0, sizeof(IR_ATTRIBUTE));
}

/// @}
