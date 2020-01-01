#ifndef __M_UTILITY_LIST_H__
#define __M_UTILITY_LIST_H__
/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Utility_list.h
 *
 *
 * HISTORY
 *      2009.09.24       Chunwei Wang         Initial Version
 *
 *-----------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"
#include "mgl_Core_Types.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef struct T_LIST_ELEMENT_TAG T_LIST_DATA, *T_LIST_ELEMENT_PTR;
struct T_LIST_ELEMENT_TAG
{
    AABBox3D aabox;
    mgl_u32 zOrder;
};

typedef struct T_LIST_TAG T_LIST_NODE, *T_LIST_PTR;
struct T_LIST_TAG
{
    T_LIST_ELEMENT_PTR    ptElement;
    T_LIST_PTR   ptPrev;
    T_LIST_PTR   ptNext;
};

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif

mgl_void mgl_List_Push_End(T_LIST_ELEMENT_PTR  pElement);
mgl_void mgl_List_Push_Begin(T_LIST_ELEMENT_PTR  pElement);
mgl_void mgl_List_Insert_After(T_LIST_PTR pList, T_LIST_ELEMENT_PTR  pElement);
mgl_void mgl_List_Insert_Before(T_LIST_PTR pList, T_LIST_ELEMENT_PTR  pElement);
mgl_void mgl_List_Erase(T_LIST_PTR pList);
mgl_void mgl_List_EraseAll(mgl_void);
mgl_u32 mgl_List_GetSize(mgl_void);
T_LIST_PTR mgl_List_GetFirstNode(mgl_void);

#ifdef  __cplusplus
}
#endif

#endif /* __M_UTILITY_LIST_H__ */

