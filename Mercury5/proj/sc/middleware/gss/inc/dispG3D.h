/*****************************************************************************\
    This software is protected by Copyright and the information
    contained herein is confidential. Distribution, reproduction
    as well as exploitation and transmission of its contents is
    not allowed except if expressly permitted. Infringments
    result in damage claims.
    Copyright : Morning Star 2006/11 ~ 2010

  File    : panelinfo.h

  Historical :
--------------------------------------------------------------------------
   Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
 16.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
/*
#include "vm_types.ht"
#include "gss_lcdc_drv.h"
*/

#if 1
#include "dispG3D_pub.h"
#else

#include "functypes.h" /* CR_1500: file name shall be in lower case */
#include "panelinfohw.h"
#include "dispbasicgrap.h"

#ifndef _DISP_G3D_H_
#define _DISP_G3D_H_

//===============================================
//    Constant
//===============================================


/*#################################################################*\
                    hardware depeneded setion
\*#################################################################*/


typedef struct _st_ms_g3d_operation_
{
  fnG3DPowerOn        PowerOn;
  fnG3DPowerOff       PowerOff;
}G3DACTION;//, *PANELACTION;


/**
 * @brief Power on the G3D device and init G3D
 *
 * @param  None
 *
 * @return TRUE                  : function request success
 * @return FALSE                 : function request fail
 */
u8 G3D_PowerOn(void);

/**
 * @brief Power off the G3D device and init G3D
 *
 * @param  None
 *
 * @return TRUE                  : function request success
 * @return FALSE                 : function request fail
 */
u8 G3D_PowerOff(void);

/**
 * @brief Install G3D interrupt routine
 *
 * @param  None
 *
 * @return None
 */
void G3d_IrqInstall(void);


#endif //_PANEL_INFOMATION_H_

#endif

