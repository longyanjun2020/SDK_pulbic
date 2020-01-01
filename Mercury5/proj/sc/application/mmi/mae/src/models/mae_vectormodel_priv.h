/**
 * @file mae_vectormodel_priv.h
 * @brief This file defines the data structure of a vector model and function prototype for implementation.
 *
 * @version $Id: mae_vectormodel_priv.h 1309 2009-07-06 14:00:16Z steve.lee $
 */
#ifndef __MAE_VECTORMODEL_PRIV_H__
#define __MAE_VECTORMODEL_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_modelbase.h"
#include "mmi_mae_vectormodel.h"

#define VECTOR_GROWBY              10
/*=============================================================*/
// type and define
/*=============================================================*/
/* the main structure for a Vector Model */

typedef struct
{
	void **ppItems;  //pointer to array of void* items
	u32  nItems;     //number of valid items in array
	u32  nSize;      //total number of allocation items(valid items and free items) in array
	u32  nGrowBy;    //grow-by size(number of items) for subsequent allocations
	PfnModelFree  pfnFree;  //free function (called in Vector_Dtor)
	IBase *pItemOwner;	///< a pointer of IBase obj to keeps the owner of the data in vector model
} Vector_t;


typedef struct
{
    Model_t  tMdlBase;
    Vector_t  tVector;
} VectorModel_t;


/*=============================================================*/
// functions
/*=============================================================*/
u32 VectorModel_Release(IVectorModel *pIVectorModel);
MAE_Ret VectorModel_QueryInterface(IVectorModel *pIVectorModel, MAE_IId nIId, void **ppObj, IBase *pOwner);

MAE_Ret VectorModel_New(MAE_ClsId nClsID, void **ppObj);
void VectorModelStrucInit(VectorModel_t *pThis, const FUNCTBL(IVectorModel) *FtblPtr);

u32 VectorModel_Size(IVectorModel *pIVectorModel);
MAE_Ret VectorModel_GetAt(IVectorModel *pIVectorModel, u32 nIndex, ListDataType_e nType, void **ppvItem);
MAE_Ret VectorModel_ReplaceAt(IVectorModel *pIVectorModel, u32 nIndex, void *pItem, boolean bNotify);
MAE_Ret VectorModel_InsertAt(IVectorModel *pIVectorModel, u32 nIndex, void *pItem);
MAE_Ret VectorModel_DeleteAt(IVectorModel *pIVectorModel, u32 nIndex);
void VectorModel_DeleteAll(IVectorModel *pIVectorModel);
MAE_Ret VectorModel_EnsureCapacity(IVectorModel *pIVectorModel, u32 nRequired, u32 nGrowBy);
ListModelFree_t VectorModel_SetPfnFree(IVectorModel *pIVectorModel, PfnModelFree pfnFree, IBase *pItemOwner);
#endif //__MAE_VECTORMODEL_PRIV_H__
/*=============================================================*/
// end of file
