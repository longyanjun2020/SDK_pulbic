/**
 *  @file   mmi_common_content.h
 *  @brief  it is used for communination within different Applications/Services in accessing content files.
 *  @version $Id: mmi_common_content.h 40955 2009-09-21 12:57:55Z young.huang $
 */
#ifndef __MMI_COMMON_CONTENT_H__
#define __MMI_COMMON_CONTENT_H__

/*****************************************************************************
*!!! NOTICE !!!
* The followings are moved to mae_common_content.h, for the purpose that
* MAE can not include any header file in app/srv/mmi_common level.
* This is just a temporary solution! It should be modified in the future!
******************************************************************************/
/**************
* End of NOTICE
**************/


/*==============================================================================
                       INCLUDE FILES FOR MODULE
==============================================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_cfgsrv.h"
#include "mmi_mae_filemgr.h"
#include "mmi_mae_image.h"
#include "mmi_mae_mime_type.h"
/*===========================================================================
                       TYPE DECLARATIONS
============================================================================*/
/*****************************************************************************
*!!! NOTICE !!!
* The followings are moved to mae_common_content.h, for the purpose that
* MAE can not include any header file in app/srv/mmi_common level.
* This is just a temporary solution! It should be modified in the future!
******************************************************************************/

extern const MAE_WChar MMI_COMMON_DEFAULT_THEME_URL[];		/**< L"DEFAULT_THEME_WP" */
/**************
* End of NOTICE
**************/

/*-------------------------------------------------------------------------*/


//-----------------------------------------------------------------------------
//#define MMI_COMMON_DATESTR_FORMAT       L"%04d-%02d-%02d"
//#define MMI_COMMON_DATESTR_LEN          10

#define MMI_COMMON_FILESIZE_STR_PRECISION   2
#define MMI_COMMON_FILESIZE_STR_MAXCHARS    100
#define MMI_COMMON_FILESIZE_STR_DELIMETER   L" "
#define MMI_COMMON_FILESIZE_ONE_KILOBYTE       1024
#define MMI_COMMON_FILESIZE_ONE_MEGABYTE       (1024 * MMI_COMMON_FILESIZE_ONE_KILOBYTE)

#define MMI_COMMON_FREESPACE_ONE_MEGABYTE   1024

#define MMI_COMMON_FNCOL_SN_MAX      (999) // append a serial # as suffix while filename collision occurring
#define MMI_COMMON_FNCOL_SN_FORMAT   L"(%d)"
#define MMI_COMMON_FNCOL_SN_LEN      2   // for '(' and ')'


/*==============================================================================
                       STRUCTURE DECLARATIONS
==============================================================================*/
enum _MMI_Common_FMList_ItemType{
    MMI_FMLSTAPP_ITEMTYPE_NONE,
    MMI_FMLSTAPP_ITEMTYPE_EMPTY,
    MMI_FMLSTAPP_ITEMTYPE_ROOTLEVEL,
    MMI_FMLSTAPP_ITEMTYPE_SYSTEMFOLDER,    // fixed folder
    MMI_FMLSTAPP_ITEMTYPE_SYSTEMFOLDERMIX, // fixed folder, and mixed with Phone mem and ExtCard mem
    MMI_FMLSTAPP_ITEMTYPE_USERFOLDER,      // user-defined folder
#if defined(__ONBOARD_USER_STORAGE_MMI__) || defined(__CAMERA_MMI_USE_PHONE_STORAGE__)
	MMI_FMLSTAPP_ITEMTYPE_VOLDISKROOT,     // One specific item contains PHONE/CARD volumes
	MMI_FMLSTAPP_ITEMTYPE_VIRTUALFOLDER,   // TODO: to be removed
	MMI_FMLSTAPP_ITEMTYPE_PHONE_VIRTUALFOLDER,   // Phone folders
	MMI_FMLSTAPP_ITEMTYPE_CARD_VIRTUALFOLDER,   // Card folders
#endif
    MMI_FMLSTAPP_ITEMTYPE_CONTENT,         // media content
    MMI_FMLSTAPP_ITEMTYPE_VIRTUALCONTENT,  // for "default" and "standard" items that are used in FilePicker
    MMI_FMLSTAPP_ITEMTYPE_LOCALLNK,        // link to local HTTP file
    MMI_FMLSTAPP_ITEMTYPE_REMOTELNK,       // link to HTTP site
    MMI_FMLSTAPP_ITEMTYPE_FUNCTIONS        // one specific function for this item, such as "new folder" in Folder Browsing, "paste" in CopyMove case and "None" in FilePicker
};
typedef u8  MMI_Common_FMList_ItemType_e;

typedef struct _MMI_Common_FMList_ItemElement{    // define the basic elements of every item
    u32                     nID; // the ContentID in content_db or CategoryID in category_db
    MMI_Common_FMList_ItemType_e  nType;   // the type of this item.
}MMI_Common_FMList_ItemElement_t;

enum _MMI_Common_Img_Usage{
    MMI_COMMON_IMG_USAGE_NONE,
    MMI_COMMON_IMG_USAGE_WALLPAPER,
    MMI_COMMON_IMG_USAGE_CALLER_PIC,
    MMI_COMMON_IMG_USAGE_DISPLAY,
    MMI_COMMON_IMG_USAGE_ONOFF,
    MMI_COMMON_IMG_USAGE_MAX
};

enum _MMI_Common_Video_Usage{
    MMI_COMMON_VIDEO_USAGE_WALLPAPER,
    MMI_COMMON_VIDEO_USAGE_CALLER_PIC,
    MMI_COMMON_VIDEO_USAGE_ONOFF,
    MMI_COMMON_VIDEO_USAGE_MAINMENU,
};
typedef u8  MMI_Common_Video_Usage_e;

enum _MMI_Common_Video_Usage_Fail_Reason{
    MMI_COMMON_VIDEO_USAGE_REASON_NONE,
    MMI_COMMON_VIDEO_USAGE_REASON_NOTVIDEO, // MMI_Common_MIMEType_DetectMediaTypeByFN
    MMI_COMMON_VIDEO_USAGE_REASON_RESOLUTION,
    MMI_COMMON_VIDEO_USAGE_REASON_SETDATA, // SrvVideoPlayerSetDataByUrl
    MMI_COMMON_VIDEO_USAGE_REASON_GETDATA, // SrvVideoPlayerGetDataInfoSync
    MMI_COMMON_VIDEO_USAGE_REASON_CODEC,
    MMI_COMMON_VIDEO_USAGE_REASON_PASSWORD,
};
typedef u8  MMI_Common_Video_Usage_Fail_e;

typedef u8  MMI_Common_Img_Usage_e;

enum _MMI_Common_Name_Type{
    MMI_COMMON_NAMETYPE_NONE,
    MMI_COMMON_NAMETYPE_MAINFILENAME,
    MMI_COMMON_NAMETYPE_DIR,
    MMI_COMMON_NAMETYPE_KEYWORD,
    MMI_COMMON_NAMETYPE_MAX
};
typedef u8  MMI_Common_Name_Type_e;

enum _MMI_Common_Location_Type{
	MMI_COMMON_LOCTYPE_NONE,
	MMI_COMMON_LOCTYPE_PREDEFINED_MUSIC,
	MMI_COMMON_LOCTYPE_PREDEFINED_IMAGE,
	MMI_COMMON_LOCTYPE_PHONE,
	MMI_COMMON_LOCTYPE_EXTMEMCARD,
	MMI_COMMON_LOCTYPE_EXTMEMCARD2,
	MMI_COMMON_LOCTYPE_HTTP,
	MMI_COMMON_LOCTYPE_RTSP,
	MMI_COMMON_LOCTYPE_MAX
};
typedef u8  MMI_Common_Location_Type_e;

typedef struct FsErrCodeInfo_t_
{
    MAE_Ret                                 nFsErrCode;
    u32                                     nTextId;
} FsErrCodeInfo_t;

//-----------------------------------------------------------------------------

/*==============================================================================
                       MACRO DECLARATIONS
==============================================================================*/
/* used for checking every character in filename is valid or not. */
#define ISVALIDFNCHAR(ch)   ((ch != L'\\') && (ch != L'/') && \
                            (ch != L':') && (ch != L'*') && (ch != L'?') && \
                            (ch != L'"') && (ch != L'<') && (ch != L'>') && \
                            (ch != L'|'))

#ifdef GETDIGITS
#undef GETDIGITS
#endif
#define GETDIGITS(n, digit) {   u32 nNum = n; digit = 0;   \
    do{   \
    nNum /= 10; digit++;    \
    }while(0 != nNum);    \
}


/*==============================================================================
                       FUNCTION DECLARATIONS
==============================================================================*/

/* functions */
//--------------------------------------------------------------------------------------------

MAE_WChar*  MMI_Common_GetFileFolderPathDUP(const MAE_WChar *pStr);
//--------------------------------------------------------------------------------------------
MAE_Ret MMI_Common_FNCheckAndCatSNEx(MAE_WChar **ppFullpath,
									 boolean *pbFNCollision,
									 u32	*pu32FNLen,
									 boolean bIsForceReName);
MAE_Ret MMI_Common_FNCheckAndCatSN(MAE_WChar **ppFullpath, boolean *pbFNCollision);
//--------------------------------------------------------------------------------------------
__SLDPM_FREE__ MAE_WChar* MMI_Common_GetDspNameFromFilenameDUP(const MAE_WChar* pStr);
//--------------------------------------------------------------------------------------------
MAE_WChar *MMI_Common_GetLastFolderName(const MAE_WChar *pStr);
//--------------------------------------------------------------------------------------------
MAE_WChar *MMI_Common_GetLastFolderNameDUP(const MAE_WChar *pStr);
//--------------------------------------------------------------------------------------------
MAE_WChar *MMI_Common_RemoveLastFolderName(const MAE_WChar *pStr);
//--------------------------------------------------------------------------------------------
MAE_WChar *MMI_Common_RemoveTailDelimiter(MAE_WChar *pStr);
//--------------------------------------------------------------------------------------------
MAE_WChar* MMI_Common_GetDataStringFromSeconds(IBase* pOwner, const u32 nTime);

//--------------------------------------------------------------------------------------------
__SLDPM_FREE__ MAE_WChar* MMI_Common_GenerateFSSizeStr(const u32 nSize);
//--------------------------------------------------------------------------------------------
//u32 MMI_Common_GetSizeUnitTxtId(u32 nSpace);
//--------------------------------------------------------------------------------------------
MAE_WChar* MMI_Common_GenerateFreeSpaceStr(const u32 nSizeInKB);
//--------------------------------------------------------------------------------------------
MAE_WChar* MMI_Common_GetSizeStr(float nDspSize, u32 nTxtID);
//--------------------------------------------------------------------------------------------

/**
 * Get URL for the config item.
 *
 * @param pICFGSrv			[in] Instance of ICFGSrv
 * @param eCFGItemID		[in] Config item ID
 * @param ppURLOut			[out] allocated buffer which represent the URL filename address of this config item
 *							NULL for content not found OR the hash value STORED in cfg item is all zero
 * @param pOwner			[in] client instance using this utility function

 * @return MAE_RET_SUCCESS	Found URL for the hash value STORED in cfg item OR the hash value is empty(all zero)
 * @return MAE_RET_FAIL		URL not found for the hash value stored in cfg item
 */
MAE_Ret MMI_Common_GetURLByCFGItemID(CFGItemID_e eCFGItemID, MAE_WChar **ppURLOut, IBase *pOwner);

/**
 * Set URL for the config item.
 *
 * @param pICFGSrv			[in] Instance of ICFGSrv
 * @param eCFGItemID		[in] Config item ID
 * @param bGetDefaultValue	[in] use default value instead of user value
 * @param pURL				[in] pointer which represent the URL filename address of this config item
 * @param pOwner			[in] client instance using this utility function

 * @return MAE_RET_SUCCESS	Convert URL to the hash value STORED in cfg item OR the hash value is empty(all zero)
 * @return MAE_RET_FAIL
 */
MAE_Ret MMI_Common_SetCFGItemByURL(CFGItemID_e eCFGItemID, MAE_WChar *pURL, IBase *pOwner);

__SLDPM_FREE__ MAE_WChar* MMI_Common_GetDisplayNameByURLDUP(const MAE_WChar* pStr);
//#endif

#ifdef  __PLAYLIST_COVER_MMI__
/**
 * Get the cover image of its corresponding playlist
 * This function will return an IImage of the giving playlist
 *
 * @param pURL	[in] the full path of the playlist
 * @param pOwner	[in] instance of the owner
 * @param ppRetImg	[out] the Cover Image of its corresponding playlist if available
 *
 * @return MAE_RET_SUCCESS  The corresonding cover image is exist and returned
 * @return MAE_RET_BAD_PARAM    Bad param
 * @return MAE_RET_NOT_FOUND    The playlist doesn't has a cover
 * @return others   Other error code
 */
MAE_Ret MMI_Common_GetCoverImgForURL(const MAE_WChar *pURL, IImage **ppRetImg, IBase *pOwner);

/**
 * Generate a full path of the cover image for the playlist
 * This function will generate the corresponding URL for the playlist's cover image
 *
 * @param pPlstURL	[in] the full path of the playlist
 * @param ppNewURL	[out] the URL of its corresponding playlist if available, you have to free it by youself
 *
 * @return MAE_RET_SUCCESS  The corresonding cover image is exist and URL is returned
 * @return MAE_RET_BAD_PARAM    Bad param
 * @return MAE_RET_OUT_OF_MEMORY   no memory
 */
MAE_Ret MMI_Common_GeneratePlaylistCoverImgURL(const MAE_WChar *pPlstURL, MAE_WChar **ppNewURL);

/**
 * Get the full path of the playlist's cover image
 * This function will find the cover image of the playlist file, then return its full path
 *
 * @param pPlstURL	[in] the full path of the playlist
 * @param pOwner	[in] instance of the owner
 * @param ppImgURL	[out] the URL of its corresponding playlist if available, you have to free it by youself
 *
 * @return MAE_RET_SUCCESS  The corresonding cover image is exist and URL is returned
 * @return MAE_RET_BAD_PARAM    Bad param
 * @return MAE_RET_NOT_FOUND    The playlist doesn't has a cover
 * @return others   Other error code
 */
MAE_Ret MMI_Common_GetPlaylistCoverImgURL(const MAE_WChar *pPlstURL, MAE_WChar **ppImgURL, IBase *pOwner);
#endif  /* __PLAYLIST_COVER_MMI__ */

MAE_Ret MMI_Common_GetImgUsedAsLimit(ImgFormat_t eImgType, MMI_Common_Img_Usage_e nUsage,
                                     u16 *nAllowW, u16 *nAllowH, u32 *nAllowFileSize);
/**
 * decide the selected image can be used or not
 * you HAVE To release *ppImg by yourself
 *
 * @param pCntBrowser	[in] instance of IContentBrowser; if pCntBrowser is NULL, the function'll create a IContentBrowser automatically
 * @param nCntID	[in] content id of the selected image
 * @param ppImg	[in][out] instance of the selected image. if *ppImg is NULL, it'll be assigned by nCntID/pCntBrowser/pOwner
 * @param nUsage	[in] the purpose of the pImg
 * @param pOwner	[in] instance of the caller
 *
 * @return MAE_RET_SUCCESS the image can be used as what user's want
 * @return MAE_RET_CONTENT_OVERCAPACITY the image is too large to be used as what the user's want
 * @return MAE_RET_BAD_PARAM pImg is NULL and at least one of pCntBrowser/nCntID/pOwner is NULL
 * @return MAE_RET_NOT_SUPPORT the content is not supported
 * @return MAE_RET_CONTENT_NOSUCHITEM pImg is NULL and cannot find the Content by nCntID
 */
MAE_Ret MMI_Common_IsImgCanBeUsedAs(MAE_WChar *strImgURL, IImage **ppImg, MMI_Common_Img_Usage_e nUsage, IBase *pOwner);


/**
 * decide the selected video path can be used or not
 *
 * @param strImgURL [in] video path
 * @param nUsage    [in] content id of the selected image
 * @param pReason  [out] detail failure reason, It can be NULL if the user doesnt care
 *
 * @return MAE_RET_SUCCESS the video can be used as what user's want
 * @return MAE_RET_BAD_PARAM strImgURL is NULL
 * @return MAE_RET_FAILED this video cant be used, the detail failure reason in pReason if pReason is not null
 */
MAE_Ret MMI_Common_VideoCanBeSetAs(MAE_WChar *strURL, MMI_Common_Video_Usage_e nUsage, MMI_Common_Video_Usage_Fail_e *pReason);

/**
Description Give a specified content URL, check this content is cropped wallpaper by checking the content URL
*/
bool MMI_Common_IsContentCropWallpaperEx(MAE_WChar *pContentURL);

/**
 * decide the selected filename is valid or not
  *
 * @param pStr	[in] main filename, i.e., it doesn't include the extension part (of course, not full path) or entity name (when create folder)
 * @param nNameType	[in] naming type for checking
 *
 * @return TRUE if it is a valid naming rule. one day, it can refine to return more information, such as position and reason (wrong prefix, suffix...)
 */
boolean MMI_Common_IsValidFN(const MAE_WChar *pStr, MMI_Common_Name_Type_e nNameType);

/**
 * Get the extension filename from the ASCII file full path and duplicate it
 *
 * @param pFilename [in] the ASCII file full path
 * @param bToLowerCase [in] denotes the out string will in lower case or not
 * @return NULL Out of memory
 *         others the string of the extension filename (without dot)
 */
u8* MMI_Common_GetAsciiFileExtension(const u8 *pFilename, boolean bToLowerCase);
//--------------------------------------------------------------------------------------------
/**
* Get the location type of a full path of a file or a foler.
*
* @param pStr [in] full path
* @return one of definition of MMI_Common_Location_Type_e
*/
__SLDPM_FREE__ MMI_Common_Location_Type_e MMI_Common_GetPathLocType(const MAE_WChar *pStr);
//--------------------------------------------------------------------------------------------
/**
Description Get the object and Mime type from file name
*/
MAE_Ret MMI_Common_GetImgObjByFileName(const MAE_WChar *pFilename, MAEIId_t preferredInterface, IBase **ppOutObj, MMI_Common_SupportedMediaType_e *nRetMIME, IBase *pOwner);

MAE_Ret MMI_Common_FsRetErrCodeToTextId(MMI_Common_Location_Type_e	eLocType, MAE_Ret nFsErrCode, u32 *pnTextId);

/**
* MMI_Common_GetSortComparatorBySetting
* @brief	Utility to get sorting compare function
*
* @param	pvFunCmp                Output compare function.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_GetSortComparatorBySetting(void *pvFunCmp);


#endif  /* __MMI_COMMON_CONTENT_H__ */
