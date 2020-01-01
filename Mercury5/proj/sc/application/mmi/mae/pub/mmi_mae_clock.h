/**
 * @file    mmi_mae_clock.h
 * @brief   The document describes the interface of IClock
 * @author  kenny.wu@mstarsemi.com
 * @version $Id: mmi_mae_clock.h 726 2009-04-29 08:23:38Z code.lin $
 */
#ifndef __MMI_MAE_CLOCK_H__
#define __MMI_MAE_CLOCK_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_clock_forward.h"
#include "mmi_mae_handler.h"

#define INHERIT_IClock(IName) \
    INHERIT_IHandler(IName);\
    MAE_Ret (*AddListener)        (IName *pIClock, ClockListener_t *pClkLsn);\
    MAE_Ret (*CancelListener)     (IName *pIClock, ClockListener_t *pClkLsn);\
    MAE_Ret (*SetTime)            (IName *pIClock, MAE_DateTime_t *pDateTime);\
    MAE_Ret (*GetTime)            (IName *pIClock, MAE_DateTime_t *pDateTime);\
    MAE_Ret (*GetTimeEx)          (IName *pIClock, MAE_TimeZone_e eTimezone, MAE_DateTime_t *pDateTime);\
    u32     (*GetTimeInSeconds)   (IName *pIClock);\
    MAE_Ret (*SetTimeZone)        (IName *pIClock, MAE_TimeZone_e timeZone);\
    MAE_Ret (*SetTimeZoneEx)      (IName *pIClock, MAE_TimeZone_Field_e timeZoneField, MAE_TimeZone_e timeZone);\
    MAE_Ret (*GetTimeZone)        (IName *pIClock, MAE_TimeZone_e *timeZone);\
    MAE_Ret (*GetTimeZoneEx)      (IName *pIClock, MAE_TimeZone_Field_e timeZoneField, MAE_TimeZone_e *timeZone);\
    MAE_Ret (*ConvertToLocalTime) (IName *pIClock, MAE_DateTime_t *pUTCTime, MAE_DateTime_t *pLocalTime);\
    MAE_Ret (*ConvertToUTCTime)   (IName *pIClock, MAE_DateTime_t *pLocalTime, MAE_DateTime_t *pUTCTime);\
    MAE_Ret (*GetTimeOffset)      (IName *pIClock, MAE_DateTime_t *pUTCTime, MAE_TimeZone_e eTimezone, s32 *ps32Offset, boolean *pbDST); \
    MAE_Ret (*CheckFactoryTime)   (IName *pIClock, MAE_DateTime_t *pLocalTime); \
    MAE_Ret (*SetDaylightSavingTime)   (IName *pIClock, boolean bOnOff);\
    MAE_Ret (*AutoBackupTime)	  (IName *pIClock);\
    MAE_Ret (*RestoreBackupTime)  (IName *pIClock);\
    MAE_Ret (*GetTimeRange)       (IName *pIClock, MAE_DateTime_t *pMinDateTime, MAE_DateTime_t *pMaxDateTime);\
    MAE_Ret (*GetSysDefaultTime) (IName *pIClock, MAE_DateTime_t *pDefaultTime)

DEFINE_INTERFACE(IClock);

#define MAECLKMASK(ID)  (1 << (ID&0xFF)) //1<<ID

#define CLKLISTENER_INIT(_pClkLsn, _pfn, _pUserData, _mask) do{ \
	(_pClkLsn)->pUsrData = (void*)(_pUserData); \
	(_pClkLsn)->pClkListener = _pfn; \
	(_pClkLsn)->nMask = (_mask); \
	(_pClkLsn)->pIClock = NULL; \
	(_pClkLsn)->pNext = NULL; \
}while(0)

#define CLKLISTENER_CANCEL(_pClkLsn) do{\
	if((_pClkLsn)->pIClock) {\
		ICLOCK_CancelListener((_pClkLsn)->pIClock,_pClkLsn); }\
}while(0)

/**
 *  ICLOCK_QueryInterface
 *  @brief  Inherit addref from IBase to query interface. It only support the interface of IClock.
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  nId              Interface ID. In this function, only IID_CLOCK is supported.
 *  @param  pp              Reference to a pointer to a function table if this interface is supported
 *  @param  pOwner			Instance of the object who uses this interface, for reference check.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_NOT_SUPPORTED Not support this interface
 *
 */
#define ICLOCK_QueryInterface(pIClock,nId,pp,pOwner)      GET_FUNCTBL((pIClock),IClock)->QueryInterface(pIClock,nId,pp,pOwner)

/**
 *  ICLOCK_AddListener
 *
 *  @brief  This function adds listener to IClock
 *
 *  @param  pIConfig      [in]Pointer to the IClock interface object
 *  @param  pClkLsn       [in]Pointer to ClockListener_t to register
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 *  @retval MAE_RET_NOT_READY      IClock is not created yet
 */
#define ICLOCK_AddListener(pIClock, pClkLsn)    GET_FUNCTBL((pIClock),IClock)->AddListener(pIClock,pClkLsn)

/**
 *  ICLOCK_CancelListener
 *
 *  @brief  This function cancels listener to IClock
 *
 *  @param  pIConfig      [in]Pointer to the IClock interface object
 *  @param  pClkLsn       [in]Pointer to ClockListener_t to cancel
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_NOT_READY      IClock is not created yet
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 */
#define ICLOCK_CancelListener(pIClock,pClkLsn) GET_FUNCTBL((pIClock),IClock)->CancelListener(pIClock,pClkLsn)


/**
 *  ICLOCK_SetTime
 *  @brief  Set current time. The time is the local time referring to the timezone.
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  pDateTime       Datetime structure.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid datetime format.
 *
 */
#define ICLOCK_SetTime(pIClock,pDateTime)            GET_FUNCTBL(pIClock,IClock)->SetTime(pIClock,pDateTime)


/**
 *  ICLOCK_GetTime
 *  @brief  Get current time. The time is the local time referring to the timezone.
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  pDateTime       Datetime structure.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid parameter.
 *
 */
#define ICLOCK_GetTime(pIClock,pDateTime)            GET_FUNCTBL(pIClock,IClock)->GetTime(pIClock,pDateTime)

/**
 *  ICLOCK_GetTimeRange
 *  @brief  Get current time range. The time is the local time referring to the timezone.
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  pMinDateTime    Datetime structure.
 *  @param  pMaxDateTime    Datetime structure.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid parameter.
 *
 */
#define ICLOCK_GetTimeRange(pIClock,pMinDateTime,pMaxDateTime)            GET_FUNCTBL(pIClock,IClock)->GetTimeRange(pIClock,pMinDateTime,pMaxDateTime)

/**
 *  ICLOCK_GetTimeEx
 *  @brief  Get current time of the gven timezone. The time is the local time referring to the timezone.
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  timeZone        Timezone
 *  @param  pDateTime       Datetime structure.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid parameter.
 *
 */
#define ICLOCK_GetTimeEx(pIClock,timeZone,pDateTime)            GET_FUNCTBL(pIClock,IClock)->GetTimeEx(pIClock,timeZone,pDateTime)

/**
 *  ICLOCK_GetTimeInSeconds
 *  @brief  Get current time. The time is the local time referring to the timezone.
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @return Get the time in seconds since 01/01/1970 at 00:00:00.
 *
 */
#define ICLOCK_GetTimeInSeconds(pIClock)            GET_FUNCTBL(pIClock,IClock)->GetTimeInSeconds(pIClock)


/**
 *  ICLOCK_SetTimeZone
 *  @brief  Set current timezone. Local time would be updated to keep UTC time unchanged.
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  timeZone        Timezone.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid timezone.
 *
 */
#define ICLOCK_SetTimeZone(pIClock,timeZone)            GET_FUNCTBL(pIClock,IClock)->SetTimeZone(pIClock,timeZone)

/**
 *  ICLOCK_SetTimeZoneEx
 *  @brief  Set current timezone to the given timezone field. Local time would be updated to keep UTC time unchanged.
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  timeZoneField   Primary/Secondary timezone field
 *  @param  timeZone        Timezone.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid timezone.
 *
 */
#define ICLOCK_SetTimeZoneEx(pIClock,timeZoneField,timeZone)            GET_FUNCTBL(pIClock,IClock)->SetTimeZoneEx(pIClock,timeZoneField,timeZone)

/**
 *  ICLOCK_GetTimeZone
 *  @brief  Get current timezone value.
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  pTimeZone       Place holder to timezone.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid parameter.
 *
 */
#define ICLOCK_GetTimeZone(pIClock,pTimeZone)            GET_FUNCTBL(pIClock,IClock)->GetTimeZone(pIClock,pTimeZone)

/**
 *  ICLOCK_GetTimeZoneEx
 *  @brief  Get current timezone value of the given timezone field
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  timeZoneField   Primary/Secondary timezone field
 *  @param  pTimeZone       Place holder to timezone.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid parameter.
 *
 */
#define ICLOCK_GetTimeZoneEx(pIClock,timeZoneField,pTimeZone)            GET_FUNCTBL(pIClock,IClock)->GetTimeZoneEx(pIClock,timeZoneField,pTimeZone)

/**
 *  ICLOCK_ConvertToLocalTime
 *  @brief  Convert UTC time to local time
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  pUTCTime        UTC time.
 *  @param  pLocalTime      local time
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid parameter.
 *
 */
#define ICLOCK_ConvertToLocalTime(pIClock,pUTCTime,pLocalTime)            GET_FUNCTBL(pIClock,IClock)->ConvertToLocalTime(pIClock,pUTCTime,pLocalTime)

/**
 *  ICLOCK_ConvertToUTCTime
 *  @brief  Convert local time to UTC time
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  pLocalTime      local time
 *  @param  pUTCTime        UTC time.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid parameter.
 *
 */
#define ICLOCK_ConvertToUTCTime(pIClock,pLocalTime,pUTCTime)            GET_FUNCTBL(pIClock,IClock)->ConvertToUTCTime(pIClock,pLocalTime,pUTCTime)

/**
 *  ICLOCK_GetTimeOffset
 *  @brief  Get the offset for a given time in UTC format at a particular time zone
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  pUTCTime        UTC time
 *  @param  timezone        Timezone
 *  @param  pOffset         offset in seconds
 *  @param  pDst            TRUE if daylight saving time is applied
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid parameter.
 *
 */
#define ICLOCK_GetTimeOffset(pIClock,pUTCTime,timezone,pOffset,pDst)    GET_FUNCTBL(pIClock,IClock)->GetTimeOffset(pIClock,pUTCTime,timezone,pOffset,pDst)

/**
 *  ICLOCK_CheckFactoryTime
 *  @brief  Check and set RTC to factory time
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  pLocalTime      Local factory time
 *  @retval None
 *
 */
#define ICLOCK_CheckFactoryTime(pIClock, pLocalTime)    GET_FUNCTBL(pIClock,IClock)->CheckFactoryTime(pIClock, pLocalTime)

/**
 *  ICLOCK_CheckFactoryTime
 *  @brief  Check and set RTC to factory time
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @param  pLocalTime      Local factory time
 *  @retval None
 *
 */
#define ICLOCK_SetDaylightSavingTime(pIClock, bOnOff)    GET_FUNCTBL(pIClock,IClock)->SetDaylightSavingTime(pIClock, bOnOff)

/**
 *  ICLOCK_AutoBackupTime
 *  @brief  Auto backup current time
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @retval None
 *
 */
#define ICLOCK_AutoBackupTime(pIClock)		GET_FUNCTBL(pIClock,IClock)->AutoBackupTime(pIClock)

/**
 *  ICLOCK_RestoreBackupTime
 *  @brief  Restore to default time
 *
 *  @param  pIClock         Pointer to the IClock interface
 *  @retval None
 *
 */
#define ICLOCK_RestoreBackupTime(pIClock)		GET_FUNCTBL(pIClock,IClock)->RestoreBackupTime(pIClock)

/**
 *  ICLOCK_GetSysDefaultTime
 *  @brief  get default time value.
 *
 *  @param  pIClock               Pointer to the IClock interface
 *  @param  pDefaultTime          Datetime structure.
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_BAD_PARAM Invalid parameter.
 *
 */
#define ICLOCK_GetSysDefaultTime(pIClock,pDefaultTime)            GET_FUNCTBL(pIClock,IClock)->GetSysDefaultTime(pIClock,pDefaultTime)

/**
 * Functions
 */
MAE_Ret MAEClock_New(MAE_ClsId nClsID, void **ppObj);

void MAEClock_Init(void);

#endif /* __MAE_CLOCK_H__ */
