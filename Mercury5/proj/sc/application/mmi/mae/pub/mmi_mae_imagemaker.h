/**
 * @file mmi_mae_imagemaker.h
 *
 * IIMAGEMAKER interface
 *
 * @version $Id: mmi_mae_imagemaker.h 697 2009-04-23 06:52:50Z steve.lee $
 */
#ifndef __MMI_MAE_IMAGEMAKER_H__
#define __MMI_MAE_IMAGEMAKER_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_imagemaker_forward.h"

#define INHERIT_IImageMaker(IName) \
	INHERIT_IBase(IName); \
	MAE_Ret     (*SaveAs) (IName*, IBase*, ImgMkrEncData_t *, MAE_WChar*, PfnMAE_ImgMkr_Callback, ImageMakerCBData_t*); \
         MAE_Ret     (*Encode) (IName*, IBase*, ImgMkrEncData_t *, u8*, u32, PfnMAE_ImgMkr_Callback, ImageMakerCBData_t*); \
	MAE_Ret     (*CancelCallback) (IName*, ImageMakerCBData_t*);\
	MAE_Ret     (*Rotate) (IName*, MAE_WChar*, ImgMkrRotate_e, PfnMAE_ImgMkr_Callback, ImageMakerCBData_t*)

DEFINE_INTERFACE(IImageMaker);

/**
 *  IIMAGEMAKER_SetParm(IImageMaker *pImgMkr, u32 id, u32 c1, u32 c2)
 *
 *  @brief  This function sets parameter to IImageMaker object
 *
 *  @param  pImgMkr         [in]Pointer to the IImageMaker Object
 *  @param  id              [in]Parameter id
 *  @param  c1              [in]First data of the parameter
 *  @param  c2              [in]Second data of the parameter
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAR_RET_FAILED      Unknown error
 *  @retval MAE_RET_NOTSUPPORT  Parameter id not support
 *
 */
//#define IIMAGEMAKER_SetParm(pImgMkr,id,c1,c2)   GET_FUNCTBL(pImgMkr,IImageMaker)->SaveAs(pImgMkr,id,c1,c2)

/**
 *  IIMAGEMAKER_SaveAs(IImageMaker *pImgMkr,
 *                     IBase *pObj,
 *                     ImgMkrEncData_t *pEncData,
 *                     MAE_WChar *pFilename,
 *                     PfnMAE_ImgMkr_Callback pfn,
 *                     ImageMakerCBData_t *pData)
 *
 *  @brief  This function saves the given image/bitmap object to file as desired format
 *
 *  @param  pImgMkr         [in]Pointer to the IImageMaker Object
 *  @param  pObj            [in]Instance of the source object, can be IImage or IBitmap
 *  @param  pEncData        [in]Encoding parameters
 *  @param  pFilename       [in]Filename to save to
 *  @param  pfn             [in]Pointer to callback function
 *  @param  pData           [in]Pointer to data of callback function
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAR_RET_FAILED      Unknown error
 *  @retval MAE_RET_NOTSUPPORT  Encode type or blocking mode not support
 *
 *  Note: This function support both BLOCKING and NON-BLOCKING mode. If pfn or pData is NULL,
 *        this function will be a BLOCKING function. If certain mode is not supported by the
 *        encoding format, MAE_RET_NOTSUPPORT will be returned.
 */
#define IIMAGEMAKER_SaveAs(pImgMkr,pObj,pEncData,pFilename,pfn,pData)   GET_FUNCTBL(pImgMkr,IImageMaker)->SaveAs(pImgMkr,pObj,pEncData,pFilename,pfn,pData)

/**
 *  IIMAGEMAKER_Encode(IImageMaker *pImgMkr, 
 *                     IBase *pObj, 
 *                     ImgMkrEncData_t *pEncData, 
 *                     u8 *pOutBuf,
 *                     u32 nBufSize,
 *                     PfnMAE_ImgMkr_Callback pfn,
 *                     ImageMakerCBData_t *pData)
 *
 *  @brief  This function saves the given image/bitmap object to file as desired format
 *   
 *  @param  pImgMkr         [in]Pointer to the IImageMaker Object
 *  @param  pObj            [in]Instance of the source object, can be IImage or IBitmap
 *  @param  pEncData        [in]Encoding parameters
 *  @param  pOutBuf         [in]Pointer to output buffer
 *  @param  nBufSize        [in]Size of output buffer
 *  @param  pfn             [in]Pointer to callback function
 *  @param  pData           [in]Pointer to data of callback function
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAR_RET_FAILED      Unknown error
 *  @retval MAE_RET_NOTSUPPORT  Encode type or blocking mode not support
 *
 *  Note: This function support both BLOCKING and NON-BLOCKING mode. If pfn or pData is NULL, 
 *        this function will be a BLOCKING function. If certain mode is not supported by the
 *        encoding format, MAE_RET_NOTSUPPORT will be returned.
 */
#define IIMAGEMAKER_Encode(pImgMkr,pObj,pEncData,pOutBuf,nBufSize,pfn,pData)   GET_FUNCTBL(pImgMkr,IImageMaker)->Encode(pImgMkr,pObj,pEncData,pOutBuf,nBufSize,pfn,pData)

/** 
 *  IIMAGEMAKER_CancelCallback(IImageMaker *pImgMkr,
 *                             ImageMakerCBData_t *pData)
 *
 *  @brief  This function cancels callback function register by function IIMAGEMAKER_SaveAs
 *
 *  @param  pImgMkr         [in]Pointer to the IImageMaker Object
 *  @param  pData           [in]Pointer to callback data
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
 *
 */
#define IIMAGEMAKER_CancelCallback(pImgMkr,pData)   GET_FUNCTBL(pImgMkr,IImageMaker)->CancelCallback(pImgMkr,pData)

/**
 *  IIMAGEMAKER_CancelCallback(IImageMaker *pImgMkr,
 *                             ImageMakerCBData_t *pData)
 *
 *  @brief  This function cancels callback function register by function IIMAGEMAKER_SaveAs
 *
 *  @param  pImgMkr         [in]Pointer to the IImageMaker Object
 *  @param  pData           [in]Pointer to callback data
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_BAD_PARAM   Wrong parameter(s)
 *
 */
#define IIMAGEMAKER_Rotate(pImgMkr,filename, rotate,pfn,pData)   GET_FUNCTBL(pImgMkr,IImageMaker)->Rotate(pImgMkr,filename,rotate,pfn,pData)

/**
 * Functions
 */
MAE_Ret MAEImageMaker_New(MAE_ClsId nClsID, void **ppObj);

#endif /* __MMI_MAE_IMAGEMAKER_H__ */
