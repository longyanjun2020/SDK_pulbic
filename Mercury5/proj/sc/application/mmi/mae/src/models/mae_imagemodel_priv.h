#ifndef __MAE_IMAGEMODEL_PRIV_H__
#define __MAE_IMAGEMODEL_PRIV_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mae_interfacemodel_priv.h"
#include "mmi_mae_imagemodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/* the main structure for a image Model */

typedef struct
{
	InterfaceModel_t tInterfaceMdl;
	ImgStatus_t 	nPreviousState;
} ImageModel_t;

/*=============================================================*/
// functions
/*=============================================================*/
MAE_Ret ImageModel_New(MAE_ClsId nClsID, void **ppObj);
MAE_Ret ImageModel_QueryInterface(IImageModel *pIImageModel, MAE_IId iId, void **ppObj, IBase *pOwner);
boolean ImageModel_DecodeNextFrame(IImageModel *pIImageModel, ImgStatus_t nState);
#endif //__MAE_IMAGEMODEL_PRIV_H__


