/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      rm_UserSetting.h
 *
 * DESCRIPTION
 *      This file provides the local functions to store user configurations
 *      If you want to add a new field in user setting,
 *      Please search keywork ADD_NEW_SETTING and following steps.
 *
 * HISTORY
 *      2009.03.01       Donald Hung     Initial Version
 *----------------------------------------------------------------------------- 
 */

#ifndef _rmUserSetting_h_
#define _rmUserSetting_h_

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "fw_std.h"
#include "fw_util.h"
//#include "rt_api.h"

/**
 * define of setting->city name
 */
typedef enum
{
    T_SETTING_CITY_NAME_BEIJING = 0,  // 北京
    T_SETTING_CITY_NAME_TIANJIN,      // 天津
    T_SETTING_CITY_NAME_HEBEI,        // 河北
    T_SETTING_CITY_NAME_SHANXI,       // 山西
    T_SETTING_CITY_NAME_NEIMONGOL,    // 內蒙古
    T_SETTING_CITY_NAME_LIAONING,     // 遼寧
    T_SETTING_CITY_NAME_JILIN,        // 吉林
    T_SETTING_CITY_NAME_HEILONGJIANG, // 黑龍江
    T_SETTING_CITY_NAME_SHANGHAI,     // 上海
    T_SETTING_CITY_NAME_JIANGSU,      // 江蘇
    T_SETTING_CITY_NAME_ZHEJIANG,     // 浙江
    T_SETTING_CITY_NAME_ANHUI,        // 安徽
    T_SETTING_CITY_NAME_FUJIAN,       // 福建
    T_SETTING_CITY_NAME_JIANGXI,      // 江西
    T_SETTING_CITY_NAME_SHANDONG,     // 山東
    T_SETTING_CITY_NAME_HENAN,        // 河南
    T_SETTING_CITY_NAME_HUBEI,        // 湖北
    T_SETTING_CITY_NAME_HUNAN,        // 湖南
    T_SETTING_CITY_NAME_GUANGDONG,    // 廣東
    T_SETTING_CITY_NAME_GUANGXI,      // 廣西
    T_SETTING_CITY_NAME_HAINAN,       // 海南
    T_SETTING_CITY_NAME_CHONGQING,    // 重慶
    T_SETTING_CITY_NAME_SICHUAN,      // 四川
    T_SETTING_CITY_NAME_GUIZHOU,      // 貴州
    T_SETTING_CITY_NAME_YUNNAN,       // 雲南
    T_SETTING_CITY_NAME_TIBET,        // 西藏
    T_SETTING_CITY_NAME_SHAANXI,      // 陜西
    T_SETTING_CITY_NAME_GANSU,        // 甘肅
    T_SETTING_CITY_NAME_QINGHAI,      // 青海
    T_SETTING_CITY_NAME_NINGXIA,      // 寧夏
    T_SETTING_CITY_NAME_XINJIANG,     // 新疆
    T_SETTING_CITY_NAME_HONGKONG,     // 香港
    T_SETTING_CITY_NAME_MACAU,        // 澳門
    T_NUM_OF_CITY_NAME
} T_SETTING_CITY_NAME;


/**
 * define of setting->POI on map
 */
typedef enum
{
    T_SETTING_POIONMAP_CATEGORY_GOVERNMENT = 0,  // 政府機關
    T_SETTING_POIONMAP_CATEGORY_EDUCATION,       // 學校教育
    T_SETTING_POIONMAP_CATEGORY_HOSPITAL,        // 醫療看護
    T_SETTING_POIONMAP_CATEGORY_RESTAURANT,      // 餐廳料理
    T_SETTING_POIONMAP_CATEGORY_STORE,           // 商店行號
    T_SETTING_POIONMAP_CATEGORY_ENTERTAINMENT,   // 休閒娛樂
    T_SETTING_POIONMAP_CATEGORY_TRAFFIC,         // 運輸交通
    T_SETTING_POIONMAP_CATEGORY_SPORTS,          // 運動設施
    T_SETTING_POIONMAP_CATEGORY_PUBLIC,          // 公共服務
    T_SETTING_POIONMAP_CATEGORY_BUILDING,        // 大樓小區
    T_NUM_OF_POIONMAP_CATEGORY
} T_SETTING_POIONMAP_CATEGORY;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_GOVERNMENT_CENTRAL = 0,       // 中央政府
    T_SETTING_POIONMAP_CATEGORY2_GOVERNMENT_PROVINCE,          // 省級機構
    T_SETTING_POIONMAP_CATEGORY2_GOVERNMENT_DISTRICT,          // 區域機構
    T_SETTING_POIONMAP_CATEGORY2_GOVERNMENT_POLICE,            // 警察局
    T_SETTING_POIONMAP_CATEGORY2_GOVERNMENT_FIREDEPARTMENT,    // 消防隊
    T_SETTING_POIONMAP_CATEGORY2_GOVERNMENT_FOREIGNINSTITUTE,  // 外國辦事處
    T_SETTING_POIONMAP_CATEGORY2_GOVERNMENT_OTHER,             // 其他政府機關
    T_NUM_OF_POIONMAP_CATEGORY2_GOVERNMENT
} T_SETTING_POIONMAP_CATEGORY2_GOVERNMENT;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_EDUCATION_SCHOOL = 0,         // 中央政府
    T_SETTING_POIONMAP_CATEGORY2_EDUCATION_CRAMMINGSCHOOL,     // 省級機構
    T_NUM_OF_POIONMAP_CATEGORY2_EDUCATION
} T_SETTING_POIONMAP_CATEGORY2_EDUCATION;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_HOSPITAL_HEALTHCENTER = 0,    // 保健中心
    T_SETTING_POIONMAP_CATEGORY2_HOSPITAL_CLINIC,              // 醫院診所
    T_SETTING_POIONMAP_CATEGORY2_HOSPITAL_NERSINGCARE,         // 看護
    T_SETTING_POIONMAP_CATEGORY2_HOSPITAL_PHARMACY,            // 藥局
    T_SETTING_POIONMAP_CATEGORY2_HOSPITAL_ANIMALHOSPITAL,      // 獸醫院
    T_NUM_OF_POIONMAP_CATEGORY2_HOSPITAL
} T_SETTING_POIONMAP_CATEGORY2_HOSPITAL;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_RESTAURANT_RESTAURANT = 0,    // 餐廳
    T_SETTING_POIONMAP_CATEGORY2_RESTAURANT_FAMILYRESTAURANT,  // 家庭餐廳
    T_SETTING_POIONMAP_CATEGORY2_RESTAURANT_FASTFOOD,          // 速食店
    T_SETTING_POIONMAP_CATEGORY2_RESTAURANT_SNACKBAR,          // 當地小吃
    T_NUM_OF_POIONMAP_CATEGORY2_RESTAURANT
} T_SETTING_POIONMAP_CATEGORY2_RESTAURANT;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_STORE_DEPARTMENTSTORE = 0,    // 百貨公司
    T_SETTING_POIONMAP_CATEGORY2_STORE_CONVENIENCESTORE,       // 便利商店
    T_SETTING_POIONMAP_CATEGORY2_STORE_SUPERMARKET,            // 超級市場
    T_SETTING_POIONMAP_CATEGORY2_STORE_FUNERALHALL,            // 殯儀館
    T_SETTING_POIONMAP_CATEGORY2_STORE_ESTATEAGENCY,           // 仲介機構
    T_SETTING_POIONMAP_CATEGORY2_STORE_MARKET,                 // 市場/夜市
    T_SETTING_POIONMAP_CATEGORY2_STORE_BOOKSTORE,              // 書店
    T_SETTING_POIONMAP_CATEGORY2_STORE_NEWSPAPER,              // 報社
    T_SETTING_POIONMAP_CATEGORY2_STORE_TVSTATION,              // 電視台
    T_SETTING_POIONMAP_CATEGORY2_STORE_PUBLISHCOMPANY,         // 出版社
    T_SETTING_POIONMAP_CATEGORY2_STORE_INSURANCECOMPANY,       // 保險公司
    T_SETTING_POIONMAP_CATEGORY2_STORE_BOUTIQUE,               // 精品店
    T_SETTING_POIONMAP_CATEGORY2_STORE_COFFEESHOP,             // 咖啡廳
    T_SETTING_POIONMAP_CATEGORY2_STORE_FACTORY,                // 工廠
    T_SETTING_POIONMAP_CATEGORY2_STORE_STOCKMARKET,            // 証卷
    T_SETTING_POIONMAP_CATEGORY2_STORE_OTHERSTORE,             // 其他商店
    T_NUM_OF_POIONMAP_CATEGORY2_STORE
} T_SETTING_POIONMAP_CATEGORY2_STORE;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_PARK = 0,       // 公園
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_TOURISTFARM,    // 觀光農場
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_ZOOBOTANICGARDEN,// 動物園/植物園
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_CEMETERY,       // 墓園
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_OTHERGREENBELT, // 其他綠地
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_MESEUM,         // 博物館
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_LIBRARY,        // 圖書館
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_CULTURECENTER,  // 文化中心
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_FAMILYTEMPLE,   // 宗祠
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_TEMPLECHURCH,   // 廟/教堂
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_HISTORICALSITE, // 古蹟
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_AQUARIUM,       // 水族館/海洋公園
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_OTHERCULTURAL,  // 其他文化設施
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_SIGHTSEESPOT,   // 觀光景點
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_MUSEMENTPLACE,  // 娛樂場所
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_LOCALPRODUCT,   // 當地小吃
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_HOTEL,          // 酒店/旅館
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_BOWLINGCENTER,  // 保齡球館
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_KARAOKE,        // 卡拉OK
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_CINEMA,         // 電影院
    T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT_OTHERLEISURE,   // 其他休閒設施
    T_NUM_OF_POIONMAP_CATEGORY2_ENTERTAINMENT
} T_SETTING_POIONMAP_CATEGORY2_ENTERTAINMENT;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_GASSTATION = 0,       // 加油站
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_CARDEALER,            // 汽車經銷商
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_CARREPAIR,            // 汽車維修
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_AIRPORT,              // 機場
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_FERRYTERMINAL,        // 渡輪碼頭
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_BUSTERMINAL,          // 巴士站
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_PUBLICSTATION,        // 公交站
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_RAILWAYSTATION,       // 火車站
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_MRTSTATION,           // 地鐵站
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_HIGHWAYRAMP,          // 公路匝道
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_HIGHWAYINTERCHANGE,   // 公路交匯處
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_HIGHWAY,              // 高速公路
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_HIGHWAYSERVICEAREA,   // 休息站
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_PARKINGLOT,           // 停車場
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_TOLLGATE,             // 收費站
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_TOWCENTER,            // 拖吊中心
    T_SETTING_POIONMAP_CATEGORY2_TRAFFIC_OTHERTRANSPORT,       // 其他交通設施
    T_NUM_OF_POIONMAP_CATEGORY2_TRAFFIC
} T_SETTING_POIONMAP_CATEGORY2_TRAFFIC;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_SPORTS_BASEBALLFIELD = 0,     // 棒球場
    T_SETTING_POIONMAP_CATEGORY2_SPORTS_GYMNASIUM,             // 體育館
    T_SETTING_POIONMAP_CATEGORY2_SPORTS_SWIMMINGPOOL,          // 游泳池
    T_SETTING_POIONMAP_CATEGORY2_SPORTS_GOLFCOURSE,            // 高爾夫球場
    T_SETTING_POIONMAP_CATEGORY2_SPORTS_OTHERSPORT,            // 其他運動設施
    T_NUM_OF_POIONMAP_CATEGORY2_SPORTS
} T_SETTING_POIONMAP_CATEGORY2_SPORTS;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_PUBLIC_WATERWORKS = 0,        // 自來水公司
    T_SETTING_POIONMAP_CATEGORY2_PUBLIC_POWERCOMPANY,          // 電力公司
    T_SETTING_POIONMAP_CATEGORY2_PUBLIC_GASCOMPANY,            // 天然氣公司
    T_SETTING_POIONMAP_CATEGORY2_PUBLIC_TELECOMCOMPANY,        // 電信公司
    T_SETTING_POIONMAP_CATEGORY2_PUBLIC_BANK,                  // 銀行
    T_SETTING_POIONMAP_CATEGORY2_PUBLIC_ATM,                   // ATM
    T_SETTING_POIONMAP_CATEGORY2_PUBLIC_POSTOFFICE,            // 郵局
    T_SETTING_POIONMAP_CATEGORY2_PUBLIC_TOILET,                // 公廁
    T_SETTING_POIONMAP_CATEGORY2_PUBLIC_OTHER,                 // 其他
    T_NUM_OF_POIONMAP_CATEGORY2_PUBLIC
} T_SETTING_POIONMAP_CATEGORY2_PUBLIC;


typedef enum
{
    T_SETTING_POIONMAP_CATEGORY2_BUILDING_BUILDING = 0,        // 大樓
    T_SETTING_POIONMAP_CATEGORY2_BUILDING_HOUSE,               // 住宅小區
    T_NUM_OF_POIONMAP_CATEGORY2_BUILDING
} T_SETTING_POIONMAP_CATEGORY2_BUILDING;


/**
 * define of setting->map color
 */
typedef enum
{
    T_SETTING_MAP_COLOR_LIGHT = 0,    // light
    T_SETTING_MAP_COLOR_DARK,         // dark
    T_NUM_OF_MAP_COLOR
} T_SETTING_MAP_COLOR;


/**
 * define of setting->GPS setting
 */
typedef enum
{
    T_SETTING_GPS_SETTING_START = 0,  // turn on when start
    T_SETTING_GPS_SETTING_NEED,       // turn on when need
    T_NUM_OF_GPS_SETTING
} T_SETTING_GPS_SETTING;


/**
 * define of My Favorite
 */
#define NUM_FAVORITE_NAME     32
#define NUM_FAVORITE_PHONE    16
#define NUM_FAVORITE_ADDRESS  64
#define NUM_FAVORITE_NOTE     128

typedef enum
{
    T_FAVORITE_CATEGORY_MYFAMILY = 0, // My family
    T_FAVORITE_CATEGORY_MYFRIENDS,    // My friends
    T_FAVORITE_CATEGORY_RESTAURANT,   // Restaurant
    T_FAVORITE_CATEGORY_TRAFFIC,      // Traffic
    T_FAVORITE_CATEGORY_ENTERTAINMENT,// Entertainment
    T_FAVORITE_CATEGORY_SHOPPING,     // Shopping
    T_FAVORITE_CATEGORY_SIGHT,        // Sight
    T_FAVORITE_CATEGORY_OTHER,        // Other
    T_NUM_OF_FAVORITE_CATEGORY
} T_FAVORITE_CATEGORY;

typedef struct  Location_s
{
    Vertex_st           vertex;
    PU16                pName;
    PU16                pPhone;
    PU16                pAddress;
    PU16                pNote;
    MBOOL             bPOI;                                      
    S32                  s32POIID;                             
    U8                    bPOIType;
} Location_st, *pLocation_st;


/**
 * define of History
 */
 

/**
 * define of section
 */
typedef enum
{
    eSettingSecNameNotDef = -1,
    eSettingSecNameSettings = 0,
    eSettingSecNameMyFamily = 1,
    eSettingSecNameMyFriends,
    eSettingSecNameRestaurant,
    eSettingSecNameTraffic,
    eSettingSecNameEntertainment,
    eSettingSecNameShopping,
    eSettingSecNameSight,
    eSettingSecNameOther,
    eSettingSecNameMyLocationHistory,
    eSettingSecNamePOIHistory,
    eNumOfSettingSectionName
} SettingSectionName_t;


/**
 * Definition of LBS cookies
 */
typedef struct LBSCookies_URLHistory_TAG
{
    boolean     bLBSURL_IsReDirected;
    PU16        pLBSURL;
    PU16        pLBSURL_Redirected;
    U32         u32ExpTimeInSec_UTC;
}LBSCookies_URLHistory_st, *pLBSCookies_URLHistory_st;

typedef struct LBSCookies_CacheFileMang_TAG
{
    PU16    pCacheFileURL;
    PU16    pCacheFileXmlAssoc;
}LBSCookies_CacheFileMang_st, *pLBSCookies_CacheFileMang_st;
typedef enum
{
    eLBSCookiesSecNameNotDef = -1,
    eLBSCookiesSecNameUrlHisoty = 0,
    eLBSCookiesSecNameCacheFileMang = 1,
    eNumOfLBSCookiesSectionName
}LBSCookiesSectionName_t;

/**
 * define of exported functions
 */
#ifdef __cplusplus
extern "C"
{
#endif

MBOOL rmUserSettingInit(PU16 pLBSCachePath, const PS8 pLBSFileFormat);
MVOID rmUserSettingEnd(MVOID);
MVOID rmUserSettingSave(MVOID);
MVOID rmUserSettingRestoreDefault(MVOID);

MBOOL rmUserSettingLoadConf(MVOID);
MVOID rmUserSettingSaveConf(MVOID);
MVOID rmUserSettingRestoreDefaultConf(MVOID);
MBOOL rmUserSettingLoadFavorite(SettingSectionName_t eSecName);
MVOID rmUserSettingSaveFavorite(MVOID);
MVOID rmUserSettingRestoreDefaultFavorite(SettingSectionName_t eSecName);
MBOOL rmUserSettingLoadHistory(SettingSectionName_t eSecName);
MVOID rmUserSettingSaveHistory(MVOID);
MVOID rmUserSettingRestoreDefaultHistory(SettingSectionName_t eSecName);

MBOOL rmUserSettingAddFavorite(SettingSectionName_t eSecName, Vertex_st vertex, PU16 sName, PU16 sPhone, PU16 sAddress, PU16 sNote, MBOOL bPOI, S32 s32POIID);
MBOOL rmUserSettingDelFavorite(SettingSectionName_t eSecName, S32 s32Index);
MBOOL rmUserSettingEditFavoriteByIndex(SettingSectionName_t eSecName, S32 s32Index, Vertex_st vertex, PU16 sName, PU16 sPhone, PU16 sAddress, PU16 sNote);
S32 rmUserSettingGetFavorites(SettingSectionName_t eSecName, pLocation_st *pArray);
pLocation_st rmUserSettingGetFavoriteByIndex(SettingSectionName_t eSecName, S32 s32Index);
MBOOL rmUserSettingSetFavoriteByIndex(SettingSectionName_t eSecName, S32 s32Index, pVertex_st pVertex, PU16 sName, PU16 sPhone, PU16 sAddress, PU16 sNote);

MBOOL rmUserSettingAddHistory(SettingSectionName_t eSecName, Vertex_st vertex, PU16 sName, PU16 sPhone, PU16 sAddress, PU16 sNote, MBOOL bPOI, S32 s32POIID);
MBOOL rmUserSettingDelHistory(SettingSectionName_t eSecName, S32 s32Index);
S32 rmUserSettingGetHistory(SettingSectionName_t eSecName, pLocation_st *pArray);
pLocation_st rmUserSettingGetHistoryByIndex(SettingSectionName_t eSecName, S32 s32Index);

T_SETTING_CITY_NAME rmUserSettingGetCityName(MVOID);
MVOID rmUserSettingSetCityName(T_SETTING_CITY_NAME tCityName);

U32 rmUserSettingGetPOIOnMap(MVOID);
MVOID rmUserSettingSetPOIOnMap(U32 U32SettingPOIOnMap);

T_SETTING_MAP_COLOR rmUserSettingGetMapColor(MVOID);
MVOID rmUserSettingSetMapColor(T_SETTING_MAP_COLOR tSettingMapColor);

T_SETTING_GPS_SETTING rmUserSettingGetGPSSetting(MVOID);
MVOID rmUserSettingSetGPSSetting(T_SETTING_GPS_SETTING tSettingGPSSetting);

MVOID rmUserSettingSetLastLocation(S32 s32X, S32 s32Y);
Vertex_st rmUserSettingGetLastLocation(MVOID);

MBOOL rmLBSCookiesInit(MVOID);
MVOID rmLBSCookiesSave(MVOID);
MVOID rmLBSCookiesEnd(MVOID);
MBOOL rmLBSCookiesAddUrlHistory(boolean bIsReDirected, PU16 sURL, PU16 sURL_ReDirected, U32 u32ExpTimeInSec_UTC);
MBOOL rmLBSCookiesDelUrlHistoryByIndex(U32 u32Index);
MBOOL rmLBSCookiesDelUrlHistoryByUrl(PU16 sUrl);
pLBSCookies_URLHistory_st rmLBSCookiesGetUrlHistoryByIndex(U32 u32Index);
pLBSCookies_URLHistory_st rmLBSCookiesGetUrlHistoryByUrl(PU16 sUrl, U32 *u32Index);
MVOID rmLBSCookiesCleanUpUrlHistoryByTime(U32 u32CurrTimeInSec_UTC);
MBOOL rmLBSCookiesAddCacheFileMang(PU16 pCacheFileURL, PU16 pCacheFileXmlAssoc);
MBOOL rmLBSCookiesDelCacheFileByIndex(U32 u32Index);
pLBSCookies_CacheFileMang_st rmLBSCookiesGetCacheFileIndexByUrl(PU16 pUrl, U32 *u32Index);
pLBSCookies_CacheFileMang_st rmLBSCookiesGetCacheFileIndexByXmlAssoc(PU16 pXmlAssocUrl, U32 *u32Index);
#ifdef __cplusplus
}
#endif


#endif //_rmUserSetting_h_
