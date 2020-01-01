////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    drv_io_chip_pub_types.h
* @version
* @brief   Header for High level GPIO interface.
*
*/

#ifndef __DRV_IO_CHIP_PUB_TYPES_H__
#define __DRV_IO_CHIP_PUB_TYPES_H__

#ifndef __SDK_SIMULATION__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_io_chip_pub_forward.h"
#include "drv_vm_io_forward.h"

#include "drv_vm_io_types.h"

#include "hal_io_chip_pub.h"
#include "mdl_pm.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define IO_CHIP_TRACE   (_DEV|LEVEL_1)
#define IO_CHIP_WARNING (_DEV|LEVEL_1)
#define IO_CHIP_ERROR   (_DEV|LEVEL_1)
#define IO_CHIP_FATAL   (_DEV|LEVEL_1|FATAL)

/* Athena driver */
#define IO_CHIP_ATHENA_I2C_SCL      (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ATHENA_I2C_SCL])
#define IO_CHIP_ATHENA_I2C_SDA      (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ATHENA_I2C_SDA])

/* ATV driver */
#if defined(__ATV_DRV__)
#define IO_CHIP_ATV_I2C_SCL         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ATV_I2C_SCL])
#define IO_CHIP_ATV_I2C_SDA         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ATV_I2C_SDA])
#define IO_CHIP_ATV_RESET           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ATV_RESET])
#define IO_CHIP_ATV_ON              (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ATV_ON])
#define IO_CHIP_ATV_LDOEN           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ATV_LDOEN])
#define IO_CHIP_ATV_LDOEN_2         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ATV_LDOEN_2])
#endif

#define IO_CHIP_ATV_NMI5625_EN      (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ATV_NMI5625_EN])

/* Proximity driver*/
#if defined(__PROXIMITY_SENSOR_DRV__)
#define IO_CHIP_PROXIMITY_SENSOR_LDOEN  (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_PROXIMITY_SENSOR_LDOEN])
#define IO_CHIP_PROXIMITY_SENSOR_I2C_SCL     (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_PROXIMITY_SENSOR_I2C_SCL])
#define IO_CHIP_PROXIMITY_SENSOR_I2C_SDA     (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_PROXIMITY_SENSOR_I2C_SDA])
#define IO_CHIP_PROXIMITY_SENSOR_INT         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_PROXIMITY_SENSOR_INT])
#endif

/* GPD driver for backlight control GPIO */
#define IO_CHIP_BACKLIGHT_EN        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BACKLIGHT_EN])
#define IO_CHIP_BACKLIGHT_PWM       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BACKLIGHT_PWM])

/* Battery */
#ifdef __DUAL_BATT_DRV__
#define IO_CHIP_BATT_BAT_SEL        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BATT_SELECT])
#define IO_CHIP_BATT_SLV_INT        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BATT_SLV_INT])
#define IO_CHIP_BATT_BAT_EN         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BATT_EN])
#define IO_CHIP_BATT_CHR_EN         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BATT_EN_CHR])
#ifdef __DUAL_BATTERY_NO_ID__
#define IO_CHIP_BATT_NO_ID           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BATT_NO_ID])
#else
#define IO_CHIP_BATT_M_ID           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BATT_M_ID])
#endif
#endif
/* Bluetooth driver */
#if defined(__BLUETOOTH_DRV__) || defined(__GPS_USE_BT_UART__)
#define IO_CHIP_BT_32K              (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_32K])
#define IO_CHIP_BT_EN               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_EN])
#define IO_CHIP_BT_RESET            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_RESET])
#define IO_CHIP_BT_HOST_WAKE_EXTINT (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_HOST_WAKE_EXTINT])
#endif

#ifdef __GPS_DUALSTAR_DRV__
#define IO_CHIP_GPS_DUALSTAR_EN      (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GPS_DUALSTAR_EN])
#define IO_CHIP_GPS_DUALSTAR_RST     (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GPS_DUALSTAR_RST])
#define IO_CHIP_GPS_DUALSTAR_32K     (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GPS_DUALSTAR_32K])
#endif //  __GPS_DUALSTAR_DRV__

/* External audio OP amplifier */
#define IO_CHIP_EXT_OPAMP_EN        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_OPAMP_EN])
#define IO_CHIP_EXT_CODEC_26M       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_26M])
#define IO_CHIP_EXT_CODEC_SDA       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_SDA])
#define IO_CHIP_EXT_CODEC_SCLK      (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_SCLK])
#define IO_CHIP_EXT_CODEC_24M       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_24M])
#define IO_CHIP_EXT_CODEC_PDW       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_PDW])
#define IO_CHIP_EXT_CODEC_RST       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_RST])
#define IO_CHIP_EXT_CODEC_BP        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_BP])
#define IO_CHIP_EXT_CODEC_SDO       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_PCM_SDO])
#define IO_CHIP_EXT_CODEC_SDI       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_PCM_SDI])
#define IO_CHIP_EXT_CODEC_BCK       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_PCM_BCK])
#define IO_CHIP_EXT_CODEC_WCK       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_CODEC_PCM_WCK])


/* Flash light driver */
#if defined(__FLASHLIGHT_DRV__)
#define IO_CHIP_FLASHLIGHT_EN       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_FLASHLIGHT_EN])
#define IO_CHIP_FLASHLIGHT_EN2      (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_FLASHLIGHT_EN2])
#define IO_CHIP_FLASHLIGHT_EN3      (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_FLASHLIGHT_EN3])
#endif

/* FM radio driver */
#define IO_CHIP_FMR_I2C_SCL         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_FMR_I2C_SCL])
#define IO_CHIP_FMR_I2C_SDA         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_FMR_I2C_SDA])

/* GPS driver */
#if defined(__GPS_DRV__)
#define IO_CHIP_GPS_32K             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GPS_32K])
#define IO_CHIP_GPS_EN              (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GPS_EN])
#define IO_CHIP_GPS_RESET           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GPS_RESET])
#endif

/* G-sensor driver */
#if defined(__G_SENSOR_DRV__)
#define IO_CHIP_GSENSOR_DETECT_1    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GSENSOR_DETECT_1])
#define IO_CHIP_GSENSOR_DETECT_2    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GSENSOR_DETECT_2])
#define IO_CHIP_GSENSOR_EN          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GSENSOR_EN])
#define IO_CHIP_GSENSOR_I2C_SCL     (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GSENSOR_I2C_SCL])
#define IO_CHIP_GSENSOR_I2C_SDA     (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_GSENSOR_I2C_SDA])
#endif

/* */
#if defined(__GPIO_HEADSET_DETECTOR_DRV__)
#define IO_CHIP_EXT_HEADSET_DETECT  (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_EXT_HEADSET_DETECT])
#endif

/* Hall switch driver */
#if defined(__HALL_SWITCH_DRV__)
#define IO_CHIP_HALLSWITCH_EXTINT   (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_HALLSWITCH_EXTINT])
#endif

/* LCD driver */
#define IO_CHIP_LCD_RESET           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_RESET])

/* OFN driver */
#if defined(__OFN_DRV__)
#define IO_CHIP_OFN_EXTINT          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_OFN_EXTINT])
#define IO_CHIP_OFN_RESET           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_OFN_RESET])
#define IO_CHIP_OFN_SHTDWN          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_OFN_SHTDWN])
// For mb303a_v2 product : take gpio to simulate I2C & two power (1.8v, 2.8v) supply.
#ifdef __OFN_POWER_BY_LDO__
#define IO_CHIP_OFN_EN            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_OFN_EN])
#define IO_CHIP_OFN_DVDD            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_OFN_DVDD_1V8])
#endif
#if defined(__OFN_DRV_GPIO_SIMU_I2C__)
#define IO_CHIP_OFN_SDA             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_OFN_SDA])
#define IO_CHIP_OFN_SCL             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_OFN_SCL])
#endif
#endif

/* BALL driver */
#if defined(__BALL_DRV__)
#define IO_CHIP_BALL_UP             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BALL_UP])
#define IO_CHIP_BALL_DOWN           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BALL_DOWN])
#define IO_CHIP_BALL_LEFT           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BALL_LEFT])
#define IO_CHIP_BALL_RIGHT          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BALL_RIGHT])
#endif

/* SD card via SDIO interface */
#define IO_CHIP_SD_EN              (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD_EN])
#define IO_CHIP_SD2_EN              (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD2_EN])
#define IO_CHIP_SD2_INT             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD2_INT])

/* Sensor driver for main sensor GPIOs */
#define IO_CHIP_SENSOR_EN           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_EN])
#define IO_CHIP_SENSOR_RESET        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_RESET])

#if defined(__FILLLIGHT_DRV__)
#define IO_CHIP_FILL_LIGHT          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_FILL_LIGHT])
#endif

/* SIM driver */
#define IO_CHIP_SIM_PRES            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SIM_PRES])
#if defined(__MSTAR_DUAL_SIM_SIM_MUX__)
#define IO_CHIP_SIM_RST             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SIM_RST])
#define IO_CHIP_SIM_RST1            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SIM_RST1])
#define IO_CHIP_SIM_RST2            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SIM_RST2])
#define IO_CHIP_SIM_SEL             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SIM_SEL])
#endif

/* Sensor driver for sub-sensor GPIOs */
#define IO_CHIP_SUB_SENSOR_EN       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SUB_SENSOR_EN])
#define IO_CHIP_SUB_SENSOR_RESET    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SUB_SENSOR_RESET])

/* Touch screen driver */
#define IO_CHIP_TSCR_EXTINT         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TSCR_EXTINT])
#define IO_CHIP_TSCR_I2C_SCL        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TSCR_I2C_SCL])
#define IO_CHIP_TSCR_I2C_SDA        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TSCR_I2C_SDA])
#define IO_CHIP_TSCR_RESET          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TSCR_RESET])

/* UART driver */
#define IO_CHIP_UART1_DCD           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART1_DCD])
#define IO_CHIP_UART1_RI            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART1_RI])

#if defined(__SPK_RECEIVER_MIX_DRV__)
/* Voice driver */
#define IO_CHIP_VOC_REV_SWITCH      (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_VOC_REV_SWITCH])
#endif

/* WIFI driver */
#if defined(__WLAN_DRV__)
#define IO_CHIP_WIFI_32K            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_WIFI_32K])
#define IO_CHIP_WIFI_EXTINT         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_WIFI_EXTINT])
#endif

/* customer GPIOs, should never be used in source file directly, please define
   the mapping in cust_gpio.h then use the mapped name instead */
#define IO_CHIP_CUSTOM_1            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_1])
#define IO_CHIP_CUSTOM_2            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_2])
#define IO_CHIP_CUSTOM_3            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_3])
#define IO_CHIP_CUSTOM_4            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_4])
#define IO_CHIP_CUSTOM_5            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_5])
#define IO_CHIP_CUSTOM_6            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_6])
#define IO_CHIP_CUSTOM_7            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_7])
#define IO_CHIP_CUSTOM_8            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_8])
#define IO_CHIP_CUSTOM_9            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_9])
#define IO_CHIP_CUSTOM_10           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_10])
#define IO_CHIP_CUSTOM_11           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_11])
#define IO_CHIP_CUSTOM_12           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_12])
#define IO_CHIP_CUSTOM_13           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_13])
#define IO_CHIP_CUSTOM_14           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_14])
#define IO_CHIP_CUSTOM_15           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_15])
#define IO_CHIP_CUSTOM_16           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CUSTOM_16])

/* BT PCM */
#define IO_CHIP_BT_PCM_SDO          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_PCM_SDO])
#define IO_CHIP_BT_PCM_SDI          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_PCM_SDI])
#define IO_CHIP_BT_PCM_BCK          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_PCM_BCK])
#define IO_CHIP_BT_PCM_WCK          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_PCM_WCK])

/* MStar BT */
#define IO_CHIP_BT_CHIP_EN          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_CHIP_EN])
#define IO_CHIP_BT_CLK_24M          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_CLK_24M])
#define IO_CHIP_BT_RX_TX            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_RX_TX])
#define IO_CHIP_BT_SPI_SENB         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_SPI_SENB])
#define IO_CHIP_BT_DATA_0           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_DATA_0])
#define IO_CHIP_BT_SPI_SCLK         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_SPI_SCLK])
#define IO_CHIP_BT_DATA_1           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_DATA_1])
#define IO_CHIP_BT_SPI_SDATA        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BT_SPI_SDATA])

/* MASTER SPI */
#define IO_CHIP_MSPI_CLK0           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MSPI_CLK0])
#define IO_CHIP_MSPI_CS0_N          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MSPI_CS0_N])
#define IO_CHIP_MSPI_DO0            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MSPI_DO0])
#define IO_CHIP_MSPI_DI0            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MSPI_DI0])

#define IO_CHIP_MSPI_CLK1           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MSPI_CLK1])
#define IO_CHIP_MSPI_CS1_N          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MSPI_CS1_N])
#define IO_CHIP_MSPI_DO1            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MSPI_DO1])
#define IO_CHIP_MSPI_DI1            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MSPI_DI1])

/* SD card */
#define IO_CHIP_SD1_CDZ             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD1_CDZ])
#define IO_CHIP_SD2_CDZ             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD2_CDZ])

/* DBB SPI */
#define IO_CHIP_DBB_SPI_CLK0        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_DBB_SPI_CLK0])
#define IO_CHIP_DBB_SPI_CS0_N       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_DBB_SPI_CS0_N])
#define IO_CHIP_DBB_SPI_DO0         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_DBB_SPI_DO0])
#define IO_CHIP_DBB_SPI_DI0         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_DBB_SPI_DI0])

#define IO_CHIP_DBB_SPI_CLK1        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_DBB_SPI_CLK1])
#define IO_CHIP_DBB_SPI_CS1_N       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_DBB_SPI_CS1_N])
#define IO_CHIP_DBB_SPI_DO1         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_DBB_SPI_DO1])
#define IO_CHIP_DBB_SPI_DI1         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_DBB_SPI_DI1])

#define IO_CHIP_DBB_SPI_CS2_N       (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_DBB_SPI_CS2_N])  /*for 4-card 2-standby*/

/* I2C controller */
#define IO_CHIP_I2C_SCK             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_I2C_SCK])
#define IO_CHIP_I2C_SDA             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_I2C_SDA])

/* MPIF controller */
#define IO_CHIP_MPIF_CS             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MPIF_CS])
#define IO_CHIP_MPIF_CLK            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MPIF_CLK])
#define IO_CHIP_MPIF_BUSY           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MPIF_BUSY])
#define IO_CHIP_MPIF_D0             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MPIF_D0])
#define IO_CHIP_MPIF_D1             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MPIF_D1])
#define IO_CHIP_MPIF_D2             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MPIF_D2])
#define IO_CHIP_MPIF_D3             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_MPIF_D3])

/* Keypad */
#define IO_CHIP_COL_5               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_COL_5])
#define IO_CHIP_COL_6               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_COL_6])
#define IO_CHIP_COL_7               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_COL_7])
#define IO_CHIP_ROW_5               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ROW_5])
#define IO_CHIP_ROW_6               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ROW_6])
#define IO_CHIP_ROW_7               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_ROW_7])

/* LCD */
#define IO_CHIP_LCD_CS0_N           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_CS0_N])
#define IO_CHIP_LCD_CS1_N           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_CS1_N])
#define IO_CHIP_LCD_CMD             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_CMD])
#define IO_CHIP_LCD_WR              (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_WR])
#define IO_CHIP_LCD_RD              (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_RD])
#define IO_CHIP_LCD_RSTZ            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_RSTZ])
#define IO_CHIP_LCD_FMARK           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_FMARK])
#define IO_CHIP_LCD_D_0             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_0])
#define IO_CHIP_LCD_D_1             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_1])
#define IO_CHIP_LCD_D_2             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_2])
#define IO_CHIP_LCD_D_3             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_3])
#define IO_CHIP_LCD_D_4             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_4])
#define IO_CHIP_LCD_D_5             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_5])
#define IO_CHIP_LCD_D_6             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_6])
#define IO_CHIP_LCD_D_7             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_7])
#define IO_CHIP_LCD_D_8             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_8])
#define IO_CHIP_LCD_D_9             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_9])
#define IO_CHIP_LCD_D_10            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_10])
#define IO_CHIP_LCD_D_11            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_11])
#define IO_CHIP_LCD_D_12            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_12])
#define IO_CHIP_LCD_D_13            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_13])
#define IO_CHIP_LCD_D_14            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_14])
#define IO_CHIP_LCD_D_15            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_15])
#define IO_CHIP_LCD_D_16            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_16])
#define IO_CHIP_LCD_D_17            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_LCD_D_17])

/* RF SPI */
#define IO_CHIP_RF_SPI_CLK          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RF_SPI_CLK])
#define IO_CHIP_RF_SPI_EN           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RF_SPI_EN])
#define IO_CHIP_RF_SPI_IN           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RF_SPI_IN])
#define IO_CHIP_RF_SPI_OUT          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RF_SPI_OUT])

/* SENSOR */
#define IO_CHIP_SENSOR_VSYNC        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_VSYNC])
#define IO_CHIP_SENSOR_HSYNC        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_HSYNC])
#define IO_CHIP_SENSOR_EN           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_EN])
#define IO_CHIP_SENSOR_RESET        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_RESET])
#define IO_CHIP_SENSOR_PCLK         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_PCLK])
#define IO_CHIP_SENSOR_MCLK         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_MCLK])
#define IO_CHIP_SENSOR_D_0          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_D_0])
#define IO_CHIP_SENSOR_D_1          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_D_1])
#define IO_CHIP_SENSOR_D_2          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_D_2])
#define IO_CHIP_SENSOR_D_3          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_D_3])
#define IO_CHIP_SENSOR_D_4          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_D_4])
#define IO_CHIP_SENSOR_D_5          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_D_5])
#define IO_CHIP_SENSOR_D_6          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_D_6])
#define IO_CHIP_SENSOR_D_7          (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SENSOR_D_7])

/* SIM 1 */
#define IO_CHIP_USIM1PRES           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_USIM1PRES])
#define IO_CHIP_USIM1DATA           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_USIM1DATA])
#define IO_CHIP_USIM1CLK            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_USIM1CLK])
#define IO_CHIP_USIM1RST            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_USIM1RST])

/* SIM 2 */
#define IO_CHIP_USIM2PRES           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_USIM2PRES])
#define IO_CHIP_USIM2DATA           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_USIM2DATA])
#define IO_CHIP_USIM2CLK            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_USIM2CLK])
#define IO_CHIP_USIM2RST            (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_USIM2RST])

/* TBUO */
#define IO_CHIP_TBUO0               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO0])
#define IO_CHIP_TBUO1               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO1])
#define IO_CHIP_TBUO2               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO2])
#define IO_CHIP_TBUO3               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO3])
#define IO_CHIP_TBUO4               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO4])
#define IO_CHIP_TBUO5               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO5])
#define IO_CHIP_TBUO6               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO6])
#define IO_CHIP_TBUO7               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO7])
#define IO_CHIP_TBUO8               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO8])
#define IO_CHIP_TBUO9               (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_TBUO9])

/* UART 1 */
#define IO_CHIP_UART1_TXD           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART1_TXD])
#define IO_CHIP_UART1_RXD           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART1_RXD])
#define IO_CHIP_UART1_CTS           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART1_CTS])
#define IO_CHIP_UART1_RTS           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART1_RTS])
#define IO_CHIP_UART1_DTR           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART1_DTR])
#define IO_CHIP_UART1_DSR           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART1_DSR])

/* UART 2 */
#define IO_CHIP_UART2_TXD           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART2_TXD])
#define IO_CHIP_UART2_RXD           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART2_RXD])
#define IO_CHIP_UART2_CTS           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART2_CTS])
#define IO_CHIP_UART2_RTS           (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_UART2_RTS])

/* WIFI */
#define IO_CHIP_WIFI_EN             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_WIFI_EN])
#define IO_CHIP_WIFI_WAKEUP         (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_WIFI_WAKEUP])
#define IO_CHIP_WIFI_RX             (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_WIFI_RX])
#define IO_CHIP_WIFI_GPIO4_OUT      (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_WIFI_GPIO4_OUT])

/* SHMCL test */
#define IO_CHIP_SHMCL_DL_MBX_SEND 	(g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SHMCL_DL_MBX_SEND])
#define IO_CHIP_SHMCL_UL_MBX_INT    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SHMCL_UL_MBX_INT])
#define IO_CHIP_SHMCL_UL_MBX_SEND   (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SHMCL_UL_MBX_SEND])
#define IO_CHIP_SHMCL_DL_MBX_INT    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SHMCL_DL_MBX_INT])

/* Macros for pad init table */
#define IO_CHIP_PULL_DEFAULT  	IO_CHIP_PULL_INVALID
#define IO_CHIP_DRIVE_DEFAULT 	IO_CHIP_DRIVE_INVALID
#define IO_CHIP_DRIVE_SET 		IO_CHIP_DRIVE_1

#define IO_CHIP_OUT_LOW       	VM_IO_LOW
#define IO_CHIP_OUT_HIGH      	VM_IO_HIGH
#define IO_CHIP_OUT_DEFAULT   	VM_IO_SKIP

#ifdef __RFID__
#define IO_CHIP_RFID_I2CSIM_SCL_IN		(g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_I2CSIM_SCL_IN])
#define IO_CHIP_RFID_I2CSIM_SCL_OUT		(g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_I2CSIM_SCL_OUT])
#define IO_CHIP_RFID_I2CSIM_SDA_IN		(g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_I2CSIM_SDA_IN])
#define IO_CHIP_RFID_I2CSIM_SDA_OUT		(g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_I2CSIM_SDA_OUT])
#ifdef __USE_MSR3110__
#define IO_CHIP_RFID_SIM_SWITCH_IN		(g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_SIM_SWITCH_IN])
#define IO_CHIP_RFID_SIM_SWITCH_OUT	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_SIM_SWITCH_OUT])
#define IO_CHIP_RFID_ROM_BOOT_OUT	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_ROM_BOOT_OUT])
#define IO_CHIP_RFID_ROM_BOOT_IN	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_ROM_BOOT_IN])
#endif //__USE_MSR3110__
#define IO_CHIP_RFID_VEN_OUT	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_VEN_OUT])
#define IO_CHIP_RFID_RSTPD_OUT	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_RSTPD_OUT])
#define IO_CHIP_RFID_SPISIM_SDO_OUT	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_SPISIM_SDO_OUT])
#define IO_CHIP_RFID_SPISIM_SCK_OUT	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_SPISIM_SCK_OUT])
#define IO_CHIP_RFID_SPISIM_CSZ_OUT	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_SPISIM_CSZ_OUT])
#define IO_CHIP_RFID_SPISIM_CSZ_IN	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_SPISIM_CSZ_IN])
#define IO_CHIP_RFID_SPISIM_SDI_IN	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_RFID_SPISIM_SDI_IN])
#endif	//__RFID__

#ifdef __BARCODE__
#define IO_CHIP_BARCODE_ENABLE_OUT	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BARCODE_ENABLE_OUT])
#define IO_CHIP_BARCODE_TRIGGER_OUT	    (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_BARCODE_TRIGGER_OUT])
#endif	//__BARCODE__

/* CMMB */

#define IO_CHIP_CMMB_I2S_BCK	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CMMB_I2S_BCK])
#define IO_CHIP_CMMB_I2S_WS 	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CMMB_I2S_WS])	
#define IO_CHIP_CMMB_I2S_DIO	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CMMB_I2S_DIO])  	
#define IO_CHIP_CMMB_RESET		        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CMMB_RESET])
#define IO_CHIP_CMMB_LDO_EN 	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CMMB_LDO_EN])
#define IO_CHIP_CMMB_PSI		        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CMMB_PSI])
#define IO_CHIP_CMMB_MODE		        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CMMB_MODE])
#define IO_CHIP_CMMB_MPIF_INT	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_CMMB_MPIF_INT])

/* SD */
#define IO_CHIP_SD1_CLK	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD1_CLK])
#define IO_CHIP_SD1_CMD	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD1_CMD])
#define IO_CHIP_SD1_D0	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD1_D0])
#define IO_CHIP_SD1_D1	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD1_D1])
#define IO_CHIP_SD1_D2	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD1_D2])
#define IO_CHIP_SD1_D3	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD1_D3])

/* SD2 */
#define IO_CHIP_SD2_CLK	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD2_CLK])
#define IO_CHIP_SD2_CMD	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD2_CMD])
#define IO_CHIP_SD2_D0	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD2_D0])
#define IO_CHIP_SD2_D1	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD2_D1])
#define IO_CHIP_SD2_D2	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD2_D2])
#define IO_CHIP_SD2_D3	        (g_aeIoChipGpioMappingTbl[IO_CHIP_INDEX_SD2_D3])



/*=============================================================*/
// Data type definition
/*=============================================================*/
opaque_enum(IoChipSignalIndex_e_)
{
    /* customer-defined GPIO */
    IO_CHIP_INDEX_ATHENA_I2C_SCL,
    IO_CHIP_INDEX_ATHENA_I2C_SDA,
    IO_CHIP_INDEX_ATV_I2C_SCL,
    IO_CHIP_INDEX_ATV_ON,
    IO_CHIP_INDEX_ATV_LDOEN,
    IO_CHIP_INDEX_ATV_LDOEN_2,
    IO_CHIP_INDEX_ATV_NMI5625_EN,
    IO_CHIP_INDEX_PROXIMITY_SENSOR_LDOEN,
    IO_CHIP_INDEX_PROXIMITY_SENSOR_I2C_SCL,
    IO_CHIP_INDEX_PROXIMITY_SENSOR_I2C_SDA,
    IO_CHIP_INDEX_PROXIMITY_SENSOR_INT,
    IO_CHIP_INDEX_ATV_I2C_SDA,
    IO_CHIP_INDEX_ATV_RESET,
    IO_CHIP_INDEX_BACKLIGHT_EN,
    IO_CHIP_INDEX_BACKLIGHT_PWM,
    /* default dual battery */
    IO_CHIP_INDEX_BATT_MST_INT,
    IO_CHIP_INDEX_BATT_SLV_INT,
    IO_CHIP_INDEX_BATT_MST_SWT,
    IO_CHIP_INDEX_BATT_SLV_SWT,
    /* ASW IC dual battery*/
    IO_CHIP_INDEX_BATT_SELECT,
    IO_CHIP_INDEX_BATT_EN,
    IO_CHIP_INDEX_BATT_EN_CHR,
    IO_CHIP_INDEX_BATT_M_ID,
    IO_CHIP_INDEX_BATT_NO_ID,
    IO_CHIP_INDEX_BT_32K,
    IO_CHIP_INDEX_BT_EN,
    IO_CHIP_INDEX_BT_HOST_WAKE_EXTINT,
    IO_CHIP_INDEX_BT_RESET,

    IO_CHIP_INDEX_GPS_DUALSTAR_EN,
    IO_CHIP_INDEX_GPS_DUALSTAR_RST,
    IO_CHIP_INDEX_GPS_DUALSTAR_32K,

    IO_CHIP_INDEX_EXT_OPAMP_EN,
    IO_CHIP_INDEX_EXT_HEADSET_DETECT,
    IO_CHIP_INDEX_EXT_CODEC_26M,
    IO_CHIP_INDEX_EXT_CODEC_SDA,
    IO_CHIP_INDEX_EXT_CODEC_SCLK,
    IO_CHIP_INDEX_EXT_CODEC_RST,
    IO_CHIP_INDEX_EXT_CODEC_PDW,
    IO_CHIP_INDEX_EXT_CODEC_BP,
    IO_CHIP_INDEX_EXT_CODEC_I2S_BCK,
    IO_CHIP_INDEX_EXT_CODEC_I2S_WCK,
    IO_CHIP_INDEX_EXT_CODEC_I2S_SDI,
    IO_CHIP_INDEX_EXT_CODEC_I2S_SDO,
    IO_CHIP_INDEX_EXT_CODEC_24M,
    IO_CHIP_INDEX_EXT_CODEC_PCM_BCK,
    IO_CHIP_INDEX_EXT_CODEC_PCM_WCK,
    IO_CHIP_INDEX_EXT_CODEC_PCM_SDI,
    IO_CHIP_INDEX_EXT_CODEC_PCM_SDO,
    IO_CHIP_INDEX_FLASHLIGHT_EN,
    IO_CHIP_INDEX_FLASHLIGHT_EN2,
    IO_CHIP_INDEX_FLASHLIGHT_EN3,
    IO_CHIP_INDEX_FMR_I2C_SCL,
    IO_CHIP_INDEX_FMR_I2C_SDA,
    IO_CHIP_INDEX_GPS_32K,
    IO_CHIP_INDEX_GPS_EN,
    IO_CHIP_INDEX_GPS_RESET,
    IO_CHIP_INDEX_GSENSOR_DETECT_1,
    IO_CHIP_INDEX_GSENSOR_DETECT_2,
    IO_CHIP_INDEX_GSENSOR_EN,
    IO_CHIP_INDEX_GSENSOR_I2C_SCL,
    IO_CHIP_INDEX_GSENSOR_I2C_SDA,
    IO_CHIP_INDEX_HALLSWITCH_EXTINT,
    IO_CHIP_INDEX_LCD_RESET,
    IO_CHIP_INDEX_OFN_EN,
    IO_CHIP_INDEX_OFN_DVDD_1V8,
    IO_CHIP_INDEX_OFN_EXTINT,
    IO_CHIP_INDEX_OFN_RESET,
    IO_CHIP_INDEX_OFN_SDA,
    IO_CHIP_INDEX_OFN_SCL,
    IO_CHIP_INDEX_OFN_SHTDWN,
    IO_CHIP_INDEX_SD_EN,
    IO_CHIP_INDEX_SD2_EN,
    IO_CHIP_INDEX_SD2_INT,
    IO_CHIP_INDEX_FILL_LIGHT,
    IO_CHIP_INDEX_SIM_PRES,
    IO_CHIP_INDEX_SIM_RST,
    IO_CHIP_INDEX_SIM_RST1,
    IO_CHIP_INDEX_SIM_RST2,
    IO_CHIP_INDEX_SIM_SEL,
    IO_CHIP_INDEX_SUB_SENSOR_EN,
    IO_CHIP_INDEX_SUB_SENSOR_RESET,
    IO_CHIP_INDEX_TSCR_EXTINT,
    IO_CHIP_INDEX_TSCR_I2C_SCL,
    IO_CHIP_INDEX_TSCR_I2C_SDA,
    IO_CHIP_INDEX_TSCR_RESET,
    IO_CHIP_INDEX_UART1_DCD,
    IO_CHIP_INDEX_UART1_RI,
    IO_CHIP_INDEX_VOC_REV_SWITCH,
    IO_CHIP_INDEX_WIFI_32K,
    IO_CHIP_INDEX_WIFI_EXTINT,
    IO_CHIP_INDEX_CUSTOM_1,
    IO_CHIP_INDEX_CUSTOM_2,
    IO_CHIP_INDEX_CUSTOM_3,
    IO_CHIP_INDEX_CUSTOM_4,
    IO_CHIP_INDEX_CUSTOM_5,
    IO_CHIP_INDEX_CUSTOM_6,
    IO_CHIP_INDEX_CUSTOM_7,
    IO_CHIP_INDEX_CUSTOM_8,
    IO_CHIP_INDEX_CUSTOM_9,
    IO_CHIP_INDEX_CUSTOM_10,
    IO_CHIP_INDEX_CUSTOM_11,
    IO_CHIP_INDEX_CUSTOM_12,
    IO_CHIP_INDEX_CUSTOM_13,
    IO_CHIP_INDEX_CUSTOM_14,
    IO_CHIP_INDEX_CUSTOM_15,
    IO_CHIP_INDEX_CUSTOM_16,

    /* MStar pad-mux abstraction, don't touch these pads */
    /* BT PCM */
    IO_CHIP_INDEX_BT_PCM_SDO,
    IO_CHIP_INDEX_BT_PCM_SDI,
    IO_CHIP_INDEX_BT_PCM_BCK,
    IO_CHIP_INDEX_BT_PCM_WCK,

    /* MStar BT */
    IO_CHIP_INDEX_BT_CHIP_EN,
    IO_CHIP_INDEX_BT_CLK_24M,
    IO_CHIP_INDEX_BT_RX_TX,
    IO_CHIP_INDEX_BT_SPI_SENB,
    IO_CHIP_INDEX_BT_DATA_0,
    IO_CHIP_INDEX_BT_SPI_SCLK,
    IO_CHIP_INDEX_BT_DATA_1,
    IO_CHIP_INDEX_BT_SPI_SDATA,

    /* MASTER SPI */
    IO_CHIP_INDEX_MSPI_CLK0,
    IO_CHIP_INDEX_MSPI_CS0_N,
    IO_CHIP_INDEX_MSPI_DO0,
    IO_CHIP_INDEX_MSPI_DI0,

    IO_CHIP_INDEX_MSPI_CLK1,
    IO_CHIP_INDEX_MSPI_CS1_N,
    IO_CHIP_INDEX_MSPI_DO1,
    IO_CHIP_INDEX_MSPI_DI1,

    /* SD card */
    IO_CHIP_INDEX_SD1_CDZ,
    IO_CHIP_INDEX_SD2_CDZ,

    /* DBB SPI */
    IO_CHIP_INDEX_DBB_SPI_CLK0,
    IO_CHIP_INDEX_DBB_SPI_CS0_N,
    IO_CHIP_INDEX_DBB_SPI_DO0,
    IO_CHIP_INDEX_DBB_SPI_DI0,

    IO_CHIP_INDEX_DBB_SPI_CLK1,
    IO_CHIP_INDEX_DBB_SPI_CS1_N,
    IO_CHIP_INDEX_DBB_SPI_DO1,
    IO_CHIP_INDEX_DBB_SPI_DI1,

    IO_CHIP_INDEX_DBB_SPI_CS2_N,

    /* I2C controller */
    IO_CHIP_INDEX_I2C_SCK,
    IO_CHIP_INDEX_I2C_SDA,

    /* MPIF controller */
    IO_CHIP_INDEX_MPIF_CS,
    IO_CHIP_INDEX_MPIF_CLK,
    IO_CHIP_INDEX_MPIF_BUSY,
    IO_CHIP_INDEX_MPIF_D0,
    IO_CHIP_INDEX_MPIF_D1,
    IO_CHIP_INDEX_MPIF_D2,
    IO_CHIP_INDEX_MPIF_D3,

    /* Keypad */
    IO_CHIP_INDEX_COL_5,
    IO_CHIP_INDEX_COL_6,
    IO_CHIP_INDEX_COL_7,
    IO_CHIP_INDEX_ROW_5,
    IO_CHIP_INDEX_ROW_6,
    IO_CHIP_INDEX_ROW_7,

    /* LCD */
    IO_CHIP_INDEX_LCD_CS0_N,
    IO_CHIP_INDEX_LCD_CS1_N,
    IO_CHIP_INDEX_LCD_CMD,
    IO_CHIP_INDEX_LCD_WR,
    IO_CHIP_INDEX_LCD_RD,
    IO_CHIP_INDEX_LCD_RSTZ,
    IO_CHIP_INDEX_LCD_FMARK,
    IO_CHIP_INDEX_LCD_D_0,
    IO_CHIP_INDEX_LCD_D_1,
    IO_CHIP_INDEX_LCD_D_2,
    IO_CHIP_INDEX_LCD_D_3,
    IO_CHIP_INDEX_LCD_D_4,
    IO_CHIP_INDEX_LCD_D_5,
    IO_CHIP_INDEX_LCD_D_6,
    IO_CHIP_INDEX_LCD_D_7,
    IO_CHIP_INDEX_LCD_D_8,
    IO_CHIP_INDEX_LCD_D_9,
    IO_CHIP_INDEX_LCD_D_10,
    IO_CHIP_INDEX_LCD_D_11,
    IO_CHIP_INDEX_LCD_D_12,
    IO_CHIP_INDEX_LCD_D_13,
    IO_CHIP_INDEX_LCD_D_14,
    IO_CHIP_INDEX_LCD_D_15,
    IO_CHIP_INDEX_LCD_D_16,
    IO_CHIP_INDEX_LCD_D_17,

    /* RF SPI */
    IO_CHIP_INDEX_RF_SPI_CLK,
    IO_CHIP_INDEX_RF_SPI_EN,
    IO_CHIP_INDEX_RF_SPI_IN,
    IO_CHIP_INDEX_RF_SPI_OUT,

    /* SENSOR */
    IO_CHIP_INDEX_SENSOR_VSYNC,
    IO_CHIP_INDEX_SENSOR_HSYNC,
    IO_CHIP_INDEX_SENSOR_EN,
    IO_CHIP_INDEX_SENSOR_RESET,
    IO_CHIP_INDEX_SENSOR_PCLK,
    IO_CHIP_INDEX_SENSOR_MCLK,
    IO_CHIP_INDEX_SENSOR_D_0,
    IO_CHIP_INDEX_SENSOR_D_1,
    IO_CHIP_INDEX_SENSOR_D_2,
    IO_CHIP_INDEX_SENSOR_D_3,
    IO_CHIP_INDEX_SENSOR_D_4,
    IO_CHIP_INDEX_SENSOR_D_5,
    IO_CHIP_INDEX_SENSOR_D_6,
    IO_CHIP_INDEX_SENSOR_D_7,

    /* SIM 1 */
    IO_CHIP_INDEX_USIM1PRES,
    IO_CHIP_INDEX_USIM1DATA,
    IO_CHIP_INDEX_USIM1CLK,
    IO_CHIP_INDEX_USIM1RST,

    /* SIM 2 */
    IO_CHIP_INDEX_USIM2PRES,
    IO_CHIP_INDEX_USIM2DATA,
    IO_CHIP_INDEX_USIM2CLK,
    IO_CHIP_INDEX_USIM2RST,

    /* TBUO */
    IO_CHIP_INDEX_TBUO0,
    IO_CHIP_INDEX_TBUO1,
    IO_CHIP_INDEX_TBUO2,
    IO_CHIP_INDEX_TBUO3,
    IO_CHIP_INDEX_TBUO4,
    IO_CHIP_INDEX_TBUO5,
    IO_CHIP_INDEX_TBUO6,
    IO_CHIP_INDEX_TBUO7,
    IO_CHIP_INDEX_TBUO8,
    IO_CHIP_INDEX_TBUO9,

    /* UART 1 */
    IO_CHIP_INDEX_UART1_TXD,
    IO_CHIP_INDEX_UART1_RXD,
    IO_CHIP_INDEX_UART1_CTS,
    IO_CHIP_INDEX_UART1_RTS,
    IO_CHIP_INDEX_UART1_DTR,
    IO_CHIP_INDEX_UART1_DSR,

    /* UART 2 */
    IO_CHIP_INDEX_UART2_TXD,
    IO_CHIP_INDEX_UART2_RXD,
    IO_CHIP_INDEX_UART2_CTS,
    IO_CHIP_INDEX_UART2_RTS,

    /* WIFI */
    IO_CHIP_INDEX_WIFI_EN,
    IO_CHIP_INDEX_WIFI_WAKEUP,
    IO_CHIP_INDEX_WIFI_RX,
    IO_CHIP_INDEX_WIFI_GPIO4_OUT,

    /* BALL */
    IO_CHIP_INDEX_BALL_UP,
    IO_CHIP_INDEX_BALL_DOWN,
    IO_CHIP_INDEX_BALL_LEFT,
    IO_CHIP_INDEX_BALL_RIGHT,

#ifdef __RFID__
	IO_CHIP_INDEX_RFID_I2CSIM_SCL_IN,
	IO_CHIP_INDEX_RFID_I2CSIM_SCL_OUT,
	IO_CHIP_INDEX_RFID_I2CSIM_SDA_IN,
	IO_CHIP_INDEX_RFID_I2CSIM_SDA_OUT,
#ifdef __USE_MSR3110__
	IO_CHIP_INDEX_RFID_SIM_SWITCH_IN,
	IO_CHIP_INDEX_RFID_SIM_SWITCH_OUT,
	IO_CHIP_INDEX_RFID_ROM_BOOT_OUT,
	IO_CHIP_INDEX_RFID_ROM_BOOT_IN,
#endif	//__USE_MSR3110__
	IO_CHIP_INDEX_RFID_VEN_OUT,
	IO_CHIP_INDEX_RFID_RSTPD_OUT,
	IO_CHIP_INDEX_RFID_SPISIM_SDO_OUT,
	IO_CHIP_INDEX_RFID_SPISIM_SCK_OUT,
	IO_CHIP_INDEX_RFID_SPISIM_CSZ_OUT,
	IO_CHIP_INDEX_RFID_SPISIM_CSZ_IN,
	IO_CHIP_INDEX_RFID_SPISIM_SDI_IN,
#endif	//__RFID__

#ifdef __BARCODE__
	IO_CHIP_INDEX_BARCODE_TRIGGER_OUT,
	IO_CHIP_INDEX_BARCODE_ENABLE_OUT,
#endif	//__BARCODE__

    /* SHMCL test */
    IO_CHIP_INDEX_SHMCL_DL_MBX_SEND,
    IO_CHIP_INDEX_SHMCL_UL_MBX_INT,
    IO_CHIP_INDEX_SHMCL_UL_MBX_SEND,
    IO_CHIP_INDEX_SHMCL_DL_MBX_INT,
    
    /* CMMB */
    IO_CHIP_INDEX_CMMB_I2S_BCK,
    IO_CHIP_INDEX_CMMB_I2S_WS,
    IO_CHIP_INDEX_CMMB_I2S_DIO,
    IO_CHIP_INDEX_CMMB_RESET,
    IO_CHIP_INDEX_CMMB_LDO_EN,
    IO_CHIP_INDEX_CMMB_PSI,
    IO_CHIP_INDEX_CMMB_MODE,
    IO_CHIP_INDEX_CMMB_MPIF_INT,

    /* SD */
    IO_CHIP_INDEX_SD1_CLK,
    IO_CHIP_INDEX_SD1_CMD,
    IO_CHIP_INDEX_SD1_D0,
    IO_CHIP_INDEX_SD1_D1,
    IO_CHIP_INDEX_SD1_D2,
    IO_CHIP_INDEX_SD1_D3,

    /* SD2 */
    IO_CHIP_INDEX_SD2_CLK,
    IO_CHIP_INDEX_SD2_CMD,
    IO_CHIP_INDEX_SD2_D0,
    IO_CHIP_INDEX_SD2_D1,
    IO_CHIP_INDEX_SD2_D2,
    IO_CHIP_INDEX_SD2_D3,

    IO_CHIP_INDEX_NONE,
};

opaque_enum(IoChipPull_e_)
{
    IO_CHIP_PULL_DISABLE,
    IO_CHIP_PULL_DOWN,
    IO_CHIP_PULL_UP,
    IO_CHIP_PULL_HW_CTL,
    IO_CHIP_PULL_AUTO,

    IO_CHIP_PULL_INVALID,
};

opaque_enum(IoChipDrive_e_)
{
    IO_CHIP_DRIVE_0,
    IO_CHIP_DRIVE_1,
    IO_CHIP_DRIVE_2,
    IO_CHIP_DRIVE_3,

    IO_CHIP_DRIVE_INVALID,
};

opaque_enum(IoChipReleaseOption_e_)
{
    IO_CHIP_RO_IN,
    IO_CHIP_RO_IN_PU,
    IO_CHIP_RO_IN_PD,
    IO_CHIP_RO_OUT_LOW,
    IO_CHIP_RO_NONE,
};

struct IoChipPadInit_t_
{
    IoChipPadNum_e ePadNum;
    IoChipPull_e   ePull;
    IoChipDrive_e  eDrive;
    u8             nOutputInit;
};

struct IoChipSignalMapping_t_
{
    MdlPmDevice_e       eDevice;
    IoChipSignalIndex_e eIndex;
    IoChipPadNum_e      ePadNum;
};

/*=============================================================*/
// Variable definition
/*=============================================================*/
extern IoChipPadNum_e g_aeIoChipGpioMappingTbl[];


/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif // __SDK_SIMULATION__
#endif // __DRV_IO_CHIP_PUB_TYPES_H__

