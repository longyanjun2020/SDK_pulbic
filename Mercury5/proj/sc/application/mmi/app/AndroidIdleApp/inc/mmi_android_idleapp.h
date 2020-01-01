/**
* @file mmi_android_idleapp.h
*
* Class Id: CLSID_ANDROID_IDLEAPP
*
*
* @version $Id: mmi_android_idleapp.h 31216 2009-05-18 09:55:14Z johnson.yeh $
*/
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
#ifndef __MMI_ANDROID_IDLEAPP_H__
#define __MMI_ANDROID_IDLEAPP_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"

/*-------------------------------------------------------------------------*/
//For Wallpaper cache to MMC Card
#define __IDLEAPP_WALLPAPER_MMC_CACHE__

#ifdef __IDLEAPP_WALLPAPER_MMC_CACHE__
#define ANDROID_IDLE_WALLPAPER_CACHE_PATH L"fs:/CARD/.system/Wallpaper/"
#define ANDROID_IDLE_WALLPAPER_CACHE_FORMAT L".bmp"
#define ANDROID_IDLE_WALLPAPER_CACHE_CRITERIA_X RS_MAIN_LCD_WIDTH
#define ANDROID_IDLE_WALLPAPER_CACHE_CRITERIA_Y RS_MAIN_LCD_HEIGHT
#endif

/*-------------------------------------------------------------------------*/


/**
 * External Events
 */
#define ANDROID_IDLEAPP_EVT_RELEASE_DESKTOP_WIDGET				(CLSID_ANDROID_IDLEAPP << 16 | 1)



/**
 * Functions
 */

MAE_Ret ANDROID_IDLEAPP_New(MAE_ClsId id, void **ppObj);

/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
#endif /*__UI_STYLE_MMI_ANDROID_IDLE__*/
#endif /* __MMI_ANDROID_IDLEAPP_H__ */
