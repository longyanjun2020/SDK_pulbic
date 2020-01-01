/**
 * @file mmi_mae_image.h
 *
 * IIMAGE interface
 *
 * @version $Id: mmi_mae_image.h 1684 2009-08-29 16:28:08Z zinc.chen $
 */
#ifndef __MMI_MAE_IMAGE_H__
#define __MMI_MAE_IMAGE_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_image_forward.h"
#include "mmi_mae_image_types.h"
#include "mmi_mae_forward.h"

#define INHERIT_IImage(IName) \
	INHERIT_IBase(IName); \
	MAE_Ret    (*DecodeFrame)(IName*, s32, ImgStatus_t*); \
	MAE_Ret    (*DrawFrame)  (IName*, s32, s32, s32, IDISPLAY*); \
	MAE_Ret    (*GetProperty)	(IName*, u32, u32); \
	MAE_Ret    (*SetProperty)    (IName*, u32, u32, u32); \
	MAE_Ret    (*Start)      (IName*, boolean); \
	MAE_Ret    (*Stop)       (IName*); \
	MAE_Ret	   (*GetResultBmp)   (IName*, IBITMAP**, IBase*); \
	MAE_Ret	   (*SetSrcData)	 (IName*, u32, u32, u32)

DEFINE_INTERFACE(IImage);

typedef void (*PfnMAE_ImgBuffer)(void *pData);

typedef void (*PfnMAE_ImgNotify)(IImage*, IBase*, ImgStatus_t);

#define IIMAGE_QueryInterface(pImg,id,pp,pOwner)   GET_FUNCTBL(pImg,IImage)->QueryInterface(pImg,id,pp,pOwner)

/**
*  IIMAGE_DecodeFrameEx(IImage *pImg, s32 nFrm, ImgCodecStatus_t* pStat)
*
*  @brief  This macro decodes a frame
*
*  @param  pImg            [in]Pointer to the IImage Object
*  @param  nFrm            [in]Frame No.
*  @param  pStat           [out]Pointer to the memory to store decode result
*
*  @retval MAE_RET_SUCCESS     Success
*  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
*
*  @note If pStat is NULL, this macro works like IIMAGE_DecodeFrame(pImg,nFrm)
*  @note If pStat is not NULL, the result will be put in it. And if the value of pStat is
*        IMG_CDC_STAT_READING or IMG_CDC_STAT_DECODING, IImage will notify the caller further result
*
*/
#define IIMAGE_DecodeFrameEx(pImg,nFrm,pStat)    GET_FUNCTBL(pImg,IImage)->DecodeFrame(pImg,nFrm,pStat)

/**
*  IIMAGE_DecodeFrame(IImage *pImg, s32 nFrm)
*
*  @brief  This macro decodes a frame
*
*  @param  pImg            [in]Pointer to the IImage Object
*  @param  nFrm            [in]Frame No.
*
*  @retval MAE_RET_SUCCESS     Success
*  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
*
*  @note  IImage will notify caller the reslut if the caller has register notify before.
*/
#define IIMAGE_DecodeFrame(pImg,nFrm)         GET_FUNCTBL(pImg,IImage)->DecodeFrame(pImg,nFrm,NULL)

/**
*  IIMAGE_DrawFrame(IImage *pImg, s32 nFrm, s32 x, s32 y, IDisplay *pDisp)
*
*  @brief  This macro draws a frame on the given IDisplay
*
*  @param  pImg            [in]Pointer to the IImage Object
*  @param  nFrm            [in]Frame No.
*  @param  x               [in]x position to draw
*  @param  y               [in]y position to draw
*  @param  pDisp           [in]Destination IDisplay
*
*  @retval MAE_RET_SUCCESS     Success
*  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
*
*  @note  If pDisp is NULL, IImage will draw on the IDisplay set by IDisplay_SetDisplay.
*/
#define IIMAGE_DrawFrame(pImg,nFrm,x,y,pDisp)        GET_FUNCTBL(pImg,IImage)->DrawFrame(pImg,nFrm,x,y,pDisp)

/**
*  IIMAGE_GetProperty(IImage *pImg, u32 c1, u32 c2)
*
*  @brief  This macro gets property value from IImage
*
*  @param  pImg            [in]Pointer to the IImage Object
*  @param  id              [in]Property ID
*  @param  value           [in]New value of the PropID
*
*  @retval MAE_RET_SUCCESS     Success
*  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
*  @retval MAE_RET_NOT_SUPPORTED    The property ID is not supported
*
*/
#define IIMAGE_GetProperty(pImg,id,value)      GET_FUNCTBL(pImg,IImage)->GetProperty(pImg,id,value)

/**
*  IIMAGE_SetParm(IImage *pImg, u32 id, u32 c1, u32 c2)
*
*  @brief  This macro sets parameters to IImage
*
*  @param  pImg            [in]Pointer to the IImage Object
*  @param  id              [in]Parameter ID
*  @param  c1              [in]Data of the parameter
*  @param  c2              [in]Data of the parameter
*
*  @retval MAE_RET_SUCCESS     Success
*  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
*  @retval MAE_RET_NOT_SUPPORTED    The property ID is not supported
*  @retval MAE_RET_OUT_OF_MEMORY      Not enough memory to process the request
*  @retval MAE_RET_FAILED     Other errors
*
*/
#define IIMAGE_SetParm(pImg,id,c1,c2)       GET_FUNCTBL(pImg,IImage)->SetProperty(pImg,id,c1,c2)
/**
*  IIMAGE_Start(IImage *pImg)
*
*  @brief  This macro starts animating
*
*  @param  pImg            [in]Pointer to the IImage Object
*
*  @retval MAE_RET_SUCCESS     Success
*  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
*  @retval MAE_RET_NOT_SUPPORTED    This image does not support animating
*  @retval MAE_RET_NOT_READY      IImage is not ready for animating
*
*/
#define IIMAGE_Start(pImg)                  GET_FUNCTBL(pImg,IImage)->Start(pImg, FALSE)

/**
*  IIMAGE_StartOnce(IImage *pImg)
*
*  @brief  This macro starts animating to play once
*
*  @param  pImg            [in]Pointer to the IImage Object
*
*  @retval MAE_RET_SUCCESS     Success
*  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
*  @retval MAE_RET_NOT_SUPPORTED    This image does not support animating
*  @retval MAE_RET_NOT_READY      IImage is not ready for animating
*
*/
#define IIMAGE_StartOnce(pImg)                  GET_FUNCTBL(pImg,IImage)->Start(pImg, TRUE)


/**
*  IIMAGE_Stop(IImage *pImg)
*
*  @brief  This macro stops animating
*
*  @param  pImg            [in]Pointer to the IImage Object
*
*  @retval MAE_RET_SUCCESS     Success
*  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
*
*/
#define IIMAGE_Stop(pImg)                   GET_FUNCTBL(pImg,IImage)->Stop(pImg)

/**
*  IIMAGE_LoadDecodeResultAsBitmap(IImage *pImg, IBitmap **ppBmp, IBase*pOwner)
*
*  @brief  This macro load the decoded result as IBitmap, 
*			the returned IBimtap must be released the ownership by RELEASEIF(pBmp, pOwner) or SH_FreeRes(pBmp)
*
*  @param  pImg            [in]Pointer to the IImage Object
*  @param  ppBmp          [in]the returned result IBitmap
*  @param  pOwner         [in]Pointer to the owner object, which will own the result bitmap, 
*
*  @retval MAE_RET_SUCCESS     Success
*  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
*  @retval MAE_RET_NOT_READY   The image doesn't decode done yet.
*
*/
#define IIMAGE_LoadDecodeResultAsBitmap(pImg,ppBmp,pOwner)    GET_FUNCTBL(pImg,IImage)->GetResultBmp(pImg,ppBmp,pOwner)

/**
 *  IIMAGE_Draw(IImage *pImg, s32 x, s32 y, IDisplay *pDisp)
 *
 *  @brief  This macro draws current frame on the given IDisplay
 *
 *  @param  pImg            [in]Pointer to the IImage Object
 *  @param  nFrm            [in]Frame No.
 *  @param  x               [in]x position to draw
 *  @param  y               [in]y position to draw
 *  @param  pDisp           [in]Destination IDisplay
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
 *
 *  @note  If pDisp is NULL, IImage will draw on the IDisplay set by IDisplay_SetDisplay.
 */
__INLINE MAE_Ret IIMAGE_Draw(IImage *pImg, u32 x, u32 y, IDISPLAY *pDisp)
{
	return IIMAGE_DrawFrame(pImg, IMG_CURRENT_FRAME, x, y, pDisp);
}

/* Get image informatin */
__INLINE MAE_Ret IIMAGE_GetImageInfo(IImage *pImg, ImageInfo_t *pInfo)
{
	return IIMAGE_GetProperty(pImg, IMG_PROP_IMG_INFO, (u32)pInfo);
}

/* Get image width and height */
__INLINE MAE_Ret IIMAGE_GetImageFormat(IImage *pImg, ImgFormat_t *pFormat)
{
	return IIMAGE_GetProperty(pImg, IMG_PROP_IMG_FORMAT, (u32)pFormat);
}

/* get Animation information */
MAE_INLINE MAE_Ret IIMAGE_IsAnimation(IImage *pImg, boolean *pbIsAnim)
{
	return IIMAGE_GetProperty(pImg, IMG_PROP_IS_ANIMATION, (u32)pbIsAnim);
}

/* Get image format */
__INLINE MAE_Ret IIMAGE_GetImageSize(IImage *pImg, ImageSize_t *pSize)
{
	return IIMAGE_GetProperty(pImg, IMG_PROP_IMG_SIZE, (u32)pSize);
}

/* get decode parameters */
__INLINE MAE_Ret IIMAGE_GetDecodeParam(IImage *pImg, ImageDecodeParm_t *pParm)
{
	return IIMAGE_GetProperty(pImg, IMG_PROP_DEC_PARAM, (u32)pParm);
}

/* get current decode status */
__INLINE MAE_Ret IIMAGE_GetStatus (IImage *pImg, ImageStatus_t *pStat)
{
	return IIMAGE_GetProperty(pImg, IMG_PROP_STATUS, (u32)pStat);
}

/* get current decode status */
__INLINE MAE_Ret IIMAGE_GetAnimStatus (IImage *pImg, ImgAnimState_t *pStat)
{
	return IIMAGE_GetProperty(pImg, IMG_PROP_ANIM_STATUS, (u32)pStat);
}

/* calculate default decode size with given decode angle */
__INLINE MAE_Ret IIMAGE_GetDefaultDecSize(IImage *pImg, ImageDefaultDecParm_t *pDefParm)
{
	return IIMAGE_GetProperty(pImg, IMG_PROP_DEF_DEC_SIZE, (u32)pDefParm);
}

MAE_Ret IIMAGE_SetSrcBuffer(IImage *pImg, u8 *pBuf, u32 size, PfnMAE_ImgBuffer pfnFree);
MAE_Ret IIMAGE_SetSrcURL(IImage *pImg, u16 *pFilePath);
#define IIMAGE_SetSrcFile IIMAGE_SetSrcURL

__INLINE MAE_Ret IIMAGE_ClearSrcBuffer(IImage *pImg)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_CLEAR_SRC_BUFFER, 0, 0);
}

__INLINE MAE_Ret IIMAGE_SetDisplay(IImage *pImg, IDISPLAY *pDisp)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_SET_DISPLAY, *(u32*)&pDisp, 0);
}

/**
 *  IIMAGE_RegNotify(IImage *pImg, PfnMAE_ImgNotify pfnNotify, IBase* pCaller)
 *
 *  @brief  This function registers notify of the IImage object
 *
 *  @param  pImg            [in]Pointer to the IImage Object
 *  @param  pfnNotify       [in]Notify function pointer
 *  @param  pCaller         [in]Pointer to the caller instance, this will be the 1st param when pfnNotify is called
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
 *
 */
__INLINE MAE_Ret IIMAGE_RegNotify(IImage *pImg, PfnMAE_ImgNotify pfnNotify, IBase* pCaller)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_REG_NOTIFY, *(u32*)&pfnNotify, *(u32*)&pCaller);
}

/**
 *  IIMAGE_DeregNotify(IImage *pImg, PfnMAE_ImgNotify pfnNotify, IBase* pCaller)
 *
 *  @brief  This function deregisters notify of the IImage object
 *
 *  @param  pImg            [in]Pointer to the IImage Object
 *  @param  pfnNotify       [in]Notify function pointer
 *  @param  pCaller         [in]Pointer to the caller instance, this will be the 1st param when pfnNotify is called
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
 *
 */
__INLINE MAE_Ret IIMAGE_DeregNotify(IImage *pImg, PfnMAE_ImgNotify pfnNotify, IBase* pCaller)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_DEREG_NOTIFY, *(u32*)&pfnNotify, *(u32*)&pCaller);
}

/**
 *  IIMAGE_SetAutoDecode(IImage *pImg, boolean bAuto)
 *
 *  @brief  This function sets auto-decode flag to IImage object
 *
 *  @param  pImg            [in]Pointer to the IImage Object
 *  @param  bAuto           [in]Flag
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_BAD_PARAM   pImg is NULL
 *
 *  Note: When bAuto is TRUE, the IImage will auto decode the first frame when any strem is set to IImage
 */
__INLINE MAE_Ret IIMAGE_SetAutoDecode(IImage *pImg, boolean bAuto)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_AUTODECODE, *(u32*)&bAuto, 0);
}

/**
 *  IIMAGE_SetDecodeParm(IImage *pImg, ImageDecodeParm_t *pDecParm)
 *
 *  @brief  This function sets decode parameters to IImage object
 *
 *  @param  pImg            [in]Pointer to the IImage Object
 *  @param  pDecParm        [in]Pointer to decode parameter structure
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_BAD_PARAM   pImg is NULL
 *  @retval MAE_RET_BUSY        IImage is decoding
 *
 *  Note: If the image is already decoded, this function will redecode with new parameters
 */
__INLINE MAE_Ret IIMAGE_SetDecodeParm(IImage *pImg, ImageDecodeParm_t *pDecParm)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_SET_DECODE_PARM, *(u32*)&pDecParm, 0);
}

__INLINE MAE_Ret IIMAGE_SetRotateAngle(IImage *pImg, u32 angle)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_SET_ROTATE_ANGLE, angle, 0);
}


__INLINE MAE_Ret IIMAGE_SetDecodeOnDraw(IImage *pImg, boolean bDecodeOnDraw)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_DECODEONDRAW, *(u32*)&bDecodeOnDraw, 0);
}

__INLINE MAE_Ret IIMAGE_SetForceAsyncDecode(IImage *pImg, boolean bForceAsync)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_FORCE_ASYNC, *(u32*)&bForceAsync, 0);
}

/**
 *  IIMAGE_SetAnimTimeInterval(IImage *pImg, u32 nTimeInterval)
 *
 *  @brief  This function sets the delay time that a frame is displayed in an animation to IImage object
 *
 *  @param  pImg            [in]Pointer to the IImage Object
 *  @param  nTimeInterval   [in]the time that a frame is displayed(ms)
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_BAD_PARAM   pImg is NULL or nTimeInterval is small than 1ms
 *
 *  @Note: For reference only
 *         APNG(Async decode) Size: 150*1024  average decode time: 280ms
 *             (Sync  decode) Size: 150*1024  average decode time: 30ms
 *         GIF (Sync  decode) Size: 150*1024  average decode time: 60ms
 *         we suggest do Not set the delay time small than above average decode time
 *
 */
__INLINE MAE_Ret IIMAGE_SetAnimTimeInterval(IImage *pImg, u32 nTimeInterval)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_SET_DELAY_TIME, nTimeInterval, 0);
}

#ifdef __MMI_STEREO_IMAGE__
/**
*set stereo for decode param,this interface don't call decode frame
*
**/
__INLINE MAE_Ret IIMAGE_SetDecodeParmStereo(IImage *pImg, ImgDecStereo_e eDecStero)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_DEC_PARM_STEREO, *(u32*)&eDecStero, 0);
}
#endif

/**
 *  IIMAGE_SetCanUsePaletteOutput(IImage *pImg, boolean bAuto)
 *
 *  @brief  This function sets if the image can use palette output, this is 8 bit color format, also need codec support
 *
 *  @param  pImg            [in]Pointer to the IImage Object
 *  @param  bCanUse           [in]Flag
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_BAD_PARAM   pImg is NULL
 *
 *  Note: If set this flag and codec support, the output format will be set as 8 bit palette format
 */
__INLINE MAE_Ret IIMAGE_SetCanUsePaletteOutput(IImage *pImg, boolean bCanUse)
{
	return IIMAGE_SetParm(pImg, IMG_PARM_SET_CAN_USE_PALETTE_OUTPUT, *(u32*)&bCanUse, 0);
}

MAE_Ret IIMAGE_FreeDecodeBuffer(IImage *pImg);

#endif /* __MAE_IMAGE_H__ */
