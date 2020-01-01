
/**
 * @file
 * implementation of browser layout.
 */

#ifndef __LAYOUT_MAIN_H__
#define __LAYOUT_MAIN_H__

#include <layout.h>
#include <wap_service.h>

void doImgAlign(T_DB_ContentLinkPtr pCurrent,T_DB_ImgNodePtr pImg,  T_DB_LayoutState *pState,int16_t screenWidth);
void doLineAlign(T_DB_ContentLinkPtr pCurrent,T_DB_LineNodePtr pLine,   T_DB_LayoutState *pState,int16_t screenWidth);

#endif /* __LAYOUT_MAIN_H__ */
