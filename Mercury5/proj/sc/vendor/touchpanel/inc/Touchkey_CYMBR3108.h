
#ifndef _CYMBR3108_TOUCH_KEY_H_
#define _CYMBR3108_TOUCH_KEY_H_

//#include "customer_config.h"
#include "mmpf_typedef.h"
#include "dsc_Key.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/
#define SEND_PANEL_CONFIG                   0
#define CUSTOM_CONFIG                       0

//register address 
#define REG_CONFIG_VERSION                  0x8047
#define REG_IC_VERSION                      0x8140
#define REG_SENSOR_ID                       0x814A
#define REG_COOR_STATUS                     0x814E
#define REG_COOR_ADDR                       0x814F

#define CONFIG_MAX_LENGTH                   240

#define MMP_GPIO_PULL_LOW                   0x22
#define MMP_GPIO_PULL_HIGH                  0x24

#define TOUCH_PANEL_I2C_SLAVE_ADDRESS 	    (0x08<<1)  

#define RESOLUTION_INDEX                    1
#define TRIGGER_INDEX                       6
#define MAX_TOUCH_POINT                     5

#define GT911_ADC_STEPS_X                   (DISP_WIDTH)
#define GT911_ADC_STEPS_Y                   (DISP_HEIGHT)

// Specify your special config info if needed
#if CUSTOM_CONFIG
  #define MAX_HEIGHT   800
  #define MAX_WIDTH    480
  #define INT_TRIGGER  0            // 0: Rising 1: Falling
#else
  #define MAX_HEIGHT   4096
  #define MAX_WIDTH    4096
  #define INT_TRIGGER  1
#endif

#define APK_FUNC_KEY1		(KEY_REL_MODE)
#define APK_FUNC_KEY2		(KEY_PRESS_UP)//(KEY_REL_UP)
#define APK_FUNC_KEY3		(KEY_PRESS_DOWN)//(KEY_REL_DOWN)
#define APK_FUNC_KEY4		(KEY_REL_REC)
#define APK_FUNC_KEY5		(VIRTUAL_EVENT)//only use in processbar update

typedef enum {
    TOUCH_CHIP_STATUS_HWRST,
    TOUCH_CHIP_STATUS_POWERON,
    TOUCH_CHIP_STATUS_INIT,
    TOUCH_CHIP_STATUS_WAITDONE,
    TOUCH_CHIP_STATUS_READVALUE,
    TOUCH_CHIP_STATUS_GETEVENT,
    TOUCH_CHIP_STATUS_RESEED,
    TOUCH_CHIP_STATUS_CHECK_UPDATE,//Apical DXQ 20161103
    TOUCH_CHIP_STATUS_NONE
  } TouchChipStatus;


void TouchKeySetStatus(TouchChipStatus	TouchKeyStatus);
TouchChipStatus TouchKeyGetStatus(void);
#endif // _CYMBR3108_TOUCH_KEY_H_
