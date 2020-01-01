/**
 * @file mmi_mae_log.h
 *
 * This header file defines the trace functions of different levels for MAE platform.
 *
 * Currently we have 6 levels of trace and the priority is:
 *
 *	TRACE < DEBUG < INFO < WARN < ERROR < FATAL
 *
 * Define LOG_LEVEL at project nLevel disables the trace which has lower priority than
 * the nLevel. Disabled trace will not be built into the target load and thus save some
 * code size. The default value is LOG_LEVEL_TRACE which enables all the trace.
 *
 * @version $Id: mmi_mae_log.h 1597 2009-08-14 05:28:06Z code.lin $
 */
#ifndef __MMI_MAE_LOG_H__
#define __MMI_MAE_LOG_H__


//
// header files
//
#ifdef __MAE_INTERNAL_BUILD__
#include <stdio.h> ///< include this only for simulator's log output
#else // __MAE_INTERNAL_BUILD__
//#include "sys_rtk_ho.h"
#include "sys_vm_dbg.ho"
#include "sys_rtk_backtrace.h"
#ifndef __PC_SIMULATOR__
#include "sys_traces.ho"
#include "remote.ho"
#endif//__PC_SIMULATOR__
#endif // __MAE_INTERNAL_BUILD__

#if defined(__MAE_DEBUG__) && defined(__PC_SIMULATOR__)
	#include <assert.h> ///< included for assert on simulator
#endif

#include "mmi_mae_common_def.h"
#include "mmi_mae_features.h" ///< for LOG_LEVEL definition

//
// definitions and prototypes
//
/// default log nLevel; only logs whose nLevel equal or higher than the LOG_LEVEL will be turned on
#ifndef LOG_LEVEL
	#define LOG_LEVEL LOG_LEVEL_TRACE
#endif

/// identifiers for the groups of trace output
enum
{
	MAE_LEVEL_0		= _MMK | LEVEL_0,
	MAE_LEVEL_1		= _MMK | LEVEL_1,
	MAE_LEVEL_2		= _MMK | LEVEL_2,
	MAE_LEVEL_3		= _MMK | LEVEL_3,
	MAE_LEVEL_4		= _MMK | LEVEL_4,
	MAE_LEVEL_5		= _MMK | LEVEL_5,
	MAE_LEVEL_6		= _MMK | LEVEL_6,
	MAE_LEVEL_7		= _MMK | LEVEL_7,
	MAE_LEVEL_8		= _MMK | LEVEL_8,
	MAE_LEVEL_9		= _MMK | LEVEL_9,
	MAE_LEVEL_10	= _MMK | LEVEL_10,
	MAE_LEVEL_11	= _MMK | LEVEL_11,
	MAE_LEVEL_12	= _MMK | LEVEL_12,
	MAE_LEVEL_13	= _MMK | LEVEL_13,
	MAE_LEVEL_14	= _MMK | LEVEL_14,
	MAE_LEVEL_15	= _MMK | LEVEL_15,
	MAE_LEVEL_16	= _MMK | LEVEL_16,
	MAE_LEVEL_17	= _MMK | LEVEL_17,
	MAE_LEVEL_18	= _MMK | LEVEL_18,
	MAE_LEVEL_19	= _MMK | LEVEL_19,
	MAE_LEVEL_20	= _MMK | LEVEL_20,
	MAE_LEVEL_21	= _MMK | LEVEL_21,
	MAE_LEVEL_22	= _MMK | LEVEL_22,
	MAE_LEVEL_23	= _MMK | LEVEL_23,
	MAE_LEVEL_24	= _MMK | LEVEL_24,
	MAE_LEVEL_25	= _MMK | LEVEL_25,
	MAE_LEVEL_26	= _MMK | LEVEL_26,
	MAE_LEVEL_27	= _MMK | LEVEL_27,
	MAE_LEVEL_28	= _MMK | LEVEL_28,
	MAE_LEVEL_29	= _MMK | LEVEL_29,
	MAE_LEVEL_30	= _MMK | LEVEL_30,
	MAE_LEVEL_31	= _MMK | LEVEL_31
};

#define MAE_LEVEL_SHELL				MAE_LEVEL_0
#define MAE_LEVEL_SM	 			MAE_LEVEL_1
#define MAE_LEVEL_VIEW	 			MAE_LEVEL_2
#define MAE_LEVEL_KEYPAD			MAE_LEVEL_3
#define MAE_LEVEL_GRAPHIC			MAE_LEVEL_6
#define MAE_LEVEL_TIMER				MAE_LEVEL_7
#define MAE_LEVEL_IRESCTRL			MAE_LEVEL_8
#define MAE_LEVEL_IMEDIA			MAE_LEVEL_9
#define MAE_LEVEL_NOTIFY 			MAE_LEVEL_10
#define MAE_LEVEL_MOTIONDETECTOR	MAE_LEVEL_11
#define MAE_LEVEL_SQLITE			MAE_LEVEL_12
#define MAE_LEVEL_DB				MAE_LEVEL_13
#define MAE_LEVEL_CUSTOMIZATION		MAE_LEVEL_14
#define MAE_LEVEL_BATTERY			MAE_LEVEL_15
#define MAE_LEVEL_CAMERA			MAE_LEVEL_16
#define MAE_LEVEL_TOUCHSCREEN       MAE_LEVEL_17
#define MAE_LEVEL_THEMEMGR          MAE_LEVEL_18
#define MAE_LEVEL_MODEL             MAE_LEVEL_19
#define MAE_LEVEL_IO                MAE_LEVEL_20
#define MAE_LEVEL_CLOCK             MAE_LEVEL_21
#define MAE_LEVEL_SUBJECT           MAE_LEVEL_23
#define MAE_LEVEL_CODEC				MAE_LEVEL_24
#define MAE_LEVEL_MEM				MAE_LEVEL_31
#define MAE_LEVEL_GPS               MAE_LEVEL_5
#define MAE_LEVEL_MGL               MAE_LEVEL_5
#define MAE_LEVEL_PGL               MAE_LEVEL_5
#define MAE_LEVEL_MULTILAYER	 MAE_LEVEL_4
#define MAE_LEVEL_MULTILAYER_VIEW	 MAE_LEVEL_5
#define MAE_LEVEL_RUNTIME_PROFILING	MAE_LEVEL_4
#ifdef __RFID__
#define MAE_LEVEL_RFID				MAE_LEVEL_25
#endif	//__RFID__

enum
{
	MMI_LEVEL_0		= _MMI | LEVEL_0,
	MMI_LEVEL_1		= _MMI | LEVEL_1,
	MMI_LEVEL_2		= _MMI | LEVEL_2,
	MMI_LEVEL_3		= _MMI | LEVEL_3,
	MMI_LEVEL_4		= _MMI | LEVEL_4,
	MMI_LEVEL_5		= _MMI | LEVEL_5,
	MMI_LEVEL_6		= _MMI | LEVEL_6,
	MMI_LEVEL_7		= _MMI | LEVEL_7,
	MMI_LEVEL_8		= _MMI | LEVEL_8,
	MMI_LEVEL_9		= _MMI | LEVEL_9,
	MMI_LEVEL_10	= _MMI | LEVEL_10,
	MMI_LEVEL_11	= _MMI | LEVEL_11,
	MMI_LEVEL_12	= _MMI | LEVEL_12,
	MMI_LEVEL_13	= _MMI | LEVEL_13,
	MMI_LEVEL_14	= _MMI | LEVEL_14,
	MMI_LEVEL_15	= _MMI | LEVEL_15,
	MMI_LEVEL_16	= _MMI | LEVEL_16,
	MMI_LEVEL_17	= _MMI | LEVEL_17,
	MMI_LEVEL_18	= _MMI | LEVEL_18,
	MMI_LEVEL_19	= _MMI | LEVEL_19,
	MMI_LEVEL_20	= _MMI | LEVEL_20,
	MMI_LEVEL_21	= _MMI | LEVEL_21,
	MMI_LEVEL_22	= _MMI | LEVEL_22,
	MMI_LEVEL_23	= _MMI | LEVEL_23,
	MMI_LEVEL_24	= _MMI | LEVEL_24,
	MMI_LEVEL_25	= _MMI | LEVEL_25,
	MMI_LEVEL_26	= _MMI | LEVEL_26,
	MMI_LEVEL_27	= _MMI | LEVEL_27,
	MMI_LEVEL_28	= _MMI | LEVEL_28,
	MMI_LEVEL_29	= _MMI | LEVEL_29,
	MMI_LEVEL_30	= _MMI | LEVEL_30,
	MMI_LEVEL_31	= _MMI | LEVEL_31
};
#define MMI_LEVEL_WIDGET            MMI_LEVEL_0
#define MMI_LEVEL_SHELL             MAE_LEVEL_SHELL
#define MMI_LEVEL_SM                MMI_LEVEL_2
// Do NOT mix this level with other function, it needs to log meaningful user input to card
#define MMI_LEVEL_USERINPUT         MMI_LEVEL_3

#define MMI_LEVEL_CALENDAR          MMI_LEVEL_4
#define MMI_LEVEL_TODOLIST          MMI_LEVEL_4
#define MMI_LEVEL_CAMERA            MMI_LEVEL_5
#define MMI_LEVEL_CC                MMI_LEVEL_6
#ifdef __VT_3G324M__
#define MMI_LEVEL_VTCC              MMI_LEVEL_6
#endif //__VT_3G324M__
#define MMI_LEVEL_FILEMGR           MMI_LEVEL_7
#define MMI_LEVEL_DRMAGENT          MMI_LEVEL_7
#define MMI_LEVEL_IDLE              MMI_LEVEL_8
#define MMI_LEVEL_MAINMENU          MMI_LEVEL_9
#define MMI_LEVEL_SHORTCUTS         MMI_LEVEL_9
#define MMI_LEVEL_MPLAYER           MMI_LEVEL_10
#define MMI_LEVEL_MESSAGE           MMI_LEVEL_11
#define MMI_LEVEL_ONOFF             MMI_LEVEL_12
#define MMI_LEVEL_PHB               MMI_LEVEL_13
#define MMI_LEVEL_PICTVIEWER        MMI_LEVEL_14
#define MMI_LEVEL_SETTING           MMI_LEVEL_15
#define MMI_LEVEL_CDWAPAPP          MMI_LEVEL_15
#define MMI_LEVEL_VIDEO             MMI_LEVEL_16
#define MMI_LEVEL_EM                MMI_LEVEL_15
#define MMI_LEVEL_RTSP              MMI_LEVEL_16
#define MMI_LEVEL_SOHU              MMI_LEVEL_15
#define MMI_LEVEL_THEMEMGR          MMI_LEVEL_17
#define MMI_LEVEL_THEMEAPP          MMI_LEVEL_17
#define MMI_LEVEL_GENERAL           MMI_LEVEL_18
#define MMI_LEVEL_FMR               MMI_LEVEL_18
#define MMI_LEVEL_NETWORK           MMI_LEVEL_19
#define MMI_LEVEL_WIFI              MMI_LEVEL_19
#define MMI_LEVEL_CALLLOG           MMI_LEVEL_20
#define MMI_LEVEL_ACCESSARY         MMI_LEVEL_21
#define MMI_LEVEL_CORESRV           MMI_LEVEL_21
#define MMI_LEVEL_STATUSBAR         MMI_LEVEL_21
#define MMI_LEVEL_CHECKDISK         MMI_LEVEL_21
#define MMI_LEVEL_SEC               MMI_LEVEL_22
#define MMI_LEVEL_PRIVATEPROTECT    MMI_LEVEL_22
#define MMI_LEVEL_TOOLS             MMI_LEVEL_23
#define MMI_LEVEL_ATSYNCSRV         MMI_LEVEL_23
#define MMI_LEVEL_WLAN              MMI_LEVEL_23
#define MMI_LEVEL_TTS               MMI_LEVEL_23
#define MMI_LEVEL_VENDOR            MMI_LEVEL_24
#define MMI_LEVEL_SS                MMI_LEVEL_26
#define MMI_LEVEL_STK               MMI_LEVEL_27
#define MMI_LEVEL_BT                MMI_LEVEL_27
#define MMI_LEVEL_EVTCENTER         MMI_LEVEL_28
#define MMI_LEVEL_DIALOGSRV         MMI_LEVEL_28
#define MMI_LEVEL_TOUCHSCREEN       MMI_LEVEL_29
//#ifdef __ATV_MMI__
#define MMI_LEVEL_ATV               MMI_LEVEL_30
//#endif
#define MMI_LEVEL_ALARM             MMI_LEVEL_30
#define MMI_LEVEL_SENDVIA           MMI_LEVEL_30
#define MMI_LEVEL_ANIMATION         MMI_LEVEL_30
#define MMI_LEVEL_VOICEMEMO         MMI_LEVEL_31
#define MMI_LEVEL_COMMON            MMI_LEVEL_31
#define MMI_LEVEL_GAME              MMI_LEVEL_2
#define MMI_LEVEL_BMI               MMI_LEVEL_23
#define MMI_LEVEL_E_BOOK            MMI_LEVEL_23
#define MMI_LEVEL_WLAN              MMI_LEVEL_23
#define MMI_LEVEL_TTS               MMI_LEVEL_23
#define MMI_LEVEL_DICTAPP           MMI_LEVEL_2
#define MMI_LEVEL_PEDOMETERAPP      MMI_LEVEL_23
#define MMI_LEVEL_PEDOMETERSRV      MMI_LEVEL_22

#define MMI_LEVEL_GPS               MMI_LEVEL_5
#define MMI_LEVEL_MAPVIEW           MMI_LEVEL_5
#define MMI_LEVEL_SCREENLOCKAPP     MMI_LEVEL_5
#define MMI_LEVEL_GLDEMO            MMI_LEVEL_5
#define MMI_LEVEL_GADGETAPP         MMI_LEVEL_5
#define MMI_LEVEL_G3DMAINMENUAPP    MMI_LEVEL_5

#ifdef __VT_3G324M__
#define MMI_LEVEL_H324M             MMI_LEVEL_5
#endif //__VT_3G324M__

#define MMI_LEVEL_TESTAPP           MMI_LEVEL_31
#define MMI_LEVEL_UNITTESTAPP       MMI_LEVEL_31

#define MMI_LEVEL_SEARCHAPP         MMI_LEVEL_30
#ifdef __PC_SIMULATOR__ // ViewTester
#define MMI_LEVEL_VIEWTESTER        MMI_LEVEL_23
#endif // __PC_SIMULATOR__

#ifdef __FT_AUTO_TEST__
#define MMI_LEVEL_AUTOTEST          MMI_LEVEL_27
#endif

#ifdef __EMAIL_MMI__
#define MMI_LEVEL_EMAILSRV          MMI_LEVEL_31
#define MMI_LEVEL_EMAILAPP          MMI_LEVEL_31
#endif

#ifdef __NCCQQ_MMI__
#define MMI_LEVEL_QQSRV             MMI_LEVEL_25
#define MMI_LEVEL_QQAPP             MMI_LEVEL_25
#endif

#ifdef __CALLER_LOCATION__
#define MMI_LEVEL_CALLERLOCATIONAPP    MMI_LEVEL_6
#endif

#define MMI_LEVEL_KMVAPP            MMI_LEVEL_16

#ifdef __APP_MMI_TUDOU__
#define MMI_LEVEL_TUDOU               MMI_LEVEL_18
#endif
/*-------------------------------------------------------------------------*/
#define DEV_TRACE vm_dbgTrace /**< Make redundant macro expansion to avoid RTPP processing to LOG_TRACEs definitions */
#define DEV_WARN vm_dbgError /**< Make redundant macro expansion to avoid RTPP processing to LOG_TRACEs definitions */
/**
 * Temporarily use RtkAssertRoutine() to raise exceptions instead of calling vm_dbgError(),
 * since it sometimes cannot report correct call stack information in exception log.
 */
#ifdef __RTK_DIAGNOSE_ENHANCE__
#define DEV_ERROR(_level_, _format_, ...) vm_dbgError((_level_) | FATAL, _format_, ##__VA_ARGS__)
#else
#define DEV_ERROR(_level_, _format_, ...) vm_dbgError((_level_), _format_, ##__VA_ARGS__)
//#define DEV_ERROR vm_dbgError /**< Make redundant macro expansion to avoid RTPP processing to LOG_TRACEs definitions */
#endif // __RTK_DIAGNOSE_ENHANCE__

#define LOG_LEVEL_TRACE 6	/**< The TRACE Level designates finer-grained informational events than the DEBUG */
#define LOG_LEVEL_DEBUG 5	/**< The DEBUG Level designates fine-grained informational events that are most useful to debug an application. */
#define LOG_LEVEL_INFO  4	/**< The INFO nLevel designates informational messages that highlight the progress of the application at coarse-grained nLevel. */
#define LOG_LEVEL_WARN  3	/**< The WARN nLevel designates potentially harmful situations. */
#define LOG_LEVEL_ERROR 2	/**< The ERROR nLevel designates error events that might still allow the application to continue running. */
#define LOG_LEVEL_FATAL 1	/**< The FATAL nLevel designates very severe error events that will presumably lead the application to abort. */
#define LOG_LEVEL_OFF   0	/**< Log nLevel whcih turn off the logging */

#ifdef __SFILE__
	/* Use short name if source file defined __SFILE__ */
	#define __TARGET_FILE__	__SFILE__
#else
	#define __TARGET_FILE__	__FILE__
#endif

/// default definitions for LOG macros
#define LOG_TRACE(_level_, _format_, ...)
#define LOG_DEBUG(_level_, _format_, ...)
#define LOG_INFO(_level_, _format_, ...)
#define LOG_WARN(_level_, _format_, ...)
#define LOG_ERROR(_level_, _format_, ...)
#define LOG_FATAL(_level_, _format_,  ...)
#define LOG_AUTO_TEST(_level_, _format_,  ...)
#define LOG_POWER_CONSUMPTION_TEST(_level_, _format_,  ...)
#define LOG_CUSTOMER(_level_, _format_,  ...)

/*-------------------------------------------------------------------------*/
#if LOG_LEVEL > LOG_LEVEL_DEBUG
#undef LOG_TRACE

#ifdef __MAE_INTERNAL_BUILD__

	#define LOG_TRACE(_level_, _format_, ...) printf(_format_, ##__VA_ARGS__)

#else

	#ifdef __PC_SIMULATOR__
		#define LOG_TRACE(_level_, _format_, ...) mae_dbgPrintf(_level_, "[TRACE] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
	#else
		/**
		 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
		 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
		 */
		#define LOG_TRACE(_level_, _format_, ...) DEV_TRACE(_level_, _format_, ##__VA_ARGS__)
	#endif

#endif /* __MAE_INTERNAL_BUILD__ */
#endif // LOG_LEVEL_TRACE

/*-------------------------------------------------------------------------*/
#if LOG_LEVEL > LOG_LEVEL_INFO
#undef LOG_DEBUG

#ifdef __MAE_INTERNAL_BUILD__

	#define LOG_DEBUG(_level_, _format_, ...) printf(_format_, ##__VA_ARGS__)

#else

	#ifdef __PC_SIMULATOR__
		#define LOG_DEBUG(_level_, _format_, ...) mae_dbgPrintf(_level_, "[DEBUG] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
	#else
		/**
		 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
		 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
		 */
		#define LOG_DEBUG(_level_, _format_, ...) DEV_TRACE(_level_, _format_, ##__VA_ARGS__)
	#endif

#endif /* __MAE_INTERNAL_BUILD__ */
#endif // LOG_LEVEL_DEBUG

/*-------------------------------------------------------------------------*/
#if LOG_LEVEL > LOG_LEVEL_WARN
#undef LOG_INFO

#ifdef __MAE_INTERNAL_BUILD__

	#define LOG_INFO(_level_, _format_, ...) printf(_format_, ##__VA_ARGS__)

#else

	#ifdef __PC_SIMULATOR__
		#define LOG_INFO(_level_, _format_, ...) mae_dbgPrintf(_level_, "[INFO] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
	#else
		/**
		 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
		 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
		 */
		#define LOG_INFO(_level_, _format_, ...) DEV_TRACE(_level_, _format_, ##__VA_ARGS__)
	#endif

#endif /* __MAE_INTERNAL_BUILD__ */
#endif // LOG_LEVEL_INFO

/*-------------------------------------------------------------------------*/
#if LOG_LEVEL > LOG_LEVEL_ERROR
#undef LOG_WARN

#ifdef __MAE_INTERNAL_BUILD__

	#define LOG_WARN(_level_, _format_, ...) printf(_format_, ##__VA_ARGS__)

#else

	#ifdef __PC_SIMULATOR__
		#define LOG_WARN(_level_, _format_, ...) mae_dbgPrintf(_level_, "[WARN] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
	#else
		/**
		 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
		 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
		 */
		#define LOG_WARN(_level_, _format_, ...) DEV_TRACE(_level_, _format_, ##__VA_ARGS__)
	#endif

#endif /* __MAE_INTERNAL_BUILD__ */
#endif // LOG_LEVEL_WARN

/*-------------------------------------------------------------------------*/
#if LOG_LEVEL > LOG_LEVEL_FATAL
#undef LOG_ERROR

#ifdef __MAE_INTERNAL_BUILD__

	#define LOG_ERROR(_level_, _format_, ...) printf(_format_, ##__VA_ARGS__)

#else

	#ifdef __PC_SIMULATOR__
		#define LOG_ERROR(_level_, _format_, ...) mae_dbgError(_level_, "[ERROR] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
	#else
		/**
		 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
		 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
		 */
		#define LOG_ERROR(_level_, _format_, ...) DEV_WARN(_level_, _format_, ##__VA_ARGS__)
	#endif

#endif /* __MAE_INTERNAL_BUILD__ */
#endif // LOG_LEVEL_ERROR

/*-------------------------------------------------------------------------*/
#undef LOG_FATAL

#ifdef __MAE_INTERNAL_BUILD__

	#define LOG_FATAL(_level_, _format_, ...) printf(_format_, ##__VA_ARGS__)

#else

	/**
	 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
	 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
	 */
	#ifdef __PC_SIMULATOR__
		#ifdef __MAE_DEBUG__
			#define LOG_FATAL(_level_, _format_, ...) (assert(0), mae_dbgPrintf(_level_, "[FATAL] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__))
		#else
			#define LOG_FATAL(_level_, _format_, ...) mae_dbgError(_level_, "[FATAL] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
		#endif // __MAE_DEBUG__
	#else
		/**
		 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
		 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
		 */
		#ifdef __RTK_DIAGNOSE_ENHANCE__
			#define LOG_FATAL(_level_, _format_, ...) DEV_ERROR(_level_, _format_, ##__VA_ARGS__)
		#else
			#define LOG_FATAL(_level_, _format_, ...) DEV_ERROR(_level_, _format_, ##__VA_ARGS__)
		#endif // __RTK_DIAGNOSE_ENHANCE__
	#endif // __PC_SIMULATOR__

#endif /* __MAE_INTERNAL_BUILD__ */

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
#undef LOG_AUTO_TEST

#ifdef __MAE_INTERNAL_BUILD__

	#define LOG_AUTO_TEST(_level_, _format_, ...) printf(_format_, ##__VA_ARGS__)

#else

	#ifdef __PC_SIMULATOR__
		#define LOG_AUTO_TEST(_level_, _format_, ...) mae_dbgPrintf(_level_, "[AUTO TEST] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
	#else
		/**
		 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
		 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
		 */

		#ifdef __AUTO_TEST_SCRIPT__
			#define LOG_AUTO_TEST(_level_, _format_, ...) KER_TESTRESPONSE((u32)TEST_RES_GRP_1 | (u32)TEST_RES_LV_0, _format_, ##__VA_ARGS__)
		#else
			#define LOG_AUTO_TEST(_level_, _format_, ...)
		#endif//__AUTO_TEST_SCRIPT__

	#endif

#endif /* __MAE_INTERNAL_BUILD__ */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
#undef LOG_POWER_CONSUMPTION_TEST

#ifdef __MAE_INTERNAL_BUILD__

	#define LOG_POWER_CONSUMPTION_TEST(_level_, _format_, ...) printf(_format_, ##__VA_ARGS__)

#else

	#ifdef __PC_SIMULATOR__
		#define LOG_POWER_CONSUMPTION_TEST(_level_, _format_, ...) mae_dbgPrintf(_level_, "[POWER CONSUMPTION TEST] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
	#else
		/**
		 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
		 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
		 */

		#ifdef __FEATURE_POWER_CONSUMPTION_LOG__
			#define LOG_POWER_CONSUMPTION_TEST(_level_, _format_, ...) DEV_TRACE(_CUS3 | LEVEL_31, _format_, ##__VA_ARGS__)
		#else
			#define LOG_POWER_CONSUMPTION_TEST(_level_, _format_, ...)
		#endif//__FEATURE_POWER_CONSUMPTION_LOG__

	#endif

#endif /* __MAE_INTERNAL_BUILD__ */

/*-------------------------------------------------------------------------*/

#ifdef __LOG_CUSTOMER_SUPPORT__
#undef LOG_CUSTOMER

#ifdef __MAE_INTERNAL_BUILD__

	#define LOG_CUSTOMER(_level_, _format_, ...) printf(_format_, ##__VA_ARGS__)

#else

	#ifdef __PC_SIMULATOR__
		#define LOG_CUSTOMER(_level_, _format_, ...) mae_dbgPrintf(_level_, "[CUSTOMER] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
	#else
		/**
		 * Beware that if the log macro's parameters before __VA_ARGS__ are changed, the source code of RTPP shall
		 * be updated also. RTPP is used to convert _format_ string to RM_String when building target loads.
		 */
		#define LOG_CUSTOMER(_level_, _format_, ...) DEV_TRACE(_level_, _format_, ##__VA_ARGS__)
	#endif

#endif /* __MAE_INTERNAL_BUILD__ */
#endif /* __LOG_CUSTOMER_SUPPORT__ */

/*-------------------------------------------------------------------------*/

#if defined(__ARMCC_VERSION)

	void MAE_SeriousError(u32 nLevel, char *pFormat, ...);
	#define LOG_SERIOUS MAE_SeriousError

#elif defined(__PC_SIMULATOR__) /*|| defined(__MAE_DEBUG__)*/

	#define LOG_SERIOUS LOG_FATAL

#else

	#define LOG_SERIOUS LOG_ERROR

#endif

/*-------------------------------------------------------------------------*/

#ifdef __PC_SIMULATOR__
	// MS-VS2005 cannot preprocess __VA_ARGS__ well in double parentheses
	#define LOG_BACKTRACE(_level_, ...) _BACKTRACE((_level_, ##__VA_ARGS__))
#else
	#define LOG_BACKTRACE(_level_, _format_, ...) _BACKTRACE((_level_, _format_, ##__VA_ARGS__))
#endif

#endif // __MAE_LOG_H__
