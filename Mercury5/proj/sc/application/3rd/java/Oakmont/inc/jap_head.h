#ifndef __JAP_HEAD_DEFINE_H__

#define __JAP_HEAD_DEFINE_H__

/**

*

* @file    jap_head.h

* @brief   This file .

*

* @author  Owen.Lee

* @version $Id: jap_head.h 28509 2009-04-15 14:23:37Z code.lin $

*

*/


/* Aplix header - begin */

#include "kjava_action.h"

/* Aplix header - end */


/* Mstar header - begin */

#include "ven_common_def.h"

#include "ven_dbg.h"

#include "ven_os.h"

#include "mmi_layout.h" // For MAIN_LCD_WIDTH, MAIN_LCD_HEIGHT, MAIN_SK_HEIGHT



#ifndef __SDK_SIMULATION__
#include "mmi_log.h"
//#include "sys_config.h"  // For SYS config from 1.07. Used to query the RAM size

#endif


#include "java_config.h"


#ifdef  __SDK_SIMULATION__

#ifdef __JAVA_OAKMONT_SCOPE_JAP0__
#pragma comment(lib, "jap0_ajsc_win32_msvc")
#pragma comment(lib, "jap0_libmjb2")
#pragma comment(lib, "jap0_libaicrypto")
#elif defined(__JAVA_OAKMONT_SCOPE_JTWI__)
#pragma comment(lib, "ajsc_win32_msvc")
#pragma comment(lib, "libmjb2")
#pragma comment(lib, "libaicrypto")
#elif defined(__JAVA_OAKMONT_SCOPE_JAP1_HI__)
#pragma comment(lib, "jap1_hi_ajsc_win32_msvc")
#pragma comment(lib, "jap1_hi_libmjb2")
#pragma comment(lib, "jap1_hi_libaicrypto")
#elif defined(__JAVA_OAKMONT_SCOPE_JAP2__)
#pragma comment(lib, "jap2_ajsc_win32_msvc")
#pragma comment(lib, "jap2_libmjb2")
#pragma comment(lib, "jap2_libaicrypto")
#elif defined(__JAVA_OAKMONT_SCOPE_JAP2C__)
#pragma comment(lib, "jap2c_ajsc_win32_msvc")
#pragma comment(lib, "jap2c_libmjb2")
#pragma comment(lib, "jap2c_libaicrypto")
#endif


#endif

#if defined (__JAVA_OAKMONT_SUP_CLDC_HI__) || defined (__JAVA_OAKMONT_SCOPE_MIDP__) || defined(__JAVA_OAKMONT_SCOPE_JTWI_184__)
#error Dont open this compile fLag
#endif

/* Mstar header - end */


/* Configure */
#define JAP_AMR_SUPPORT

#ifdef __JAVA_OAKMONT_NFC_PUSH_SUPPORT__
#define SUPPORT_PUSH_REGISTRY_URL_REGISTRATION
#endif


/************************************************************* 
    some issues relate to TCK test case but it have spec issue or design limitation..
    we use this definition to seperate..

    PRlist::
        PR 139106,

    note::
        please open this definition MS_JAP_TCK_FIX if you want to pass TCK test.
**************************************************************/
//#define JAP_MS_TCK_FIX


#define IMPL_SUPPORT_FILE_CONNECTION

/* Enable debug trace and assert or not */

#define JAP_CFG_DEBUG_ON

/* Enable TCK test mechanism or not

 * If Enable, the entry from EM is for the use of TCK test

 *   *#*#1705# -> XMMI Debug -> JAVA test

 */

#define JAP_CFG_TCK_TEST


#define JAP_WATCHDOGRESET




/*
*   the fefinition JAP_PLAYER_USE_OS_MEM is used to alloc memory of Player by OS heap instead of Java first heap(AmMemFreePointer)
*/
#define JAP_PLAYER_USE_OS_MEM


/* Fine tune the graphic response time in porting layer */

//#define JAP_CFG_ASYNC_LCM_UPDATE


/* Test the performance if not drawing LCD

 *  Press 1 to turn on/off the drawing

 */

//#define JAP_TEST_NOT_DRAW


//#ifdef __SDK_SIMULATION__
#if 0

/* In simulator, we just support JTWI scope now */

#define JAP_SCOPE_JTWI

#define JAP_LIB_VERSION "Java Oakmont: 20110728_Mstar_a, JTWI"


#else // Target




/* Support JSRs and lib version control

 */

#ifdef __JAVA_OAKMONT_SCOPE_JAP0__

  #define JAP_SCOPE_MIDP

  #define JAP_LIB_VERSION "Java Oakmont JAP0"

#elif defined(__JAVA_OAKMONT_SCOPE_JTWI__ )

  #define JAP_SCOPE_JTWI

  #define JAP_LIB_VERSION "Java Oakmont JTWI"

#elif defined(__JAVA_OAKMONT_SCOPE_JTWI_184__ )

  #define JAP_SCOPE_JTWI_184

  #define JAP_LIB_VERSION "Java Oakmont JTWI_184"

#elif defined(__JAVA_OAKMONT_SCOPE_JAP1_HI__ )
  
#define JAP_SCOPE_JAP1_HI
    
#define JAP_LIB_VERSION "Java Oakmont JAP1_HI"

#elif defined(__JAVA_OAKMONT_SCOPE_JAP2__ )

#define JAP_SCOPE_JAP2
  
#define JAP_LIB_VERSION "Java Oakmont JAP2"

#elif defined(__JAVA_OAKMONT_SCOPE_JAP2C__ )

#define JAP_SCOPE_JAP2C
	
#define JAP_LIB_VERSION "Java Oakmont JAP2C"

#endif


#endif // __SDK_SIMULATION__


#if defined(__ONBOARD_USER_STORAGE_MMI__)

    #define JAP_SUPPORT_DUAL_STORAGE

#endif


#if defined(__ONBOARD_USER_STORAGE_MMI__)

#if defined(__NAND__)

/* Support NAND */

#if 1

	/* For debug purpose */

	#define JAP_PRIVATE_SYS_ROOT	"/NAND/.system/"

	#define JAP_PRIVATE_ROOT		"/NAND/.system/java/"

	#define JAP_TEMP_AUDIO_FOLDER   L"/NAND/.system/java_audio"

	#define JAP_TEMP_AUDIO_ROOT		"/NAND/.system/java_audio/"

#else

	#define JAP_PRIVATE_SYS_ROOT	"/SYS0/.system/"

	#define JAP_PRIVATE_ROOT		"/SYS0/.system/java/"

	#define JAP_TEMP_AUDIO_FOLDER   L"/SYS0/.system/java_audio"

	#define JAP_TEMP_AUDIO_ROOT		"/SYS0/.system/java_audio/"

#endif


	/* Support dual storage feature: NAND/SD */

	#define JAP_SUPPORT_DUAL_STORAGE_NAND

#else

    #define JAP_PRIVATE_SYS_ROOT	"/NOR0/.system/"

    #define JAP_PRIVATE_ROOT		"/NOR0/.system/java/"

    #define JAP_TEMP_AUDIO_FOLDER	L"/NOR0/.system/java_audio"

    #define JAP_TEMP_AUDIO_ROOT 	"/NOR0/.system/java_audio/"


	#define JAP_SUPPORT_DUAL_STORAGE_NOR

#endif

#else

	#define JAP_PRIVATE_SYS_ROOT	"/CARD/.system/"

    #define JAP_PRIVATE_ROOT	"/CARD/.system/java/"

	#define JAP_TEMP_AUDIO_FOLDER   L"/CARD/.system/java_audio"

	#define JAP_TEMP_AUDIO_ROOT		"/CARD/.system/java_audio/"


	/* NOT Support dual storage feature: NAND/SD */

	#undef JAP_SUPPORT_DUAL_STORAGE

#endif /* defined(__NAND__) */


/* Support onboard user storage */

#if defined(JAP_SUPPORT_DUAL_STORAGE_NAND)

	#define JAP_DUAL_NAND_ROOT  	"/NAND/java_data/"

	#define JAP_DUAL_SD_ROOT      	"/CARD/java_data/"


	#define JAP_PUBLIC_NAND_ROOT		"/NAND/"JAVA_CONFIG_PHONE_FOLDER"/"

	#define JAP_PUBLIC_NAND_WROOT		L"/NAND/"JAVA_CONFIG_PHONE_FOLDER"/" // JAP_PUBLIC_NAND_ROOT in wide character

#endif /* defined(JAP_SUPPORT_DUAL_STORAGE_NAND) */


#if defined(JAP_SUPPORT_DUAL_STORAGE_NOR)

    #define JAP_DUAL_NOR_ROOT		"/NOR0/java_data/"

    #define JAP_DUAL_SD_ROOT		"/CARD/java_data/"


    #define JAP_PUBLIC_NOR_ROOT		"/NOR0/"JAVA_CONFIG_PHONE_FOLDER"/"

    #define JAP_PUBLIC_NOR_WROOT		L"/NOR0/"JAVA_CONFIG_PHONE_FOLDER"/" // JAP_PUBLIC_NAND_ROOT in wide character

#endif



#if defined(__DUAL_CARD__)
    #define JAP_SUPPORT_DUAL_CARD
    #define JAP_DUAL_SD_ROOT2		"/SD_2/java_data/"	

    #define JAP_PUBLIC_ROOT_C2		"/SD_2/"JAVA_CONFIG_CARD2_FOLDER"/"
    #define JAP_PUBLIC_ROOT_C2_FOR_MIDLET_QUERY		"file:///"JAVA_CONFIG_CARD2_FOLDER"/"
    #define JAP_PUBLIC_WROOT_C2	L"/SD_2/"JAVA_CONFIG_CARD2_FOLDERL L"/" // JAP_PUBLIC_ROOT_C2 in wide character
    
#endif

#define JAP_PUBLIC_ROOT		"/CARD/"JAVA_CONFIG_CARD_FOLDER"/"
#define JAP_PUBLIC_ROOT_FOR_MIDLET_QUERY		"file:///"JAVA_CONFIG_CARD_FOLDER"/"

#define JAP_PUBLIC_WROOT	L"/CARD/"JAVA_CONFIG_CARD_FOLDERL L"/" // JAP_PUBLIC_ROOT in wide character


/*It's used to determine if we need to issue jap_media_stopAllAudio*/

#define _DET_STOP


#define JAVA_FULL_SCREEN_W      (MAIN_LCD_WIDTH)

#define JAVA_FULL_SCREEN_H      (MAIN_LCD_HEIGHT)

#define JAVA_NUM_SOFTKEY        2

#ifdef __MMI_NAVIGATION_SK__
    //#define __JAVA_NAVIGATION_SK__
    #ifdef __JAVA_NAVIGATION_SK__
    #define JAVA_SOFTKEY_H          (MAIN_SK_HEIGHT)
    #define JAVA_ALLOWKEY_H          (MAIN_SK_HEIGHT>>1)
    #else
    #define JAVA_SOFTKEY_H          (MAIN_SK_HEIGHT>>1)
    #define ARROWSCROLL_SHIFT   3
    #endif
#else
    // No MMI definition , need to double the height
    //#define __JAVA_NAVIGATION_SK__
    #ifdef __JAVA_NAVIGATION_SK__
    #define JAVA_SOFTKEY_H          (MAIN_SK_HEIGHT<<1)
    #define JAVA_ALLOWKEY_H          (MAIN_SK_HEIGHT)
    #else
    #define JAVA_SOFTKEY_H          (MAIN_SK_HEIGHT)
    #define ARROWSCROLL_SHIFT   3
    #endif
#endif

#ifdef __JAVA_OAKMONT_LOW_MEMORY__
#define JAP_TERMINATEJAVA
#endif

/* Trace group and level */

#define _JAP      VEN_DBG_GROUP_0           /* The group level for Aplix Java solution */


/* Define levels by functionality */

#define _JAVATASK	    VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_0  /* Task process / init           */

#define _JAVAMSG   	    VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_1  /* Messages parsing / dump       */

#define _JAVAMMAPI	    VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_2  /* MMAPI                         */

#define _JAVAMEDIA      VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_3  /* Media control                 */

#define _JAVAAMS        VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_4  /* AMS                           */

#define _JAVAGRA        VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_5  /* GRAPHICS                      */

#define _JAVAVM         VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_6  /* Aplix VM                      */

#define _JAVAFILE       VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_7  /* File system, JSR 75: File Connection */

#define _JAVANET        VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_8  /* Network                       */

#define _JAVAPUSH       VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_9  /* Push registry                 */

#define _JAVAUTIL       VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_10 /* Utility functions             */

#define _JAVAWMA        VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_11 /* WMA                           */

#define _JAVAKBD        VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_12 /* Keyboard                      */

#define _JAVAOTA        VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_13 /* OTA                           */

#define _JAVACLDCHI     VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_14 /* CLDC-HI                   */

#define _JAVANFC        VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_15 /* JSR257 , NFC                 */

#define _JAVADBG     VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_31 /* Debug                */


#if defined(JAP_CFG_DEBUG_ON)

    #define JAP_ASSERT(x)   CUS_ASSERT(x)

    #define JAP_TRACE       ven_dbg_trace


    #ifdef __JSFILE__
    /* Use short name if source file defined __JFILE__ */
    #define __TARGET_FILE__ __JSFILE__
    #else
    #define __TARGET_FILE__ __FILE__
    #endif

    /*
        *   If you want to use JAP_ERROR() Please define __JFILE__ on the C file.. 
        *
        *   ex:: #define __JFILE__ "JkContactless.c" on JkContactless.c
        *
        */
    #define JAP_ERROR(_level_, _format_, ...) ven_dbg_trace(_level_, "[ERROR] %s (%d): " _format_,__TARGET_FILE__, __LINE__, ##__VA_ARGS__)
    
#else

    #define JAP_ASSERT(x)

    #define JAP_TRACE       1?(s8)0:ven_dbg_trace

    #define JAP_ERROR

#endif /* defined(JAP_CFG_DEBUG_ON) */




#define JWE_LOG(x,y)


/* Main/KVE task communication messages */


/* Base */

#define				JAP_MSG_BASE		(0x0100)


/* Message ID */

typedef enum

{

   JAP_MSG_KJAVACOMMAND	  = JAP_MSG_BASE + 0x01,


} JAP_MsgId_t;


/* Message */

typedef struct

{

	/* Message ID */

    JAP_MsgId_t				eMsgId;


	/* Message Body */

	union {

		KJavaActionCommand sKjavaCommand; /* JAP_MSG_KJAVACOMMAND */

	} sMsgBody;


} JAP_Msg_t;


typedef enum

{

	JAP_VM_NONE = 0,

    JAP_VM_INITIALED,   // ajms_init is called, but VM doesn't run at foreground

    JAP_VM_STARTING,    // has sent ven_stc_startRsp to framework

	JAP_VM_STARTED,

    JAP_VM_SUSPENDING,

    JAP_VM_SUSPENDED,

    JAP_VM_RESUMING,

    JAP_VM_FORCESTOPPING, // The stopping process is trigger by native system, not by JVM


	JAP_TOTAL_VM_STATUS


} jap_VMStatusE;


/**

 *  jap_get_app_handle

 *

 *  @brief  Get SDK handle.

 *

 *  @param  void

 *

 *  @retval SDK handle for Aplix Java

 */

u32 jap_get_app_handle(void);





#if defined (__V201_API__) 
typedef unsigned char		U8;	// 1 byte
typedef unsigned short      U16;    // 2 bytes

typedef unsigned long int U32;
typedef unsigned long long int U64;


#endif




#endif /* __JAP_HEAD_DEFINE_H__ */

