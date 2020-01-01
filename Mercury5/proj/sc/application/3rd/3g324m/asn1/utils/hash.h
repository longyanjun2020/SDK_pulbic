/***********************************************************************
        Copyright (c) 2003 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

/*
  ohash.c

  Opened hash table implementation


  Notes:
  Hash function is provided by the user.
  Hash function parameters may be duplicated in the hash table.
  Each table element holds list id. New collided parameter is
  positioned in the list corresponding to parameter key.
  Duplicated parameters following each other in the corresponding list.
  The hash size is the first prime number above the supplied hashSize.

  */

#ifndef _HASH_H
#define _HASH_H

#include "rvtypes.h"
#include "rvlog.h"

#ifdef __cplusplus
extern "C" {
#endif



/* Handle to a HASH object */
RV_DECLARE_HANDLE(HHASH);


/************************************************************************
 * Hash function type
 * Input:   key     - Pointer the key.
 *          length  - The size of the key, in bytes.
 *          initVal - An initial 4-byte value. Can be the previous hash,
 *                    or an arbitrary value. Passed as 0 by the hash
 *                    module.
 * Return : 32bit hash result
 ************************************************************************/
typedef RvUint32 (RVCALLCONV *hashFunc) (IN void *key, IN RvUint32 length, IN RvUint32 initVal);


/************************************************************************
 * Comparison function for elements
 * input  : key1, key2  - Keys to compare
 *          keySize     - Size of each key
 * return : RV_TRUE if elements are the same
 *          RV_FALSE otherwise
 ************************************************************************/
typedef RvBool (*hashCompareFunc) (IN void *key1, IN void* key2, IN RvUint32 keySize);


/************************************************************************
 * HASHEFunc
 * purpose: Definition of a general function on an RA element
 * input  : hHash   - Hash object
 *          elem    - Element to function on
 *          param   - Context to use for it
 * output : none
 * return : Pointer for the context to use on the next call to this
 *          HASHEFunc.
 ************************************************************************/
typedef void*(*HASHEFunc)(IN HHASH hHash, IN void* elem, void *param);



/*************************************************************************
 * hashDefaultFunc
 * ------------------------------------------------------------------------
 * General: A generic fast hashing function for hash-tables.
 *   Hash a variable-length key into a 32-bit value
 *   Originally by Bob Jenkins, December 1996, Public Domain.
 *   Use for hash table lookup, or anything where one collision in 2^32 is
 *   acceptable.  Do NOT use for cryptographic purposes.
 *
 *   Returns a 32-bit value.  Every bit of the key affects every bit of
 *   the return value.  Every 1-bit and 2-bit delta achieves avalanche.
 *   About 36+6len instructions.
 *   The best hash table sizes are powers of 2.  There is no need to do
 *   mod a prime (mod is so slow!).
 *
 * Return Value: RvUint32 hash value.
 * ------------------------------------------------------------------------
 * Arguments: 
 * Input:   key     - Pointer the key.
 *          length  - The size of the key, in bytes.
 *          initVal - An initial 4-byte value. Can be the previous hash,
 *                    or an arbitrary value.
 * Output:  None.
 *************************************************************************/
RVINTAPI RvUint32 RVCALLCONV
hashDefaultFunc(
    IN void         *key,
    IN RvUint32     length,
    IN RvUint32     initVal);


/************************************************************************
 * Default comparison function. Checks byte-by-byte.
 * input  : key1, key2  - Keys to compare
 *          keySize     - Size of each key
 * return : RV_TRUE if elements are the same
 *          RV_FALSE otherwise
 ************************************************************************/
RvBool
hashDefaultCompare(IN void *key1, IN void* key2, IN RvUint32 keySize);



/************************************************************************
 * hashConstruct
 * purpose: Create a HASH object, holding a hash table of keys and the
 *          actual data in an array
 * input  : numOfKeys       - Size of hash table.
 *                            This is the amount of keys available for use
 *                            It should be greater than the number of
 *                            elements in the table
 *          numOfElems      - Number of elements that will be stored
 *                            in the hash table
 *          hashFunc        - Hash function used on the data
 *          compareFunc     - Comparison function used on the keys
 *          keySize         - Size of the keys
 *          elemSize        - Size of the elements
 *          name            - Name of HASH (used in log messages)
 *          logMgr          - Log manager to use
 * output : none
 * return : Handle to RA constructed on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI HHASH RVCALLCONV
hashConstruct(
    IN  int             numOfKeys,
    IN  int             numOfElems,
    IN  hashFunc        hashFunc,
    IN  hashCompareFunc compareFunc,
    IN  int             keySize,
    IN  int             elemSize,
    IN  const RvChar*   name,
    IN  RvLogMgr*       logMgr);


/************************************************************************
 * hashDestruct
 * purpose: Delete a HASH object, freeing all of the taken memory
 * input  : hHash   - HASH object handle
 * output : none
 * return : Non negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
hashDestruct(
    IN  HHASH hHash);


/************************************************************************
 * hashAdd
 * purpose: Add a new element to the hash table.
 *          This function will not add the element if an element with the
 *          same key already exists if asked
 * input  : hHash               - HASH object handle
 *          key                 - Pointer to the key
 *          userElem            - Pointer to the element to store
 *          searchBeforeInsert  - Check for the same key inside the HASH or not
 * output : none
 * return : Pointer to the element's location in the hash table on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI void* RVCALLCONV
hashAdd(
     IN  HHASH  hHash,
     IN  void*  key,
     IN  void*  userElem,
     IN  RvBool searchBeforeInsert);


/************************************************************************
 * hashFind
 * purpose: Find the location of an element by its key
 * input  : hHash       - HASH object handle
 *          key         - Pointer to the key
 * output : none
 * return : Pointer to the element's location in the hash table on success
 *          NULL on failure or if the element wasn't found
 ************************************************************************/
RVINTAPI void* RVCALLCONV
hashFind(
    IN  HHASH hHash,
    IN  void* key);


/************************************************************************
 * hashFindNext
 * purpose: Find the location of the next element with the same key
 * input  : hHash       - HASH object handle
 *          key         - Pointer to the key
 *          location    - Location given in the last call to hashFindNext()
 *                        or hashFind().
 * output : none
 * return : Pointer to the element's location in the hash table on success
 *          NULL on failure or if the element wasn't found
 ************************************************************************/
RVINTAPI void* RVCALLCONV
hashFindNext(
    IN  HHASH hHash,
    IN  void* key,
    IN  void* location);


/************************************************************************
 * hashGetElement
 * purpose: Get the element's data by its location (given by hashFind()).
 * input  : hHash       - HASH object handle
 *          location    - Pointer to the element in hash
 *                        (given by hashAdd)
 * output : none
 * return : Pointer to the element's date in the hash table on success
 *          NULL on failure or if the element wasn't found
 ************************************************************************/
RVINTAPI void* RVCALLCONV
hashGetElement(
    IN  HHASH hHash,
    IN  void* location);


/************************************************************************
 * hashSetElement
 * purpose: Set the element's data by its location (given by hashFind()).
 * input  : hHash       - HASH object handle
 *          location    - Pointer to the element in hash
 *                        (given by hashAdd)
 * output : none
 * return : Non negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
hashSetElement(
    IN  HHASH   hHash,
    IN  void*   location,
    IN  void*   userElem);


/************************************************************************
 * hashGetKey
 * purpose: Get the element's key by its location (given by hashFind()).
 * input  : hHash       - HASH object handle
 *          location    - Pointer to the element in hash
 *                        (given by hashAdd)
 * output : none
 * return : Pointer to the element's key in the hash table on success
 *          NULL on failure or if the element wasn't found
 ************************************************************************/
RVINTAPI void* RVCALLCONV
hashGetKey(
    IN  HHASH hHash,
    IN  void* location);


/************************************************************************
 * hashDelete
 * purpose: Delete an element from the HASH
 * input  : hHash       - HASH object handle
 *          location    - Pointer to the element in hash
 *                        (given by hashAdd)
 * output : none
 * return : Non negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
hashDelete(
    IN  HHASH   hHash,
    IN  void*   location);


/************************************************************************
 * hashDoAll
 * purpose: Call a function on all used elements stored in HASH
 * input  : hHash       - HASH object handle
 *          func        - Function to execute on all elements. If this
 *                        function returns NULL, then this function
 *                        stops its execution.
 *          param       - Context to use when executing the function
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
hashDoAll(
    IN HHASH        hHash,
    IN HASHEFunc    func,
    IN void*        param);


#ifdef __cplusplus
}
#endif

#endif  /* _HASH_H */

