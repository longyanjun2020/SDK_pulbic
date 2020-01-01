//==============================================================================
//
//  File        : mmpf_touchpanel.h
//  Description : INCLUDE File for the touchpanel Driver Function
//  Author      : Lucas Chuang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_TOUCHPANEL_H_
#define _MMPF_TOUCHPANEL_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"

/** @addtogroup MMPF_touchpanel
@{
*/

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct  _TOUCHPANEL_ATTRIBUTE
{
    MMP_BOOL  bInitialized;
    MMP_UBYTE ubtouchpanelID;
    MMP_UBYTE ubStoreFreq;
    MMP_UBYTE ubRange;
    MMP_UBYTE ubSensitive;
    MMP_UBYTE ubGroundAxis;
    MMP_UBYTE ub1G;
    MMP_UBYTE ub1G_Err;
    int		  nMaxG;
    int		  nInited;
} TOUCHPANEL_ATTR, *PTOUCHPANEL_ATTR;

typedef struct _3RD_PARTY_TOUCHPANEL
{
    //0
    MMP_ERR (*MMPF_TouchPanel_Init)(struct _3RD_PARTY_TOUCHPANEL *);
    int 	(*MMPF_TouchPanel_ReadPosition)(struct _3RD_PARTY_TOUCHPANEL *, MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir);
    MMP_ERR (*MMPF_TouchPanel_ReadVBAT1)(struct _3RD_PARTY_TOUCHPANEL *, MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir);
    void    (*MMPF_TouchPanel_ResetCtrl)(struct _3RD_PARTY_TOUCHPANEL *, MMP_BOOL bOn);
    MMP_ERR (*MMPF_TouchPanel_IOControl)(struct _3RD_PARTY_TOUCHPANEL *, TOUCHPANEL_ATTR *ptouchpanel_attr, MMP_UBYTE cmd, MMP_UBYTE* arg);
    //5
    MMP_BOOL (*MMPF_TouchPanel_ModuleAttached)(struct _3RD_PARTY_TOUCHPANEL *);
        
} THIRD_PARTY_TOUCHPANEL;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_3RDParty_TouchPanel_Init(void);
int  MMPF_3RDParty_TouchPanel_ReadPosition(MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir);
MMP_ERR MMPF_3RDParty_TouchPanel_ReadVBAT1(MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir);
void MMPF_3RDParty_TouchPanel_ResetCtrl(MMP_BOOL bOn);
MMP_ERR MMPF_3RDParty_TouchPanel_IOControl(MMP_UBYTE cmd, MMP_UBYTE* arg);
MMP_BOOL MMPF_3RDParty_TouchPanel_Attached(void);

void MMPF_3RDParty_TouchPanel_Register(struct _3RD_PARTY_TOUCHPANEL *pdev_obj);
void MMPF_3RDParty_TouchPanel_Unregister(void);

TOUCHPANEL_ATTR* MMPF_3RDParty_TouchPanel_GetAttr(void);

#endif // _MMPF_TOUCHPANEL_H_

/// @}
