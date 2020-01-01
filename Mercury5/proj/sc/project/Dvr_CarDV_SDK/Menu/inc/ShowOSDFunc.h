#ifndef	__SHOWOSDFUNC_H__
#define	__SHOWOSDFUNC_H__

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gui.h"
#include "IconPosition.h"

/*===========================================================================
 * Enum define 
 *===========================================================================*/ 
 
typedef enum
{
    SHOWOSD_LANG_ENG = 0,	// English
    SHOWOSD_LANG_SPA,		// Spanish
    SHOWOSD_LANG_POR,		// Portuguese
    SHOWOSD_LANG_RUS,		// Russian
    SHOWOSD_LANG_CHT,		// Simple Chinese
    SHOWOSD_LANG_CHS		// Tradition Chinese
} SHOWOSD_LANGID;

/*===========================================================================
 * Extern varible
 *===========================================================================*/ 

extern  const GUI_FONT GUI_FontEnglish12;
//extern  const GUI_FONT GUI_FontSpanish12;
//extern  const GUI_FONT GUI_FontPortuguese12;
//extern  const GUI_FONT GUI_FontRussian12;
extern  const GUI_FONT GUI_FontSChinese12;
extern  const GUI_FONT GUI_FontTChinese12;
extern  const GUI_FONT GUI_FontJapanese12;
extern  const GUI_FONT GUI_FontKorean12;
extern	const GUI_FONT GUI_FontWest12;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

void OSD_ClearAll(void);
void OSD_ShowIcon(UINT16 uiDisplayID,const GUI_BITMAP Bmp, POINT Pos);
void OSD_ShowIconRect(const GUI_BITMAP Bmp, RECT posRect);
void ShowOSD_SetLanguage(UINT8 id);
const unsigned char *OSD_GetStringViaID(UINT32 uiStringID);
const unsigned char *OSD_GetEnglishStringViaID(UINT32 uiStringID);
void OSD_ShowStringPool(UINT16 uwDisplayID,UINT32 iStrID, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign);
void OSD_ShowStringPool2(UINT16 uwDisplayID, char* Line1Str, char* Line2Str, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign);
void OSD_ShowStringPool3(UINT16 uwDisplayID,UINT32 iStrID, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign);
void OSD_ShowString(UINT16 uwDispID, char *ascStr1, char *ascStr2, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign);
void OSD_ShowStringPoolSlide(UINT16 uwDisplayID, UINT32 iStrID, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign, int *ps);
void OSD_ShowStringPool(UINT16 uwDispID, UINT32 iStrID, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign);

#endif	// __SHOWOSDFUNC_H__