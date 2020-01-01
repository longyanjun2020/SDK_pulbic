#if (0)
******************************************************************************
Filename    : rvvector.h
Description :
The following pseudo C++ prototypes describe the RvVector<T> interface:
RvVector<T>* rvVectorConstruct<T>(RvVector<T>* v, RvAlloc *a);
RvVector<T>* rvVectorConstructN<T>(RvVector<T>* v, RvSize_t n, const T* x, RvAlloc *a);
RvVector<T>* rvVectorConstructCopy<T>(RvVector<T>* v, const _RvVector<T>* src, RvAlloc *a);
void rvVectorDestruct<T>(RvVector<T>* v);
RvVector<T>* rvVectorCopy<T>(RvVector<T>* v, const RvVector<T>* src);
void rvVectorClear<T>(RvVector<T>* v);
RvBool rvVectorFill<T>(RvVector<T>* v);
RvBool rvVectorReserve<T>(_RvVector<T>* v, RvSize_t n);
RvVectorIter<T> rvVectorPushBack<T>(RvVector<T>* v, const T* x);
RvVectorIter<T> rvVectorInsert<T>(RvVector<T>* v, RvVectorIter<T> it, const T* x);
void rvVectorPopBack(RvVector<T>* v);
RvVectorIter<T> rvVectorErase(RvVector<T>* v, _RvVectorIter<T> it);
RvBool rvVectorEqual<T>(const RvVectorT* a, const RvVector<T>* b);
void rvVectorSwap(RvVector<T>* a, RvVector<T>* b);
RvSize_t rvVectorSize(RvVector<T>* v);
RvSize_t rvVectorCapacity(RvVector<T>* v);
T* rvVectorFront(RvVector<T>* v);
T* rvVectorBack(RvVector<T>* v);
RvVectorIter<T> rvVectorBegin(RvVector<T>* v);
RvVectorIter<T> rvVectorEnd(RvVector<T>* v);
RvVectorRevIter<T> rvVectorRevBegin(RvVector<T>* v);
RvVectorRevIter<T> rvVectorRevEnd(RvVector<T>* v);
T* rvVectorAt(RvVector<T>* v, RvSize_t i);

The following C++ prototypes describe the RvVectorIter interface:
RvVectorIter<T> rvVectorIterPrev(RvVectorIter<T> i);
RvVectorIter<T> rvVectorIterNext(RvVectorIter<T> i);
T* rvVectorIterData(RvVectorIter<T> i);

The following C++ prototypes describe the RvVectorRevIter interface:
RvVectorRevIter<T> rvVectorRevIterPrev(RvVectorRevIter<T> i);
RvVectorRevIter<T> rvVectorRevIterNext(RvVectorRevIter<T> i);
T* rvVectorRevIterData(RvVectorIter<T> i);

******************************************************************************
                Copyright (c) 1999 RADVision Inc.
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

#ifndef RV_VECTOR_H
#define RV_VECTOR_H

#include "rvalloc.h"
#include "rvassert.h"

#ifndef NULL
#define NULL (0)
#endif


#define rvDeclareForwardVector(T) \
	typedef struct _RvVector##T; \
	typedef T* _RvVectorIter##T; \
	typedef T* _RvVectorRevIter##T;

#define rvDeclareVectorEx(T, linkage) \
	typedef struct { \
		T* data; \
		RvSize_t size; \
		RvSize_t capacity; \
		RvAlloc *allocator; \
	} _RvVector##T; \
	typedef T* _RvVectorIter##T; \
	typedef T* _RvVectorRevIter##T; \
	linkage RvVector(T)* _RvVector##T##Construct(RvVector(T)* v, RvAlloc *a); \
	linkage RvVector(T)* _RvVector##T##ConstructN(RvVector(T)* v, RvSize_t n, \
	  const T* x, RvAlloc *a); \
	linkage RvVector(T)* _RvVector##T##ConstructCopy(RvVector(T)* d, \
	  const RvVector(T)* s, RvAlloc *a); \
	linkage void _RvVector##T##Destruct(RvVector(T)* v); \
	linkage RvVector(T)* _RvVector##T##Copy(RvVector(T)* d, const RvVector(T)* s); \
	linkage void _RvVector##T##Clear(RvVector(T)* v); \
	linkage RvBool _RvVector##T##Fill(RvVector(T)* v, RvSize_t n, const T* x); \
	linkage RvBool _RvVector##T##Reserve(RvVector(T)* v, RvSize_t n); \
	linkage _RvVectorIter##T _RvVector##T##PushBack(RvVector(T)* v, const T* x); \
	linkage _RvVectorIter##T _RvVector##T##Insert(RvVector(T)* v, \
	  _RvVectorIter##T it, const T* x); \
	linkage T* _RvVector##T##AllocBack(RvVector(T)* v); \
	linkage void _RvVector##T##PopBack(RvVector(T)* v); \
	linkage _RvVectorIter##T _RvVector##T##Erase(RvVector(T)* v, \
	  _RvVectorIter##T it); \
	linkage RvBool _RvVector##T##Equal(const RvVector(T)* a, const RvVector(T)* b); \
	linkage void _RvVector##T##Swap(_RvVector##T* a, _RvVector##T* b);

#define RV_LINKAGE_INTERNAL

#define rvDeclareVector(T) rvDeclareVectorEx(T,RV_LINKAGE_INTERNAL)

#define rvDefineVector(T) \
	void _RvVector##T##Copy_(T* d, const T* s, RvSize_t n, RvAlloc *a) { \
		RvSize_t i; \
		for (i = 0; i < n; ++i) \
			(void)T##ConstructCopy(&(d[i]), &(s[i]), a); \
	} \
	void _RvVector##T##Clear_(RvVector(T)* v) { \
		RvSize_t i; \
		for (i = v->size; i > 0; --i) \
			T##Destruct(&v->data[i - 1]); \
	} \
	RvVector(T)* _RvVector##T##Construct(RvVector(T)* v, RvAlloc *a) { \
		v->allocator = a; \
		v->size = 0; \
		v->capacity = 0; \
		return v; \
	} \
	RvVector(T)* _RvVector##T##ConstructN(RvVector(T)* v, RvSize_t n, const T* x, RvAlloc *a) { \
		v->allocator = a; \
		v->size = 0; \
		v->capacity = 0; \
		if (!rvVectorFill(T)(v, n, x)) return NULL; \
		return v; \
	} \
	RvVector(T)* _RvVector##T##ConstructCopy(RvVector(T)* d, const RvVector(T)* s, RvAlloc *a) { \
		d->allocator = a; \
		d->size = 0; \
		d->capacity = 0; \
		if (!rvVectorReserve(T)(d, s->size)) return NULL; \
		_RvVector##T##Copy_(d->data, s->data, s->size, d->allocator); \
		d->size = s->size; \
		return d; \
	} \
	void _RvVector##T##Destruct(RvVector(T)* v) { \
		if (v->capacity) { \
			_RvVector##T##Clear_(v); \
			rvAllocDeallocate(v->allocator, \
			  v->capacity * sizeof(T), v->data); \
		} \
	} \
	RvVector(T)* _RvVector##T##Copy(RvVector(T)* d, const RvVector(T)* s) { \
		_RvVector##T##Clear_(d); \
		d->size = 0; \
		if (!rvVectorReserve(T)(d, s->size)) return NULL; \
		_RvVector##T##Copy_(d->data, s->data, s->size, d->allocator); \
		d->size = s->size; \
		return d; \
	} \
	void _RvVector##T##Clear(RvVector(T)* v) { \
		_RvVector##T##Clear_(v); \
		v->size = 0; \
	} \
	RvBool _RvVector##T##Fill(RvVector(T)* v, RvSize_t n, const T* x) { \
		if (rvVectorReserve(T)(v, n)) { \
			RvSize_t i; \
			for (i = 0; i < n; ++i) { \
				T##Destruct(rvVectorAt(v, i)); \
				(void)T##ConstructCopy(rvVectorAt(v, i), x, v->allocator); \
			} \
			v->size = RvMax(v->size, n); \
		} else \
			return RV_FALSE; \
		return RV_TRUE; \
	} \
	RvBool _RvVector##T##Reserve(RvVector(T)* v, RvSize_t n) { \
		RvSize_t capacity; \
		T* data; \
		if (n > v->capacity) { \
			if (v->capacity == 0) { \
				capacity = ((n < 4) ? 4 : n); \
				data = (T*)rvAllocAllocate(v->allocator, capacity * sizeof(T)); \
				if (!data) return RV_FALSE; \
			} else { \
				capacity = v->size + ((n < v->size) ? v->size : n); \
				data = (T*)rvAllocAllocate(v->allocator, capacity * sizeof(T)); \
				if (!data) return RV_FALSE; \
				_RvVector##T##Copy_(data, v->data, v->size, v->allocator); \
				_RvVector##T##Clear_(v); \
				rvAllocDeallocate(v->allocator, v->capacity * sizeof(T), \
				  v->data); \
			} \
			v->capacity = capacity; \
			v->data = data; \
		} \
		return RV_TRUE; \
	} \
	_RvVectorIter##T _RvVector##T##PushBack(RvVector(T)* v, const T* x) { \
		if (rvVectorReserve(T)(v, v->size + 1)) { \
			(void)T##ConstructCopy(&(v->data[v->size]), x, v->allocator); \
			++(v->size); \
			return &(v->data[v->size - 1]); \
		} \
		return rvVectorEnd(v); \
	} \
	T* _RvVector##T##AllocBack(RvVector(T)* v) { \
		if (rvVectorReserve(T)(v, v->size + 1)) { \
			++(v->size); \
			return &(v->data[v->size - 1]); \
		} \
		return NULL; \
	} \
	_RvVectorIter##T _RvVector##T##Insert(RvVector(T)* v, _RvVectorIter##T it, const T* x) { \
		RvPtrdiff_t i = it - rvVectorBegin(v); \
		RvSize_t j; \
		RvAssert(it >= rvVectorBegin(v) && it <= rvVectorEnd(v)); \
		if (rvVectorReserve(T)(v, v->size + 1)) { \
			for (j = v->size; j > (RvSize_t)i; --j) { \
				(void)T##ConstructCopy(&(v->data[j]), &(v->data[j - 1]), v->allocator); \
				T##Destruct(&v->data[j - 1]); \
			} \
			(void)T##ConstructCopy(&(v->data[i]), x, v->allocator); \
			++(v->size); \
			return rvVectorBegin(v) + i; \
		} \
		return rvVectorEnd(v); \
	} \
	void _RvVector##T##PopBack(RvVector(T)* v) { \
		if (v->size != 0) { \
			--(v->size); \
			T##Destruct(&v->data[v->size]); \
		} \
	} \
	_RvVectorIter##T _RvVector##T##Erase(RvVector(T)* v, _RvVectorIter##T it) { \
		_RvVectorIter##T i = it; \
  	RvAssert(i >= rvVectorBegin(v) && i < rvVectorEnd(v)); \
		if (i < rvVectorEnd(v)) { \
			T##Destruct(rvVectorIterData(i)); \
			i = rvVectorIterNext(i); \
			for (; i != rvVectorEnd(v); i = rvVectorIterNext(i)) { \
				(void)T##ConstructCopy(rvVectorIterData(i - 1), \
				rvVectorIterData(i), v->allocator); \
				T##Destruct(rvVectorIterData(i)); \
			} \
			--(v->size); \
		} \
		return it; \
	} \
	RvBool _RvVector##T##Equal(const RvVector(T)* a, const RvVector(T)* b) { \
		if (a->size == b->size) { \
			RvSize_t i; \
			for (i = 0; i < a->size; ++i) \
				if (!(T##Equal(&(a->data[i]), &(b->data[i])))) \
					return RV_FALSE; \
			return RV_TRUE; \
		} \
		return RV_FALSE; \
	} \
	void _RvVector##T##Swap(RvVector(T)* a, RvVector(T)* b) { \
		RvVector(T) t = *a; *a = *b; *b = t; \
	}

/* Vector */
#define RvVector(T)					_RvVector##T
#define rvVectorGetAllocator(v)		((v)->allocator)
#define rvVectorSize(v)				((v)->size)
#define rvVectorCapacity(v)			((v)->capacity - (v)->size)
#define rvVectorFront(v)			(&((v)->data[0]))
#define rvVectorBack(v)				((v)->size ? &((v)->data[(v)->size - 1]) : &((v)->data[-1]))
#define rvVectorBegin(v)			(&((v)->data[0]))
#define rvVectorEnd(v)				(&((v)->data[(v)->size]))
#define rvVectorRevBegin(v)			(rvVectorBack(v))
#define rvVectorRevEnd(v)			(&((v)->data[-1]))
#define rvVectorAt(v, i)			(&((v)->data[i]))
#define rvVectorConstruct(T)		_RvVector##T##Construct
#define rvVectorConstructN(T)		_RvVector##T##ConstructN
#define rvVectorConstructCopy(T)	_RvVector##T##ConstructCopy
#define rvVectorDestruct(T)			_RvVector##T##Destruct
#define rvVectorCopy(T)				_RvVector##T##Copy
#define rvVectorClear(T)			_RvVector##T##Clear
#define rvVectorFill(T)				_RvVector##T##Fill
#define rvVectorReserve(T)			_RvVector##T##Reserve
#define rvVectorAllocBack(T)		_RvVector##T##AllocBack
#define rvVectorPushBack(T)			_RvVector##T##PushBack
#define rvVectorInsert(T)			_RvVector##T##Insert
#define rvVectorPopBack(T)			_RvVector##T##PopBack
#define rvVectorErase(T)			_RvVector##T##Erase
#define rvVectorEqual(T)			_RvVector##T##Equal
#define rvVectorSwap(T)				_RvVector##T##Swap

/* Aliases for naming problem */
#define RvVectorConstructCopy(T)	rvVectorConstructCopy(T)
#define RvVectorCopy(T)				rvVectorCopy(T)
#define RvVectorDestruct(T)			rvVectorDestruct(T)
#define RvVectorGetAllocator(T)		rvVectorGetAllocator(T)
#define RvVectorSwap(T)				rvVectorSwap(T)
#define RvVectorEqual(T)			rvVectorEqual(T)

/* Iterator */
#define RvVectorIter(T)				_RvVectorIter##T
#define rvVectorIterNext(i)			((i) + 1)
#define rvVectorIterPrev(i)			((i) - 1)
#define rvVectorIterData(i)			(i)
#define rvVectorIterEqual(a,b)		((a) == (b))

/* Aliases for naming problem */
#define RvVectorIterData(i)			rvVectorIterData(i)
#define RvVectorIterPrev(i)			rvVectorIterPrev(i)
#define RvVectorIterNext(i)			rvVectorIterNext(i)
#define RvVectorIterEqual(a,b)		rvVectorIterEqual(a,b)

/* Reverse Iterator */
#define RvVectorRevIter(T)			_RvVectorRevIter##T
#define rvVectorRevIterNext(i)		((i) - 1)
#define rvVectorRevIterPrev(i)		((i) + 1)
#define rvVectorRevIterData(i)		(i)
#define rvVectorRevIterEqual(a,b)	((a) == (b))

/* Aliases for naming problem */
#define RvVectorRevIterData(i)		rvVectorRevIterData(i)
#define RvVectorRevIterPrev(i)		rvVectorRevIterPrev(i)
#define RvVectorRevIterNext(i)		rvVectorRevIterNext(i)
#define RvVectorRevIterEqual(a,b)	rvVectorRevIterEqual(a,b)

#endif
