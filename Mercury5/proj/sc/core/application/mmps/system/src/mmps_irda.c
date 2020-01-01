//==============================================================================
//
//  File        : mmps_IrDA.c
//  Description : IrDA Functions.
//  Author      : lei.qin
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_IrDA.c
 *  @brief The IrDA control functions
 *  @author Lei.Qin
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//============================================================================== 
 
#include "mmp_lib.h"
#include "mmpf_irda.h"
#include "Dsc_key.h"
#include "Customer_config.h"

/*===========================================================================
 * Global variable
 *===========================================================================*/ 

unsigned char   gLastKey = 0;
int    			gpre_ubKeyId = -1;
int				gRepeat_cnt = 0;
MMPF_OS_TMRID	gIRDA_Rel_TMRID = MMPF_OS_CREATE_TMR_INT_ERR;

#define SEND_REPEAT_CMD 0

MMPF_IRDA_CMD	gCmdAttr[2]={
	{
		1,		//MMP_UBYTE	ubNumOfStartBit;
		0x20,	//MMP_UBYTE	ubNumOfDataBit;
		{1,0,0,0,0,0,0,1},	//MMP_UBYTE	ubBitModeSel[8];	// 7 Start Bit + 1 Data Bit
		13500,	// 8.812ms<high>+4.42ms<low>MMP_USHORT	usMode1StartBitLen; // Unit:us
				//1654us/1515.1515ns = 1091<0x0443>   1654us/1939.393ns = 853<0x0355> <0X0358> Mute key 100% correct
		1690,	//MMP_USHORT	usMode1Log1LevelLen;// Unit:us
		17,		//MMP_USHORT	usMode1CompRange;
		1,		//MMP_USHORT	usMode1DiffLevel;	// High or Low
		0,		//MMP_USHORT	usMode0DataPeriod;	// Unit:us
		0,		//MMP_USHORT	usMode0LatchFac;	// Unit:us
		
		NULL,//&IrCode0_CB,			// Callback function for parsing data
	},
	{
		1,		//MMP_UBYTE	ubNumOfStartBit;
		0,		//MMP_UBYTE	ubNumOfDataBit;
		{1,0,0,0,0,0,0,1},	//MMP_UBYTE	ubBitModeSel[8];	// 7 Start Bit + 1 Data Bit
				//8.813ms<high>+2.204ms<low> / 1000ns = 11017<0x2B09>	
				//8.813ms<high>+2.204ms<low> / 1000ns = 7271<0x1C67>
				//8.813ms<high>+2.204ms<low> / 1939ns = 5681<0x1631>
		11245,	//MMP_USHORT	usMode1StartBitLen; // Unit:us
		0,	//MMP_USHORT	usMode1Log1LevelLen;// Unit:us
		17,		//MMP_USHORT	usMode1CompRange;
		1,		//MMP_USHORT	usMode1DiffLevel;	// High or Low
		0,		//MMP_USHORT	usMode0DataPeriod;	// Unit:us
		0,		//MMP_USHORT	usMode0LatchFac;	// Unit:us
		
		NULL,//IrCode1_CB			// Callback function for parsing data
	}

};

SIRBUTTON sIRDAButton[] =
{
//   iPressId            		iReleaseId          		iLongPressId        		iLongReleaseId      		ulKeyValue          		ubKeyStateId            		ubKeyPairId    				ubKeyCount 	ubPressStatus ubkeyname
    {KEY_PRESS_UP, 		KEY_REL_UP, 		KEY_LPRESS_UP, 		KEY_LREL_UP,		IRDA_VALUE_U, 		IR_STATE_ID_U, 			IR_STATE_ID_D,			0,			0,	"IR_UP"},
    {KEY_PRESS_DOWN, 	KEY_REL_DOWN, 		KEY_LPRESS_DOWN, 	KEY_LREL_DOWN,		IRDA_VALUE_D, 		IR_STATE_ID_D, 			IR_STATE_ID_U,			0,			0,	"IR_DOWN"},
    {KEY_PRESS_LEFT, 	KEY_REL_LEFT, 		KEY_LPRESS_LEFT, 	KEY_LREL_LEFT,		IRDA_VALUE_L, 		IR_STATE_ID_L, 			IR_STATE_ID_R,			0,			0,	"IR_LEFT"},
    {KEY_PRESS_RIGHT, 	KEY_REL_RIGHT, 		KEY_LPRESS_RIGHT, 	KEY_LREL_RIGHT,		IRDA_VALUE_R, 		IR_STATE_ID_R, 			IR_STATE_ID_L,			0,			0,	"IR_RIGHT"},
    {KEY_PRESS_REC, 	KEY_REL_REC, 		KEY_LPRESS_REC, 	KEY_LREL_REC,		IRDA_VALUE_REC, 	IR_STATE_ID_REC, 		IR_STATE_ID_INVALID,	0,			0,	"IR_REC"},
	{KEY_PRESS_MODE,	KEY_REL_MODE,		KEY_LPRESS_MODE,	KEY_LREL_MODE,		IRDA_VALUE_MODE,	IR_STATE_ID_MODE,		IR_STATE_ID_INVALID,	0,			0,	"IR_MODE"},
	{KEY_PRESS_MENU,	KEY_REL_MENU,		KEY_LPRESS_MENU,	KEY_LREL_MENU,		IRDA_VALUE_MENU,	IR_STATE_ID_MENU,		IR_STATE_ID_INVALID,	0,			0,	"IR_MENU"},
	{KEY_PRESS_POWER, 	KEY_REL_POWER,		KEY_LPRESS_POWER, 	KEY_LREL_POWER, 	IRDA_VALUE_POWER,	IR_STATE_ID_POWER,		IR_STATE_ID_INVALID, 	0,			0,	"IR_POWER"},
};

#define	NUM_IRDA_KEY	(sizeof(sIRDAButton) / sizeof(SIRBUTTON))
#define SEND_CMD_IN_CB	(1)
#if (SUPPORT_ONCHIP_IRDA)
#define	CDV_IRDA_START_FLAG		0x00000008
#define	CDV_IRDA_STOP_FLAG		0x00000010
#endif

extern MMPF_OS_FLAGID   CDV_UI_Flag;

/*===========================================================================
 * Extern function
 *===========================================================================*/

/*===========================================================================
 * local function
 *===========================================================================*/
void IrCode0_CB(MMP_ULONG   ulData0,MMP_ULONG   ulData1);
void IrCode1_CB(MMP_ULONG   ulData0,MMP_ULONG   ulData1);

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
//------------------------------------------------------------------------------
//  Function    : MMPS_IrDA_Initialize
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Initialize IrDA

 @return the status of the operation.
*/
MMP_ERR MMPS_IrDA_Initialize(void)
{
	MMPF_IRDA_ATTR pAttr;
	MMP_ERR		ret = MMP_ERR_NONE;

	pAttr.bInDataInvEn = MMP_FALSE;
	pAttr.bStartBitH2L = MMP_FALSE;
	pAttr.bInDataMsbFirst = MMP_TRUE;
	pAttr.bData2FIFOInvEn = MMP_FALSE;
	pAttr.ulIrdaClk = 600000;          // Unit:Hz
	gCmdAttr[0].pCBFunc = (void*)&IrCode0_CB;
	gCmdAttr[1].pCBFunc = (void*)&IrCode1_CB;
	pAttr.pCmdAttr[0]= &gCmdAttr[0];
	pAttr.pCmdAttr[1]= &gCmdAttr[1];
	MMPF_IRDA_EnableRx(MMP_FALSE);
	MMPF_IRDA_PADSetting();
	ret = MMPF_IRDA_Initialize();
	ret |= MMPF_IRDA_SetCmdAttribute(&pAttr);
	printc("\r\n IrDA start\r\n");
	
    return ret;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_IrDA_SetTime
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set IrDA

 @warning This function uses OS sleep, please DON'T call this function in ISR.

 @param[in] datetime : Date time information
 @return the status of the operation.
*/
MMP_ERR MMPS_IrDA_SetIrCb(void* IrCode0CB, void *IrCode1CB)
{
	gCmdAttr[0].pCBFunc = IrCode0CB;
	gCmdAttr[1].pCBFunc = IrCode1CB;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_IrDA_SetIrEn
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set wake up counter of IrDA unit


 @param[in] bEnable : Enable/Disable IrDA 
 @return the status of the operation.
*/
MMP_ERR MMPS_IrDA_SetIrEn(MMP_BOOL bEnable)
{
	return MMPF_IRDA_EnableRx(bEnable);
}

void MMPS_IrDA_RelCheck_TMRStop(void)
{
	if (MMPF_OS_CREATE_TMR_INT_ERR != gIRDA_Rel_TMRID)
	{
		MMPF_OS_StopTimer(gIRDA_Rel_TMRID, NULL);
		gIRDA_Rel_TMRID = MMPF_OS_CREATE_TMR_INT_ERR;
	}
}

void MMPS_IrDA_TMRCB(OS_TMR *ptmr, void *parg)
{
	MMPS_IrDA_RelCheck_TMRStop();
	//SetKeyPadEvent(sIRDAButton[gpre_ubKeyId].iReleaseId);
	//printc("IR Key Release %s Sent %d\r\n", sIRDAButton[gpre_ubKeyId].ubkeyname, sIRDAButton[gpre_ubKeyId].iReleaseId);
}

void MMPS_IrDA_RelCheck_TMRStart(void)
{
	gIRDA_Rel_TMRID = MMPF_OS_StartTimer(200, MMPF_OS_TMR_OPT_PERIODIC, (MMPF_OS_TMR_CALLBACK)&MMPS_IrDA_TMRCB, NULL);
	if (gIRDA_Rel_TMRID == MMPF_OS_CREATE_TMR_INT_ERR) {
		printc("IR Key Press,Start timer error!\r\n");
	}
}

//------------------------------------------------------------------------------
//  Function    : IrCode0_CB
//  Description :
//------------------------------------------------------------------------------
/**
 @brief IrDA callback
  @param[in] ulData0 : CMD0 
  @param[in] ulData1 : CMD1 
 */
extern unsigned char AHC_SetButtonStatus(unsigned int keyId);

void IrCode0_CB(MMP_ULONG   ulData0,MMP_ULONG   ulData1)
{
	U16 key,key_inverse,i;
		
	key = ulData0 & 0xff;
	key_inverse = (ulData0 >> 8) & 0xff;
	gRepeat_cnt 	= 0;
#if 1	
	if(key == (0xff - key_inverse))
	{
		gLastKey = key;
		
		for(i=0; i<NUM_IRDA_KEY; i++) 
		{
			if (sIRDAButton[i].ulKeyValue == (unsigned short)key /* little endian */) 
			{
				gpre_ubKeyId = i;
				//SetKeyPadEvent(sIRDAButton[i].iPressId);
				//AHC_SetButtonStatus(sIRDAButton[i].iPressId);
				//MMPS_IrDA_RelCheck_TMRStop();
				//MMPS_IrDA_RelCheck_TMRStart();
				//printc("IR Key Press %s Sent %d,key=0x%x\r\n", sIRDAButton[i].ubkeyname, sIRDAButton[i].iPressId,key);
				break;
			}
		}
	}
	else
	{
		gLastKey 		= 0;
		gpre_ubKeyId 	= -1;
	}
#endif
}

void IrCode1_CB(MMP_ULONG   ulData0,MMP_ULONG   ulData1)
{
	if(gLastKey != 0 && gpre_ubKeyId != -1)
	{
		//SetKeyPadEvent(sIRDAButton[gpre_ubKeyId].iReleaseId);
		gLastKey = 0;
		gpre_ubKeyId = -1;
	}

#if SEND_REPEAT_CMD
	if (MMPF_OS_CREATE_TMR_INT_ERR != gIRDA_Rel_TMRID)
	{
		MMPF_OS_StopTimer(gIRDA_Rel_TMRID, NULL);
		gIRDA_Rel_TMRID = MMPF_OS_CREATE_TMR_INT_ERR;
	}
				
	if(gLastKey != 0)
	{
		gRepeat_cnt ++;
		if(gRepeat_cnt%2 == 0){
			//SetKeyPadEvent(sIRDAButton[gpre_ubKeyId].iPressId);		//repeat key, send event per second interrupt.
			//printc("Repeat IR Key Press %s Sent %d,key=0x%x,cnt=%d\r\n", sIRDAButton[gpre_ubKeyId].ubkeyname, sIRDAButton[gpre_ubKeyId].iPressId, gLastKey, gRepeat_cnt);
		}	
	}

	gIRDA_Rel_TMRID = MMPF_OS_StartTimer(200, MMPF_OS_TMR_OPT_PERIODIC, (MMPF_OS_TMR_CALLBACK)&MMPS_IrDA_TMRCB, NULL);
	if (gIRDA_Rel_TMRID == MMPF_OS_CREATE_TMR_INT_ERR) {
		printc("IR Key Press,Start timer error!\r\n");
	}
#endif
}


