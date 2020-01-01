#ifndef __MMI_MAPAPP_MAPVIEW_LBS_H__
#define __MMI_MAPAPP_MAPVIEW_LBS_H__

#include "fw_std.h"
#include "db_rdgeoAPI.h"
#include "db_poi.h"
#include "fw_util.h"
#include "mmi_mapapp_nameplace.h"
#include "mmi_mapapp_custom.h"
#include "mmi_mapapp_priv.h"
#include "rm_UserSetting.h"
#include "mmi_util_rtc.h"

#define LBS_STORE_PATH   L"/CARD/Maps/FileCache/"
#ifdef __DUAL_CARD__
#define LBS_STORE_PATH_2   L"/SD_2/Maps/FileCache/"
#endif
#define LBS_WINDOW_X	32

#if defined __LCM_QVGA_MMI__
    #define LBS_WINDOW_Y	32
#elif defined __LCM_WQVGA_240_400_MMI__
    #define LBS_WINDOW_Y	64
#elif defined __LCM_HVGA_320_480_MMI__      //HVGA is not yet developed, define here to pass compile option.
    #define LBS_WINDOW_Y	64
#elif defined __LCM_LANDSCAPE_WQVGA_240_400_MMI__
    #define LBS_WINDOW_Y	64
#elif defined __LCM_QCIF_PLUS_MMI__         //QCIF is not yet developed, define here to pass compile option.
    #define LBS_WINDOW_Y	64
#elif defined __LCM_LANDSCAPE_QVGA_MMI__    //LANDSCAPE is not yet developed, define here to pass compile option.
    #define LBS_WINDOW_Y	64
#elif defined __LCM_LANDSCAPE_QCIF_MMI__    //LANDSCAPE is not yet developed, define here to pass compile option.
    #define LBS_WINDOW_Y	64
#else
    #define LBS_WINDOW_Y    0
#endif

#define LBS_WINDOW_W	176
#define LBS_WINDOW_H	192
#define LBS_WINDOW_MARGIN_W         6
#define LBS_WINDOW_MARGIN_H         8
#define LBS_ICONMENU_IMAGE_W        16
#define LBS_LINE_BOX_H	            32
#define LBS_MAX_CHAR_PER_LINE_MENU       12
#define LBS_MAX_CHAR_PER_LINE_ICONMENU   10
#define LBS_MAX_CHAR_PER_LINE_2LMENU     14
void _MapmapDrawLBS(MapAppData_t* pThis);
void _MapmapDrawPageLBS(MapAppData_t* pThis);

/* XML parser */
// parser entry * reset functions
MBOOL _MapXMLTagParser(MapAppData_t* pThis, u16 *pFileName);
MVOID _MapXMLStartTagHandler(MVOID *userData, const char *name, const char **atts);
MVOID _MapXMLEndTagHandler(MVOID *userData, const char *name);
MVOID _MapXMLTextHandler(MVOID *userData, const char *text, int len);
MBOOL _MapXMLLinkParser(MapAppData_t* pThis, u16 *pFileName);
MVOID _MapXMLStartLinkHandler(MVOID *userData, const char *name, const char **atts);
MVOID _MapXMLEndLinkHandler(MVOID *userData, const char *name);
MBOOL _MapXMLExpirationParser(MapAppData_t* pThis, MHANDLE fileHandle);
MVOID _MapXMLStartExpirationHandler(MVOID *userData, const char *name, const char **atts);
MVOID _MapXMLEndExpirationHandler(MVOID *userData, const char *name);
MVOID _MapXMLInit(MapAppData_t* pThis);
MVOID _MapXMLResetContent(MapAppData_t* pThis);
MVOID _MapXMLResetContentByView(MapAppData_t* pThis);
MVOID _MapXMLResetContentByPage(MapAppData_t* pThis);
MVOID _MapXMLResetContentByHyperlink(MapAppData_t* pThis);
MVOID _MapXMLResetHyperLinkHistory(MapAppData_t* pThis);

// property parser
int     _MapXMLGetNextToken(char *str);
MAE_Ret _MapXMLPropertyHandlerTYPE(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerDIVSTYLE(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerTITLE(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerSRC(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerWIDTH(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerHEIGHT(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerHREF(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerONCLICK(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerTEMPLATESTYLE(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerLISTYLE(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLLinkPropertyHandlerSTYLE(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerATYPE(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerATEL(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerAX(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerAY(MVOID *userData, const char *name, const char *value);
MAE_Ret _MapXMLPropertyHandlerSPANSTYLE(MVOID *userData, const char *name, const char *value);

// template handler
MAE_Ret _MapXMLTemplateHandlerCUSTOM(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTemplateHandlerMENU(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTemplateHandlerIMAGETEXT(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTemplateHandler2LMENU(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTemplateHandlerICONMENU(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTemplateHandlerCUSTOMMULTIPAGES(MVOID *userData, const char *name, const char **atts);

// tag handler
MAE_Ret _MapXMLLinkTagHandlerIMG(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLLinkTagHandlerLI(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLLinkTagHandlerTEMPLATE(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLLinkTagHandlerCONTENTVIEW(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLLinkTagHandlerMENUVIEW(MVOID *userData, const char *name, const char **atts);

MAE_Ret _MapXMLTagHandlerPAGES(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerCONTENTVIEW(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerMENUVIEW(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerPAGE(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerTEMPLATE(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerDIV(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerIMG(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerSPAN(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerH1(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerH2(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerH3(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerLI(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerA(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerSTRONG(MVOID *userData, const char *name, const char **atts);
MAE_Ret _MapXMLTagHandlerBR(MVOID *userData, const char *name, const char **atts);

// utility functions
u16 *_MapGetFullURL(MapAppData_t* pThis, u16 *pURL, char *link);
u16 *_MapAddQueryString(MapAppData_t* pThis, u16 *pURL);
U32 _MapTimeGetCurrUTCTimeInSec(MapAppData_t* pThis);

// key and touch lanel handling
MBOOL _MapLBSCheckIntersect(S32 x, S32 y, S32 x1, S32 y1, S32 x2, S32 y2);
MBOOL _MapLBSCheckHyperlinkUp(MapAppData_t* pThis);
MBOOL _MapLBSCheckHyperlinkDown(MapAppData_t* pThis);
MBOOL _MapLBSCheckPageUp(MapAppData_t* pThis);
MBOOL _MapLBSCheckPageDown(MapAppData_t* pThis);
MBOOL _MapLBSCheckSelectItem(MapAppData_t* pThis);
MVOID _MapLBSCheckDownPoint(MapAppData_t* pThis, S32 x, S32 y);
MVOID _MapLBSCheckUpPoint(MapAppData_t* pThis, S32 x, S32 y);
MVOID _MapLBSCheckMovePoint(MapAppData_t* pThis, S32 x, S32 y);

/* file Cache */
u16 *_MapFileCacheGetNextInDownloadList(MapAppData_t* pThis);
MAE_Ret _MapFileCacheCheckFile(MapAppData_t* pThis, u16 *pNewFile);
MVOID _MapFileCacheAddToDownloadList(MapAppData_t* pThis, u16 *pNewFile);
MVOID _MapFileCacheConvertFilename(u16 *text, int len);
MVOID _MapFileCacheWriteFile(MapAppData_t* pThis, u16 *pFileName, char *text, int len);
MBOOL _MapFileCacheReadFile(MapAppData_t* pThis, u16 *pFileName, char **text, int *len);

#endif /* __MMI_MAPAPP_MAPVIEW_LBS_H__ */
