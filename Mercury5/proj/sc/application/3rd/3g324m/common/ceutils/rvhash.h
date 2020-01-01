#if (0)
******************************************************************************
Filename:
Description:
******************************************************************************
                Copyright (c) 2000 RADVision Inc.
************************************************************************
NOTICE:
This document contains information that is proprietary to RADVision LTD.
No part of this publication may be reproduced in any form whatsoever
without written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
******************************************************************************
$Revision:$
$Date:$
$Author: S. Cipolli$
******************************************************************************
#endif
#ifndef RV_HASH_H
#define RV_HASH_H

#include <stddef.h>
#include "rvtypes.h"
#include "rvptrvector.h"
#include "rvhashu.h"
#include "rvassert.h"

/*
RvHash Method Prototypes:
    RvHash(K,T)*    rvHashConstruct(K, T)(RvHash(K,T) *thisPtr, size_t n, size_t (*hasher)(const K*),
	                                      void* nodeAllocator, void* bucketAllocator);
    void            rvHashDestruct(K, T)(RvHash(K,T) *thisPtr);
    size_t          rvHashSize(h)(RvHash(K,T) *thisPtr);
    void            rvHashResize(K, T)(RvHash(K,T) *thisPtr, size_t n);
    void            rvHashClear(K, T)(RvHash(K,T) *thisPtr);
    RvHashIter(K,T) rvHashInsertUnique(K, T)(RvHash(K,T) *thisPtr, const K* key, T* data);
    RvHashIter(K,T) rvHashInsertEqual(K, T)(RvHash(K,T) *thisPtr, const K* key, T* data);
    void            rvHashErase(K, T)(RvHash(K,T) *thisPtr, RvHashIter(K,T) i);
    void            rvHashEraseKey(K, T)(RvHash(K,T) *thisPtr, const K* key);
    T*              rvHashFind(K, T)(RvHash(K,T) *thisPtr, const K* key);
    RvHashIter(K,T) rvHashFindIter(K, T)(RvHash(K,T) *thisPtr, const K* key);
    RvHashIter(K,T) rvHashBegin(K, T)(RvHash(K,T) *thisPtr);
    RvHashIter(K,T) rvHashEnd(K, T)(RvHash(K,T) *thisPtr);
    size_t          rvHashGetNodeSize(K,T);

RvHashIter Method Prototypes:
    RvHashIter(K, T)* rvHashIterConstructCopy(K, T)(RvHashIter(K, T) *thisPtr, const RvHashIter(K, T)* s, void* a);
    void              rvHashIterDestruct(K, T)(RvHashIter(K, T) *thisPtr);
    void*          rvHashIterGetAllocator(K, T)(RvHashIter(K, T) *thisPtr);
    void              rvHashIterSwap(K, T)(RvHashIter(K, T) *a,RvHashIter(K, T) *b);
    RvBool            rvHashIterEqual(K, T)(const RvHashIter(K, T) *a,const RvHashIter(K, T) *b);
    void              rvHashIterCopy(K, T)(RvHashIter(K, T) *a,RvHashIter(K, T) *b);
    RvHashIter(K,T)   rvHashIterNext(K, T)(RvHashIter(K, T) this);
    const K*          rvHashIterKey(K, T)(RvHashIter(K, T)  this);
    T*                rvHashIterData(K, T)(RvHashIter(K, T) this);
*/


/************************************************************************/
/* Declare																*/
/************************************************************************/

#define rvDeclareHash(K, T)	\
	typedef struct _RvHashNode##K##T##_ { \
		K key; \
		T data;	\
		size_t index; \
		struct _RvHashNode##K##T##_* next; \
	} _RvHashNode##K##T; \
	typedef _RvHashNode##K##T* _RvHashNodePtr##K##T; \
	_RvHashNodePtr##K##T* _RvHashNodePtr##K##T##ConstructCopy(_RvHashNodePtr##K##T* d, const _RvHashNodePtr##K##T* s, void* a); \
	void _RvHashNodePtr##K##T##Destruct(_RvHashNodePtr##K##T* i); \
	_RvHashNode##K##T* _RvHashNodePtr##K##T##Copy(_RvHashNodePtr##K##T* d, const _RvHashNodePtr##K##T* s); \
	RvBool _RvHashNodePtr##K##T##Equal(const _RvHashNodePtr##K##T* a, const _RvHashNodePtr##K##T* b); \
	void _RvHashNodePtr##K##T##Swap(_RvHashNodePtr##K##T* a, _RvHashNodePtr##K##T* b); \
	struct _RvHash##K##T##_; \
	typedef struct { \
		struct _RvHash##K##T##_ *hash; \
		_RvHashNode##K##T *node; \
	} _RvHashIter##K##T; \
	_RvHashIter##K##T* _RvHashIter##K##T##ConstructCopy(_RvHashIter##K##T* d, const _RvHashIter##K##T* s, void* a); \
	void _RvHashIter##K##T##Destruct(_RvHashIter##K##T* i); \
	_RvHashIter##K##T* _RvHashIter##K##T##Copy(_RvHashIter##K##T* d, const _RvHashIter##K##T* s); \
	RvAlloc* _RvHashIter##K##T##GetAllocator(_RvHashIter##K##T* iter); \
	RvBool _RvHashIter##K##T##Equal(const _RvHashIter##K##T* a, const _RvHashIter##K##T* b); \
	void _RvHashIter##K##T##Swap(_RvHashIter##K##T* a, _RvHashIter##K##T* b); \
	_RvHashIter##K##T _RvHashIter##K##T##Next(_RvHashIter##K##T iter); \
	const K *_RvHashIter##K##T##Key(_RvHashIter##K##T iter); \
	T *_RvHashIter##K##T##Data(_RvHashIter##K##T iter); \
	/* rvDeclarePair(_RvHashIter##K##T, _RvHashIter##K##T) \
	typedef RvPair(_RvHashIter##K##T, _RvHashIter##K##T) _RvHashIterPair##K##T; */ \
	typedef struct _RvHash##K##T##_ { \
		RvPtrVector buckets; \
		size_t (*hasher)(const K*); \
		size_t size; \
		RvAlloc *allocator; \
	} _RvHash##K##T; \
	_RvHash##K##T* _RvHash##K##T##Construct(_RvHash##K##T* h, size_t n, \
	  size_t (*hasher)(const K*), RvAlloc *nodeAllocator, RvAlloc *bucketAllocator); \
	void _RvHash##K##T##Clear(_RvHash##K##T* h); \
	void _RvHash##K##T##Destruct(_RvHash##K##T* h); \
	_RvHashIter##K##T _RvHash##K##T##Begin(_RvHash##K##T *h); \
	_RvHashIter##K##T _RvHash##K##T##End(_RvHash##K##T *h); \
	void _RvHash##K##T##Resize(_RvHash##K##T* h, size_t n); \
	_RvHashIter##K##T _RvHash##K##T##InsertUnique(_RvHash##K##T* h, const K* key, T* data); \
	_RvHashIter##K##T _RvHash##K##T##InsertEqual(_RvHash##K##T* h, const K* key, T* data); \
	_RvHashIter##K##T _RvHash##K##T##Erase(_RvHash##K##T* h, _RvHashIter##K##T i); \
	void _RvHash##K##T##EraseKey(_RvHash##K##T* h, const K* key); \
	T* _RvHash##K##T##Find(_RvHash##K##T* h, const K* key); \
	_RvHashIter##K##T _RvHash##K##T##FindIter(_RvHash##K##T* h, const K* key); /* \
	_RvHashIterPair##K##T _RvHash##K##T##EqualRange(_RvHash##K##T* h, \
	  K* key);*/

/************************************************************************/
/* Define																*/
/************************************************************************/
#define rvDefineHash(K, T) \
	static _RvHashNode##K##T* _RvHashNode##K##T##Construct(_RvHashNode##K##T* n, \
	  const K* key, T* data, size_t index, _RvHashNode##K##T* next) { \
		K##ConstructCopy(&n->key, key, K##GetAllocator(key)); \
		T##ConstructCopy(&n->data, data, T##GetAllocator(data)); \
		n->index = index; \
		n->next = next; \
		return n; \
	} \
	_RvHashNodePtr##K##T* _RvHashNodePtr##K##T##ConstructCopy(_RvHashNodePtr##K##T* d, const _RvHashNodePtr##K##T* s, void* a) { \
        RV_UNUSED_ARG(a); \
		*d = *s; \
		return d; \
	} \
	void _RvHashNodePtr##K##T##Destruct(_RvHashNodePtr##K##T* i) { \
        RV_UNUSED_ARG(i); \
	} \
	RvBool _RvHashNodePtr##K##T##Equal(const _RvHashNodePtr##K##T* a, const _RvHashNodePtr##K##T* b) { \
		return *a == *b; \
	} \
	_RvHashIter##K##T* _RvHashIter##K##T##ConstructCopy(_RvHashIter##K##T* d, const _RvHashIter##K##T* s, void* a) { \
        RV_UNUSED_ARG(a); \
		*d = *s; \
		return d; \
	} \
	void _RvHashIter##K##T##Destruct(_RvHashIter##K##T* i) { \
        RV_UNUSED_ARG(i); \
	} \
	_RvHashIter##K##T* _RvHashIter##K##T##Copy(_RvHashIter##K##T* d, const _RvHashIter##K##T* s) { \
		*d = *s; \
		return d; \
	} \
	RvAlloc* _RvHashIter##K##T##GetAllocator(_RvHashIter##K##T* iter) { \
        RV_UNUSED_ARG(iter); \
		return NULL; \
	} \
	RvBool _RvHashIter##K##T##Equal(const _RvHashIter##K##T* a, const _RvHashIter##K##T* b) { \
		return a->node == b->node; \
	} \
	void _RvHashIter##K##T##Swap(_RvHashIter##K##T* a, _RvHashIter##K##T* b) { \
		_RvHashIter##K##T t = *a; \
		*a = *b; \
		*b = t; \
	} \
	static _RvHashIter##K##T _rvHashEnd##K##T##_ = {NULL, NULL}; \
	const K *_RvHashIter##K##T##Key(_RvHashIter##K##T iter) { \
		return &iter.node->key; \
	} \
	T *_RvHashIter##K##T##Data(_RvHashIter##K##T iter) { \
		return &iter.node->data; \
	} \
	_RvHashIter##K##T _RvHashIter##K##T##Next(_RvHashIter##K##T iter) { \
		if (iter.node->next) { \
			iter.node = iter.node->next; \
			return iter; \
		} else { \
			size_t n = rvPtrVectorSize(&iter.hash->buckets); \
			size_t i; \
			for (i = (iter.node->index % n) + 1; i < n; ++i) \
				if ((iter.node = *(_RvHashNode##K##T**)rvPtrVectorAt(&iter.hash->buckets, i))) \
					return iter; \
			return _rvHashEnd##K##T##_; \
		} \
	} \
	/* rvDefinePair(_RvHashIter##K##T, _RvHashIter##K##T) */\
	_RvHash##K##T* _RvHash##K##T##Construct(_RvHash##K##T* h, size_t n, size_t (*hasher)(const K*), \
	  RvAlloc *nodeAllocator, RvAlloc *bucketAllocator) { \
		void* null = (void*)NULL; \
		h->size = 0; \
		h->hasher = hasher; \
		RvAssert(hasher); \
		h->allocator = nodeAllocator; \
		rvPtrVectorConstruct(&h->buckets, bucketAllocator); \
		rvPtrVectorFill(&h->buckets, _rvHashNextPrime(n), &null); \
		return h; \
	} \
	void _RvHash##K##T##Clear(_RvHash##K##T* h) { \
		void* null = (void*)NULL; \
		size_t i; \
		for (i = 0; i < rvPtrVectorSize(&h->buckets); ++i) { \
			_RvHashNode##K##T* node = *(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, i); \
			while (node) { \
				_RvHashNode##K##T* cur = node; \
				node = node->next; \
				K##Destruct(&cur->key); \
				T##Destruct(&cur->data); \
				rvAllocDeallocateObject(h->allocator, _RvHashNode##K##T, cur); \
			} \
		} \
		rvPtrVectorFill(&h->buckets, rvPtrVectorSize(&h->buckets), &null); \
		h->size = 0; \
	} \
	void _RvHash##K##T##Destruct(_RvHash##K##T* h) { \
		rvHashClear(K, T)(h); \
		rvPtrVectorDestruct(&h->buckets); \
	} \
	_RvHashIter##K##T _RvHash##K##T##End(_RvHash##K##T *h) { \
        RV_UNUSED_ARG(h); \
		return _rvHashEnd##K##T##_; \
	} \
	_RvHashIter##K##T _RvHash##K##T##Begin(_RvHash##K##T *h) { \
		_RvHashIter##K##T iter; \
		size_t i; \
		for (i = 0; i < rvPtrVectorSize(&h->buckets); ++i) \
			if ((iter.node = *(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, i))) { \
				iter.hash = h; \
				return iter; \
			} \
		return _rvHashEnd##K##T##_; \
	} \
	void _RvHash##K##T##Resize(_RvHash##K##T* h, size_t n) { \
		void* null = (void*)NULL; \
		size_t oldSize = rvPtrVectorSize(&h->buckets); \
		if (n > oldSize) { \
			size_t newSize = _rvHashNextPrime(n); \
			size_t i; \
			RvPtrVector v; \
			rvPtrVectorConstruct(&v, rvPtrVectorGetAllocator(&h->buckets)); \
			rvPtrVectorFill(&v, newSize, &null); \
   	     	for (i = 0; i < oldSize; ++i) { \
				_RvHashNode##K##T* oldBucket = *(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, i); \
				while (oldBucket) { \
					_RvHashNode##K##T* node = oldBucket; \
					_RvHashNode##K##T** newBucket = (_RvHashNode##K##T**)rvPtrVectorAt(&v, node->index % newSize); \
					oldBucket = oldBucket->next; \
					node->next = *newBucket; \
					*newBucket = node; \
				} \
			} \
			rvPtrVectorSwap(&h->buckets, &v); \
			rvPtrVectorDestruct(&v); \
		} \
	} \
	_RvHashIter##K##T _RvHash##K##T##InsertUnique(_RvHash##K##T* h, const K* key, T* data) { \
		_RvHashIter##K##T iter; \
		_RvHashNode##K##T *tmp = NULL; \
		if (_RvHash##K##T##Find(h, key) == NULL) { \
            tmp = rvAllocAllocateObject(h->allocator, _RvHashNode##K##T); \
			if (tmp) { \
				_RvHashNode##K##T **first; \
				size_t index = h->hasher(key); \
				rvHashResize(K, T)(h, h->size + 1); \
				first = (_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, index % rvPtrVectorSize(&h->buckets)); \
				_RvHashNode##K##T##Construct(tmp, key, data, index, *first); \
				*first = tmp; \
				++(h->size); \
			} \
		} \
		iter.hash = h; \
		iter.node = tmp; \
		return iter; \
	} \
	_RvHashIter##K##T _RvHash##K##T##InsertEqual(_RvHash##K##T* h, const K* key, T* data) { \
		_RvHashIter##K##T iter; \
		_RvHashNode##K##T *tmp = rvAllocAllocateObject(h->allocator, _RvHashNode##K##T); \
		if (tmp) { \
			size_t index = h->hasher(key); \
			rvHashResize(K, T)(h, h->size + 1); \
			iter = _RvHash##K##T##FindIter(h, key); \
			if (iter.node) { \
				_RvHashNode##K##T##Construct(tmp, key, data, index, iter.node->next); \
				iter.node->next = tmp; \
			} else { \
				size_t n = rvPtrVectorSize(&h->buckets); \
				_RvHashNode##K##T **first = (_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, index % n); \
				_RvHashNode##K##T##Construct(tmp, key, data, index, *first); \
				*first = tmp; \
			} \
			++(h->size); \
		} \
		iter.hash = h; \
		iter.node = tmp; \
		return iter; \
	} \
	_RvHashIter##K##T _RvHash##K##T##Erase(_RvHash##K##T* h, _RvHashIter##K##T i) { \
		_RvHashIter##K##T nextIter = _RvHashIter##K##T##Next(i); \
		size_t n = rvPtrVectorSize(&h->buckets); \
		_RvHashNode##K##T* node = *(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, i.node->index % n); \
		if (node == i.node) { \
			*(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, i.node->index % n) = node->next; \
		} else { \
			_RvHashNode##K##T* prev = node; \
			node = node->next; \
			while (node && (node != i.node)) { \
				prev = node; \
				node = node->next; \
			} \
			if (!node) return nextIter; \
			prev->next = node->next; \
		} \
		K##Destruct(&node->key); \
		T##Destruct(&node->data); \
		rvAllocDeallocateObject(h->allocator, _RvHashNode##K##T, node); \
		--(h->size); \
		return nextIter; \
	} \
	void _RvHash##K##T##EraseKey(_RvHash##K##T* h, const K* key) { \
		size_t n = rvPtrVectorSize(&h->buckets); \
		size_t index = h->hasher(key); \
		_RvHashNode##K##T* node = *(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, index % n); \
		if (node) { \
			if (K##Equal(&node->key, key)) { \
				*(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, index % n) = node->next; \
			} else { \
				_RvHashNode##K##T* prev = node; \
				node = node->next; \
				while (node && !K##Equal(&node->key, key)) { \
					prev = node; \
					node = node->next; \
				} \
				if (!node) return; \
				prev->next = node->next; \
			} \
		K##Destruct(&node->key); \
		T##Destruct(&node->data); \
		rvAllocDeallocateObject(h->allocator, _RvHashNode##K##T, node); \
		--(h->size); \
		} \
	} \
	T* _RvHash##K##T##Find(_RvHash##K##T* h, const K* key) { \
		size_t n = rvPtrVectorSize(&h->buckets); \
		size_t index = h->hasher(key); \
		_RvHashNode##K##T* node = *(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, index % n); \
		for (; node; node = node->next) \
			if (K##Equal(&node->key, key)) \
				return &node->data; \
		return NULL; \
	} \
	_RvHashIter##K##T _RvHash##K##T##FindIter(_RvHash##K##T* h, const K* key) { \
		size_t n = rvPtrVectorSize(&h->buckets); \
		size_t index = h->hasher(key); \
		_RvHashIter##K##T r; \
		_RvHashNode##K##T* node = *(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, index % n); \
		for (; node; node = node->next) \
			if (K##Equal(&node->key, key)) { \
				r.hash = h; \
				r.node = node; \
				return r; \
			} \
		return _rvHashEnd##K##T##_; \
	} /* \
	RvPair(_RvHashIter##K##T, _RvHashIter##K##T) _RvHash##K##T##EqualRange(_RvHash##K##T* h, \
		K* key) { \
		RvPair(_RvHashIter##K##T, _RvHashIter##K##T) p; \
		size_t n = rvPtrVectorSize(&h->buckets); \
		size_t index = h->hasher(key); \
		_RvHashNode##K##T* node = *(_RvHashNode##K##T**)rvPtrVectorAt(&h->buckets, index % n); \
		for (; node; node = node->next) \
			if (K##Equal(&node->key, key)) { \
				p.first.hash = p.second.hash = h; \
				p.first.node = p.second.node = node; \
				while (p.second.node && K##Equal(&p.second.node->key, key)) \
					p.second.node = p.second.node->next; \
				return p; \
			} \
		p.first = p.second = _rvHashEnd##K##T##_; \
		return p; \
	} */

/* rvHashEqualRange<K, T> does not compile on Diab because of preprocessor
bugs, so use rvHashFindIter to get the first node in the range and walk the
iterator until either the key of the node is not the same or the end of the
hash is reached. */

RVCOREAPI
size_t _rvHashNextPrime(size_t n);

/* Public */

/* Hash */
#define RvHash(K, T)					_RvHash##K##T
#define rvHashSize(h)					((h)->size)
#define rvHashBegin(K, T)				_RvHash##K##T##Begin
#define rvHashEnd(K, T)					_RvHash##K##T##End
#define rvHashConstruct(K, T)			_RvHash##K##T##Construct
#define rvHashDestruct(K, T)			_RvHash##K##T##Destruct
#define rvHashClear(K, T)				_RvHash##K##T##Clear
#define rvHashResize(K, T)				_RvHash##K##T##Resize
#define rvHashInsertUnique(K, T)		_RvHash##K##T##InsertUnique
#define rvHashInsertEqual(K, T)			_RvHash##K##T##InsertEqual
#define rvHashErase(K, T)				_RvHash##K##T##Erase
#define rvHashEraseKey(K, T)			_RvHash##K##T##EraseKey
#define rvHashFind(K, T)				_RvHash##K##T##Find
#define rvHashFindIter(K, T)			_RvHash##K##T##FindIter
#define rvHashGetNodeSize(K, T)			sizeof(_RvHashNode##K##T)
/*#define rvHashEqualRange(K, T)			_RvHash##K##T##EqualRange*/

/* Hash iterator */
#define RvHashIter(K, T)				_RvHashIter##K##T
#define rvHashIterConstructCopy(K, T)	_RvHashIter##K##T##ConstructCopy
#define rvHashIterDestruct(K, T)		_RvHashIter##K##T##Destruct
#define rvHashIterGetAllocator(K, T)	_RvHashIter##K##T##GetAllocator
#define rvHashIterSwap(K, T)			_RvHashIter##K##T##Swap
#define rvHashIterEqual(K, T)			_RvHashIter##K##T##Equal
#define rvHashIterCopy(K, T)			_RvHashIter##K##T##Copy
#define rvHashIterNext(K, T)			_RvHashIter##K##T##Next
#define rvHashIterKey(K, T)				_RvHashIter##K##T##Key
#define rvHashIterData(K, T)			_RvHashIter##K##T##Data

/*#define RvHashIterPair(K, T)			_RvHashIterPair##K##T*/


#endif
