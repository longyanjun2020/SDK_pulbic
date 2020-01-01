
#ifndef _CSS_STACK_0P_H_
#define _CSS_STACK_0P_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sa_stack.h>
#include <html_tag.h>
/*
 * All the following declarations are encapsulations for SA stack
 * and ensurance for compiling of unit test(uapp_wap_css2, uapp_wap_css2_unit) independently
 */
#ifdef NCC_BROWSER_SA_UNIT
/* the following definations just for sa unit test */

/**
 * Stack info used in querying
 */
typedef struct _MLParsing_Stack MLParsing_Stack;

/**
 * Stack node info used in querying
 */
typedef struct _MLParsing_StackNode MLParsing_StackNode;

struct _MLParsing_StackNode
{
    HTMLTAG htmlTag;
    int8_t * className;
    int8_t * idName;
    int32_t pseudo;
} ;

struct _MLParsing_Stack
{
    MLParsing_StackNode * stackBase;
    int32_t         top;
    int32_t         depth;
    int32_t         visitIndex;
} ;

/**
 * Get the number of elements in stack.
 * \param stack pointer to stack to be visited
 * \return the number of elements
 */
int32_t CSS_getStackSize(MLParsing_Stack * stack);

/**
 * Get element at appointed position
 * \param  stack pointer to stack
 * \position the position
 * \return
 *      pointer to element if success
 *      NULL if failed
 */
const MLParsing_StackNode *CSS_getElementAt(MLParsing_Stack * stack, int32_t position);

#define CSS_GET_STACKNODE_TAG_NAME(_a_)    ((_a_)->htmlTag)
#define CSS_GET_STACKNODE_TAG_CLASS(_a_)   ((_a_)->className)
#define CSS_GET_STACKNODE_TAG_ID(_a_)      ((_a_)->idName)
#define CSS_GET_STACKNODE_TAG_PSEUDO(_a_)  ((_a_)->pseudo)

/* The following will be used by unit test only, should be never invoked by normal code */
#define CSS_MAX_STACK_DEPTH     (16)

/**
 * Create a new stack
 * \param void
 * \return
 *      Pointer to new created stack if success
 *      NULL if failed
 */
MLParsing_Stack * CSS_createStack();

/**
 * Destroy a stack
 * \param stack pointer to stack
 * \return void
 */
void CSS_destroyStack(MLParsing_Stack ** stack);

/**
 * Push a node into stack
 * \param stack pointer to stack
 * \param node pointer to node to be pushed
 * \return
 *      TURE if success
 *      FALSE if failed
 */
int32_t CSS_pushStack(MLParsing_Stack * stack, const MLParsing_StackNode * node);

/**
 * Pop a node from stack
 * \param stack pointer to stack
 * \return
 *      pointer to poped node if success
 *      NULL if failed
 */
MLParsing_StackNode *CSS_popStack(MLParsing_Stack *stack);

#else

/**
 * Stack info used in querying
 */
typedef struct _MLParsing_Stack MLParsing_Stack;

/**
 * Stack node info used in querying
 */
typedef T_DBA_StackNode MLParsing_StackNode;

struct _MLParsing_Stack
{
    int32_t stack;
};

int32_t CSS_getStackSize(MLParsing_Stack * stack);

const MLParsing_StackNode *CSS_getElementAt(MLParsing_Stack * stack, int32_t position);

#define CSS_GET_STACKNODE_TAG_NAME(_a_)    ((_a_)->element)
#define CSS_GET_STACKNODE_TAG_CLASS(_a_)   ((_a_)->className)
#define CSS_GET_STACKNODE_TAG_ID(_a_)      ((_a_)->idName)
#define CSS_GET_STACKNODE_TAG_PSEUDO(_a_)  ((_a_)->pseudo)

#endif /* NCC_BROWSER_SA */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CSS_STACK_0P_H_ */
