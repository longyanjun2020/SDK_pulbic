
/**
 * \file    mmi_mae_battery.h
 * \brief   The document describes the interface of IBATTERY
 * \author  christoph.kuo@mstarsemi.com
 */
#ifndef __MMI_MAE_BATTERY_H__
#define __MMI_MAE_BATTERY_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_handler.h"
#include "mmi_mae_model_forward.h"
#include "mmi_mae_battery_forward.h"
#include "mmi_mae_clstbl.h"

   

/**
 * IIBATTERY Interfaces
 */
#define INHERIT_IBattery(IName) \
    INHERIT_IHandler(IName); \
    MAE_Ret     (*GetBattStatus)							(IName *, MAEBattStatus_e* pStatus); \
    MAE_Ret	    (*GetChargerStatus)							(IName *, MAEChargerStatus_e* pStatus); \
    MAE_Ret		(*ExternalPowerExist)						(IName *, boolean* pbExtPower); \
    MAE_Ret		(*GetChargerType)							(IName *, MAEChargerType_e* pType); \
    MAE_Ret		(*IsPowerOnAllowed)							(IName *, boolean* pbAllow); \
    MAE_Ret		(*IsPowerOnByCharger)						(IName *, boolean* pbPowerOn); \
    MAEBatteryLevel_e (*GetBattLevel)                       (IName *, MAEBatteryID_e BatID); \
    MAE_Ret     (*AddMdlListener)                           (IName *, ModelListener_t *MdlLsnPtr); \
    u16         (*GetBattVoltage)                           (IName *, MAEBatteryID_e BatID); \
    MAE_Ret		(*ChangeBattery)							(IName *, MAEBatteryID_e BatID); \
    MAE_Ret		(*GetBatteryPresence)						(IName *, MAEBatteryID_e *BatID); \
    MAE_Ret		(*GetBattNumber)							(IName *, u8 *nBatNum); \
    MAE_Ret     (*NotifyBattLevel)                          (IName *); \
    MAE_Ret     (*CheckLowBattery)                          (IName *); \
    MAE_Ret     (*IsBatteryExist)                          (IName *,boolean *pbBatExist)

DEFINE_INTERFACE(IBattery);


/**
* IBATTERY_QueryInterface
* @brief	This function queries another interface from an IBattery object.
*          It will return an interface object which you want to query if successful.
*
* @param   (IBattery*)pICntlr        A pointer of IBattery interface object.
* @param   (MAE_IId)id               An interface id to be queried.
* @param   (void**)pp                A pointer of void pointer to retrieve an interface object which you want to query.
* @param   (IBase*)pOwner            Shall be an IBase interface object to keep the return object.
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
*
* @note    Only support IID_IBATTERY and IID_HANDLER.
*/
#define IBATTERY_QueryInterface(pICntlr,id,pp,pOwner)				GET_FUNCTBL((pICntlr),IBattery)->QueryInterface(pICntlr,id,pp,pOwner)

/**
* IBATTERY_GetBattStatus
* @brief   This function identifies the current Battery status
*
* @param   (IBattery*)pICntlr      A pointer of IBattery interface object.
* @param   (MAEBattStatus*)p1[out] Returned battery status
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_BAD_PARAM       Failed. Bad parameters.
* @retval  MAE_RET_NOT_READY       Failed. Driver is not ready yet.
*
* @note    MAE_BATTSTATUS_POWERDOWN: Bettery level too low to keep handset operating. Power down required.
*          MAE_BATTSTATUS_LOW: Battery needs to be charged
*          MAE_BATTSTATUS_NORMAL: Battery is within operating level
*          MAE_BATTSTATUS_UNRECOGNIZED: Unrecognized battery status
*          MAE_BATTSTATUS_UNKNOWN: Unknown error
*/
#define IBATTERY_GetBattStatus(pICntlr,p1)					GET_FUNCTBL((pICntlr),IBattery)->GetBattStatus(pICntlr,p1)

/**
* IBATTERY_GetChargerStatus
* @brief   This function identifies the current Charger status
*
* @param   (IBattery*)pICntlr         A pointer of IBattery interface object.
* @param   (MAEChargerStatus*)p1[out] Returned charger status
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_BAD_PARAM       Failed. Bad parameters.
* @retval  MAE_RET_NOT_READY       Failed. Driver is not ready yet.
*
* @note    MAE_CHGSTATUS_NO_CHARGER: No Charger inserted
*          MAE_CHGSTATUS_CHARGING: Charging normally
*          MAE_CHGSTATUS_FULLY_CHARGED: Fully Charged
*          MAE_CHGSTATUS_BADCHARGER: Unknown Charger
*          MAE_CHGSTATUS_UNKNOWN: Unrecognized status
*/
#define IBATTERY_GetChargerStatus(pICntlr,p1)				GET_FUNCTBL((pICntlr),IBattery)->GetChargerStatus(pICntlr,p1)

/**
* IBATTERY_ExternalPowerExist
* @brief   This function identifies whether an external power source exists or not
*
* @param   (IBattery*)pICntlr      A pointer of IBattery interface object.
* @param   (boolean*)p1[out]       Returned boolean
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_BAD_PARAM       Failed. Bad parameters.
*
* @note    TRUE: External Power source exist
*          FALSE: No External Power source
*/
#define IBATTERY_ExternalPowerExist(pICntlr,p1)				GET_FUNCTBL((pICntlr),IBattery)->ExternalPowerExist(pICntlr,p1)

/**
* IBATTERY_GetChargerType
* @brief   This function identifies the current Charger Type
* @param   (IBattery*)pICntlr       A pointer of IBattery interface object.
* @param   (MAEChargerType*)p1[out] Returned charger type
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_BAD_PARAM       Failed. Bad parameters.
* @retval  MAE_RET_NOT_READY       Failed. Driver is not ready yet.
*
* @note    MAE_CHARGERTYPE_INVALID: Invalid/Unknown Charger type
*          MAE_CHARGERTYPE_STANDARD: Standard Wall Charger
*          MAE_CHARGERTYPE_USB: Normal USB Charger
*          MAE_CHARGERTYPE_USB_LOW: Low current USB Charger
*/
#define IBATTERY_GetChargerType(pICntlr,p1)				    GET_FUNCTBL((pICntlr),IBattery)->GetChargerType(pICntlr,p1)

/**
* IBATTERY_IsPowerOnAllowed
* @brief   This function identifies whether the battery has enough power for handset to power on
* @param   (IBattery*)pICntlr      A pointer of IBattery interface object.
* @param   (boolean*)p1[out]       Returned boolean
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_BAD_PARAM       Failed. Bad parameters.
*
* @note    TRUE: Allowed
*          FALSE: Disallowed
*/
#define IBATTERY_IsPowerOnAllowed(pICntlr,p1)				GET_FUNCTBL((pICntlr),IBattery)->IsPowerOnAllowed(pICntlr,p1)

/**
* IBATTERY_IsPowerOnByCharger
* @brief   This function identifies whether the handset is powered on due to insertion of an external
//          power source
* @param   (IBattery*)pICntlr      A pointer of IBattery interface object.
* @param   (boolean*)p1[out]       Returned boolean
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_BAD_PARAM       Failed. Bad parameters.
*
* @note    TRUE: Power on by charger
*          FALSE: Power on by user
*/
#define IBATTERY_IsPowerOnByCharger(pICntlr,p1)             GET_FUNCTBL((pICntlr),IBattery)->IsPowerOnByCharger(pICntlr,p1)

/**
* IBATTERY_GetBattLevel
* @brief   This function returns current Battery Level
* @param   (IBattery*)pICntlr       A pointer of IBattery interface object.
* @param   (MAEBatteryID_e*)p1[in]       Battery ID (MAE_BATT_MASTER/MAE_BATT_SLAVE)

* @retval  MAEBatteryLevel  Returned battery level
*
* @note    MAE_BATT_DUMMY_LEVEL       Uninitialized Dummy level
*	       MAE_BATT_TOO_LOW_FOR_COMM  Battery level too low. Handset has to be turned off
*	       MAE_BATT_LOW_BATTERY       Battery level low. Handset should warn the user
*	       MAE_BATT_LEVEL_0           Battery level 0
*	       MAE_BATT_LEVEL_1           Battery level 1
*	       MAE_BATT_LEVEL_2           Battery level 2
*	       MAE_BATT_LEVEL_3           Battery level 3
*	       MAE_BATT_LEVEL_4           Battery level 4
*	       MAE_BATT_LEVEL_5           Battery level 5
*	       MAE_BATT_LEVEL_6           Battery level 6
*	       MAE_BATT_LEVEL_7           Battery level 7
*/
#define IBATTERY_GetBattLevel(pICntlr,p1)                      GET_FUNCTBL((pICntlr),IBattery)->GetBattLevel(pICntlr,p1)

/**
* IBATTERY_AddMdlListener
* @brief   This function registers a listener to this IBattery object.
*
* @param   (IBattery*)pICntlr    A pointer of IBattery interface object.
* @param   (ModelListener_t*)p1  A pointer to ModelListener_t sturcture that will register to this IBattery object.
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
* @retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
#define IBATTERY_AddMdlListener(pICntlr,p1)                 GET_FUNCTBL((pICntlr),IBattery)->AddMdlListener(pICntlr,p1)

/**
* IBATTERY_GetBattVoltage
* @brief   This function returns current Battery voltage
* @param   (IBattery*)pICntlr       A pointer of IBattery interface object.
* @param   (MAEBatteryID_e*)p1[in]       Battery ID (MAE_BATT_MASTER/MAE_BATT_SLAVE)
*
* @retval  u16  Returned battery voltage
*
* @note    Actual u16 voltage number
*/
#define IBATTERY_GetBattVoltage(pICntlr,p1)                    GET_FUNCTBL((pICntlr),IBattery)->GetBattVoltage(pICntlr,p1)

/**
* IBATTERY_ChangeBattery
* @brief   This function sets current Battery ID
* @param   (IBattery*)pICntlr       A pointer of IBattery interface object.
* @param   (MAEBatteryID_e*)p1[in]       Battery ID (MAE_BATT_MASTER/MAE_BATT_SLAVE)
*
* @retval MAE_RET_SUCCESS         If successful.
* @retval MAE_RET_NOT_READY      Battery Srv is already terminated.
* @retval MAE_RET_BAD_PARAM     IBattery is NULL.
*
* @note   For dual battery to set battery by user
*/
#define IBATTERY_ChangeBattery(pICntlr,p1)                    GET_FUNCTBL((pICntlr),IBattery)->ChangeBattery(pICntlr,p1)

/**
* IBATTERY_GetBatteryPresence
* @brief   This function gets current Battery ID
* @param   (IBattery*)pICntlr       A pointer of IBattery interface object.
* @param   (MAEBatteryID_e*)p1[out]       Battery ID (MAE_BATT_MASTER/MAE_BATT_SLAVE)
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
* @retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
#define IBATTERY_GetBatteryPresence(pICntlr,p1)                    GET_FUNCTBL((pICntlr),IBattery)->GetBatteryPresence(pICntlr,p1)

/**
* IBATTERY_GetBattNumber
* @brief   This function gets current Battery number
* @param   (IBattery*)pICntlr       A pointer of IBattery interface object.
* @param   (u8*)p1[out]       Current battery number 
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
* @retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
#define IBATTERY_GetBattNumber(pICntlr,p1)                    GET_FUNCTBL((pICntlr),IBattery)->GetBattNumber(pICntlr,p1)

/**
* IBATTERY_NotifyBattLevel
* @brief   This function to send notification for current battery level
* @param   (IBattery*)pICntlr       A pointer of IBattery interface object.
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_BAD_PARAM       Failed. Bad parameters.
*
* @note    Used for ap to request for battery level notification
*/
#define IBATTERY_NotifyBattLevel(pICntlr)                    GET_FUNCTBL((pICntlr),IBattery)->NotifyBattLevel(pICntlr)

/**
* IBATTERY_CheckLowBattery
* @brief   Force send notify to mmi if battery is low when executed
* @param   (IBattery*)pICntlr       A pointer of IBattery interface object.
*
* @retval  MAE_RET_SUCCESS         Successfully.
*
* @note    Used for ap to request for low battery level notification
*/
#define IBATTERY_CheckLowBattery(pICntlr)                    GET_FUNCTBL((pICntlr),IBattery)->CheckLowBattery(pICntlr)

/**
* IBATTERY_IsBatteryExist
* @brief   This function to get battery exist or not
* @param   (IBattery*)pICntlr       A pointer of IBattery interface object.
* @param   (boolean*)p1[out]       Returned boolean
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_NOT_READY       Battery Srv is already terminated.
* @retval  MAE_RET_NOT_SUPPORTED   Not support charger power on without battery
*
* @note    Used to get battery exist or not
*/
#define IBATTERY_IsBatteryExist(pICntlr,p1)                    GET_FUNCTBL((pICntlr),IBattery)->IsBatteryExist(pICntlr,p1)


/**
 * Functions
 */
MAE_Ret MAEBattery_CreateInstance(MAE_ClsId nId, void **ppObj);

#endif /*__MAE_BATTERY_H__ */
