#ifndef _SMP_H
#define _SMP_H


#include "sgl_types.h"
#include "sgl_gal.h"
//user defined colors
#define COLOR_focus				0x00fe9900
#define COLOR_border			0x000a3a73
#define COLOR_controlbg			0x00e7f1f3
#define COLOR_controlhili			0x0075a4c7
#define COLOR_controlborder		0x00cfe3fe
#define COLOR_wndheader		0x00074c87 //0x00248ad3


#define SCREEN_WIDTH	scrdev.scrInfo.width
#define SCREEN_HEIGHT	scrdev.scrInfo.height

#define SMP_RADIOBOX_SIZE		20
#define SMP_HEADER_HEIGHT		29
#define SMP_TOOLBAR_HEIGHT	26 
#define SMP_ITEM_HEIGHT		26 
#define SMP_ITEM_SPACE			3
#define SMP_ITEM_MARGIN		9
#define SMP_LIST_TOP_MARGIN	3
#define SMP_MSGBOX_MARGIN		8
#define SMP_MSGBOX_TBHEIHT	26
#define SMP_ITEM_LENGTH			(SCREEN_WIDTH - 2*SMP_ITEM_MARGIN)
#define SMP_ITEM_SPACE_HEIGHT		(SMP_ITEM_HEIGHT + SMP_ITEM_SPACE)
#define SMP_CONTENT_VIEW_WIDTH	SCREEN_WIDTH
#define SMP_CONTENT_VIEW_HEIGHT	(SCREEN_HEIGHT - SMP_HEADER_HEIGHT - SMP_TOOLBAR_HEIGHT)
#define SMP_CHECKBOX_SIZE			SMP_RADIOBOX_SIZE
#define SMP_SCRBAR_WIDTH			14
#define SMP_MENU_BOTTOM_HEIGHT	SMP_TOOLBAR_HEIGHT
#define SMP_LIST_LEFT_MARGIN		3	
#define SMP_LIST_ITEM_HEIGHT		SMP_ITEM_HEIGHT

/**
 * \brief button left/right space
 */
#define SMP_ITEM_CONTENT_MARGIN		4 //pixels

#define DSM_TITLE_LEN        (50)
#define MAX_SUB_MENUS         (60)

/**
 * \brief Draw radio box frame.
 *
 * \param x the left position in screen's coords
 * \param y the top position in screen's coords
 * \param checked check the radio box
 */
VOID SMP_DrawRadioBox(int x, int y, BOOL checked);

/**
 * \brief Draw check box frame.
 *
 * \param x the left position in screen's coords
 * \param y the top position in screen's coords
 * \param checked check the check box
 */
VOID SMP_DrawCheckBox(int x, int y, BOOL checked);

/**
 * \brief Draw a message box frame.
 *
 * \param x the left position of the msgbox
 * \param y the top position of the msgbox
 * \param w the width of the msgbox
 * \param h the height of the msgbox
 */
VOID SMP_DrawMsgBoxFrame(int x, int y, int w, int h);

/**
 * \brief Draw a top-level window header.
 *
 * \param x the left position of the msgbox
 * \param y the top position of the msgbox
 * \param w the width of the msgbox
 * \param h the height of the msgbox
 * \param bgcolor the background color
 * \param fgcolor the foreground color
 * \param bmpID the bitmap ID
 * \param str the title of the header
 */
VOID SMP_DrawWndHeader(int x, int y, int w, int h, Uint32 bgcolor, Uint32 fgcolor, DWORD bmpID, PCWSTR str);


#endif
