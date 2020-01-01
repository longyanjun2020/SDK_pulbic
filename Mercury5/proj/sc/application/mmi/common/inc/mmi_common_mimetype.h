/**
 *  @file   mmi_common_mimetype.h
 *  @brief  this file denotes the supported MIME types in AP level
 *  @version $Id: mmi_common_mimetype.h 38084 2009-08-19 09:57:22Z joe.hsu $
 */
#ifndef __MMI_COMMON_MIMETYPE_H__
#define __MMI_COMMON_MIMETYPE_H__
/*==============================================================================
                       INCLUDE FILES FOR MODULE
==============================================================================*/
#include "mmi_mae_common_def.h"
/* define the extension name */
/* Picture */
extern const MAE_WChar g_wszMMI_COMMON_EXT_BMP[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_GIF[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_PNG[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_JPG[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_JPEG[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_WBMP[];

/* Audio */
extern const MAE_WChar g_wszMMI_COMMON_EXT_MP1[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_MP2[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_MP3[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_AAC[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_AMR[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_AWB[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_WAV[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_WAVE[];
#ifdef __FEATURE_MMF_SUPPORTED__
extern const MAE_WChar g_wszMMI_HCOMMON_EXT_MMF[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_XMF[];
#endif /* __FEATURE_MMF_SUPPORTED__ */
#ifdef __FEATURE_IMY_SUPPORTED__
extern const MAE_WChar g_wszMMI_COMMON_EXT_IMY[];
#endif /* __FEATURE_IMY_SUPPORTED__ */
extern const MAE_WChar g_wszMMI_COMMON_EXT_MID[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_MIDI[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_RAM[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_RA[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_ASF[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_WMA[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_APE[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_M4A[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_WMV[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_PCM[];
/* Video */
extern const MAE_WChar g_wszMMI_COMMON_EXT_3GP[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_3GPP[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_MP4[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_RM[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_RMVB[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_AVI[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_FLV[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_MFS[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_MPG[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_MPEG[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_VOB[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_PS[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_TS[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_DAT[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_DIVX[];
#if defined(__MMI_KING_MOVIE__)
extern const MAE_WChar g_wszMMI_COMMON_EXT_KMV[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_QKMV[];
#if defined(__KING_MOVIE_SUPPORT_HVGA_MMI__)
extern const MAE_WChar g_wszMMI_COMMON_EXT_HKMV[];
#endif
#if defined(__MMI_KING_MOVIE_3D__)
extern const MAE_WChar g_wszMMI_COMMON_EXT_3DKMV[];
#endif
#endif
extern const MAE_WChar g_wszMMI_COMMON_EXT_MKV[];
/* Other */
extern const MAE_WChar g_wszMMI_COMMON_EXT_EMU[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_SMC[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_THEME[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_JAR[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_JAD[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_VCF[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_PHB[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_TXT[];
extern const MAE_WChar g_wszMMI_COMMON_EXT_VCS[];

/*===========================================================================
                       TYPE DECLARATIONS
============================================================================*/

//Paul: the followings are moved to mae_mime_type.h temporarily. so we need to include mae_mime_type.h here
#include "mmi_mae_mime_type.h"
#include "mmi_mae_common_content_forward.h"

typedef struct MMI_COMMON_MIME_ICON_MAPPING_T
{
	MMI_Common_SupportedFileType_e	eFileType;
	u32								nSmallImgId;
	u32								nLargeImgId;
}MMI_COMMON_MIME_ICON_MAPPING_st;


// index of _g_tMMI_COMMON_MIME[]
enum
{
	/**
	* NOTE: the order of the MIME type effect the order when sorting by TYPE in FileManager.
	* The following order is depends on the extension name for that MIME type file.
	*/
	MMI_COMMON_MIME_NONE = MAE_MIME_TYPE_NONE,
	MMI_COMMON_MIME_UNSUPPORTED = MAE_MIME_TYPE_UNSUPPORTED,
	/* 3GP */ MMI_COMMON_MIME_AUD3GPP,
	/* 3GP */ MMI_COMMON_MIME_VID3GP,
	/* 3GP */ MMI_COMMON_MIME_VID3GPP,
	/* AAC */ MMI_COMMON_MIME_AUDAAC,
	/* AAC */ MMI_COMMON_MIME_AUDXAAC,
	/* AAC */ MMI_COMMON_MIME_SUNAAC,
	/* AMR */ MMI_COMMON_MIME_AUDAMR,
	/* AMR */ MMI_COMMON_MIME_SNDAMR,
	/* BMP */ MMI_COMMON_MIME_IMGBMP,
	/* BMP */ MMI_COMMON_MIME_IMGVNDWBMP,
	/* BMP */ MMI_COMMON_MIME_IMGWBMP,
	/* GIF */ MMI_COMMON_MIME_IMGGIF,
#ifdef __FEATURE_IMY_SUPPORTED__
	/* IMY */ MMI_COMMON_MIME_AUDIMLDY,
	/* IMY */ MMI_COMMON_MIME_AUDIMY,
	/* IMY */ MMI_COMMON_MIME_SNDIMY,
#endif /* __FEATURE_IMY_SUPPORTED__ */
#if defined(__DALVIK__)
	/* APK */ MMI_COMMON_MIME_APK,
#endif
#if defined(__JAVA_MMI__)
	/* JAD */ MMI_COMMON_MIME_JAD,
	/* JAR */ MMI_COMMON_MIME_JAR,
#endif
	/* JPG */ MMI_COMMON_MIME_IMGJPEG,
	/* JPG */ MMI_COMMON_MIME_IMGJPG,
	/* MID */ MMI_COMMON_MIME_AUDMID,
	/* MID */ MMI_COMMON_MIME_AUDMIDI,
	/* MID */ MMI_COMMON_MIME_AUDSPMIDI,
	/* MID */ MMI_COMMON_MIME_AUDXMIDI,
#ifdef __FEATURE_MMF_SUPPORTED__
	/* MMF */ MMI_COMMON_MIME_APPSMAF,
	/* MMF */ MMI_COMMON_MIME_APPVNDSMAF,
	/* MMF */ MMI_COMMON_MIME_APPXSMAF,
	/* MMF */ MMI_COMMON_MIME_AUDMBXMF,
	/* MMF */ MMI_COMMON_MIME_AUDMMF,
	/* MMF */ MMI_COMMON_MIME_AUDMXMF,
	/* MMF */ MMI_COMMON_MIME_AUDSMAF,
	/* MMF */ MMI_COMMON_MIME_AUDVNDSMAF,
	/* MMF */ MMI_COMMON_MIME_AUDXMF,
	/* MMF */ MMI_COMMON_MIME_AUDXMF0,
	/* MMF */ MMI_COMMON_MIME_AUDXMF1,
	/* MMF */ MMI_COMMON_MIME_AUDXSMAF,
	/* MMF */ MMI_COMMON_MIME_SNDMMF,
#endif /* __FEATURE_MMF_SUPPORTED__ */
    /* MP1 */ MMI_COMMON_MIME_AUDMP1,
    /* MP2 */ MMI_COMMON_MIME_AUDMP2,
	/* MP3 */ MMI_COMMON_MIME_AUDMP3,
	/* MP3 */ MMI_COMMON_MIME_SNDMP3,
	/* MP4 */ MMI_COMMON_MIME_VIDMP4,
	/* MPG */ MMI_COMMON_MIME_AUDMPG,
#if defined(__GAME_ENGINE_EMU_MMI__)
	/* EMU */ MMI_COMMON_MIME_EMU,
#if defined(__GAME_ENGINE_EMU_16BIT__)
	/* SMC */ MMI_COMMON_MIME_SMC,
#endif // __GAME_ENGINE_EMU_16BIT__
#endif // __GAME_ENGINE_EMU_MMI__
	/* PNG */ MMI_COMMON_MIME_IMGPNG,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
	/* PHB */ MMI_COMMON_MIME_PHB,
#ifdef __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__
	/* CSV */ MMI_COMMON_MIME_CSV,
#endif
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
	/* RM  */ MMI_COMMON_MIME_RM,
	/* RMV */ MMI_COMMON_MIME_RMVB,
	/* THM */ MMI_COMMON_MIME_THEME,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
	/* VCF */ MMI_COMMON_MIME_VCARD,
#endif
	/* WAV */ MMI_COMMON_MIME_AUDWAV,
	/* WAV */ MMI_COMMON_MIME_AUDWAVE,
	/* WAV */ MMI_COMMON_MIME_AUDXWAV,
	/* WAV */ MMI_COMMON_MIME_SUDWAV,
#if defined(__E_BOOK_MMI__)
	/* TXT */ MMI_COMMON_MIME_TXT,
#endif
#if defined(__CALENDAR_SUPPORT_VCS_MMI__)
	/* VCS */ MMI_COMMON_MIME_VCALENDAR,
#endif // End of __CALENDAR_SUPPORT_VCS_MMI__
#if defined(__MMI_KING_MOVIE__)
    /* KMV */ MMI_COMMON_MIME_KMV,
    /* KMV */ MMI_COMMON_MIME_QKMV,
#if defined(__KING_MOVIE_SUPPORT_HVGA_MMI__)
    /* KMV */ MMI_COMMON_MIME_HKMV,
#endif
#if defined(__MMI_KING_MOVIE_3D__)
   /*3DKMV*/MMI_COMMON_MIME_3DKMV,
#endif
#endif
	/* MKV */ MMI_COMMON_MIME_MKV,

	/* Following types are depended on MMP. */
	/* RAM */ MMI_COMMON_MIME_RAM,
	/* AWB */ MMI_COMMON_MIME_AWB,
	/* ASF */ MMI_COMMON_MIME_ASF,
	/* WMA */ MMI_COMMON_MIME_WMA,
	/* RA  */ MMI_COMMON_MIME_RA,
	/* APE */ MMI_COMMON_MIME_APE,
	/* M4A */ MMI_COMMON_MIME_M4A,
	/* AVI */ MMI_COMMON_MIME_AVI,
	/* FLV */ MMI_COMMON_MIME_FLV,
	/* MFS */ MMI_COMMON_MIME_MFS,
	/* MPG */ MMI_COMMON_MIME_MPG,
	/* MPEG*/ MMI_COMMON_MIME_MPEG,
	/* VOB */ MMI_COMMON_MIME_VOB,
	/* PS  */ MMI_COMMON_MIME_PS,
	/* TS  */ MMI_COMMON_MIME_TS,
	/* DAT */ MMI_COMMON_MIME_DAT,
	/* DIVX */ MMI_COMMON_MIME_DIVX,
	/* MOV */ MMI_COMMON_MIME_MOV,

	MMI_COMMON_MIME_MAX
};

/*==============================================================================
                       FUNCTION DECLARATIONS
==============================================================================*/
void MMI_Common_MIMEType_InitTable(void);
MAE_Ret MMI_Common_GetExtByMIMEType(const char *pszMIME, MAE_WChar**pExtName);
MAE_MIME_et MMI_Common_MIMEType_GetMEMIByExt(const MAE_WChar* pwszExt);
MAE_MIME_et MMI_Common_MIMEType_GetMIMEByString(const char *pszMIME);
const char * MMI_Common_MIMEType_GetMIMEString(u32 nIdx);

/*  - MMI_Common_SupportedMediaType_e
    desc:
        get the media type from its mime type..
    argu:
        pMIMETypeStr: mime type of a media content
    return:
        MMI_COMMON_FILETYPE_NONE - invalid mime type or insufficient memory
        MMI_COMMON_FILETYPE_UNSUPPORTED - the mime type is not supported..
        others - media type of this content
*/
MMI_Common_SupportedMediaType_e MMI_Common_MIMEType_DetectMediaTypeByMIME(const char *pMIMETypeStr);

MMI_Common_SupportedMediaType_e MMI_Common_MIMEType_DetectMediaTypeByExt(const MAE_WChar *pExt);

//------------------------------------------------------------------------------------------------------
/*  - MMI_Common_SupportedMediaType_e
    desc:
        get the file type from its mime type..
    argu:
        pMIMETypeStr: mime type of a media content
    return:
        MMI_COMMON_FILETYPE_NONE - invalid mime type or insufficient memory
        MMI_COMMON_FILETYPE_UNSUPPORTED - the mime type is not recognized..
        others - file type of this content
*/
MMI_Common_SupportedFileType_e  MMI_Common_MIMEType_DetectFileTypeByMIME(const char *pMIMETypeStr);
//-------------------------------------------------------------------------------------------------------
/*  - MMI_Common_SupportedMediaType_e
desc:
get the file type from it's mime type..
argu:
pMIMETypeStr: mime type of a media content
return:
MMI_COMMON_FILETYPE_NONE - invalid mime type or insufficient memory
MMI_COMMON_FILETYPE_UNSUPPORTED - the mime type is not recognized..
others - file type of this content
*/
MMI_Common_SupportedFileType_e  MMI_Common_MIMEType_DetectFileTypeByExt(const MAE_WChar *pwszExt);
//-------------------------------------------------------------------------------------------------------
/*  - MMI_Common_SupportedMediaType_e
desc:
get the file type from it's mime type..
argu:
pMIMETypeStr: mime type of a media content
return:
MMI_COMMON_FILETYPE_NONE - invalid mime type or insufficient memory
MMI_COMMON_FILETYPE_UNSUPPORTED - the mime type is not recognized..
others - file type of this content
*/
MMI_Common_SupportedFileType_e  MMI_Common_MIMEType_DetectFileTypeByFN(const MAE_WChar *pFilename);
//------------------------------------------------------------------------------------------------------
/*  - MMI_Common_SupportedMediaType_e
    desc:
        get the mime type string from its filename..
    argu:
        pFilenameStr: filename (or path) of this file
    return:
        NULL - 1.invalid filename 2.insufficient memory 3.not recognized
        others - mime type string of this content
*/
char* MMI_Common_MIMEType_GetMIMETypeStrByFN(const MAE_WChar* pFilename);

//-------------------------------------------------------------------------------------------------------
/*  - MMI_Common_MIMEType_GetDispIconByFileType
desc:
get the thumbnail icon for displaying
argu:
bLargeOne: large icon or not
return:
image id
*/
u32  MMI_Common_MIMEType_GetDispIconByFileType(boolean bLargeOne, MMI_Common_SupportedFileType_e nFileType);

//-------------------------------------------------------------------------------------------------------
/*  - MMI_Common_MIMEType_GetDispIconByExt
desc:
get the thumbnail icon for displaying
argu:
bLargeOne: large icon or not
return:
image id
*/
__SLDPM_FREE__ u32  MMI_Common_MIMEType_GetDispIconByExt(boolean bLargeOne, const MAE_WChar *pFilenameExt);
//------------------------------------------------------------------------------------------------------

MAE_MIME_et MMI_Common_MIMEType_GetFilterExtList(MAEMIMEFilterID_e eFilterID, u32 *pnNum, MAE_WChar *pExtList);

#endif  /* __MMI_COMMON_MIMETYPE_H__ */
