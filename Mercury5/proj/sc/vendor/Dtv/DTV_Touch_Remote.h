#ifndef _IR_TOUCH_REMOTE_H_
#define _IR_TOUCH_REMOTE_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 
#include "Customer_config.h"

#include "ahc_common.h"
//#include "ahc_general.h" 
#include "IR_IRC120x.h"

#define DTV_IR_ID  0x55AA
#define DTV_IR_ID1 0x99AA
#define DTV_IR_ID2 0xAA55
#define DTV_IR_ID3 0xEA01

typedef enum _Remote_KEY_VAL
{
	KEY_LEFT	 = 0x05,
	KEY_UP		 = 0x16,
	KEY_DOWN 	 = 0x0D,
	KEY_RIGHT 	 = 0x19,
	KEY_MENU	 = 0x1C,
	KEY_OK		 = 0x0F,
	KEY_EXIT	 = 0x18,
	KEY_POWER	 = 0x12,
	KEY_MUTE	 = 0x14,

    MAX_KEY_VAL  = 0xFF
} Remote_KEY_VAL;

typedef struct tagRemote_KeyButton
{
    unsigned char  iCmdId;
    unsigned char  ulkeyEvent; 
	unsigned char  ubkeyname[16];
} CMDREMOTEKEY;

AHC_BOOL DTV_Touch_GetIrData(void);
void DTV_Touch_ParserData(IR_DATA data);
void DTV_Touch_SetIrStatus(void);

#endif
