/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "gps_ctl.h"
#include "ait_utility.h"
#include "MenuSetting.h"

#if (GPS_CONNECT_ENABLE && (GPS_MODULE == GPS_MODULE_NMEA0183))
#include "gps_nmea0183.h"
#if (GPS_CONFIG_NMEA_FILE)
#include "ahc_fs.h"
#include "fs_clib.h"
#endif
#if (EDOG_ENABLE)
#include "edog_ctl.h"
#endif
#include "GSensor_ctrl.h"
#include "ahc_os.h"
#include "drv_uart_api.h"
#include "drv_uart.h"
#include "drv_gpio.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

void printc(char* fmt, ...);
#ifdef _DEBUG_
#define DPRINT( ... )   printc( __VA_ARGS__);
#else
#define DPRINT( ... )   {}
#endif

/*===========================================================================
 * Global varible
 *===========================================================================*/

#if (GPS_CONFIG_NMEA_FILE)
static MMP_ULONG    ulGPSFileID         = 0;
static MMP_ULONG    ul64GPSFileSize     = 0;
static MMP_BOOL     bStartCount         = MMP_FALSE;
static MMP_BOOL     bGPSStartPosition;
static MMP_BOOL     bGPSStringCounter;
static MMP_BOOL     m_bEOF              = MMP_FALSE;
#endif

static MMP_BYTE     m_bGPSString[GPS_RX_QUEUE_SIZE] = {0};
//static MMP_ULONG  m_bGPSStringLen;
static int          m_ulStartPosition = 0, m_ulEndPosition = 0;
static int          m_nGpsStartSignNum = 0;

static __attribute__((aligned(32))) MMP_UBYTE   m_ulGPSBuffStartAddr[GPS_CONFIG_BUFFER_SIZE] = {0};
//static MMP_ULONG  m_ulTTFFCounter;
#if 1 // moved to GPSCtrl_Initial()
static MMP_BOOL     bReceiveFirstString = MMP_FALSE;
#endif

//static MMP_UBYTE  ubCntUBlox7         = 0;
//static MMP_BOOL   bStartSimulation    = MMP_FALSE;

NMEAGGA             *pGGAPack;
NMEAGSA             *pGSAPack;
NMEAGSV             *pGPGSVPack, *pGLGSVPack;
NMEARMC             *pRMCPack;
NMEAVTG             *pVTGPack;
NMEAINFO            *pGPSInfo;
GPSINFOCHUCK        *pGPSInfoForChuck;
NMEATIME            *pGMTBackup;

MMP_ULONG           dump_nmeaflag = 0;


static MMP_UBYTE    ubSetExpert[48]         = {0xB5, 0x62, 0x06, 0x23, 0x28, 0x00, 0x00, 0x00, 0x4C, 0x66,
                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x16, 0x07, 0x00,
                                               0x00, 0x00, 0x00, 0x00, 0x9B, 0x06, 0x00, 0x00, 0x00, 0x00,
                                               0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0xE0}; // 48

static MMP_UBYTE    ubSLconfig[21]          = {0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00,
                                               0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1D,
                                               0xAB}; // 21
// End of new added commands for u-blox 7


struct _3RD_PARTY_GPS *gpGPS_obj = NULL;

extern MMP_BYTE     ubGPSRawBuffer_0[GPS_RAW_BUFFER_SIZE];
extern MMP_ULONG    ulGPSRawBufferLen_0;
extern MMP_BYTE     ubGPSRawBuffer_1[GPS_RAW_BUFFER_SIZE];
extern MMP_ULONG    ulGPSRawBufferLen_1;
extern MMP_UBYTE    ubGPSRAWBufferIndex;
extern MMP_ULONG    ulGPSRawEmerStartAddr;
extern MMP_UBYTE    ubGPSRawEmerBufIndex;

#if (EDOG_ENABLE)
extern EDOG_BOOL EDOGIO_GPS_MsgHandle(void);
#endif

/*===========================================================================
 * Main body
 *===========================================================================*/
/**********************************************************************************************************/
/* the proto-type of video APIs*/

MMP_HANDLE GPS_NMEA0183_Open(void)
{
    NMEAINFO *mgps;
    pGPSInfo = (NMEAINFO*)(m_ulGPSBuffStartAddr+600);
    mgps = pGPSInfo;
    mgps->h_dec = (void*)(pGPSInfo);
    //MMPF_3RDParty_GPS_Initiate();
    return mgps;
}
//------------------------------------------------------------------------------
//  Function    : Gps_PostitionOffset
//  Description :
//------------------------------------------------------------------------------
char gpsstr[]="$GPRMC,,,,,a,,,,,";
#if (GPS_OFFSET_ENABLE == 1)
static double Gps_PostitionOffset(double gbGPSLatLon, MMP_UBYTE ubLat) //ubLat 0: Latitude  1: Longitude
{
    double dbPos = 0;
    dbPos = (!gubLiteType)? GpsDmmToDegree_double(gbGPSLatLon): GpsDmmToDegree_float(gbGPSLatLon);
    if(!ubLat)
    dbPos += GPS_OFFSET_LAT;
    else
    dbPos += GPS_OFFSET_LON;

    //printc("dbPos %d: %f\r\n",ubLat,dbPos);
    return (!gubLiteType)? DegreeToGpsDmm_double(dbPos): DegreeToGpsDmm_float(dbPos);
}

#endif

void GPS_String_RxCallback(MMP_UBYTE size, MMP_UBYTE *fifo)
{
//    MMP_LONG i;
    MMP_BYTE chGPSchar;

 /*
    for(i = 0; i < size; i++)
    {
        chGPSchar =  *fifo;
    }
    return;

    if(size > GPS_RX_QUEUE_SIZE)
        printc("!!!!!!!!!!!!!!!!\r\n");
*/
    //for(i = 0; i < size; i++)
    while(size--)
    {
        int nNextPos = (m_ulEndPosition + 1) %GPS_RX_QUEUE_SIZE;
            //GPS_RX_QUEUE_SIZE;
        // chech next pos valid

        if(nNextPos == m_ulStartPosition )
        {
            static AHC_BOOL bShowed = AHC_FALSE;
            if( !bShowed )
            {
                printc("==> GPS buffer full %d\n", m_nGpsStartSignNum);
                bShowed = AHC_TRUE;

            }
            while(size--)        chGPSchar =  *fifo;
            break;
        }

        chGPSchar =  *fifo;

        m_bGPSString[m_ulEndPosition] = chGPSchar;


        if(chGPSchar == RX_GPS_SIGNAL)
        {
            m_nGpsStartSignNum++;
//            MMPF_OS_SetFlags(UartCtrlFlag, GPS_FLAG_GETGPSPACK, MMPF_OS_FLAG_SET); // GPS control flow to get GPS package from UART
        }

        m_ulEndPosition = nNextPos;

    }
//  MMPF_OS_SetFlags(UartCtrlFlag, GPS_FLAG_GETGPSPACK, MMPF_OS_FLAG_SET); // GPS control flow to get GPS package from UART
//    printc("]");
}

static void _GPS_String_RxCallback(MMP_UBYTE uart_num, MMP_UBYTE *buffer, MMP_ULONG size)
{
    GPS_String_RxCallback(size, buffer);
}

//------------------------------------------------------------------------------
//  Function    : GPS_GetString
//  Description : This function will send back the string until the user enter the "$"
//------------------------------------------------------------------------------

char szGpsTestStr[]="$GPRMC,110501.00,A,2503.78270,N,12135.45905,E,2.528,355.44,251013,,,A*67\r\n";

//char szGpsTestStr[]="$GPGSV,3,1,10,02,18,147,09,05,34,075,24,08,04,035,,09,05,036,08*77\r\n";

//char szGpsTestStr[]="$GPRMC,110501.00,A,2503.78270,N,12135.45905,E,2.528,355.44,251013,,,oooxxxoox\r\n";

//char szGpsTestStr[]="$GPRMC\r\n";

MMP_ERR GPS_GetString_UART(MMP_BYTE *bGPSString, MMP_ULONG *ulGPSStringLength)
{
/*
    printc("g");
    STRCPY( bGPSString, szGpsTestStr );
    *ulGPSStringLength = STRLEN(szGpsTestStr);
    m_ulStartPosition = m_ulEndPosition;
*/

    MMP_LONG j;
    int nLen;
    int nNextPost =0;
    int nGpsStartCharNum = 0;
    MMP_ULONG ulStartPositionBack = m_ulStartPosition;

    nLen = m_ulEndPosition - m_ulStartPosition;
    nLen = (nLen<0)?nLen+GPS_RX_QUEUE_SIZE : nLen;

    //printc("nLen = %d\n", nLen );

    if( m_nGpsStartSignNum < 2 )
    {
        *ulGPSStringLength = 0;
        return 0;
    }

    j = 0;

    while(nLen>0)
    {
        char chGPSchar =  m_bGPSString[m_ulStartPosition];
        //printc("gps c: %c",chGPSchar);
        if(chGPSchar == RX_GPS_SIGNAL)
        {
            nGpsStartCharNum++;

            if( nGpsStartCharNum == 2 )
            {
                MMPF_OS_SetFlags(UartCtrlFlag, GPS_FLAG_GETGPSPACK, MMPF_OS_FLAG_SET); // GPS control flow to get GPS package from UART
                //printc("}");
                break;
            }

            m_nGpsStartSignNum--;

        }
        nNextPost = (m_ulStartPosition +1)%GPS_RX_QUEUE_SIZE;
        bGPSString[j++] = chGPSchar;//m_bGPSString[m_ulStartPosition];
        m_ulStartPosition = nNextPost;
        nLen-- ;
    }

    if( nGpsStartCharNum < 2 )
    {
        // roll back
        m_ulStartPosition  = ulStartPositionBack;
        *ulGPSStringLength = 0;
        bGPSString[0] = '\0';
    }
    else
    {
        *ulGPSStringLength = j;
        bGPSString[j] = '\0';
    }


    //printc("GPSStringLength : %d %s\r\n",*ulGPSStringLength, bGPSString);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : GPS_InitPathUART_NMEA0183
//  Description : Initialize the UART path.
//------------------------------------------------------------------------------

void GPS_InitPathUART_NMEA0183(MMP_ULONG ulBaudRate)
{
    Uart_cfg_t      uart_cfg;
    vm_v24_Rate_t   baud_rate;

    baud_rate = (ulBaudRate == 300) ? VM_V24_300 :
                (ulBaudRate == 600) ? VM_V24_600 :
                (ulBaudRate == 1200) ? VM_V24_1200 :
                (ulBaudRate == 2400) ? VM_V24_2400 :
                (ulBaudRate == 4800) ? VM_V24_4800 :
                (ulBaudRate == 9600) ? VM_V24_9600 :
                (ulBaudRate == 19200) ? VM_V24_19200 :
                (ulBaudRate == 38400) ? VM_V24_38400 :
                (ulBaudRate == 57600) ? VM_V24_57600 :
                (ulBaudRate == 115200) ? VM_V24_115200 :
                (ulBaudRate == 230400) ? VM_V24_230400 :
                (ulBaudRate == 460800) ? VM_V24_460800 :
                (ulBaudRate == 921600) ? VM_V24_921600 :
                VM_V24_UNDEFINED_RATE;

    if (baud_rate == VM_V24_UNDEFINED_RATE) {
        printc("%s set baud rate error\r\n", __func__);
    }

    uart_cfg.length = VM_V24_8BIT_LENGTH;
    uart_cfg.parity = VM_V24_NO_PARITY;
    uart_cfg.stop = VM_V24_1STOP_BIT;
    uart_cfg.rate = baud_rate;
    uart_cfg.signal_mask = (VM_V24_SIGNAL_RX | VM_V24_SIGNAL_TX);
    uart_cfg.RxFlowCtrlMethod = VM_V24_NONE;
    uart_cfg.TxFlowCtrlMethod = VM_V24_NONE;
    uart_cfg.rxCallback = _GPS_String_RxCallback;
    uart_cfg.txCallback = NULL;
    uart_cfg.EvtCallback = NULL;
    uart_Open(FUART, &uart_cfg);
}

void GPS_InitPathUART_E_DOG(void)
{
    //MMP_UART_ATTR uartattribute;
    MMP_LONG            error;

    printc("init E_Dog\r\n");
    //uartattribute.bParityEn   = MMP_FALSE;
    //uartattribute.parity      = MMP_UART_PARITY_ODD;
    //uartattribute.bFlowCtlEn  = MMP_FALSE;
    //uartattribute.ubFlowCtlSelect = 1;
    //uartattribute.padset      = 4;
    //uartattribute.ulMasterclk     = GPS_MASTER_CLK * 1000 ;
    //uartattribute.ulBaudrate  = GPS_BAUD_RATE;

    //error = MMPF_Uart_Open(MMP_UART_ID_2, &uartattribute);
    //TODO: Call M5 uart driver

    if(error)
        printc("Uart UseRxDMA : %d\r\n",error);
}

void GPS_UnInitPathUART_NMEA0183(MMP_ULONG ulBaudRate)
{
    MMP_LONG error;

    //error = MMPF_Uart_DisableRx(GPS_UART_NUM);
    //error = MMPF_Uart_Close(GPS_UART_NUM);
    //TODO: Call M5 uart driver

    if(error)
        printc("GPS_UnInitPathUART_NMEA0183 Error : %d\r\n",error);
}

//------------------------------------------------------------------------------
//  Function    : GPS_ControlPathUART_NMEA0183
//  Description : Control the UART path.
//------------------------------------------------------------------------------

void GPS_ControlPathUART_NMEA0183(MMP_BOOL bEnable)
{
    if(bEnable) {
        //MMPF_Uart_EnableRx(GPS_UART_NUM, 1,(UartCallBackFunc *)&GPS_String_RxCallback);
        //TODO: Call M5 uart driver
    }
    else {
        //MMPF_Uart_DisableRx(GPS_UART_NUM);
        //TODO: Call M5 uart driver
    }
}

//------------------------------------------------------------------------------
//  Function    : GPS_ControlReceivePath_NMEA0183
//  Description : Control(on/off) the path between GPS and DSP.
//------------------------------------------------------------------------------

void GPS_ControlReceivePath_NMEA0183(MMP_BYTE path,MMP_BOOL bEnable)
{
    switch (path)
    {
        case NMEA_RECEIVE_UART:
            GPS_ControlPathUART_NMEA0183(bEnable);
        break;
        case NMEA_RECEIVE_USB:
        //To do;
        break;
        case NMEA_RECEIVE_DDC:
        //To do;
        break;
        #if (GPS_CONFIG_NMEA_FILE)
        case NMEA_RECEIVE_TXT:
        break;
        #endif
    }
}

//------------------------------------------------------------------------------
//  Function    : GPS_GetGPSPack_NMEA0183
//  Description : Control(on/off) the path between GPS and DSP.
//------------------------------------------------------------------------------

void GPS_GetGPSPack_NMEA0183(MMP_BYTE path, MMP_BYTE *bGPSString, MMP_ULONG *ulGPSStringLength)
{
    switch (path)
    {
        case NMEA_RECEIVE_UART:
            GPS_GetString_UART(bGPSString,ulGPSStringLength);
        break;
        case NMEA_RECEIVE_USB:
            //To do;
        break;
        case NMEA_RECEIVE_DDC:
            //To do;
        break;
        #if (GPS_CONFIG_NMEA_FILE)
        case NMEA_RECEIVE_TXT:
            GPS_GetGPSStringFromFile(bGPSString,ulGPSStringLength);
        break;
        #endif
    }
}

//------------------------------------------------------------------------------
//  Function    : GPS_InitReceivePath_NMEA0183
//  Description : Select the path between GPS and DSP.
//------------------------------------------------------------------------------

void GPS_InitReceivePath_NMEA0183(MMP_BYTE path, MMP_ULONG ulBaudRate)
{
    switch (path)
    {
        case NMEA_RECEIVE_UART:
            GPS_InitPathUART_NMEA0183(ulBaudRate);
        break;
        case NMEA_RECEIVE_USB:
        //To do;
        break;
        case NMEA_RECEIVE_DDC:
        //To do;
        break;
        #if (GPS_CONFIG_NMEA_FILE)
        case NMEA_RECEIVE_TXT:
        break;
        #endif
    }
}

//------------------------------------------------------------------------------
//  Function    : GPS_ParserInitialize_NMEA0183
//  Description : Set required memory to 0.
//------------------------------------------------------------------------------

void GPS_ParserInitialize_NMEA0183(void)
{
    if(m_ulGPSBuffStartAddr == 0)
    {
        printc("GPS_ParserInitialize Error: No Buffer Address\r\n");
        return;
    }

    pGGAPack            = (NMEAGGA*)(m_ulGPSBuffStartAddr);
    pGSAPack            = (NMEAGSA*)(m_ulGPSBuffStartAddr+100);
    pGPGSVPack          = (NMEAGSV*)(m_ulGPSBuffStartAddr+200);
    pGLGSVPack          = (NMEAGSV*)(m_ulGPSBuffStartAddr+300);
    pRMCPack            = (NMEARMC*)(m_ulGPSBuffStartAddr+400);
    pVTGPack            = (NMEAVTG*)(m_ulGPSBuffStartAddr+500);
    pGPSInfo            = (NMEAINFO*)(m_ulGPSBuffStartAddr+600);
    pGPSInfoForChuck    = (GPSINFOCHUCK*)(m_ulGPSBuffStartAddr+1000);
    pGMTBackup          = (NMEATIME*)((m_ulGPSBuffStartAddr+1100));

    memset(pGGAPack, 0, sizeof(NMEAGGA));
    memset(pGSAPack, 0, sizeof(NMEAGSA));
    memset(pGPGSVPack, 0, sizeof(NMEAGSV));
    memset(pGLGSVPack, 0, sizeof(NMEAGSV));
    memset(pRMCPack, 0, sizeof(NMEARMC));
    memset(pVTGPack, 0, sizeof(NMEAVTG));
    memset((unsigned char*)pGPSInfo + sizeof(MMP_HANDLE), 0, sizeof(NMEAINFO));
    memset(pGPSInfoForChuck, 0, sizeof(GPSINFOCHUCK));
    memset(pGMTBackup, 0, sizeof(NMEATIME));
}

//------------------------------------------------------------------------------
//  Function    : GPS_ResetContainer_NMEA0183
//  Description : Set required memory to 0.
//------------------------------------------------------------------------------

void GPS_ResetContainer_NMEA0183(void)
{
    memset(pGGAPack, 0, sizeof(NMEAGGA));
    memset(pGSAPack, 0, sizeof(NMEAGSA));
    memset(pGPGSVPack, 0, sizeof(NMEAGSV));
    memset(pGLGSVPack, 0, sizeof(NMEAGSV));
    memset(pRMCPack, 0, sizeof(NMEARMC));
    memset(pVTGPack, 0, sizeof(NMEAVTG));
    memset(pGPSInfo, 0, sizeof(NMEAINFO));
    memset(pGPSInfoForChuck, 0, sizeof(GPSINFOCHUCK));
    memset(pGMTBackup, 0, sizeof(NMEATIME));
}

//------------------------------------------------------------------------------
//  Function    : GPS_GMT2LocalTime
//  Description : Convert received time to Local time
//------------------------------------------------------------------------------

void GPS_GMT2LocalTime(NMEATIME *sGMTBackup, NMEATIME *sRes, signed char sbGMTOffset)
{
    MMP_LONG lBackupYear,lBackupDay,lBackupHour,lBackupMin;
    signed char byHour = sbGMTOffset/4;
    signed char byMinute = (sbGMTOffset%4)*15;

    if( sGMTBackup->iYear == 0 ||  sGMTBackup->iMon == 0 ||  sGMTBackup->iDay == 0)
    return;

    if(byHour < -12)
        byHour = -12;
    else if(byHour > 13)
        byHour = 13;

    lBackupYear = sGMTBackup->iYear;
    lBackupDay  = sGMTBackup->iDay;
    lBackupHour = sGMTBackup->iHour;
    lBackupMin  = sGMTBackup->iMin;

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
    sRes->iMon  = sGMTBackup->iMon ;
    sRes->iDay  = sGMTBackup->iDay;
    sRes->iHour = sGMTBackup->iHour;
    sRes->iMin  = sGMTBackup->iMin ;
    sRes->iSec  = sGMTBackup->iSec ;

    sGMTBackup->iYear   = lBackupYear;
    sGMTBackup->iDay    = lBackupDay;
    sGMTBackup->iHour   = lBackupHour;
    sGMTBackup->iMin    = lBackupMin;
}

//------------------------------------------------------------------------------
//  Function    : GPS_ParseTime_NMEA0183
//  Description : Parse received time format and check if it is valid
//------------------------------------------------------------------------------

MMP_LONG GPS_ParseTime_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEATIME *sRes)
{
    MMP_LONG iSuccess = 0;

    switch(iBuff_sz)
    {
        case sizeof("hhmmss") - 1:
            iSuccess = (3 == GPSCtrl_Scanf(pBuff,iBuff_sz,
                        "%2d%2d%2d", &(sRes->iHour), &(sRes->iMin), &(sRes->iSec)
                        ));
        break;
        case sizeof("hhmmss.s") - 1:
        case sizeof("hhmmss.ss") - 1:
        case sizeof("hhmmss.sss") - 1:
            iSuccess = (4 == GPSCtrl_Scanf(pBuff,iBuff_sz,
                        "%2d%2d%2d.%d", &(sRes->iHour), &(sRes->iMin), &(sRes->iSec), &(sRes->iHsec)
                        ));
        break;
        default:
            DPRINT("Parse of time error (format error)!\r\n");
            iSuccess = 0;
        break;
    }

    return (iSuccess?0:-1);
}

//------------------------------------------------------------------------------
//  Function    : GPS_PackType_NMEA0183
//  Description : Define packet type by header
//------------------------------------------------------------------------------

MMP_LONG GPS_PackType_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz)
{
    static const MMP_BYTE *szHeads[] = {
        "GPGGA",
        "GPGSA",
        "GPGSV",
        "GPRMC",
        "GPVTG",
        "GPGLL",
        "GNGSA",
        "GNRMC",
        "GLGSV"
    };

    if(iBuff_sz < 5)
        return GPNON;
    else if(0 == memcmp(pBuff, szHeads[0], 5))
        return GPGGA;
    else if(0 == memcmp(pBuff, szHeads[1], 5))
        return GPGSA;
    else if(0 == memcmp(pBuff, szHeads[2], 5))
        return GPGSV;
    else if(0 == memcmp(pBuff, szHeads[3], 5))
        return GPRMC;
    else if(0 == memcmp(pBuff, szHeads[4], 5))
        return GPVTG;
    else if(0 == memcmp(pBuff, szHeads[5], 5))
        return GPGLL;
    else if(0 == memcmp(pBuff, szHeads[6], 5))
        return GNGSA;
    else if(0 == memcmp(pBuff, szHeads[7], 5))
        return GNRMC;
    else if(0 == memcmp(pBuff, szHeads[8], 5))
        return GLGSV;

    return GPNON;
}

//------------------------------------------------------------------------------
//  Function    : GPS_FindTail_NMEA0183
//  Description : Find tail of packet ("\r\n") in buffer and check control sum (CRC).
//------------------------------------------------------------------------------
/** @brief

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] pRes_crc a integer pointer for return CRC of packet (must be defined).
@return Number of bytes to packet tail.
*/

MMP_LONG GPS_FindTail_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_LONG *pRes_crc)
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
//  Function    : GPS_ParseGPGGA_NMEA0183
//  Description : Parse GGA packet from buffer.
//------------------------------------------------------------------------------
/** @brief

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

MMP_LONG GPS_ParseGPGGA_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGGA *psPack)
{
    MMP_BYTE chTime_buff[256];

    memset(psPack, 0, sizeof(NMEAGGA));

    if (dump_nmeaflag & D_GGA) {
        *(pBuff + iBuff_sz) = 0;
        printc("%s", pBuff);
    }

    if(14 != GPSCtrl_Scanf(pBuff,iBuff_sz,
        "$GPGGA,%s,%f,%s,%f,%s,%d,%d,%f,%f,%s,%f,%s,%f,%d*",
        &(chTime_buff[0]),
        &(psPack->dwLat),  &(psPack->chNS),         &(psPack->dwLon),      &(psPack->chEW),
        &(psPack->iSig),   &(psPack->iSatinuse),    &(psPack->dwHDOP),     &(psPack->dwElv), &(psPack->chElv_Units),
        &(psPack->dwDiff), &(psPack->chDiff_Units), &(psPack->dwDgps_Age), &(psPack->iDgps_sid)))
    {
        DPRINT("GPGGA parse error!\r\n");
        return 0;
    }

    if(0 != GPS_ParseTime_NMEA0183(&chTime_buff[0], (MMP_LONG)strlen(&chTime_buff[0]), &(psPack->sUTC)))
    {
        DPRINT("GPGGA time parse error!\r\n");
        return 0;
    }

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : GPS_ParseGPGSA_NMEA0183
//  Description : Parse GSA packet from buffer.
//------------------------------------------------------------------------------
/** @brief

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/
MMP_LONG GPS_ParseGPGSA_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGSA *psPack)
{
    memset(psPack, 0, sizeof(NMEAGSA));

    if (dump_nmeaflag & D_GSA) {
        *(pBuff + iBuff_sz) = 0;
        printc("%s", pBuff);
    }

    if(17 != GPSCtrl_Scanf(pBuff,iBuff_sz,
        "$GPGSA,%C,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f*",
        &(psPack->chFix_Mode),  &(psPack->iFix_Type),
        &(psPack->iSat_Prn[0]), &(psPack->iSat_Prn[1]), &(psPack->iSat_Prn[2]), &(psPack->iSat_Prn[3]), &(psPack->iSat_Prn[4]), &(psPack->iSat_Prn[5]),
        &(psPack->iSat_Prn[6]), &(psPack->iSat_Prn[7]), &(psPack->iSat_Prn[8]), &(psPack->iSat_Prn[9]), &(psPack->iSat_Prn[10]), &(psPack->iSat_Prn[11]),
        &(psPack->dwPDOP),      &(psPack->dwHDOP),      &(psPack->dwVDOP)))
    {
        DPRINT("GPGSA parse error!\r\n");
        return 0;
    }

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : GPS_ParseGNGSA_NMEA0183
//  Description : Parse GSA packet from buffer.
//------------------------------------------------------------------------------
/** @brief

@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/
MMP_LONG GPS_ParseGNGSA_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGSA *psPack)
{
    memset(psPack, 0, sizeof(NMEAGSA));

    if (dump_nmeaflag & D_GSA) {
        *(pBuff + iBuff_sz) = 0;
        printc("%s", pBuff);
    }

    if(17 != GPSCtrl_Scanf(pBuff,iBuff_sz,
        "$GNGSA,%C,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f*",
        &(psPack->chFix_Mode),  &(psPack->iFix_Type),
        &(psPack->iSat_Prn[0]), &(psPack->iSat_Prn[1]), &(psPack->iSat_Prn[2]), &(psPack->iSat_Prn[3]), &(psPack->iSat_Prn[4]), &(psPack->iSat_Prn[5]),
        &(psPack->iSat_Prn[6]), &(psPack->iSat_Prn[7]), &(psPack->iSat_Prn[8]), &(psPack->iSat_Prn[9]), &(psPack->iSat_Prn[10]), &(psPack->iSat_Prn[11]),
        &(psPack->dwPDOP),      &(psPack->dwHDOP),      &(psPack->dwVDOP)))
    {
        DPRINT("GNGSA parse error!\r\n");
        return 0;
    }

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : GPS_ParseGPGSV_NMEA0183
//  Description : Parse GSV packet from buffer.
//------------------------------------------------------------------------------
/** @brief
@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

MMP_LONG GPS_ParseGPGSV_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGSV *psPack)
{
    MMP_LONG iNsen, iNsat;

    memset(psPack, 0, sizeof(NMEAGSV));

    if (dump_nmeaflag & D_GSV) {
        *(pBuff + iBuff_sz) = 0;
        printc("%s", pBuff);
    }

    iNsen = GPSCtrl_Scanf(pBuff,iBuff_sz,
        "$GPGSV,%d,%d,%d,"
        "%d,%d,%d,%d,"
        "%d,%d,%d,%d,"
        "%d,%d,%d,%d,"
        "%d,%d,%d,%d*",
        &(psPack->iPack_count), &(psPack->iPack_index), &(psPack->iSat_count),
        &(psPack->sSat_data[0].iId), &(psPack->sSat_data[0].iElv), &(psPack->sSat_data[0].iAzimuth), &(psPack->sSat_data[0].iSig),
        &(psPack->sSat_data[1].iId), &(psPack->sSat_data[1].iElv), &(psPack->sSat_data[1].iAzimuth), &(psPack->sSat_data[1].iSig),
        &(psPack->sSat_data[2].iId), &(psPack->sSat_data[2].iElv), &(psPack->sSat_data[2].iAzimuth), &(psPack->sSat_data[2].iSig),
        &(psPack->sSat_data[3].iId), &(psPack->sSat_data[3].iElv), &(psPack->sSat_data[3].iAzimuth), &(psPack->sSat_data[3].iSig));

    iNsat = (psPack->iPack_index - 1) * NMEA_SATINPACK;
    iNsat = (iNsat + NMEA_SATINPACK > psPack->iSat_count)?psPack->iSat_count - iNsat:NMEA_SATINPACK;
    iNsat = iNsat * 4 + 3 /* first three sentence`s */;

    if(iNsen < iNsat || iNsen > (NMEA_SATINPACK * 4 + 3))
    {
        DPRINT("GPGSV parse error!\r\n");
        return 0;
    }

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : GPS_ParseGLGSV_NMEA0183
//  Description : Parse GSV packet from buffer.
//------------------------------------------------------------------------------
/** @brief
@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

MMP_LONG GPS_ParseGLGSV_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAGSV *psPack)
{
    MMP_LONG iNsen, iNsat;

    memset(psPack, 0, sizeof(NMEAGSV));

    if (dump_nmeaflag & D_GSV) {
        *(pBuff + iBuff_sz) = 0;
        printc("%s", pBuff);
    }

    iNsen = GPSCtrl_Scanf(pBuff,iBuff_sz,
        "$GLGSV,%d,%d,%d,"
        "%d,%d,%d,%d,"
        "%d,%d,%d,%d,"
        "%d,%d,%d,%d,"
        "%d,%d,%d,%d*",
        &(psPack->iPack_count), &(psPack->iPack_index), &(psPack->iSat_count),
        &(psPack->sSat_data[0].iId), &(psPack->sSat_data[0].iElv), &(psPack->sSat_data[0].iAzimuth), &(psPack->sSat_data[0].iSig),
        &(psPack->sSat_data[1].iId), &(psPack->sSat_data[1].iElv), &(psPack->sSat_data[1].iAzimuth), &(psPack->sSat_data[1].iSig),
        &(psPack->sSat_data[2].iId), &(psPack->sSat_data[2].iElv), &(psPack->sSat_data[2].iAzimuth), &(psPack->sSat_data[2].iSig),
        &(psPack->sSat_data[3].iId), &(psPack->sSat_data[3].iElv), &(psPack->sSat_data[3].iAzimuth), &(psPack->sSat_data[3].iSig));

    iNsat = (psPack->iPack_index - 1) * NMEA_SATINPACK;
    iNsat = (iNsat + NMEA_SATINPACK > psPack->iSat_count)?psPack->iSat_count - iNsat:NMEA_SATINPACK;
    iNsat = iNsat * 4 + 3 /* first three sentence`s */;

    if(iNsen < iNsat || iNsen > (NMEA_SATINPACK * 4 + 3))
    {
        DPRINT("GLGSV parse error!\r\n");
        return 0;
    }

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : GPS_ParseGPRMC_NMEA0183
//  Description : Parse RMC packet from buffer.
//------------------------------------------------------------------------------
/** @brief
@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

MMP_LONG GPS_ParseGPRMC_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEARMC *psPack)
{
    MMP_LONG iNsen;
    MMP_BYTE chTime_buff[256];

    memset(psPack, 0, sizeof(NMEARMC));

    if (dump_nmeaflag & D_RMC) {
        *(pBuff + iBuff_sz) = 0;
        printc("%s", pBuff);
    }

    iNsen = GPSCtrl_Scanf(pBuff,iBuff_sz,
        "$GPRMC,%s,%C,%f,%C,%f,%C,%f,%f,%2d%2d%2d,%f,%C,%C*",
        &(chTime_buff[0]),
        &(psPack->chStatus),      &(psPack->dwLat),       &(psPack->chNS), &(psPack->dwLon), &(psPack->chEW),
        &(psPack->dwSpeed),       &(psPack->dwDirection),
        &(psPack->sUTC.iDay),     &(psPack->sUTC.iMon),   &(psPack->sUTC.iYear),
        &(psPack->dwDeclination), &(psPack->chDeclin_ew), &(psPack->chMode));

    if(iNsen != 13 && iNsen != 14)
    {
        DPRINT("GPRMC parse error!\r\n");
        return 0;
    }

    if(0 != GPS_ParseTime_NMEA0183(&chTime_buff[0], (MMP_LONG)strlen(&chTime_buff[0]), &(psPack->sUTC)))
    {
        DPRINT("GPRMC time parse error!\r\n");
        return 0;
    }

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : GPS_ParseGNRMC_NMEA0183
//  Description : Parse RMC packet from buffer.
//------------------------------------------------------------------------------
/** @brief
@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

MMP_LONG GPS_ParseGNRMC_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEARMC *psPack)
{
    MMP_LONG iNsen;
    MMP_BYTE chTime_buff[256];

    memset(psPack, 0, sizeof(NMEARMC));

    if (dump_nmeaflag & D_RMC) {
        *(pBuff + iBuff_sz) = 0;
        printc("%s", pBuff);
    }

    iNsen = GPSCtrl_Scanf(pBuff,iBuff_sz,
        "$GNRMC,%s,%C,%f,%C,%f,%C,%f,%f,%2d%2d%2d,%f,%C,%C*",
        &(chTime_buff[0]),
        &(psPack->chStatus),      &(psPack->dwLat),       &(psPack->chNS), &(psPack->dwLon), &(psPack->chEW),
        &(psPack->dwSpeed),       &(psPack->dwDirection),
        &(psPack->sUTC.iDay),     &(psPack->sUTC.iMon),   &(psPack->sUTC.iYear),
        &(psPack->dwDeclination), &(psPack->chDeclin_ew), &(psPack->chMode));

    if(iNsen != 13 && iNsen != 14)
    {
        DPRINT("GNRMC parse error!\r\n");
        return 0;
    }

    if(0 != GPS_ParseTime_NMEA0183(&chTime_buff[0], (MMP_LONG)strlen(&chTime_buff[0]), &(psPack->sUTC)))
    {
        DPRINT("GNRMC time parse error!\r\n");
        return 0;
    }

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : GPS_ParseGPVTG_NMEA0183
//  Description : Parse RMC packet from buffer.
//------------------------------------------------------------------------------
/** @brief
@param[in] pBuff a character pointer of packets buffer.
@param[in] iBuff_sz buffer size.
@param[in] psPack a pointer of packet which will filled by function.
@return 1 (true) - if parsed successfully or 0 (false) - if fail.
*/

MMP_LONG GPS_ParseGPVTG_NMEA0183( MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAVTG *psPack)
{
    memset(psPack, 0, sizeof(NMEAVTG));

    if (dump_nmeaflag & D_VTG) {
        *(pBuff + iBuff_sz) = 0;
        printc("%s", pBuff);
    }

    if(8 != GPSCtrl_Scanf(pBuff,iBuff_sz,
        "$GPVTG,%f,%C,%f,%C,%f,%C,%f,%C*",
        &(psPack->dwDir), &(psPack->chDir_t),
        &(psPack->dwDec), &(psPack->chDec_m),
        &(psPack->dwSpn), &(psPack->chSpn_n),
        &(psPack->dwSpk), &(psPack->chSpk_k)))
    {
        DPRINT("GPVTG parse error!\r\n");
        return 0;
    }

    if( psPack->chDir_t != 'T' ||
        psPack->chDec_m != 'M' ||
        psPack->chSpn_n != 'N' ||
        psPack->chSpk_k != 'K')
    {
        DPRINT("GPVTG parse error (format error)!\r\n");
        return 0;
    }

    return 1;
}

//------------------------------------------------------------------------------
//  Function    : GPS_GGA2info_NMEA0183
//  Description : Fill nmeaINFO structure by GGA packet data.
//------------------------------------------------------------------------------
/** @brief
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/

void GPS_GGA2info_NMEA0183(NMEAGGA *psPack, NMEAINFO *psInfo)
{
    //static MMP_BOOL bUpdateInfo = MMP_TRUE;
    //static MMP_BOOL bResetInfo = MMP_FALSE;

    psInfo->sUTC.iHour  = psPack->sUTC.iHour;
    psInfo->sUTC.iMin   = psPack->sUTC.iMin;
    psInfo->sUTC.iSec   = psPack->sUTC.iSec;
    psInfo->sUTC.iHsec  = psPack->sUTC.iHsec;
    psInfo->iSig        = psPack->iSig;
    psInfo->dwHDOP      = psPack->dwHDOP;
    psInfo->dwElv       = psPack->dwElv;
    #if (GPS_OFFSET_ENABLE ==1 )
    psInfo->dwLat       = Gps_PostitionOffset(psPack->dwLat, 0);//3200.32256;//((psPack->chNS == 'N')?psPack->dwLat:-(psPack->dwLat));
    psInfo->dwLon       = Gps_PostitionOffset(psPack->dwLon, 1);//12014.6679;//((psPack->chEW == 'E')?psPack->dwLon:-(psPack->dwLon));
    #else
    psInfo->dwLat       = ((psPack->chNS == 'N')?psPack->dwLat:-(psPack->dwLat));
    psInfo->dwLon       = ((psPack->chEW == 'E')?psPack->dwLon:-(psPack->dwLon));
    #endif

    #if 0
    //To Fix Ublox-7 GPS module issue
    {
        if(psInfo->dwLat != 0 && psInfo->dwLon != 0)
        {
            if(psPack->iSig == 0 && bStartSimulation)
            {
                psInfo->iSig = 1;
                psPack->iSig = 1;
            }else
            {
                bStartSimulation = AHC_FALSE;
            }
        }
    }
    #endif

    psInfo->iSmask      = GPGGA;

    pGMTBackup->iHour   = psPack->sUTC.iHour;
    pGMTBackup->iMin    = psPack->sUTC.iMin;
    pGMTBackup->iSec    = psPack->sUTC.iSec;
    pGMTBackup->iHsec   = psPack->sUTC.iHsec;
}

//------------------------------------------------------------------------------
//  Function    : GPS_GSA2info_NMEA0183
//  Description : Fill nmeaINFO structure by GSA packet data.
//------------------------------------------------------------------------------
/** @brief
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/

void GPS_GSA2info_NMEA0183(NMEAGSA *psPack, NMEAINFO *psInfo)
{
    MMP_LONG i, j, iNuse = 0;
    MMP_BOOL    bUpdateInfo = MMP_FALSE;
    psInfo->iFix    = psPack->iFix_Type;
    psInfo->dwPDOP  = psPack->dwPDOP;
    psInfo->dwHDOP  = psPack->dwHDOP;
    psInfo->dwVDOP  = psPack->dwVDOP;
    for(i = 0; i < NMEA_MAXSAT; ++i)
    {
        if(bUpdateInfo == MMP_FALSE)
        {
            if((psPack->iSat_Prn[i] <=32) && (psPack->iSat_Prn[i] >=1))
            {
                bUpdateInfo = MMP_TRUE;
            }
        }else if((bUpdateInfo == MMP_FALSE) && (i == (NMEA_MAXSAT -1)))
        {
            bUpdateInfo = MMP_TRUE;
        }
        for(j = 0; j < psInfo->sSatinfo_GPS.iInview; ++j)
        {
            if((psPack->iSat_Prn[i]) && (psPack->iSat_Prn[i] == psInfo->sSatinfo_GPS.sSat[j].iId))
            {
                psInfo->sSatinfo_GPS.sSat[j].iIn_use = 1;
                iNuse++;
            }
        }
    }
    if(bUpdateInfo)
        psInfo->sSatinfo_GPS.iInuse = iNuse;

    iNuse = 0;
    bUpdateInfo = MMP_FALSE;

    for(i = 0; i < NMEA_MAXSAT; ++i)
    {
        if(bUpdateInfo == MMP_FALSE)
        {
            if((psPack->iSat_Prn[i] <=96) && (psPack->iSat_Prn[i] >=65))
            {
                bUpdateInfo = MMP_TRUE;
            }
        }else if((bUpdateInfo == MMP_FALSE) && (i == (NMEA_MAXSAT -1)))
        {
            bUpdateInfo = MMP_TRUE;
        }
        for(j = 0; j < psInfo->sSatinfo_GLONASS.iInview; ++j)
        {
            if((psPack->iSat_Prn[i]) && (psPack->iSat_Prn[i] == psInfo->sSatinfo_GLONASS.sSat[j].iId))
            {
                psInfo->sSatinfo_GLONASS.sSat[j].iIn_use = 1;
                iNuse++;
            }
        }
    }
    if(bUpdateInfo)
    psInfo->sSatinfo_GLONASS.iInuse = iNuse;

    psInfo->ubTotalSatInUse = psInfo->sSatinfo_GPS.iInuse + psInfo->sSatinfo_GLONASS.iInuse;
}

//------------------------------------------------------------------------------
//  Function    : GPS_GPGSV2info_NMEA0183
//  Description : Fill nmeaINFO structure by GSV packet data.
//------------------------------------------------------------------------------
/** @brief
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/

void GPS_GPGSV2info_NMEA0183(NMEAGSV *psPack, NMEAINFO *psInfo)
{
    MMP_LONG iSat, iSi, iNsat;

    if(psPack->iPack_index > psPack->iPack_index ||
        psPack->iPack_index * NMEA_SATINPACK > NMEA_MAXSAT)
        return;

    if(psPack->iPack_index < 1)
        psPack->iPack_index = 1;

    psInfo->sSatinfo_GPS.iInview = psPack->iSat_count;

    iNsat = (psPack->iPack_index - 1) * NMEA_SATINPACK;
    iNsat = (iNsat + NMEA_SATINPACK > psPack->iSat_count)?psPack->iSat_count - iNsat:NMEA_SATINPACK;

    for(iSat = 0; iSat < iNsat; ++iSat)
    {
        iSi = (psPack->iPack_index - 1) * NMEA_SATINPACK + iSat;
        psInfo->sSatinfo_GPS.sSat[iSi].iId      = psPack->sSat_data[iSat].iId;
        psInfo->sSatinfo_GPS.sSat[iSi].iElv     = psPack->sSat_data[iSat].iElv;
        psInfo->sSatinfo_GPS.sSat[iSi].iAzimuth = psPack->sSat_data[iSat].iAzimuth;
        psInfo->sSatinfo_GPS.sSat[iSi].iSig     = psPack->sSat_data[iSat].iSig;
    }
    psInfo->iSmask = GPGSV;
}

//------------------------------------------------------------------------------
//  Function    : GPS_GLGSV2info_NMEA0183
//  Description : Fill nmeaINFO structure by GSV packet data.
//------------------------------------------------------------------------------
/** @brief
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/

void GPS_GLGSV2info_NMEA0183(NMEAGSV *psPack, NMEAINFO *psInfo)
{
    MMP_LONG iSat, iSi, iNsat;

    if(psPack->iPack_index > psPack->iPack_index ||
        psPack->iPack_index * NMEA_SATINPACK > NMEA_MAXSAT)
        return;

    if(psPack->iPack_index < 1)
        psPack->iPack_index = 1;

    psInfo->sSatinfo_GLONASS.iInview = psPack->iSat_count;

    iNsat = (psPack->iPack_index - 1) * NMEA_SATINPACK;
    iNsat = (iNsat + NMEA_SATINPACK > psPack->iSat_count)?psPack->iSat_count - iNsat:NMEA_SATINPACK;

    for(iSat = 0; iSat < iNsat; ++iSat)
    {
        iSi = (psPack->iPack_index - 1) * NMEA_SATINPACK + iSat;
        psInfo->sSatinfo_GLONASS.sSat[iSi].iId      = psPack->sSat_data[iSat].iId;
        psInfo->sSatinfo_GLONASS.sSat[iSi].iElv     = psPack->sSat_data[iSat].iElv;
        psInfo->sSatinfo_GLONASS.sSat[iSi].iAzimuth = psPack->sSat_data[iSat].iAzimuth;
        psInfo->sSatinfo_GLONASS.sSat[iSi].iSig     = psPack->sSat_data[iSat].iSig;
    }
    psInfo->iSmask = GLGSV;
}

//------------------------------------------------------------------------------
//  Function    : GPS_RMC2info_NMEA0183
//  Description : Fill nmeaINFO structure by RMC packet data.
//------------------------------------------------------------------------------
/** @brief
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/

void GPS_RMC2info_NMEA0183(NMEARMC *psPack, NMEAINFO *psInfo)
{
    //static MMP_BOOL bUpdateInfo = MMP_TRUE;
    //static MMP_BOOL bResetInfo = MMP_FALSE;

    #if 0
    if('A' == psPack->chStatus)
    {
        if(NMEA_SIG_BAD == psInfo->iSig)
            psInfo->iSig = NMEA_SIG_MID;
        if(NMEA_FIX_BAD == psInfo->iFix)
            psInfo->iFix = NMEA_FIX_2D;
    }
    else if('V' == psPack->chStatus)
    {
        psInfo->iSig = NMEA_SIG_BAD;
        psInfo->iFix = NMEA_FIX_BAD;
    }
    #endif
    psInfo->sUTC        = psPack->sUTC;

    #if 0
    //To Fix Ublox-7 GPS module issue
    {
        if(psInfo->dwLat != 0 && psInfo->dwLon != 0)
        {
            if('V' == psPack->chStatus && ubCntUBlox7)
            {
                psInfo->iSig = 1;
                if(ubCntUBlox7)
                {
                    ubCntUBlox7--;
                }else
                {
                    bResetInfo = MMP_TRUE;
                }
                bUpdateInfo = MMP_FALSE;
            }else if('A' == psPack->chStatus)
            {
                ubCntUBlox7 = 10;
                bResetInfo  = MMP_FALSE;
                bUpdateInfo = MMP_TRUE;
            }
        }else
        {
            bResetInfo  = MMP_FALSE;
            bUpdateInfo = MMP_TRUE;
        }
    }
    #endif

    if(1)//(bUpdateInfo == MMP_TRUE)
    {
        #if (GPS_OFFSET_ENABLE ==1 )
        psInfo->dwLat       = Gps_PostitionOffset(psPack->dwLat, 0);//3200.32256;//((psPack->chNS == 'N')?psPack->dwLat:-(psPack->dwLat));
        psInfo->dwLon       = Gps_PostitionOffset(psPack->dwLon, 1);//12014.6679;//((psPack->chEW == 'E')?psPack->dwLon:-(psPack->dwLon));
        #else
        psInfo->dwLat       = ((psPack->chNS == 'N')?psPack->dwLat:-(psPack->dwLat));
        psInfo->dwLon       = ((psPack->chEW == 'E')?psPack->dwLon:-(psPack->dwLon));
        #endif
        psInfo->dwSpeed     = psPack->dwSpeed * NMEA_TUD_KNOTS;
        psInfo->dwDirection = psPack->dwDirection;

        psInfo->iSmask = GPRMC;
    }
        pGMTBackup->iYear   = psPack->sUTC.iYear;
        pGMTBackup->iMon    = psPack->sUTC.iMon;
        pGMTBackup->iDay    = psPack->sUTC.iDay;
        pGMTBackup->iHour   = psPack->sUTC.iHour;
        pGMTBackup->iMin    = psPack->sUTC.iMin;
        pGMTBackup->iSec    = psPack->sUTC.iSec;
        pGMTBackup->iHsec   = psPack->sUTC.iHsec;

}

//------------------------------------------------------------------------------
//  Function    : GPS_VTG2info_NMEA0183
//  Description : Fill nmeaINFO structure by VTG packet data.
//------------------------------------------------------------------------------
/** @brief
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/

void GPS_VTG2info_NMEA0183(NMEAVTG *psPack, NMEAINFO *psInfo)
{
    psInfo->dwDirection     = psPack->dwDir;
    psInfo->dwDeclination   = psPack->dwDec;
    psInfo->dwSpeed         = psPack->dwSpk;
    psInfo->iSmask          = GPVTG;
}

//------------------------------------------------------------------------------
//  Function    : GPS_ValidValue_NMEA0183
//  Description : Check if the value from GPS is valid.
//------------------------------------------------------------------------------

MMP_BOOL GPS_IsValidValue_NMEA0183(void)
{
    NMEAINFO  *pInfo = GPS_Information();
    if((pInfo->iSig >= 1)/* || (pInfo->sSatinfo.iInuse >=3) iInuse cannot guaranty GPS fixed or not*/)
        return MMP_TRUE;
    else
        return MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : GPS_Information
//  Description : Get the parsed GPS information.
//------------------------------------------------------------------------------

pNmeaInfo GPS_Information(void)
{
    return pGPSInfo;
}

//------------------------------------------------------------------------------
//  Function    : GPS_GetGMTBackupTime
//  Description : Get the address of GMT time.
//------------------------------------------------------------------------------

pNmeaTime GPS_GetGMTBackupTime(void)
{
    return pGMTBackup;
}

//------------------------------------------------------------------------------
//  Function    : GPS_GPVTG2info_NMEA0183
//  Description : Fill nmeaINFO structure by VTG packet data.
//------------------------------------------------------------------------------
/** @brief
@param[in] psPack a pointer of packet which will filled by function.
@param[in] psInfo a pointer of summary information structure.
*/
void GPS_DubugMessageInfo_NMEA0183(NMEAINFO *pInfo)
{
    printc("---------------------------------------------------\n");
    printc(" Mask                = %d \n", pInfo->iSmask           );
    printc(" Time Information:\n");
    printc(" Year                = %d \n", pInfo->sUTC.iYear       );
    printc(" Mon                 = %d \n", pInfo->sUTC.iMon        );
    printc(" Day                 = %d \n", pInfo->sUTC.iDay        );
    printc(" Hour                = %d \n", pInfo->sUTC.iHour       );
    printc(" Min                 = %d \n", pInfo->sUTC.iMin        );
    printc(" Sec                 = %d \n", pInfo->sUTC.iSec        );
    printc(" Hsec                = %d \n", pInfo->sUTC.iHsec       );
    printc(" \r\n");
    printc(" Position Information:\n");
    printc(" GPS quality         = %d \n", pInfo->iSig             );
    printc(" Operating mode      = %d \n", pInfo->iFix             );
    printc(" Position Dilution   = %f \n", pInfo->dwPDOP           );
    printc(" Horizontal Dilution = %f \n", pInfo->dwHDOP           );
    printc(" Vertical Dilution   = %f \n", pInfo->dwVDOP           );
    printc(" Latitude            = %f \n", pInfo->dwLat            );
    printc(" Longitude           = %f \n", pInfo->dwLon            );
    printc(" Antenna altitude    = %f \n", pInfo->dwElv            );
    printc(" Ground Speed(km/h)  = %f \n", pInfo->dwSpeed          );
    printc(" Track angle(degree) = %f \n", pInfo->dwDirection      );
    printc(" Magnetic variation  = %f \n", pInfo->dwDeclination    );
    printc("\n");
    printc(" Satellites Information:\n");
    printc(" Satellites GPS in use   = %d \n", pInfo->sSatinfo_GPS.iInuse  );
    printc(" Satellites GPS in view  = %d \n", pInfo->sSatinfo_GPS.iInview );
    printc(" Satellites GLONASS in use   = %d \n", pInfo->sSatinfo_GLONASS.iInuse  );
    printc(" Satellites GLONASS in view  = %d \n", pInfo->sSatinfo_GLONASS.iInview );
    printc(" Satellites Total in use  = %d \n", pInfo->ubTotalSatInUse );
    printc("---------------------------------------------------\n");
}

//------------------------------------------------------------------------------
//  Function    : GPS_PaeserMain_NMEA0183
//  Description : Entry of GPS_Parser
//------------------------------------------------------------------------------

void GPS_ParserMain_NMEA0183(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, NMEAINFO *pInfo)
{
    MMP_LONG iRetCrc, iError, iRead = 0, iPackageType = 0, iParsed = 0;
    #if ((GPS_RAW_FILE_ENABLE == 1 || GPS_RAW_FILE_EMER_EN == 1)&&(GPS_CONNECT_ENABLE == 1))
    static MMP_UBYTE ubCount = 0;
    #endif
    static MMP_UBYTE ubCnt   = 0;
    static MMP_UBYTE ubDisCnt = 0;

    if( iBuff_sz == 0 )
    {
        if(ubDisCnt++ >30)
        {
            pInfo->iSig = 0;
            ubDisCnt = 0;
        }
    return;
    }

    ubDisCnt = 0;

    do
    {
        iRead = GPS_FindTail_NMEA0183(pBuff+iParsed, iBuff_sz-iParsed, &iRetCrc);
        //printc("iRead : %d\r\n",iRead);
        //printc("iRetCrc : %d\r\n",iRetCrc);
        if(!iRead)
        {
            //pBuff[iBuff_sz] = '\0';
            //printc("Can't pass %d-%d-%d-%s \n", iBuff_sz,iParsed<iBuff_sz,iRetCrc, pBuff );
            printc("*");
            break;
        }
        else if(iRetCrc > 0)
        {
            iPackageType = GPS_PackType_NMEA0183(pBuff+iParsed+1,iBuff_sz-iParsed-1);

        #if 1 // moved to GPSCtrl_Initial()
            if (iPackageType != GPNON && (bReceiveFirstString == MMP_FALSE))
            {
                GPS_EnableNMEA0183();
                bReceiveFirstString = MMP_TRUE;
            }
        #endif

            switch (iPackageType)
            {
                case GPGGA:
                    #if ((GPS_RAW_FILE_ENABLE == 1 || GPS_RAW_FILE_EMER_EN == 1)&&(GPS_CONNECT_ENABLE == 1))
                        if(AHC_GPS_Module_Attached())
                        {
                            UINT8 bgps_en;

                            if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) {
                                switch (bgps_en) {
                                    case RECODE_GPS_OFF:
                                    case RECODE_GPS_IN_VIDEO:
                                    // NOP
                                    break;

                                    default:
                                    GPSCtrl_GPSRawWriteBuffer(pBuff,iRead);

                                #if GPS_RAW_FILE_EMER_EN
                                    GPSCtrl_GPSRawWriteBuffer_Emer(pBuff,iRead);
                                #endif

                                    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                                    {
                                        GPSCtrl_GPSRawWriteBuffer_Normal(pBuff,iRead);
                                    }
                                    break;
                                    }
                                }
                        }
                        #endif

                    #if (EDOG_ENABLE)
                        if(AHC_GPS_Module_Attached())
                            EDOGIO_GPS_MsgHandle();
                    #endif

                iError = GPS_ParseGPGGA_NMEA0183(pBuff+iParsed,iRead,pGGAPack);
                    if(pGGAPack->iSig != 0)
                    {
                        ubCnt = 20;
                        GPS_GGA2info_NMEA0183(pGGAPack,pGPSInfo);
                    }
                    else
                    {
                        if(ubCnt)
                        {
                            ubCnt--;
                        }else
                        {
                            GPS_ResetContainer_NMEA0183();
                        }
                    }
                break;
                case GPGSA:
                    #if ((GPS_RAW_FILE_ENABLE == 1 || GPS_RAW_FILE_EMER_EN == 1)&&(GPS_CONNECT_ENABLE == 1))
                    if(AHC_GPS_Module_Attached())
                    {
                        UINT8 bgps_en;

                        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) {
                            switch (bgps_en) {
                            case RECODE_GPS_OFF:
                            case RECODE_GPS_IN_VIDEO:
                                break;

                            default:
                                GPSCtrl_GPSRawWriteBuffer(pBuff,iRead);
                            #if GPS_RAW_FILE_EMER_EN
                                GPSCtrl_GPSRawWriteBuffer_Emer(pBuff,iRead);
                            #endif
                                if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                                {
                                    GPSCtrl_GPSRawWriteBuffer_Normal(pBuff,iRead);
                                }
                                break;
                            }
                        }
                    }
                    #endif
                    iError = GPS_ParseGPGSA_NMEA0183(pBuff+iParsed,iRead,pGSAPack);
                    GPS_GSA2info_NMEA0183(pGSAPack,pGPSInfo);
                break;
                case GPGSV:
                    #if ((GPS_RAW_FILE_ENABLE == 1 || GPS_RAW_FILE_EMER_EN == 1)&&(GPS_CONNECT_ENABLE == 1))
                    if(AHC_GPS_Module_Attached())
                    {
                        UINT8 bgps_en;

                        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) {
                            switch (bgps_en) {
                            case RECODE_GPS_OFF:
                            case RECODE_GPS_IN_VIDEO:
                                break;

                            default:
                                GPSCtrl_GPSRawWriteBuffer(pBuff,iRead);
                                #if GPS_RAW_FILE_EMER_EN
                                GPSCtrl_GPSRawWriteBuffer_Emer(pBuff,iRead);
                                #endif
                                if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                                {
                                    GPSCtrl_GPSRawWriteBuffer_Normal(pBuff,iRead);
                                }
                                break;
                            }
                        }
                    }
                    #endif
                    iError = GPS_ParseGPGSV_NMEA0183(pBuff+iParsed,iRead,pGPGSVPack);
                    GPS_GPGSV2info_NMEA0183(pGPGSVPack,pGPSInfo);
                break;
                case GPRMC:
                    #if(GPS_RAW_FILE_EMER_EN == 1)
                    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_MOVE_FILE)
                    {
                        if(GPSCtrl_GetGPSRawStart_Emer() && !GPSCtrl_GetGPSRawWriteFirst())
                        {
                            GPSCtrl_GPSRawWriteFirst_Emer();
                            GPSCtrl_SetGPSRawWriteFirst(AHC_TRUE);
                            if(ubGPSRAWBufferIndex == 0)
                            {
                                ulGPSRawEmerStartAddr = ulGPSRawBufferLen_0;
                            }
                            else
                            {
                                ulGPSRawEmerStartAddr = ulGPSRawBufferLen_1;
                            }
                        }
                    }
                    #endif

                    #if (GPS_RAW_FILE_EMER_EN == 1)
                    GPSCtrl_IncGPSRawIndex_Emer();
                #endif

            #if (GPS_RAW_FILE_ENABLE == 1)
                        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE && AHC_VIDEO_IsEmergRecStarted())
                        {
                            GPSCtrl_IncGPSRawIndex_Normal();
                        }
            #endif

                    #if ((GPS_CONFIG_NMEA_FILE == 0) || (GPS_CONFIG_NMEA_FILE == 1))//(GPS_CONFIG_NMEA_FILE == 0)
                    #if(GSENSOR_RAW_FILE_ENABLE == 1)
                        AHC_Gsensor_RawWrite(MMP_FALSE); //Andy Liu TBD
                    #endif
                    #endif

                    #if ((GPS_RAW_FILE_ENABLE == 1 || GPS_RAW_FILE_EMER_EN == 1)&&(GPS_CONNECT_ENABLE == 1))
                    if(AHC_GPS_Module_Attached())
                    {
                        UINT8 bgps_en;

                        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) {
                            switch (bgps_en) {
                            case RECODE_GPS_OFF:
                            case RECODE_GPS_IN_VIDEO:
                                break;

                            default:
                                GPSCtrl_GPSRawWriteBuffer(pBuff,iRead);
                                //if(!GPSCtrl_GetGPSRawWriteFirst())
                                //{
                                    #if GPS_RAW_FILE_EMER_EN
                                    GPSCtrl_GPSRawWriteBuffer_Emer(pBuff,iRead);
                                    #endif
                                    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                                    {
                                        GPSCtrl_GPSRawWriteBuffer_Normal(pBuff,iRead);
                                    }
                                //}
                                if(ubCount == 2)
                                {
                                    if(ubGPSRAWBufferIndex == 0)
                                    {

                                        #if(GPS_RAW_FILE_ENABLE == 1)
                                        GPSCtrl_GPSRawWrite(ubGPSRawBuffer_0,ulGPSRawBufferLen_0);
                                        #endif
                                        #if(GPS_RAW_FILE_EMER_EN == 1)
                                        if(GPSCtrl_GetGPSRawStart_Emer())
                                        {
                                            if(ulGPSRawEmerStartAddr != 0)
                                            GPSCtrl_GPSRawWriteFlushBuf_Emer();
                                            else
                                            GPSCtrl_GPSRawWrite_Emer(ubGPSRawBuffer_0,ulGPSRawBufferLen_0);
                                        }
                                        #endif
                                        MEMSET(ubGPSRawBuffer_0, 0, GPS_RAW_BUFFER_SIZE);
                                        ulGPSRawBufferLen_0 = 0;
                                        #if(GPS_RAW_FILE_EMER_EN == 1)
                                        if(GPSCtrl_GetGPSRawStart_Emer())
                                        {
                                            ulGPSRawEmerStartAddr = 0;
                                        }
                                        #endif
                                    }else
                                    {

                                        #if(GPS_RAW_FILE_ENABLE == 1)
                                        GPSCtrl_GPSRawWrite(ubGPSRawBuffer_1,ulGPSRawBufferLen_1);
                                        #endif
                                        #if(GPS_RAW_FILE_EMER_EN == 1)
                                        if(GPSCtrl_GetGPSRawStart_Emer())
                                        {
                                            if(ulGPSRawEmerStartAddr != 0)
                                            GPSCtrl_GPSRawWriteFlushBuf_Emer();
                                            else
                                            GPSCtrl_GPSRawWrite_Emer(ubGPSRawBuffer_1,ulGPSRawBufferLen_1);
                                        }
                                        #endif
                                        MEMSET(ubGPSRawBuffer_1, 0, GPS_RAW_BUFFER_SIZE);
                                        ulGPSRawBufferLen_1 = 0;
                                        #if(GPS_RAW_FILE_EMER_EN == 1)
                                        if(GPSCtrl_GetGPSRawStart_Emer())
                                        {
                                            ulGPSRawEmerStartAddr = 0;
                                        }
                                        #endif
                                    }
                                    ubCount = 0;
                                }else
                                {
                                    ubCount++;
                                }
                                break;
                            }
                        }
                }
                #endif

                    iError = GPS_ParseGPRMC_NMEA0183(pBuff+iParsed,iRead,pRMCPack);
                    if('A' == pRMCPack->chStatus)
                    {
                        ubCnt = 20;
                        GPS_RMC2info_NMEA0183(pRMCPack,pGPSInfo);
                    }
                    else
                    {
                        if(ubCnt)
                        {
                            ubCnt--;
                        }else
                        {
                            GPS_ResetContainer_NMEA0183();
                        }
                    }
                break;
                case GPVTG:
                    #if ((GPS_RAW_FILE_ENABLE == 1 || GPS_RAW_FILE_EMER_EN == 1)&&(GPS_CONNECT_ENABLE == 1))
                    if(AHC_GPS_Module_Attached())
                    {
                        UINT8 bgps_en;

                        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) {
                            switch (bgps_en) {
                            case RECODE_GPS_OFF:
                            case RECODE_GPS_IN_VIDEO:
                                break;

                            default:
                                GPSCtrl_GPSRawWriteBuffer(pBuff,iRead);
                                #if GPS_RAW_FILE_EMER_EN
                                GPSCtrl_GPSRawWriteBuffer_Emer(pBuff,iRead);
                                #endif
                                if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                                {
                                    GPSCtrl_GPSRawWriteBuffer_Normal(pBuff,iRead);
                                }
                                break;
                            }
                        }
                    }
                    #endif
                    iError = GPS_ParseGPVTG_NMEA0183(pBuff+iParsed,iRead,pVTGPack);
                    GPS_VTG2info_NMEA0183(pVTGPack,pGPSInfo);
                break;
                case GNGSA:
                    #if ((GPS_RAW_FILE_ENABLE == 1 || GPS_RAW_FILE_EMER_EN == 1)&&(GPS_CONNECT_ENABLE == 1))
                    if(AHC_GPS_Module_Attached())
                    {
                        UINT8 bgps_en;

                        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) {
                            switch (bgps_en) {
                            case RECODE_GPS_OFF:
                            case RECODE_GPS_IN_VIDEO:
                                break;

                            default:
                                GPSCtrl_GPSRawWriteBuffer(pBuff,iRead);
                                #if GPS_RAW_FILE_EMER_EN
                                GPSCtrl_GPSRawWriteBuffer_Emer(pBuff,iRead);
                                #endif
                                if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                                {
                                    GPSCtrl_GPSRawWriteBuffer_Normal(pBuff,iRead);
                                }
                                break;
                            }
                        }
                    }
                    #endif
                    iError = GPS_ParseGNGSA_NMEA0183(pBuff+iParsed,iRead,pGSAPack);
                    GPS_GSA2info_NMEA0183(pGSAPack,pGPSInfo);
                break;
                case GNRMC:
                    #if ((GPS_RAW_FILE_ENABLE == 1 || GPS_RAW_FILE_EMER_EN == 1)&&(GPS_CONNECT_ENABLE == 1))
                    if(AHC_GPS_Module_Attached())
                    {
                        UINT8 bgps_en;

                        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) {
                            switch (bgps_en) {
                            case RECODE_GPS_OFF:
                            case RECODE_GPS_IN_VIDEO:
                                break;

                            default:
                                GPSCtrl_GPSRawWriteBuffer(pBuff,iRead);
                                #if GPS_RAW_FILE_EMER_EN
                                GPSCtrl_GPSRawWriteBuffer_Emer(pBuff,iRead);
                                #endif
                                if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                                {
                                    GPSCtrl_GPSRawWriteBuffer_Normal(pBuff,iRead);
                                }
                                break;
                            }
                        }
                    }
                    #endif
                    iError = GPS_ParseGNRMC_NMEA0183(pBuff+iParsed,iRead,pRMCPack);
                    GPS_RMC2info_NMEA0183(pRMCPack,pGPSInfo);
                break;
                case GLGSV:
                    #if ((GPS_RAW_FILE_ENABLE == 1 || GPS_RAW_FILE_EMER_EN == 1)&&(GPS_CONNECT_ENABLE == 1))
                    if(AHC_GPS_Module_Attached())
                    {
                        UINT8 bgps_en;

                        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bgps_en) == AHC_TRUE) {
                            switch (bgps_en) {
                            case RECODE_GPS_OFF:
                            case RECODE_GPS_IN_VIDEO:
                                break;

                            default:
                                GPSCtrl_GPSRawWriteBuffer(pBuff,iRead);
                                #if GPS_RAW_FILE_EMER_EN
                                GPSCtrl_GPSRawWriteBuffer_Emer(pBuff,iRead);
                                #endif
                                if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                                {
                                    GPSCtrl_GPSRawWriteBuffer_Normal(pBuff,iRead);
                                }
                                break;
                            }
                        }
                    }
                    #endif
                    iError = GPS_ParseGLGSV_NMEA0183(pBuff+iParsed,iRead,pGLGSVPack);
                    GPS_GLGSV2info_NMEA0183(pGLGSVPack,pGPSInfo);
                break;
            }
        }

        iParsed += iRead;

    }while(iParsed<iBuff_sz);
}

void GPS_SetCommand_NMEA0183(NMEACOMMAND_TYPE type)
{
    char        chCommand[50];
    MMP_UBYTE   ublength = 0;

    MEMSET(chCommand, 0, 50);
    switch (type)
    {
        case NMEACMD_CFG_SET_EXPERT:
            MEMCPY(chCommand, ubSetExpert, sizeof(ubSetExpert));
            ublength = sizeof(ubSetExpert);
            break;

        case NMEACMD_CFG_SL_CFG:
            MEMCPY(chCommand, ubSLconfig, sizeof(ubSLconfig));
            ublength = sizeof(ubSLconfig);
            break;
    }
    GPS_SetCommand(chCommand, ublength);
}

//------------------------------------------------------------------------------
//  Function    : GPS_SetCommand
//  Description :
//------------------------------------------------------------------------------
MMP_ERR GPS_SetCommand(void *CommAry, MMP_ULONG ulCmdSize)
{
    char        chCommand[128];
    MMP_ERR     sRet = MMP_ERR_NONE;

    if (ulCmdSize >= 128) {
        RTNA_DBG_Str(0, FG_RED("GPS set command error\r\n"));
        return MMP_SYSTEM_ERR_PARAMETER;
    }

    MEMSET(chCommand, 0, ulCmdSize);
    MEMCPY(chCommand, CommAry, ulCmdSize);

    uart_Write(FUART, chCommand, ulCmdSize);
    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(0,sRet);}

    return sRet;
}

#if (GPS_CONFIG_NMEA_FILE)
//------------------------------------------------------------------------------
//  Function    : GPS_GetGPSStringFromFile
//  Description : Read GPS string from file
//------------------------------------------------------------------------------
MMP_BOOL GPS_GetGPSStringFromFile(MMP_BYTE *bGPSString, MMP_ULONG *ulGPSStringLength)
{
    MMP_ERR     err;
    char        ubBuffer;
    MMP_ULONG   read_count;
    MMP_ULONG   read_file_cnt = 0;
    MMP_UBYTE   i;
    MMP_BOOL    bSkipString;
    char        TempStr[9];
    static MMP_LONG64  l64CurrFilePosition = 0;

    static void* ppUserPtr = 0;
    static u64 MiuAddr = 0;
    static u64 lpPhysAddr = 0;

    MEMSET(bGPSString, 0, 0xFF);
    MEMSET(TempStr, 0, sizeof(TempStr));

    if (!ulGPSFileID) {
        err = MMPF_FS_FOpen(GPS_CONFIG_NMEA_FILE_NAME, "rb", &ulGPSFileID);
        if (err != MMP_ERR_NONE) {
            UartSendTrace("File open error\r\n");
            return MMP_FALSE;
        }

        err = MMPF_FS_GetFileSize(ulGPSFileID, &ul64GPSFileSize);
        if (err != MMP_ERR_NONE) {
            UartSendTrace("File GetFileSize error\r\n");
            MMPF_FS_FClose(ulGPSFileID);
            return MMP_FALSE;
        }

        CamOsDirectMemAlloc("GPS_Info", ul64GPSFileSize, &ppUserPtr, &MiuAddr, &lpPhysAddr);

        while (read_file_cnt < ul64GPSFileSize) {
            if (ul64GPSFileSize - read_file_cnt > 4096)
                err = MMPF_FS_FRead(ulGPSFileID, (UINT8*)(lpPhysAddr + read_file_cnt), 4096, &read_count);
            else
                err = MMPF_FS_FRead(ulGPSFileID, (UINT8*)(lpPhysAddr + read_file_cnt), ul64GPSFileSize - read_file_cnt, &read_count);

            if (err != MMP_ERR_NONE) {
                if (err == MMP_FS_ERR_EOF)
                    m_bEOF = MMP_TRUE;

                MMPF_FS_FClose(ulGPSFileID);
                CamOsDirectMemRelease(ppUserPtr, ul64GPSFileSize);
                ulGPSFileID = NULL;
                MMPF_OS_SleepMs(100);
                return MMP_FALSE;
            }
            read_file_cnt += read_count;
        }

        l64CurrFilePosition = 0;
        UartSendTrace("Read GPS_Info OK\n");
    }

    if (ulGPSFileID) {
        for (i = 0; i < 256; i++) {
            if (l64CurrFilePosition + i >= ul64GPSFileSize) {
                m_bEOF = MMP_TRUE;
                l64CurrFilePosition = 0;
                MMPF_OS_SleepMs(100);
                return MMP_FALSE;
            }

            ubBuffer = *(UINT8*)(lpPhysAddr + l64CurrFilePosition + i);

            if (ubBuffer == '$') {
                if (bStartCount == MMP_FALSE) {
                    bStartCount = MMP_TRUE;
                    bGPSStartPosition = i;
                }
            }

            if (bStartCount == MMP_TRUE) {
                if (ubBuffer == '\n') {
                    bGPSStringCounter = i;
                    break;
                }
            }
        }

        *ulGPSStringLength = (bGPSStringCounter - bGPSStartPosition + 1);

        l64CurrFilePosition = l64CurrFilePosition + bGPSStartPosition;

        MEMCPY(bGPSString, (UINT8*)(lpPhysAddr + l64CurrFilePosition), (bGPSStringCounter - bGPSStartPosition + 1));
        l64CurrFilePosition += (bGPSStringCounter - bGPSStartPosition + 1);

        bGPSStringCounter = 0;
        bGPSStartPosition = 0;
        #if 1 // 1: skip printing GPS String from file
        // NOP
        #else
        UartSendTrace("%s",(bGPSString));
        #endif

        MEMCPY(TempStr, bGPSString, 9);

        if (STRCMP(TempStr,"$GSENSORD"))
            bSkipString = 0;
        else
            bSkipString = 1;

        return bSkipString;
    }
}

MMP_BOOL GPS_IsEOF(void)
{
    return m_bEOF;
}

void GPS_ResetEOF(void)
{
    m_bEOF = MMP_FALSE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPF_3RDParty_GPS_Register
//  Description : This function should be called before using sensor function.
//------------------------------------------------------------------------------
void MMPF_3RDParty_GPS_Register(struct _3RD_PARTY_GPS *pdev_obj)
{
    gpGPS_obj = pdev_obj;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_3RDParty_GPS_Initiate
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPF_3RDParty_GPS_Initiate(void)
{
    if(gpGPS_obj){
        return gpGPS_obj->GPS_Initiate_ANA(gpGPS_obj); //GPS_Initiate_ANA_ByModule
    }
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_3RDParty_GPS_SetHotStart
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPF_3RDParty_GPS_SetHotStart(void)
{
    if(gpGPS_obj){
        return gpGPS_obj->GPS_SetHotStart(gpGPS_obj); //GPS_SetHotStart_ByModule
    }
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_3RDParty_GPS_SetWarmStart_1
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPF_3RDParty_GPS_SetWarmStart_1(void)
{
    if(gpGPS_obj){
        return gpGPS_obj->GPS_SetWarmStart_1(gpGPS_obj); //GPS_SetWarmStart_1_ByModule
    }
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_3RDParty_GPS_SetWarmStart_2
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPF_3RDParty_GPS_SetWarmStart_2(void)
{
    if(gpGPS_obj){
        return gpGPS_obj->GPS_SetWarmStart_2(gpGPS_obj); //GPS_SetWarmStart_2_ByModule
    }
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_3RDParty_GPS_SetColdStart
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPF_3RDParty_GPS_SetColdStart(void)
{
    if(gpGPS_obj){
        return gpGPS_obj->GPS_SetColdStart(gpGPS_obj); //GPS_SetColdStart_ByModule
    }
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_3RDParty_GPS_SetBR57600
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPF_3RDParty_GPS_SetBR57600(void)
{
    if(gpGPS_obj){
        return gpGPS_obj->GPS_SetBR57600(gpGPS_obj); //GPS_SetBR57600_ByModule
    }
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_3RDParty_GPS_DisableNMEASentence
//  Description :   Disable output of the NMEA sentences.
//------------------------------------------------------------------------------
MMP_ERR MMPF_3RDParty_GPS_DisableNMEASentence(void)
{
    if(gpGPS_obj){
        return gpGPS_obj->GPS_DisableNMEASentence(gpGPS_obj);
    }
    return MMP_SYSTEM_ERR_HW;
}

//------------------------------------------------------------------------------
//  Function    : MMPF_3RDParty_GPS_DisableNMEASentence
//  Description :   Enable output of the NMEA sentences.
//------------------------------------------------------------------------------
MMP_ERR MMPF_3RDParty_GPS_EnableNMEASentence(void)
{
    if(gpGPS_obj){
        return gpGPS_obj->GPS_EnableNMEASentence(gpGPS_obj);
    }
    return MMP_SYSTEM_ERR_HW;
}


#endif // (GPS_CONNECT_ENABLE && (GPS_MODULE == GPS_MODULE_NMEA0183))
