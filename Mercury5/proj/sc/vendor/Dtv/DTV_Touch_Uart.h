
#ifndef _TOUCH_UART_DRIVER_H_
#define _TOUCH_UART_DRIVER_H_

/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "mmpf_typedef.h"
#include "Touch_Uart_ctrl.h"
/*===========================================================================
 * Macro define
 *===========================================================================*/
#ifndef DTV_UART_NUM
#define DTV_UART_NUM                    (MMP_UART_ID_2)
#endif
#ifndef DTV_UART_PADSET
#define DTV_UART_PADSET                 (MMP_UART_PADSET_2)
#endif
#define Uart_RX_QUEUE_SIZE               (256)
#define Uart_RX_SIGNAL                   (0xFE)
#ifndef DTV_UART_BAUD_RATE
#define DTV_UART_BAUD_RATE                   (57600)//(115200)
#endif
#define DTV_UART_CLK                    (264000 >> 1)

#define HEAD1_S680                  0XFF
#define HEAD2_S680                  0XAA


#define TAIL1_S680                  0XFF
#define TAIL2_S680                  0XFE


/*===========================================================================
 * Enum define
 *===========================================================================*/
typedef enum _DTVCOMMAND_ID // 
{
	DTVCMD_TOUCH_DEFAULT   	= 0xA0,
	DTVCMD_TOUCH_PRESS	= 0xA1,
	DTVCMD_TOUCH_RELEASE	= 0xA2,
	DTVCMD_KEY	= 0xA3,
	DTVCMD_TIME	= 0xA4,
	DTVCMD_DATE	= 0xA5
} UARTCOMMAND_ID;



typedef enum _KEY_VAL
{
	KEY_CH_UP =0x80,
	KEY_CH_DOWN = 0x81,
	KEY_VOL_UP = 0x82,
	KEY_VOL_DOWN = 0x83,
	KEY_PAGE_UP = 0x84,
	KEY_MENU = 0x85,
	KEY_PAUSE = 0x86,
	KEY_EXIT = 0x87,
	KEY_RECALL = 0x88,
	KEY_INFO_VAL = 0x89,
	KEY_POWER = 0x8A,
	KEY_PAGE_DOWN = 0x8B,
	KEY_MUTE = 0x8C,
	KEY_REServed = 0x8D,
	KEY_VAL_0 = 0x90,
	KEY_VAL_1 = 0x91,
	KEY_VAL_2 = 0x92,
	KEY_VAL_3 = 0x93,
	KEY_VAL_4 = 0x94,
	KEY_VAL_5 = 0x95,
	KEY_VAL_6 = 0x96,
	KEY_VAL_7 = 0x97,
	KEY_VAL_8 = 0x98,
	KEY_VAL_9 = 0x99,
	KEY_CAPTURE = 0xA0,
	KEY_LOCK = 0xA1,
	KEY_FRCAM_SWITCH = 0xA2
	
} KEY_VAL;

typedef struct tagKeyButton
{
    unsigned char  iCmdId;
    unsigned char  ulkeyEvent; 
	unsigned char  ubkeyname[16];
} CMDKEY;

/*===========================================================================
 * Structure define
 *===========================================================================*/
extern MMPF_OS_FLAGID   	UartCtrlFlag;
#if (DTV_UART_SEND_LDWS)
extern AHC_BOOL DTV_UART_Get_LDWS(void);
#endif
#if (DTV_UART_SEND_FCWS)
extern AHC_BOOL  DTV_UART_Get_FCWS(void);
#endif
#endif // _TOUCH_UART_DRIVER_H_
