/**
* @file ObjArray.h
*
* This header file defines the types of object array utility
*
*/

#ifndef __OBJARRAY_H__
#define __OBJARRAY_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ObjArrayItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ObjArray_t_
{
    u16 uMaxSize;
    u16 uObjSize;
    u16 uObjNum;
    ObjArray_CopyObject CopyData;
    ObjArray_ClearObject ClearData ;
    ObjArray_IsObjEqual  IsDataEqual ;
    void *pObjects;
    bool *pHasObject;
} ObjArray_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__OBJARRAY_H__
