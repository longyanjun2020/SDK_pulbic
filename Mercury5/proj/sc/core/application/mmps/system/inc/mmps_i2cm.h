//==============================================================================
//
//  File        : mmps_i2cm.h
//  Description : INCLUDE File for the i2c master
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_i2cm.h
 *  @brief Header File for the I2c Master API.
 *  @author Ben Lu
 *  @version 1.0
 */

#ifndef _MMPS_I2CM_H_
#define _MMPS_I2CM_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_i2c_inc.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPS_I2cm_WriteReg(MMP_I2CM_ATTR *attr, MMP_USHORT usSubAddr, MMP_USHORT usData);
MMP_ERR MMPS_I2cm_ReadReg(MMP_I2CM_ATTR *attr, MMP_USHORT usSubAdde, MMP_USHORT* usData);
MMP_ERR MMPS_I2cm_WriteBurstData(MMP_I2CM_ATTR *attr, MMP_USHORT usSubAdd,
                                MMP_USHORT usData, MMP_ULONG ulDataAddr);
MMP_ERR MMPS_I2cm_ReadBurstData(MMP_I2CM_ATTR *attr ,MMP_USHORT usSubAdd,
                                MMP_USHORT usData, MMP_ULONG ulDataAddr);

#endif // _MMPS_I2CM_H_