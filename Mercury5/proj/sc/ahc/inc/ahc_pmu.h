//==============================================================================
//
//  File        : ahc_pmu.h
//  Description : INCLUDE File for the AHC PMU function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_PMU_H_
#define _AHC_PMU_H_

/*===========================================================================
 * Include files
 *===========================================================================*/
 
#include "ahc_common.h"

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum _AHC_PMU_LDO_ID
{
	AHC_PMU_LDO_ID_1 = 0x0,
	AHC_PMU_LDO_ID_2,
	AHC_PMU_LDO_ID_3,
	AHC_PMU_LDO_ID_4,
	AHC_PMU_LDO_ID_5,
	AHC_PMU_LDO_MAX
} AHC_PMU_LDO_ID;

typedef enum _AHC_PMU_ADC_TYPE
{
	AHC_PMU_ADC_AUX1 = 0,
	AHC_PMU_ADC_AUX2,
	AHC_PMU_ADC_WIPER, // Equal to AUX3
	AHC_PMU_ADC_TP_PRE,
	AHC_PMU_ADC_X_CO,
	AHC_PMU_ADC_Y_CO,
	AHC_PMU_ADC_MAX	
} AHC_PMU_ADC_TYPE;

/*===========================================================================
 * Function Prototype
 *===========================================================================*/

void AHC_PMUCtrl_ADC_Measure_Key(UINT32 *level, UINT8 *source, AHC_PMU_ADC_TYPE type);
void AHC_PMU_PowerOff(void);
void AHC_PMUCtrl_Write_Reg(UINT8 ubReg, UINT8 ubValue);
void AHC_PMUCtrl_Read_Reg(UINT8 ubReg, UINT16* ubValue);
void AHC_PMUCtrl_LDO(AHC_PMU_LDO_ID ldoID, AHC_BOOL bEnable);
void AHC_PMU_PowerOff(void);

#endif