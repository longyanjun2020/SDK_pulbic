#ifndef __DRVNAND_BKGND_TASK_H__
#define __DRVNAND_BKGND_TASK_H__

#include "osdefs.hc"
#include "sys_rtk_vmoshi.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "drvNAND_bkgnd_task_message_define__.hi"
};


#define NAND_WEAR_LEVELING_TIMER	1500 // ms
#define NAND_WEAR_LEVELING1_TIMER	1500 // ms
#define NAND_READ_DISTURBANCE_TIMER	1000 // ms
#define NAND_FORCE_WRITE_BACK_TIMER	1000 // ms

extern void drvNAND_BkgndInit(void);
extern void drvNAND_SendMsg2BkgndTask(u16 TypMsg);
extern void drvNAND_BkgndParser(void *pMsgPass);

#endif /* __DRVNAND_BKGND_TASK_H__ */
