typedef struct _DSTTimeInfo
{
	INT     uiYear;       /**< Years since 1900 */
    INT     uiMon;        /**< Months since January - [0,11] */
    INT     uiDay;        /**< Day of the month - [1,31] */
    INT     uiHour;       /**< Hours since midnight - [0,23] */
} DSTTimeInfo, *pDSTTimeInfo;

typedef struct _DSTDuration
{
	DSTTimeInfo sStart;
	DSTTimeInfo sEnd;
} DSTDuration, *pDSTDuration;

typedef struct _DSTFullTime
{
    INT     iYear;       /**< Years since 1900 */
    INT     iMon;        /**< Months since January - [0,11] */
    INT     iDay;        /**< Day of the month - [1,31] */
    INT     iHour;       /**< Hours since midnight - [0,23] */
    INT     iMin;        /**< Minutes after the hour - [0,59] */
    INT     iSec;        /**< Seconds after the minute - [0,59] */

} DSTFullTime, *pDSTFullTime;
/*===========================================================================
 * Extern varible
 *===========================================================================*/ 
 extern DSTDuration DST_GMT_P02[7];
 extern DSTDuration DST_GMT_P10[7];
 extern DSTDuration DST_GMT_P00[7];
 extern signed char TimeZoneTable[33];
 
/*===========================================================================
 * Function prototype
 *===========================================================================*/ 
AHC_BOOL AHC_RTC_DSTCheck_GMT(const UINT32 uiYear, const UINT32 uiMon, const UINT32 uiDay, const UINT32 uiHour);
AHC_BOOL AHC_RTC_DSTCheck_UserSet(const UINT32 uiYear, const UINT32 uiMon, const UINT32 uiDay, const UINT32 uiHour);

