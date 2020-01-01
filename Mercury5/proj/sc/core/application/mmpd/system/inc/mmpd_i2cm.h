//==============================================================================
//
//  File        : mmpd_i2cm.h
//  Description : INCLUDE File for the Host I2CM Control Driver
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

/// @ait_only

#ifndef _MMPD_I2CM_H
#define _MMPD_I2CM_H

#include "mmp_i2c_inc.h"

/** @addtogroup MMPD_I2CM
 *  @{
 */

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPD_I2cm_WriteReg(MMP_I2CM_ATTR *attr, MMP_USHORT usReg, MMP_USHORT usData);
MMP_ERR MMPD_I2cm_ReadReg(MMP_I2CM_ATTR *attr, MMP_USHORT usReg, MMP_USHORT *usData);
MMP_ERR MMPD_I2cm_WriteBurstData(MMP_I2CM_ATTR *attr, MMP_USHORT wSubAdd,
                                 MMP_USHORT wData, MMP_ULONG ulDataAddr);
MMP_ERR MMPD_I2cm_ReadBurstData(MMP_I2CM_ATTR *attr, MMP_USHORT wSubAdd,
                                MMP_USHORT wData, MMP_ULONG ulDataAddr);

#endif/// @}

/// @end_ait_only

