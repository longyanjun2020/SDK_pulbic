//==============================================================================
//
//  File        : ahc_pwm.h
//  Description : INCLUDE File for the AHC PWM function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_PWM_H_
#define _AHC_PWM_H_

/*===========================================================================
 * Include files
 *===========================================================================*/
 
#include "ahc_common.h"
#include "mmp_pwm_inc.h"
#include "drv_pwm.h"
#include "drv_gpio.h"

/*===========================================================================
 * Enum define
 *===========================================================================*/
typedef enum
{
	//CMD EXT:io pwm 3 3 6000 0 50 0
	LCD_D10_PWM2_PWMD1_MOTOR1_R		= MMP_PWM2_PIN, //DRV_IO_LCD_GPIO10,	//mode3
	LCD_D11_PWM3_DRV1_MOTOR1_F		= MMP_PWM3_PIN, //DRV_IO_LCD_GPIO11,	//mode3

	LCD_D12_PWM4_PWMD2_MOTOR2_R		= MMP_PWM4_PIN, //DRV_IO_LCD_GPIO12,	//mode3
	LCD_D13_PWM5_DRV2_MOTOR2_F 		= MMP_PWM5_PIN, //DRV_IO_LCD_GPIO13,	//mode3

	LCD_D14_PWM6_PWMD3_CAM2_SPD		= MMP_PWM6_PIN, //DRV_IO_LCD_GPIO14,	//mode3
	LCD_D15_PWM7_DRV3_CAM2_FLAP 	= MMP_PWM7_PIN, //DRV_IO_LCD_GPIO15 	//mode3

} CustPinUse2PwmName;

typedef enum
{
	//CMD EXT:io gpio 57 0 1
	LCD_D10_PWM2_PWMD1_MOTOR1_R_IO		= DRV_IO_LCD_GPIO10,
	LCD_D11_PWM3_DRV1_MOTOR1_F_IO		= DRV_IO_LCD_GPIO11,
	
	LCD_D12_PWM4_PWMD2_MOTOR2_R_IO		= DRV_IO_LCD_GPIO12,
	LCD_D13_PWM5_DRV2_MOTOR2_F_IO		= DRV_IO_LCD_GPIO13,
	
	LCD_D14_PWM6_PWMD3_CAM2_SPD_IO		= DRV_IO_LCD_GPIO14,	
	LCD_D15_PWM7_DRV3_CAM2_FLAP_IO		= DRV_IO_LCD_GPIO15, 
	
	DRV_PM_PWM0_DRV4_WIRE_FLAP_IO		= DRV_IO_PM_GPIO0,	//PM_GPIO0
	DRV_PM_PWM2_DRV5_WIRE_REL_IO		= DRV_IO_PM_GPIO2,	//PM_GPIO2
	
	DRV_PM_PWM1_LED_EN_IO				= DRV_IO_PM_GPIO5,	//PM_GPIO5
} CustPinUse2GpioName;

typedef enum
{
	DEAD_AHEAD			= 0X10,
	FRONT_LEFT,
	FRONT_RIGHT,
	DEAD_ASTERN,
	LEFT_REAR,
	RIGHT_REAR,
	
	STOP_ALL			= 0X20,
	STOP_MOT1,
	STOP_MOT2,
	
	FLAP_CAM2			= 0X30,
	RELEASE_CAM2,

	CLIP_WIRE			= 0X40,
	RELEASE_WIRE,

	NET_LED_EN			= 0X50,
	PWM_ACTION_NONE		= 0XFF,
} CustRemoterWorkMode;



#define	GPIO_OUTPUT(PIN,VAL)	do{	\
									DrvGPIOPadSet(PIN,1);\
									DrvGPIOOutputEnable(PIN,1);\
									DrvGPIOSetOutputData(PIN,VAL);\
								}while(0)
								
#define MOTOR1_FORWARD(ulDuty)	do{\
									GPIO_OUTPUT(LCD_D10_PWM2_PWMD1_MOTOR1_R_IO,MMP_FALSE);\
									MMPS_PWM_SetOutputPin(LCD_D11_PWM3_DRV1_MOTOR1_F,DRV_PWM_PAD_MODE3);\
									MMPS_PWM_OutputPulse(LCD_D11_PWM3_DRV1_MOTOR1_F,0,1000,ulDuty, MMP_TRUE, MMP_FALSE, NULL, 0);\
								}while(0)
#define MOTOR1_REAR(ulDuty)		do{\
									GPIO_OUTPUT(LCD_D11_PWM3_DRV1_MOTOR1_F_IO,MMP_FALSE);\
									MMPS_PWM_SetOutputPin(LCD_D10_PWM2_PWMD1_MOTOR1_R,DRV_PWM_PAD_MODE3);\
									MMPS_PWM_OutputPulse(LCD_D10_PWM2_PWMD1_MOTOR1_R,0,1000,ulDuty, MMP_TRUE, MMP_FALSE, NULL, 0);\
								}while(0)
#define MOTOR1_STOP(ulDuty)		do{\
									GPIO_OUTPUT(LCD_D11_PWM3_DRV1_MOTOR1_F_IO,MMP_FALSE);\
									GPIO_OUTPUT(LCD_D10_PWM2_PWMD1_MOTOR1_R_IO,MMP_FALSE);\
								}while(0)

#define MOTOR2_FORWARD(ulDuty)	do{\
									GPIO_OUTPUT(LCD_D12_PWM4_PWMD2_MOTOR2_R_IO,MMP_FALSE);\
									MMPS_PWM_SetOutputPin(LCD_D13_PWM5_DRV2_MOTOR2_F,DRV_PWM_PAD_MODE3);\
									MMPS_PWM_OutputPulse(LCD_D13_PWM5_DRV2_MOTOR2_F,0,1000,ulDuty, MMP_TRUE, MMP_FALSE, NULL, 0);\
								}while(0)
#define MOTOR2_REAR(ulDuty)		do{\
									GPIO_OUTPUT(LCD_D13_PWM5_DRV2_MOTOR2_F_IO,MMP_FALSE);\
									MMPS_PWM_SetOutputPin(LCD_D12_PWM4_PWMD2_MOTOR2_R,DRV_PWM_PAD_MODE3);\
									MMPS_PWM_OutputPulse(LCD_D12_PWM4_PWMD2_MOTOR2_R,0,1000,ulDuty, MMP_TRUE, MMP_FALSE, NULL, 0);\
								}while(0)
#define MOTOR2_STOP(ulDuty)		do{\
									GPIO_OUTPUT(LCD_D12_PWM4_PWMD2_MOTOR2_R_IO,MMP_FALSE);\
									GPIO_OUTPUT(LCD_D13_PWM5_DRV2_MOTOR2_F_IO,MMP_FALSE);\
								}while(0)

/*===========================================================================
 * Function Prototype
 *===========================================================================*/
// PWM Function
AHC_BOOL 	AHC_PWM_Initialize(void);
AHC_BOOL 	AHC_PWM_OutputPulse(MMP_PWM_PIN pwm_pin, AHC_BOOL bEnableIoPin, UINT32 ulFrquency, AHC_BOOL bHigh2Low, AHC_BOOL bEnableInterrupt, void* pwm_callBack, UINT32 ulNumOfPulse);
AHC_BOOL 	AHC_PWM_OutputPulseEx(MMP_PWM_PIN pwm_pin, AHC_BOOL bEnableIoPin, UINT32 ulFrquency, UINT32 ulDuty, AHC_BOOL bHigh2Low, AHC_BOOL bEnableInterrupt, void* pwm_callBack, UINT32 ulNumOfPulse);
AHC_BOOL	AHC_PWM_MotorCtrl(UINT32 ulEvent, UINT32 ulParam);
#endif
