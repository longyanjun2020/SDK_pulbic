#ifndef _IR_IRC120X_H_
#define _IR_IRC120X_H_

#include "Customer_config.h"
#include "ir_ctrl.h"

#ifndef IR_CONVERTER_USE_SOFT_I2CM
#define IR_CONVERTER_USE_SOFT_I2CM		(1)
#endif

#ifndef IR_SCL
#define IR_SCL			MMP_GPIO16
#endif

#ifndef IR_SDA
#define IR_SDA			MMP_GPIO17
#endif

#ifndef IR_INTR 
#define IR_INTR			MMP_GPIO19
#endif

#if (IR_CONVERTER_USE_SOFT_I2CM == 0x1)
#define IR_SLAVE_ADDR		0x44	//SW I2CM
#else
#define IR_SLAVE_ADDR		0x22    //HW I2CM
#endif

typedef enum _IR_CONVERTER_COMMAND {
	IR_CONVERTER_CLEAR_POWERON = 0x10,
	IR_CONVERTER_COMMAND_MAX
}IR_CONVERTER_COMMAND;

typedef enum
{
	IR_CLR = 0xC0,
	IR_DATA0,
	IR_DATA1,
	IR_DATA2,
	IR_DATA3
} IR_REG;

#endif
