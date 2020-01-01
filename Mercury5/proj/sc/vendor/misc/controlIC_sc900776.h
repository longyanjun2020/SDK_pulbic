/*
* Bigbang project
* Copyright (c) 2009 VPS R&D Group, Samsung Electronics, Inc.
* All rights reserved.
*
* This software is the confidential and proprietary information
* of Samsung Electronics, Inc. ("Confidential Information").  You
* shall not disclose such Confidential Information and shall use
* it only in accordance with the terms of the license agreement
* you entered into with Samsung Electronics.
*/

/**
* This file defines data structures and APIs for Freescale SC900776
*
* @name    sc900776.h
* @author  Eung Chan Kim (eungchan.kim@samsung.com)
* @version 0.1
* @see
*/

#ifndef _CONTROLIC_SC900776_H_
#define _CONTROLIC_SC900776_H_


typedef enum
{
	SC900776_DEVICE_ID = 0x01,		/* 01h		R   */
	SC900776_CONTROL,				/* 02h		R/W */
	SC900776_INTERRUPT1,			/* 03h		R/C */
	SC900776_INTERRUPT2,			/* 04h		R/C */
	SC900776_INTERRUPT_MASK1,		/* 05h		R/W */
	SC900776_INTERRUPT_MASK2,		/* 06h		R/W */
	SC900776_ADC_RESULT,			/* 07h		R   */
	SC900776_TIMING_SET1,			/* 08h		R/W */
	SC900776_TIMING_SET2,			/* 09h		R/W */
	SC900776_DEVICE_TYPE1,			/* 0Ah		R   */
	SC900776_DEVICE_TYPE2,			/* 0Bh		R   */
	SC900776_BUTTON1,				/* 0Ch		R/C */
	SC900776_BUTTON2,				/* 0Dh		R/C */
	/* 0Eh ~ 12h : reserved */
	SC900776_MANUAL_SWITCH1 = 0x13,	/* 13h		R/W */
	SC900776_MANUAL_SWITCH2, 		/* 14h		R/W */
	/* 15h ~ 1Fh : reserved */
	SC900776_FSL_STATUS = 0x20, 	/* 20h		R   */
	SC900776_FSL_CONTROL,			/* 21h		R/W */
	SC900776_TIME_DELAY,			/* 22h		R/W */
	SC900776_DEVICE_MODE,			/* 23h		R/W */

	SC900776_REG_MAX
} eSc900776_register_t;

typedef enum
{
	DEVICETYPE1_UNDEFINED = 0,
	DEVICETYPE1_USB,				//0x04 0x00	//Normal usb cable & ad200
	DEVICETYPE1_DEDICATED, 			//0x40 0x00	//Dedicated charger cable
	DEVICETYPE2_JIGUARTON,			//0x00 0x08	//Anyway_UART_Jig
	DEVICETYPE2_JIGUSBOFF,			//0x00 0x01	//301K, Recovery_USB_Cable
	DEVICETYPE2_JIGUSBON			//0x00 0x02	//255K, Anyway_USB_Jig
} eMinivet_device_t;

/*
 * sc900776 register bit definitions
 */
#define MINIVET_DEVICETYPE1_USBOTG 		0x80	/* 1: a USBOTG device is attached */
#define MINIVET_DEVICETYPE1_DEDICATED 	0x40	/* 1: a dedicated charger is attached */
#define MINIVET_DEVICETYPE1_USBCHG 		0x20	/* 1: a USB charger is attached */
#define MINIVET_DEVICETYPE1_5WCHG 		0x10	/* 1: a 5-wire charger (type 1 or 2) is attached */
#define MINIVET_DEVICETYPE1_UART 		0x08	/* 1: a UART cable is attached */
#define MINIVET_DEVICETYPE1_USB 		0x04	/* 1: a USB host is attached */
#define MINIVET_DEVICETYPE1_AUDIO2 		0x02	/* 1: an audio accessory type 2 is attached */
#define MINIVET_DEVICETYPE1_AUDIO1 		0x01	/* 1: an audio accessory type 1 is attached */

#define MINIVET_DEVICETYPE2_AV			0x40	/* 1: an audio/video cable is attached */
#define MINIVET_DEVICETYPE2_TTY			0x20	/* 1: a TTY converter is attached */
#define MINIVET_DEVICETYPE2_PPD			0x10	/* 1: a phone powered device is attached */
#define MINIVET_DEVICETYPE2_JIGUARTON 	0x08	/* 1: a UART jig cable with the BOOT-on option is attached */
#define MINIVET_DEVICETYPE2_JIGUARTOFF 	0x04	/* 1: a UART jig cable with the BOOT-off option is attached */
#define MINIVET_DEVICETYPE2_JIGUSBON 	0x02	/* 1: a USB jig cable with the BOOT-on option is attached */
#define MINIVET_DEVICETYPE2_JIGUSBOFF 	0x01	/* 1: a USB jig cable with the BOOT-off option is attached */

#define MINIVET_FSLSTATUS_FETSTATUS		0x40	/* 1: The on status of the power MOSFET */
#define MINIVET_FSLSTATUS_IDDETEND		0x20	/* 1: ID resistance detection finished */
#define MINIVET_FSLSTATUS_VBUSDETEND	0x10	/* 1: VBUS power supply type identification completed */
#define MINIVET_FSLSTATUS_IDGND			0x08	/* 1: ID pin is shorted to ground */
#define MINIVET_FSLSTATUS_IDFLOAT		0x04	/* 1: ID line is floating */
#define MINIVET_FSLSTATUS_VBUSDET		0x02	/* 1: VBUS voltage is higher than the POR */
#define MINIVET_FSLSTATUS_ADCSTATUS		0x01	/* 1: ADC conversion completed */


#define SC900776_I2C_SLAVE_ADDR			0x4A    //AIT_PMP,20100319


void scSwitchUSBPath(void);



#endif /* __MINIVET_IOCTL_H__ */
