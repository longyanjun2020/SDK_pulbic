/*===========================================================================
 * Include file 
 *===========================================================================*/

#include "gps_ctl.h"
#include "mmpf_fs_api.h"
#include "fs_clib.h"
#include "ait_utility.h"

#if (GPS_CONNECT_ENABLE && (GPS_MODULE == GPS_MODULE_GMC1030))
#include "GpsRadar_GMC1030.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/
/*===========================================================================
 * Global varible
 *===========================================================================*/

#if (GPS_CONFIG_NMEA_FILE)
static MMP_ULONG 	ulGPSRadarFileID 		= 0;
static MMP_ULONG 	ul64GPSRadarFileSize 	= 0;
static MMP_BOOL  	bStartCount 		= MMP_FALSE;
static MMP_BOOL  	bGPSRadarStartPosition;
static MMP_BOOL  	bGPSRadarStringCounter;
#endif

static MMP_BYTE		m_bGPSRadarString[GPS_RX_QUEUE_SIZE];
static MMP_ULONG	m_bGPSRadarStringLen;
static MMP_UBYTE 	m_ulGPSRadarBuffStartAddr[GPS_CONFIG_BUFFER_SIZE];

GPSRADARPACK        *pGPSRadarPack;
GPSRADARINFO		*pGPSRadarInfomation;
GPSINFOCHUCK 		*pGPSInfoForChuck; 
GPSRADARTIME  		*pGPSRadarGMTBackup;

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern MMP_ULONG   	UartCtrlFlag;
extern int 			sprintf(char * /*s*/, const char * /*format*/, ...);

/*===========================================================================
 * Main body
 *===========================================================================*/
/**********************************************************************************************************/
/* the proto-type of video APIs*/

MMP_HANDLE GPS_GMC1030_Open( )
{
    GPSRADARINFO *mgps;
    pGPSRadarInfomation = (GPSRADARINFO*)(m_ulGPSBuffStartAddr+100);
    mgps = pGPSRadarInfomation;
	mgps->h_dec = (void*)(pGPSRadarInfomation);
    return mgps;
}
//------------------------------------------------------------------------------
//  Function    : GPSRadar_String_RxCallback
//  Description : Callback to handle input data via UART FIFO port
//------------------------------------------------------------------------------

void GPSRadar_String_RxCallback(MMP_UBYTE size, volatile MMP_UBYTE *fifo)
{
    MMP_LONG i;
    MMP_BYTE chGPSRadarchar;
    MMP_BOOL bFindGPSRadarPack= MMP_FALSE;

	for(i = 0; i < size; i++) 
	{
        chGPSRadarchar =  *fifo;
        m_bGPSRadarString[(m_bGPSRadarStringLen + i)%GPS_RX_QUEUE_SIZE] = chGPSRadarchar;                    
    	
		if(chGPSRadarchar == RX_GPSRADAR_SIGNAL)
    	{
    	 	m_bGPSRadarStringLen += i;
    	 	bFindGPSRadarPack = MMP_TRUE;
    	 	MMPF_OS_SetFlags(UartCtrlFlag, GPS_FLAG_GETGPSPACK, MMPF_OS_FLAG_SET); // GPS control flow to get GPS package from UART
    		break;
    	}
    	else
    	{
    		bFindGPSRadarPack = MMP_FALSE;
    	}
    	
    	if (m_bGPSRadarStringLen >= GPS_RX_QUEUE_SIZE) {
		    m_bGPSRadarStringLen = 0;
		    RTNA_DBG_Str(0, "Error: UART RX overflow\r\n");
		}
    }

	if(!bFindGPSRadarPack)
		m_bGPSRadarStringLen += size;
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_GetString
//  Description : This function will send back the string until the user enter the "$"
//------------------------------------------------------------------------------

MMP_ERR GPSRadar_GetString_UART(MMP_BYTE *bGPSRadarString, MMP_ULONG *ulGPSRadarStringLength)
{
#if (UART_RXINT_MODE_EN == 1)
	MMP_LONG j;	

	for (j = 0; j < m_bGPSRadarStringLen; j++) {
		bGPSRadarString[j] = m_bGPSRadarString[j];
	}

	*ulGPSRadarStringLength = m_bGPSRadarStringLen;
	m_bGPSRadarStringLen = 1;
	MEMSET0(&m_bGPSRadarString);
	m_bGPSRadarString[0] = '$';		

#endif
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_InitPathUART_GMC1030
//  Description : Initialize the UART path. 
//------------------------------------------------------------------------------

void GPSRadar_InitPathUART_GMC1030(void)
{
	MMP_UART_ATTR uartattribute;
    MMP_LONG error;
    
	uartattribute.bParityEn 		= MMP_FALSE;
	uartattribute.parity 			= MMPF_UART_PARITY_ODD;
	uartattribute.bFlowCtlEn 		= MMP_FALSE;
	uartattribute.ubFlowCtlSelect 	= 1;	
    uartattribute.padset 			= GPSRADAR_UART_PIN;
    uartattribute.ulMasterclk 		= GPSRADAR_MASTER_CLK * 1000 ;
	uartattribute.ulBaudrate 		= GPSRADAR_BAUD_RATE;
	
	error = MMPF_Uart_Open(GPSRADAR_UART_NUM, &uartattribute);
	
	if(error)
		printc("Uart Open Error : %d\r\n",error);
	
	MMPF_Uart_EnableRx(GPSRADAR_UART_NUM, 1,(UartCallBackFunc *)&GPSRadar_String_RxCallback);
	
	if(error)
		printc("Uart UseRxDMA : %d\r\n",error);
}

void GPSRadar_UnInitPathUART_GMC1030(void)
{
    MMP_LONG error;
	
	error = MMPF_Uart_DisableRx(GPSRADAR_UART_NUM);
	
	error = MMPF_Uart_Close(GPSRADAR_UART_NUM);
	
	if(error)
		printc("GPSRadar_UnInitPathUART_GMC1030 Error : %d\r\n",error);
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_ControlPathUART_GMC1030
//  Description : Control the UART path.
//------------------------------------------------------------------------------

void GPSRadar_ControlPathUART_GMC1030(MMP_BOOL bEnable)
{
	if(bEnable)
		MMPF_Uart_EnableRx(GPSRADAR_UART_NUM, 1,(UartCallBackFunc *)&GPSRadar_String_RxCallback);
	else
		MMPF_Uart_DisableRx(GPSRADAR_UART_NUM);	
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_ControlReceivePath_GMC1030
//  Description : Control(on/off) the path between GPSRadar and DSP.
//------------------------------------------------------------------------------

void GPSRadar_ControlReceivePath_GMC1030(MMP_BYTE path,MMP_BOOL bEnable)
{
	switch (path)
	{
		case GPSRADAR_RECEIVE_UART:
			GPSRadar_ControlPathUART_GMC1030(bEnable);
		break;
		case GPSRADAR_RECEIVE_USB:
		//To do;
		break;
		case GPSRADAR_RECEIVE_DDC:
		//To do;
		break;
		case GPSRADAR_RECEIVE_TXT:
		break;
		
	}
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_GetGPSPack_GMC1030
//  Description : Get strings from Uart buffer
//------------------------------------------------------------------------------

void GPSRadar_GetPack_GMC1030(MMP_BYTE path, MMP_BYTE *bGPSRadarString, MMP_ULONG *ulGPSRadarStringLength)
{
	switch (path)
	{
		case GPSRADAR_RECEIVE_UART:
			GPSRadar_GetString_UART(bGPSRadarString,ulGPSRadarStringLength);
		break;
		case GPSRADAR_RECEIVE_USB:
			//To do;
		break;
		case GPSRADAR_RECEIVE_DDC:
			//To do;
		break;
		case GPSRADAR_RECEIVE_TXT:
			GPS_GetGPSStringFromFile(bGPSRadarString,ulGPSRadarStringLength);
		break;
		
	}
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_InitReceivePath_GMC1030
//  Description : Select the path between GPS and DSP.
//------------------------------------------------------------------------------

void GPSRadar_InitReceivePath_GMC1030(MMP_BYTE path)
{
	switch (path)
	{
		case GPSRADAR_RECEIVE_UART:
			GPSRadar_InitPathUART_GMC1030();
		break;
		case GPSRADAR_RECEIVE_USB:
		//To do;
		break;
		case GPSRADAR_RECEIVE_DDC:
		//To do;
		break;
		case GPSRADAR_RECEIVE_TXT:
		break;
		
	}
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_ParserInitialize_GMC1030
//  Description : Set required memory to 0.
//------------------------------------------------------------------------------

void GPSRadar_ParserInitialize_GMC1030(void)
{
	if(m_ulGPSRadarBuffStartAddr == 0)
	{
		printc("GPRadar_ParserInitialize Error: No Buffer Address\r\n");
		return;
	}
	
	pGPSRadarPack		= (GPSRADARPACK*)(m_ulGPSRadarBuffStartAddr);
    pGPSRadarInfomation	= (GPSRADARINFO*)(m_ulGPSRadarBuffStartAddr+100);
    pGPSInfoForChuck 	= (GPSINFOCHUCK*)(m_ulGPSRadarBuffStartAddr+200);
    pGPSRadarGMTBackup 	= (GPSRADARTIME*)(m_ulGPSRadarBuffStartAddr+300); 
	
	memset(pGPSRadarPack		, 0, sizeof(GPSRADARPACK));
	memset(pGPSRadarInfomation	, 0, sizeof(GPSRADARINFO));
	memset(pGPSInfoForChuck		, 0, sizeof(GPSINFOCHUCK));
	memset(pGPSRadarGMTBackup	, 0, sizeof(GPSRADARTIME));
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_ResetContainer_GMC1030
//  Description : Set required memory to 0.
//------------------------------------------------------------------------------

void GPSRadar_ResetContainer_GMC1030(void)
{
	memset(pGPSRadarPack		, 0, sizeof(GPSRADARPACK));
	memset(pGPSRadarInfomation	, 0, sizeof(GPSRADARINFO));
	memset(pGPSInfoForChuck		, 0, sizeof(GPSINFOCHUCK));
	memset(pGPSRadarGMTBackup	, 0, sizeof(GPSRADARTIME));
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_GMT2LocalTime
//  Description : Convert received time to Local time
//------------------------------------------------------------------------------

void GPSRadar_GMT2LocalTime(GPSRADARTIME *sGMTBackup, GPSRADARTIME *sRes, signed char sbGMTOffset)
{
	MMP_LONG lBackupYear,lBackupDay,lBackupHour,lBackupMin;
	signed char byHour = sbGMTOffset/4;
	signed char byMinute = (sbGMTOffset%4)*15;
	
	if (sGMTBackup->iYear == 0 ||  sGMTBackup->iMon == 0 ||  sGMTBackup->iDay == 0)
		return;
	
	if (byHour < -12)
		byHour = -12;
	else if (byHour > 13)
		byHour = 13;
	
	lBackupYear = sGMTBackup->iYear;
	lBackupDay 	= sGMTBackup->iDay;
	lBackupHour = sGMTBackup->iHour;
	lBackupMin 	= sGMTBackup->iMin;
	
	if(byMinute != 0)
	{
		sGMTBackup->iMin = ((sGMTBackup->iMin + byMinute)%60);
		
		if((lBackupMin + byMinute)>60)
		{
			if(sGMTBackup->iHour != 23)
			{
				sGMTBackup->iHour +=1;
			}
			else
			{
				sGMTBackup->iHour = 0;
				if(sGMTBackup->iMon != 2)
				{
					switch(sGMTBackup->iDay)
					{
						case 30:
							switch(sGMTBackup->iMon)
							{
								case 4:
								case 6:
								case 9:
								case 11:
									sGMTBackup->iDay = 1;
									sGMTBackup->iMon += 1;
								break;
								default:
									sGMTBackup->iDay += 1;
								break;
							}
						break;
						case 31:
							switch(sGMTBackup->iMon)
							{
								case 12:
									sGMTBackup->iDay = 1;
									sGMTBackup->iMon = 1;
									sGMTBackup->iYear += 1;
								break;
								default:
									sGMTBackup->iDay = 1;
									sGMTBackup->iMon += 1;
								break;
							}
						break;
						default:
							sGMTBackup->iDay += 1;
						break;
					}
				}
				else
				{
					switch(sGMTBackup->iDay)
					{
						case 29:
							sGMTBackup->iDay = 1;
							sGMTBackup->iMon += 1;
						break;
						case 28:
							if((sGMTBackup->iYear%400==0))
							{
								sGMTBackup->iDay += 1;	
							}
							else if((sGMTBackup->iYear%4 == 0)&&(sGMTBackup->iYear%100 != 0))
							{
								sGMTBackup->iDay += 1;
							}
							else
							{
								sGMTBackup->iDay = 1;
								sGMTBackup->iMon += 1;
							}
						break;
						default:
							sGMTBackup->iDay += 1;
						break;
					}
				}
			}
		}
		else if((lBackupMin + byMinute)<0)
		{
			if(sGMTBackup->iHour > 0)
			{
				sGMTBackup->iHour -=1;
			}
			else if(sGMTBackup->iHour == 0)
			{
				sGMTBackup->iHour = 23;
				
				if(sGMTBackup->iDay != 1)
				{
					sGMTBackup->iDay -= 1;
				}
				else if(sGMTBackup->iDay == 1)
				{
					if(sGMTBackup->iMon == 3)
					{
						if((sGMTBackup->iYear%400==0))
						{
							sGMTBackup->iMon = 2;
							sGMTBackup->iDay = 29;	
						}
						else if((sGMTBackup->iYear%4 == 0) && (sGMTBackup->iYear%100 != 0))
						{
							sGMTBackup->iMon = 2;
							sGMTBackup->iDay = 29;
						}
						else
						{
							sGMTBackup->iMon = 2;
							sGMTBackup->iDay = 28;							
						}
					}
					else
					{
						switch(sGMTBackup->iMon)
						{
							case 1:
								sGMTBackup->iYear -= 1;
								sGMTBackup->iMon = 12; 
								sGMTBackup->iDay = 31;
							break;
							case 3:
							case 5:
							case 7:
							case 8:
							case 10:
							case 12:
								sGMTBackup->iMon -= 1;
								sGMTBackup->iDay = 30;
							break;
							case 2:
							case 4:
							case 6:
							case 9:
							case 11:
								sGMTBackup->iMon -= 1;
								sGMTBackup->iDay = 31;
							break;
							 
						}
					}
				}	
			}
		}
	}
	
	if((sGMTBackup->iHour + byHour)>=24)
	{
		sGMTBackup->iHour = ((sGMTBackup->iHour + byHour)%24);
		
		if(sGMTBackup->iMon != 2)
		{
			switch(sGMTBackup->iDay)
			{
				case 30:
					switch(sGMTBackup->iMon)
					{
						case 4:
						case 6:
						case 9:
						case 11:
							sGMTBackup->iDay = 1;
							sGMTBackup->iMon += 1;
						break;
						default:
							sGMTBackup->iDay += 1;
						break;
					}
				break;
				case 31:
					switch(sGMTBackup->iMon)
					{
						case 12:
							sGMTBackup->iDay = 1;
							sGMTBackup->iMon = 1;
							sGMTBackup->iYear += 1;
						break;
						default:
							sGMTBackup->iDay = 1;
							sGMTBackup->iMon += 1;
						break;
					}
				break;
				default:
					sGMTBackup->iDay += 1;
				break;
			}
		}
		else
		{
			switch(sGMTBackup->iDay)
			{
				case 29:
					sGMTBackup->iDay = 1;
					sGMTBackup->iMon += 1;
				break;
				case 28:
					if((sGMTBackup->iYear%400==0))
					{
						sGMTBackup->iDay += 1;	
					}
					else if((sGMTBackup->iYear%4 == 0)&&(sGMTBackup->iYear%100 != 0))
					{
						sGMTBackup->iDay += 1;
					}
					else
					{
						sGMTBackup->iDay = 1;
						sGMTBackup->iMon += 1;
					}
				break;
				default:
					sGMTBackup->iDay += 1;
				break;
			}
		}
	}
	else if((sGMTBackup->iHour + byHour)<0)
	{
		sGMTBackup->iHour = ((sGMTBackup->iHour + 24 + byHour));
		
		if(sGMTBackup->iDay != 1)
		{
			sGMTBackup->iDay -= 1;
		}
		else if(sGMTBackup->iDay == 1)
		{	
			if(sGMTBackup->iMon == 3)
			{
				if((sGMTBackup->iYear%400==0))
				{
					sGMTBackup->iMon = 2;
					sGMTBackup->iDay = 29;	
				}
				else if((sGMTBackup->iYear%4 == 0)&&(sGMTBackup->iYear%100 != 0))
				{
					sGMTBackup->iMon = 2;
					sGMTBackup->iDay = 29;
				}
				else
				{
					sGMTBackup->iMon = 2;
					sGMTBackup->iDay = 28;							
				}	
			}
			else
			{
				switch(sGMTBackup->iMon)
				{
					case 1:
						sGMTBackup->iYear -= 1;
						sGMTBackup->iMon = 12; 
						sGMTBackup->iDay = 31;
					break;
					case 3:
					case 5:
					case 7:
					case 10:
					case 12:
						sGMTBackup->iMon -= 1;
						sGMTBackup->iDay = 30;
					break;
					case 2:
					case 4:
					case 6:
					case 8:
					case 9:
					case 11:
						sGMTBackup->iMon -= 1;
						sGMTBackup->iDay = 31;
					break;			 
				}
			}	
		}
	}
	else
	{
		sGMTBackup->iHour += byHour;
	}
	
	sRes->iYear = sGMTBackup->iYear;
	sRes->iMon 	= sGMTBackup->iMon ;
	sRes->iDay 	= sGMTBackup->iDay;
	sRes->iHour = sGMTBackup->iHour;
	sRes->iMin 	= sGMTBackup->iMin ;
	sRes->iSec 	= sGMTBackup->iSec ;
	
	sGMTBackup->iYear 	= lBackupYear;
	sGMTBackup->iDay 	= lBackupDay;
	sGMTBackup->iHour 	= lBackupHour;
	sGMTBackup->iMin 	= lBackupMin;
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_ParseTime_GMC1030
//  Description : Parse received time format and check if it is valid
//------------------------------------------------------------------------------

MMP_LONG GPSRadar_ParseTime_GMC1030(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, GPSRADARTIME *sRes)
{
    MMP_LONG iSuccess = 0;

   
    iSuccess = (6 == GPSCtrl_Scanf(pBuff,iBuff_sz,
       			"%2d%2d%2d,%2d%2d%2d", &(sRes->iYear), &(sRes->iMon), &(sRes->iDay),
       								   &(sRes->iHour), &(sRes->iMin), &(sRes->iSec)
       			));
       			
    return (iSuccess?0:-1);        
}


//------------------------------------------------------------------------------
//  Function    : GPSRadar_FindTail_GMC1030
//  Description : Find tail of packet ("\r\n") in buffer and check control sum (CRC).
//------------------------------------------------------------------------------
/** @brief 

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] pRes_crc a integer pointer for return CRC of packet (must be defined).
@return Number of bytes to packet tail.
*/

MMP_LONG GPSRadar_FindTail_GMC1030(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_LONG *pRes_crc)
{
    static const MMP_LONG iTail_sz = 3 /* *[CRC] */ + 2 /* \r\n */;

    const MMP_BYTE *pEnd_buff = pBuff + iBuff_sz;
    MMP_LONG iNread = 0;
    MMP_LONG iCrc = 0;

    *pRes_crc = -1;

    for(;pBuff < pEnd_buff; ++pBuff, ++iNread)
    {
        if(('$' == *pBuff) && iNread)
        {
            pBuff = 0;
            break;
        }
        else if('*' == *pBuff)
        {
            if(pBuff + iTail_sz <= pEnd_buff && '\r' == pBuff[3] && '\n' == pBuff[4])
            {
                *pRes_crc = GPSCtrl_Atoi(pBuff + 1, 2, 16);
                iNread = iBuff_sz - (MMP_LONG)(pEnd_buff - (pBuff + iTail_sz));
                
                if(*pRes_crc != iCrc)
                {
                    *pRes_crc = -1;
                    pBuff = 0;
                }
            }

            break;
        }
        else if(iNread)
            iCrc ^= (MMP_LONG)*pBuff;
    }

    if(*pRes_crc < 0 && pBuff)
        iNread = 0;

    return iNread;
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_Parse_GMC1030
//  Description : Parse GMC1030 packet from buffer.
//------------------------------------------------------------------------------
/** @brief 

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

MMP_LONG GPSRadar_Parse_GMC1030(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, GPSRADARPACK *psPack)
{
    //MMP_BYTE chTime_buff[256];
    memset(psPack, 0, sizeof(GPSRADARPACK));
    if( 18 != GPSCtrl_Scanf(pBuff,iBuff_sz,
        "$1,%2d%2d%2d,%2d%2d%2d,%C,%f,%C,%f,%C,%f,%f,%C,%d,%d,%d,%d*",
        &(psPack->sUTC.iYear),&(psPack->sUTC.iMon),&(psPack->sUTC.iDay),&(psPack->sUTC.iHour),&(psPack->sUTC.iMin),&(psPack->sUTC.iSec),
        &(psPack->chLocated),&(psPack->dwLon),&(psPack->chEW), &(psPack->dwLat),  &(psPack->chNS),
        &(psPack->dwSpeed),  &(psPack->dwDirection) , &(psPack->ubFixedPointSig), &(psPack->ubFixedPointType),
        &(psPack->ubFixedPointSpeedLimit),  &(psPack->usFixedPointDistance) , &(psPack->usMobileRadarSig)
        ))
    {
        printc("GMC1030 parse error!\r\n");
        return 0;
    }    
    #if 0
    if(0 != GPSRadar_ParseTime_GMC1030(&chTime_buff[0], (MMP_LONG)strlen(&chTime_buff[0]), &(psPack->sUTC)))
    {
        printc("GMC1030 time parse error!\r\n");
        return 0;
    }
    #endif
    return 1;
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_ValidValue_GMC1030
//  Description : Check if the value from GPSRadar is valid.
//------------------------------------------------------------------------------

MMP_BOOL GPSRadar_ValidValue_GMC1030(void)
{
   	GPSRADARINFO  *pInfo;
   	
   	pInfo = GPSRadar_Information();
    
    if((pInfo->chLocated) == 'A')
    	return MMP_TRUE;
    else
    	return MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_Information
//  Description : Get the parsed GPSRadar information. 
//------------------------------------------------------------------------------

pGPSRadarInfo GPSRadar_Information(void)
{
    return pGPSRadarInfomation;
}



//------------------------------------------------------------------------------
//  Function    : GPS_GetGMTBackupTime
//  Description : Get the address of GMT time. 
//------------------------------------------------------------------------------

pGPSRadarTime GPSRadar_GetGMTBackupTime(void)
{
    return pGPSRadarGMTBackup;
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_2info_GMC1030
//  Description : Fill INFO structure by GPSRADAR packet data.
//------------------------------------------------------------------------------
/** @brief 
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/

void GPSRadar_2info_GMC1030(GPSRADARPACK *psPack, GPSRADARINFO *psInfo)
{
	psInfo->sUTC.iYear 		= psPack->sUTC.iYear;
	psInfo->sUTC.iMon 		= psPack->sUTC.iMon;
	psInfo->sUTC.iDay 		= psPack->sUTC.iDay;
    psInfo->sUTC.iHour 		= psPack->sUTC.iHour;
    psInfo->sUTC.iMin 		= psPack->sUTC.iMin;
    psInfo->sUTC.iSec 		= psPack->sUTC.iSec;
    psInfo->chLocated    	= psPack->chLocated;
    psInfo->dwLon 			= psPack->dwLon;
    psInfo->dwLat			= psPack->dwLat;
    psInfo->chEW 			= psPack->chEW;
    psInfo->chNS			= psPack->chNS;
    psInfo->dwSpeed			= psPack->dwSpeed;
    psInfo->dwDirection		= psPack->dwDirection;
    psInfo->ubFixedPointSig	= psPack->ubFixedPointSig;
    psInfo->ubFixedPointType	= psPack->ubFixedPointType;
    psInfo->ubFixedPointSpeedLimit	= psPack->ubFixedPointSpeedLimit;
    psInfo->usFixedPointDistance	= psPack->usFixedPointDistance;
    psInfo->usMobileRadarSig	= psPack->usMobileRadarSig;
    
    
    pGPSRadarGMTBackup->iYear 	= psPack->sUTC.iYear;
    pGPSRadarGMTBackup->iMon 	= psPack->sUTC.iMon;
    pGPSRadarGMTBackup->iDay 	= psPack->sUTC.iDay;
	pGPSRadarGMTBackup->iHour 	= psPack->sUTC.iHour;
    pGPSRadarGMTBackup->iMin 	= psPack->sUTC.iMin;
    pGPSRadarGMTBackup->iSec 	= psPack->sUTC.iSec;
    
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_DubugMessageInfo_GMC1030
//  Description : Fill nmeaINFO structure by VTG packet data. 
//------------------------------------------------------------------------------
/** @brief 
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/
void GPSRadar_DubugMessageInfo_GMC1030(GPSRADARINFO *pInfo)
{
    printc("---------------------------------------------------\n");
    printc(" Time Information:\n");
    printc(" Year                = %d \n", pInfo->sUTC.iYear       );
    printc(" Mon                 = %d \n", pInfo->sUTC.iMon        );
    printc(" Day                 = %d \n", pInfo->sUTC.iDay        );
    printc(" Hour                = %d \n", pInfo->sUTC.iHour       );
    printc(" Min                 = %d \n", pInfo->sUTC.iMin        );
    printc(" Sec                 = %d \n", pInfo->sUTC.iSec        );
    printc(" \r\n");
    printc(" Position Information:\n");
    printc(" Located or not      = %c \n", pInfo->chLocated        );
    printc(" East or West        = %c \n", pInfo->chEW		       );
    printc(" Longitude           = %f \n", pInfo->dwLon            );
    printc(" South or North      = %c \n", pInfo->chNS		       );
    printc(" Latitude            = %f \n", pInfo->dwLat            );    
    printc(" Ground Speed(km/h)  = %d \n", pInfo->dwSpeed          );
    printc(" Track angle(degree) = %d \n", pInfo->dwDirection      );
    printc("\n");
    printc(" Radar Information:\n");
    printc(" Fixed point signature = %c \n", pInfo->ubFixedPointSig);
    printc(" Fixed point Type    = %d \n", pInfo->ubFixedPointType );
    printc(" Speed Limit         = %d \n", pInfo->ubFixedPointSpeedLimit );
    printc(" Distance to the Fixed point = %d \n", pInfo->usFixedPointDistance );
    printc(" Mobile Radar Signal = %d \n", pInfo->usMobileRadarSig );
    printc("---------------------------------------------------\n");
}


//------------------------------------------------------------------------------
//  Function    : GPSRadar_ParserMain_GMC1030
//  Description : Entry of GPSRadar_Parser
//------------------------------------------------------------------------------

void GPSRadar_ParserMain_GMC1030(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, GPSRADARINFO *pInfo)
{
	MMP_LONG iRetCrc, iError, iRead = 0, iParsed = 0; 
	{
		iRead = GPSRadar_FindTail_GMC1030(pBuff, iBuff_sz, &iRetCrc);
		if(!iRead)
		{
			printc("iRead Error\r\n");
		}
		else if(iRetCrc > 0)
		{
			iError = GPSRadar_Parse_GMC1030(pBuff,iRead,pGPSRadarPack);
		    
		    GPSRadar_2info_GMC1030(pGPSRadarPack,pGPSRadarInfomation);
		}
		
		iParsed += iRead;	
	}
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_SetCommand_GMC1030
//  Description : Set command to Radar
//------------------------------------------------------------------------------

void GPSRadar_SetCommand_GMC1030(RADARSET_TYPE ubType, MMP_UBYTE ubValue)
{
	MMP_BYTE chCommand[15];
	MMP_BYTE chTempBuffer[2];
	MMP_UBYTE ubXorTemp =0, i;

	MEMSET(chCommand, 0, 15);
	MEMSET(chTempBuffer, 0, 2);
	STRCAT(chCommand, "$2,");
	
	//Command Type.
	if(ubType <10)
	STRCAT(chCommand, "0");
	sprintf(chTempBuffer, "%d",ubType);
	STRCAT(chCommand, chTempBuffer);
	
	STRCAT(chCommand, ":");
	
	//Command Value
	if(ubValue <10)
	STRCAT(chCommand, "0");
	sprintf(chTempBuffer, "%d",ubValue);
	STRCAT(chCommand, chTempBuffer);
	
	STRCAT(chCommand, "*");
	
	//Checksum
	for(i = 1; i<8; i++) //Between $ to *
	ubXorTemp ^= chCommand[i];	
	sprintf(chTempBuffer, "%x",ubXorTemp);
	STRCAT(chCommand ,chTempBuffer);
	
	//Tail
	STRCAT(chCommand, "\r\n");
	printc("chCommand : %s\r\n",chCommand);
	
	//Write fixed-length(13) ASCII codes to Radar
	MMPF_Uart_Write(GPSRADAR_UART_NUM, chCommand, 13 );
		
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_Set_MuteSpeed
//  Description : Set MuteSpeed to Radar
//------------------------------------------------------------------------------

void GPSRadar_Set_MuteSpeed(MMP_UBYTE ubValue)
{
	if (ubValue <= RADARSET_MUTE_OFF)
		ubValue = RADARSET_MUTE_OFF;
	else if (ubValue >= RADARSET_MUTE_50)
		ubValue = RADARSET_MUTE_50;

	GPSRadar_SetCommand_GMC1030(RADARSET_MUTE, ubValue);
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_Set_SpeedRefinement
//  Description : Set Speed to Radar
//------------------------------------------------------------------------------

void GPSRadar_Set_SpeedRefinement(MMP_UBYTE ubValue)
{
	if (ubValue <= RADARSET_SPEED_REFIN_MINUS_10)
		ubValue = RADARSET_SPEED_REFIN_MINUS_10;
	else if (ubValue >= RADARSET_SPEED_REFIN_PLUS_10)
		ubValue = RADARSET_SPEED_REFIN_PLUS_10;

	GPSRadar_SetCommand_GMC1030(RADARSET_SPEED_REFINEMENT, ubValue);
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_Set_AlarmMode
//  Description : Set AlarmMode to Radar
//------------------------------------------------------------------------------

void GPSRadar_Set_AlarmMode(MMP_UBYTE ubValue)
{
	if(ubValue <= RADARSET_ALARM_PICTURE)
	ubValue = RADARSET_ALARM_PICTURE;
	else if(ubValue >= RADARSET_ALARM_SAFE)
	ubValue = RADARSET_ALARM_SAFE;
	
	GPSRadar_SetCommand_GMC1030(RADARSET_ALARM, ubValue);
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_Set_EnableRadar
//  Description : Enable/Disable Radar
//------------------------------------------------------------------------------

void GPSRadar_Set_EnableRadar(MMP_UBYTE ubValue)
{
	if (ubValue <= RADARSET_ENABLE_ON)
		ubValue = RADARSET_ENABLE_ON;
	else if (ubValue >= RADARSET_ENABLE_OFF)
		ubValue = RADARSET_ENABLE_OFF;

	GPSRadar_SetCommand_GMC1030(RADARSET_ENABLE, ubValue);
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_Set_Brightness
//  Description : Set Brightness to Radar
//------------------------------------------------------------------------------

void GPSRadar_Set_Brightness(MMP_UBYTE ubValue)
{
	if (ubValue <= RADARSET_BRIGHTNESS_DARK)
		ubValue = RADARSET_BRIGHTNESS_DARK;
	else if (ubValue >= RADARSET_BRIGHTNESS_AUTO)
		ubValue = RADARSET_BRIGHTNESS_AUTO;

	GPSRadar_SetCommand_GMC1030(RADARSET_BRIGHTNESS, ubValue);
}

//------------------------------------------------------------------------------
//  Function    : GPSRadar_Set_Volume
//  Description : Set Volume to Radar
//------------------------------------------------------------------------------

void GPSRadar_Set_Volume(MMP_UBYTE ubValue)
{
	if (ubValue <= RADARSET_VOLUME_LEVEL_01)
		ubValue = RADARSET_VOLUME_LEVEL_01;
	else if (ubValue >= RADARSET_VOLUME_LEVEL_05)
		ubValue = RADARSET_VOLUME_LEVEL_05;

	GPSRadar_SetCommand_GMC1030(RADARSET_VOLUME, ubValue);
}

#if (GPS_CONFIG_NMEA_FILE)
//------------------------------------------------------------------------------
//  Function    : GPS_GetGPSStringFromFile
//  Description : Read GPS string from file
//------------------------------------------------------------------------------

void GPS_GetGPSStringFromFile(MMP_BYTE *bGPSRadarString, MMP_ULONG *ulGPSRadarStringLength)
{
	MMP_ERR 	err;
	char 		*ubBuffer;
	MMP_ULONG 	read_count;
	MMP_UBYTE 	i;
	MMP_LONG64 	l64CurrFilePosition = 0;
	
	MEMSET(bGPSRadarString, 0, 0xFF);
	if(!ulGPSRadarFileID)
	{
		err = MMPF_FS_FOpen("SD:\\GPSRadar_Info.txt", "rb", &ulGPSRadarFileID);
		if(err)
		{
			printc("File open error\r\n");
			return;
		}
		err = MMPF_FS_GetFileSize(ulGPSRadarFileID, &ul64GPSRadarFileSize);
		if(err)
		{
			printc("File GetFileSize error\r\n");
			MMPF_FS_FClose(ulGPSRadarFileID);
			return;
		}
	}
	MMPF_FS_FTell(ulGPSRadarFileID, &l64CurrFilePosition);
	if(((l64CurrFilePosition + 256) > ul64GPSRadarFileSize) && ul64GPSRadarFileSize >256 )
	{
		MMPF_FS_FClose(ulGPSRadarFileID);
		ulGPSRadarFileID = 0;
	}
	
	if(ulGPSRadarFileID)
	{
		for( i = 0; i<256; i++)
		{
			MMPF_FS_FRead(ulGPSRadarFileID,ubBuffer,1,&read_count);
			
			if(*ubBuffer == '$')
			{
				if(bStartCount == MMP_FALSE)
				{
					bStartCount = MMP_TRUE;
					bGPSRadarStartPosition = i;
				}
			}
			if(bStartCount == MMP_TRUE)
			{
				if(*ubBuffer == '*')
				{
					bGPSRadarStringCounter = i;
					break;
				}
			}
		}
		
		*ulGPSRadarStringLength = (bGPSRadarStringCounter - bGPSRadarStartPosition + 1) + 4; //Add CRC & '\r\n'
		
		MMPF_FS_FSeek(ulGPSRadarFileID,(l64CurrFilePosition+bGPSRadarStartPosition),0);
		MMPF_FS_FRead(ulGPSRadarFileID, bGPSRadarString, (bGPSRadarStringCounter- bGPSRadarStartPosition + 1)+2,&read_count);
		MMPF_FS_FSeek(ulGPSRadarFileID,1,1);
		
		FS_STRCAT(bGPSRadarString,"\r");
		FS_STRCAT(bGPSRadarString,"\n");
		MMPF_FS_FTell(ulGPSRadarFileID, &l64CurrFilePosition);
		
		bGPSRadarStringCounter = 0;
		bGPSRadarStartPosition = 0;
		printc("%s",(bGPSRadarString));
	}
}
#endif
#endif // #if (GPS_CONNECT_ENABLE && (GPS_MODULE == GPS_MODULE_GMC1030))
