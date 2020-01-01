/**
 *
 * @file    sdkven_example.h
 * @brief   This file is the common define file for the example vendor
 *
 * @author  Ray.Lee
 * @version $Id: sdkven_example.h 47156 2009-12-11 13:28:22Z kenny.wu $
 *
 */

#ifndef __SDKVEN_EXAMPLE_H__
#define __SDKVEN_EXAMPLE_H__

#include "ven_sdk.h"
#include "ven_dbg.h"
#ifndef __SDK_SIMULATION__
#include "sys_traces.ho"
#include "remote.ho"
#endif//__SDK_SIMULATION__

#define _SDKTEST             VEN_DBG_GROUP_0

#define _SDKTEST_DBGLVL_GENERAL     _SDKTEST | VEN_DBG_LEVEL_0
#define _SDKTEST_DBGLVL_AUTOTEST    _SDKTEST | VEN_DBG_LEVEL_0   /* Auto Test API                    */

#define _SDKTEST_DBGLVL_NET         _SDKTEST | VEN_DBG_LEVEL_8   /* Network API                      */
#define _SDKTEST_DBGLVL_FILE        _SDKTEST | VEN_DBG_LEVEL_21  /* for file                         */
#define _SDKTEST_DBGLVL_SET         _SDKTEST | VEN_DBG_LEVEL_22  /* for Settings                     */
#define _SDKTEST_DBGLVL_TIME        _SDKTEST | VEN_DBG_LEVEL_23  /* for time                         */
#define _SDKTEST_DBGLVL_CODEC       _SDKTEST | VEN_DBG_LEVEL_24  /* for codec                        */
#define _SDKTEST_DBGLVL_COMMON      _SDKTEST | VEN_DBG_LEVEL_25  /* for utility                      */
#define _SDKTEST_DBGLVL_GRAPHICS    _SDKTEST | VEN_DBG_LEVEL_26  /* for graphics                     */
#define _SDKTEST_DBGLVL_FONT        _SDKTEST | VEN_DBG_LEVEL_27  /* for font                         */
#define _SDKTEST_DBGLVL_CLIPBOARD   _SDKTEST | VEN_DBG_LEVEL_28  /* for clipboard                    */
#define _SDKTEST_DBGLVL_SETTING     _SDKTEST | VEN_DBG_LEVEL_29  /* for clipboard                    */
#define _SDKTEST_DBGLVL_STC     _SDKTEST | VEN_DBG_LEVEL_30  /* for state control                    */

#ifdef __PC_SIMULATOR__
#define LOG_AUTO_TEST(_level_, _format_, ...) ven_dbg_trace(_level_, "[AUTO TEST] (%d): " _format_, __LINE__, ##__VA_ARGS__)
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

#define CAT_MAXITEM	100
enum
{
	_SDKTEST_CAT_START,
	_SDKTEST_CAT_AUTO = _SDKTEST_CAT_START, /*   0   */
	_SDKTEST_CAT_FS,                        /*   1   */
	_SDKTEST_CAT_OS,                        /*   2   */
	_SDKTEST_CAT_GRAPHICS,                  /*   3   */
	_SDKTEST_CAT_CODEC,                     /*   4   */
	_SDKTEST_CAT_TIME,                      /*   5   */
	_SDKTEST_CAT_SETTING,                   /*   6   */
	_SDKTEST_CAT_NET,                       /*   7   */
	_SDKTEST_CAT_EDITOR,                    /*   8   */
	_SDKTEST_CAT_PHB,                       /*   9   */
	_SDKTEST_CAT_FILEBROWSE,                /*  10   */
	_SDKTEST_CAT_SMS,                       /*  11   */
	_SDKTEST_CAT_WMA,                       /*  12   */
	_SDKTEST_CAT_CC,                        /*  13   */
	_SDKTEST_CAT_CLIPBOARD,                 /*  14   */
	_SDKTEST_CAT_DRV,                       /*  15   */
	_SDKTEST_CAT_SYS,                       /*  16   */
	_SDKTEST_CAT_UI,                        /*  17   */
	_SDKTEST_CAT_UTIL,                      /*  18   */
	_SDKTEST_CAT_CAMERA,                    /*  19   */
	_SDKTEST_CAT_WAP,                       /*  20   */
	_SDKTEST_CAT_GPS,                       /*  21   */
	_SDKTEST_CAT_STC,                       /*  22   */
	_SDKTEST_CAT_KERNEL,                    /*  23   */
	_SDKTEST_CAT_KPD,                       /*  24   */
	_SDKTEST_CAT_MM,                        /*  25   */
	_SDKTEST_CAT_CODEC_2,                   /*  26   */
  	_SDKTEST_CAT_SENSOR,                    /*  27   */
	_SDKTEST_CAT_SUM
};

extern u32 ven_handle;

#define SDKVEN_EXAMPLE_APID   E_VEN_DEFAULT

#define VEN_TEST_REFRESH_TEST_SCREEN   VenTest_draw
#define VEN_TEST_PRINT_INFO_LINE( x )  VenTest_printLine( x )
#define VEN_TEST_WPRINT_INFO_LINE( x ) VenTest_wprintLine( x )
#define VEN_TEST_CHECK_RESULT( x )     VenTest_result( ( x ) ? TRUE : FALSE )
#define VEN_TEST_CHECK_CONFIRM         VenTest_confirm
#define VEN_TEST_STOP_AUTO_TIMER       VenTest_stopAutoTimer
#define VEN_TEST_RESTART_AUTO_TIMER    VenTest_restartAutoTimer
#define VEN_TEST_RESPONSE_TIME( x )    VenTest_responseTime( x )

void VenTest_draw( void );
void VenTest_printLine( u8 *pu8Str );
void VenTest_wprintLine( u16 *pu16Str );
void VenTest_result( bool bResult );
void VenTest_confirm( void );
void VenTest_stopAutoTimer(void);
void VenTest_restartAutoTimer(void);
void VenTest_responseTime( u16 u16Time );
void VenTest_gotoResume(void);

enum
{
    UI_SET_BACKLIGHT,
    UI_GET_BACKLIGHT
};

#endif /* __SDKVEN_EXAMPLE_H__ */
