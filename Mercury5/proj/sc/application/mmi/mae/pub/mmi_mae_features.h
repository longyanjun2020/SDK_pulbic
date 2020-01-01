/**
* @file mmi_mae_features.h
*
* This file collects the define of features.
*
* @version $Id: mmi_mae_features.h 1204 2009-06-23 02:54:55Z kenny.wu $
*/

#ifndef __MMI_MAE_FEATURES_H__
#define __MMI_MAE_FEATURES_H__


/*=============================================================*/
// include
/*=============================================================*/

/*=============================================================*/
// type and define
/*=============================================================*/
#define __FEATURE_SECOND_DISPLAY__			/**< support second display */
#define __FEATURE_CLAMSHELL__				/**< handset type is clamshell */
#define __MAE_DEBUG__						/**< Enable debug mode in MAE */

#define __MAE_DISABLE_PLATFORM_ASSERT__     /**< Disable Platform Level BREAK_IF_NULL, BREAK_IF_FAIL, ...etc. assert */

#define __MAE_DISABLE_APPLET_ASSERT__     /**< Disable App Level BREAK_IF_NULL, BREAK_IF_FAIL, ...etc. assert */

#define __SM_ALLOW_REENTRY__				/**< Allow reentry for these function for different app: MAE_SM_ProcessEvent, MAE_SM_Activate, MAE_SM_InActivate. */

#define __IMAGEMAKER_SAVE_BMP_16__		/**< image maker save 16 bit bmp format */

#ifdef  __SDK_SIMULATION__
#ifndef __PC_SIMULATOR__
#define __PC_SIMULATOR__					///< it defines features only for PC simulator
#endif

// Java Delta is not supported in simulator
#if defined(__JAVA_DELTA__) && !defined(__DALVIK__) // dalvik is using Java delta option right now
#undef __JAVA__
#undef __JAVA_MMI__
#undef __JAVA_DELTA__
#endif /* defined(__JAVA_DELTA__) */
#if !defined(__JAVA__)
#undef __JAVA_MMI__
#endif /* !defined(__JAVA__) */
#endif /* __SDK_SIMULATION__ */

/// MAE debug features
#ifdef __MAE_DEBUG__
#ifndef __SMALL_ROM__
#define SHELL_LOG_AMOUNT 30
#define APM_LOG_AMOUNT 10
#define WND_LOG_AMOUNT 10
#define __MAE_DEBUG_APM__
#define __MAE_DEBUG_SHELL__
#define __MAE_DEBUG_WND__
/*Enable it, and then do not need to enable Hopper.*/
#ifndef __INTERNAL_TEST__
#define QUERY_HOPPER_RUNNING (MAE_RET_SUCCESS == mmi_query_HopperRunning())
#else
#define QUERY_HOPPER_RUNNING 1
#endif
#if defined(__MAE_DEBUG_APM__ ) || defined(__MAE_DEBUG_WND__)
#define CLSID_NONE 0xF0FF
#define MAE_EVT_APP_NONE 0x0FFF
#endif
#endif
#ifndef VC_MEM_DBG
#define _MAE_MEM_STATUS_
#endif //#ifndef VC_MEM_DBG

/**< Enable the statistic of runtime status in SM engine */
//#define __SM_ENABLE_STATISTICS__
/**< Enable the recording of transition history in SM engine */
//#define __SM_TRANSITION_HISTORY__
/// it enables diagnosis features in MAE platform
#define __MAE_CORE_DIAGNOSIS__


#if defined (__PC_SIMULATOR__) || defined(__DEBUG_POOL__)
/// it enables memory leak detection for objects, and also legit verification for sending/posting events
#define __MAE_LEAK_DETECTION__

/// it enables the cyclic detection features for objects
#define __MAE_CYCLIC_DETECTION__
#endif // #if defined (__PC_SIMULATOR__) || defined(__DEBUG_POOL__)

//This is used to protect if the App want to free an invalid object by MAE_FreeObject.
//Protect now, but all Apps need to fix this illegal action.
#define __MAE_INVALID_OBJ_PROTECT__

/// it enables the screen update indication
// #define __MAE_SHOW_SCR_UPDATE__

#endif // __MAE_DEBUG__

#define __MAE_VENEERED_INTERFACE__

#define __USB_MMI_NON_BLOCKING_USAGE__

/*=============================================================*/
// MAE v0.09.01 compile option 
/*=============================================================*/

// PR113694 CL#43126 mae_motiondector.c
//on:mainline ,off:others
#define __MOTIONDECTECTOR_GAME__

/*=============================================================*/
// MAE v0.09.00 compile option 
/*=============================================================*/

// PR95915, CL#15698, mae_imagemaker.c
// on: mainline, off:others
#define __MAE_MMS_IMG_REENCODING__

// PR110833, CL#21315, mae_shell_memory.c, mmi_mae_common_def.h
// on: mainline, off:others
#define __SIMULATOR_MEMORY_CHECK_OVERLAY__ 

/*=============================================================*/
// configuration 
/*=============================================================*/

#if defined(__LOG_LEVEL_ALL__ )
#define LOG_LEVEL       LOG_LEVEL_TRACE /**< Log level, will be LOG_LEVEL_INFO if not defined */
#elif defined(__LOG_LEVEL_MMI_CUT_TRACE__)
#define LOG_LEVEL       LOG_LEVEL_DEBUG /**< Log level, will be LOG_LEVEL_INFO if not defined */
#elif defined(__CRITICAL_TRACES_ONLY__)
#define LOG_LEVEL       LOG_LEVEL_ERROR
#endif

/*=============================================================*/
// show profiling data (EmApp -> EMMI Debug -> update *** time)
// The update time will show on the status bar
/*=============================================================*/
#if !defined(__SMALL_ROM__)
//skip this feature on the product that performs quota check on DZ
#define __EMAPP_SHOW_PROFILING_DATA__ 1
#endif //!defined(__SMALL_ROM__)

#endif //__MAE_FEATURES_H__
/*=============================================================*/
// end of file
