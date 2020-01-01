
//==============================================================================
//
//  File        : RTC_AIT.c
//  Description : RTC Control Interface for test by using internal rtc
//  Author      : Jerry Li
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file RTC_AIT.c
 *  @brief The RTC control functions
 *  @author Jerry Li
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "AIT_Init.h"
#include "RTC_AIT.h"
#include "mmpf_rtc_ctl.h"
#include "mmpf_rtc.h"

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Open
//  Description :
//------------------------------------------------------------------------------
MMP_ERR RTC_AIT_Open(struct _3RD_PARTY_RTC *pthis)
{
    return MMPF_RTC_Initialize();
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Release
//  Description :
//------------------------------------------------------------------------------
MMP_ERR RTC_AIT_Release(struct _3RD_PARTY_RTC *pthis)
{
    printc("%s,%d under construction.\r\n", __func__, __LINE__);
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Ioctl
//  Description :
//------------------------------------------------------------------------------
MMP_ERR RTC_AIT_Ioctl(struct _3RD_PARTY_RTC *pthis, MMP_ULONG cmd, MMP_U_LONG arg)
{
    printc("%s,%d under construction.\r\n", __func__, __LINE__);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Set_Time
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for setting time information to RTC.

This function is used for setting time information to RTC.
@param[in] pointer of structure AUTL_DATETIME.
@return It reports the status of the operation.
*/
MMP_ERR	RTC_AIT_Set_Time(struct _3RD_PARTY_RTC *pthis, AUTL_DATETIME *pRtcData)
{
    return MMPF_RTC_SetTime(pRtcData);
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Read_Time
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for getting RTC information.

This function is used for getting RTC time information.
@warning This function uses OS sleep, please don't call this function in ISR.
@param[in] pointer of structure AUTL_DATETIME.
@return It reports the status of the operation.
*/
MMP_ERR RTC_AIT_Read_Time(struct _3RD_PARTY_RTC *pthis, AUTL_DATETIME *pRtcData)
{
    return MMPF_RTC_GetTime(pRtcData);
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Read_ShadowTime
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for getting the last RTC time.

This function is used for getting the last RTC time information.
@warning This function uses OS sleep, please don't call this function in ISR.
@param[in] pointer of structure AUTL_DATETIME.
@return It reports the status of the operation.
*/
MMP_ERR RTC_AIT_Read_ShadowTime(struct _3RD_PARTY_RTC *pthis, AUTL_DATETIME *pRtcData)
{
    return MMPF_RTC_GetShadowTime(pRtcData);
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Read_Alarm
//  Description :
//------------------------------------------------------------------------------
MMP_ERR RTC_AIT_Read_Alarm(struct _3RD_PARTY_RTC *pthis, RTC_WKALRM *pAlarm)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Set_Alarm
//  Description :
//------------------------------------------------------------------------------
MMP_ERR RTC_AIT_Set_Alarm(struct _3RD_PARTY_RTC *pthis, RTC_WKALRM *pAlarm)
{
    // If you connect external RTC driver, please use GPIO interrupt instead of calling AIT internal alarm to call alarm callback function.
    return MMPF_RTC_SetAlarmEnable(pAlarm->bEnable, &(pAlarm->sTime), pAlarm->pRTCCB);
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Set_Mmss
//  Description :
//------------------------------------------------------------------------------
MMP_ERR RTC_AIT_Set_Mmss(struct _3RD_PARTY_RTC *pthis, MMP_U_LONG secs)
{
    MMP_ERR 		err;
    AUTL_DATETIME 	sRTCTime;
    
    err = MMPF_RTC_SecondsToDate(secs, &sRTCTime);
    
    if (err != MMP_ERR_NONE) {
        return err;
    }
    
    err = RTC_AIT_Set_Time(pthis, &sRTCTime);

    return err;
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Read_Callback
//  Description :
//------------------------------------------------------------------------------
MMP_ERR RTC_AIT_Read_Callback(struct _3RD_PARTY_RTC *pthis, MMP_LONG data)
{
    printc("%s,%d under construction.\r\n", __func__, __LINE__);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Alarm_Irq_Enable
//  Description :
//------------------------------------------------------------------------------
MMP_ERR RTC_AIT_Alarm_Irq_Enable(struct _3RD_PARTY_RTC *pthis, MMP_ULONG enabled)
{
    printc("%s,%d under construction.\r\n", __func__, __LINE__);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : RTC_AIT_Read_BaseTime
//  Description :
//------------------------------------------------------------------------------
MMP_ERR RTC_AIT_Read_BaseTime(struct _3RD_PARTY_RTC *pthis, MMP_ULONG *data)
{
    return MMPF_RTC_GetBaseTime(data);
}


struct _3RD_PARTY_RTC RTC_AIT_Obj =
{
    //0
    RTC_AIT_Open,
    RTC_AIT_Release,
    RTC_AIT_Ioctl,
    RTC_AIT_Read_Time,
    RTC_AIT_Read_ShadowTime,
    //5
    RTC_AIT_Set_Time,
    RTC_AIT_Read_Alarm,
    RTC_AIT_Set_Alarm,
    RTC_AIT_Set_Mmss,
    RTC_AIT_Read_Callback,
    //10
    RTC_AIT_Alarm_Irq_Enable,
    RTC_AIT_Read_BaseTime,
};

int RTC_AIT_Module_Init(void) 
{
    printc("[RTC_AIT_Module_Init]\r\n");
    MMPF_RTC_CTL_Register(&RTC_AIT_Obj);
    return 0;    
}

#if defined(__RTK_OS__)

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(RTC_AIT_Module_Init);

#else //#if defined(__RTK_OS__)
#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6" 
#pragma O0
ait_module_init(RTC_AIT_Module_Init);
#pragma
#pragma arm section rodata, rwdata ,  zidata 
#endif //#if defined(__RTK_OS__)
