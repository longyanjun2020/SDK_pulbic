/// @ait_only
//==============================================================================
//
//  File        : mmpd_i2cm.c
//  Description : Ritina I2C Master Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

/**
*  @file mmpd_i2cm.c
*  @brief The I2C Master Module Control functions
*  @author Penguin Torng
*  @version 1.0
*/

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_i2cm.h"
#include "mmpf_i2cm.h"

/** @addtogroup MMPD_I2CM
 *  @{
 */

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//*----------------------------------------------------------------------------
// function : MMPD_I2cm_WriteReg
// input    : (enable/disable)
// output   : none
// descript : Write one I2C data to specific register 
//*----------------------------------------------------------------------------
/**
 @brief Write one I2C data to specific register 
 Parameters:
 @param[in] p_i2cm_attribute : I2CM attribute, please refer the structure MMP_I2CM_ATTR
 @param[in] usSubAddr : The register sub address.
 @param[in] usData : The data to be sent.
 @return the status of the operation
*/
MMP_ERR MMPD_I2cm_WriteReg(MMP_I2CM_ATTR *attr, MMP_USHORT usReg, MMP_USHORT usData)
{
	return MMPF_I2cm_WriteReg(attr, usReg, usData);
}

//*----------------------------------------------------------------------------
// function : MMPD_I2cm_ReadReg
// input    : (address)
// output   : (data)
// descript : I2C Signal Register Word Reading
//*----------------------------------------------------------------------------
/**
 @brief Read one I2C data to specific register 

 Receives data over I2C interface to specific device.
 Parameters:
 @param[in] p_i2cm_attribute : I2CM attribute, please refer the structure MMP_I2CM_ATTR
 @param[in] usReg : The register sub address. //Note: usReg is used for stand for data-count in the case ubRegLen = 0
 @param[in] *usData	The received data.
 @return the status of the operation
*/
MMP_ERR MMPD_I2cm_ReadReg(MMP_I2CM_ATTR *attr, MMP_USHORT usReg, MMP_USHORT *usData)
{
	return MMPF_I2cm_ReadReg(attr, usReg, usData);
}

//*----------------------------------------------------------------------------
// function : MMPD_I2cm_WriteBurstData
// input    : (address)
// output   : (data)
// descript : I2C burst write ,write reg(usReg), reg(usReg + 1)....reg(usReg + usDataCnt - 1)
//*----------------------------------------------------------------------------
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
MMP_ERR MMPD_I2cm_WriteBurstData(MMP_I2CM_ATTR *attr, MMP_USHORT usSubAdd, MMP_USHORT usData, MMP_ULONG ulDataAddr)
{
	MMP_ERR status = MMP_ERR_NONE;

	status |= MMPF_I2cm_WriteBurstData(attr, usSubAdd, (MMP_USHORT *)ulDataAddr, usData, MMP_TRUE);
	return status;
}

//*----------------------------------------------------------------------------
// function : MMPF_I2cm_ReadBurstData
// input    : (address)
// output   : (data)
// descript : I2C burst read ,read reg(usReg), reg(usReg + 1)....reg(usReg + usDataCnt - 1)
// Note		: The depth of I2CM RX fifo is only 8 bytes.
//*----------------------------------------------------------------------------
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
MMP_ERR MMPD_I2cm_ReadBurstData(MMP_I2CM_ATTR *attr, MMP_USHORT usSubAdd, MMP_USHORT usData, MMP_ULONG ulDataAddr)
{
	MMP_ERR status;

	status |= MMPF_I2cm_ReadBurstData(attr, usSubAdd, (MMP_USHORT *)ulDataAddr, usData);
	return status;
}
