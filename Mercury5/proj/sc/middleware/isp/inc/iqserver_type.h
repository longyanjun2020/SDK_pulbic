/**************************************************************************
 * 	FileName:		tool_type.h
 *	Description:	system param define
 *	Copyright(C):	2010-2010 mstar Inc.
*	Version:
 *	Author:
 *	Created:		2010-4-20
 *	Updated:
 **************************************************************************/

#ifndef _IQSERVER_TYPE_H
#define _IQSERVER_TYPE_H

#include <iqserver_api_id.h>

#define MIN_DATA_LEN    2

typedef enum
{
    CAMERA_MODE_YUV_422,  //yuv after scaler
    CAMERA_MODE_YUV_420,
    CAMERA_MODE_ISP_RAW,  //raw from sensor
    CAMERA_MODE_ISP_YC,   //yuv before scaler
    CAMERA_MODE_ISP_STS,  //raw before demosaic
    CAMERA_MODE_ENC_JPEG
} CAMERA_MODE_TYPE;

typedef enum
{
	CALIBRATION_DATA = 1,
	XML_DATA = 2,
}FILE_TRANSFER_ID;
typedef enum
{
    CAMERA_CMD_SET = 0,
    CAMERA_CMD_GET,
    CAMERA_CMD_SET_MODE ,
    CAMERA_CMD_GET_MODE,
    CAMERA_CMD_GET_PIC,
    CAMERA_CMD_SET_API,
    CAMERA_CMD_GET_API,
	CAMERA_CMD_UPLOAD_FILE,    /* client upload file to server */
	CAMERA_CMD_DOWNLOAD_FILE,  /* client download file from server*/
} CAMERA_EXT_CMD_TYPE;

typedef struct	_IQ_CMD_HEADER_S
{
    CAMERA_EXT_CMD_TYPE CmdType;
	int		        CmdLen;
}IQ_CMD_HEADER_S;

typedef enum  _IQ_RESPONSE_CODE_E
{
	IQ_RES_OK           = 0x0,
	IQ_RES_ERROR
}IQ_RESPONSE_CODE_E;


typedef struct	_IQ_CMD_RESPONSE_S
{
    IQ_RESPONSE_CODE_E  ResCode;
	int         		DataLen;

}IQ_CMD_RESPONSE_S;

#endif
