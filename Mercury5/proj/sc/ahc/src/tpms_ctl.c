/*===========================================================================
 * Include file 
 *===========================================================================*/ 
#include "os_wrap.h"
#include "ahc_general.h"
#include "ahc_parameter.h"
#include "ahc_os.h"
#include "MenuSetting.h"
#include "ahc_fs.h"
#include "ahc_video.h"
#include "ahc_utility.h"
#include "ahc_datetime.h"
#include "ahc_media.h"
#include "stdarg.h"
#include "stdio.h"
#include "mmpf_pio.h"
#include "mmpf_fs_api.h"
#include "math.h"
#include "ahc_menu.h"
#include "tpms_ctl.h"
#include "TPMS_driver.h"

#if (TPMS_FUNC_EN)

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define IS_A_DIGIT(x)					 ((x >='0') && (x <='9'))

/*===========================================================================
 * Global varible
 *===========================================================================*/
MMP_BOOL	m_bTPMS_init = MMP_FALSE;
/*===========================================================================
 * Main body
 *===========================================================================*/
#if 0
void _____TPMS_String_Tool_________(){ruturn;} //dummy
#endif

static UINT32 TPMSCtrl_Convert_Endian(UINT32 d)
{
	UINT32 t = d;	
	*((char*)&d + 3) = *((char*)&t + 0);
	*((char*)&d + 2) = *((char*)&t + 1);
	*((char*)&d + 1) = *((char*)&t + 2);
	*((char*)&d + 0) = *((char*)&t + 3);
	return d;
}

/** 
 @brief Convert string to number
 */

MMP_LONG TPMSCtrl_Atoi(MMP_BYTE *pStr, MMP_LONG iStr_sz, MMP_LONG iRadix)
{
    MMP_BYTE *pTmp_ptr;
    MMP_BYTE szBuff[256];
    MMP_LONG iRes = 0;

    if(iStr_sz < 256)
    {
        memcpy(&szBuff[0], pStr, iStr_sz);
        szBuff[iStr_sz] = '\0';
        iRes = strtol(&szBuff[0], &pTmp_ptr, iRadix);
    }

    return iRes;
}

/** 
 @brief Convert string to fractional number
 */

double TPMSCtrl_Atof(MMP_BYTE *pStr, MMP_LONG iStr_sz)
{
    MMP_BYTE 	*pTmp_ptr;
    MMP_BYTE 	szBuff[256];
    double 		dwRes = 0;

    if(iStr_sz < 256)
    {
        memcpy(&szBuff[0], pStr, iStr_sz);
        szBuff[iStr_sz] = '\0';
        dwRes = strtod(&szBuff[0], &pTmp_ptr);
    }

    return dwRes;
}

/**
 @brief Analyse string (specificate for NMEA sentences)
 */
 
MMP_LONG TPMSCtrl_Scanf(MMP_BYTE *pBuff, MMP_LONG iBuff_sz, MMP_BYTE *pFormat, ...)
{
    MMP_BYTE 	*pBeg_tok;
    MMP_BYTE 	*pEnd_buf 	= pBuff + iBuff_sz;
    MMP_LONG 	iTok_type 	= TPMS_SCAN_TOKS_COMPARE;
    MMP_LONG 	iWidth 		= 0;
    MMP_BYTE 	*pBeg_fmt 	= 0;
    MMP_LONG 	iSnum = 0, iUnum = 0;
    MMP_LONG 	iTok_count 	= 0;
    void 		*parg_target;
    va_list 	arg_ptr;

    va_start(arg_ptr, pFormat);
    
    for(; *pFormat && pBuff < pEnd_buf; ++pFormat)
    {
        switch(iTok_type)
        {
			case TPMS_SCAN_TOKS_COMPARE:
	            if('%' == *pFormat)
	                iTok_type = TPMS_SCAN_TOKS_PERCENT;
	            else if(*pBuff++ != *pFormat)
	                goto fail;
	        break;
	        
	        case TPMS_SCAN_TOKS_PERCENT:
	            iWidth = 0;
	            pBeg_fmt = pFormat;
	            iTok_type = TPMS_SCAN_TOKS_WIDTH;
	            
	        case TPMS_SCAN_TOKS_WIDTH:
	            if(IS_A_DIGIT(*pFormat))
	                break;
	            {
	                iTok_type = TPMS_SCAN_TOKS_TYPE;
	                if(pFormat > pBeg_fmt)
	                    iWidth = TPMSCtrl_Atoi(pBeg_fmt, (MMP_LONG)(pFormat - pBeg_fmt), 10);
	            }
	            
	        case TPMS_SCAN_TOKS_TYPE:
	            pBeg_tok = pBuff;

	            if(!iWidth && ('c' == *pFormat || 'C' == *pFormat) && *pBuff != pFormat[1])
	                iWidth = 1;

	            if(iWidth)
	            {
	                if(pBuff + iWidth <= pEnd_buf)
	                    pBuff += iWidth;
	                else
	                    goto fail;
	            }
	            else
	            {
	                if(!pFormat[1] || (0 == (pBuff = (MMP_BYTE *)memchr(pBuff, pFormat[1], pEnd_buf - pBuff))))
	                    pBuff = pEnd_buf;
	            }

	            if(pBuff > pEnd_buf)
	                goto fail;

	            iTok_type = TPMS_SCAN_TOKS_COMPARE;
	            iTok_count++;

	            parg_target = 0; iWidth = (MMP_LONG)(pBuff - pBeg_tok);

	            switch(*pFormat)
	            {
		            case 'c':
		            case 'C':
		                parg_target = (void *)va_arg(arg_ptr, MMP_BYTE *);
		                if(iWidth && 0 != (parg_target))
		                    *((MMP_BYTE *)parg_target) = *pBeg_tok;
		                break;
		            case 's':
		            case 'S':
		                parg_target = (void *)va_arg(arg_ptr, MMP_BYTE *);
		                if(iWidth && 0 != (parg_target))
		                {
		                    memcpy(parg_target, pBeg_tok, iWidth);
		                    ((MMP_BYTE *)parg_target)[iWidth] = '\0';
		                }
		                break;
		            case 'f':
		            case 'e':
		            case 'E':
		                parg_target = (void *)va_arg(arg_ptr, double *);
		                if(iWidth && 0 != (parg_target))
		                    *((double *)parg_target) = TPMSCtrl_Atof(pBeg_tok, iWidth);
		                break;
	            };

	            if(parg_target)
	                break;
	            if(0 == (parg_target = (void *)va_arg(arg_ptr, int *)))
	                break;
	            if(!iWidth)
	                break;

	            switch(*pFormat)
	            {
		            case 'd':
		            case 'i':
		                iSnum = TPMSCtrl_Atoi(pBeg_tok, iWidth, 10);
		                memcpy(parg_target, &iSnum, sizeof(MMP_LONG));
		                break;
		            case 'u':
		                iUnum = TPMSCtrl_Atoi(pBeg_tok, iWidth, 10);
		                memcpy(parg_target, &iUnum, sizeof(MMP_ULONG));
		                break;
		            case 'x':
		            case 'X':
		                iUnum = TPMSCtrl_Atoi(pBeg_tok, iWidth, 16);
		                memcpy(parg_target, &iUnum, sizeof(MMP_ULONG));
		                break;
		            case 'o':
		                iUnum = TPMSCtrl_Atoi(pBeg_tok, iWidth, 8);
		                memcpy(parg_target, &iUnum, sizeof(MMP_ULONG));
		                break;
		            default:
		                goto fail;
	            };

	            break;
        };
    }

fail:

    va_end(arg_ptr);

    return iTok_count;
}
#if 0
void _____TPMS_Function_________(){ruturn;} //dummy
#endif

MMP_BOOL TPMSCtrl_GetConnectStatus(void) // SW level.
{
	return (m_bTPMS_init & TPMS_IsReceiverConnected());
}

MMP_BOOL TPMSCtrl_GetInitStatus(void)
{
	return m_bTPMS_init;
}

MMP_BOOL TPMSCtrl_GetWheelInformation(MMP_UBYTE ubWheelNum)
{
	MMP_UBYTE ubCommand = 0;
	switch (ubWheelNum)
	{
		case 0:
			ubCommand = TPMSCMD_GET_WHEEL_DATA_0;
			break;
		case 1:
			ubCommand = TPMSCMD_GET_WHEEL_DATA_1;
			break;
		case 2:
			ubCommand = TPMSCMD_GET_WHEEL_DATA_2;
			break;
		case 3:
			ubCommand = TPMSCMD_GET_WHEEL_DATA_3;
			break;
	}
	
	TPMS_SetCommand(ubCommand);
	
	return MMP_TRUE;
}

MMP_BOOL TPMSCtrl_GetBatteryIndication(MMP_UBYTE ubWheelNum)
{
	TPMSINFO  *pInfo;
   	
   	pInfo = (TPMSINFO *)TPMS_Information();
	
	return pInfo->sTire[ubWheelNum].ubBatteryIndication;
}

MMP_BOOL TPMSCtrl_IsAvailable(UINT32 SensorNum)
{
	TPMSINFO  *pInfo;
   	
    pInfo = (TPMSINFO *)TPMS_Information();
    
    return (pInfo->sTire[SensorNum].ubWheelDataUpdate) ? MMP_TRUE : MMP_FALSE;
}

MMP_BOOL TPMSCtrl_GetWheelDataUpdateIndication(MMP_UBYTE ubWheelNum)
{
	
	TPMSINFO  *pInfo;
   	
    pInfo = (TPMSINFO *)TPMS_Information();
	
	return pInfo->sTire[ubWheelNum].ubWheelDataUpdate;

}

float TPMSCtrl_GetTirePressure(MMP_UBYTE ubWheelNum)//default: PSI
{
	TPMSINFO  *pInfo;
	float	fpressure = 0;
	
   	pInfo = (TPMSINFO *)TPMS_Information();
	
	fpressure = (float)(((pInfo->sTire[ubWheelNum].ubTirePressureInt * 10) \
			   +(pInfo->sTire[ubWheelNum].ubTirePressure))) / 10; 
	
	return fpressure;
}

MMP_LONG TPMSCtrl_GetTireTemp(MMP_UBYTE ubWheelNum)
{
	TPMSINFO  *pInfo;
	MMP_LONG  ltemp = -300;
	
   	pInfo = (TPMSINFO *)TPMS_Information();
   	
   	ltemp = (MMP_LONG)(pInfo->sTire[ubWheelNum].ubTireTemp - 40); 
	
	return ltemp;
}

static WHEEL_DATA m_WheelData;

void TPMSCtrl_GetWheelData(WHEEL_DATA* WheelData)
{
	int i;
	
	if (WheelData == NULL)
		return;
	
	for (i=0; i<4; i++)
	{
		WheelData->sWheelData[i].bNoSignal = TPMSCtrl_GetWheelDataUpdateIndication(i) ? 0 : 1;
		WheelData->sWheelData[i].bLowBattery = TPMSCtrl_GetBatteryIndication(i) ? 1 : 0;
		WheelData->sWheelData[i].fPressure = TPMSCtrl_GetTirePressure(i);
		WheelData->sWheelData[i].lTemperature = TPMSCtrl_GetTireTemp(i);
	}
}

void TPMSCtrl_EnterLearnMode(PTPMSLEARNMODE_CALLBACK pCallback, UINT32 TimeOut)
{
	TPMS_EnterLearnMode(pCallback, TimeOut);
}

void TPMSCtrl_ExitLearnMode(void) // Force stop the learning, may need check the sync. problem.
{
	TPMS_ExitLearnMode();
}

static TPMS_CALLBACK_ERROR m_pErrCallback = NULL;

#if (0)
void TPMSCtrl_Initial(TPMS_CALLBACK_ERROR pErrCallback)
#else
void TPMSCtrl_Initial(void)
#endif
{
	MMP_BOOL bUartInitSuccess = MMP_FALSE;
	
	TPMS_ParserInitialize();
	bUartInitSuccess = TPMS_InitPathUART();
	AHC_OS_Sleep(100);
	
	if (bUartInitSuccess)
	{
		m_bTPMS_init = MMP_TRUE;
		TPMS_SetCommand(TPMSCMD_SET_AUTO);
	}
	else
	{
		m_bTPMS_init = MMP_FALSE;
	}
}

void TPMSCtrl_UnInitial(void)
{
	TPMS_ParserUnInitialize();
	TPMS_UnInitPathUART();
	m_bTPMS_init = MMP_FALSE;
}

typedef struct _TPMS_SAFE_RANGE
{
	float pressureLowBound;
	float pressureHighBound;
	MMP_LONG temperatureLowBound;
	MMP_LONG temperatureHighBound;
} TPMS_SAFE_RANGE;

typedef struct _TPMS_SPEC
{
	TPMS_SAFE_RANGE FrontTire;
	TPMS_SAFE_RANGE RearTire;
} TPMS_SPEC;

static TPMS_SPEC m_TPMSSpec; // front tire & rear tire.
#if 0
void TPMSCtrl_ErrorCheck(void)
{
	int i = 0;
	int Err = 0;
	
	
	return;
	
	
	for (i=0; i<4; i++)
	{
		if ((TPMSCtrl_GetTirePressure(i) > pressureHighBound ||
			TPMSCtrl_GetTirePressure(i) < pressureLowBound) &&
			TPMSCtrl_GetWheelDataUpdateIndication(i) == MMP_TRUE)
		{
			Err |= TPMS_ERR_PRESSURE;
		}
		
		if ((TPMSCtrl_GetTireTemp(i) > temperatureHighBound ||
			TPMSCtrl_GetTireTemp(i) < temperatureLowBound) &&
			TPMSCtrl_GetWheelDataUpdateIndication(i) == MMP_TRUE)
		{
			Err |= TPMS_ERR_TEMPERATURE;
		}
		
		if (Err)
		{
			if (m_pErrCallback)
				m_pErrCallback(i, Err);
		}
	}
}
#endif
typedef enum
{
	TIRE_POSITION_LF = 0,
	TIRE_POSITION_RF,
	TIRE_POSITION_LR,
	TIRE_POSITION_RR
} TIRE_POSITION;

void TPMSCtrl_SetSensorLocation(int sensorIndex, TIRE_POSITION tire_pos)
{
	
}

void TPMSCtrl_SetRange(TPMS_SPEC *psSpec)
{
	memcpy(&m_TPMSSpec, psSpec, sizeof(TPMS_SPEC));
}

#endif // #if (TPMS_FUNC_EN)
