#ifndef __DEV_ACC_PUB_TYPES_H__
#define __DEV_ACC_PUB_TYPES_H__

#include "vm_types.ht"
#include "vm_msgof.hc"

#include "dev_acc_pub_forward.h"

/* Need to consider other drivers */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
opaque_enum(dev_accItfMsgTypes_t_)
{
#include "dev_acc_message_define__.hi"
};

opaque_enum(dev_accPlugId_t_)
{
	HEADSET,
	DATACABLE,
	MEMCARD,
	ACC_MAX
};

opaque_enum(dev_accPlugEvt_t_)
{
	DEV_ACC_HEADSET_IN=1,
	DEV_ACC_HEADSET_OUT,
	DEV_ACC_DATACABLE_IN,
	DEV_ACC_DATACABLE_OUT,
	DEV_ACC_MEMCARD_IN,
	DEV_ACC_MEMCARD_OUT
};

opaque_enum(dev_accBacklightLevel_t_)
{
	DEV_ACC_BL_LEVEL0 = 0,
	DEV_ACC_BL_LEVEL1,
	DEV_ACC_BL_LEVEL2,
	DEV_ACC_BL_LEVEL3,
	DEV_ACC_BL_LEVEL4,
	DEV_ACC_BL_LEVEL5,
	DEV_ACC_BL_LEVEL6,
	DEV_ACC_BL_MAX /* Shall not be larger than 65535 (u16) */
};

opaque_enum(dev_PowerOnCause_t_)
{
    DEV_PWR_ON_NONE=0,
    DEV_PWR_ON_NORMAL,
    DEV_PWR_ON_CHARGER,
    DEV_PWR_ON_ALARM,
    DEV_PWR_ON_RESET,
    DEV_PWR_ON_POWERCUT,
    DEV_PWR_ON_MAX
};

struct dev_accPlugInd_t_
{
	dev_accPlugEvt_t  PlugEvt;
};

struct dev_accPlugStatus_t_
{
  dev_accPlugEvt_t Headset_status;
  dev_accPlugEvt_t Datacable_status;
  dev_accPlugEvt_t Memcard_status;
};

#endif /* __DEV_ACC_PUB_TYPES_H__ */
