/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      pgl_Utility_Container.h
*
*
* HISTORY
*      2011.10.04       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __PGL_UTILITY_CONTAINER_INC__
#define __PGL_UTILITY_CONTAINER_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "pgl_Utility_Types.h"
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define PGL_LIST_NULL                     0
#define PGL_STACK_NULL                    0
#define PGL_DATA_NODE_NULL                0
/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef pgl_s32 hDataNode;
typedef pgl_s32 hList;
typedef pgl_s32 hStack;

typedef pgl_void (*PGL_ListTraverse_pfn)(pgl_void *pvClientData, pgl_void *pvUserData);
typedef pgl_boolean (*PGL_ListTraverseAndStop_pfn)(pgl_void *pvClientData, pgl_void *pvUserData);

typedef struct Node_t
{
    pgl_boolean isAutoFreeData;
	pgl_void *pData;
	struct Node_t* pNext;
	struct Node_t* pPrev;
} Node_t;

typedef struct List_tag
{
	Node_t *pHead;
	Node_t *pTail;
} List_t;

typedef struct Stack_tag
{
	Node_t *pHead;
} Stack_t;

/*------------------------------------------------------------------------------
Internal Function
-------------------------------------------------------------------------------*/
/*List part*/
hList pgl_List_Create(pgl_void);
pgl_void pgl_List_Destroy(hList hLi);
hDataNode pgl_List_AddTail(hList hLi, pgl_void *pData, pgl_boolean isAutoFreeData);
hDataNode pgl_List_AddHead(hList hLi, pgl_void *pData, pgl_boolean isAutoFreeData);
pgl_void* pgl_List_Find(hList hLi, hDataNode hListNode);
pgl_void pgl_List_Clear(hList hLi);
pgl_void pgl_List_Remove(hList hLi, hDataNode hListNode);
hDataNode pgl_List_Head(hList hLi);
hDataNode pgl_List_Tail(hList hLi);
pgl_void pgl_List_Traverse(hList hLi, PGL_ListTraverse_pfn pfnTraverseCB, pgl_void *pvUserData);
pgl_void pgl_List_TraverseAndStop(hList hLi, PGL_ListTraverseAndStop_pfn pfnTraverseAndStopCB, pgl_void *pvUserData);
pgl_boolean pgl_List_isEmpty(hList hLi);

/*Stack part*/
hStack pgl_Stack_Create(pgl_void);
pgl_void pgl_Stack_Destroy(hStack hStk);
pgl_void pgl_Stack_Clear(hStack hStk);
hDataNode pgl_Stack_Push(hStack hStk, pgl_void *pData);
pgl_void* pgl_Stack_Pop(hStack hStk);
hDataNode pgl_Stack_Top(hStack hStk);
pgl_boolean pgl_Stack_isEmpty(hStack hStk);
hDataNode pgl_Stack_Find(hStack hStk, void* pData);

#endif
