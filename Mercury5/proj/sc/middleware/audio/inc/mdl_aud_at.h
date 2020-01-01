////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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

/**
* @file    mdl_audio_at.h
* @version
* @brief   header file
*
*/

#ifndef __MDL_AUD_AT_H__
#define __MDL_AUD_AT_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
// #include mdl_audio.h" is replaced by the following three header
#include "hal_audio.h"
#include "vm_audio_api.h"
#include "mdl_audio_pub_api.h"
#include "mdl_aud_pub_api.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
/**
 * @brief The enumeration defines the device type.
 */
typedef enum
{
    MDL_AUD_SIM_MASTER = 0,   /**< Master */
    MDL_AUD_SIM_SLAVE         /**< Slave  */
} MdlAudDualMode_e;

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/**
 * @brief Init at command for voc task
 *
 * @param       : NONE
 *
 * @return      : NONE
 */
MdlAudRet_e MdlAudATInit(void);


/**
 * @brief Calculate minimum value
 *
 * @param  in   : [in] input path
 *
 * @param  out  : [in] output path
 *
 * @return      : NONE
 */
MdlAudRet_e MdlAudSetPath(MdlAudInput_e eIn, MdlAudOutput_e eOut, MdlAudDualMode_e eMode);


/**
 * @brief Set input volume
 *
 * @param  volume : [in] input volume (0-255)
 *
 * @return        : NONE
 */
MdlAudRet_e MdlAudSetInVolume(u8 nVolume, MdlAudDualMode_e nMode);


/**
 * @brief Set output volume
 *
 * @param  volume : [in] output volume (0-255)
 *
 * @return        : NONE
 */
MdlAudRet_e MdlAudSetOutVolume(u8 nVolume, MdlAudDualMode_e nMode);

#endif //__MDL_AUD_AT_H__

