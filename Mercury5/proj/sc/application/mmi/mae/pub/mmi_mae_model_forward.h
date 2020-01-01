/**
 * @file mmi_mae_model_forward.h
 *
 * 
 *
 * @version $Id: mmi_mae_model_forward.h $
 */

#ifndef __MMI_MAE_MODEL_FORWARD_H__
#define __MMI_MAE_MODEL_FORWARD_H__

/**
* @brief   Model event structure. It is used as parameter in IMODEL_SendNotify(),
*          and will be passed into the callback function of model listener. This
*          data structure provides elements to indicate which event was happened,
*          the changed data, and the model object which sent this notification.
*/
typedef struct ModelEvent_Tag ModelEvent_t;

typedef struct MaeModelEvtListenerAddDataInf_t_ MaeModelEvtListenerAddDataInf_t;

typedef struct ModelListener_Tag ModelListener_t;

typedef struct MdlListener_t_ MdlListener_t;

typedef struct Model_t_ Model_t;

#endif //__MMI_MAE_MODEL_FORWARD_H__

