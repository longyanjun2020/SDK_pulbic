/*
 * Copyright 2010 MStarSemi. All Rights Reserved.
 * $Id$
 */

#ifndef _JSR_HELPER_H_
#define _JSR_HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


/**
 * Create a list
 *
 * @param the handle of the list or 0 if the list can't be create.
 */
int jsr_helper_list_create();

/**
 * Check if the list contains the given element.
 *
 * @param handle the handle of the list.
 * @param element the element to be checked.
 * @return TRUE if the list contains the element, FALSE otherwise.
 **/
int jsr_helper_list_contains(int handle, void* element);

/**
 * Add an element to the list. The element can't be added into the list
 * if it has been in the list already.
 *
 * @param handle the handle of the list.
 * @param element the element to be added.
 * @return TRUE if the element is added to the list, FALSE otherwise.
 */
int jsr_helper_list_add(int handle, void* element);

/**
 * Get an element from the list with a given index
 *
 * @param handle the handle of the list
 * @param index index at which the specified element is to be get.
 * @return the element or NULL if nothing is get
 */
void* jsr_helper_list_get(int handle, int index);

/**
 * Remove the given element from the list
 *
 * @param handle the handle of the list
 * @param element the element to be removed
 * @return TRUE if the element is removed from the list, FALSE otherwise.
 */
int jsr_helper_list_remove(int handle, void* element, int force);

/**
 * Return Returns the number of elements in this list.
 *
 * @param handle the handle of the list
 * @return the number of elements in this list.
 */
int jsr_helper_list_size(int handle);

/**
 * Destroy the list, the handle must be null while calling the
 * method.
 *
 * @handle the handle of the list
 * @return TRUE if the list is destroyed, FALSE otherwise.
 */
int jsr_helper_list_destroy(int handle);

#ifdef __cplusplus
}
#endif

#endif // _JNI_MMAPI_H_