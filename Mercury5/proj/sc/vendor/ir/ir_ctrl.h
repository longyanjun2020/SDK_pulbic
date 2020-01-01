#ifndef _MMPF_IR_H_
#define _MMPF_IR_H_

#include "mmpf_i2cm.h"

typedef struct _IR_DATA
{
	MMP_UBYTE	data0;
	MMP_UBYTE	data1;
	MMP_UBYTE	data2;
	MMP_UBYTE	data3;
	MMP_UBYTE	repeat_times;
} IR_DATA;

typedef struct  _IR_ATTRIBUTE
{
	MMP_UBYTE	data_updated;
	MMP_UBYTE	nInited;
	MMP_UBYTE	reserved[3];
}IR_ATTRIBUTE, *PIR_ATTRIBUTE;

typedef struct  _IR_I2CM_ATTRIBUTE
{ 
   MMP_I2CM_ID      i2cmID;				//MMP_I2CM0 ~ MMP_I2CM3 stand for HW I2CM
   MMP_UBYTE 		ubPadNum;      		//HW pad map, the relate pad definition, please refer global register spec.
   MMP_ULONG 		ulI2cmSpeed; 		//SW and HW I2CM speed control, the unit is HZ.
   MMP_GPIO_PIN 	sw_clk_pin;  		//Used in SW I2CM (i2cmID = MMP_I2CM_GPIO only), indicate the clock pin
   MMP_GPIO_PIN 	sw_data_pin;	 	//Used in SW I2CM (i2cmID = MMP_I2CM_GPIO only), indicate the data pin
} IR_I2CM_ATTRIBUTE;

typedef struct _3RD_PARTY_IR
{
    MMP_ERR  (*pIR_Initial)(struct _3RD_PARTY_IR *, IR_ATTRIBUTE *);
    MMP_ERR  (*pIR_GetIntStatus)(struct _3RD_PARTY_IR *, MMP_UBYTE *);
    MMP_ERR  (*pIR_GetIrData)(struct _3RD_PARTY_IR *, IR_DATA *);
    MMP_BOOL (*pIR_ModuleAttached)(struct _3RD_PARTY_IR *);	
    MMP_ERR  (*pIR_Config_I2C)(struct _3RD_PARTY_IR *, IR_I2CM_ATTRIBUTE *);
    MMP_ERR  (*pIR_ReadRegister)(struct _3RD_PARTY_IR *, MMP_UBYTE , MMP_UBYTE *);	
    MMP_ERR  (*pIR_WriteRegister)(struct _3RD_PARTY_IR *, MMP_UBYTE , MMP_UBYTE );
}THIRD_PARTY_IR;

MMP_ERR  IR_Ctrl_Config_I2C(IR_I2CM_ATTRIBUTE *psI2cmAttr_ir);
MMP_ERR  IR_Ctrl_ReadRegister(MMP_UBYTE reg , MMP_UBYTE *pval);
MMP_ERR  IR_Ctrl_WriteRegister(MMP_UBYTE reg , MMP_UBYTE val);
MMP_BOOL IR_Ctrl_Attached(void);
MMP_ERR  IR_Ctrl_GetIrData(IR_DATA *pData);
MMP_ERR  IR_Ctrl_GetIntStatus(MMP_UBYTE	*pstatus);
MMP_ERR  IR_Ctrl_IDCheck(IR_DATA *pData, MMP_UBYTE  *pstatus);
MMP_ERR  IR_Ctrl_Initial(void);

void     IR_Ctrl_Register(struct _3RD_PARTY_IR *pdev_obj);
void     IR_Ctrl_Unregister(void);
  
#endif // _MMPF_IR_H_
/// @}
