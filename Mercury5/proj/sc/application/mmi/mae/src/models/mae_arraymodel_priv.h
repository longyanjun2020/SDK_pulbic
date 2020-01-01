/**
 * @file mae_arraymodel_priv.h
 * @brief This file defines the data structure of a array model and function prototype for implementation.
 *
 * @version $Id: mae_arraymodel_priv.h 1309 2009-07-06 14:00:16Z steve.lee $
 */
#ifndef __MAE_ARRAYMODEL_PRIV_H__
#define __MAE_ARRAYMODEL_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_modelbase.h"
#include "mmi_mae_arraymodel.h"

#define ITEM_GROWBY              10
#define ITEM_FREE_THRESHOLD      10

/*=============================================================*/
// type and define
/*=============================================================*/
/* the main structure for a Array Model */

typedef struct
{
	u32  nItemSize;     //the byte size of each item
	u32  nValidItems;   //number of valid items in array
	u32  nTotalItems;   //Total number of allocation items(valid items and free items) in array
	u32  nEnsureItems;  //number of ensure items in array
	u32  nGrowBy;       //grow-by size(number of items) for subsequent allocations
	void *pItemArray;     //pointer to array of items
	PfnModelFree  pfnFree;  //the free function for the member of the items
	IBase *pItemOwner;	///< a pointer of IBase obj to keeps the owner of the data in array model
} Array_t;

typedef struct
{
	Model_t tMdlBase;
	Array_t  tArray;
} ArrayModel_t;

/*=============================================================*/
// functions
/*=============================================================*/
u32 ArrayModel_Release(IArrayModel *pIArrayModel);
MAE_Ret ArrayModel_QueryInterface(IArrayModel *pIArrayModel, MAE_IId nIId, void **ppObj, IBase *pOwner);

MAE_Ret ArrayModel_New(MAE_ClsId nClsID, void **ppObj);
void ArrayModelStrucInit(ArrayModel_t *pThis, const FUNCTBL(IArrayModel) *FtblPtr);

u32 ArrayModel_Size(IArrayModel *pIArrayModel);
MAE_Ret ArrayModel_GetAt(IArrayModel *pIArrayModel, u32 nIndex, ListDataType_e nType, void **ppvItem);
MAE_Ret ArrayModel_ReplaceAt(IArrayModel *pIArrayModel, u32 nIndex, void *pItem, boolean bNotify);
MAE_Ret ArrayModel_InsertAt(IArrayModel *pIArrayModel, u32 nIndex, void *pItem);
MAE_Ret ArrayModel_DeleteAt(IArrayModel *pIArrayModel, u32 nIndex);
void ArrayModel_DeleteAll(IArrayModel *pIArrayModel);
MAE_Ret ArrayModel_EnsureCapacity(IArrayModel *pIArrayModel, u32 nRequired, u32 nGrowBy);
ListModelFree_t ArrayModel_SetPfnFree(IArrayModel *pIArrayModel, PfnModelFree pfnFree, IBase *pItemOwner);


void ArrayModel_SetItemByteSize(IArrayModel *pIArrayModel, u32 nItemByteSize);
u32 ArrayModel_GetItemByteSize(IArrayModel *pIArrayModel);

#endif //__MAE_ARRAYMODEL_PRIV_H__
/*=============================================================*/
// end of file
