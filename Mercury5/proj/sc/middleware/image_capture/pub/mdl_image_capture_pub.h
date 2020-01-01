////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mdl_image_capture_pub.h
* @version
* @brief   Image Capture header file.
*
*/

#ifndef __MDL_IMAGECAPUTRE_PUB_H__
#define __MDL_IMAGECAPUTRE_PUB_H__

/*=============================================================*/
//  Includes Files
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum {
    /* Common   (0x0000 ~ 0x0FFF) */
    MSMERR_IMGCAP_OK = 0x0000,
    MSMERR_IMGCAP_FALSE = 0x0001,
    /* REC  (0x5000 ~ 0x5FFF) */
    MSMERR_IMGCAP_FAIL = 0x5000,
    MSMERR_IMGCAP_IBUFOV = 0x5001,
    MSMERR_IMGCAP_OUTOFDISK = 0x5002,
    MSMERR_IMGCAP_REDO = 0x5003,
    MSMERR_IMGCAP_CREATE_FILE_ERR = 0x5004,
    MSMERR_IMGCAP_TIMEOUT = 0x5005,
    MSMERR_IMGCAP_NOT_SUPP_RESOLUTION = 0x5006,
    MSMERR_IMGCAP_SUCCESS = 0x5007,
    MSMERR_IMGCAP_SUCCESS_STOP_CONTINUOUS_CAPTURE = 0x5008,
    MSMERR_IMGCAP_OUT_OF_MEMORY = 0x5009,
    MSMERR_IMGCAP_OPEN_FILE_FAILED = 0x500a,
    MSMERR_IMGCAP_OPEN_SD_NOT_DETECT = 0x500b,
    MSMERR_IMGCAP_OPEN_SD_WRITE_FAIL = 0x500c,
    MSMERR_IMGCAP_OPEN_SD_CLOSE_FAIL = 0x500d,
    MSMERR_IMGCAP_AUDIO_OPEN_FAIL = 0x500e,
    MSMERR_IMGCAP_GET_CAPACITY_FAIL = 0x500f,
    MSMERR_IMGCAP_CMDRESPONSE_TIMEOUT = 0x5010,
} MSMIMGCAPErrcode_e;
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
//  Local function definition
/*=============================================================*/

/*=============================================================*/
// Global Function definition
/*=============================================================*/

/**
 * @brief Handler of middleware of image-capture task
 *
 * @param pMessage          : Received message.
 *
 * @return                  : None
 */
void MdlImgCapParseMsg(void *pMessage);

/**
 * @brief Initial middleware of image-capture task
 *
 * @param                   : None
 *
 * @return                  : None
 */
void MdlImgCapInit(void);



/**
 * @brief Initial fake driver for middleware of image-capture testing
 *
 * @param                   : None
 *
 * @return                  : None
 */
void MdlImgCapMainTaskInit(void);


/**
 * @brief Handler of fake driver for middleware of image-capture testing
 *
 * @param pMessage          : Received message.
 *
 * @return                  : None
 */
void MdlImgCapMainTask(void *pMessage);

/**
 * @brief Initial fake driver for middleware of image-capture testing
 *
 * @param                   : None
 *
 * @return                  : None
 */
void MdlImgCapShutterSndInit(void);


/**
 * @brief Handler of fake driver for middleware of image-capture testing
 *
 * @param pMessage          : Received message.
 *
 * @return                  : None
 */
void MdlImgCapShutterSndTask(void * pMessage);

MSMIMGCAPErrcode_e MdlJPE_UVC_Init(void);
MSMIMGCAPErrcode_e MdlJPE_UVC_Sensor(u32 nWidth, u32 nHeight);
MSMIMGCAPErrcode_e MdlJPE_UVC_Encode(u32 *pointer, u32 *length);
MSMIMGCAPErrcode_e MdlJPE_UVC_deInit(void);

#endif /* __MDL_IMAGECAPUTRE_PUB_H__ */

