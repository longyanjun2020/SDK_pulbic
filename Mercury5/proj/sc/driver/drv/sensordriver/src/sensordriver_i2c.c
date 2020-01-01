
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (������MStar Confidential Information������) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __cplusplus
}
#endif

#include "drv_bus_i2c.h"
#include "sys_sys_isw_uart.h"

//#include "sys_MsWrapper_cus_os_mem.h"
//#include "sys_MsWrapper_cus_os_util.h"
//#include "drv_i2c_common.h"
#include <isp_i2c_api.h>

//#define _ERROR_   /*_DEBUG_      _ERROR_*/
#include <sensor_log.h>

#if defined(__RTK_OS__)
#include "sys_MsWrapper_cus_os_sem.h"
#endif
#define I2C_RETRYTIME (5)
#define SENSOR_I2C_SEM_TIMEOUT (1000)

int WriteRegisterPair( app_i2c_cfg tCfg, short nReg, short nValue, ISP_I2C_FMT eFmt)
{
	unsigned char data[4];
	I2CErrorCode_e i2cRet = I2C_PROC_DONE;
	I2COptions_t stI2COption;
#if defined(__RTK_OS__)	
	cus_ErrCode_e err_ret;
#endif
	SENSOR_DMSG("[%s]\n", __FUNCTION__);

    s32 nHandleID = 0;
    stI2COption.nSlaveID = tCfg.address;
    stI2COption.nChannel = tCfg.nChannel;
    stI2COption.ePadNum = tCfg.nPadNum;
    stI2COption.bReStart = 1;
    stI2COption.eClockSpeed = tCfg.speed;
    stI2COption.bDMAenable = 1;

    memset(data, 0, sizeof(data));
	
#if defined(__RTK_OS__)
    err_ret = MsConsumeSemDelay(SENSOR_I2C_CH_SEM + stI2COption.nChannel, SENSOR_I2C_SEM_TIMEOUT);
    if(err_ret != CUS_OS_OK){
        UartSendTrace("[%s] MsConsumeSemDelay nChannel:%d error!\n",__FUNCTION__, stI2COption.nChannel);
        return I2C_ERROR;
    }
#endif	
	DrvI2cOpen(&nHandleID,&stI2COption);

	switch(eFmt)
	{
		case I2C_FMT_A8D8:
			data[0] = nReg & 0xff;
			data[1] = nValue & 0xff;
            i2cRet = DrvI2cWrite(nHandleID,(void *) data, 2, 0);
			break;
		case I2C_FMT_A16D8:
			data[0] = (nReg >> 8) & 0xff;
			data[1] = nReg & 0xff;
			data[2] = nValue & 0xff;
            i2cRet = DrvI2cWrite(nHandleID,(void *) data, 3, 0);
			break;
		case I2C_FMT_A8D16:
			data[0] = nReg & 0xff;
			data[1] = (nValue >> 8) & 0xff;
			data[2] = (nValue ) & 0xff;
            i2cRet = DrvI2cWrite(nHandleID,(void *) data, 3, 0);
			break;
		case I2C_FMT_A16D16:
			data[0] = (nReg >> 8) & 0xff;
			data[1] = (nReg ) & 0xff;
			data[2] = (nValue >> 8) & 0xff;
			data[3] = (nValue ) & 0xff;
            i2cRet = DrvI2cWrite(nHandleID,(void *) data, 4, 0);
			break;

		default:
			SENSOR_EMSG("[%s] Not support I2C format\n",__FUNCTION__);
			i2cRet = I2C_BAD_PARAMETER;
			break;
	}

    DrvI2cClose(nHandleID);

#if defined(__RTK_OS__)
    err_ret = MsProduceSem(SENSOR_I2C_CH_SEM + stI2COption.nChannel);
    if(err_ret != CUS_OS_OK){
        UartSendTrace("[%s] MsProduceSem nChannel:%d error!\n",__FUNCTION__, stI2COption.nChannel);
        return I2C_ERROR;
    }
#endif

	return i2cRet;
}

int ReadRegisterPair( app_i2c_cfg tCfg, unsigned int nReg, unsigned short *pnVal, ISP_I2C_FMT eFmt)
{
#define I2C_DMA_ALIGN_BASE 0x10
    unsigned char reg_addr[2];
    unsigned char array[I2C_DMA_ALIGN_BASE+2];
    unsigned long alignaddr;
    I2CErrorCode_e i2cRet = I2C_PROC_DONE;
    I2COptions_t stI2COption;
#if defined(__RTK_OS__)	
    cus_ErrCode_e err_ret;
#endif

    SENSOR_DMSG("[%s]\n", __FUNCTION__);
	memset(reg_addr, 0, sizeof(unsigned char));
	s32 nHandleID = 0;

	stI2COption.nSlaveID = tCfg.address;
	stI2COption.nChannel = tCfg.nChannel;
	stI2COption.ePadNum = tCfg.nPadNum;
	stI2COption.bReStart = 1;
	stI2COption.eClockSpeed = tCfg.speed;
	stI2COption.bDMAenable = 0;

    alignaddr = (unsigned long)array;
    alignaddr = (alignaddr+(I2C_DMA_ALIGN_BASE-1))&~(I2C_DMA_ALIGN_BASE-1);    

#if defined(__RTK_OS__)
    err_ret = MsConsumeSemDelay(SENSOR_I2C_CH_SEM + stI2COption.nChannel, SENSOR_I2C_SEM_TIMEOUT);
    if(err_ret != CUS_OS_OK){
        UartSendTrace("[%s] MsConsumeSemDelay nChannel:%d error!\n",__FUNCTION__, stI2COption.nChannel);
        return I2C_ERROR;
    }
#endif

	DrvI2cOpen(&nHandleID,&stI2COption);

	switch(eFmt)
	{
		case I2C_FMT_A8D8:
			reg_addr[0] =  nReg & 0xff;
            i2cRet = DrvI2cWrite(nHandleID,(void *) reg_addr, 1, 0);
            if(i2cRet != I2C_PROC_DONE)
                goto END_READ;//return FAIL;
            i2cRet = DrvI2cRead(nHandleID, (void *) alignaddr, 1);
            if(i2cRet != I2C_PROC_DONE)
                goto END_READ;//return FAIL;
			break;

		case I2C_FMT_A16D8:
			reg_addr[0] = (nReg >> 8) & 0xff;
			reg_addr[1] =  nReg & 0xff;
            i2cRet = DrvI2cWrite(nHandleID,(void *) reg_addr, 2, 0);
            if(i2cRet != I2C_PROC_DONE)
                goto END_READ;//return FAIL;
            i2cRet = DrvI2cRead(nHandleID, (void *) alignaddr, 1);
            if(i2cRet != I2C_PROC_DONE)
                goto END_READ;//return FAIL;
			break;

		case I2C_FMT_A8D16:
			reg_addr[0] =  nReg & 0xff;
            i2cRet = DrvI2cWrite(nHandleID,(void *) reg_addr, 1, 0);
            if(i2cRet != I2C_PROC_DONE)
                goto END_READ;//return FAIL;
            i2cRet = DrvI2cRead(nHandleID, (void *) alignaddr, 2);
            if(i2cRet != I2C_PROC_DONE)
                goto END_READ;//return FAIL;
			break;

		case I2C_FMT_A16D16:
			reg_addr[0] = (nReg >> 8) & 0xff;
			reg_addr[1] =  nReg & 0xff;
            i2cRet = DrvI2cWrite(nHandleID,(void *) reg_addr, 2, 0);
            if(i2cRet != I2C_PROC_DONE)
                goto END_READ;//return FAIL;
            i2cRet = DrvI2cRead(nHandleID, (void *) alignaddr, 2);
            if(i2cRet != I2C_PROC_DONE)
                goto END_READ;//return FAIL;
			break;

		default:
			SENSOR_EMSG("[%s] not support I2C format\n",__FUNCTION__);
			goto END_READ;//return FAIL;
	}

END_READ:
    DrvI2cClose(nHandleID);

#if defined(__RTK_OS__)
    err_ret = MsProduceSem(SENSOR_I2C_CH_SEM + stI2COption.nChannel);
    if(err_ret != CUS_OS_OK){
        UartSendTrace("[%s] MsProduceSem nChannel:%d error!\n",__FUNCTION__, stI2COption.nChannel);
        return I2C_ERROR;
    }
#endif

    *pnVal = *(unsigned short*)alignaddr;
    
	return i2cRet;
}

int MstarExternalI2cTx( app_i2c_cfg tCfg, short nReg, short nData)
{
	int ret = SUCCESS;

	ret = WriteRegisterPair( tCfg, nReg, nData, tCfg.fmt);
	if(ret == FAIL)
		SENSOR_EMSG("[%s] Fail!!, addr = %#x, data = %#x\n", __func__, nReg, nData);
	else
		SENSOR_DMSG("[%s] addr = %#x, data = %#x\n", __func__, nReg, nData);
	return ret;
}

int MstarExternalI2cRx(app_i2c_cfg tCfg, short nReg, volatile short *pnDdata)
{
	unsigned short tmp_data;
	int ret = SUCCESS;

	ret = ReadRegisterPair( tCfg, nReg, &tmp_data, tCfg.fmt);
	if(ret == FAIL)
	{
		SENSOR_EMSG("[%s] Fail!!, read reg = %#x \n", __func__, nReg);
		return FAIL;
	}
	switch(tCfg.fmt)
	{
		default:
		case I2C_FMT_A8D8:
		case I2C_FMT_A16D8:
			*pnDdata = tmp_data & 0x00ff;
			break;
		case I2C_FMT_A8D16:
		case I2C_FMT_A16D16:
			tmp_data = tmp_data & 0x00ffff;
			*pnDdata = (unsigned short)((tmp_data & 0xff00) >> 8) | ((tmp_data & 0x00ff) << 8);
			break;
	}

	SENSOR_DMSG("[%s] addr = %#x, data = %#x\n", __func__, nReg, *pnDdata);
    return ret;
}

int MstarExternalI2cArrayTx( app_i2c_cfg tCfg, I2C_ARRAY *ptData, int nLen)
{
    unsigned short i, reg, data;
	int ret = 0;
	int retry = 0;

	for (i = 0; i < nLen; i++)
	{
		reg = ptData[i].reg;
		data = ptData[i].data;
		retry = I2C_RETRYTIME;
		while(retry--)
		{
			ret = WriteRegisterPair( tCfg, reg, data, tCfg.fmt);
			SENSOR_DMSG("[%s] addr = %#x, data = %#x\n", __func__, reg, data);
			if(ret == SUCCESS )
				break;
		}

		if(ret == FAIL)
		{
			SENSOR_EMSG("[%s] Fail!!, addr = %#x, data = %#x \n", __func__, reg, data);
			return FAIL;
		}
    }
    return SUCCESS;
}

int MstarExternalI2cArrayRx( app_i2c_cfg tCfg, I2C_ARRAY *ptData, int nLen)
{
	int i;
	unsigned short tmp_data, reg;
	int ret = 0;

    SENSOR_DMSG("[%s]\n", __FUNCTION__);
	for (i = 0; i < nLen; i++)
	{
		reg = ptData[i].reg;
		ret = ReadRegisterPair( tCfg, reg, &tmp_data, tCfg.fmt);
		if(ret == FAIL)
		{
			return FAIL;
		}
		switch(tCfg.fmt)
		{
			default:
			case I2C_FMT_A8D8:
			case I2C_FMT_A16D8:
				ptData[i].data =  tmp_data & 0xff;
				break;
			case I2C_FMT_A8D16:
			case I2C_FMT_A16D16:
				ptData[i].data = ((tmp_data & 0xff00) >> 8) | ((tmp_data & 0x00ff) << 8);
				break;
		}
	}
	return SUCCESS;
}
/*
int DrvIspExternalI2cOpen(i2c_handle_t*  app_i2c_cfg *ptCfg)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    return SUCCESS;
}

int DrvIspExternalI2cClose(i2c_handle_t* ptHandle)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
	return SUCCESS;
}

int DrvIspExternalI2cRelease(i2c_handle_t *ptHandle)
{
    SENSOR_DMSG("[%s]\n", __FUNCTION__);
    CamOsMemRelease(ptHandle);
    return SUCCESS;
}

int  DrvIspExternalI2cInit(i2c_handle_t **pptHandle)
{
	i2c_handle_t * i2c_hnd = (i2c_handle_t * )CamOsMemAlloc(sizeof(i2c_handle_t));
	*pptHandle = i2c_hnd;

	if (!pptHandle)
	{
		SENSOR_EMSG("[%s] i2c_handle calloc fail\n", __FUNCTION__);
		return -1;
	}
	SENSOR_DMSG("[%s]\n", __FUNCTION__);

	i2c_hnd->i2c_open          = DrvIspExternalI2cOpen;
	i2c_hnd->i2c_close          = DrvIspExternalI2cClose;
	i2c_hnd->i2c_tx              = MstarExternalI2cTx;
	i2c_hnd->i2c_rx              = MstarExternalI2cRx;
	i2c_hnd->i2c_array_tx	= MstarExternalI2cArrayTx;
	i2c_hnd->i2c_array_rx	= MstarExternalI2cArrayRx;

    return SUCCESS;
}
*/
