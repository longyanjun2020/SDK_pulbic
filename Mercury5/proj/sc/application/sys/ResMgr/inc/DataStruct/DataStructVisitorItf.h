/**
* @file DataStructVisitorItf.h
*
* This header file defines the interface of data structure visitor.
*
*/

#ifndef __DATASTRUCTVISITORITF_H__
#define __DATASTRUCTVISITORITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define DS_ACT__STRATEGY_MASK           0x00FF
#define DS_ACT__CUS_MASK                0xFF00

#define DS_COMBINE_RET(_RET_, _CUS_)    ((_RET_) & DS_ACT__STRATEGY_MASK | (((_CUS_) << 8) & DS_ACT__CUS_MASK))
#define DS_SET_CUS_RET(_CUS_)           (((_CUS_) << 8) & DS_ACT__CUS_MASK)
#define DS_GET_STRATEGY_RET(_RET_)      ((_RET_) & DS_ACT__STRATEGY_MASK)
#define DS_GET_CUS_RET(_RET_)           (((_RET_) & DS_ACT__CUS_MASK) >> 8)

#define DS_ACT__STOP                    0x0001
#define DS_ACT__DEL                     0x0002

#define DS__STOP_TRANSVERSE(_RET_)      (_RET_ | DS_ACT__STOP)
#define DS__DEL_ITEM(_RET_)             (_RET_ | DS_ACT__DEL)

#define DS__IS_STOP(_RET_)              (DS_ACT__STOP == (_RET_ & DS_ACT__STOP))
#define DS__IS_DEL(_RET_)               (DS_ACT__DEL == (_RET_ & DS_ACT__DEL))

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum DataStructVisitRet_e_
{
    DS_VISIT_RET__KEEP_AND_CONTINUE = 0,
    DS_VISIT_RET__BAD_PARAMS,
    DS_VISIT_RET__KEEP_AND_STOP = DS_ACT__STOP,
    DS_VISIT_RET__DEL_AND_CONTINUE = DS_VISIT_RET__KEEP_AND_CONTINUE | DS_ACT__DEL,
    DS_VISIT_RET__DEL_AND_STOP = DS_ACT__DEL | DS_ACT__STOP
} DataStructVisitRet_e;

typedef u16 (*DataStructVisitor_DoAction)(void *pCusData, void *pItem);
typedef void (*DataStructVisitor_FreeItem)(void *pCusData, void *pRefItem, void *pFreeItem);

typedef struct DataStructVisitorItf_t_
{
    DataStructVisitor_DoAction DoAction;
    DataStructVisitor_FreeItem Free;
} DataStructVisitorItf_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__DATASTRUCTVISITORITF_H__

