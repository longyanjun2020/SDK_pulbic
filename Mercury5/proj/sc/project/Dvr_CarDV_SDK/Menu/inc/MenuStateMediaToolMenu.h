
#ifndef _MENU_STATE_MEDIA_TOOL_MENU_H_
#define _MENU_STATE_MEDIA_TOOL_MENU_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gui.h"

/*===========================================================================
 * Enum define 
 *===========================================================================*/ 
 
typedef enum {
    ITEMID_MEDIA_SELECT=1,
    ITEMID_MEDIA_SD_CARD,
    ITEMID_MEDIA_INTERNAL,
    ITEMID_FORMAT_SD_CARD,
    ITEMID_FORMAT_CARD_YES,
    ITEMID_FORMAT_CARD_NO,
    ITEMID_FORMAT_INTMEM,
    ITEMID_FORMAT_INTMEM_YES,
    ITEMID_FORMAT_INTMEM_NO,
    ITEMID_SD_CARD_INFO,
    ITEMID_CARD_TIME_LEFT,
    ITEMID_CARD_PHOTO_LEFT,
    ITEMID_INTMEM_INFO,
    ITEMID_INT_TIME_LEFT,
    ITEMID_INT_PHOTO_LEFT
} MEDIATOOLITEMID;

#endif //_MENU_STATE_MEDIA_TOOL_MENU_H_


