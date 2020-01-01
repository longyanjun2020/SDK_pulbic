/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ShowOSDFunc.h"
#include "IconDefine.h"
#include "OSDStrings.h"
#include "ColorDefine.h"
#include "MenuSetting.h"
#include "MenuDrawingFunc.h"
#include "ahc_general.h"
#include "ahc_gui.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

const unsigned char **pShowOSDStringPool = (const unsigned char **)gEnglishOSDStringPool;

/*===========================================================================
 * Main Body
 *===========================================================================*/ 

void ShowOSD_SetLanguage(UINT8 id)
{
    ShowOSD_SetLanguageEx(id, MenuSettingConfig()->uiLanguage);
}

const unsigned char *OSD_GetStringViaID(UINT32 uiStringID)
{
    return (const unsigned char *)pShowOSDStringPool[uiStringID];
}

const unsigned char *OSD_GetEnglishStringViaID(UINT32 uiStringID)
{
    return (const unsigned char *)gEnglishOSDStringPool[uiStringID];
}

void OSD_ShowString(UINT16 uwDispID, char *ascStr1, char *ascStr2, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign)
{
    GUI_RECT guiRect;

    AHC_OSDSetColor(uwDispID, uiBkColor);
    
    if(uiBkColor != OSD_COLOR_TRANSPARENT)
        AHC_OSDDrawFillRoundedRect(uwDispID, StrRECT.uiLeft, StrRECT.uiTop, StrRECT.uiLeft+StrRECT.uiWidth, StrRECT.uiTop+StrRECT.uiHeight, RECT_ROUND_RADIUS);
    
    AHC_OSDSetColor(uwDispID, uiForeColor);
    AHC_OSDSetBkColor(uwDispID, uiBkColor);
    
    guiRect.x0 = StrRECT.uiLeft;
    guiRect.y0 = StrRECT.uiTop;
    guiRect.x1 = StrRECT.uiLeft + StrRECT.uiWidth;
    guiRect.y1 = StrRECT.uiTop  + StrRECT.uiHeight;
    AHC_OSDDisableDrawFontBk(AHC_TRUE);
    
    AHC_OSDDrawTextInRect(uwDispID, (UINT8*)ascStr1, &guiRect, wTextAlign);
    
    if ((ascStr2!=NULL) && (ascStr2[0] != 0))
    {
        guiRect.y0 = StrRECT.uiTop + 40;	
        AHC_OSDDrawTextInRect(uwDispID, (UINT8*)ascStr2, &guiRect, wTextAlign);
    }
    
    AHC_OSDDisableDrawFontBk(AHC_FALSE);
}

void OSD_ShowStringPool(UINT16 uwDispID, UINT32 iStrID, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign)
{	
    ShowOSD_SetLanguage(uwDispID);
    OSD_ShowString(uwDispID, (char*)OSD_GetStringViaID(iStrID), NULL, StrRECT, uiForeColor, uiBkColor, wTextAlign);   
}

void OSD_ShowStringPool2(UINT16 uwDispID, char* Line1Str, char* Line2Str, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign)
{
    ShowOSD_SetLanguage(uwDispID);
    OSD_ShowString(uwDispID, Line1Str, Line2Str, StrRECT, uiForeColor, uiBkColor, wTextAlign);
}

void OSD_ShowStringPool3(UINT16 uwDispID, UINT32 iStrID, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign)
{
    GUI_RECT guiRect;
    
    ShowOSD_SetLanguage(uwDispID);

    AHC_OSDSetColor(uwDispID, uiForeColor);
    AHC_OSDSetBkColor(uwDispID, uiBkColor);
    
    guiRect.x0 = StrRECT.uiLeft;
    guiRect.y0 = StrRECT.uiTop;
    guiRect.x1 = StrRECT.uiLeft + StrRECT.uiWidth;
    guiRect.y1 = StrRECT.uiTop  + StrRECT.uiHeight;

    AHC_OSDDisableDrawFontBk(AHC_TRUE);  
    AHC_OSDDrawTextInRect(uwDispID, (UINT8*)OSD_GetStringViaID(iStrID), &guiRect, wTextAlign);
    AHC_OSDDisableDrawFontBk(AHC_FALSE);
}

void OSD_ShowStringPoolSlide(UINT16 uwDispID, UINT32 iStrID, RECT StrRECT, UINT32 uiForeColor, UINT32 uiBkColor, INT16 wTextAlign, int *ps)
{
#ifdef SLIDE_STRING

    GUI_RECT guiRect;

    AHC_OSDSetColor(uwDispID, uiBkColor);
    
    if(uiBkColor != OSD_COLOR_TRANSPARENT)
        AHC_OSDDrawFillRoundedRect(uwDispID, StrRECT.uiLeft, StrRECT.uiTop, StrRECT.uiLeft+StrRECT.uiWidth, StrRECT.uiTop+StrRECT.uiHeight, RECT_ROUND_RADIUS);
    
    ShowOSD_SetLanguage(uwDispID);
    AHC_OSDSetColor(uwDispID, uiForeColor);
    AHC_OSDSetBkColor(uwDispID, uiBkColor);
        
    guiRect.x0 = StrRECT.uiLeft;
    guiRect.y0 = StrRECT.uiTop;
    guiRect.x1 = StrRECT.uiLeft + StrRECT.uiWidth;
    guiRect.y1 = StrRECT.uiTop  + StrRECT.uiHeight;

    AHC_OSDDisableDrawFontBk(AHC_TRUE);
    AHC_OSDDrawTextInRectSlide(uwDispID, (UINT8*)OSD_GetStringViaID(iStrID), &guiRect, wTextAlign, ps);
    AHC_OSDDisableDrawFontBk(AHC_FALSE);
#endif
}
