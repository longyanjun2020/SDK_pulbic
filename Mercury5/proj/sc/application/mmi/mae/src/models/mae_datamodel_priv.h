/**
* @file mae_datamodel_priv.h
* @version $Id: mae_datamodel_priv.h 1309 2009-07-06 14:00:16Z steve.lee $
* @brief This file defines the data structure of datamodel object and function prototype for implementation.
*
*/

#ifndef __MAE_DATAMODEL_PRIV_H__
#define __MAE_DATAMODEL_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_datamodel.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_modelbase.h"


/*=============================================================*/
// type and define
/*=============================================================*/
/**
* @brief   The structure for a DataModel object.
*/
typedef struct
{
	Model_t             tMdlBase;            ///< Base structure for a model
	void                *pDataPtr;           ///< A pointer to keep the address of data
	s32                 nDataLen;            ///< The length of data
	PfnModelFree  pfnFreeFuncPtr;        /*!< A pointer to keep free function which will execute
											when this model release or when data is set to another one*/
	IBase 				*pDataOwner;	    ///< A pointer of IBase to keeps the data's owner
	void                *pCtxToAdaptSet;    ///< A pointer to keep context data which will be used when call adapt-Set function
	PfnAdaptSet         pfnAdaptSetFuncPtr;    ///< A pointer to keep adapt-Set function
	void                *pCtxToAdaptGet;    ///< A pointer to keep context data which will be used when call adapt-Get function
	PfnAdaptGet         pfnAdaptGetFuncPtr;    ///< A pointer to keep adapt-Get function
} DataModel_t;


/*=============================================================*/
// functions
/*=============================================================*/
/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
/**
* DataModelStructCtor
* @brief   To initilize datamodel structure(DataModel_t).
*
* @param   pThis(DataModel_t*)   A pointer of structure DataModel_t.
* @param   FtblPtr               Function table pointer of IDataModel interface.
*
* @retval  None.
*/
void DataModelStructCtor(DataModel_t *pThis, const FUNCTBL(IDataModel) *FtblPtr);

/**
* DataModelStructDtor
* @brief   A destructor for datamodel structure(DataModel_t).
*          The data kept in this datamodel will be freed in this function call.
*
* @param   pThis(DataModel_t*)   A pointer of structure DataModel_t.
*
* @retval  None.
*/
void DataModelStructDtor(DataModel_t *pThis);

/**
* DataModel_New
* @brief   This is a constructor for CLSID_DATAMODEL class object.
*          Here is the beginning to create CLSID_DATAMODEL object.
*          This function will allocate structure DataModel_t as the base of CLSID_DATAMODEL object.
*
* @param   nClsID(MAE_ClsId)       A class id to indicate which object to create.
* @param   ppObj(void**)          A pointer of void pointer to retrieve the datamodel object.
*
* @retval  MAE_RET_SUCCESS        Successfully.
* @retval  MAE_RET_OUT_OF_MEMORY  Failed. Not enough memory to create this object.
* @retval  MAE_RET_NOT_SUPPORTED  Failed. Not support this kind of class id.
*/
MAE_Ret DataModel_New(MAE_ClsId nClsID, void **ppObj);


/*------------------------------------------------------------------------------------------
* For IBase interface
------------------------------------------------------------------------------------------*/

/**
* DataModel_Release
* @brief   This function is the implementation of release function in IDataModel interface.
*          Everytime this function executes, the reference count would minus one. If the
*          reference count comes to zero, the object would be released.
*
* @param   pIDataModel(IDataModel*)    A pointer of IDataModel interface object.
*
* @retval  Return the reference count.
*/
u32 DataModel_Release(IDataModel *pIDataModel);

/**
* DataModel_QueryInterface
* @brief   This function is the implementation of query interface function in IDataModel interface.
*
* @param   pIDataModel(IDataModel*)    A pointer of IDataModel interface object.
* @param   nIId(MAE_IId)                An interface id to be queried.
* @param   ppObj(void**)               A pointer of void pointer to retrieve an interface object which you want to query.
* @param   pOwner(IBase*)              Shall be an IBase interface object to keep the return object.
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
*
* @note    Only supports IID_DATAMODEL and IID_MODEL to query.
*/
MAE_Ret DataModel_QueryInterface(IDataModel *pIDataModel, MAE_IId nIId, void **ppObj, IBase *pOwner);


/*------------------------------------------------------------------------------------------
* For IDataModel interface
------------------------------------------------------------------------------------------*/

/**
* DataModel_SetData
* @brief   This function is the implementation of set data function in IDataModel interface.
*
* @param   pIDataModel(IDataModel*)    A pointer of IDataModel interface object.
* @param   pDataPtr(void*)              A void pointer of data which want to be set into datamodel object.
* @param   nLen(s32)                   The length of data.
* @param   evtParam(u32)               Additional data for model change event (optional).
* @param   pfnFree(PfnModelFree)  A free function pointer to free data.
* @param   pOwner(IBase*)              A IBase pointer to indicate who is the owner of data.
*
* @retval  None.
*
* @note    Adapt-Set would occur if there is adapt-set function pointer.(set by IDATAMODEL_SetAdaptSetFunc())
*          The free function(pfnFree) and owner of data(pOwner) should be set to the datamodel object
*          if the data want to be freed. If the data is not dynamic allocated or AP/user wants to control
*          the data by himself, just set the free function to NULL.
*          The owner of data(pOwner) would pass in the free function to release object(s) which kept in the data.
*/
void DataModel_SetData(IDataModel *pIDataModel, void *pDataPtr, s32 nLen, u32 evtParam, PfnModelFree pfnFree, IBase *pOwner);

/**
* DataModel_GetData
* @brief   This function is the implementation of get data function in IDataModel interface.
*
* @param   pIDataModel(IDataModel*)    A pointer of IDataModel interface object.
* @param   pLenPtr(s32*)                An output to retrieve data length.
*
* @retval  Reture a void pointer(void*) to indicate data address.
*
* @note    Adapt-Get would occur if there is adapt-get function pointer.(set by IDATAMODEL_SetAdaptGetFunc())
*/
void *DataModel_GetData(IDataModel *pIDataModel, s32 *pLenPtr);

/**
* DataModel_SetAdaptSet
* @brief   This function is the implementation of set adapt-set function in IDataModel interface.
*          IDataModel object keeps the adapt-set function and context data pointer and uses them
*          only when IDATAMODEL_SetData() executes.
*
* @param   pIDataModel(IDataModel*)            A pointer of IDataModel interface object.
* @param   pAdaptSetFunc(ADAPT_SET_FUNC_PTR)   A adapt-set function pointer.
* @param   pCtxData(void*)                     A context data pointer.
*
* @retval  None.
*/
void DataModel_SetAdaptSet(IDataModel *pIDataModel, PfnAdaptSet pAdaptSetFunc, void *pCtxData);

/**
* DataModel_SetAdaptGet
* @brief   This function is the implementation of set adapt-get function in IDataModel interface.
*          IDataModel object keeps the adapt-get function and context data pointer and uses them
*          only when IDATAMODEL_GetData() executes.
*
* @param   pIDataModel(IDataModel*)            A pointer of IDataModel interface object.
* @param   pAdaptGetFunc(ADAPT_GET_FUNC_PTR)   A adapt-get function pointer.
* @param   pCtxData(void*)                     A context data pointer.
*
* @retval  None.
*/
void DataModel_SetAdaptGet(IDataModel *pIDataModel, PfnAdaptGet pAdaptGetFunc, void *pCtxData);

#endif //__MAE_DATAMODEL_PRIV_H__
/*=============================================================*/
// end of file

