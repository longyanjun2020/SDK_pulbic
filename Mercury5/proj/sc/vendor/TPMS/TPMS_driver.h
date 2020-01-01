
#ifndef _TPMS_DRIVER_H_
#define _TPMS_DRIVER_H_

/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "mmpf_typedef.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/
#define TPMS_DEBUG		(0)
 
#define TPMS_LEARN_MODE_FINISH		(0)
#define TPMS_LEARN_MODE_NOT_FINISH	(1)
#define TPMS_LEARN_MODE_TIME_OUT	(2)

#define TPMS_UART_NUM 		(MMP_UART_ID_2)
#define TPMS_RX_QUEUE_SIZE	(4096)
#define RX_TPMS_SIGNAL  	'$'
#define TPMS_BAUD_RATE 		(9600)
#define TPMS_UART_CLK 		(264000 >> 1)

/*===========================================================================
 * Enum define
 *===========================================================================*/
typedef enum _TPMSCOMMAND_TYPE // Only support UBX protocol now
{
	TPMSCMD_GET_WHEEL_DATA_0   	= 0,
	TPMSCMD_GET_WHEEL_DATA_1	= 1,
	TPMSCMD_GET_WHEEL_DATA_2	= 2,
	TPMSCMD_GET_WHEEL_DATA_3	= 3,
	TPMSCMD_ENTER_LEARN_ID_MODE	= 4,
	TPMSCMD_EXIT_LEARN_ID_MODE	= 5,
	TPMSCMD_SET_AUTO			= 6,
	TPMSCMD_SET_MANUAL			= 7

} TPMSCOMMAND_TYPE;

/*===========================================================================
 * Structure define
 *===========================================================================*/
//1 PSI = 0.06895 Bar = 0.07031 kg/cm^2 = 6.89506 KPa
typedef struct _TPMSPACK
{
	MMP_LONG	ubWheelPosition;      	//0: front left, 1:front right, 2: rear left, 3: rear right
	MMP_LONG	ubBatteryIndication; 	//0: normal, 1:battery low power
	MMP_LONG    ubWheelDataUpdate;		//0: data is not updated  1: data is updated
	MMP_LONG	ubTirePressure; 		// Unit 0.1 PSI.
	MMP_LONG	ubTirePressureInt; 		// Unit 1 PSI.
	MMP_LONG    ubTireTemp;				//0-185 stands for -40-145 degree in Celsius.

} TPMSPACK, *pTirePressurePack;

typedef struct _TPMSINFO
{
	TPMSPACK  sTire[4];

} TPMSINFO, *pTireInfo;

/*===========================================================================
 * Function pointer
 *===========================================================================*/
typedef void (*PTPMSLEARNMODE_CALLBACK)(UINT32); // For learning mode.

/*===========================================================================
 * Function prototype
 *===========================================================================*/
void TPMS_String_RxCallback(MMP_UBYTE size, volatile MMP_UBYTE *fifo);
MMP_ERR TPMS_GetString_UART(MMP_BYTE *bTPMSString, MMP_ULONG *ulTPMSStringLength);
MMP_BOOL TPMS_InitPathUART(void);
pTireInfo TPMS_Information(void);
void TPMS_ParserInitialize(void);
MMP_LONG TPMS_FindTail(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_LONG *pRes_crc);
MMP_LONG TPMS_ParsePack(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, TPMSPACK *psPack);
void TPMS_Pack2info(TPMSPACK *psPack, TPMSINFO *psInfo);
void TPMS_PaeserMain(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, TPMSINFO *pInfo);
void TPMS_SetCommand(TPMSCOMMAND_TYPE type);
void TPMS_EnterLearnMode(PTPMSLEARNMODE_CALLBACK pCallback, UINT32 TimeOut);
void TPMS_ExitLearnMode(void);
MMP_BOOL TPMS_IsReceiverConnected(void);
void TPMS_UpdateData(void);
#if (TPMS_DEBUG)
TPMSINFO* TPMS_GetTPMSInfo(void);
void TPMS_SetConnectStatus(void);
#endif

#endif // _TPMS_DRIVER_H_
