
#ifndef _REG_CUSTOMER_PMU_H_
#define _REG_CUSTOMER_PMU_H_

#include "config_fw.h"

#if (CUSTOMER_PMU_EN)

//#include "mmp_register.h"

typedef enum
{

	CUSTOMER_PMU_OTHER
} CUSTOMER_PMU_REG;

typedef enum _CUMTOMER_PMU_ADC_TYPE
{
	CUSTOMER_PMU_ADC_1 = 0,
	CUSTOMER_PMU_ADC_2,

	CUSTOMER_PMU_ADC_MAX
} CUSTOMER_PMU_ADC_TYPE;

#endif // #if (CUSTOMER_PMU_EN)

#endif // #ifndef _REG_CUSTOMER_PMU_H_
