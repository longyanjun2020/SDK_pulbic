//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

#ifndef __MS_EHCI_HCD_H
#define __MS_EHCI_HCD_H

/* Flib Includes */
#include "include/drvCompiler.h"
#include "include/drvBitops.h"
#include "include/drvPCIMEM.h"
#include "include/drvList.h"
#include "include/drvTimer.h"
#include "include/drvKernel.h"
#include "include/drvUSBHost.h"

/* USB related implemented header files */
#include "drvUsbd.h"

#define  EHCI_IAA_MSEC        (20) /* if USB_SW_TIMER_TICK < 10, it could be 10 ms */
#define  EHCI_IAA_JIFFIES     (HZ/100)  /* arbitrary; ~10 msec */
#define  EHCI_IO_JIFFIES      (HZ/10)    /* io watchdog  */
#define  EHCI_ASYNC_JIFFIES   (HZ/20)    /* async idle timeout */
#define  EHCI_SHRINK_JIFFIES  (HZ/200)  /* async qh unlink delay */

#ifdef ENABLE_EHCI_ISOC_PIPE
#define ehci_qh_shadow ehci_shadow
#endif

struct usb_api_data
{
	int done;
	MS_S32  WaitFlag_ApiData;
};

/* save EHCI IRQ status for polling */
struct ehci_irq_stats {
	/* irq usage */
	U32    u32Normal;
	U32    u32Error;
	U32    u32Reclaim;
	U32    u32LostIAA;

	/* termination of urbs from core */
	U32    u32Complete;
	U32    u32Unlink;
};

#define  EHCI_MAX_ROOT_PORTS  1    /* see HCS_N_PORTS */

struct ehci_hcd {      /* one per controller */
	spinlock_t    tHcdLock;

	/* async schedule support */
	struct ehci_qh    *stAsync;
	struct ehci_qh    *stReclaim;

	int      iScanning : 1;
	int      need_rescan : 1;

	/* periodic schedule support , be careful about the size of memory cleanup*/
#define  DEFAULT_I_TDPS    1024    /* some HCs can do less */
	U32    u32PeriodicSize;
	U32    *pPeriodic;      /* hw periodic table */
	dma_addr_t    tPeriodicDma;
	U32    u32IThresh;  /* uframes HC might cache */
	union ehci_qh_shadow  *pshadow;  /* mirror hw periodic table */
	int    iNextUframe;  /* scan periodic, start here */
	U32    u32PeriodicSched;  /* periodic activity count */
	U32    u32random_frm; // to generate random start frame
	/* interrupt pipe new method (linux 3.10.40) */
	struct ehci_qh		*qh_scan_next;
	struct list_head	intr_qh_list;
#if 1 //def ENABLE_EHCI_ISOC_PIPE
	struct list_head	cached_itd_list;
	unsigned		clock_frame;
	// FIXME, 3.10.40
	unsigned		now_frame;	/* frame from HC hardware */
	unsigned		last_iso_frame;	/* last frame scanned for iso */
	unsigned		intr_count;	/* intr activity count */
	unsigned		isoc_count;	/* isoc activity count */
	unsigned		sitd_count;	/* siTD activity count */
	//unsigned		periodic_count;	/* periodic activity count */
	unsigned		uframe_periodic_max; /* max periodic time per uframe */
#endif

	/* 每個根集線器有一個 */
	U32    u32ResetEnd [EHCI_MAX_ROOT_PORTS];

	/* EHCI 控制器 registers */
	struct usb_hcd    hcd;
	struct ehci_cap_regs  *cap_regs;
	struct ehci_op_regs   *op_regs;
	U32      hcs_params;  /* cached register copy */

	/* EHCI 控制器 memory pools */
	struct ms_mem_pool    *pQhPool;  /* 一個 active urb 有一個 qh*/
	struct ms_mem_pool    *pQtdPool;  /* 一個 qh 有一個或更多個qtd*/
#ifdef ENABLE_EHCI_ISOC_PIPE
	struct ms_mem_pool    *itd_pool;  /* == itd per iso urb */
	struct ms_mem_pool    *sitd_pool;	/* sitd per split iso urb */
#endif

	struct timer_list  stWatchdog;
	struct timer_list  stiaa_Watchdog;
	U32    u32Actions;
	U32    u32Stamp;

	/* store EHCI IRQ status */
#ifdef EHCI_STATS
	struct ehci_irq_stats  stats;
#endif
	U32    ehci_port_not_change_cnt;
	U32    u32MoreCSC;
};

#ifdef EHCI_STATS
#define INCREASE(x) do { (x)++; } while (0)
#else
#define INCREASE(x) do {} while (0)
#endif

/* unwrap an HCD pointer to get an EHCI_HCD pointer */

//#define hcd_to_ehci(hcd_ptr) container_of(hcd_ptr, struct ehci_hcd, hcd)
static __inline__ struct ehci_hcd *hcd_to_ehci(struct usb_hcd *hcd_ptr)
{
	const struct usb_hcd *__mptr = (hcd_ptr);
	return (struct ehci_hcd *)( (char *)__mptr - (char *)offsetof(struct ehci_hcd,hcd) );
}

static __inline__ void
ms_iaa_watchdog_begin(struct ehci_hcd *ehci)
{
	//if (ms_timer_pending(&ehci->stiaa_Watchdog))
	//	diag_printf("iaa watchdog timer pending\n");
	//mod_timer(&ehci->iaa_watchdog,
	//		jiffies + msecs_to_jiffies(EHCI_IAA_MSECS));
	ms_update_timer (&ehci->stiaa_Watchdog, EHCI_IAA_MSEC, 0); // 20 ms
}

static __inline__ void
ms_iaa_watchdog_done(struct ehci_hcd *ehci)
{
	ms_del_timer(&ehci->stiaa_Watchdog,1);
}

enum ehci_timer_event {
	TIMER_IO_WATCHDOG,
	//TIMER_IAA_WATCHDOG, // NUSED
	TIMER_ASYNC_SHRINK,
	TIMER_ASYNC_OFF
};

static __inline__ void
ms_timer_action_done (struct ehci_hcd *ehci, enum ehci_timer_event eAction)
{
	ms_clear_bit (eAction, &ehci->u32Actions, U32);
}

static __inline__ void
ms_timer_action (struct ehci_hcd *ehci, enum ehci_timer_event eAction)
{
    if (ms_timer_pending(&ehci->stWatchdog)
            && (ms_test_bit(TIMER_ASYNC_SHRINK, &ehci->u32Actions) || ms_test_bit(TIMER_ASYNC_OFF, &ehci->u32Actions)))
            return;

    if (!ms_test_and_set_bit(eAction, &ehci->u32Actions))
    {
        U32 u32Time;

        switch (eAction)
        {
            case TIMER_IO_WATCHDOG:
              u32Time = EHCI_IO_JIFFIES;
              break;
            case TIMER_ASYNC_OFF:
              u32Time = EHCI_ASYNC_JIFFIES;
              break;
            default:
              u32Time = EHCI_SHRINK_JIFFIES;
              break;
        }
        /* Open watch dog to deal with the interrupt lost issue */
        //ehci->stWatchdog.base_jiffies = u32Time + jiffies; // NUSED
        ms_update_timer (&ehci->stWatchdog, u32Time, 0);
    }
}

/*-------------------------------------------------------------------------*/
struct ehci_cap_regs {
	unsigned char    caplength;          /* Capability Register Length */
	unsigned char    reserved;       /* [01h] */
	U16   hciversion;    /* HCIVERSION : [02h] */
	U32   hcsparams;     /* HCSPARAMS : [04h] */
	U32   hcc_params;    /* HCCPARAMS : [08h] */
	unsigned char    hcsp_portroute [8];   /* Companion Port Route Description : [0Ch] */
} __attribute__((packed));

/* HCSPARAMS : [04h] */
#define HCS_DBG_PORTS(p)  (((p)>>20)&0xf)
#define HCS_P_INDICATOR(p)((p)&(1 << 16))
#define HCS_N_CC(p)       (((p)>>12)&0xf) /* Number of Companion Controller */
#define HCS_N_PCC(p)      (((p)>>8)&0xf)  /* Number of Ports per Companion Controller */
#define HCS_PORT_ROUTE(p) ((p)&(1 << 7))   /* Port Routing Rules */
#define HCS_PPC(p)        ((p)&(1 << 4))   /* Port Power Control */
#define HCS_N_PORTS(p)    (((p)>>0)&0xf)

/* HCCPARAMS : [08h] */
#define HCC_ISO_CACHE(p)  ((p)&(1 << 7))   /* Cache isochronous entire frame*/
#define HCC_ISO_THRES(p)  (((p)>>4)&0x7)  /* Isochronous Scheduling Threshold */
#define HCC_ASPC(p)       ((p)&(1 << 2))   /* Asynchronous Schedule Park Capability. */
#define HCC_PFLF(p)       ((p)&(1 << 1))   /* Programmable Frame List Flag*/
#define HCC_64BIT_ADDR_CAP(p)  ((p)&(1))   /* 64-bit Addressing Capability */

/* Define for EHCI Spec Host Controller Operational Registers */

struct ehci_op_regs {

	U32    usbcmd;              /* USB Command : [00h] */
	U32    usbsts;              /* USB Status : [04h] */
	U32    usbintr;             /* USB Interrupt Enable : [08h] */
	U32    frindex;             /* USB Frame Index : [0Ch] */
	U32    ctrldssegment;       /* 4G Segment Selector: [10h] */
	U32    periodiclistbase;    /* Frame List Base Address : [14h] */
	U32    asynclistaddr;       /* Next Asynchronous List Address : [18h] */
	U32    reserved2;           /* reserve, [1Ch] */
	U32    portsc[1];           /* port status/control [20h], Faraday change*/
	U32    hcmisc;
	U32    reserved[2];
	/* Faraday specified register */
	U32    bus_control;             /* Bus monitor control : [30h] */

	U32    reserved1 [4];
} __attribute__((packed));

/* USB Command : [00h] */
#define USBCMD_PARK    (1<<11)   /* Asynchronous Schedule Park Mode Count */
#define USBCMD_PARK_CNT(c)  (((c)>>8)&3)  /* Asynchronous Schedule Park Mode Count */
//#define USBCMD_LRESET  (1<<7)    /* Light Host Controller Reset => NUSED */
#define USBCMD_IAAD    (1<<6)    /* Interrupt on Async Advance Doorbell */
#define USBCMD_ASE     (1<<5)    /* Asynchronous Schedule Enable */
#define USBCMD_PSE     (1<<4)    /* Periodic Schedule Enable */
#define USBCMD_RESET   (1<<1)    /* Host Controller Reset */
#define USBCMD_RUN     (1<<0)    /* Run/Stop HCD */

/* USB Status : [04h] */
#define USBSTS_ASS    (1<<15)    /* Asynchronous Schedule Status */
#define USBSTS_PSS    (1<<14)    /* Periodic Schedule Status */
#define USBSTS_RECL   (1<<13)    /* Reclamation */
#define USBSTS_HALT   (1<<12)    /* HCHalted */
#define USBSTS_IAA    (1<<5)     /* Interrupt on Async Advance */
#define USBSTS_FATAL  (1<<4)     /* Host System Error */
#define USBSTS_FLR    (1<<3)     /* Frame List Rollover */
#define USBSTS_PCD    (1<<2)     /* Port Change Detect */
#define USBSTS_ERR    (1<<1)     /* USB Error Interrupt (USBERRINT) */
#define USBSTS_INT    (1<<0)     /* USB Interrupt (USBINT) */

/* port status/control [20h], Faraday change*/
#define PORTSC_WKOC_E    (1<<22)  /* Wake on Over-current Enable */
#define PORTSC_WKDISC_E  (1<<21)  /* Wake on Disconnect Enable */
#define PORTSC_WKCONN_E  (1<<20)  /* Wake on Connect Enable */
#define PORTSC_OWNER     (1<<13)
#define PORTSC_POWER     (1<<12)
#define PORTSC_USBFS(x) (((x)&(3<<10))==(1<<10))  /* Indicate USB full speed device */
#define PORTSC_RESET    (1<<8)    /* Start bus reset */
#define PORTSC_SUSPEND  (1<<7)
#define PORTSC_RESUME   (1<<6)
#define PORTSC_OCC      (1<<5)    /* Over-current Change */
#define PORTSC_OC       (1<<4)    /* Over-current Active */
#define PORTSC_PEC      (1<<3)    /* Port Enable/Disable Change */
#define PORTSC_PE       (1<<2)    /* Port Enabled/Disabled */
#define PORTSC_CSC      (1<<1)    /* Connect Status Change */
#define PORTSC_CONNECT  (1<<0)    /* Current Connect Status */
#define PORTSC_RWC_BITS (PORTSC_CSC | PORTSC_PEC | PORTSC_OCC)

/* Bus monitor control : [30h] */
#define   HALF_SPEED      (1<<2)
#define   INT_POLAR       (1<<3)
#define   VBUS_OFF        (1<<4)

/*-------------------------------------------------------------------------*/

struct ehci_qtd {
	U32      hw_next_qtd;
	U32      hw_alt_next_qtd;
	U32      hw_token;
	U32      hw_buffer [5];

	/* the rest is HCD-private */
	dma_addr_t    qtd_dma_addr;    /* qtd address */
	struct list_head  qtd_list;    /* sw qtd list */
	struct urb    *urb;            /* qtd's urb */
	size_t      length;            /* length of buffer */
#if (_USB_128_ALIGMENT)
} __attribute__ ((aligned (128)));
#else
} __attribute__ ((aligned (32)));
#endif

/* qTD Token (DWord 2) */
#define  QTD_TOGGLE       ((U32)1 << 31)
#define  QTD_BYTES(t)     (((t)>>16) & 0x7fff)
#define  QTD_IOC          ((U32)1 << 15)
#define  QTD_CERR(t)      (((t)>>10) & 0x3)
#define  MAX_CERR_CNT      3    /* qtd error retry count is 0~3, if 0 qtd will not retry  */
#define  QTD_PID(t)       (((t)>>8) & 0x3)
#define  PID_OUT          (0 << 8)
#define  PID_IN           (1 << 8)
#define  PID_SETUP        (2 << 8)
#define  QTD_STS_ACT      ((U32)1 << 7)
#define  QTD_STS_HALT     ((U32)1 << 6)
#define  QTD_STS_DATERR   ((U32)1 << 5)
#define  QTD_STS_BABBLE   ((U32)1 << 4)
#define  QTD_STS_XACTERR  ((U32)1 << 3)
#define  QTD_STS_MISSMF   ((U32)1 << 2)
#define  QTD_STS_SPLITXST ((U32)1 << 1)
#define  QTD_STS_PERR     ((U32)1 << 0)

/* mask NakCnt+T in qh->hw_alt_next */
#define QTD_MASK (~0x1f)

#define IS_SHORT_READ(token) (QTD_BYTES (token) != 0 && QTD_PID (token) == 1)

/*-------------------------------------------------------------------------*/

#define Q_NEXT_TYPE(dma) ((dma) & (3 << 1))
#define Q_TYPE_ITD    (0 << 1)
#define QH_TYPE     (1 << 1)
#define Q_TYPE_SITD   (2 << 1)
#define Q_TYPE_FSTN   (3 << 1)
#define QH_NEXT(dma)  ((((U32)dma)&~0x01f)| QH_TYPE)

#define  EHCI_LIST_END  1

#ifdef ENABLE_EHCI_ISOC_PIPE
union ehci_shadow {
	struct ehci_qh     *qh;    /* == Q_TYPE_QH */
	struct ehci_itd    *itd;    /* == Q_TYPE_ITD */
	struct ehci_sitd  *sitd;    /* == Q_TYPE_SITD */
	//struct ehci_fstn  *fstn;    /* == Q_TYPE_FSTN */

	U32      *hw_next;
	void      *ptr; // page pointer
};
#else
union ehci_qh_shadow {
	struct ehci_qh     *qh;
	U32      *hw_next;
	void      *ptr; // page pointer
};
#define ehci_shadow ehci_qh_shadow
#endif

/*-------------------------------------------------------------------------*/
#define QH_MAX_XACTRTT_RETRY 32
struct ehci_qh {
	U32      hw_next_qh;
	U32      hw_ep_state1;
	U32      hw_ep_state2;
	U32      hw_current_qtd;
	U32      hw_next_qtd;
	U32      hw_alt_next_qtd;
	U32      hw_token;
	U32      hw_bufptr_lo [5];

	/* the rest is software HCD-private */
	dma_addr_t    qh_dma_addr;    /* address of qh */
	union ehci_qh_shadow  qh_next;  /* ptr to qh; or periodic */
	struct list_head  qtd_list;  /* sw qtd list */
	struct list_head	intr_node;	/* intr QHs new method */
	struct ehci_qtd    *pDummyQtd;
	struct ehci_qh    *pReclaimQh;
	atomic_t    tRefCnt;
	U32    u32Stamp;
	unsigned char      qh_status;
	U8 xacterrs;
	unsigned char      u8Usecs;
	unsigned char      u8Gap_uf;
	unsigned char      c_usecs;
	U16    u16Period;
	U16    u16Start;
#define NO_FRAME ((U16)~0)
	struct usb_device	*dev;		/* for TT */
#if (_USB_128_ALIGMENT)
} __attribute__ ((aligned (128)));
#else
} __attribute__ ((aligned (32)));
#endif

/* QH DWORD 2 */
#define	QH_SMASK	0x000000ff
#define	QH_CMASK	0x0000ff00

/* QH DWORD 1 */
#define QH_C_BIT	0x08000000 /* bit 27 */
#define QH_H_BIT	0x00008000 /* bit 15 */
#define QH_DTC_BIT	0x00004000 /* bit 14 */

/* qh status */
#define QH_STS_LINKED        1
#define QH_STS_UNLINK        2
#define QH_STS_IDLE          3
#define QH_STS_UNLINK_WAIT   4
#define QH_STS_COMPLETING    5

struct ehci_itd {
	/* first part defined by EHCI spec */
	U32			hw_next;	   /* see EHCI 3.3.1 */
	U32			hw_transaction [8]; /* see EHCI 3.3.2 */
#define EHCI_ISOC_ACTIVE        (1<<31)        /* activate transfer this slot */
#define EHCI_ISOC_BUF_ERR       (1<<30)        /* Data buffer error */
#define EHCI_ISOC_BABBLE        (1<<29)        /* babble detected */
#define EHCI_ISOC_XACTERR       (1<<28)        /* XactErr - transaction error */
#define	EHCI_ITD_LENGTH(tok)	(((tok)>>16) & 0x0fff)
#define	EHCI_ITD_IOC		(1 << 15)	/* interrupt on complete */

#define ITD_ACTIVE(ehci)	(EHCI_ISOC_ACTIVE)

	U32			hw_bufp [7];	/* see EHCI 3.3.3 */
	U32			hw_bufp_hi [7]; /* Appendix B */

	/* the rest is HCD-private */
	dma_addr_t		itd_dma;	/* for this itd */
	union ehci_shadow	itd_next;	/* ptr to periodic q entry */

	struct urb		*urb;
	struct ehci_iso_stream	*stream;	/* endpoint's queue */
	struct list_head	itd_list;	/* list of stream's itds */

	/* any/all hw_transactions here may be used by that urb */
	unsigned		frame;		/* where scheduled */
	unsigned		pg;
	unsigned		index[8];	/* in urb->iso_frame_desc */
#if (_USB_128_ALIGMENT)
} __attribute__ ((aligned (128)));
#else
} __attribute__ ((aligned (32)));
#endif

struct ehci_sitd {
	/* first part defined by EHCI spec */
	U32			hw_next;
/* uses bit field macros above - see EHCI 0.95 Table 3-8 */
	U32			hw_fullspeed_ep;	/* EHCI table 3-9 */
	U32			hw_uframe;		/* EHCI table 3-10 */
	U32			hw_results;		/* EHCI table 3-11 */
#define	SITD_IOC	(1 << 31)	/* interrupt on completion */
#define	SITD_PAGE	(1 << 30)	/* buffer 0/1 */
#define	SITD_LENGTH(x)	(0x3ff & ((x)>>16))
#define	SITD_STS_ACTIVE	(1 << 7)	/* HC may execute this */
#define	SITD_STS_ERR	(1 << 6)	/* error from TT */
#define	SITD_STS_DBE	(1 << 5)	/* data buffer error (in HC) */
#define	SITD_STS_BABBLE	(1 << 4)	/* device was babbling */
#define	SITD_STS_XACT	(1 << 3)	/* illegal IN response */
#define	SITD_STS_MMF	(1 << 2)	/* incomplete split transaction */
#define	SITD_STS_STS	(1 << 1)	/* split transaction state */

#define SITD_ACTIVE(ehci)	(SITD_STS_ACTIVE)

	U32			hw_buf [2];		/* EHCI table 3-12 */
	U32			hw_backpointer; 	/* EHCI table 3-13 */
	U32			hw_buf_hi [2];		/* Appendix B */

	/* the rest is HCD-private */
	dma_addr_t		sitd_dma;
	union ehci_shadow	sitd_next;	/* ptr to periodic q entry */

	struct urb		*urb;
	struct ehci_iso_stream	*stream;	/* endpoint's queue */
	struct list_head	sitd_list;	/* list of stream's sitds */
	unsigned		frame;
	unsigned		index;
#if (_USB_128_ALIGMENT)
} __attribute__ ((aligned (128)));
#else
} __attribute__ ((aligned (32)));
#endif

struct ehci_iso_packet {
	/* These will be copied to iTD when scheduling */
	MS_U64			bufp;		/* itd->hw_bufp{,_hi}[pg] |= */
	U32			transaction;	/* itd->hw_transaction[i] |= */
	U8			cross;		/* buf crosses pages */
	/* for full speed OUT splits */
	U32			buf1;
};

struct ehci_iso_sched {
	struct list_head	td_list;
	unsigned		span;
	struct ehci_iso_packet	packet [0];
};

struct ehci_iso_stream {
	/* first two fields match QH, but info1 == 0 */
	U32			hw_next;
	U32			hw_info1;

	U32			refcount;	/* linux 2.6.28 element */
	U8			bEndpointAddress;
	U8			highspeed;
	//U16			depth;		/* depth in uframes, 2.6.28 method */
	struct list_head	td_list;	/* queued itds/sitds */
	struct list_head	free_list;	/* list of unused itds/sitds */
	struct usb_device	*udev;
	struct usb_host_endpoint *ep;

	/* output of (re)scheduling */
	unsigned long		start;		/* jiffies,  linux 2.6.28 element */
	unsigned long		rescheduled;	/* linux 2.6.28 element */
	int			next_uframe;
	U32			splits;

	/* the rest is derived from the endpoint descriptor,
	 * trusting urb->interval == f(epdesc->bInterval) and
	 * including the extra info for hw_bufp[0..2]
	 */
	U8			usecs, c_usecs;
	U16			interval;
	U16			tt_usecs;
	U16			maxp;
	U16			raw_mask;
	unsigned		bandwidth;

	/* This is used to initialize iTD's hw_bufp fields */
	U32			buf0;
	U32			buf1;
	U32			buf2;

	/* this is used to initialize sITD's tt info */
	U32			address;
};

/*-------------------------------------------------------------------------*/
#define writel(data, reg_adr)              ( (*( (volatile MS_U32 *) (reg_adr) ) ) = ((MS_U32)data) )
#define readl(reg_adr)                     ( *( (volatile MS_U32 *) (reg_adr) ) )
#define writew(data, reg_adr)              ( (*( (volatile MS_U16 *) (reg_adr) ) ) = ((MS_U16)data) )
#define readw(reg_adr)                     ( *( (volatile MS_U16 *) (reg_adr) ) )
#define writeb(data, reg_adr)              ( (*( (volatile MS_U8 *) (reg_adr) ) ) = ((MS_U8)data) )
#define readb(reg_adr)                     ( *( (volatile MS_U8 *) (reg_adr) ) )

static inline unsigned int hcd_reg_readl(unsigned int regs)
{
	regs = ( (regs & 0xffffff00) + ((regs & 0x000000ff)*2) );
	return (readl((void*)(unsigned int)regs) & 0x0000ffff)|((readl((void*)((unsigned int)regs+4))<<16) & 0xffff0000);
}

static inline void hcd_reg_writel(const unsigned int val, unsigned int regs)
{
	regs = ((regs & 0xffffff00) + ((regs & 0x000000ff)*2)) ;
		writel(val & 0x0000ffff,(void*)regs) ;
		writel(((val>>16) & 0x0000ffff),(void*)((unsigned int)regs+4)) ;
}

static inline unsigned short hcd_reg_readw(unsigned int regs)
{
	//USB_ASSERT((regs & 0x1) == 0, "TRAP: hcd_reg_readw address not alignment !!\n");
	regs = ( (regs & 0xffffff00) + ((regs & 0x000000ff)*2) );
	return (readw((void*)(unsigned int)regs));
}

static inline unsigned char hcd_reg_readb(unsigned int regs)
{
	if (regs & 0x1)
		regs = ( (regs & 0xffffff00) + ((regs & 0x000000ff)*2)-1 );
	else
		regs = ( (regs & 0xffffff00) + ((regs & 0x000000ff)*2) );
	return (readb((void*)(unsigned int)regs));
}

/*-------------------------------------------------------------------------*/
/* drvEhciHcd.c */
extern int ms_ehci_init (struct usb_hcd *pHcd);
extern int ms_ehci_begin (struct usb_hcd *hcd);
extern int ms_urb_enqueue (struct usb_hcd *, struct urb *, int);
extern int ms_urb_dequeue (struct usb_hcd *, struct urb *, int);
extern void ms_ehci_end (struct usb_hcd *hcd);
extern int ms_ehci_get_frame_idx (struct usb_hcd *);
extern void ms_ehci_disable_ep (struct usb_hcd *, struct usb_host_endpoint *);
extern int ms_hub_status_data (struct usb_hcd *pHcd, char *pBuf);
extern int ms_ehci_hub_control (struct usb_hcd *, U16, U16, U16, char *);
extern void ms_ehci_softrst(struct ehci_hcd *);
extern void ms_ehci_periodic_size_init (struct usb_hcd *hcd);
extern void ms_ehci_irq (struct usb_hcd *pHcd);
extern struct list_head *ms_qh_urb_transaction_EHSET (struct ehci_hcd *ehci, struct urb *urb, struct list_head *head, int iFlags, int iStage);
extern int ms_submit_async_EHSET (struct ehci_hcd *ehci, struct urb *urb, struct list_head *qtd_list, int mem_flags);

#ifdef EHCI_TD_DEBUG
extern void dbg_timeout_async(struct usb_hcd *);
#endif
#endif
