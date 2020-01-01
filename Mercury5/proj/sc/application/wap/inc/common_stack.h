/*
 * Copyright 2006 NCC Inc. All Rights Reserved.
 * $Id: //depot/dev/base/inc/uapps/common/common_stack.h#1 $
 */

/*
 *  Common stack Interface
 */

#ifndef __COMMON_STACK_H_
#define __COMMON_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ncc_types.h>

/*
 * this is just a initial version of dynamic stack, just aim for layout's needs,
 * you can refactor it by adding more methods for it if you requir it
 */

typedef struct _CommonStack CommonStack;

/* invalid index for common stack */
#define COMMON_STACK_INVALID_INDEX  (-1)

/**
 * common stack delete element destructor function.
 */
typedef void (*CommonStackElementDestructor) (void *element);

struct _CommonStack {
    int32_t  capacity;           /**< the max number of elements in the dynamic stack */
    int32_t  sp;                /**< the  stack pointer*/
    int32_t  elemSize;           /**< the size of stack element */
    int8_t * stack;              /**< the buffer of stack */
    CommonStackElementDestructor destructor;     /**< element destructor destructor function */
};

/**
 * get the num of the elements in the stack
 */
#define COMMON_STACK_GET_NUM_OF_ELEMENTS( _stack_ ) ((_stack_)->sp + 1)

/**
 * get the size of element in the stack
 */
#define COMMON_STACK_GET_SIZE_OF_ELEMENT( _stack_ ) ((_stack_)->elemSize)

/**
 * get the base address of the dynamic stack
 */
#define COMMON_STACK_GET_STACK_BASE_ADDR( _stack_ ) ((_stack_)->stack)

/**
 * create a stack container according capacity and element size
 *
 * \param capacity the initial capacity num of elements for the stack
 * \param size the size of an stack element
 * \param destructor element destructor destructor function
 *
 * \return CommonStack* the created common stack , null if failed
 */
CommonStack *commonStack_new(int32_t capacity, int32_t elemSize, CommonStackElementDestructor destructor);

/**
 * destroy  a stack container
 *
 * \param stack the reference to the common stack
 *
 * \return void
 */
void commonStack_destroy(CommonStack ** stack);

/**
 * clear the content of the stack container
 *
 * \param stack the reference to the common stack
 *
 * \return void
 */
void commonStack_clear(CommonStack * stack);

/**
 * add element to a stack container
 *
 * \param stack the reference to the common stack container
 * \param element the element to be added to the stack
 *
 * \return int32_t  true for success else failed
 */
int32_t commonStack_push(CommonStack * stack, const void *element);

/**
 * add element to a stack container
 *
 * \param stack the reference to the common stack container
 *
 * \return ref to the poped element
 */
void * commonStack_pop(CommonStack * stack);

/**
 * get a  element from a stack container  by it's index
 *
 * \param stack the reference to the common stack container
 * \param index the index of the element in the stack
 *
 * \return void*  null if failed , !null if success
 */
void *commonStack_elementAt(const CommonStack * stack, int32_t index);

/**
 * get a  element from a stack container  by it's reverse index (index from the stack top)
 *
 * \param stack the reference to the common stack container
 * \param rindex the reverse index from the stack top
 *
 * \return void*  null if failed , !null if success
 */
void *commonStack_elementAtRIndex(const CommonStack * stack, int32_t rindex);

/**
 * get top element of a stack container
 *
 * \param stack the reference to the common stack container
 *
 * \return void*  null if failed , !null if success
 */
void * commonStack_getTopElement(const CommonStack * stack);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_STACK_H_ */
