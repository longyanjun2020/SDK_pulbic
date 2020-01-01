//==============================================================================
//
//  File        : ahc_macro.h
//  Description : 
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_MACRO_H_
#define _AHC_MACRO_H_

/*===========================================================================
 * Macro define
 *===========================================================================*/

#ifndef MIN
#define MIN(X,Y)    ((X)<(Y))?(X):(Y)
#endif    

#ifndef MAX
#define MAX(X,Y)    ((X)>(Y))?(X):(Y)
#endif

#ifndef FIT_IN_RANGE
#define FIT_IN_RANGE(X,LOW,HIGH)                (((X)>(HIGH)) ? (HIGH) : (((X)<(LOW))?(LOW):(X)) )
#endif

#ifndef IS_FIT_IN_RANGE
#define IS_FIT_IN_RANGE(X,LOW,HIGH)             ((X)<(LOW) || (X)>(HIGH))
#endif

#ifndef ALIGN_UP    
#define ALIGN_UP( X, Y )                        (((X)+(Y)-1)/(Y)*(Y))
#endif

#ifndef ALIGN_DOWN    
#define ALIGN_DOWN( X, Y )                      (((X))/(Y)*(Y))
#endif

#define IS_SAME_PAGE( A, B, ITEMS_PER_PAGE )    ( (A)/(ITEMS_PER_PAGE) == (B)/(ITEMS_PER_PAGE) )

#ifndef __func__
#define __func__                                ""
#endif

#endif //_AHC_MACRO_H_
