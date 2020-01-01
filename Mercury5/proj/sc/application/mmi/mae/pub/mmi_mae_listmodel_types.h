/**
* @file    mmi_mae_listmodel.h
* @version $Id: mmi_mae_listmodel.h 978 2009-05-26 10:47:39Z elvis.chen $
* @brief   This file defines IListModel interface.
*
*/
#ifndef __MMI_MAE_LISTMODEL_TYPES_H__
#define __MMI_MAE_LISTMODEL_TYPES_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/**
* @brief   when list model changed, send notification via this structure.
*/
struct ListModelEvent_t_
{
	ModelEvent_t    tMEvtBase;  ///< model event base structure
	u32             nPos;      ///< changed position.
	u32             nOldSize;  ///< item number before changed
	u32             nNewSize;  ///< item number after changed
};

enum ListDataType_e_
{
	COMMON_LIST_DATA = 0,
	LIST_DATATYPE_SUM
};


/**
 * @brief   This structure is the return value of the SetPfnFree function.
 *          Keeping the pointer of free function and the object instance of data owner.
 */
struct ListModelFree_t_
{
	PfnModelFree pfnFreeFunc;    /*!< A function pointer to keep free function which will be used
                                          when release a model or deleting/replacing the data in the model.*/
	IBase * pOwner;                  ///< An IBase object instance to indicate who is the owner of the data(object) in the model.
};

#endif //__MMI_MAE_LISTMODEL_TYPES_H__
/*=============================================================*/
// end of file
