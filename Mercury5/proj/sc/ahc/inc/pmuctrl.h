//==============================================================================
//
//  File        : pmuctrl.h
//  Description : INCLUDE File for the Motor flow control function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _PMU_CTRL_H_
#define _PMU_CTRL_H_

#include "mmp_lib.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _PMU_ADC_TYPE
{
	PMU_ADC_AUX1 = 0,
	PMU_ADC_AUX2,
	PMU_ADC_WIPER, // Equal to AUX3
	PMU_ADC_TP_PRE,
	PMU_ADC_X_CO,
	PMU_ADC_Y_CO,
	PMU_ADC_MAX
} PMU_ADC_TYPE;

typedef enum _PMU_LDO_ID
{
	PMU_LDO_ID_1 = 0x0,
	PMU_LDO_ID_2,
	PMU_LDO_ID_3,
	PMU_LDO_ID_4,
	PMU_LDO_ID_5,
	PMU_LDO_MAX
} PMU_LDO_ID;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

void 		PMUCtrl_ADC_Measure_Key( MMP_ULONG *level, MMP_UBYTE *source, PMU_ADC_TYPE type);
void 		PMUCtrl_Power_Gpio_En(MMP_BOOL bGPIOEnable);
void 		PMUCtrl_Power_Off(void);
void 		PMUCtrl_Write_Reg(MMP_UBYTE ubReg, MMP_UBYTE ubValue);
void 		PMUCtrl_Read_Reg(MMP_UBYTE ubReg, MMP_USHORT* ubValue);
void 		PMUCtrl_Enable_LDO(PMU_LDO_ID ldoID, MMP_BOOL	bEnable);
MMP_ERR 	PMUCtrl_Initialize(void);
void        PMUCtrl_Power_Off_For_Exception(void);

#endif // _PMU_CTRL_H_
