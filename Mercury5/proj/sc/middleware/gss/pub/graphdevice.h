/*****************************************************************************\
    This software is protected by Copyright and the information
    contained herein is confidential. Distribution, reproduction
    as well as exploitation and transmission of its contents is
    not allowed except if expressly permitted. Infringments
    result in damage claims.
    Copyright : Morning Star 2006/11 ~ 2010

  File    : GraphicDevice.h

  Contents: Basic structures and constants here

  Historical :
--------------------------------------------------------------------------
   Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
 10.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
#ifndef _GRAPHIC_DEVICE_H_
#define _GRAPHIC_DEVICE_H_
#include "vm_types.ht"
#include "dispbasicgrap_pub.h" //
#include "dispsurfmgr_pub.h" //
#include "panelinfo_pub.h" //
#include "bitblt_pub.h"
//#include "bltpattern_pub.h"
//#include "disppowermgr_pub.h" //
#include "displine_pub.h" //
#include "dispG3D_pub.h" //
#include "sys_sys_bootinit.h"
//===============================================
//    Graphic device interface
//===============================================

typedef struct _st_graphic_device_
{
    COLOCONVERT     csc;
    POINTACTION     Point;
    LINEACTION      Line;
    BITBLTACTION    Bitblt;
    SURFMGR         Surf;
    PANELACTION     Panel;
    //POWERACTION     Power;
    G3DACTION       G3D;
    fnSetDWORD      SetActivePanel;
    fnGetDWORD      GetActivePanel;
} MSGRAPHICDEV, *PMSGRAPHICDEV;
    //PICACTION               opPic;

//===============================================
//    Variables
//===============================================
#ifndef _GRAPHIC_DEVICE_BODY_

    extern PMSGRAPHICDEV    mspGraphDev;
    extern __ONCE_CALL_ON_BOOT__ void GDI_Init(void);

    //extern PMSSURFACE       gm_pPrimary;
    //extern PMSSURFACE       gm_pSecondary;

#endif //_GRAPHIC_DEVICE_BODY_

//#define mml_GraphDev    mspGraphDev
#endif // _GRAPHIC_DEVICE_H_
