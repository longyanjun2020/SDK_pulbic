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
* @file    srv_resmgr_mmlcommon_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLCOMMON_TYPES_H__
#define __SRV_RESMGR_MMLCOMMON_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerManager
    @brief      Error codes
*/
opaque_enum(MmlErrCode_e_)
{
    MML_ERROR_SUCCESS = 0,
    MML_ERROR_FAIL,
    MML_ERROR_PRECONDITIONS_VIOLATED,
    MML_ERROR_PARAMETER_INVALID,
    MML_ERROR_MEMORY_FAILURE,
    MML_ERROR_RESOURCE_ERROR,
    MML_ERROR_RESOURCE_LOST,
    MML_ERROR_IO_ERROR,
    MML_ERROR_BUFFER_INSUFFICIENT,
    MML_ERROR_CONTENT_CORRUPTED,
    MML_ERROR_CONTENT_UNSUPPORTED,
    MML_ERROR_CONTENT_NOT_FOUND,
    MML_ERROR_PERMISSION_DENIED,
    MML_ERROR_FEATURE_UNSUPPORTED,
    MML_ERROR_INTERNAL_ERROR,
    MML_ERROR_UNKNOWN_ERROR,
    MML_ERROR_OPERATION_ABORTED,
    MML_ERROR_CONTROL_LOST,
    MML_ERROR_OPERATION_ASYNCTOSYNC,
    MML_ERROR_OPERATION_IMMEDIATELY,
    MML_ERROR_OPERATION_DROP,
    MML_ERROR_NUM
};

/** @ingroup    MMLayerManager
    @brief      Use case group IDs
*/
opaque_enum(MmlUseCaseGroupId_e_)
{
    MML_UCGID_MANAGER = 0x0,
    MML_UCGID_AUDIO = 0x1,
    MML_UCGID_VIDEO = 0x2,
    MML_UCGID_IMAGE = 0x3,
    MML_UCGID_DISPLAY = 0x4,
    MML_UCGID_GAME = 0x5,
    MML_UCGID_USB = 0x6,
    MML_UCGID_TV = 0x7,
    MML_UCGID_CAMERA = 0x8,
    MML_UCGID_RADIO = 0x9,
    MML_UCGID_GPS = 0xa,
    MML_UCGID_WLAN = 0xb,
    MML_UCGID_UTILITY = 0xc,
    MML_UCGID_VIDEOSDK = 0xd,
    MML_UCGID_RFID = 0xe,
};

/** @ingroup    MMLayerManager
    @brief      Filename formats
*/
opaque_enum(MmlFilenameFormat_e_)
{
    MML_FILENAMEFORMAT_DIRECTORY = 0x0,    ///< Specify the folder only
    MML_FILENAMEFORMAT_PREFIX,             ///< Specify the folder + filename's prefix
    MML_FILENAMEFORMAT_ABSOLUTE,           ///< Specify the folder + filename
    MML_FILENAMEFORMAT_NUM
};

/** @ingroup    MMLayerManager
    @brief      File operating modes
*/
opaque_enum(MmlFileOperatingMode_e_)
{
    MML_FILEOPERATINGMODE_WRITERENAME = 0x0,    ///< Write at the beginning of the file. If the file exists, rename to create another file for writing.
    MML_FILEOPERATINGMODE_WRITEAPPEND,          ///< Write at the end of the file. If the file doesn't exist, create the file first.
    MML_FILEOPERATINGMODE_WRITERENEW,           ///< Write at the beginning of the file. If the file exists, its contents are destroyed.
    MML_FILEOPERATINGMODE_NUM
};

/** @ingroup    MMLayerManager
    @brief      External CallbackID
*/
opaque_enum(MmlCallbackId_e_)
{
    MML_CALLBACKID_ISRESMGRTASKIDLE = 0

};

/** @ingroup    MMLayerManager
    @brief      Color formats
*/
typedef enum
{
    IMAGE_COLORFORMAT_RGB565 = 0,
    IMAGE_COLORFORMAT_RGB888,
    IMAGE_COLORFORMAT_YUV420,
    IMAGE_COLORFORMAT_YUV422H2V1,
    IMAGE_COLORFORMAT_COLOR_INDEX_8BIT,
    IMAGE_COLORFORMAT_DONTCARE,
    /* */
    IMAGE_COLORFORMAT_NUM
} MmlImageColorFormat_e;


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLCOMMON_TYPES_H__

