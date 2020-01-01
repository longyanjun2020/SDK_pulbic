////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_base_util.h
* @version
* @brief   base utility header file
*
*/

#ifndef __MMI_BASE_UTIL_H__
#define __MMI_BASE_UTIL_H__

#include "mmi_mae_log.h"
#include "mmi_mae_common_def.h"

typedef enum ArrayType_e_
{
    TYPE_ARRAY = 0,
    TYPE_VECTOR
} ArrayType_e;

#define ARRAY_STEP 10
typedef void (*PfnArrayItemFree) (void *pItemData, void *pUseData);
typedef void (*PfnArrayChangedCb) (void *pArray, void *pUseData);

typedef struct
{
    PfnArrayChangedCb pfnChange;    //the callback function for the Array changed
    void *pUseData;        //the data pointer for     
}ArrayChangeCb_t;

typedef struct
{
    PfnArrayItemFree pfnFree;    //the callback function for the Array changed
    void *pUseData;        //the data pointer for     
}ArrayFreeCb_t;

typedef struct ArrayClass_tag
{
    ArrayType_e     nType;            //type(array or vector)    
    u32  nItemSize;     //the byte size of each item
    u32  nValidItems;   //number of valid items in array
    u32  nTotalItems;   //Total number of allocation items(valid items and free items) in array
    u32  nEnsureItems;  //number of ensure items in array
    u32  nGrowBy;       //grow-by size(number of items) for subsequent allocations
    ArrayFreeCb_t  FreeCbStruct;  //the free function for the member of the items
    ArrayChangeCb_t    ChangCbStruct;    //the struct use to the Array changed
    void *pItemArray;   //pointer to array of items
}ArrayClass_t;

ArrayClass_t* ArrayNew(u32 nItemSize);
void ArrayRelease(ArrayClass_t* pArray);

boolean ArraySetGrowStep(ArrayClass_t* pArray, u32 nGrowBy);
boolean ArrayInsertItem(ArrayClass_t* pArray, u32 nIndex, void *pItem);
boolean ArrayAddItem(ArrayClass_t* pArray, void *pItem);
boolean ArrayDeleteItem(ArrayClass_t* pArray, u32 nIndex);
boolean ArrayItemReplace(ArrayClass_t* pArray, u32 nIndex, void* pItem);
void ArrayDeleteAll(ArrayClass_t* pArray);
u32 ArrayGetItemSize(ArrayClass_t* pArray);
void* ArrayGetItem(ArrayClass_t* pArray, u32 nIndex);
boolean ArrayEnsureCapacity(ArrayClass_t* pArray,u32 nRequired);
ArrayFreeCb_t ArraySetPfnFree(ArrayClass_t* pArray, PfnArrayItemFree pfnFree, void* pUseData);
void ArraySetPfnChange(ArrayClass_t* pArray, PfnArrayChangedCb pfnChange, void* pUseData);
u32 ArrayGetItemCount(ArrayClass_t* pArray);

typedef ArrayClass_t VectorClass_t;
#define PfnVectorItemFree PfnArrayItemFree
#define PfnVectorChangedCb PfnArrayChangedCb

#define VectorRelease(a) ArrayRelease(a)
#define VectorSetGrowStep(a,b) ArraySetGrowStep(a,b)
#define VectorDeleteItem(a,b) ArrayDeleteItem(a,b)
#define VectorItemReplace(a,b,c) ArrayItemReplace(a,b,c)
#define VectorDeleteAll(a) ArrayDeleteAll(a)
#define VectorEnsureCapacity(a,b) ArrayEnsureCapacity(a,b)
#define VectorSetPfnFree(a,b,c) ArraySetPfnFree(a,b,c)
#define VectorSetPfnChange(a,b,c) ArraySetPfnChange(a,b,c)
#define VectorGetItemCount(a) ArrayGetItemCount(a)

VectorClass_t* VectorNew(void);
boolean VectorInsertItem(VectorClass_t* pVector, u32 nIndex, void *pItem);
boolean VectorAddItem(VectorClass_t* pVector, void *pItem);
void* VectorGetItem(VectorClass_t* pVector, u32 nIndex);


#endif //__MMI_BASE_UTIL_H__
