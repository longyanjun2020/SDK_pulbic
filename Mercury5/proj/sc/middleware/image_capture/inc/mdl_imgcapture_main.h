#ifndef _IMGCAPTURE_MAIN_H_
#define _IMGCAPTURE_MAIN_H_

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "sys_sys_arm.h"
//#include "kernel.h"

//image capture public header file
//#include "mdl_image_capture_pub.h"
#include "mdl_vfs_file.ho"
#include "mdl_vfs_errno.h"
#include "mdl_vfs_struct.h"
#include <string.h>
//MML public header file
#include "srv_resmgr_mmlcamera_types.h"
#include "srv_resmgr_mmlimage_types.h"
#include "srv_ResMgr_MmlManager.h"
//Image capture public
#include "mdl_image_capture_pub.h"
#ifndef true
// definition for true
#define true                (1)
// definition for false
#define false               (0)
#endif


/*--------------------S-----------------------------------------------------*/
/* CONSTANT DEFINITION                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* MACRO DEFINITION                                                         */
/*--------------------------------------------------------------------------*/
#define IMG_CAP_DBG_LEVEL                 (_CUS2 | LEVEL_5)/* Trace Filter of image capture  */

/*--------------------------------------------------------------------------*/
/* DATA TYPE DEFINITION                                                     */
/*--------------------------------------------------------------------------*/
// is_short_dct definition


// jpe output bitstream
#define IMGCAP_NORMAL_WRITE 0
#define IMGCAP_BUFFER_WRITE 1

#define BANKCOUNT 2
#define JPEGENC_LBC_BUFSIZE             (2048 * 16 * 2) // support up to 3M sensor
#define JPE_IIS_BUFSIZE                 (10*1024)


#define JPE_SHUTTER_SND_BUFSIZE         (20*1024)
#define JPEGENC_STACKSIZE               (1024*10)
#define JPGHEADERBUFFER_SIZE            (14*1024)// 14K header buffer + 10k thumbnail buffer
#define JPE_BSBUF_SIZE_SDRAM            (480*1024)
#define JPD_OUTPUT_BUFSIZE              (24*1024)//RGB565 : 128x96x2
#define JPE_THUMBNAIL_BUFSIZE_SDRAM     (10*1024)

#define JPGHEADER_BUFFER_NOThumbnail    (3*1024)// 3K header buffer
#define JPE_BSBUF_SIZE_SDRAM_2MP        (440*1024)
#define JPE_BSBUF_SIZE_SDRAM_3MP        (550*1024)
#define JPE_BSBUF_SIZE_SDRAM_JPEGMODE    (1000*1024)

#define JPE_GLOBAL_BUFSIZE              (4*1024)

#define JPE_SRAMDUMMY_ALILEN            (256)
#define JPE_DRAMDUMMY_ALILEN            (32)

#define JPE_BSRAWOUT_SDRAM              (100*1024)//MMS max size 100kbytes
#define JPGHEADER                       (JPGHEADER_BUFFER_NOThumbnail+JPGHEADER_BUFFER_NOThumbnail+JPE_GLOBAL_BUFSIZE)

#define SCL_ROT_RESERVE                 (480*32) //support up to HVGA
typedef enum
{
    MIDJPE_INPUTMODE_NORMAL,
    MIDJPE_INPUTMODE_BUF,
    MIDJPE_INPUTMODE_UVC,
    MIDJPE_INPUTMODE_ATV,
    MIDJPE_INPUTMODE_PHOTOSTICK,
} MIDJPE_INPUTMODE;

typedef enum
{
    MIDJPE_CAPTUREMODE_CONTINUOUS = 0, 
    MIDJPE_ROTATIONCAPTURE,            ///< Rotation capture
    MIDJPE_CAPTUREMODE_ATVSNAPSHOT,      ///< ATV snapshot
    MIDJPE_CAPTUREMODE_PHOTOSTICKER,     ///< Photo sticker
    MIDJPE_CAPTUREMODE_PANORAMA,         ///< Panorama
    MIDJPE_CAPTUREMODE_LOMO_4LENS,       ///< LOMO 4 lens
    MIDJPE_CAPTUREMODE_MIRROR,           ///< Mirror    
    /* */
    MIDJPE_CAPTUREMODE_NUM
} MDLCaptureMode_e;

typedef enum
{
    MIDJPE_SPECIALEFFECT_NONE = 0,
    MIDJPE_SPECIALEFFECT_PANORAMA,         ///< Panorama
    MIDJPE_SPECIALEFFECT_LOMO_4LENS,       ///< LOMO 4 lens
    MIDJPE_SPECIALEFFECT_MIRROR,           ///< Mirror 
    /* */    
    MIDJPE_SPECIALEFFECT_NUM
} MDLCapSpecialEffect_e;

typedef enum
{
    MIDJPE__ROTATION_0 = 0,
    MIDJPE__ROTATION_90,
    MIDJPE__ROTATION_180,
    MIDJPE__ROTATION_270,
    /* */
    MIDJPE__ROTATION_NUM
} MDLCapRotAngle_e;

typedef enum
{
    MIDJPE_HWCONFIG_DCT = 0x0001,
    MIDJPE_HWCONFIG_GRAY = 0x0002,
    MIDJPE_HWCONFIG_BSMODE = 0x0004,
} MIDJPE_HWCONFIG;

typedef enum
{
    MDLJPE_OUTMODE_NONE = 0,
    MDLJPE_OUTMODE_SD,
    MDLJPE_OUTMODE_BUF,
} MDLJPE_OUTMODE;

typedef enum
{
    MDLJPE_TopLeft = 1,
    MDLJPE_TopRight,
    MDLJPE_BottomRight,
    MDLJPE_BottomLeft,
    MDLJPE_LeftTop,
    MDLJPE_RightTop,
    MDLJPE_RightBottom,
    MDLJPE_LeftBottom
} MDLJPE_ORIENTATION;

typedef enum
{
    MDLJPE_HIGHQ = 0,
    MDLJPE_NORMALQ,
    MDLJPE_LOWQ,
} MDLJPE_QTBL;

typedef enum
{
    MDLJPE_QLEVEL_1 = 0,
    MDLJPE_QLEVEL_2,
    MDLJPE_QLEVEL_3,
    MDLJPE_QLEVEL_4,
    MDLJPE_QLEVEL_5,
    MDLJPE_QLEVEL_6,
}MDLJPE_QLEVEL;

typedef enum
{
    JPE_FILENAMEFORMAT_DIRECTORY = 0x0,    ///< Specify the folder only
    JPE_FILENAMEFORMAT_PREFIX,             ///< Specify the folder + filename's prefix
    JPE_FILENAMEFORMAT_ABSOLUTE,           ///< Specify the folder + filename
} JPEFilenameFormat_e;

typedef enum
{
    MDLJPE_YUV_MODE =0,
    MDLJPE_JPG_MODE,
}MDLJPE_SenDataFormat_e;

typedef enum
{
    MDLJPE_YUV_422 =0,
    MDLJPE_YUV_420,
}MDLJPE_EnFormat_e;
//Need Check typedef enum "VFS_VOL_TYPE"(define @ vfs_struch.h)
/*
typedef enum
{
    IMG_FILE_DEVICE_TYPE_NOR        = 0,  ///< no matching file system
    IMG_FILE_DEVICE_TYPE_SD         = 1,  ///< Use SD file system
    IMG_FILE_DEVICE_TYPE_SD2        = 2,  ///< Use SD file system
    IMG_FILE_DEVICE_TYPE_NAND		= 3,  ///< Use NAND flash file system
    IMG_FILE_DEVICE_TYPE_MAX,
}JPEGFILEDEVICE_e;
*/
typedef struct _MDLJPE_INPUTSTRUC {
    MIDJPE_INPUTMODE    inputMode;
    MDLJPE_OUTMODE      outputMode;
    MDLJPE_QTBL         u8Qualitylevel;// Q value : 1 to 32
    u8                  *pu8InputBuf;
    u8                  *pu8OutputBuf; //output buffer pointer
    u32                 nBufferSize;   //output buffer size
    u8                  *pu8OutputPath;//output file path
    u16                 u16InputW;
    u16                 u16InputH;
    u16                 u16Input_Pitch;
    u16                 u16OutputW;
    u16                 u16OutputH;
    u16                 u16LCDWidth;
    u16                 u16LCDHeight;
    u8                  u8LCDRotate;
    u16                 u16Num_pictures;// capture numbers :1 to 9
    MDLJPE_ORIENTATION  rotateType;
    MDLJPE_ORIENTATION  exifOrientation;
    u16                 bShutterSoundEnable;
    u8                  *pu8ShutterSndBuffer;
    u32                 nShutterSndSize;
    u16                 *pFileNamePath;
    JPEFilenameFormat_e FileNameformat;
    MDLCaptureMode_e    eCaptureMode;
    MDLCapRotAngle_e    eRotateAngle;
    u8                  *pStickerFramebuffer;
    u16                 bImageCapture13MegaOnly;
    u8                  u8EncodeFrameMode;
    u8                  u8landscape;
    u8                  u8sclblockEn;
    u8                  u8sclRingModeEn;
    u8                  u8sclRingNum;
    MDLJPE_EnFormat_e   eJPGFormat;
    MmlImageCaptureLomo4LensParam_t tLomo4LenParam; 
    MmlImageCaptureMirrorParam_t tMirrorParam;         
    MmlImageCapturePanoramaParam_t tPanoramaParam;     
} MDLJPE_INPUTSTRUC;

typedef struct _MDLJPE_SHAREBUF {
    u8  *pSram_oriBuf;
    u8  *pSram_oriBuf1;    
    u8  *pSram_lbcBuf;
    u8  *pSram_lbcBuf1;    
    u8  *pSram_i2sBuf;

    u8  *pDram_oriBuf;
    u8  *pDram_headerBuf;
    u8  *pDram_thumbBuf;
    u8  *pDram_totalBsBuf;
    u8  *pDram_multiBsBuf[BANKCOUNT];
    u8  *pDram_oriMultiBsBuf[BANKCOUNT];   
    u8  *pDram_globalBuf;
    u8  *pDram_RawBSBuf;

    u8  *pDram_oriShutBuf;
    u8  *pDram_pcmBuf;
    u8  *pDram_RawAudioBuf;
    u8  *pDram_RawFrameBuf;

    u32   u32bankSize;
    u32  u32Y0LogAddr;
    u32  u32Y1LogAddr;
    u32  u32C0LogAddr;
    u32  u32C1LogAddr;
    u32  u32SCLbufferSize;
    u32  u32OutBSSize;
} MDLJPE_SHAREBUF;

typedef struct  _MDLJPE_DISPLAYINFO
{
    u16     u16Disp_Pitch;
    u16     u16Disp_X_Offset;
    u16     u16Disp_Y_Offset;
    u16     u16Disp_Width;
    u16     u16Disp_Height;
    u16     u16LCDWidth;
    u16     u16LCDHeight;
    u32     u32Disp_Addr[2];
    MmlCameraRotationAngle_e    eSLCRotationAngle;
} MDLJPE_DISPLAYINFO_t;

#define MDLJPE_MAXFILELEN       (1 * 1024)
#define MDLJPE_RESERVELEN       1//(1 * 1024)
#define MDLJPE_THUMBNAIL_W      128
#define MDLJPE_THUMBNAIL_H      96


#define MDLJPE_TESTBUF_W      128
#define MDLJPE_TESTBUF_H      96

typedef struct _MDLJPE_PARAM {
//**********************************************
//ap layer related parameter
//**********************************************
    u32     u32MagicNum;
    MIDJPE_INPUTMODE    inputMode;
    MDLJPE_OUTMODE      outputMode;
    MDLJPE_SenDataFormat_e senDataFormat;       
    u8      *pu8InputBuf;
    u8      *pu8OutputBuf;
    u8       pu8bankSize;
  //u8      u8OutputPath[MDLJPE_MAXFILELEN];    // output path
    u16     u16orgimg_width;                    // ALIGN_TO_16(u16orgimg_width)
    u16     u16orgimg_height;                   // ALIGN_TO_16(u16orgimg_height)
    u16     u16OutputW;                         // ALIGN_TO_16(u16orgimg_width)
    u16     u16OutputH;                         // ALIGN_TO_16(u16orgimg_height)
    u8      u8Num_pictures;                     // capture numbers :1 to 9
    u8      u8Qualitylevel;                     // Q value : 1 to 32
    u16     *YQTable;                           //pointer to Y Qtable of 64 entries
    u16     *CQTable;                           //pointer to C Qtable of 64 entries
    MDLJPE_QLEVEL QLevel;
    MDLJPE_ORIENTATION  rotateType;
    MDLCapRotAngle_e    eRotateAngle;
    MDLJPE_EnFormat_e   eJPGFormat;
//**********************************************
//middleware layer related parameter
//**********************************************
    MDLJPE_SHAREBUF     bufInfo;
    u32                 obufMode;
    s32                 s32FileHandle;
    ascii               *c8o_filename;
    u16                 *dest_filename;
    MIDJPE_HWCONFIG     hwConfig;
    u32                 u32HeaderLen;
    u32                 u32BSLen;
    u8                  *u8BSOutBufPtr;
    u32                 u32BSChecksum;
    u8                  SensorNoteBuf[MDLJPE_RESERVELEN]; //marine test Exif
    u8                  *pu8DispBuf[2];
    u8                  *pu8JPEDesBuf;
    u32                 u32JPEDesBufLen;
    u16                 u16InputW;
    u16                 u16InputH;
    u16                 u16Input_Pitch;
    u16                 sclSrcFormat;//SCLSRC_FORMAT_e     sclSrcFormat;
    u16                 sclDesFormat;//SCLDST_FORMAT_e     sclDesFormat;
    u8                  u8enThumbnail;
    u32                 u32StorageFree_space;
    u8                  u8EncodeFromBuf;
    u8                  u8EncodeFrameMode;
    u8                  u8SpecialEffectMode;
    u8                  u8ATVCapture;
    u8                  u8sclblockEn;
    u8                  u8sclRingModeEn;
    u8                  u8sclRingNum;
    u8                  u8DiffYCBufMemEn;
    u8                  u8NumOfPic;
    MmlImageCaptureLomo4LensParam_t     tLomo4LenParam; 
    MmlImageCaptureMirrorParam_t        tMirrorParam;         
    MmlImageCapturePanoramaParam_t      tPanoramaParam;     
    u8                  *pu8PanoramaBuf;
} MDLJPE_PARAM;

#if 1//defined(VFS_FILE_EN)
	//typedef long int		FILE_POS;
	typedef VFS_FILE*		IMGFILE_HANDLE;
	#define cap_fopen(name, mode) 					    file_fopen(name, mode)
	#define cap_fclose(stream) 						    file_fclose(stream)
	#define cap_fdelete(name) 						    file_unlink(name)
	#define cap_fwrite(stream, pBytes, count, size) 	file_fwrite(stream, (u8 *)pBytes, count)
	#define cap_fread(stream, pBytes, count, size) 	    file_fread(stream, pBytes, count)
	#define cap_fseek(stream, offset, origin)		    file_fseek(stream, offset, origin)
	#define cap_ftell(stream) 						    file_ftell(stream)
	#define cap_frename(old_name, new_name)			    fat_N_rename(old_name, new_name)
	#define cap_fgetattr(name, attr)					fat_N_get_file_attr(name, attr)
	#define cap_fsetattr(name, attr)					fat_N_set_file_attr(name, attr)
	#define cap_mkdir(dirname)						    fat_N_make_dir(dirname)
	#define NULL_IMGFILE_HANDLE						    NULL
	#define F_SUCC     								    (FAT_NO_ERROR)
	#define F_FAIL  								    (-1)
    #define cap_SDFULL                                  28    /* No space left on device */
    #define cap_FSGetCapacity(Id, totalSize, freeSize)  fat_N_get_volume_space_info(Id, totalSize, freeSize)
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////
// Extern Functions
///////////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------------*/
/* VARIABLE DEFINITION                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTION PROTOTYPE DECLARATION AND DEFINITION                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

MSMIMGCAPErrcode_e MdlJPE_Main(MDLJPE_INPUTSTRUC *pInput);
MSMIMGCAPErrcode_e MdlJPE_OutResult(MDLJPE_PARAM *pParam);

MSMIMGCAPErrcode_e MdlJPE_Init(MDLJPE_INPUTSTRUC *pInput, MDLJPE_PARAM **ppParam);
MSMIMGCAPErrcode_e MdlJPE_Run(MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_DeInit(MDLJPE_PARAM *pParam);


MSMIMGCAPErrcode_e MdlJPE_InitBuf(MDLJPE_INPUTSTRUC *pInput, MDLJPE_PARAM **ppParam);
MSMIMGCAPErrcode_e MdlJPE_DeInitBuf(MDLJPE_PARAM *pParam);


MSMIMGCAPErrcode_e MdlJPE_InitClk(MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_DeInitClk(void);


MSMIMGCAPErrcode_e MdlJPE_InitGlobal(MDLJPE_INPUTSTRUC *pInput, MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_DeInitGlobal(MDLJPE_PARAM *pParam);


MSMIMGCAPErrcode_e MdlJPE_SetJPE(MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_SetSCL(MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_FireSCL(MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_MultiBuf(MDLJPE_PARAM *pParam);

MSMIMGCAPErrcode_e MdlJPE_SensorInit(MDLJPE_PARAM *pParam , u8 bWithFullSet);
void MdlJPE_ResetPreview(MDLJPE_INPUTSTRUC *pInput);
void MdlJPE_GetPreDisplayPara(MDLJPE_DISPLAYINFO_t *pPreDispInfo);
MSMIMGCAPErrcode_e MdlJPE_ShutterSnd(u8 u8ATVShutEn, u8 *pAudioDMAbuf, u8 *pnSrcAddr, u32 nSrcDataSize);
MSMIMGCAPErrcode_e MdlJPE_SDSizeCheck(MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_Write2DST(MDLJPE_PARAM *pParam);

MSMIMGCAPErrcode_e MdlJPE_InitSclBuffer(MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_SE_Mirror(MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_SE_Lomo4Len(MDLJPE_PARAM *pParam);
MSMIMGCAPErrcode_e MdlJPE_SE_Panorama(MDLJPE_PARAM *pParam);
#endif




