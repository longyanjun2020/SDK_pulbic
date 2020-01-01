/*===========================================================================
 * Include file
 *===========================================================================*/
#include "Customer_config.h"

#include "ait_utility.h"
#include "mmpf_uart.h"
#include "MenuSetting.h"
#include "ahc_os.h"
#include "ahc_parameter.h"
#include "AHC_message.h"
//#include "ahc_general.h"

#include "DTV_Touch_Uart.h"
#include "AIT_Init.h"
//#include "ahc_menu.h"
#if (DTV_UART_SEND_LDWS)
#include "ldws.h"
#endif
#if(DTV_UART_SEND_FCWS)
#include "fcws.h"
#endif
#if defined(__GNUC__)
#include "vm_types.ht"
#endif

/*===========================================================================
 * Macro define
 *===========================================================================*/

void printc(char* fmt, ...);

#ifdef _DEBUG_
#define	DPRINT( ... ) 	printc( __VA_ARGS__);
#else
#define	DPRINT( ... ) 	{}
#endif

/*===========================================================================
 * Global varible
 *===========================================================================*/

#if (TOUCH_UART_FUNC_EN)
#ifdef ALL_FW
static int 			m_bUartRxStrLen=0;
static MMP_BYTE 	m_bUartString[Uart_RX_QUEUE_SIZE] = {0};
static MMP_BOOL 	m_bUartRxSatus = AHC_FALSE;
#endif
extern MMPF_OS_FLAGID   	UartCtrlFlag;
static	MMP_BYTE 		chCommand[20]={0};
MMP_UBYTE 	ublength = 0;

static const CMDKEY CmdKey[] =
{
  	{KEY_CH_UP,		KEY_PRESS_UP,	"CH UP"	    },
  	{KEY_CH_DOWN,	KEY_PRESS_DOWN,	"CH DOWN"	},
  	{KEY_VOL_UP,	KEY_PRESS_UP,	"VOL UP"	},
  	{KEY_VOL_DOWN,	KEY_REL_DOWN,	"VOL DOWN"	},
  	{KEY_MENU,		KEY_REL_MENU,	"KEY MENU"	},
  	{KEY_PAUSE,		KEY_REL_PLAY,	"KEY PAUSE"	},
  	{KEY_EXIT,		KEY_REL_FUNC1,	"KEY EXIT"	},
  	{KEY_POWER,		KEY_REL_POWER,	"KEY POWER"	},
  	{KEY_MUTE,		KEY_PRESS_MUTE,	"KEY MUTE"	},
  	{KEY_PAGE_UP,	KEY_PRESS_LEFT,	"PAGE UP"	},
  	{KEY_PAGE_DOWN,	KEY_PRESS_RIGHT,"PAGE DOWN"	},
  	{KEY_CAPTURE  , KEY_LPRESS_REC ,"CAPTURE " },
  	{KEY_LOCK  ,    BUTTON_LOCK_FILE_G ,"LOCK FILE " },
  	{KEY_FRCAM_SWITCH,KEY_REL_FUNC1,   "FRCAM SWITCH"}
};

static MMP_UBYTE	gNumOfCMDIDKey = sizeof(CmdKey) / sizeof(CMDKEY);

/*===========================================================================
 * Main body
 *===========================================================================*/
#ifdef ALL_FW

//------------------------------------------------------------------------------
//  Function    : DTV_Uart_TouchPress
//  Description : Get the parsed UART information.
//------------------------------------------------------------------------------
#define offset_x  10
static void DTV_Uart_TouchPress(MMP_BYTE *pBuff)
{
    MMP_USHORT TemppX=0, TemppY=0;
    MMP_ULONG  ulParm;
	UINT32		curtick;
	static	UINT32 pretick;	

	#if JWD_HONDA_TOUCH
	UINT32		curtick;
	static	UINT32 pretick;	

	MMPF_OS_GetTime(&curtick);
    if(curtick - pretick < 300)
	{
		pretick = curtick;
		return;
	}
	pretick = curtick;
	#endif
	
	TemppX = (MMP_USHORT)pBuff[4]>>4&0x0F;
	TemppX = TemppX<<8 | pBuff[3] ;

	#if JWD_HONDA_TOUCH
	if(TemppX>720) TemppX = 0; //TBD 
	#else
	if(TemppX<360)  TemppX += offset_x;
	#endif
	
	TemppY = (MMP_USHORT)pBuff[4]&0x0F;
	TemppY = TemppY<<8 | pBuff[5];
	ulParm = TemppY<<16 | TemppX;
	
    printc("ulParm %x\r\n",ulParm);
//	SetKeyPadEvent(TOUCH_PANEL_PRESS);
    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, TOUCH_PANEL_PRESS, ulParm);
}

static void DTV_Uart_TouchRelease(MMP_BYTE *pBuff)
{
    printc("DTV_Uart_TouchRelease  \r\n");  
    SetKeyPadEvent(TOUCH_PANEL_REL);
}

static void DTV_Uart_SetKEY(MMP_BYTE *pBuff)
{
    MMP_UBYTE i = 0;

    printc("DTV_Uart_SetKEY  \r\n");
    for( i=0; i<gNumOfCMDIDKey ; i++ )
    {
        if(CmdKey[i].iCmdId == pBuff[3])
        {
            SetKeyPadEvent(CmdKey[i].ulkeyEvent);
            printc("%s \r\n",CmdKey[i].ubkeyname);
        }
    }
}

UINT16 uCurHour,uCurMinute,uCurSecond;
static void DTV_Uart_SetTime(MMP_BYTE *pBuff)
{
	if(pBuff[3]<24) 
		uCurHour = pBuff[3];
	if(pBuff[4]<60)
		uCurMinute = pBuff[4];
	if(pBuff[5]<60)
		uCurSecond = pBuff[5];
}

static void DTV_Uart_SetDate(MMP_BYTE *pBuff)
{
    UINT16 uwYear,uwMonth,uwDay,uwDayInWeek,uwHour,uwMinute,uwSecond;
	UINT16 uCurYear,uCurMonth,uCurDay;
    UINT8 ubAmOrPm, b_12FormatEn;
    static AHC_BOOL bWflag = AHC_FALSE;
	
	AHC_SetParam(PARAM_ID_USE_RTC,AHC_TRUE);
	AHC_GetClock(&uwYear,&uwMonth,&uwDay,&uwDayInWeek,&uwHour,&uwMinute,&uwSecond,&ubAmOrPm,&b_12FormatEn);
	if(pBuff[3]<99) 
		uCurYear = 2000 + pBuff[3];
	if(pBuff[4]<12)
		uCurMonth = pBuff[4];
	if(pBuff[5]<32)
		uCurDay = pBuff[5];
	
	if((uwHour == uCurHour)&&(uwMinute == uCurMinute))
		return ;
	if(!bWflag)
	{
		AHC_SetClock(uCurYear, uCurMonth, uCurDay, uwDayInWeek, uCurHour, uCurMinute, uwSecond,ubAmOrPm, b_12FormatEn);
		bWflag = AHC_TRUE;
	}
}

//------------------------------------------------------------------------------
//  Function    : DTV_Uart_ParsePack
//  Description : Parse UART packet from buffer.
//------------------------------------------------------------------------------
/** @brief

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

static MMP_LONG DTV_Uart_ParsePack(MMP_BYTE *pBuff )
{
    switch(pBuff[2]) //Command ID
    {
    case DTVCMD_TOUCH_DEFAULT :
        printc("Command ID default \r\n");;
        break;
		  
    case DTVCMD_TOUCH_PRESS:
        DTV_Uart_TouchPress(pBuff);
        break;
		  
    case DTVCMD_TOUCH_RELEASE:
        DTV_Uart_TouchRelease(pBuff);
        break;

    case DTVCMD_KEY:
        DTV_Uart_SetKEY(pBuff);
        break;

    case DTVCMD_TIME:
        DTV_Uart_SetTime(pBuff);
        break;

    case DTVCMD_DATE:
        DTV_Uart_SetDate(pBuff);
        break;
	default:
		 printc("pBuff[2] %d\r\n",pBuff[2]);
		  break;
   	}

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : DTV_Uart_CheckSum
//  Description : 
// byte0		byte1		byte2		byte3		byte4		byte5		byte6
//Customer		payload		Command		Command		Command		Command		Checksum
// code			length		 ID			 data0		 data1		 data2
//  packet Checksum = -(Customer code + payload length + Command ID + Command data)
//------------------------------------------------------------------------------

static MMP_BOOL DTV_Uart_CheckSum(MMP_BYTE *pBuff, MMP_ULONG iBuff_sz)
{
    MMP_UBYTE sum = 0,bsum = ~pBuff[iBuff_sz-1]+1;
    MMP_UBYTE  i = 0;
   
    for(i=0;i<(iBuff_sz-1);i++)
    {
        sum += pBuff[i];
    }

	if(sum == bsum)
        return AHC_TRUE;
	else
	{ 
		printc("sum %d bsum %d\r\n",sum,bsum);
        return AHC_FALSE;
	}
}

//------------------------------------------------------------------------------
//  Function    : DTV_Uart_PaeserMain
//  Description : Entry of DTV_Parser
// byte0		byte1		byte2		byte3		byte4		byte5		byte6
//Customer		payload		Command		Command		Command		Command		Checksum
// code			length		 ID			 data0		 data1		 data2
//  packet  payload Length = Command ID + Command data
//  packet Checksum = -(Customer code + payload length + Command ID + Command data)
//------------------------------------------------------------------------------

static void DTV_Uart_ParserMain(MMP_BYTE *pBuff, MMP_ULONG iBuff_length)
{
    MMP_BYTE temp[128]={0};;
	
//	printc("++++++DTV_PaeserMain \r\n");

    if( iBuff_length <= 3 )
    {
    	printc(FG_RED("%s: iBuff_length err %d")"\r\n", __func__, iBuff_length);
        return;
    }
	if((iBuff_length-3) != pBuff[1])
	{
		if(pBuff[pBuff[1]+3] == Uart_RX_SIGNAL )
		{
			MEMCPY(temp,&pBuff[pBuff[1]+3],iBuff_length-pBuff[1]-3);
            pBuff[pBuff[1]+3] ='\0';
			if(DTV_Uart_CheckSum(pBuff,pBuff[1]+3))
				DTV_Uart_ParsePack(pBuff);
			MEMCPY(pBuff,temp,temp[1]+3);
			pBuff[pBuff[1]+3] ='\0';
		}
		iBuff_length = pBuff[1] + 3;
	}
	
	if(DTV_Uart_CheckSum(pBuff,iBuff_length))
		DTV_Uart_ParsePack(pBuff);
	else
		printc(FG_RED("%s: Check sum err")"\r\n", __func__);
}

 void DTV_Uart_String_RxCallback(MMP_UBYTE size, volatile MMP_UBYTE *fifo)
{
	MMP_BYTE chUartchar,i;
	
    for(i = 0; i < size; i++) {
		chUartchar = *fifo;
		m_bUartString[(m_bUartRxStrLen + i) % Uart_RX_QUEUE_SIZE] = chUartchar;
		// Uart Echo
    }
    m_bUartRxStrLen += size;
    if (m_bUartRxStrLen >= Uart_RX_QUEUE_SIZE) {
        RTNA_DBG_Str(0, "Error: DTV UART RX overflow\r\n");
    }
    if(chUartchar == Uart_RX_SIGNAL)
    {
		m_bUartRxSatus	= AHC_TRUE;
		MMPF_OS_SetFlags(UartCtrlFlag, Touch_Uart_FLAG_GETPACK, MMPF_OS_FLAG_SET);
    }
    return;
}

MMP_ERR DTV_Uart_InitPathUART(struct _3RD_PARTY_TOUCH_UART *pthis,MMP_UART_ATTR uartattribute)
{
	
    MMP_LONG error;

	printc(FG_RED("UartTouch_InitPathUART \r\n"));

	uartattribute.bParityEn 		= MMP_FALSE;
	uartattribute.parity 			= MMP_UART_PARITY_ODD;
	uartattribute.bFlowCtlEn 		= MMP_FALSE;
	uartattribute.ubFlowCtlSelect 	= 1;
    uartattribute.padset 			= DTV_UART_PADSET;
    uartattribute.ulMasterclk 		= DTV_UART_CLK * 1000 ;
	uartattribute.ulBaudrate 		= DTV_UART_BAUD_RATE;

	error = MMPF_Uart_Open(DTV_UART_NUM, &uartattribute);
	if(error)
		printc("Uart Open Error : %d\r\n",error);

	MMPF_Uart_EnableRx(DTV_UART_NUM, 1,(UartCallBackFunc *)&DTV_Uart_String_RxCallback);

	if(error)
		printc("Uart UseRxDMA : %d\r\n",error);
	return MMP_ERR_NONE;
}

MMP_ERR DTV_Uart_GetString_UART(struct _3RD_PARTY_TOUCH_UART *pthis,MMP_BYTE *bUTString, MMP_ULONG *ulUTStringLength)
{
#if (UART_RXINT_MODE_EN == 1)
	MMP_LONG j,i;
    int nLen;
    MMP_BOOL Parse_flag = AHC_FALSE;
    MMP_ULONG ulStartPosition =0;

//	printc("DTV_GetString_UART %d \r\n",m_bUTRxStrLen);
	if(m_bUartRxStrLen<1) 
		return MMP_ERR_NONE;
	
	AHC_OS_SleepMs(10);
	
    nLen =  m_bUartRxStrLen;

//    printc("nLen = %d\n", nLen );
    j = 0;
    while(nLen>0)
    {
        char chUartchar =  m_bUartString[ulStartPosition];
    //    printc("%x  ",chDTVchar);
        if(chUartchar == Uart_RX_SIGNAL)
        {	
            i = ulStartPosition;
			for(;i<m_bUartRxStrLen;i++)
			{
				bUTString[j++] = m_bUartString[ulStartPosition];
				ulStartPosition ++;
			}
			Parse_flag = AHC_TRUE;
	        break;
        }
		ulStartPosition++;	
		nLen--;
    }
    m_bUartRxStrLen = 0;
	
	*ulUTStringLength = j;
    bUTString[j] = '\0';
	
	m_bUartRxSatus	= AHC_FALSE;
	if(Parse_flag)
		DTV_Uart_ParserMain(bUTString,j);
#endif
	return MMP_ERR_NONE;
}
/*********************************************************************************/
// byte0		byte1		byte2		byte3		byte4		byte5		byte6
//Customer		payload		Command		Command		Command		Command		Checksum
// code			length		 ID			 data0		 data1		 data2
//  packet  payload Length = Command ID + Command data
//  packet Checksum = -(Customer code + payload length + Command ID + Command data)
/*********************************************************************************/

#if (DTV_UART_SEND_LDWS)
AHC_BOOL DTV_UART_Get_LDWS(void)
{
    MMP_LONG  ulAlert;
    ldws_params_t cur_ldws_attribute = {0};
    UINT32 uiAdasFlag = 0;
	MMP_BYTE cnt = 0;
	
	memset(chCommand,0,20);
    AHC_GetParam( PARAM_ID_ADAS, &uiAdasFlag );

    if ((uiAdasFlag & AHC_ADAS_ENABLED_LDWS) == 0) 
	{
        return;
    }
	
    ADAS_CTL_GetLDWSAttr(&cur_ldws_attribute, &ulAlert);
	
	if((ulAlert != LDWS_STATE_DEPARTURE_LEFT)
		&&(ulAlert != LDWS_STATE_DEPARTURE_LEFT))
	{
		ulAlert = 0;
		return AHC_FALSE;
	}
	chCommand[0] = 0xFE;
	chCommand[1] = 14;
	chCommand[2] = 0xB0;
	chCommand[3] = ulAlert;
	if (cur_ldws_attribute.state != LDWS_STATE_NODETECT)
	{
		chCommand[4]= (cur_ldws_attribute.left_lane[0].x)&0xff ;
		chCommand[5]= (((cur_ldws_attribute.left_lane[0].x >> 8)&0x0f)<< 4) \
			             | ((cur_ldws_attribute.left_lane[0].y >> 8)&0x0f) ;
		chCommand[6]= (cur_ldws_attribute.left_lane[0].y)&0xff ;
		
		chCommand[7]= (cur_ldws_attribute.left_lane[1].x)&0xff ;
		chCommand[8]= (((cur_ldws_attribute.left_lane[1].x >> 8)&0x0f)<< 4)\
						 | ((cur_ldws_attribute.left_lane[1].y >> 8)&0x0f) ;
		chCommand[9]= (cur_ldws_attribute.left_lane[1].y )&0xff ;
		
		chCommand[10]= (cur_ldws_attribute.right_lane[0].x)&0xff ;
		chCommand[11]= (((cur_ldws_attribute.right_lane[0].x >> 8)&0x0f)<< 4)\
						| ((cur_ldws_attribute.right_lane[0].y >> 8)&0x0f);
		chCommand[12]= (cur_ldws_attribute.right_lane[0].y)&0xff ;
		
		chCommand[13]= (cur_ldws_attribute.right_lane[1].x)&0xff ;
		chCommand[14]= (((cur_ldws_attribute.right_lane[1].x >>  8)&0x0f)<< 4)\
						| ((cur_ldws_attribute.right_lane[1].y >> 8)&0x0f);
		chCommand[15]= (cur_ldws_attribute.right_lane[1].y)&0xff;
		
		for(cnt =0;cnt<16;cnt++)
			chCommand[16] += chCommand[cnt];
			
		chCommand[16] = ~chCommand[16]+1;
		ublength = 17 ;	
		return AHC_TRUE;
	}
	else
		return AHC_FALSE;	
}
#endif

#if (DTV_UART_SEND_FCWS)
AHC_BOOL  DTV_UART_Get_FCWS(void)
{
    UINT32 uiAdasFlag = 0;
	MMP_BYTE cnt = 0;
	
	memset(chCommand,0,20);
	
    AHC_GetParam( PARAM_ID_ADAS, &uiAdasFlag );
        
    if ( uiAdasFlag & AHC_ADAS_ENABLED_FCWS )
	{
        fcws_info_t cur_fcws_info = {0};

        ADAS_CTL_GetFCWSAttr(&cur_fcws_info);
 		if( cur_fcws_info.state == FCWS_STATE_FIND )
 		{
			if (cur_fcws_info.distance > 100)
                     cur_fcws_info.distance = 99;
			
			chCommand[0] = 0xFE;
			chCommand[1] = 9;
			chCommand[2] = 0xB1;
			chCommand[3] = 1;
			chCommand[4] = cur_fcws_info.distance ;
			
			chCommand[5] = cur_fcws_info.car_x & 0xff;
			chCommand[6] = (((cur_fcws_info.car_x >> 8)&0x0f)<< 4)\
				              | ((cur_fcws_info.car_y >> 8)&0x0f);
			chCommand[7] = cur_fcws_info.car_y & 0xff;
			
			chCommand[8] = cur_fcws_info.car_width & 0xff;
			chCommand[9] = ((cur_fcws_info.car_width >>8& 0x0f)<< 4)\
								|((cur_fcws_info.car_height >> 8)&0x0f);
			chCommand[10] = cur_fcws_info.car_height & 0xff;
			
			for(cnt = 0;cnt<11;cnt++)
				chCommand[11] += chCommand[cnt];
			
			chCommand[11] = ~chCommand[11] + 1;
			ublength = 12 ;	
			return AHC_TRUE;			
 		}
    }
	return AHC_FALSE;
}
#endif
//------------------------------------------------------------------------------
//  Function    : DTV_Uart_Setstring
//  Description : DVR To 
// byte0		byte1		byte2		byte3		byte4		byte5		byte6
//Customer		payload		Command		Command		Command		Command		Checksum
// code			length		 ID			 data0		 data1		 data2
//  packet  payload Length = Command ID + Command data
//  packet Checksum = -(Customer code + payload length + Command ID + Command data)
//------------------------------------------------------------------------------

MMP_ERR DTV_Uart_Setstring(struct _3RD_PARTY_TOUCH_UART *pthis,MMP_BYTE *data,MMP_ULONG length)
{
	MMP_ERR 	err;
	
	printc(FG_RED("%s: ")"\r\n", __func__);
	err = MMPF_Uart_Write(DTV_UART_NUM, chCommand, ublength);
	if (err)
		printc(FG_RED("%s: Send TPMS Tx error 0x%x")"\r\n", __func__, err);
}

MMP_BOOL DTV_Uart_ModuleAttached(struct _3RD_PARTY_TOUCH_UART *pthis)
{
  return MMP_TRUE;
}

MMP_ERR DTV_Uart_IOControl(struct _3RD_PARTY_TOUCH_UART *pthis, MMP_UBYTE cmd,MMP_UBYTE *arg)
{
	return MMP_ERR_NONE;
}

static struct _3RD_PARTY_TOUCH_UART Touch_Uart_Obj = 
{
	DTV_Uart_InitPathUART,
	DTV_Uart_GetString_UART,
	DTV_Uart_Setstring,	
	DTV_Uart_ModuleAttached,
	DTV_Uart_IOControl,
};

int Touch_Uart_Module_Init(void)
{
    printc(FG_GREEN("[Touch_Uart_Module_Init]\r\n"));
    Touch_Uart_Ctrl_Register(&Touch_Uart_Obj);
    return 0;    
}

#if defined(__GNUC__)
__section__(initcall6)
#else //#if defined(__GNUC__)
#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6" 
#pragma O0
#endif
ait_module_init(Touch_Uart_Module_Init);
#if defined(__GNUC__)
//NOP
#else //#if defined(__GNUC__)
#pragma
#pragma arm section rodata, rwdata ,  zidata 
#endif

#endif		// ALL_FW
#endif //TOUCH_UART_FUNC_EN



