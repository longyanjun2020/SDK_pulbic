/**
 *
 * @file    esl_vc_itf.c
 *
 * @brief   This file defines the video chat interface for upper layer (like MMI) using.
 *
 * @author  Kurt Chen
 * @version $Id$
 *
 */
#ifndef __ESL_VC_ITF_H__
#define __ESL_VC_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_VC_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
/**
 *  @brief The enumeration defines the return code of the amera interface function.
 */
typedef enum {
  ESL_VC_OK,               /**< Function complete successfully */
  ESL_VC_FAIL,             /**< Function fail */
  ESL_VC_PARAM_ERROR,      /**< The input parameter is wrong */
  ESL_VC_MEM_ALLOC_ERROR,  /**< Can not allocate available memory from OS */
  ESL_VC_REJECT,           /**< Request reject because of other function's confliction */
  ESL_VC_ABORT,            /**< Request abort because of incorrect sequence */
  ESL_VC_TIMEOUT,          /**< Request command to MMP is no response */
} esl_VcErrCode_e;

/**
 *  @brief The enumeration defines the device camera.
 */
typedef enum {
    ESL_VC_CAM_ID_MAIN, /**< Main sensor */
    ESL_VC_CAM_ID_SUB,  /**< Sub sensor */
} esl_VcCamID_e;

/**
 *  @brief Video chat switch on / off
 */
typedef enum{
  ESL_VC_OFF,
  ESL_VC_ON
}esl_Vc_Switch_e;

/**
 *  @brief The enumeration defines the preview command.
 */
typedef enum{
  ESL_VC_STOP,          /**< Stop previewing */
  ESL_VC_START,         /**< Start previewing */
  ESL_VC_GETFRAME,      /**< Get Frame  */
}esl_Vc_Control_e;

typedef enum{
	ESL_VC_PRIMARY,
	ESL_VC_SECONDARY
}esl_Vc_Index_e;

/**
 *  @brief The enumeration defines the color format
 */
typedef enum{
  ESL_VC_YUV420 = 0,
  ESL_VC_RGB565 = 1
}esl_Vc_Colorformat_e;


/**
 *  @brief The enumeration defines the width and height of the frame.
 */
typedef struct{
  u16 width;
  u16 height;
}esl_Vc_Size_t;

/**
 *  @brief Structure of infomation of buffer
 */
typedef struct{
  u32 *pbuffer;           /**< Pointer to buffer */
  u32 buffer_size;        /**< Buffer size */
}esl_Vc_Buff_t;

typedef struct{
  esl_Vc_Size_t         frame_size;
  esl_Vc_Colorformat_e  color_format;
  esl_Vc_Buff_t         buffer_info;
}esl_Vc_Source_t;

typedef struct{
  esl_Vc_Size_t         frame_size;
  esl_Vc_Colorformat_e  color_format;
  esl_Vc_Buff_t         buffer_info;
  u16                   X0;
  u16                   Y0;
  u16                   pitch;
}esl_Vc_Destination_t;

typedef struct{
  union{
    esl_Vc_Buff_t buffer_info;
    }param;
}esl_VcInfo_t;


typedef void (*esl_VcCb)(u16 senderID, u32 userValue, esl_VcErrCode_e errCode, esl_VcInfo_t *pVcInfo);

typedef struct {
  u16        senderID;  /**< Sender ID */
  u32        userValue; /**< Reference value for indicating different sender in same task or check msg response. */
  esl_VcCb   pfnCb;     /**< Call back function that called by Media task after process finished. */
} esl_VcCb_t;

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/* @brief Video chat preview command: Start preview / Get Frame / Stop preview
 *
 * @param preview_control : ESL_VC_STOP,  ESL_VC_START,  ESL_VC_GETFRAME,
 * @param frame_size      : Width , height
 * @param color_format    : YUV420/RGB565
 * @param buffer_info     : buffer address , buffer size
 * @param pVcCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_CAM__VC_OK   : Command success.
 * @return ESL_CAM_VC_FAIL  : Command fail.
 */

esl_VcErrCode_e esl_Vc_Preview(esl_Vc_Index_e index,esl_Vc_Control_e preview_control,esl_Vc_Size_t frame_size,esl_Vc_Colorformat_e color_format,esl_Vc_Buff_t buffer_info,esl_VcCb_t *pVcCb);


/* @brief Video chat power off
 *
 * @param camID           : Sensor device id.
 * @param pVcCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_CAM__VC_OK   : Close success.
 * @return ESL_CAM_VC_FAIL  : Close fail.
 */
esl_VcErrCode_e esl_Vc_Exit(esl_VcCamID_e camId, esl_VcCb_t *pVcCb);


/* @brief Video chat power on
 *
 * @param camID           : Sensor device id.
 * @param pVcCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_CAM__VC_OK   : Open success.
 * @return ESL_CAM_VC_FAIL  : Open fail.
 */
esl_VcErrCode_e esl_Vc_Init(esl_VcCamID_e camId, esl_VcCb_t *pVcCb);



/* @brief Video color space coversion
 *
 * @param source            : Source video information.
 * @param destination       : destination video information.
 * @param pVcCb             : Call back structure, include sender ID, userValue and call back function.
 *                            It uses to send response message that provide by application layer(MMI)
 *                            to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_CAM__VC_OK   : Open success.
 * @return ESL_CAM_VC_FAIL  : Open fail.
 */
esl_VcErrCode_e esl_Vc_Convert(esl_Vc_Source_t source, esl_Vc_Destination_t destination, esl_VcCb_t *pVcCb);


#endif /* __ESL_VC_ITF_H__ */

