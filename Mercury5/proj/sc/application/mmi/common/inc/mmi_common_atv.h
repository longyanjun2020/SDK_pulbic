
#ifndef __MMI_COMMON_ATV_H__
#define __MMI_COMMON_ATV_H__

#define IATV_STORED_PATH_LEN 100

/**
*  @brief The enumeration defines the mode of tv snapshot.
*/
typedef enum 
{       
	IATV_TV_SINGLE,      /**< Tv single shot mode */
	IATV_TV_CONSSINGLE,  /**< Tv continuous shot mode */
} iatv_TvShotMode_e;

typedef enum
{
	IATV_TV_CAPTURE_SOUND_OFF = 0,
	IATV_TV_CAPTURE_SOUND_ON
} iatv_TvShutterSound_e;

/**
*  @brief The enumeration defines TV nations' region.
*/
typedef enum {
	IATV_TV_REGION_USA = 0,      /*USA*/
	IATV_TV_REGION_CANADA,       /*CANADA*/
	IATV_TV_REGION_KOREA,        /*KOREA*/
	IATV_TV_REGION_TAIWAN,       /*TAIWAN*/
	IATV_TV_REGION_MEXICO,       /*MEXICO*/
	IATV_TV_REGION_CHILE,        /*CHILE*/
	IATV_TV_REGION_VENEZUELA,    /*VENEZUELA*/
	IATV_TV_REGION_PHILIPPINES,  /*PHILIPPINES*/ 
	IATV_TV_REGION_JAMAICA,      /*JAMAICA*/
	IATV_TV_REGION_CHINA,        /*CHINA*/
	IATV_TV_REGION_SHENZHEN,     /*SHENZHE*/
	IATV_TV_REGION_VIETNAM,      /*VIETNAM*/
	IATV_TV_REGION_WESTERNEUROPE,/*WESTERNEUROPE*/
	IATV_TV_REGION_TURKEY,       /*TURKEY*/
	IATV_TV_REGION_UAE,          /*UAE*/
	IATV_TV_REGION_AFGHANISTAN,  /*AFGHANISTAN*/ 
	IATV_TV_REGION_SINGAPORE,    /*SINGAPORE*/ 
	IATV_TV_REGION_THAILAND,     /*THAILAND*/    
	IATV_TV_REGION_CAMBODIA,     /*CAMBODIA*/  
	IATV_TV_REGION_INDONESIA,    /*INDONESIA*/   
	IATV_TV_REGION_MALAYSIA,     /*MALAYSIA*/  
	IATV_TV_REGION_LAOS,         /*LAOS*/
	IATV_TV_REGION_PORTUGAL,     /*PORTUGAL*/
	IATV_TV_REGION_SWEDEN,       /*SWEDEN*/
	IATV_TV_REGION_PAKISTAN,     /*PAKISTAN*/    
	IATV_TV_REGION_SPAIN,        /*SPAIN*/ 
	IATV_TV_REGION_JAPAN,        /*JAPAN*/ 
	IATV_TV_REGION_UK,           /*UK*/        
	IATV_TV_REGION_HONGKONG,     /*HONGKONG*/    
	IATV_TV_REGION_SOUTHAFRICA,  /*SOUTHAFRICA*/     
	IATV_TV_REGION_BRAZIL,       /*BRAZIL*/          
	IATV_TV_REGION_ARGENTINA,    /*ARGENTINA*/       
	IATV_TV_REGION_INDIA,        /*INDIA*/         
	IATV_TV_REGION_BURMA,        /*BURMA*/         
	IATV_TV_REGION_SUDAN,        /*SUDAN*/         
	IATV_TV_REGION_YEMEN,        /*YEMEN*/         
	IATV_TV_REGION_PERU,         /*PERU*/          
	IATV_TV_REGION_BOLIVIA,      /*BOLIVIA*/       
	IATV_TV_REGION_ECUADOR,      /*ECUADOR*/       
	IATV_TV_REGION_SURINAME,     /*SURINAME*/        
	IATV_TV_REGION_AUSTRALIA,    /*AUSTRALIA*/       
	IATV_TV_REGION_NEWZEALAND,   /*NEWZEALAND*/      
	IATV_TV_REGION_COLUMBIA,     /*COLUMBIA*/        
	IATV_TV_REGION_COSTARICA,    /*COSTARICA*/     
	IATV_TV_REGION_HONDURAS,     /*HONDURAS*/      
	IATV_TV_REGION_GERMAN,       /*GERMAN*/      
	IATV_TV_REGION_ITALY,        /*ITALY*/       
	IATV_TV_REGION_TOTAL         /*MAXIMUM REGION NUMBER*/ 
} iatv_TvRegion_e;

/**
*  @brief The structure defines the tv capture resolution.
*/
typedef enum {
	IATV_TV_RATIO_4_3 ,
	IATV_TV_RATIO_16_9 ,
	IATV_TV_RATIO_16_10
} iatv_TvRatio_e;

/**
*  @brief The structure defines the window area property.
*/
typedef struct { 
	u16   posX;     /**< Horizontal position of top-left */
	u16   posY;     /**< Vertical position of top-left */
	u16   width;    /**< Horizontal width */
	u16   height;   /**< Vertical height */
} iatv_TvRegion_t;

/**
*  @brief The structure defines the tv capture resolution.
*/
typedef enum {
	IATV_TV_UXGA_1600_1200,  /* 1600x1200(UXGA) */
	IATV_TV_1_3M_1280_1024,  /* 1280x1024(1.3M pixel) */
	IATV_TV_1024_768,   /* 1024x768 */
	IATV_TV_800_600,    /* 800x600 */
	IATV_TV_VGA_640_480,    /* 640x480(VGA) */
	IATV_TV_QVGA_320_240,    /* 320x240(QVGA) */
	IATV_TV_Wallpaper_240_320,    /* 240x320(Wallpaper) */
	IATV_TV_Wallpaper_176_220,    /* 176x220(Wallpaper)*/
	IATV_TV_QQVGA_160_120,    /* 160x120(QQVGA) */
	IATV_TV_Contact_96_96       /* For Contact */
} iatv_TvCaptureRes_e;

/**
*  @brief The enumeration defines the path of loading shutter sound.
*/
typedef enum {
	IATV_TV_SOUND_DEFAULT,  /**< Using the default sound in MMP */
	IATV_TV_SOUND_DOWNLOAD, /**< Using the sound that load from BB */
	IATV_TV_SOUND_CARD,     /**< Using the sound that save in card */
} iatv_TvSoundPath_e;

/**
*  @brief The sturcture defines the property of the camera shutter sound.
*/
typedef struct {
	iatv_TvSoundPath_e  soundPath; /**< The shutter sound path that want to use */
	u8                 *pSound;   /**< PCM data buffer or file name in card (MMI should release buffer after receiving response msg)  */
	u32                soundLen;  /**< The length of PCM or filen name in card */
} iatv_TvSound_t;

typedef union
{
	iatv_TvCaptureRes_e		atvPicRes;
	//iatv_TvVdoResolution_t atvVdoRes;
} iatv_TvResolution_t;

/**
*  @brief The enumeration defines the tv rotation angle
*/
typedef enum {
	IATV_TV_ROTATE_NONE, /**< No Rotation */ 
	IATV_TV_ROTATE_90,   /**< Rotate angle 90 degree */ 
	IATV_TV_ROTATE_180,  /**< Rotate angle 180 degree */ 
	IATV_TV_ROTATE_270   /**< Rotate angle 270 degree */ 
} iatv_TvRotate_e;

/**
*  @brief The enumeration defines the tv capture recording quality.
*/
typedef enum {
	IATV_TV_QUALITY_LOW,     /* Low quality */
	IATV_TV_QUALITY_NORMAL,  /* Nomal quality */
	IATV_TV_QUALITY_HIGH     /* High quality */
} iatv_ImgQuality_e;

typedef enum
{
	IATV_TV_STORAGE_PHONE = 0,
	IATV_TV_STORAGE_CARD
} iatv_CaptureStorage_e;

/**
*  @brief The structure defines the tv signal.
*/
typedef enum {
	IATV_TV_SIGNAL_LV_NONE = 0,  /* signal level 0 (not recieve signal) */
	IATV_TV_SIGNAL_LV_1,         /* signal level 1  */
	IATV_TV_SIGNAL_LV_2,         /* signal level 2  */
	IATV_TV_SIGNAL_LV_3,         /* signal level 3  */
	IATV_TV_SIGNAL_LV_4,         /* signal level 4  */
	IATV_TV_SIGNAL_LV_5,         /* signal level 5  */
	IATV_TV_SIGNAL_LV_6,         /* signal level 6  */
	IATV_TV_SIGNAL_LV_7,         /* signal level 7  */
	IATV_TV_SIGNAL_LV_8,         /* signal level 8  */
	IATV_TV_SIGNAL_LV_9,         /* signal level 9  */
	IATV_TV_SIGNAL_LV_MAX,       /*signal level max */
} iatv_TvSignalLv_e;

/**
*  @brief The sturcture defines the file name and length of the last jpeg or 3gp file.
*/
typedef struct {
	u16 outLen;        /**< file name length */
	u16 *pFileNameOut; /**< file name buffer (MMI should release file name buffer after receiving response msg) */
} iatv_TvFileName_t;

/**
*  @brief The sturcture defines the return value for application layer (MMI) query.
*/
typedef struct {
	union {
		iatv_TvFileName_t tvFileName; /**< File name output information response from 'TV_Capture' Request */
		struct {
			u32 totalChn;                 /**< Total capacity of channels in current area */
			iatv_TvSignalLv_e  singalLv;    /**< Tv signal level */
		} info;                         /**< Information resonse from 'GetInfo' Request */
		struct {
			u32  ch;       /**< the scanning channel */
			boolean isExist;  /**< this channel was found and exist in this scanning (TRUE: exist, FALSE: it not scanned*/
		} scan;            /**< Information resonse from 'ScanChn' Request */
	} param;  
} iatv_TvInfo_t;

/**
*  @brief The enumeration defines type of the TV error.
*/
typedef enum {
	IATV_ERROR_CAPTURE = 0,         /**< TV error type about file action fail */
	IATV_ERROR_SPACE_FULL,          /**< Notify MMI that space full error */
	IATV_ERROR_UNKNOWN,             /**< TV error type about unknown type */
	IATV_ERROR_NONE                 /**< TV error type about no error */
} iatv_TvErrorType_e;

// Config definition
typedef struct IATVConfig_TAG
{
	MAE_WChar				pTvStoredPath[IATV_STORED_PATH_LEN+1];	// *Storage
	u16						u16PathLen;								// Storage
	
	iatv_TvShutterSound_e   eTvShutterSound;
	iatv_TvResolution_t		tTvResolution;		// *Image Size
	iatv_ImgQuality_e		eTvImgQty;			// Currently, both image quality and video quality set the same config, jpegQuality!
	//iatv_VdoQuality_t		tTvVdoQty;
	//MAECameraVdoSound_t		camVdoSound;		// Video recording sound
	//iatv_CaptureStorage_e   eCaptureStorage;	/* Move to ATVInfo_t. */
	iatv_TvShotMode_e       eShotMode;
	iatv_TvSoundPath_e      eSoundPath;
	//u8						padding1;
	//u8						padding2;
	//u8						padding3;
	//u8					u8SkipFrameNum;		// 0 ~ 63, skip 0 ~ 63 frame
	//u8					u8BurstShootNum;	// *Multi-shot, 1 ~ 16, 0 denote single snapshot
	//u8					u8JpegQuality;		// 1 ~ 63, (Quality level: 1: best, 63: worst)
} iatv_Config_t;

#endif //__MMI_COMMON_ATV_H__
