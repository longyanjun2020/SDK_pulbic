/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) $Date:   Mar 05 2004 16:58:20  $
*/

/****************************************************************************/
/*  File    : $Workfile:   rm_lcd.h  $       $Revision:   1.11  $           */
/*--------------------------------------------------------------------------*/
/*  Scope   : INFO_LCD message definition                                   */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Changes    :                                                            */
/*--------------------------------------------------------------------------*/
/*  Version PVCS  | Date           | Author |   Modification                */
/*--------------------------------------------------------------------------*/
/*																																					*/
/*   $LogWavecom: U:\projet\tools\pvcsarch\archives\Devel\Win32\Totem\RemoteTasks\Rte_Gateway\rm_lcd.h-arc $*/
/* --------------------------------------------------------------------------*/
/*  Date     | Author | Revision       | Description												 */
/* ----------+--------+----------------+-------------------------------------*/
/*  05.03.04 | gde    | 1.11           | Update for HANTIS touchpad          */
/* ----------+--------+----------------+-------------------------------------*/
/*  14.11.03 | gde    | 1.0            | Initial revision.                   */
/* ----------+--------+----------------+-------------------------------------*/
/****************************************************************************/
#include "vm_types.ht"
#include "panelinfo_pub.h"
#include "drv_lcd_info.h"

#ifndef __MSG_LCD__
#define __MSG_LCD__

#define MAX_SIZE_DATA_LCD        (MAIN_PANEL_WIDTH*MAIN_PANEL_HEIGHT*2+8)/*0x60000*///0x40000      /* (256ko)  */
//#define MAX_SIZE_DATA_LCD        (0x100000)/* PC only:1M*/
#define SIZE_NAME_PRODUCT	200		/* to be modified ?         */
#define	MSG_INFO_LCD_1		1		/* Main target interface    */
#define	MSG_INFO_LCD_2		2		/* Second target lcd        */

enum nHantisMsg
{
    HANTIS_INIT      ,/* 0 Initialize the LCD               */
    HANTIS_SCREEN    ,/* 1 Receive screen data for the LCD  */
    HANTIS_ICON      ,/* 2 Receive icon data                */
    HANTIS_CONTRAST  ,/* 3 Receive contrast level           */
    HANTIS_KEYBOARD  ,/* 4 Receive keyboard info            */
    HANTIS_TOUCHPAD   /* 5 Receive touchpad info            */
};

/***********************/
/*  Hantis structures  */
/***********************/

typedef struct
{
	int		nType;	/* Type of LCD message     */
					/*		0 Init,            */
					/*		1 Graph LCD,       */
					/*		2 Icon management  */
					/*		3 Contrast info    */
	char	buffData[MAX_SIZE_DATA_LCD];  /* Entrance of data */
} MsgLCD_t;

/****************************************************************/
/*		 nType = HANTIS_INIT =>	Initialization of the screen	*/
/****************************************************************/
typedef struct
{
	u16  nBitPixel;     /* Number of Bit per pixel  1 black & white    */
                        /*                          4 16 LCD colors    */
	char bGraphicLCD;   /* Text mode (0) or Graphic mode (1)		   */
	char bLineMode;     /* Display method : column (0) or line (1)	   */
	u32 nWidth;			/* Width of the screen                         */
	u32 nHeight;		/* Height of the screen                        */
	char strProduct[SIZE_NAME_PRODUCT];	/* Name of the product         */
	u16 iSpare1;		/* No more used. Previoulsy used by kbd message*/
	u16 iSpare2;		/* No more used. Previoulsy used by kbd message*/
	u16 m_iMaxContrast1;/* Maximum level contrast for LCD 1 */
	u16 m_iMaxContrast2;/* Maximum level contrast for LCD 2 */

} InitLCD_t;


/****************************************************************/
/*	 nType = HANTIS_SCREEN =>	LCD message in Graphic mode     */
/****************************************************************/
typedef struct
{
	u32 nSizeImage; /* size of BufferLCD */
	u16 nLeft;		/* Used by partial refresh */
	u16 nTop;
	u16 nRight;
	u16 nBottom;
	char BufferLCD[MAX_SIZE_DATA_LCD-8]; /* BMP Data */
} GraphLCDMsg_t;


/****************************************************************/
/*		 nType = HANTIS_ICON =>	Icon message			 		*/
/****************************************************************/
//#ifndef __KER_MISC_H__
typedef enum
{
   ICON_OFF  ,       //Important to keep ICON_OFF == 0, ICON_ON == 1 for lcd_main.c
   ICON_ON   ,
   ICON_FLASH,
   ICON_FLASH2,

   ICON_SKIP      /* JMO Add, avoid displaying the icon */

} IconState_t;
//#endif // __KER_MISC_H__

typedef struct
{
	int			nIdIcon;	/* Identificator of an icon	*/
	IconState_t	tStatus;	/* Status of an Icon		*/
} IconLCDMsg_t;


/****************************************************************/
/*		 nType = HANTIS_CONTRAST =>	Contrast level			    */
/****************************************************************/
/* See Hantis application / CMainFrame class                    */
/* u8  nContrast;   0->max   0 : Transparent                    */
/*                         max : Black                          */
/****************************************************************/



/****************************************************************/
/*	 nType = HANTIS_KEYBOARD =>	Receive Button info             */
/*	 nType = HANTIS_TOUCHPAD =>	Receive Touchpad info           */
/****************************************************************/
typedef struct
{
	u16 iMsgSendMbx;  /* Send mailbox DEV_MBX, see cus_os.hc and wm_osdef.hc */
	u16 iMsgDestMbx;  /* Destination mailbox MMI_MBX, see cus_os.hc and wm_osdef.hc */
	u16 iMsgBase; /* Message type WM_KBD_DATA_IND, see wm_kbd.hc and wm_msgofs.hc */
} KeyBoardMsg_t;



/**************************************/
/*  RemoteTasks function declaration  */
/**************************************/

#ifdef __SDK_SIMULATION__

#ifdef __SDK_SIMULATION_V2__
#include "MKernel_Display.h"
#else

#ifdef __cplusplus
#include "StdAfx.h"
	extern "C" void SendInfoLcdToHantisApp(MsgLCD_t* Info_Lcd_t, unsigned long dwSize, unsigned long dwLcd);
#else
	void SendInfoLcdToHantisApp(MsgLCD_t* Info_Lcd_t, unsigned long dwSize, unsigned long dwLcd);
#endif /*#ifdef __cplusplus*/

#endif /*#ifdef __SDK_SIMULATION_V2__*/
#endif


/*********************/
/*  Milk structures  */
/*********************/

typedef struct
{
	u8	chMark[4];  /* Mark of Milk message : chMark = "MILK" */
	u16	nLength;    /* Size of buffData                       */
	u8	chIdFlow;   /* Identicator of message (see HAPC mode) */
	u8	chPadding;
	u8	buffData[MAX_SIZE_DATA_LCD+8];
} MilkMsg_t;


#endif  /* __MSG_LCD__ */
