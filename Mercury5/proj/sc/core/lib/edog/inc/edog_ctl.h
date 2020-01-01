//------------------------------------------------------------------------------
//
//  File        : edog_ctl.h
//  Description :
//  Author      :
//  Revision    : 0.0
//
//------------------------------------------------------------------------------
#ifndef _EDOG_ctl_H_
#define _EDOG_ctl_H_

/*===========================================================================
 * Include file
 *===========================================================================*/

/*===========================================================================
 * Macro define
 *===========================================================================*/
typedef unsigned char EDOG_BOOL;
typedef void* EDOG_HANDLE;
#define EDOG_TRUE        (1)
#define EDOG_FALSE       (0)

//#define MENU_MOVIE_SPEED_CAR_EN    (1)

#define EDOG_ABS(a) (((a) < 0) ? (0 -(a)) : (a))
#define UNIT_DISTANCE_PER_SECOND_LON    30.8642 //Meter (40000KM/360/3600)=30M
#define UNIT_DISTANCE_PER_SECOND_LAT    30.8642 //

#define EARTH_RADIUS_A                  (6378137.0)    // Unit in meter
#define EARTH_RADIUS_B                  (6356752.3142) // Unit in meter
#define UNIT_DISTANCE_PER_DEGREE_LON    (( EARTH_RADIUS_A * 3.14159265359 / 180 )) //Meter (40000KM/360/3600)=30M
#define UNIT_DISTANCE_PER_DEGREE_LAT    (( EARTH_RADIUS_B * 3.14159265359 / 180 )) //


//AHC_Config_SDK
//#define EDOG_ANGLECHECK_EN            AHC_EDOG_ANGLECHECK_EN
//#define EDOG_SEARCHING_ANGLE          AHC_EDOG_SEARCHING_ANGLE
//#define EDOG_SEARCHING_ANGLE_ERR      AHC_EDOG_SEARCHING_ANGLE_ERR
//#define EDOG_TRIGGER_XANGLE           AHC_EDOG_TRIGGER_XANGLE

#define GPS_REMOVE_REDUNDANT_DATA       0


#define EDOG_TRIGGER_DISTANCE           300  //Meter
#define EDOG_TRIGGER_BOUNDRY            EDOG_TRIGGER_DISTANCE/UNIT_DISTANCE_PER_SECOND_LON

#define MAX_SPEED_CAM_INFO_BUILT_IN     6000//2000
#define MAX_SPEED_CAM_INFO_MANUAL       100
#define EDOGDATABASELENGTH              39 //included \r\n
#define LARGEBLOCKNUMBER                500
#define EDOG_CONFIG_BUFFER_SIZE         1024*100 //Buffer

//#ifndef PI
//#define PI                              3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
//#endif

#define DOT(x1, y1, x2, y2)             (x1*x2 + y1*y2)
#define CROSS(x1, y1, x2, y2)           (x1*y2 - x2*y1)

#define EDOGDBVERSIONLENGTH             12

//#define EDOG_DBG_EN                       (0)
#define EDOG_RAW_HEADER                 "$GPSDC\r\n"
#define EDOG_STOPALARMBEFORESPEEDCAM    (0)

//#define SPEED_CAM_DB_FILE_NAME        ("SF:1:\\SpeedCam_Data.bin") //TBD. Should be configed by API.
//#define SPEEM_CAM_MANUAL_DB           ("SF:2:\\SpeedCam_Data_Manual.bin") //TBD. Should be configed by API.
//#if EDOG_DB_DYNAMIC_SEGMENT
#define EDOG_FILE_LAYOUT_NUM_MAX        (30)
//#define MAPLAYOUT_HEADERNAME          ("SF:1:\\SpeedCam_FileHeader.bin")
//#define MAPLAYOUT_BASENAME            ("SF:1:\\DB")
//#define MAPLAYOUT_EXTNAME             (".bin")
#define MAP_OVERLAP_LAT                 (0.015)
#define MAP_OVERLAP_LON                 (0.03)
//#endif

#define EDOG_MANUAL_SPEED_LIMIT         (60)
#define EDOG_MANUAL_SPEED_VERSION       (1)

#define NEW_ON_TOP                      (0)
#define OLD_ON_TOP                      (1)
#define MANUAL_SPEED_DATA_ORDER         (NEW_ON_TOP)

/*===========================================================================
 * Enum define
 *===========================================================================*/

/*===========================================================================
 * Structure define
 *===========================================================================*/
typedef enum _DIST_METHOD {
    DIST_METHOD_NONE            = 0,
    DIST_METHOD_CARTESIAN       = 1,
    DIST_METHOD_GBL_CIRCLE_DIST = 2,
    DIST_METHOD_VINCENTY        = 3
}DIST_METHOD;

typedef enum _POINTOFINTEREST {
    POI_NULL            = 0,
    POI_SPEEDCAMERA     = 1,
    POI_HIGH_ACCIDENT   = 2

}POINTOFINTEREST;

typedef enum _POI_CARVIEWLR {
    POI_CARVIEWRIGHT    = 0,
    POI_CARVIEWLEFT     = 1,
    POI_CARVIEWCENTER   = 2,
    POI_CARVIEWNUM
}POI_CARVIEWLR;

typedef enum _SPEEDCAMSTATUS {
    SPEEDCAM_STATUS_NO_ENCOUNTER    = 0,
    SPEEDCAM_STATUS_ENCOUNTER       = 1,
    SPEEDCAM_STATUS_APPROACH        = 2,
    SPEEDCAM_STATUS_LEAVE           = 3,
    SPEEDCAM_STATUS_STOP_ALERT      = 4

}SPEEDCAMSTATUS;

typedef enum _EDOGPOSITION {
    EDOG_POS_CORNER_DL              = 0,
    EDOG_POS_CORNER_DR              = 1,
    EDOG_POS_CORNER_UL              = 2,
    EDOG_POS_CORNER_UR              = 3,
    EDOG_POS_CORNER_U               = 4,
    EDOG_POS_CORNER_D               = 5,
    EDOG_POS_CORNER_L               = 6,
    EDOG_POS_CORNER_R               = 7

}EDOGPOSITION;

//#if EDOG_DB_DYNAMIC_SEGMENT
typedef enum _MAPOVERLAPTYPE {
    MAPOVERLAP_NONE     = 0x00,
    MAPOVERLAP_EDGE     = 0x01,
    MAPOVERLAP_INSIDE   = 0x02,
    MAPOVERLAP_UPPER    = 0x04

}MAPOVERLAPTYPE;
//#endif

typedef enum _SPEEDCAMDBTYPE {
    EDOG_DB_BUILT_IN                = 0,
    EDOG_DB_MANUAL_ADD              = 1,
    EDOG_DB_NUM                     = 2
}SPEEDCAMDBTYPE;

typedef enum _EDOGINITSTATE {
    EDOG_INIT_NONE              = 0,
    EDOG_INIT_START,
    EDOG_INIT_DONE
}EDOGINITSTATE;

typedef struct _SPEEDCAMGLBHEADER
{
    short  usST_Lon;
    short  usST_Lat;
    short  usED_Lon;
    short  usED_Lat;
    short  SB_NUM_Lon;
    short  SB_NUM_Lat;
    short  LB_NUM_Lon;
    short  LB_NUM_Lat;
    unsigned char  ubVersion;
    unsigned char  Dummy[3];
}SPEEDCAMGLBHEADER;

typedef struct _SPEEDCAMGLBHEADER_EX
{
    unsigned int  ulDBVersion;
    unsigned char  ubTransFormDate[EDOGDBVERSIONLENGTH];
}SPEEDCAMGLBHEADER_EX;

typedef struct _SPEEDCAMERALAYER
{
    short TotalPoints;
    short ST_Lat;
    short ST_Lon;
    short ED_lat;
    short ED_lon;

}SPEEDCAMERALAYER;

typedef struct _COORDINFO
{
    short SB_x;
    short SB_y;
    short LB_x;
    short LB_y;

}COORDINFO;

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(4)     /* set alignment to 4 byte boundary */
typedef struct _SPEEDCAMERA_DBL
{
    double                  dwLat;/**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    double                  dwLon;/**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    unsigned char           ubSpeed;/**< Speed unit: km/h */
    unsigned char           ubDirection;/**< Clockwise degree from the North/2.*/
    unsigned char           ubPOI;  //Refer to POINTOFINTEREST;
    unsigned char           ubDirType;
}SPEEDCAMERA_DBL;
#pragma pack(pop)  /* pop current alignment from stack */

typedef struct _SPEEDCAMERA_FLOAT
{
    float                   dfLat;/**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    float                   dfLon;/**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    unsigned char           ubSpeed;/**< Speed unit: km/h */
    unsigned char           ubDirection;/**< Clockwise degree from the North/2.*/
    unsigned char           ubPOI;  //Refer to POINTOFINTEREST;
    unsigned char           ubDirType;
}SPEEDCAMERA_FLOAT;


typedef struct _SPEEDCAMERA
{
    double                  dwLat;/**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    double                  dwLon;/**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    unsigned char           ubSpeed;/**< Speed unit: km/h */
    unsigned char           ubDirection;/**< Clockwise degree from the North/2.*/
    unsigned char           ubPOI;  //Refer to POINTOFINTEREST;
    unsigned char           ubDirType;
}SPEEDCAMERA;

typedef struct _POSITIONINFO
{
    COORDINFO       ul;
    COORDINFO       u;
    COORDINFO       ur;
    COORDINFO       l;
    COORDINFO       c;
    COORDINFO       r;
    COORDINFO       dl;
    COORDINFO       d;
    COORDINFO       dr;
    unsigned short  usTotalPoint;
    unsigned char   bEncounter;
    unsigned char   bStartPlaySound;
    unsigned char   bStartUI;
    unsigned char   bReDraw;
    unsigned char   ubSpeedLimit;
    unsigned char   ubPOItype;
    unsigned char   ubDirType;
    unsigned short  usDistance;
    double          dLockLat;
    double          dLockLon;
    float           fLockLat;
    float           fLockLon;
    unsigned char   bOriginalLCDOn;
    unsigned char   ubStatus;
    //#if EDOG_DB_DYNAMIC_SEGMENT
    unsigned char   ubCurMapIndex;
    unsigned char   ubCurMapOverlapType;
    //#endif
    unsigned char   ubDBType;
}POSITIONINFO, *sPosInfo;

//Copyed from AHC_RTC_TIME. It maybe combined with EDOG_NMEATIME. TBD
typedef struct _EDOG_RTC_TIME
{
    unsigned short uwYear;
    unsigned short uwMonth;
    unsigned short uwDay;       //The date of January is 1~31
    unsigned short uwDayInWeek; //Sunday ~ Saturday
    unsigned short uwHour;
    unsigned short uwMinute;
    unsigned short uwSecond;
    unsigned char ubAmOrPm;     //am: 0, pm: 1, work only at b_12FormatEn = MMP_TURE
    unsigned char b_12FormatEn;  //for set time, to indacate which format, 0 for 24 Hours,   //1 for 12 Hours format
}EDOG_RTC_TIME; //Sync it with AUTL_DATETIME

typedef struct _MANUALCAMERAHEADER
{
    unsigned int                ulTotalCount;
    unsigned int                ulCheckSum;
    unsigned int                ulCheckSumHeader;
    unsigned int                ulDummy[12];
    unsigned char               ubVersion;
    unsigned char               ubDummy[3];
}MANUALCAMERAHEADER;

typedef struct _MANUALSPEEDCAMERA
{
    double                  dwLat;/**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    double                  dwLon;/**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    EDOG_RTC_TIME           sRTC;
    unsigned char           ubDirection;/**< Clockwise degree from the North/2.*/
    unsigned char           ubPOI;  //Refer to POINTOFINTEREST;
    unsigned char           ubDirType;
    unsigned char           dummy[1];

}MANUALSPEEDCAMERA, *pSpeedCamInfo;

//#if EDOG_DB_DYNAMIC_SEGMENT
typedef struct _FILELAYOUTINFO
{
    unsigned int ulOffset;
    unsigned int ulFileSize;
    unsigned int ulCheckSum;
}FILELAYOUTINFO;

typedef struct _DYNAMICSEGMENTHEADER
{
    unsigned int ulSignature; //One file or divided into several files;
    unsigned int ulSKUID_1;
    unsigned int ulSKUID_2;
    unsigned char ubID[32];
    unsigned int ulFlag;
}DYNAMICSEGMENTHEADER;

typedef struct _FILELAYOUTTABLE
{
    unsigned int ulTotalPart;
    FILELAYOUTINFO sFileInfo[EDOG_FILE_LAYOUT_NUM_MAX];
}FILELAYOUTTABLE, *sLayoutTable;

typedef struct _MAPLAYOUTTABLE
{
    unsigned char ubMapIndex;
    unsigned short ulLat;
    unsigned short ulLon;
    unsigned short drLat;
    unsigned short drLon;
    unsigned short SB_NUM_Lon;
    unsigned short SB_NUM_Lat;
    unsigned short LB_NUM_Lon;
    unsigned short LB_NUM_Lat;
    unsigned char ubOverlapType;

}MAPLAYOUTTABLE;

//#endif //#if EDOG_DB_DYNAMIC_SEGMENT

/*===========================================================================
 * IO functions definition.
 *===========================================================================*/
//#define EDOG_STRCPY strcpy
//#define EDOG_STRCAT strcat
//#define EDOG_MEMSET0(s)      memset(s,0,sizeof(*s))
#define  EDOG_FS_SEEK_SET   0
#define  EDOG_FS_SEEK_CUR   1
#define  EDOG_FS_SEEK_END   2
typedef enum _EDOG_ERR
{
    EDOG_ERR_NONE = 0x00000000,
    EDOG_ERR_FS_FAIL,
    EDOG_ERR_MAX
} EDOG_ERR;

typedef struct
{
    EDOG_HANDLE  *h_dec;
    double       dwLat;        /**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    double       dwLon;        /**< Longitude in NDEG - +/-[degree][min].[sec/60] */
    double       dwSpeed;      /**< Speed over the ground in kilometers/hour */
    double       dwDirection;  /**< Track angle in degrees True */
} GPS_DATA_BUF;

typedef enum _EDOGIO_FUNC_ENUM
{
    EDOGIO_FUNC_ENUM_PRINTF = 0x00000000,

    EDOGIO_FUNC_ENUM_FS_OPEN,
    EDOGIO_FUNC_ENUM_FS_CLOSE,
    EDOGIO_FUNC_ENUM_FS_READ,
    EDOGIO_FUNC_ENUM_FS_WRITE,
    EDOGIO_FUNC_ENUM_FS_SEEK,
    EDOGIO_FUNC_ENUM_FS_GET_FILESIZE,

    EDOGIO_FUNC_ENUM_GPS_GETINFORMATION,
    EDOGIO_FUNC_ENUM_GPS_ISATTACHED,
    EDOGIO_FUNC_ENUM_GPS_ISVALIDVALUE,
    EDOGIO_FUNC_ENUM_GPS_DMM2DEGREE_DBL,
    EDOGIO_FUNC_ENUM_GPS_DEGREE2DMM_DBL,
    EDOGIO_FUNC_ENUM_GPS_DMM2DEGREE_FLOAT,
    EDOGIO_FUNC_ENUM_GPS_DEGREE2DMM_FLOAT,
    EDOGIO_FUNC_ENUM_GPS_ISEOF,
    EDOGIO_FUNC_ENUM_GPS_RESETEOF,

    EDOGIO_FUNC_ENUM_RTC_GETTIME,

    EDOGIO_FUNC_ENUM_LED_CTRL_LCDBACKLIGHT,
    EDOGIO_FUNC_ENUM_LED_CTRL_BACKLIGHT_STATUS,

    EDOGIO_FUNC_ENUM_MAX
} EDOGIO_FUNC_ENUM;

typedef void (*EDOGIO_PRINTF)(char* , ...);

typedef EDOG_ERR (*EDOGIO_FS_OPEN)(char *, char *, unsigned int *);
typedef EDOG_ERR (*EDOGIO_FS_CLOSE)(unsigned int );
typedef EDOG_ERR (*EDOGIO_FS_READ)(unsigned int, unsigned char *, unsigned int, unsigned int *);
typedef EDOG_ERR (*EDOGIO_FS_WRITE)(unsigned int, unsigned char *, unsigned int, unsigned int *);
typedef EDOG_ERR (*EDOGIO_FS_SEEK)(unsigned int, long long, int);
typedef EDOG_ERR (*EDOGIO_FS_GET_FILESIZE)(unsigned int, unsigned int *);

//typedef pEDOGNmeaInfo (*EDOGIO_GPS_GETINFORMATION)(void);
typedef EDOG_BOOL (*EDOGIO_GPS_ISATTACHED)(void);
typedef EDOG_BOOL (*EDOGIO_GPS_ISVALIDVALUE)(void);
typedef double (*EDOGIO_GPS_DMM2DEGREE_DBL)(double);
typedef double (*EDOGIO_GPS_DEGREE2DMM_DBL)(double);
typedef float (*EDOGIO_GPS_DMM2DEGREE_FLOAT)(float);
typedef float (*EDOGIO_GPS_DEGREE2DMM_FLOAT)(float);
typedef EDOG_BOOL (*EDOGIO_GPS_ISEOF)(void);
typedef void (*EDOGIO_GPS_RESETEOF)(void);

typedef void (*EDOGIO_RTC_GETTIME)(EDOG_RTC_TIME *);

typedef void (*EDOGIO_LED_LCDBACKLIGHT)(EDOG_BOOL);
typedef EDOG_BOOL (*EDOGIO_LED_BACKLIGHT_STATUS)(void);
/*===========================================================================
 * Extern varible
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/

void        EDOGCtrl_UpdateSpeedCameraArray_BLOCK(unsigned int LargeLayerIndex, unsigned int SmallLayerIndex, unsigned int ArrayIndex, unsigned int *UpdateCount);
void        EDOGCtrl_UpdateSpeedCameraArray_ALL(void);
void        EDOGCtrl_ReadGlobalHeader(void);
void        EDOGCtrl_UpdatePositionInfo_double(double lat, double lon);
void        EDOGCtrl_CheckCurrentCoordinate_double(double lat, double lon, unsigned short *lx, unsigned short *ly, unsigned short *sx, unsigned short *sy);
void        EDOGCtrl_CheckSpeedCamera_double(EDOG_HANDLE *h, unsigned char *bEncounter, unsigned char *ubSpeedLimit, unsigned char *POItype, unsigned char *Dirtype, unsigned short *osDistance, double *locklat, double *locklon, unsigned char *POIDB);
void        EDOGCtrl_UpdatePositionInfo_float(float lat, float lon);
void        EDOGCtrl_CheckCurrentCoordinate_float(float lat, float lon, unsigned short *lx, unsigned short *ly, unsigned short *sx, unsigned short *sy);
void        EDOGCtrl_CheckSpeedCamera_float(EDOG_HANDLE*h, unsigned char *bEncounter, unsigned char *ubSpeedLimit, unsigned char *POItype, unsigned char *Dirtype, unsigned short *osDistance, float *locklat, float *locklon, unsigned char *POIDB);
void        EDOGCtrl_Initial(void);
EDOG_BOOL   EDOGCtrl_IsInitial(void);
void        EDOGCtrl_UpdatePOIArray_Manual(EDOG_HANDLE *h);
void        EDOGCtrl_ReadPOIfromFile_Manual(void);
void        EDOGCtrl_RestoesPOItoFile_Manual(void);
EDOG_BOOL   EDOGCtrl_AddPOI_Manual(EDOG_HANDLE *h);
EDOG_BOOL   EDOGCtrl_DeletPOI_Manual(unsigned int ulIndex);
void        EDOGCtrl_GetTotalIndex(unsigned int *ulTotalIndex);
MANUALSPEEDCAMERA* EDOGCtrl_GetPOI_Manual(unsigned int ulIndex);
void        EDOGCtrl_ReadManualHeader(void);
void        EDOGCtrl_ClearAllManualSetting(void);
void        EDOGCtrl_ListAllCameraInfo(void);

EDOG_BOOL   EDOGCtrl_NeedtoUpdate(unsigned short lx, unsigned short ly, unsigned short sx, unsigned short sy);
void        EDOGCtrl_Handler(EDOG_HANDLE *h);
sPosInfo    EDOGCtrl_Information(void);
EDOG_BOOL   EDOGCtrl_IsOverSpeedLimit(EDOG_HANDLE *h);
EDOG_BOOL   EDOGCtrl_CheckIsHeaderValid(void);
void        EDOGCtrl_ClearAllManualSetting(void);
void        EDOGCtrl_TestCode(EDOG_HANDLE *h);
void        EDOGCtrl_ParseHeader(EDOG_HANDLE *h);
void        EDOGCtrl_SetLCDstatusToOn(void);
EDOG_BOOL   EDOGCtrl_GetDBVersion(char *szDVversion, unsigned int ulSize);
EDOG_BOOL   EDOGCtrl_SpeedCamCheckSum(unsigned int* ulValue );
EDOG_BOOL   EDOGCtrl_SpeedCamCheckSum_float(unsigned int* ulValue );
//#if EDOG_DB_DYNAMIC_SEGMENT
sLayoutTable EDOGCtrl_HeaderInfo(void);
void        EDOGCtrl_ParseDBHeader(unsigned int ulFileID);
void        EDOGCtrl_ParseMapLayout(void);
void        EDOGCtrl_CheckOverlapType(void);
EDOG_BOOL   EDOGCtrl_NeedToReloadMap(EDOG_HANDLE *h, unsigned int* ubLoadInxex);
EDOG_BOOL   EDOGCtrl_ReloadMap(unsigned char ubLoadInxex, unsigned int *MapFileID);
EDOG_BOOL   EDOGCtrl_CheckOverlapPosition(float inlat, float inlon, unsigned char* ubOverlapIndex);
//#endif //#if EDOG_DB_DYNAMIC_SEGMENT

double DegreeToGpsDmm_double(double dblLatLonDmm);
double GpsDmmToDegree_double(double dblLatLonDmm );
float  DegreeToGpsDmm_float(float fLatLonDmm);
float  GpsDmmToDegree_float(float dblLatLonDmm );

EDOG_BOOL EDOGCtrl_IsManualVersionCorrect(void);
EDOG_BOOL EDOGCtrl_BackupManualDB(void);
EDOG_BOOL EDOGCtrl_WriteBackManualDB(void);

#if 1//(MENU_MOVIE_SPEED_CAR_EN)
unsigned char   EDOGCtrl_SpeedCamSpeedLimit(void);
double          EDOGCtrl_CurrentSpeed(void);
unsigned char   EDOGCtrl_IsSPCAMAlerted(void);
unsigned char   EDOGCtrl_IsSPCAMFound(void);
unsigned char   EDOGCtrl_IsSPCAMAway(void);
unsigned char   EDOGCtrl_SetSPCAMAwayStatus(unsigned char bEn);
unsigned char   EDOGCtrl_SetSPCAMFoundStatus(unsigned char bEn);
unsigned int    EDOGCtrl_CurrentDist(void);
unsigned char   EDOGCtrl_SetSpeedLvl(unsigned int ulLvl);
unsigned char   EDOGCtrl_SetSpeedDist(unsigned int ulDist);
unsigned char   EDOGCtrl_SetCheckAngleEn(unsigned char ubEn);
unsigned char   EDOGCtrl_SetSearchAngle(unsigned short ulAngle);
unsigned char   EDOGCtrl_SetSearchXAngle(unsigned short ulXAngle);
unsigned char   EDOGCtrl_SetPoiDataType(unsigned char ubPoiType);
unsigned char   EDOGCtrl_GetPoiDataType(void);
unsigned char   EDOGCtrl_EnAddSpeedCamPOI(unsigned char ubEnAddCamPOI);
unsigned char   EDOGCtrl_GetAddSpeedCamPOI(void);
unsigned char   EDOGCtrl_SetDistMethod(DIST_METHOD ubDistMethod);
unsigned char   EDOGCtrl_SetBaseName(char ubFileName[]);
unsigned char   *EDOGCtrl_GetBaseName(void);
unsigned char   EDOGCtrl_SetExtName(char ubExtension[]);
unsigned char   *EDOGCtrl_GetExtName(void);
unsigned char   EDOGCtrl_GetCameraType(void);
unsigned char   *EDOGCtrl_GetEdogVersion(void);
unsigned char   EDOGCtrl_SetEnEdogLog(unsigned char ubEnEdoglog);
unsigned char   EDOGCtrl_SetEnGpsSimulator(unsigned char ubEnGpsSim);
#endif

#endif