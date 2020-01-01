/**
 * @file    mmi_common_util.h
 *
 * @brief   This file defines the interface of sms utility functions.
 * @version $Id: mmi_common_util.h 41655 2009-09-29 03:41:03Z christoph.kuo $
 * @author
 *
 */
#ifndef __MMI_COMMON_UTIL_H__
#define __MMI_COMMON_UTIL_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_class.h"
#include "mmi_mae_shell.h"
#include "mmi_cfgsrv.h"
#include "mmi_simsrv.h"
#include "mmi_mae_helper.h"
#include "mmi_common_cfg.h"
#include "mmi_wdg_itf_menu_common.h"
#include "mmi_mae_menumodel.h"
#include "mae_textlabel.h"
#include "mmi_secapp_cfg.h"
#include "mmi_util_rtc.h"
#include "mmi_util_fs.h"
#include "mmi_mae_clock.h"
#include "mmi_wdg_text.h"
#include "mmi_common_lang.h"
#include "mmi_common_content.h"
#include "mmi_mae_filemgr.h"
#include "mmi_mae_view.h"
//#include "mae_doubleitemwidget.h"
#include "mmi_mae_battery.h"
#include "mmi_sys_cfg.h"
#include "mmi_coresrv.h"
#include "mmi_filemgr_util.h"

#ifdef  __G_SENSOR_MMI__
#include "mmi_mae_motiondetector.h"
#endif  /* __G_SENSOR_MMI__ */

#include "mmi_shortcutssrv_cfg.h"
#include "mmi_audioenvsrv.h"
#include "ResMgr_Common.h"
#include "MediaRspItf.h"
#include "MediaCtrlItf.h"

#include "mmi_wdg_overlayimage.h"
#include "mmi_wdg_viewportanim_android.h"
#include "mmi_wdg_viewportanim_iphone.h"
#include "mmi_wdg_viewportanim_boundonly.h"

#define COMMON_NO_SIM_ECC_NUM	6
#define COMMON_DEFAULT_ECC_NUM	2
#define COMMON_IMEI_BUF_SIZE   18

#ifdef __PROGRAM_TEMP_IMEI_MMI__
#define COMMON_SET_IMEI_CMD "*#*#4634*"
#define COMMON_SET_IMEI2_CMD "*#*#46342*"
#endif

extern const u8 COMMON_EMERGENCY_CALL_NUMBER_112[];
extern const u8 COMMON_EMERGENCY_CALL_NUMBER_911[];

extern const u8 COMMON_EMERGENCY_CALL_NUMBER_000[];	// No SIM inserted only
extern const u8 COMMON_EMERGENCY_CALL_NUMBER_08[];	// No SIM inserted only
extern const u8 COMMON_EMERGENCY_CALL_NUMBER_110[];	// No SIM inserted only
extern const u8 COMMON_EMERGENCY_CALL_NUMBER_999[];	// No SIM inserted only
extern const u8 COMMON_EMERGENCY_CALL_NUMBER_118[];	// No SIM inserted only
extern const u8 COMMON_EMERGENCY_CALL_NUMBER_119[];	// No SIM inserted only

#define COMMON_TOTAL_ECC_NUM 	(COMMON_DEFAULT_ECC_NUM + (XMMI_SIM_MAX_ECC_NUM * 2) + MAX_PHONE_ECC_NUM)
#define COMMON_MAX_ECC_LEN 		MAX(XMMI_SIM_MAX_ECC_LEN, MAX_PHONE_ECC_LEN)

#define COMMON_DATE_FORMAT_WITH_YEAR    L"2000/01/01"
#define COMMON_DATE_FORMAT_WITH_YEAR_AND_WEEKDAY    L"2000/01/01 Su"
#define COMMON_DATE_FORMAT_WITH_WEEKDAY L"Su/01/01"
#define COMMON_TIME_FORMAT_24           L"00:00"
#define COMMON_TIME_FORMAT_12           L"00:00 AM"
#define COMMON_ELLIPSIS_STRING          L"..."
#define COMMON_ELLIPSIS_STRING_LEN      3
#define COMMON_LUNAR_FIRSTYEAR          1936 /* The first year in LunarCal[]. */

#define COMMON_SECONDS_PER_MINUTE        60
#define COMMON_MINUTES_PER_HOUR          60
#define COMMON_HOURS_PER_DAY             24
#define COMMON_DAYS_PER_WEEK        7
#define COMMON_MONTHS_PER_YEAR      12
#define COMMON_DAYS_PER_YEAR      365

#define COMMON_DATE_LIMIT_MIN_YEAR  1970
#define COMMON_DATE_LIMIT_MAX_YEAR  2039

#define COMMON_DURATION_INFO_LENGTH      9

#define COMMON_IMEI_NUM_LENGTH      15

#define COMMON_CHINA_SPN_SPECIALPROCESS    TRUE
#define COMMON_CHINA_MCC                   460

//Added for command select language
#define MULTIPLE_LANGUAGE_CODE_LENGTH        (4)
//Added end
#if defined(__UI_STYLE_MMI_MAIN_MENU_ANIMATION__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__)|| defined(__UI_STYLE_FLIPDCLOCK__)|| defined(__UI_STYLE_MMI_ANDROID_KEYGUARD__)
#define COMMON_SPLIT_BITMAP_ROW     3
#define COMMON_SPLIT_BITMAP_COL     3
#endif //#ifdef __UI_STYLE_MMI_MAIN_MENU_ANIMATION__

#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
#define FIND_HIGH_SPEED_TASK_BUFFER (10240 + 100)  //100: software version string length
#endif //__CHECK_CPU_STATUS_BEFORE_SLEEP__

#ifdef __UI_STYLE_FLIPDCLOCK__
#ifndef BREAKIF
#define BREAKIF(a)    {if(MAE_RET_SUCCESS != a) break;}
#endif
#endif
enum
{
	ALERT_DISPLAYTYPE_DIALOG,	// content + "\n" + time
	ALERT_DISPLAYTYPE_KEYGUARD	// time + " " + content
};
typedef u8 AlertDisplayType_e;

enum
{
	WEEKDAY_DISPLAYTYPE_SHORT,
	WEEKDAY_DISPLAYTYPE_LONG,
	WEEKDAY_DISPLAYTYPE_COUNT
};
typedef u8 WeekDayDispType_e;

enum
{
	ROT_INT_ANGLE_15 = 0,
	ROT_INT_ANGLE_30,
	ROT_INT_ANGLE_330,
	ROT_INT_ANGLE_345,
	ROT_INT_TOTAL_NUM
};
typedef u8 RotateIntAngle_e;

#if defined(__UI_STYLE_MMI_MAIN_MENU_ANIMATION__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__)|| defined(__UI_STYLE_FLIPDCLOCK__)|| defined(__UI_STYLE_MMI_ANDROID_KEYGUARD__)
enum
{
    ROT_ANGLE_0 = 0,
	ROT_ANGLE_30,
    ROT_ANGLE_45,
    ROT_ANGLE_60,
    ROT_ANGLE_90,
    ROT_ANGLE_120,
    ROT_ANGLE_135,
    ROT_ANGLE_150,
    ROT_ANGLE_180,
    ROT_TOTAL_NUM
};
typedef u8 RotateAngle_e;

enum
{
    APART_TOP_HALF = 0,
    APART_BOTTOM_HALF,
    APART_LEFT_HALF,
    APART_RIGHT_HALF,
    APART_TOTAL_NUM
};
typedef u8 DestructPortion_e;

#endif //#if defined(__UI_STYLE_MMI_MAIN_MENU_ANIMATION__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__)|| defined(__UI_STYLE_FLIPDCLOCK__)|| defined(__UI_STYLE_MMI_ANDROID_KEYGUARD__)

#ifdef __AUTO_TEST_SCRIPT__
enum
{
    AUTOTEST_BEGIN = 0,
    AUTOTEST_ENTER_IDLE = AUTOTEST_BEGIN,
    AUTOTEST_PHB_READY,
    AUTOTEST_SMS_READY,
    AUTOTEST_END
};
typedef u8 GetTick_e;
#endif

enum {
	DIR_UP = 0,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_OTHER,
	DIR_NUM
};
typedef u8 IADirection_e;

typedef struct
{
    u8 nBaseDays;   /* The cumulative days from 1/1 of a lunar year to 1/1 of a solar year.  */
    u8 nIntercalation; /* Leap month. 0 means no leap month for this year. */
    u8 nBaseWeekday;  // solar day of 1/1 minus 1
    u8 nBaseKanChih;  // solar day of 1/1 KanChih minus 1
    u8 nMonthDays[13]; /* Indicate the days of the twelve months for a lunar year. 0 means small month(29 days). 1 means big month(30 days). */

}  LunarCal_t;

typedef struct
{
    MAE_WChar* pYear;  /* Lunar year string. */
    MAE_WChar* pMonth; /* Lunar month string. */
    MAE_WChar* pDay;   /* Lunar day string. */
    MAE_WChar* pAnimal; /* Animal string */
//    u32 nMonth;
//    u32 nDay;

} LunarDate_t;

typedef struct
{
	u16 nYear;
	u8  nMonth;
	u8  nDay;
	u8  nLeapMonth;   //0 for no-leap month
	u8  nKanIndex;
	u8  nChihIndex;

} CalDate_t;

typedef struct  // City info of world clock
{
    u32       nTzId;            // Timezone id
    u32       nCityNameLblId;   // Textlabel id of city name
} WclkCityInfo_t;

typedef struct COMMON_TotalEccList	//total emergency call list (SIM + Phone)
{
	u8 u8TotalEccNum;
	u8 au8TotalEccList[COMMON_TOTAL_ECC_NUM][COMMON_MAX_ECC_LEN+1];
}COMMON_TotalEccList_t;

/*
Security Code format type:
1. Change PIN1 with old PIN1:
**04*[Old PIN1]*[New PIN1]*[Confirm PIN1]#
**04*12345678*12345678*12345678#

2. Change PIN2 with old PIN2:
**042*[Old PIN2]*[New PIN2]*[Confirm PIN2]#
**042*12345678*12345678*12345678#

3. Change PIN1 with PUK1:
**05*[PUK]*[New PIN1]*[Confirm PIN1]#
**05*12345678*12345678*12345678#

4. Change PIN2 with PUK2:
**052*[PUK2]*[New PIN2]*[Confirm PIN2]#
**052*12345678*12345678*12345678#

*/
#define MAX_SECURITY_CODE_STRING_LEN	33

typedef enum
{
  COMMON_SecurityCodeFormat_Unknow = 0,
  COMMON_SecurityCodeFormat_04,		/* "**04*" */
  COMMON_SecurityCodeFormat_042,	/* "**042*" */
  COMMON_SecurityCodeFormat_05,		/* "**05*" */
  COMMON_SecurityCodeFormat_052  	/* "**052*" */
}COMMON_SecurityCodeFormat_e;


/**
 * \brief Listing all GSM sequence type
 */
typedef enum
{   COMMON_SEQ_USSD,                                    /**< 000: Send USSD                  */

   COMMON_SEQ_ACTCBX,                                  /**< 001: Activate call barring      */
   COMMON_SEQ_DEACBX,                                  /**< 002: Deactivate call barring    */
   COMMON_SEQ_INTCBX,                                  /**< 003: Interrogate call barring   */

   COMMON_SEQ_REGCFX,                                  /**< 004: Register call forwarding   */
   COMMON_SEQ_REGCFX_T,                                /**< 005: Reg. with cond.timer       */
   COMMON_SEQ_ERACFX,                                  /**< 006: Erase call forwarding      */
   COMMON_SEQ_INTCFX,                                  /**< 007: Interrogate call forward   */
   COMMON_SEQ_ACTCFX,                                  /**< 008: Activate call forwarding   */
   COMMON_SEQ_DEACFX,                                  /**< 009: Deactivate call forwarding */

   COMMON_SEQ_ACTCWX,                                  /**< 010: Activate call waiting      */
   COMMON_SEQ_DEACWX,                                  /**< 011: Deactivate call waiting    */
   COMMON_SEQ_INTCWX,                                  /**< 012: Interrogate call waiting   */

   COMMON_SEQ_INTCLX,                                  /**< 013: Interrogate line identif   */

   COMMON_SEQ_CHGSSPWD,                                /**< 014: Change SS password         */
   COMMON_SEQ_CHGPIN1,                                 /**< 015: Change PIN 1               */
   COMMON_SEQ_CHGPIN2,                                 /**< 016: Change PIN 2               */
   COMMON_SEQ_ENTPUK1,                                 /**< 017: Enter PUK 1                */
   COMMON_SEQ_ENTPUK2,                                 /**< 018: Enter PUK 2                */

   COMMON_SEQ_IMEI  ,                                  /**< 019: Display IMEI               */
   COMMON_SEQ_ADN   ,                                  /**< 020: Abreviated Dialing Number  */

   COMMON_SEQ_DN,                                      /**< 021: Directory number           */
   COMMON_SEQ_DN_CLIRON,                               /**< 022: Directory number + CLIR    */
   COMMON_SEQ_DN_CLIRNO,                               /**< 023: Directory number - CLIR    */
   COMMON_SEQ_EMERG,                                   /**< 024: Emergency number           */

   COMMON_SEQ_0_SEND,                                  /**< 025: Zero Send in comm          */
   COMMON_SEQ_1_SEND,                                  /**< 026: One Send in comm           */
   COMMON_SEQ_2_SEND,                                  /**< 027: Two Send in comm           */
   COMMON_SEQ_3_SEND,                                  /**< 028: Three Send in comm         */
   COMMON_SEQ_1X_SEND,                                 /**< 029: One Send in comm           */
   COMMON_SEQ_2X_SEND,                                 /**< 030: Two Send in comm           */
   COMMON_SEQ_ECT,                                     /**< 031: Four Send in comm (ECT)    */
   COMMON_SEQ_CCBS,                                    /**< 032: Five Send in comm (CCBS)   */
   COMMON_SEQ_CD,                                      /**< 033: 4*"DN" Send in comm (CD)   */
   COMMON_SEQ_GPRS_CALL,                               /**< 034:  __GPRS__ CALL             */

   COMMON_SEQ_SPECIFIC,                                /**< 035: Specific manufacturer menu */

   COMMON_SEQ_ACT_SIMLCK,                              /**< 036: Activate SIM lock          */
   COMMON_SEQ_ACT_NETLCK,                              /**< 037: Activate NET lock          */
   COMMON_SEQ_ACT_SNETLCK,                             /**< 038: Activate SUBNET lock       */
   COMMON_SEQ_ACT_SPLCK,                               /**< 039: Activate SP lock           */
   COMMON_SEQ_ACT_CORPLCK,                             /**< 040: Activate Corporate lock    */

   COMMON_SEQ_DEA_SIMLCK,                              /**< 041: Deactivate SIM lock        */
   COMMON_SEQ_DEA_NETLCK,                              /**< 042: Deactivate NET lock        */
   COMMON_SEQ_DEA_SNETLCK,                             /**< 043: Deactivate SUBNET lock     */
   COMMON_SEQ_DEA_SPLCK,                               /**< 044: Deactivate SP lock         */
   COMMON_SEQ_DEA_CORPLCK,                             /**< 045: Deactivate Corporate lock  */

   COMMON_SEQ_WAVECOM_SPECIFIC,                        /**< 046: Production test  */
   COMMON_SEQ_WIFI_SPECIFIC,                           /**< 047: Wifi Production test  */

   COMMON_SEQ_SCBS_INVALID,                            /**< 048: SC or BS code invalid      */
   COMMON_SEQ_INSTALL_JAVA,                            /**< 049: Factory install Java       */
   COMMON_SEQ_RESET_FACTORY_SPECIFIC,                  /**< 050: Specific manufacturer menu */
   COMMON_SEQ_SET_IMEI,							   	   /**< 051: Set IMEI		 			*/
   COMMON_SEQ_SET_IMEI2,							   /**< 052: Set IMEI2				 */

//Added for command select language
   COMMON_SEQ_SPECIFIC_MULTIPLE_LANGUAGE,             /**<select language for diffrent language */
//Added end
   COMMON_SEQ_MAX,

   COMMON_SEQ_ERR_PWD_MISMATCH = 0x80,
   COMMON_SEQ_ERR_SIM_ABSENT,
   COMMON_SEQ_ERR_TOO_LONG,
   COMMON_SEQ_STLK_SS,
   COMMON_SEQ_INCORRECT_LEN_SS_PWD,

   COMMON_SEQ_LOCK_OK,
   COMMON_SEQ_LOCK_KO,

   COMMON_SEQ_INVALID,

   COMMON_SEQ_NO_ACTION = 0xFF                          /**< No Sequence execution */
} COMMON_GSM_SEQ_e;

#define COMMON_TERM_SEND   0
#define COMMON_TERM_HASH   1

#define COMMON_HASH        '#'
#define COMMON_STAR        '*'
#define COMMON_PLUS        '+'
#define COMMON_PAUSE(X)    ( ( (X) == ',' ) || ( (X) == 'p' ) )
#define COMMON_DIGIT(X)    ( ( (X) >= '0' ) && ( (X) <= '9' ) )
#define COMMON_DTMF(X)     (   COMMON_DIGIT(X)      ||                \
                          ( (X) == COMMON_STAR ) ||                \
                          ( (X) == COMMON_HASH ) ||                \
                          ( (X) == 'A'      ) ||                \
                          ( (X) == 'B'      ) ||                \
                          ( (X) == 'C'      ) ||                \
                          ( (X) == 'D'      )                   \
                        )

#define COMMON_SEQ_NONE    0
#define COMMON_SEQ_ACT     1
#define COMMON_SEQ_DEA     2
#define COMMON_SEQ_ERA     3

#define COMMON_IS_SPACE(X)    ( ( (X) == ' ' ))

#define COMMON_BREAKIF_DISPERROR(s,n)							\
									   {						\
									   if(MAE_RET_SUCCESS != n) \
										{						\
										LOG_ERROR(MMI_LEVEL_COMMON, s);			\
										break;					\
										}						\
									  }


typedef enum
{
    COMMON_SEQ_NOT_CL,       /**< No calling line identification             */
    COMMON_SEQ_CLIP,         /**< Calling line identification presentation   */
    COMMON_SEQ_CLIR,         /**< Calling line identification restriction    */
    COMMON_SEQ_COLP,         /**< Connected line identification presentation */
    COMMON_SEQ_COLR          /**< Connected line identification restriction  */
} COMMON_SEQ_CL_e;


typedef enum
{
    COMMON_RIL_ERR_OK=0,				                //OK
    COMMON_RIL_ERR_UNKNOWN_ERROR=1,	                    //unknow error
    COMMON_RIL_ERR_NOT_ALLOWED=3,			            //opearation not allowed
    COMMON_RIL_ERR_NOT_SUPPORTED=4,                     //opearation not support
    COMMON_RIL_ERR_PH_SIM_PIN_REQUIRED=5,               //PH-SIM PIN required(SIM lock)
    COMMON_RIL_ERR_SIM_NOT_INSERTED=10,                 //SIM not inserted
    COMMON_RIL_ERR_SIM_PIN_REQUIRED=11,                 //SIM PIN required
    COMMON_RIL_ERR_SIM_PUK_REQUIRED=12,                 //SIM PUK required
    COMMON_RIL_ERR_SIM_FAILURE=13,                      //SIM failure
    COMMON_RIL_ERR_INCORRECT_PWD=16,		            //password incorrect
    COMMON_RIL_ERR_SIM_PIN2_REQUIRED=17,                //SIM PIN2 required
    COMMON_RIL_ERR_SIM_PUK2_REQUIRED=18,                //SIM PUK2 required
    COMMON_RIL_ERR_NO_NETWORK_SERVICE=30,               //no network service
    COMMON_RIL_ERR_NETWORK_NOT_ALLOWED=32,              //network not allowed - emergency calls only
    COMMON_RIL_ERR_RSLUT_UNKNOWN_ERROR=500,             //Unknown PLMN error
    COMMON_RIL_ERR_INCOMING_CALL_ERROR=520,             //the operation is aborted because of incoming call
    COMMON_RIL_ERR_NETWORK_BUSY=527,                    //Please wait, RR or MM is busy. Try it later.
    COMMON_RIL_ERR_LOC_UPDATE_FAIL=528,                 //Location update failure. Emergency calls only.
    COMMON_RIL_ERR_SEL_FAILED=529,                      //selection failed - emergency calls only
    COMMON_RIL_ERR_NO_EMERGE_CALL=534,                  //Emergency call is not allowed without SIM
    COMMON_RIL_ERR_NO_EMERGE_CALL_WITHOUT_SIM=546,      //Emergency call is not allowed without SIM
    COMMON_RIL_ERR_EMERGE_CALL_WITHOUT_SIM=547,         //Emergency call only without SIM
    COMMON_RIL_ERR_NULL_ERR=998,                        //Response data is NULL
    COMMON_RIL_ERR_INTERNAL_ERR=999                     //Internal error

} COMMON_RIL_ERR_e;

typedef enum
{
	COMMON_TIME_LOCAL,
	COMMON_TIME_REMOTE
} COMMON_Time_Type_e;

typedef enum
{
	COMMON_DATE_WESTEN,
	COMMON_DATE_LUNAR
} COMMON_Date_Type_e;

enum MMI_Common_ScaleType{
    MMI_SCALE_NONE,
    MMI_SCALE_INNER,
    MMI_SCALE_FIT
};
typedef u8  MMI_Common_ScaleType_e;

#ifdef  __G_SENSOR_MMI__
enum _PicOrientation_tag
{
    PIC_ORIENTATION_PORTRAIT,       // my head: up
    PIC_ORIENTATION_LANDSCAPE,       // my head: right
    PIC_ORIENTATION_REV_PORTRAIT,   // my head: down
    PIC_ORIENTATION_REV_LANDSCAPE   // my head: left
};
typedef s8 PicOrientation_e;
#endif  /* __G_SENSOR_MMI__ */

typedef enum
{
	COMMON_SIM_STATUS_NOSIM,
	COMMON_SIM_STATUS_ACTIVE,
	COMMON_SIM_STATUS_INACTIVE

} COMMON_SIM_Status_e;

typedef enum
{
	COMMON_SPN_TYPE_START = 0,
	COMMON_SPN_TYPE_ONS = COMMON_SPN_TYPE_START,
	COMMON_SPN_TYPE_ONS_SHORT,
	COMMON_SPN_TYPE_SPN,
	COMMON_SPN_TYPE_NITZ,
	COMMON_SPN_TYPE_PLMN,
	COMMON_SPN_TYPE_END

} COMMON_SPN_Type_e;

#define COMMON_MAX_SPN_TYPE 6

#if defined(__UI_STYLE_MMI_MAIN_MENU_ANIMATION__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__)|| defined(__UI_STYLE_FLIPDCLOCK__)|| defined(__UI_STYLE_MMI_ANDROID_KEYGUARD__)
enum
{
	PERSPECTIVEDIR_UP,
	PERSPECTIVEDIR_DOWN,
	PERSPECTIVEDIR_LEFT,
	PERSPECTIVEDIR_RIGHT,

	PERSPECTIVEDIR_TOTAL
};
typedef u16 PerspectiveDirection_t;

typedef struct
{
	PerspectiveDirection_t tDir;
	u16 height;
	u16 topWidth;
}PerspectiveParm_t;

typedef struct
{
	s32 x;
	s32 y;
	Rect_t tRcCA;
	PerspectiveParm_t tPerspective;
}Transform_PerspectiveParam_t;
#endif //#ifdef __UI_STYLE_MMI_MAIN_MENU_ANIMATION__

#ifdef __UI_STYLE_FLIPDCLOCK__
typedef struct
{
    PerspectiveDirection_t tDir;
    u16 nheight;
    u16 nSmallWidth;
    u16 nLargeWidth;
}PerspectiveParamEx_t;
#endif

enum
{
	COMMON_EXT_AUDIO_DEVICE_NONE = 0xFF,
	COMMON_EXT_AUDIO_DEVICE_HEADSET = 0,    // Wired headset
	COMMON_EXT_AUDIO_DEVICE_BT,             // Mono Bluetooth headset(HSP/HFP)
	COMMON_EXT_AUDIO_DEVICE_BT_A2DP,        // Stereo Bluetooth headset(A2DP)

    /*--- Add new external audio device before this line ---*/
    COMMON_EXT_AUDIO_DEVICE_NUM,
};
typedef u8 COMMON_ExtAudioDevice_e;

typedef enum
{
    VIEWPORT_ANIM_TYPE_DEFAULT = 0
    ,VIEWPORT_ANIM_TYPE_IPHONE = VIEWPORT_ANIM_TYPE_DEFAULT
    ,VIEWPORT_ANIM_TYPE_ANDROID
    ,VIEWPORT_ANIM_TYPE_BOUNDONLY
    ,VIEWPORT_ANIM_TYPE_NUM
} ViewportAnimType_e;

/**
* MMI_COMMON_IsE2PEnableRSSISmoothAlgorithm
* @brief		Check the smooth algorithm for RSSI is enabled or not.
*
* @retVal		TRUE		Enable smooth algorithm.
* @retVal		FALSE		Disable smooth algorithm.
*/
boolean MMI_COMMON_IsE2PEnableRSSISmoothAlgorithm(void);

/**
* MMI_COMMON_SetE2PRSSISmoothAlgorithm
* @brief		Set the smooth algorithm for RSSI.
*
* @param        bOnOff      Set TRUE to enable, otherwise.
*/
void MMI_COMMON_SetE2PRSSISmoothAlgorithm(boolean bOnOff);

/**
* MMI_Common_IsLeapYear
* @brief	Check if the solar year is leap.
*
* @param	nYear	(xxxx)eg. 1978
*
* Return FALSE means a non-leap year.
* Return TRUE means a leap year.
*/
boolean MMI_Common_IsLeapYear(u32 nYear);

/**
* MMI_COMMON_GetTotalEccList
* @brief		Get total emergency call number list from SIM and Phone.
*
* @param	pThis		The pointer of the caller.
* @param	pTotalEccList	Return Ecc list data.
*/
MAE_Ret MMI_COMMON_GetTotalEccList(IBase* pThis, COMMON_TotalEccList_t* pTotalEccList);

/**
* MMI_COMMON_ConfigEccListItemsForMenuModel
* @brief		Add Ecc list items into menu model for emergency call list menu. Caller should set menu first item and focus item by himself.
*
* @param	pThis			The pointer of caller.
* @param	pIMenuWdg		The pointer of menu widget.
* @param	ModelItemFreeFunc	Free function for model item.
* @param	pEccList			The pointer for storing Ecc list.
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_SUCCESS	Config Ecc list done.
*/
MAE_Ret MMI_COMMON_ConfigEccListItemsForMenuModel(IBase* pThis, IWidget *pIMenuWdg, PfnModelFree ModelItemFreeFunc,  COMMON_TotalEccList_t* pEccList);

/**
* MMI_Common_GetDateString
* @brief		Get date string based on the current date format.
*
* @param	pThis				The pointer of caller.
* @param	pDate				The pointer for passing the date to be formated.
* @param	bIsWithWeekDay		Decide whether or not to display the date string with week day.
* @param	eWeekDayDispType	Decide to use short/long name to display the week day string if require to display.
* @param	ppDateStr			The pointer for storing the formated date string.
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get date string done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_GetDateString(IBase* pThis, MAE_DateTime_t* pDate, boolean bIsWithWeekDay, WeekDayDispType_e eWeekDayDispType, MAE_WChar** ppDateStr);

/**
* MMI_Common_GetTimeString
* @brief		Get time string based on the current time format.
*
* @param	pThis			The pointer of caller.
* @param	pTime			The pointer for passing the time to be formated.
* @param	ppTimeStr		The pointer for storing the formated time string.
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get time string done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_GetTimeString(IBase* pThis, MAE_DateTime_t* pTime, MAE_WChar** ppTimeStr);

/**
* MMI_Common_GetDateTimeString
* @brief		Get date + time string based on the current time format.
*
* @param	pThis				The pointer of caller.
* @param	pDateTime			The pointer for passing the time to be formated.
* @param	bIsWithWeekDay		Decide whether or not to display the date string with week day.
* @param	eWeekDayDispType	Decide to use short/long name to display the week day string if require to display.
* @param	ppDateTimeStr		The pointer for storing the formated time string.
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get time string done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_GetDateTimeString(IBase* pThis, MAE_DateTime_t* pDateTime, boolean bIsWithWeekDay, WeekDayDispType_e eWeekDayDispType, MAE_WChar** ppDateTimeStr);

/**
* MMI_Common_GetLunarDateString
* @brief		Get lunar date string based on the input solar date.
*
* @param	pSolarDate			The pointer for passing the solar date.
* @param	ppLunarDateStr		The pointer for storing the lunar date string.
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get lunar date string done.
*/
MAE_Ret MMI_Common_GetLunarDateString(MAE_DateTime_t* pSolarDate, MAE_WChar** ppLunarDateStr);


/**
* MMI_Common_ConvertMaeDateToCalDate
* @brief		Converter MaeDate to CalDate
*
* @param	pMaeDate			The pointer for passing the MaeDate
* @param	pCalDate		    The pointer for storing the CalDate
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get lunar date string done.
*/
void MMI_Common_ConvertMaeDateToCalDate(MAE_DateTime_t* pMaeDate, CalDate_t* pCalDate);

/**
* MMI_Common_ConvertMaeDateToCalDate
* @brief		Converter MaeDate to CalDate
*
* @param	pCalDate			The pointer for passing the CalDate
* @param	pMaeDate		    The pointer for storing the MaeDate
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get lunar date string done.
*/
void MMI_Common_ConvertCalDateToMaeDate(CalDate_t* pCalDate, MAE_DateTime_t* pMaeDate);

/**
* MMI_Common_GetLunarMonthDays
* @brief		Get days for the lunar date
*
* @param	pLunarDate			The pointer for passing the lunar date (only take into account of Lunar year, month, and leap month)
* @param	pNumDays		    The pointer for storing number of days for that Lunar year month
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get lunar date string done.
*/
MAE_Ret MMI_Common_GetLunarMonthDays(CalDate_t* pLunarDate, u8* pNumDays);


/**
* MMI_Common_GetLeapMonth
* @brief		Get leap month for the lunar date
*
* @param	pLunarDate			The pointer for passing the lunar date (only take into account of Lunar year, month, and leap month)
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get lunar date string done.
*/
MAE_Ret MMI_Common_GetLeapMonth(CalDate_t* pLunarDate);

/**
* MMI_Common_SolarToLunar
* @brief		Convert solar date to lunar date
*
* @param	pSolarDate			The pointer for passing the solar date
* @param	pLunarDate		    The pointer for storing the lunar date
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get lunar date string done.
*/
MAE_Ret MMI_Common_SolarToLunar(CalDate_t* pSolarDate, CalDate_t* pLunarDate);

/**
* MMI_Common_LunarToSolar
* @brief		Convert lunar date to solar date
*
* @param	pLunarDate			The pointer for passing the lunar date
* @param    pSolarDate          The pointer for stroing the solar date
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get lunar date string done.
*/
MAE_Ret MMI_Common_LunarToSolar(CalDate_t* pLunarDate, CalDate_t* pSolarDate);

/**
* MMI_Common_GetTimeZoneCityString
* @brief    Get city name of given timezone.
*
* @param    MAE_TimeZone_e  The pointer of caller.
* @param    ppStr           The pointer for storing the city name string.
*
* @retVal   MAE_RET_BAD_PARAM       Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Out of memory.
* @retVal   MAE_RET_SUCCESS         Get city name string done.
*/
MAE_Ret MMI_Common_GetTimeZoneCityString(MAE_TimeZone_e eTimeZone, MAE_WChar **ppStr);

/**
* MMI_Common_ParseCityNameFromTimeZone
* @brief    parse city name from timezone with city
*
* @param    pSrcStr    The pointer of source string.
* @param    ppDestStr  The pointer for storing the city name string.
*
* @retVal   MAE_RET_BAD_PARAM       Invalid parameters.
* @retVal   MAE_RET_FAILED          parse failed.
* @retVal   MAE_RET_NOT_FOUND       Not found.
* @retVal   MAE_RET_OUT_OF_MEMORY   Out of memory.
* @retVal   MAE_RET_SUCCESS         Parse city name string done.
*/
MAE_Ret MMI_Common_ParseCityNameFromTimeZone(MAE_WChar *pSrcStr, MAE_WChar **ppDestStr);

/**
* MMI_Common_ParseSIMSecurityCode
* @brief		Check if input string is SIM security code format and return format type.
*
* @param	pstrInput		The pointer of input string.
*
*@retval		COMMON_SecurityCodeFormat_Unknow		Input string is not SIM security code format.
*@retval		COMMON_SecurityCodeFormat_04			Input string is  Change PIN1 with old PIN1 format.
*@retval		COMMON_SecurityCodeFormat_042			Input string is  Change PIN2 with old PIN2 format.
*@retval		COMMON_SecurityCodeFormat_05			Input string is  Change PIN1 with PUK1 format.
*@retval		COMMON_SecurityCodeFormat_052			Input string is  Change PIN2 with PUK2 format.
*/
COMMON_SecurityCodeFormat_e MMI_Common_ParseSIMSecurityCode(u8* pstrInput);



/**
* MMI_Common_ParseGsmSeq
* @brief		Check input string format and return format type.
*
* @param	Sequence		The pointer of input string.
* @param	send		    Is end with SEND key or not.
*
*@retval		COMMON_GSM_SEQ_e.
*/
u8 MMI_Common_ParseGsmSeq(const u8 * Sequence, boolean send,  boolean bInACall, boolean bSIMInserted);


/**
* MMI_Common_GetRILErrorCause
* @brief    Get error string pointer.
*
* @param	errorCode			ATI +CME error code.
*
* @retVal		Return pointer to error string.
*/
MAE_WChar* MMI_Common_GetRILErrorCause(u16 errorCode);

/**
* MMI_Common_ConvertDuration
* @brief		Convert the total time of a media file to time format, like 00:00:00.
*
* @param	nDuration		The pointer for passing the time to be formated.
* @param	pDuration		The pointer for storing the formated time string.
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal		MAE_RET_SUCCESS	Get time format string done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_ConvertDuration(u32 nDuration, MAE_WChar** pDuration);

/**
* MMI_Common_CheckTextPixelWidth
* @brief	Get text pixel width with given font size and fount type
*
* @param	pThis			The pointer of caller
* @param	pWCharText		The pointer of text to calculate
* @param	pPixelWidth		The pointer for storing the pixel width
* @param	nFontCat		Font category (refer to mae_font.h)
* @param	nFontSize		Font size
* @param	nFontType		Font type (refer to mae_font.h)
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal	MAE_RET_SUCCESS			Calculate text pixel with done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_CheckTextPixelWidth(IBase *pThis, MAE_WChar *pWCharText, u32 *pPixelWidth, u32 nFontCat, u32 nFontSize, u32 nFontType);

/**
* MMI_Common_SetWidgetTextToFit
* @brief		Set widget size of given widget (text widget) to fit given text width
*
* @param	pThis			The pointer of caller
* @param	pIWidget		The pointer of widget (text widget)
* @param	pstrTxt			The pointer of text to set into widget (text widget)
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal	MAE_RET_SUCCESS			Set text into widget done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_SetWidgetTextToFit(IBase *pThis, IWidget *pIWidget, MAE_WChar *pstrTxt);

/**
* MMI_Common_GetWidgetTextWidth
* @brief		Get the width in pixels of the text in a text widget
*
* @param	pThis			The pointer of caller
* @param	pIWidget		The pointer of widget (text widget)
* @param	pstrTxt			The pointer of text to set into widget (text widget)
* @param    pWidth          A pointer to a u32 buffer to get the text width in pixels
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal	MAE_RET_SUCCESS			Set text into widget done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_GetWidgetTextWidth(IBase *pThis, IWidget *pIWidget, MAE_WChar *pstrTxt, u32 *pWidth);

/**
* MMI_Common_SetDateWidget
* @brief	Set current date text string into given widget (text widget)
*
* @param	pThis			The pointer of caller
* @param	pDateWidget		The pointer of widget (text widget)
* @param	eWeekDayDispType	Decide to use short/long name to display the week day string if require to display.
* @param	nType			Date type (refer to COMMON_Date_Type_e)
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal	MAE_RET_SUCCESS			Set current date text into widget done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_SetDateWidget(IBase *pThis, IWidget *pDateWidget, WeekDayDispType_e eWeekDayDispType, COMMON_Date_Type_e nType);

/**
* MMI_Common_SetDateWidget
* @brief	Set current time text string into given widget (text widget)
*
* @param	pThis			The pointer of caller
* @param	pTimeWidget		The pointer of widget (text widget) for time text string
* @param	p12HWidget		The pointer of widget (text widget) for AM/PM text string
* @param	nType			Time type (refer to COMMON_Time_Type_e)
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal	MAE_RET_SUCCESS			Set current time text into widget done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_SetTimeWidget(IBase *pThis, IWidget *pTimeWidget, IWidget *p12HWidget, COMMON_Time_Type_e nType);


/**
* MMI_Common_ConvertKeyCode
* @brief	Convert MAE event key code to ascii code
*
* @param	MAE_KeyCode			MAE keycode. (EX. MAE_KEY_1)
*
* @retVal	u8		Ascii code. (EX. 0x31)
*
*/
u8	MMI_Common_ConvertKeyCode(u32 MAE_KeyCode);

/**
* MMI_Common_ParseIMEICode
* @brief	Check the input string is *#06# string
*
* @param	pstrInput			The input string pointer
*
* @retVal	boolean			TURE			The input string is *#06#
											FALSE		The input string is not *#06#
*
*/
boolean MMI_Common_ParseIMEICode(u8* pstrInput);

/**
* MMI_Common_Parse_ProductTestCode
* @brief	Check the input string is *#*0* string
*
* @param	pstrInput			The input string pointer
*
* @retVal	boolean			TURE			The input string is *#*0*
											FALSE		The input string is not *#*0*
*
*/
boolean MMI_Common_Parse_ProductTestCode(u8* pstrInput);

u8 MMI_Common_SeqIsMinMaxDigits( const u8 *ptr, u8 min, u8 max );
#ifdef __PROGRAM_TEMP_IMEI_MMI__
void MMI_Common_SetIMEICode(u8 *pIMEI, MAE_DualMode_t eDualMode);
#endif
void MMI_Common_GetIMEICode(MAE_WChar **pOutputText);
void MMI_Common_GetSoftWareVersion(MAE_WChar **pOutputText);

/**
* MMI_Common_UpdateWallpaper
* @brief	Set widget background with wallpaper setting
*
* @param	pThis			The pointer of caller
* @param	pBGWidget		The pointer of widget
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_OUT_OF_MEMORY	Out of memory.
* @retVal	MAE_RET_SUCCESS			Set wallpaper setting done.
*/
MAE_Ret MMI_Common_UpdateWallpaper(IBase *pThis, IWidget *pBGWidget);

__SLDPM_FREE__ MAE_Ret MMI_Common_GetUrlByCfgItemId(IBase* pOwner, CFGItemID_e eCFGItemID, boolean bUseDefaultIfNotExist, MAE_WChar **ppUrl);

/**
* MMI_COMMON_IsEccNumber
* @brief		Check if input string is an emergency call number.
*
* @param	pThis		The pointer of the caller.
* @param	pInputStr		Input string.
*
* @retVal		TRUE	Input string is an emergency call number.
* @retVal		FALSE	Input string is not an emergency call number.
*/
boolean MMI_COMMON_IsEccNumber(IBase* pThis, u8* pInputStr);

/**
* MMI_Common_GetRemainingEntityLength
* @brief	Calculate the remaining (max) length of the entity
*
* @param	pFolder		The pointer to MAE_WCHAR string (the full folder name with the end "/", like "fs:/card/music/")
* @param	pNLen		The available length of the entity
* @param   bIsFolder  Indicate if the entity is folder
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_Ret MMI_Common_GetRemainingEntityLength(MAE_WChar *pFolder, u32 *pNLen, boolean bIsFolder);

/**
* MMI_Common_GetRemainingMasterFilenameLength
* @brief	Calculate the remaining (max) length of the master file name.
*
* @param	pFolder		The pointer to MAE_WCHAR string (the full path file name, like "fs:/card/music/test.mp3")
* @param	pNLen		The available length of the fullpath
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_Ret MMI_Common_GetRemainingMasterFilenameLength(MAE_WChar *pFullPath, u32 *pNLen, boolean bIsFolder);

/**
* MMI_Common_ResetCalibrationSetting
* @brief	Delete the calibration setting file
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_Ret MMI_Common_ResetCalibrationSetting(void);

/**
* MMI_Common_EnableHwHotKey
* @brief	Enable/disable HW hot key.
*
* @param	pThis		Caller object pointer.
* @param	bEnable		TRUE for enable; FALSE for disable.
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS		Success done.
*/
MAE_Ret MMI_Common_EnableHwHotKey(IBase *pThis, boolean bEnable);

/**
* MMI_Common_EnableTouchHotKey
* @brief	Enable/disable Touch hot key.
*
* @param	pThis		Caller object pointer.
* @param	bEnable		TRUE for enable; FALSE for disable.
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS		Success done.
*/
MAE_Ret MMI_Common_EnableTouchHotKey(IBase *pThis, boolean bEnable);

/**
* MMI_Common_RequestBacklight
* @brief		To turn on/off backlight.
*
* @param	pThis	The pointer of caller object.
* @param	bTurnOn	True for turn on backlight; False for turn off backlight.
* @param	bAlwaysOn	True to backlight always on; False for default duration.
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS		Success done.
*/
MAE_Ret MMI_Common_RequestBacklight(IBase *pThis, boolean bTurnOn, boolean bAlwaysOn);

/**
* MMI_Common_RequestBacklightEx
* @brief		To turn on/off backlight.
*
* @param	pThis	The pointer of caller object.
* @param	bTurnOn	True for turn on backlight; False for turn off backlight.
* @param	bAlwaysOn	True to backlight always on; False for default duration.
* @param	bIsKeypadLightAutoOff	True to auto turn off keypad light only when the LCD backlight is always on; False for not to auto turn off keypad light when the LCD backlight is always on.
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS		Success done.
*/
MAE_Ret MMI_Common_RequestBacklightEx(IBase *pThis, boolean bTurnOn, boolean bAlwaysOn, boolean bIsKeypadLightAutoOff);

/**
* MMI_Common_GetDownWdgByWIDFromView
* @brief	Get down widget of double item widget which is get from view through widget id.
*
* @param	pIView		The pointer of caller object.
* @param	id			Widget id for view.
* @param	ppDownWdg	Pioint to the pointer of IWidget to store the down widget pointer.
* @param	pOwner		The pointer of caller object.
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_Ret MMI_Common_GetDownWdgByWIDFromView(IView *pIView, u16 id, IWidget **ppDownWdg, IBase *pOwner);


/**
* MMI_Common_SlideTextWdgText
* @brief	Slide the text widget text if the text length exceeds the widget width no matter if the text widget is
*           currently onfocus or not.
*
* @param	pITextWdg	The pointer of the text widget
* @param	nAlignment	u32 alignment mask. Please refer to Alignment_e in mae_widget_properties.h
*/
__SLDPM_FREE__ void MMI_Common_SlideTextWdgText(IWidget *pITextWdg, u32 nAlignment);

/**
* MMI_Common_SavePowerOnOffCause
* @brief		To save the cause and status of power on/off.
*
* @param	pOwner	The pointer of caller object.
* @param	eType	Type On or Off.
* @param	eCause	The cause for eType.
*/
void MMI_Common_SavePowerOnOffCause(IBase *pOwner, ONOFF_Type_e eType, ONOFF_Cause_e eCause);

void MMI_Common_ReadPowerOnOffCauseFromRAI(IBase *pOwner, ONOFF_Record_List_t* stRecordList, u32* nListSize);


/**
* MMI_Common_CopyPowerOnOffCauseFromRAIToSD
* @brief	To copy the cause and status of power on/off from RAI to SD card.
*
* @param	pOwner	The pointer of caller object.
*/
void MMI_Common_CopyPowerOnOffCauseFromRAIToSD(IBase *pOwner);


#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
MAE_Ret MMI_Common_StoreHighSpeedTtasktoSD(IBase *pOwner,MAE_WChar *pOutputText);
MAE_Ret MMI_Common_GetHighSpeedTaskStr(IBase *pOwner, MAE_WChar **ppOutputText);
#endif

/**
* _MMI_Common_SaveSystemDebugInfo
* @brief    To Save system debug information.
*
* @param    pOwner    The pointer of caller object.
* @param    isDump    Perforce dump to SD/TMT or not.
*/
void MMI_Common_SaveSystemDebugInfo(IBase *pOwner, bool isDump);

/**
* MMI_Common_StrTrim
* @brief		To trim the space characters in head and tail of string.
*
* @param	dest	The destination string.
* @param	src	    The source string.
* @retVal	        The pointer of space trimmed string.
*/
u8* MMI_Common_StrTrim(u8* dest, u8* src);


MAE_Ret MMI_Common_GetDetermineSPNwithPriority(IBase *pThis, COMMON_SPN_Type_e nCurrentType, boolean bRoaming, u8 nDualMode, MAE_WChar **ppSPNName);
MAE_Ret MMI_Common_GetSPNName(IBase *pThis, COMMON_SPN_Type_e nSPNType, u8 nDualMode, MAE_WChar **ppSPNName);

/**
* MMI_Common_If_InFactoryMode
* @brief		To check if in factory mode.
*
* @retVal	        TRUE	--->	In factory mode.
*			 FALSE	--->	In business mode.
*/

boolean MMI_Common_If_InFactoryMode(void);
void MMI_Common_Reset_FactoryMode(void);

/**
* MMI_Common_Is_PreferNetwork
* @brief		To check if use prefer network.
*
* @retVal       TRUE      --->  Test network.
*               FALSE     --->  Normal mode.
*/
#ifdef __NOSIM_CAMP_ON_TEST_NETWORK__
boolean MMI_Common_Is_PreferNetwork(void);
#endif

/**
* MMI_Common_If_CFUQuery
* @brief		To check if need to send CFU query.
*
* @retVal	 TRUE	--->	Yes.
*			 FALSE	--->	No.
*/
boolean MMI_Common_If_CFUQuery(void);


/**
* MMI_Common_If_InMpReleaseMode
* @brief		To check if in MP release mode
*
* @retVal	 TRUE	--->	Yes.
*			 FALSE	--->	No.
*/
boolean MMI_Common_If_InMpReleaseMode(void);

/**
* MMI_Common_Set_MpReleaseMode
* @brief		Set MP release mode or not
*
* @param	nMode	Set MP release mode.
*
*/
void MMI_Common_Set_MpReleaseMode(u8 nMode);

///////////////////////////////////////////////////////////////
/* Count the number of digits of an integer. */
#ifndef COUNT_DIGITS
#define COUNT_DIGITS(nInteger, nLength) { \
    u32 nTemp; \
    nTemp = (nInteger); \
    nLength = 0; \
    do { \
    nTemp /=10; \
    nLength++; \
    } while(0 != nTemp); \
}
#endif

/*  - MMI_Common_GetImageDecodeSizeToFit
    desc:
        scale the image size to fit the image rect
    argu:
        pImage: the image pointer
        nType: scale type (inner or resize to fit)
        nWidth: destination size (in portrait)
        nHeight: destination size (in portrait)
        pnNewWidth: new width (in portrait)
        pnNewHeight: new height (in portrait)
        nDecAngle: to be decoded angle
        bSetImageSize: scale the image directly?

    return:
        MAE_RET_BAD_PARAM - image is null. dest width or height is zero
        MAE_RET_FAILED - scale failed
        MAE_RET_SUCCESS - ok.
*/
MAE_Ret MMI_Common_GetImageDecodeSizeToFit(IImage                   *pImage,
                                           MMI_Common_ScaleType_e   nType,
                                           u32                      nFitWidth,
                                           u32                      nFitHeight,
                                           u32                      *pnNewWidth,
                                           u32                      *pnNewHeight,
                                           ImgDecAngle_t            nDecAngle,
                                           boolean                  bSetImageSize);

#ifdef  __G_SENSOR_MMI__
void MMI_Common_GetDecAngle(ORIENTATION_e nDispOrientation, ORIENTATION_e nBaseOrientation, ImgDecAngle_t *pnDecAngle);
#endif  /* __G_SENSOR_MMI__ */


MAE_Ret MMI_Common_InitialSPN(IBase *pThis, IWidget *pINetworkWdg_Master, IWidget *pINetworkWdg_Slave);
MAE_Ret MMI_Common_UpdateSPN(IBase *pThis, u8 nDualMode, IWidget *pINetworkWdg);
MAE_Ret MMI_Common_DetermineSPNwithPriority(IBase *pThis, COMMON_SPN_Type_e nCurrentType, boolean bRoaming, u8 nDualMode, IWidget *pINetworkWdg);
COMMON_SPN_Type_e MMI_Common_MapSPNTypebySimFile(SIMSRV_SIM_FILE_ID_e nSimFileID);
MAE_Ret MMI_Common_SetSPNName(IBase *pThis, COMMON_SPN_Type_e nSPNType, u8 nDualMode, IWidget *pINetworkWdg);
void MMI_Common_ReadSIMSPNName(IBase *pThis, u8 nDualMode, SIMSRV_FileReadCnf_t *SimFileReadCnf, IWidget *pINetworkWdg);
__SLDPM_FREE__ MAE_Ret MMI_Common_GetSIMStatus(IBase *pThis, u8 *pMasterStatus, u8 *pSlaveStatus);

MAE_Ret MMI_Common_MeasureText(IDisplay *pIDisplay,
                                                         u32 FonCat,          // Input: Font category, Get PROP_WDG_FONT_CATE
                                                         u32 nFontSize,
                                                         u32 FontType,        // Input: Font type, Get PROP_WDG_FONT_TYPE form text widget
                   									     MAE_WChar* pwText,   // Input: Text
                    									 u32 nTextLen,        // Input: Text Len
                    									 u32 nWidth,          // Input: Width to fit in
                    									 boolean bAlignFirst,       //Input: Align First
                    									 boolean bBreakOnWord,      //Input: Break on word
                    									 boolean bEllipsis,         //Input: Is Last line and show ellipsis if the string can't show compliete
                    									 u32 *pnFits,               //Output: number of char that could show (doesn't include the ellipsis)
                      									 u32 *pnPix,                //Output: number of pixcel (doesn't include the ellipsis)
                      									 u32 *pnEllipsis            //Output: number of pixcel for ellipsis string "..."
                      									 );

MAE_Ret MMI_Common_MeasureEllipsis( IDisplay *pIDisplay, u32 u32FonCat,u32 nFontSize, u32 u32FontType, u32 *pu32Width );

#ifdef	__FEATURE_POWER_CONSUMPTION_LOG__
/*-------------------------------------------------------------------------*/
#define __MMI_DIRECT_WRITE_POW_CONT_LOG__

#ifdef __MMI_DIRECT_WRITE_POW_CONT_LOG__
void _MMI_Common_WritePowContLogtoSD(IBase *pOwner, int level, char *strFormat, ...);
#define MMI_LOG_POWER_CONSUMPTION_TEST(_powner, _level_, _format_, ...) _MMI_Common_WritePowContLogtoSD(_powner, _level_, _format_, ##__VA_ARGS__)
#else//__MMI_DIRECT_WRITE_POW_CONT_LOG__
#define MMI_LOG_POWER_CONSUMPTION_TEST(_powner, _level_, _format_, ...) LOG_POWER_CONSUMPTION_TEST(_level_, _format_, ##__VA_ARGS__)
#endif//__MMI_DIRECT_WRITE_POW_CONT_LOG__

//Power Consumption Log

typedef enum
{
		COMMON_POW_CONS_STATE_POWER_ON
		,COMMON_POW_CONS_STATE_POWER_OFF
		//,COMMON_POW_CONS_STATE_PERIODIC
		,COMMON_POW_CONS_STATE_MUSIC_IN
		,COMMON_POW_CONS_STATE_MUSIC_OUT
		,COMMON_POW_CONS_STATE_CAMERA_IN
		,COMMON_POW_CONS_STATE_CAMERA_OUT
		,COMMON_POW_CONS_STATE_VIDEO_IN
		,COMMON_POW_CONS_STATE_VIDEO_OUT
		,COMMON_POW_CONS_STATE_CALL_IN
		,COMMON_POW_CONS_STATE_CALL_OUT
		,COMMON_POW_CONS_STATE_FM_IN
		,COMMON_POW_CONS_STATE_FM_OUT
		,COMMON_POW_CONS_STATE_BT_PAIR_START
		,COMMON_POW_CONS_STATE_BT_PAIR_CNF
		,COMMON_POW_CONS_STATE_BT_INQUIRY_START
		,COMMON_POW_CONS_STATE_BT_INQUIRY_END
		,COMMON_POW_CONS_STATE_CHARGER_IN
		,COMMON_POW_CONS_STATE_CHARGER_OUT
		//,COMMON_POW_CONS_STATE_NET_DEF_SIM_IN
		//,COMMON_POW_CONS_STATE_NET_DEF_SIM_OUT
		,COMMON_POW_CONS_STATE_NET_SIM1_IN
		,COMMON_POW_CONS_STATE_NET_SIM1_OUT
		,COMMON_POW_CONS_STATE_NET_SIM2_IN
		,COMMON_POW_CONS_STATE_NET_SIM2_OUT
		,COMMON_POW_CONS_STATE_ALARM_IN
		,COMMON_POW_CONS_STATE_ALARM_OUT
		,COMMON_POW_CONS_STATE_LCM_ON
		,COMMON_POW_CONS_STATE_LCM_OFF
		,COMMON_POW_CONS_STATE_CDWAP_ON
		,COMMON_POW_CONS_STATE_CDWAP_OFF
} COMMON_POW_CONS_STATE_et;


typedef union
{
	LCDSrv_BacklightLevel_e eBacklightLevel;
	u8 u8Volume;
} PowContInfo_ut;






/**
* _MMI_Common_If_Pow_Cons_Log_Enable
*
* @brief  This function is used to notify driver to write power consumption log to SD .
*
* @param  void
*
* @retval boolean
*/
boolean _MMI_Common_If_Pow_Cons_Log_Enable(IBase* pOwner);


#ifndef __MMI_DIRECT_WRITE_POW_CONT_LOG__
/**
* _MMI_Common_SendCmdtoWritePowContLogtoSD
*
* @brief  This function is used to notify driver to write power consumption log to SD .
*
* @param  void
*
* @retval NONE
*/
void _MMI_Common_SendCmdtoWritePowContLogtoSD(void);
#endif//__MMI_DIRECT_WRITE_POW_CONT_LOG__


/**
* MMI_Common_LogPowContInfo
*
* @brief  This function is used to record information for handling power consumption issue.
*
* @param  pOwner           								[in]Pointer to the IDisplay Object
* @param  COMMON_POW_CONS_LOG_STATE_et    [in]Notice log state
*
* @retval NONE
*/
void MMI_Common_LogPowContInfo(IBase* pOwner,
											COMMON_POW_CONS_STATE_et ePowContState,
											IAUDIOENVSRV *pIAudioEvnSrv,
											PowContInfo_ut *puPowContInfo);

#endif//__FEATURE_POWER_CONSUMPTION_LOG__

/*-------------------------------------------------------------------------*/

/**
* MMI_Common_GetSTKTitleName
* @brief	Get STK title name
*
* @param	pThis			The pointer of caller
* @param	nSIMType		SIM type (DUAL_MASTER/DUAL_SLAVE)
*
* @retVal	STK title string in MAE_WChar* type
*/
MAE_WChar * MMI_Common_GetSTKTitleName(IBase *pThis, u8 nSIMType);

/**
* MMI_Common_IsSwitchModeAvailable
* @brief	Check is Switch mode item should be shown or disable
*
* @param	pThis			The pointer of caller
*
* @retVal	TURE			Switch mode item can be shown
*			FALSE			Switch mode item is not available (only insert one sim card)
*/
boolean MMI_Common_IsSwitchModeAvailable(IBase *pThis);

/**
* MMI_Common_CheckAPFuncAvailability
* @brief	Check the given shortcut funcion id availability (according to compile option)
*
* @param	pThis				The pointer of caller
* @param	eShortcutsFuncId	Shortcut function id (refer to mmi_shortcutssrv_cfg.h)
*
* @retVal	TURE				The shortcut function id is available
*			FALSE				The shortcut function id is not available
*/
boolean MMI_Common_CheckAPFuncAvaibility(IBase *pThis, ShortcutsFuncId_e eShortcutsFuncId);

/**
* MMI_Common_RedirectMainMenuStyle
* @brief	Redirect main menu style setting value if current value is not be activated (exclude by compile option)
*
* @param	pThis				The pointer of caller
*/
void MMI_Common_RedirectMainMenuStyle(IBase *pThis);

/**
* MMI_Common_TriggerReLoadMainMenu
* @brief	Trigger mainmenu ap to relead
*
* @param	pThis				The pointer of caller
*/
MAE_Ret MMI_Common_TriggerReLoadMainMenu(IBase *pThis);

// Designate IMEI code
typedef enum
{
    COMMON_DESIGNATE_IMEI_CODE_UNKNOWN = 0
    ,COMMON_DESIGNATE_IMEI_CODE_1
//#if defined(__MSTAR_DUAL_SIM_E2P__)&& defined(__DUAL_IMEI_MMI__)
    ,COMMON_DESIGNATE_IMEI_CODE_2
//#endif
} COMMON_DESIGNATE_IMEI_CODE_e;

/**
* MMI_Common_GetDesignateIMEICode
* @brief	To get designate IMEI code for 15 digits ascii string.
*
* @param	pThis	                            The caller instance.
* @param	COMMON_DESIGNATE_IMEI_CODE_e	    The designate IMEI codec.
* @param	ppOuput	                            The output is a malloc memory for 15 digits of ascii IMEI num.
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Out of memory.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/

MAE_Ret MMI_Common_GetDesignateIMEICode(IBase* pThis, COMMON_DESIGNATE_IMEI_CODE_e eDesignateIMEI, u8 **ppOuput);

/**
* MMI_Common_HideInactiveNetworkStatus
* @brief	To hide master network widget or slave network widget if __DUAL_SIM_ONE_STANDBY_MMI__ is defined.
*
* @param	pThis					The caller instance.
* @param	pMaster					The master network widget.
* @param	pSlave					The slave network widget.
*/
#ifdef __DUAL_SIM_ONE_STANDBY_MMI__
void MMI_Common_HideInactiveNetworkStatus(IBase *pThis, IWidget *pMaster, IWidget *pSlave);
#endif

/**
* MMI_Common_GetLanguageCode
* @brief		Get current language code from config.
*
* @param	pThis					The pointer of caller.
* @param	pLanguageCode			The pointer for passing the time to be formated.
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal		MAE_RET_NOT_FOUND	If no file in file system.
* @retVal		MAE_RET_FAILED	If an error happen.
* @retVal		MAE_RET_SUCCESS	If successful.
*/
MAE_Ret MMI_Common_GetLanguageCode(IBase* pThis, MAE_LANG_CODE_e* pLanguageCode);

/**
* MMI_Common_IsExtCardExist
* @brief	Check is ExtCard inserted or not
*
* @param	pThis			The pointer of caller
*
* @retVal	TURE			ExtCard inserted
*			FALSE			ExtCard not inserted
*/
boolean MMI_Common_IsExtCardExist(IBase *pThis);

/**
* MMI_Common_GetWeekDay
* @brief	Get the week day of a specified date
*
* @param	pDate			The specified date
*
* @retVal	week day
*/
u32 MMI_Common_GetWeekDay(MAE_DateTime_t *pDate);

#if defined(__UI_STYLE_MMI_MAIN_MENU_ANIMATION__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__)|| defined(__UI_STYLE_FLIPDCLOCK__)|| defined(__UI_STYLE_MMI_ANDROID_KEYGUARD__)
/**
* MMI_Common_ScaleBitmap
* @brief		Scale the bitmap to requested size
*
* @param	pDisplay					The pointer of display instance.
* @param	pSrcBmp                             Pointer to the source bitmap.
* @param      ppDstBmp                           Pointer to the pointer of scaled bitmap
* @param      tDstRc                                Rectangular to specify the scale operation
* @param      pOwner                              The owner of created destination bitmap
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal		MAE_RET_FAILED	If an error happen.
* @retVal		MAE_RET_SUCCESS	If successful.
*/
MAE_Ret MMI_Common_ScaleBitmap(IDisplay *pDisplay, IBitmap *pSrcBmp, IBitmap **ppDstBmp, Rect_t tDstRc, IBase *pOwner);

/**
* MMI_Common_PerspectiveBitmap
* @brief    Generate the perspective bitmap (downsample)
*
* @param	pDisplay					The pointer of display instance.
* @param	pSrcBmp                             Pointer to the source bitmap.
* @param    ppDstBmp                Pointer to the pointer of perspective bitmap.
* @param    pTransformParm          Trapezoid size and direction.
* @param    pOwner                  The owner of created destination bitmap.
*
* @retVal		MAE_RET_BAD_PARAM	Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal		MAE_RET_FAILED	If an error happen.
* @retVal		MAE_RET_SUCCESS	If successful.
*
* [copy from mae_viewMgr_pl.h]
*      UP          DOWN       RIGHT      LEFT
*
*     topW
*     ----      ----------    |\            /|
*    / |  \     \   |    /    |  \        /  |
*   /  h   \     \  h   /     |-h-| topW |-h-|
*  /   |    \     \ |  /      |  /        \  |
* ------------     ----       |/            \|
*                  topW
* h = height
* topW = topWidth
*/
MAE_Ret MMI_Common_PerspectiveBitmap(IDisplay *pDisplay, IBitmap *pSrcBmp, Rect_t *pSrcRc, IBitmap **ppDstBmp, Transform_PerspectiveParam_t *pTransformParm, IBase* pOwner);

/**
* MMI_Common_PerspectiveBitmap2
* @brief    Generate the perspective bitmap (enlarge)
*
* @param    pDisplay                The pointer of display instance.
* @param    pSrcBmp                 Pointer to the source bitmap.
* @param    ppDstBmp                Pointer to the pointer of perspective bitmap.
* @param    pTransformParm          Trapezoid size and direction.
* @param    pOwner                  The owner of created destination bitmap.
*
* @retVal   MAE_RET_BAD_PARAM	    Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal   MAE_RET_FAILED	        If an error happen.
* @retVal   MAE_RET_SUCCESS	        If successful.
*/
MAE_Ret MMI_Common_PerspectiveBitmap2(IDisplay *pDisplay, IBitmap *pSrcBmp, Rect_t *pSrcRc, IBitmap **ppDstBmp, Transform_PerspectiveParam_t *pTransformParm, IBase* pOwner);

/**
* MMI_Common_ResizeOneRowBitmap
* @brief    resize one row/column bitmap
*
* @param    pDisplay                The pointer of display instance.
* @param    pSrcBmp                 Pointer to the source bitmap.
* @param    pSrcRc                  Pointer to the source bitmap rectangle.
* @param    ppDstBmp                Pointer to the pointer of resized bitmap.
* @param    pDstRc                  Pointer to the destination bitmap rectangle.
* @param    pOwner                  The owner of created destination bitmap.
*
* @retVal   MAE_RET_BAD_PARAM	    Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal   MAE_RET_FAILED	        If an error happen.
* @retVal   MAE_RET_SUCCESS	        If successful.
*/
MAE_Ret MMI_Common_ResizeOneRowBitmap(IDisplay *pDisplay, IBitmap *pSrcBmp, Rect_t *pSrcRc, IBitmap *pDstBmp, Rect_t *pDstRc, IBase* pOwner);

/**
* MMI_Common_RotateBitmap
* @brief    Rotate bitmap to request angle
*
* @param    pDisplay                The pointer of display instance.
* @param    pSrcBmp                 Pointer to the source bitmap.
* @param    ppDstBmp                Pointer to the pointer of rotated bitmap.
* @param    pOwner                  The owner of created destination bitmap.
* @param    outWidth                Pointer of output width.
* @param    outHeight               Pointer of output height.
* @param    nAngle                  Angle of the destination.
*
* @retVal   MAE_RET_BAD_PARAM	    Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal   MAE_RET_FAILED	        If an error happen.
* @retVal   MAE_RET_SUCCESS	        If successful.
*/
MAE_Ret MMI_Common_RotateBitmap(IDisplay *pDisplay, IBitmap *pSrcBmp, IBitmap **ppDstBmp, IBase* pOwner, u16 *outWidth, u16 *outHeight, RotateAngle_e nAngle);

/**
* MMI_Common_InverseBitmap
* @brief    Inverse bitmap (180 degree)
*
* @param    pDisplay                The pointer of display instance.
* @param    pSrcBmp                 Pointer to the source bitmap.
* @param    ppDstBmp                Pointer to the pointer of inversed bitmap.
* @param    pOwner                  The owner of created destination bitmap.
* @param    nWidth                  Width of source bitmap.
* @param    nHeight                 Height of source bitmap.
*
* @retVal   MAE_RET_BAD_PARAM	    Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal   MAE_RET_FAILED	        If an error happen.
* @retVal   MAE_RET_SUCCESS	        If successful.
*/
MAE_Ret MMI_Common_InverseBitmap(IDisplay *pDisplay, IBitmap *pSrcBmp, IBitmap **ppDstBmp, IBase* pOwner, u16 nWidth, u16 nHeight);

/**
* MMI_Common_ApartBitmap
* @brief    Take the bitmap apart
*
* @param    pDisplay                The pointer of display instance.
* @param    pSrcBmp                 Pointer to the source bitmap.
* @param    ppDstBmp                Pointer to the pointer of bitmap apart.
* @param    pOwner                  The owner of created destination bitmap.
* @param    nWidth                  Width of source bitmap.
* @param    nHeight                 Height of source bitmap.
* @param    ePart                   Destruct portion.
*
* @retVal   MAE_RET_BAD_PARAM	    Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal   MAE_RET_FAILED	        If an error happen.
* @retVal   MAE_RET_SUCCESS	        If successful.
*/
MAE_Ret MMI_Common_ApartBitmap(IDisplay *pDisplay, IBitmap *pSrcBmp, IBitmap **ppDstBmp, IBase* pOwner, u16 nWidth, u16 nHeight, DestructPortion_e ePart);

/**
* MMI_Common_SplitBitmap
* @brief    Split bitmap
*
* @param    pDisplay                The pointer of display instance.
* @param    pSrcBmp                 Pointer to the source bitmap.
* @param    ppDstBmp                Pointer to the pointer of split bitmap.
* @param    pOwner                  The owner of created destination bitmap.
* @param    nWidth                  Width of source bitmap.
* @param    nHeight                 Height of source bitmap.
* @param    nGap                    The pixel in a gap.
*
* @retVal   MAE_RET_BAD_PARAM	    Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal   MAE_RET_FAILED	        If an error happen.
* @retVal   MAE_RET_SUCCESS	        If successful.
*/
MAE_Ret MMI_Common_SplitBitmap(IDisplay *pDisplay, IBitmap *pSrcBmp, IBitmap **ppDstBmp, IBase* pOwner, u16 nWidth, u16 nHeight, u16 nGap);
#endif //#ifdef __UI_STYLE_MMI_MAIN_MENU_ANIMATION__

#ifdef __UI_STYLE_FLIPDCLOCK__

/*
* MMI_Common_PerspectiveBitmapEx
* @brief    Generate the perspective bitmap (enlarge)
*
* @param    pDisplay                The pointer of display instance.
* @param    pSrcBmp                 The pointer of source bitmap.
* @param    ppDstBmp                Point to the pointer of destination bitmap.
* @param    pPerspectiveParam       Perspective parameter
* @param    pOwner					The owner of created destination bitmap.
*
* @retVal   MAE_RET_BAD_PARAM	    Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal   MAE_RET_FAILED	        If an error happen.
* @retVal   MAE_RET_SUCCESS	        If successful.
*/
MAE_Ret MMI_Common_PerspectiveBitmapEx(IDisplay *pDisplay, IBitmap *pSrcBmp, IBitmap **ppDstBmp, PerspectiveParamEx_t *pPerspectiveParam, IBase *pOwner);
#endif
#ifdef __FT_AUTO_TEST__
/**
* MMI_Common_IsFTAutoTestProgressing
* @brief		Check is the FT Auto Test Progressing.
*
* @param	pThis				The pointer of caller.
*
* @retVal	TRUE	                  The FT Auto Test is Progressing.
* @retVal	FALSE		         The FT Auto Test is not Progressing.
*/
boolean MMI_Common_IsFTAutoTestProgressing( IBase *pThis );
void MMI_Common_Set_FTAutoTestProgressing( IBase *pThis, bool flag );
#endif

/**
* MMI_Common_RotateBitmapInt
* @brief    Rotate bitmap to request angle, use integer to calculate
*
* @param    pDisplay                The pointer of display instance.
* @param    pSrcBmp                 Pointer to the source bitmap.
* @param    ppDstBmp                Pointer to the pointer of rotated bitmap.
* @param    pOwner                  The owner of created destination bitmap.
* @param    outWidth                Pointer of output width.
* @param    outHeight               Pointer of output height.
* @param    nAngle                  Angle of the destination.
* @param    bOnlyScreenSize     only calculate center screen size
*
* @retVal   MAE_RET_BAD_PARAM	    Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal   MAE_RET_FAILED	        If an error happen.
* @retVal   MAE_RET_SUCCESS	        If successful.
*
* @note     the value of nAngle can be ROT_INT_ANGLE_15, ROT_INT_ANGLE_30, ROT_INT_ANGLE_330 and ROT_INT_ANGLE_345.
*/
MAE_Ret MMI_Common_RotateBitmapInt(IDisplay *pDisplay, IBitmap *pSrcBmp, IBitmap **ppDstBmp, IBase* pOwner, u16 *outWidth, u16 *outHeight, RotateIntAngle_e nAngle, boolean bOnlyScreenSize);

/**
* MMI_Common_ConvertKeyByRotation
* @brief	convert the key code based on current Rotation
*
* @retVal	KeyCode		The original key code
*
* @retVal   u32			The converted key code
*/
u32 MMI_Common_ConvertKeyByRotation(u32 KeyCode);

/**
* MMI_Common_RotateBitmapIntEx
* @brief    Rotate bitmap to request angle, use integer to calculate
*
* @param    pDisplay                The pointer of display instance.
* @param    pSrcBmp                 Pointer to the source bitmap.
* @param    ppDstBmp                Pointer to the pointer of rotated bitmap.
* @param    pOwner                  The owner of created destination bitmap.
* @param    outWidth                Pointer of output width.
* @param    outHeight               Pointer of output height.
* @param    nAngle                  Angle of the destination.
* @param    bOnlyScreenSize     only calculate center screen size
*
* @retVal   MAE_RET_BAD_PARAM	    Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Can not allocate memory.
* @retVal   MAE_RET_FAILED	        If an error happen.
* @retVal   MAE_RET_SUCCESS	        If successful.
*
* @note     the value of nAngle can be any integer.
*/
MAE_Ret MMI_Common_RotateBitmapIntEx(IDisplay *pDisplay, IBitmap *pSrcBmp, IBitmap **ppDstBmp, IBase* pOwner, u16 *outWidth, u16 *outHeight, u32 nAngle, boolean bOnlyScreenSize);

/**
* MMI_Common_GetDefaultHotkeySetting
* @brief	To get default hotkey setting for applet (enable/disable each hw hotkey)
*
* @param	nClsId	    Applet class Id.
* @retVal	u32 		if input clsid is found in Hotkey_Mapping table, then return the setting stored in this table
*                       else return nDefaultHotkeySetting
*/

__SLDPM_FREE__ u32 MMI_Common_GetDefaultHotkeySetting(u32 nClsId);
__SLDPM_FREE__ MultiBKLSetting* MMI_Common_GetDefaultBacklightSetting(u32 nClsId);

u32 MMI_Common_GetImageIdBySCFuncId(IBase *pOwner, ShortcutsFuncId_e eSCFuncId);

/**
* MMI_Common_SetDefaultHotkeySetting
* @brief	To set default hotkey setting for applet (enable/disable each hw hotkey)
*
* @param	nClsId	    Applet class Id.
* @retVal
*/

__SLDPM_FREE__ void MMI_Common_SetDefaultHotkeySetting(u32 nClsId);

/**
* MMI_Common_SetHotkeySetting
* @brief	To set hotkey setting for applet (enable/disable each hw hotkey)
*
* @param	nHotkeySetting	    hotkey setting
* @retVal
*/

__SLDPM_FREE__ void MMI_Common_SetHotkeySetting(u32 nClsId);


#if defined (__UI_STYLE_MMI_ANDROID_IDLE__)|| defined(__UI_STYLE_MMI_ANDROID_KEYGUARD__)
IDispCanvas * MMI_Common_CreateDispCanvas(IBase* pOwner, u16 w, u16 h);
IBitmap* MMI_Common_GetWidgetRawData(IBase *pOwner,IWidget *pSrcWdg,u32 nSrcWidth,u32 nSrcHight,u32 nDstWidth,u32 nDstHight,u32 nMaskVal,boolean bIsSilkSytle,boolean bIsBGTrans);
#endif//#if defined (__UI_STYLE_MMI_ANDROID_IDLE__)|| defined(__UI_STYLE_MMI_ANDROID_KEYGUARD__)

#if defined(__3D_UI_IDLE_MULTIPAGE__)
MAE_Ret MMI_Common_SetIdlePreviewPageBmp(IBitmap *pBmp, u8 imageIdx, IBase* pOwner);
IBitmap* MMI_Common_GetIdlePreviewPageBmp(u8 imageIdx, IBase* pOwner);
#endif // __3D_UI_IDLE_MULTIPAGE__

#ifdef __AUTO_TEST_SCRIPT__
/**
* MMI_Common_GetOsTickForAutoTest
* @brief	To get os tick from trun on the handset
*
* @param
* @retVal
*/
void MMI_Common_GetOsTickForAutoTest(GetTick_e eTickFrom, u32 nTick);
#endif

/**
* MMI_Common_InitAvailableExtAudioDevice
* @brief	To init current available external audio device list
*
* @param
* @retVal
*/
void MMI_Common_InitAvailableExtAudioDevice(void);

/**
* MMI_Common_UpdateAvailableExtAudioDevice
* @brief	To update current available external audio device list
*
* @param	eExtAudioDevice	    External audio device
* @param	bAdd	            TRUE to add the audio device into list.
*                               FALSE to remove the audio device from list.
* @retVal
*/
void MMI_Common_UpdateAvailableExtAudioDevice(COMMON_ExtAudioDevice_e eExtAudioDevice, boolean bAdd);

/**
* MMI_Common_GetActiveExtAudioDevice
* @brief	Get current active external audio device
*
* @param	eExtAudioDevice	            External audio device
* @param	bAdd	                    TRUE to add the audio device into list.
*                                       FALSE to remove the audio device from list.
* @retVal	COMMON_ExtAudioDevice_e     Return current external audio device which is defined by the following rule:
*                                       The lasted connected external audio device is the active one.
*/
COMMON_ExtAudioDevice_e MMI_Common_GetActiveExtAudioDevice(void);

/**
* MMI_Common_ConvertAngleToBlitType
* @brief	convert the image decode angle to bitmap bitblt type
*
* @retVal	nDecAngle		The image decode angle
*
* @retVal   BitmapBlitType_e			The converted bitblt type
*/
BitmapBlitType_e MMI_Common_ConvertAngleToBlitType(ImgDecAngle_t nDecAngle);

/**
* MMI_Common_CreateOverlayBitmap
* @brief	create overlay bitmap according pDataID config with pWdgSize
*
* @param	pThis	        Instance
* @param	pDataID		    OverlayImage widget Common Data, refer to WdgOverlayImageDataID_t
* @param	WidgetSize_t    OverlayImageWidget size, be specified by base image if given NULL
*
* @retVal   IBitmap			The overlay bitmap
*/
__SLDPM_FREE__ IBitmap *MMI_Common_CreateOverlayBitmap(IBase *pThis, WdgOverlayImageDataID_t *pDataID, WidgetSize_t *pWdgSize);

/**
* MMI_Common_QueryAppletToResist
* @brief		Check the some critical applet existed or not for Queried AP to resist memory consuming
*
* @retVal		TRUE		Queried AP need resist
* @retVal		FALSE		Queried AP didn't need resist
*/
boolean MMI_Common_QueryAppletToResist(void);

/**
* MMI_Common_SetViewportAnim
* @brief		Enable Viewport Animation, now support 3 type, IPhone stype(default), Android style, and Boundonly style
*
* @param        pViewportWdg        The Viewportwdg
* @param        eAnimType           Animation Type
*
* @retVal		MAE_RET_SUCCESS		Set animation successful
* @retVal		MAE_RET_BAD_PARAM   Wrong parameters
* @retVal		others              Failed
*/
MAE_Ret MMI_Common_SetViewportAnim(IWidget *pViewportWdg, ViewportAnimType_e eAnimType, ViewportAnimUserData_t *pAnimUserData);

#endif /* __MMI_COMMON_UTIL_H__ */
