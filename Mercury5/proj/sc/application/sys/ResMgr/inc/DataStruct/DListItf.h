/**
* @file DListItf.h
*
* This header file defines the interfaces of double link list.
*
*/

#ifndef __DLISTITF_H__
#define __DLISTITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DataCtnrItf.h"
#include "IteratorItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct DListNode_t_
{
    struct DListNode_t_ *pNext;
    struct DListNode_t_ *pPrev;
    void *pData;
} DListNode_t;

typedef struct DListPosNode_t_
{
    struct DListPosNode_t_ *pNext;
    struct DListPosNode_t_ *pPrev;
    DListNode_t *pNode;
    DataCtnrHdl_t pDListHdl;
    bool bValid;
} DListPosNode_t;

typedef struct DList_t_
{
    DataCtnr_t dataCtnr;
    DListPosNode_t *pPosHandles;
    DListNode_t *pHead;
} DList_t;

typedef enum DListIteratorType_e_
{
    DLIST_ITERATOR_TYPE__NONE,
    DLIST_ITERATOR_TYPE__FORWARD,
    DLIST_ITERATOR_TYPE__BACKWARD,
    DLIST_ITERATOR_TYPE__NUM
} DListIteratorType_e;

typedef struct DListIterator_t_
{
    Iterator_t tIterator;
    DListIteratorType_e eType;
    DList_t *pDList;
    DListPosNode_t *pPosNode;
} DListIterator_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

DList_t* DList_Init(void);
void DList_Uninit(DList_t* pDList);
bool DList_AddItemToHead(DataCtnrHdl_t pHandle, void *pItem);
bool DList_AddItemToTail(DataCtnrHdl_t pHandle, void *pItem);
void* DList_GetFirstItem(DataCtnrHdl_t pHandle);
void* DList_GetLastItem(DataCtnrHdl_t pHandle);
DataCtnrPosHdl_t DList_CreatePosHdl(DataCtnrHdl_t pHandle);
bool DList_DestroyPosHdl(DataCtnrPosHdl_t pPosHandle);
bool DList_SetPosToHead(DataCtnrPosHdl_t pPosHandle);
bool DList_SetPosToTail(DataCtnrPosHdl_t pPosHandle);
bool DList_MoveToNextPos(DataCtnrPosHdl_t pPosHandle);
bool DList_MoveToPrevPos(DataCtnrPosHdl_t pPosHandle);
void* DList_GetCurItemByPos(DataCtnrPosHdl_t pPosHandle);
void* DList_GetNextItemByPos(DataCtnrPosHdl_t pPosHandle);
void* DList_GetPrevItemByPos(DataCtnrPosHdl_t pPosHandle);
void* DList_GetItemByIdx(DataCtnrHdl_t pHandle, u16 idx);
bool DList_FindItem(DataCtnrHdl_t pHandle, DataCtnrPosHdl_t pPosHandle, void *pItem);
bool DList_RemoveItem(DataCtnrHdl_t pHandle, void *pItem);
bool DList_RemoveItemByIdx(DataCtnrHdl_t pHandle, u16 idx);
void DList_RemoveAllItem(DataCtnrHdl_t pHandle);
void DList_RemoveAllItemEx(DataCtnrHdl_t pHandle, DataCtnr_FreeData FreeItem);
void* DList_RemoveFirstItem(DataCtnrHdl_t pHandle);
void* DList_RemoveLastItem(DataCtnrHdl_t pHandle);
u16 DList_GetItemNum(DataCtnrHdl_t pHandle);
Iterator_t* DList_GetIterator(DataCtnrHdl_t pHandle, DListIteratorType_e eType);
void DList_FreeIterator(Iterator_t *pIterator);

#endif //__DLISTITF_H__

