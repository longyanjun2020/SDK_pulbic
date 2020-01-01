#ifndef __DEV_ACC_PUB_FORWARD_H__
#define __DEV_ACC_PUB_FORWARD_H__

#include "vm_types.ht"

opaque_enum(dev_accItfMsgTypes_t_);
typedef enum dev_accItfMsgTypes_t_ dev_accItfMsgTypes_t;

opaque_enum(dev_accPlugId_t_);
typedef enum dev_accPlugId_t_ dev_accPlugId_t;

opaque_enum(dev_accPlugEvt_t_);
typedef enum dev_accPlugEvt_t_ dev_accPlugEvt_t;

opaque_enum(dev_accBacklightLevel_t_);
typedef enum dev_accBacklightLevel_t_ dev_accBacklightLevel_t;

opaque_enum(dev_PowerOnCause_t_);
typedef enum dev_PowerOnCause_t_ dev_PowerOnCause_t;

typedef struct dev_accPlugInd_t_ dev_accPlugInd_t;

typedef struct dev_accPlugStatus_t_ dev_accPlugStatus_t;

#endif /* __DEV_ACC_PUB_H__ */

