/*
*===============================================================================
*                                    USB-EH
*                          The USB Embedded Host Stack
*                              EMBEDDED HOST CORE
*
*              Copyright (c) 2014, Alpha Imaging Technology Corp.
*                             All Rights Reserved
*
* File    : usbeh_core.h
* Author  : Alterman
* Version : v1.0
*===============================================================================
*/

#ifndef _USBEH_CORE_H_
#define _USBEH_CORE_H_

#include "stddef.h"
#include "usbeh_cfg.h"
#include "usbeh_bsp.h"
#include "usbeh_os.h"
#include "usbeh_std.h"

/*
*-------------------------------------------------------------------------------
*                                 Error Codes
*-------------------------------------------------------------------------------
*/
#define USBEH_ERR_NONE              (0)

#define USBEH_ERR_NULL_POINTER      (-100)
#define USBEH_ERR_INVALID_PARAM     (-101)
#define USBEH_ERR_UNSUPPORTED       (-102)
#define USBEH_ERR_API_FLOW          (-103)
#define USBEH_ERR_UNKNOWN           (-104)

#define USBEH_ERR_OS_CREATE_TASK    (-200)
#define USBEH_ERR_OS_CREATE_EVENT   (-201)
#define USBEH_ERR_OS_DESTROY_EVENT  (-202)
#define USBEH_ERR_OS_PEND_EVENT     (-203)
#define USBEH_ERR_OS_POST_EVENT     (-204)
#define USBEH_ERR_OS_CREATE_SEM     (-205)
#define USBEH_ERR_OS_DESTROY_SEM    (-206)
#define USBEH_ERR_OS_ACQUIRE_SEM    (-207)
#define USBEH_ERR_OS_RELEASE_SEM    (-208)
#define USBEH_ERR_OS_ACCEPT_SEM     (-209)
#define USBEH_ERR_OS_CREATE_MSGQ    (-210)
#define USBEH_ERR_OS_DESTROY_MSGQ   (-211)
#define USBEH_ERR_OS_READ_MSG       (-212)
#define USBEH_ERR_OS_SNED_MSG       (-213)

#define USBEH_ERR_CORE_RESOURCE     (-300)
#define USBEH_ERR_CORE_PARAM        (-301)
#define USBEH_ERR_CORE_ENUMERATION  (-302)
#define USBEH_ERR_URB_INVALID       (-303)

#define USBEH_ERR_CNTL_RESOURCE     (-400)
#define USBEH_ERR_CNTL_UNSUPPORTED  (-401)
#define USBEH_ERR_CNTL_EP0_CLOSE    (-402)
#define USBEH_ERR_CNTL_EP_CLOSE     (-403)
#define USBEH_ERR_CNTL_PROTOCOL     (-404)

#define USBEH_ERR_CLASS_NO_DRV      (-500)
#define USBEH_ERR_CLASS_PARAM       (-501)
#define USBEH_ERR_CLASS_RESOURCE    (-502)

#define USBEH_ERR_URB_PARAM         (-600)
#define USBEH_ERR_URB_RESOURCE      (-601)

/*
*-------------------------------------------------------------------------------
*                             USB Connection Speed
*-------------------------------------------------------------------------------
*/
typedef enum _USBEH_DEV_SPEED {
    USBEH_DEV_LS = 0,
    USBEH_DEV_FS,
    USBEH_DEV_HS,
    USBEH_DEV_SS
} USBEH_DEV_SPEED;

/*
*-------------------------------------------------------------------------------
*                                USB Core Events
*-------------------------------------------------------------------------------
*/
typedef enum _USBEH_DEV_EVENT {
    USBEH_DEV_CONNECT       = 0x00000001,
    USBEH_DEV_SUSPEND       = 0x00000002,
    USBEH_DEV_DISCONNECT    = 0x00000004
} USBEH_DEV_EVENT;

typedef enum _USBEH_XFER_EVENT {
    USBEH_XFER_SCHEDULE     = 0x00000001
} USBEH_XFER_EVENT;

/*
*-------------------------------------------------------------------------------
*                     USB Embedded Host Endpoint Structures
*-------------------------------------------------------------------------------
*/
typedef struct _USBEH_EP_CFG {
    UCHAR       num;        /* endpoint logical number          */
    UCHAR       type;       /* transfer type                    */
    UCHAR       speed;      /* transfer speed                   */
    UCHAR       dir;        /* transfer direction               */
    UCHAR       nak_limit;  /* NAK timeout count (bulk, ctrl)   */
    UCHAR       interval;   /* transfer interval (iso, int)     */
    UCHAR       addl_txn;   /* additional transaction per sof   */
    USHORT      func_addr;  /* target function address          */
    USHORT      max_pkt_size; /* max packet size                */
} USBEH_EP_CFG;

typedef struct _USBEH_EP {
    BOOL        is_opened;  /* is this endpoint opened?         */
    UCHAR       id;         /* physical endpoint number         */
} USBEH_EP;

typedef struct _USBEH_EP0 {
    USHORT          max_pkt_size;
    USBEH_DEV_REQ   reqest;
    UCHAR           dev_desc[USBEH_DEV_DESC_BUF_SIZE]; /* buf for device desc */
    UCHAR           cfg_desc[USBEH_CFG_DESC_BUF_SIZE]; /* buf for config desc */
    UCHAR           data[USBEH_EP0_DATA_BUF_SIZE];  /* buf for ctrl xfer data */
} USBEH_EP0;

/*
*-------------------------------------------------------------------------------
*                            USB Embedded Host Handler
*-------------------------------------------------------------------------------
*/
typedef struct _USBEH_DEV_HANDLE {
    USHORT              addr;
    USBEH_DEV_SPEED     speed;
} USBEH_DEV_HANDLE;

typedef struct _USBEH_MSG {
    UINT    *pool;      /* pointer to msg pool */
    UINT    depth;      /* total number of msg elements in pool */
    UINT    index;      /* point to a free one element */
    UINT    free;       /* number of msg element available */
} USBEH_MSG;

typedef struct _USBEH_HANDLE {
    OS_MSGQ             enum_msgq_id;
    OS_MSGQ             xfer_msgq_id;
    void                *enum_msgq[USBEH_OS_ENUM_MSGQ_SIZE];
    void                *xfer_msgq[USBEH_OS_XFER_MSGQ_SIZE];
    UINT                enum_msg[USBEH_OS_ENUM_MSGQ_SIZE];
    UINT                xfer_msg[USBEH_OS_XFER_MSGQ_SIZE];
    USBEH_MSG           enum_msg_hd;
    USBEH_MSG           xfer_msg_hd;
    USBEH_DEV_HANDLE    device;
    USBEH_EP0           ep0;
    USBEH_EP            ep[USBEH_MAX_LOG_EP_NUM];
} USBEH_HANDLE;

/*
*-------------------------------------------------------------------------------
*                               USB Request Block
*-------------------------------------------------------------------------------
*/
typedef enum _USBEH_URB_STATUS {
    USBEH_URB_STATUS_IDLE = 0,
    USBEH_URB_STATUS_OCCUPIED,
    USBEH_URB_STATUS_QUEUED,
    USBEH_URB_STATUS_XFER,
    USBEH_URB_STATUS_COMPLETED,
    USBEH_URB_STATUS_ABORTED
} USBEH_URB_STATUS;

typedef struct _USBEH_URB {
    UCHAR       ep;
    BOOL        fifo_mode;      /* 1:fifo mode, 0:dma mode  */
    UCHAR       dir;            /* transfer direction       */
    UCHAR       status;         /* current status           */
    INT         err;            /* error code               */
    UCHAR       *p_buf;         /* start pointer of buf     */
    UCHAR       *p_buf_cur;     /* current pointer of buf   */
    UINT        data_length;    /* size of data to transfer */
    UINT        xfer_length;    /* size of data transfered  */
    void        (*complete_cb)(struct _USBEH_URB *urb);
} USBEH_URB;

typedef struct _USBEH_URB_NODE {
    struct _USBEH_URB_NODE  *next;  /* point to next urb        */
    struct _USBEH_URB_NODE  *prev;  /* point to previous urb    */
    USBEH_URB               urb;    /* urb instance             */
    USHORT                  num;    /* urb node no. in pool     */
} USBEH_URB_NODE;

typedef struct _USBEH_URB_LIST {
    USBEH_URB_NODE  *head;      /* head of the urb list         */
    USBEH_URB_NODE  *tail;      /* tail of the urb list         */
    USHORT          in_used;    /* count urb nodes in used      */
    USHORT          last;       /* num of last used urb in pool,
                                   for speedup searching        */
} USBEH_URB_LIST;

/* Takes a urb pointer and returns the associated urb node pointer */
#define USBEH_GET_URB_NODE(urb)     \
            ((USBEH_URB_NODE *)((CHAR *)(urb) - offsetof(USBEH_URB_NODE, urb)))

/*
*-------------------------------------------------------------------------------
*                          USB Embedded Host Handler
*-------------------------------------------------------------------------------
*/
extern USBEH_HANDLE     m_usbeh_hd;

/*
*-------------------------------------------------------------------------------
*                       USB Embedded Host Core Functions
*-------------------------------------------------------------------------------
*/
extern INT  USBEH_Init(void);
extern void USBEH_GetVersion(USBEH_RELEASE_VER *version);
extern void USBEH_Start(void);
extern void USBEH_Stop(void);
extern INT  USBEH_InitEnumTask(void);
extern INT  USBEH_InitXferTask(void);
extern void USBEH_SetEnumEvent(USBEH_DEV_EVENT dev_event);
extern void USBEH_SetXferEvent(USBEH_XFER_EVENT xfer_event);
extern INT  USBEH_OpenEP(USBEH_EP_CFG *cfg);
extern INT  USBEH_Get_URB(USBEH_URB **urb);
extern INT  USBEH_URB_Link(USBEH_URB *urb);
extern INT  USBEH_URB_Unlink(USBEH_URB *urb);
extern INT  USBEH_URB_UnlinkAll(void);
/*
*-------------------------------------------------------------------------------
*                  Endpoint0 Standard Control Transfer Functions
*-------------------------------------------------------------------------------
*/
extern INT  USBEH_EP0_SubmitXfer(USBEH_DEV_REQ *req, void *data);
extern INT  USBEH_EP0_GetDeviceDesc(USBEH_HANDLE *hc, void *desc, USHORT length);
extern INT  USBEH_EP0_SetAddress(USBEH_HANDLE *hc, USHORT dev_addr);
extern INT  USBEH_EP0_GetConfigDesc(USBEH_HANDLE *hc, void *desc, UCHAR desc_idx, 
                                    USHORT length);

/*
*-------------------------------------------------------------------------------
*                      USB Request Block Related Functions
*-------------------------------------------------------------------------------
*/
extern INT  USBEH_URB_Link(USBEH_URB *urb);
extern INT  USBEH_URB_Unlink(USBEH_URB *urb);
extern INT  USBEH_URB_UnlinkAll(void);

/*
*-------------------------------------------------------------------------------
*                      USB Embedded Host Controller Functions
*-------------------------------------------------------------------------------
*/
extern INT  USBEH_Controller_Init(void);
extern void USBEH_Controller_Start(void);
extern void USBEH_Controller_Stop(void);
extern void USBEH_Controller_Suspend(void);
extern void USBEH_Controller_Resume(void);
extern void USBEH_Controller_ResetDev(void);
extern UINT USBEH_Controller_GetSOF(void);
extern void USBEH_Controller_GetConnSpeed(USBEH_DEV_SPEED *speed);
extern void USBEH_Controller_SetDevAddr(UCHAR addr);
extern INT  USBEH_Controller_ConfigEP(UCHAR ep, USBEH_EP_CFG *cfg);
extern INT  USBEH_Controller_OpenEP(UCHAR *ep, USBEH_EP_CFG *cfg);
extern void USBEH_Controller_CloseEP(UCHAR ep);
extern void USBEH_Controller_AbortEP(UCHAR ep);
extern INT  USBEH_Controller_SubmitMsg(USBEH_DEV_REQ *req, void *data);
extern INT  USBEH_Controller_SubmitURB(UCHAR ep, USBEH_URB *urb);

#endif //_USBEH_CORE_H_

