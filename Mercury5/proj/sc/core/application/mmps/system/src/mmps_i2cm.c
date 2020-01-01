//==============================================================================
//
//  File        : mmps_i2cm.c
//  Description : I2c Master Functions.
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_i2cm.c
 *  @brief The i2c master control functions
 *  @author Ben Lu
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_i2cm.h"

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPS_I2cm_WriteReg
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Write one I2C data to specific register 

 Send data over I2C interface to specific device according to the configuration set by AHC_ConfigI2Caccess().
 Parameters:
 @param[in] p_i2cm_attribute : I2CM attribute, please refer the structure MMP_I2CM_ATTR
 @param[in] usSubAddr : The register sub address.
 @param[in] usData : The data to be sent.
 @return the status of the operation
*/
MMP_ERR MMPS_I2cm_WriteReg(MMP_I2CM_ATTR *attr, MMP_USHORT usSubAddr, MMP_USHORT usData)
{
	return MMPD_I2cm_WriteReg(attr, usSubAddr, usData);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_I2cm_ReadReg
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Read one I2C data to specific register 

 Receives data over I2C interface to specific device.
 Parameters:
 @param[in] p_i2cm_attribute : I2CM attribute, please refer the structure MMP_I2CM_ATTR
 @param[in] usSubAdde : The register sub address.//Note: usSubAdde is used for stand for data-count in the case ubRegLen = 0
 @param[in] *usData	The received data.
 @return the status of the operation
*/
MMP_ERR MMPS_I2cm_ReadReg(MMP_I2CM_ATTR *attr, MMP_USHORT usSubAdde, MMP_USHORT* usData)
{
	return MMPD_I2cm_ReadReg(attr, usSubAdde, usData);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_I2cm_WriteBurstData
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Write I2C data burstly.

 write data by I2C interface in burst mode. The data is taken from ulDataAddr memory location.
 Parameters:
 @param[in] p_i2cm_attribute : I2CM attribute, please refer the structure MMP_I2CM_ATTR
 @param[in] usSubAdd : The register sub address.
 @param[in] usData : Number of words to be sent.
 @param[in] ulDataAddr : The address which stores the data.
 @return the status of the operation
*/
MMP_ERR MMPS_I2cm_WriteBurstData(MMP_I2CM_ATTR *attr, MMP_USHORT usSubAdd, MMP_USHORT usData, MMP_ULONG ulDataAddr)
{
	return MMPD_I2cm_WriteBurstData(attr, usSubAdd, usData, ulDataAddr);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_I2cm_ReadBurstData
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Read I2C data burstly.

 Receive data from I2C interface in burst mode. The data will store at ulDataAddr memory location.
 Parameters:
 @param[in] p_i2cm_attribute : I2CM attribute, please refer the structure MMP_I2CM_ATTR
 @param[in] usSubAdd The register sub address.
 @param[in] usData Number of words to be read..
 @param[in] ulDataAddr : The address which stores the data.
 @return the status of the operation.
*/
MMP_ERR MMPS_I2cm_ReadBurstData(MMP_I2CM_ATTR *attr ,MMP_USHORT usSubAdd, MMP_USHORT usData, MMP_ULONG ulDataAddr)
{
	return MMPD_I2cm_ReadBurstData(attr, usSubAdd, usData, ulDataAddr);
}

