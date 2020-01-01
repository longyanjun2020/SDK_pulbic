////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


/**
* @file    mdl_vt_rec_mux_internal.h
* @version
* @brief   3g324mTask
*
*/

#ifdef __VT_3G324M__
#ifndef _MDL_VTMUX_INTERNAL_H_
#define _MDL_VTMUX_INTERNAL_H_

//Create dynamic task for VT recording data mux
#define ENABLE_MDLVTREC_DYNAMIC_VIDEO_THREAD 1

//VT record start from first I frame arrived if enable this definition
//#define VT_REC_START_FROM_1ST_KEYFRAME

/*  definitions */
#if ENABLE_MDLVTREC_DYNAMIC_VIDEO_THREAD
extern MsTaskId_e               g_nMdlVtRec_MuxTaskId;
#define MDL_VTMUX_MBX_ID        g_nMdlVtRec_MuxTaskId
//#define MDL_VTMUX_MBX_ID                       VM_MBX_CUS67
#else
#define MDL_VTMUX_MBX_ID                       VM_MBX_CUS67
#endif
#define MDL_VTMUX_MSG_BASE                  (u16)(VM_CUS67_BASE + 0x0000) // Message Base ID
#define MDL_VTMUX_TIMER_BASE               (MDL_VTMUX_ERROR_MASK_TIMER)

#define mdl_vtmux_printf vm_dbgTrace
#define mdl_vtmux_err_printf vm_dbgError

#define VT_DBG_UART 0
#if VT_DBG_UART
    //#define VT_MSG(fmt, ...) UartSendTrace("[VT] "fmt, ##__VA_ARGS__)
    #define VTMUX_MSG(fmt, ...) DrvUartDebugTrace("[VT] "fmt, ##__VA_ARGS__)
#else
    #define VTMUX_MSG(fmt, ...) mdl_vtmux_printf( (_CUS1|LEVEL_30) , "[VTMUX] "fmt, ##__VA_ARGS__)
    #define VTMUX_DBGMSG(fmt, ...) mdl_vtmux_printf( (_CUS1|LEVEL_29) , "[VTMUXDBG] "fmt, ##__VA_ARGS__)
    #define VTMUX_ERRMSG(fmt, ...) mdl_vtmux_err_printf( (_CUS1|LEVEL_30) , "[VTMUX_ERROR] "fmt, ##__VA_ARGS__)
    #define VTMUX_DBGMSG2(fmt, ...) mdl_vtmux_printf( (_CUS1|LEVEL_31) , "[VTMUXDBG2] "fmt, ##__VA_ARGS__)
#endif

typedef enum
{
    /* Common */
    VTMUX_ERROR_SUCCESS = 0,
    VTMUX_ERROR_FAIL,
    VTMUX_ERROR_PARAMETER_INVALID,
    VTMUX_ERROR_STATE_CHANGE,
    VTMUX_ERROR_ACCEPT,
    VTMUX_ERROR_IGNORE,
    VTMUX_ERROR_REJECT,

    /* */
    VTMUX_ERROR_NUM
} MdlVTMuxResult_e;


//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------

#define VIDEO_TRACK 1
#define AUDIO_TRACK 2

#define MP4_PACKET_START                 0x01
#define MP4_PACKET_MORE                 0x02
#define MP4_PACKET_END                  0x03
#define MP4_PACKET_ERR                  0x04

// max size of one video frame in VT feature, to store some incoming video frame(H.263) without picture start code
#define VTMUX_MAXVIDEOBUFFERSIZE    8192

#define VTMUX_STATE_MSG(fmt, ...) mdl_vt_printf(2, "[VTMUX_STATE] "fmt, ##__VA_ARGS__)
#define VTMUX_STATE_MSG_FUNCTION_IN VTMUX_STATE_MSG("%s() In\n", __FUNCTION__);
#define VTMUX_STATE_MSG_FUNCTION_OUT VTMUX_STATE_MSG("%s() Out\n", __FUNCTION__);
//vt_trace(DBG_VT_324M, "[VTMUX_STATE] %s() In \n", __FUNCTION__);

typedef struct
{
    u8 *buf;
    u16 pos;
    u16 preduration;
    u16 curduration;
    u16 prebuffersize;
    u16 get_firstframe;
    u16 flush_firstframe;
    u16 max_size;

    void *userdata;
} MdlVtMux_VideoBuffer_t;

typedef struct
{
    u32 videosize;
    u32 vincoming_framecnt;
    u32 vtotalduration;
    u32 vavg_bitrate;

    u32 audiosize;
    u32 aincoming_framecnt;
    u32 atotalduration;
    u32 aavg_bitrate;

    u32 totalsize;

    void *userdata;
} MdlVtRec_Info_t;


typedef enum
{
    MDL_VTMUX_CMD_INIT                     = MDL_VTMUX_MSG_BASE,   //0xD400
    MDL_VTMUX_CMD_RECORD,
    MDL_VTMUX_CMD_STOP,
    MDL_VTMUX_CMD_PAUSE,
    MDL_VTMUX_CMD_RESUME,
    MDL_VTMUX_CMD_SAVE,
    MDL_VTMUX_CMD_DISCARD,
    MDL_VTMUX_CMD_ABORT,
    MDL_VTMUX_CMD_DEINIT,

    MDL_VTMUX_RESPONSE_WRITE               = (MDL_VTMUX_MSG_BASE + 0x0030),   // General purpose write task response
    MDL_VTMUX_RESPONSE_WRITE_STOPPED,                                      // Write Task Stopped Successfully
    MDL_VTMUX_RESPONSE_WRITE_PAUSED,                                       // Write Task Paused Successfully
    MDL_VTMUX_RESPONSE_WRITE_RESUMED,                                      // Write Task Resumed Successfully
    MDL_VTMUX_RESPONSE_WRITE_START_SAVE,                                   // Write Task Starts Saving
    MDL_VTMUX_RESPONSE_WRITE_SAVE_DONE,                                    // Write Task Saves File Done
    MDL_VTMUX_RESPONSE_WRITE_START_DISCARD,                                // Write Task Starts Discard
    MDL_VTMUX_RESPONSE_WRITE_DISCARD_DONE,                                 // Write Task Discards Files Done
    MDL_VTMUX_RESPONSE_WRITE_ABORT_SAVING,                                 // Write Task Abort Saving

    MDL_VTMUX_INTERNAL_WRITE               = (MDL_VTMUX_MSG_BASE + 0x0060),   // Internal Command to Write Task
    MDL_VTMUX_INTERNAL_WRITE_SAVE_DONE,                                    // Write Task Saves File Done
    MDL_VTMUX_INTERNAL_WRITE_DISCARD_START,                                // Write Task Discards Files
    MDL_VTMUX_INTERNAL_WRITE_DATA,			                                // Write Task Write Buffer

    MDL_VTMUX_MBOX_NONE                    = (MDL_VTMUX_MSG_BASE + 0x007F),   // NOTE: this should not be error

    MDL_VTMUX_ERROR_MASK                   = (MDL_VTMUX_MSG_BASE + 0x0080),   // Error Mask
    MDL_VTMUX_ERROR_MAIN,
    MDL_VTMUX_ERROR_VIDEO,
    MDL_VTMUX_ERROR_AUDIO,
    MDL_VTMUX_ERROR_WRITE,
    MDL_VTMUX_ERROR_DISK_FULL,                                             // disk full
    MDL_VTMUX_ERROR_MASK_TIMER             = (MDL_VTMUX_MSG_BASE + 0x0090),   // Error Mask for Timer
    MDL_VTMUX_BYPASS_CMD                         = (MDL_VTMUX_MSG_BASE + 0x00A0),   // Error Mask for Timer    
} MdlVTMuxCmd_e;

typedef enum VTMuxWriteTaskState
{
    VTMUX_WRITE_TASK_STANDBY,
    VTMUX_WRITE_TASK_INIT,
    VTMUX_WRITE_TASK_START,
    VTMUX_WRITE_TASK_STOP,      //0x3
    VTMUX_WRITE_TASK_PAUSE,
    VTMUX_WRITE_TASK_SAVE,
    VTMUX_WRITE_TASK_DISCARD,
    VTMUX_WRITE_TASK_ERROR,     //0x7

    VTMUX_WRITE_TASK_ARBITRARY,
    VTMUX_WRITE_TASK_NUMBER,    //0x9
} VTMuxWriteTaskState_e;

u16 MdlVt_SendMsg2VtMux( MdlVTMuxCmd_e vVtMuxCmd, void *Userdata );
u16 _MdlSendMsgToVtMux(u32 MsgType, void *Msg, u32 MsgSize, u32 UserData);

void _MdlVTMuxPrint2String(char *str1, char *str2);

S32 MdlVtRecMux_Delete(void *data);
S32 MdlVtRecMux_Create(void *data);

typedef u16 (* VT_VTMUX_WRITE_PACKET_CALLBACK) (u8 *, u16 , s32);

typedef enum
{
     VT_VTMUX_WRITE_PACKET_NO_CALLBACK=0,
     VT_VTMUX_WRITE_PACKET_WITH_CALLBACK,
}VT_VTMUX_WRITE_PACKET_CALLBACK_STATUS_e;

void Vt_VtMux_Write_Packet_CallbackAttach(VT_VTMUX_WRITE_PACKET_CALLBACK nCallbackAdr);
void Vt_VtMux_Write_Packet_CallbackDisable(void);
u16 Vt_VtMux_Write_Packet_CallbackAttached(void);

#endif //_MDL_VTMUX_INTERNAL_H_
#endif //__VT_3G324M__

