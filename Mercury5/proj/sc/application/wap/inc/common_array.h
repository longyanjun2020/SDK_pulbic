/*
 * Copyright 2006 NCC Inc. All Rights Reserved.
 * $Id: //depot/dev/base/inc/uapps/common/common_array.h#6 $
 */

/*
 *  Common Array Interface
 */

#ifndef __COMMON_ARRAY_H_
#define __COMMON_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ncc_types.h>
/*
 * this is just a initial version of dynamic array, just aim for wcss's needs,
 * you can refactor it by adding more methods for it if you requir it
 */

typedef struct _CommonArray CommonArray;

/* invalid index for common array */
#define COMMON_ARRAY_INVALID_INDEX  (-1)

/**
 * define the growth type of the common array
 */
enum _CommonnArrayGrowType {
    COMMON_ARRAY_GROW_BY_ADD,   /* the capacity of the array grow by add a fix value */
    COMMON_ARRAY_GROW_BY_MULTI  /* the capacity of the array grow by multiply a value */
};

typedef enum _CommonnArrayGrowType CommonnArrayGrowType;

/**
 * common array delete element destructor function.
 */
typedef void (*CommonArrayElementDestructor) (void *element);

struct _CommonArray {
    int32_t capacity;           /**< the max number of elements in the dynamic array */
    int32_t num;                /**< the  number of array elements */
    int32_t elemSize;           /**< the size of array element */
    int32_t growType;           /**< the grow type for this dynamic array */
    int8_t *array;                              /**< the buffer of array */
    CommonArrayElementDestructor destructor;     /**< element destructor destructor function */
};

/**
 * get the num of the elements in the array
 */
#define COMMON_ARRAY_GET_NUM_OF_ELEMENTS( _array_ ) ((_array_)->num)

/**
 * get the size of element in the array
 */
#define COMMON_ARRAY_GET_SIZE_OF_ELEMENT( _array_ ) ((_array_)->elemSize)

/**
 * get the base address of the dynamic array
 */
#define COMMON_ARRAY_GET_ARRAY_BASE_ADDR( _array_ ) ((_array_)->array)

/**
 * create a array container according capacity and element size
 *
 * \param capacity the initial capacity num of elements for the array
 * \param size the size of an array element
 * \param growType array size grow type.
 * \param destructor element destructor destructor function
 *
 * \return CommonArray* the created common array , null if failed
 */
CommonArray *commonArrayNew(int32_t capacity, int32_t elemSize, CommonnArrayGrowType growType, CommonArrayElementDestructor destructor);

/**
 * clear the array container
 *
 * \param array the reference to the common array
 *
 * \return void
 */
void commonArrayClear(CommonArray * array);

/**
 * destroy  a array container
 *
 * \param array the reference to the common array
 *
 * \return void
 */
void commonArrayDestroy(CommonArray ** array);

/**
 * add element to a array container
 *
 * \param array the reference to the common array container
 * \param element the element to be added to the array
 *
 * \return int32_t  COMMON_ARRAY_INVALID_INDEX for failed else the index of the newly added element
 */
int32_t commonArrayAddElement(CommonArray * array, const void *element);

/**
 * add element to a array container
 *
 * \param array the reference to the common array container
 * \param elements the point of elements to be added to the array
 * \param num num of the elements
 *
 * \return int32_t FALSE if failed , TRUE if success
 */
int32_t commonArrayAppend(CommonArray * array, const void *elements, int num);

/**
 * get a  element from a array container  by it's index
 *
 * \param array the reference to the common array container
 * \param index the index of the element in the array
 *
 * \return void*  null if failed , !null if success
 */
void *commonArrayElementAt(const CommonArray * array, int32_t index);

/**
 * delete a  element from a array container  by it's index
 *
 * \param array the reference to the common array container
 * \param index the index of the element in the array
 *
 * \return int32_t FALSE if failed , TRUE if success
 */
int32_t commonArrayRemoveAt(CommonArray * array, int32_t index);

/**
 * remove the empty element at the end of buffer.
 *
 * \param array the reference to the common array container
 *
 * \return int32_t -1 failed, others the true number of elements.
 */
int32_t commonArrayCompact(CommonArray * array);

/**
 * Duplicate the common array buffer.
 *
 * \param dst the destination buffer to copy to.
 * \param array the reference to the common array container
 * \param start the start of element to be copy
 * \param end the (last + 1) of element to be copy, so the copy length is end - start
 *
 * \return int32_t -1 failed, others the number of elements copyed
 */
int32_t commonArrayCopy(void *dst, const CommonArray * array, int start, int end);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_ARRAY_H_ */
