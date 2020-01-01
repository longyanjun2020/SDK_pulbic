/*! @file isp_i2c_api.h
      @brief This file contains Infinity ISP I2C basic API.
*/

/** @defgroup group1 ISP I2C API
* @{
*/

#ifndef ISP_I2C_API_H
#define ISP_I2C_API_H

#define FAIL        (-1)
#define SUCCESS     0

#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_util.h"

/*! @brief I2C API handle.*/

/*! @brief I2C batch read/write data.*/
typedef struct _I2C_ARRAY{
    unsigned short reg; /**< Register address.*/
    unsigned short data; /**< Data.*/
} I2C_ARRAY;

/*! @brief I2C data direction*/
typedef enum {
    I2C_RW_R, /**< Data direction read.*/
    I2C_RW_W,/**< Data direction write.*/
} I2C_RW;

/*! @brief Use for i2c_array_rw only */
typedef struct _I2C_CPX_ARRAY{
    I2C_RW  rw; /**< Data direction */
    unsigned short reg; /**< Device register address */
    unsigned short data; /**< Data write to device or read from device*/
}__attribute__((packed, aligned(1))) I2C_CPX_ARRAY;

/*! @brief Internal use for I2C API*/
typedef enum {
    I2C_FMT_A8D8, /**< 8 bits Address, 8 bits Data */
    I2C_FMT_A16D8,/**< 16 bits Address 8 bits Data */
    I2C_FMT_A8D16,/**< 8 bits Address 16 bits Data */
    I2C_FMT_A16D16,/**< 16 bits Address 16 bits Data */
    I2C_FMT_END/**< Reserved */
} ISP_I2C_FMT;

/*! @brief ISP_I2C_MODE Internal use for I2C API*/
typedef enum {
    I2C_LEGACY_MODE,    /**< Do not use */
    I2C_NORMAL_MODE     /**< Sensor driver can only use I2C_NORMAL_MODE */
} ISP_I2C_MODE;


/*! @brief app_i2c_cfg I2C setting for sensor and bus.*/
typedef struct _app_i2c_cfg{
    ISP_I2C_MODE        mode;   		//!< I2C_NORMAL_MODE only
    ISP_I2C_FMT         fmt;        	//!< I2C data format
    u32                 speed;          //!< I2C clock in Hz
    u8 					nChannel;		//!< I2C Channel
    u8					nPadNum;		//!< I2C Pad output
    u16                 address;       	//!< Sensor slave address , bit[7~1] are available, bit[0] user don't care
    u16  reserved;
}__attribute__((packed, aligned(1))) app_i2c_cfg;

/** @} */ // end of ISP I2C API

int MstarExternalI2cTx(app_i2c_cfg tCfg, short nReg, short nData);
int MstarExternalI2cRx(app_i2c_cfg tCfg, short nReg, volatile short *pnDdata);
int MstarExternalI2cArrayTx(app_i2c_cfg tCfg, I2C_ARRAY *ptData, int nLen);
int MstarExternalI2cArrayRx( app_i2c_cfg tCfg, I2C_ARRAY *ptData, int nLen);

#define SensorReg_Read(_reg,_data)  (MstarExternalI2cRx(handle->i2c_cfg,_reg,_data))
#define SensorReg_Write(_reg,_data) (MstarExternalI2cTx(handle->i2c_cfg,_reg,_data))
#define SensorRegArrayW(_reg,_len)  (MstarExternalI2cArrayTx(handle->i2c_cfg,(_reg),(_len)))
#define SensorRegArrayR(_reg,_len)  (MstarExternalI2cArrayRx(handle->i2c_cfg,(_reg),(_len)))

#endif
