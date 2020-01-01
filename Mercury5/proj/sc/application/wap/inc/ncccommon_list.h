/**
 * @file ncccommon_list.h
 * Common List Service Layer
 *
 * Service API exposed by the Common List Module
 *
 * <!-- #interface list begin -->
 * \section ncccommon interface
 * - NCCCommon_list_newList()
 * - NCCCommon_list_deleteList()
 * - NCCCommon_list_addObject()
 * - NCCCommon_list_appendObject()
 * - NCCCommon_list_removeObject()
 * - NCCCommon_list_removeAllMatchedObject()
 * - NCCCommon_list_removeFirstObject()
 * - NCCCommon_list_removeLastObject()
 * - NCCCommon_list_removeAll()
 * - NCCCommon_list_removeAllList()
 * - NCCCommon_list_getFirstObject()
 * - NCCCommon_list_getLastObject()
 * - NCCCommon_list_getElementCount()
 * - NCCCommon_list_getObjectIndex()
 * - NCCCommon_list_getElementIndex()
 * - NCCCommon_list_getObjectByIndex()
 * - NCCCommon_list_removeObjectByIndex()
 * <!-- #interface list end -->
 */

#ifndef __NCC_COMMON_LIST_H__
#define __NCC_COMMON_LIST_H__

#include <ncc_types.h>
#include <ncccommon.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CommonList_s
{
    struct CommonList_s *pre;      /**< Previous node */
    struct CommonList_s *next;    /**< Next node */
    void *object;                           /**< Object */
} CommonList;

/**
 * Create a list
 * \return  If failed return NULL;otherwise return a pointer to the list.
 */
CommonList * NCCCommon_list_newList( void );

/**
 * Delete a list
 * \param me List pointer.
 * \return  If success return TRUE;otherwise return FALSE.
 */
int32_t  NCCCommon_list_deleteList(CommonList *me);

/**
 * Add a object to the current position of the list.
 * \param me  list pointer
 * \param newObject  object pointer.
 * \return  If success return TRUE;otherwise return FALSE.
 */
int32_t NCCCommon_list_addObject(CommonList *me, void *newObject);

/**
 * Append a object to tail of the list.
 * \param me  list pointer
 * \param newObject  object pointer
 * \return  If success return TRUE;otherwise return FALSE.
 */
int32_t NCCCommon_list_appendObject(CommonList * me, void * newObject);

/**
 *  Remove the specified object from the list.
 * \param me    list pointer
 * \param oldObject   object pointer
 * \return  If success return TRUE;otherwise return FALSE.
 * \attention Only remove the first found object from the list.
 *   if there are several matched object in the list.
 */
int32_t  NCCCommon_list_removeObject(CommonList * me, void * oldObject);

/**
 *  Remove all matched object from the list.
 * \param me    list pointer
 * \param oldObject   object pointer
 * \return  If success return TRUE;otherwise return FALSE.
 * \attention Remove the all matched object from the list.
 *   if there are several matched object in the list.
 */
int32_t  NCCCommon_list_removeAllMatchedObject (CommonList * me, void * oldObject);

/**
 * Remove the last object.
 * \param me    List pointer
 * \return  If failed return NULL;otherwise return a pointer to the object to be deleted.
 */
void *   NCCCommon_list_removeLastObject(CommonList * me);

/**
 * Remove the first object.
 * \param me    List pointer
 * \return  If failed return NULL;otherwise return a pointer to the object to delete.
 */
void *   NCCCommon_list_removeFirstObject(CommonList * me);

/**
 * Remove all lists and their object.
 * \param me    List pointer
 * \param pfree Memory free function handler.
 * \return  If success return TRUE;otherwise return FALSE
 */
int32_t NCCCommon_list_removeAll(CommonList *me, pubFreeFunc pfree);

/**
 * Remove all lists.
 * \param me List pointer.
 * \return  If success return TRUE;otherwise return FALSE
 */
int32_t NCCCommon_list_removeAllList(CommonList *me);

/**
 * Get the first object of the list.
 * \param me List pointer.
 * \return  If failed return NULL;otherwise return a pointer to the object.
 */
void * NCCCommon_list_getFirstObject  (CommonList * me);

/**
 *  Get the last object of the list.
 * \param me List pointer.
 * \return  If failed return NULL;otherwise return a pointer to the object.
 */
void * NCCCommon_list_getLastObject  (CommonList * me);

/**
 *  Get the element count of the list.
 * \param me List pointer.
 * \return  Return the element count.
 */
int32_t  NCCCommon_list_getElementCount(CommonList *me);

/**
 * Get index number of a object.
 * \param me    List pointer
 * \param object The list element.
 * \return  Return the index number of a object.
 */
int32_t  NCCCommon_list_getObjectIndex(CommonList * me, void * object);

/**
 * Get index number of a element.
 * \param me    List pointer
 * \param element The list element.
 * \return Return the index number of a element.
 */
int32_t  NCCCommon_list_getElementIndex(CommonList * me, CommonList * element);

/**
 * Get a object by its index.
 * \param me    List pointer
 * \param position The index number of list element.
 * \return  If failed return NULL;otherwise return a pointer to the object.
 */
void *   NCCCommon_list_getObjectByIndex(CommonList * me, int32_t position);

/**
 * Remove a object by its index number.
 * \param me    List pointer
 * \param position The index number of list element.
 * \return  If failed return NULL;otherwise return a pointer to the object to delete.
 */
void * NCCCommon_list_removeObjectByIndex(CommonList * me, int32_t position);


#ifdef __cplusplus
}
#endif

#endif /* __NCC_COMMON_LIST_H__ */

