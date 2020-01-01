#ifndef __MMI_SEARCHAPP_ID_H__
#define __MMI_SEARCHAPP_ID_H__

typedef enum
{
    SEARCHAPP_WND_MAIN = WND_ID_APP_BASE,    
}SearchId_e;


enum
{
    ePropContainer = APP_WDG_START,
    eMainMenuWdg,
    eItemMenuWdg,
    eSearchAbsContainer,
    eSearchBgImageWidget,
    eSearchIconImgWidget,
    eSearchInputWidget,
    eSearchLoadingImgWdg,
}; 

enum 
{
	// menu item page display
	SEARCH_MENUITEM_CONTACT,
	SEARCH_MENUITEM_IMAGE,
	SEARCH_MENUITEM_MUSIC,
	SEARCH_MENUITEM_VIDEO,                
	SEARCH_MENUITEM_EBOOK,   
#ifdef __SEARCHAPP_SEARCH_CALENDAR_MMI__
	SEARCH_MENUITEM_EVENT,
#endif // End of __SEARCHAPP_SEARCH_CALENDAR_MMI__
	SEARCH_MENUITEM_MAX ,

	SEARCH_MENUITEM_MAIN,
	SEARCH_MENUITEM_MAIN_INIT,
	SEARCH_MENUITEM_MAIN_END,

}; 
typedef u16 MenuItemStatus_e;



#endif //__MMI_SEARCHAPP_ID_H__

