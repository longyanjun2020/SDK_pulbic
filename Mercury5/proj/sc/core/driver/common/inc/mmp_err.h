//==============================================================================
//
//  File        : mmp_err.h
//  Description : Top level system error definition.
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================
/**
 @file mmp_err.h
 @brief The header file of MMP error codes

 This is a common file used in firmware and the host side, it describle the error codes that shared between
 firmware and host side

 @author Penguin Torng
 @version 1.0 Original Version
*/

#ifndef _MMP_ERR_H_
#define _MMP_ERR_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MODULE_ERR_SHIFT        24

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef enum _MMP_MODULE
{
    MMP_HIF     = 0,
    MMP_SYSTEM  = 1,
    MMP_SENSOR  = 2,
    MMP_VIF     = 3,
    MMP_ISP     = 4,
    MMP_SCALER  = 5,
    MMP_ICON    = 6,
    MMP_INT     = 9, //CarDV... No used.  Remove it after AHC_ERR is deleted.
    MMP_DSPY    = 10,
    MMP_DRAM    = 11,
    MMP_I2CM    = 12,
    MMP_PSPI    = 13,
    MMP_DMA     = 14,
    MMP_SD      = 15,
    MMP_NAND    = 16,
    MMP_MP4VE   = 17,
    MMP_MP4VD   = 18,
    MMP_H264D   = 19,
    MMP_USB     = 20,
    MMP_FS      = 21,
    MMP_3GPMGR  = 22,
    MMP_3GPPSR  = 23,
    MMP_AUDIO   = 24,
    MMP_DSC     = 25,
    MMP_3GPPLAY = 28,
    MMP_3GPRECD = 29,
    MMP_UART    = 30,
    MMP_SPI     = 32,
    MMP_PLL     = 33,
    MMP_USER    = 34,
    MMP_CCIR    = 36,
    MMP_STORAGE = 37,
    MMP_PIO     = 38,
    MMP_PWM     = 40,
    MMP_RAWPROC = 41,
    MMP_SIF     = 42,
    MMP_EVENT   = 43,
    MMP_MJPGD   = 44,
    MMP_LDC     = 46,
    MMP_RTC     = 47,
    MMP_CORES   = 48,
    MMP_WIFI    = 49,
    MMP_UVC     = 50,
    MMP_COMPONENT = 51,
    MMP_PERIPHERAL = 52
} MMP_MODULE;

typedef enum _MMP_ERR
{
    MMP_ERR_NONE = 0x00000000,

    // MMP_HIF(00:00h)
    MMP_HIF_ERR_PARAMETER = (MMP_HIF << MODULE_ERR_SHIFT) | 0x000001,
    MMP_HIF_ERR_CMDTIMEOUT,

    // MMP_SYSTEM(01:01h)
    MMP_SYSTEM_ERR_PARAMETER = (MMP_SYSTEM << MODULE_ERR_SHIFT) | 0x000001,
    MMP_SYSTEM_ERR_CMDTIMEOUT,
    MMP_SYSTEM_ERR_HW,
    MMP_SYSTEM_ERR_CPUBOOT,
    MMP_SYSTEM_ERR_SETOPMODE,
    MMP_SYSTEM_ERR_MALLOC,
    MMP_SYSTEM_ERR_FORMAT,
    MMP_SYSTEM_ERR_TIMER,
    MMP_SYSTEM_ERR_PMU,
    MMP_SYSTEM_ERR_DOUBLE_SET_ALARM,
    MMP_SYSTEM_ERR_ADC,

    // MMP_SENSOR(02:02h)
    MMP_SENSOR_ERR_PARAMETER = (MMP_SENSOR << MODULE_ERR_SHIFT) | 0x000001,
    MMP_SENSOR_ERR_INITIALIZE,
    MMP_SENSOR_ERR_INITIALIZE_NONE,
    MMP_SENSOR_ERR_SETMODE,
    MMP_SENSOR_ERR_VMD,
    MMP_SENSOR_ERR_LDWS,
    MMP_SENSOR_ERR_FCWS,
    MMP_SENSOR_ERR_NOT_SUPPORT,

    // MMP_VIF(03:03h)
    MMP_VIF_ERR_PARAMETER = (MMP_VIF << MODULE_ERR_SHIFT) | 0x000001,

    // MMP_ISP(04:04h)
    MMP_ISP_ERR_PARAMETER = (MMP_ISP << MODULE_ERR_SHIFT) | 0x000001,
    
    // MMP_SCALER(05:05h)
    MMP_SCALER_ERR_PARAMETER = (MMP_SCALER << MODULE_ERR_SHIFT) | 0x000001,
    MMP_SCALER_ERR_PTZ_SAME_RANGE,
    MMP_SCALER_ERR_LINEOFFSETNUM,

    // MMP_ICON(06:06h)
    MMP_ICON_ERR_PARAMETER = (MMP_ICON << MODULE_ERR_SHIFT) | 0x000001,
    MMP_ICON_ERR_ENABLE,
    MMP_ICON_ERR_UPDATE_ADDRESS,

    // MMP_DISPLAY(10:0Ah)
    MMP_DISPLAY_ERR_PARAMETER = (MMP_DSPY << MODULE_ERR_SHIFT) | 0x000001,
    MMP_DISPLAY_ERR_NOT_SUPPORT,
    MMP_DISPLAY_ERR_HW,
    MMP_DISPLAY_ERR_OVERRANGE,
    MMP_DISPLAY_ERR_START_PREVIEW_TIMEOUT,
    MMP_DISPLAY_ERR_STOP_PREVIEW_TIMEOUT,
    MMP_DISPLAY_ERR_RGBLCD_NOT_ENABLED,
    MMP_DISPLAY_ERR_LCD_BUSY,
    MMP_DISPLAY_ERR_FRAME_END,
    MMP_DISPLAY_ERR_WIN_ENABLE,
    MMP_DISPLAY_ERR_WIN_ADDR,
    
    // MMP_DRAM(11:0Bh)
    MMP_DRAM_ERR_PARAMETER = (MMP_DRAM << MODULE_ERR_SHIFT) | 0x000001,
    MMP_DRAM_ERR_INITIALIZE,
    MMP_DRAM_ERR_NOT_SUPPORT,

    // MMP_I2CM(12:0Ch)
    MMP_I2CM_ERR_PARAMETER = (MMP_I2CM << MODULE_ERR_SHIFT) | 0x000001,
    MMP_I2CM_ERR_SLAVE_NO_ACK,
    MMP_I2CM_ERR_READ_TIMEOUT,
    MMP_I2CM_ERR_SEM_TIMEOUT,
    MMP_I2CM_ERR_TIMEOUT,
    MMP_I2CM_ERR_PEND_ISR,

    // MMP_PSPI(13:0Dh)
    MMP_PSPI_ERR_PARAMETER = (MMP_PSPI << MODULE_ERR_SHIFT) | 0x000001,

    // MMP_DMA(14:0Eh)
    MMP_DMA_ERR_PARAMETER = (MMP_DMA << MODULE_ERR_SHIFT) | 0x000001,
    MMP_DMA_ERR_BUSY,

    // MMP_SD(15:0Fh)
    MMP_SD_ERR_COMMAND_FAILED = (MMP_SD << MODULE_ERR_SHIFT) | 0x000001,
    MMP_SD_ERR_RESET,
    MMP_SD_ERR_PARAMETER,
    MMP_SD_ERR_DATA,
    MMP_SD_ERR_NO_CMD,
    MMP_SD_ERR_BUSY,
    MMP_SD_ERR_CARD_REMOVED,
    MMP_SD_ERR_COMMAND_SENDDONETIMEOUT,
    MMP_SD_ERR_TIMEOUT,

    // MMP_NAND(16:10h)
    MMP_NAND_ERR_PARAMETER = (MMP_NAND << MODULE_ERR_SHIFT) | 0x000001,
    MMP_NAND_ERR_RESET,
    MMP_NAND_ERR_HW_INT_TO,
    MMP_NAND_ERR_ECC,
    MMP_NAND_ERR_NOT_COMPLETE,
    MMP_NAND_ERR_ERASE,
    MMP_NAND_ERR_PROGRAM,
    MMP_NAND_ERR_ECC_CORRECTABLE,
    MMP_NAND_ERR_TIMEOUT,

    // MMP_MP4VENC(17:11h)
    MMP_MP4VE_ERR_PARAMETER = (MMP_MP4VE << MODULE_ERR_SHIFT) | 0x000001,
    MMP_MP4VE_ERR_NOT_SUPPORTED_PARAMETERS,
    MMP_MP4VE_ERR_WRONG_STATE_OP,
    MMP_MP4VE_ERR_QUEUE_OVERFLOW,
    MMP_MP4VE_ERR_QUEUE_UNDERFLOW,
    MMP_MP4VE_ERR_CAPABILITY,
    MMP_MP4VE_ERR_MOD_BUSY,
    MMP_MP4VE_ERR_CARD_ERR_STOP,
    MMP_MP4VE_ERR_SKIP_FRM,
    
    // MMP_MP4VD(18:12h)
    MMP_MP4VD_ERR_BASE = MMP_MP4VD << MODULE_ERR_SHIFT, // 0x12
        /** One or more parameters were not valid.
        The input parameters are supported but are not valid value. E.g. it's out of range.*/
        MMP_MP4VD_ERR_PARAMETER = MMP_MP4VD_ERR_BASE | 0x1005,
        /** The buffer was emptied before the next buffer was ready */
        MMP_MP4VD_ERR_UNDERFLOW = MMP_MP4VD_ERR_BASE | 0x1007,
        /** The buffer was not available when it was needed */
        MMP_MP4VD_ERR_OVERFLOW = MMP_MP4VD_ERR_BASE | 0x1008,
        /** The hardware failed to respond as expected */
        MMP_MP4VD_ERR_HW = MMP_MP4VD_ERR_BASE | 0x1009,
        /** Stream is found to be corrupt */
        MMP_MP4VD_ERR_STREAM_CORRUPT = MMP_MP4VD_ERR_BASE | 0x100B,
        /** The component is not ready to return data at this time */
        MMP_MP4VD_ERR_NOT_READY = MMP_MP4VD_ERR_BASE | 0x1010,
        /** There was a timeout that occurred */
        MMP_MP4VD_ERR_TIME_OUT = MMP_MP4VD_ERR_BASE | 0x1011,
        /** Attempting a command that is not allowed during the present state. */
        MMP_MP4VD_ERR_INCORRECT_STATE_OPERATION = MMP_MP4VD_ERR_BASE | 0x1018,
        /** The values encapsulated in the parameter or config structure are not supported. */
        MMP_MP4VD_ERR_UNSUPPORTED_SETTING = MMP_MP4VD_ERR_BASE | 0x1019,

    // MMP_H264D(19:13h)
    MMP_H264D_ERR_BASE = MMP_H264D << MODULE_ERR_SHIFT, // 0x13
        /** There were insufficient resources to perform the requested operation
        E.g. The bitstream buffer is overflow. Since the video bitstream buffer is a
        plain buffer, the buffer is not able to be full loaded when one video
        frame is greater than the buffer.  For the size of the video bitstream
        buffer, refer AIT for more detail.*/
        MMP_H264D_ERR_INSUFFICIENT_RESOURCES = MMP_H264D_ERR_BASE | 0x1000,
        /** One or more parameters were not valid.
        The input parameters are supported but are not valid value. E.g. it's out of range.*/
        MMP_H264D_ERR_PARAMETER = MMP_H264D_ERR_BASE | 0x1005,
        /** The buffer was emptied before the next buffer was ready */
        MMP_H264D_ERR_UNDERFLOW = MMP_H264D_ERR_BASE | 0x1007,
        /** The buffer was not available when it was needed */
        MMP_H264D_ERR_OVERFLOW = MMP_H264D_ERR_BASE | 0x1008,
        /** The hardware failed to respond as expected */
        MMP_H264D_ERR_HW = MMP_H264D_ERR_BASE | 0x1009,
        /** The component is in the state MMP_M_STATE_INVALID */
        MMP_H264D_ERR_INVALID_STATE = MMP_H264D_ERR_BASE | 0x100A,
        /** Stream is found to be corrupt */
        MMP_H264D_ERR_STREAM_CORRUPT = MMP_H264D_ERR_BASE | 0x100B,
        /** The component is not ready to return data at this time */
        MMP_H264D_ERR_NOT_READY = MMP_H264D_ERR_BASE | 0x1010,
        /** There was a timeout that occurred */
        MMP_H264D_ERR_TIME_OUT = MMP_H264D_ERR_BASE | 0x1011,
        /** Attempting a command that is not allowed during the present state. */
        MMP_H264D_ERR_INCORRECT_STATE_OPERATION = MMP_H264D_ERR_BASE | 0x1018,
        /** The values encapsulated in the parameter or config structure are not supported. */
        MMP_H264D_ERR_UNSUPPORTED_SETTING = MMP_H264D_ERR_BASE | 0x1019,
    MMP_H264D_ERR_MEM_UNAVAILABLE,
    MMP_H264D_ERR_INIT_VIDEO_FAIL,
    MMP_H264D_ERR_FRAME_NOT_READY,

    // MMP_MJPGD(44:2Ch)
    MMP_MJPGD_ERR_BASE = MMP_MJPGD << MODULE_ERR_SHIFT, // 0x13
        /** There were insufficient resources to perform the requested operation
        E.g. The bitstream buffer is overflow. Since the video bitstream buffer is a
        plain buffer, the buffer is not able to be full loaded when one video
        frame is greater than the buffer.  For the size of the video bitstream
        buffer, refer AIT for more detail.*/
        MMP_MJPGD_ERR_INSUFFICIENT_RESOURCES = MMP_MJPGD_ERR_BASE | 0x1000,
        /** One or more parameters were not valid.
        The input parameters are supported but are not valid value. E.g. it's out of range.*/
        MMP_MJPGD_ERR_PARAMETER = MMP_MJPGD_ERR_BASE | 0x1005,
        /** The buffer was emptied before the next buffer was ready */
        MMP_MJPGD_ERR_UNDERFLOW = MMP_MJPGD_ERR_BASE | 0x1007,
        /** The buffer was not available when it was needed */
        MMP_MJPGD_ERR_OVERFLOW = MMP_MJPGD_ERR_BASE | 0x1008,
        /** The hardware failed to respond as expected */
        MMP_MJPGD_ERR_HW = MMP_MJPGD_ERR_BASE | 0x1009,
        /** The component is in the state MMP_M_STATE_INVALID */
        MMP_MJPGD_ERR_INVALID_STATE = MMP_MJPGD_ERR_BASE | 0x100A,
        /** Stream is found to be corrupt */
        MMP_MJPGD_ERR_STREAM_CORRUPT = MMP_MJPGD_ERR_BASE | 0x100B,
        /** The component is not ready to return data at this time */
        MMP_MJPGD_ERR_NOT_READY = MMP_MJPGD_ERR_BASE | 0x1010,
        /** There was a timeout that occurred */
        MMP_MJPGD_ERR_TIME_OUT = MMP_MJPGD_ERR_BASE | 0x1011,
        /** Attempting a command that is not allowed during the present state. */
        MMP_MJPGD_ERR_INCORRECT_STATE_OPERATION = MMP_MJPGD_ERR_BASE | 0x1018,
        /** The values encapsulated in the parameter or config structure are not supported. */
        MMP_MJPGD_ERR_UNSUPPORTED_SETTING = MMP_MJPGD_ERR_BASE | 0x1019,
    MMP_MJPGD_ERR_MEM_UNAVAILABLE,//MMP_MJPGD_ERR_INSUFFICIENT_RESOURCES
    MMP_MJPGD_ERR_INIT_VIDEO_FAIL,//MMP_MJPGD_ERR_INVALID_STATE
    MMP_MJPGD_ERR_FRAME_NOT_READY,//MMP_MJPGD_ERR_NOT_READY

    // MMP_USB(20:14h)
    MMP_USB_ERR_PARAMETER = (MMP_USB << MODULE_ERR_SHIFT) | 0x000001,
    MMP_USB_ERR_PCSYNC_BUSY,
    MMP_USB_ERR_MEMDEV_ACK_TIMEOUT,
    MMP_USB_ERR_MEMDEV_NACK,
    MMP_USB_ERR_UNSUPPORT_MODE,
    MMP_USB_ERR_SEMAPHORE_FAIL,
    MMP_USB_ERR_BUF_FULL,
    MMP_USB_ERR_SESSION_TIMEOUT,
    MMP_USB_ERR_EP_TX_TIMEOUT,
    MMP_USB_ERR_EP_RX_TIMEOUT,
    MMP_USB_ERR_EP_RX_STALL,
    MMP_USB_ERR_EP_TX_STALL,
    MMP_USB_ERR_EP_ERROR,
    MMP_USB_ERR_EP_NAK_TIMEOUT,
    MMP_USB_ERR_DEV_DISCONNECT,
    MMP_USB_ERR_EP_UNKNOWN,
    MMP_USB_ERR_RESOURCE,
    MMP_USB_ERR_NOT_PARSE_DONE,

    // MMP_FS(21:15h)
    MMP_FS_ERR_PARAMETER = (MMP_FS << MODULE_ERR_SHIFT) | 0x000001,
    MMP_FS_ERR_TARGET_NOT_FOUND,
    MMP_FS_ERR_OPEN_FAIL,
    MMP_FS_ERR_CLOSE_FAIL,
    MMP_FS_ERR_READ_FAIL,              //05:05h
    MMP_FS_ERR_WRITE_FAIL,
    MMP_FS_ERR_FILE_SEEK_FAIL,
    MMP_FS_ERR_FILE_POS_ERROR,
    MMP_FS_ERR_FILE_COPY_FAIL,
    MMP_FS_ERR_FILE_ATTR_FAIL,         //10:0Ah
    MMP_FS_ERR_FILE_TIME_FAIL,
    MMP_FS_ERR_FILE_NAME_FAIL,
    MMP_FS_ERR_FILE_MOVE_FAIL,
    MMP_FS_ERR_FILE_REMOVE_FAIL,
    MMP_FS_ERR_FILE_REMNAME_FAIL,      //15:0Fh
    MMP_FS_ERR_INVALID_SIZE,
    MMP_FS_ERR_FILE_TRUNCATE_FAIL,
    MMP_FS_ERR_EXCEED_MAX_OPENED_NUM,
    MMP_FS_ERR_NO_MORE_ENTRY,
    MMP_FS_ERR_CREATE_DIR_FAIL,        //20:14h
    MMP_FS_ERR_DELETE_FAIL,
    MMP_FS_ERR_FILE_INIT_FAIL,
    MMP_FS_ERR_PATH_NOT_FOUND,
    MMP_FS_ERR_RESET_STORAGE,
    MMP_FS_ERR_EOF,                    //25:19h
    MMP_FS_ERR_FILE_EXIST,
    MMP_FS_ERR_DIR_EXIST,
    MMP_FS_ERR_SEMAPHORE_FAIL,
    MMP_FS_ERR_NOT_SUPPORT,
    MMP_FS_ERR_GET_FREE_SPACE_FAIL,    //30:1Eh
    MMP_FS_ERR_IO_WRITE_FAIL,
    MMP_FS_ERR_WRITESIZE_OVERFLOW_FAIL,

    // MMP_3GPMGR(22:16h)
    MMP_3GPMGR_ERR_PARAMETER = (MMP_3GPMGR << MODULE_ERR_SHIFT) | 0x000001,
    MMP_3GPMGR_ERR_HOST_CANCEL_SAVE,
    MMP_3GPMGR_ERR_MEDIA_FILE_FULL,
    MMP_3GPMGR_ERR_AVBUF_FULL,
    MMP_3GPMGR_ERR_AVBUF_EMPTY,
    MMP_3GPMGR_ERR_AVBUF_OVERFLOW,
    MMP_3GPMGR_ERR_AVBUF_FAILURE,
    MMP_3GPMGR_ERR_FTABLE_FULL,
    MMP_3GPMGR_ERR_FTABLE_EMPTY,
    MMP_3GPMGR_ERR_FTABLE_OVERFLOW,
    MMP_3GPMGR_ERR_FTABLE_FAILURE,
    MMP_3GPMGR_ERR_TTABLE_FULL,
    MMP_3GPMGR_ERR_TTABLE_EMPTY,
    MMP_3GPMGR_ERR_TTABLE_OVERFLOW,
    MMP_3GPMGR_ERR_TTABLE_FAILURE,
    MMP_3GPMGR_ERR_ITABLE_FULL,
    MMP_3GPMGR_ERR_QUEUE_UNDERFLOW,
    MMP_3GPMGR_ERR_QUEUE_OVERFLOW,
    MMP_3GPMGR_ERR_EVENT_UNSUPPORT,
    MMP_3GPMGR_ERR_FILL_TAIL,
    MMP_3GPMGR_ERR_POST_PROCESS,
    MMP_3GPMGR_ERR_STREAM_NOMOVE,
    MMP_3GPMGR_ERR_ONLYKEEP_EMERGRECD,
    MMP_3GPMGR_ERR_INVLAID_STATE,
    MMP_3GPMGR_ERR_UNSUPPORT,
    MMP_3GPMGR_ERR_COMP_BUF_OVERFLOW,
    MMP_3GPMGR_ERR_COMP_BUF_UNDERFLOW,

    // MMP_3GPPSR(23:17h)
    MMP_VIDPSR_ERR_BASE = (MMP_3GPPSR << MODULE_ERR_SHIFT), // 0x17
        //----- The followings ( < 0x1000) are not error -----
        /** End of stream */
        MMP_VIDPSR_ERR_EOS = MMP_VIDPSR_ERR_BASE | 0x0001,
        /** The max correct number of the error code*/
        MMP_VIDPSR_ERR_MIN = MMP_VIDPSR_ERR_BASE | 0x0FFF,
        /** There were insufficient resources to perform the requested operation
        E.g. The bitstream buffer is overflow. Since the video bitstream buffer is a
        plain buffer, the buffer is not able to be full loaded when one video
        frame is greater than the buffer.  For the size of the video bitstream
        buffer, refer AIT for more detail.*/
        MMP_VIDPSR_ERR_INSUFFICIENT_RESOURCES = MMP_VIDPSR_ERR_BASE | 0x1000,
        /** There was an error, but the cause of the error could not be determined */
        MMP_VIDPSR_ERR_UNDEFINED = MMP_VIDPSR_ERR_BASE | 0x1001,
        /** One or more parameters were not valid.
        The input parameters are supported but are not valid value. E.g. it's out of range.*/
        MMP_VIDPSR_ERR_PARAMETER = MMP_VIDPSR_ERR_BASE | 0x1005,
        /** This functions has not been implemented yet.*/
        MMP_VIDPSR_ERR_NOT_IMPLEMENTED = MMP_VIDPSR_ERR_BASE | 0x1006,
        /** The buffer was emptied before the next buffer was ready */
        MMP_VIDPSR_ERR_UNDERFLOW = MMP_VIDPSR_ERR_BASE | 0x1007,
        /** The buffer was not available when it was needed */
        MMP_VIDPSR_ERR_OVERFLOW = MMP_VIDPSR_ERR_BASE | 0x1008,
        /** The component is in the state MMP_M_STATE_INVALID */
        MMP_VIDPSR_ERR_INVALID_STATE = MMP_VIDPSR_ERR_BASE | 0x100A,
        /** There was a timeout that occurred */
        MMP_VIDPSR_ERR_TIME_OUT = MMP_VIDPSR_ERR_BASE | 0x1011,
        /** Resources allocated to an executing or paused component have been
          preempted, causing the component to return to the idle state */
        MMP_VIDPSR_ERR_RESOURCES_PREEMPTED = MMP_VIDPSR_ERR_BASE | 0x1013,
        /** Attempting a state transtion that is not allowed.
        The video player encounter an invalid state transition.
        Such as try to PLAY while it is playing.*/
        MMP_VIDPSR_ERR_INCORRECT_STATE_TRANSITION = MMP_VIDPSR_ERR_BASE | 0x1017,
        /** Attempting a command that is not allowed during the present state. */
        MMP_VIDPSR_ERR_INCORRECT_STATE_OPERATION = MMP_VIDPSR_ERR_BASE | 0x1018,
        /** The values encapsulated in the parameter or config structure are not supported. */
        MMP_VIDPSR_ERR_UNSUPPORTED_SETTING = MMP_VIDPSR_ERR_BASE | 0x1019,
        /** A component reports this error when it cannot parse or determine the format of an input stream. */
        MMP_VIDPSR_ERR_FORMAT_NOT_DETECTED = MMP_VIDPSR_ERR_BASE | 0x1020,
        /** The content open operation failed. */
        MMP_VIDPSR_ERR_CONTENT_PIPE_OPEN_FAILED = MMP_VIDPSR_ERR_BASE | 0x1021,
        MMP_VIDPSR_ERR_CONTENT_CORRUPT          = MMP_VIDPSR_ERR_BASE | 0x1022,
        MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA     = MMP_VIDPSR_ERR_BASE | 0x1023,
        MMP_VIDPSE_ERR_CONTENT_CANNOTSEEK       = MMP_VIDPSR_ERR_BASE | 0x1024,

    // MMP_AUDIO(24:18h)
    MMP_AUDIO_ERR_PARAMETER = (MMP_AUDIO << MODULE_ERR_SHIFT) | 0x000001,
    MMP_AUDIO_ERR_END_OF_FILE,
    MMP_AUDIO_ERR_STREAM_UNDERFLOW,
    MMP_AUDIO_ERR_STREAM_BUF_FULL,
    MMP_AUDIO_ERR_STREAM_BUF_EMPTY,
    MMP_AUDIO_ERR_STREAM_OVERFLOW,
    MMP_AUDIO_ERR_STREAM_POINTER,
    MMP_AUDIO_ERR_COMMAND_INVALID,
    MMP_AUDIO_ERR_OPENFILE_FAIL,
    MMP_AUDIO_ERR_FILE_CLOSED,
    MMP_AUDIO_ERR_FILE_IO_FAIL,
    MMP_AUDIO_ERR_INSUFFICIENT_BUF,
    MMP_AUDIO_ERR_UNSUPPORT_FORMAT,
    MMP_AUDIO_ERR_NO_AUDIO_FOUND,
    MMP_AUDIO_ERR_INVALID_EQ,
    MMP_AUDIO_ERR_INVALID_FLOW,
    MMP_AUDIO_ERR_DATABASE_SORT,
    MMP_AUDIO_ERR_DATABASE_FLOW,
    MMP_AUDIO_ERR_DATABASE_MEMORY_FULL,
    MMP_AUDIO_ERR_DATABASE_NOT_FOUND,
    MMP_AUDIO_ERR_DATABASE_NOT_SUPPORT,
    MMP_AUDIO_ERR_NO_MIXER_DATA,
    MMP_AUDIO_ERR_BUF_ALLOCATION,
    MMP_AUDIO_ERR_DECODER_INIT,
    MMP_AUDIO_ERR_SEEK,
    MMP_AUDIO_ERR_DECODE,

    // MMP_DSC(25:19h)
    MMP_DSC_ERR_PARAMETER = (MMP_DSC << MODULE_ERR_SHIFT) | 0x000001,
    MMP_DSC_ERR_SAVE_CARD_FAIL,
    MMP_DSC_ERR_FILE_END,
    MMP_DSC_ERR_FILE_ERROR,
    MMP_DSC_ERR_DECODE_FAIL,
    MMP_DSC_ERR_JPEGINFO_FAIL,
    MMP_DSC_ERR_CAPTURE_FAIL,
    MMP_DSC_ERR_QUEUE_OPERATION,
    MMP_DSC_ERR_JPEG_BUSY,
    MMP_DSC_ERR_EXIF_ENC,
    MMP_DSC_ERR_EXIF_DEC,
    MMP_DSC_ERR_EXIF_NO_THUMBNAIL,
    MMP_DSC_ERR_EXIF_NO_LARGE_THUMBNAIL,
    MMP_DSC_ERR_EXIF_NOT_SUPPORT,
    MMP_DSC_ERR_EXIF_PARAMETER,
    
    // MMP_3GPPLAY(28:1Ch)
    MMP_3GPPLAY_ERR_BASE = (MMP_3GPPLAY << MODULE_ERR_SHIFT), // 0x1C
        /** There were insufficient resources to perform the requested operation 
        E.g. The bitstream buffer is overflow. Since the video bitstream buffer is a
        plain buffer, the buffer is not able to be full loaded when one video 
        frame is greater than the buffer.  For the size of the video bitstream 
        buffer, refer AIT for more detail.*/
        MMP_3GPPLAY_ERR_INSUFFICIENT_RESOURCES = MMP_3GPPLAY_ERR_BASE | 0x1000,
        /** There was an error, but the cause of the error could not be determined */
        MMP_3GPPLAY_ERR_UNDEFINED = MMP_3GPPLAY_ERR_BASE | 0x1001,
        /** One or more parameters were not valid.
        The input parameters are supported but are not valid value. E.g. it's out of range.*/
        MMP_3GPPLAY_ERR_PARAMETER = MMP_3GPPLAY_ERR_BASE | 0x1005,
        /** This functions has not been implemented yet.*/
        MMP_3GPPLAY_ERR_NOT_IMPLEMENTED = MMP_3GPPLAY_ERR_BASE | 0x1006, 
        /** The buffer was emptied before the next buffer was ready */
        MMP_3GPPLAY_ERR_UNDERFLOW = MMP_3GPPLAY_ERR_BASE | 0x1007,
        /** The buffer was not available when it was needed */
        MMP_3GPPLAY_ERR_OVERFLOW = MMP_3GPPLAY_ERR_BASE | 0x1008,
        /** The hardware failed to respond as expected */
        MMP_3GPPLAY_ERR_HW = MMP_3GPPLAY_ERR_BASE | 0x1009,
        /** The component is in the state MMP_M_STATE_INVALID */
        MMP_3GPPLAY_ERR_INVALID_STATE = MMP_3GPPLAY_ERR_BASE | 0x100A,
        /** The component is not ready to return data at this time */
        MMP_3GPPLAY_ERR_NOT_READY = MMP_3GPPLAY_ERR_BASE | 0x1010,
        /** There was a timeout that occurred */
        MMP_3GPPLAY_ERR_TIME_OUT = MMP_3GPPLAY_ERR_BASE | 0x1011,
        /** Attempting a state transition that is not allowed.
        The video player encounter an invalid state transition.
        Such as try to PLAY while it is playing.*/
        MMP_3GPPLAY_ERR_INCORRECT_STATE_TRANSITION = MMP_3GPPLAY_ERR_BASE | 0x1017,
        /** Attempting a command that is not allowed during the present state. */
        MMP_3GPPLAY_ERR_INCORRECT_STATE_OPERATION = MMP_3GPPLAY_ERR_BASE | 0x1018,
        /** The values encapsulated in the parameter or config structure are not supported. */
        MMP_3GPPLAY_ERR_UNSUPPORTED_SETTING = MMP_3GPPLAY_ERR_BASE | 0x1019,
        /** The heap memory is exhausted */
        MMP_3GPPLAY_ERR_MEM_EXHAUSTED = MMP_3GPPLAY_ERR_BASE | 0x101A,

    // MMP_3GPRECD(29:1Dh)
    MMP_3GPRECD_ERR_PARAMETER = (MMP_3GPRECD << MODULE_ERR_SHIFT) | 0x000001,
    MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS,     ///< The input parameters are not supported.
    MMP_3GPRECD_ERR_INVALID_PARAMETERS,         ///< The input parameters are supported but are not valid value. E.g. it's out of range.
    MMP_3GPRECD_ERR_GENERAL_ERROR,              ///< General Error without specific define.
    MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE,           ///< Not enough space for minimum recording.
    MMP_3GPRECD_ERR_OPEN_FILE_FAILURE,          ///< Open file failed.
    MMP_3GPRECD_ERR_BUFFER_OVERFLOW,            ///< Buffer overflow
    MMP_3GPRECD_ERR_MEM_EXHAUSTED,              ///< Memory exhausted
    MMP_3GPRECD_ERR_STILL_CAPTURE,
    MMP_3GPRECD_ERR_STOPRECD_SLOWCARD,          //// Stop record for slow card

    // MMP_UART(30:1Eh)
    MMP_UART_ERR_PARAMETER = (MMP_UART << MODULE_ERR_SHIFT) | 0x000001,
    MMP_UART_SYSTEM_ERR,

    // MMP_SPI(32:20h)
    MMP_SPI_ERR_PARAMETER = (MMP_SPI << MODULE_ERR_SHIFT) | 0x000001,
    MMP_SPI_ERR_INIT,
    MMP_SPI_ERR_CMDTIMEOUT,
    MMP_SPI_ERR_TX_UNDERFLOW,
    MMP_SPI_ERR_RX_OVERFLOW,

    // MMP_PLL(33:21h)
    MMP_PLL_ERR_PARAMETER = (MMP_PLL << MODULE_ERR_SHIFT) | 0x000001,

    // MMP_USER(34:22h)
    MMP_USER_ERR_PARAMETER = (MMP_USER << MODULE_ERR_SHIFT) | 0x000001,
    MMP_USER_ERR_UNSUPPORTED,
    MMP_USER_ERR_INSUFFICIENT_BUF,
    MMP_USER_ERR_INIT,
    MMP_USER_ERR_UNINIT,

    // MMP_CCIR(36:24h)
    MMP_CCIR_ERR_PARAMETER = (MMP_CCIR << MODULE_ERR_SHIFT) | 0x000001,
    MMP_CCIR_ERR_UNSUPPORTED_PARAMETERS,
    MMP_CCIR_ERR_NOT_INIT,

    // MMP_STORAGE(37:25h)
    MMP_STORAGE_ERR_PARAMETER = (MMP_STORAGE << MODULE_ERR_SHIFT) | 0x000001,
    MMP_STORAGE_ERR_NOT_FOUND,
    MMP_STORAGE_ERR_PARTITION_INFO,
    MMP_STORAGE_ERR_IO_ACCESS,
    
    // MMP_PIO(38:26h)
    MMP_PIO_ERR_PARAMETER = (MMP_PIO << MODULE_ERR_SHIFT) | 0x000001,
    MMP_PIO_ERR_INPUTMODESETDATA,
    MMP_PIO_ERR_OUTPUTMODEGETDATA,

    // MMP_PWM(40:28h)
    MMP_PWM_ERR_PARAMETER = (MMP_PWM << MODULE_ERR_SHIFT) | 0x000001,
    
    // MMP_RAWPROC(41:29h)
    MMP_RAWPROC_ERR_PARAMETER = (MMP_RAWPROC << MODULE_ERR_SHIFT) | 0x000001,
    MMP_RAWPROC_ERR_UNSUPPORTED_PARAMETERS,
    MMP_RAWPROC_ERR_PROCESS,
    
    // MMP_SIF(42:2Ah)
    MMP_SIF_ERR_PARAMETER = (MMP_SIF << MODULE_ERR_SHIFT) | 0x000001,
    MMP_SIF_ERR_DMA_ADDRESS,
    MMP_SIF_ERR_TIMEOUT,
    MMP_SIF_ERR_UNSUPPORT_DEV,
    MMP_SIF_ERR_BUSY,
    MMP_SIF_ERR_CHIP_ERASE,
    MMP_SIF_ERR_BLK_ERASE,
    MMP_SIF_ERR_SEC_ERASE,
    MMP_SIF_ERR_PROG,
    
    // MMP_EVENT(43:2Bh)
    MMP_EVENT_ERR_PARAMETER = (MMP_EVENT << MODULE_ERR_SHIFT) | 0x000001,
    MMP_EVENT_ERR_MSGQ_FULL,
    MMP_EVENT_ERR_POST,

    // MMP_LDC(46:2Eh)
    MMP_LDC_ERR_PARAMETER = (MMP_LDC << MODULE_ERR_SHIFT) | 0x000001,
    MMP_LDC_ERR_QUEUE_OPERATION,
    MMP_LDC_ERR_OS_OPERATION,
    MMP_LDC_ERR_SD_UPDATE_LUT_FAIL,

    // MMP_RTC(47:2Fh)
    MMP_RTC_ERR_ISR = (MMP_RTC << MODULE_ERR_SHIFT) | 0x000001,
    MMP_RTC_ERR_FMT,
    MMP_RTC_ERR_HW,
    MMP_RTC_ERR_SEM,
    MMP_RTC_ERR_PARAM,
    MMP_RTC_ERR_INVALID,

    // MMP_MCORE(48:30h)
    MMP_CORES_ERR_BASE = (MMP_CORES << MODULE_ERR_SHIFT),
    MMP_CORES_ERR_INVALID_CMD = (MMP_CORES << MODULE_ERR_SHIFT) | 0x000100,
    MMP_CORES_ERR_FAIL,
    
    // MMP_WIFI(49:31h)
    MMP_WIFI_ERR_PARAMETER = (MMP_WIFI << MODULE_ERR_SHIFT) | 0x000001,
    MMP_WIFI_ERR_UNSUPPORTED_PARAMETERS,
    MMP_WIFI_ERR_INVALID_PARAMETERS,
    MMP_WIFI_ERR_MEM_EXHAUSTED,
    MMP_WIFI_ERR_UNDER_DEVELOP,
    MMP_WIFI_ERR_INVALID_STATE,
    MMP_WIFI_ERR_INCORRECT_STATE_OPERATION,
    MMP_WIFI_ERR_NOT_READY,
    
    // MMP_UVC(50:32h)
    MMP_UVC_ERR_PARAMETER = (MMP_UVC << MODULE_ERR_SHIFT) | 0x000001,
    MMP_UVC_ERR_UNSUPPORTED_PARAMETERS,
    MMP_UVC_ERR_INVALID_PARAMETERS,
    MMP_UVC_ERR_MEM_EXHAUSTED,
    MMP_UVC_ERR_UNDER_DEVELOP,
    MMP_UVC_ERR_INVALID_STATE,
    MMP_UVC_ERR_INCORRECT_STATE_OPERATION,
    MMP_UVC_ERR_FRAME_OVERFLOW,
    MMP_UVC_ERR_NOT_READY,
    
    // MMP_COMPONENT(51:33h)
    MMP_COMPONENT_ERR_PARAMETER = (MMP_COMPONENT << MODULE_ERR_SHIFT) | 0x000001,
    MMP_COMPONENT_ERR_USAGE_ID,
    MMP_COMPONENT_ERR_INVALID_STATUS,
    MMP_COMPONENT_ERR_OUTOFNUM,
    MMP_COMPONENT_ERR_CALL,
    MMP_COMPONENT_ADV_RDIDX,
    MMP_COMPONENT_ADV_WRIDX,
    MMP_COMPONENT_ERR_INIT,
    MMP_COMPONENT_ERR_OPEN,
    MMP_COMPONENT_ERR_BUFFER_USED,
    MMP_COMPONENT_NO_NEED_ORDER,

    // MMP_PERIPHERAL(52:34h)
    MMP_PERIPHERAL_ERR_OPEN = (MMP_PERIPHERAL << MODULE_ERR_SHIFT) | 0x000001,
    MMP_PERIPHERAL_ERR_CLOSE,
    MMP_PERIPHERAL_ERR_INIT,
    MMP_PERIPHERAL_ERR_ACCESS,
    MMP_PERIPHERAL_ERR_PARAM,
} MMP_ERR;

#endif // _MMP_ERR_H_
