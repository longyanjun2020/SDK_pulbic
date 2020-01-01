#if (0)
******************************************************************************
Filename    :
Description :
The following pseudo C++ prototypes describe the RvList interface:
RvList* rvListConstruct<T>(RvList<T>* l, RvAlloc* a);
RvList* rvListConstructCopy<T>(RvList<T>* d, const RvList<T>* s, RvAlloc *a);
RvList* rvListCopy<T>(RvList<T>* d, const RvList<T>* s);
void rvListDestruct<T>(RvList<T>* l);
void rvListSwap<T>(RvList<T>* a, RvList<T>* b);
RvBool rvListEqual<T>(const RvList<T>* a, const RvList<T>* b);
size_t rvListSize(RvList<T>* l);
RvListIter<T> rvListBegin(RvList<T>* l);
RvListIter<T> rvListEnd(RvList<T>* l);
RvListRevIter<T> rvListRevBegin(RvList<T>* l);
RvListRevIter<T> rvListRevEnd(RvList<T>* l);
T* rvListFront(RvList<T>* l);
T* rvListBack(RvList<T>* l);
RvListIter<T> rvListPushFront<T>(RvList<T>* l, T* x);
RvListIter<T> rvListPushBack<T>(RvList<T>* l, T* x);
void rvListPopFront<T>(RvList<T>* l);
void rvListPopBack<T>(RvList<T>* l);
RvListIter<T> rvListInsert<T>(RvList<T>* l, RvListIter<T> i, T* x);
RvListIter<T> rvListErase<T>(RvList<T>* l, RvListIter<T> i);
void rvListClear<T>(RvList<T>* l);
void rvListSplice<T>(RvList<T> *d, RvListIter<T> it, RvList<T> *s,
  RvListIter<T> f, RvListIter<T> l);
RvListIter<T> rvListRemove<T>(RvList<T>* l, T* x);
RvListIter<T> rvListRemoveIf<T>(RvList<T>* l, RvBool (*pred)(T*));

The following pseudo C++ prototypes describe the RvListIter interface:
RvListIter<T> rvListIterPrev(RvListIter<T> i);
RvListIter<T> rvListIterNext(RvListIter<T> i);
T* rvListIterData(RvListIter<T> i);

The following pseudo C++ prototypes describe the RvListRevIter interface:
RvListRevIter<T> rvListRevIterPrev(RvListRevIter<T> i);
RvListRevIter<T> rvListRevIterNext(RvListRevIter<T> i);
T* rvListRevIterData(RvListIter<T> i);

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

#ifndef RV_LIST_H
#define RV_LIST_H

#include "rvalloc.h"

#define rvDeclareForwardList(T) \
	struct _RvListNode##T; \
	typedef const struct _RvListNode##T *_RvListConstIter##T; \
	typedef struct _RvListNode##T *_RvListIter##T; \
	typedef struct _RvListNode##T *_RvListRevIter##T; \
	struct _RvList##T; \

#define rvDeclareList(T) \
	struct _RvListNode##T { \
		struct _RvListNode##T *prev; \
		struct _RvListNode##T *next; \
		T data; \
	}; \
	typedef const struct _RvListNode##T *_RvListConstIter##T; \
	typedef struct _RvListNode##T *_RvListIter##T; \
	typedef struct _RvListNode##T *_RvListRevIter##T; \
	typedef struct { \
		RvAlloc *allocator; \
		size_t size; \
		struct _RvListNode##T end; \
		struct _RvListNode##T *head; \
	} _RvList##T; \
	RvList(T) *_RvList##T##Construct(RvList(T) *l, RvAlloc *a); \
	RvList(T) *_RvList##T##ConstructCopy(RvList(T) *l, const RvList(T) *x, RvAlloc *a); \
	RvList(T) *_RvList##T##Copy(RvList(T) *d, const RvList(T) *s); \
	void _RvList##T##Swap(RvList(T) *a, RvList(T) *b); \
	RvBool _RvList##T##Equal(const RvList(T) *a, const RvList(T) *b); \
	RvListIter(T) _RvList##T##PushFront(RvList(T) *l, const T *x); \
	RvListIter(T) _RvList##T##PushBack(RvList(T) *l, const T *x); \
	void _RvList##T##PopFront(RvList(T) *l); \
	void _RvList##T##PopBack(RvList(T) *l); \
	RvListIter(T) _RvList##T##Insert(RvList(T) *l, RvListIter(T) n, \
	  const T *x); \
	void _RvList##T##Splice(RvList(T) *d, RvListIter(T) it, RvList(T) *s, \
	  RvListIter(T) f, RvListIter(T) l); \
	RvListIter(T) _RvList##T##Erase(RvList(T) *l, RvListIter(T) n); \
	void _RvList##T##Clear(RvList(T) *l); \
	RvListIter(T) _RvList##T##Remove(RvList(T) *l, T *x); \
	RvListIter(T) _RvList##T##RemoveIf(RvList(T) *l, RvBool (*pred)(T *)); \
	T* _RvList##T##At(const RvList(T) *l, size_t n); \
	T* _RvList##T##AllocBack(RvList(T)* l);

#define rvDefineList(T) \
	RvList(T) *_RvList##T##Construct(RvList(T) *l, RvAlloc *a) { \
		l->allocator = a; \
		l->size = 0; \
		l->end.prev = l->end.next = 0; \
		l->head = &l->end; \
		return l; \
	} \
	RvList(T) *_RvList##T##ConstructCopy(RvList(T) *d, const RvList(T) *s, RvAlloc *a) { \
		RvListIter(T) i; \
		rvListConstruct(T)(d, a); \
		for (i = rvListBegin(s); i != rvListEnd(s); i = rvListIterNext(i)) { \
			if (rvListPushBack(T)(d, rvListIterData(i)) == rvListEnd(d)) { \
				rvListClear(T)(d); \
				return NULL; \
			} \
		} \
		return d; \
	} \
	RvList(T) *_RvList##T##Copy(RvList(T) *d, const RvList(T) *s) { \
		RvListIter(T) i; \
		rvListClear(T)(d); \
		for (i = rvListBegin(s); i != rvListEnd(s); i = rvListIterNext(i)) { \
			if (rvListPushBack(T)(d, rvListIterData(i)) == rvListEnd(d)) { \
				rvListClear(T)(d); \
				return NULL; \
			} \
		} \
		return d; \
	} \
	void _RvList##T##Swap(RvList(T) *a, RvList(T) *b) { \
		if (a->allocator == b->allocator) { \
			RvList(T) t = *a; *a = *b; *b = t; \
			if(a->end.prev) \
				a->end.prev->next = &a->end; \
			else \
				a->head = &a->end; \
			if(b->end.prev) \
				b->end.prev->next = &b->end; \
			else \
				b->head = &b->end; \
		} else { \
			RvListIter(T) firstA = rvListBegin(a); \
			rvListSplice(T)(a, rvListBegin(a), b, rvListBegin(b), rvListEnd(b)); \
			rvListSplice(T)(b, rvListEnd(b), a, firstA, rvListEnd(a)); \
		} \
	} \
	RvBool _RvList##T##Equal(const RvList(T) *a, const RvList(T) *b) { \
		if (rvListSize(a) == rvListSize(b)) { \
			RvListIter(T) i, j; \
			i = rvListBegin(a); \
			j = rvListBegin(b); \
			while (i != rvListEnd(a)) { \
				if (! T##Equal(rvListIterData(i), rvListIterData(j))) \
					return RV_FALSE; \
				i = rvListIterNext(i); \
				j = rvListIterNext(j); \
			} \
			return RV_TRUE; \
		} \
		return RV_FALSE; \
	} \
	RvListIter(T) _RvList##T##PushFront(RvList(T) *l, const T *x) { \
		RvListIter(T) n = (RvListIter(T))rvAllocAllocate(l->allocator, \
		  sizeof(struct _RvListNode##T)); \
		if (n) { \
			if (T##ConstructCopy(&n->data, x, l->allocator)) { \
				n->prev = 0; \
				n->next = l->head; \
				l->head->prev = n; \
				l->head = n; \
				l->size++; \
				return n; \
			} else \
				rvAllocDeallocate(l->allocator, sizeof(struct _RvListNode##T), n); \
		} \
		return rvListEnd(l); \
	} \
	RvListIter(T) _RvList##T##PushBack(RvList(T) *l, const T *x) { \
		return rvListInsert(T)(l, &l->end, x); \
	} \
	void _RvList##T##PopFront(RvList(T) *l) { \
		if (l->head != &l->end) { \
			struct _RvListNode##T* n = l->head; \
			l->head->next->prev = 0; \
			l->head = n->next; \
			l->size--; \
			T##Destruct(&n->data); \
			rvAllocDeallocate(l->allocator, \
			  sizeof(struct _RvListNode##T), n); \
		} \
	} \
	void _RvList##T##PopBack(RvList(T) *l) { \
		rvListErase(T)(l, l->end.prev); \
	} \
	RvListIter(T) _RvList##T##Insert(RvList(T) *l, RvListIter(T) it, const T *x) { \
		RvListIter(T) n = (RvListIter(T))rvAllocAllocate(l->allocator, \
		  sizeof(struct _RvListNode##T)); \
		if (n) { \
			if (T##ConstructCopy(&n->data, x, l->allocator)) { \
				n->prev = it->prev; \
				n->next = it; \
				if (it->prev) \
					it->prev->next = n; \
				else \
					l->head = n; \
				it->prev = n; \
				l->size++; \
				return n; \
			} else \
				rvAllocDeallocate(l->allocator, sizeof(struct _RvListNode##T), n); \
		} \
		return rvListEnd(l); \
	} \
	RvListIter(T)  _RvList##T##Erase(RvList(T) *l, RvListIter(T) it) { \
		if (it != &l->end) { \
			RvListIter(T) o = it->next; \
			if (it->prev) \
				it->prev->next = o; \
			else \
				l->head = o; \
			o->prev = it->prev; \
			l->size--; \
			T##Destruct(&it->data); \
			rvAllocDeallocate(l->allocator, \
			  sizeof(struct _RvListNode##T), it); \
			return o; \
		} \
		return 0; \
	} \
	void _RvList##T##Clear(RvList(T) *l) { \
		while (l->size != 0) \
			rvListPopFront(T)(l); \
	} \
	void _RvList##T##Splice(RvList(T) *d, RvListIter(T) it, RvList(T) *s, \
	  RvListIter(T) f, RvListIter(T) l) { \
		if (f != l) { \
			if (d->allocator == s->allocator) { \
				RvListIter(T) k = l->prev; \
				RvListIter(T) i; \
				size_t n = 0; \
				for (i = f; i != l; i = rvListIterNext(i)) ++n; \
				d->size += n; \
				s->size -= n; \
				if (f == rvListBegin(s)) { \
					s->head = l; l->prev = 0; \
				} else { \
					f->prev->next = l; l->prev = f->prev; \
				} \
				if (it == rvListBegin(d)) { \
					d->head = f; f->prev = 0; \
				} else { \
					it->prev->next = f; f->prev = it->prev; \
				} \
				it->prev = k; k->next = it; \
			} else { \
				while (f != l) { \
					RvListIter(T) next = rvListIterNext(f); \
					rvListInsert(T)(d, it, rvListIterData(f)); \
					rvListErase(T)(s, f); \
					f = next; \
				} \
			} \
		} \
	} \
	RvListIter(T) _RvList##T##Remove(RvList(T) *l, T *x) { \
		RvListIter(T) i = rvListBegin(l); \
		RvListIter(T) e = rvListEnd(l); \
		while (i != e) \
			if (T##Equal(rvListIterData(i), x)) \
				i = rvListErase(T)(l, i); \
			else \
				i = rvListIterNext(i); \
		return i; \
	}

/* Exotic list method -- need to define individually */
#define rvDefineListRemoveIf(T) \
	RvListIter(T) _RvList##T##RemoveIf(RvList(T) *l, RvBool (*pred)(T *)) { \
		RvListIter(T) i = rvListBegin(l); \
		RvListIter(T) e = rvListEnd(l); \
		while (i != e) \
			if (pred(rvListIterData(i))) \
				i = rvListErase(T)(l, i); \
			else \
				i = rvListIterNext(i); \
		return i; \
	}

/* Exotic list method (not recommended) -- need to define individually */
#define rvDefineListAt(T) \
	T* _RvList##T##At(const RvList(T) *l, size_t i) { \
		size_t j; \
		RvListIter(T) iter = rvListBegin(l); \
		if(i >= l->size) return NULL; \
		for (j = 0; j < i; ++j) \
			iter = rvListIterNext(iter); \
		return rvListIterData(iter); \
	}

/* Exotic list method -- need to define individually */
#define rvDefineListAllocBack(T) \
	T* _RvList##T##AllocBack(RvList(T)* l) { \
		struct _RvListNode##T* n; \
		n = (struct _RvListNode##T*)rvAllocAllocate(l->allocator, \
		  sizeof(struct _RvListNode##T)); \
		if (n) { \
			n->prev = l->end.prev; \
			n->next = &l->end; \
			if (l->end.prev) \
				l->end.prev->next = n; \
			else \
				l->head = n; \
			l->end.prev = n; \
			l->size++; \
			return &n->data; \
		} \
		return 0; \
	}

/* Public rvList interface */
#define RvList(T)					_RvList##T 
#define rvListSize(l)				((l)->size)
#define rvListGetAllocator(l)		((l)->allocator)
#define rvListBegin(l)				((l)->head)
#define rvListEnd(l)				(&(l)->end)
#define rvListRevBegin(l)			((l)->end.prev)
#define rvListRevEnd(l)				((l)->head->prev)
#define rvListFront(l)				(&((l)->head->data))
#define rvListBack(l)				(&((l)->end.prev->data))
#define rvListEmpty(l)				(rvListBegin(l) == rvListEnd(l))
#define rvListConstruct(T)			_RvList##T##Construct
#define rvListConstructCopy(T)		_RvList##T##ConstructCopy
#define rvListCopy(T)				_RvList##T##Copy
#define rvListDestruct(T)			_RvList##T##Clear
#define rvListSwap(T)				_RvList##T##Swap
#define rvListEqual(T)				_RvList##T##Equal
#define rvListPushFront(T)			_RvList##T##PushFront
#define rvListPushBack(T)			_RvList##T##PushBack
#define rvListPopFront(T)			_RvList##T##PopFront
#define rvListPopBack(T)			_RvList##T##PopBack
#define rvListInsert(T)				_RvList##T##Insert
#define rvListErase(T)				_RvList##T##Erase
#define rvListClear(T)				_RvList##T##Clear
#define rvListSplice(T)				_RvList##T##Splice
#define rvListRemove(T)				_RvList##T##Remove
#define rvListRemoveIf(T)			_RvList##T##RemoveIf
#define rvListAt(T)					_RvList##T##At
#define rvListAllocBack(T)			_RvList##T##AllocBack
#define rvListGetAllocSize(T)		(sizeof(struct _RvListNode##T))

/* Aliases for naming problem */
#define RvListConstructCopy(T)		rvListConstructCopy(T)	
#define RvListDestruct(T)			rvListDestruct(T)
#define RvListEqual(T)				rvListEqual(T)

/* List iterators */
#define RvListIter(T)				_RvListIter##T
#define rvListIterData(i)			(&(i)->data)
#define rvListIterPrev(i)			((i)->prev)
#define rvListIterNext(i)			((i)->next)
#define rvListIterEqual(a, b)		((a) == (b))
#define rvListIterCopy(a, b)		((a) = (b))

/* Aliases for naming problem */
#define RvListIterData(i)			rvListIterData(i)
#define RvListIterPrev(i)			rvListIterPrev(i)
#define RvListIterNext(i)			rvListIterNext(i)
#define RvListIterEqual(a, b)		rvListIterEqual(a, b)
#define RvListIterCopy(a, b)		rvListIterCopy(a, b)

/* Reverse List iterators */
#define RvListRevIter(T)			_RvListRevIter##T
#define rvListRevIterData(i)		(&(i)->data)
#define rvListRevIterPrev(i)		((i)->next)
#define rvListRevIterNext(i)		((i)->prev)
#define rvListRevIterEqual(a, b)	((a) == (b))
#define rvListRevIterCopy(a, b)	    ((a) = (b))

/* Aliases for naming problem */
#define RvListRevIterData(i)		rvListRevIterData(i)
#define RvListRevIterPrev(i)		rvListRevIterPrev(i)
#define RvListRevIterNext(i)		rvListRevIterNext(i)
#define RvListRevIterEqual(a, b)	rvListRevIterEqual(a, b)
#define RvListRevIterCopy(a, b)	    rvListRevIterCopy(a, b)

/* Constant List iterators */
#define RvListConstIter(T)			_RvListConstIter##T
#define rvListConstIterData(i)		(&(i)->data)
#define rvListConstIterPrev(i)		((i)->prev)
#define rvListConstIterNext(i)		((i)->next)
#define rvListConstIterEqual(a, b)	((a) == (b))
#define rvListConstIterCopy(a, b)	((a) = (b))

/* Aliases for naming problem */
#define RvListConstIterData(i)		rvListConstIterData(i)
#define RvListConstIterPrev(i)		rvListConstIterPrev(i)
#define RvListConstIterNext(i)		rvListConstIterNext(i)
#define RvListConstIterEqual(a, b)	rvListConstIterEqual(a, b)
#define RvListConstIterCopy(a, b)	rvListConstIterCopy(a, b)


#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

#endif

