/**
 *
 * @file    ven_prim.h
 * @brief   This file defines the vendor SDK v2 primitives
 *
 * @author  Jorena.Ku
 * @version $Id: ven_prim.h 16691 2008-11-19 08:01:38Z steve.lee $
 *
 */


#ifndef __VEN_PRIM_H__
#define __VEN_PRIM_H__

#include "cus_msg.hc"
#include "ven_primitem.h"

#define VEN_PRIM_BASE     (VM_VENSDK_BASE)

#define MAKE_PRIM_ITEM(_Name, _Parser)  _Name##_IDX

typedef enum
{
    VEN_IN_PRIM_ITEMS
    VEN_OUT_PRIM_ITEMS
    VEN_PRIM_NUMBER
} Ven_PrimIdx_t;

#undef MAKE_PRIM_ITEM


#define MAKE_PRIM_ITEM(_Name, _Parser)  _Name = VEN_PRIM_BASE + _Name##_IDX

typedef enum
{
    VEN_IN_PRIM_ITEMS
    VEN_OUT_PRIM_ITEMS
} Ven_PrimDef_t;

#define Ven_MsgDef_t Ven_PrimDef_t

#undef MAKE_PRIM_ITEM


#define VEN_V2_PRIM_START   VEN_PRIM_BASE
#define VEN_V2_PRIM_END     (VEN_PRIM_BASE + VEN_PRIM_NUMBER - 1)
#define VEN_V2_PRIM_NUMBER  VEN_PRIM_NUMBER

#endif /* __VEN_PRIM_H__ */


