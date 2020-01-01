#include "type.h"
#include "sys_sys.h"


#define USB_PID_OUT                 0xe1
#define USB_PID_ACK                 0xd2
#define USB_PID_IN                  0x69
#define USB_PID_STALL               0x1e

#define USB_ST_NOERROR                  0
#define USB_ST_NORESPONSE               0xfc
#define USB_ST_STALL                    0xec


#define usb_pipeout(pipe)       ((((pipe) >> PIPEDEF_DIR) & 1) ^ 1)
#define usb_pipein(pipe)        (((pipe) >> PIPEDEF_DIR) & 1)
#define usb_pipeendpoint(pipe)  (((pipe) >> PIPEDEF_EP) & 0xf)
#define usb_pipetype(pipe)      (((pipe) >> PIPEDEF_ATTR) & 3)
//#define usb_pipeisoc(pipe)      (usb_pipetype((pipe)) == PIPE_ISOCHRONOUS)
#define usb_pipebulk(pipe)      (usb_pipetype((pipe)) == PIPE_BULK)

#define usb_sndctrlpipe(endpoint)       ((PIPE_CONTROL << PIPEDEF_ATTR) | \
        (PIPE_OUT << PIPEDEF_DIR) | (((endpoint) << PIPEDEF_EP) &0xf))

#define usb_rcvctrlpipe(endpoint)       ((PIPE_CONTROL << PIPEDEF_ATTR) | \
        (PIPE_IN  << PIPEDEF_DIR) | (((endpoint) << PIPEDEF_EP) &0xf))

#define usb_sndbulkpipe(endpoint)       ((PIPE_BULK << PIPEDEF_ATTR) | \
        (PIPE_OUT << PIPEDEF_DIR) | (((endpoint) << PIPEDEF_EP) &0xf))

#define usb_rcvbulkpipe(endpoint)       ((PIPE_BULK << PIPEDEF_ATTR) | \
        (PIPE_IN << PIPEDEF_DIR) | (((endpoint) << PIPEDEF_EP) &0xf))


#define USB_TYPE_MASK                   (0x03 << 5)
#define USB_TYPE_STANDARD               (0x00 << 5)
#define USB_TYPE_CLASS                  (0x01 << 5)
#define USB_TYPE_VENDOR                 (0x02 << 5)
#define USB_TYPE_RESERVED               (0x03 << 5)

#define USB_RECIP_MASK                  0x1f
#define USB_RECIP_DEVICE                0x00
#define USB_RECIP_INTERFACE             0x01
#define USB_RECIP_ENDPOINT              0x02
#define USB_RECIP_OTHER                 0x03

/*
 * Standard requests
 */
#define USB_REQ_GET_STATUS                  0x00
#define USB_REQ_CLEAR_FEATURE           0x01
#define USB_REQ_SET_FEATURE                 0x03
#define USB_REQ_SET_ADDRESS                 0x05
#define USB_REQ_GET_DESCRIPTOR          0x06
#define USB_REQ_SET_DESCRIPTOR          0x07
#define USB_REQ_GET_CONFIGURATION       0x08
#define USB_REQ_SET_CONFIGURATION       0x09
#define USB_REQ_GET_INTERFACE           0x0A
#define USB_REQ_SET_INTERFACE           0x0B
#define USB_REQ_SYNCH_FRAME                 0x0C

/*
 * USB Set Features
 */
#define	ENDPOINT_HALT			        0x00
#define	DEVICE_REMOTE_WAKEUP		    0x01
#define	TEST_MODE			            0x02

#define	b_hnp_enable			0x03
#define	a_hnp_support			0x04
#define	a_alt_hnp_support		0x05

#define USB_DT_DEVICE                   0x01
#define USB_DT_CONFIG                   0x02
#define USB_DT_STRING                   0x03
#define USB_DT_INTERFACE                0x04
#define USB_DT_ENDPOINT                 0x05
#define USB_DT_DEVICE_QUALIFIER         0x06
#define USB_DT_OTHER_SPEED                  0X07

/* MSD BOT Functional Characteristics */
#define MSDFN_BOT_RESET               0xFF
#define MSDFN_BOT_GET_MAXLUN          0xFE


#define USB_POWERED     1   /* CONNECT int in, Reset pending */
#define USB_DEFAULT     2   /* CONNECT in, Reset completed */
#define USB_ADDRESS     3   /* Above,+ peripheral SET_ADDRESS completed */
#define USB_CONFIGURED  4   /* Above,+ enumeration completed. OK for traffic*/

#define IRC_INTRUSB 0   /* 2 possible cause codes:INTRUSB ... */
#define IRC_EP      1   /* or an endpoint */

#define EP_TX       0x00            /* set endpoint to TX only, no status */
#define EP_RX       0x01            /* set endpoint to RX only, no status */
#define EP_TXST     0x02            /* set status in TX direction */
#define EP_RXST     0x03            /* set status in RX direction */
#define EP_IDLE     0x02            /* peripheral only! 2nd bit set is idle */

#define GETLSB(x)   ((x) & 0xff)
#define GETMSB(x)   GETLSB((x)>>8)
#define SWOP(X)  (X = X)
#define usb_pipeendpoint(pipe)  (((pipe) >> PIPEDEF_EP) & 0xf)

#define     FIFO_TX             0           /* endpoint fifo is TX only */
#define     FIFO_RX             1           /* endpoint fifo is RX only */
#define     FIFO_DUAL           2           /* endpoint fifo is TX or RX */
#define     FIFO_DPB            16          /* double packet buffering */
#define     FIFO_ERROR          256

#define LOW_SPEED       3
#define FULL_SPEED      1
#define HIGH_SPEED      2


typedef	U8	pipe_t;

typedef enum
{
    E_USB_MassStorage = 0,
    //E_USB_VirtCOM = 1,
    //E_USB_Modem = 2,
    E_USB_PCCAM = 3,
    //E_USB_PictureBridge = 4,
    //E_USB_OTG=5
	E_USB_DETECT=6
} USB_DEVICE_MODE;


typedef    struct
{
    U16  IReg;     /* holds content of INTRUSB|CSR0|TXCSR1|RXCSR1 */
    U16  ICount;   /* 8-bit COUNT holds bits 0-7 for RX EP */
    U8   IIntSrc;  /* 0=TXInt,1=Rxint for EP interrupts */
    U8   ICause;   /* 0=INTRUSB, 1=EP */
    U8   InUse;    /* 0=free,1=holds interrupt data */
    U8   IDMA;     /* set if DMA interrupt */
    U8   IDummy;   /* unclaimed,use at will */
    U8   IEP;      /* identifies the EP when EP is source of int */
}   drcintitem_t;

struct devrequest{
	U8 bmRequestType;
	U8 bRequest;
	U16 wValue;
	U16 wIndex;
	U16 wLength;
};

struct videoprobe {
	U16  bmHint;
	U16  wIndex; //H byte -> Format Index, L Byte -> Frame Index
	U16  wIntervalLo;
	U16  wIntervalHi;
	U16  wKeyFrameRate;
	U16  wPFrameRate;
	U16  wCompQuality;
	U16  wCompWinSize;
	U16  wDelay;
	U16  wMaxFrameSizeLo;
	U16  wMaxFrameSizeHi;
	U16  wMaxPayloadSizeLo;
	U16  wMaxPayloadSizeHi;
};


typedef struct
{
    U16   FIFOSize;
    U16   MaxEPSize;
    U32   FifoRemain;
    U32   BytesRequested;
    U32   BytesProcessed;
    U8    DRCInterval;
    U8    intr_flag;
    U8    pipe;
    U8    BltEP;
    U8    DRCDir;
    U8    LastPacket;
    U8    IOState;
    U8    Halted;
    U8    Infnum;
    U32   transfer_buffer;
    U32   transfer_buffer_length;
    U8     BltEP2;
}   endpoint_t;

typedef struct USB_VAR_
{
    U8  volatile    otgPerMassmax_Lun;
    U8  volatile    otgSD_LUN;
    U8  volatile    otgNAND_LUN;
    U8  volatile    otgSetFaddr;
    U8  volatile    otgClearedEP;
    U8  volatile    otgMyDeviceHNPSupport;
    U8  volatile    free_dma_channels;
    U8  volatile    otgResetComplete;
    U16 volatile    otgTestMode;
    U16 volatile    otgGetStatusResponse;
    U32 volatile    otgCSW_Addr;
    U32 volatile    otgSetupCmdBuf_Addr;
    U32 volatile    otgCBWCB_Addr;
    U8  volatile    otgRegPower;
    U8  volatile    otgIntStatus;
    U8  volatile    otgDMARXIntStatus;
    U8  volatile    otgDMATXIntStatus;
    U8  volatile    otgDataPhaseDir;
    U8  volatile    otgMassCmdRevFlag;
    U8  volatile    otgMassRxDataReceived;
    U8  volatile    otgReqOTGState;
    U8  volatile    otgCurOTGState;
    U8  volatile    otgSuspended;
    U8  volatile    otgRemoteWakeup;
    U8  volatile    otgHNPEnabled;
    U8  volatile    otgHNPSupport;
    U8  volatile    otgConfig;
    U8  volatile    otgInterface;
    U8  volatile    otgUSBState;
    U8  volatile    otgcid;
    U8  volatile    otgFaddr;
    U8  volatile    otgRegDevCtl;
    U8  volatile    otgSpeed;
    U16 volatile    otgSOF_1msCount;
    U8  volatile    u8USBDeviceMode;
    U8  volatile    DeviceConnect;
    U8  volatile    u8USBDevMode;
    U8  volatile    otgFSenseKey;
    U8  volatile    otgFASC;
    U8  volatile    otgFASCQ ;
    U8  volatile    otgdataXfer_dir;
    U8  volatile    otgStop;
    S32 volatile    otgfun_residue;
    U32 volatile    otgactualXfer_len;
    endpoint_t volatile otgUSB_EP[4];
    struct devrequest volatile otgEP0Setup;
    U8  volatile    UsbSetupCmdBuf[32];
    U8  volatile    UsbCSWBuf[(13+3)];
    U8  volatile    UsbCBWBuf[(31+1)];
    U8  volatile    *ucptrDataBuf;      /* Uncached pointer to data buffer */
    //struct vendorCmdStruct_t volatile   *ptrVCmdStruct;
    //U8  volatile    *USB_Msdfn_Dscr;
    //U32 volatile    SizeofUSB_Msdfn_Dscr;

}   USB_VAR;
    
extern USB_VAR gUSBVar;

