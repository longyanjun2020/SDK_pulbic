#if !defined(__MSMDEV_H__)
#define __MSMDEV_H__

#include "msmdrv.h"

//#define CMD_ID(devType, op, attribute) ((U16)((op << 12) | (devType << 8) | (attribute << 4)))
#define CMD_ID(devType, op, attribute) makeCMD_ID((MSMDevType_e)devType, (MSMCmdOp_e)op, (U16)attribute)
#define GET_DEV_TYPE(uid)   ((uid & 0x0F00) >> 8)
#define GET_OP(uid)         ((uid & 0xF000) >> 12)
#define GET_ATTR(uid)       ((uid & 0x00F0) >> 4)
#define GET_CH(uid)         (uid & 0x000F)
#define REMAP_OP(op, attr)  (op = (MSMCmdOp_e)((U32)op > (U32)0 ? op + MSDEV_LAST_SCMD : attr))
#define MANAGE_OP(uid)      ((U16)MSMDEV_MANAGE == ((U16)GET_OP(uid) + (U16)MSDEV_LAST_SCMD))

/* Channel definition */
#define CH_NUM              (6)
#define CMD_CH              (0)
#define READ_CH             (1)
#define WRITE_CH            (2)
#define EXE_CH              (3)
#define MANAGE_CH           (4)
#define DIRECT_CH           (5)
#ifdef  USE_DEV_CHANNEL_BUFFER
#define CH_BUF_SIZE         (16)
#endif

/* Channel Attribute */
#define CH_NORMAL           (0)             /* normal */
#define CH_EMERGENCY        (1)             /* urgent in ISR context */
#define CH_SYSTEM_REAL_TIME_REQUEST (2)     /* real-time request from Montage */


/* Add buffer macro */
#define ALLOC_ADD_BUFFER(devCh_sp)          allocAddBuffer(devCh_sp)
#define DELETE_ADD_BUFFER(addBuffer_sp)     delAddBuffer(addBuffer_sp)
#define INIT_ADD_BUFFER(devCh_sp)           initDevChAddBuffer(devCh_sp)
#define POST_ADD_BUFFER(addBuffer_sp)       postDevChAddBuffer(addBuffer_sp)
#define GET_ADD_BUFFER(devCh_sp)            getDevChAddBuffer(devCh_sp)

/* Multi-buffer ? */
#define GET_BUFFER_COUNT(devCh_sp)          checkDevChAddBuffer(devCh_sp)
#define BUILD_BUFFER_LIST(devCh_sp, data_np, dataLen_n) buildAddBufferList(devCh_sp, data_np, dataLen_n)
#define RETURN_BUFFER(devCh_sp)             returnAddBuffer(devCh_sp)

/* Channel Event */
#define SET_EVENT(msmEvent_sp, eventId, d32_0, d32_1, userData_n)  (msmEvent_sp)->eventID_e = eventId; (msmEvent_sp)->eventData_n[0] = (U32)d32_0;(msmEvent_sp)->eventData_n[1] = (U32)d32_1;(msmEvent_sp)->userData_n = userData_n;

typedef MSMErrcode_e (* DevGenIF)
(
    MSMDev_h        dev_h,
    MSMCmdData_s    *cmdData_sp,
    U32             cmdID_n
);

struct DevCh_s_;

typedef struct DevCh_AddBuffer_s_
{
    U8          *data_np;       /* Data buffer for reading/writing */
    U32         len_n;          /* The length of data buffer */
    U32         writeLen_n;     /* The length of written data */
    U32         readLen_n;      /* The length of read data */
    U32         bufID_n;        /* The attached buffer identifier */

    struct DevCh_s_                 *owner; /* Owner (DevCh) */
    struct DevCh_AddBuffer_s_       *prev;  /* Link field */
    struct DevCh_AddBuffer_s_       *next;

} DevCh_AddBuffer_s;

typedef struct DevCh_s_
{
    MSMDev_h    dev_h;                  /* Device handle */
    U16         cmdID_n;                /* Command identifier */
    Boolean     used_b;                 /* Released ? */
    Boolean     dataAbort_b;            /* Stop ? */
    U32         userData_n;             /* User data recorded */
    U8          *data_np;               /* Data buffer for reading/writing */
    U32         dataLen_n;              /* Data size prepared */
    U32         len_n;                  /* The length of data buffer */
    U32         writeLen_n;             /* The length of written data */
    U32         readLen_n;              /* The length of read data */
    MSMDone     done_fxp;               /* Done Callback */
    MSMReturn   return_fxp;             /* Return Callback */
    MSMNotify   notifyCallback_fxp;     /* Notification Callback */
    U16         dataBufferCount_s;      /* Count of data buffer attached */
    U16         chInfo_n;               /* Reserved channel info. */
    U16         chAttrib_n;             /* Specific attributes */
    U32         timeStamp_n;            /* Timestamp */
    U32         elapsed_n;              /* Elapsed time */
    DevCh_AddBuffer_s   *queueFront_sp; /* Front of Add Buffer queue */
    DevCh_AddBuffer_s   *queueRear_sp;  /* Read of Add Buffer queue */
    U16         renderType_n;           /* Packet or Direct-rendering ? */
    U32         dcVar_n;                /* Direct Variable */
    U32         dcAddr_n;               /* Direct Address */
    U32         dcCount_n;              /* Direct Size */
    U32         dcRO_n;                 /* Direct RO Area (midi) */
    U16         dcObj_n;                /* Direct Object type (e.g. pcm, osd, cdc, midi, mp3...) */
    U16         dcError_n;              /* Direct Error return */
#ifdef USE_DEV_CHANNEL_BUFFER
    U8          chBuf_na[CH_BUF_SIZE];  /* Channel buffer for private use*/
#endif

    U32         checksum_n;             /* Checksum (read) */
    U8          *shareData_np;
    U32         shareDataLen_n;
    struct DevCh_s_     *prev;          /* Link field */
    struct DevCh_s_     *next;

} DevCh_s;

typedef struct DevCmd_s_
{
    DevGenIF    devIFEntry_fxp;         /* prep */
    DevGenIF    devIFImmediate_fxp;     /* Immediate handler */
    DevCh_s     *devCh_sp;
    U16         chNum_n;
    Boolean     oneShot_b;
} DevCmd_s;

typedef struct Dev_s_
{
    DevCmd_s    devCmd_sa[MSMDEV_CMD_NUM];
} Dev_s;

typedef struct DevHandle_s_
{
    MSMDevType_e    devType_e;
    U32             alloc_n;
} DevHandle_s;

I32 findFreeCh
(
    MSMCmdOp_e      op_e,
    DevCmd_s       *devCmd_sp,
    U16            cmdID_n,
    MSMCmdData_s   *cmdData_sp
);

DevCh_s *findWriteCh
(
    void
);

DevCh_s *findChFromCmdID
(
    U16             cmdID_n
);

Boolean freeChFromCmdID
(
    U16             cmdID_n
);

DevCh_s *findChFromManageReturn
(
    U16             cause_n
);

void msmDevChanInit
(
    void
);

void addDevChActiveList
(
    DevCh_s*    devChListHead_sp,
    DevCh_s* devChNew_sp
);

void delDevChActiveList
(
    DevCh_s *devChDel_sp
);

DevCh_s *findDevChActiveList
(
    DevCh_s*    devChListHead_sp,
    U16    chInfo_n
);

void  msmBypass
(
    U16 devDisp_n,
    U16 bpMode_n
);

Boolean  msmClockManager
(
    U16 perfID_n
);

void msmDevAddBufferInit
(
    void
);

void initDevChAddBuffer
(
    DevCh_s *devCh_sp
);

DevCh_AddBuffer_s *allocAddBuffer
(
    DevCh_s *devCh_sp
);

DevCh_AddBuffer_s   *getDevChAddBuffer
(
    DevCh_s *devCh_sp
);

DevCh_AddBuffer_s   *returnAddBuffer
(
    DevCh_s *devCh_sp
);

U32 checkDevChAddBuffer
(
    DevCh_s *devCh_sp
);

void postDevChAddBuffer
(
    DevCh_AddBuffer_s* addBuffer_sp
);

void delAddBuffer
(
    DevCh_AddBuffer_s* addBuffer_sp
);

void buildAddBufferList
(
    DevCh_s     *devCh_sp,
    U8          *data_np,
    U32         dataLen_n
);

Boolean  msmPowerManager
(
    U16 perfID_n
);

void msmManageCmdHandler
(
    U16    cmdID_n,
    MSMCmdData_s   *cmdData_sp
);

U16 makeCMD_ID
(
    MSMDevType_e    devType_e,
    MSMCmdOp_e        op_e,
    U16   attr_n
);

Boolean checkManageCmd
(
    U16 cmdID_n
);

Boolean checkHWCmd
(
    U16 cmdID_n
);

void msmDevCallbacks
(
    MSMEvent_s      event_s,
    U32             userData_n
);

DevHandle_s *requestDevHandle
(
    MSMDevType_e    devType_e
);

void releaseDevHandle
(
    DevHandle_s   *devHandle_sp
);

#define MSM_DEV_HANDLE_REQ(devType_e)       requestDevHandle(devType_e)
#define MSM_DEV_HANDLE_RELEAE(devHandle_sp) releaseDevHandle(devHandle_sp);

extern U16 maxChNum_n;
#define MAX_CH_NUM  maxChNum_n

extern DevCh_s *devChPool_sp;
extern Dev_s dev_sa[MSMDEV_NUM];

extern DevCh_s devChManageList_s;       /* reserved */
extern DevCh_s devChNormWriteList_s;    /* reserved */
extern DevCh_s devChNormReadList_s;     /* reserved */
extern DevCh_s devChUrgentReadList_s;   /* reserved */
extern DevCh_s devChUrgentWriteList_s;  /* reserved */



#endif  /* __MSMDEV_H__ */
