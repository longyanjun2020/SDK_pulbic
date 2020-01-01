//==============================================================================
//
//  File        : gps.c
//  Description : Firmware Sensor Control File
//  Author      : Philip Lin
//  Revision    : 1.0
//
//=============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "includes_fw.h"
#include "Customer_config.h"

#include "Customer_config.h"
#include "gps_ctl.h"
#include "ait_utility.h"
#if defined(__GNUC__)
#include "vm_types.ht"
#endif

#if (GPS_CONNECT_ENABLE && (GPS_MODULE == GPS_MODULE_NMEA0183))
#include "GPS_nmea0183_ANA.h"

//==============================================================================
//
//                              GLOBAL VARIABLE
//
//==============================================================================

// new added commands for u-blox 7
//******************************************************************************
//                              [GPS ANA Command]
//******************************************************************************
/*
 * 1-1. Enable ANA function (AssistNow Autonomous), 3D fix
 * B5 62 06 23 28 00 00 00 4C 66 00 00 00 00 00 00 03 10 00 00 01 00 00 00 00 00 00 00 00 00 00 00 01 01 00 00 00 00 00 00 00 00 00 00 00 00 19 DE
 */
static MMP_UBYTE 	ubANA3DFix[48] 			= {0xB5, 0x62, 0x06, 0x23, 0x28, 0x00, 0x00, 0x00, 0x4C, 0x66, 
											   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x10, 0x00, 0x00, 
											   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
											   0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
											   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0xDE}; // 48

/*
 * 1-2. Automotive mode, PDOP Mask = 35, Ele = 3, Static hold 1.0m/s
 * B5 62 06 24 24 00 FF FF 04 03 00 00 00 00 10 27 00 00 03 00 5E 01 FA 00 64 00 2C 01 64 3C 00 00 00 00 00 00 00 00 00 00 00 00 17 99
 */
static MMP_UBYTE 	ubAutomotiveMode[44] 	= {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x04, 0x03, 
											   0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x03, 0x00, 
											   0x5E, 0x01, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x64, 0x3C, 
											   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
											   0x00, 0x00, 0x17, 0x99}; // 44

/*
 * 1-3. NMEA configuration: Filters(12346)&1-Extended(3-digit), Max SVs(16), Compatibility mode(V), GP
 * B5 62 06 17 0C 00 2F 23 10 03 00 00 00 00 01 01 00 00 90 D8
 */
static MMP_UBYTE 	ubNMEAconfig[20] 		= {0xB5, 0x62, 0x06, 0x17, 0x0C, 0x00, 0x2F, 0x23, 0x10, 0x03, 
											   0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x90, 0xD8}; // 20

/*
 * 1-4. Enable PRN128
 * B5 62 06 16 08 00 01 01 03 00 D1 A3 06 00 A3 E4
 */
static MMP_UBYTE 	ubPRN128[16] 			= {0xB5, 0x62, 0x06, 0x16, 0x08, 0x00, 0x01, 0x01, 0x03, 0x00, 
											   0xD1, 0xA3, 0x06, 0x00, 0xA3, 0xE4}; // 16

/*
 * 1-5. del GLL (to save space that baud rate = 9600) (UART 1)
 * B5 62 06 01 08 00 F0 01 01 00 01 01 01 01 05 3A
 */
static MMP_UBYTE 	ubGLLdel[16] 			= {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x01, 0x00, 
											   0x01, 0x01, 0x01, 0x01, 0x05, 0x3A}; // 16

/*
 * 1-6. del VTG (to save space that baud rate = 9600) (UART 1)
 * B5 62 06 01 08 00 F0 05 01 00 01 01 01 01 09 56
 */
static MMP_UBYTE 	ubVTGdel[16] 			= {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x01, 0x00, 
											   0x01, 0x01, 0x01, 0x01, 0x09, 0x56}; // 16

/*
 * 1-7. Save current setting Command: 
 * B5 62 06 09 0D 00 00 00 00 00 FF FF 00 00 00 00 00 00 03 1D AB
 */
static MMP_UBYTE 	ubSettingSave[21] 		= {0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 
											   0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1D, 
											   0xAB}; // 21
//******************************************************************************											   
//                              [GPS Common Command]
//******************************************************************************

static MMP_UBYTE 	ubHotStart[12] 			= {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 
										   	   0x10, 0x68}; // 12

static MMP_UBYTE 	ubWarmStart_1[12] 		= {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 
										   	   0x11, 0x6C}; // 12

static MMP_UBYTE 	ubWarmStart_2[12] 		= {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x01, 0x80, 0x02, 0x00, 
										   	   0x91, 0xEC}; // 12

static MMP_UBYTE 	ubColdStart[12] 		= {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0xFF, 0x87, 0x02, 0x00, 
										   	   0x96, 0xF9}; // 12

static MMP_UBYTE 	ubBR57600[28] 			= {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 
											   0xD0, 0x08, 0x00, 0x00, 0x00, 0xE1, 0x00, 0x00, 0x07, 0x00, 
										   	   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDE, 0xC9}; // 28
//******************************************************************************
//                              [GPS User Command]
//******************************************************************************
/*
 * Switch to Glonass Command:
 * B5 62 06 3E 24 00 00 00 16 04 00 04 FF 00 00 00 00 01 01 01 03 00 00 00 00 01 05 00 03 00 00 00 00 01 06 08 FF 00 01 00 00 01 A4 0D
 */
/*
static MMP_UBYTE 	ubGLONASSswitch[44] 	= {0xB5, 0x62, 0x06, 0x3E, 0x24, 0x00, 0x00, 0x00, 0x16, 0x04, 
											   0x00, 0x04, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 
											   0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x05, 0x00, 0x03, 0x00, 
											   0x00, 0x00, 0x00, 0x01, 0x06, 0x08, 0xFF, 0x00, 0x01, 0x00, 
											   0x00, 0x01, 0xA4, 0x0D}; // 44
*/
/*
 * Switch to GPS Command:
 * B5 62 06 3E 24 00 00 00 16 04 00 04 FF 00 01 00 00 01 01 01 03 00 01 00 00 01 05 00 03 00 01 00 00 01 06 08 FF 00 00 00 00 01 A6 45
 */
 /*
static MMP_UBYTE 	ubGPSswitch[44] 		= {0xB5, 0x62, 0x06, 0x3E, 0x24, 0x00, 0x00, 0x00, 0x16, 0x04, 
											   0x00, 0x04, 0xFF, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 
											   0x03, 0x00, 0x01, 0x00, 0x00, 0x01, 0x05, 0x00, 0x03, 0x00, 
											   0x01, 0x00, 0x00, 0x01, 0x06, 0x08, 0xFF, 0x00, 0x00, 0x00, 
											   0x00, 0x01, 0xA6, 0x45}; // 44
*/									   
//******************************************************************************
// End of new added commands for u-blox 7											   

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
static THIRD_PARTY_GPS  GPS_Module_Obj = 
{
    GPS_SetCommand_ByModule,          //00
    GPS_Initiate_ANA_ByModule,        //01
    GPS_SetHotStart_ByModule,         //02
    GPS_SetWarmStart_1_ByModule,      //03
    GPS_SetWarmStart_2_ByModule,      //04
    GPS_SetColdStart_ByModule,        //05
    GPS_SetBR57600_ByModule,           //06
    GPS_DisableNMEASentence_ByModule,
    GPS_EnableNMEASentence_ByModule
};

//------------------------------------------------------------------------------
//  Function    : GPS_SetCommand_ByModule
//  Description :
//------------------------------------------------------------------------------

MMP_ERR GPS_SetCommand_ByModule(struct _3RD_PARTY_GPS *pthis, void *pCommAry, MMP_ULONG ulCmdSize)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    sRet = GPS_SetCommand(pCommAry, ulCmdSize);
    return sRet;
}


//------------------------------------------------------------------------------
//  Function    : GPS_Initiate_ANA_ByModule
//  Description :
//------------------------------------------------------------------------------

MMP_ERR GPS_Initiate_ANA_ByModule(struct _3RD_PARTY_GPS *pthis)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    
    printc(FG_YELLOW("Run GPS_Initiate_ANA\r\n")); 
    sRet = pthis->GPS_SetCommand(pthis, (void *)&ubANA3DFix, sizeof(ubANA3DFix)); //GPS_SetCommand_ByModule
    MMPF_OS_Sleep(20);
    
    sRet |= pthis->GPS_SetCommand(pthis, (void *)&ubAutomotiveMode, sizeof(ubAutomotiveMode));    
    MMPF_OS_Sleep(20);

    sRet |= pthis->GPS_SetCommand(pthis, (void *)&ubNMEAconfig, sizeof(ubNMEAconfig));    
    MMPF_OS_Sleep(20);
    
    sRet |= pthis->GPS_SetCommand(pthis, (void *)&ubPRN128, sizeof(ubPRN128));    
    MMPF_OS_Sleep(20);
    
    sRet |= pthis->GPS_SetCommand(pthis, (void *)&ubGLLdel, sizeof(ubGLLdel));    
    MMPF_OS_Sleep(20);
    
    sRet |= pthis->GPS_SetCommand(pthis, (void *)&ubVTGdel, sizeof(ubVTGdel));    
    MMPF_OS_Sleep(20);
    
    sRet |= pthis->GPS_SetCommand(pthis, (void *)&ubSettingSave, sizeof(ubSettingSave));
    MMPF_OS_Sleep(20);

    return sRet;
}


//------------------------------------------------------------------------------
//  Function    : GPS_SetHotStart_ByModule
//  Description :
//------------------------------------------------------------------------------

MMP_ERR GPS_SetHotStart_ByModule(struct _3RD_PARTY_GPS *pthis)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    
    printc(FG_YELLOW("Run GPS_SetHotStart\r\n")); 
    sRet = pthis->GPS_SetCommand(pthis, (void *)&ubHotStart, sizeof(ubHotStart)); //GPS_SetCommand_ByModule

    return sRet;
}

//------------------------------------------------------------------------------
//  Function    : GPS_SetWarmStart_1_ByModule
//  Description :
//------------------------------------------------------------------------------

MMP_ERR GPS_SetWarmStart_1_ByModule(struct _3RD_PARTY_GPS *pthis)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    
    printc(FG_YELLOW("Run GPS_SetWarmStart_1\r\n")); 
    sRet = pthis->GPS_SetCommand(pthis, (void *)&ubWarmStart_1, sizeof(ubWarmStart_1)); //GPS_SetCommand_ByModule

    return sRet;
}

//------------------------------------------------------------------------------
//  Function    : GPS_SetWarmStart_2_ByModule
//  Description :
//------------------------------------------------------------------------------

MMP_ERR GPS_SetWarmStart_2_ByModule(struct _3RD_PARTY_GPS *pthis)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    
    printc(FG_YELLOW("Run GPS_SetWarmStart_2\r\n")); 
    sRet = pthis->GPS_SetCommand(pthis, (void *)&ubWarmStart_2, sizeof(ubWarmStart_2)); //GPS_SetCommand_ByModule

    return sRet;
}

//------------------------------------------------------------------------------
//  Function    : GPS_SetColdStart_ByModule
//  Description :
//------------------------------------------------------------------------------

MMP_ERR GPS_SetColdStart_ByModule(struct _3RD_PARTY_GPS *pthis)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    
    printc(FG_YELLOW("Run GPS_SetColdStart\r\n")); 
    sRet = pthis->GPS_SetCommand(pthis, (void *)&ubColdStart, sizeof(ubColdStart)); //GPS_SetCommand_ByModule

    return sRet;
}


//------------------------------------------------------------------------------
//  Function    : GPS_SetBR57600_ByModule
//  Description :
//------------------------------------------------------------------------------

MMP_ERR GPS_SetBR57600_ByModule(struct _3RD_PARTY_GPS *pthis)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    
    printc(FG_YELLOW("Run GPS_SetBR57600\r\n")); 
    sRet = pthis->GPS_SetCommand(pthis, (void *)&ubBR57600, sizeof(ubBR57600)); //GPS_SetCommand_ByModule

    return sRet;
}

// Disable NMEA sentence output.
char szDisableDTM[] = "$PUBX,40,DTM,0,0,0,0,0,0,46";
char szDisableGBS[] = "$PUBX,40,GBS,0,0,0,0,0,0,4D";
char szDisableGGA[] = "$PUBX,40,GGA,0,0,0,0,0,0,5A";
char szDisableGLL[] = "$PUBX,40,GLL,0,0,0,0,0,0,5C";
char szDisableGLQ[] = "$PUBX,40,GLQ,0,0,0,0,0,0,41";
char szDisableGNS[] = "$PUBX,40,GNS,0,0,0,0,0,0,41";
char szDisableGPQ[] = "$PUBX,40,GPQ,0,0,0,0,0,0,5D";
char szDisableGRS[] = "$PUBX,40,GRS,0,0,0,0,0,0,5D";
char szDisableGSA[] = "$PUBX,40,GSA,0,0,0,0,0,0,4E";
char szDisableGST[] = "$PUBX,40,GST,0,0,0,0,0,0,5B";
char szDisableGSV[] = "$PUBX,40,GSV,0,0,0,0,0,0,59";
char szDisableRMC[] = "$PUBX,40,RMC,0,0,0,0,0,0,47";
char szDisableTXT[] = "$PUBX,40,TXT,0,0,0,0,0,0,43";
char szDisableVTG[] = "$PUBX,40,VTG,0,0,0,0,0,0,5E";
char szDisableZDA[] = "$PUBX,40,ZDA,0,0,0,0,0,0,44";
// Enable NMEA sentence output.
char szEnableDTM[] = "$PUBX,40,DTM,0,1,0,0,0,0,47";
char szEnableGBS[] = "$PUBX,40,GBS,0,1,0,0,0,0,4C";
char szEnableGGA[] = "$PUBX,40,GGA,0,1,0,0,0,0,5B";
char szEnableGLL[] = "$PUBX,40,GLL,0,1,0,0,0,0,5D";
char szEnableGLQ[] = "$PUBX,40,GLQ,0,1,0,0,0,0,40";
char szEnableGNS[] = "$PUBX,40,GNS,0,1,0,0,0,0,40";
char szEnableGPQ[] = "$PUBX,40,GPQ,0,1,0,0,0,0,5C";
char szEnableGRS[] = "$PUBX,40,GRS,0,1,0,0,0,0,5C";
char szEnableGSA[] = "$PUBX,40,GSA,0,1,0,0,0,0,4F";
char szEnableGST[] = "$PUBX,40,GST,0,1,0,0,0,0,5A";
char szEnableGSV[] = "$PUBX,40,GSV,0,1,0,0,0,0,58";
char szEnableRMC[] = "$PUBX,40,RMC,0,1,0,0,0,0,46";
char szEnableTXT[] = "$PUBX,40,TXT,0,1,0,0,0,0,42";
char szEnableVTG[] = "$PUBX,40,VTG,0,1,0,0,0,0,5F";
char szEnableZDA[] = "$PUBX,40,ZDA,0,1,0,0,0,0,45";
// Checksum Example: "$PUBX,40,ZDA,0,1,0,0,0,0,45";
// Checksum = XOR'ing all characters between the $ and the *

MMP_ERR GPS_DisableNMEASentence_ByModule(struct _3RD_PARTY_GPS *pthis)
{
	MMP_ERR sRet = MMP_ERR_NONE;
    
	printc(FG_YELLOW("Run GPS_DisableNMEASentence_ByModule\r\n"));
	
   	sRet |= pthis->GPS_SetCommand(pthis, szDisableDTM, sizeof(szDisableDTM)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGBS, sizeof(szDisableGBS)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGGA, sizeof(szDisableGGA)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGLL, sizeof(szDisableGLL)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGLQ, sizeof(szDisableGLQ)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGNS, sizeof(szDisableGNS)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGPQ, sizeof(szDisableGPQ)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGRS, sizeof(szDisableGRS)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGSA, sizeof(szDisableGSA)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGST, sizeof(szDisableGST)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableGSV, sizeof(szDisableGSV)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableRMC, sizeof(szDisableRMC)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableTXT, sizeof(szDisableTXT)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableVTG, sizeof(szDisableVTG)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szDisableZDA, sizeof(szDisableZDA)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);

    return sRet;
}

MMP_ERR GPS_EnableNMEASentence_ByModule(struct _3RD_PARTY_GPS *pthis)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    
    printc(FG_YELLOW("Run GPS_EnableNMEASentence_ByModule\r\n"));
	
   	sRet |= pthis->GPS_SetCommand(pthis, szEnableDTM, sizeof(szEnableDTM)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGBS, sizeof(szEnableGBS)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGGA, sizeof(szEnableGGA)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGLL, sizeof(szEnableGLL)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGLQ, sizeof(szEnableGLQ)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGNS, sizeof(szEnableGNS)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGPQ, sizeof(szEnableGPQ)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGRS, sizeof(szEnableGRS)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGSA, sizeof(szEnableGSA)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGST, sizeof(szEnableGST)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableGSV, sizeof(szEnableGSV)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableRMC, sizeof(szEnableRMC)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableTXT, sizeof(szEnableTXT)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableVTG, sizeof(szEnableVTG)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);
	sRet |= pthis->GPS_SetCommand(pthis, szEnableZDA, sizeof(szEnableZDA)-1);
	sRet |= pthis->GPS_SetCommand(pthis, "\r\n", sizeof("\r\n")-1);

    return sRet;
}

//------------------------------------------------------------------------------
//  Function    : GPS_Module_Init
//  Description :
//------------------------------------------------------------------------------

int GPS_Module_Init(void)
{
	printc("[U-BLOX 7 - GPS_Module_Init]\r\n");
    MMPF_3RDParty_GPS_Register(&GPS_Module_Obj);
    return 0;
}

#if defined(__RTK_OS__)
#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(GPS_Module_Init);
#endif // #if defined(__RTK_OS__)

#endif // (GPS_CONNECT_ENABLE && (GPS_MODULE == GPS_MODULE_NMEA0183))
