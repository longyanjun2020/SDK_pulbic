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

#ifndef MDW_AUD_HANDLE_H
#define MDW_AUD_HANDLE_H

#define __B3_AUDIO_DRV_API__
//#define __DBG_UART__
//#define __MDL_AUD_REC_DYN_TASK__

#include "vm_stdio.ho"
#include "vm_osdef.hc"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_MsWrapper_cus_os_mem.h"

#include "srv_ResMgr_MmlManager.h"
#include "srv_resmgr_mml_api.h"
#include "srv_resmgr_mmlaudio_types.h"
#include "srv_resmgr_mmlradio_types.h"
#include "srv_resmgr_mmlutility_api.h"
#include "srv_resmgr_mmlconcurrent_api.h"

#include "mdl_mmaudio_marrecorder.h"
#include "mdl_mmaudio_msmerror.h"
#include "mdl_aud_pub_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/

void MMMAPInit(void);
void MMReadProcInit(void);
void MMMAPParseMsg(void *pMessage);
void MMReadProcParseMsg(void *pMessage);
void MDLAudPlayCtlnit(void);
void MDLAudPlayCtlProc(void *pMessage);
void MMAudGetInfoInit(void);
void MMAudGetInfoProc(void *pMessage);
void MMWriteProcParseMsg(vm_msg_t *pMessage);
void MMWriteProcInit(void *);
void MMMARParseMsg(vm_msg_t *pMessage);
void MMMARInit(void *);
void PlayDTMFToneHandler(const void *pMessage); /*play DTMF tone*/
void MdlPlayDTMFToneRepCallback(MmlUseCaseAudioId_e eAudUcid, MmlAudioState_e eAudState, MmlAudioResult_e eAudResult);


//void MdlAudRepCallBack(void *pMessage, MmlAudioState_e eAudState, u32 nHandle, MmlAudioResult_e eErrCode);
void MDLAudRecordCtlProc(void *pMsg);
void MdlErrorHandle(void *pMsg);
void MdlNotifyStateChange(MmlAudioState_e eChangeState, MmlAudioEvent_e eCause);
void MdlAudRepCallback(MmlUseCaseAudioId_e eAudUcid, MmlAudioState_e eAudRecState, MmlAudioResult_e eAudResult);
void MdlErrorHandleStopWriteProc(void);
void MdlErrorHandleSaving(void *pMsg);

#define MDLAUD_READDATA_MBX VM_MBX_CUS21
#define MDLAUD_MAP_MBX VM_MBX_CUS22
#define MDLAUD_PLAYCTL_MBX VM_MBX_CUS23
#define MDLAUD_GETINFO_MBX VM_MBX_CUS45
#define MDLAUD_MIDCONV_MBX VM_MBX_CUS46 //use getinfo for test emporarily
#define MDLAUD_PLAYTONE_MBX VM_MBX_CUS65   /*play DTMF tone*/
#define MDLAUD_AEC_MBX VM_MBX_CUS66  /*AEC play*/
#define MDLAUD_AEC_PROC_MBX VM_MBX_CUS68 /*AEC NS process*/


#ifdef __MDL_AUD_REC_DYN_TASK__
extern MsTaskId_e nMdlAudRecMarTaskId;
extern MsTaskId_e nMdlAudRecWriteTaskId;
#define MDLAUD_MAR_MBX nMdlAudRecMarTaskId
#define MDLAUD_WRITEDATA_MBX nMdlAudRecWriteTaskId
#else
#define MDLAUD_MAR_MBX VM_MBX_CUS24
#define MDLAUD_WRITEDATA_MBX VM_MBX_CUS25
#endif


// we reserver the first 10 for general purpose usage, internal message start from the 11-th
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum
{
#include "mdw_aud_message_define__.hi"
} MdlAudioCtlMsgId_e;

typedef void (*MdlAudioRecEvtHandle_t)(void *pMsg);

void _MdlAudioRecEvtStop(void *pMessage);
void _MdlAudioRecEvtRecord(void *pMessage);
void _MdlAudioRecEvtPause(void *pMessage);
void _MdlAudioRecEvtSaving(void *pMessage);
void _MdlAudioRecEvtStopTrans(void *pMessage);
void _MdlAudioRecEvtRecordTrans(void *pMessage);
void _MdlAudioRecEvtPauseTrans(void *pMessage);
void _MdlAudioRecEvtSavingTrans(void *pMessage);
void _MdlAudioRecEvtErrorTrans(void *pMessage);

#ifdef __MDL_AUD_WB_TEST__
typedef enum
{
    MDL_WB_AUD_RET_OK = 0,
    MDL_WB_AUD_RET_FAIL,
    MDL_WB_AUD_RET_SKIP,
    MDL_WB_AUD_RET_PARAM_ERROR,
    MDL_WB_AUD_RET_MEM_ALLOC_ERROR,
    MDL_WB_AUD_RET_REJECT,
    MDL_WB_AUD_RET_ABORT,
    MDL_WB_AUD_RET_PATH_ERROR,
    MDL_WB_AUD_RET_TIMEOUT,
    MDL_WB_AUD_RET_WRONG_STATE,
    MDL_WB_AUD_RET_NO_SUPPORT,
    MDL_WB_AUD_SIZE_MISMATCH,
    MDL_WB_FILE_OPEN_ERROR,
    MDL_WB_FILE_WRITE_ERROR,
    MDL_WB_FILE_CLOSE_ERROR,
    MDL_WB_RING_ERROR,
    MDL_WB_MEM_ALLOC_ERROR
} MdlAudWBRet_e;

typedef struct
{
    MdlAudWBRet_e eAudErrorType;
    MdlAudWBRet_e eFileErrorType;
    u32 pData;
    u32 nSize;
    u32 nActualSize;
} AudWbSimTaks_t;
#endif

typedef enum
{
#if 0
    /* AUD  (0x2000 ~ 0x2FFF) */
    MSMERR_AUD_NONE = 0x2000,
    MSMERR_AUD_RINGDATA_RANGE_ERR = 0x2001,
    MSMERR_AUD_PLAYREC_MODE_NOT_EXIST = 0x2002,
    MSMERR_AUD_RINGDATA_NOT_EXIST = 0x2003,
    MSMERR_AUD_TX_RESET = 0x2004,
    MSMERR_AUD_TX_UNDERFLOW = 0x2005,
    MSMERR_AUD_TX_FULL = 0x2006,
    MSMERR_AUD_TX_ADDED_SAMPLES_OVER = 0x2007,
    MSMERR_AUD_RX_RESET = 0x2008,
    MSMERR_AUD_RX_OVERFLOW = 0x2009,
    MSMERR_AUD_RX_OVERFLOW_CHGSAMPLE_OK = 0x200a,
    MSMERR_AUD_RX_EMPTY = 0x200b,
    MSMERR_AUD_RX_REMOVED_SAMPLES_OVER = 0x200c,
    MSMERR_AUD_DATA_NOT_EXIST = 0x200d,
    MSMERR_AUD_UNKNOW = 0x200e,

    /* SBC  */
    MSMERR_SBCSTREAM_DONE = 0x2100,
    MSMERR_SBCSTREAM_FULL = 0x2101,
    MSMERR_SBCSTREAM_EMPTY = 0x2102,


    /* Ring Buffer  */
    MSMERR_RINGBUF_DONE = 0x2200,
    MSMERR_RINGBUF_FULL = 0x2201,
    MSMERR_RINGBUF_EMPTY = 0x2202,


    //MSMERR_WAV_HEADERPARSER_ERR = 0x2103,
    //MSMERR_WAV_FORMAT_UNSUPPORT = 0x2104,
    MSMERR_AUD_SCMD_REJECT = 0x2105,

    /* REC  (notification return: 0x5100 ~ 0x51FF) */
    MSMERR_REC_START = 0x5100,
    MSMERR_REC_STOP_NORMAL = 0x5101,
    MSMERR_REC_STOP_REACH_TIME_LIMIT = 0x5102,
    MSMERR_REC_STOP_REACH_SIZE_LIMIT = 0x5103,
    MSMERR_REC_STOP_SPACE_FULL = 0x5104,
    MSMERR_REC_SAVE_FILE_COMPLETE = 0x5105,
    MSMERR_REC_PLAY_SHUTTER_SOUND = 0x5106,
    MSMERR_REC_SINGLE_CAPTURE = 0x5107,
    MSMERR_REC_SINGLE_CPATURE = 0x5107,
    MSMERR_REC_STOP_WRITE_ERROR = 0x5108,
    MSMERR_REC_STOP_ABORTED = 0x5109,
    MSMERR_REC_SRC_INIT_FAIL = 0x510a,
    MSMERR_REC_SRC_PROC_FAIL = 0x510b,
    /* MP   (0x9000 ~ 0x9FFF) */
    /* MP thread common part (0x9000~0x90FF) */
    MSMERR_FORMAT_NOT_SUPPORT2 = 0x9000,
    MSMERR_PLAY_SEEK_ERROR = 0x9001,
    MSMERR_PLAY_SEEK_OVER_FILE_SIZE = 0x9002,
    MSMERR_PLAY_B2_MALLOC_FAIL = 0x9003,

    /* MP Notification part (0x9100~0x91FF) */
    MSMERR_PLAY_START = 0x9100,
    MSMERR_PLAY_STOP = 0x9101,
    MSMERR_PLAY_SEEK_COMPLETE = 0x9102,
    MSMERR_PLAY_PAUSE = 0x9103,
    MSMERR_PLAY_RESUME = 0x9104,
    MSMERR_PLAY_END = 0x9105,
    MSMERR_PLAY_WATERMARK = 0x9106,
    MSMERR_PLAY_STREAMS_END = 0x9107,
    MSMERR_PLAY_SPEED_CHANGED = 0x9108,
    MSMERR_PLAY_AMPON_UPDATE = 0x9109,
    MSMERR_PLAY_AMP_ON_REQUEST = 0x910a,

    /* MP Mp3 related part (0x9600~0x97FF) */
    MSMERR_ID3_NODATA = 0x9600,
    MSMERR_MP3_DECODE_ERR = 0x9601,
    MSMERR_MP3_CLOSE_ERR = 0x9602,
    MSMERR_LYRICS_NODATA = 0x9603,
    MSMERR_LYRICS_LYRICFILE_ERR = 0x9604,
    MSMERR_AUD_HW_ERR = 0x9605,
    MSMERR_ID3TAG_WR_ERR = 0x9606,
    /* MP AMR/ACC related part (0x9800~0x99FF) */
    MSMERR_AMR_DEC_INIT_FAIL = 0x9800,
    MSMERR_AMR_DEC_OPEN_FAIL = 0x9801,
    MSMERR_FILE_READ_ERR = 0x9802,
    MSMERR_AACDecode_ERR = 0x9803,
    MSMERR_AAC_OpenFileErr = 0x9804,
    MSMERR_Aud_TxDrvInitErr = 0x9805,
    MSMERR_AES_DEC_KEY_ERR = 0x9806,
    MSMERR_Decode_ERR = 0x9807,
    MSMERR_Decode_EMPTY = 0x9808,

    /* MP MIDI/WAV related part (0x9A00~0x9BFF) */
    MSMERR_MIDI_DEC_ERR = 0x9A00,
    MSMERR_MIDI_OPENFILE_FAILED = 0x9A01,
    MSMERR_MIDI_FILESIZE_TOO_BIG = 0x9A02,
    MSMERR_MIDI_FORMAT_ERR = 0x9A03,
    MSMERR_MIDI_WAIT_STREAM_FAIL = 0x9A04,
    MSMERR_MIDI_TABLE_ERR = 0x9A05,
    MSMERR_MIDI_GETSTREAMSIZE_ERR = 0x9A06,
    MSMERR_MIDI_EQ_ERR = 0x9A07,
    MSMERR_WAV_HEADERPARSER_ERR = 0x9B00,
    MSMERR_WAV_FORMAT_UNSUPPORT = 0x9B01,
    MSMERR_WAV_PEQ_ERR = 0x9B02,

    //MP Post-Processing related part (0x9C00~0x9CFF)
    MSMERR_POSTPROC_USR_PEQ_ERR      = 0x9C00,
    MSMERR_POSTPROC_SPK_PEQ_ERR      = 0x9C01,
    MSMERR_POSTPROC_LIMITER_ERR      = 0x9C02,
    MSMERR_POSTPROC_SURROUND_ERR     = 0x9C03,
    MSMERR_POSTPROC_DPGA_ERR         = 0x9C04,
    MSMERR_POSTPROC_ADJUSTCLOCK_ERR  = 0x9C05,
    MSMERR_POSTPROC_TMPMEM_ERR       = 0x9C06,
    MSMERR_POSTPROC_CMDMEM_ERR       = 0x9C07,
    MSMERR_POSTPROC_DPGAVOL_ERR      = 0x9C08,
    MSMERR_POSTPROC_EXPVOL_ERR       = 0x9C09,


    // SRC Main IP Part(0x9C80~0x9CFF)
    MSMERR_SRC_INIT_ERR                 = 0x9C80,
    MSMERR_SRC_PROC_ERR                 = 0x9C81,
    MSMERR_SRC_CLOSE_ERR                = 0x9C82,
    // SRC Memory Layout Part
    MSMERR_SRC_OVEROUTPUTBUFSIZE_ERR    = 0x9C83,
    MSMERR_SRC_OUTBUFFERSIZEINVALID_ERR = 0x9C84,
    // SRC Control Part
    MSMERR_SRC_GETOUTSAMPLERATE_ERR     = 0x9C85,
    MSMERR_SRC_GETOUTSAMPLESIZE_ERR     = 0x9C86,
    MSMERR_SRC_SETPOWER_ERR             = 0x9C87,
    MSMERR_SRC_SETSAMPLERATE_ERR        = 0x9C88,
    MSMERR_SRC_SETRULE_ERR              = 0x9C89,

    /* MP FM/RDS related part (0x9D00~0x9DFF) */
    MSMERR_FMRX_INVLD_INPUTFREQ  = 0x9D00,
    MSMERR_FMRX_INVLD_OUTPUTFREQ = 0x9D01,
    MSMERR_FMRX_RFLO_UNLOCK      = 0x9D02,
    MSMERR_FMRX_BBCARRY_UNLOCK   = 0x9D03,
#endif

    MSMERR_AUD_MEMALLOC_FAIL = 0x2010,
    MSMERR_AUD_GETINFO_MEMERR = 0x2011,
    MSMERR_AUD_GETINFO_INPUTPATHERR = 0x2012,
    MSMERR_AUD_GETINFO_OK = 0x2013,
} MdlAudErr_e;

/** @ingroup    AudioAEC
    @brief      AEC setting
*/
typedef struct
{
    u8 nBufferID;
    u32 nDataDLAddr;
    u32 nDataUpAddr;
    u32 nOutAddr;
    u32 nOutSize;
} MmlAECSetting_t ;

typedef struct
{
    MdlAudioCtlMsgId_e eMsgId;
    union
    {
        u32                  nStatus;                       // use to update status
        MmlAudioNotify_t     tNotify;                       // use to pass notify callback structure to state control thread
        MmlAudioRecordingSetting_t    tRecordingSetting;    // the audio recorder settings
        MmlAECSetting_t      tAECSetting;                   // the audio aec settings
        MdlAudPath_e         eAudPath;                      // the audio aec path
    } uParam;
} MdlAudInterCtlMsg_t;

typedef union
{
    u32                   nUseCaseID;
    MmlAudioUCParam_t     tAudioUCParam;
    MmlRingMessage_t      tRingMessage;
    MdlAudInterCtlMsg_t   tAudioInterCtlMsg;
    vm_osTimerMsgBody_t   tTimerMsg;
} vm_msgBody_t;

#include "vm_msgt.ht"

#define MDL_GET_UCID(pMsg)                 ((u32)(pMsg->Body.nUseCaseID))
#define MDL_GET_AUDIO_UCID(pMsg)           (MML_GET_AUDIO_UCID(&pMsg->Body.tAudioUCParam))
#define MDL_GET_AUDIO_CTL_MSGID(pMsg)      ((MdlAudioCtlMsgId_e)(pMsg->Body.tAudioInterCtlMsg.eMsgId))

//#define __MDW_AUD_WB_TEST__
#define MDW_AUDREC_ERR_AUD_OPEN_FAIL                (0x1<<0)
#define MDW_AUDREC_ERR_AUD_REGCALLBACK_FAIL         (0x1<<1)
#define MDW_AUDREC_ERR_AUD_GETINFO_FAIL             (0x1<<2)
#define MDW_AUDREC_ERR_AUD_GETDATA_FAIL             (0x1<<3)
#define MDW_AUDREC_ERR_AUD_CLOSE_FAIL               (0x1<<4)
#define MDW_AUDREC_ERR_AUD_SETADDR_FAIL             (0x1<<5)
#define MDW_AUDREC_ERR_AUD_SETTHRES_FAIL            (0x1<<6)
#define MDW_AUDREC_ERR_AUD_CTLINTR_FAIL             (0x1<<7)
#define MDW_AUDREC_ERR_AUD_CTLINTR_DISABLE_FAIL     (0x1<<8)
#define MDW_AUDREC_ERR_AUD_START_FAIL               (0x1<<9)
#define MDW_AUDREC_ERR_AUD_STOP_FAIL                (0x1<<10)

#define MDW_AUDREC_ERR_CODEC_OPEN_FAIL              (0x1<<11)
#define MDW_AUDREC_ERR_CODEC_ENCODE_FAIL            (0x1<<12)
#define MDW_AUDREC_ERR_CODEC_CLOSE_FAIL             (0x1<<13)

#define MDW_AUDREC_ERR_RING_BUF_ACCESS_FAIL         (0x1<<14)

#define MDW_AUDREC_ERR_WRITE_FILE_FAIL              (0x1<<15)
#define MDW_AUDREC_ERR_WRITE_MEM_FAIL               (0x1<<16)
#define MDW_AUDREC_ERR_WRITE_STREAM_RING_FAIL       (0x1<<17)

#define MDW_AUDREC_ERR_ALLOC_MEMORY_FAIL            (0x1<<18)

#define MDW_AUDREC_ERR_CORNER_MSG_BEFORE            (0x1<<19)
#define MDW_AUDREC_ERR_CORNER_MSG_AFTER             (0x1<<20)
#define MDW_AUDREC_ERR_CORNER_MSG_DISK_FULL         (0x1<<21)

#endif
