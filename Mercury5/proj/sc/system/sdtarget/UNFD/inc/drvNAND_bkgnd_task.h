#ifndef __DRVNAND_BKGND_TASK_H__
#define __DRVNAND_BKGND_TASK_H__

#include "osdefs.hc"
#include "vm_os.hi"
#include "cus_os_mem.h"
#include "cus_os_sem.h"
#include "cus_os_msg.h"
#include "cus_os_timer.h"

#define NAND_MSG_TYPE_BASE VM_CUS61_BASE

#define NAND_MSG_TOGGLE_BUSY		(NAND_MSG_TYPE_BASE+0x00)
#define NAND_MSG_WEAR_LEVELING		(NAND_MSG_TYPE_BASE+0x01)
#define NAND_MSG_WEAR_LEVELING1		(NAND_MSG_TYPE_BASE+0x02)
#define NAND_MSG_READ_DISTURBANCE	(NAND_MSG_TYPE_BASE+0x03)
#define NAND_MSG_FORCE_WRITE_BACK	(NAND_MSG_TYPE_BASE+0x04)

#define NAND_WEAR_LEVELING_TIMER	1500 // ms
#define NAND_WEAR_LEVELING1_TIMER	1500 // ms
#define NAND_READ_DISTURBANCE_TIMER	1000 // ms
#define NAND_FORCE_WRITE_BACK_TIMER	1000 // ms

extern void drvNAND_BkgndInit(void);
extern void drvNAND_SendMsg2BkgndTask(u16 TypMsg);
extern void drvNAND_BkgndParser(void *pMsgPass);

#endif /* __DRVNAND_BKGND_TASK_H__ */
