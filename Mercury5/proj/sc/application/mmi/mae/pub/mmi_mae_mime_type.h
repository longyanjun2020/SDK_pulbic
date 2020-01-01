/**
 * @file mmi_mae_mime_type.h
 *
 * TODO: Add desctiptions here
 *
 * @version $Id: mmi_mae_mime_type.h 1815 2009-09-22 13:11:14Z sam.chen $
 */
#ifndef __MMI_MAE_MIME_TYPE_H__
#define __MMI_MAE_MIME_TYPE_H__
typedef enum
{
    MIME_START = 0,
    MIME_UNKNOWN = 0,
    MIME_BMP,
    MIME_GIF,
    MIME_PNG,
    MIME_JPG,
    MIME_MP1,
    MIME_MP2,
    MIME_MP3,
    MIME_AAC,
    MIME_AMR,
    MIME_WAV,
    MIME_MID,
    MIME_IMY,
    MIME_WMA,
    MIME_WMV,
    MIME_MP4,
    MIME_3GP,
    MIME_MIDI_EVENT,
	MIME_AWB,
    MIME_RAM,
	MIME_PCM,
	MIME_RM,
	MIME_RMVB,
	MIME_AVI,
	MIME_MFS,
	MIME_TS,
	/* Image Raw Data format */
	MIME_ARGB8888,
	MIME_ARGB4444,
	MIME_RGB565_A8,
	MIME_TOTAL,
} MaeMimeType_e;
typedef u16 MaeMimeType_t;

#define MAE_MIME_TYPE_NONE	0
#define MAE_MIME_TYPE_UNSUPPORTED 1
#define MAE_MEDIA_TYPE_NONE	0
#define MAE_FILETYPE_NONE	0

typedef u16 MAE_MIME_et;

/****************************************************************************
* !!! NOTICE:
* The following definitions are moved from mmi_common_mimetype.h, for MAE to remove
* the include header file of mmi_common level.
*
*/
#define __MMI_FEATURE_UNSUPPORTED_FILE_BROWSING__
typedef u8 MMI_Common_SupportedMediaType_e;
typedef u8 MMI_Common_SupportedFileType_e;

/* define the type of media contents */
enum
{
    MMI_COMMON_MEDIA_TYPE_NONE = MAE_MIME_TYPE_NONE,
    MMI_COMMON_MEDIA_TYPE_UNSUPPORTED,
    MMI_COMMON_MEDIA_TYPE_IMAGE,
    MMI_COMMON_MEDIA_TYPE_SOUND,
    MMI_COMMON_MEDIA_TYPE_VIDEO,
    MMI_COMMON_MEDIA_TYPE_HTML,
    MMI_COMMON_MEDIA_TYPE_URL,
    MMI_COMMON_MEDIA_TYPE_EMU,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
    MMI_COMMON_MEDIA_TYPE_PHONEBOOK,
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
    MMI_COMMON_MEDIA_TYPE_THEME,
#if defined(__DALVIK__)
	MMI_COMMON_MEDIA_TYPE_APK,
#endif //#if defined(__DALVIK__)
    MMI_COMMON_MEDIA_TYPE_APPLICATION,	/**< Java application */
    MMI_COMMON_MEDIA_TYPE_TXT,
    MMI_COMMON_MEDIA_TYPE_CALENDAR
};


enum
{
    MMI_COMMON_FILETYPE_NONE = MAE_FILETYPE_NONE,
    MMI_COMMON_FILETYPE_UNSUPPORTED,
    MMI_COMMON_FILETYPE_BMP,
    MMI_COMMON_FILETYPE_GIF,
    MMI_COMMON_FILETYPE_PNG,
    MMI_COMMON_FILETYPE_JPG,
    MMI_COMMON_FILETYPE_MP4,
    MMI_COMMON_FILETYPE_VID3GPP,
    MMI_COMMON_FILETYPE_MP1,
    MMI_COMMON_FILETYPE_MP2,
    MMI_COMMON_FILETYPE_MP3,
    MMI_COMMON_FILETYPE_AAC,
    MMI_COMMON_FILETYPE_AMR,
    MMI_COMMON_FILETYPE_AUD3GPP,
    MMI_COMMON_FILETYPE_WAV,
#ifdef __FEATURE_MMF_SUPPORTED__
    MMI_COMMON_FILETYPE_MMF,
#endif /* __FEATURE_MMF_SUPPORTED__ */
    MMI_COMMON_FILETYPE_MID,
#ifdef __FEATURE_IMY_SUPPORTED__
MMI_COMMON_FILETYPE_IMY,
#endif /* __FEATURE_IMY_SUPPORTED__ */
    MMI_COMMON_FILETYPE_EMU,
    MMI_COMMON_FILETYPE_SMC,
    MMI_COMMON_FILETYPE_THEME,
    MMI_COMMON_FILETYPE_RM,
    MMI_COMMON_FILETYPE_RMVB,
#if defined(__DALVIK__)
    MMI_COMMON_FILETYPE_APK,
#endif //#if defined(__DALVIK__)
    MMI_COMMON_FILETYPE_JAR,
    MMI_COMMON_FILETYPE_JAD,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
    MMI_COMMON_FILETYPE_PHB,
    MMI_COMMON_FILETYPE_VCF,
#ifdef __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__
    MMI_COMMON_FILETYPE_CSV,
#endif
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
    MMI_COMMON_FILETYPE_WBMP,
    MMI_COMMON_FILETYPE_TXT,
    MMI_COMMON_FILETYPE_VCS,
#if defined(__MMI_KING_MOVIE__)
    MMI_COMMON_FILETYPE_KMV,
    MMI_COMMON_FILETYPE_QKMV,
#if defined(__KING_MOVIE_SUPPORT_HVGA_MMI__)
    MMI_COMMON_FILETYPE_HKMV,
#endif
#if defined(__MMI_KING_MOVIE_3D__)
   MMI_COMMON_FILETYPE_3DKMV,
#endif
#endif
    MMI_COMMON_FILETYPE_MKV,

    /* Following types are depended on MMP. */
    MMI_COMMON_FILETYPE_RAM,
    MMI_COMMON_FILETYPE_AWB,
    MMI_COMMON_FILETYPE_ASF,
    MMI_COMMON_FILETYPE_WMA,
    MMI_COMMON_FILETYPE_RA,
    MMI_COMMON_FILETYPE_APE,
    MMI_COMMON_FILETYPE_M4A,
    MMI_COMMON_FILETYPE_AVI,
    MMI_COMMON_FILETYPE_FLV,
    MMI_COMMON_FILETYPE_MFS,
    MMI_COMMON_FILETYPE_MPG,
    MMI_COMMON_FILETYPE_MPEG,
    MMI_COMMON_FILETYPE_VOB,
    MMI_COMMON_FILETYPE_PS,
    MMI_COMMON_FILETYPE_TS,
    MMI_COMMON_FILETYPE_DAT,
    MMI_COMMON_FILETYPE_DIVX,
    MMI_COMMON_FILETYPE_MOV,

    MMI_COMMON_FILETYPE_NUM
};

//------------------------------------------------------------------------------------------------------
/*  - MMI_Common_SupportedMediaType_e
    desc:
        get the media type from its filename..
    argu:
        pFilenameStr: filename (or path) of this file
    return:
        MMI_COMMON_FILETYPE_NONE - invalid filename or insufficient memory
        MMI_COMMON_FILETYPE_UNSUPPORTED - the file is not supported..
        others - media type of this file
*/
__SLDPM_FREE__ MMI_Common_SupportedMediaType_e MMI_Common_MIMEType_DetectMediaTypeByFN(const MAE_WChar *pFilenameStr);


/****************************************************************************
* !!! end of NOTICE
*/



#endif /* __MAE_MIME_TYPE_H__ */
