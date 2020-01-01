#ifndef __JAVA_CONFIG_DEFINE_H__

#define __JAVA_CONFIG_DEFINE_H__

//Java config file

/* Mstar header - begin */
#include "ven_codec.h"
/* Mstar header - end */


/* Support in 128/32 platform
 *  1. Java heap / JVM heap are re-defined in kjava_sys_core.c
 *  2. Disable file cache in kjava_sys_fs.c
 *  3. Any possible RAM usage reduced method
 */

#if (SYS_PHY_RAM_SIZE_SETTING == 0x00400000) //4MB

  #define JAP_SUPPORT_128_32

#elif (SYS_PHY_RAM_SIZE_SETTING == 0x00800000) //8MB

	#define JAP_SUPPORT_128_64

#endif




#if defined(__JAVA_OAKMONT_SCOPE_JAP1_HI__ )
    #define CLDC_HI_NO_DHA
#endif
//#define CLDC_HI_DHA

//if the Aplix lib is CLDC-HI version and with or without DHA (dynamic heap allocation) 
//CLDC-HI needs more memory 
#if defined(CLDC_HI_DHA) || defined(CLDC_HI_NO_DHA)
    #define JAVA_CONFIG_EXTRA_RAM_FOR_CLDCHI (800 * 1024)
#else
    #define JAVA_CONFIG_EXTRA_RAM_FOR_CLDCHI 0
#endif


/////////////////////////////////////
//1. Java Ram size configuration////////////
/////////////////////////////////////

//The Ram size (bytes) defines the heap size allocated for Java on a mobile phone. 
// "JAVA_CONFIG_RAM_FIRST_BLOCK_SIZE_BYTE" is the Ram size (bytes) for JAVA midlet. 
// "JAVA_CONFIG_RAM_SECOND_BLOCK_SIZE_BYTE"  is the Ram size (bytes) for VM itself.
// "JAVA_CONFIG_RAM_FIRST_BLOCK_FOR_INSTALL_SIZE_BYTE" is the Ram size (bytes) for JAVA midlet installation. 
// "JAVA_CONFIG_RAM_SECOND_BLOCK_FOR_INSTALL_SIZE_BYTE"  is the Ram size (bytes) for VM during midlet installing.
//110826
// If JAVA_CONFIG_RAM_SECOND_BLOCK_FOR_INSTALL_SIZE_BYTE is too small, the certificate verification of the midlet may fail.

#ifdef JAP_SUPPORT_128_32 // 128/32
#ifdef __JAVA_OAKMONT_SCOPE_JTWI__
#define JAVA_CONFIG_RAM_FIRST_BLOCK_SIZE_BYTE                    (1000 * 1024)
#define JAVA_CONFIG_RAM_SECOND_BLOCK_SIZE_BYTE                   (100 * 1024)
#else
#define JAVA_CONFIG_RAM_FIRST_BLOCK_SIZE_BYTE                    (650 * 1024)
#define JAVA_CONFIG_RAM_SECOND_BLOCK_SIZE_BYTE                   (150 * 1024)
#endif
#else
#define JAVA_CONFIG_RAM_FIRST_BLOCK_SIZE_BYTE          (JAVA_CONFIG_EXTRA_RAM_FOR_CLDCHI + 3200 * 1024)
#define JAVA_CONFIG_RAM_SECOND_BLOCK_SIZE_BYTE         (300 * 1024)
#endif

#ifdef JAP_SUPPORT_128_32 //for 12832 product only
#define JAVA_CONFIG_RAM_FIRST_BLOCK_FOR_INSTALL_SIZE_BYTE          (400 * 1024)
#define JAVA_CONFIG_RAM_SECOND_BLOCK_FOR_INSTALL_SIZE_BYTE         (250 * 1024) // Second block cant <100
#else
#define JAVA_CONFIG_RAM_FIRST_BLOCK_FOR_INSTALL_SIZE_BYTE          (1000 * 1024)
#define JAVA_CONFIG_RAM_SECOND_BLOCK_FOR_INSTALL_SIZE_BYTE         (1000 * 1024)
#endif

//
// 110721
// JAVA_AMS_JAR_CHECK_INSTALL_MEM_CACHE_BLOCK_SIZE defined the cache size for 
// AMS ajms_reader(for check and install jar file) cache block size and the cache memory size for installing jar file copy
//
#ifdef JAP_SUPPORT_128_32 // 128/32
#define JAVA_AMS_JAR_CHECK_INSTALL_MEM_CACHE_BLOCK_SIZE 50*1024
#else
#define JAVA_AMS_JAR_CHECK_INSTALL_MEM_CACHE_BLOCK_SIZE 1024*1024
#endif

/////////////////////////////////////
//2. Java RMS size configuration////////////
/////////////////////////////////////

//"Record Management System" structure provides midlets with a persistent data store that is Java ME based.
// The RMS size (bytes) defines the maximum storage size "a single midlet" could use on the mobile phone.

#define JAVA_CONFIG_RMS_MAXIMUM_SIZE_BYTE "1024000"



/////////////////////////////////////
//3. Midlets configuration//////////////////
/////////////////////////////////////

//"JAVA_CONFIG_MIDLET_MAX_INSTALL_SUIT_COUNT" defines the maximum amount of midlets could be installed on the mobile phone.

#define JAVA_CONFIG_MIDLET_MAX_INSTALL_SUIT_COUNT  50

/////////////////////////////////////
//4. Directory configuration////////////////
/////////////////////////////////////
//"JAVA_CONFIG_PHONE_FOLDER" and "JAVA_CONFIG_PHONE_FOLDERL" definded the root folder of JAVA FS corresponding to native file system on Phone
//"JAVA_CONFIG_PHONE_FOLDER_DISPLAY_NAME" is the name of the folder in phone showing in JAVA midlet 
//"JAVA_CONFIG_CARD_FOLDER" and "JAVA_CONFIG_CARD_FOLDERL" definded the root folder of JAVA FS corresponding to native file system on T card
//"JAVA_CONFIG_CARD_FOLDER_DISPLAY_NAME" is the name of the folder in card showing in JAVA midlet 
//Please let "JAVA_CONFIG_PHONE_FOLDER" be identical to  "JAVA_CONFIG_PHONE_FOLDERL" and  "JAVA_CONFIG_CARD_FOLDER" be identical to  "JAVA_CONFIG_CARD_FOLDERL"
//"JAVA_CONFIG_CARD2_FOLDER" and "JAVA_CONFIG_CARD_FOLDERL" definded the root folder of JAVA FS corresponding to native file system on T card2
//"JAVA_CONFIG_CARD2_FOLDER_DISPLAY_NAME" is the name of the folder in card2 showing in JAVA midlet 
//Please let "JAVA_CONFIG_CARD2_FOLDER" be identical to  "JAVA_CONFIG_CARD2_FOLDERL" 


#define JAVA_CONFIG_PHONE_FOLDER "root_phone"
#define JAVA_CONFIG_PHONE_FOLDERL L"root_phone"
#define JAVA_CONFIG_PHONE_FOLDER_DISPLAY_NAME "root_phone"

#define JAVA_CONFIG_CARD_FOLDER "root_sd"
#define JAVA_CONFIG_CARD_FOLDERL L"root_sd"
#define JAVA_CONFIG_CARD_FOLDER_DISPLAY_NAME "root_sd"

#define JAVA_CONFIG_CARD2_FOLDER "root_sd2"
#define JAVA_CONFIG_CARD2_FOLDERL L"root_sd2"
#define JAVA_CONFIG_CARD2_FOLDER_DISPLAY_NAME "root_sd2"

/////////////////////////////////////
//5. Java background behavior configuration///
/////////////////////////////////////

//Media behavior configuration
//When foreground is playing music
//This configuration would define the behavior of JAVA when incoming message of QQ

//define JAVA_BACKGROUND_NOTIFY_USE_VIBRATION to trigger the vibration mechanism while message incoming
//Use JAVA_BACKGROUND_NOTIFY_USE_VIBRATION_INTERVAL_MS to control the vibration interval in millisecond (ms)

#define JAVA_BACKGROUND_NOTIFY_USE_VIBRATION
#define JAVA_BACKGROUND_NOTIFY_USE_VIBRATION_INTERVAL_MS 2000

//define JAVA_BACKGROUND_NOTIFY_USE_TONE to trigger a single tone while message incoming
//Use JAVA_BACKGROUND_NOTIFY_USE_TONE_LEVEL to set the tone
//Use JAVA_BACKGROUND_NOTIFY_USE_TONE_VOLUME to set the tone volume

#define JAVA_BACKGROUND_NOTIFY_USE_TONE
#define JAVA_BACKGROUND_NOTIFY_USE_TONE_LEVEL VEN_MEDIA_TONE_ID_9
#define JAVA_BACKGROUND_NOTIFY_USE_TONE_VOLUME VEN_MEDIA_VOLUME_MAX



#endif /* __JAVA_CONFIG_DEFINE_H__ */



