/**
 * @file mmi_idleapp_custom.h
 *
 * IdleApp customization file
 *
 * @version $Id: mmi_idleapp_custom.h 32026 2009-05-27 05:34:19Z christoph.kuo $
 */
#ifndef __MMI_IDLEAPP_CUSTOM_H__
#define __MMI_IDLEAPP_CUSTOM_H__

//For Wallpaper cache to MMC Card
#define __IDLEAPP_WALLPAPER_MMC_CACHE__

//For turn off wallpaper memory cache
//#define __IDLEAPP_WALLPAPER_RELEASE_MEMORY_CACHE__

//For Finger Command. Wallpaper transition animation delay
#define IDLE_BGTRANSITION_TIME 300
#define IDLE_WALLPAPER_MAX_NUM 100
#define IDLE_WALLPAPER_BATCH_SEARCH_FILE_NUM     (100) // need to consider memory usage

#define IDLE_CB_NUM_OF_REPEAT 3
#define IDLE_TS_LONGPRESS_TIME 1500

#ifdef __IDLEAPP_WALLPAPER_MMC_CACHE__
#define IDLE_WALLPAPER_CACHE_PATH L"fs:/CARD/.system/Wallpaper/"
#define IDLE_WALLPAPER_CACHE_FILEPATH L"fs:/CARD/.system/Wallpaper/%S"
#define IDLE_WALLPAPER_CACHE_FORMAT L".bmp"
#define IDLE_WALLPAPER_CACHE_MAX_FILENAME_LENGTH 65 //path(28) + MD5 Hash ID to Hex String (32) + file extension (4) + terminator (1)
#define IDLE_WALLPAPER_CACHE_CRITERIA_X RS_MAIN_LCD_WIDTH
#define IDLE_WALLPAPER_CACHE_CRITERIA_Y RS_MAIN_LCD_HEIGHT
#endif

// Enable this option for softkey using user-defined image
// Disable this option for softkey with basic style
#define __IDLE_SOFTKEY_USER_DEFINED_IMAGE__


#endif /* __MMI_IDLEAPP_CUSTOM_H__ */
