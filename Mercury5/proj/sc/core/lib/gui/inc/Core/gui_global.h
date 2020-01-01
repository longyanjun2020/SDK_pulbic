/*
**********************************************************************
*                          Micrium, Inc.
*                      949 Crestview Circle
*                     Weston,  FL 33327-1848
*
*                            uC/FS
*
*             (c) Copyright 2001 - 2006, Micrium, Inc.
*                      All rights reserved.
*
***********************************************************************

----------------------------------------------------------------------
File    : GLOBAL.h
Purpose : Global types etc.
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GLOBAL_H            // Guard against multiple inclusion
#define GLOBAL_H

#include <string.h>

/*********************************************************************
*
*       Macros
*
**********************************************************************
*/
#define COUNTOF(a)          (sizeof(a)/sizeof(a[0]))

#ifndef	MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef	MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#define ZEROFILL(p, Size)   (memset(p, 0, Size))

//#ifndef __VM_TYPES_HT__
#ifdef __ARMGCC__
#include "vm_types.ht"
#else
#define U8    unsigned char
#define U16   unsigned short
#define U32   unsigned long
#define U64   unsigned long long
#define I8    signed char
#define I16   signed short
#define I32   signed long
#define I64   signed long long
#endif

#endif  // Avoid multiple inclusion

/*************************** End of file ****************************/
	 	 			 		    	 				 	   		   	 		  	 	      	   		 	 	  	  		  	 		 	   		 		      		       	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 
