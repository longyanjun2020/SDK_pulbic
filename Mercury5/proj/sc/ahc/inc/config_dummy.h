#ifndef _CONFIG_DUMMY_H_
#define _CONFIG_DUMMY_H_

/*===========================================================================
 *  DBG Config
 *===========================================================================*/

#ifndef AIT_HW_WATCHDOG_ENABLE
#define AIT_HW_WATCHDOG_ENABLE (0)
#endif

#ifndef AIT_HW_WATCHDOG_TIMEOUT
#define AIT_HW_WATCHDOG_TIMEOUT (4000) //Unit: ms.  Max value is about 4000.
#endif

/*===========================================================================
 *  External Module Config
 *===========================================================================*/

#ifndef FW_DCF_BACKGROUND
#define FW_DCF_BACKGROUND                       (0)
#endif

#ifndef LCD_MODEL_TYPE
#define LCD_MODEL_TYPE                          (ILI8961)
#endif

#ifndef LCD_MODEL_RATIO_X
#define LCD_MODEL_RATIO_X                       (4)
#endif

#ifndef LCD_MODEL_RATIO_Y
#define LCD_MODEL_RATIO_Y                       (3)
#endif

#ifndef ENABLE_POWER_OFF_PICTURE
#define ENABLE_POWER_OFF_PICTURE                (0)
#endif

#ifndef KEYPAD_DETECT_METHOD
#define KEYPAD_DETECT_METHOD                    KEYPAD_DETECT_TASK    
#endif

#ifndef RMT_CTL_TYPE
#define RMT_CTL_TYPE                            RMT_CTL_DISABLE    
#endif

#ifndef KEYPAD_S01_GPIO
#define KEYPAD_S01_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S02_GPIO
#define KEYPAD_S02_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S03_GPIO
#define KEYPAD_S03_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S04_GPIO
#define KEYPAD_S04_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S05_GPIO
#define KEYPAD_S05_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S06_GPIO
#define KEYPAD_S06_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S07_GPIO
#define KEYPAD_S07_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S08_GPIO
#define KEYPAD_S08_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S09_GPIO
#define KEYPAD_S09_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S10_GPIO
#define KEYPAD_S10_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S11_GPIO
#define KEYPAD_S11_GPIO                         MMP_GPIO_MAX
#endif

#ifndef KEYPAD_S12_GPIO
#define KEYPAD_S12_GPIO                         MMP_GPIO_MAX
#endif

#ifndef POWER_KEY_GPIO
#define POWER_KEY_GPIO                          MMP_GPIO_MAX
#endif

//Lens motor driver
#ifndef AIT_LENS_TYPE
#define AIT_LENS_TYPE                           AIT_LENS_TYPE_DUMMY
#endif

#ifndef ENABLE_MOTOR_DRV_POWER_CTRL
#define ENABLE_MOTOR_DRV_POWER_CTRL             (0)
#endif

#ifndef LENS_MOTOR_DRV_MT_SPI_CLK
#define LENS_MOTOR_DRV_MT_SPI_CLK               MMP_GPIO_MAX
#endif

#ifndef LENS_MOTOR_DRV_MT_SPI_DATA
#define LENS_MOTOR_DRV_MT_SPI_DATA              MMP_GPIO_MAX
#endif

#ifndef LENS_MOTOR_DRV_MT_SPI_CS
#define LENS_MOTOR_DRV_MT_SPI_CS                MMP_GPIO_MAX
#endif

#ifndef LENS_MOTOR_DRV_MT_RESET
#define LENS_MOTOR_DRV_MT_RESET                 MMP_GPIO_MAX 
#endif

#if defined(DSC_IRIS_ENABLE) && DSC_IRIS_ENABLE
#ifndef IRIS_GPIO_PIN_1
#define IRIS_GPIO_PIN_1                         MMP_GPIO_MAX    
#endif

#ifndef IRIS_GPIO_PIN_1_ON
#define IRIS_GPIO_PIN_1_ON                      0x1
#endif

#ifndef IRIS_GPIO_PIN_1_OFF
#define IRIS_GPIO_PIN_1_OFF                     0x0
#endif

#ifndef IRIS_GPIO_PIN_2
#define IRIS_GPIO_PIN_2                         MMP_GPIO_MAX    
#endif

#ifndef IRIS_GPIO_PIN_2_ON
#define IRIS_GPIO_PIN_2_ON                      0x1
#endif

#ifndef IRIS_GPIO_PIN_2_OFF
#define IRIS_GPIO_PIN_2_OFF                     0x0
#endif
#endif///< (DSC_IRIS_ENABLE)

#if defined(DSC_M_SHUTTER_ENABLE) && DSC_M_SHUTTER_ENABLE

#ifndef MECHANICAL_SHUTTER_TIMER_ID
#define MECHANICAL_SHUTTER_TIMER_ID             MMPF_TIMER_3
#endif

#ifndef MECHANICAL_SHUTTER_GPIO
#define MECHANICAL_SHUTTER_GPIO                 MMP_GPIO_MAX
#endif

#ifndef MECHANICAL_SHUTTER_GPIO_ON
#define MECHANICAL_SHUTTER_GPIO_ON              0x1
#endif

#ifndef MECHANICAL_SHUTTER_GPIO_OFF
#define MECHANICAL_SHUTTER_GPIO_OFF             0x0
#endif
#endif///< (DSC_M_SHUTTER_ENABLE)

#ifndef LENS_MOTOR_DRV_MT_MOB1
#define LENS_MOTOR_DRV_MT_MOB1                  MMP_GPIO_MAX
#endif

#ifndef SD_WRITE_PROTECT_GPIO
#define SD_WRITE_PROTECT_GPIO                   MMP_GPIO_MAX   // SD write protect Detect     
#endif

#ifndef DEVICE_GPIO_SD_POWER
#define DEVICE_GPIO_SD_POWER                    MMP_GPIO_MAX 
#endif

#ifndef DEVICE_GPIO_SD_POWER_LEVEL
#define DEVICE_GPIO_SD_POWER_LEVEL              (0)
#endif

#ifndef DEVICE_GPIO_SD_PLUG
#define DEVICE_GPIO_SD_PLUG                     MMP_GPIO_MAX 
#endif

#ifndef USB_IN_DETECT_VBUS_PIN
#define USB_IN_DETECT_VBUS_PIN                  MMP_GPIO_MAX
#endif

#ifndef USB_IN_DETECT_VBUS_PIN_ACTIVE
#define USB_IN_DETECT_VBUS_PIN_ACTIVE         (0) // Low Active
#endif

#ifndef LCD_GPIO_BACK_LIGHT
#define LCD_GPIO_BACK_LIGHT                     MMP_GPIO_MAX
#endif

#ifndef HDMI_PC_GPIO
#define HDMI_PC_GPIO                            MMP_GPIO_MAX
#endif

#ifndef ENABLE_DETECT_FLOW
#define ENABLE_DETECT_FLOW                      (0)
#endif

#ifndef LENS_MOTOR_DRV_MT_MOB2
#define LENS_MOTOR_DRV_MT_MOB2                  MMP_GPIO_MAX 
#endif

#ifndef LENS_MOTOR_DRV_MT_EXT1
#define LENS_MOTOR_DRV_MT_EXT1                  MMP_GPIO_MAX
#endif

#ifndef LENS_MOTOR_DRV_MT_EXT2
#define LENS_MOTOR_DRV_MT_EXT2                  MMP_GPIO_MAX
#endif

#ifndef LENS_MOTOR_DRV_F_OUT
#define LENS_MOTOR_DRV_F_OUT                    MMP_GPIO_MAX
#endif

#ifndef LENS_MOTOR_DRV_Z_OUT
#define LENS_MOTOR_DRV_Z_OUT                    MMP_GPIO_MAX
#endif

#ifndef USE_PWM_AS_MOTOR_OSC
#define USE_PWM_AS_MOTOR_OSC                    0 // Disable pwm as motor driver osc source
#endif

//SD PAD
//#ifndef CFG_SD_PIN_PAD_NUM
//#define CFG_SD_PIN_PAD_NUM                        SD3_PIN_PAD_NUM
//#endif

#ifndef STORAGE_FOR_FACTORY_INFO
#define STORAGE_FOR_FACTORY_INFO                 (0)
#endif

#ifndef STORAGE_FOR_ISP_INFO
#define STORAGE_FOR_ISP_INFO                     (0)
#endif

//#ifndef CFG_SD1_PIN_PAD_NUM
//#define CFG_SD1_PIN_PAD_NUM                       SD1_PIN_PAD_NUM
//#endif

//Device    
#ifndef USB_ADAPTER_GPIO
#define USB_ADAPTER_GPIO                        MMP_GPIO_MAX  // L ->USB CABLE , H-> ADAPTER
#endif

#ifndef USE_PWM_FOR_LCD_BACKLIGHT
#define USE_PWM_FOR_LCD_BACKLIGHT               0
#endif

#ifndef LCD_BACKLIGHT_PWM_UNIT_PIN
#define LCD_BACKLIGHT_PWM_UNIT_PIN              MMP_PWM_PIN_MAX // UNIT 0
#endif

//CHARGER IC
#ifndef ENABLE_CHARGER_IC
#define ENABLE_CHARGER_IC                       (0)
#endif

#ifndef ENABLE_CHARGER_IC_DS9525
#define ENABLE_CHARGER_IC_DS9525                0
#endif

#ifndef CHARGER_ENABLE_GPIO_ACT_LEVEL
#define CHARGER_ENABLE_GPIO_ACT_LEVEL           (GPIO_HIGH)
#endif

#ifndef CHARGER_STATUS_ACT_LEVEL
#define CHARGER_STATUS_ACT_LEVEL                (GPIO_LOW)
#endif

//Speaker
#ifndef SUPPORT_SPEAKER
#define SUPPORT_SPEAKER                         0
#endif 
#ifndef SPEAKER_ENABLE_GPIO
#define SPEAKER_ENABLE_GPIO                     MMP_GPIO_MAX
#endif
#ifndef DAC_NOT_OUTPUT_SPEAKER_HAS_NOISE
#define DAC_NOT_OUTPUT_SPEAKER_HAS_NOISE        0
#endif


// Uart
#ifndef DEBUG_UART_PAD
#define DEBUG_UART_PAD                          (MMP_UART_PADSET_0)
#endif

// BUZZER
#ifndef DEVICE_GPIO_BUZZER
#define DEVICE_GPIO_BUZZER                      MMP_GPIO_MAX
#endif

// POWER EN
#ifndef POWER_EN_GPIO
#define POWER_EN_GPIO                           MMP_GPIO_MAX
#endif

#ifndef POWER_EN_GPIO_LEVEL
#define POWER_EN_GPIO_LEVEL                     (1)
#endif

//
#ifndef POWER_ON_BATTERY_DETECTION
#define POWER_ON_BATTERY_DETECTION              0
#endif

#ifndef POWER_ON_BATTERY_OFFSET
#define POWER_ON_BATTERY_OFFSET                 200
#endif

#ifndef POWER_ON_LOW_BATTERY_VOLTAGE
#define POWER_ON_LOW_BATTERY_VOLTAGE            3500
#endif

#ifndef POWER_KEY_DETECT_ADC
#define POWER_KEY_DETECT_ADC                    (0)
#endif

#ifndef POWER_KEY_DETECT_GPIO
#define POWER_KEY_DETECT_GPIO                   (1)
#endif

#ifndef POWER_KEY_DETECTION
#define POWER_KEY_DETECTION                     (POWER_KEY_DETECT_GPIO)
#endif

#ifndef BIND_MOTOR_R2A30440NP
#define BIND_MOTOR_R2A30440NP                   (0)
#endif

#ifndef BIND_MOTOR_R2A30423NP
#define BIND_MOTOR_R2A30423NP                   (0)
#endif

#ifndef BIND_MOTOR_DUMMY
#define BIND_MOTOR_DUMMY                        (1)
#endif

#ifndef BATTERY_DETECTION_EN
#define BATTERY_DETECTION_EN                    (0)
#endif

#ifndef POWER_OFF_PREPROCESS_EN 
#define POWER_OFF_PREPROCESS_EN                 (0)
#endif

#ifndef POWER_OFF_WHEN_SD_REMOVE 
#define POWER_OFF_WHEN_SD_REMOVE                (0)
#endif

#ifndef SUPPORT_TOUCH_PANEL 
#define SUPPORT_TOUCH_PANEL                     (0)
#define DSC_TOUCH_PANEL                         (TOUCH_PANEL_DUMMY)
#endif

#ifndef DSC_TOUCH_PANEL
#define DSC_TOUCH_PANEL                         TOUCH_PANEL_DUMMY
#endif

#ifndef SD_DETECT_EN 
#define SD_DETECT_EN                            (0)
#endif

#ifndef SD_WRITE_PROTECT_EN
#define SD_WRITE_PROTECT_EN         (0)
#endif

#ifndef LCD_PLACEMENT_TYPE
#define LCD_PLACEMENT_TYPE          (0)
#endif

#ifndef ENABLE_ADAPTER_DEVICE
#define ENABLE_ADAPTER_DEVICE       (0)
#endif

#ifndef DSC_DIGIT_ZOOM_ENABLE
#define DSC_DIGIT_ZOOM_ENABLE       (0)
#endif

/*===========================================================================
 * Sensor related Config
 *===========================================================================*/
#ifndef SENSOR_GPIO_ENABLE
#define SENSOR_GPIO_ENABLE              (MMP_GPIO_MAX)
#endif

#ifndef SENSOR_GPIO_ENABLE_ACT_LEVEL
#define SENSOR_GPIO_ENABLE_ACT_LEVEL    (GPIO_HIGH)
#endif

#ifndef SENSOR_GPIO_REAR_ENABLE
#define SENSOR_GPIO_REAR_ENABLE         (MMP_GPIO_MAX)
#endif

#ifndef SENSOR_GPIO_REAR_ENABLE_ACT_LEVEL
#define SENSOR_GPIO_REAR_ENABLE_ACT_LEVEL    (GPIO_HIGH)
#endif

#ifndef SENSOR_RESET_ACT_LEVEL
#define SENSOR_RESET_ACT_LEVEL          (GPIO_LOW)
#endif

#ifndef SENSOR_ROTATE_180
#define SENSOR_ROTATE_180               (0)
#endif

#ifndef BIND_SENSOR_AR0330_OTPM
#define BIND_SENSOR_AR0330_OTPM         (0)
#endif

#ifndef BIND_SENSOR_OV2643
#define BIND_SENSOR_OV2643              (0)
#endif

#ifndef BIND_SENSOR_AP1302
#define BIND_SENSOR_AP1302              (0)
#endif

#ifndef BIND_SENSOR_OV2710
#define BIND_SENSOR_OV2710              (0)
#endif

#ifndef BIND_SENSOR_OV9732_MIPI
#define BIND_SENSOR_OV9732_MIPI              (0)
#endif

#ifndef BIND_SENSOR_OV2710_MIPI
#define BIND_SENSOR_OV2710_MIPI         (0)
#endif

#ifndef BIND_SENSOR_OV2735
#define BIND_SENSOR_OV2735              (0)
#endif

#ifndef BIND_SENSOR_H42_MIPI
#define BIND_SENSOR_H42_MIPI         (0)
#endif

#ifndef BIND_SENSOR_AR0331
#define BIND_SENSOR_AR0331              (0)
#endif

#ifndef BIND_SENSOR_AR0832E
#define BIND_SENSOR_AR0832E             (0)
#endif

#ifndef BIND_SENSOR_AR0835
#define BIND_SENSOR_AR0835              (0)
#endif

#ifndef BIND_SENSOR_AR1820
#define BIND_SENSOR_AR1820              (0)
#endif

#ifndef BIND_SENSOR_GC2023
#define BIND_SENSOR_GC2023              (0)
#endif

#ifndef BIND_SENSOR_IMX175
#define BIND_SENSOR_IMX175              (0)
#endif

#ifndef BIND_SENSOR_IMX214
#define BIND_SENSOR_IMX214              (0)
#endif

#ifndef BIND_SENSOR_IMX322
#define BIND_SENSOR_IMX322              (0)
#endif

#ifndef BIND_SENSOR_OV4689
#define BIND_SENSOR_OV4689              (0)
#endif

#ifndef BIND_SENSOR_H42_MIPI 
#define BIND_SENSOR_H42_MIPI              (0)
#endif

#ifndef BIND_SENSOR_OV4689_2LINE
#define BIND_SENSOR_OV4689_2LINE              (0)
#endif

#ifndef BIND_SENSOR_OV5653
#define BIND_SENSOR_OV5653              (0)
#endif

#ifndef BIND_SENSOR_OV10822
#define BIND_SENSOR_OV10822             (0)
#endif

#ifndef BIND_SENSOR_DM5150
#define BIND_SENSOR_DM5150              (0)
#endif

#ifndef BIND_SENSOR_PS1210
#define BIND_SENSOR_PS1210              (0)
#endif

#ifndef BIND_SENSOR_BIT1603
#define BIND_SENSOR_BIT1603             (0)
#endif

#ifndef BIND_SENSOR_CJC5150
#define BIND_SENSOR_CJC5150             (0)
#endif

#ifndef BIND_SENSOR_GM7150
#define BIND_SENSOR_GM7150             (0)
#endif

#ifndef BIND_SENSOR_CP8210
#define BIND_SENSOR_CP8210              (0)
#endif

#ifndef BIND_GYROSNR_ICG20660
#define BIND_GYROSNR_ICG20660           (0)
#endif

#ifndef BIND_SENSOR_JXF02
#define BIND_SENSOR_JXF02               (0)
#endif

#ifndef BIND_SENSOR_JXF22
#define BIND_SENSOR_JXF22               (0)
#endif
/*===========================================================================
 * UI related Config
 *===========================================================================*/

#ifndef UI_MENU_AUTO_VANISH
#define UI_MENU_AUTO_VANISH             (0)
#endif

//ZOOM config
//Digital zoom
//  ex.
//  |----------|------------|  <-digital zoom is separated into two sections.
//  |  1x~16x  |  16x~240x  |    Need to config the ratio and steps respectively. 
//
#ifndef DIGITAL_ZOOM_EN
#define DIGITAL_ZOOM_EN                 (0)
#endif

#ifndef DIGITAL_ZOOM_CNT
#define DIGITAL_ZOOM_CNT                (0)
#endif

#ifndef DIGITAL_ZOOM_RATIO_0
#define DIGITAL_ZOOM_RATIO_0        (0)
#endif

#ifndef DIGITAL_ZOOM_STEP_0
#define DIGITAL_ZOOM_STEP_0         (0)
#endif

#ifndef DIGITAL_ZOOM_RATIO_1
#define DIGITAL_ZOOM_RATIO_1        (0)
#endif

#ifndef DIGITAL_ZOOM_STEP_1
#define DIGITAL_ZOOM_STEP_1         (0)
#endif

#ifndef DIGITAL_ZOOM_RATIO_MAX
#define DIGITAL_ZOOM_RATIO_MAX  (0)
#endif

//Cover (open,close) flow
#ifndef COVER_CLOSE_POWER_OFF
#define COVER_CLOSE_POWER_OFF       (0)
#endif

#ifndef COVER_CLOSE_BACKLIGHT_OFF
#define COVER_CLOSE_BACKLIGHT_OFF   (1)
#endif

#ifndef COVER_CLOSE_FLOW
#define COVER_CLOSE_FLOW            (COVER_CLOSE_POWER_OFF)
#endif

//UI OSD Draw Icon
#ifndef DRAW_EV_MAIN_PAGE_ENABLE
#define DRAW_EV_MAIN_PAGE_ENABLE       (0)
#endif

//Menu Setting
#ifndef MENU_STYLE
#define MENU_STYLE                     (0)
#endif

#ifndef MENU_AUDIO_DEFAULT_LOUD
#define MENU_AUDIO_DEFAULT_LOUD        (0)
#endif

#ifndef ENABLE_AUTO_LOCKFILE_JPG
#define ENABLE_AUTO_LOCKFILE_JPG       (0)
#endif

#ifndef ENABLE_CAPTURE_STABILIZER
#define ENABLE_CAPTURE_STABILIZER      (0)
#endif

#ifndef ENABLE_VIDEO_LED_ON_WHILE_VR
#define ENABLE_VIDEO_LED_ON_WHILE_VR   (0)
#endif

#ifndef VIDEO_REC_WITH_MUTE_EN
#define VIDEO_REC_WITH_MUTE_EN         (0)
#endif

#ifndef SW_STICKER_EN
#define SW_STICKER_EN                  (0)
#endif

#ifndef STICKER_DRAW_EDGE         
#define STICKER_DRAW_EDGE              (0)
#endif 

#ifndef VIDEO_EARLY_START_1920_LINE_NO
#define VIDEO_EARLY_START_1920_LINE_NO  (256)
#endif

#ifndef VIDEO_EARLY_START_1280_LINE_NO
#define VIDEO_EARLY_START_1280_LINE_NO  (128)
#endif

#ifndef VIDEO_EARLY_START_720_LINE_NO
#define VIDEO_EARLY_START_720_LINE_NO   (64)
#endif

#ifndef VIDEO_EARLY_START_640_LINE_NO
#define VIDEO_EARLY_START_640_LINE_NO   (16)
#endif

//Video Record Emergency
#ifndef EMERGENCY_RECODE_NONE
#define EMERGENCY_RECODE_NONE           (0)
#endif
#ifndef EMERGENCY_RECODE_DUAL_FILE
#define EMERGENCY_RECODE_DUAL_FILE      (1)
#endif
#ifndef EMERGENCY_RECODE_SWITCH_FILE
#define EMERGENCY_RECODE_SWITCH_FILE    (2)
#endif
#ifndef EMERGENCY_RECODE_MOVE_FILE
#define EMERGENCY_RECODE_MOVE_FILE      (3)
#endif
#ifndef EMERGENCY_RECODE_FLOW_TYPE
#define EMERGENCY_RECODE_FLOW_TYPE      (EMERGENCY_RECODE_NONE)
#endif
#ifndef EMERGENTRECD_SUPPORT
#define EMERGENTRECD_SUPPORT            (0)
#endif

#ifndef SD_FW_REMOVE_SD_UPDATE_FILE
#define SD_FW_REMOVE_SD_UPDATE_FILE     (0)
#endif

#ifndef SD_FW_UPDATER_BIN_NAME
#define SD_FW_UPDATER_BIN_NAME          ("SD:\\SD_CarDV.bin")
#define SD_WP_FAT_BIN_NAME              ("SD:\\SD_WpFat.bin")
#define SD_WP_BAK_BIN_NAME              ("SD:\\SD_WpDataBak.bin")
#define SD_WP_BASENAME                  ("SD:\\SD_WpData")
#define SD_WP_EXTNAME                   (".txt")
#endif

#ifndef SD_FW_DUMP_BIN_NAME
#define SD_FW_DUMP_BIN_NAME          ("SD:\\DumpNor2SD.bin")
#endif

#ifndef SD_FW_UPDATER_LOG_NAME
#define SD_FW_UPDATER_LOG_NAME          ("SD:\\update.log")
#endif

#ifndef BIND_LCD_ILI9341_RGB
#define BIND_LCD_ILI9341_RGB            (0)
#endif

#ifndef BIND_LCD_OTA5184A
#define BIND_LCD_OTA5184A               (0)
#endif

#ifndef BIND_LCD_HX8357C
#define BIND_LCD_HX8357C                  (0)
#endif

#ifndef BIND_LCD_ILI9341
#define BIND_LCD_ILI9341                  (0)
#endif

#ifndef CFG_BATTERY_EMPTY_WARNING_DELAY_TIME
#define CFG_BATTERY_EMPTY_WARNING_DELAY_TIME    1000
#endif

#ifndef CFG_ENABLE_HDMI_HPD
#define CFG_ENABLE_HDMI_HPD             (1)
#endif

#ifndef CFG_ENABLE_TV_HPD
#define CFG_ENABLE_TV_HPD               (1)
#endif

// bit mapping for PWR_ON_SRC
//#define PWR_ON_BY_KEY                 0x01
//#define PWR_ON_BY_VBUS                    0x02
//#define PWR_ON_BY_GSENSOR             0x04
//#define PWR_ON_BY_IR                  0x08
//#define PWR_ON_BY_DC                  0x10

#define DETECT_SD_BY_TIMER              (1)
#if (DETECT_SD_BY_TIMER)
#define DETECT_SD_BY_OS_TIMER           (1)
#endif

#ifndef DIR_KEY_TYPE
#define DIR_KEY_TYPE                    (KEY_TYPE_2KEY)
#endif

#ifndef DEVICE_GPIO_DC_INPUT_LEVEL
#define DEVICE_GPIO_DC_INPUT_LEVEL      (0)
#endif

#ifndef NO_CARD_POWER_OFF_EN
#define NO_CARD_POWER_OFF_EN            (0)
#endif

#ifndef BUTTON_BIND_LED
#define BUTTON_BIND_LED                 (0)
#endif

#ifndef POWER_ON_BY_GSENSOR_EN
#define POWER_ON_BY_GSENSOR_EN          (0)
#endif

#ifndef GSENSOR_INT_ACT_LEVEL
#define GSENSOR_INT_ACT_LEVEL           (0)
#endif

#ifndef GSNR_GROUND_AXIS
#define GSNR_GROUND_AXIS                (0)
#endif

#ifndef IR_KEY_EN
#define IR_KEY_EN                       (0)
#endif

#ifndef COMBO_KEY_EN
#define COMBO_KEY_EN                    (0)
#endif

#ifndef PANEL_OSD_FILP_ENABLE
#define PANEL_OSD_FILP_ENABLE           (0)
#endif

#ifndef LCD_ROTATE_WITH_HALL_SENSOR
#define LCD_ROTATE_WITH_HALL_SENSOR     (0)
#endif

#ifndef SENSOR_FLIP_ENABLE
#define SENSOR_FLIP_ENABLE              (0)
#endif

#ifndef MENU_MOVIE_GSENSOR_SENSITIVITY_XYZ_EN
#define MENU_MOVIE_GSENSOR_SENSITIVITY_XYZ_EN       (0)
#endif

#ifndef BATTERY_DETECT_ADC_CHANNEL
#define BATTERY_DETECT_ADC_CHANNEL      (0)     // SAR ADC0
#endif

#ifndef ADC_KEY_SARADC_CHANNEL
#define ADC_KEY_SARADC_CHANNEL          (1)     // SAR ADC1
#endif

#ifndef TEMPERATURE_SARADC_CHANNEL
#define TEMPERATURE_SARADC_CHANNEL      (2)     // SAR ADC2
#endif

#ifndef USB_PATH_SELECT_GPIO_ACT_LEVEL
#define USB_PATH_SELECT_GPIO_ACT_LEVEL  (GPIO_HIGH)
#endif

// For Battery Detect Circuit
#ifndef REAL_BAT_VOLTAGE_RATIO_N
#define REAL_BAT_VOLTAGE_RATIO_N        (5)
#endif

#ifndef REAL_BAT_VOLTAGE_RATIO_M
#define REAL_BAT_VOLTAGE_RATIO_M        (17)
#endif

#ifndef DEVICE_GPIO_DC_INPUT
#define DEVICE_GPIO_DC_INPUT            (MMP_GPIO_MAX)
#endif

#ifndef CFG_DBG_SET_PSEN_TO_INPUT
#define CFG_DBG_SET_PSEN_TO_INPUT       (0)
#endif

#ifndef LDWS_WARN_MIN_SPEED
#define LDWS_WARN_MIN_SPEED             (60)
#endif

#ifndef ENABLE_ADAS_LDWS
#define ENABLE_ADAS_LDWS                (0)
#endif

#ifndef ENABLE_ADAS_FCWS
#define ENABLE_ADAS_FCWS                (0)
#endif

#ifndef ENABLE_ADAS_SAG
#define ENABLE_ADAS_SAG                 (0)
#endif

#ifndef FCWS_WARN_DISTANCE
#define FCWS_WARN_DISTANCE              (10)
#endif

#ifndef TOUCH_UART_FUNC_EN
#define TOUCH_UART_FUNC_EN                      (0)
#endif

#ifndef TPMS_FUNC_EN
#define TPMS_FUNC_EN                    (0)
#endif

// Factory Mode
#ifndef SUPPORT_FACTORY_MODE
#define SUPPORT_FACTORY_MODE            0
#endif

#ifndef CLOCK_SETTING_TIME_LIMIT
#define CLOCK_SETTING_TIME_LIMIT        (0)
#endif

#ifndef ESD_SW_PATCH
#define ESD_SW_PATCH                    (0)
#endif

#ifndef WAIT_BDEVICE_SHUTDOWN_INTERVAL
#define WAIT_BDEVICE_SHUTDOWN_INTERVAL  (2000)
#endif

#ifndef OSD_PREVIEW_SCALE_HDMI
#define OSD_PREVIEW_SCALE_HDMI          (1)
#endif

#ifndef OSD_DISPLAY_SCALE_HDMI_FHD
#define OSD_DISPLAY_SCALE_HDMI_FHD      (4)
#endif

#ifndef OSD_DISPLAY_SCALE_HDMI_HD
#define OSD_DISPLAY_SCALE_HDMI_HD       (2)
#endif

#ifndef OSD_DISPLAY_SCALE_TV
#define OSD_DISPLAY_SCALE_TV            (2)
#endif

#ifndef OSD_DISPLAY_SCALE_LCD
#define OSD_DISPLAY_SCALE_LCD           (0)     // 0: mean no duplicate, same as 1x
#endif

/* For Store LCD/Sensor/TV/HDMI Status To SF Offset */
#ifndef SETTING_TOTAL_ITEMS
#define SETTING_TOTAL_ITEMS             (6)     // include check sum
#endif

#ifndef SETTING_CHECK_VALUE
#define SETTING_CHECK_VALUE             (0xFF)
#endif

#ifndef MENU_STATUS_REGION_SIZE
#define MENU_STATUS_REGION_SIZE         (256)

#undef  TV_SYSTEM_SETTING_OFFSET
#undef  HDMI_SYSTEM_SETTING_OFFSET
#undef  SNR_STATUS_OFFSET
#undef  LCD_STATUS_OFFSET
#undef  LCD_MENU_SETTING_OFFSET
#undef  SETTING_CHECKSUM

#define TV_SYSTEM_SETTING_OFFSET        (MENU_STATUS_REGION_SIZE-6)
#define HDMI_SYSTEM_SETTING_OFFSET      (MENU_STATUS_REGION_SIZE-5)
#define SNR_STATUS_OFFSET               (MENU_STATUS_REGION_SIZE-4)
#define LCD_STATUS_OFFSET               (MENU_STATUS_REGION_SIZE-3)
#define LCD_MENU_SETTING_OFFSET         (MENU_STATUS_REGION_SIZE-2)
#define SETTING_CHECKSUM                (MENU_STATUS_REGION_SIZE-1)
#endif

/*===========================================================================
 * MISC Config
 *===========================================================================*/

#ifndef SARADC_REFERENCE_VOLTAGE
#define SARADC_REFERENCE_VOLTAGE    (3300)
#endif

#ifndef SARADC_FULL_SCALE
#define SARADC_FULL_SCALE           (1023)
#endif

#ifndef RTC_FORCE_DEFAULT_TIME
#define RTC_FORCE_DEFAULT_TIME      (0)
#endif

#ifndef SUPPORT_DTV_TOUCH_REMOTE
#define SUPPORT_DTV_TOUCH_REMOTE    (0)
#endif

#ifndef FORMAT_FREE_ENABLE
#define FORMAT_FREE_ENABLE          (0)
#endif

#ifndef FS_FORMAT_FREE_ENABLE
#define FS_FORMAT_FREE_ENABLE       (0)
#endif

#ifndef AHC_VR_THUMBNAIL_JPG_ENABLE
#define AHC_VR_THUMBNAIL_JPG_ENABLE     (0)
#endif

#ifndef SCALE_UP_REC_HD_TO_FHD_TEST
#define SCALE_UP_REC_HD_TO_FHD_TEST (0)
#endif

/*===========================================================================
 *  IQ setting
 *===========================================================================*/

#ifndef CUS_DO_AWB_OPERATION
#define CUS_DO_AWB_OPERATION    (0)
#endif

/*===========================================================================
 *  Wifi setting
 *===========================================================================*/
#ifndef MJPEG_STREAM_BUF_W
#define MJPEG_STREAM_BUF_W    (0)
#endif

#ifndef MJPEG_STREAM_BUF_H
#define MJPEG_STREAM_BUF_H    (0)
#endif

#endif  // _CONFIG_DUMMY_H_
