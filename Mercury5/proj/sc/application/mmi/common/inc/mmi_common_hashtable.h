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
* @file    mmi_common_hashtable.h
* @version
* @brief
*
*/

#ifndef __MMI_COMMON_HASHTABLE_H__
#define __MMI_COMMON_HASHTABLE_H__

#define HASHTABLE_LOAD_FACTOR 0.65
#define HASHTABLE_INDEX_OF(pHashTable, nHash) nHash % pHashTable->nLength

struct entry
{
    void *pKey;
    void *pValue;
    unsigned int nHash;
    struct entry *pNext;	
};

typedef struct Hashtable_tag
{
    struct entry **ppEntries;
    unsigned int nLength;
    unsigned int nCount;
    unsigned int nLoadLimit;
    unsigned int nPrimeIndex;
    unsigned int (*pHashFunc)(void*);
    unsigned int (*pEqualFunc)(void*, void*);
	unsigned int nEntryMemHandle;
	void *pEntryMem;
}Hashtable_t;

Hashtable_t* hashtable_create(unsigned int nMinSize, unsigned int (*pHashFunc)(void *), unsigned int (*pEqualFunc)(void *, void *));
Hashtable_t* hashtable_createEx(unsigned int nInitialSize, unsigned int nMaxSize, unsigned int (*pHashFunc)(void *), unsigned int (*pEqualFunc)(void*, void *));
void hashtable_destroy(Hashtable_t *pHashTable);

int hashtable_insert(Hashtable_t *pHashTable, void *pKey, void *pValue);
void* hashtable_update(Hashtable_t *pHashTable, void *pKey, void *pValue);
void* hashtable_search(Hashtable_t *pHashTable, void *pKey);
void* hashtable_remove(Hashtable_t *pHashTable, void *pKey);
unsigned int hashtable_size(Hashtable_t *pHashTable);

#endif/* __MMI_COMMON_HASHTABLE_H__ */
