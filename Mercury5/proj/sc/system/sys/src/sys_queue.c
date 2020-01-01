/** @file sys_queue.c
 * @author Piazza.Lo
 * @date 04/07/2010
 *
 * General queue utility implementation.
 */

#include "sys_queue.h"
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "sys_traces.ho"
#include "sys_sys_bootinit.h"

/************************************************************************/
/*                                                   Macros                                                              */
/************************************************************************/
#define QUELE_LOG_LEVEL  (_SYS|LEVEL_16)
#define QUELE_LOG_FATAL (QUELE_LOG_LEVEL|FATAL)
#define QUEUE_NODES_MAX 128

/************************************************************************/
/*                                                   Types                                                               */
/************************************************************************/


/************************************************************************/
/*                                                   Variables                                                          */
/************************************************************************/
static Node_t gQueueNodes[QUEUE_NODES_MAX];
static pNode_t gPtrFirstFreeNode = (pNode_t)&gQueueNodes[0];
static u32 gNodesCount = QUEUE_NODES_MAX;

/************************************************************************/
/*                                                   Functions                                                          */
/************************************************************************/
static pNode_t GetNode(void)
{
	pNode_t N;

	/* execption if no node availlable */
	if (NULL == gPtrFirstFreeNode)
		_ERROR((QUELE_LOG_FATAL, "[SysQueue:%d] no available node", __LINE__));

	N = gPtrFirstFreeNode;

	gPtrFirstFreeNode = N->Next;

	gNodesCount--;

	return N;
}


static void FreeNode(pNode_t N)
{   
	/* the free node is queue first */
	N->Next = gPtrFirstFreeNode;

	gPtrFirstFreeNode = N;

	gNodesCount++;

	if (QUEUE_NODES_MAX < gNodesCount)
		_ERROR((QUELE_LOG_FATAL, "[SysQueue:%d] nodes overflow", __LINE__));
}


__ONCE_CALL_ON_BOOT__ void SysQueueRtInit(void)
{
	int i_n;
	pNode_t N = (pNode_t)&gQueueNodes[0];
	
	for (i_n=1;i_n<QUEUE_NODES_MAX;i_n++, N = N->Next)
		N->Next = (pNode_t)&gQueueNodes[i_n];

	N->Next = NULL;
	
	gPtrFirstFreeNode = (pNode_t)&gQueueNodes[0];
}

QueueErr_e SysEnQueue(pMsQueue_t Q, void *E)
{
	MsIntMask_e eIntMask;
	pNode_t N;

	if (NULL == Q)
		return QUEUE_INVALID_PARAM;

	eIntMask = MsDisableInterrupt();

	if (0 == Q->count && (NULL != Q->First || NULL != Q->Last))
	{
		MsEnableInterrupt(eIntMask);
		return QUEUE_NON_INITIALIZE;
	}

	N = GetNode();
	N->Element = E;
	N->Next = NULL;

	if (NULL != Q->First)
	{
		(Q->Last)->Next = N;
		Q->Last = N;
	}
	else
	{
		if (0 != Q->count)
			_ERROR((QUELE_LOG_FATAL, "[SysEnQueue:%d] lr=<SYMBOL> (0x%0.8x) in-consistent queue 0x%08X", __LINE__, Q));
		Q->First = Q->Last = N;
	}
	
	Q->count++;
	
	MsEnableInterrupt(eIntMask);
	
	return QUEUE_OK;
}


QueueErr_e SysEnQueueBySort(pMsQueue_t Q, void *E)
{
	MsIntMask_e eIntMask;
	pNode_t N, preN, nextN;
	int i_n;
	
	if (NULL == Q)
		return QUEUE_INVALID_PARAM;

	eIntMask = MsDisableInterrupt();

	if (0 == Q->count && (NULL != Q->First || NULL != Q->Last))
	{
		MsEnableInterrupt(eIntMask);
		return QUEUE_NON_INITIALIZE;
	}

	N = GetNode();
	N->Element = E;
	N->Next = NULL;
	if (NULL != Q->First)
	{
		nextN = Q->First;
		for (i_n=0, preN=nextN;i_n<Q->count;i_n++, preN=nextN, nextN=nextN->Next)
		{
			if ((u32)E < (u32)nextN->Element)
				break;
		}

		N->Next = nextN;

		if (nextN == Q->First)
			Q->First = N;
		else
		{
			preN->Next = N;
			if (NULL == nextN)
				Q->Last = N;
		}
	}
	else
	{
		if (0 != Q->count)
			_ERROR((QUELE_LOG_FATAL, "[SysEnQueue:%d] lr=<SYMBOL> (0x%0.8x) in-consistent queue 0x%08X", __LINE__, Q));
		Q->First = Q->Last = N;
	}
	
	Q->count++;
	
	MsEnableInterrupt(eIntMask);
	
	return QUEUE_OK;
}


void *SysDeQueue(pMsQueue_t Q)
{
	MsIntMask_e eIntMask;
	pNode_t N;
	void *E;

	if (NULL == Q || 0 == Q->count)
		return NULL;

	eIntMask = MsDisableInterrupt();
	N=Q->First;

	if (NULL == N && 0 < Q->count)
		_ERROR((QUELE_LOG_FATAL, "[SysDeQueue:%d] count=%d underflow", __LINE__, Q->count));

	E = N->Element;

	if (Q->First != Q->Last)
		Q->First = N->Next;
	else
	{
		if (1 < Q->count)
			_ERROR((QUELE_LOG_FATAL, "[SysDeQueue:%d] count=%d overflow", __LINE__, Q->count));
		Q->First = Q->Last = NULL;
	}
	
	FreeNode(N);
	
	Q->count--;

	MsEnableInterrupt(eIntMask);
	
	return E;
}


void *SysDeleteQueue(pMsQueue_t Q, void *E)
{
	MsIntMask_e eIntMask;
	pNode_t N, preN;
	int i_n;

	if (NULL == Q || 0 == Q->count)
		return NULL;

	eIntMask = MsDisableInterrupt();
	N=Q->First;

	if (NULL == N && 0 < Q->count)
		_ERROR((QUELE_LOG_FATAL, "[SysDeleteQueue:%d] count=%d underflow", __LINE__, Q->count));

	for (i_n=0, preN=N;i_n<Q->count;i_n++, preN=N, N=N->Next)
	{
		if (E == N->Element)
			break;
	}

	if (NULL == N)
		_ERROR((QUELE_LOG_FATAL, "[SysDeleteQueue:%d] no node is found 0x%08X", __LINE__, Q));

	if (N == Q->First)
	{
		if (N == Q->Last)
		{
			if (1 < Q->count)
				_ERROR((QUELE_LOG_FATAL, "[SysDeleteQueue:%d] count=%d overflow", __LINE__, Q->count));
			Q->First = Q->Last = NULL;
		}
		else
			Q->First = N->Next;
	}
	else
	{
		preN->Next = N->Next;
		if (NULL == N->Next)
			Q->Last = preN;
	}

	FreeNode(N);
	
	Q->count--;

	MsEnableInterrupt(eIntMask);
	
	return E;
}

