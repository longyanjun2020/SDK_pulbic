/*
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file 
 *   LandmarkStore JSI
 */

#ifndef ___JKLOCATIONLANDMARKSTORE_H___
#define ___JKLOCATIONLANDMARKSTORE_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkLocationCommon.h"

/**
 * @addtogroup location_LandmarkStore
 *
 * @{
 */

/**
 *   landmark store handle type
 */
typedef JKHandle JKLocationLandmarkStoreHandle;

/**
 *   A data structure to store a category
 *
 *   This structure is used to pass a category to/from JBlend from/to
 *   the native system.
 *
 *   A category is used for grouping landmarks in a landmark store.
 */
typedef struct JKLocationCategory {
    /**
     *   Category name
     *
     *   Category name (e.g. restaurant, museum).
     */
    JKLocationString name;

    /**
     *   Flags of landmarks
     *
     *   The array of flags that indicates whether or not each landmark 
     *   in the landmark store belongs to this category.
     *   <i>landmarks[n]</i> is JK_TRUE if the n-th landmark belongs to this
     *   category. JK_FALSE, otherwise.
     *
     *   If there are no landmarks in the landmark store, this member
     *   points to invalid address.
     */
    JKSint8 *landmarks;
} JKLocationCategory;
    
/**
 *   A data structure to store a landmark information
 *
 *   This structure is used when passing a landmark information to/from
 *   JBlend from/to the native system.
 *
 *   A landmark represents a known location in a landmark store.
 */
typedef struct JKLocationLandmark {
    /**
     *   Landmark name
     *
     *   The name of the landmark. The name must be a valid character string.
     */
    JKLocationString name;

    /**
     *   Description
     *
     *   The detailed description of the Landmark. If no description is given, 
     *   the <i>str</i> member of <i>description</i> is #JK_NULL.
     */
    JKLocationString description;

    /**
     *   Coordinates
     *
     *   The coordinates of this landmark. If the coordinates are unknown, 
     *   the <i>isValid</i> member of <i>coordinates</i> is #JK_FALSE.
     */
    JKLocationCoordinates coordinates;

    /**
     *   Address information
     *
     *   The address information of the landmark. If no address information
     *   is available, the <i>isValid</i> member of <i>addressInfo</i> is #JK_FALSE.
     */
    JKLocationAddressInfo addressInfo;
} JKLocationLandmark;

/**
 *   Gets the list of landmark stores
 * 
 * @return
 *       If the operation succeeds, return the number of landmark stores in the native
 *       system, excluding the default landmark store.
 *       If an I/O error occurs, return #JK_LOCATION_ERROR_IO.
 *
 *   Create the list of landmark stores in the native system and return
 *   the number of elements in the list.
 *
 *   After this function is called, #JkLocationGetLandmarkStoreName() is
 *   called to obtain the landmark store names.  Prepare the list so that 
 *   landmark store names can be returned by that function in an order. 
 *   After all the landmark store names are obtained,
 *   #JkLocationReleaseLandmarkStoreList() is called to release the list 
 *   created in this function.
 *
 *   The sequence starting from this function to
 *   #JkLocationReleaseLandmarkStoreList() is never interrupted.
 *
 *   Whether or not the list should be created in a memory depends on the 
 *   native system. If the native system has capability to get the landmark 
 *   store name directly from the storage in turn, simply returning the number 
 *   of landmark stores is sufficient for this function.
 */
JKSint32 JkLocationGetLandmarkStoreList(void);

/**
 *   Gets a landmark store name
 * 
 * @param index
 *       The index of the landmark store name.
 *       The index is a zero-based number.
 * @param storeName
 *       A pointer to the #JKLocationString structure for putting the
 *       landmark store name.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If an I/O error occurs, return #JK_LOCATION_ERROR_IO.
 * 
 *   This function is called to obtain an item of the 
 *   landmark store name list that has been created by preceding
 *   #JkLocationGetLandmarkStoreList() call. Store the landmark store name 
 *   located at the position indicated by <i>index</i> in the memory area 
 *   designated by <i>storeName</i> parameter.
 *
 *   Landmark store names must be unique. If the terminal arrows
 *   multiple landmark stores with the same name, the landmark store
 *   names obtained by this function must be converted so that they 
 *   are distinguishable. An example of the conversion is postfix addition.
 *   
 *   The case sensitivity of landmark store names is implementation-dependent.
 */
JKSint32 JkLocationGetLandmarkStoreName(JKSint32 index, JKLocationString *storeName);

/**
 *   Releases the list of landmark stores
 * 
 *   Release the landmark store list created in the preceding
 *   #JkLocationGetLandmarkStoreList() call.
 */
void JkLocationReleaseLandmarkStoreList(void);

/**
 *   Creates a landmark store
 * 
 * @param storeName
 *       A pointer to the #JKLocationString structure containing the
 *       landmark store name.
 *       This parameter always contains valid string.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If it fails, return one of the following values.
 *       <ul>
 *         <li> #JK_LOCATION_ERROR_ILLEGAL_ARGUMENT<br>
 *             The name passed is too long or a landmark store
 *             with the same name already exists.
 *         <li> #JK_LOCATION_ERROR_IO<br>
 *             An I/O error occurred.
 *         <li> #JK_LOCATION_ERROR_NOT_SUPPORTED<br>
 *             The native system does not support creation of landmark stores.
 *         <li> #JK_LOCATION_ERROR_NO_MEMORY<br>
 *             Memory allocation failed.
 *       </ul>
 * <p>
 *   This function is called to create a new landmark store. The newly
 *   created landmark store must be empty. The native system must allow 
 *   the following operations on the created landmark store: 
 *   <ul>
 *    <li>to get the handle of the landmark store by #JkLocationOpenLandmarkStore(),
 *    <li>to delete the landmark store by #JkLocationDeleteLandmarkStore(), and
 *    <li>to get the landmark store name by #JkLocationGetLandmarkStoreName().
 *   </ul>
 *   Store information necessary for those operations in the terminal's storage 
 *   when creating landmark store.
 *   
 *   The case sensitivity of landmark store names is implementation-dependent.
 */
JKSint32 JkLocationCreateLandmarkStore(const JKLocationString *storeName);

/**
 *   Deletes a landmark store
 * 
 * @param storeName
 *       A pointer to the #JKLocationString structure containing the
 *       landmark store name.  
 *       This parameter always contains valid string.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If it fails, return one of the following values.
 *       <ul>
 *         <li> #JK_LOCATION_ERROR_IO<br>
 *              An I/O error occurred.
 *         <li> #JK_LOCATION_ERROR_NOT_SUPPORTED<br>
 *              The native system does not support deletion of landmark stores.
 *       </ul>
 * 
 * <p>
 *   This function is called to delete a landmark store. Delete all the
 *   information associated with the landmark store from the terminal's
 *   storage. If there is no landmark store of the name designated by 
 *   <i>storeName</i>, return #JK_LOCATION_OK without doing further action.
 *
 *   Even in the case that this function is called for an open
 *   landmark store (i.e. The one that JBlend obtained its handle by
 *   #JkLocationOpenLandmarkStore()), force deletion. After the deletion, 
 *   succeeding accesses to the landmark store must fail with #JK_LOCATION_ERROR_IO.
 *   
 *   The case sensitivity of landmark store names is implementation-dependent.
 */
JKSint32 JkLocationDeleteLandmarkStore(const JKLocationString *storeName);

/**
 *   Opens a landmark store
 * 
 * @param storeName
 *       A pointer to the #JKLocationString structure containing the
 *       landmark store name.  
 *       If the <i>str</i> member of the #JKLocationString structure
 *       is #JK_NULL, it indicates the default landmark store.
 * @return
 *       Return the handle of the open landmark store. The
 *       handle must be a unique and positive value.
 *       If opening landmark store fails by any reason, return
 *       #JK_INVALID_HANDLE.
 * 
 *   This function is called before the Java application accesses a
 *   landmark store. JBlend uses the handle obtained by this function
 *   when accessing to the landmark store by succeeding LandmarkStore 
 *   JSI function calls.
 *   
 *   The case sensitivity of landmark store names is implementation-dependent.
 *
 *   Do not access to the terminal's storage for the operation requested to 
 *   this function.
 */
JKLocationLandmarkStoreHandle JkLocationOpenLandmarkStore(const JKLocationString *storeName);

/**
 *   Closes a landmark store
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * 
 *   This function is called when the landmark store obtained by 
 *   #JkLocationOpenLandmarkStore() becomes unnecessary.
 *   Release all the memory for holding the information associated with 
 *   the landmark store indicated by <i>hLandmarkStore</i>.
 */
void JkLocationCloseLandmarkStore(JKLocationLandmarkStoreHandle hLandmarkStore);

/**
 *   Starts acquisition of landmark store data
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If it fails, return one of the following values.
 *       <ul>
 *         <li> #JK_LOCATION_ERROR_IO<br>
 *             An I/O error occurred.
 *         <li> #JK_LOCATION_ERROR_NO_MEMORY<br>
 *             Memory allocation failed.
 *       </ul>
 * <p>
 *   This function is called to obtain landmark store data. Prepare for
 *   the succeeding acquisition of the landmark store information.
 *
 *   After this function is called, JBlend calls
 *   #JkLocationGetNumCategories(), #JkLocationGetNumLandmarks(),
 *   #JkLocationGetCategory(), and #JkLocationGetLandmark() to get all
 *   the landmark store information.  When the acquisition operation 
 *   completes, JBlend calls #JkLocationEndGetLandmarkStoreData() to 
 *   indicate the completion. These calling sequence is never interrupted.
 *
 *   If the native system prefers, it may read all the data from terminal's
 *   storage for the first time this function is called and the read data
 *   may be used in the succeeding calls of those functions.
 * @see #JkLocationEndGetLandmarkStoreData()
 */
JKSint32 JkLocationBeginGetLandmarkStoreData(JKLocationLandmarkStoreHandle hLandmarkStore);

/**
 *   Ends acquisition of landmark store data
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 *
 *   This function is called to end acquisition of the landmark store data.
 *
 *   Finalize the process that began with #JkLocationBeginGetLandmarkStoreData().
 * @see #JkLocationBeginGetLandmarkStoreData()
 */
void JkLocationEndGetLandmarkStoreData(JKLocationLandmarkStoreHandle hLandmarkStore);

/**
 *   Gets the number of categories
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @return
 *       Return the number of categories in given landmark store.
 *       If an I/O error occurs, return #JK_LOCATION_ERROR_IO.
 * @see #JkLocationBeginGetLandmarkStoreData()
 */
JKSint32 JkLocationGetNumCategories(JKLocationLandmarkStoreHandle hLandmarkStore);

/**
 *   Gets a category
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @param index
 *       The index of the category.
 *       The index is a zero-based number.
 * @param category
 *       A pointer to the memory area for putting a pointer to the 
 *       #JKLocationCategory structure containing the category information.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If an I/O error occurs, return #JK_LOCATION_ERROR_IO.
 *
 *   Put a pointer to the landmark store category located at the position indicated by 
 *   the <i>index</i> parameter, in the memory area designated by the <i>category</i> parameter.
 *
 *   The stored pointer must remain valid until #JkLocationGetCategory() is called again
 *   or until #JkLocationEndGetLandmarkStoreData() is called.
 * @see #JkLocationBeginGetLandmarkStoreData()
 */
JKSint32 JkLocationGetCategory(JKLocationLandmarkStoreHandle hLandmarkStore, JKSint32 index, JKLocationCategory **category);

/**
 *   Adds a category
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @param category
 *       A pointer to the #JKLocationCategory structure containing 
 *       the category information to be added.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If it fails, return one of the following values.
 *       <ul>
 *         <li> #JK_LOCATION_ERROR_IO<br>
 *             An I/O error occurred.
 *         <li> #JK_LOCATION_ERROR_NOT_SUPPORTED<br>
 *             The native system does not support adding Categories.
 *       </ul>
 *
 * <p> 
 *   Add the given category to the end of given landmark store. Writing
 *   to the terminal's storage must be completed within this function.
 *
 *   JBlend assures that the new category does not have the same name with
 *   any other existing categories in the landmark store.
 *
 *   At least 32 characters of category name must be stored. 
 *   The native system can specify a value of 32 or more as the maximum character length of a category name.
 *   JBlend obtains the value as a JBlend customization property value by 
 *   calling JkOptionGetString() passing "location_category_max_length" as the property name.
 *   
 *   When a Java application passes to the <code>LandmarkStore##addCategory</code> method 
 *   a category name which exceeds the maximum length limit, JBlend truncates the name to the maximum length.
 *   If this results a duplicated category name, JBlend throws an <code>IllegalArgumentException</code>
 *   to the Java application without calling this function.
 *   If the maximum length is specified as 0, JBlend does not perform category name truncation.
 *   That is, this function is called, and the native system must modify the category name if necessary.
 *   The default value of the maximum length is 0. 
 *   
 *   This function is never called during the acquisition of landmark store
 *   data (i.e. from #JkLocationBeginGetLandmarkStoreData() to
 *   #JkLocationEndGetLandmarkStoreData()).
 */
JKSint32 JkLocationAddCategory(JKLocationLandmarkStoreHandle hLandmarkStore, const JKLocationCategory *category);

/**
 *   Updates a category
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @param index
 *       The index of the category.
 *       The index is a zero-based number.
 * @param category
 *       A pointer to the #JKLocationCategory structure containing the 
 *       category information to be updated.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If it fails, return #JK_LOCATION_ERROR_IO.
 *
 *   Update the landmark store category located at the position
 *   <i>index</i> by the information passed by the <i>category</i> parameter.
 *   Writing to the terminal's storage must be completed within this function.
 *
 *   This function is called to add/remove a Landmark to/from a
 *   category. The <i>name</i> member of the #JKLocationCategory structure passed
 *   by the <i>category</i> parameter is the same as the previous category.
 *   Only the <i>landmarks</i> member is different.
 *
 *   This function is never called during acquisition of landmark store
 *   data (i.e. from #JkLocationBeginGetLandmarkStoreData() to
 *   #JkLocationEndGetLandmarkStoreData()).
 */
JKSint32 JkLocationUpdateCategory(JKLocationLandmarkStoreHandle hLandmarkStore, JKSint32 index, const JKLocationCategory *category);

/**
 *   Deletes a category
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @param index
 *       The index of the category to be deleted.
 *       The index is a zero-based number. 
 *       When a negative value is passed, return a value indicating whether or not the native system supports deletion of categories.
 * @return
 *       When a negative value is designated in the <i>index</i> parameter,
 *       and the native system supports deletion of categories, return #JK_LOCATION_ERROR_IO; 
 *       otherwise return #JK_LOCATION_ERROR_NOT_SUPPORTED.
 *       When a value of 0 or more is designated in the <i>index</i> parameter,
 *       and the delete operation succeeds, return #JK_LOCATION_OK; 
 *       if it fails, return one of the following values.
 *       <ul>
 *         <li> #JK_LOCATION_ERROR_IO<br>
 *             An I/O error occurred.
 *         <li> #JK_LOCATION_ERROR_NOT_SUPPORTED<br>
 *             The native system does not support deletion of Categories.
 *       </ul>
 * <p>
 *   JBlend calls this function passing a negative value in the <i>index</i> 
 *   parameter to determine whether or not the native system supports deletion of categories.
 *   If it supports deletion, JBlend again calls this function to request deletion.
 *
 *   If this function is called passing in <i>index</i> a value of 0 or more, 
 *   delete the information of the category positioned at <i>index</i> in the designated landmark store.
 *   Writing to the terminal's storage must be completed within 
 *   this function.
 *
 *   After the deletion, re-assign indices to the categories located at
 *   positions after <i>index</i>.
 *
 *   This function is never called during acquisition of landmark store
 *   data (i.e. from #JkLocationBeginGetLandmarkStoreData() to
 *   #JkLocationEndGetLandmarkStoreData()).
 */
JKSint32 JkLocationDeleteCategory(JKLocationLandmarkStoreHandle hLandmarkStore, JKSint32 index);

/**
 *   Gets the number of landmarks
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @return
 *       Return the total number of landmarks in the designated landmark store.
 *       If an I/O error occurs, return #JK_LOCATION_ERROR_IO.
 * @see #JkLocationBeginGetLandmarkStoreData()
 */
JKSint32 JkLocationGetNumLandmarks(JKLocationLandmarkStoreHandle hLandmarkStore);

/**
 *   Gets a landmark
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @param index
 *       The index of the landmark.
 *       The index is a zero-based number.
 * @param landmark
 *       A pointer to the memory area for putting a pointer to the 
 *       #JKLocationLandmark structure containing the landmark information.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If an I/O error occurs, return #JK_LOCATION_ERROR_IO.
 *
 *   Put a pointer to the landmark located at the position indicated by 
 *   <i>index</i> in the memory area designated by the <i>landmark</i> parameter.
 *
 *   The stored pointer must remain valid until #JkLocationGetLandmark() is called again
 *   or until #JkLocationEndGetLandmarkStoreData() is called.
 * @see #JkLocationBeginGetLandmarkStoreData()
 */
JKSint32 JkLocationGetLandmark(JKLocationLandmarkStoreHandle hLandmarkStore, JKSint32 index, JKLocationLandmark **landmark);

/**
 *   Adds a landmark
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @param landmark
 *       A pointer to the #JKLocationLandmark structure containing 
 *       the landmark information to be added.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If it fails, return #JK_LOCATION_ERROR_IO.
 * <p>
 *   Add the given landmark to the end of given landmark store. Writing
 *   to the terminal's storage must be completed within this function.
 *
 *   The added landmark should not belong to any category at the initial state.
 *
 *   When adding a Landmark, every categories in the landmark store 
 *   must be updated so that they do not contain the newly added landmark.
 *   As the result, the <i>landmarks</i> member of every
 *   category information should have an extra entry with the value
 *   #JK_FALSE for the next time JBlend acquires categories.
 *
 *   At least 32 characters of landmark name must be stored. 
 *   The native system can specify a value of 32 or more as the maximum character length of a landmark name.
 *   JBlend obtains the value as a JBlend customization property value by 
 *   calling JkOptionGetString() passing "location_landmark_max_length" as the property name.
 *   
 *   When a Java application passes to the <code>LandmarkStore##addLandmark</code> method 
 *   a landmark name which exceeds the maximum length limit, JBlend truncates the name to the maximum length.
 *   If this results a duplicated landmark name, JBlend throws an <code>IllegalArgumentException</code>
 *   to the Java application without calling this function.
 *   If the maximum length is specified as 0, JBlend does not perform landmark name truncation.
 *   That is, this function is called, and the native system must modify the landmark name if necessary.
 *   The default value of the maximum length is 0. 
 *
 *   The native system must assure that an empty landmark store has
 *   enough capacity to store a landmark with 30 characters long for every
 *   character string properties of a landmark.
 *
 *   This function is never called during acquisition of landmark store
 *   data (i.e. from #JkLocationBeginGetLandmarkStoreData() to
 *   #JkLocationEndGetLandmarkStoreData()).
 */
JKSint32 JkLocationAddLandmark(JKLocationLandmarkStoreHandle hLandmarkStore, const JKLocationLandmark *landmark);

/**
 *   Updates a landmark
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @param index
 *       The index of the Landmark.
 *       The index is a zero-based number.
 * @param landmark
 *       A pointer to the #JKLocationLandmark structure containing the 
 *       landmark information to be updated.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If it fails, return #JK_LOCATION_ERROR_IO.
 *
 *   Update the landmark located at the position 
 *   <i>index</i> by the information passed by the <i>landmark</i> parameter.
 *   Writing to the terminal's storage must be completed within this function.
 *
 *   This function is never called during acquisition of landmark store
 *   data (i.e. from #JkLocationBeginGetLandmarkStoreData() to
 *   #JkLocationEndGetLandmarkStoreData()).
 */
JKSint32 JkLocationUpdateLandmark(JKLocationLandmarkStoreHandle hLandmarkStore, JKSint32 index, const JKLocationLandmark *landmark);

/**
 *   Deletes a landmark
 * 
 * @param hLandmarkStore
 *       The handle of the landmark store.
 *       The value returned by #JkLocationOpenLandmarkStore() is designated.
 * @param index
 *       The index of the Landmark to be deleted.
 *       The index is a zero-based number.
 * @return
 *       If the operation succeeds, return #JK_LOCATION_OK.
 *       If it fails, return  #JK_LOCATION_ERROR_IO.
 * <p>
 *   Delete the landmark located at the position indicated by
 *   <i>index</i>. Writing to the terminal's storage must be completed within 
 *   this function.
 *
 *   After the deletion, re-assign indices to the landmarks located at
 *   positions after <i>index</i>, and reflect the deletion to all 
 *   categories. As a result, the deleted item must be removed from the 
 *   elements in the array proviced in <i>landmarks</i> of categories 
 *   when they are acquired in the next time.
 *
 *   This function is never called during acquisition of landmark store
 *   data (i.e. from #JkLocationBeginGetLandmarkStoreData() to
 *   #JkLocationEndGetLandmarkStoreData()).
 */
JKSint32 JkLocationDeleteLandmark(JKLocationLandmarkStoreHandle hLandmarkStore, JKSint32 index);

#ifdef __cplusplus
}
#endif

#endif /* !___JKLOCATIONLANDMARKSTORE_H___ */

/** @} end of group */
