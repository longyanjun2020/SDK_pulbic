/**
 * \file i2c_drv.h
 * \brief This file contains the bus I2C hardware layer headers.
 */

#ifndef __I2C_DRV_H__
#define __I2C_DRV_H__


/*********** TYPE DEFINITIONS ***********/


/*********** CONSTANTS ***********/

/**
 * \brief Clock Speed
 * 
 *  Used in \ref vm_i2cOpen .
 */
typedef enum {
	VM_I2C_HIGHSPEED_MODE =   0x01, ///< 1 MHz
	VM_I2C_FAST_MODE =       0x02, ///< 400 kHz
	VM_I2C_SLOW_MODE  =      0x82 ///< 100 kHz
} vm_I2cClockSpeed_t;

/*********** PROTOTYPES ***********/

void bus_I2c_Init_Standard (u16 Speed);
s32 bus_I2c_SendData_Standard(u8 Addr, s32 NbItems, const u8 *pDataToWrite, bool StopBit);
s32 bus_I2c_Receive_Standard(u8 Addr, u32 NbItemsToWrite, u8 *pDataToWrite, u32 NbItemsToRead, u8 *pDataToRead);

#endif  /* !__BUS_I2C_DRV_H__ */