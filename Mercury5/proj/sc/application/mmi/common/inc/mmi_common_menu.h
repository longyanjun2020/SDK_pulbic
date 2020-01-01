/**
 * @file    mmi_common_menu.h
 * @brief
 *
 *
 * @author
 * @version $Id: mmi_common_menu.h 3696 2007-11-05 08:52:13Z eric.chen $
 */

#ifndef __MMI_COMMON_MENU_H__
#define __MMI_COMMON_MENU_H__

#include "mmi_mae_common_def.h"

enum
{
    MAINMENU_APPLET = 0,
    MAINMENU_SUBMENU,
#ifdef __APP_MMI_FM_SCHEDULE__
    MAINMENU_SUBMENU_FM,
#endif
#if defined (__MMI_KING_MOVIE_3D__) && defined(__MMI_KING_MOVIE_3D_APP_INDIE__)
    MAINMENU_SUBMENU_KMV,
#endif
    MAINMENU_SUBMENU_GAME
};
typedef u16 MainMenuStartType_e;

typedef struct
{
    MainMenuStartType_e eStartType;
    u16 nViewID;
    u16 nMenuID;
} MenuItemInfo_t;			// basic main menu item information for different menu item

// due to menu_data.c is currently removed from resource then mae_GetMenuInfoById doesn't work anymore
// so mark-off following two functions


#endif /* __MMI_COMMON_MENU_H__ */
