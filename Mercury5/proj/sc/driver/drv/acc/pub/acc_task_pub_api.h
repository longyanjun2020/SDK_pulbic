/**
 * \file acc_task_pub_api.h
 * Description:  acc task public api
*/

#ifndef __ACC_TASK_PUB_API_H__
#define __ACC_TASK_PUB_API_H__

#include "vm_types.ht"
#include "acc_task_pub_forward.h"
#include "drv_vm_io_forward.h"

u16 dev_GetDeviceInfo(dev_DeviceInfoType_t deviceType, u8 id, char *pStr, u16 maxLen);
void dev_AtWcusSendOut(tAtCmdFuncParam * ptAtCmdFuncParam, vm_ioPort_e portId);
void dev_SendRspExt(u8 sendRes, vm_ioPort_e portId);
u8   dev_FactoryCmdParser(void* pMessage);
void dev_accInit(void);

void dev_FacAtCmdFunc12_Rsp(u8 type, s8 Status);

#endif  /* __ACC_TASK_PUB_API_H__ */
