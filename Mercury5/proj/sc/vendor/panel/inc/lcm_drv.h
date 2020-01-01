/*
* Copyright (C) 2011-2014 MediaTek Inc.
*
* This program is free software: you can redistribute it and/or modify it under the terms of the
* GNU General Public License version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with this program.
* If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __LCM_DRV_H__
#define __LCM_DRV_H__
// ---------------------------------------------------------------------------
#ifndef ARY_SIZE
#define ARY_SIZE(x) (sizeof((x)) / sizeof((x[0])))
#endif
#ifndef MAX_LCM_CNT
#define MAX_LCM_CNT 10
#endif
#ifndef MAX_VAR_CNT
#define MAX_VAR_CNT 2
#endif
#ifndef MAX_INIT_CNT
#define MAX_INIT_CNT 256
#endif
// ---------------------------------------------------------------------------
/* common enumerations */
typedef enum
{
    LCM_TYPE_DBI = 0,
    LCM_TYPE_DPI,
    LCM_TYPE_DSI
} LCM_TYPE;

typedef enum
{
    LCM_CTRL_NONE = 0,
    LCM_CTRL_SERIAL_DBI,
    LCM_CTRL_PARALLEL_DBI,
    LCM_CTRL_GPIO
} LCM_CTRL;

typedef enum
{
    LCM_COLOR_ORDER_RGB = 0,
    LCM_COLOR_ORDER_BGR = 1
} LCM_COLOR_ORDER;

/* DSI related enumerations */
typedef enum
{
    CMD_MODE = 0,
    SYNC_PULSE_VDO_MODE = 1,
    SYNC_EVENT_VDO_MODE = 2,
    BURST_VDO_MODE = 3
} LCM_DSI_MODE_CON;
typedef enum
{
    LCM_ONE_LANE = 1,
    LCM_TWO_LANE = 2,
    LCM_THREE_LANE = 3,
    LCM_FOUR_LANE = 4,
} LCM_LANE_NUM;
typedef enum
{
    LCM_DSI_FORMAT_RGB565 = 0,
    LCM_DSI_FORMAT_RGB666 = 1,
    LCM_DSI_FORMAT_RGB888 = 2
} LCM_DSI_FORMAT;
typedef enum
{
    LCM_DSI_TRANS_SEQ_MSB_FIRST = 0,
    LCM_DSI_TRANS_SEQ_LSB_FIRST = 1
} LCM_DSI_TRANS_SEQ;
typedef enum
{
    LCM_DSI_PADDING_ON_LSB = 0,
    LCM_DSI_PADDING_ON_MSB = 1
} LCM_DSI_PADDING;
typedef enum
{
    LCM_PACKED_PS_16BIT_RGB565=0,
    LCM_LOOSELY_PS_18BIT_RGB666=1,
    LCM_PACKED_PS_24BIT_RGB888=2,
    LCM_PACKED_PS_18BIT_RGB666=3
} LCM_PS_TYPE;
typedef enum
{
    LCM_DSI_6589_PLL_CLOCK_NULL      = 0,
    LCM_DSI_6589_PLL_CLOCK_201_5  = 1,
    LCM_DSI_6589_PLL_CLOCK_208      = 2,
    LCM_DSI_6589_PLL_CLOCK_214_5  = 3,
    LCM_DSI_6589_PLL_CLOCK_221      = 4,
    LCM_DSI_6589_PLL_CLOCK_227_5  = 5,
    LCM_DSI_6589_PLL_CLOCK_234      = 6,
    LCM_DSI_6589_PLL_CLOCK_240_5  = 7,
    LCM_DSI_6589_PLL_CLOCK_247      = 8,
    LCM_DSI_6589_PLL_CLOCK_253_5  = 9,
    LCM_DSI_6589_PLL_CLOCK_260      = 10,
    LCM_DSI_6589_PLL_CLOCK_266_5  = 11,
    LCM_DSI_6589_PLL_CLOCK_273      = 12,
    LCM_DSI_6589_PLL_CLOCK_279_5  = 13,
    LCM_DSI_6589_PLL_CLOCK_286      = 14,
    LCM_DSI_6589_PLL_CLOCK_292_5  = 15,
    LCM_DSI_6589_PLL_CLOCK_299      = 16,
    LCM_DSI_6589_PLL_CLOCK_305_5  = 17,
    LCM_DSI_6589_PLL_CLOCK_312      = 18,
    LCM_DSI_6589_PLL_CLOCK_318_5  = 19,
    LCM_DSI_6589_PLL_CLOCK_325      = 20,
    LCM_DSI_6589_PLL_CLOCK_331_5  = 21,
    LCM_DSI_6589_PLL_CLOCK_338      = 22,
    LCM_DSI_6589_PLL_CLOCK_344_5  = 23,
    LCM_DSI_6589_PLL_CLOCK_351      = 24,
    LCM_DSI_6589_PLL_CLOCK_357_5  = 25,
    LCM_DSI_6589_PLL_CLOCK_364      = 26,
    LCM_DSI_6589_PLL_CLOCK_370_5  = 27,
    LCM_DSI_6589_PLL_CLOCK_377      = 28,
    LCM_DSI_6589_PLL_CLOCK_383_5  = 29,
    LCM_DSI_6589_PLL_CLOCK_390      = 30,
    LCM_DSI_6589_PLL_CLOCK_396_5  = 31,
    LCM_DSI_6589_PLL_CLOCK_403      = 32,
    LCM_DSI_6589_PLL_CLOCK_409_5  = 33,
    LCM_DSI_6589_PLL_CLOCK_416      = 34,
    LCM_DSI_6589_PLL_CLOCK_422_5  = 35,
    LCM_DSI_6589_PLL_CLOCK_429      = 36,
    LCM_DSI_6589_PLL_CLOCK_435_5  = 37,
    LCM_DSI_6589_PLL_CLOCK_442      = 38,
    LCM_DSI_6589_PLL_CLOCK_448_5  = 39,
    LCM_DSI_6589_PLL_CLOCK_455      = 40,
    LCM_DSI_6589_PLL_CLOCK_461_5  = 41,
    LCM_DSI_6589_PLL_CLOCK_468      = 42,
    LCM_DSI_6589_PLL_CLOCK_474_5  = 43,
    LCM_DSI_6589_PLL_CLOCK_481      = 44,
    LCM_DSI_6589_PLL_CLOCK_487_5  = 45,
    LCM_DSI_6589_PLL_CLOCK_494      = 46,
    LCM_DSI_6589_PLL_CLOCK_500_5  = 47,
    LCM_DSI_6589_PLL_CLOCK_507      = 48,
    LCM_DSI_6589_PLL_CLOCK_513_5  = 49,
    LCM_DSI_6589_PLL_CLOCK_520      = 50,
} LCM_DSI_PLL_CLOCK;
// ---------------------------------------------------------------------------


typedef struct
{
    LCM_COLOR_ORDER color_order;
    LCM_DSI_TRANS_SEQ trans_seq;
    LCM_DSI_PADDING padding;
    LCM_DSI_FORMAT format;
} LCM_DSI_DATA_FORMAT;
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
typedef struct
{
    LCM_DSI_MODE_CON     mode;
    unsigned int        DSI_WMEM_CONTI;
    unsigned int        DSI_RMEM_CONTI;
    unsigned int        VC_NUM;
    LCM_LANE_NUM        LANE_NUM;
    LCM_DSI_DATA_FORMAT    data_format;
    /* intermediate buffers parameters */
    unsigned int         intermediat_buffer_num; // 2..3
    LCM_PS_TYPE            PS;
    unsigned int        word_count;
    unsigned int        packet_size;
    unsigned int        vertical_sync_active;
    unsigned int        vertical_backporch;
    unsigned int        vertical_frontporch;
    unsigned int        vertical_active_line;
    unsigned int        horizontal_sync_active;
    unsigned int        horizontal_backporch;
    unsigned int        horizontal_frontporch;
    unsigned int        horizontal_blanking_pixel;
    unsigned int        horizontal_active_pixel;
    unsigned int        horizontal_bllp;
    unsigned int        line_byte;
    unsigned int        horizontal_sync_active_byte;
    unsigned int        horizontal_backporch_byte;
    unsigned int        horizontal_frontporch_byte;
    unsigned int        rgb_byte;
    unsigned int        horizontal_sync_active_word_count;
    unsigned int        horizontal_backporch_word_count;
    unsigned int        horizontal_frontporch_word_count;
    unsigned char        HS_TRAIL;
    unsigned char        HS_ZERO;
    unsigned char        HS_PRPR;
    unsigned char        LPX;
    unsigned char        TA_SACK;
    unsigned char        TA_GET;
    unsigned char        TA_SURE;
    unsigned char        TA_GO;
    unsigned char        CLK_TRAIL;
    unsigned char        CLK_ZERO;
    unsigned char        LPX_WAIT;
    unsigned char        CONT_DET;
    unsigned char        CLK_HS_PRPR;
    unsigned char        CLK_HS_POST;
    unsigned char       DA_HS_EXIT;
    unsigned char       CLK_HS_EXIT;
    unsigned int        pll_select;
    unsigned int        pll_div1;
    unsigned int        pll_div2;
    unsigned int        fbk_div;
    unsigned int        fbk_sel;
    unsigned int        rg_bir;
    unsigned int        rg_bic;
    unsigned int        rg_bp;
    unsigned int        PLL_CLOCK;
    unsigned int        dsi_clock;
    unsigned int        ssc_disable;
    unsigned int        ssc_range;
    unsigned int        compatibility_for_nvk;
    unsigned int        cont_clock;
    unsigned int        ufoe_enable;
    unsigned int        lcm_int_te_monitor;
    unsigned int        lcm_int_te_period;
    unsigned int        lcm_ext_te_monitor;
    unsigned int        lcm_ext_te_enable;
    unsigned int        noncont_clock;
    unsigned int        noncont_clock_period;
} LCM_DSI_PARAMS;
// ---------------------------------------------------------------------------
#if 0
typedef struct
{
    LCM_TYPE type;
    LCM_CTRL ctrl;  //! how to control LCM registers
    //LCM_INTERFACE_ID lcm_if;
    /* common parameters */
    unsigned int width;
    unsigned int height;
    unsigned int io_select_mode; //DBI or DPI should select IO mode according to chip spec
    /* particular parameters */
    #if 0
    LCM_DBI_PARAMS dbi;
    LCM_DPI_PARAMS dpi;
    #endif
    LCM_DSI_PARAMS dsi;
    unsigned int physical_width;
    unsigned int physical_height;
} LCM_PARAMS;
#endif

// ---------------------------------------------------------------------------
#define REGFLAG_ESCAPE_ID        (0x00)
#define REGFLAG_DELAY_MS_V3        (0xFF)
#define REGFLAG_DELAY                                         0xFFFE
#define REGFLAG_END_OF_TABLE                                  0xFFFF   // END OF REGISTERS MARKER


typedef struct {
    unsigned char id;
    unsigned char cmd;
    unsigned char count;
    unsigned char para_list[128];
} LCM_setting_table_V3;


struct LCM_setting_table {
    unsigned int cmd;
    unsigned char count;
    unsigned char para_list[64];
};


typedef struct
{
    void (*set_reset_pin)(unsigned int value);
    void (*set_chip_select)(unsigned int value);
    int  (*set_gpio_out)(unsigned int gpio, unsigned int value);
    void (*udelay)(unsigned int us);
    void (*mdelay)(unsigned int ms);
    void (*send_cmd)(unsigned int cmd);
    void (*send_data)(unsigned int data);
    unsigned int (*read_data)(void);
    void (*dsi_set_cmdq_V3)(LCM_setting_table_V3 *para_list, unsigned int size, unsigned char force_update);
    void (*dsi_set_cmdq_V2)(unsigned cmd, unsigned char count, unsigned char *para_list, unsigned char force_update);
    void (*dsi_set_cmdq)(unsigned int *pdata, unsigned int queue_size, unsigned char force_update);
    void (*dsi_write_cmd)(unsigned int cmd);
    void (*dsi_write_regs)(unsigned int addr, unsigned int *para, unsigned int nums);
    unsigned int (*dsi_read_reg)(void);
    unsigned int (*dsi_dcs_read_lcm_reg)(unsigned char cmd);
    unsigned int (*dsi_dcs_read_lcm_reg_v2)(unsigned char cmd, unsigned char *buffer, unsigned char buffer_size, unsigned char mode);
    void (*wait_transfer_done)(void);
    /** FIXME: GPIO mode should not be configured in lcm driver
               REMOVE ME after GPIO customization is done
    */
    int (*set_gpio_mode)(unsigned int pin, unsigned int mode);
    int (*set_gpio_dir)(unsigned int pin, unsigned int dir);
    int (*set_gpio_pull_enable)(unsigned int pin, unsigned char pull_en);
} LCM_UTIL_FUNCS;


typedef struct
{
    const char* name;
    void (*set_util_funcs)(const LCM_UTIL_FUNCS *util);
    void (*set_params)(struct LCM_setting_table *init_table, unsigned int init_size, LCM_PARAMS *params);
    void (*get_id)(unsigned int* driver_id, unsigned int* module_id);
    void (*get_params)(LCM_PARAMS *params);
    void (*init)(void);
    void (*suspend)(void);
    void (*resume)(void);
    // for power-on sequence refinement
    void (*init_power)(void);
    void (*suspend_power)(void);
    void (*resume_power)(void);
    void (*update)(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    unsigned int (*compare_id)(void);
    ///////////////////////////CABC backlight related function
    void (*set_backlight)(unsigned int level);
    void (*set_pwm)(unsigned int divider);
    unsigned int (*get_pwm)(unsigned int divider);
    void (*set_backlight_mode)(unsigned int mode);
    ///////////////////////////
    /////////////ESD_RECOVERY//////////////////////
    unsigned int (*esd_check)(void);
    unsigned int  (*esd_recover)(void);
    unsigned int (*check_status)(void);
    unsigned int (*ata_check)(unsigned char *buffer);
    void (*read_fb)(unsigned char *buffer);
    /////////////////////////////////////////////////
} LCM_DRIVER;


struct lcm_custom_node
{
    int offset;
    int len;
};

struct lcm_custom_header
{
    unsigned int driver_id;  // driver ID of LCM
    unsigned int module_id;  // module ID of LCM
    struct lcm_custom_node node_list[MAX_VAR_CNT];  // custom node of LCM
};

struct lcm_para_header
{
    unsigned int version;
    unsigned int list;
    unsigned int count;
    unsigned int size;
    struct lcm_custom_header header_list[MAX_LCM_CNT];
};
// ---------------------------------------------------------------------------
//  LCM Driver Functions
// ---------------------------------------------------------------------------
const LCM_DRIVER* LCM_GetDriver(void);
unsigned char which_lcd_module_triple(void);
#endif // __LCM_DRV_H__
