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
File        : fs_os.h
Purpose     : File system's OS Layer header file
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
---------------------------END-OF-HEADER------------------------------
*/

#ifndef _FS_OS_H_

#define _FS_OS_H_

#include "FS_ConfDefaults.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

void     FS_X_OS_Lock            (unsigned LockIndex);
void     FS_X_OS_Unlock          (unsigned LockIndex);

U16   FS_X_OS_GetDate         (void);
U16   FS_X_OS_GetTime         (void);
int   FS_X_OS_GetDateTime(FS_FILETIME* pFsOsTime);
int   FS_X_OS_SetDateTime(FS_FILETIME* pFsOsTime);

int      FS_X_OS_Init            (void);
int      FS_X_OS_Exit            (void);

void     FS_X_Warn     (const char *s);
void     FS_X_ErrorOut (const char *s);
void     FS_X_Log      (const char *s);


#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif    /*  _FS_OS_H_  */

/*************************** End of file ****************************/
	 	 			 		    	 				 	   		   	 		  	 	      	   		 	 	  	  		  	 		 	    	 		  	 	 		       	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 
