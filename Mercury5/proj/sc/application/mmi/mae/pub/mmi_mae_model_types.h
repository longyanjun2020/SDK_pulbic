/**
 * \file    mmi_mae_model_types.h
 * \brief   
 *
 * @version
 */

#ifndef __MMI_MAE_MODEL_TYPES_H__
#define __MMI_MAE_MODEL_TYPES_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_model.h"
#include "mmi_mae_model_events.h"
#include "mmi_mae_forward.h"

/**
* @brief   The callback function prototype for model listener
*
* @param   pUsrData(void*)            A context data which keeps in structure ModelListener_t,
*                                     will pass into this callback function.
* @param   pMdlEvent(ModelEvent_t*)   A pointer of ModelEvent_t structure to indicate event, changed data and model object.
*/
typedef void (*PfnModelListener) (void *pUsrData, ModelEvent_t *pMdlEvent);

//typedef struct IModel_tag IMODEL;  ///< the same with IModel
typedef void (*PfnModelEvtListener) (void *pUsrData, void *pUsrData2, ModelEvtCode_t nEvtCode, u32 dwParam, void *pObject);

/**
* @brief   The free data function prototype for data-model and vector-model
*
* @param   pData(void*)     A pointer of data to be freed.
* @param   pOwner(IBase*)   A pointer of IBase object which is the owner of freed data.
*/
typedef void (*PfnModelFree) (void *pData, IBase *pOwner);

/**
* @brief   Model event structure. It is used as parameter in IMODEL_SendNotify(),
*          and will be passed into the callback function of model listener. This
*          data structure provides elements to indicate which event was happened,
*          the changed data, and the model object which sent this notification.
*/
struct ModelEvent_Tag
{
	ModelEvtCode_t nEvtCode; ///< model event code, reference to mmi_mae_model_events.h
	u32 nParam;             ///< a certain of data, such as index, pointer of structure, pointer of object
	IMODEL *pThisModel;      ///< pointer to this model which sent model event
};

struct MaeModelEvtListenerAddDataInf_t_
{
    void *pUserData1;
    void *pUserData2;
};

/**
* @brief   Model Listener structure. It is used as parameter in IMODEL_AddMdlListener(), IMODEL_CancelMdlListener().
*          This structure should be initilized by MDLLISTENER_INIT(). Ap/object wants to register a listener to a model,
*          shall have this structure first.
* @note    If a model listener structure has already registered to someone model, please do not use it to register to
*          another model before cancel it.
*/
struct ModelListener_Tag
{
	PfnModelListener pMdlListener;	///< a call back function with PfnModelListener prototype
	void *pUsrData;					///< a context data pointer to pass into callback function
	IMODEL *pModel;					///< a model pointer to indicate which model this listener belong to
	ModelListener_t *pNext;			///< next model listener structure
};

struct MdlListener_t_
{
	PfnModelListener pMdlListener;	///< a call back function with PfnModelListener prototype
	PfnModelEvtListener pfnEvtListener;   ///<
	ModelEvtCode_t nEvtCode;
	u32 nMask;
	void *pUsrData;					///< a context data pointer to pass into callback function
    void *pUsrData2;
};



#endif /* __MMI_MAE_MODEL_TYPES_H__ */

