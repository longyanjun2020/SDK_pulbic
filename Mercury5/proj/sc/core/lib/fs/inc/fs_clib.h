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
File        : fs_clib.h 
Purpose     : Header file for the file system's CLIB functions.
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
---------------------------END-OF-HEADER------------------------------
*/

#ifndef _FS_CLIB_H_
#define _FS_CLIB_H_

#include "FS_ConfDefaults.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       #define constants
*
**********************************************************************
*/


/*********************************************************************
*
*       Global function prototypes
*
**********************************************************************
*/

int            FS__CLIB_atoi    (const char *s);
int            FS__CLIB_memcmp  (const void *s1, const void *s2, unsigned n);
void *         FS__CLIB_memcpy  (      void *s1, const void *s2, FS_SIZE_T n);
void *         FS__CLIB_memset  (void *s, int c, FS_SIZE_T n);
int            FS__CLIB_strcmp  (const char *s1, const char *s2);
char *         FS__CLIB_strcpy  (char *s1, const char *s2);
unsigned       FS__CLIB_strlen  (const char *s);
int            FS__CLIB_strncmp (const char *s1, const char *s2, int n);
char *         FS__CLIB_strncpy (char *s1, const char *s2, FS_SIZE_T n);
int            FS__CLIB_toupper (int c);
char *         FS__CLIB_strcat  (char *s1, const char *s2);


#if FS_NO_CLIB
  #define FS_ATOI(s)             FS__CLIB_atoi(s)
  #define FS_MEMCMP(s1,s2,n)     FS__CLIB_memcmp(s1,s2,n)
  #define FS_MEMCPY(s1,s2,n)     FS__CLIB_memcpy(s1,s2,n)
  #define FS_MEMSET(s,c,n)       FS__CLIB_memset(s,c,n)
  #define FS_STRCAT(s1,s2)       FS__CLIB_strcat(s1, s2)
  #define FS_STRCMP(s1,s2)       FS__CLIB_strcmp(s1,s2)
  #define FS_STRCPY(s1,s2)       FS__CLIB_strcpy(s1,s2)
  #define FS_STRLEN(s)           FS__CLIB_strlen(s)
  #define FS_STRNCMP(s1,s2,n)    FS__CLIB_strncmp(s1,s2,n)
  #define FS_STRNCPY(s1,s2,n)    FS__CLIB_strncpy(s1,s2,n)
  #define FS_TOUPPER(c)          FS__CLIB_toupper(c)
#else
  #define FS_ATOI(s)             atoi(s)
  #define FS_MEMCMP(s1,s2,n)     memcmp(s1,s2,n)
  #define FS_MEMCPY(s1,s2,n)     memcpy(s1,s2,n)
  #define FS_MEMSET(s,c,n)       memset(s,c,n)
  #define FS_STRCAT(s1,s2)       strcat(s1,s2)
  #define FS_STRCMP(s1,s2)       strcmp(s1,s2)
  #define FS_STRCPY(s1,s2)       strcpy(s1,s2)
  #define FS_STRLEN(s)           strlen(s)
  #define FS_STRNCMP(s1,s2,n)    strncmp(s1,s2,n)
  #define FS_STRNCPY(s1,s2,n)    strncpy(s1,s2,n)
  #define FS_TOUPPER(c)          toupper(c)
#endif


#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif  /* _FS_CLIB_H_  */

/*************************** End of file ****************************/
	 	 			 		    	 				 	   		   	 		  	 	      	   		 	 	  	  		  	 		 	   		 		      		       	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 
