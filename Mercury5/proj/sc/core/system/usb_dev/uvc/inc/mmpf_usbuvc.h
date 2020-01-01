#ifndef _MMPF_USBUVC_H_
#define _MMPF_USBUVC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_typedef.h"
#include "mmpf_usbpccam.h"
#include "mmpf_usb_h264.h"
#include "mmp_usb_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define EN_EZMODE_TEMP_DBG_LOG      (0) //1: temp EZMODE debug log
#define EN_EZMODE_FML_PROC          (1) //1: enable EZMODE formal ISP process, 0: disable

#define UVC_SEND_IMG_RET_CONTINUE 	(0x00)
#define UVC_SEND_IMG_RET_END_FRAME 	(0x01)

// Total numbers of video frames
#if (SUPPORT_DUAL_SNR_PCAM_OUT)
#define NUM_YUY2_VIDEO  (3)
#define NUM_MJPG_VIDEO  (3)
#define NUM_H264_VIDEO  (2)
#else
#define NUM_YUY2_VIDEO  (2)
#define NUM_MJPG_VIDEO  (2)
#define NUM_H264_VIDEO  (2)
#endif

// Total numbers of still frames
#define NUM_YUY2_STILL  (3)
#if (SUPPORT_DUAL_SNR_PCAM_OUT)
#define NUM_MJPG_STILL  (4)
#else
#define NUM_MJPG_STILL  (3)
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

// Still capture
typedef enum _MMPF_USBUVC_CAPTURE_EVENT {
	STILL_IMAGE_WAITING 		= 0,
	STILL_IMAGE_TRIGGER 		= 1,
	STILL_IMAGE_PREVIEW_STOP 	= 2,
	STILL_IMAGE_SENDING 		= 3,
	STILL_IMAGE_FINISH 			= 4
} MMPF_USBUVC_CAPTURE_EVENT;

// Get data 32 status
typedef enum _MMPF_USBUVC_CS_GET_DATA_32_STS {
	CS_GET_DATA_32_STS_IDLE 			= 0,
	CS_GET_DATA_32_STS_EXEC_ISP_RD,
	CS_GET_DATA_32_STS_EXEC_ISP_RD_DONE,
	CS_GET_DATA_32_STS_EXEC_CALI_RD,
	CS_GET_DATA_32_STS_EXEC_CALI_RD_DONE,
	CS_GET_DATA_32_STS_IN_DATA_TRANS,
	CS_GET_DATA_32_STS_IN_DATA_TRANS_DONE,
	CS_GET_DATA_32_STS_MAX
} MMPF_USBUVC_CS_GET_DATA_32_STS;

// Set data 32 status
typedef enum _MMPF_USBUVC_CS_SET_DATA_32_STS {
	CS_SET_DATA_32_STS_IDLE 			= 0,
	CS_SET_DATA_32_STS_EXEC_ISP_WR,
	CS_SET_DATA_32_STS_EXEC_ISP_WR_DONE,
	CS_SET_DATA_32_STS_OUT_IQ_TBL,
	CS_SET_DATA_32_STS_OUT_IQ_TBL_DONE,
	CS_SET_DATA_32_STS_EXEC_SIF_WR,
	CS_SET_DATA_32_STS_EXEC_SIF_WR_DONE,
	CS_SET_DATA_32_STS_OUT_CALI,
	CS_SET_DATA_32_STS_OUT_CALI_DONE,
	CS_SET_DATA_32_STS_MAX
} MMPF_USBUVC_CS_SET_DATA_32_STS;

typedef enum _MMPF_USBUVC_EVENT {
    USBUVC_EVENT_INIT_SENSOR = 0,
    USBUVC_EVENT_INIT_PIPE,
    USBUVC_EVENT_START_STREAMING,
    USBUVC_EVENT_STOP_STREAMING,
    USBUVC_EVENT_NUM
} MMPF_USBUVC_EVENT;

typedef int (MMPF_USBUVC_CBFunc) (void*);

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _DataExchangeParam
{
	MMP_USHORT	id;			// command ID
	MMP_ULONG	data_len;	// transfer lens
	MMP_ULONG	cur_offset;	// current read/write offset
	MMP_BYTE	*ptr;		// data buffer
} DataExchangeParam;

/* Set or get data 32 configuration */
typedef struct __attribute__((packed)) _MMPF_USBUVC_CS_DATA_32_CFG 
{
    
    MMP_UBYTE   bCurSts;            /* status of set or get data 32 op */
    MMP_UBYTE   bSyncAck;           /* Wait operation complete to reply ack */
    MMP_ULONG   dwParm_0;           /* parameter 0 of set data 32 op */
    MMP_ULONG   dwParm_1;           /* parameter 1 of set data 32 op */
    MMP_ULONG   dwParm_2;           /* parameter 2 of set data 32 op */
    MMP_ULONG   dwParm_3;           /* parameter 3 of set data 32 op */
} MMPF_USBUVC_CS_DATA_32_CFG;

typedef void (*USB_Cmd2TaskCB)(void);

#if (EN_EZMODE_FML_PROC == 0)
/* test code when w/o ISP Lib */
typedef struct __attribute__((packed)) _EZ_MODE_IQ_DATA_BUF 
{
	unsigned short cmd_type;
	unsigned short data_length;
	unsigned short sysmode;
	unsigned short page;
	unsigned short type;
	unsigned short index;
	unsigned short buf_ptr_size;
	char  data[256];
} EZ_MODE_IQ_DATA_BUF;
#endif

typedef struct _DMAInfo
{
	MMP_ULONG fb_addr;
	MMP_ULONG endpoint;
	MMP_USHORT pkt_byte;
	MMP_USHORT last_tx_flag;
} DMAInfo;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

#if(SUPPORT_UVC_FUNC)
void USB_SetCommandToTask(void *pfUSBCmd2Task);
void *USB_GetCommandToTask(void);
MMP_UBYTE usb_vc_send_image(MMP_UBYTE sti_mode);

MMP_ERR usb_vc_wait_dma_done(MMP_ULONG timeout);
void usb_vc_set_still_commit(STILL_PROBE* pSCIN);
void usb_vc_get_still_probe(MMP_UBYTE FormatIndex, MMP_UBYTE FrameIndex, STILL_PROBE* pSP);
void usb_vc_set_still_probe(MMP_UBYTE FormatIndex, MMP_UBYTE FrameIndex);
void usb_vc_set_still_resolution(MMP_UBYTE FormatIndex, MMP_UBYTE FrameIndex);
MMP_UBYTE uvc_setH264mode(MMP_UBYTE ubMode);
void usb_uvc_start_preview(void);
void usb_uvc_reset_multi_stream(void);

MMP_BOOL usb_uvc_config_stream(void);
void usb_uvc_config_sensor_isp(void);
void usb_uvc_start_stream(void);
void usb_uvc_stop_stream(void);
void usb_uvc_fill_payload_header(MMP_UBYTE *frame_ptr, MMP_ULONG framelength, MMP_ULONG frameseq, MMP_ULONG flag, MMP_ULONG timestamp, MMP_USHORT w, MMP_USHORT h, MMP_USHORT type, MMP_USHORT framerate);
void usb_skype_fill_payload_header(MMP_UBYTE *frame_ptr,MMP_ULONG framelength, MMP_ULONG frameseq, MMP_ULONG flag, MMP_ULONG timestamp, MMP_USHORT w, MMP_USHORT h, MMP_USHORT type, MMP_USHORT framerate);
MMP_UBYTE *usb_uvc_search_app3_insert_addr(MMP_UBYTE *jpeg, MMP_ULONG len, MMP_USHORT tag);

void uvc_init(void);
void usb_vc_req_proc(MMP_UBYTE req);
void usb_vc_update_automode(void);
int  usb_vc_out_data(void);
void usb_vc_capture_trigger(MMP_UBYTE pressed);
void usb_uvc_stop_preview(void);
void usb_vc_update_async_mode(MMP_UBYTE bOriginator, MMP_UBYTE bSelector, MMP_UBYTE bAttribute,void *bValue,MMP_UBYTE bValUnit);
MMP_ULONG usb_vc_take_raw_picture(MMP_UBYTE ubSnrSel, MMP_UBYTE raw_mode, MMP_ULONG srcAddr, MMP_ULONG dstAddr);
volatile MMP_UBYTE *usb_vc_fill_header(volatile MMP_UBYTE *ptr, MMP_UBYTE bfh, MMP_ULONG pts, MMP_ULONG stc, MMP_USHORT sofnum);
H264_ENCODER_VFC_CFG *usb_get_uvc_h264_cfg(void);
void usb_vc_cmd_cfg(MMP_UBYTE req, VC_CMD_CFG *cfg, MMP_ULONG cur_val);

#if defined(SUPPORT_UVC_ISP_EZMODE_FUNC) && (SUPPORT_UVC_ISP_EZMODE_FUNC)
MMPF_USBUVC_CS_DATA_32_CFG* usb_uvc_GetData32CFG(void);
MMPF_USBUVC_CS_DATA_32_CFG* usb_uvc_SetData32CFG(void);
void usb_uvc_ProcessStatus(void);
MMP_ERR usb_uvc_InitDat32(MMP_ULONG pulBufAddr, MMP_ULONG pulSz);
MMP_ERR usb_uvc_DwnldDat32(MMP_UBYTE *pulDat, MMP_USHORT pulLen);
MMP_ERR usb_uvc_UpldDat32(MMP_UBYTE *pulDat, MMP_USHORT pulLen, MMP_USHORT *pulValLen);
#endif
void usb_uvc_SetRtcTime(void);

MMP_ERR MMPF_USBUVC_H264_RegisterCallback(MMP_ULONG ulEvent, void *pCallback);
void usb_vc_eu1_mmp_cmd16_register_handler(void *pfEventHandler);
#endif

#endif //_MMPF_USBUVC_H_
