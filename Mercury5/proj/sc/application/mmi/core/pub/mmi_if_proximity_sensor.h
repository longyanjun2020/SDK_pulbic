/**
* @file    mmi_if_paisensor.h
* @brief   
* @author  mark.yang@mstarsemi.com
* 
* @version $Id: mmi_if_paisensor.h 15893 2008-11-04 14:51:24Z mark.yang $
*/
#ifndef __MMI_IF_PAISENSOR_H__
#define __MMI_IF_PAISENSOR_H__

#include "mmi_mae_interface_def.h"
#include "mmi_proximity_sensor_msgdef.h"

void mmi_paisensor_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_Infrared_ind_if(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_PAISENSOR_H__ */
