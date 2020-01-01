////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MDL_CAMERA_STABILIZER_H_
#define	_MDL_CAMERA_STABILIZER_H_

#include "mdl_camera_ip_pub.h"

/**
 *	@file
 *	@brief public video stabilizer interface
 */

typedef struct __VS_Config_t VS_Config_t;


/**
 *	the main function of video stabilizer
 *	@param[in] pImageBuffer		the pointer of image buffer
 *	@param[in] nWidth			width of image buffer
 *	@param[in] nHeight			height of image buffer
 *	@param[out] pMV				the moving vector
 *	@return						error code
 */
s32		VS_Main(u8 *pImageBuffer, s32 nWidth, s32 nHeight, s32 *pMV);


/**
 *	to enable or disable video stabilizer
 *	@param[in] bEnable			0: disable video stabilizer; 1: enable video stabilizer
 */
void	VS_Enable(u8 bEnable);


/**
 *	to configure the settings of video stabilizer
 *	@param[in] pNewConfig		update the configuration of video stabilizer (only for expert)
 */
void	VS_Config(VS_Config_t *pNewConfig);

/**
 *	to update the frame rate information to video stabilizer
 *	@param[in] bIs15fps			0: 30 frame rate; 1: 15 frame rate
 */
void	VS_SetFramerateTarget(u8 bIs15fps);

#endif

