
#include "Customer_config.h" //for SUPPORT_IR_CONVERTER
#include "os_wrap.h"
#include "config_fw.h"
#include "mmpf_typedef.h"
#include "lib_retina.h"
#include "mmp_err.h"
#include "mmpf_pio.h"
#include "ahc_common.h"
#include "mmpf_i2cm.h"

#if ((SUPPORT_IR_CONVERTER || SUPPORT_DTV_TOUCH_REMOTE) && (IR_MODULE == IR_MODULE_IRC120X))

#include "IR_IRC120x.h"

#if (IR_CONVERTER_USE_SOFT_I2CM == 0x1)
static MMP_I2CM_ATTR m_I2cmAttr_ir = {
	MMP_I2CM_GPIO,
	IR_SLAVE_ADDR,
	8,
	8,
	0x2,
	MMP_FALSE,
	MMP_FALSE,
	MMP_FALSE,
	MMP_FALSE,
	0,
	0,
	0,
	50000,
	MMP_TRUE,
	IR_SCL,
	IR_SDA,
	MMP_TRUE,
	MMP_FALSE,
	MMP_FALSE,
	0
};
#else
static MMP_I2CM_ATTR m_I2cmAttr_ir = {
	MMP_I2CM1,
    IR_SLAVE_ADDR,
    8,
    8,
    0x02,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    0,
    0,
    1,
    200000,
    MMP_TRUE,
    IR_SCL,
    IR_SDA,
    MMP_TRUE,
    MMP_FALSE,
    MMP_FALSE,
    0
};
#endif

#if (IR_DBG_MSG && defined(ALL_FW))
extern void	printc( char* szFormat, ... );
#define	DPRINT( ... ) printc( __VA_ARGS__ )
#else
#define	DPRINT( ... ) {}
#endif

static MMP_ERR IRC120x_IR_Config_I2CM(struct _3RD_PARTY_IR *pthis, IR_I2CM_ATTRIBUTE *psI2cmattr)
{
	m_I2cmAttr_ir.i2cmID 		= psI2cmattr->i2cmID;
	m_I2cmAttr_ir.ubPadNum 		= psI2cmattr->ubPadNum;
	m_I2cmAttr_ir.ulI2cmSpeed	= psI2cmattr->ulI2cmSpeed;
    m_I2cmAttr_ir.sw_clk_pin    = psI2cmattr->sw_clk_pin;
    m_I2cmAttr_ir.sw_data_pin   = psI2cmattr->sw_data_pin;
    
    return MMP_ERR_NONE;
}

static MMP_ERR IRC120x_IR_ReadRegister(struct _3RD_PARTY_IR *pthis, MMP_UBYTE reg , MMP_UBYTE *pval)
{
	MMP_USHORT data;
    
	MMPF_I2cm_ReadReg(&m_I2cmAttr_ir, (MMP_USHORT)reg, (MMP_USHORT*)&data);
	
	*pval = (MMP_UBYTE)(data & 0x00FF);
	
	return MMP_ERR_NONE;
}

static MMP_ERR IRC120x_IR_WriteRegister(struct _3RD_PARTY_IR *pthis, MMP_UBYTE reg , MMP_UBYTE val)
{	
	MMPF_I2cm_WriteReg(&m_I2cmAttr_ir, (MMP_USHORT)reg, (MMP_USHORT)val);
	
	return MMP_ERR_NONE;
}

static MMP_BOOL IRC120x_IR_ModuleAttached(struct _3RD_PARTY_IR *pthis)
{
	return AHC_TRUE;
}	

static MMP_ERR IRC120x_IR_GetIrData(struct _3RD_PARTY_IR *pthis, IR_DATA *data)
{
	MMP_USHORT	KeyCode[4];

	MMPF_I2cm_ReadBurstData(&m_I2cmAttr_ir, 0, KeyCode, 4);

    data->data0 = KeyCode[0];
    data->data1 = KeyCode[1];
    data->data2 = KeyCode[2];
    data->data3 = KeyCode[3];
    data->repeat_times = 0;
	
	return MMP_ERR_NONE;
}

static MMP_ERR IRC120x_IR_GetIntStatus(struct _3RD_PARTY_IR *pthis, MMP_UBYTE *Value)
{
	UINT8 tempValue = 0;
	
    #ifdef IR_INTR
    if (IR_INTR != MMP_GPIO_MAX) {
		AHC_GPIO_GetData(IR_INTR, &tempValue);
    }
    #endif
    
	if (Value)
        *Value = tempValue;

	return MMP_ERR_NONE;
}

static MMP_ERR IRC120x_IR_Initial(struct _3RD_PARTY_IR *pthis, IR_ATTRIBUTE *pgsnr_attr)//R_DATA *ir_data)
{
    #ifdef IR_INTR
    if (IR_INTR != MMP_GPIO_MAX) {
        AHC_GPIO_ConfigPad(IR_INTR, PAD_NORMAL_TRIG | PAD_PULL_UP);
        AHC_GPIO_SetOutputMode(IR_INTR, MMP_FALSE);
    }
    #endif
    	
	return MMP_ERR_NONE;
}

struct _3RD_PARTY_IR IR_Obj = 
{
    IRC120x_IR_Initial,
	IRC120x_IR_GetIntStatus,
	IRC120x_IR_GetIrData,
	IRC120x_IR_ModuleAttached,
    IRC120x_IR_Config_I2CM,
    IRC120x_IR_ReadRegister,
    IRC120x_IR_WriteRegister
};


int IR_Module_Init(void)
{
    RTNA_DBG_Str(0, FG_GREEN("IR_Module_Init for IRC120x\r\n"));
    IR_Ctrl_Register(&IR_Obj);
    return 0;    
}

#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6" 
#pragma O0
ait_module_init(IR_Module_Init);
#pragma
#pragma arm section rodata, rwdata ,  zidata 


#endif		// #if (SUPPORT_IR_CONVERTER)

