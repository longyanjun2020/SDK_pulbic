#ifndef __MMI_MAPAPP_MAPVIEW_H__
#define __MMI_MAPAPP_MAPVIEW_H__

#include "fw_std.h"
#include "db_rdgeoAPI.h"
#include "db_poi.h"
#include "db_district.h"
#include "fw_util.h"
#include "mmi_mapapp_nameplace.h"
#include "mmi_mapapp_custom.h"
#include "mmi_mapapp_priv.h"
#include "rm_UserSetting.h"

typedef struct T_COLOR_TAG T_COLOR_DATA, *T_COLOR_PTR;
struct T_COLOR_TAG {
	U8 r;
	U8 g;
	U8 b;
	U8 a;
};

typedef struct T_POINT_TAG T_POINT_DATA, *T_POINT_PTR;
struct T_POINT_TAG{
    S32    iX;
    S32    iY;
};

typedef struct T_EXBBOX_TAG T_EXBBOX_DATA, *T_EXBBOX_PTR;
struct T_EXBBOX_TAG
{
	T_POINT_DATA tLowLeft;
	T_POINT_DATA tUpRight;
};

typedef enum T_ROAD_TYPE_TAG
{
	T_ROAD_NORMAL = 0,
	T_ROAD_COUNTRYLINE1,      /* 省、自治區、直轄市界(線), 省級區界 */
	T_ROAD_COUNTRYLINE2,      /* 國界(線) */
	T_ROAD_COUNTRYLINE3,      /* 未定國界(線) */
	T_ROAD_COUNTRYLINE4,      /* 珊瑚礁 */
	T_ROAD_COUNTRYLINE5,	    /* 特別行政區 */
	T_ROAD_COUNTRYLINE6,      /* 海岸線 */
	T_ROAD_COUNTRYLINE7,      /* 地市級區界 */
	T_ROAD_COUNTRYLINE8,      /* 區縣級區界 */
	T_ROAD_COUNTRYLINE9,      /* 未定省界 */
	T_ROAD_RIVER,
	T_ROAD_RAIL,
} T_ROAD_TYPE;

typedef enum T_BRUSH_TYPE_TAG
{
	T_BRUSH_SOLID = 0,
	T_BRUSH_DOTTED1,     /* ----- - ----- 5111 */
	T_BRUSH_DOTTED2,     /* --- - --- - 3111 */
	T_BRUSH_DOTTED3,     /* -   -   -   131  */
	T_BRUSH_DOTTED4,     /* -----   ----- 53 */
	T_BRUSH_RAIL_SOLID,
	T_BRUSH_RAIL_DOTTED3
}T_BRUSH_TYPE;

typedef enum MAPVIEW_OP_STATE_TAG
{
	MAPVIEW_OP_POISELECTED,
	MAPVIEW_OP_BROWSEMAP,
	MAPVIEW_OP_LBS
}MAPVIEW_OP_STATE;

typedef struct RoadNameStructTAG RoadNameStruct, *RoadNameStruct_PTR;
struct RoadNameStructTAG
{
    PU16           sName;
    Vertex_st     tTextPos[10];                      /* Screen Coordinate */
    S32             iTextRotation;
};

typedef struct POIStructTAG POIStruct, *POIStruct_PTR;
struct POIStructTAG
{
	POIType_et  tType;
	Vertex_st     tPOIPos;
	U32             u32POIID;
};

/*data type of capital of each province*/
typedef struct ProvCapital_s
{
    S32 s32X;                                  /* the x coordinate       */
    S32 s32Y;                                  /* the y coordinate       */
    U16 szNameU[12];    /* the unicode-coded name */
} ProvCapital_st,*pProvCapital_st;

/* Golden, MapView funtion. */
#ifdef CHECK_MAPAPP_VERSION
MapView_Init_State Check_MapView_Version(MVOID);
#endif  // for CHECK_MAPAPP_VERSION
PU16 Get_MapView_Version(MVOID);
MapView_Init_State InitMapView(MVOID);
MapView_Init_State InitDBMemory(void);
MBOOL FinalizeMapView(MVOID);
MBOOL FinalizeDBMemory(void);
MVOID _MapSetMapBBox(MVOID);
MVOID _MapSetZoomStatus(MVOID);
MVOID _MapSetMapViewPos(S32 dx, S32 dy);
MVOID _MapResetMapViewPos(void);
MVOID _MapZoomIn(MVOID);
MVOID _MapZoomOut(MVOID);
MVOID _MapPanMap(S32 s32WhereX, S32 s32WhereY);
MVOID _MapUpdateDistrictName(MVOID);
MVOID _MapPanMapRight(MVOID);
MVOID _MapPanMapLeft(MVOID);
MVOID _MapPanMapUp(MVOID);
MVOID _MapPanMapDown(MVOID);
MVOID _MapSetDownPoint(S32 x, S32 y);
MVOID _MapSetPressPoint(S32 x, S32 y);
MVOID _MapSetUpPoint(S32 x, S32 y);
MVOID _MapConvertScreenToMapPoint(S32 iX, S32 iY, pVertex_st ptVertex);
MVOID _MapConvertMapPtToScreenPt(Vertex_st tMapPt, pVertex_st ptScrnPt);
RoadLayer_et _MapGetRoadLayerFromRdCodes(RdCodes_et eRdCodes);
MVOID mapGeoShpColor(GeoCodes_et eType, T_COLOR_DATA* ptColor);
T_ROAD_TYPE GetRoadTypeFromGeoType(GeoCodes_et eType);
MVOID _MapGetPenWidthColor(RdCodes_et eRdCodes, PS32 iPenWidth, T_COLOR_DATA* rColor, T_BRUSH_TYPE* tBrushType);
#ifdef SUPPORT_TWICE_RD_DRAWING
MVOID _MapGetPenWidthColorTW(RdCodes_et eRdCodes, PS32 iPenWidth, T_COLOR_DATA* rColor, T_BRUSH_TYPE* tBrushType);
#endif
MVOID _MapDrawRoad(MapAppData_t* pThis, S32 iPenWidth, S32 iVNum, pVertex_st pVertices, T_COLOR_DATA nColor, T_BRUSH_TYPE tBrushType);
MVOID _MapexDrawLine(MapAppData_t* pThis, pVertex_st ptSrc, pVertex_st ptDest, U8 u8LineWidth, T_COLOR_DATA tColor, T_BRUSH_TYPE tBrushType, MBOOL bHeadAndTail);
MVOID _MapexDrawPolyLine(MapAppData_t* pThis, S32 iPtNum, pVertex_st pPtArray, U8 nLineWidth, T_COLOR_DATA nColor, T_BRUSH_TYPE tBrushType);
MVOID _MapexDrawCountryLine2(MapAppData_t* pThis, S32 iPtNum, pVertex_st pPtArray, T_COLOR_DATA nColor);
MVOID _MapexDrawCountryLine3(MapAppData_t* pThis, S32 iPtNum, pVertex_st pPtArray, T_COLOR_DATA nColor);
MVOID _MapexDrawFillPolygon(MapAppData_t* pThis, S32 iPt, pVertex_st pPtArray, T_COLOR_DATA nColor);
MVOID _Mapgraphictext(MapAppData_t* pThis, u32 x1, u32 y1, u32 x2, u32 y2, const u16 *pText, u32 FontType, u32 FontCat, u32 FontColor, u32 BackColor);
MVOID _Mapgraphictextcenter(MapAppData_t* pThis, u32 x1, u32 y1, u32 x2, u32 y2, const u16 *pText, u32 FontType, u32 FontCat, u32 FontColor, u32 BackColor);
MVOID _MapRoadNameRotateByAzimuth(S32 iOriginX, S32 iOriginY, S32 iX, S32 iY, PS32 piNewX, PS32 piNewY, S32 iAzimuth);
MVOID _MapPOITimer(MapAppData_t* pThis, boolean enable, boolean bRepaint);
MVOID _MapMotionTimer(MapAppData_t* pThis, boolean enable);
MVOID _MapDrawPOIPicking(S32 iPickX, S32 iPickY);
MVOID _MapDrawPOILeftSelect(U32 u32POIID);
MVOID _MapDrawPOIRightSelect(U32 u32POIID);
MVOID _MapEnterPOISelectMode(MVOID);
MVOID _MapEnterPOIAutoFocus(MVOID);
U32 _MapGetCurrentFocusPOIID(MVOID);
MVOID _MapmapDrawNameCB(PU16 sName, pVertex_st ptVertex, S32 iTextRotation);//, S32 iCenPosX, S32 iCenPosY);
MVOID _MapmapAddPOI(S32 s32X, S32 s32Y, POIType_et etPOIType, U32 u32POIID);
MVOID _MapmapAddStName(PU16 sStName, pVertex_st atScreenPoint, S32 iPointNum);
MVOID _MapSetMapOrigin(S32 iX, S32 iY, U32 u32FocusPOIID);
RoadLayer_et _MapScaleToDBLayer(MVOID);
MAPVIEW_OP_STATE GetMapViewOpState(MVOID);
MVOID SetMapViewOpState(MAPVIEW_OP_STATE OpState);
MBOOL _MapIsEnableMotionTimer(MVOID);
PU8 _MapGetPOITelephoneNum(MVOID);
MapViewZoomLevel _MapGetCurrentZoomLevel(MVOID);
MBOOL mapPosInBBox(S32 iX, S32 iY, T_EXBBOX_PTR ptBBox);

/* Golden, kernel map drawing functions. */
MVOID _MapDrawMap(MapAppData_t* pThis);
MVOID _MapmapClipOldStName(MVOID);
MVOID _MapexClearGround(MapAppData_t* pThis);
MVOID _MapmapDrawSTBody(MapAppData_t* pThis, MBOOL bDrawEdge);
MVOID _MapmapDrawStreetName(MapAppData_t* pThis);
MVOID _MapmapDrawUI(MapAppData_t* pThis);
MVOID _MapmapDrawPOI(MVOID);

#ifdef SUPPORT_RETURN_ONE_SCREENDATA
/* Copy Screen Series */
#ifdef SOFTWARE_REDRAW_PANMAP_COPYSCRN
MVOID _MapDrawMapCopyScrn(MapAppData_t* pThis);
MVOID _MapmapDrawSTBodyCopyScrn(MapAppData_t* pThis);
#endif  // SOFTWARE_REDRAW_PANMAP_COPYSCRN
MVOID _MapexClearGroundCopyScrn(MapAppData_t* pThis);
MVOID _MapCopyScrnStateReset(MVOID);
MVOID _MapRenderPOICopyScrn(MVOID);
MVOID _MapmapDrawPOICopyScrn(MVOID);
#else //SUPPORT_RETURN_ONE_SCREENDATA
MVOID _MapStateReset(MVOID);
#endif //SUPPORT_RETURN_ONE_SCREENDATA

/* Golden, MapView call back functions. */
MVOID _MapTraverseStreetCB(PMVOID pClientData, pMVShpData_st psMVLnkData);
#ifdef SUPPORT_TWICE_RD_DRAWING
#ifdef SUPPORT_DRAWING_TW
MVOID _MapTraverseStreetCBTW(PMVOID pClientData, pMVShpData_st psMVLnkDataTW, MBOOL bTwice);
#else    /* !defined(SUPPORT_DRAWING_TW) */
MVOID _MapTraverseStreetCBTW(PMVOID pClientData, pMVShpData_st psMVLnkDataTW);
#endif    /* end of #ifdef SUPPORT_DRAWING_TW */
#endif    /* end of #ifdef SUPPORT_TWICE_RD_DRAWING */
MVOID _MapTraverseGeoShapeCB(PMVOID pvClientData, pMVShpData_st psMVGeoData);

/* Golden, MapView Utility funtions. */
MVOID _MapDrawBitmap(MapAppData_t* pThis, u32 pic, u16 x, u16 y);
MVOID _MapDrawBitmapByPath(MapAppData_t* pThis, u16 *pPath, u16 x, u16 y);
MVOID _FreeImageBuffer(void *pData);
S32 sysRound(MDOUBLE dInput);
u32 Color_RGB(u8 red, u8 green, u8 blue);
S32 mapGetDist(S32 iX1, S32 iY1, S32 iX2, S32 iY2);
PU16 ReverseStr(PU16 sStr);

MVOID _MapAddWordBBox(S32 s32ScrnX, S32 s32ScrnY);
MBOOL _MapCheckWordBBoxCollision(S32 s32ScrnX, S32 s32ScrnY);
MVOID _MapWordBBoxReset(MVOID);
MVOID _MapDrawWordBBox(MVOID);
MVOID _MapAddPOIWordBBox(S32 s32ScrnX, S32 s32ScrnY, S32 s32POINameLength);
MBOOL _MapCheckPOIWordBBoxCollision(S32 s32ScrnX, S32 s32ScrnY, S32 s32POINameLength);
MVOID _MapPOIWordBBoxReset(MVOID );
MVOID _MapDrawPOIWordBBox(MVOID);

//  Public-domain function by Darel Rex Finley, 2006.
MDOUBLE _MapPolygonArea(pVertex_st ptVertex, S32 s32PointNum);

/* Golden, Nearby POI functions. */
MBOOL   NearFilterCB(PMVOID pvClientData, POIGroup_et tGroup, POIType_et tType);
MBOOL   NearSearchCB(PMVOID pvClientData, U32 u32POI, S32 iDistance);
S32     StartNearbyPOISearch(MapAppData_t* pThis);

/* Keyword Search POI functions */
MVOID KeywordSearchEnable(MVOID);
MVOID KeywordSearchDisable(MVOID);
MBOOL KeywordSearchCB(PMVOID pvClientData, U32 u32POI);
S32 StartKeywordSearch(MapAppData_t* pThis, PU16 sKeyword, POIDistrict_et eDistrict, POIGroup_et eGroup);

MVOID	POIFreeAll(MVOID);

MBOOL	mapTraversePOICB(PMVOID pvClientData, U32 u32POIID, S32 iX, S32 iY, POIType_et tType);
MVOID	_MapRenderPOI(MVOID);
MBOOL	pngInitPOIMgr(MVOID);
MVOID   pngClosePOIMgr(MVOID);
MVOID   pngGetByPOIType(S32 iPOIType, S16 i16X, S16 i16Y);
S32     pngGetByPOITypeExt(S32 iPOIType);
MVOID   _MapSetPOIShowGroupLOD(MVOID);

/* For UI set location focus */
MVOID _MapGetOrigin(pVertex_st atMapOrigin);
MVOID _MapGetDistrictName(MVOID);
PU16  _MapGetCurrentAddress(MVOID);

MAE_Ret _MapSaveSearchPOIInfo(MAPAPP_POIInfo_t *pPOIInfo, S32 nSearchPOICount);
S32 _MapGetSearchPOIInfo(MAPAPP_POIInfo_t **pPOIInfo);
MVOID _MapDeleteSearchPOIInfo(MVOID);
MVOID _MapFreeSearchPOIInfo(MVOID);

#endif /* __MMI_MAPAPP_MAPVIEW_H__ */
