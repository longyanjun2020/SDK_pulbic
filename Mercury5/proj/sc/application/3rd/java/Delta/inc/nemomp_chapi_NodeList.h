#ifndef __NEMOMP_CHAPI_NODE_LIST_H
#define __NEMOMP_CHAPI_NODE_LIST_H

typedef struct Node
{
/*public:*/
    void *pData;

/*private:*/
    struct Node *pNext;
    struct Node *pPrev;
}Node, *pNode;

/* callbacks for NodeList */

/* returns true if a == b */
typedef nm_bool (*CompareNodeItemsFunctionPointer)( void *pNode1, void *pItem );
/* destroys item (i.e. calls destructor and frees its mem) */
typedef void (*FreeNodeItemFunctionPointer)( void *pData );

typedef struct NodeList
{
	Node *pHead;
	Node *pTail;
	int length;
	FreeNodeItemFunctionPointer fpDestroyData;
	CompareNodeItemsFunctionPointer fpCompareItems;
}NodeList, *pNodeList;

typedef enum
{
    NODE_LIST_NO_ERROR = 0,
    NODE_LIST_MEMORY_ALLACTION_FAILURE = 101,
} node_list_error_code_enum;

NodeList *NodeList_create(void);
void NodeList_free(NodeList *pSelf);

NodeList *NodeList_constructor(NodeList *pSelf,
							FreeNodeItemFunctionPointer fpDataDestructor,
							CompareNodeItemsFunctionPointer fpComparator);

void NodeList_destructor(NodeList *pSelf);
void NodeList_addAfterTail(NodeList *pSelf, void *pItem, int *error_code);
void NodeList_addBeforeHead(NodeList* pSelf, void *pItem, int *error_code);
void NodeList_addAfter(NodeList *pSelf, Node *pNode, void *pItem, int *error_code);
void NodeList_addBefore(NodeList *pSelf, Node *pNode, void *pItem, int *error_code);
void NodeList_insertAfter(NodeList *pSelf, Node *pNode, Node *pNewNode);
void NodeList_insertBefore(NodeList *pSelf, Node *pNode, Node *pNewNode);
void *NodeList_getHead(NodeList *pSelf);
void *NodeList_getTail(NodeList *pSelf);
/*const */int NodeList_length(NodeList *pSelf);

Node *NodeList_getFirstItem(NodeList *pSelf);
Node *NodeList_getLastItem(NodeList *pSelf);
Node *NodeList_next(NodeList *pSelf, Node *pNode);
Node *NodeList_prev(NodeList *pSelf, Node *pNode);

void NodeList_remove(NodeList *pSelf, Node *pNode, nm_bool freeNodeMemory);
void NodeList_removeAll(NodeList *pSelf, nm_bool freeNodeMemory);
Node *NodeList_find(NodeList *pSelf, void *pItem);

#endif /* __NEMOMP_CHAPI_NODE_LIST_H */

