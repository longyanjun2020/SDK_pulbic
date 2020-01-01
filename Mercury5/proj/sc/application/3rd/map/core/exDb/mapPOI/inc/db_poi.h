/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      db_poi.h
 *
 * DESCRIPTION
 *      This file provides the interfaces to traverse, query, search POI information.
 *
 * HISTORY
 *      2009.05.07       Wolloh Chou       Version 1.0                                     
 *----------------------------------------------------------------------------- 
 */
#ifndef DB_POI_H
#define DB_POI_H

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "fw_std.h"

/*------------------------------------------------------------------------------
    EXTERN definition
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/
#define DBPOI_INVALID_POIID     0xFFFFFFFF /* defines invalid POI id */
#define DB_POI_NEARBY_RESULT_MNUM           30             /* defines the max number for nearby search */
#define DB_POI_MAX_KEYWORD_RESULT           50   /* max number of the search result */
/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

/* POI district enum*/
typedef enum POIDistrict_e
{
    E_POI_DISTRICT_UNKNOWN = -1,
    E_POI_DISTRICT_ANHUISHENG = 0,                    /* 安徽省 */
    E_POI_DISTRICT_BEILJINGSHI,                       /* 北京市 */
    E_POI_DISTRICT_GANSUSHENG,                        /* 甘肅省 */
    E_POI_DISTRICT_HEBEISHENG,                        /* 河北省 */
    E_POI_DISTRICT_HENANSHENG,                        /* 河南省 */
    E_POI_DISTRICT_HUBEISHENG,                        /* 湖北省 */
    E_POI_DISTRICT_HUNANSHENG,                        /* 湖南省 */
    E_POI_DISTRICT_JILINSHENG,                        /* 吉林省 */
    E_POI_DISTRICT_TIANJINSHI,                        /* 天津市 */
    E_POI_DISTRICT_FUJIANSHENG,                       /* 福建省 */
    E_POI_DISTRICT_HAINANSHENG,                       /* 海南省(10) */
    E_POI_DISTRICT_SHANGHAISHI,                       /* 上海市 */
    E_POI_DISTRICT_SHANXISHENG,                       /* 山西省 */
    E_POI_DISTRICT_YUNNANSHENG,                       /* 雲南省 */
    E_POI_DISTRICT_CHONGQINGSHI,                      /* 重慶市 */
    E_POI_DISTRICT_GUIZHOUSHENG,                      /* 貴州省 */
    E_POI_DISTRICT_JIANGSUSHENG,                      /* 江蘇省 */
    E_POI_DISTRICT_JIANGXISHENG,                      /* 江西省 */
    E_POI_DISTRICT_QINGHAISHENG,                      /* 青海省 */
    E_POI_DISTRICT_SHANNXISHENG,                      /* 陝西省 */
    E_POI_DISTRICT_SICHUANSHENG,                      /* 四川省(20) */
    E_POI_DISTRICT_LIAONINGSHENG,                     /* 遼寧省 */
    E_POI_DISTRICT_SHANDONGSHENG,                     /* 山東省 */
    E_POI_DISTRICT_XIZANGZIZHIQU,                     /* 西藏自治區 */
    E_POI_DISTRICT_ZHEJIANGSHENG,                     /* 浙江省 */
    E_POI_DISTRICT_GUANGDONGSHENG,                    /* 廣東省 */
    E_POI_DISTRICT_NEIMENGGUZIZHIQU,                  /* 內蒙古自治區 */
    E_POI_DISTRICT_HEILONGJIANGSHENG,                 /* 黑龍江省 */
    E_POI_DISTRICT_NINGXIAHUIZUZIZHIQU,               /* 寧夏回族自治區 */
    E_POI_DISTRICT_AOMENTEBIEXINGZHENGQU,             /* 澳門特別行政區 */

    E_POI_DISTRICT_GUANGXIZHUANGZUZIZHIQU,            /* 廣西壯族自治區(30) */
    E_POI_DISTRICT_XINJIANGWEIWUERZIZHIQU,            /* 新疆維吾爾自治區 */
    E_POI_DISTRICT_XIANGGANGTEBIEXINGZHENGQU,         /* 香港特別行政區 */
    E_POI_NUM_OF_DISTRICT,                                  /* (33) */
    E_POI_DISTRICT_ALL
} POIDistrict_et;

/*POI group enum*/
typedef enum POIGroup_e
{
    E_POI_GROUP_UNKNOWN = -1,
    E_POI_GROUP_LANDMARK = 0,                         /* 地名社區 */
    E_POI_GROUP_GOVERNMENT_INDUSTRY,                  /* 企業政府機關 */
    E_POI_GROUP_CULTURE_EDUCATION,                    /* 文化教育 */
    E_POI_GROUP_TRAFFIC_CAR,                          /* 交通汽車 */
    E_POI_GROUP_FINANCE,                              /* 金融 */
    E_POI_GROUP_FOOD,                                 /* 餐廳 */
    E_POI_GROUP_SHOPPING,                             /* 購物 */
    E_POI_GROUP_HEALTH_MEDICINE,                      /* 健康醫藥 */
    E_POI_GROUP_TOUR,                                 /* 旅遊 */
    E_POI_GROUP_LEISURE_ENTERTAINMENT_SPORT,          /* 休閒娛樂運動 */
    E_POI_GROUP_ACCOMMODATION,                        /* 住宿 */
    E_POI_GROUP_PUBLIC_SERVICE,                       /* 公共服務 */
    E_POI_NUM_OF_GROUP,                               /* (12)*/
    E_POI_GROUP_ALL

} POIGroup_et;

/*POI type enum*/
typedef enum POIType_e
{
    E_POI_TYPE_UNKNOWN = -1,
    /* E_POI_GROUP_LANDMARK */
    E_POI_TYPE_PLACE_NAME_CAPITAL = 0,                /* 國家首都 */
    E_POI_TYPE_PLACE_NAME_PROVINCIAL,                 /* 省級行政中心 */
    E_POI_TYPE_PLACE_NAME_PREFECTURE,                 /* 市級行政中心 */
    E_POI_TYPE_PLACE_NAME_COUNTY,                     /* 區縣級行政中心 */
    E_POI_TYPE_PLACE_NAME_TOWN,                       /* 鄉鎮級行政中心 */
    E_POI_TYPE_PLACE_NAME_VILLAGE,                    /* 村級行政中心 */
    E_POI_TYPE_PLACE_NAME_SPECIFIC_AREA,              /* 特定區域 */
    E_POI_TYPE_OTHER_LANDMARK,                        /* 其他地標 */
    E_POI_TYPE_MANSION,                               /* 大廈 */
    E_POI_TYPE_RESIDENCE_COMMINITY,                   /* 住宅小區 */

    /* E_POI_GROUP_GOVERMENT_INDUSTRY */
    E_POI_TYPE_GOBERNMENT_AGENCIES,                   /* 政府機關(10) */
    E_POI_TYPE_FIRE_SERVICE_DEPARTMENT,               /* 消防機關 */
    E_POI_TYPE_JUDICIAL_AUTHORITY,                    /* 司法機關 */
    E_POI_TYPE_NOTARY_AGENCY,                         /* 公正機關 */
    E_POI_TYPE_CUSTOM,                                /* 海關 */
    E_POI_TYPE_FOREIGN_AFFAIRS_INSTITUTION,           /* 涉外機關 */
    E_POI_TYPE_RESIDENT_AGENCY,                       /* 駐外機關(16) */
    E_POI_TYPE_SOCIAL_ORGANIZATION,                   /* 社會團體 */
    E_POI_TYPE_COMPANY,                               /* 公司企業 */

    /* E_POI_GROUP_CULTURE_EDUCATION */
    E_POI_TYPE_LIBRARY,                               /* 圖書館(19) */
    E_POI_TYPE_MUSEUM,                                /* 博物館 */
    E_POI_TYPE_CULTURE_PLACE,                         /* 文化設施 */
    E_POI_TYPE_CULTURE_CENTER,                        /* 文化中心 */
    E_POI_TYPE_SCHOOL,                                /* 學校 */
    E_POI_TYPE_OTHER_CULTURE_PLACE,                   /* 其他化設施 */

    /* E_POI_GROUP_TRAFFIC_CAR */
    E_POI_TYPE_AIRPORT,                               /* 機場(25) */
    E_POI_TYPE_TRAIN_STATION,                         /* 火車站 */
    E_POI_TYPE_STATION,                               /* 車站 */
    E_POI_TYPE_PORT_AND_WHARF,                        /* 港口碼頭 */
    E_POI_TYPE_TICKET_OFFICE,                         /* 售票處 */
    E_POI_TYPE_SERVICE_AREA,                          /* 服務區 */
    E_POI_TYPE_TOLL_STATION,                          /* 收費站 */
    E_POI_TYPE_PARKING_LOT,                           /* 停車場(32)  */
    E_POI_TYPE_GAS_STATION,                           /* 加油站 */
    E_POI_TYPE_TRAFFIC_SERVICE_AGENCY,                /* 交通服務機構 */
    E_POI_TYPE_4S_SHOP,                               /* 汽車4S店 */
    E_POI_TYPE_AUTOMOBILE_SALES,                      /* 汽車銷售 */
    E_POI_TYPE_AUTO_REPAIR,                           /* 汽車維修 */
    E_POI_TYPE_AUTO_INSPECTION,                       /* 汽車檢測 */
    E_POI_TYPE_OTHER_VEHICLE_SERVICE,                 /* 其他汽車服務 */

    /* E_POI_GROUP_FINANCE */
    E_POI_TYPE_BANK,                                  /* 銀行(40) */
    E_POI_TYPE_ATM,                                   /* ATM */
    E_POI_TYPE_CREDIT_COOPERATIVE,                    /* 信用社 */
    E_POI_TYPE_SECURITIES,                            /* 証券 */
    E_POI_TYPE_INSURANCE,                             /* 保險 */
    E_POI_TYPE_OTHER_FINANCE_UNIT,                    /* 其它金融單位 */

    /* E_POI_GROUP_FOOD */
    E_POI_TYPE_CHINESE_FOOD,                          /* 中式餐廳(46) */
    E_POI_TYPE_INTERNATIONAL_CUISINE,                 /* 中式餐廳 */
    E_POI_TYPE_CHAFING_DISH,                          /* 火鍋城  */
    E_POI_TYPE_RESTAURANT,                            /* 普通餐廳 */
    E_POI_TYPE_CAFETERIA,                             /* 自助餐廳 */
    E_POI_TYPE_NOSHERY,                               /* 快餐店 */

    /* E_POI_GROUP_SHOPPING */
    E_POI_TYPE_DEPARTMENT_STORE,                      /* 百貨商場(52) */
    E_POI_TYPE_SUPERMARKET,                           /* 超市 */
    E_POI_TYPE_CONVENIENT_STORE,                      /* 便利店 */
    E_POI_TYPE_SPECIALTY_MARKET,                      /* 專營市場 */

    /* E_POI_GROUP_HEALTH_MEDICINE */
    E_POI_TYPE_GENERAL_HOSPITAL,                      /* 綜合醫院(56) */
    E_POI_TYPE_SPECIAL_HOSPITAL,                      /* 專科醫院 */
    E_POI_TYPE_URGENT_CARE_CENTER,                    /* 急救中心 */
    E_POI_TYPE_CLINIQURE,                             /* 診所 */
    E_POI_TYPE_PHARMACY,                              /* 藥店  */
    E_POI_TYPE_REHABILITATIVE_SANATORIUM,             /* 康復療養院 */
    E_POI_TYPE_PHYSICAL_EXAMINATION,                  /* 體檢/防疫站 */
    E_POI_TYPE_BLOOD_CENTER,                          /* 血液中心 */
    E_POI_TYPE_ANIMAL_HOSPITAL,                       /* 動物醫院 */

    /* E_POI_GROUP_TOUR */
    E_POI_TYPE_PARK,                                  /* 公園(65) */
    E_POI_TYPE_ZOO,                                   /* 動物園 */
    E_POI_TYPE_BOTANICAL_GARDEN,                      /* 植物園 */
    E_POI_TYPE_AQUARIUM_AND_OCEAN_PARK,               /* 水族館/海洋館 */
    E_POI_TYPE_NATURAL_LANDSCAPE,                     /* 自然景觀 */
    E_POI_TYPE_CEMETERY_OF_REVOLUTIONARY_MARTYR,      /* 烈士陵園 */
    E_POI_TYPE_HISTORICAL_RELIC,                      /* 歷史文化遺址 */
    E_POI_TYPE_TEMPLE_AND_CHURCH,                     /* 廟宇/教堂 */
    E_POI_TYPE_URBAN_LANDMARK_BUILDING,               /* 城市標誌建築/標誌 */
    E_POI_TYPE_SPECIAL_STREET,                        /* 特色街道 */

    /* E_POI_GROUP_LEISURE_ENTERTAINMENT_SPORT */
    E_POI_TYPE_BOWLING_ALLEY,                         /* 保齡球場(75) */
    E_POI_TYPE_WATER_SPORT,                           /* 水上運動 */
    E_POI_TYPE_ICE_SPORT,                             /* 冰上運動 */
    E_POI_TYPE_FOOTBALL_FILED,                        /* 足球場 */
    E_POI_TYPE_BASEBALL_FILED,                        /* 棒球場 */
    E_POI_TYPE_OTHER_BALL_GAME_PLACE,                 /* 其他球類運動設施 */
    E_POI_TYPE_OTHER_SPORT_PLACE,                     /* 其他運動設施 */
    E_POI_TYPE_GOLF_COURSE,                           /* 高爾夫球場 */
    E_POI_TYPE_FITNESS_CENTER,                        /* 健身中心 */
    E_POI_TYPE_THEATER_AND_CONCERT_HALL,              /* 影劇院/音樂廳 */
    E_POI_TYPE_AMUSEMENT_PARK,                        /* 遊樂場 */
    E_POI_TYPE_LEISURE_AND_ENTERTAINMENT_PLACE,       /* 休閒娛樂場所 */

    /* E_POI_GROUP_ACCOMMODATION */
    E_POI_TYPE_FIVE_STAR_HOTEL,                       /* 五星級賓館酒店(87) */
    E_POI_TYPE_FOUR_STAR_HOTEL,                       /* 四星級賓館酒店 */
    E_POI_TYPE_THREE_STAR_HOTEL,                      /* 三星級賓館酒店 */
    E_POI_TYPE_ORDINARY_HOTEL,                        /* 一般賓館酒店 */
    E_POI_TYPE_HOTEL_CHAIN,                           /* 連鎖酒店 */
    E_POI_TYPE_REST_HOUSE,                            /* 招待所 */
    E_POI_TYPE_RESORT,                                /* 度假村 */

    /* E_POI_GROUP_PUBLIC_SERVICE */
    E_POI_TYPE_TELECOM,                               /* 電信(94) */
    E_POI_TYPE_POST,                                  /* 郵政 */
    E_POI_TYPE_TELECAST,                              /* 廣播電視  */
    E_POI_TYPE_PRESS_AND_PUBLISHING,                  /* 新聞出版  */
    E_POI_TYPE_WELFARE_AGENCY,                        /* 福利機構  */
    E_POI_TYPE_OFFICE,                                /* 事務所 */
    E_POI_TYPE_PUBLIC_TOILET,                         /* 公共廁所 */
    E_POI_TYPE_OTHER_SERVICE_UNIT,                    /* 其它專業服務 */
    E_POI_NUM_OF_TYPE,                                /* (102)*/
    E_POI_TYPE_ALL

} POIType_et;

/*This data structure is for query detail POI information*/
typedef struct POI_Info_s
{
    S32                         s32X; /*X-coordinate*/
    S32                         s32Y; /*Y-coordinate*/
    PU16                       pwszName; /* POI name */
    PU16                       pwszTel;/* POI tel */
    PU16                       pwszAddres;/*POI address */
    POIType_et             eType;     /* POI type */
} POI_Info_st, *pPOI_Info_st;

/*
 *  Syntax:
 *      MBOOL (*POIFilter_pfn)(PMVOID pvClientData, POIGroup_et eGroup, POIType_et eType);
 *
 *  Purpose:
 *      Defines the callback function to filter POI.
 *
 *  Parameters:
 *      pvClientData
 *          [in] The caller's client data.
 *      eGroup
 *          [in] Specifie the POI group.
 *      eType
 *          [in] Specifie the POI type.
 *
 *  Return Values:
 *      MBOOL_TRUE: reserves this POI.
 *      MBOOL_FALSE: discards this POI.
 */
typedef MBOOL (*POIFilter_pfn)(PMVOID pvClientData, POIGroup_et eGroup, POIType_et eType);

/*
 *  Syntax:
 *      MBOOL (*POITraverseHandler_pfn)(PMVOID pvClientData, U32 u32POIID, S32 s32X, S32 s32Y, POIType_et eType);
 *
 *  Purpose:
 *      Defines the callback function to handle the result of travering POIs by the quadrangle/bounding.
 *
 *  Parameters:
 *      pvClientData
 *          [in] The caller's client data.
 *      u32POIID
 *          [in] Specifie the POI id.
 *      s32X
 *          [in] The longitude position of POI.
 *      s32Y
 *          [in] The latitude position of POI.
 *      eType
 *          [in] Specifie the POI type.
 *
 *  Return Values:
 *      MBOOL_TRUE: continues to travese POI.
 *      MBOOL_FALSE: stops to traverse POI.
 */
typedef MBOOL (*POITraverseHandler_pfn)(PMVOID pvClientData, U32 u32POIID, S32 s32X, S32 s32Y, POIType_et eType);

/*
 *  Syntax:
 *      MBOOL (*POISearchHandler_pfn)(PMVOID pvClientData, U32 u32POIID, PU16 pwszName);
 *
 *  Purpose:
 *      Defines the callback function to handle the result of keyword search/phone numner serach.
 *
 *  Parameters:
 *      pvClientData
 *          [in] The caller's client data.
 *      u32POIID
 *          [in] Specifie the POI id.
 *
 *  Return Values:
 *      MBOOL_TRUE: continues to travese POI.
 *      MBOOL_FALSE: stops to traverse POI.
 */
typedef MBOOL (*POISearchHandler_pfn)(PMVOID pvClientData, U32 u32POIID);

/*
 *  Syntax:
 *      MBOOL (*POINearbySearchHandler_pfn)(PMVOID pvClientData, U32 u32POIID, PU16 pwszName, S32 s32Distance);
 *
 *  Purpose:
 *      Defines the callback function to handle the result of nearby search.
 *
 *  Parameters:
 *      pvClientData
 *          [in] The caller's client data.
 *      u32POIID
 *          [in] Specifie the POI id.
 *      s32Distance
 *          [in] Specifie the distance betwwen the POI and the given location.
 *
 *  Return Values:
 *      MBOOL_TRUE: continues to travese POI.
 *      MBOOL_FALSE: stops to traverse POI.
 */
typedef MBOOL (*POINearbySearchHandler_pfn)(PMVOID pvClientData, U32 u32POIID, S32 s32Distance);

/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


 /*
 *  Syntax:
 *      MBOOL  dbPOIOpenGroup(POIGroup_et eGroup);
 * 
 *  Purpose:
 *     Open on map group
 *
 *  Parameters:
 *      eGroup
 *          [in] on map group
 *
 *  Return Values
 *      MBOOL_TRUE: success.
 *      MBOOL_FALSE: fail.
 */
MBOOL  dbPOIOpenGroup(POIGroup_et eGroup);

/*
 *  Syntax:
 *      MBOOL  dbPOICloseGroup(POIGroup_et eGroup);
 * 
 *  Purpose:
 *     close on map group
 *
 *  Parameters:
 *      eGroup
 *          [in] the group to be closed
 *
 *  Return Values
 *      MBOOL_TRUE: success.
 *      MBOOL_FALSE: fail.
 */
MBOOL  dbPOICloseGroup(POIGroup_et eGroup);

/*
 *  Syntax:
 *      MBOOL dbPOIInit(const PU16 pwszRootDirName, U32 u32Lod, PS8 ps8Mem, U32 u32MemSize);
 * 
 *  Purpose:
 *      Initialize the POI database.
 *
 *  Parameters:
 *      pszRootDirName
 *          [in] Root directory name of the database.
 *      u32Lod
 *          [in] LOD 
 *       ps8Mem  
 *          [in] memory
 *       u32Memsize
 *          [in] memory size 
 *
 *  Return Values
 *      MBOOL_TRUE: success.
 *      MBOOL_FALSE: fail.
 */
#ifdef USE_STATIC_MEMORY
    MBOOL dbPOIInit(const PU16 pwszRootDirName, U32 u32Lod, PS8 ps8Mem, U32 u32MemSize);
#else
    MBOOL dbPOIInit(const PU16 pwszRootDirName, U32 u32Lod, PS8 ps8Mem, U32 u32MemSize, PU8 pu8ExtMem);
#endif

/*
 *  Syntax:
 *      MVOID dbPOIFinal(MVOID);
 * 
 *  Purpose:
 *      Final the POI database.
 *
 *  Parameters:
 *      None.
 *
 *  Return Values
 *      None.
 */
    MVOID dbPOIFinal(MVOID);


/* 
 *  Syntax:
 *      U32 dbPOIGetByBounding(S32 s32Left, S32 s32Bottom, S32 s32Right, S32 s32Top, POITraverseHandler_pfn pfnHandler, POIFilter_pfn pfnFilter, PMVOID pvClientData);
 *
 *  Purpose:
 *      Traverse POIs by the bounding.
 *
 *  Parameters:
 *      s32Left
 *          [in] Specifie the left of bounding box.
 *      s32Bottom
 *          [in] Specifie the bottom of bounding box.
 *      s32Right
 *          [in] Specifie the right of bounding box.
 *      s32Top
 *          [in] Specifie the top of bounding box.
 *      pfnHandler
 *          [in] Specifie the callback function for traversing result.
 *      pfnFilter
 *          [in] Specifie the callback function for POI filter.
 *               If filter is not needed, passes NULL.
 *      u32Lod
 *          [in] Specify the LOD
 *      pvClientData
 *          [in] Specifie the caller's client data.
 *
 *  Return Values:
 *      Return the POI count of traversing result.
 */
    U32 dbPOIGetByBounding(S32 s32Left, S32 s32Bottom, S32 s32Rigtht, S32 s32Top, 
                                       POITraverseHandler_pfn pfnHandler, POIFilter_pfn pfnFilter, 
                                       U32 u32Lod, PMVOID pvClientData);

  /* 
 *  Syntax:
 *      MBOOL dbPOIGetLoc(U32 u32POIID, PS32 ps32X, PS32 ps32Y);
 *
 *  Purpose:
 *      Get POI location.      
 *
 *  Parameters:
 *      u32POIID
 *          [in] Specifie the POI id.
 *      ps32X
 *          [out] The longitude position of POI
 *      ps32Y
 *          [out] The latitude position of POI
 *
 *  Return Values:
 *      If succeeds, returns MBOOL_TRUE.
 *      If fails, returns MBOOL_FALSE.
 */
    MBOOL dbPOIGetLoc(U32 u32POIID, PS32 ps32X, PS32 ps32Y);

/* 
 *  Syntax:
 *      PU16 dbPOIGetName(U32 u32POIID);
 *
 *  Purpose:
 *      Get POI name.      
 *
 *  Parameters:
 *      u32POIID
 *          [in] Specifie the POI id.
 *
 *  Return Values:
 *      If succeeds, returns the POI name.
 *      If fails, returns NULL.
 */
    PU16 dbPOIGetName(U32 u32POIID);

/* 
 *  Syntax:
 *      PU16  dbPOIGetAddress(U32 u32POIID);
 *
 *  Purpose:
 *      Get POI address.      
 *
 *  Parameters:
 *      u32POIID
 *          [in] Specifie the POI id.
 *
 *  Return Values:
 *      If succeeds, returns the POI address.
 *      If fails, returns NULL.
 */
    PU16 dbPOIGetAddress(U32 u32POIID);

/* 
 *  Syntax:
 *      PU16 dbPOIGetTel(U32 u32POIID);
 *
 *  Purpose:
 *      Get POI telephone.      
 *
 *  Parameters:
 *      u32POIID
 *          [in] Specifie the POI id.
 *
 *  Return Values:
 *      If succeeds, returns the telephone number.
 *      If fails, returns NULL.
 */
    PU16 dbPOIGetTel(U32 u32POIID);

/* 
 *  Syntax:
 *      POIType_et dbPOIGetType(U32 u32POIID);
 *
 *  Purpose:
 *      Get POI type.      
 *
 *  Parameters:
 *      u32POIID
 *          [in] Specifie the POI id.
 *
 *  Return Values:
 *      If succeeds, returns POI type.
 *      If fails, returns E_POI_TYPE_UNKNOWN.
 */
    POIType_et dbPOIGetType(U32 u32POIID);

 /* 
 *  Syntax:
 *      PU16 dbPOIGetInfo(U32 u32POIID);
 *
 *  Purpose:
 *      Get POI Information.      
 *
 *  Parameters:
 *      u32POIID
 *          [in] Specify the POI id.
 *
 *  Return Values:
 *      If succeeds, returns the whole POI information.
 *      If fails, returns NULL.
 */
 pPOI_Info_st dbPOIGetInfo(U32 u32POIID);

 /*
 *  Syntax:
 *      MBOOL dbPOIEnableNearby()
 *
 *  Purpose:
 *      Enable nearby searching 
 *
 *  Parameters:
 *      
 *  Return Values
 *      MBOOL_TRUE: success.
 *      MBOOL_FALSE: fail.    
 */
 MBOOL dbPOIEnableNearby(MVOID);
 
 /*
 *  Syntax:
 *      MBOOL dbPOIEnableNearby()
 *
 *  Purpose:
 *      Enable nearby searching 
 *
 *  Parameters:
 *      
 *  Return Values
 *      MBOOL_TRUE: success.
 *      MBOOL_FALSE: fail.    
 */
 MBOOL dbPOIDisableNearby(MVOID);

/* 
 *  Syntax:
 *      U32 dbPOINearbySearch(S32 s32LocX, S32 s32LocY, S32 s32Range, POIType_et eType, POIGroup_et eGroup, 
                                      POINearbySearchHandler_pfn pfnHandler, PMVOID pvClientData);
 *
 *  Purpose:
 *      Search the nearby POIs by the location and radius range.
 *
 *  Parameters:
 *      s32LocX
 *          [in] Specifie the longitude position of location.
 *      s32LocY
 *          [in] Specifie the latitude position of location.
 *      u32Range
 *          [in] Specifie the radius range.
 *      eType
 *          [in] Specifie the POI type
 *      eGroup
 *          [in] Specifie the POI group
 *      pfnHandler
 *          [in] Specifie the callback function for searching result.
 *      pvClientData
 *          [in] Specifie the caller's client data.
 *
 *  Return Values:
 *      Return the POI count of searching result.
 */
    U32 dbPOINearbySearch(S32 s32LocX, S32 s32LocY, U32 u32Range, POIType_et eType, POIGroup_et eGroup, 
                                      POINearbySearchHandler_pfn pfnHandler, PMVOID pvClientData);

    
  /* 
 *  Syntax:
 *      MBOOL dbPOIEnableSearching(PU8 pu8Mem, U32 u32Size);
 *
 *  Purpose:
 *      Init keyword searching
 *
 *  Parameters:
 *      pu8Mem
 *          [in] memory
 *      u32Size
 *          [in] memory size
 *
 *  Return Values:
 *      MBOOL_TRUE: success.
 *      MBOOL_FALSE: fail.
 */

    MBOOL dbPOIEnableSearching(PU8 pu8Mem, U32 u32Size);

    
    /*
 *  Syntax:
 *      MBOOL dbPOIDisableSearching(MVOID);
 *
 *  Purpose:
 *      disable keyword searching 
 *
 *  Parameters:
 *      
 *  Return Values
 *      MBOOL_TRUE: success.
 *      MBOOL_FALSE: fail.    
 */
    MBOOL dbPOIDisableSearching(MVOID);

 /* 
 *  Syntax:
 *      MBOOL dbPOISetKeywordDistrict(POIDistrict_et eDistrict);
 *
 *  Purpose:
 *      Set the district which want which want to search by keyword
 *
 *  Parameters:
 *      eDistrict
 *          [in] Specifie the district.
 *
 *  Return Values:
 *      MBOOL_TRUE: success.
 *      MBOOL_FALSE: fail.
 */
MBOOL dbPOISetKeywordDistrict(POIDistrict_et eDistrict);

/* 
 *  Syntax:
 *      MBOOL dbPOISetKeywordGroup(POIGroup_et eGroup);
 *
 *  Purpose:
 *      Set the group which want which want to search by keyword
 *
 *  Parameters:
 *      eGroup
 *          [in] Specifie the group.
 *
 *  Return Values:
 *      MBOOL_TRUE: success.
 *      MBOOL_FALSE: fail.
 */
MBOOL dbPOISetKeywordGroup(POIGroup_et eGroup);

/* 
 *  Syntax:
 *      U32 dbPOIKeywordSearch(PU16 pwszKeyword, POISearchHandler_pfn pfnHandler,  PMVOID pvClientData);
 *
 *  Purpose:
 *      Search the POIs by the keyword.
 *
 *  Parameters:
 *      pwszKeyword
 *          [in] Specifie the keyword.
 *      pfnHandler
 *          [in] Specifie the callback function for searching result.
 *      pvClientData
 *          [in] Specifie the caller's client data.
 *
 *  Return Values:
 *      Return the POI count of searching result.
 */
    U32 dbPOIKeywordSearch(PU16 pwszKeyword, POISearchHandler_pfn pfnHandler,  PMVOID pvClientData);

 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DB_POI_H */
