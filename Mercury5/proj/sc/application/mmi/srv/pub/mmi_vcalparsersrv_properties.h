/**
 * @file mmi_vproperties.h
 *
 * @version $Id: mmi_vproperties.h 40145 2009-09-14 06:16:32Z johnson.yeh $
 */
#ifndef __MMI_VCALPARSERSRV_PROPERTIES_H__
#define __MMI_VCALPARSERSRV_PROPERTIES_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/**
 * Constant value definition
 */

/* Day in week */
#define VCALDAY_SUN        0x00000001
#define VCALDAY_MON        0x00000002
#define VCALDAY_TUE        0x00000004
#define VCALDAY_WED        0x00000008
#define VCALDAY_THU        0x00000010
#define VCALDAY_FRI        0x00000020
#define VCALDAY_SAT        0x00000040

/* Week in month */
#define VCALWEEK_FIRST     0x00000000
#define VCALWEEK_SECOND    0x00000001
#define VCALWEEK_THIRD     0x00000002
#define VCALWEEK_FOURTH    0x00000003
#define VCALWEEK_FIFTH     0x00000004
#define VCALWEEK_LAST      0x00000005
#define VCALWEEK_LSECOND   0x00000006   // Second last
#define VCALWEEK_LTHIRD    0x00000007   // Third last
#define VCALWEEK_LFOURTH   0x00000008   // Fourth last
#define VCALWEEK_LFIFTH    0x00000009   // Fifth last

/* Month in the year */
#define VCALMONTH_JAN      0x00000001
#define VCALMONTH_FEB      0x00000002
#define VCALMONTH_MAR      0x00000004
#define VCALMONTH_APR      0x00000008
#define VCALMONTH_MAY      0x00000010
#define VCALMONTH_JUN      0x00000020
#define VCALMONTH_JUL      0x00000040
#define VCALMONTH_AUG      0x00000080
#define VCALMONTH_SEP      0x00000100
#define VCALMONTH_OCT      0x00000200
#define VCALMONTH_NOV      0x00000400
#define VCALMONTH_DEC      0x00000800

#define VCAL_DURATION_DAY                         'D'
#define VCAL_DURATION_HOUR                        'H'
#define VCAL_DURATION_MIN_MON                     'M'
#define VCAL_DURATION_PERIOD                      'P'
#define VCAL_DURATION_SEC                         'S'
#define VCAL_DURATION_TIME                        'T'
#define VCAL_DURATION_WEEK                        'W'
#define VCAL_DURATION_YEAR                        'Y'

#define VCAL_RRULE_MONTHLY                        'M'
#define VCAL_RRULE_BY_DAY                         'D'
#define VCAL_RRULE_YEARLY                         'Y'
#define VCAL_RRULE_WEEKLY                         'W'
#define VCAL_RRULE_DAILY                          'D'

#define VCAL_FRIDAY_FL                           'F'
#define VCAL_FRIDAY_SL                           'R'
#define VCAL_SATDAY_FL                           'S'
#define VCAL_SATDAY_SL                           'A'
#define VCAL_SUNDAY_FL                           'S'
#define VCAL_SUNDAY_SL                           'U'
#define VCAL_TUEDAY_FL                           'T'
#define VCAL_TUEDAY_SL                           'U'
#define VCAL_THUDAY_FL                           'T'
#define VCAL_THUDAY_SL                           'H'
#define VCAL_MONDAY_FL                           'M'
#define VCAL_MONDAY_SL                           'O'
#define VCAL_WEDDAY_FL                           'W'
#define VCAL_WEDDAY_SL                           'E'

#define VCAL_LASTDAY_FL                           'L'
#define VCAL_LASTDAY_SL                           'D'


/* Number of weeks in a month(5+ve weeks and 5 -ve weeks) */
#define VCAL_NR_WEEKS_IN_MONTH              10

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 * Enum value definition
 */

/* Types of properties supported. */
typedef enum
{
    VCALOBJECT_PARAM = 1
   ,VCALOBJECT_PROPERTY
   ,VCALOBJECT_EVENT
   ,VCALOBJECT_CALENDAR
   ,VCALOBJECT_CALPARSER
   ,VCALOBJECT_MAX
} VCALObjectType_e;

/* Properties for vCalendar & vEvent & vTodo */
typedef enum
{
    VCALPROPERTY_GEO
   ,VCALPROPERTY_TIMEZONE
   ,VCALPROPERTY_VERSION
   ,VCALPROPERTY_DAYLIGHT
   ,VCALPROPERTY_PRODID
   ,VCALPROPERTY_ATTACH
   ,VCALPROPERTY_ATTENDEE
   ,VCALPROPERTY_AALARM
   ,VCALPROPERTY_CATEGORIES
   ,VCALPROPERTY_CLASS
   ,VCALPROPERTY_DCREATED
   ,VCALPROPERTY_DCOMPLETED
   ,VCALPROPERTY_DESCRIPTION
   ,VCALPROPERTY_DALARM
   ,VCALPROPERTY_DUE
   ,VCALPROPERTY_DTEND
   ,VCALPROPERTY_EXDATE
   ,VCALPROPERTY_EXRULE
   ,VCALPROPERTY_LASTMODIFIED
   ,VCALPROPERTY_LOCATION
   ,VCALPROPERTY_MALARM
   ,VCALPROPERTY_RNUM
   ,VCALPROPERTY_PRIORITY
   ,VCALPROPERTY_PALARM
   ,VCALPROPERTY_RELATEDTO
   ,VCALPROPERTY_RDATE
   ,VCALPROPERTY_RRULE
   ,VCALPROPERTY_RESOURCES
   ,VCALPROPERTY_SEQUENCE
   ,VCALPROPERTY_DTSTART
   ,VCALPROPERTY_STATUS
   ,VCALPROPERTY_SUMMARY
   ,VCALPROPERTY_TRANSP
   ,VCALPROPERTY_URL
   ,VCALPROPERTY_UID
   ,VCALPROPERTY_EXTENDED
   ,VCALPROPERTY_MAX
} VCALProperty_e;

typedef enum
{
    VCALPARAM_ENCODING
   ,VCALPARAM_CHARSET
   ,VCALPARAM_LANG
   ,VCALPARAM_VALUE
   ,VCALPARAM_TYPE
   ,VCALPARAM_ROLE
   ,VCALPARAM_STATUS
   ,VCALPARAM_RSVP
   ,VCALPARAM_EXPECT
   ,VCALPARAM_MAX
} VCALParameter_e;

typedef enum
{
    VCALCHARSET_ASCII
   ,VCALCHARSET_UTF8
   ,VCALCHARSET_MAX
} VCALCharset_e;

typedef enum
{
    VCALRSVP_FALSE
   ,VCALRSVP_TRUE
   ,VCALRSVP_MAX
} VCALRSVP_e;

typedef enum
{
    VCAL_TYPE_DOM
   ,VCAL_TYPE_INTL
   ,VCAL_TYPE_POSTAL
   ,VCAL_TYPE_PARCEL
   ,VCAL_TYPE_HOME
   ,VCAL_TYPE_PREF
   ,VCAL_TYPE_WORK
   ,VCAL_TYPE_VOICE
   ,VCAL_TYPE_FAX
   ,VCAL_TYPE_MSG
   ,VCAL_TYPE_CELL
   ,VCAL_TYPE_PAGER
   ,VCAL_TYPE_BBS
   ,VCAL_TYPE_MODEM
   ,VCAL_TYPE_CAR
   ,VCAL_TYPE_ISDN
   ,VCAL_TYPE_VIDEO
   ,VCAL_TYPE_AOL
   ,VCAL_TYPE_APPLE
   ,VCAL_TYPE_ATT
   ,VCAL_TYPE_CIS
   ,VCAL_TYPE_EWORLD
   ,VCAL_TYPE_INTERNET
   ,VCAL_TYPE_IBM
   ,VCAL_TYPE_MCM
   ,VCAL_TYPE_PWRSHR
   ,VCAL_TYPE_PRODIGY
   ,VCAL_TYPE_TLX
   ,VCAL_TYPE_X400
   ,VCAL_TYPE_WAVE
   ,VCAL_TYPE_PCM
   ,VCAL_TYPE_AIFF
   ,VCAL_TYPE_GIF
   ,VCAL_TYPE_CGM
   ,VCAL_TYPE_WMF
   ,VCAL_TYPE_BMP
   ,VCAL_TYPE_MET
   ,VCAL_TYPE_PMB
   ,VCAL_TYPE_DIB
   ,VCAL_TYPE_PICT
   ,VCAL_TYPE_TIFF
   ,VCAL_TYPE_PS
   ,VCAL_TYPE_PDF
   ,VCAL_TYPE_JPEG
   ,VCAL_TYPE_MPEG
   ,VCAL_TYPE_MPEG2
   ,VCAL_TYPE_AVI
   ,VCAL_TYPE_QTIME
   ,VCAL_TYPE_VCARD
   ,VCAL_TYPE_MAX_
}VCALType_e;

typedef enum
{
    VCALROLE_ATTENDEE
   ,VCALROLE_ORGANIZER
   ,VCALROLE_OWNER
   ,VCALROLE_DELEGATE
   ,VCALROLE_MAX
} VCALRole_e;

typedef enum
{
    VCALSTATUS_ACCEPTED
   ,VCALSTATUS_ACTION
   ,VCALSTATUS_SENT
   ,VCALSTATUS_TENTATIVE
   ,VCALSTATUS_CONFIRMED
   ,VCALSTATUS_DECLINED
   ,VCALSTATUS_COMPLETED
   ,VCALSTATUS_DELEGATED
   ,VCALSTATUS_MAX
} VCALStatus_e;

typedef enum
{
    VCALEXPECT_FYI
   ,VCALEXPECT_REQUIRE
   ,VCALEXPECT_REQUEST
   ,VCALEXPECT_IMMEDIATE
   ,VCALEXPECT_MAX
} VCALExpect_e;

/**
 * These values have been made mutually exclusive as there can be 
 * multiple values for category.
 */
typedef enum
{
    VCALCATEGORY_APPOINTMENT = 1
   ,VCALCATEGORY_BUSINESS
   ,VCALCATEGORY_EDUCATION
   ,VCALCATEGORY_HOLIDAY
   ,VCALCATEGORY_MEETING
   ,VCALCATEGORY_MISC
   ,VCALCATEGORY_PERSONAL
   ,VCALCATEGORY_PHONE
   ,VCALCATEGORY_SICKDAY
   ,VCALCATEGORY_SPECIAL
   ,VCALCATEGORY_TRAVEL
   ,VCALCATEGORY_VACATION
   ,VCALCATEGORY_ANNIVERSARY
   ,VCALCATEGORY_MAX
} VCALCategory_e;

typedef enum
{
    VCALCLASS_PUBLIC
   ,VCALCLASS_PRIVATE
   ,VCALCLASS_CONFIDENTIAL
   ,VCALCLASS_MAX
} VCALClassification_e;

typedef enum
{
    VCALVALUE_URL
   ,VCALVALUE_URI
   ,VCALVALUE_CID
   ,VCALVALUE_MAX
} VCALValueType_e;

typedef enum
{
    VCALENCODING_BASE64
   ,VCALENCODING_QUOTED_PRINTABLE
   ,VCALENCODING_8_BIT
   ,VCALENCODING_BINARY
   ,VCALENCODING_MAX
} VCALEncoding_e;

enum
{
    VCALFREQUQNCY_OFF
   ,VCALFREQUENCY_DAILY
   ,VCALFREQUENCY_WEEKLY
   ,VCALFREQUENCY_MONTHLY
   ,VCALFREQUENCY_YEARLY
};
typedef u8 VCALFrequency_e;

/**
 * Object structure definition
 */

typedef struct
{
    boolean bDayFlag;       /* ==1 Day light supported */
    s16 nDayOffsetHours;
    s16 nDayOffsetMinutes;
    u32 nStart;          /* number of seconds elapsed from CDMA time */
    u32 nEnd;           /* number of seconds elapsed from CDMA time */
    u8 cStanDesg[8];   /* MUST be NULL terminated */
    u8 cDayDesg[8];    /* MUST be NULL terminated */
} VCALDayLight_t;

typedef struct
{
    double nLongitude;
    double nLatitude;
} VCALGeo_t;

typedef struct
{
    s32 nId;
    u8 *pName;
} vCalEnum_t;

#define VCAL_INITRRULE(x) { \
  (x)->nFrequency = VCALFREQUENCY_DAILY;    \
  (x)->nCount = 0;                          \
  (x)->nInterval = 1;                       \
  MEMSET(&(x)->tEndDate,0,sizeof(VCALUTCDate_t));                    \
  (x)->nMonthInYear = 0;                    \
  MEMSET((x)->nWeekDay,0,10*sizeof(u32));\
  MEMSET((x)->nDayInMonth,0,2*sizeof(s32));\
  (x)->pDayInYear = NULL;                   \
}

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/

#endif /* __MMI_VCALPARSERSRV_PROPERTIES_H__ */
