/**
 * @file    mmi_common_azan.h
 * @brief   
 *          
 *
 * @author  
 * @version $Id:$
 */
 
#ifndef __MMI_COMMON_AZAN_H__
#define __MMI_COMMON_AZAN_H__

#include "vm_types.ht"
#include "mmi_mae_common_def.h"

#define AZAN_LAT  0
#define AZAN_LONG 1
#define AZAN_PI 3.14159265358979323846

#define ANGLE2CIRCULAR(Angle) ((((Angle)*AZAN_PI)/180))
#define CIRCULAR2ANGLE(Angle) ((((Angle)*180)/AZAN_PI))

enum PrayerMethod
{
    EGYPT_SURVEY = 0,
    KARACHI_SHAF,
    MUSLIM_LEAGUE,
    UMM_ALQURRA,
    NORTH_AMERICA,
    FIXED_ISHAA,
    KARACHI_HANAF,
    NUM_PRAYER_METHOD
};

enum{
    NORTH = 0,
    NORTHWEST,
    WEST,
    SOUTHWEST,
    SOUTH,
    SOUTHEAST,
    EAST,
    NORTHEAST,
};

typedef struct
{
    u32 nDay;
    u32 nMonth;
    u32 nYear;
} Date;

typedef struct
{
    double fLongitude;/* Longitude in decimal degree. */
    double fLatitude; /* Latitude in decimal degree. */
    double fGMT;      /* GMT difference at regular time. */
    bool   bDST;      /* Daylight savings time switch (0 if not used). Setting this to 1 should add 1 hour to all the calculated prayer times */
} Location_t;

/* This structure holds the prayer time output for a single prayer. */
typedef struct 
{
    u32 nHour;
    u32 nMinute;
    u32 nSecond;
    bool bExtremed;
    /* Extreme calculation status. The 'getPrayerTimes' function sets this variable to 1 to indicate that
       this particular prayer time has been calculated through extreme latitude methods and NOT by
       conventional means of calculation. */ 
} Prayer_t;

MAE_Ret AzanGetPrayerTimes(const Location_t *pLocation, u32 nMethod, const Date *pDate, Prayer_t *pPrayerTime);
double AzanGetQiblaDirection(double nLont, double nLagt);
int AzanCalcCompass(double CircularAngle);

#endif /* __MMI_COMMON_AZAN_H__ */
