#ifndef _MMPF_MSG_H_
#define _MMPF_MSG_H_

#include "os_wrap.h"
#include "mmp_err.h"

typedef MMP_ULONG MMP_MSG_RETURN;

typedef struct _msg_t
{
    MMP_UBYTE *srcName;//task name of the sending task
    MMP_ULONG val;//A general purpose integer field for quick debugging or simple integer data.
    MMP_ULONG id;
    MMP_ULONG sub_id;
    void      *data;
    MMPF_OS_SEMID *sem;
    MMP_MSG_RETURN err;//as return value
} msg_t ;

typedef struct _msg_queue_t
{
    MMP_USHORT rd_i ;
    MMP_USHORT wr_i ;
    MMP_USHORT msg_len;
    MMP_ULONG  *msg_q ;
} msg_queue_t ;

typedef struct MMP_MSG_T *MMP_MSG_HANDLE;

typedef enum {
	MMP_MSG_ERR_NONE = 0,
	MMP_MSG_ERR_INIT,
	MMP_MSG_ERR_CREATE_SEM,
	MMP_MSG_ERR_POST,
	MMP_MSG_ERR_TIMEOUT,
	MMP_MSG_ERR_ACQUIRE_SEM,
	MMP_MSG_ERR_QUEUE_FULL
}MMP_MSG_ERR;//may merge to MMP_ERR later

//define the main message type here
enum {
    MSG_STREAM_H264_FRAME_SIZE,
	MSG_MAX
};

//The ID of the task that receives the message
typedef enum {
    MSG_RX_STREAM,
    MSG_RX_MAX,
    MSG_RX_NONE
} MMP_MSG_RECEIVER;

//define max number of tasks that will use this message queue system.
#define MSG_QUEUE_NUMS MSG_RX_MAX


MMP_ERR MMPF_MSG_Init(void);

#define USE_HANDLE 0

#if USE_HANDLE
MMP_MSG_ERR MMPF_MSG_Register(MMP_MSG_HANDLE* pHandle, MMPF_OS_FLAGID os_id, MMPF_OS_FLAGS flags, MMP_ULONG timeOut);
msg_t *MMPF_MSG_Wait(MMP_MSG_HANDLE h, MMPF_OS_FLAGS *ret_flags);
MMP_MSG_ERR MMPF_MSG_Send(MMP_MSG_HANDLE h,MMP_ULONG gp_val,MMP_ULONG msg_id,MMP_ULONG msg_sub_id,void *data, MMP_MSG_RETURN* ret);
MMP_MSG_ERR MMPF_MSG_Post(MMP_MSG_HANDLE h,MMP_ULONG gp_val,MMP_ULONG msg_id,MMP_ULONG msg_sub_id,void *data);
#else
MMP_MSG_ERR MMPF_MSG_Register(MMP_MSG_RECEIVER rx, MMPF_OS_FLAGID os_id, MMPF_OS_FLAGS msgFlag, MMPF_OS_FLAGS waitFlags, MMP_ULONG timeOut);
MMP_MSG_ERR MMPF_MSG_Wait(MMP_MSG_RECEIVER rx, MMPF_OS_FLAGS *ret_flags, msg_t **ppMsg);
MMP_MSG_ERR MMPF_MSG_Send(MMP_MSG_RECEIVER rx,MMP_ULONG gp_val,MMP_ULONG msg_id,MMP_ULONG msg_sub_id,void *data, MMP_MSG_RETURN* ret);
MMP_MSG_ERR MMPF_MSG_Post(MMP_MSG_RECEIVER rx,MMP_ULONG gp_val,MMP_ULONG msg_id,MMP_ULONG msg_sub_id,void *data);
MMP_MSG_ERR MMPF_MSG_Tear(MMP_MSG_RECEIVER rx, msg_t *msg);
#endif

#endif //_MMPF_MSG_H_
