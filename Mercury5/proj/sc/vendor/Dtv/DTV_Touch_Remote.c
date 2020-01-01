#include "Customer_config.h"

#include "ahc_common.h" 
#include "DTV_Touch_Remote.h"
#include "AHC_message.h"
#include "ahc_os.h"

#if (SUPPORT_DTV_TOUCH_REMOTE)

MMP_ULONG  ulParm;

static const CMDREMOTEKEY CmdKey[] =
{
  	{KEY_UP,		KEY_PRESS_UP,		"KEY UP"	    },
  	{KEY_DOWN,		KEY_PRESS_DOWN,		"KEY DOWN"		},
  	{KEY_RIGHT,		KEY_PRESS_RIGHT,	"KEY RIGHT"	},
  	{KEY_LEFT,		KEY_PRESS_LEFT,		"KEY LEFT"		},
  	{KEY_OK,		KEY_PRESS_OK,		"KEY OK "	},

  	{KEY_MENU,		KEY_REL_MENU,		"KEY MENU"	},
  	{KEY_EXIT,		KEY_REL_MODE,		"KEY EXIT"	},
  	{KEY_POWER,		KEY_REL_POWER,		"KEY POWER"	},
  	{KEY_MUTE,		KEY_PRESS_MUTE,		"KEY MUTE"	},
  	
};

static MMP_UBYTE	gNumOfCMDIDKey = sizeof(CmdKey) / sizeof(CMDREMOTEKEY);

void DTV_Touch_SetKEY(MMP_BYTE pBuff)
{
    MMP_UBYTE i = 0;

    printc("DTV_Touch_SetKEY  \r\n");
    for( i=0; i<gNumOfCMDIDKey ; i++ )
    {
        if(CmdKey[i].iCmdId == pBuff)
        {
            SetKeyPadEvent(CmdKey[i].ulkeyEvent);
            printc("%s \r\n",CmdKey[i].ubkeyname);
        }
    }
}

void DTV_Touch_ParserData(IR_DATA data)
{
	MMP_USHORT TemppX,TemppY;
	MMP_UBYTE ID_H,ID_L;
	MMP_UBYTE ID_H1,ID_L1;
	MMP_UBYTE ID_H2,ID_L2;
	MMP_UBYTE ID_H3,ID_L3;
	
	ID_H = (DTV_IR_ID >> 8)& 0xff;
	ID_L = DTV_IR_ID & 0xff;
	ID_H1 = (DTV_IR_ID1 >> 8)& 0xff;
	ID_L1 = DTV_IR_ID1 & 0xff;	
	ID_H2 = (DTV_IR_ID2 >> 8)& 0xff;
	ID_L2 = DTV_IR_ID2 & 0xff;	
	ID_H3 = (DTV_IR_ID3 >> 8)& 0xff;
	ID_L3 = DTV_IR_ID3 & 0xff;	
	
	//if((data.data0  == 0xAA)&&(data.data1== 0x55))
	if(((ID_L == data.data0 )&&(ID_H == data.data1))
		||((ID_L1 == data.data0 )&&(ID_H1 == data.data1))
		||((ID_L2 == data.data0 )&&(ID_H2 == data.data1))
		)
	{
		TemppX = (MMP_USHORT)data.data2 * DISP_WIDTH/255;
		TemppY = (MMP_USHORT)data.data3 * DISP_HEIGHT/255 ;
		ulParm =  TemppY<<16 | TemppX;
		SetKeyPadEvent(TOUCH_PANEL_PRESS);
	}
	else if((ID_L3 == data.data0)&&(ID_H3 == data.data1))
	{
         //TBD
         DTV_Touch_SetKEY(data.data2);
	}
	else
	{
        printc("err .Customer ID  0x%x... \r\n",(MMP_USHORT)data.data1<<8|data.data0);
	}
}

AHC_BOOL DTV_Touch_GetIrData(void)
{
    MMP_ERR ret_val;
	IR_DATA Data;
	
    ret_val = IR_Ctrl_GetIrData(&Data);
	printc("\r\n Data %x %x %x %x\r\n",Data.data0,Data.data1,Data.data2,Data.data3);
	DTV_Touch_ParserData(Data);

    return AHC_TRUE;
}

MMP_UBYTE status = AHC_FALSE;

AHC_BOOL DTV_Touch_GetIrStatus(void)
{	
	if(status)
	{
		status = AHC_FALSE;
		return AHC_TRUE;
	}
	else
		return AHC_FALSE;

}

void DTV_Touch_SetIrStatus(void)
{	
	printc("DTV_Touch_SetIrStatus \r\n");
	 status = AHC_TRUE;
}

void DTV_Touch_CheckUpdate(MMP_ULONG* pulKeyEvent, UINT32* pulPosition)
{
  if(*pulKeyEvent !=KEYPAD_NONE)
    *pulPosition = ulParm;
  else
  	*pulPosition = 0;
}

#endif
