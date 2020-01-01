/*
 * Copyright 2006 NCC Inc. All Rights Reserved.
 * $Id: //depot/dev/base/inc/uapps/common/common_vector.h#1 $
 */

/*
 *  Vector Interface
 */
#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ncc_types.h>

typedef void *VectorItem;

typedef struct {
    int32_t capacity;           /* the max item that the current verctor can contain */
    int32_t size;               /* num of the items in the verctor */
    VectorItem *items;
} Vector;

/**
 * Function: Create and return a new empty vector.
 *
 * \return NULL if errors.
 */
Vector *vectorNew();

/**
 * Function:  Add element into vector v at position index.
 * Shifts the element currently at position index (if any) and any
 * subsequent elements to the right (adds one to their indices).
 * The index must be a value greater than or equal to 0
 * and less than or equal to the current size of the vector.
 *
 * \param v this pointer of vector
 * \param index index for inserting the element.
 * \param element the element to be inserted.
 * \return -1 if index is not valid, return 0 otherwise.
 */
int32_t vectorAddElementAt(Vector * v, int32_t index, VectorItem element);

/**
 * Fucntion: Append element to the end of vector v.
 *
 * \param v this pointer of vector
 * \param element the element to be inserted.
 * \return -1 if index is not valid, return 0 otherwise.
 */
int32_t vectorAddElement(Vector * v, VectorItem element);

/**
 * Fucntion: Remove all elements from vector v.
 * The vector will become empty after this function call returns.
 *
 * \param v this pointer of vector
 * \return void
 */
void vectorClear(Vector * v);

/**
 * Fucntion: judge if specified element in the vector
 *
 * \param v this pointer of vector
 * \param element the specified element
 * \return 1 if vector v contains element, return 0 otherwise.
 */
int32_t vectorContains(Vector * v, VectorItem element);

/**
 * Funciton: return the element stored at position index in vector v.
 *
 * \param v this pointer of vector
 * \param index the index for the specified element
 * \return VectorItem ,  found VectorItem at the index , NULL if failed.
 */
VectorItem vectorElementAt(Vector * v, int32_t index);

/**
 * Funciton: Deallocate the vector v.
 * v should points to NULL after this function returns.
 *
 * \param v the address of this pointer of vector
 * \return void
 */
void vectorFree(Vector ** v);

/**
 * Return the index of element in v.
 * If more than one occurrences of element appears in v,
 * return the smallest index of such occurrences.
 * If element does not exist in v, return -1.
 *
 * \param v this pointer of vector
 * \param element the specified element
 * \return the index for element in vector, -1 if failed.
 */
int32_t vectorIndexOf(Vector * v, VectorItem element);

/**
 * Return 1 if the vector v is empty, return 0 otherwise.
 *
 * \param v this pointer of vector
 * \return 1 if the vector v is empty, return 0 otherwise.
 */
int32_t vectorIsEmpty(Vector * v);

/**
 * Remove the first occurrence of element from vector v.
 * If the element is found, shift all component in v that
 * has a larger index than element to the left (reduce
 * their indices by 1).
 * Return -1 if the element is not found, return 0 otherwise.
 *
 * \param v this pointer of vector
 * \param element the specified element
 * \return -1 if the element is not found, return 0 otherwise.
 */
int32_t vectorRemoveElement(Vector * v, VectorItem element);

/**
 * Remove the element at position index from vector v and
 * return the element removed.
 * Each component in v with an index larger than index is
 * shifted to the left (subtract one to their indices).
 * The size of v is decreased by one.
 * The index must be a value greater than or equal to 0
 * and less than the current size of the vector.
 * If index is not valid, return NULL.
 *
 * \param v this pointer of vector
 * \param index the index for the specified element
 * \return the element removed, If index is not valid, return NULL.
 */
VectorItem vectorRemoveElementAt(Vector * v, int32_t index);

/**
 * Set the element at position index of vector v
 * to be the specified element.
 * The index must be a value greater than or equal to 0
 * and less than the current size of the vector.
 * Return -1 if index is not valid, return 0 otherwise.
 *
 * \param v this pointer of vector
 * \param index the index for the specified element
 * \param element the specified element
 * \return -1 if index is not valid, return 0 otherwise.
 */
int32_t vectorSetElementAt(Vector * v, int32_t index, VectorItem element);

/**
 * Get the current size of the vector.
 * Return the current size of the vector v.
 *
 * \param v this pointer of vector
 * \return the current size of the vector v.
 */
int32_t vectorSize(Vector * v);

#ifdef __cplusplus
}
#endif

#endif
