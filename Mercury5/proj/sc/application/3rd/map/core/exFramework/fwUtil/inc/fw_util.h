/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      fw_util.h
 *
 * DESCRIPTION
 *      This file implements the interface to support utility function in framework level.
 *
 * HISTORY
 *      2008.04.30       Lester Hsu         Initial Version
 *      2008.06.06       Kate Liu           Added function headeers for bouning
 *                                          box and distance utilities.
 *      2008.06.27       Kate Liu           Modified coding style
 *----------------------------------------------------------------------------- 
 */

#ifndef FW_UTIL_H
#define FW_UTIL_H

#include "fw_std.h"

typedef enum Language_Type_e
{
    e_ENGLISH_US = 0,
    e_Chinese_Tradition,
    e_Chinese_Simplified,
    e_Num_Language
} Language_Type_et;

/* Get the offset of structure member */
#define             MF_GET_OFFSET(Type,Member)          ((size_t) &(((Type *) 0)->Member))

/* A big prime for hash value factor */
#define             MF_HASH_VALUE_FACTOR                1000584527

/* prevent from the compile warning message */
#if defined(WIN32) || defined(WINCE)
#define             MF_UNUSED_PARAMETER(X)              (X) 
#else
#define             MF_UNUSED_PARAMETER(X)              X=X 
#endif

#ifdef  __cplusplus
extern "C"
{
#endif


/* ------------------------------------------------------------------------------------------
 * Hash Utility:
 *      (1) Provide a hash utility for general purpose. 
 *      (2) The caller needs to define the callback fucntion for hash value and data comprison. 
 *      (3) The caller needs to prepare the memory to store the data.
 *      (4) The data structure needs to reserve one pointer variable for hash use.  
 * ------------------------------------------------------------------------------------------
 */

/*
 *  Syntax:
 *      S32 XXX(PMVOID pvData);
 *
 *  Purpose:
 *      Defines the callback function type MF_HashValue_pfn to get hash value.
 *
 *  Parameters:
 *      pvData
 *          [in] The data pointer.
 *
 *  Return Values:
 *      Returns the hash value. 
 */
typedef S32 (*MF_HashValue_pfn)(PMVOID pvData);


/*
 *  Syntax:
 *      S32 XXX(PMVOID pvData1, PMVOID pvData2);
 *
 *  Purpose:
 *      Defines the callback function type MF_HashComp_pfn for data comparison
 *
 *  Parameters:
 *      pvData1
 *          [in] The first data pointer
 *      pvData2
 *          [in] The second data pointer
 *
 *  Return Values:
 *      0: Two data has the same hash key. 
 *      not 0: Two data has not the same hash key. 
 */
typedef S32 (*MF_HashComp_pfn)(PMVOID pvData1, PMVOID pvData2);


/*
 *  Syntax:
 *      MVOID XXX(PMVOID pvClientData, PMVOID pvUserData);
 *
 *  Purpose:
 *      Defines the callback function type MF_HashTraverse_pfn to traverse all the hash data
 *
 *  Parameters:
 *      pvClientData
 *          [in] The client data pointer. (see mfHashTraverse() )
 *      pvUserData
 *          [in] The hash data pointer.
 */
typedef MVOID (*MF_HashTraverse_pfn)(PMVOID pvClientData, PMVOID pvUserData);


/*
 *  Define the hash pointer type
 */
typedef PMVOID    pMF_Hash_st;


/* 
 *  Syntax:
 *      pMF_Hash_st mfOpenHash(S32 iHashSize, U32 u32HashLinkOffset, MF_HashValue_pfn pfnHashValue, MF_HashComp_pfn pfnHashComp);
 *
 *  Purpose:
 *      Open a new hash
 *
 *  Parameters:
 *      iHashSize
 *          [in] Specify the initial hash size. (Min:64, Max:1024*1024).
 *      u32HashLinkOffset
 *          [in] Specify the offset of hash link in the data structure.
 *      pfnHashValue
 *          [in] Specifies the callback function to give the hash value. 
 *      pfnHashComp
 *          [in] Specify the callback function check if two data the same hash key. 
 *
 *  Return Values:
 *      Returns the hash pointer.
 *      If the function fails, return NULL.
 */
pMF_Hash_st mfOpenHash(S32 iHashSize, U32 u32HashLinkOffset, MF_HashValue_pfn pfnHashValue, MF_HashComp_pfn pfnHashComp);



/* 
 *  Syntax:
 *      MVOID mfCloseHash(pMF_Hash_st ptHashPtr);
 *  Purpose:
 *      Close the hash.
 *
 *  Parameters:
 *      ptHashPtr
 *          [in] Specify the hash pointer.
 *
 */
MVOID mfCloseHash(pMF_Hash_st ptHashPtr);



/* 
 *  Syntax:
 *      PMVOID mfHashFind(pMF_Hash_st ptHashPtr, PMVOID pvUserData);
 *
 *  Purpose:
 *      Finds the specific data from the hash.      
 *
 *  Parameters:
 *      ptHashPtr
 *          [in] Specify the hash pointer.
 *      pvUserData
 *          [in] Specify the pointer to specify the search information.
 *
 *  Return Values:
 *      Returns the hash data pointer.
 *      If not found, return NULL.
 */
PMVOID mfHashFind(pMF_Hash_st ptHashPtr, PMVOID pvUserData);


/* 
 *  mfHashInsert()
 *      Insert a data to the hash.
 *
 *  Syntax:
 *      MVOID mfHashInsert(pMF_Hash_st ptHashPtr, PMVOID pvUserData);
 *
 *  Parameters:
 *      ptHashPtr
 *          [in] Specify the hash pointer.
 *      pvUserData
 *          [in] Specify the pointer of the new added data.
 */
MVOID mfHashInsert(pMF_Hash_st ptHashPtr, PMVOID pvUserData);

/* 
 *
 *  Syntax:
 *      PMVOID mfHashDelete(pMF_Hash_st ptHashPtr, PMVOID pvUserData);
 *
 *  Purpose:
 *      Remove specifix data from hash.
 *
 *  Parameters:
 *      ptHashPtr
 *          [in] Specify the hash pointer.
 *      pvUserData
 *          [in] Specify the pointer to specific the delete data information.
 *
 *  Return Values:
 *      If the function succeeds, the return value is not NULL and the hash pointer. 
 *      If the function fails, the return value NULL.
 *
 */
PMVOID mfHashDelete(pMF_Hash_st ptHashPtr, PMVOID pvUserData);


/* 
 *  Syntax:
 *      MVOID mfResetHash(pMF_Hash_st ptHashPtr);
 *
 *  Purpose:
 *      Remove all hash data.
 *
 *  Parameters:
 *      ptHashPtr
 *          [in] Specify the hash pointer.
 *
 */
MVOID mfResetHash(pMF_Hash_st ptHashPtr);


/* 
 *  Syntax:
 *      MVOID mfHashTraverse(pMF_Hash_st ptHashPtr, MF_HashTraverse_pfn pfnTraverseCB, PMVOID pvClientData);
 *
 *  Purpose:
 *      Traverse all data in the hash.
 *
 *  Parameters:
 *      ptHashPtr
 *          [in] Specify the hash pointer.
 *      pfnTraverseCB
 *          [in] Specify callback function for traversing the hash data.
 *      pvClientData
 *          [in] Specify the client data pointer. 
 */
MVOID mfHashTraverse(pMF_Hash_st ptHashPtr, MF_HashTraverse_pfn pfnTraverseCB, PMVOID pvClientData);



/* 
 *  Syntax:
 *      S32 mfStr16HashValue(PU16 sText);
 *
 *  Purpose:
 *      Generates the hash value of a string. (UNICODE)
 *
 *  Parameters:
 *      sText
 *          [in] Specifies the string.
 *
 *  Return Values:
 *      Returns the hash value.
 */
S32 mfStr16HashValue(PU16 sText);


/* 
 *  Syntax:
 *      S32 mfStr8HashValue(PS8 sText);
 *
 *  Purpose:
 *      Generates the hash value of a string. (ANSI)
 *
 *  Parameters:
 *      sText
 *          [in] Specifies the string.
 *
 *  Return Values:
 *      Returns the hash value.
 */
S32 mfStr8HashValue(PS8 sText);




/* ------------------------------------------------------------------------------------------
 * Memory Pool Utility:
 *     Provide a fast and saving method to allocate a small memory with fixed size. 
 * ------------------------------------------------------------------------------------------
 */


/*
 *  Define memory pool pointer type
 */
typedef PMVOID    pMF_Pool_st;


/* 
 *  Syntax:
 *      pMF_Pool_st mfOpenPool(U32 u32BlockSize);
 *
 *  Purpose:
 *      Opens a new memory pool.
 *
 *  Parameters:
 *      u32BlockSize
 *          [in] Specifies the memory block size. (u32BlockSize: 1 ~ 512)
 *
 *  Return Values:
 *      Returns the memory pool pointer.
 *      If the function fails, returns NULL.
 */
pMF_Pool_st mfOpenPool(U32 u32BlockSize);


/* 
 *  Syntax:
 *      PMVOID mfGetPoolBlock(pMF_Pool_st ptPoolPtr);
 *
 *  Purpose:
 *      Allocates a new memory block from a memory pool.
 *
 *  Parameters:
 *      ptPoolPtr
 *          [in] Specifies the memory pool pointer.
 *
 *  Return Values:
 *      Returns the memory block pointer.
 *      If the function fails, returns NULL.
 */
PMVOID mfGetPoolBlock(pMF_Pool_st ptPoolPtr);


/* 
 *  Syntax:
 *      MVOID mfPutPoolBlock(pMF_Pool_st ptPoolPtr, PMVOID pvBlock);
 *
 *  Purpose:
 *      Puts the memory block back to the memory pool.
 *
 *  Parameters:
 *      ptPoolPtr
 *          [in] Specifies the memory pool pointer.
 *      pvBlock
 *          [in] Specifies the released memory block.
 */
MVOID mfPutPoolBlock(pMF_Pool_st ptPoolPtr, PMVOID pvBlock);


/* 
 *  Syntax:
 *      MVOID mfResetPool(pMF_Pool_st ptPoolPtr);
 *
 *  Purpose:
 *      Puts all the allocated block back to the memory pool.
 *
 *  Parameters:
 *      ptPoolPtr
 *          [in] Specifies the memory pool pointer.
 */
MVOID mfResetPool(pMF_Pool_st ptPoolPtr);


/* 
 *  Syntax:
 *      MVOID mfClosePool(pMF_Pool_st ptPoolPtr);
 *
 *  Purpose:
 *      Closes the the memory pool and frees all allocated memory.
 *
 *  Parameters:
 *      ptPoolPtr
 *          [in] Specifies the memory pool pointer.
 */
MVOID mfClosePool(pMF_Pool_st ptPoolPtr);


/* 
 *  Syntax:
 *      U32 mfGetPoolTotalMemSize(pMF_Pool_st ptPoolPtr);
 *
 *  Purpose:
 *      Gets the total memory size used by the memory pool.
 *
 *  Parameters:
 *      ptPoolPtr
 *          [in] Specifies the memory pool pointer.
 *
 *  Return Values:
 *      Returns the memory size used by the memory pool.
 *      If the function fails, returns 0.
 */
U32 mfGetPoolTotalMemSize(pMF_Pool_st ptPoolPtr);



/* ------------------------------------------------------------------------------------------
 *  Memory Arena Utility
 *      Provide a fast and saving method to allocate a small memory with variable size. 
 * ------------------------------------------------------------------------------------------
 */

/*
 *  Define memory arena pointer type
 */
typedef PMVOID    pMF_Arena_st;


/* 
 *  Syntax:
 *      pMF_Arena_st mfOpenArena();
 *
 *  Purpose:
 *      Opens a new memory arena.
 *
 *  Return Values:
 *      Returns the memory arena pointer.
 *      If the function fails, returns NULL.
 */
pMF_Arena_st mfOpenArena(MVOID);


/* 
 *  Syntax:
 *      PMVOID mfGetArenaBlock(pMF_Arena_st ptArenaPtr, U32 u32Size);
 *
 *  Purpose:
 *      Allocates a new memory block with the specific size from a memory arena.
 *
 *  Parameters:
 *      ptArenaPtr
 *          [in] Specifies the memory arena pointer.
 *      u32Size
 *          [in] Specifies the memory block size.
 *
 *  Return Values:
 *      Returns the memory block pointer.
 *      If the function fails, returns NULL.
 */
PMVOID mfGetArenaBlock(pMF_Arena_st ptArenaPtr, U32 u32Size);


/* 
 *  Syntax:
 *      MVOID mfResetArena(pMF_Arena_st ptArenaPtr);
 *
 *  Purpose:
 *      Puts all the allocated block back to the memory arena.
 *
 *  Parameters:
 *      ptArenaPtr
 *          [in] Specifies the memory arena pointer.
 */
MVOID mfResetArena(pMF_Arena_st ptArenaPtr);


/* 
 *  Syntax:
 *      MVOID mfCloseArena(pMF_Arena_st ptArenaPtr);
 *
 *  Purpose:
 *      Closes the the memory arena and frees all allocated memory
 *
 *  Parameters:
 *      ptArenaPtr
 *          [in] Specifies the memory pool pointer.
 */
MVOID mfCloseArena(pMF_Arena_st ptArenaPtr);



/* 
 *  Syntax:
 *      U32 mfGetArenaTotalMemSize(pMF_Arena_st ptArenaPtr);
 *
 *  Purpose:
 *      Gets the total memory size used by the memory arena.
 *
 *  Parameters:
 *      ptArenaPtr
 *          [in] Specifies the memory arena pointer.
 *
 *  Return Values:
 *      Returns the memory size used by the memory pool.
 *      If the function fails, returns 0.
 */
U32 mfGetArenaTotalMemSize(pMF_Arena_st ptArenaPtr);


/* ------------------------------------------------------------------------------------------
 * Permanent String
 *     Provides a utlity to create permanent string
 * ------------------------------------------------------------------------------------------
 */

/*
 * Defines the permanent string management pointer type
 */
typedef PMVOID        pMF_PermStrMgr_st;


/* 
 *  Syntax:
 *      pMF_PermStrMgr_st mfOpenPermStringMgr();
 *
 *  Purpose:
 *      Open a new permanent string management.
 *
 *  Return Values:
 *      Returns the permanent string management pointer.
 *      If the function fails, returns NULL.
 */
pMF_PermStrMgr_st mfOpenPermStringMgr(MVOID);


/* 
 *  Syntax:
 *      MVOID mfClosePermStringMgr(pMF_PermStrMgr_st ptMgr);
 *
 *  Purpose:
 *      Closes the permanent string management.
 *
 *  Parameters:
 *      ptMgr
 *          [in] Specifies the permanent string management pointer
 */
MVOID mfClosePermStringMgr(pMF_PermStrMgr_st ptMgr);


/* 
 *  Syntax:
 *      PU16 mfMakePermStringByMgr(pMF_PermStrMgr_st ptMgr, PU16 sText);
 *
 *  Purpose:
 *      Make a permanent string by the permanent string management.
 *
 *  Parameters:
 *      ptMgr
 *          [in] Specifies the permanent string management pointer
 *      sText
 *          [in] Specifies soruce string.
 *
 *  Return Values:
 *      Returns the permanent string.
 *      If the function fails, returns NULL.
 */
PU16 mfMakePermStringByMgr(pMF_PermStrMgr_st ptMgr, PU16 sText);


/* 
 *  Syntax:
 *      PU16 mfMakePermString(PU16 sText);
 *
 *  Purpose:
 *      Make a permanent string for application level. 
 *      Memory will be kept until the program exits.
 *
 *  Parameters:
 *      sText
 *          [in] Specifies the source string.
 *
 *  Return Values:
 *      Returns the permanent string.
 *      If the function fails, returns NULL.
 */
PU16 mfMakePermString(PU16 sText);


/* ------------------------------------------------------------------------------------------
 * Distance Utility
 * ------------------------------------------------------------------------------------------
 */

/* 
 *  Syntax:
 *      MDOUBLE mfGetLatitudeUnitLength(S32 iLatitude);
 *
 *  Purpose:
 *      Get the latitude unit length by the specific latitude position.  (unit: 1/100000 degree)
 *
 *  Parameters:
 *      iLatitude
 *          [in] Specifies the latitude position.
 *
 *  Return Values:
 *      Returns the length of one latitude unit.
 */
MDOUBLE mfGetLatitudeUnitLength(S32 iLatitude);


/* 
 *  Syntax:
 *      MDOUBLE mfGetLongitudeUnitLength(S32 iLatitude);
 *
 *  Purpose:
 *      Get the longitude unit length by the specific latitude position.  (unit: 1/100000 degree)
 *
 *  Parameters:
 *      iLatitude
 *          [in] Specifies the latitude position.
 *
 *  Return Values:
 *      Returns the length of one latitude unit.
 */
MDOUBLE mfGetLongitudeUnitLength(S32 iLatitude);



/*
 *  Syntax:
 *      S32 mfGetDistance (pVertex_st ptVertexA, pVertex_st ptVertexB);
 *
 *  Purpose:
 *      Get distance (in meter) between two points (in LL).
 *
 *  Parameters:
 *      ptVertexA
 *          [in] Pointer to a vertex A.
 *      ptVertexB
 *          [in] Pointer to a vertex B.
 *
 *  Return Values:
 *      Distance (in meter) bewteen vertex A and vertex B if the values of parameter are valid.
 *      Otherwise, return a negative distance value.
 */
S32 mfGetDistance (pVertex_st ptVextexA, pVertex_st ptVertexB);

/*
 *  Syntax:
 *      S32 mfGetPointLineDistance (pVertex_st ptSegStart, pVertex_st ptSegEnd, pVertex_st ptUserVertex, pVertex_st ptProjVertex);
 *
 *  Purpose:
 *      Get distance (in meter) from a vertex to a line and get projection point onto the line.
 *
 *  Parameters:
 *      ptSegStart
 *          [in] Pointer to a vertex where the line starts.
 *      ptSegEnd
 *          [in] Pointer to a vertex where the line ends.
 *      ptUserVertex
 *          [in] Pointer to a vertex given by the user.
 *      ptProjVertex
 *          [out] Pointer to a vertex where the user vertex's projected .
 *
 *  Return Values:
 *      Distance (in meter) from the user vertex to the line if the values of parameters are valid.
 *      Otherwise, return a negative distance value.
 */
S32 mfGetPointLineDistance (pVertex_st ptSegStart, pVertex_st ptSegEnd, pVertex_st ptUserVertex, pVertex_st ptProjVertex);

/*
 *  Syntax:
 *      S32 mfGetPointPolylineDistance (pVertex_st ptUserVertex, pVertex_st ptVertex, S32 iNO, PS32 piSegment, pVertex_st ptProjVertex);
 *
 *  Purpose:
 *      Get distance from a vertex to a polyline and get a projection vertex onto the polyline.
 *
 *  Parameters:
 *      ptUserVertex
 *          [in] Pointer to a vertex given by the user.
 *      ptVertex
 *          [in] Pointer to a vertex array to store the vertices on a polyline.
 *      iNO
 *          [in] Number of vertices on a polyline.
 *      piSegment
 *          [out] Pointer to a segment where the user vertex's projected onto the polyline.
 *      ptProjVertex
 *          [out] Pointer to a vertex where the user vertex's projected onto the polyline.
 *          
 *          
 *  Return Values:
 *      Distance (in meter) from the user vertex to the polyline if the values of parameter are valid.
 *      Otherwise, return a negative distance value.
 */
S32 mfGetPointPolylineDistance (pVertex_st ptUserVertex, pVertex_st ptVertex, S32 iNO, PS32 piSegment, pVertex_st ptProjVertex);




/* ------------------------------------------------------------------------------------------
 * Degree/Azimuth Utility
 * ------------------------------------------------------------------------------------------
 */

/* 
 *  Syntax:
 *      S32 mfGetDegree(S32 iX1, S32 iY1, S32 iX2, S32 iY2);
 *
 *  Purpose:
 *      Get the degree from (iX1,iY1) to (iX2,iY2).
 *
 *  Parameters:
 *      iX1
 *          [in] Specifies the X position of the first pointer
 *      iY1
 *          [in] Specifies the Y position of the first pointer
 *      iX2
 *          [in] Specifies the X position of the second pointer
 *      iY2
 *          [in] Specifies the Y position of the second pointer
 *
 *  Return Values:
 *      Returns the integer value.
 */
S32 mfGetDegree(S32 iX1, S32 iY1, S32 iX2, S32 iY2);



/* 
 *  Syntax:
 *      S32 mfGetAzimuth(S32 iX1, S32 iY1, S32 iX2, S32 iY2);
 *
 *  Purpose:
 *      Get the azimuth from (iX1,iY1) to (iX2,iY2). (North is 0)
 *
 *  Parameters:
 *      iX1
 *          [in] Specifies the X position of the first pointer
 *      iY1
 *          [in] Specifies the Y position of the first pointer
 *      iX2
 *          [in] Specifies the X position of the second pointer
 *      iY2
 *          [in] Specifies the Y position of the second pointer
 *
 *  Return Values:
 *      Returns the azimuth value. (-179 ~ 180)
 */
S32 mfGetAzimuth(S32 iX1, S32 iY1, S32 iX2, S32 iY2);



/* 
 *  Syntax:
 *      S32 mfNormalizeAzimuth(S32 iAzimuth);
 *
 *  Purpose:
 *     Normalize the azimuth. (North is 0)
 *
 *  Parameters:
 *      iAzimuth
 *          [in] Specifies original azimuth.
 *
 *  Return Values:
 *      Returns the normalized azimuth value. (-179 ~ 180)
 */
S32 mfNormalizeAzimuth(S32 iAzimuth);



/* 
 *  Syntax:
 *      S32 mfDiffAzimuth(S32 iAzimuth1, S32 iAzimuth2);
 *
 *  Purpose:
 *      Get the different azimuth by two given azimuth. (iAzimuth2-iAzimuth1),
 *
 *  Parameters:
 *      iAzimuth1
 *          [in] Specifies first azimuth.
 *      iAzimuth2
 *          [in] Specifies second azimuth.
 *
 *  Return Values:
 *      Returns the different azimuth value. (-179 ~ 180)
 */
S32 mfDiffAzimuth(S32 iAzimuth1, S32 iAzimuth2);



/* ------------------------------------------------------------------------------------------
 * Bounding Box Utility
 * ------------------------------------------------------------------------------------------
 */

/*
 *  Syntax:
 *      MVOID mfBBoxOrBBox (pBBox_st ptLHS, pBBox_st ptRHS);
 * 
 *  Purpose:
 *      Find a proper bounding box that contains the two given bounding boxes. 
 *      (LHS |= RHS, where LHS, RHS are bounding boxes.)
 *
 *  Parameters:
 *      ptLHS
 *          [out] Pointer to a bounding box that contains the two given 
 *                bounding boxes.
 *      ptRHS
 *          [in] Pointer to a bounding box to be included.
 *
 *  Return Values
 *      None.
 */
MVOID mfBBoxOrBBox (pBBox_st ptLHS, pBBox_st ptRHS);

/*
 *  Syntax:
 *      MVOID mfBBoxOrVertex (pBBox_st ptLHS, pVertex_st ptVertex);
 * 
 *  Purpose:
 *      Find a proper bounding box that contains the given bounding box and the
 *      given vertex.
 *      (LHS |= RHS, where LHS is a bounding box, RHS is a vertex.)
 *
 *  Parameters:
 *      ptLHS
 *          [out] Pointer to a bounding box that contains the vertex and itself.
 *      ptRHS
 *          [in] Pointer to a vertex to be included.
 *
 *  Return Values
 *      None.
 */
MVOID mfBBoxOrVertex (pBBox_st ptLHS, pVertex_st ptVertex);

/*
 *  Syntax:
 *      MBOOL mfBBoxAndBBox (pBBox_st ptLHS, pBBox_st ptRHS);
 * 
 *  Purpose:
 *      Find a proper bounding box where the two given bounding boxes overlop.
 *      (LHS &= RHS, where LHS, RHS are bounding boxes.)
 *
 *  Parameters:
 *      ptLHS
 *          [out] Pointer to a bounding box to store the bounds where the two 
 *                given bounding boxes overlap.
 *                If the two bounding box don't overlap, this bounding box will
 *                be set as the origin (0,0,0,0)
 *      ptRHS
 *          [in] Pointer to a vertex to be included.
 *
 *  Return Values
 *      Return true if LHS and RHS overlap and the overlap bounding box is found.
 *      Otherwise, return false.
 */ 
MBOOL mfBBoxAndBBox (pBBox_st ptLHS, pBBox_st ptRHS);

/*
 *  Syntax:
 *       MBOOL mfBBoxGetCenter (pBBox_st ptBBox, pVertex_st ptCenter);
 * 
 *  Purpose:
 *      Find the center of the bounding box.
 *
 *  Parameters:
 *      ptBBox
 *          [in] Pointer to a bounding box to find its center.
 *      ptCenter
 *          [out] Pointer to a vertex to store the center of the bounding box.
 *
 *
 *  Return Values
 *      Return true if the center is found.
 *      Otherwise, return false.
 */
MBOOL mfBBoxGetCenter (pBBox_st ptBBox, pVertex_st ptCenter);

/*
 *  Syntax:
 *       MBOOL mfBBoxGetCenterX (pBBox_st ptBBox, PS32 piX);
 * 
 *  Purpose:
 *      Find the center between the left and right boundaries.
 *
 *  Parameters:
 *      ptBBox
 *          [in] Pointer to a bounding box to find the center between the left
 *               and right boundaries.
 *      piX
 *          [out] Pointer to a x-coordinate in the middle of the left and 
 *                right boundaries.
 *
 *
 *  Return Values
 *      Return true if the center is found.
 *      Otherwise, return false.
 */
MBOOL mfBBoxGetCenterX (pBBox_st ptBBox, PS32 piX);

/*
 *  Syntax:
 *       MBOOL mfBBoxGetCenterY (pBBox_st ptBBox, PS32 piY);
 * 
 *  Purpose:
 *      Find the center between the top and bottom boundaries.
 *
 *  Parameters:
 *      ptBBox
 *          [in] Pointer to a bounding box to find the center between the top
 *               and bottom boundaries.
 *      piY
 *          [out] Pointer to a y-coordinate in the middle of the top and bottom
 *                boundaries.
 *
 *
 *  Return Values
 *      Return true if the center is found.
 *      Otherwise, return false.
 */
MBOOL mfBBoxGetCenterY (pBBox_st ptBBox, PS32 piY);

/*
 *  Syntax:
 *       MBOOL mfBBoxContainsBBox (pBBox_st ptLHS, pBBox_st ptRHS);
 * 
 *  Purpose:
 *      Check if the bounding box RHS is within another bounding box LHS.
 *
 *  Parameters:
 *      ptLHS
 *          [in] Pointer to a bounding box LHS to check if another bounding box RHS
 *               is within it.
 *      ptRHS
 *          [in] Pointer to a bounding box RHS to check if RHS is within LHS.
 *
 *
 *  Return Values
 *      Return true if RHS is within LHS.
 *      Otherwise, return false.
 */
MBOOL mfBBoxContainsBBox (pBBox_st ptLHS, pBBox_st ptRHS);

/*
 *  Syntax:
 *       MBOOL mfBBoxContainsVertex (pBBox_st ptLHS, pVertex_st ptVertex);
 * 
 *  Purpose:
 *      Check if the given vertex is within the bounding boux.
 *
 *  Parameters:
 *      ptLHS
 *          [in] Pointer to a bounding box to check if the vertex is within it.
 *      ptVertex
 *          [in] Pointer to a vertex to check if the vertex is within the 
 *               bounding box.
 *
 *
 *  Return Values
 *      Return true if the vertex is within the bounding box.
 *      Otherwise, return false.
 */
MBOOL mfBBoxContainsVertex (pBBox_st ptLHS, pVertex_st ptVertex);

/*
 *  Syntax:
 *       MBOOL mfBBoxOverlapsBBox (pBBox_st ptLHS, pBBox_st ptRHS);
 * 
 *  Purpose:
 *      Check if the two bounding boxes overlap.
 *
 *  Parameters:
 *      ptLHS
 *          [in] Pointer to a bounding box A to check if A overlaps with B.
 *      ptRHS
 *          [in] Pointer to a bounding box B to check if B overlaps with A.
 *
 *
 *  Return Values
 *      Return true if the two bounding boxes overlap.
 *      Otherwise, return false.
 */
MBOOL mfBBoxOverlapsBBox (pBBox_st ptLHS, pBBox_st ptRHS);

/*
 *  Syntax:
 *       MVOID mfBBoxSet(pBBox_st ptBBox, S32 s32Left, S32 s32Bottom, S32 s32Right, S32 s32Top);
 * 
 *  Purpose:
 *      Set the values in a bounding box.
 *
 *  Parameters:
 *      ptBBox
 *          [out] Pointer to a bounding box A to check if A overlaps with B.
 *      s32Left
 *          [in] Left boundary.
 *      s32Bottom
 *          [in] Bottom boundary.
 *      s32Right
 *          [in] Right boundary.
 *      s32Top
 *          [in] Top boundary.
 *
 *
 *  Return Values
 *      None.
 */
MVOID mfBBoxSet(pBBox_st ptBBox, S32 s32Left, S32 s32Bottom, S32 s32Right, S32 s32Top);


/* ------------------------------------------------------------------------------------------
 *  Get modules under excalibur/data
 * ------------------------------------------------------------------------------------------
 */
PU16          fw_GetModuleDirectory(MVOID);
PU16          fw_GetDataDirectory(MVOID);
PU16          fw_GetBinDirectory(MVOID);
PU16          fw_GetIncDirectory(MVOID);
PU16          fw_GetConfigDirectory(MVOID);
PU16          fw_GetMapDirectory(MVOID);
PU16          fw_GetIconDirectory(MVOID);
PU16          fw_GetFontDirectory(MVOID);
PU16          fw_GetTTSDirectory(MVOID);
PU16          fw_GetStringDirectory(MVOID);
PU16          fw_GetNmeaDirectory(MVOID);
PU16          fw_GetVoiceLangDirectory(Language_Type_et eLang);

/* ------------------------------------------------------------------------------------------
 * Time Utility
 * ------------------------------------------------------------------------------------------
 */
MBOOL mfSetLocalTime (pTime_st psTime);
 
MVOID mfGetLocalTime (pTime_st psTime);

MVOID mfGetUTCTime (pTime_st psTime);

/* ------------------------------------------------------------------------------------------
 * Other
 * ------------------------------------------------------------------------------------------
 */

/* 
 *  Syntax:
 *      S32 mfDouble2Int(MDOUBLE dValue);
 *
 *  Purpose:
 *      Converts the double to interger (round off).
 *
 *  Parameters:
 *      dValue
 *          [in] Specifies the double value.
 *
 *  Return Values:
 *      Returns the integer value.
 */
S32 mfDouble2Int(MDOUBLE dValue);


/* 
 *  Syntax:
 *      S32 mfFloat2Int(MFLOAT fValue);
 *
 *  Purpose:
 *      Converts the float to interger (round off).
 *
 *  Parameters:
 *      fValue
 *          [in] Specifies the float value.
 *
 *  Return Values:
 *      Returns the integer value.
 */
S32 mfFloat2Int(MFLOAT fValue);




/* 
 *  Syntax:
 *      MBOOL mfInit(S32 iArgc, PU16* asArgv);
 *
 *  Purpose:
 *      Initializes the framework.
 *
 *  Parameters:
 *      asArgv
 *          [in] Specifies the argument data.
 *      iArgc
 *          [in] Specifies the argument count
 *  Return Values:
 *      If the function succeeds, return MBOOL_TRUE.
 *      If the function fails, returns MBOOL_FALSE.
 */
MBOOL mfInit(S32 iArgc, PU16* asArgv);



/* defines the function pointer type for program exit */
typedef MVOID (*MF_Exit_pfn)(PMVOID pvData);

/* 
 *  Syntax:
 *      MBOOL mfRegExitFun(MF_Exit_pfn pfnRegFun, PMVOID pvClientData);
 *
 *  Purpose:
 *      Registers the callback function for program exit.
 *
 *  Parameters:
 *      pfnRegFun
 *          [in] Specifies the callback function.
 *      pvClientData
 *          [in] Specifies the client data
 *
 *  Return Values:
 *      If the function succeeds, return MBOOL_TRUE.
 *      If the function fails, returns MBOOL_FALSE.
 */
MBOOL mfRegExitFun(MF_Exit_pfn pfnRegFun, PMVOID pvClientData);


/* 
 *  Syntax:
 *      MVOID mfExit(S32 iCode);
 *
 *  Purpose:
 *      terminates the process.
 *
 *  Parameters:
 *      iCode
 *          [in] Specifies exit code.
 *
 */
MVOID mfExit(S32 iCode);



/* 
 *  Syntax:
 *      MBOOL mfKeywordIsInStr(PU16 sString, PU16 sKeyword);
 *
 *  Purpose:
 *      Checks if the specific keyword exists in the specific string
 *
 *  Parameters:
 *      sString
 *          [in] Specifies the string.
 *      sKeyword
 *          [in] Specifies the keyword
 *
 *  Return Values:
 *      If the keyword found in the string, return MBOOL_TRUE.
 *      If the keyword not found in the string, returns MBOOL_FALSE.
 */
MBOOL mfKeywordIsInStr(PU16 sString, PU16 sKeyword);


/* 
 *  Syntax:
 *      MBOOL mfChar16IsSpace(U16 u16Char);
 *
 *  Purpose:
 *      Checks if the specific character is space or not
 *
 *  Parameters:
 *      u16Char
 *          [in] Specifies the character.
 *
 *  Return Values:
 *      If the character is space, return MBOOL_TRUE.
 *      If the character is not space, returns MBOOL_FALSE.
 */
MBOOL mfChar16IsSpace(U16 u16Char);

#ifdef  __cplusplus
}
#endif


#endif
