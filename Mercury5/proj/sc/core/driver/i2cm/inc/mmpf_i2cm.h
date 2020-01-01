//==============================================================================
//
//  File        : mmpf_i2cm.h
//  Description : INCLUDE File for the Firmware I2CM Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_I2CM_H_
#define _MMPF_I2CM_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_i2c_inc.h"
//#include "mmp_display_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define I2CM_RX_FIFO_DEPTH		(0x20)
#define I2CM_TX_FIFO_DEPTH		(0x20)
#define I2CM_SW_MAX_SPEED		(200000) // For CPU 144 MHz, for loop delay set as 1, the one clock cycle is about 53 us

#define I2CM_DEBUG_LEVEL		(0)

#define I2CM_SEM_TIMEOUT 		(0x0)
#define I2CM_WHILE_TIMEOUT      (10000) // Unit:ms
#define I2CM_WHILE_SHORTTIMEOUT (1000)  // Unit:ms

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

// Software I2cm
MMP_ERR MMPF_SwI2cm_Start(const MMP_I2CM_ATTR *pI2cmAttr);
MMP_ERR MMPF_SwI2cm_Stop(const MMP_I2CM_ATTR *pI2cmAttr);
MMP_ERR MMPF_SwI2cm_WriteData(const MMP_I2CM_ATTR *pI2cmAttr, MMP_UBYTE ubData);
MMP_UBYTE MMPF_SwI2cm_ReadData(const MMP_I2CM_ATTR *pI2cmAttr);
MMP_ERR MMPF_SwI2cm_GetACK(const MMP_I2CM_ATTR *pI2cmAttr);
MMP_ERR MMPF_SwI2cm_SendNACK(const MMP_I2CM_ATTR *pI2cmAttr);
MMP_ERR MMPF_SwI2cm_SendACK(const MMP_I2CM_ATTR *pI2cmAttr);

// Common I2cm
MMP_ERR MMPF_I2cm_InitDriver(void);
MMP_UBYTE MMPF_I2cm_StartSemProtect(const MMP_I2CM_ATTR *pI2cmAttr);
MMP_UBYTE MMPF_I2cm_EndSemProtect(const MMP_I2CM_ATTR *pI2cmAttr);
MMP_ERR MMPF_I2cm_Initialize(const MMP_I2CM_ATTR *pI2cmAttr);
MMP_ERR	MMPF_I2cm_WriteReg(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT usReg, MMP_USHORT usData);
MMP_ERR	MMPF_I2cm_WriteRegEx(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT usReg, MMP_USHORT usData, MMP_BOOL ubWait);
//MMP_ERR MMPF_I2cm_ReadEEDID(const MMP_I2CM_ATTR *pI2cmAttr, MMP_UBYTE *ubData, MMP_USHORT usSeg, MMP_USHORT usOffset, MMP_USHORT usSize, MMP_DDC_OPERATION_TYPE mode);
MMP_ERR	MMPF_I2cm_ReadReg(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT usReg, MMP_USHORT *usData);
MMP_ERR	MMPF_I2cm_WriteRegSet(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT *usReg, MMP_USHORT *usData, MMP_UBYTE usSetCnt, MMP_BOOL ubWait);
MMP_ERR	MMPF_I2cm_ReadRegSet(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT *usReg, MMP_USHORT *usData, MMP_UBYTE usSetCnt);
MMP_ERR MMPF_I2cm_WriteBurstData(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT usReg, MMP_USHORT *usData, MMP_UBYTE usDataCnt, MMP_BOOL ubWait);
MMP_ERR MMPF_I2cm_ReadBurstData(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT usReg, MMP_USHORT *usData, MMP_UBYTE usDataCnt);
MMP_ERR MMPF_I2cm_ReadBurstDataApk(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT usReg, MMP_USHORT *usData, MMP_UBYTE usDataCnt);
MMP_ERR MMPF_I2cm_WriteNoRegMode(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT usData, MMP_BOOL ubWait);
MMP_ERR MMPF_I2cm_ReadNoRegMode(const MMP_I2CM_ATTR *pI2cmAttr, MMP_USHORT *usData, MMP_UBYTE usDataCnt);
MMP_ERR MMPF_I2cm_DMAWriteBurstData(const MMP_I2CM_ATTR   *pI2cmAttr,
                                    MMP_USHORT      usReg,
                                    const MMP_UBYTE     *usData,
                                    MMP_USHORT      usDataCnt,
                                    MMP_BOOL        ubWait);
MMP_ERR MMPF_I2cm_DMAReadBurstData(const MMP_I2CM_ATTR    *pI2cmAttr,
                                   MMP_USHORT       usReg,
                                   MMP_UBYTE        *usData,
                                   MMP_USHORT       usDataCnt);

#endif // _MMPF_I2CM_H_
