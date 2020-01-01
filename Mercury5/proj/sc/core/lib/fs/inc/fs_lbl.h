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
File        : fs_lbl.h
Purpose     : Header file for the file system's Logical Block Layer
---------------------------END-OF-HEADER------------------------------
*/

#ifndef _FS_LBL_H_
#define _FS_LBL_H_

#include "fs_api.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif
#include "FS_Debug.h"

/*********************************************************************
*
*       #define constants
*
**********************************************************************
*/
/* These defines are obsolete */
#define FS_LBL_MEDIA_UNCHANGED  FS_MEDIA_IS_PRESENT
#define FS_LBL_MEDIA_CHANGED    FS_MEDIA_CHANGED

/*********************************************************************
*
*       Global function prototypes
*
**********************************************************************
*/

int    FS_LB_GetStatus  (const FS_DEVICE    * pDevice);
U16    FS_GetSectorSize     (const FS_DEVICE    * pDevice);
int    FS_LB_GetDeviceInfo  (const FS_DEVICE    * pDevice, FS_DEV_INFO * pDevInfo);
int    FS_LB_InitMedium (const FS_DEVICE    * pDevice);
int    FS_LB_ioctl          (      FS_DEVICE    * pDevice, I32 Cmd,         I32 Aux,              void * pBuffer);
void   FS_LB_FreePartSectors(      FS_PARTITION * pPart,   U32 SectorIndex, U32 NumSectors);
int    FS_LB_ReadBurst      (      FS_PARTITION * pPart,   U32 SectorNo,    U32 NumSectors,       void * pBuffer, U8 Type);
int    FS_LB_ReadDevice     (      FS_DEVICE    * pDevice, U32 Sector,                            void * pBuffer, U8 Type);
int    FS_LB_ReadPart       (      FS_PARTITION * pPart,   U32 Sector,                            void * pBuffer, U8 Type);
int    FS_LB_WriteBurst     (      FS_PARTITION * pPart,   U32 SectorNo,    U32 NumSectors, const void * pBuffer, U8 Type);
int    FS_LB_WriteDevice    (      FS_DEVICE    * pDevice, U32 Sector,                      const void * pBuffer, U8 Type);
int    FS_LB_WritePart      (      FS_PARTITION * pPart,   U32 Sector,                      const void * pBuffer, U8 Type);
int    FS_LB_WriteMultiple  (      FS_PARTITION * pPart,   U32 Sector,      U32 NumSectors, const void * pBuffer, U8 Type);

/*********************************************************************
*
*       Statistic functions
*
**********************************************************************
*/
#if FS_DEBUG_LEVEL >= FS_DEBUG_LEVEL_CHECK_PARA
typedef struct {
  U32 ReadSectorCnt;
  U32 ReadBurstCnt;
  U32 ReadBurstSectorCnt;
  U32 WriteSectorCnt;
  U32 WriteBurstCnt;
  U32 WriteBurstSectorCnt;
  U32 WriteMultipleCnt;
  U32 WriteMultipleSectorCnt;
} FS_STAT;                    /* For debugging only (statistics) */
void FS_LB_GetCounters  (FS_STAT * pStat);
void FS_LB_ResetCounters(void);
#endif
#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif  /* _FS_LBL_H_  */

/*************************** End of file ****************************/
	 	 			 		    	 				 	   		   	 		  	 	      	   		 	 	  	  		  	 		 	    	 		     			       	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 
