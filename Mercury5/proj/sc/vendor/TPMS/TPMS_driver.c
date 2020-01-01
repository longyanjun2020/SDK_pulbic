/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ait_utility.h"
#include "mmpf_uart.h"
#include "MenuSetting.h"
#include "ahc_os.h"

#include "TPMS_driver.h"
#include "TPMS_ctl.h"
#include "gps_ctl.h"

#if (TPMS_FUNC_EN)

/*===========================================================================
 * Macro define
 *===========================================================================*/

void printc(char* fmt, ...);
#ifdef _DEBUG_
#define	DPRINT( ... ) 	printc( __VA_ARGS__);
#else
#define	DPRINT( ... ) 	{}
#endif


typedef enum _TPMS_MODE
{
	TPMS_MODE_AUTO,
	TPMS_MODE_MANUAL,
	TPMS_MODE_LEARN
}TPMS_MODE;


/*===========================================================================
 * Global varible
 *===========================================================================*/
static MMP_UBYTE 	m_ulTPMSBuffStartAddr[1024] = {0};
static int 			m_ulTPMSStartPosition = 0, m_ulTPMSEndPosition = 0;
static MMP_BYTE 	m_bTPMSString[TPMS_RX_QUEUE_SIZE] = {0};
static int 			m_nTPMSStartSignNum = 0;
static MMP_BOOL		bTPMDeviceConnected = MMP_FALSE;
static TPMSPACK 	*m_pTPMSPack;
static TPMSINFO 	*m_pTPMSInfo;
static MMP_BOOL		m_bLearnReturn = MMP_FALSE;
static TPMS_MODE	m_curMode = TPMS_MODE_AUTO;
static UINT32		m_timeLearnStart = 0, m_timeLearnEnd = 0;
static UINT32		m_LearnModeTimeOut = 0;
static PTPMSLEARNMODE_CALLBACK		m_pLearnModeCallback = NULL;
static MMP_BOOL		m_bTPMSDriverInit = MMP_FALSE;


static MMP_UBYTE 	ubTPMSAuto[4] 			= 	{0x24 ,0x54 ,0x30, 0x23 };
static MMP_UBYTE 	ubTPMSManual[4] 		= 	{0x24 ,0x54 ,0x31, 0x23 };
static MMP_UBYTE 	ubTPMSGetW0[4] 			= 	{0x24 ,0x57 ,0x30, 0x23 };
static MMP_UBYTE 	ubTPMSGetW1[4] 			= 	{0x24 ,0x57 ,0x31, 0x23 };
static MMP_UBYTE 	ubTPMSGetW2[4] 			= 	{0x24 ,0x57 ,0x32, 0x23 };
static MMP_UBYTE 	ubTPMSGetW3[4] 			= 	{0x24 ,0x57 ,0x33, 0x23 };
static MMP_UBYTE 	ubTPMSEnterLearn[7] 	= 	{0x24 ,0x4C ,0x45, 0x41, 0x52, 0x4E, 0x23 };
static MMP_UBYTE 	ubTPMSExitLearn[6] 	    = 	{0x24 ,0x4C ,0x45, 0x4E, 0x44 ,0x23};


extern MMPF_OS_FLAGID   	UartCtrlFlag;
/*===========================================================================
 * Main body
 *===========================================================================*/
void TPMS_String_RxCallback(MMP_UBYTE size, volatile MMP_UBYTE *fifo)
{
	MMP_BYTE chTPMSchar;
	
	#if (TPMS_DEBUG)
	while (size--) chTPMSchar = *fifo;
	return;
	#endif
	
    while(size--)
	{
	    int nNextPos = (m_ulTPMSEndPosition + 1) %TPMS_RX_QUEUE_SIZE;
            //TPMS_RX_QUEUE_SIZE;
	    // chech next pos valid

        if(nNextPos == m_ulTPMSStartPosition )
        {
            static AHC_BOOL bShowed = AHC_FALSE;
            if( !bShowed )
            {
    	 	    printc(BG_YELLOW("==> TPMS buffer full")"\r\n");
                //bShowed = AHC_TRUE;

            }
            while(size--)        chTPMSchar =  *fifo;
            break;
        }

        chTPMSchar =  *fifo;
        //printc("%c", chTPMSchar);

        m_bTPMSString[m_ulTPMSEndPosition] = chTPMSchar;


		if(chTPMSchar == RX_TPMS_SIGNAL)
    	{
            m_nTPMSStartSignNum++;
    	}

    	m_ulTPMSEndPosition = nNextPos;
    }
    //printc("\r\n");
    return;
}

MMP_ERR TPMS_GetString_UART(MMP_BYTE *bTPMSString, MMP_ULONG *ulTPMSStringLength)
{
	MMP_LONG j;
    int nLen;
    int nNextPost =0;
    int nTPMSStartCharNum = 0;
    MMP_ULONG ulStartPositionBack = m_ulTPMSStartPosition;

    nLen = m_ulTPMSEndPosition - m_ulTPMSStartPosition;
    nLen = (nLen<0)?nLen+TPMS_RX_QUEUE_SIZE : nLen;

    //printc("nLen = %d\n", nLen );
	if( m_nTPMSStartSignNum < 2 )
    {
        *ulTPMSStringLength = 0;
        return 0;
    }

    j = 0;

    while(nLen>0)
    {
        char chTPMSchar =  m_bTPMSString[m_ulTPMSStartPosition];
        //printc("%c",chTPMSchar);
        if(chTPMSchar == RX_TPMS_SIGNAL)
        {
            nTPMSStartCharNum++;

            if( nTPMSStartCharNum == 2 )
            {
                #if TPMS_FUNC_EN
                MMPF_OS_SetFlags(UartCtrlFlag, TPMS_FLAG_GETTPMSPACK, MMPF_OS_FLAG_SET); // GPS control flow to get GPS package from UART
                #endif
                break;
            }

            m_nTPMSStartSignNum--;

        }
		nNextPost = (m_ulTPMSStartPosition +1)%TPMS_RX_QUEUE_SIZE;
        bTPMSString[j++] = chTPMSchar;//m_bTPMSString[m_ulStartPosition];
        m_ulTPMSStartPosition = nNextPost;
        nLen-- ;
    }

    if( nTPMSStartCharNum < 2 )
    {
        // roll back
        m_ulTPMSStartPosition  = ulStartPositionBack;
        *ulTPMSStringLength = 0;
        bTPMSString[0] = '\0';
    }
    else
    {
        *ulTPMSStringLength = j;
        bTPMSString[j] = '\0';
    }

	bTPMDeviceConnected = MMP_TRUE;
	return MMP_ERR_NONE;
}

MMP_BOOL TPMS_InitPathUART(void)
{
	MMP_UART_ATTR uartattribute;
    MMP_ERR error;

	uartattribute.bParityEn 		= MMP_FALSE;
	uartattribute.parity 			= MMP_UART_PARITY_ODD;
	uartattribute.bFlowCtlEn 		= MMP_FALSE;
	uartattribute.ubFlowCtlSelect 	= 1;
    uartattribute.padset 			= MMP_UART_PADSET_2;
    uartattribute.ulMasterclk 		= TPMS_UART_CLK * 1000 ;
	uartattribute.ulBaudrate 		= TPMS_BAUD_RATE;

	error = MMPF_Uart_Open(TPMS_UART_NUM, &uartattribute);

	if(error != MMP_ERR_NONE)
	{
		m_bTPMSDriverInit = MMP_FALSE;
		printc("Uart Open Error : %d\r\n",error);
		return MMP_FALSE;
	}

	error = MMPF_Uart_EnableRx(TPMS_UART_NUM, 16,(UartCallBackFunc *)&TPMS_String_RxCallback);

	if(error != MMP_ERR_NONE)
	{
		m_bTPMSDriverInit = MMP_FALSE;
		printc("Uart UseRxDMA : %d\r\n",error);
		return MMP_FALSE;
	}
	
	#if (TPMS_WORKAROUND)
	MMPF_PIO_EnableOutputMode(MMP_GPIO20, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_SetData(MMP_GPIO20, MMP_FALSE, MMP_TRUE);
	#endif
		
	m_bTPMSDriverInit = MMP_TRUE;
	return MMP_TRUE;
}

void TPMS_UnInitPathUART(void)
{
	m_bTPMSDriverInit = MMP_FALSE;
	
	MMPF_Uart_Close(TPMS_UART_NUM);
}

//------------------------------------------------------------------------------
//  Function    : TPMS_Information
//  Description : Get the parsed TPMS information.
//------------------------------------------------------------------------------

pTireInfo TPMS_Information()
{
    return m_pTPMSInfo;
}

void TPMS_ParserInitialize(void)
{
	m_pTPMSPack			= (TPMSPACK*)(m_ulTPMSBuffStartAddr);
	m_pTPMSInfo 		= (TPMSINFO*)(m_ulTPMSBuffStartAddr + 100);
	
	bTPMDeviceConnected = MMP_FALSE;

	memset(m_pTPMSPack, 0, sizeof(TPMSPACK));
	memset(m_pTPMSInfo, 0, sizeof(TPMSINFO));
	memset(m_bTPMSString, 0, sizeof(m_bTPMSString));
}

void TPMS_ParserUnInitialize(void)
{
	bTPMDeviceConnected = MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : TPMS_FindTail
//  Description : Find tail of packet ("\r\n") in buffer and check control sum (CRC).
//------------------------------------------------------------------------------
/** @brief

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] pRes_crc a integer pointer for return CRC of packet (must be defined).
@return Number of bytes to packet tail.
*/

MMP_LONG TPMS_FindTail(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_LONG *pRes_crc)
{
    static const MMP_LONG iTail_sz = 3 /* #\r\n */;

    const MMP_BYTE *pEnd_buff = pBuff + iBuff_sz;
    MMP_LONG iNread = 0;
    MMP_UBYTE iCrc = 0;

    *pRes_crc = -1;

    for(;pBuff < pEnd_buff; ++pBuff, ++iNread)
    {
        if(('$' == *pBuff) && iNread)
        {
            pBuff = 0;
            break;
        }
        else if(iNread == 9)
        {
            {
                *pRes_crc = TPMSCtrl_Atoi(pBuff, 2, 16);
                iNread = iBuff_sz - (MMP_LONG)(pEnd_buff - (pBuff + iTail_sz));

                if(*pRes_crc != iCrc)
                {
                    *pRes_crc = -1;
                    pBuff = 0;
                }
            }

            break;
        }

        if(iNread)
            iCrc += (MMP_UBYTE)(*pBuff);
    }

    if(*pRes_crc < 0 && pBuff)
        iNread = 0;

    return iNread;
}
//------------------------------------------------------------------------------
//  Function    : TPMS_ParsePack
//  Description : Parse TPMS packet from buffer.
//------------------------------------------------------------------------------
/** @brief

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

MMP_LONG TPMS_ParsePack(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, TPMSPACK *psPack)
{

    MMP_ULONG checksum;
    memset(psPack, 0, sizeof(TPMSPACK));


	*(pBuff + iBuff_sz) = 0;
	//printc("%s", pBuff);

    if(7 != TPMSCtrl_Scanf(pBuff,iBuff_sz,"$%1d%1d%1d%1d%2x%2x%2x#",
        &(psPack->ubWheelPosition), &(psPack->ubBatteryIndication), &(psPack->ubWheelDataUpdate), \
        &(psPack->ubTirePressure), &(psPack->ubTirePressureInt), &(psPack->ubTireTemp), &checksum))
    {
        DPRINT("TPMS parse error!\r\n");
        return 0;
    }

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : TPMS_Pack2info
//  Description : Fill TPMSINFO structure by packet data.
//------------------------------------------------------------------------------
/** @brief
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/

void TPMS_Pack2info(TPMSPACK *psPack, TPMSINFO *psInfo)
{
    if(psPack->ubWheelPosition <4 && psPack->ubWheelPosition >=0)
    {
    	MMP_UBYTE ubWheel = psPack->ubWheelPosition;
    	psInfo->sTire[ubWheel].ubWheelPosition 		= psPack->ubWheelPosition;
    	psInfo->sTire[ubWheel].ubBatteryIndication 	= psPack->ubBatteryIndication;
    	psInfo->sTire[ubWheel].ubWheelDataUpdate 	= psPack->ubWheelDataUpdate;
    	psInfo->sTire[ubWheel].ubTirePressure 		= psPack->ubTirePressure;
    	psInfo->sTire[ubWheel].ubTirePressureInt 	= psPack->ubTirePressureInt;
    	psInfo->sTire[ubWheel].ubTireTemp 			= psPack->ubTireTemp;
    }
}

//------------------------------------------------------------------------------
//  Function    : TPMS_PaeserMain
//  Description : Entry of TPMS_Parser
//------------------------------------------------------------------------------

MMP_BOOL TPMS_IsReceiverConnected(void) // SW level.
{
	return bTPMDeviceConnected;
}

void TPMS_PaeserMain(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, TPMSINFO *pInfo)
{
	MMP_LONG iRetCrc, iError, iRead = 0, iPackageType = 0, iParsed = 0;
	static MMP_UBYTE ubCount = 0;

	if( iBuff_sz == 0 )
    {
        return;
    }
    
	do
	{
		iRead = TPMS_FindTail(pBuff+iParsed, iBuff_sz-iParsed, &iRetCrc);
		//printc("iRead : %d\r\n",iRead);
		//printc("iRetCrc : %d\r\n",iRetCrc);
		if(!iRead)
		{
            printc("*");
			break;
		}		
		else if(iRetCrc > 0)
		{
			iError = TPMS_ParsePack(pBuff+iParsed ,iRead ,m_pTPMSPack);
		    TPMS_Pack2info(m_pTPMSPack, pInfo);

		}

		iParsed += iRead;

	}while(iParsed<iBuff_sz);
}

void TPMS_SetCommand(TPMSCOMMAND_TYPE type)
{
	char 		chCommand[10];
	MMP_UBYTE 	ublength = 0;
	MMP_UBYTE 	i = 0;
	MMP_ERR 	err;
	
	#if (TPMS_WORKAROUND)
	MMPF_PIO_Enable(MMP_GPIO20, MMP_FALSE);
	#endif

	MEMSET(chCommand, 0, 10);
	switch (type)
	{
		case TPMSCMD_GET_WHEEL_DATA_0:
			MEMCPY(chCommand, ubTPMSGetW0, sizeof(ubTPMSGetW0));
			ublength = sizeof(ubTPMSGetW0);
			break;
		case TPMSCMD_GET_WHEEL_DATA_1:
			MEMCPY(chCommand, ubTPMSGetW1, sizeof(ubTPMSGetW1));
			ublength = sizeof(ubTPMSGetW1);
			break;
		case TPMSCMD_GET_WHEEL_DATA_2:
			MEMCPY(chCommand, ubTPMSGetW2, sizeof(ubTPMSGetW2));
			ublength = sizeof(ubTPMSGetW2);
			break;
		case TPMSCMD_GET_WHEEL_DATA_3:
			MEMCPY(chCommand, ubTPMSGetW3, sizeof(ubTPMSGetW3));
			ublength = sizeof(ubTPMSGetW3);
			break;
		case TPMSCMD_ENTER_LEARN_ID_MODE:
			MEMCPY(chCommand, ubTPMSEnterLearn, sizeof(ubTPMSEnterLearn));
			ublength = sizeof(ubTPMSEnterLearn);
			break;
		case TPMSCMD_EXIT_LEARN_ID_MODE:
			MEMCPY(chCommand, ubTPMSExitLearn, sizeof(ubTPMSExitLearn));
			ublength = sizeof(ubTPMSExitLearn);
			break;
		case TPMSCMD_SET_AUTO:
			MEMCPY(chCommand, ubTPMSAuto, sizeof(ubTPMSAuto));
			ublength = sizeof(ubTPMSAuto);
			break;
		case TPMSCMD_SET_MANUAL:
			MEMCPY(chCommand, ubTPMSManual, sizeof(ubTPMSManual));
			ublength = sizeof(ubTPMSManual);
			break;

	}
	
	#if 0
	printc("Send TPMS command %d bytes via TX :\r\n", ublength);
	for (i = 0; i < ublength; i++)
	{
		printc("0x%x, ", chCommand[i]);
		if ((i % 10) == 0 && (i != 0))
			printc("\n");
	}
	printc("\n");
	#endif
	
	err = MMPF_Uart_Write(TPMS_UART_NUM, chCommand, ublength);
	if (err)
		printc("Send TPMS Tx error 0x%x\r\n", err);
		
	
	#if (TPMS_WORKAROUND)
	//AHC_OS_SleepMs(1000);
	MMPF_Uart_WaitTxDone(TPMS_UART_NUM);
	MMPF_PIO_EnableOutputMode(MMP_GPIO20, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_SetData(MMP_GPIO20, MMP_FALSE, MMP_TRUE);
	#endif

}

void TPMS_EnterLearnMode(PTPMSLEARNMODE_CALLBACK pCallback, UINT32 TimeOut)
{	
	printc("%s\n", __func__);
	
	/* Set callback and time out */
	m_pLearnModeCallback = pCallback;
	m_LearnModeTimeOut = TimeOut;

	/* Reset counter */
	AHC_OS_GetTime(&m_timeLearnStart);
	m_timeLearnEnd = m_timeLearnStart;
	
	/* Reset parameters */
	m_bLearnReturn = MMP_FALSE;
	m_curMode = TPMS_MODE_LEARN;
	
	/* Start learning mode */
	//TPMS_SetCommand(TPMSCMD_SET_MANUAL);
	TPMS_SetCommand(TPMSCMD_SET_AUTO);
	TPMS_SetCommand(TPMSCMD_ENTER_LEARN_ID_MODE);
}

void TPMS_ExitLearnMode(void)
{
	if (m_curMode == TPMS_MODE_LEARN)
	{
		printc("%s\n", __func__);
		TPMS_SetCommand(TPMSCMD_EXIT_LEARN_ID_MODE);
		TPMS_SetCommand(TPMSCMD_SET_AUTO);
	}
	m_curMode = TPMS_MODE_AUTO;
}

void TPMS_ReEnterLearnMode(void)
{
	/* Start learning mode */
	m_bLearnReturn = MMP_FALSE;
	m_curMode = TPMS_MODE_LEARN;
	TPMS_SetCommand(TPMSCMD_ENTER_LEARN_ID_MODE);
}

static MMP_BOOL	TPMS_bReceiveAll(void)
{
	if (m_pTPMSInfo->sTire[0].ubWheelDataUpdate == 1 &&
		m_pTPMSInfo->sTire[1].ubWheelDataUpdate == 1 &&
		m_pTPMSInfo->sTire[2].ubWheelDataUpdate == 1 &&
		m_pTPMSInfo->sTire[3].ubWheelDataUpdate == 1 )
	{	
		return MMP_TRUE;
	}
	else
	{
		return MMP_FALSE;
	}
	return MMP_FALSE;
}

void TPMS_UpdateData(void)
{ 	
	MMP_BYTE	szTPMSPack[1024] = {0};
	MMP_ULONG	uiTPMSPackLength = 0;
	static UINT32 timeRelearnStart = 0, timeRelearnEnd = 0;
	
	#if (TPMS_DEBUG)
	return;
	#endif
	
	TPMS_GetString_UART(szTPMSPack, &uiTPMSPackLength);
	//printc("%s\n", (const char*)szTPMSPack);
	
	TPMS_PaeserMain(szTPMSPack, uiTPMSPackLength, m_pTPMSInfo);
	
	if (m_curMode == TPMS_MODE_LEARN)
	{
		AHC_OS_GetTime(&m_timeLearnEnd);
		if (m_timeLearnEnd-m_timeLearnStart >= m_LearnModeTimeOut)
		{
			printc("Learn time-out\n");
			m_pLearnModeCallback(TPMS_LEARN_MODE_TIME_OUT);
			TPMS_ExitLearnMode();
			return;
		}
		else if (STRCMP((INT8*)"$LEARN#", (INT8*)szTPMSPack) == 0)
		{
			printc("Receive $LEARN#\r\n");
			TPMS_ExitLearnMode();
			
			// Check is all sensor learned.
			if (TPMS_bReceiveAll())
			{
				printc("Learn finish\r\n");
				m_pLearnModeCallback(TPMS_LEARN_MODE_FINISH);
				return;
			}
			else
			{
				printc("Not all sensor learned. Re-learn start\r\n");
				m_pLearnModeCallback(TPMS_LEARN_MODE_NOT_FINISH);
				TPMS_ReEnterLearnMode();
			}
		}
	}
}

#if (TPMS_DEBUG)
TPMSINFO* TPMS_GetTPMSInfo(void)
{
	return m_pTPMSInfo;
}

void TPMS_SetConnectStatus(void) // SW level.
{
	bTPMDeviceConnected = MMP_TRUE;
}
#endif

#endif // #if (TPMS_FUNC_EN)