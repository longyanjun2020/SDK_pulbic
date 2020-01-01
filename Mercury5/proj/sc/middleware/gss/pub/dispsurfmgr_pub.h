/*****************************************************************************\
    This software is protected by Copyright and the information
    contained herein is confidential. Distribution, reproduction
    as well as exploitation and transmission of its contents is
    not allowed except if expressly permitted. Infringments
    result in damage claims.
    Copyright : Morning Star 2006/11 ~ 2010

  File    : DispMemoryMgr.h

  Contents: Handle embedded memory here

  Historical :
--------------------------------------------------------------------------
   Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
 16.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
#include <string.h>
#include "vm_types.ht"
//  #include "graphdevice.h"
#include "msgdidef.h"
#include "dispbasicgrap_pub.h"

#ifndef _EMBEDDED_MEMORY_MGR_H_
#define _EMBEDDED_MEMORY_MGR_H_

//===============================================
//    Constant
//===============================================
#define TOTAL_EMBEDDED_MEMORY_SIZE  0    //1328400 bytes
#define MINIMAL_ALLOCATED_SIZE      0
#define MAXIMAL_ALLOCATED_SIZE      TOTAL_EMBEDDED_MEMORY_SIZE
//#define TOTAL_EMBEDDED_MEMORY_SIZE  0x144510    //1328400 bytes
//#define MINIMAL_ALLOCATED_SIZE
//#define MAXIMAL_ALLOCATED_SIZE      0
#define ERR_SURFACE_NOT_ENOUGH_MEMORY       0xFFFFFFFD //-3
//#define DISP_HW_BOUNDARY_LIMIT(addr,size) ((((u32)(addr)%0x800000)+ (size))>0x800000)
//===============================================
//    Structures
//===============================================


typedef struct _st_surface_manager_
{
    fnCreateSurface     CreateSurface;
    fnDestroySurface    DestroySurface;
    fnGetSurfDWORD      GetSurfCaps;
    fnGetSurfDWORD      GetSurfAddress;
    fnGetPrimary        GetPrimarySurf;
    //fnSetToOnScreen     SetToOnScreen;
}SURFMGR, *PSURFMGR;


#ifdef _EMBEDDED_MEMORY_MGR_BODY_
#define interface
#else
#define interface extern
#endif


    interface PMSSURFACE  CreateSurfaceSW(u16 width, u16 height, u32 uCaps);
    interface u32         DestroySurfaceSW(PMSSURFACE pSurfNode);
    interface u32         GetSurfAddressSW(PMSSURFACE);
    interface PMSSURFACE  GetPrimarySurfSW(u32);
    //interface PMSSURFACE  SetToOnScreenSW(u32 PanelID, PMSSURFACE pSurf);

    interface void*       DispGetHeapMemory(u32 nMemSize);
    interface s32         DispFreeHeapMemory(void *pMem);

    interface PMSSURFACE       gm_pPrimary;
    interface PMSSURFACE       gm_pSecondary;


#endif //_EMBEDDED_MEMORY_MGR_H_
