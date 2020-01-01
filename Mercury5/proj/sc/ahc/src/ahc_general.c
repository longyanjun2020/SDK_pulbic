/**
 @file AHC_General.c
 @brief AHC general control Function
 @author
 @version 1.0
*/

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_fs.h"
#include "ahc_general.h"
#include "ahc_parameter.h"
#include "ahc_mediaplayback.h"
#include "ahc_message.h"
#include "ahc_stream.h"
#include "ahc_media.h"
#include "ahc_callback.h"
#include "pCam_api.h"
#include "dram_cfg.h"
#include "lcd_common.h"

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
#include "wlan.h"
#include "netapp.h"
#include "mmpf_streaming.h"
#endif

/*===========================================================================
 * Project definition check
 *===========================================================================*/

#if (AHC_DRAM_SIZE == COMMON_DRAM_SIZE_NG)
#error "Definition AHC_DRAM_SIZE NG!!!"
#endif

#if (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_NG)
#error "Definition VR_VIDEO_TYPE NG!!!"
#endif

#if 0
void _____Global_Variable_________(){ruturn;} //dummy
#endif

/** @addtogroup AHC_GENERAL
@{
*/
/*===========================================================================
 * Global varible
 *===========================================================================*/
static AHC_BOOL                 gbPIRStarted            = AHC_FALSE;

AHC_BOOL                        gbBlockRealIDUIKeyTask = AHC_FALSE;

static UINT32                   gulCurKeyEventID = EVENT_NONE;

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern AHC_BOOL                     gbAhcDbgBrk;

/*===========================================================================
 * Extern function
 *===========================================================================*/

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void _____Utility_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_KeyEventIDCheckConflict
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_KeyEventIDCheckConflict(UINT32 ulCurKeyEventID)
{
    if (((BUTTON_USB_B_DEVICE_DETECTED == gulCurKeyEventID) ||
         (BUTTON_USB_B_DEVICE_REMOVED == gulCurKeyEventID)  ||
         (BUTTON_TV_DECODER_SRC_TYPE == gulCurKeyEventID)) &&
        ((BUTTON_VRCB_RECDSTOP_CARDSLOW == ulCurKeyEventID) ||
         (BUTTON_VRCB_FILE_FULL == ulCurKeyEventID)     ||
         (BUTTON_VRCB_MEDIA_FULL == ulCurKeyEventID)    ||
         (BUTTON_VRCB_SEAM_LESS == ulCurKeyEventID)     ||
         (BUTTON_VRCB_SHARE_FILE_FULL == ulCurKeyEventID)))
    {
        AHC_DBG_ERR(1, "[%s] gulCurKeyEventID:0x%x, ulCurKeyEventID:0x%x\r\n",
                    __FUNCTION__, gulCurKeyEventID, ulCurKeyEventID);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetCurKeyEventID
//  Description :
//------------------------------------------------------------------------------
void AHC_SetCurKeyEventID(UINT32 ulCurKeyEventID)
{
    gulCurKeyEventID = ulCurKeyEventID;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetCurKeyEventID
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_GetCurKeyEventID(void)
{
    return gulCurKeyEventID;
}

#if 0
void ____PIR_Function_____(){ruturn;} //dummy
#endif

#if (ENABLE_PIR_MODE)
//------------------------------------------------------------------------------
//  Function    : AHC_PIR_CheckStart
//  Description :
//------------------------------------------------------------------------------
void AHC_PIR_CheckStart(void)
{
    MMP_UBYTE tempValue;

    if (DEVICE_GPIO_PIR_INT != MMP_GPIO_MAX) {

        MMPF_PIO_GetData(DEVICE_GPIO_PIR_INT, &tempValue);

        if (tempValue) {
            gbPIRStarted = AHC_FALSE;
        }
        else {
            gbPIRStarted = AHC_TRUE;
        }
    }
    else {
        gbPIRStarted = AHC_FALSE;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_PIR_CheckStart
//  Description :
//------------------------------------------------------------------------------
void AHC_PIR_SetEnable(AHC_BOOL bEnable)
{
    if (DEVICE_GPIO_PIR_EN != MMP_GPIO_MAX) {
        
        MMPF_PIO_EnableOutputMode(DEVICE_GPIO_PIR_EN, MMP_TRUE, MMP_FALSE);
       
        if (bEnable)
            MMPF_PIO_SetData(DEVICE_GPIO_PIR_EN, MMP_FALSE, MMP_FALSE);
        else
            MMPF_PIO_SetData(DEVICE_GPIO_PIR_EN, MMP_TRUE, MMP_FALSE);
    }
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_PIR_IsStarted
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_PIR_IsStarted(void)
{
    return gbPIRStarted;
}

#if 0
void ____Buzzer_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_BUZZER_Alert
//  Description :
//------------------------------------------------------------------------------
void AHC_BUZZER_Alert(UINT32 ulFrquency, UINT32 ulTimes, UINT32 ulMs)
{
#if defined(SUPPORT_BUZZER) && (SUPPORT_BUZZER)

    #if (BUZZER_USING_SW_PWMN)

    #if defined(DEVICE_GPIO_BUZZER) && (DEVICE_GPIO_BUZZER != MMP_GPIO_MAX)
    {
        UINT32	ulPulseTimes = 300;
        
        AHC_GPIO_SetOutputMode(DEVICE_GPIO_BUZZER, AHC_TRUE);
        
        while (ulTimes > 0)
        {
            ulPulseTimes = 100*ulMs;
            
            while (ulPulseTimes > 0)
            {
                MMPF_PIO_SetData(DEVICE_GPIO_BUZZER, 0x01, MMP_TRUE);
                RTNA_WAIT_US(121);///110---4.46KHZ///122---3.968Khz////137---3.6KHZ
                MMPF_PIO_SetData(DEVICE_GPIO_BUZZER, 0x00, MMP_TRUE);
                RTNA_WAIT_US(121);
                
                ulPulseTimes--;
            }
            ulTimes--;
            AHC_OS_SleepMs(60);
        }

        AHC_OS_SleepMs(150);
    }
    #endif

    #else
    {    
        MMP_BYTE i = 0;

        AHC_PWM_Initialize();

        for (i = 0; i < ulTimes; i++) {
            #if defined(DEVICE_GPIO_BUZZER)
            if (DEVICE_GPIO_BUZZER != MMP_GPIO_MAX) {
                AHC_PWM_OutputPulse(DEVICE_GPIO_BUZZER, MMP_TRUE, (MMP_ULONG)ulFrquency, MMP_TRUE, MMP_FALSE, NULL, 0xFF);
            }
            #else
                AHC_PWM_OutputPulse(PWM2_PIN_AGPIO3, MMP_TRUE, (MMP_ULONG)ulFrquency, MMP_TRUE, MMP_FALSE, NULL, 0xFF);
            #endif

            if (i < (ulTimes - 1)) {
                AHC_OS_SleepMs(ulMs);
            }
        }
    }
    #endif
    
#endif
}

#if 0
void ____Misc_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_DumpRegister
//  Description : CHECK
//------------------------------------------------------------------------------
void AHC_DumpRegister(ULONG ulStartAddress, ULONG ulBytes)
{
    static MMP_ULONG preTime = 0;
    MMP_ULONG   curTime;
    ULONG       Register;

    RTNA_DBG_Str(0, "\r\n=====================================Register Dump Start\r\n");
    
    MMPF_OS_GetTime(&curTime);

    if (curTime >= preTime) {
        curTime -= preTime;
    }
    else {
        curTime += ((MMP_ULONG) -1) - preTime + 1;
    }

    if (curTime < 5000) {
        return;
    }

    MMPF_OS_GetTime(&preTime);

    for (Register = 0; Register < ulBytes; Register += 4) {
        if ((Register % 16) == 0) {
            RTNA_DBG_Str(0, "\r\n");
            RTNA_DBG_Long(0, ulStartAddress + Register);
            RTNA_DBG_Str(0, ": ");
        }

        //RTNA_DBG_Long(0, *(AIT_REG_D *) (ulStartAddress + Register));
    }

    RTNA_DBG_Str(0, "\r\n========================================Register Dump End\r\n\r\n");
}

//------------------------------------------------------------------------------
//  Function    : AHC_CheckSysCalibMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_CheckSysCalibMode(void)
{
    UINT32  ulFileId;
    AHC_ERR error = AHC_ERR_NONE;

    if (AHC_IsSDInserted() == AHC_FALSE) {
        printc("Check FactoryModeFile - No SD\r\n");
        return AHC_FALSE;
    }

    error = AHC_FS_FileOpen("SD:\\Test\\FACTORY.CAL", AHC_StrLen("SD:\\Test\\FACTORY.CAL"), "rb", AHC_StrLen("rb"), &ulFileId);
    
    if (error == AHC_ERR_NONE) {
        AHC_FS_FileClose(ulFileId);
        printc("FactoryModeFile FACTORY.CAL was found in SD\r\n");
        return AHC_TRUE;
    }
    else {
        printc("No FactoryModeFile FACTORY.CAL in SD\r\n");
    }

    return AHC_FALSE;
}

#if (SUPPORT_HDMI_OUT_FOCUS)
//------------------------------------------------------------------------------
//  Function    : AHC_CheckHdmiOutFocus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_CheckHdmiOutFocus(void)
{
    UINT32  ulFileId;
    AHC_ERR error = AHC_ERR_NONE;

    if (AHC_IsSDInserted() == AHC_FALSE) {
        printc("Check HdmiOutFousFile - No SD\r\n");
        return AHC_FALSE;
    }

    error = AHC_FS_FileOpen(CFG_HDMI_OUT_FOCUS_FILE, AHC_StrLen(CFG_HDMI_OUT_FOCUS_FILE), "rb", AHC_StrLen("rb"), &ulFileId);
    
    if (error == AHC_ERR_NONE) {
        AHC_FS_FileClose(ulFileId);
        printc("HdmiOutFousFile %s was found in SD\r\n", CFG_HDMI_OUT_FOCUS_FILE);
        return AHC_TRUE;
    }
    else {
        printc("No HdmiOutFousFile %s in SD\r\n", CFG_HDMI_OUT_FOCUS_FILE);
    }

    return AHC_FALSE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_RestoreFromDefaultSetting
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_RestoreFromDefaultSetting(void)
{
    #ifdef FACTORY_RESET
    AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, FACTORY_RESET, 0);
    #endif
    
    return AHC_TRUE;
}



