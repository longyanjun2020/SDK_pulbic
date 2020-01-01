/***************************************************************************
 *  kernel_gpio.h
 *--------------------------------------------------------------------------
 *  Scope: GPIO register description
 *
 ****************************************************************************/

#ifndef __KERNEL_GPIO_H__
#define __KERNEL_GPIO_H__

/* B2 registers definition */

#include "vm_types.ht"
#include "cpu_mem_map.h"

/************************************************/
/* GPIO registers definition                    */
/************************************************/

#ifdef __B1__
typedef struct KeGpio_s
{
	u32 u32_Mux6;
	u32 u32_Mux5;
	u32 u32_Mux4;
	u32 u32_Mux3;
	u32 u32_Mux2;
	u32 u32_Mux1;
	u32 u32_Mux0;
   	u32 u32_PullEn1;
   	u32 u32_PullEn0;
   	u32 u32_DataIn1;
   	u32 u32_DataIn0;
	u32 u32_Drive2;
	u32 u32_Drive1;
	u32 u32_Drive0;
   	u32 u32_DataOut1;
   	u32 u32_DataOut0;
  	u32 u32_Dir1;
  	u32 u32_Dir0;
} KeGpio_t;
#else // __B1__
typedef struct KeGpio_s
{
    u32 u32_mx_sel_0_reg; // mx_sel_0_reg[28:0]
    u32 u32_mx_sel_1_reg; // mx_sel_1_reg[30:0]
    u32 u32_mx_sel_2_reg; // mx_sel_2_reg[29:0]
    u32 u32_mx_sel_3_reg; // mx_sel_3_reg[30:0]
    u32 u32_mx_sel_4_reg; // mx_sel_4_reg[30:0]
    u32 u32_mx_sel_5_reg; // mx_sel_5_reg[2:0]
    u32 reserved_1[26];
    u32 u32_p_sel_0; // p_sel_0[31:0] 0x80
    u32 u32_p_sel_1; // p_sel_1[31:0]
    u32 u32_p_sel_2; // p_sel_2[11:0]
    u32 reserved_2[13];
    u32 u32_drive_0; // drive_0[30:0] 0xC0
    u32 u32_drive_1; // drive_1[30:0]
    u32 u32_drive_2; // drive_2[20:0]
    u32 reserved_3[13];
    u32 u32_gpio_in0; // gpio_in0[31:0] 0x100
    u32 u32_gpio_in1; // gpio_in1[40:32]
    u32 reserved_4[6];
    u32 u32_gpio_reg0; // gpio_reg0[31:0] 0x120
    u32 u32_gpio_reg1; // gpio_reg1[40:32]
    u32 reserved_5[6];
    u32 u32_gpio_oen0; // gpio_oen0[31:0] 0x140
    u32 u32_gpio_oen1; // gpio_oen1[40:32]
    u32 reserved_6[6];
    u32 u32_gpio_sleep_en0; // gpio_sleep_en0[31:0] 0x160
    u32 u32_gpio_sleep_en1; // gpio_sleep_en1[40:32]
} KeGpio_t;
#endif // __B1__


/*** DataL registers ***/
#define GPIO_DATAL_GPIO0_MSK                          ((u32)1<<0)
#define GPIO_DATAL_GPIO0_POS                          0
#define GPIO_DATAL_GPIO1_MSK                          ((u32)1<<1)
#define GPIO_DATAL_GPIO1_POS                          1
#define GPIO_DATAL_GPIO2_MSK                          ((u32)1<<2)
#define GPIO_DATAL_GPIO2_POS                          2
#define GPIO_DATAL_GPIO3_MSK                          ((u32)1<<3)
#define GPIO_DATAL_GPIO3_POS                          3
#define GPIO_DATAL_GPIO4_MSK                          ((u32)1<<4)
#define GPIO_DATAL_GPIO4_POS                          4
#define GPIO_DATAL_GPIO5_MSK                          ((u32)1<<5)
#define GPIO_DATAL_GPIO5_POS                          5
#define GPIO_DATAL_GPIO6_MSK                          ((u32)1<<6)
#define GPIO_DATAL_GPIO6_POS                          6
#define GPIO_DATAL_GPIO7_MSK                          ((u32)1<<7)
#define GPIO_DATAL_GPIO7_POS                          7
#define GPIO_DATAL_GPIO8_MSK                          ((u32)1<<8)
#define GPIO_DATAL_GPIO8_POS                          8
#define GPIO_DATAL_GPIO9_MSK                          ((u32)1<<9)
#define GPIO_DATAL_GPIO9_POS                          9
#define GPIO_DATAL_GPIO10_MSK                         ((u32)1<<10)
#define GPIO_DATAL_GPIO10_POS                         10
#define GPIO_DATAL_GPIO11_MSK                         ((u32)1<<11)
#define GPIO_DATAL_GPIO11_POS                         11
#define GPIO_DATAL_GPIO12_MSK                         ((u32)1<<12)
#define GPIO_DATAL_GPIO12_POS                         12
#define GPIO_DATAL_GPIO13_MSK                         ((u32)1<<13)
#define GPIO_DATAL_GPIO13_POS                         13
#define GPIO_DATAL_GPIO14_MSK                         ((u32)1<<14)
#define GPIO_DATAL_GPIO14_POS                         14
#define GPIO_DATAL_GPIO15_MSK                         ((u32)1<<15)
#define GPIO_DATAL_GPIO15_POS                         15
#define GPIO_DATAL_GPIO16_MSK                         ((u32)1<<16)
#define GPIO_DATAL_GPIO16_POS                         16
#define GPIO_DATAL_GPIO17_MSK                         ((u32)1<<17)
#define GPIO_DATAL_GPIO17_POS                         17
#define GPIO_DATAL_GPIO18_MSK                         ((u32)1<<18)
#define GPIO_DATAL_GPIO18_POS                         18
#define GPIO_DATAL_GPIO19_MSK                         ((u32)1<<19)
#define GPIO_DATAL_GPIO19_POS                         19
#define GPIO_DATAL_GPIO20_MSK                         ((u32)1<<20)
#define GPIO_DATAL_GPIO20_POS                         20
#define GPIO_DATAL_GPIO21_MSK                         ((u32)1<<21)
#define GPIO_DATAL_GPIO21_POS                         21
#define GPIO_DATAL_GPIO22_MSK                         ((u32)1<<22)
#define GPIO_DATAL_GPIO22_POS                         22
#define GPIO_DATAL_GPIO23_MSK                         ((u32)1<<23)
#define GPIO_DATAL_GPIO23_POS                         23
#define GPIO_DATAL_GPIO24_MSK                         ((u32)1<<24)
#define GPIO_DATAL_GPIO24_POS                         24
#define GPIO_DATAL_GPIO25_MSK                         ((u32)1<<25)
#define GPIO_DATAL_GPIO25_POS                         25
#define GPIO_DATAL_GPIO26_MSK                         ((u32)1<<26)
#define GPIO_DATAL_GPIO26_POS                         26
#define GPIO_DATAL_GPIO27_MSK                         ((u32)1<<27)
#define GPIO_DATAL_GPIO27_POS                         27
#define GPIO_DATAL_GPIO28_MSK                         ((u32)1<<28)
#define GPIO_DATAL_GPIO28_POS                         28
#define GPIO_DATAL_GPIO29_MSK                         ((u32)1<<29)
#define GPIO_DATAL_GPIO29_POS                         29
#define GPIO_DATAL_GPIO30_MSK                         ((u32)1<<30)
#define GPIO_DATAL_GPIO30_POS                         30
#define GPIO_DATAL_GPIO31_MSK                         ((u32)1<<31)
#define GPIO_DATAL_GPIO31_POS                         31

/*** DataH registers ***/
#define GPIO_DATAH_GPIO32_MSK                         ((u32)1<<0)
#define GPIO_DATAH_GPIO32_POS                         0
#define GPIO_DATAH_GPIO33_MSK                         ((u32)1<<1)
#define GPIO_DATAH_GPIO33_POS                         1
#define GPIO_DATAH_GPIO34_MSK                         ((u32)1<<2)
#define GPIO_DATAH_GPIO34_POS                         2
#define GPIO_DATAH_GPIO35_MSK                         ((u32)1<<3)
#define GPIO_DATAH_GPIO35_POS                         3
#define GPIO_DATAH_GPIO36_MSK                         ((u32)1<<4)
#define GPIO_DATAH_GPIO36_POS                         4
#define GPIO_DATAH_GPIO37_MSK                         ((u32)1<<5)
#define GPIO_DATAH_GPIO37_POS                         5
#define GPIO_DATAH_GPIO38_MSK                         ((u32)1<<6)
#define GPIO_DATAH_GPIO38_POS                         6
#define GPIO_DATAH_GPIO39_MSK                         ((u32)1<<7)
#define GPIO_DATAH_GPIO39_POS                         7
#define GPIO_DATAH_GPIO40_MSK                         ((u32)1<<8)
#define GPIO_DATAH_GPIO40_POS                         8


/*** Mux0 registers ***/
typedef struct MUX_0 {
    u32 KEYPAD      : 4 ; // 3:0     KEYPAD             ETM                DBG
    u32 RXTX        : 4 ; // 7:4     RXTX               GPIO_25_24         TBUO_9_8           IDBG_RXTX
    u32 EXT_IQ_CLK  : 4 ; // 11:8    EXT_IQ_CLK         GPIO_26            EXTINT5            IDBG_SYSCLK
    u32 SPI_RF_IN   : 4 ; // 15:12   SPI_RF_IN          EXT_TXPORT_CLK     GPIO_27            IDBG_DBG_OUT_0
    u32 SPI_RF      : 4 ; // 19:16   SPI_RF             IDBG_CTRL
    u32 TBUO1       : 4 ; // 23:20   TBUO1              GPIO_28            IDBG_DBG_OUT_1
    u32 TBUO2       : 4 ; // 27:24   TBUO2              GPIO_29            IDBG_DBG_OUT_2
    u32 TBUO3       : 4 ; // 31:28   TBUO3              GPIO_30            IDBG_DBG_OUT_3
} KePadMux0_t;

#define GPIO_MUX_KEYPAD_POS                 0 //---------------------------- KEYPAD
#define GPIO_MUX_KEYPAD_MSK                 ((u32)0xF<<GPIO_MUX_KEYPAD_POS)
#define GPIO_MUX_KEYPAD_KEYPAD              0
#define GPIO_MUX_KEYPAD_ETM                 1
#define GPIO_MUX_KEYPAD_DBG                 2
#define GPIO_MUX_RXTX_POS                   4 //---------------------------- RXTX
#define GPIO_MUX_RXTX_MSK                   ((u32)0xF<<GPIO_MUX_RXTX_POS)
#define GPIO_MUX_RXTX_RXTX                  0
#define GPIO_MUX_RXTX_GPIO_25_24            1
#define GPIO_MUX_RXTX_TBUO_9_8              2
#define GPIO_MUX_RXTX_IDBG_RXTX             3
#define GPIO_MUX_EXT_IQ_CLK_POS             8 //---------------------------- EXT_IQ_CLK
#define GPIO_MUX_EXT_IQ_CLK_MSK             ((u32)0xF<<GPIO_MUX_EXT_IQ_CLK_POS)
#define GPIO_MUX_EXT_IQ_CLK_EXT_IQ_CLK      0
#define GPIO_MUX_EXT_IQ_CLK_GPIO_26         1
#define GPIO_MUX_EXT_IQ_CLK_EXTINT5         2
#define GPIO_MUX_EXT_IQ_CLK_IDBG_SYSCLK     3
#define GPIO_MUX_SPI_RF_IN_POS              12 //---------------------------- SPI_RF_IN
#define GPIO_MUX_SPI_RF_IN_MSK              ((u32)0xF<<GPIO_MUX_SPI_RF_IN_POS)
#define GPIO_MUX_SPI_RF_IN_SPI_RF_IN        0
#define GPIO_MUX_SPI_RF_IN_EXT_TXPORT_CLK   1
#define GPIO_MUX_SPI_RF_IN_GPIO_27          2
#define GPIO_MUX_SPI_RF_IN_IDBG_DBG_OUT_0   3
#define GPIO_MUX_SPI_RF_POS                 16 //---------------------------- SPI_RF
#define GPIO_MUX_SPI_RF_MSK                 ((u32)0xF<<GPIO_MUX_SPI_RF_POS)
#define GPIO_MUX_SPI_RF_SPI_RF              0
#define GPIO_MUX_SPI_RF_IDBG_CTRL           1
#define GPIO_MUX_TBUO1_POS                  20 //---------------------------- TBUO1
#define GPIO_MUX_TBUO1_MSK                  ((u32)0xF<<GPIO_MUX_TBUO1_POS)
#define GPIO_MUX_TBUO1_TBUO1                0
#define GPIO_MUX_TBUO1_GPIO_28              1
#define GPIO_MUX_TBUO1_IDBG_DBG_OUT_1       2
#define GPIO_MUX_TBUO2_POS                  24 //---------------------------- TBUO2
#define GPIO_MUX_TBUO2_MSK                  ((u32)0xF<<GPIO_MUX_TBUO2_POS)
#define GPIO_MUX_TBUO2_TBUO2                0
#define GPIO_MUX_TBUO2_GPIO_29              1
#define GPIO_MUX_TBUO2_IDBG_DBG_OUT_2       2
#define GPIO_MUX_TBUO3_POS                  28 //---------------------------- TBUO3
#define GPIO_MUX_TBUO3_MSK                  ((u32)0xF<<GPIO_MUX_TBUO3_POS)
#define GPIO_MUX_TBUO3_TBUO3                0
#define GPIO_MUX_TBUO3_GPIO_30              1
#define GPIO_MUX_TBUO3_IDBG_DBG_OUT_3       2

/*** Mux1 registers ***/
typedef struct MUX_1 {
    u32 TBUO4       : 4 ; // 3:0     TBUO4              GPIO_31            IDBG_DBG_OUT_4
    u32 TBUO5       : 4 ; // 7:4     TBUO5              GPIO_32            IDBG_DBG_OUT_5
    u32 TBUO6       : 4 ; // 11:8    TBUO6              GPIO_33            IDBG_DBG_OUT_6
    u32 TBUO7       : 4 ; // 15:12   TBUO7              QBSAVE             GPIO_34            BOOT_CTRL5         IDBG_DBG_OUT_7
    u32 GPIO_0      : 4 ; // 19:16   GPIO_0             SPI1_SCLK          UART2_TXD          ROW_6              DBG_SPI_0          SPI_CLK            SDIO_CLK
    u32 GPIO_1      : 4 ; // 23:20   GPIO_1             SPI1_SDO           UART2_RXD          ROW_7              DBG_SPI_1          SPI_DO             SDIO_CDZ
    u32 GPIO_2      : 4 ; // 27:24   GPIO_2             SPI1_SDIO          UART2_CTS          COL_6              DBG_SPI_2          SPI_DI             SDIO_OCDET
    u32 GPIO_3      : 4 ; // 31:28   GPIO_3             SPI1_SSL0          UART2_RTS          COL_7              DBG_SPI_3          SPI_CS0_N          SDIO_CMD
} KePadMux1_t;

#define GPIO_MUX_TBUO4_POS                  0 //---------------------------- TBUO4
#define GPIO_MUX_TBUO4_MSK                  ((u32)0xF<<GPIO_MUX_TBUO4_POS)
#define GPIO_MUX_TBUO4_TBUO4                0
#define GPIO_MUX_TBUO4_GPIO_31              1
#define GPIO_MUX_TBUO4_IDBG_DBG_OUT_4       2
#define GPIO_MUX_TBUO5_POS                  4 //---------------------------- TBUO5
#define GPIO_MUX_TBUO5_MSK                  ((u32)0xF<<GPIO_MUX_TBUO5_POS)
#define GPIO_MUX_TBUO5_TBUO5                0
#define GPIO_MUX_TBUO5_GPIO_32              1
#define GPIO_MUX_TBUO5_IDBG_DBG_OUT_5       2
#define GPIO_MUX_TBUO6_POS                  8 //---------------------------- TBUO6
#define GPIO_MUX_TBUO6_MSK                  ((u32)0xF<<GPIO_MUX_TBUO6_POS)
#define GPIO_MUX_TBUO6_TBUO6                0
#define GPIO_MUX_TBUO6_GPIO_33              1
#define GPIO_MUX_TBUO6_IDBG_DBG_OUT_6       2
#define GPIO_MUX_TBUO7_POS                  12 //---------------------------- TBUO7
#define GPIO_MUX_TBUO7_MSK                  ((u32)0xF<<GPIO_MUX_TBUO7_POS)
#define GPIO_MUX_TBUO7_TBUO7                0
#define GPIO_MUX_TBUO7_QBSAVE               1
#define GPIO_MUX_TBUO7_GPIO_34              2
#define GPIO_MUX_TBUO7_BOOT_CTRL5           3
#define GPIO_MUX_TBUO7_IDBG_DBG_OUT_7       4
#define GPIO_MUX_GPIO_0_POS                 16 //---------------------------- GPIO_0
#define GPIO_MUX_GPIO_0_MSK                 ((u32)0xF<<GPIO_MUX_GPIO_0_POS)
#define GPIO_MUX_GPIO_0_GPIO_0              0
#define GPIO_MUX_GPIO_0_SPI1_SCLK           1
#define GPIO_MUX_GPIO_0_UART2_TXD           2
#define GPIO_MUX_GPIO_0_ROW_6               3
#define GPIO_MUX_GPIO_0_DBG_SPI_0           4
#define GPIO_MUX_GPIO_0_SPI_CLK             5
#define GPIO_MUX_GPIO_0_SDIO_CLK            6
#define GPIO_MUX_GPIO_1_POS                 20 //---------------------------- GPIO_1
#define GPIO_MUX_GPIO_1_MSK                 ((u32)0xF<<GPIO_MUX_GPIO_1_POS)
#define GPIO_MUX_GPIO_1_GPIO_1              0
#define GPIO_MUX_GPIO_1_SPI1_SDO            1
#define GPIO_MUX_GPIO_1_UART2_RXD           2
#define GPIO_MUX_GPIO_1_ROW_7               3
#define GPIO_MUX_GPIO_1_DBG_SPI_1           4
#define GPIO_MUX_GPIO_1_SPI_DO              5
#define GPIO_MUX_GPIO_1_SDIO_CDZ            6
#define GPIO_MUX_GPIO_2_POS                 24 //---------------------------- GPIO_2
#define GPIO_MUX_GPIO_2_MSK                 ((u32)0xF<<GPIO_MUX_GPIO_2_POS)
#define GPIO_MUX_GPIO_2_GPIO_2              0
#define GPIO_MUX_GPIO_2_SPI1_SDIO           1
#define GPIO_MUX_GPIO_2_UART2_CTS           2
#define GPIO_MUX_GPIO_2_COL_6               3
#define GPIO_MUX_GPIO_2_DBG_SPI_2           4
#define GPIO_MUX_GPIO_2_SPI_DI              5
#define GPIO_MUX_GPIO_2_SDIO_OCDET          6
#define GPIO_MUX_GPIO_3_POS                 28 //---------------------------- GPIO_3
#define GPIO_MUX_GPIO_3_MSK                 ((u32)0xF<<GPIO_MUX_GPIO_3_POS)
#define GPIO_MUX_GPIO_3_GPIO_3              0
#define GPIO_MUX_GPIO_3_SPI1_SSL0           1
#define GPIO_MUX_GPIO_3_UART2_RTS           2
#define GPIO_MUX_GPIO_3_COL_7               3
#define GPIO_MUX_GPIO_3_DBG_SPI_3           4
#define GPIO_MUX_GPIO_3_SPI_CS0_N           5
#define GPIO_MUX_GPIO_3_SDIO_CMD            6

/*** Mux2 registers ***/
typedef struct MUX_2 {
    u32 GPIO_4      : 4 ; // 3:0     GPIO_4             SPI1_SSL1          TRACECLK           EXTINT0
    u32 GPIO_6_5    : 4 ; // 7:4     GPIO_6_5           B_I2C
    u32 GPIO_7      : 4 ; // 11:8    GPIO_7             FDI_G711           I2S_SDI_E          DAI_PCMIN          DBG_EAI_0
    u32 GPIO_8      : 4 ; // 15:12   GPIO_8             FDO_G711           I2S_SDO_E          DAI_PCMOUT         DBG_EAI_1
    u32 GPIO_9      : 4 ; // 19:16   GPIO_9             FBCK_G711          I2S_SCK_E          DAI_PCMCLK         DBG_EAI_2
    u32 GPIO_10     : 4 ; // 23:20   GPIO_10            FSY_G711           I2S_WS_E           DAI_PCMRST         DBG_EAI_3
    u32 GPIO_11     : 4 ; // 27:24   GPIO_11            UART1_RXD
    u32 GPIO_12     : 4 ; // 31:28   GPIO_12            UART1_TXD          BOOT_CTRL0
} KePadMux2_t;

#define GPIO_MUX_GPIO_4_POS                 0 //---------------------------- GPIO_4
#define GPIO_MUX_GPIO_4_MSK                 ((u32)0xF<<GPIO_MUX_GPIO_4_POS)
#define GPIO_MUX_GPIO_4_GPIO_4              0
#define GPIO_MUX_GPIO_4_SPI1_SSL1           1
#define GPIO_MUX_GPIO_4_TRACECLK            2
#define GPIO_MUX_GPIO_4_EXTINT0             3
#define GPIO_MUX_GPIO_6_5_POS               4 //---------------------------- GPIO_6_5
#define GPIO_MUX_GPIO_6_5_MSK               ((u32)0xF<<GPIO_MUX_GPIO_6_5_POS)
#define GPIO_MUX_GPIO_6_5_GPIO              0
#define GPIO_MUX_GPIO_6_5_B_I2C             1
#define GPIO_MUX_GPIO_7_POS                 8 //---------------------------- GPIO_7
#define GPIO_MUX_GPIO_7_MSK                 ((u32)0xF<<GPIO_MUX_GPIO_7_POS)
#define GPIO_MUX_GPIO_7_GPIO_7              0
#define GPIO_MUX_GPIO_7_FDI_G711            1
#define GPIO_MUX_GPIO_7_I2S_SDI_E           2
#define GPIO_MUX_GPIO_7_DAI_PCMIN           3
#define GPIO_MUX_GPIO_7_DBG_EAI_0           4
#define GPIO_MUX_GPIO_8_POS                 12 //---------------------------- GPIO_8
#define GPIO_MUX_GPIO_8_MSK                 ((u32)0xF<<GPIO_MUX_GPIO_8_POS)
#define GPIO_MUX_GPIO_8_GPIO_8              0
#define GPIO_MUX_GPIO_8_FDO_G711            1
#define GPIO_MUX_GPIO_8_I2S_SDO_E           2
#define GPIO_MUX_GPIO_8_DAI_PCMOUT          3
#define GPIO_MUX_GPIO_8_DBG_EAI_1           4
#define GPIO_MUX_GPIO_9_POS                 16 //---------------------------- GPIO_9
#define GPIO_MUX_GPIO_9_MSK                 ((u32)0xF<<GPIO_MUX_GPIO_9_POS)
#define GPIO_MUX_GPIO_9_GPIO_9              0
#define GPIO_MUX_GPIO_9_FBCK_G711           1
#define GPIO_MUX_GPIO_9_I2S_SCK_E           2
#define GPIO_MUX_GPIO_9_DAI_PCMCLK          3
#define GPIO_MUX_GPIO_9_DBG_EAI_2           4
#define GPIO_MUX_GPIO_10_POS                20 //---------------------------- GPIO_10
#define GPIO_MUX_GPIO_10_MSK                ((u32)0xF<<GPIO_MUX_GPIO_10_POS)
#define GPIO_MUX_GPIO_10_GPIO_10            0
#define GPIO_MUX_GPIO_10_FSY_G711           1
#define GPIO_MUX_GPIO_10_I2S_WS_E           2
#define GPIO_MUX_GPIO_10_DAI_PCMRST         3
#define GPIO_MUX_GPIO_10_DBG_EAI_3          4
#define GPIO_MUX_GPIO_11_POS                24 //---------------------------- GPIO_11
#define GPIO_MUX_GPIO_11_MSK                ((u32)0xF<<GPIO_MUX_GPIO_11_POS)
#define GPIO_MUX_GPIO_11_GPIO_11            0
#define GPIO_MUX_GPIO_11_UART1_RXD          1
#define GPIO_MUX_GPIO_12_POS                28 //---------------------------- GPIO_12
#define GPIO_MUX_GPIO_12_MSK                ((u32)0xF<<GPIO_MUX_GPIO_12_POS)
#define GPIO_MUX_GPIO_12_GPIO_12            0
#define GPIO_MUX_GPIO_12_UART1_TXD          1
#define GPIO_MUX_GPIO_12_BOOT_CTRL0         2

/*** Mux3 registers ***/
typedef struct MUX_3 {
    u32 GPIO_13     : 4 ; // 3:0     GPIO_13            UART1_RTS          BOOT_CTRL1
    u32 GPIO_14     : 4 ; // 7:4     GPIO_14            UART1_CTS
    u32 GPIO_15     : 4 ; // 11:8    GPIO_15            UART1_DSR          EXTINT6            SPI1_SCLK
    u32 GPIO_16     : 4 ; // 15:12   GPIO_16            UART1_DTR          BOOT_CTRL2         CLK8KHZ_OUT        SPI1_SDIO
    u32 GPIO_17     : 4 ; // 19:16   GPIO_17            PWM_OUT0           USIM1PRES          EXTINT4
    u32 GPIO_18     : 4 ; // 23:20   GPIO_18            PWM_OUT1           BOOT_CTRL3
    u32 GPIO_19     : 4 ; // 27:24   WDN                GPIO_19
    u32 GPIO_20     : 4 ; // 31:28   GPIO_20            PERIPH1_CLK        CLK32K_OUT         EXTINT1            TRACECLK           DBG_CLK1_0
} KePadMux3_t;

#define GPIO_MUX_GPIO_13_POS                0 //---------------------------- GPIO_13
#define GPIO_MUX_GPIO_13_MSK                ((u32)0xF<<GPIO_MUX_GPIO_13_POS)
#define GPIO_MUX_GPIO_13_GPIO_13            0
#define GPIO_MUX_GPIO_13_UART1_RTS          1
#define GPIO_MUX_GPIO_13_BOOT_CTRL1         2
#define GPIO_MUX_GPIO_14_POS                4 //---------------------------- GPIO_14
#define GPIO_MUX_GPIO_14_MSK                ((u32)0xF<<GPIO_MUX_GPIO_14_POS)
#define GPIO_MUX_GPIO_14_GPIO_14            0
#define GPIO_MUX_GPIO_14_UART1_CTS          1
#define GPIO_MUX_GPIO_15_POS                8 //---------------------------- GPIO_15
#define GPIO_MUX_GPIO_15_MSK                ((u32)0xF<<GPIO_MUX_GPIO_15_POS)
#define GPIO_MUX_GPIO_15_GPIO_15            0
#define GPIO_MUX_GPIO_15_UART1_DSR          1
#define GPIO_MUX_GPIO_15_EXTINT6            2
#define GPIO_MUX_GPIO_15_SPI1_SCLK          3
#define GPIO_MUX_GPIO_16_POS                12 //---------------------------- GPIO_16
#define GPIO_MUX_GPIO_16_MSK                ((u32)0xF<<GPIO_MUX_GPIO_16_POS)
#define GPIO_MUX_GPIO_16_GPIO_16            0
#define GPIO_MUX_GPIO_16_UART1_DTR          1
#define GPIO_MUX_GPIO_16_BOOT_CTRL2         2
#define GPIO_MUX_GPIO_16_CLK8KHZ_OUT        3
#define GPIO_MUX_GPIO_16_SPI1_SDIO          4
#define GPIO_MUX_GPIO_17_POS                16 //---------------------------- GPIO_17
#define GPIO_MUX_GPIO_17_MSK                ((u32)0xF<<GPIO_MUX_GPIO_17_POS)
#define GPIO_MUX_GPIO_17_GPIO_17            0
#define GPIO_MUX_GPIO_17_PWM_OUT0           1
#define GPIO_MUX_GPIO_17_USIM1PRES          2
#define GPIO_MUX_GPIO_17_EXTINT4            3
#define GPIO_MUX_GPIO_18_POS                20 //---------------------------- GPIO_18
#define GPIO_MUX_GPIO_18_MSK                ((u32)0xF<<GPIO_MUX_GPIO_18_POS)
#define GPIO_MUX_GPIO_18_GPIO_18            0
#define GPIO_MUX_GPIO_18_PWM_OUT1           1
#define GPIO_MUX_GPIO_18_BOOT_CTRL3         2
#define GPIO_MUX_GPIO_19_POS                24 //---------------------------- GPIO_19
#define GPIO_MUX_GPIO_19_MSK                ((u32)0xF<<GPIO_MUX_GPIO_19_POS)
#define GPIO_MUX_GPIO_19_WDN                0
#define GPIO_MUX_GPIO_19_GPIO_19            1
#define GPIO_MUX_GPIO_20_POS                28 //---------------------------- GPIO_20
#define GPIO_MUX_GPIO_20_MSK                ((u32)0xF<<GPIO_MUX_GPIO_20_POS)
#define GPIO_MUX_GPIO_20_GPIO_20            0
#define GPIO_MUX_GPIO_20_PERIPH1_CLK        1
#define GPIO_MUX_GPIO_20_CLK32K_OUT         2
#define GPIO_MUX_GPIO_20_EXTINT1            3
#define GPIO_MUX_GPIO_20_TRACECLK           4
#define GPIO_MUX_GPIO_20_DBG_CLK1_0         5

/*** Mux4 registers ***/
typedef struct MUX_4 {
    u32 GPIO_21     : 4 ; // 3:0     GPIO_21            PERIPH2_CLK        CLK32K_OUT         EXTINT2            BOOT_CTRL4         DBG_CLK1_1
    u32 GPIO_22     : 4 ; // 7:4     GPIO_22            PERIPH3_CLK        CLK32K_OUT         EXTINT3            USIM2PRES          DBG_CLK1_2         SPI_CS0_N          SDIO_D_3
    u32 GPIO_23     : 4 ; // 11:8    GPIO_23            PERIPH2_CLK        CLK32K_OUT         EXTINT2            DBG_CLK1_3         SDIO_PCTL          OTG_DRVVBUS
    u32 USIM1DATA   : 4 ; // 15:12   USIM1DATA          GPIO_35
    u32 USIM1CLK    : 4 ; // 19:16   USIM1CLK           GPIO_36
    u32 USIM1RST    : 4 ; // 23:20   USIM1RST           GPIO_37
    u32 USIM2DATA   : 4 ; // 27:24   USIM2DATA          GPIO_38            RFID_SIN           JTDO               JTDI               SPI_DI             SDIO_D_0
    u32 USIM2CLK    : 4 ; // 31:28   USIM2CLK           GPIO_39            RFID_SOUT          JTCK               JTMS               SPI_DO             SDIO_D_1
} KePadMux4_t;

#define GPIO_MUX_GPIO_21_POS                0 //---------------------------- GPIO_21
#define GPIO_MUX_GPIO_21_MSK                ((u32)0xF<<GPIO_MUX_GPIO_21_POS)
#define GPIO_MUX_GPIO_21_GPIO_21            0
#define GPIO_MUX_GPIO_21_PERIPH2_CLK        1
#define GPIO_MUX_GPIO_21_CLK32K_OUT         2
#define GPIO_MUX_GPIO_21_EXTINT2            3
#define GPIO_MUX_GPIO_21_BOOT_CTRL4         4
#define GPIO_MUX_GPIO_21_DBG_CLK1_1         5
#define GPIO_MUX_GPIO_22_POS                4 //---------------------------- GPIO_22
#define GPIO_MUX_GPIO_22_MSK                ((u32)0xF<<GPIO_MUX_GPIO_22_POS)
#define GPIO_MUX_GPIO_22_GPIO_22            0
#define GPIO_MUX_GPIO_22_PERIPH3_CLK        1
#define GPIO_MUX_GPIO_22_CLK32K_OUT         2
#define GPIO_MUX_GPIO_22_EXTINT3            3
#define GPIO_MUX_GPIO_22_USIM2PRES          4
#define GPIO_MUX_GPIO_22_DBG_CLK1_2         5
#define GPIO_MUX_GPIO_22_SPI_CS0_N          6
#define GPIO_MUX_GPIO_22_SDIO_D_3           7
#define GPIO_MUX_GPIO_23_POS                8 //---------------------------- GPIO_23
#define GPIO_MUX_GPIO_23_MSK                ((u32)0xF<<GPIO_MUX_GPIO_23_POS)
#define GPIO_MUX_GPIO_23_GPIO_23            0
#define GPIO_MUX_GPIO_23_PERIPH2_CLK        1
#define GPIO_MUX_GPIO_23_CLK32K_OUT         2
#define GPIO_MUX_GPIO_23_EXTINT2            3
#define GPIO_MUX_GPIO_23_DBG_CLK1_3         4
#define GPIO_MUX_GPIO_23_SDIO_PCTL          5
#define GPIO_MUX_GPIO_23_OTG_DRVVBUS        6
#define GPIO_MUX_USIM1DATA_POS              12 //---------------------------- USIM1DATA
#define GPIO_MUX_USIM1DATA_MSK              ((u32)0xF<<GPIO_MUX_USIM1DATA_POS)
#define GPIO_MUX_USIM1DATA_USIM1DATA        0
#define GPIO_MUX_USIM1DATA_GPIO_35          1
#define GPIO_MUX_USIM1CLK_POS               16 //---------------------------- USIM1CLK
#define GPIO_MUX_USIM1CLK_MSK               ((u32)0xF<<GPIO_MUX_USIM1CLK_POS)
#define GPIO_MUX_USIM1CLK_USIM1CLK          0
#define GPIO_MUX_USIM1CLK_GPIO_36           1
#define GPIO_MUX_USIM1RST_POS               20 //---------------------------- USIM1RST
#define GPIO_MUX_USIM1RST_MSK               ((u32)0xF<<GPIO_MUX_USIM1RST_POS)
#define GPIO_MUX_USIM1RST_USIM1RST          0
#define GPIO_MUX_USIM1RST_GPIO_37           1
#define GPIO_MUX_USIM2DATA_POS              24 //---------------------------- USIM2DATA
#define GPIO_MUX_USIM2DATA_MSK              ((u32)0xF<<GPIO_MUX_USIM2DATA_POS)
#define GPIO_MUX_USIM2DATA_USIM2DATA        0
#define GPIO_MUX_USIM2DATA_GPIO_38          1
#define GPIO_MUX_USIM2DATA_RFID_SIN         2
#define GPIO_MUX_USIM2DATA_JTDO             3
#define GPIO_MUX_USIM2DATA_JTDI             4
#define GPIO_MUX_USIM2DATA_SPI_DI           5
#define GPIO_MUX_USIM2DATA_SDIO_D_0         6
#define GPIO_MUX_USIM2CLK_POS               28 //---------------------------- USIM2CLK
#define GPIO_MUX_USIM2CLK_MSK               ((u32)0xF<<GPIO_MUX_USIM2CLK_POS)
#define GPIO_MUX_USIM2CLK_USIM2CLK          0
#define GPIO_MUX_USIM2CLK_GPIO_39           1
#define GPIO_MUX_USIM2CLK_RFID_SOUT         2
#define GPIO_MUX_USIM2CLK_JTCK              3
#define GPIO_MUX_USIM2CLK_JTMS              4
#define GPIO_MUX_USIM2CLK_SPI_DO            5
#define GPIO_MUX_USIM2CLK_SDIO_D_1          6

/*** Mux5 registers ***/
typedef struct MUX_5 {
    u32 USIM2RST    : 4 ; // 3:0     USIM2RST           GPIO_40            SPI_CLK            SDIO_D_2           OTG_DRVVBUS
    u32             : 28;
} KePadMux5_t;

#define GPIO_MUX_USIM2RST_POS               0 //---------------------------- USIM2RST
#define GPIO_MUX_USIM2RST_MSK               ((u32)0xF<<GPIO_MUX_USIM2RST_POS)
#define GPIO_MUX_USIM2RST_USIM2RST          0
#define GPIO_MUX_USIM2RST_GPIO_40           1
#define GPIO_MUX_USIM2RST_SPI_CLK           2
#define GPIO_MUX_USIM2RST_SDIO_D_2          3
#define GPIO_MUX_USIM2RST_OTG_DRVVBUS       4

extern volatile KeGpio_t* const KeGpio;

#endif //__KERNEL_GPIO_H__
