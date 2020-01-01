/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      db_rdgeoAPI.h
 *
 * DESCRIPTION
 *      This file provides the interfaces to get the data of the road or
 *      geometry background by the given bounding box.
 *
 * HISTORY
 *      2009.04.21       Mickey Chiang     Initial Version
 *      2009.04.21       Mickey Chiang     Modified the interface of dbRdGeoSetMode().
 *      2009.04.23       Mickey Chiang     1.Enlarge DB_RDGEO_MAX_VER_INGRID from 4000
 *                                           to 6000; enlarge DB_RDGEO_MAX_NAME_INGRID
 *                                           from 3000 to 6000 according to the statistic
 *                                           results.
 *                                         2.Added SUPPORT_COMBINED_DB.
 *      2009.04.24       Mickey Chiang     1.Added two new DB modes, E_DBMODE_UPDATE and
 *                                           E_DBMODE_ROUTING.
 *                                         2.Implemented dbDataGetByBoundingWithFn(),
 *                                           dbDataGetByBoundingWithFnTW() and
 *                                           dbDataGetByBounding().
 *      2009.05.08       Mickey Chiang     Added DB_RDGEO_ISROAD() and DB_RDGEO_ISGEO()
 *                                         macros.
 *      2009.05.13       Mickey Chiang     Added s32NumOfShps, s32NumOfVers and s32NumOfNames
 *                                         at struct GridShp_s to return these three values
 *                                         in one bounding screen.
 *      2009.06.16       Mickey Chiang     Modified the structure of the grid for
 *                                         the reduced DB.
 *      2009.06.23       Mickey Chiang     Add error code for retrieving APIs.
 *      2009.07.03       Mickey Chiang     Add the new definition of boundary polylines
 *                                         and change the defined value of E_L_RL_RAIL.
 *      2009.07.07       Mickey Chiang     Added 4 error codes: E_DBERRCODE_FSZ,
 *                                         E_DBERRCODE_FRD, E_DBERRCODE_FDB and
 *                                         E_DBERRCODE_FID.
 *      2009.07.14       Mickey Chiang     Added SUPPORT_NAMECACHE to determine
 *                                         whether to support name cache.
 *      2009.07.16       Mickey Chiang     Adjusted the definitions for the required
 *                                         memory space when LARGE_MEMORY_SPACE is
 *                                         declared.
 *      2009.07.30       Mickey Chiang     Modified the defintion of all of geometry
 *                                         code type.
 *      2009.09.17       Mickey Chiang     Added SUPPORT_DRAWING_TW to determine whether
 *                                         support the function with twice drawing.
 *-----------------------------------------------------------------------------
 */
#ifndef DB_RDGEOAPI_H
#define DB_RDGEOAPI_H

/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/
#define RDGEO_INVALID_ID        0xFFFFFFFF    /* invalid ID   */
#define RDGEO_UNKNOW_TYPE       0xFF          /* unknown type */

/* determine whether to support those APIs which can return the given boundary screen data once. */
/* If SUPPORT_RETURN_ONE_SCREENDATA is not defined, the application only can get the data by     */
/* registering the callback function to handle them.                                             */
#define SUPPORT_RETURN_ONE_SCREENDATA

/* determine whether to support the given memory space for need.           */
/* If SUPPORT_INPUT_MEMSPACE is not defined, use the static heaps instead. */
#define SUPPORT_INPUT_MEMSPACE

/* determine whether to support file cache. If SUPPORT_FILE_CACHE is not defined, */
/* all of file access will be executed every time.                                */
/* #define SUPPORT_FILE_CACHE */

/* determine whether to use combined DB. If SUPPORT_COMBINED_DB is defined, the */
/* road and geometry grid with the same grid ID will be combined into one.      */
#define SUPPORT_COMBINED_DB

/* determine whether to use the name cache. If SUPPORT_NAMECACHE is defined, the */
/* name cache will be used while decoding and returning the whole data.          */
/* #define SUPPORT_NAMECACHE */

/* determine whether to use the larger memory space. If LARGE_MEMORY_SPACE is defined, the */
/* system will need larger memory space at runtime.                                        */
/* #define LARGE_MEMORY_SPACE */

/* determine whether to support the drawing twice. If SUPPORT_DRAWING_TW is defined, the */
/* related APIs or functions will be provided.                                           */
#define SUPPORT_DRAWING_TW

#ifdef LARGE_MEMRORY_SPACE
#define DB_RDGEO_MAX_SHP_INGRID  4000         /* the maximal number of shapes in matched grids   */
#define DB_RDGEO_MAX_VER_INGRID  10000        /* the maximal number of vertices in matched grids */
#ifdef SUPPORT_RETURN_ONE_SCREENDATA
#define DB_RDGEO_MAX_NAME_INGRID 10000        /* the maximal number of names in matched grids    */
#endif    /* end of #ifdef SUPPORT_RETURN_ONE_SCREENDATA */
#else    /* !defined(LARGE_MEMRORY_SPACE) */
#define DB_RDGEO_MAX_SHP_INGRID  2000         /* the maximal number of shapes in matched grids   */
#define DB_RDGEO_MAX_VER_INGRID  6000         /* the maximal number of vertices in matched grids */
#ifdef SUPPORT_RETURN_ONE_SCREENDATA
#define DB_RDGEO_MAX_NAME_INGRID 8000         /* the maximal number of names in matched grids    */
#endif    /* end of #ifdef SUPPORT_RETURN_ONE_SCREENDATA */
#endif    /* end of #ifdef LARGE_MEMORY_SPACE */

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
/* the road layer type */
typedef enum RoadLayer_e
{
    E_RDLAYER_HIGHWAY=0,        /* 0.  Highway,                                高速公路               */
    E_RDLAYER_NHIGHWAY,         /* 1.  National Highway,                       國道                   */
    E_RDLAYER_EXPRESSWAY,       /* 2.  Expressway,                             快速路(環城路)         */
    E_RDLAYER_PHIGHWAY,         /* 3.  Provincial Highway,                     省道                   */
    E_RDLAYER_MAINROAD,         /* 4.  Main Road,                              主要道路(市區一級道路) */
    E_RDLAYER_SECONDARYROAD,    /* 5.  Secondary Road,                         次要道路(市區二級道路) */
    E_RDLAYER_ORDINARYROAD,     /* 6.  Ordinary Road,                          一般道路(縣鄉道)       */
    E_RDLAYER_ENTRANCEEXIT,     /* 7.  Entrance or Exit Road of A Destination, 出入目的地道路         */
    E_RDLAYER_PATH,             /* 8.  Slim Road or Path,                      細道路                 */
    E_RDLAYER_WALK,             /* 9.  Walks, Footpath or Pedestrian Street,   步行路                 */
    E_RDLAYER_MAX               /* 10. Unknown Layer,                          未知等級               */
} RoadLayer_et,*pRoadLayer_et;

#define E_RDLAYER_FIRST E_RDLAYER_HIGHWAY    /* the first road layer */
#define E_RDLAYER_LAST  E_RDLAYER_WALK       /* the last road layer  */

/* the geometry background type */
typedef enum GeoLayer_e
{
    E_GEOLAYER_RAIL=0,         /* 0.  Railway,              鐵路         */
    E_GEOLAYER_ADMINLINE,      /* 1.  Administrative Line,  行政區劃(線) */
    E_GEOLAYER_SINGLEBUILD,    /* 2.  Single Building,      獨立建築物   */
    E_GEOLAYER_MASS,           /* 3.  Mass Facilities,      大眾設施     */
    E_GEOLAYER_CULTURAL,       /* 4.  Cultural Facilities,  文化設施     */
    E_GEOLAYER_LARGEBUILD,     /* 5.  Large Building Area,  大型建築區   */
    E_GEOLAYER_LEISURE,        /* 6.  Leisure Facilities,   休閒設施     */
    E_GEOLAYER_TRANSPORT,      /* 7.  Transport Facilities, 交通設施     */
    E_GEOLAYER_VEGETATION,     /* 8.  Vegetation,           植被         */
    E_GEOLAYER_WATER,          /* 9.  Water,                水系         */
    E_GEOLAYER_ADMINAREA,      /* 10. Administrative Area,  行政區劃(面) */
    E_GEOLAYER_ISLAND,         /* 11. Island,               島嶼         */
    E_GEOLAYER_MAX             /* 12. Unknown Layer,        未知等級     */
} GeoLayer_et,*pGeoLayer_et;

#define E_GEOLAYER_FIRST E_GEOLAYER_RAIL      /* the first geometry layer */
#define E_GEOLAYER_LAST  E_GEOLAYER_ISLAND    /* the last geometry layer  */

/* the road code type */
typedef enum RdCodes_e
{
    E_L_RD_HIGHWAY       =0xB7,    /* 一般道路:           高速公路               */
    E_L_RD_FHIGHWAY      =0xB5,    /* 擺渡路線:           高速公路               */
    E_L_RD_NHIGHWAY      =0xB3,    /* 一般道路:           國道                   */
    E_L_RD_FNHIGHWAY     =0xB1,    /* 擺渡路線:           國道                   */
    E_L_RD_EXPRESSWAY    =0xAF,    /* 一般道路:           快速路(環城路)         */
    E_L_RD_FEXPRESSWAY   =0xAD,    /* 擺渡路線:           快速路(環城路)         */
    E_L_RD_PHIGHWAY      =0xAB,    /* 一般道路:           省道                   */
    E_L_RD_FPHIGHWAY     =0xA9,    /* 擺渡路線:           省道                   */
    E_L_RD_MAINROAD      =0xA3,    /* 一般道路:           主要道路(市區一級道路) */
    E_L_RD_PMAINROAD     =0xA1,    /* 擺渡路線:           主要道路(市區一級道路) */
    E_L_RD_SECONDARYROAD =0x9F,    /* 一般道路:           次要道路(市區二級道路) */
    E_L_RD_FSECONDARYROAD=0x9D,    /* 擺渡路線:           次要道路(市區二級道路) */
    E_L_RD_ORDINARYROAD  =0x9B,    /* 一般道路:           一般道路(縣鄉道)       */
    E_L_RD_FORDINARYROAD =0x99,    /* 擺渡路線:           一般道路(縣鄉道)       */
    E_L_RD_ENTRANCEEXIT  =0x97,    /* 一般道路:           出入目的地道路         */
    E_L_RD_FENTRANCEEXIT =0x95,    /* 擺渡路線:           出入目的地道路         */
    E_L_RD_PATH          =0x93,    /* 一般道路:           細道路                 */
    E_L_RD_FPATH         =0x91,    /* 擺渡路線:           細道路                 */
    E_L_RD_WALK          =0x8F,    /* 步行道路:           步行路                 */
    E_L_RD_FWALK         =0x8D,    /* 步行道路(擺渡路線): 步行路                 */
    E_L_RD_CROSSSTREET   =0x8B,    /* 步行道路:           人行橫道               */
    E_L_RD_FCROSSSTREET  =0x89,    /* 步行道路(擺渡路線): 人行橫道               */
    E_L_RD_FLYOVER       =0xA7,    /* 步行道路:           過街天橋               */
    E_L_RD_FFLYOVER      =0xA5,    /* 步行道路(擺渡路線): 過街天橋               */
    E_L_RD_UNDERPASS     =0x87,    /* 步行道路:           地下通道               */
    E_L_RD_FUNDERPASS    =0x85,    /* 步行道路(擺渡路線): 地下通道               */
    E_L_RD_RAILWAYPASS   =0x83,    /* 步行道路:           地鐵通道               */
    E_L_RD_FRAILWAYPASS  =0x81     /* 步行道路(擺渡路線): 地鐵通道               */
} RdCodes_et,*pRdCodes_et;

/* the geometry code type */
typedef enum GeoCodes_e
{
    /* Polygon */
    /* 行政區劃 Administrative Area */
    E_G_AD_NATION=0x02,    /* 1010201 行政區劃(面): 國家                                         */
    E_G_AD_MUNICI=0x04,    /* 1010202 行政區劃(面): 一級(省, 自治區, 直轄市)                     */
    E_G_AD_PREFEC=0x06,    /* 1010203 行政區劃(面): 二級(地區, 盟, 自治州, 地級市)               */
    E_G_AD_COUNTR=0x08,    /* 1010204 行政區劃(面): 三級(縣, 自治縣, 旗, 自治旗, 縣級市, 市轄區) */
    /* 水系 Water Area */
    E_G_WA_RESERV=0x0A,    /* 1020101 水庫                                                       */
    E_G_WA_LAKE  =0x0C,    /* 1020102 湖泊/池塘1(一萬平方公尺以上)                               */
    E_G_WA_POND  =0x0E,    /* 1020103 湖泊/池塘2(一萬平方公尺以下, 2500平方公尺以上)             */
    E_G_WA_CANAL =0x10,    /* 1020104 運河(面)                                                   */
    E_G_WA_RIVER =0x12,    /* 1020106 河流(面)                                                   */
    E_G_WA_OCEAN =0x14,    /* 1020108 海, 洋(面)                                                 */
    /* 土地覆蓋與利用 - 植被 Vegetation */
    E_G_VE_URBAN =0x16,    /* 1030101 城市綠地                                                   */
    E_G_VE_FOREST=0x18,    /* 1030102 森林                                                       */
    E_G_VE_MEADOW=0x1A,    /* 1030103 自然草地                                                   */
    E_G_VE_PARK  =0x1C,    /* 1030104 公園/花園                                                  */
    /* 土地覆蓋與利用 - 島嶼 Island */
    E_G_IS_ISLAND=0x00,    /* 1040101 島嶼                                                       */
    /* 土地覆蓋與利用 - 交通設施 Transport Facilities */
    E_G_TF_AIRPOR=0x1E,    /* 1060101 機場                                                       */
    E_G_TF_TRAINS=0x20,    /* 1060102 火車站                                                     */
    /* 土地覆蓋與利用 - 文化設施 Cultural Facilities */
    E_G_CF_RELIGI=0x38,    /* 1060201 宗教                                                       */
    E_G_CF_GALLER=0x3A,    /* 1060202 美術館                                                     */
    E_G_CF_LIBRAR=0x3C,    /* 1060203 圖書館                                                     */
    E_G_CF_MUSEUM=0x3E,    /* 1060204 博物館                                                     */
    E_G_CF_EXHIBI=0x40,    /* 1060205 展覽館                                                     */
    E_G_CF_ARTMUS=0x42,    /* 1060206 藝術館                                                     */
    E_G_CF_STMUSE=0x44,    /* 1060207 科技館                                                     */
    E_G_CF_MEMORI=0x46,    /* 1060208 紀念館                                                     */
    E_G_CF_HALL  =0x48,    /* 1060209 文化活動場館                                               */
    E_G_CF_UNIVER=0x4A,    /* 1060211 大學                                                       */
    E_G_CF_SCHOOL=0x4C,    /* 1060212 中學                                                       */
    /* 土地覆蓋與利用 - 休閒設施 Leisure Facilities */
    E_G_LF_AMUSEM=0x22,    /* 1060301 遊樂園                                                     */
    E_G_LF_GOLF  =0x24,    /* 1060302 高爾夫球場                                                 */
    E_G_LF_SPORTS=0x26,    /* 1060303 運動場所                                                   */
    E_G_LF_ENTERT=0x28,    /* 1060304 娛樂區                                                     */
    E_G_LF_THEATE=0x2A,    /* 1060305 影劇院                                                     */
    E_G_LF_ZOO   =0x2C,    /* 1060306 動物園                                                     */
    E_G_LF_SQUARE=0x2E,    /* 1060307 廣場                                                       */
    E_G_LF_VIEWPT=0x30,    /* 1060308 觀光景點                                                   */
    E_G_LF_PLAYGD=0x32,    /* 1060309 運動場                                                     */
    /* 土地覆蓋與利用 - 大眾設施 Mass Facilities */
    E_G_MF_GOVERN=0x4E,    /* 1060401 政府                                                       */
    E_G_MF_HOSPIT=0x50,    /* 1060402 醫院                                                       */
    E_G_MF_HOTEL =0x52,    /* 1060403 賓館酒店                                                   */
    /* 土地覆蓋與利用 - 大型建築區 Large Building Area */
    E_G_LB_COMMER=0x34,    /* 1060501 商業區                                                     */
    E_G_LB_INDUST=0x36,    /* 1060502 工業區                                                     */
    /* 土地覆蓋與利用 - 獨立建築物 Single Building */
    E_G_SB_GOVERN=0x54,    /* 1060601 政府建築物(500平方公尺及其以上)                            */
    E_G_SB_LANDMA=0x56,    /* 1060602 主要目標物(面積1平方公尺以上及標誌性建築物)                */
    E_G_SB_OTHERS=0x58,    /* 1999999 其它建築物                                                 */
    /* Polyline */
    /* 行政區劃 Administrative Line */
    E_L_AD_BNATIO=0x61,    /* 1010101 行政區界(線): 國界                                         */
    E_L_AD_BUNDEF=0x63,    /* 1010102 行政區界(線): 未定國界                                     */
    E_L_AD_BMUNIC=0x65,    /* 1010103 行政區界(線): 省級區界                                     */
    E_L_AD_BCITY =0x67,    /* 1010104 行政區界(線): 市級區界                                     */
    E_L_AD_BCOUNT=0x69,    /* 1010105 行政區界(線): 區縣級區界                                   */
    E_L_AD_BCOAST=0x6B,    /* 1010106 行政區界(線): 海岸線                                       */
    E_L_AD_BSPECI=0x6D,    /* 1010107 行政區界(線): 特別行政區                                   */
    E_L_AD_BUNDPR=0x6F,    /* 1010108 行政區界(線): 未定省界                                     */
    /* 鐵路 Railway */
    E_L_RL_RAIL  =0x71,    /* 1050101 鐵路                                                       */
    /* 水系 Wate Line */
    E_L_WA_CANAL =0x11,    /* 1020105 運河(線)                                                   */
    E_L_WA_RIVER =0x13,    /* 1020107 河流(線)                                                   */
    /* 土地覆蓋與利用 - 島嶼 */
    E_L_IS_ISLAND=0x01,    /* 1040102 島嶼(線)                                                   */
    /* 土地覆蓋與利用 - 文化設施 Cultural Facilities */
    E_L_CF_ANCIEN=0x49     /* 1060210 城牆                                                       */
} GeoCodes_et,*pGeoCodes_et;

#ifdef SUPPORT_INPUT_MEMSPACE
/* the manipulation mode of the DB module */
typedef enum DBMode_e
{
    E_DBMODE_FINAL=0,    /* finalization   */
    E_DBMODE_MAPVIEW,    /* map view       */
    E_DBMODE_KSEARCH,    /* keyword search */
    E_DBMODE_UPDATE,     /* DB update      */
    E_DBMODE_ROUTING     /* routing        */
} DBMode_et,*pDBMode_et;
#endif    /* end of #ifdef SUPPORT_INPUT_MEMSPACE */

#ifdef SUPPORT_COMBINED_DB
/* the DB session type */
typedef enum DBSession_e
{
    E_DBSESSION_GE=0,    /* the combined DB session for geometry                */
    E_DBSESSION_RD,      /* the combined DB session for road                    */
    E_DBSESSION_BOTH     /* the combined DB sessions for both geometry and road */
} DBSession_et,*pDBSession_et;
#endif    /* end of #ifdef SUPPORT_COMBINED_DB */

/* the error code type */
typedef enum DBErrCode_e
{
    E_DBERRCODE_NON=0,    /* no error                          */
    E_DBERRCODE_MEM,      /* no enough memory space            */
    E_DBERRCODE_INI,      /* no initialization                 */
    E_DBERRCODE_PAR,      /* wrong parameters                  */
    E_DBERRCODE_SIZ,      /* wrong grid size calculation       */
    E_DBERRCODE_FRD,      /* wrong file reading                */
    E_DBERRCODE_ARS,      /* overflow for shape array          */
    E_DBERRCODE_ARV,      /* overflow for vertex array         */
    E_DBERRCODE_ARN,      /* overflow for name array           */
    E_DBERRCODE_BDE,      /* decoding error for bounding shape */
    E_DBERRCODE_DEC,      /* decoding error                    */
    E_DBERRCODE_FSZ,      /* too small index file size         */
    E_DBERRCODE_FIS,      /* the wrong loaded index data size  */
    E_DBERRCODE_FDB,      /* failed to open DB file            */
    E_DBERRCODE_FID       /* wrong function ID                 */
} DBErrCode_et,*pDBErrCode_et;

/* data structure of one shape attribute */
typedef struct OneShpAttri_s
{
    S32  s32VerCount;    /* the number of vertices                            */
    PU16 pu16Name1;      /* the pointer to the name table for the name 2      */
    PU16 pu16Name2;      /* the pointer to the name table for the name 1      */
    PU16 pu16NameNum;    /* the pointer to the name table for the name number */
} OneShpAttri_st,*pOneShpAttri_st;

#if defined(SUPPORT_DRAWING_TW)||defined(SUPPORT_RETURN_ONE_SCREENDATA)
/* data structure of shapes in one grid */
typedef struct GridShp_s
{
#if defined(FOR_UNIT_TEST)&&defined(SUPPORT_RETURN_ONE_SCREENDATA)
    S32            s32NumOfShps;                               /* the number of shapes                                        */
    S32            s32NumOfVers;                               /* the number of vertices                                      */
    S32            s32NumOfNames;                              /* the number of names                                         */
#endif    /* end of #if defined(FOR_UNIT_TEST)&&defined(SUPPORT_RETURN_ONE_SCREENDATA) */
    MBOOL          bCovered;                                   /* depict whether the boundary polygons cover the whole screen */
    U16            u16NumOfClass;                              /* the number of classes                                       */
    U8             au8Class[DB_RDGEO_MAX_SHP_INGRID-2];        /* the class types                                             */
    U16            au16ClassCount[DB_RDGEO_MAX_SHP_INGRID];    /* the number of shapes in every class                         */
    OneShpAttri_st asShpAttri[DB_RDGEO_MAX_SHP_INGRID];        /* the attributes for every shape in matched grids             */
    S16            as16VerIdx[DB_RDGEO_MAX_SHP_INGRID];        /* the starting vertex index of every shape                    */
    Vertex_st      asVertices[DB_RDGEO_MAX_VER_INGRID];        /* the vertices in matched grids                               */
#ifdef SUPPORT_RETURN_ONE_SCREENDATA
    U16            au16Names[DB_RDGEO_MAX_NAME_INGRID+30];     /* the names in matched grids                      */
#endif    /* end of #ifdef SUPPORT_RETURN_ONE_SCREENDATA */
} GridShp_st,*pGridShp_st;
#else    /* !defined(SUPPORT_DRAWING_TW)&&!defined(SUPPORT_RETURN_ONE_SCREENDATA) */
#define GridShp_st  MVOID
#define pGridShp_st PMVOID
#endif    /* end of #if defined(SUPPORT_DRAWING_TW)||defined(SUPPORT_RETURN_ONE_SCREENDATA) */

/* data structure of mapview road data */
typedef struct MVShpData_s
{
#ifdef FOR_UNIT_TEST
    U32             u32GridID;     /* the grid ID                           */
    S32             s32ShpIdx;     /* the index of the shape                */
#endif    /* end of #ifdef FOR_UNIT_TEST */
    U32             u32Class;      /* the shape class                       */
    pOneShpAttri_st psShpAttri;    /* the pointer to the shape attribute    */
    pVertex_st      psVertices;    /* the pointer to the shape spatial data */
} MVShpData_st,*pMVShpData_st;

/*
 *  Syntax:
 *      MVOID (*MapViewShpDataHandler_pfn)(PMVOID pvClientData,pMVShpData_st psMVShpData);
 *
 *  Purpose:
 *      Handle the mapView shape data for every matched shape.
 *
 *  Parameters:
 *      pvClientData
 *          [in] The caller's client data.
 *      psMVShpData
 *          [in] The matched shape data.
 *
 *  Return Values:
 *      None.
 */
typedef MVOID (*MapViewShpDataHandler_pfn)(PMVOID,pMVShpData_st);

#ifdef SUPPORT_DRAWING_TW
/*
 *  Syntax:
 *      MVOID (*MapViewShpDataHandlerEx_pfn)(PMVOID pvClientData,pMVShpData_st psMVShpData,
 *                                           MBOOL bTwice);
 *
 *  Purpose:
 *      Handle the mapView shape data for every matched shape twice.
 *
 *  Parameters:
 *      pvClientData
 *          [in] The caller's client data.
 *      psMVShpData
 *          [in] The matched shape data.
 *      bTwice
 *          [in] Depict whether it's the 2nd run.
 *
 *  Return Values:
 *      None.
 */
typedef MVOID (*MapViewShpDataHandlerEx_pfn)(PMVOID,pMVShpData_st,MBOOL);
#endif    /* end of #ifdef SUPPORT_DRAWING_TW */

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
/* judge whether the code of the input shape implies to polyline or not (polygon) */
#define DB_RDGEO_ISPOLYLINE(x)    ((x)&1)
/* judge whether the code of the input road implies to ferry or not */
/* bit7bit1 = 11 -> road; bit7bit1 = 10 -> ferry */
#define DB_RD_ISFERRY(x)          (0x80==((x)&0x82))
#define DB_RD_ISROAD(x)           (0x82==((x)&0x82))
/* judge whether the code of the input shape implies to road */
#define DB_RDGEO_ISROAD(x)        (0x80==((x)&0x80))
/* judge whether the code of the input shape implies to geometry */
#define DB_RDGEO_ISGEO(x)         (0x00==((x)&0x80))

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef SUPPORT_INPUT_MEMSPACE
/*
 *  Syntax:
 *      MBOOL dbRdGeoSetMode(DBMode_et eMode,PU16 pu16RootDIR,PMVOID pvInitMemAddr,S32 s32MemSize,
 *                           PMVOID *ppvModuleAddr,PS32 ps32ModuleAddrSize);
 *
 *  Purpose:
 *      Set the manipulating mode for memory sharing among road/geometry and other modules.
 *
 *  Parameters:
 *      eMode
 *          [in] The manipulating mode.
 *               E_DBMODE_FINAL is for finalization.
 *               E_DBMODE_MAPVIEW is for map view.
 *               E_DBMODE_KSEARCH is for keyword searching.
 *               E_DBMODE_UPDATE is for DB updating.
 *               E_DBMODE_ROUTING is for routing.
 *      pu16RootDIR
 *          [in] The root path of road/geometry DB.
 *      pvInitMemAddr
 *          [in] The address of the given memory space.
 *      s32MemSize
 *          [in] The size of the given memory space.
 *      ppvModuleAddr
 *          [out] The address of the other module requested memory space.
 *      ps32ModuleAddrSize
 *          [out] The size of the other module requested memory space.
 *
 *  Return Values
 *      MBOOL_TRUE:  success.
 *      MBOOL_FALSE: fail.
 */
MBOOL dbRdGeoSetMode(DBMode_et eMode,PU16 pu16RootDIR,
                     PMVOID pvInitMemAddr,S32 s32MemSize,
                     PMVOID *ppvModuleAddr,PS32 ps32ModuleAddrSize);

#else    /* !defined(SUPPORT_INPUT_MEMSPACE) */
/*
 *  Syntax:
 *      MBOOL dbRdGeoInitialize(PU16 pu16RootDIR);
 *
 *  Purpose:
 *      Initialize the road/geometry DB API.
 *
 *  Parameters:
 *      pu16RootDIR
 *          [in] The root path of road/geometry DB.
 *
 *  Return Values
 *      MBOOL_TRUE:  success.
 *      MBOOL_FALSE: fail.
 */
MBOOL dbRdGeoInitialize(PU16 pu16RootDIR);

/*
 *  Syntax:
 *      MVOID dbRdGeoFinalize(MVOID);
 *
 *  Purpose:
 *      Finalize the road/geometry DB API.
 *
 *  Parameters:
 *      None.
 *
 *  Return Values
 *      None.
 */
MVOID dbRdGeoFinalize(MVOID);

#endif    /* end of #ifdef SUPPORT_INPUT_MEMSPACE */
#ifdef SUPPORT_COMBINED_DB
/*
 *  Syntax:
 *      U32 dbRdGeoGridIDGet(S32 s32X,S32 s32Y,S32 s32LOD);
 *
 *  Purpose:
 *      Get the grid ID by the given (x,y) and LOD.
 *
 *  Parameters:
 *      s32X
 *          [in] The given x coordinate.
 *      s32Y
 *          [in] The given y coordinate.
 *      s32LOD
 *          [in] The level of degree.
 *
 *  Return Values
 *      The grid ID with 32 bits format as below.
 *          bit31      : 0 (don't care)
 *          bit30~bit28: LOD
 *          bit26~bit16: The grid group ID
 *          bit15~bit0 : The local grid ID in one grid group
 */
U32 dbRdGeoGridIDGet(S32 s32X,S32 s32Y,S32 s32LOD);
#else    /* !defined(SUPPORT_COMBINED_DB) */
/*
 *  Syntax:
 *      U32 dbRdGeoGridIDGet(S32 s32X,S32 s32Y,S32 s32LOD,MBOOL bRoad);
 *
 *  Purpose:
 *      Get the road or geometry grid ID by the given (x,y) and LOD.
 *
 *  Parameters:
 *      s32X
 *          [in] The given x coordinate.
 *      s32Y
 *          [in] The given y coordinate.
 *      s32LOD
 *          [in] The level of degree.
 *      bRoad
 *          [in] Depict whether it's the road DB or geometry DB.
 *
 *  Return Values
 *      The grid ID with 32 bits format as below.
 *          bit31      : Type (0-> road; 1-> geometry)
 *          bit30~bit28: LOD
 *          bit26~bit16: The grid group ID
 *          bit15~bit0 : The local grid ID in one grid group
 */
U32 dbRdGeoGridIDGet(S32 s32X,S32 s32Y,S32 s32LOD,MBOOL bRoad);
#endif    /* end of #ifdef SUPPORT_COMBINED_DB */

/*
 *  Syntax:
 *      S32 dbRdDataGetByBoundingWithFn(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
 *                                      RoadLayer_et eRdFilter,PMVOID pvClientData,
 *                                      MapViewShpDataHandler_pfn pfnHandler,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Use the registered callback function to handle the data from the road DB by the
 *      given boundary box.
 *
 *  Parameters:
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32LOD
 *          [in] The level of degree.
 *      eRdFilter
 *          [in] The filter of the road level.
 *      pvClientData
 *          [in] The caller's client data.
 *      pfnHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The number of the matched road shape data.
 */
S32 dbRdDataGetByBoundingWithFn(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,RoadLayer_et eRdFilter,
                                PMVOID pvClientData,MapViewShpDataHandler_pfn pfnHandler,
                                pDBErrCode_et peErrCode);

#ifdef SUPPORT_DRAWING_TW
/*
 *  Syntax:
 *      S32 dbRdDataGetByBoundingWithFnTW(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
 *                                        RoadLayer_et eRdFilter,RoadLayer_et eRdTWFilter,
 *                                        PMVOID pvClientData,MapViewShpDataHandlerEx_pfn pfnHandler,
 *                                        pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Use the registered callback function to handle the data from the road DB by the
 *      given boundary box twice.
 *
 *  Parameters:
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32LOD
 *          [in] The level of degree.
 *      eRdFilter
 *          [in] The filter of the road level.
 *      eRdTWFilter
 *          [in] The filter of the road level for twice handling.
 *      pvClientData
 *          [in] The caller's client data.
 *      pfnHandler
 *          [in] The callback function to handle the matched mapview shape data twice.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The number of the matched road shape data.
 */
S32 dbRdDataGetByBoundingWithFnTW(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,RoadLayer_et eRdFilter,
                                  RoadLayer_et eRdTWFilter,PMVOID pvClientData,
                                  MapViewShpDataHandlerEx_pfn pfnHandler,pDBErrCode_et peErrCode);
#endif    /* end of #ifdef SUPPORT_DRAWING_TW */

/*
 *  Syntax:
 *      S32 dbGeoDataGetByBoundingWithFn(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
 *                                       GeoLayer_et eGeoFilter,PMVOID pvClientData,
 *                                       MapViewShpDataHandler_pfn pfnHandler,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Use the registered callback function to handle the data from the geometry DB by the
 *      given boundary box.
 *
 *  Parameters:
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32LOD
 *          [in] The level of degree.
 *      eGeoFilter
 *          [in] The filter of the geometry level.
 *      pvClientData
 *          [in] The caller's client data.
 *      pfnHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The number of the matched geometry shape data.
 */
S32 dbGeoDataGetByBoundingWithFn(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,GeoLayer_et eGeoFilter,
                                 PMVOID pvClientData,MapViewShpDataHandler_pfn pfnHandler,
                                 pDBErrCode_et peErrCode);

#ifdef SUPPORT_RETURN_ONE_SCREENDATA
/*
 *  Syntax:
 *      pGridShp_st dbRdDataGetByBounding(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
 *                                        RoadLayer_et eRdFilter,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Get the shape data from the road DB by the given boundary box.
 *
 *  Parameters:
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32LOD
 *          [in] The level of degree.
 *      eRdFilter
 *          [in] The filter of the road level.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The matched road shape data.
 */
pGridShp_st dbRdDataGetByBounding(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
                                  RoadLayer_et eRdFilter,pDBErrCode_et peErrCode);

/*
 *  Syntax:
 *      pGridShp_st dbGeoDataGetByBounding(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
 *                                         GeoLayer_et eGeoFilter,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Get the data from the geometry DB by the given boundary box.
 *
 *  Parameters:
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32LOD
 *          [in] The level of degree.
 *      eGeoFilter
 *          [in] The filter of the geometry level.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The matched geometry shape data.
 */
pGridShp_st dbGeoDataGetByBounding(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
                                   GeoLayer_et eGeoFilter,pDBErrCode_et peErrCode);

#endif    /* end of #ifdef SUPPORT_RETURN_ONE_SCREENDATA */

#ifdef SUPPORT_COMBINED_DB
/*
 *  Syntax:
 *      S32 dbDataGetByBoundingWithFn(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
 *                                    RoadLayer_et eRdFilter,GeoLayer_et eGeoFilter,
 *                                    PMVOID pvRdClientData,MapViewShpDataHandler_pfn pfnRdHandler,
 *                                    PMVOID pvGeClientData,MapViewShpDataHandler_pfn pfnGeHandler,
 *                                    pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Use the registered callback function to handle the data from the road and geometry DB by the
 *      given boundary box.
 *
 *  Parameters:
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32LOD
 *          [in] The level of degree.
 *      eRdFilter
 *          [in] The filter of the road level.
 *      eGeoFilter
 *          [in] The filter of the geometry level.
 *      pvRdClientData
 *          [in] The caller's client data for road handing
 *      pfnRdHandler
 *          [in] The callback function to handle the matched mapview road data.
 *      pvGeClientData
 *          [in] The caller's client data for geometry handing
 *      pfnGeHandler
 *          [in] The callback function to handle the matched mapview geometry data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The number of the matched road and geometry shape data.
 */
S32 dbDataGetByBoundingWithFn(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
                              RoadLayer_et eRdFilter,GeoLayer_et eGeoFilter,
                              PMVOID pvRdClientData,MapViewShpDataHandler_pfn pfnRdHandler,
                              PMVOID pvGeClientData,MapViewShpDataHandler_pfn pfnGeHandler,
                              pDBErrCode_et peErrCode);

#ifdef SUPPORT_DRAWING_TW
/*
 *  Syntax:
 *      S32 dbDataGetByBoundingWithFnTW(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
 *                                      RoadLayer_et eRdFilter,RoadLayer_et eRdTWFilter,
 *                                      GeoLayer_et eGeoFilter,
 *                                      PMVOID pvRdClientData,MapViewShpDataHandlerEx_pfn pfnRdHandler,
 *                                      PMVOID pvGeClientData,MapViewShpDataHandler_pfn pfnGeHandler,
 *                                      pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Use the registered callback function to handle the data from the road and geometry DB by the
 *      given boundary box.
 *
 *  Parameters:
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32LOD
 *          [in] The level of degree.
 *      eRdFilter
 *          [in] The filter of the road level.
 *      eRdTWFilter
 *          [in] The filter of the road level for twice handling.
 *      eGeoFilter
 *          [in] The filter of the geometry level.
 *      pvRdClientData
 *          [in] The caller's client data for road handing
 *      pfnRdHandler
 *          [in] The callback function to handle the matched mapview road data twice.
 *      pvGeClientData
 *          [in] The caller's client data for geometry handing
 *      pfnGeHandler
 *          [in] The callback function to handle the matched mapview geometry data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The number of the matched road and geometry shape data.
 */
S32 dbDataGetByBoundingWithFnTW(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
                                RoadLayer_et eRdFilter,RoadLayer_et eRdTWFilter,GeoLayer_et eGeoFilter,
                                PMVOID pvRdClientData,MapViewShpDataHandlerEx_pfn pfnRdHandler,
                                PMVOID pvGeClientData,MapViewShpDataHandler_pfn pfnGeHandler,
                                pDBErrCode_et peErrCode);
#endif    /* end of #ifdef SUPPORT_DRAWING_TW */

#ifdef SUPPORT_RETURN_ONE_SCREENDATA
/*
 *  Syntax:
 *      pGridShp_st dbDataGetByBounding(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
 *                              RoadLayer_et eRdFilter,GeoLayer_et eGeoFilter,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Get the shape data from the road and geometry DB by the given boundary box.
 *
 *  Parameters:
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32LOD
 *          [in] The level of degree.
 *      eRdFilter
 *          [in] The filter of the road level.
 *      eGeoFilter
 *          [in] The filter of the geometry level.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The matched road/geometry shape data.
 */
pGridShp_st dbDataGetByBounding(S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32LOD,
                                RoadLayer_et eRdFilter,GeoLayer_et eGeoFilter,pDBErrCode_et peErrCode);
#endif    /* end of #ifdef SUPPORT_RETURN_ONE_SCREENDATA */
#endif    /* end of #ifdef SUPPORT_COMBINED_DB */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* end of #ifndef DB_RDGEOAPI_H */
