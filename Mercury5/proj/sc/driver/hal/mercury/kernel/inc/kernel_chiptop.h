#ifndef __KERNEL_CHIPTOP_H__
#define __KERNEL_CHIPTOP_H__

#include "cpu_mem_map.hc"

typedef struct CHIPTOP_s{
    // h0000, bit: 0
    /* MIU clock select DFT clock
    MPLL_SYN clock select DFT clock
    MIU_REC clock select DFT clock
    GE clock select DFT clock*/
    #define offset_of_chiptop_reg_ckg_alldft (0)
    #define mask_of_chiptop_reg_ckg_alldft (0x1)
    unsigned int reg_ckg_alldft:1;

    // h0000, bit: 14
    /* */
    unsigned int :15;

    // h0000
    unsigned int /* padding 16 bit */:16;

    // h0001, bit: 8
    /* */
    unsigned int :9;

    // h0001, bit: 9
    /* FT mode
    1: enable FT mode
    0: disable FT mode*/
    #define offset_of_chiptop_reg_ft_mode (2)
    #define mask_of_chiptop_reg_ft_mode (0x200)
    unsigned int reg_ft_mode:1;

    // h0001, bit: 11
    /* */
    unsigned int :2;

    // h0001, bit: 12
    /* digital pads set high*/
    #define offset_of_chiptop_reg_seth (2)
    #define mask_of_chiptop_reg_seth (0x1000)
    unsigned int reg_seth:1;

    // h0001, bit: 13
    /* digital pads set low*/
    #define offset_of_chiptop_reg_setl (2)
    #define mask_of_chiptop_reg_setl (0x2000)
    unsigned int reg_setl:1;

    // h0001, bit: 14
    /* */
    unsigned int :2;

    // h0001
    unsigned int /* padding 16 bit */:16;

    // h0002, bit: 14
    /* */
    unsigned int :16;

    // h0002
    unsigned int /* padding 16 bit */:16;

    // h0003, bit: 2
    /* FUART Mode*/
    #define offset_of_chiptop_reg_fuart_mode (6)
    #define mask_of_chiptop_reg_fuart_mode (0x7)
    unsigned int reg_fuart_mode:3;

    // h0003, bit: 3
    /* */
    unsigned int :1;

    // h0003, bit: 4
    /* UART0 Mode*/
    #define offset_of_chiptop_reg_uart0_mode (6)
    #define mask_of_chiptop_reg_uart0_mode (0x10)
    unsigned int reg_uart0_mode:1;

    // h0003, bit: 7
    /* */
    unsigned int :3;

    // h0003, bit: 10
    /* UART1 Mode*/
    #define offset_of_chiptop_reg_uart1_mode (6)
    #define mask_of_chiptop_reg_uart1_mode (0x700)
    unsigned int reg_uart1_mode:3;

    // h0003, bit: 14
    /* */
    unsigned int :5;

    // h0003
    unsigned int /* padding 16 bit */:16;

    // h0004, bit: 14
    /* */
    unsigned int :16;

    // h0004
    unsigned int /* padding 16 bit */:16;

    // h0005, bit: 14
    /* */
    unsigned int :16;

    // h0005
    unsigned int /* padding 16 bit */:16;

    // h0006, bit: 2
    /* SR Mode*/
    #define offset_of_chiptop_reg_sr_mode (12)
    #define mask_of_chiptop_reg_sr_mode (0x7)
    unsigned int reg_sr_mode:3;

    // h0006, bit: 3
    /* */
    unsigned int :1;

    // h0006, bit: 5
    /* SR I2C Mode*/
    #define offset_of_chiptop_reg_sr_i2c_mode (12)
    #define mask_of_chiptop_reg_sr_i2c_mode (0x30)
    unsigned int reg_sr_i2c_mode:2;

    // h0006, bit: 14
    /* */
    unsigned int :10;

    // h0006
    unsigned int /* padding 16 bit */:16;

    // h0007, bit: 2
    /* PWM0 Mode*/
    #define offset_of_chiptop_reg_pwm0_mode (14)
    #define mask_of_chiptop_reg_pwm0_mode (0x7)
    unsigned int reg_pwm0_mode:3;

    // h0007, bit: 5
    /* PWM1 Mode*/
    #define offset_of_chiptop_reg_pwm1_mode (14)
    #define mask_of_chiptop_reg_pwm1_mode (0x38)
    unsigned int reg_pwm1_mode:3;

    // h0007, bit: 8
    /* PWM2 Mode*/
    #define offset_of_chiptop_reg_pwm2_mode (14)
    #define mask_of_chiptop_reg_pwm2_mode (0x1c0)
    unsigned int reg_pwm2_mode:3;

    // h0007, bit: 11
    /* PWM3 Mode*/
    #define offset_of_chiptop_reg_pwm3_mode (14)
    #define mask_of_chiptop_reg_pwm3_mode (0xe00)
    unsigned int reg_pwm3_mode:3;

    // h0007, bit: 14
    /* PWM4 Mode*/
    #define offset_of_chiptop_reg_pwm4_mode (14)
    #define mask_of_chiptop_reg_pwm4_mode (0x7000)
    unsigned int reg_pwm4_mode:3;

    // h0007, bit: 15
    /* */
    unsigned int :1;

    // h0007
    unsigned int /* padding 16 bit */:16;

    // h0008, bit: 2
    /* PWM5 Mode*/
    #define offset_of_chiptop_reg_pwm5_mode (16)
    #define mask_of_chiptop_reg_pwm5_mode (0x7)
    unsigned int reg_pwm5_mode:3;

    // h0008, bit: 5
    /* PWM6 Mode*/
    #define offset_of_chiptop_reg_pwm6_mode (16)
    #define mask_of_chiptop_reg_pwm6_mode (0x38)
    unsigned int reg_pwm6_mode:3;

    // h0008, bit: 8
    /* PWM7 Mode*/
    #define offset_of_chiptop_reg_pwm7_mode (16)
    #define mask_of_chiptop_reg_pwm7_mode (0x1c0)
    unsigned int reg_pwm7_mode:3;

    // h0008, bit: 9
    /* NAND Mode*/
    #define offset_of_chiptop_reg_nand_mode (16)
    #define mask_of_chiptop_reg_nand_mode (0x200)
    unsigned int reg_nand_mode:1;

    // h0008, bit: 11
    /* SD Mode*/
    #define offset_of_chiptop_reg_sd_mode (16)
    #define mask_of_chiptop_reg_sd_mode (0xc00)
    unsigned int reg_sd_mode:2;

    // h0008, bit: 14
    /* SDIO Mode*/
    #define offset_of_chiptop_reg_sdio_mode (16)
    #define mask_of_chiptop_reg_sdio_mode (0x7000)
    unsigned int reg_sdio_mode:3;

    // h0008, bit: 15
    /* */
    unsigned int :1;

    // h0008
    unsigned int /* padding 16 bit */:16;

    // h0009, bit: 1
    /* I2C0 Mode*/
    #define offset_of_chiptop_reg_i2c0_mode (18)
    #define mask_of_chiptop_reg_i2c0_mode (0x3)
    unsigned int reg_i2c0_mode:2;

    // h0009, bit: 3
    /* */
    unsigned int :2;

    // h0009, bit: 5
    /* I2C1 Mode*/
    #define offset_of_chiptop_reg_i2c1_mode (18)
    #define mask_of_chiptop_reg_i2c1_mode (0x30)
    unsigned int reg_i2c1_mode:2;

    // h0009, bit: 14
    /* */
    unsigned int :10;

    // h0009
    unsigned int /* padding 16 bit */:16;

    // h000a, bit: 14
    /* */
    unsigned int :16;

    // h000a
    unsigned int /* padding 16 bit */:16;

    // h000b, bit: 14
    /* */
    unsigned int :16;

    // h000b
    unsigned int /* padding 16 bit */:16;

    // h000c, bit: 2
    /* SPI0 Mode*/
    #define offset_of_chiptop_reg_spi0_mode (24)
    #define mask_of_chiptop_reg_spi0_mode (0x7)
    unsigned int reg_spi0_mode:3;

    // h000c, bit: 3
    /* */
    unsigned int :1;

    // h000c, bit: 6
    /* SPI1 Mode*/
    #define offset_of_chiptop_reg_spi1_mode (24)
    #define mask_of_chiptop_reg_spi1_mode (0x70)
    unsigned int reg_spi1_mode:3;

    // h000c, bit: 14
    /* */
    unsigned int :9;

    // h000c
    unsigned int /* padding 16 bit */:16;

    // h000d, bit: 14
    /* */
    unsigned int :16;

    // h000d
    unsigned int /* padding 16 bit */:16;

    // h000e, bit: 14
    /* */
    unsigned int :16;

    // h000e
    unsigned int /* padding 16 bit */:16;

    // h000f, bit: 2
    /* EJ Mode*/
    #define offset_of_chiptop_reg_ej_mode (30)
    #define mask_of_chiptop_reg_ej_mode (0x7)
    unsigned int reg_ej_mode:3;

    // h000f, bit: 3
    /* ETH Mode*/
    #define offset_of_chiptop_reg_eth_mode (30)
    #define mask_of_chiptop_reg_eth_mode (0x8)
    unsigned int reg_eth_mode:1;

    // h000f, bit: 5
    /* CCIR Mode*/
    #define offset_of_chiptop_reg_ccir_mode (30)
    #define mask_of_chiptop_reg_ccir_mode (0x30)
    unsigned int reg_ccir_mode:2;

    // h000f, bit: 6
    /* TTL Mode*/
    #define offset_of_chiptop_reg_ttl_mode (30)
    #define mask_of_chiptop_reg_ttl_mode (0x40)
    unsigned int reg_ttl_mode:1;

    // h000f, bit: 7
    /* */
    unsigned int :1;

    // h000f, bit: 10
    /* DMIC Mode*/
    #define offset_of_chiptop_reg_dmic_mode (30)
    #define mask_of_chiptop_reg_dmic_mode (0x700)
    unsigned int reg_dmic_mode:3;

    // h000f, bit: 11
    /* */
    unsigned int :1;

    // h000f, bit: 13
    /* I2S Mode*/
    #define offset_of_chiptop_reg_i2s_mode (30)
    #define mask_of_chiptop_reg_i2s_mode (0x3000)
    unsigned int reg_i2s_mode:2;

    // h000f, bit: 14
    /* */
    unsigned int :2;

    // h000f
    unsigned int /* padding 16 bit */:16;

    // h0010, bit: 14
    /* */
    unsigned int :16;

    // h0010
    unsigned int /* padding 16 bit */:16;

    // h0011, bit: 14
    /* */
    unsigned int :16;

    // h0011
    unsigned int /* padding 16 bit */:16;

    // h0012, bit: 1
    /* select TEST IN mode
    2'd0: TEST_IN functions are not enabled
    2'd1: TEST_IN[23:0] use FUART/SR/SPI0 pads
    2'd2: TEST_IN[23:0] use I2C0/SD/USB/SAR/PM/ETH pads
    2'd3: TEST_IN[14:0] use SAR/ETH/FUART/SPI0/SD/USB pads*/
    #define offset_of_chiptop_reg_test_in_mode (36)
    #define mask_of_chiptop_reg_test_in_mode (0x3)
    unsigned int reg_test_in_mode:2;

    // h0012, bit: 3
    /* */
    unsigned int :2;

    // h0012, bit: 5
    /* select TEST_OUT mode
    2'd0: TEST_OUT functions are not enabled.
    2'd1: TEST_OUT[23:0] use FUART/SR/SPI0 pads
    2'd2: TEST_OUT[23:0] use I2C0/SD/USB/SAR/PM/ETH pads
    2'd3: TEST_OUT[15:0] use SR pads*/
    #define offset_of_chiptop_reg_test_out_mode (36)
    #define mask_of_chiptop_reg_test_out_mode (0x30)
    unsigned int reg_test_out_mode:2;

    // h0012, bit: 14
    /* */
    unsigned int :10;

    // h0012
    unsigned int /* padding 16 bit */:16;

    // h0013, bit: 1
    /* EMMC mode*/
    #define offset_of_chiptop_reg_emmc_mode (38)
    #define mask_of_chiptop_reg_emmc_mode (0x3)
    unsigned int reg_emmc_mode:2;

    // h0013, bit: 3
    /* EMMC rst enable*/
    #define offset_of_chiptop_reg_emmc_rstn_en (38)
    #define mask_of_chiptop_reg_emmc_rstn_en (0xc)
    unsigned int reg_emmc_rstn_en:2;

    // h0013, bit: 4
    /* */
    #define offset_of_chiptop_reg_fuart_cts_gpio_en (38)
    #define mask_of_chiptop_reg_fuart_cts_gpio_en (0x10)
    unsigned int reg_fuart_cts_gpio_en:1;

    // h0013, bit: 5
    /* */
    #define offset_of_chiptop_reg_fuart_rts_gpio_en (38)
    #define mask_of_chiptop_reg_fuart_rts_gpio_en (0x20)
    unsigned int reg_fuart_rts_gpio_en:1;

    // h0013, bit: 6
    /* */
    #define offset_of_chiptop_reg_fuart_tx_gpio_en (38)
    #define mask_of_chiptop_reg_fuart_tx_gpio_en (0x40)
    unsigned int reg_fuart_tx_gpio_en:1;

    // h0013, bit: 7
    /* */
    #define offset_of_chiptop_reg_lcd_c0_gpio_en (38)
    #define mask_of_chiptop_reg_lcd_c0_gpio_en (0x80)
    unsigned int reg_lcd_c0_gpio_en:1;

    // h0013, bit: 8
    /* */
    #define offset_of_chiptop_reg_lcd_c6_gpio_en (38)
    #define mask_of_chiptop_reg_lcd_c6_gpio_en (0x100)
    unsigned int reg_lcd_c6_gpio_en:1;

    // h0013, bit: 9
    /* */
    #define offset_of_chiptop_reg_lcd_de_gpio_en (38)
    #define mask_of_chiptop_reg_lcd_de_gpio_en (0x200)
    unsigned int reg_lcd_de_gpio_en:1;

    // h0013, bit: 10
    /* */
    #define offset_of_chiptop_reg_spi0_gpio_en (38)
    #define mask_of_chiptop_reg_spi0_gpio_en (0x400)
    unsigned int reg_spi0_gpio_en:1;

    // h0013, bit: 14
    /* */
    unsigned int :5;

    // h0013
    unsigned int /* padding 16 bit */:16;

    // h0014, bit: 0
    /* */
    #define offset_of_chiptop_reg_pl80_16b_mode (40)
    #define mask_of_chiptop_reg_pl80_16b_mode (0x1)
    unsigned int reg_pl80_16b_mode:1;

    // h0014, bit: 1
    /* */
    #define offset_of_chiptop_reg_pl80_18b_mode (40)
    #define mask_of_chiptop_reg_pl80_18b_mode (0x2)
    unsigned int reg_pl80_18b_mode:1;

    // h0014, bit: 2
    /* */
    #define offset_of_chiptop_reg_pl80_8b_mode (40)
    #define mask_of_chiptop_reg_pl80_8b_mode (0x4)
    unsigned int reg_pl80_8b_mode:1;

    // h0014, bit: 3
    /* */
    unsigned int :1;

    // h0014, bit: 5
    /* */
    #define offset_of_chiptop_reg_rgb_16b_mode (40)
    #define mask_of_chiptop_reg_rgb_16b_mode (0x30)
    unsigned int reg_rgb_16b_mode:2;

    // h0014, bit: 6
    /* */
    #define offset_of_chiptop_reg_rgb_18b_mode (40)
    #define mask_of_chiptop_reg_rgb_18b_mode (0x40)
    unsigned int reg_rgb_18b_mode:1;

    // h0014, bit: 7
    /* */
    #define offset_of_chiptop_reg_rgb_24b_mode (40)
    #define mask_of_chiptop_reg_rgb_24b_mode (0x80)
    unsigned int reg_rgb_24b_mode:1;

    // h0014, bit: 9
    /* */
    #define offset_of_chiptop_reg_rgb_8b_mode (40)
    #define mask_of_chiptop_reg_rgb_8b_mode (0x300)
    unsigned int reg_rgb_8b_mode:2;

    // h0014, bit: 11
    /* */
    #define offset_of_chiptop_reg_sd30_mode (40)
    #define mask_of_chiptop_reg_sd30_mode (0xc00)
    unsigned int reg_sd30_mode:2;

    // h0014, bit: 14
    /* */
    #define offset_of_chiptop_reg_spi2_mode (40)
    #define mask_of_chiptop_reg_spi2_mode (0x7000)
    unsigned int reg_spi2_mode:3;

    // h0014, bit: 15
    /* */
    unsigned int :1;

    // h0014
    unsigned int /* padding 16 bit */:16;

    // h0015, bit: 2
    /* */
    #define offset_of_chiptop_reg_sr0_bt601_mode (42)
    #define mask_of_chiptop_reg_sr0_bt601_mode (0x7)
    unsigned int reg_sr0_bt601_mode:3;

    // h0015, bit: 3
    /* */
    unsigned int :1;

    // h0015, bit: 6
    /* */
    #define offset_of_chiptop_reg_sr0_bt656_mode (42)
    #define mask_of_chiptop_reg_sr0_bt656_mode (0x70)
    unsigned int reg_sr0_bt656_mode:3;

    // h0015, bit: 7
    /* */
    unsigned int :1;

    // h0015, bit: 9
    /* */
    #define offset_of_chiptop_reg_sr0_mipi_mode (42)
    #define mask_of_chiptop_reg_sr0_mipi_mode (0x300)
    unsigned int reg_sr0_mipi_mode:2;

    // h0015, bit: 11
    /* */
    #define offset_of_chiptop_reg_sr0_par_mode (42)
    #define mask_of_chiptop_reg_sr0_par_mode (0xc00)
    unsigned int reg_sr0_par_mode:2;

    // h0015, bit: 12
    /* */
    #define offset_of_chiptop_reg_sr1_bt656_mode (42)
    #define mask_of_chiptop_reg_sr1_bt656_mode (0x1000)
    unsigned int reg_sr1_bt656_mode:1;

    // h0015, bit: 14
    /* */
    #define offset_of_chiptop_reg_sr1_mipi_mode (42)
    #define mask_of_chiptop_reg_sr1_mipi_mode (0xe000)
    unsigned int reg_sr1_mipi_mode:3;

    // h0015
    unsigned int /* padding 16 bit */:16;

    // h0016, bit: 1
    /* */
    #define offset_of_chiptop_reg_tx_mipi_mode (44)
    #define mask_of_chiptop_reg_tx_mipi_mode (0x3)
    unsigned int reg_tx_mipi_mode:2;

    // h0016, bit: 4
    /* */
    #define offset_of_chiptop_reg_uart2_mode (44)
    #define mask_of_chiptop_reg_uart2_mode (0x1c)
    unsigned int reg_uart2_mode:3;

    // h0016, bit: 7
    /* */
    unsigned int :3;

    // h0016, bit: 9
    /* */
    #define offset_of_chiptop_reg_i2c2_mode (44)
    #define mask_of_chiptop_reg_i2c2_mode (0x300)
    unsigned int reg_i2c2_mode:2;

    // h0016, bit: 11
    /* */
    #define offset_of_chiptop_reg_i2c3_mode (44)
    #define mask_of_chiptop_reg_i2c3_mode (0xc00)
    unsigned int reg_i2c3_mode:2;

    // h0016, bit: 14
    /* */
    unsigned int :4;

    // h0016
    unsigned int /* padding 16 bit */:16;

    // h0017, bit: 1
    /* */
    #define offset_of_chiptop_reg_i2c1_dual_mode (46)
    #define mask_of_chiptop_reg_i2c1_dual_mode (0x3)
    unsigned int reg_i2c1_dual_mode:2;

    // h0017, bit: 2
    /* 0: I2C1 use reg_i2c1_dual_mode for I2C input control*/
    #define offset_of_chiptop_reg_i2c1_manu_enable (46)
    #define mask_of_chiptop_reg_i2c1_manu_enable (0x4)
    unsigned int reg_i2c1_manu_enable:1;

    // h0017, bit: 3
    /* */
    unsigned int :1;

    // h0017, bit: 5
    /* I2C1 SCL input for manu mode
    0: AND(du0, du1)
    1: OR(du0, du1)
    2: equal du0
    3: equal du1*/
    #define offset_of_chiptop_reg_i2c1_manu_scl (46)
    #define mask_of_chiptop_reg_i2c1_manu_scl (0x30)
    unsigned int reg_i2c1_manu_scl:2;

    // h0017, bit: 7
    /* I2C1 SDA input for manu mode
    0: AND(du0, du1)
    1: OR(du0, du1)
    2: equal du0
    3: equal du1*/
    #define offset_of_chiptop_reg_i2c1_manu_sda (46)
    #define mask_of_chiptop_reg_i2c1_manu_sda (0xc0)
    unsigned int reg_i2c1_manu_sda:2;

    // h0017, bit: 14
    /* */
    unsigned int :8;

    // h0017
    unsigned int /* padding 16 bit */:16;

    // h0018, bit: 14
    /* */
    unsigned int :16;

    // h0018
    unsigned int /* padding 16 bit */:16;

    // h0019, bit: 14
    /* */
    unsigned int :16;

    // h0019
    unsigned int /* padding 16 bit */:16;

    // h001a, bit: 14
    /* */
    unsigned int :16;

    // h001a
    unsigned int /* padding 16 bit */:16;

    // h001b, bit: 14
    /* */
    unsigned int :16;

    // h001b
    unsigned int /* padding 16 bit */:16;

    // h001c, bit: 11
    /* */
    unsigned int :12;

    // h001c, bit: 12
    /* force all of the whole chip sram power-on*/
    #define offset_of_chiptop_reg_force_allsram_on (56)
    #define mask_of_chiptop_reg_force_allsram_on (0x1000)
    unsigned int reg_force_allsram_on:1;

    // h001c, bit: 13
    /* */
    unsigned int :1;

    // h001c, bit: 14
    /* BIST mode start*/
    #define offset_of_chiptop_reg_bist_start_ext (56)
    #define mask_of_chiptop_reg_bist_start_ext (0x4000)
    unsigned int reg_bist_start_ext:1;

    // h001c, bit: 15
    /* BIST mode enable (disable in default)*/
    #define offset_of_chiptop_reg_bist_mode_ext (56)
    #define mask_of_chiptop_reg_bist_mode_ext (0x8000)
    unsigned int reg_bist_mode_ext:1;

    // h001c
    unsigned int /* padding 16 bit */:16;

    // h001d, bit: 14
    /* indicate sram done
    [0]: dig_gp
    [1]: pm_gp
    [2]: sc_gp
    [3]: vhe_gp
    [4]~[14]: N/A
    [15]: all*/
    #define offset_of_chiptop_reg_bist_done (58)
    #define mask_of_chiptop_reg_bist_done (0xffff)
    unsigned int reg_bist_done:16;

    // h001d
    unsigned int /* padding 16 bit */:16;

    // h001e, bit: 14
    /* indicate sram fail
    [0]: dig_gp
    [1]: pm_gp
    [2]: sc_gp
    [3]: vhe_gp
    [4]~[14]: N/A
    [15]: all*/
    #define offset_of_chiptop_reg_bist_fail (60)
    #define mask_of_chiptop_reg_bist_fail (0xffff)
    unsigned int reg_bist_fail:16;

    // h001e
    unsigned int /* padding 16 bit */:16;

    // h001f, bit: 14
    /* */
    unsigned int :16;

    // h001f
    unsigned int /* padding 16 bit */:16;

    // h0020, bit: 14
    /* dummy registers for CHIPTOP*/
    #define offset_of_chiptop_reg_chiptop_dummy_0 (64)
    #define mask_of_chiptop_reg_chiptop_dummy_0 (0xffff)
    unsigned int reg_chiptop_dummy_0:16;

    // h0020
    unsigned int /* padding 16 bit */:16;

    // h0021, bit: 14
    /* dummy registers for CHIPTOP*/
    #define offset_of_chiptop_reg_chiptop_dummy_1 (66)
    #define mask_of_chiptop_reg_chiptop_dummy_1 (0xffff)
    unsigned int reg_chiptop_dummy_1:16;

    // h0021
    unsigned int /* padding 16 bit */:16;

    // h0022, bit: 14
    /* dummy registers for CHIPTOP*/
    #define offset_of_chiptop_reg_chiptop_dummy_2 (68)
    #define mask_of_chiptop_reg_chiptop_dummy_2 (0xffff)
    unsigned int reg_chiptop_dummy_2:16;

    // h0022
    unsigned int /* padding 16 bit */:16;

    // h0023, bit: 14
    /* dummy registers for CHIPTOP*/
    #define offset_of_chiptop_reg_chiptop_dummy_3 (70)
    #define mask_of_chiptop_reg_chiptop_dummy_3 (0xffff)
    unsigned int reg_chiptop_dummy_3:16;

    // h0023
    unsigned int /* padding 16 bit */:16;

    // h0024, bit: 1
    /* I2C pad control, [0]: SCL, [1]: SDA*/
    #define offset_of_chiptop_reg_i2c1_ie (72)
    #define mask_of_chiptop_reg_i2c1_ie (0x3)
    unsigned int reg_i2c1_ie:2;

    // h0024, bit: 14
    /* */
    unsigned int :14;

    // h0024
    unsigned int /* padding 16 bit */:16;

    // h0025, bit: 1
    /* I2C pad control, [0]: SCL, [1]: SDA*/
    #define offset_of_chiptop_reg_i2c1_pe (74)
    #define mask_of_chiptop_reg_i2c1_pe (0x3)
    unsigned int reg_i2c1_pe:2;

    // h0025, bit: 14
    /* */
    unsigned int :14;

    // h0025
    unsigned int /* padding 16 bit */:16;

    // h0026, bit: 1
    /* I2C pad control, [0]: SCL, [1]: SDA*/
    #define offset_of_chiptop_reg_i2c1_ps (76)
    #define mask_of_chiptop_reg_i2c1_ps (0x3)
    unsigned int reg_i2c1_ps:2;

    // h0026, bit: 14
    /* */
    unsigned int :14;

    // h0026
    unsigned int /* padding 16 bit */:16;

    // h0027, bit: 1
    /* I2C pad control, [0]: SCL, [1]: SDA*/
    #define offset_of_chiptop_reg_i2c1_drv (78)
    #define mask_of_chiptop_reg_i2c1_drv (0x3)
    unsigned int reg_i2c1_drv:2;

    // h0027, bit: 14
    /* */
    unsigned int :14;

    // h0027
    unsigned int /* padding 16 bit */:16;

    // h0028, bit: 1
    /* I2C pad control, [0]: SCL, [1]: SDA*/
    #define offset_of_chiptop_reg_i2c1_lsh18_en (80)
    #define mask_of_chiptop_reg_i2c1_lsh18_en (0x3)
    unsigned int reg_i2c1_lsh18_en:2;

    // h0028, bit: 14
    /* */
    unsigned int :14;

    // h0028
    unsigned int /* padding 16 bit */:16;

    // h0029, bit: 14
    /* */
    unsigned int :16;

    // h0029
    unsigned int /* padding 16 bit */:16;

    // h002a, bit: 7
    /* SPI pad control*/
    #define offset_of_chiptop_reg_spi0_drv (84)
    #define mask_of_chiptop_reg_spi0_drv (0xff)
    unsigned int reg_spi0_drv:8;

    // h002a, bit: 14
    /* */
    unsigned int :8;

    // h002a
    unsigned int /* padding 16 bit */:16;

    // h002b, bit: 7
    /* SPI pad control*/
    #define offset_of_chiptop_reg_spi1_drv (86)
    #define mask_of_chiptop_reg_spi1_drv (0xff)
    unsigned int reg_spi1_drv:8;

    // h002b, bit: 14
    /* */
    unsigned int :8;

    // h002b
    unsigned int /* padding 16 bit */:16;

    // h002c, bit: 3
    /* */
    #define offset_of_chiptop_reg_i2c0_drv (88)
    #define mask_of_chiptop_reg_i2c0_drv (0xf)
    unsigned int reg_i2c0_drv:4;

    // h002c, bit: 14
    /* */
    unsigned int :12;

    // h002c
    unsigned int /* padding 16 bit */:16;

    // h002d, bit: 1
    /* */
    #define offset_of_chiptop_reg_i2c0_pe (90)
    #define mask_of_chiptop_reg_i2c0_pe (0x3)
    unsigned int reg_i2c0_pe:2;

    // h002d, bit: 14
    /* */
    unsigned int :14;

    // h002d
    unsigned int /* padding 16 bit */:16;

    // h002e, bit: 1
    /* */
    #define offset_of_chiptop_reg_i2c0_ps (92)
    #define mask_of_chiptop_reg_i2c0_ps (0x3)
    unsigned int reg_i2c0_ps:2;

    // h002e, bit: 14
    /* */
    unsigned int :14;

    // h002e
    unsigned int /* padding 16 bit */:16;

    // h002f, bit: 1
    /* */
    #define offset_of_chiptop_reg_i2c0_gcr_sel_in (94)
    #define mask_of_chiptop_reg_i2c0_gcr_sel_in (0x3)
    unsigned int reg_i2c0_gcr_sel_in:2;

    // h002f, bit: 3
    /* */
    unsigned int :2;

    // h002f, bit: 4
    /* */
    #define offset_of_chiptop_reg_i2c0_gcr_bist_en (94)
    #define mask_of_chiptop_reg_i2c0_gcr_bist_en (0x10)
    unsigned int reg_i2c0_gcr_bist_en:1;

    // h002f, bit: 14
    /* */
    unsigned int :11;

    // h002f
    unsigned int /* padding 16 bit */:16;

    // h0030, bit: 14
    /* NAND pad control*/
    #define offset_of_chiptop_reg_nand_drv (96)
    #define mask_of_chiptop_reg_nand_drv (0x7fff)
    unsigned int reg_nand_drv:15;

    // h0030, bit: 15
    /* */
    unsigned int :1;

    // h0030
    unsigned int /* padding 16 bit */:16;

    // h0031, bit: 4
    /* NAND pad control*/
    #define offset_of_chiptop_reg_nand_pe (98)
    #define mask_of_chiptop_reg_nand_pe (0x1f)
    unsigned int reg_nand_pe:5;

    // h0031, bit: 14
    /* */
    unsigned int :11;

    // h0031
    unsigned int /* padding 16 bit */:16;

    // h0032, bit: 5
    /* NAND pad control*/
    #define offset_of_chiptop_reg_sd_drv (100)
    #define mask_of_chiptop_reg_sd_drv (0x3f)
    unsigned int reg_sd_drv:6;

    // h0032, bit: 7
    /* */
    unsigned int :2;

    // h0032, bit: 12
    /* NAND pad control*/
    #define offset_of_chiptop_reg_sd_pe (100)
    #define mask_of_chiptop_reg_sd_pe (0x1f00)
    unsigned int reg_sd_pe:5;

    // h0032, bit: 14
    /* */
    unsigned int :3;

    // h0032
    unsigned int /* padding 16 bit */:16;

    // h0033, bit: 1
    /* */
    #define offset_of_chiptop_reg_fuart_drv0 (102)
    #define mask_of_chiptop_reg_fuart_drv0 (0x3)
    unsigned int reg_fuart_drv0:2;

    // h0033, bit: 3
    /* */
    unsigned int :2;

    // h0033, bit: 5
    /* */
    #define offset_of_chiptop_reg_fuart_ie (102)
    #define mask_of_chiptop_reg_fuart_ie (0x30)
    unsigned int reg_fuart_ie:2;

    // h0033, bit: 7
    /* */
    unsigned int :2;

    // h0033, bit: 9
    /* */
    #define offset_of_chiptop_reg_fuart_pe (102)
    #define mask_of_chiptop_reg_fuart_pe (0x300)
    unsigned int reg_fuart_pe:2;

    // h0033, bit: 11
    /* */
    unsigned int :2;

    // h0033, bit: 13
    /* */
    #define offset_of_chiptop_reg_fuart_ps (102)
    #define mask_of_chiptop_reg_fuart_ps (0x3000)
    unsigned int reg_fuart_ps:2;

    // h0033, bit: 14
    /* */
    unsigned int :2;

    // h0033
    unsigned int /* padding 16 bit */:16;

    // h0034, bit: 4
    /* */
    #define offset_of_chiptop_reg_sd_ie (104)
    #define mask_of_chiptop_reg_sd_ie (0x1f)
    unsigned int reg_sd_ie:5;

    // h0034, bit: 7
    /* */
    unsigned int :3;

    // h0034, bit: 12
    /* */
    #define offset_of_chiptop_reg_sd_ps (104)
    #define mask_of_chiptop_reg_sd_ps (0x1f00)
    unsigned int reg_sd_ps:5;

    // h0034, bit: 14
    /* */
    unsigned int :3;

    // h0034
    unsigned int /* padding 16 bit */:16;

    // h0035, bit: 0
    /* PWM pad control*/
    #define offset_of_chiptop_reg_pwm0_drv (106)
    #define mask_of_chiptop_reg_pwm0_drv (0x1)
    unsigned int reg_pwm0_drv:1;

    // h0035, bit: 3
    /* */
    unsigned int :3;

    // h0035, bit: 5
    /* UART0 pad control*/
    #define offset_of_chiptop_reg_uart0_drv (106)
    #define mask_of_chiptop_reg_uart0_drv (0x30)
    unsigned int reg_uart0_drv:2;

    // h0035, bit: 7
    /* */
    unsigned int :2;

    // h0035, bit: 9
    /* UART1 pad control*/
    #define offset_of_chiptop_reg_uart1_drv (106)
    #define mask_of_chiptop_reg_uart1_drv (0x300)
    unsigned int reg_uart1_drv:2;

    // h0035, bit: 14
    /* */
    unsigned int :6;

    // h0035
    unsigned int /* padding 16 bit */:16;

    // h0036, bit: 14
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_lsh18_en (108)
    #define mask_of_chiptop_reg_sr_lsh18_en (0xffff)
    unsigned int reg_sr_lsh18_en:16;

    // h0036
    unsigned int /* padding 16 bit */:16;

    // h0037, bit: 1
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_lsh18_en_1 (110)
    #define mask_of_chiptop_reg_sr_lsh18_en_1 (0x3)
    unsigned int reg_sr_lsh18_en_1:2;

    // h0037, bit: 14
    /* */
    unsigned int :14;

    // h0037
    unsigned int /* padding 16 bit */:16;

    // h0038, bit: 14
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_ie (112)
    #define mask_of_chiptop_reg_sr_ie (0xffff)
    unsigned int reg_sr_ie:16;

    // h0038
    unsigned int /* padding 16 bit */:16;

    // h0039, bit: 1
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_ie_1 (114)
    #define mask_of_chiptop_reg_sr_ie_1 (0x3)
    unsigned int reg_sr_ie_1:2;

    // h0039, bit: 14
    /* */
    unsigned int :14;

    // h0039
    unsigned int /* padding 16 bit */:16;

    // h003a, bit: 14
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_pe (116)
    #define mask_of_chiptop_reg_sr_pe (0xffff)
    unsigned int reg_sr_pe:16;

    // h003a
    unsigned int /* padding 16 bit */:16;

    // h003b, bit: 1
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_pe_1 (118)
    #define mask_of_chiptop_reg_sr_pe_1 (0x3)
    unsigned int reg_sr_pe_1:2;

    // h003b, bit: 14
    /* */
    unsigned int :14;

    // h003b
    unsigned int /* padding 16 bit */:16;

    // h003c, bit: 14
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_ps (120)
    #define mask_of_chiptop_reg_sr_ps (0xffff)
    unsigned int reg_sr_ps:16;

    // h003c
    unsigned int /* padding 16 bit */:16;

    // h003d, bit: 1
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_ps_1 (122)
    #define mask_of_chiptop_reg_sr_ps_1 (0x3)
    unsigned int reg_sr_ps_1:2;

    // h003d, bit: 14
    /* */
    unsigned int :14;

    // h003d
    unsigned int /* padding 16 bit */:16;

    // h003e, bit: 14
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_drv (124)
    #define mask_of_chiptop_reg_sr_drv (0xffff)
    unsigned int reg_sr_drv:16;

    // h003e
    unsigned int /* padding 16 bit */:16;

    // h003f, bit: 1
    /* SR pad control*/
    #define offset_of_chiptop_reg_sr_drv_1 (126)
    #define mask_of_chiptop_reg_sr_drv_1 (0x3)
    unsigned int reg_sr_drv_1:2;

    // h003f, bit: 14
    /* */
    unsigned int :14;

    // h003f
    unsigned int /* padding 16 bit */:16;

    // h0040, bit: 14
    /* */
    unsigned int :16;

    // h0040
    unsigned int /* padding 16 bit */:16;

    // h0041, bit: 14
    /* */
    unsigned int :16;

    // h0041
    unsigned int /* padding 16 bit */:16;

    // h0042, bit: 14
    /* */
    unsigned int :16;

    // h0042
    unsigned int /* padding 16 bit */:16;

    // h0043, bit: 14
    /* */
    unsigned int :16;

    // h0043
    unsigned int /* padding 16 bit */:16;

    // h0044, bit: 14
    /* riu write clock mask
    [0]: sc_gp
    [1]: vhe_gp
    [2]: hemcu_gp
    [3]: mipi_gp
    [4]: mcu_if_gp
    [5]: others*/
    #define offset_of_chiptop_reg_riu_wclk_mask (136)
    #define mask_of_chiptop_reg_riu_wclk_mask (0xffff)
    unsigned int reg_riu_wclk_mask:16;

    // h0044
    unsigned int /* padding 16 bit */:16;

    // h0045, bit: 6
    /* */
    #define offset_of_chiptop_reg_lcd_ctrl_drv (138)
    #define mask_of_chiptop_reg_lcd_ctrl_drv (0x7f)
    unsigned int reg_lcd_ctrl_drv:7;

    // h0045, bit: 7
    /* */
    unsigned int :1;

    // h0045, bit: 14
    /* */
    #define offset_of_chiptop_reg_lcd_ctrl_ie (138)
    #define mask_of_chiptop_reg_lcd_ctrl_ie (0x7f00)
    unsigned int reg_lcd_ctrl_ie:7;

    // h0045, bit: 15
    /* */
    unsigned int :1;

    // h0045
    unsigned int /* padding 16 bit */:16;

    // h0046, bit: 6
    /* */
    #define offset_of_chiptop_reg_lcd_ctrl_pe (140)
    #define mask_of_chiptop_reg_lcd_ctrl_pe (0x7f)
    unsigned int reg_lcd_ctrl_pe:7;

    // h0046, bit: 7
    /* */
    unsigned int :1;

    // h0046, bit: 14
    /* */
    #define offset_of_chiptop_reg_lcd_ctrl_ps (140)
    #define mask_of_chiptop_reg_lcd_ctrl_ps (0x7f00)
    unsigned int reg_lcd_ctrl_ps:7;

    // h0046, bit: 15
    /* */
    unsigned int :1;

    // h0046
    unsigned int /* padding 16 bit */:16;

    // h0047, bit: 3
    /* */
    #define offset_of_chiptop_reg_lcd_time_drv (142)
    #define mask_of_chiptop_reg_lcd_time_drv (0xf)
    unsigned int reg_lcd_time_drv:4;

    // h0047, bit: 7
    /* */
    #define offset_of_chiptop_reg_lcd_time_ie (142)
    #define mask_of_chiptop_reg_lcd_time_ie (0xf0)
    unsigned int reg_lcd_time_ie:4;

    // h0047, bit: 11
    /* */
    #define offset_of_chiptop_reg_lcd_time_pe (142)
    #define mask_of_chiptop_reg_lcd_time_pe (0xf00)
    unsigned int reg_lcd_time_pe:4;

    // h0047, bit: 14
    /* */
    #define offset_of_chiptop_reg_lcd_time_ps (142)
    #define mask_of_chiptop_reg_lcd_time_ps (0xf000)
    unsigned int reg_lcd_time_ps:4;

    // h0047
    unsigned int /* padding 16 bit */:16;

    // h0048, bit: 14
    /* */
    #define offset_of_chiptop_reg_lcd_d_drv (144)
    #define mask_of_chiptop_reg_lcd_d_drv (0xffff)
    unsigned int reg_lcd_d_drv:16;

    // h0048
    unsigned int /* padding 16 bit */:16;

    // h0049, bit: 7
    /* */
    #define offset_of_chiptop_reg_lcd_d_drv_1 (146)
    #define mask_of_chiptop_reg_lcd_d_drv_1 (0xff)
    unsigned int reg_lcd_d_drv_1:8;

    // h0049, bit: 14
    /* */
    unsigned int :8;

    // h0049
    unsigned int /* padding 16 bit */:16;

    // h004a, bit: 14
    /* */
    #define offset_of_chiptop_reg_lcd_d_ie (148)
    #define mask_of_chiptop_reg_lcd_d_ie (0xffff)
    unsigned int reg_lcd_d_ie:16;

    // h004a
    unsigned int /* padding 16 bit */:16;

    // h004b, bit: 7
    /* */
    #define offset_of_chiptop_reg_lcd_d_ie_1 (150)
    #define mask_of_chiptop_reg_lcd_d_ie_1 (0xff)
    unsigned int reg_lcd_d_ie_1:8;

    // h004b, bit: 14
    /* */
    unsigned int :8;

    // h004b
    unsigned int /* padding 16 bit */:16;

    // h004c, bit: 14
    /* */
    #define offset_of_chiptop_reg_lcd_d_pe (152)
    #define mask_of_chiptop_reg_lcd_d_pe (0xffff)
    unsigned int reg_lcd_d_pe:16;

    // h004c
    unsigned int /* padding 16 bit */:16;

    // h004d, bit: 7
    /* */
    #define offset_of_chiptop_reg_lcd_d_pe_1 (154)
    #define mask_of_chiptop_reg_lcd_d_pe_1 (0xff)
    unsigned int reg_lcd_d_pe_1:8;

    // h004d, bit: 14
    /* */
    unsigned int :8;

    // h004d
    unsigned int /* padding 16 bit */:16;

    // h004e, bit: 14
    /* */
    #define offset_of_chiptop_reg_lcd_d_ps (156)
    #define mask_of_chiptop_reg_lcd_d_ps (0xffff)
    unsigned int reg_lcd_d_ps:16;

    // h004e
    unsigned int /* padding 16 bit */:16;

    // h004f, bit: 7
    /* */
    #define offset_of_chiptop_reg_lcd_d_ps_1 (158)
    #define mask_of_chiptop_reg_lcd_d_ps_1 (0xff)
    unsigned int reg_lcd_d_ps_1:8;

    // h004f, bit: 14
    /* */
    unsigned int :8;

    // h004f
    unsigned int /* padding 16 bit */:16;

    // h0050, bit: 14
    /* */
    unsigned int :15;

    // h0050, bit: 15
    /* 1: Set all pads (except PM) as input*/
    #define offset_of_chiptop_reg_allpad_in (160)
    #define mask_of_chiptop_reg_allpad_in (0x8000)
    unsigned int reg_allpad_in:1;

    // h0050
    unsigned int /* padding 16 bit */:16;

    // h0051, bit: 14
    /* */
    unsigned int :16;

    // h0051
    unsigned int /* padding 16 bit */:16;

    // h0052, bit: 14
    /* */
    unsigned int :16;

    // h0052
    unsigned int /* padding 16 bit */:16;

    // h0053, bit: 3
    /* Select controller for PAD_PM_UART_RX and PAD_PM_UART_TX
    0000:  N/A
    0001:  FUART
    0010:  UART0
    0011:  UART1
    Note: For PAD_PM_UART_RX and PAD_PM_UART_TX, please refer to the "reg_hk51_uart0_en" and "reg_uart_rx_enable" in reg_pm_sleep.xls
    (a). "reg_hk51_uart0_en" == 0
    (b). "reg_uart_rx_enable" == 1*/
    #define offset_of_chiptop_reg_uart_sel0 (166)
    #define mask_of_chiptop_reg_uart_sel0 (0xf)
    unsigned int reg_uart_sel0:4;

    // h0053, bit: 7
    /* Select controller for PAD_FUART_RX and PAD_FUART_TX*/
    #define offset_of_chiptop_reg_uart_sel1 (166)
    #define mask_of_chiptop_reg_uart_sel1 (0xf0)
    unsigned int reg_uart_sel1:4;

    // h0053, bit: 11
    /* Select controller for PAD_UART0_RX and PAD_UART0_TX*/
    #define offset_of_chiptop_reg_uart_sel2 (166)
    #define mask_of_chiptop_reg_uart_sel2 (0xf00)
    unsigned int reg_uart_sel2:4;

    // h0053, bit: 14
    /* Select controller for PAD_UART1_RX and PAD_UART1_TX*/
    #define offset_of_chiptop_reg_uart_sel3 (166)
    #define mask_of_chiptop_reg_uart_sel3 (0xf000)
    unsigned int reg_uart_sel3:4;

    // h0053
    unsigned int /* padding 16 bit */:16;

    // h0054, bit: 3
    /* Select controller for ?? (useless on iNfinity)*/
    #define offset_of_chiptop_reg_uart_sel4 (168)
    #define mask_of_chiptop_reg_uart_sel4 (0xf)
    unsigned int reg_uart_sel4:4;

    // h0054, bit: 14
    /* */
    unsigned int :12;

    // h0054
    unsigned int /* padding 16 bit */:16;

    // h0055, bit: 3
    /* JTAG selection (useless on iNfinity)*/
    #define offset_of_chiptop_reg_jtag_sel (170)
    #define mask_of_chiptop_reg_jtag_sel (0xf)
    unsigned int reg_jtag_sel:4;

    // h0055, bit: 7
    /* */
    unsigned int :4;

    // h0055, bit: 14
    /* invert PAD UART TX/RX*/
    #define offset_of_chiptop_reg_uart_pad_inverse (170)
    #define mask_of_chiptop_reg_uart_pad_inverse (0xff00)
    unsigned int reg_uart_pad_inverse:8;

    // h0055
    unsigned int /* padding 16 bit */:16;

    // h0056, bit: 7
    /* enable of inner loopback test for 3 sets of UART controller
    [0]: N/A
    [1]: FUART enable
    [2]: UART0 enable
    [3]: UART1 enable
    [4]~[7]: N/A*/
    #define offset_of_chiptop_reg_uart_inner_loopback (172)
    #define mask_of_chiptop_reg_uart_inner_loopback (0xff)
    unsigned int reg_uart_inner_loopback:8;

    // h0056, bit: 14
    /* enable of outer loopback test for 4 sets of UART pad
    [0]: PM_UART enable
    [1]: FUART enable
    [2]: UART0 enable
    [3]: UART1 enable
    [4]~[7]: N/A*/
    #define offset_of_chiptop_reg_uart_outer_loopback (172)
    #define mask_of_chiptop_reg_uart_outer_loopback (0xff00)
    unsigned int reg_uart_outer_loopback:8;

    // h0056
    unsigned int /* padding 16 bit */:16;

    // h0057, bit: 14
    /* disable RX signals from PADs*/
    #define offset_of_chiptop_reg_force_rx_disable (174)
    #define mask_of_chiptop_reg_force_rx_disable (0xffff)
    unsigned int reg_force_rx_disable:16;

    // h0057
    unsigned int /* padding 16 bit */:16;

    // h0058, bit: 5
    /* */
    #define offset_of_chiptop_reg_sd2pad_drv (176)
    #define mask_of_chiptop_reg_sd2pad_drv (0x3f)
    unsigned int reg_sd2pad_drv:6;

    // h0058, bit: 7
    /* */
    unsigned int :2;

    // h0058, bit: 13
    /* */
    #define offset_of_chiptop_reg_sd2pad_pe (176)
    #define mask_of_chiptop_reg_sd2pad_pe (0x3f00)
    unsigned int reg_sd2pad_pe:6;

    // h0058, bit: 14
    /* */
    unsigned int :2;

    // h0058
    unsigned int /* padding 16 bit */:16;

    // h0059, bit: 5
    /* */
    #define offset_of_chiptop_reg_sd2pad_ps (178)
    #define mask_of_chiptop_reg_sd2pad_ps (0x3f)
    unsigned int reg_sd2pad_ps:6;

    // h0059, bit: 14
    /* */
    unsigned int :10;

    // h0059
    unsigned int /* padding 16 bit */:16;

    // h005a, bit: 11
    /* */
    #define offset_of_chiptop_reg_snr0_d_drv (180)
    #define mask_of_chiptop_reg_snr0_d_drv (0xfff)
    unsigned int reg_snr0_d_drv:12;

    // h005a, bit: 14
    /* */
    unsigned int :4;

    // h005a
    unsigned int /* padding 16 bit */:16;

    // h005b, bit: 11
    /* */
    #define offset_of_chiptop_reg_snr0_d_ie (182)
    #define mask_of_chiptop_reg_snr0_d_ie (0xfff)
    unsigned int reg_snr0_d_ie:12;

    // h005b, bit: 14
    /* */
    unsigned int :4;

    // h005b
    unsigned int /* padding 16 bit */:16;

    // h005c, bit: 11
    /* */
    #define offset_of_chiptop_reg_snr0_d_pe (184)
    #define mask_of_chiptop_reg_snr0_d_pe (0xfff)
    unsigned int reg_snr0_d_pe:12;

    // h005c, bit: 14
    /* */
    unsigned int :4;

    // h005c
    unsigned int /* padding 16 bit */:16;

    // h005d, bit: 11
    /* */
    #define offset_of_chiptop_reg_snr0_d_ps (186)
    #define mask_of_chiptop_reg_snr0_d_ps (0xfff)
    unsigned int reg_snr0_d_ps:12;

    // h005d, bit: 14
    /* */
    unsigned int :4;

    // h005d
    unsigned int /* padding 16 bit */:16;

    // h005e, bit: 6
    /* */
    #define offset_of_chiptop_reg_snr0_io_drv (188)
    #define mask_of_chiptop_reg_snr0_io_drv (0x7f)
    unsigned int reg_snr0_io_drv:7;

    // h005e, bit: 7
    /* */
    unsigned int :1;

    // h005e, bit: 14
    /* */
    #define offset_of_chiptop_reg_snr0_io_ie (188)
    #define mask_of_chiptop_reg_snr0_io_ie (0x7f00)
    unsigned int reg_snr0_io_ie:7;

    // h005e, bit: 15
    /* */
    unsigned int :1;

    // h005e
    unsigned int /* padding 16 bit */:16;

    // h005f, bit: 6
    /* */
    #define offset_of_chiptop_reg_snr0_io_pe (190)
    #define mask_of_chiptop_reg_snr0_io_pe (0x7f)
    unsigned int reg_snr0_io_pe:7;

    // h005f, bit: 7
    /* */
    unsigned int :1;

    // h005f, bit: 14
    /* */
    #define offset_of_chiptop_reg_snr0_io_ps (190)
    #define mask_of_chiptop_reg_snr0_io_ps (0x7f00)
    unsigned int reg_snr0_io_ps:7;

    // h005f, bit: 15
    /* */
    unsigned int :1;

    // h005f
    unsigned int /* padding 16 bit */:16;

    // h0060, bit: 5
    /* */
    #define offset_of_chiptop_reg_snr1_d_drv (192)
    #define mask_of_chiptop_reg_snr1_d_drv (0x3f)
    unsigned int reg_snr1_d_drv:6;

    // h0060, bit: 7
    /* */
    unsigned int :2;

    // h0060, bit: 13
    /* */
    #define offset_of_chiptop_reg_snr1_d_ie (192)
    #define mask_of_chiptop_reg_snr1_d_ie (0x3f00)
    unsigned int reg_snr1_d_ie:6;

    // h0060, bit: 14
    /* */
    unsigned int :2;

    // h0060
    unsigned int /* padding 16 bit */:16;

    // h0061, bit: 5
    /* */
    #define offset_of_chiptop_reg_snr1_d_pe (194)
    #define mask_of_chiptop_reg_snr1_d_pe (0x3f)
    unsigned int reg_snr1_d_pe:6;

    // h0061, bit: 7
    /* */
    unsigned int :2;

    // h0061, bit: 13
    /* */
    #define offset_of_chiptop_reg_snr1_d_ps (194)
    #define mask_of_chiptop_reg_snr1_d_ps (0x3f00)
    unsigned int reg_snr1_d_ps:6;

    // h0061, bit: 14
    /* */
    unsigned int :2;

    // h0061
    unsigned int /* padding 16 bit */:16;

    // h0062, bit: 4
    /* */
    #define offset_of_chiptop_reg_snr1_io_drv (196)
    #define mask_of_chiptop_reg_snr1_io_drv (0x1f)
    unsigned int reg_snr1_io_drv:5;

    // h0062, bit: 7
    /* */
    unsigned int :3;

    // h0062, bit: 12
    /* */
    #define offset_of_chiptop_reg_snr1_io_ie (196)
    #define mask_of_chiptop_reg_snr1_io_ie (0x1f00)
    unsigned int reg_snr1_io_ie:5;

    // h0062, bit: 14
    /* */
    unsigned int :3;

    // h0062
    unsigned int /* padding 16 bit */:16;

    // h0063, bit: 4
    /* */
    #define offset_of_chiptop_reg_snr1_io_pe (198)
    #define mask_of_chiptop_reg_snr1_io_pe (0x1f)
    unsigned int reg_snr1_io_pe:5;

    // h0063, bit: 7
    /* */
    unsigned int :3;

    // h0063, bit: 12
    /* */
    #define offset_of_chiptop_reg_snr1_io_ps (198)
    #define mask_of_chiptop_reg_snr1_io_ps (0x1f00)
    unsigned int reg_snr1_io_ps:5;

    // h0063, bit: 14
    /* */
    unsigned int :3;

    // h0063
    unsigned int /* padding 16 bit */:16;

    // h0064, bit: 4
    /* */
    #define offset_of_chiptop_reg_spi0_drv0 (200)
    #define mask_of_chiptop_reg_spi0_drv0 (0x1f)
    unsigned int reg_spi0_drv0:5;

    // h0064, bit: 7
    /* */
    unsigned int :3;

    // h0064, bit: 8
    /* */
    #define offset_of_chiptop_reg_spi0_drv1 (200)
    #define mask_of_chiptop_reg_spi0_drv1 (0x100)
    unsigned int reg_spi0_drv1:1;

    // h0064, bit: 14
    /* */
    unsigned int :7;

    // h0064
    unsigned int /* padding 16 bit */:16;

    // h0065, bit: 5
    /* CHIP_CONFIG status*/
    #define offset_of_chiptop_reg_chip_config_stat (202)
    #define mask_of_chiptop_reg_chip_config_stat (0x3f)
    unsigned int reg_chip_config_stat:6;

    // h0065, bit: 7
    /* */
    unsigned int :2;

    // h0065, bit: 8
    /* in_sel_sbus*/
    #define offset_of_chiptop_reg_in_sel_sbus (202)
    #define mask_of_chiptop_reg_in_sel_sbus (0x100)
    unsigned int reg_in_sel_sbus:1;

    // h0065, bit: 9
    /* in_sel_dbus*/
    #define offset_of_chiptop_reg_in_sel_dbus (202)
    #define mask_of_chiptop_reg_in_sel_dbus (0x200)
    unsigned int reg_in_sel_dbus:1;

    // h0065, bit: 11
    /* */
    unsigned int :2;

    // h0065, bit: 12
    /* POWERGOOD_AVDD status*/
    #define offset_of_chiptop_reg_powergood_avdd (202)
    #define mask_of_chiptop_reg_powergood_avdd (0x1000)
    unsigned int reg_powergood_avdd:1;

    // h0065, bit: 14
    /* */
    unsigned int :3;

    // h0065
    unsigned int /* padding 16 bit */:16;

    // h0066, bit: 1
    /* */
    #define offset_of_chiptop_reg_uart0_ie (204)
    #define mask_of_chiptop_reg_uart0_ie (0x3)
    unsigned int reg_uart0_ie:2;

    // h0066, bit: 3
    /* */
    #define offset_of_chiptop_reg_uart0_pe (204)
    #define mask_of_chiptop_reg_uart0_pe (0xc)
    unsigned int reg_uart0_pe:2;

    // h0066, bit: 5
    /* */
    #define offset_of_chiptop_reg_uart0_ps (204)
    #define mask_of_chiptop_reg_uart0_ps (0x30)
    unsigned int reg_uart0_ps:2;

    // h0066, bit: 7
    /* */
    #define offset_of_chiptop_reg_uart1_ie (204)
    #define mask_of_chiptop_reg_uart1_ie (0xc0)
    unsigned int reg_uart1_ie:2;

    // h0066, bit: 9
    /* */
    #define offset_of_chiptop_reg_uart1_pe (204)
    #define mask_of_chiptop_reg_uart1_pe (0x300)
    unsigned int reg_uart1_pe:2;

    // h0066, bit: 11
    /* */
    #define offset_of_chiptop_reg_uart1_ps (204)
    #define mask_of_chiptop_reg_uart1_ps (0xc00)
    unsigned int reg_uart1_ps:2;

    // h0066, bit: 13
    /* */
    #define offset_of_chiptop_reg_fuart_drv (204)
    #define mask_of_chiptop_reg_fuart_drv (0x3000)
    unsigned int reg_fuart_drv:2;

    // h0066, bit: 14
    /* */
    unsigned int :2;

    // h0066
    unsigned int /* padding 16 bit */:16;

    // h0067, bit: 2
    /* when pad operate at input mode
    0: pull disable, 1: pull enable*/
    #define offset_of_chiptop_reg_spi0_pe (206)
    #define mask_of_chiptop_reg_spi0_pe (0x7)
    unsigned int reg_spi0_pe:3;

    // h0067, bit: 3
    /* */
    unsigned int :1;

    // h0067, bit: 6
    /* 0: pull down, 1: pull up*/
    #define offset_of_chiptop_reg_spi0_ps (206)
    #define mask_of_chiptop_reg_spi0_ps (0x70)
    unsigned int reg_spi0_ps:3;

    // h0067, bit: 7
    /* */
    unsigned int :1;

    // h0067, bit: 10
    /* */
    #define offset_of_chiptop_reg_spi0_ie (206)
    #define mask_of_chiptop_reg_spi0_ie (0x700)
    unsigned int reg_spi0_ie:3;

    // h0067, bit: 14
    /* */
    unsigned int :5;

    // h0067
    unsigned int /* padding 16 bit */:16;

    // h0068, bit: 14
    /* */
    unsigned int :16;

    // h0068
    unsigned int /* padding 16 bit */:16;

    // h0069, bit: 10
    /* */
    unsigned int :11;

    // h0069, bit: 11
    /* boot from SDRAM
    1: enable boot from SDRAM
    0: disable boot from SDRAM*/
    #define offset_of_chiptop_reg_boot_from_sdram (210)
    #define mask_of_chiptop_reg_boot_from_sdram (0x800)
    unsigned int reg_boot_from_sdram:1;

    // h0069, bit: 14
    /* */
    unsigned int :4;

    // h0069
    unsigned int /* padding 16 bit */:16;

    // h006a, bit: 14
    /* The booting address of SDRAM*/
    #define offset_of_chiptop_reg_boot_from_sdram_offset (212)
    #define mask_of_chiptop_reg_boot_from_sdram_offset (0xffff)
    unsigned int reg_boot_from_sdram_offset:16;

    // h006a
    unsigned int /* padding 16 bit */:16;

    // h006b, bit: 9
    /* The booting address of SDRAM*/
    #define offset_of_chiptop_reg_boot_from_sdram_offset_1 (214)
    #define mask_of_chiptop_reg_boot_from_sdram_offset_1 (0x3ff)
    unsigned int reg_boot_from_sdram_offset_1:10;

    // h006b, bit: 14
    /* */
    unsigned int :6;

    // h006b
    unsigned int /* padding 16 bit */:16;

    // h006c, bit: 14
    /* */
    unsigned int :16;

    // h006c
    unsigned int /* padding 16 bit */:16;

    // h006d, bit: 14
    /* */
    unsigned int :16;

    // h006d
    unsigned int /* padding 16 bit */:16;

    // h006e, bit: 14
    /* */
    unsigned int :16;

    // h006e
    unsigned int /* padding 16 bit */:16;

    // h006f, bit: 14
    /* */
    unsigned int :16;

    // h006f
    unsigned int /* padding 16 bit */:16;

    // h0070, bit: 7
    /* */
    unsigned int :8;

    // h0070, bit: 10
    /* ring OSC output select
    000: select delay chain 0
    001: select delay chain 1
    010: select delay chain 2
    011: select delay chain 3
    100: select delay chain 4
    101: select delay chain 5
    110: select delay chain 6
    111: select delay chain 7*/
    #define offset_of_chiptop_reg_rosc_out_sel (224)
    #define mask_of_chiptop_reg_rosc_out_sel (0x700)
    unsigned int reg_rosc_out_sel:3;

    // h0070, bit: 14
    /* */
    unsigned int :4;

    // h0070, bit: 15
    /* reg_clk_calc_en
    1:enable
    0:disable*/
    #define offset_of_chiptop_reg_clk_calc_en (224)
    #define mask_of_chiptop_reg_clk_calc_en (0x8000)
    unsigned int reg_clk_calc_en:1;

    // h0070
    unsigned int /* padding 16 bit */:16;

    // h0071, bit: 14
    /* reg_calc_cnt_report*/
    #define offset_of_chiptop_reg_calc_cnt_report (226)
    #define mask_of_chiptop_reg_calc_cnt_report (0xffff)
    unsigned int reg_calc_cnt_report:16;

    // h0071
    unsigned int /* padding 16 bit */:16;

    // h0072, bit: 14
    /* */
    unsigned int :16;

    // h0072
    unsigned int /* padding 16 bit */:16;

    // h0073, bit: 14
    /* Reserved register*/
    #define offset_of_chiptop_reg_reserved (230)
    #define mask_of_chiptop_reg_reserved (0xffff)
    unsigned int reg_reserved:16;

    // h0073
    unsigned int /* padding 16 bit */:16;

    // h0074, bit: 14
    /* Reserved register*/
    #define offset_of_chiptop_reg_reserved_1 (232)
    #define mask_of_chiptop_reg_reserved_1 (0xffff)
    unsigned int reg_reserved_1:16;

    // h0074
    unsigned int /* padding 16 bit */:16;

    // h0075, bit: 2
    /* select TEST_CLK_OUT source
    3'd0: TEST_CLK_OUT= TEST_BUS_GB[0]
    3'd1: TEST_CLK_OUT= TEST_BUS_GB[1]
    3'd2: TEST_CLK_OUT= TEST_BUS_GB[2]
    3'd3: TEST_CLK_OUT= TEST_BUS_GB[3]
    3'd4: TEST_CLK_OUT= TEST_BUS_GB[4]
    3'd5: TEST_CLK_OUT= TEST_BUS_GB[5]
    3'd6: TEST_CLK_OUT= TEST_BUS_GB[6]
    3'd7: TEST_CLK_OUT= TEST_BUS_GB[7]*/
    #define offset_of_chiptop_reg_clk_out_sel (234)
    #define mask_of_chiptop_reg_clk_out_sel (0x7)
    unsigned int reg_clk_out_sel:3;

    // h0075, bit: 3
    /* swap MSB 12bits with LSB 12bits of test bus*/
    #define offset_of_chiptop_reg_swaptest12bit     (234)
    #define mask_of_chiptop_reg_swaptest12bit     (0x8)
    unsigned int reg_swaptest12bit    :1;

    // h0075, bit: 4
    /* */
    unsigned int :1;

    // h0075, bit: 5
    /* setting for the data arrangement on test bus*/
    #define offset_of_chiptop_reg_test_rg            (234)
    #define mask_of_chiptop_reg_test_rg            (0x20)
    unsigned int reg_test_rg           :1;

    // h0075, bit: 6
    /* setting for the data arrangement on test bus*/
    #define offset_of_chiptop_reg_test_gb              (234)
    #define mask_of_chiptop_reg_test_gb              (0x40)
    unsigned int reg_test_gb             :1;

    // h0075, bit: 7
    /* setting for the data arrangement on test bus*/
    #define offset_of_chiptop_reg_test_rb           (234)
    #define mask_of_chiptop_reg_test_rb           (0x80)
    unsigned int reg_test_rb          :1;

    // h0075, bit: 9
    /* select CLK_TEST_OUT
    2'd0:  select CLK_TEST_OUT[47:0]
    2'd1:  select CLK_TEST_OUT[95:48]
    2'd2:  select CLK_TEST_OUT[143:96]
    2'd3:  reserved*/
    #define offset_of_chiptop_reg_sel_clk_test_out     (234)
    #define mask_of_chiptop_reg_sel_clk_test_out     (0x300)
    unsigned int reg_sel_clk_test_out    :2;

    // h0075, bit: 12
    /* */
    unsigned int :3;

    // h0075, bit: 13
    /* testCLK_mode used in TEST_CTRL*/
    #define offset_of_chiptop_reg_testclk_mode           (234)
    #define mask_of_chiptop_reg_testclk_mode           (0x2000)
    unsigned int reg_testclk_mode          :1;

    // h0075, bit: 14
    /* Enable test bus output (disable in default)*/
    #define offset_of_chiptop_reg_testbus_en   (234)
    #define mask_of_chiptop_reg_testbus_en   (0x4000)
    unsigned int reg_testbus_en  :1;

    // h0075, bit: 15
    /* Select the input source of ring oscillator in CHIP_CONF
    1: close-loop (enable ring oscillator)
    0: open-loop (input from external digital input)*/
    #define offset_of_chiptop_reg_rosc_in_sel (234)
    #define mask_of_chiptop_reg_rosc_in_sel (0x8000)
    unsigned int reg_rosc_in_sel:1;

    // h0075
    unsigned int /* padding 16 bit */:16;

    // h0076, bit: 2
    /* select single CLK_OUT
    3'd1: TEST_BUS[11] = TEST_CLK_OUT_d2
            TEST_BUS[10] = TEST_CLK_OUT
    3'd2: TEST_BUS[11] = TEST_CLK_OUT_d2
            TEST_BUS[10] = TEST_CLK_OUT_d4
    3'd3: TEST_BUS[11] = TEST_CLK_OUT_d2.
            TEST_BUS[10] = TEST_CLK_OUT_d8
    3'd4: TEST_BUS[11] = TEST_CLK_OUT_d2
            TEST_BUS[10] = TEST_CLK_OUT_d16
    3'd5: TEST_BUS[11] = TEST_CLK_OUT_d2
            TEST_BUS[10] = TEST_CLK_OUT_d32
    3'd6: TEST_BUS[11] = TEST_CLK_OUT_d2
            TEST_BUS[10] = TEST_CLK_OUT_d64
    Others: no TEST_CLK_OUT*/
    #define offset_of_chiptop_reg_single_clk_out_sel     (236)
    #define mask_of_chiptop_reg_single_clk_out_sel     (0x7)
    unsigned int reg_single_clk_out_sel    :3;

    // h0076, bit: 14
    /* */
    unsigned int :13;

    // h0076
    unsigned int /* padding 16 bit */:16;

    // h0077, bit: 5
    /* select TEST_BUS[23:0] source
    6'd2: TEST_BUS = ANA_MISC_TEST_OUT
    6'd3: TEST_BUS = MIU_TEST_OUT
    6'd4: TEST_BUS = DIAMOND_TOP_WP_TEST_OUT
    6'd7: TEST_BUS = UTMI_TEST_OUT
    6'd8: TEST_BUS = AUSDM_TEST_OUT
    6'd9: TEST_BUS = DIG_PM_TEST_OUT
    6'd10: TEST_BUS = MCU_IF_TEST_OUT
    6'd11: TEST_BUS = MIPI_TEST_OUT
    6'd12: TEST_BUS = MIPI_TEST_OUT
    6'd16: TEST_BUS = SC_GP_TEST_OUT
    6'd17: TEST_BUS = VHE_TEST_OUT
    6'd25: TEST_BUS = CLKGEN_TEST_OUT
    Others: no TEST_OUT*/
    #define offset_of_chiptop_reg_test_bus24b_sel       (238)
    #define mask_of_chiptop_reg_test_bus24b_sel       (0x3f)
    unsigned int reg_test_bus24b_sel      :6;

    // h0077, bit: 14
    /* */
    unsigned int :10;

    // h0077
    unsigned int /* padding 16 bit */:16;

    // h0078, bit: 14
    /* */
    unsigned int :16;

    // h0078
    unsigned int /* padding 16 bit */:16;

    // h0079, bit: 14
    /* */
    unsigned int :16;

    // h0079
    unsigned int /* padding 16 bit */:16;

    // h007a, bit: 14
    /* */
    unsigned int :16;

    // h007a
    unsigned int /* padding 16 bit */:16;

    // h007b, bit: 14
    /* */
    #define offset_of_chiptop_reg_chiptop_reserved (246)
    #define mask_of_chiptop_reg_chiptop_reserved (0xffff)
    unsigned int reg_chiptop_reserved:16;

    // h007b
    unsigned int /* padding 16 bit */:16;

    // h007c, bit: 14
    /* */
    #define offset_of_chiptop_reg_chk_clk_hemcu_freq_cmp_data (248)
    #define mask_of_chiptop_reg_chk_clk_hemcu_freq_cmp_data (0xffff)
    unsigned int reg_chk_clk_hemcu_freq_cmp_data:16;

    // h007c
    unsigned int /* padding 16 bit */:16;

    // h007d, bit: 3
    /* 256bus miu 2x div enable*/
    #define offset_of_chiptop_reg_256bus_2x_div_en (250)
    #define mask_of_chiptop_reg_256bus_2x_div_en (0xf)
    unsigned int reg_256bus_2x_div_en:4;

    // h007d, bit: 14
    /* */
    unsigned int :12;

    // h007d
    unsigned int /* padding 16 bit */:16;

    // h007e, bit: 3
    /* clk_miu2x_div sw rstz
    [0]: MIU0
    [3:1]: Reserved*/
    #define offset_of_chiptop_reg_miu2x_div_rstz (252)
    #define mask_of_chiptop_reg_miu2x_div_rstz (0xf)
    unsigned int reg_miu2x_div_rstz:4;

    // h007e, bit: 14
    /* */
    unsigned int :12;

    // h007e
    unsigned int /* padding 16 bit */:16;

    // h007f, bit: 14
    /* */
    unsigned int :16;

    // h007f
    unsigned int /* padding 16 bit */:16;

}  __attribute__((packed, aligned(1))) CHIPTOP_t;

extern volatile CHIPTOP_t * const g_ptCHIPTOP;

#endif
