/**
 * \file mdl_bat_msg_pub.h
 * Description:  Messages interface for Battery Task
*/

#ifndef __MDL_BAT_MSG_PUB_H__
#define __MDL_BAT_MSG_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "sys_rtk_vmoshi.h"

#include "mdl_bat_itf_pub.h"
#include "mdl_vm_bat_pub.h"

#include "vm_abb_pub.h"
#include "drv_abb_pub.h"
#ifndef __DUAL_BATT_DRV__
#include "api_ati_msg.h"
#endif

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/
/**
 * \brief Union of all messages received or sent by BAT
*/
union BatMsgBody_t
{
    vm_osTimerMsgBody_t     vm_osTimerMsgBody;
    vm_batChargerPlugged_t  vm_batChargerPlugged;
    bat_Alarm_t             vm_batAlarm;
    vm_batEndOfCharge_t     vm_EndOfChargeValue;
    vm_batLevel_t           vm_BatteryLevel;
    vm_batTemperature_t     vm_BatteryTemperature;
    vm_batChargerPlugged_t  vm_ChargerPlugged;
    bat_MeasureMsg_t        batteryMeasure;
    DrvAbbAdcResults_t      adcResults;
    BatID_e                 battid;
    DrvAbbMsgCode_e         eDrvAbbMsgCode;
	vm_batmsg_t             msgbox;
#ifndef __DUAL_BATT_DRV__
	bat_MeasureADCMsg_t		batAdcMeasure;
#endif
#ifndef __DUAL_BATT_DRV__
    api_atCmdPreParser_t    AT_CmdPreParserInd;
#endif
};

/*=============================================================*/
// Local function prototype & definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif  /* __MDL_BAT_MSG_PUB_H__ */






