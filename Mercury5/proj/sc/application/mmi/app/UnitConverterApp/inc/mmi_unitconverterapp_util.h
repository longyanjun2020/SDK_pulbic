
//*****************************************************
//This file is generated from UnitConversionTable.xls.
//Do not modify it directly.
//*****************************************************

#include "mmi_mae_common_def.h"
#include "mae_textlabel.h"

#ifndef __MMI_UNITCONVERTERAPP_UTIL_H__
#define __MMI_UNITCONVERTERAPP_UTIL_H__

extern boolean getRate(double *pRate, u8 conType, u8 rowIndex, u8 colIndex);

#define NUM_CONVERSION_TYPES  12
extern const u8 numItemsForEachConversionType[];

extern const u32 * const UnitTextLabelTable[];

extern const u32 conversionTypeTextLabel[];
extern const u32 currencyTextLabel[];
extern const u32 energyTextLabel[];
extern const u32 speedTextLabel[];
extern const u32 massTextLabel[];
extern const u32 areaTextLabel[];
extern const u32 volumeTextLabel[];
extern const u32 powerTextLabel[];
extern const u32 timeTextLabel[];
extern const u32 pressureTextLabel[];
extern const u32 lengthTextLabel[];
extern const u32 temperatureTextLabel[];

#endif
