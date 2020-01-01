//------------------------------------------------------------------------------
//
//  File        : mmp_i2c_inc.h
//  Description : Header file of I2C common information
//  Author      : Alterman
//  Revision    : 1.0
//
//------------------------------------------------------------------------------
#ifndef _MMP_I2C_INC_H_
#define _MMP_I2C_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_typedef.h"
#include "mmp_gpio_inc.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_I2CM_ID {
    /* [HW I2CM engines]
     * NOTE: The order of hardware engines is a little tricky for MercuryV2 to
     * meet the I2CM register map.
     */
    MMP_I2CM0 = 0,
    MMP_I2CM1 = 2,
    MMP_I2CM2 = 1,
    MMP_I2CM3 = 3,

    /* [SW I2CM engines]
     * Use the user specified GPIO pins or PSNR_SCK/PSNR_SDA to implement the
     * I2C protocol.
     */
    MMP_I2CM_GPIO = 4,
    MMP_I2CM_SNR = 5
} MMP_I2CM_ID;

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

/* The number of hardware master I2C engines */
#define I2CM_HW_CNT         (4) // MMP_I2CM0 ~ MMP_I2CM3

/* The number of software master I2C engines */
#define I2CM_SW_CNT         (2) // MMP_I2CM_GPIO & MMP_I2CM_SNR

/* The total number of master I2C engines available */
#define I2CM_CNT            (I2CM_SW_CNT + I2CM_HW_CNT)

//==============================================================================
//
//                              MACRO FUNCTIONS
//
//==============================================================================

/* The index of software master I2C engines */
#define SW_I2CM_IDX(id)     (id - MMP_I2CM_GPIO)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_I2CM_ATTR {
   MMP_I2CM_ID  i2cmID;         // I2CM engine ID
   MMP_UBYTE    ubSlaveAddr;    // slave device address.
   MMP_UBYTE    ubRegLen;       // register bit length (8/16 bit)
   MMP_UBYTE    ubDataLen;      // data bit length (8/16)
   MMP_UBYTE    ubDelayTime;    // delay time after each ACK/NACK (for SW I2C)
   MMP_BOOL     bDelayWaitEn;   // delay between each I2CM accessing set (for HW I2C)
   MMP_BOOL     bInputFilterEn; // filter input noise (for HW I2C)
   MMP_BOOL     b10BitModeEn;   // 10 bit slave address enable (for HW I2C)
   MMP_BOOL	    bClkStretchEn;  // stretch clock (for HW I2C)
   MMP_UBYTE    ubSlaveAddr1;   // bit [9:8] for 10 bit slave device address.
   MMP_UBYTE    ubDelayCycle;   // the delay cycle when bDelayWaitEn is TRUE
   MMP_UBYTE    ubPadNum;       // Pad selection (for HW I2C)
   MMP_ULONG    ulI2cmSpeed;    // I2C speed control in unit of HZ.
   MMP_BOOL	    bOsProtectEn;   // Use OS semaphore to support driver reentry
   MMP_GPIO_PIN sw_clk_pin;     // User specified clock pin (for MMP_I2CM_GPIO)
   MMP_GPIO_PIN sw_data_pin;    // User specified data pin (for MMP_I2CM_GPIO)
   MMP_BOOL     bRfclModeEn;    // Read from current location mode enable:
                                // read data without send register address.
   MMP_BOOL     bWfclModeEn;    // Write from current location mode enable:
                                // Write data without send register address.
   MMP_BOOL		bRepeatModeEn;	// Read with repeat start mode.
   MMP_UBYTE    ubVifPioMdlId;  // VIF module Id for MMP_I2CM_SNR
} MMP_I2CM_ATTR;

#endif // _MMP_I2C_INC_H_

