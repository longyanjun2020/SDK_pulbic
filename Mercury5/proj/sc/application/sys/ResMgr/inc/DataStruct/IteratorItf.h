/**
* @file IteratorItf.h
*
* This header file defines the interfaces of iterator
*
*/

#ifndef __ITERATORITF_H__
#define __ITERATORITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* IteratorHandle_t;

typedef void* (*Iterator_GetNext) (IteratorHandle_t pHandle);

typedef struct Iterator_t_
{
    Iterator_GetNext GetNext;
} Iterator_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__ITERATORITF_H__

