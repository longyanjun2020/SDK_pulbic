
#ifndef __DSC_KEYPAD_H__
#define __DSC_KEYPAD_H__

#include "includes_fw.h"

/*===========================================================================
 * Include files
 *===========================================================================*/

/* Note : This file is the top-level include file, 
          it's better not to include other files. 
*/

/*===========================================================================
 * Structure define
 *===========================================================================*/

/* For ADC Button */
typedef struct tagADCButton
{
    int             iPressId;
    int             iReleaseId;
    int             iLongPressId;
    int             iLongReleaseId;
    unsigned int    ulKeyVolt;
    unsigned int    ulKeyMargin;
    unsigned char   ubKeyStateId;
    unsigned char   ubKeyPairId;
    unsigned char   ubKeyCount;
    unsigned int    ulKeyFlag;
    unsigned char   ubkeyname[16];
} SADCBUTTON;

/* For GPIO Button/Device */
typedef struct tagButton
{
    int            iPressId;
    int            iReleaseId;
    int            iLongPressId;
    int            iLongReleaseId;
    int            piopin;
    unsigned int   ulKeyLastTime;
    unsigned int   ulDebounceTime;
    unsigned int   ulContinuousTime;
    unsigned char  ulPressLevel;       
    unsigned char  ulKeyLastValue;
    unsigned int   ulKeyCount;
    unsigned char  ubLongPress;
    unsigned char  ubKeyStateId;
    unsigned char  ubKeyPairId;
    unsigned int   ulKeyFlag;
    unsigned char  ubkeyname[16];
    unsigned char  ubLPRepeatEn;
    unsigned char  ubLPRepeatTime;  // repeat period: num of long press time
    bool           bGetByGpio;      // get High
    int            (*pfGetByReg)(void *handler);
} SGPIOBUTTON;

/* For IR Button */
typedef struct tagIRButton
{
    int             iPressId;
    int             iReleaseId;
    int             iLongPressId;
    int             iLongReleaseId;
    unsigned short  ulKeyValue;
    unsigned char   ubKeyStateId;
    unsigned char   ubKeyPairId;
    unsigned char   ubKeyCount;
    unsigned char   ubPressStatus;
    unsigned char   ubkeyname[16];
} SIRBUTTON;

/*===========================================================================
 * Enum define
 *===========================================================================*/

/* For GPIO ID : Ref:mmpf_pio.h */
#define CONFIG_PIO_REG_GPIO0        0x0
#define CONFIG_PIO_REG_GPIO1        0x1
#define CONFIG_PIO_REG_GPIO2        0x2
#define CONFIG_PIO_REG_GPIO3        0x3
#define CONFIG_PIO_REG_GPIO4        0x4
#define CONFIG_PIO_REG_GPIO5        0x5
#define CONFIG_PIO_REG_GPIO6        0x6
#define CONFIG_PIO_REG_GPIO7        0x7
#define CONFIG_PIO_REG_GPIO8        0x8
#define CONFIG_PIO_REG_GPIO9        0x9
#define CONFIG_PIO_REG_GPIO10       0xa
#define CONFIG_PIO_REG_GPIO11       0xb
#define CONFIG_PIO_REG_GPIO12       0xc
#define CONFIG_PIO_REG_GPIO13       0xd
#define CONFIG_PIO_REG_GPIO14       0xe
#define CONFIG_PIO_REG_GPIO15       0xf
#define CONFIG_PIO_REG_GPIO16       0x10
#define CONFIG_PIO_REG_GPIO17       0x11
#define CONFIG_PIO_REG_GPIO18       0x12
#define CONFIG_PIO_REG_GPIO19       0x13
#define CONFIG_PIO_REG_GPIO20       0x14
#define CONFIG_PIO_REG_GPIO21       0x15
#define CONFIG_PIO_REG_GPIO22       0x16
#define CONFIG_PIO_REG_GPIO23       0x17
#define CONFIG_PIO_REG_GPIO24       0x18
#define CONFIG_PIO_REG_GPIO25       0x19
#define CONFIG_PIO_REG_GPIO26       0x1a
#define CONFIG_PIO_REG_GPIO27       0x1b
#define CONFIG_PIO_REG_GPIO28       0x1c
#define CONFIG_PIO_REG_GPIO29       0x1d
#define CONFIG_PIO_REG_GPIO30       0x1e
#define CONFIG_PIO_REG_GPIO31       0x1f
#define CONFIG_PIO_REG_GPIO32       0x20
#define CONFIG_PIO_REG_GPIO33       0x21
#define CONFIG_PIO_REG_GPIO34       0x22
#define CONFIG_PIO_REG_GPIO35       0x23
#define CONFIG_PIO_REG_GPIO36       0x24
#define CONFIG_PIO_REG_GPIO37       0x25
#define CONFIG_PIO_REG_GPIO38       0x26
#define CONFIG_PIO_REG_GPIO39       0x27
#define CONFIG_PIO_REG_GPIO40       0x28
#define CONFIG_PIO_REG_GPIO41       0x29
#define CONFIG_PIO_REG_GPIO42       0x2a
#define CONFIG_PIO_REG_GPIO43       0x2b
#define CONFIG_PIO_REG_GPIO44       0x2c
#define CONFIG_PIO_REG_GPIO45       0x2d
#define CONFIG_PIO_REG_GPIO46       0x2e
#define CONFIG_PIO_REG_GPIO47       0x2f
#define CONFIG_PIO_REG_GPIO48       0x30
#define CONFIG_PIO_REG_GPIO49       0x31
#define CONFIG_PIO_REG_GPIO50       0x32
#define CONFIG_PIO_REG_GPIO51       0x33
#define CONFIG_PIO_REG_GPIO52       0x34
#define CONFIG_PIO_REG_GPIO53       0x35
#define CONFIG_PIO_REG_GPIO54       0x36
#define CONFIG_PIO_REG_GPIO55       0x37
#define CONFIG_PIO_REG_GPIO56       0x38
#define CONFIG_PIO_REG_GPIO57       0x39
#define CONFIG_PIO_REG_GPIO58       0x3a
#define CONFIG_PIO_REG_GPIO59       0x3b
#define CONFIG_PIO_REG_GPIO60       0x3c
#define CONFIG_PIO_REG_GPIO61       0x3d
#define CONFIG_PIO_REG_GPIO62       0x3e
#define CONFIG_PIO_REG_GPIO63       0x3f
#define CONFIG_PIO_REG_GPIO64       0x40
#define CONFIG_PIO_REG_GPIO65       0x41
#define CONFIG_PIO_REG_GPIO66       0x42
#define CONFIG_PIO_REG_GPIO67       0x43
#define CONFIG_PIO_REG_GPIO68       0x44
#define CONFIG_PIO_REG_GPIO69       0x45
#define CONFIG_PIO_REG_GPIO70       0x46
#define CONFIG_PIO_REG_GPIO71       0x47
#define CONFIG_PIO_REG_GPIO72       0x48
#define CONFIG_PIO_REG_GPIO73       0x49
#define CONFIG_PIO_REG_GPIO74       0x4A
#define CONFIG_PIO_REG_GPIO75       0x4B
#define CONFIG_PIO_REG_GPIO76       0x4C
#define CONFIG_PIO_REG_GPIO77       0x4D
#define CONFIG_PIO_REG_GPIO78       0x4E
#define CONFIG_PIO_REG_GPIO79       0x4F
#define CONFIG_PIO_REG_GPIO80       0x50
#define CONFIG_PIO_REG_GPIO81       0x51
#define CONFIG_PIO_REG_GPIO82       0x52
#define CONFIG_PIO_REG_GPIO83       0x53
#define CONFIG_PIO_REG_GPIO84       0x54
#define CONFIG_PIO_REG_GPIO85       0x55
#define CONFIG_PIO_REG_GPIO86       0x56
#define CONFIG_PIO_REG_GPIO87       0x57
#define CONFIG_PIO_REG_GPIO88       0x58
#define CONFIG_PIO_REG_GPIO89       0x59
#define CONFIG_PIO_REG_GPIO90       0x5A
#define CONFIG_PIO_REG_GPIO91       0x5B
#define CONFIG_PIO_REG_GPIO92       0x5C
#define CONFIG_PIO_REG_GPIO93       0x5D
#define CONFIG_PIO_REG_GPIO94       0x5E
#define CONFIG_PIO_REG_GPIO95       0x5F
#define CONFIG_PIO_REG_GPIO96       0x60
#define CONFIG_PIO_REG_GPIO97       0x61
#define CONFIG_PIO_REG_GPIO98       0x62
#define CONFIG_PIO_REG_GPIO99       0x63
#define CONFIG_PIO_REG_GPIO100      0x64
#define CONFIG_PIO_REG_GPIO101      0x65
#define CONFIG_PIO_REG_GPIO102      0x66
#define CONFIG_PIO_REG_GPIO103      0x67
#define CONFIG_PIO_REG_GPIO104      0x68
#define CONFIG_PIO_REG_GPIO105      0x69
#define CONFIG_PIO_REG_GPIO106      0x6A
#define CONFIG_PIO_REG_GPIO107      0x6B
#define CONFIG_PIO_REG_GPIO108      0x6C
#define CONFIG_PIO_REG_GPIO109      0x6D
#define CONFIG_PIO_REG_GPIO110      0x6E
#define CONFIG_PIO_REG_GPIO111      0x6F
#define CONFIG_PIO_REG_GPIO112      0x70
#define CONFIG_PIO_REG_GPIO113      0x71
#define CONFIG_PIO_REG_GPIO114      0x72
#define CONFIG_PIO_REG_GPIO115      0x73
#define CONFIG_PIO_REG_GPIO116      0x74
#define CONFIG_PIO_REG_GPIO117      0x75
#define CONFIG_PIO_REG_GPIO118      0x76
#define CONFIG_PIO_REG_GPIO119      0x77
#define CONFIG_PIO_REG_GPIO120      0x78
#define CONFIG_PIO_REG_GPIO121      0x79
#define CONFIG_PIO_REG_GPIO122      0x7A
#define CONFIG_PIO_REG_GPIO123      0x7B
#define CONFIG_PIO_REG_GPIO124      0x7C
#define CONFIG_PIO_REG_GPIO125      0x7D
#define CONFIG_PIO_REG_GPIO126      0x7E
#define CONFIG_PIO_REG_GPIO127      0x7F
#define CONFIG_PIO_REG_UNKNOWN      0xFFF

/* For ADC Key */
typedef enum _ADCSELECTION {
    ADC_AUX1 = 0,
    ADC_AUX2    ,
    ADC_WIPER   ,
    ADC_TP_PRE  ,
    ADC_X_CO    ,
    ADC_Y_CO    ,
    ADC_MAX
} ADCSELECTION;

typedef enum _ADCPRESSKEYSTATUS {
    ADCPRESS_U = 0,
    ADCPRESS_D,
    ADCPRESS_L,
    ADCPRESS_R,
    ADCPRESS_ENTER,
    ADCPRESS_REC,
    ADCPRESS_MENU,
    ADCPRESS_PLAY,
    ADCPRESS_MODE,
    ADCPRESS_SOS,
    ADCPRESS_MUTE,
    ADCPRESS_CAPTURE,
    ADCPRESS_FUNC1,
    ADCPRESS_FUNC2,
    ADCPRESS_FUNC3,
    ADCPRESS_NONE,
    ADCPRESS_MAX
} ADCPRESSKEYSTATUS;

/* For GPIO Key */
/* NOTE: DON'T change the order!!!, it is relative for KEY ROTATE */
typedef enum _GPIOKEYSTATUS {
    GPIOID_REC = 0,
    GPIOID_MENU,
    GPIOID_PLAY,
    GPIOID_MODE,
    GPIOID_POWER,
    GPIOID_UP,
    GPIOID_DOWN,
    GPIOID_LEFT,
    GPIOID_RIGHT,
    GPIOID_OK,
    GPIOID_SOS,
    GPIOID_MUTE,
    GPIOID_CAPTURE,
    GPIOID_FUNC1,
    GPIOID_FUNC2,
    GPIOID_FUNC3,
    GPIOID_TOUCH,
    GPIOID_NONE,
    GPIOID_MAX
} GPIOKEYSTATUS;

/* For Device */
typedef enum _DEVSTATUS {
    DEVID_USB = 0,
    DEVID_SDMMC,
    DEVID_LCDCOV,
    DEVID_LCDINV,
    DEVID_DC_CABLE,
    DEVID_CUS_SW1,
    DEVID_CUS_SW2,
    DEVID_NONE,
    DEVID_MAX
} DEVSTATUS;

/* For IR Key */
typedef enum _IRPRESSKEYSTATUS {
    IRPRESS_U = 0,
    IRPRESS_D,
    IRPRESS_L,
    IRPRESS_R,
    IRPRESS_ENTER,
    IRPRESS_REC,
    IRPRESS_MENU,
    IRPRESS_PLAY,
    IRPRESS_MODE,
    IRPRESS_SOS,
    IRPRESS_MUTE,
    IRPRESS_CAPTURE,
    IRPRESS_FUNC1,
    IRPRESS_FUNC2,
    IRPRESS_FUNC3,
    IRPRESS_TELE,
    IRPRESS_WIDE,
    IRPRESS_POWER,
    IRPRESS_NONE,
    IRPRESS_MAX
} IRPRESSKEYSTATUS;

/*===========================================================================
 * Macro define : Key
 *===========================================================================*/

/* Short Press */
#define KEYPAD_NONE                         0
#define KEY_PRESS_START                     1
#define KEY_PRESS_UP                        KEY_PRESS_START
#define KEY_PRESS_DOWN                      2
#define KEY_PRESS_LEFT                      3
#define KEY_PRESS_RIGHT                     4
#define KEY_PRESS_OK                        5
#define KEY_PRESS_REC                       6
#define KEY_PRESS_MENU                      7
#define KEY_PRESS_PLAY                      8
#define KEY_PRESS_MODE                      9
#define KEY_PRESS_POWER                     10
#define KEY_PRESS_TELE                      11
#define KEY_PRESS_WIDE                      12
#define KEY_PRESS_SOS                       13
#define KEY_PRESS_MUTE                      14
#define KEY_PRESS_CAPTURE                   15
#define KEY_PRESS_FUNC1                     16
#define KEY_PRESS_FUNC2                     17
#define KEY_PRESS_FUNC3                     18
#define KEY_PRESS_END                       19      // Keep this at last of KEY_PRESS_xxxxx

#define VRCB_SHARE_FILE_FULL                36
#define VRCB_PREVIEW_ERR                    37 
#define VRCB_RECDSTOP_CARDSLOW              38
#define VRCB_AP_STOP_VIDEO_RECD             39
#define VRCB_MEDIA_FULL                     40
#define VRCB_FILE_FULL                      41
#define VRCB_MEDIA_SLOW                     42
#define VRCB_MEDIA_ERROR                    43
#define VRCB_SEAM_LESS                      44
#define VRCB_MOTION_DTC                     45
#define VRCB_VR_START                       46
#define VRCB_VR_STOP                        47
#define VRCB_VR_POSTPROCESS                 48
#define VRCB_VR_EMER_DONE                   49
#define VRCB_LONG_TIME_FILE_FULL            50

/* Long Press */
#define KEY_LPRESS_START                    51
#define KEY_LPRESS_UP                       KEY_LPRESS_START
#define KEY_LPRESS_DOWN                     52
#define KEY_LPRESS_LEFT                     53
#define KEY_LPRESS_RIGHT                    54
#define KEY_LPRESS_OK                       55
#define KEY_LPRESS_REC                      56
#define KEY_LPRESS_MENU                     57
#define KEY_LPRESS_PLAY                     58
#define KEY_LPRESS_MODE                     59
#define KEY_LPRESS_POWER                    60
#define KEY_LPRESS_TELE                     61
#define KEY_LPRESS_WIDE                     62
#define KEY_LPRESS_SOS                      63
#define KEY_LPRESS_MUTE                     64
#define KEY_LPRESS_CAPTURE                  65
#define KEY_LPRESS_FUNC1                    66
#define KEY_LPRESS_FUNC2                    67
#define KEY_LPRESS_FUNC3                    68
#define KEY_LPRESS_END                      69      // Keep this at last of KEY_LPRESS_xxxxx

#define TOUCH_PANEL_PRESS                   81
#define TOUCH_PANEL_MOVE                    82
#define TOUCH_PANEL_REL                     83

#define TOUCH_KEY_PRESS                     84
#define TOUCH_KEY_MOVE                      85
#define TOUCH_KEY_REL                       86

/* Short Release */
#define KEY_REL_START                       101
#define KEY_REL_UP                          KEY_REL_START
#define KEY_REL_DOWN                        102
#define KEY_REL_LEFT                        103
#define KEY_REL_RIGHT                       104
#define KEY_REL_OK                          105
#define KEY_REL_REC                         106
#define KEY_REL_MENU                        107
#define KEY_REL_PLAY                        108
#define KEY_REL_MODE                        109
#define KEY_REL_POWER                       110
#define KEY_REL_TELE                        111
#define KEY_REL_WIDE                        112
#define KEY_REL_SOS                         113
#define KEY_REL_MUTE                        114
#define KEY_REL_CAPTURE                     115
#define KEY_REL_FUNC1                       116
#define KEY_REL_FUNC2                       117
#define KEY_REL_FUNC3                       118
#define KEY_REL_END                         119      // Keep this at last of KEY_REL_xxxxx

#define SUB_MODE_ENTER                      140
#define SUB_MODE_EXIT                       141

#define DEVICE_LCD_NOR                      150
#define DEVICE_LCD_COVERED                  151
#define USB_CABLE_IN                        152
#define SD_CARD_IN                          153
#define TV_CABLE_IN                         154
#define HDMI_CABLE_IN                       155
#define DC_CABLE_IN                         156
#define CUS_SW1_ON                          157
#define CUS_SW2_ON                          158
#define USB_B_DEVICE_IN                     159

/* Long Release */
#define KEY_LREL_START                      161
#define KEY_LREL_UP                         KEY_LREL_START
#define KEY_LREL_DOWN                       162
#define KEY_LREL_LEFT                       163
#define KEY_LREL_RIGHT                      164
#define KEY_LREL_OK                         165
#define KEY_LREL_REC                        166
#define KEY_LREL_MENU                       167
#define KEY_LREL_PLAY                       168
#define KEY_LREL_MODE                       169
#define KEY_LREL_POWER                      170
#define KEY_LREL_TELE                       171
#define KEY_LREL_WIDE                       172
#define KEY_LREL_SOS                        173
#define KEY_LREL_MUTE                       174
#define KEY_LREL_CAPTURE                    175
#define KEY_LREL_FUNC1                      176
#define KEY_LREL_FUNC2                      177
#define KEY_LREL_FUNC3                      178
#define KEY_LREL_END                        179      // Keep this at last of KEY_LREL_xxxxx

#define DEVICE_LCD_INV                      190
#define DEVICE_LCD_OPEN                     191
#define USB_CABLE_OUT                       192
#define SD_CARD_OUT                         193
#define TV_CABLE_OUT                        194
#define HDMI_CABLE_OUT                      195
#define DC_CABLE_OUT                        196
#define CUS_SW1_OFF                         197
#define CUS_SW2_OFF                         198
#define USB_B_DEVICE_OUT                    200
#define FACTORY_RESET                       201
#define BATTERY_DETECTION                   202
#define TV_DECODER_SRC_TYPE_CHANGED         203
#define USB_REARCAM_REVERSE_GEAR            204//reverse gear

#define VIRTUAL_EVENT                       998 //soft key without interpretation
#define DEVICES_READY                       999

/* For Quick Key/Combo Key */
#define KEYFLAG_DUMMY                       0x0

#define KEYFLAG_REC                         (1 << 0)
#define KEYFLAG_MENU                        (1 << 1)
#define KEYFLAG_PLAY                        (1 << 2)
#define KEYFLAG_MODE                        (1 << 3)
#define KEYFLAG_POWER                       (1 << 4)
#define KEYFLAG_UP                          (1 << 5)
#define KEYFLAG_DOWN                        (1 << 6)
#define KEYFLAG_LEFT                        (1 << 7)
#define KEYFLAG_RIGHT                       (1 << 8)
#define KEYFLAG_OK                          (1 << 9)
#define KEYFLAG_SOS                         (1 << 10)
#define KEYFLAG_MUTE                        (1 << 11)
#define KEYFLAG_CAPTURE                     (1 << 12)
#define KEYFLAG_FUNC1                       (1 << 13)
#define KEYFLAG_FUNC2                       (1 << 14)
#define KEYFLAG_FUNC3                       (1 << 15)

#define KEYFLAG_LP_REC                      (1 << 16)
#define KEYFLAG_LP_MENU                     (1 << 17)
#define KEYFLAG_LP_PLAY                     (1 << 18)
#define KEYFLAG_LP_MODE                     (1 << 19)
#define KEYFLAG_LP_POWER                    (1 << 20)
#define KEYFLAG_LP_UP                       (1 << 21)
#define KEYFLAG_LP_DOWN                     (1 << 22)
#define KEYFLAG_LP_LEFT                     (1 << 23)
#define KEYFLAG_LP_RIGHT                    (1 << 24)
#define KEYFLAG_LP_OK                       (1 << 25)
#define KEYFLAG_LP_SOS                      (1 << 26)
#define KEYFLAG_LP_MUTE                     (1 << 27)
#define KEYFLAG_LP_CAPTURE                  (1 << 28)
#define KEYFLAG_LP_FUNC1                    (1 << 29)
#define KEYFLAG_LP_FUNC2                    (1 << 30)
#define KEYFLAG_LP_FUNC3                    (1 << 31)

/* POWER_ON_BUTTON_ACTION. For Quick Key */
#define QUICK_NONE                          (0)
#define QUICK_REC                           (1 << 0)
#define QUICK_MODE                          (1 << 1)
#define QUICK_PLAY                          (1 << 2)
#define QUICK_MENU                          (1 << 3)
#define QUICK_UP                            (1 << 4)
#define QUICK_DOWN                          (1 << 5)
#define QUICK_ALL                           (0xFFFFFFFF)

/* IR Key State ID */
#define IR_STATE_ID_U                       (IRPRESS_U)
#define IR_STATE_ID_D                       (IRPRESS_D)
#define IR_STATE_ID_L                       (IRPRESS_L)
#define IR_STATE_ID_R                       (IRPRESS_R)
#define IR_STATE_ID_ENTER                   (IRPRESS_ENTER)
#define IR_STATE_ID_REC                     (IRPRESS_REC)
#define IR_STATE_ID_MENU                    (IRPRESS_MENU)
#define IR_STATE_ID_PLAY                    (IRPRESS_PLAY)
#define IR_STATE_ID_MODE                    (IRPRESS_MODE)
#define IR_STATE_ID_SOS                     (IRPRESS_SOS)
#define IR_STATE_ID_MUTE                    (IRPRESS_MUTE)
#define IR_STATE_ID_CAPTURE                 (IRPRESS_CAPTURE)
#define IR_STATE_ID_TELE                    (IRPRESS_TELE)
#define IR_STATE_ID_WIDE                    (IRPRESS_WIDE)
#define IR_STATE_ID_FUNC1                   (IRPRESS_FUNC1)
#define IR_STATE_ID_FUNC2                   (IRPRESS_FUNC2)
#define IR_STATE_ID_FUNC3                   (IRPRESS_FUNC3)
#define IR_STATE_ID_POWER                   (IRPRESS_POWER)

/*===========================================================================
 * Macro define : Config Option
 *===========================================================================*/

/* For Lock File Type */
#define LOCK_FILE_PREV_CUR              (1)
#define LOCK_FILE_CUR_NEXT              (2)
#define LOCK_FILE_PREV_CUR_NEXT         (3)
#define LOCK_FILE_CUR                   (4)

/* For Lock File Limit Action */
#define LOCK_FILE_STOP                  (1)
#define LOCK_FILE_DEL_CYCLIC            (2)
#define LOCK_FILE_RENAME_CYCLIC         (3)

/* For Deleting file when Lock File Fulled */
#define DEL_LOCKED_FILE                 (1)
#define DEL_ANY_FILE                    (2)

/*For Gsensor Powering On*/
#define GSNR_PWRON_REC_BY_KEY           (0)
#define GSNR_PWRON_REC_BY_SHAKED        (1)
#define GSNR_PWRON_REC_BY_VMD           (1<<1)

#define GSNR_PWRON_IDLE                 (0)
#define GSNR_PWRON_REC_AUTO             (1)

#define GSNR_PWRON_MOVIE_UNLOCKED       (0)
#define GSNR_PWRON_MOVIE_LOCKED         (1)

/* For LED Control */
#define LED_BY_NONE                     (0)
#define LED_BY_KEY                      (1) //Change uiFlashMode
#define LED_BY_KEY_WITH_MENU_CONFIRMED  (2) //Change uiFlashMode
#define LED_BY_MENU                     (3) //Change uiLEDFlash
#define LED_BY_MENU_AND_KEY_LINK        (4) //Change uiLEDFlash
#define LED_BY_MENU_AND_KEY_NOT_LINK    (5) //Change uiLEDFlash

/* For LED Control Mode */
#define LED_MODE_AUTO_ON_OFF            (0)
#define LED_MODE_ON_OFF                 (1)

/* For Gsensor Function */
#define FUNC_LOCK_FILE                  (0x01)
#define FUNC_VIDEOSTREM_INFO            (0x02)
#define FUNC_FLIP_PANEL                 (0x04)
#define FUNC_ALL_SUPPORT                (FUNC_LOCK_FILE | FUNC_VIDEOSTREM_INFO | FUNC_FLIP_PANEL)

/* For Direction Key Type */
#define KEY_TYPE_4KEY                   (0) //Up,Down,Left,Right
#define KEY_TYPE_2KEY                   (1) //Up,Down or Left,Right

/* For Menu Style */
#define MENU_ORIGINAL                   (1) //SubMenu Type : SUBMENU_SUBPAGE
#define MENU_2ND_STYLE                  (2) //SubMenu Type : SUBMENU_SUBPAGE/SUBMENU_SIDE_TEXTPAGE/SUBMENU_SIDE_ICONPAGE
#define MENU_3RD_STYLE                  (3) //SubMenu Type : SUBMENU_SIDE_TEXTPAGE/SUBMENU_SIDE_ICONPAGE

/* For SubMenu Style */
#define SUBMENU_SUBPAGE                 (0)
#define SUBMENU_SIDE_TEXTPAGE           (1)
#define SUBMENU_SIDE_ICONPAGE           (2)
#define SUBMENU_SIDE_SMALLPAGE          (3)

/* For Store LCD/Sensor/TV/HDMI Status To SF Offset */
#define SETTING_TOTAL_ITEMS             (6)     // include check sum
#define SETTING_CHECK_VALUE             (0xFF)

#define MENU_STATUS_REGION_SIZE         (256)
#define TV_SYSTEM_SETTING_OFFSET        (MENU_STATUS_REGION_SIZE-6)
#define HDMI_SYSTEM_SETTING_OFFSET      (MENU_STATUS_REGION_SIZE-5)
#define SNR_STATUS_OFFSET               (MENU_STATUS_REGION_SIZE-4)
#define LCD_STATUS_OFFSET               (MENU_STATUS_REGION_SIZE-3)
#define LCD_MENU_SETTING_OFFSET         (MENU_STATUS_REGION_SIZE-2)
#define SETTING_CHECKSUM                (MENU_STATUS_REGION_SIZE-1)

/* For Charger Plug In/Out Action */
#define ACT_NONE                        (0x00)
#define ACT_RECORD_VIDEO                (0x01)
#define ACT_CHARGING_ONLY               (0x02)
#define ACT_FORCE_POWER_OFF             (0x04)
#define ACT_DELAY_POWER_OFF             (0x08)

#define GSNR_POSITION_NOCHANGE          (0x0)
#define GSNR_POSITION_UP                (0x1)
#define GSNR_POSITION_DOWN              (0x2)
#define GSNR_POSITION_UNKNOWN           (0xFF)

/* For G-sensor Sensitivity */
#define SCALE_G                         (100) // Remove later...
#define GR(g)                           (g * SCALE_G)

/* For GPIO Key Press Level */
#define LEVEL_HIGH                      (GPIO_HIGH)
#define LEVEL_LOW                       (GPIO_LOW)

/* For Motion Detection Event */
#define VMD_ACTION_NONE                 (0x00)
#define VMD_RECORD_VIDEO                (0x01)
#define VMD_BURST_CAPTURE               (0x02)
#define VMD_ACTION_ALL                  (VMD_RECORD_VIDEO | VMD_BURST_CAPTURE)

/* For DSC Multi-Mode */
#define DSC_MULTI_DIS                   (0x00)
#define DSC_ONE_SHOT                    (0x01)
#define DSC_BURST_SHOT                  (0x02)
#define DSC_TIME_LAPSE                  (0x04)
#define DSC_MODE_ALL                    (DSC_ONE_SHOT | DSC_BURST_SHOT | DSC_TIME_LAPSE)

/* For TimeLapse Function */
#define TIMELAPSE_NONE                  (0x00)
#define TIMELAPSE_IMG                   (0x01)
#define TIMELAPSE_VIDEO                 (0x02)
#define TIMELAPSE_VIDEO_AND_IMG         (TIMELAPSE_IMG | TIMELAPSE_VIDEO)

/* For Touch Panel Type */
#define TOUCH_PANEL_DIR_0               (0)
#define TOUCH_PANEL_DIR_1               (1)
#define TOUCH_PANEL_DIR_2               (2)
#define TOUCH_PANEL_DIR_3               (3)

/* For Qucik Edit File Option */
#define QUICK_EDIT_DISABLE              (0)
#define QUICK_EDIT_NO_CONFIRM           (1)
#define QUICK_EDIT_WITH_CONFIRM         (2)

/* For Movie Playback EOS Action */
#define EOS_ACT_RESTART                 (0)
#define EOS_ACT_PAUSE_AT_FIRST_FRAME    (1)
#define EOS_ACT_PAUSE_AT_LAST_FRAME     (2)
#define EOS_ACT_NONE                    (3)

/* For Video Record Container Format */
#define VR_CONTAINER_TYPE_3GP           (0)
#define VR_CONTAINER_TYPE_AVI           (1)

/* For Video Record Audio Format */
#define VR_AUDIO_TYPE_ALL_WIFI          (0x7) //currently AAC, MP3, ADPCM

/* For Browser Style */
#define BROWSER_ORIGINAL_STYLE          (0)
#define BROWSER_2ND_STYLE               (1)

#define WIFI_BY_KEY                     (0)
#define WIFI_BY_MENU                    (1)

#define LCD_DIR_0                       (0)
#define LCD_DIR_1                       (1)

/* For IR */
#define IR_MODULE_NONE                  (0)
#define IR_MODULE_AIT8x28               (1)
#define IR_MODULE_IRC120X               (2)

/*===========================================================================
 * Macro define : Default Config
 *===========================================================================*/

#define GPIO_REG_UNKNOWN                (CONFIG_PIO_REG_UNKNOWN)

#define KEY_GPIO_ID_INVALID             (GPIOID_NONE)

#define BUTTON_ID_UNKNOWN               (0xFF)

#define ADC_KEY_VOLT_DEFAULT            (5000)//TBD

#define ADC_STATE_ID_INVALID            (ADCPRESS_NONE)

#define IR_VALUE_DEFAULT                (0xFF)

#define IR_STATE_ID_INVALID             (IRPRESS_NONE)

/*===========================================================================
 * Function prototype
 *===========================================================================*/

void AutoPowerOffCounterReset(void);
void LCDPowerSaveCounterReset(void);
void VideoPowerOffCounterReset(void);
int  Enable_SD_Power(int bEnable);
void SetKeyPadEvent(unsigned int keyevent);
void InitGsensorAhead(void);

#endif // __DSC_KEYPAD_H__
