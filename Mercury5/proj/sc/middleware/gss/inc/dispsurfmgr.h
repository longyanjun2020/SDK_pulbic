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
#if 1
#include "dispsurfmgr_pub.h"
#else

#include <string.h>
#include "vm_types.ht"
//  #include "graphdevice.h"
#include "msgdidef.h"
#include "dispbasicgrap.h"

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
#define DISP_HW_BOUNDARY_LIMIT(addr,size) ((((u32)(addr)%0x800000)+ (size))>0x800000)
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
    fnSetToOnScreen     SetToOnScreen;
}SURFMGR, *PSURFMGR;


#ifdef _EMBEDDED_MEMORY_MGR_BODY_

    PMSSURFACE  CreateSurfaceSW(u16 width, u16 height, u32 uCaps);
    u32         DestroySurfaceSW(PMSSURFACE pSurfNode);
    u32         IsPageExternSW(PMSSURFACE);
    u32         GetSurfCapsSW(PMSSURFACE);
    u32         GetSurfAddressSW(PMSSURFACE);
    PMSSURFACE  GetPrimarySurfSW(u32);
    PMSSURFACE  SetToOnScreenSW(u32 PanelID, PMSSURFACE pSurf);

    PMSSURFACE       gm_pPrimary;
    PMSSURFACE       gm_pSecondary;

#else  //_EMBEDDED_MEMORY_MGR_BODY_

    extern PMSSURFACE  CreateSurfaceSW(u16 width, u16 height, u32 uCaps);
    extern u32         DestroySurfaceSW(PMSSURFACE pSurfNode);
    extern u32         IsPageExternSW (PMSSURFACE );
    extern u32         GetSurfCapsSW(PMSSURFACE);
    extern u32         GetSurfAddressSW(PMSSURFACE);
    extern PMSSURFACE  GetPrimarySurfSW(u32);
    extern PMSSURFACE  SetToOnScreenSW(u32 PanelID, PMSSURFACE pSurf);

    extern PMSSURFACE       gm_pPrimary;
    extern PMSSURFACE       gm_pSecondary;

#endif //_EMBEDDED_MEMORY_MGR_BODY_

#endif //_EMBEDDED_MEMORY_MGR_H_
#endif

