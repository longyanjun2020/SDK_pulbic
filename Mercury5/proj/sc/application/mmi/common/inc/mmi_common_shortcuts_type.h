#ifndef __MMI_COMMON_SHORTCUTS_TYPE_H__
#define __MMI_COMMON_SHORTCUTS_TYPE_H__

#include "mmi_mae_common_def.h"
/*
 * Data type definition of shortcutsapp that is needed by other libraries
 * */

typedef u32 ShortcutsEntryType_e;
enum
{
    SHORTCUTS_ENTRY_SHORTCUTS = 0,
    SHORTCUTS_ENTRY_KEY_ASSIGN,
    SHORTCUTS_ENTRY_NUM_KEY,
    SHORTCUTS_ENTRY_DYNA_LINK,
    SHORTCUTS_ENTRY_MAIN_MENU_SETTING,
    SHORTCUTS_ENTRY_NAVI_KEY,
    SHORTCUTS_ENTRY_SPEED_DIAL,
#ifdef __3D_UI_SHORTCUTAPP__
    SHORTCUTS_ENTRY_ICON_LIST,
#endif      
    SHORTCUTS_ENTRY_NEW_CONTACT
};

typedef u16 ShortcutsDynaLinkType_e;
enum
{
    SHORTCUTS_DYNA_LINK_FROM_PHONEBOOK = 0,
    SHORTCUTS_DYNA_LINK_FROM_BOOKMARK
};

typedef struct ParamData_t_
{
    u32 Param1;
    u32 Param2 ;  
} ParamData_t ;

typedef struct  
{
    void *pParamData;
    ParamData_t stParamData ;
    ShortcutsEntryType_e eEntryType;
    ShortcutsDynaLinkType_e eDynaLinkType;
} ShortcutsEntryParamInfo_t;

#endif // __MMI_COMMON_SHORTCUTS_TYPE_H__
