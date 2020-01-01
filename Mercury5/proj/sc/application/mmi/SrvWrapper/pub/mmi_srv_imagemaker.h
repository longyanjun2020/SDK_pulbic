/**
* @file    mmi_srv_imagemaker.h
* @brief   
*          
*/

#ifndef __MMI_SRV_IMAGEMAKER_H__
#define __MMI_SRV_IMAGEMAKER_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_imagemaker_forward.h"

/** SrvImageMakerSaveAs
* @brief  This function saves the given image/bitmap object to file as desired format.
* 
* @param[in]      pObj                    Instance of the source object, can be IImage or IBitmap
* @param[in]      pEncData                Encoding parameters
* @param[in]      pFilename               Filename saved to
* @param[in]      pfnCB                   Pointer to callback function
* @param[in]      pData                   Pointer to data of callback function
* 
* @retval  MAE_RET_SUCCESS                 If successful.
* @retval  MAE_RET_NOT_SUPPORTED           If pEncData is not supported format. 
* @retval  MAE_FS_ERROR                    If write failed. 
*/
MAE_Ret SrvImageMakerSaveAs(IBase *pObj,
                            ImgMkrEncData_t *pEncData,
                            MAE_WChar *pFilename,
                            PfnMAE_ImgMkr_Callback pfnCB,
                            ImageMakerCBData_t *pData);

/** SrvImageMakerCancelCallback
* @brief  This function cancels callback function which is registered by SrvImageMakerSaveAs function.
* 
* @param[in]      pData                   Pointer to data of callback function, which will be set to NULL.
*/
void SrvImageMakerCancelCallback(ImageMakerCBData_t *pData);

/** SrvImageMakerRotate
* @brief  This function rotates image by given filename.
* 
* @param[in]      pFileName               Filename of image object which is desired to rotate.
* @param[in]      rotate				  Rotate angle, which are 0, 90, 180, 270, and 360(=0) degrees.
* @param[in]      pfnCB					  Pointer to callback function.
* @param[in]      pData                   Pointer to data of callback function.
* 
* @retval  MAE_RET_SUCCESS           If successful.
* @retval  MAE_RET_FAILED            If an error happens. 
*/
MAE_Ret SrvImageMakerRotate(MAE_WChar *pFileName,
                            ImgMkrRotate_e rotate,
                            PfnMAE_ImgMkr_Callback pfnCB,
                            ImageMakerCBData_t *pData);


#endif /*__MMI_SRV_IMAGEMAKER_H__*/
