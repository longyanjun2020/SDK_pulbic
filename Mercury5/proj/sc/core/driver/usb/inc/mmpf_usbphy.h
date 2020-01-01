//==============================================================================
//
//  File        : mmpf_usbphy.h
//  Description : INCLUDE File for the Firmware USB PHY Driver
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_USBPHY_H_
#define _MMPF_USBPHY_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================
/* - PHY register index -
 * For more detail information, please refer to
 * "AIT_USB2PHYA_U040L7_function_spec_v1.0.doc" for MCR_V2
 */
#define BG_OPT1_TRCV_OPT        (0x00)
    /* Default value of TRCV Option reg */
    #define TRCV_OPT_DEFAULT        (0x0000)
    /* Default value of BG Option1 reg */
    #define BG_OPT1_DEFAULT         (0x0300)
    /* Band-Gap 1.2V selection */
    #define RESISTOR_DIV_OUTPUT     (0x0800)
    /* Embedded LDO Output Cotrol */
    #define LDO_OUT_1d20V           (0x0000)
    #define LDO_OUT_1d10V           (0x1000)
    #define LDO_OUT_1d30V           (0x2000)
    #define LDO_OUT_1d25V           (0x3000)
    #define LDO_OUT_MASK            (0x3000)
#define PLL_CTL1_BG_OPT2        (0x02)
    /* Default value of BG Option2 reg */
    #define BG_OPT2_DEFAULT         (0x005F)
    #define BG_VREF_412mV               (0x0000)
    #define BG_VREF_400mV               (0x0040)
    #define BG_VREF_392mV               (0x0080)
    #define BG_VREF_485mV               (0x00C0)
    #define BG_VREF_MASK                (0x0003)
    #define BG_VREF_SHIFT               (0x06)
    #define BG_BIAS_CURRENT_29d84375uA  (0x0000)
    #define BG_BIAS_CURRENT_29d6875uA   (0x0001)
    #define BG_BIAS_CURRENT_29d53125uA  (0x0002)
    #define BG_BIAS_CURRENT_29d375uA    (0x0003)
    #define BG_BIAS_CURRENT_29d21875uA  (0x0004)
    #define BG_BIAS_CURRENT_29d0625uA   (0x0005)
    #define BG_BIAS_CURRENT_28d90625uA  (0x0006)
    #define BG_BIAS_CURRENT_28d75uA     (0x0007)
    #define BG_BIAS_CURRENT_28d59375uA  (0x0008)
    #define BG_BIAS_CURRENT_28d4375uA   (0x0009)
    #define BG_BIAS_CURRENT_28d28125uA  (0x000A)
    #define BG_BIAS_CURRENT_28d125uA    (0x000B)
    #define BG_BIAS_CURRENT_27d96875uA  (0x000C)
    #define BG_BIAS_CURRENT_27d8125uA   (0x000D)
    #define BG_BIAS_CURRENT_27d65625uA  (0x000E)
    #define BG_BIAS_CURRENT_27d5uA      (0x000F)
    #define BG_BIAS_CURRENT_27d34375uA  (0x0010)
    #define BG_BIAS_CURRENT_27d1875uA   (0x0011)
    #define BG_BIAS_CURRENT_27d03125uA  (0x0012)
    #define BG_BIAS_CURRENT_26d875uA    (0x0013)
    #define BG_BIAS_CURRENT_26d71875uA  (0x0014)
    #define BG_BIAS_CURRENT_26d5625uA   (0x0015)
    #define BG_BIAS_CURRENT_26d40625uA  (0x0016)
    #define BG_BIAS_CURRENT_26d25uA     (0x0017)
    #define BG_BIAS_CURRENT_26d09375uA  (0x0018)
    #define BG_BIAS_CURRENT_25d9375uA   (0x0019)
    #define BG_BIAS_CURRENT_25d78125uA  (0x001A)
    #define BG_BIAS_CURRENT_25d625uA    (0x001B)
    #define BG_BIAS_CURRENT_25d46875uA  (0x001C)
    #define BG_BIAS_CURRENT_25d3125uA   (0x001D)
    #define BG_BIAS_CURRENT_25d15625uA  (0x001E)
    #define BG_BIAS_CURRENT_25uA        (0x001F)
    #define BG_BIAS_CURRENT_24d84375uA  (0x0020)
    #define BG_BIAS_CURRENT_24d6875uA   (0x0021)
    #define BG_BIAS_CURRENT_24d53125uA  (0x0022)
    #define BG_BIAS_CURRENT_24d375uA    (0x0023)
    #define BG_BIAS_CURRENT_24d21875uA  (0x0024)
    #define BG_BIAS_CURRENT_24d0625uA   (0x0025)
    #define BG_BIAS_CURRENT_23d90625uA  (0x0026)
    #define BG_BIAS_CURRENT_23d75uA     (0x0027)
    #define BG_BIAS_CURRENT_23d59375uA  (0x0028)
    #define BG_BIAS_CURRENT_23d4375uA   (0x0029)
    #define BG_BIAS_CURRENT_23d28125uA  (0x002A)
    #define BG_BIAS_CURRENT_23d125uA    (0x002B)
    #define BG_BIAS_CURRENT_22d96875uA  (0x002C)
    #define BG_BIAS_CURRENT_22d8125uA   (0x002D)
    #define BG_BIAS_CURRENT_22d65625uA  (0x002E)
    #define BG_BIAS_CURRENT_22d5uA      (0x002F)
    #define BG_BIAS_CURRENT_22d34375uA  (0x0030)
    #define BG_BIAS_CURRENT_22d1875uA   (0x0031)
    #define BG_BIAS_CURRENT_22d03125uA  (0x0032)
    #define BG_BIAS_CURRENT_21d875uA    (0x0033)
    #define BG_BIAS_CURRENT_21d71875uA  (0x0034)
    #define BG_BIAS_CURRENT_21d5625uA   (0x0035)
    #define BG_BIAS_CURRENT_21d40625uA  (0x0036)
    #define BG_BIAS_CURRENT_21d25uA     (0x0037)
    #define BG_BIAS_CURRENT_21d09375uA  (0x0038)
    #define BG_BIAS_CURRENT_20d9375uA   (0x0039)
    #define BG_BIAS_CURRENT_20d78125uA  (0x003A)
    #define BG_BIAS_CURRENT_20d625uA    (0x003B)
    #define BG_BIAS_CURRENT_20d46875uA  (0x003C)
    #define BG_BIAS_CURRENT_20d3125uA   (0x003D)
    #define BG_BIAS_CURRENT_20d15625uA  (0x003E)
    #define BG_BIAS_CURRENT_20uA        (0x003F)
    #define BG_BIAS_CURRENT_MASK        (0x003F)

    #define PLL_CTL1_DEFAULT        (0x9400)

    /* Charge Pump current control */
    #define CHARGE_PUMP_7d5uA       (0x0800)
    #define CHARGE_PUMP_5d0uA       (0x0400)
    #define CHARGE_PUMP_2d5uA       (0x0200)
    #define CHARGE_PUMP_1d5uA       (0x0100)
    /* Control Perfect PLL CP Current */
    #define PLL_IMATCH_EN           (0x1000)
    #define PLL_FB_CLK              (0x8000)
#define PLL_CTL3_CTL2           (0x04)
    /* PLL M selection from register or XTL_SELECT */
    #define PLL_M_REG_CTL           (0x0080)
    #define PLL_M_12MHZ_DIV         (0x0028)
    #define PLL_M_24MHZ_DIV         (0x0014)
    #define PLL_M_30MHZ_DIV         (0x0010)
    #define PLL_M_24MHZ_DIV_MP      (0x000E)

    #define PLL_CTL3_DEFAULT        (0x8200)

    /* PLL lock judge value with REG_CLK count */
    #define TT_DELAY_1d4nS          (0x8000)
    #define N_SEL_IN_DIV256_EN      (0x0200)
#define FS_TX_OPT_PLL_CTL4      (0x06)
    #define PLL_CTL4_DEFAULT        (0x0010)
    /* For Full-Speed current tune */
    #define FXTX_RESL_42OHM         (0x0000)
    #define FXTX_RESL_45OHM         (0x0100)
    #define FXTX_RESL_49OHM         (0x0300)
    /* HSTX data sampler */
    #define HSTX_DATA_SAMPLER_DIS   (0x0400)
#define SQ_OPT_HS_TX_OPT        (0x08)
    /* Default value of HS_TX Option reg */
    #define HS_TX_DEFAULT           (0x0044)
    #define LOWER_AFF_POWER_EN      (0x0040)
    #define HS_CUR_MASK             (0x07)
    #define HS_CUR_200mV            (0x0000)
    #define HS_CUR_240mV            (0x0001)
    #define HS_CUR_280mV            (0x0002)
    #define HS_CUR_320mV            (0x0003)
    #define HS_CUR_360mV            (0x0004)
    #define HS_CUR_400mV            (0x0005)
    #define HS_CUR_440mV            (0x0006)
    #define HS_CUR_480mV            (0x0007)
    #define HS_CUR_PLUS_MASK        (0x07)
    #define HS_CUR_PLUS_SHIFT       (0x03)
    #define HS_CUR_PLUS_00mV        (0x0000)
    #define HS_CUR_PLUS_10mV        (0x0008)
    #define HS_CUR_PLUS_20mV        (0x0018)
    #define HS_CUR_PLUS_30mV        (0x0028)
    #define HS_CUR_PLUS_40mV        (0x0038)
    /* Enable Digital Filiter on Squelch Detection */
    #define SQ_FILTER_EN            (0x0800)
    /* Squelch level tuning option */
    #define SQ_LEVEL_SHIFT          (0x08)
    #define SQ_LEVEL_MASK           (0x07)
    #define SQ_LEVEL_62d5mV         (0x0000)
    #define SQ_LEVEL_75mV           (0x0100)
    #define SQ_LEVEL_87d5mV         (0x0200)
    #define SQ_LEVEL_100mV          (0x0300)
    #define SQ_LEVEL_112d5mV        (0x0400)
    #define SQ_LEVEL_125mV          (0x0500)
    #define SQ_LEVEL_137d5mV        (0x0600)
    #define SQ_LEVEL_150mV          (0x0700)
#define PLL_TEST_OTG_CTL        (0x0A)
    /* Control OTG reference voltage */
    #define OTG_VREF_PWR_DOWN       (0x0020)
    /* Enable OTG comparators */
    #define OTG_COMP_ENABLE         (0x000F)
    /* Analog test mode */
    #define ANA_TEST_MODE           (0x0100)
    /* Control REFCLK_CORE in Analog test mode */
    #define REFCLK_CORE_EN          (0x0000)
    #define REFCLK_CORE_OFF         (0x0200)
    /* Control XO power down in Analog test mode */
    #define XO_BLOCK_EN             (0x0000)
    #define XO_BLOCK_OFF            (0x0400)
    /* Enable Single-Pair PLL output */
    #define PLL_NORMAL_OUT          (0x0000)
    #define PLL_SPCLK_OUT           (0x2000)
    /* Control PLL power */
    #define PLL_PWR_UP              (0x0000)
    #define PLL_PWR_DOWN            (0x8000)
#define PWR_CTL_PUPD_TEST       (0x0C)
    /* RPU/RPD control */
    #define DM_PULL_DOWN            (0x0004)
    #define DP_PULL_DOWN            (0x0008)
    #define DM_PULL_UP1             (0x0010)
    #define DM_PULL_UP2             (0x0020)
    #define DP_PULL_UP1             (0x0040)
    #define DP_PULL_UP2             (0x0080)
    /* Power Down control */
    #define HSTX_PWR_DOWN           (0x0100)
    #define HSRX_PWR_DOWN           (0x0200)
    #define FSLS_TX_PWR_DOWN        (0x0400)
    #define FSLS_RX_PWR_DOWN        (0x0800)
    #define DISCON_DTC_PWR_DOWN     (0x1000)
    #define SQ_DTC_PWR_DOWN         (0x2000)
    #define USB_BS_PWR_DOWN         (0x4000)
    #define USB_BG_PWR_DOWN         (0x8000)
#define UTMI_DBG_CHIP_TEST      (0x10)
#define HS_RX_DBG_RX_ERR        (0x12)
#define OTG_DISCONN_SIG_CTL     (0x20)

#endif // _MMPF_USBPHY_H_
