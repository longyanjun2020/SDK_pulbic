#if !defined(__MSMDRV_H__)
#define __MSMDRV_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "msmglobal.h"
#include "msmcomm.h"


/************************************************************************/
/*  Marco and Constants Definition                                      */
/************************************************************************/
#if defined(MSMCmdOpDec)
#undef MSMCmdOpDec
#endif

#define MSMCmdOpDec(op, cmd, attr) op
#define MSMTag(op, cmd, attr) , op

#define MSMSCmdOpCol \
    MSMCmdOpDec(MSMDEV_INIT,       0, 00), \
    MSMCmdOpDec(MSMDEV_SLEEP,      0, 01), \
    MSMCmdOpDec(MSMDEV_RESUME,     0, 02), \
    MSMCmdOpDec(MSMDEV_PAUSE,      0, 03), \
    MSMCmdOpDec(MSMDEV_CONTINUE,   0, 04), \
    MSMCmdOpDec(MSMDEV_STOP,       0, 05), \
    MSMCmdOpDec(MSMDEV_RESET,      0, 06), \
    MSMCmdOpDec(MSMDEV_MKDIR,      0, 07), \
    MSMCmdOpDec(MSMDEV_RM,         0, 08), \
    MSMCmdOpDec(MSMDEV_LS,         0, 09), \
    MSMCmdOpDec(MSMDEV_SEEK,       0, 10), \
    MSMCmdOpDec(MSMDEV_PWD,        0, 11), \
    MSMCmdOpDec(MSMDEV_COPY,       0, 12), \
    MSMCmdOpDec(MSMDEV_RENAME,     0, 13) \
    MSMTag(MSDEV_LAST_SCMD_D,       0, 0) \
    MSMTag(MSDEV_LAST_SCMD = MSDEV_LAST_SCMD_D - 1, 0, 0)

#define MSMCmdOpCol \
    MSMCmdOpDec(MSMDEV_CP,         1, 0), \
    MSMCmdOpDec(MSMDEV_EXE,        2, 0), \
    MSMCmdOpDec(MSMDEV_READ,       3, 0), \
    MSMCmdOpDec(MSMDEV_WRITE,      4, 0), \
    MSMCmdOpDec(MSMDEV_MANAGE,     5, 0)

/************************************************************************/
/*  Type Definition                                                     */
/************************************************************************/

typedef enum MSMDevType_e_
{
    MSMDEV_CHIP,
    MSMDEV_CAM,
    MSMDEV_AUD,
    MSMDEV_IP,
    MSMDEV_DISP,
    MSMDEV_REC,
    MSMDEV_USB,
    MSMDEV_FS,
    MSMDEV_GE,
    MSMDEV_MP,
    MSMDEV_CDD,
    MSMDEV_GEM,
    MSMDEV_EAUD,
    MSMDEV_EVDO,
    MSMDEV_ND,
    MSMDEV_BOUNDARY = 0x0F,
    MSMDEV_NUM
} MSMDevType_e;

typedef Boolean (*MSMDone)
(
    MSMErrcode_e    status_e,
    U8              *data_np,
    U32             len_n,
    U32             userData_n
);

typedef void (*MSMReturn)
(
    MSMErrcode_e    status_e,
    U32             retValue_n,
    U32             userData_n
);

typedef enum MSMRegType_e_
{
    MSMREG_U8,
    MSMREG_U16
} MSMRegType_e;

typedef void (*MSMNotify)
(
    MSMEvent_s      event_s,
    U32             ownerUserData_n/*,
    U32             cmdUserData_n*/
);

typedef union MSMParam_u_
{
    U8              *param_np;
    U32             param_n;
} MSMParam_u;

typedef struct MSMCmdData_s_
{
    U32             attribute_n;
    U32             setting_n;
    MSMParam_u      param_u;
    U32             paramLen_n;
    U8              *data_np;
    U32             dataLen_n;
    U8              *shareData_np;
    U32             shareDataLen_n;
    Boolean         simpCmd_b;
    U32             userData_n;
    MSMDone         done_fxp;
    MSMReturn       return_fxp;
    MSMNotify       notify_fxp;
} MSMCmdData_s;

#define MSM_SHMREQ_WAIT          (0)
#define MSM_SHMREQ_FINISH        (1)
#define MSM_SHMREQ_ACCEPTED      (2)
#define MSM_SHMREQ_REJECTED      (3)

typedef struct PayloadHeader_s_
{
    U16 	        request_n;                  /* 0: user-defined request, 1: write data request, 2: read data request */
    U16 	        done_n;                     /* 0: request is waiting for service, 1: request has been finished */
    U32 	        sharedDataBuf_np;           /* Point to shared data buffer */
    U32 	        sharedDataBufSize_n;        /* The size in bytes of shared data buffer */
    U32 	        availableDataSize_n;        /* The read/write size in bytes of data in shared data buffer */
    U32 	        payloadBufSize_n;           /* The size in bytes of payload buffer */
    U32 	        usrDefDataSize_n;           /* The size in bytes of user-defined data structure */
    U16             dataType_n;                 /* Indicate what type of data is associated with */
    U16             cmdId_n;                    /* Command ID */
    U8              align_na[36];               /* Force to be cache line aligned (32-bytes) */
} PayloadHeader_s;

/* Data Request */
typedef struct MSMDataReq_s_
{
    U8 	            *buffer_np;     /* Point to data buffer (MMP based address) */
    U32             dataSize_n;     /* The read/write size in bytes of data */
    U8              align_na[24];   /* Force to be cache line aligned (32-bytes) */
} MSMDataReq_s;

typedef enum MSMCmdOp_e_
{
    MSMSCmdOpCol,
    MSMCmdOpCol,
    MSMDEV_CMD_NUM,
    MSMDEV_CMD /* Internal using */
} MSMCmdOp_e;

/* Date & Time */
typedef struct MSMDateTime_s_
{
    U16             year_n;         /* years since 1980 */
    U16             month_n;        /* months since January - [0..11] */
    U16             day_n;          /* days of the month - [1..31] */
    U16             hour_n;         /* hours since midnight - [0..23] */
    U16             minute_n;       /* minutes - [0..59] */
    U16             sec_n;          /* seconds - [0..59] */
} MSMDateTime_s;

/* Surface */
typedef struct MSMSurface_s_
{
    U16             x;              /* x-position of display surface */
    U16             y;              /* y-position of display surface */
    U16             width_n;        /* width of the display surface */
    U16             height_n;       /* height of the display surface */
    U16             pixelType_n;    /* Reserved (RGB565 only) */
    U16             sck_n;          /* Source color key */
    U8              *data_np;       /* data bytes buffer */
    U32             dataLen_n;      /* data length */
} MSMDisplaySurface_s;

/* Debug Read/Write */
typedef struct MSMDebugRW_s_
{
    U32             addr_n;         /* 32-bits physical address */
    U16             data_n;         /* 16-bits data read from/written to MMP */
} MSMDebugRW_s;


typedef enum MSMTableId_e_
{
    MSM_TABLE_DISPLAY = 0x0,        /* display table */
    MSM_TABLE_NUM
} MSMTableId_e;

/* Table Address Get/Set */
typedef struct MSMTableAddr_s_
{
    MSMTableId_e    tableId_e;      /* table identifier */
    U32             addr_n;         /* 32-bit address of resource table */
} MSMTableAddr_s;

/* Vendor Command */
typedef struct MSMVndCmdRW_s_
{
    U32 	        param_n;        /* 32-bit vendor command parameter */
    U8 	            *dataBuf_np;    /* Point to the data buffer */
    U32 	        dataBufSize_n;  /* The size in bytes of data buffer */
    U32             dataSize_n;     /* The read/write size in bytes of data in data buffer */
} MSMVndCmdRW_s;

/* Fire Interrupt (Ex) */
typedef struct MSMFireInt_s_
{
    U16             cause_n;        /* Interrupt cause */
    U16 	        status_na[4];   /* Interrupt payload */
} MSMFireInt_s;

/* Shared Memory Protection */
typedef struct MSMSHMProtect_s_
{
    U16             group_n;
    U16             item_n;
    U32             start_n;        /* The starting address of shared memory being protected */
    U32             size_n;         /* The size in bytes of shared memory being protected */
    U16             clientId_n;     /* The client Id */
    Boolean         inverse_b;      /* Set TRUE/FALSE to disallow/allow only this client to access */
    Boolean         enable_b;       /* Set TRUE/FALSE to enable/disable the protection */
} MSMSHMProtect_s;

/* FIFO Queue */
typedef struct MSMFIFOBufAlloc_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U8 	            *buffer_np;     /* Point to data buffer */
    U32             bufferSize_n;   /* The size in bytes of data buffer */
    U16             lock_b;         /* Lock the buffer if successful */
} MSMFIFOBufAlloc_s;

typedef struct MSMFIFOBufEnq_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U8 	            *buffer_np;     /* Point to data buffer */
    U32             dataSize_n;     /* The read/write size in bytes of data */
    U16             cmdId_n;        /* Associated command ID */
} MSMFIFOBufEnq_s;

typedef struct MSMFIFOBufDeq_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U8 	            *buffer_np;     /* Point to data buffer */
    U32             dataSize_n;     /* The read/write size in bytes of data */
} MSMFIFOBufDeq_s;

typedef struct MSMFIFOBufFree_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U8 	            *buffer_np;     /* Point to data buffer */
} MSMFIFOBufFree_s;

typedef struct MSMFIFOBufLock_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U8 	            *buffer_np;     /* Point to the buffer you want to lock */
} MSMFIFOBufLock_s;

typedef struct MSMFIFOBufUnlock_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U8 	            *buffer_np;     /* Point to the locked buffer */
} MSMFIFOBufUnlock_s;

typedef struct MSMFIFOBufAvail_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U32 	        bufAvail_n;     /* The number of available buffers */
} MSMFIFOBufAvail_s;

typedef struct MSMFIFOBufCount_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U32 	        bufCount_n;     /* The number of buffers in FIFO queue */
} MSMFIFOBufCount_s;

typedef struct MSMFIFOQueInit_s_
{
    U32             queueId_n;          /* Point to the associated queue */
    U16             nodeLowWmk_n;       /* Notify receiver to read when increasing from 0 to nodeLowWmk_n */
    U16             nodeHighWmk_n;      /* Notify sender to write when decreasing from full to nodeHighWmk_n */
    U16             freeLowWmk_n;       /* Notify sender of free buffer available when increasing from 0 to freeLowWmk_n */
    U16             freeHighWmk_n;      /* Notify receiver to release buffer when decreasing from full to freeHighWmk_n */
    U32 			pool_np;            /* Point to a block of shared memory (32-bytes aligned) */
    U32 			poolSize_n;         /* The size in bytes of the block of shared memory (32-bytes aligned) */
    U32 			bufferSize_n;       /* The size in bytes of data buffer (32-bytes aligned) */
} MSMFIFOQueInit_s;

typedef struct MSMFIFOQueClean_s_
{
    U32             queueId_n;      /* Point to the associated queue */
} MSMFIFOQueClean_s;

typedef struct MSMFIFOQueDel_s_
{
    U32             queueId_n;      /* Point to the associated queue */
} MSMFIFOQueDel_s;

typedef struct MSMFIFOQueStatus_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U16             full_b;         /* Will be set to 1 if FIFO queue is full */
    U16             empty_b;        /* Will be set to 1 if FIFO queue is empty */
} MSMFIFOQueStatus_s;

typedef struct MSMFIFOBufStatus_s_
{
    U32             queueId_n;      /* Point to the associated queue */
    U8 	            *buffer_np;     /* Point to data buffer */
    U16             locked_b;       /* Will be set to 1 if the buffer is locked */
} MSMFIFOBufStatus_s;

/* Low-level API Request Type */
typedef enum MSMLowlevelApiReqType_e_
{
    /* Back-Trace */
    MSM_BACKTRACE_INIT = 0,             /* initBacktrace() */
    MSM_BACKTRACE_GET_VOLUME_INFO,      /* getBacktraceVolumeInfo() */
    MSM_BACKTRACE_ERASE_VOLUME,         /* eraseBacktraceVolume() */
    MSM_BACKTRACE_ADD_RECORD,           /* addBacktrace() */
    MSM_BACKTRACE_WRITE,                /* writeBacktrace() */
    MSM_BACKTRACE_FINALIZE,             /* finalizeBacktrace() */
    MSM_BACKTRACE_INIT_FIND,            /* initFindBacktrace() */
    MSM_BACKTRACE_FIND_NEXT,            /* findNextBactrace() */
    MSM_BACKTRACE_READ,                 /* readBactraceData() */
    /* NAND E2P */
    MSM_NAND_E2P_RO_SAVE,               /* Save to Partition_0 */
    MSM_NAND_E2P_RO_LOAD,               /* Load from Partition_0 */
    MSM_NAND_E2P_BACKUP,                /* reserve */
    MSM_NAND_E2P_RESTORE,               /* reserve */
    MSM_NAND_E2P_RW_SAVE,               /* Save to Partition_1 */
    MSM_NAND_E2P_RW_LOAD,               /* Load from Partition_1 */
    /* RAMDUMP */
    MSM_RAMDUMP_SD,                     /* WriteToSD */
    MSM_RAMDUMP_SD_PWR_QUERY,           /* QuerySDPower */
    MSM_RAMDUMP_SD_INIT,                /* InitSD */
    MSM_RAMDUMP_FS_INIT_QUERY,          /* Query FS Init*/
    MSM_RAMDUMP_FS_UNMNT,               /* Unmount FS */
    /* NAND CUS */
    MSM_NAND_CUS_READ,
    MSM_NAND_CUS_WRITE,
    /* NADN DRIVER */
    MSM_NAND_CLOSE,                     /* Flush NAND driver data out of cache */
    /* ... */
    MSM_LOW_LEVEL_API_REQ_TYPE_FORCE_U32 = 0x7FFFFFFF
} MSMLowlevelApiReqType_e;

/*
 * remove me!
 * temporary fix compile error when hdapi_e2p.c is not update
 */
#define MSM_NAND_E2P_SAVE       MSM_NAND_E2P_RO_SAVE
#define MSM_NAND_E2P_LOAD       MSM_NAND_E2P_RO_LOAD
#define MSM_NAND_E2P_BACKUP     MSM_NAND_E2P_BACKUP
#define MSM_NAND_E2P_RESTORE    MSM_NAND_E2P_RESTORE
#define MSM_NAND_E2P_CLEAN_MAIN MSM_NAND_E2P_RW_SAVE
#define MSM_NAND_E2P_CLEAN_BKP  MSM_NAND_E2P_RW_LOAD

/* Low-level API Request */
typedef struct MSMLowlevelApiReq_s_
{
    MSMLowlevelApiReqType_e     request_e;               /* low-level API request type */
    U32                         parameterBufferAddr_n;   /* parameter buffer address */
    U32                         msTimeoutCnt_n;          /* 32-bits timeout counter, unit: msec */
    U32                         errRet_n;                /* return zero if success, otherwise nonzero value */
} MSMLowlevelApiReq_s;

/* Device GPIO Ids */
typedef enum MSMDevGpioId_e_
{
    /* M2U01 ~ M2U05 */
    MSM_DEV_M2U0X_GPIO17 = 0,
    MSM_DEV_M2U0X_GPIO19,
    MSM_DEV_M2U0X_GPIO20,
    MSM_DEV_M2U0X_GPIO38,
    MSM_DEV_M2U0X_GPIO39,
    MSM_DEV_M2U0X_GPIO60,
    /* BigBlue U01 ~ BigBlue U02 */
    /* Big2 U01 */
    MSM_DEV_GPIO_ID_FORCE_U32 = 0x7FFFFFFF
} MSMDevGpioId_e;

/* Device GPIO Configuration */
typedef struct MSMDevGpioConfig_s_
{
    U16     mode_n;             /* 0: output, 1: input, 2: input without pull-up/down (floating) */
    U16     defaultOutput_n;    /* default output level (0: Low, 1: High), only used for output mode */
} MSMDevGpioConfig_s;

/* Device GPIO */
typedef struct MSMDevGpio_s_
{
    MSMDevGpioId_e          gpioId_e;       /* device GPIO Id */
    U32                     errRet_n;       /* return zero if success, otherwise nonzero value */
    union gpioOp_u_
    {
        MSMDevGpioConfig_s  config_s;       /* config */
        U32                 input_n;        /* get input level */
        U32                 output_n;       /* set output level */
    } gpioOp_u;
} MSMDevGpio_s;

/** @internal
    @brief Internal data structure used to keep track of a sample's state
*/
typedef enum MSMManageOp_e_
{
    MSMMAN_CONFIG = 0,
    MSMMAN_PROBE = 7,
    MSMMAN_POWER = 8,
    MSMMAN_BYPASS = 9,
    MSMMAN_CLOCK = 10,
    MSMMAN_CMD_NUM = 5
} MSMManageOp_e;

typedef enum MSMDrvConfig_e_
{
    MSMCFG_SD_DRIVER_INIT = 0x0,
    MSMCFG_NO_SD_DRIVER_INIT = 0x1,
    MSMCFG_TRACE_BUFFER_INIT = 0x2,
    MSMCFG_TEST_RESP_BUFFER_INIT = 0x3,
    MSMCFG_UART_OUTPUT_PATH_MTX0 = 0x4,
    MSMCFG_UART_OUTPUT_PATH_MTX1 = 0x5,
    MSMCFG_NUM
} MSMDrvConfig_e;

typedef enum MSMDrvBusy_e_
{
    MSMBUSY_HIF = 0x0,
    MSMBUSY_NUM
} MSMDrvBusy_e;

typedef unsigned int MSMDev_h;


#define MAX_BIN_FILE_NAME       256
#define MSM_SIGNATURE           0x4D534D44

#include "msmplatform.h"

#ifdef __cplusplus
}
#endif


#endif /* MSMDEV_H */
