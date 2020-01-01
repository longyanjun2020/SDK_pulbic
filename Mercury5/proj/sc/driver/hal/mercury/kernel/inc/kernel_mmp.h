#ifndef __KERNEL_MMP_H__
#define __KERNEL_MMP_H__

/************************************************/
/* RIU MMP Bank                                 */
/************************************************/

typedef struct KeMmp_s
{
    /* [0x00] */
    u32 reg_rq00_type                 :2 ; /// arb_pre rq00 type setting
    u32 reg_rq01_type                 :2 ; /// arb_pre rq01 type setting
    u32 reg_rq02_type                 :2 ; /// arb_pre rq02 type setting
    u32 reg_rq03_type                 :2 ; /// arb_pre rq03 type setting
    u32 reg_rq04_type                 :2 ; /// arb_pre rq04 type setting
    u32 reg_rq05_type                 :2 ; /// arb_pre rq05 type setting
    u32 reg_rq06_type                 :2 ; /// arb_pre rq06 type setting
    u32 reg_rq07_type                 :2 ; /// arb_pre rq07 type setting
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_rq08_type                 :2 ; /// arb_pre rq08 type setting
    u32 reg_rq09_type                 :2 ; /// arb_pre rq09 type setting
    u32 reg_rq10_type                 :2 ; /// arb_pre rq10 type setting
    u32 reg_rq11_type                 :2 ; /// arb_pre rq11 type setting
    u32 reg_rq12_type                 :2 ; /// arb_pre rq12 type setting
    u32 reg_rq13_type                 :2 ; /// arb_pre rq13 type setting
    u32 reg_rq14_type                 :2 ; /// arb_pre rq14 type setting
    u32 reg_rq15_type                 :2 ; /// arb_pre rq15 type setting
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_pre4_garb1_0_sel          :1 ; /// Select the client for pre_arb:
                                           /// 00: MPIF
                                           /// 01: GARB_TEST
    u32 reg_garb_test_en_sel          :1 ; /// reg_garb_test_en_sel
    u32 reg_rq16_type                 :2 ; /// arb_pre rq16 type setting
    u32 reg_rq17_type                 :2 ; /// arb_pre rq17 type setting
    u32 reg_rq18_type                 :2 ; /// arb_pre rq18 type setting
    u32 reg_rq19_type                 :2 ; /// arb_pre rq19 type setting
    u32 :22; /// [0x02]
    /* [0x03] */
    u32 reg_clk_miu_en                :16; /// clk_miu enable 
                                           /// [0] : clk_miu_disp
                                           /// [1]: clk_miu_otg20
                                           /// [2]: reserved
                                           /// [3]:clk_miu_jpde
                                           /// [4]: clk_miu_ds
                                           /// [5]: clk_miu_camscl
                                           /// [6]: clk_miu_fcie
                                           /// [7]: clk_miu_sdio
                                           /// [8]: clk_miu_dma2d
                                           /// [9]: clk_miu_bt
                                           /// [10]: clk_miu_bach
                                           /// [11]: clk_miu_adcdma
                                           /// [12]: clk_miu_gdma
                                           /// [13]: clk_miu_i2c
                                           /// [15:14] reserved
    u32 :16; /// [0x03]
    /* [0x04] */
    u32 reg_dbbus_sel                 :5 ; /// debug bus selection
    u32 :27; /// [0x04]
    /* [0x05] */
    u32 reg_garb_imi2_rq2mi_type      :16; /// imi2 group arbitor type setting
                                           /// [1:0] : rq2mi0_type
                                           /// [3:2] : rq2mi1_type
                                           /// [5:4] : rq2mi2_type
                                           /// [7:6] : rq2mi3_type
                                           /// [9:8] : rq2mi4_type
                                           /// [11:10] : rq2mi5_type
                                           /// [13:12] : rq2mi6_type
                                           /// [15:14] : rq2mi7_type
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_rf_tx_dpa_test_mode       :1 ; /// switch DMA2D miu write bus 
    u32 :31; /// [0x06]
    /* [0x07] */
    u32 reg_mmp_spare                 :16; /// spare register
    u32 :16; /// [0x07]
    u32 :32; /// [0x08]
    u32 :32; /// [0x09]
    u32 :32; /// [0x0A]
    u32 :32; /// [0x0B]
    u32 :32; /// [0x0C]
    u32 :32; /// [0x0D]
    u32 :32; /// [0x0E]
    u32 :32; /// [0x0F]
    u32 :32; /// [0x10]
    u32 :32; /// [0x11]
    u32 :32; /// [0x12]
    u32 :32; /// [0x13]
    u32 :32; /// [0x14]
    u32 :32; /// [0x15]
    u32 :32; /// [0x16]
    u32 :32; /// [0x17]
    u32 :32; /// [0x18]
    u32 :32; /// [0x19]
    u32 :32; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    u32 :32; /// [0x1F]
    u32 :32; /// [0x20]
    u32 :32; /// [0x21]
    u32 :32; /// [0x22]
    u32 :32; /// [0x23]
    u32 :32; /// [0x24]
    u32 :32; /// [0x25]
    u32 :32; /// [0x26]
    u32 :32; /// [0x27]
    u32 :32; /// [0x28]
    u32 :32; /// [0x29]
    u32 :32; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    u32 :32; /// [0x30]
    u32 :32; /// [0x31]
    u32 :32; /// [0x32]
    u32 :32; /// [0x33]
    u32 :32; /// [0x34]
    u32 :32; /// [0x35]
    u32 :32; /// [0x36]
    u32 :32; /// [0x37]
    u32 :32; /// [0x38]
    u32 :32; /// [0x39]
    u32 :32; /// [0x3A]
    u32 :32; /// [0x3B]
    u32 :32; /// [0x3C]
    u32 :32; /// [0x3D]
    u32 :32; /// [0x3E]
    u32 :32; /// [0x3F]
    u32 :32; /// [0x40]
    u32 :32; /// [0x41]
    u32 :32; /// [0x42]
    u32 :32; /// [0x43]
    u32 :32; /// [0x44]
    u32 :32; /// [0x45]
    u32 :32; /// [0x46]
    u32 :32; /// [0x47]
    u32 :32; /// [0x48]
    u32 :32; /// [0x49]
    u32 :32; /// [0x4A]
    u32 :32; /// [0x4B]
    u32 :32; /// [0x4C]
    u32 :32; /// [0x4D]
    u32 :32; /// [0x4E]
    u32 :32; /// [0x4F]
    u32 :32; /// [0x50]
    u32 :32; /// [0x51]
    u32 :32; /// [0x52]
    u32 :32; /// [0x53]
    u32 :32; /// [0x54]
    u32 :32; /// [0x55]
    u32 :32; /// [0x56]
    u32 :32; /// [0x57]
    u32 :32; /// [0x58]
    u32 :32; /// [0x59]
    u32 :32; /// [0x5A]
    u32 :32; /// [0x5B]
    u32 :32; /// [0x5C]
    u32 :32; /// [0x5D]
    u32 :32; /// [0x5E]
    u32 :32; /// [0x5F]
    u32 :32; /// [0x60]
    u32 :32; /// [0x61]
    u32 :32; /// [0x62]
    u32 :32; /// [0x63]
    u32 :32; /// [0x64]
    u32 :32; /// [0x65]
    u32 :32; /// [0x66]
    u32 :32; /// [0x67]
    u32 :32; /// [0x68]
    u32 :32; /// [0x69]
    u32 :32; /// [0x6A]
    u32 :32; /// [0x6B]
    u32 :32; /// [0x6C]
    u32 :32; /// [0x6D]
    u32 :32; /// [0x6E]
    u32 :32; /// [0x6F]
    /* [0x70] */
    u32 reg_garb_test_en              :1 ; /// miu self test enable
    u32 reg_garb_test_mode            :2 ; /// miu self test mode
                                           /// 00 : address mode
                                           /// 01 : from reg_test_data
                                           /// 10 : shift data
                                           /// 11 : address mode + data toggle
    u32 reg_garb_test_inv_data        :1 ; /// invers test data
    u32 reg_garb_test_loop            :1 ; /// loop mode
    u32 :3 ; /// [0x70]
    u32 reg_garb_test_read_only       :1 ; /// only issue read command
    u32 reg_garb_test_write_only      :1 ; /// only issue write command
    u32 reg_garb_test_byte            :2 ; /// read back data byte switch
    u32 :1 ; /// [0x70]
    u32 reg_garb_test_flag            :1 ; /// test fail indicator
    u32 reg_garb_test_fail            :1 ; /// test fail indicator
    u32 reg_garb_test_finish          :1 ; /// test finish indicator
    u32 :16; /// [0x70]
    /* [0x71] */
    u32 reg_garb_test_base            :16; /// test base address
    u32 :16; /// [0x71]
    /* [0x72] */
    u32 reg_garb_test_length_0        :16; /// test length
    u32 :16; /// [0x72]
    u32 reg_garb_test_length_1        :8 ; /// @see reg_garb_test_length_0
    u32 reg_garb_test_mask            :8 ; /// test data mask
    u32 :16; /// [0x73]
    /* [0x74] */
    u32 reg_garb_test_data            :16; /// test data
    u32 :16; /// [0x74]
    /* [0x75] */
    u32 reg_garb_test_status          :16; /// test status
    u32 :16; /// [0x75]
    /* [0x76] */
    u32 reg_garb_test_byte_fail       :16; /// test byte fail
    u32 :16; /// [0x76]
    /* [0x77] */
    u32 reg_garb_test_bit_fail        :16; /// test bit fail
    u32 :16; /// [0x77]
    /* [0x78] */
    u32 reg_garb_test_base_h          :8 ; /// test base address high byte [32:24]
    u32 reg_ana_bist_en               :1 ; /// grab bist enable
} KeMmp_t;

typedef enum
{
    E_CLK_MIU_EN_DISP    = 0,
    E_CLK_MIU_EN_OTG20   = 1,
    E_CLK_MIU_EN_RESERVED    = 2,
    E_CLK_MIU_EN_JPDE    = 3,
    E_CLK_MIU_EN_DS      = 4,
    E_CLK_MIU_EN_CAMSCL  = 5,
    E_CLK_MIU_EN_FCIE    = 6,
    E_CLK_MIU_EN_SDIO    = 7,
    E_CLK_MIU_EN_DMA2D   = 8,
    E_CLK_MIU_EN_BT      = 9,
    E_CLK_MIU_EN_BACH    = 10,
    E_CLK_MIU_EN_ADC_DMA = 11,
    E_CLK_MIU_EN_GDMA = 12,
    E_CLK_MIU_EN_I2C = 13,

    E_CLK_MIU_EN_MAX     = 14,
} ClkMiuEn_e;

/// the value is matched to register setting
typedef enum
{
    E_GARB_TEST_MODE_ADDR_TOGGLE    = 0,
    E_GARB_TEST_MODE_TEST_DATA      = 1,
    E_GARB_TEST_MODE_SHIFT_DATA     = 2,
    E_GARB_TEST_MODE_BOTH_TOGGLE    = 3,
} eGarbTestMode;

extern volatile KeMmp_t * const g_ptKeMmp;

#endif /*__KERNEL_MMP_H__*/
