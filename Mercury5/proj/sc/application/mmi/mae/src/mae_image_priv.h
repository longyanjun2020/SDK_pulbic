/**
* @file mae_image_priv.h
*
* TODO:Add descriptions here
*
* @version $Id: mae_image_priv.h 1684 2009-08-29 16:28:08Z zinc.chen $
*/
#ifndef __MAE_IMAGE_PRIV_H__
#define __MAE_IMAGE_PRIV_H__

#include "mmi_mae_image.h"
#include "mmi_mae_forward.h"
#include "mmi_mae_codec_util.h"
#include "mmi_mae_customization_forward.h"
#include "mmi_mae_image_forward.h"

typedef struct
{
	PfnMAE_ImgNotify  pfnNotify;
	u32               nCaller;//store instance id instead of IBase pointer
	boolean            bValid;
} ImageNtfyElmnt_t;

typedef struct
{
	ImageNtfyElmnt_t  *pElmnts;
	u32                nMax;
	u32                nCnt;
} ImageNtfyData_t;


typedef struct
{
	DECLARE_FUNCTBL(IImage);
	ImageNtfyData_t			tNtfyData;
	ImageSize_t				tImgSize;
	ImageDecodeParm_t		tDecodeParm;
	PfnMAE_ImgBuffer		pfnFree;

	IDISPLAY				*pDisp;
	u8						*pSrcBuf;
	IBITMAP					*pBmp;
	ThmHead_t				*pImageTheme;

	ImgStatus_e				nStatus;
	ImgCDCMsg_e				nErrorCode;
	ImgFormat_e				nFormat;
	ImgAnimState_e			nAnimState;

	u32 					nRefCnt;
	u32						nResId;	// resource image ID
	u32						nSrcSize;
	u32						nDelayTime;   //msec


	s32						nCodecHandle;
	s32						nCurFrame;
	s32                     nDrawX;
	s32                     nDrawY;
#ifdef __MMI_STEREO_IMAGE__
    ImgDecStereo_e          eDecStereo;
#endif

	u8						bWaitReleaseImage:1;
	u8						bWaitReleaseSrcBuf:1;
	u8						bWaitReleaseDecBuf:1;
	u8						bAutoDecode:1;
	u8						bAsyncDecode:1;
	u8						bWaitDraw:1;
	u8						bIsAnim:1;
	u8						bHasAlphaMask:1;
	u8						bAnimOnce:1;
	u8						bSupportPaletteOutput:1;	// for codec info
	u8						bCanUsePaletteOutput:1;	// for AP setting
	u8						bNeedReDecode:1;	// cancel abort
	u8						bSetUserTimeInterval:1;
}_Image_t;

enum Img_Priv_Param_tag
{
	IMG_PRIV_PARM_RES_IMAGE_ID=IMG_PARM_LAST+1,			///< to set resource image id, IMG_NULL_ID as default, should only be set from shell load pre-defined image
	IMG_PRIV_PARM_SET_THEME								/// to set the image belongs to the theme
};

///< to set resource image id, IMG_NULL_ID as default value, should only be set from shell load pre-defined image
__INLINE MAE_Ret IIMAGE_SetResID(IImage *pImg, u32 nResId)
{
	return GET_FUNCTBL(pImg,IImage)->SetProperty(pImg, IMG_PRIV_PARM_RES_IMAGE_ID, nResId, 0);
}

#define IIMAGE_GetResultBmp(pImg,ppBmp,pOwner)    GET_FUNCTBL(pImg,IImage)->GetResultBmp(pImg,ppBmp,pOwner)

#endif /* __MAE_IMAGE_PRIV_H__ */
