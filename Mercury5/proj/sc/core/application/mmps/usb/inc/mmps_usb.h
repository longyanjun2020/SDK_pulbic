//==============================================================================
//
//  File        : mmps_usb.h
//  Description : Usb User Application Interface
//  Author      : Hans Liu
//  Revision    : 1.0
//
//==============================================================================
/**
 @file mmps_usb.h
 @brief Header File for the Host USB API.
 @author Hans Liu
 @version 1.0
*/

#ifndef _MMPS_USB_H_
#define _MMPS_USB_H_

#include "mmpd_usb.h"
#include "mmp_usbctl_inc.h"

/** @addtogroup MMPS_USB
@{
*/

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

#define PCSYNC_CTL_BUF_SIZE         (0x200)
#define PCSYNC_IN_BUF_SIZE          (0x20000)
#define PCSYNC_OUT_BUF_SIZE         (0x20000)
#define PCSYNC_HANDSHAKE_BUF_SIZE   (16)
#define PCSYNC_NAME_BUF_SIZE        (0x200)
#define PCSYNC_PARAM_BUF_SIZE       (0x400)

#define MTP_CTL_BUF_SIZE            (0x200)
#define MTP_EP_BUF_SIZE             (0x6200)
#define MTP_DRM_BUF_SIZE            (0xD034)
#define MTP_PCSYNC_IN_BUF_SIZE      (0x800)
#define MTP_PCSYNC_OUT_BUF_SIZE     (0x800)
#define MTP_HANDSHAKE_BUF_SIZE      (16)
#define MTP_NAME_BUF_SIZE           (0x200)
#define MTP_PARAM_BUF_SIZE          (0x2000)

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define USB_MSDC_MODE_BUF_START 0x170000
#define MMPS_USB_MODE_NUMBER    (7)

#define MMPS_USB_PRINTSERVICE_MASK      0xFFF0
#define MMPS_USB_PRINTSERVICE_PRINTING  0x0001
#define MMPS_USB_PRINTSERVICE_IDLE      0x0002
#define MMPS_USB_PRINTSERVICE_PAUSED    0x0004

#define MMPS_USB_ERRORSTATUS_MASK       0xFF0F
#define MMPS_USB_ERRORSTATUS_NO         0x0010
#define MMPS_USB_ERRORSTATUS_WARNING    0x0020
#define MMPS_USB_ERRORSTATUS_FATAL      0x0040

#define MMPS_USB_ERRORREASON_MASK       0xF0FF
#define MMPS_USB_ERRORREASON_NO         0x0000
#define MMPS_USB_ERRORREASON_PAPER      0x0100
#define MMPS_USB_ERRORREASON_INK        0x0200
#define MMPS_USB_ERRORREASON_HARDWARE   0x0400
#define MMPS_USB_ERRORREASON_FILE       0x0800

#define MMPS_USB_NEWJOBOK_MASK          0x0FFF
#define MMPS_USB_NEWJOBOK_FALSE         0x1000
#define MMPS_USB_NEWJOBOK_TRUE          0x2000

#define MemDevBufferSize1 32
#define MemDevBufferSize2 32

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMPS_USB_PTP_OBJ
{
    MMP_USHORT OpCode;
    MMP_ULONG SessionID;
    MMP_ULONG TransactionID;
    MMP_ULONG para[5];
} MMPS_USB_PTP_OBJ;

typedef struct
{
  MMP_ULONG     ulFileID;       ///< file id
  MMP_ULONG     ulCopies;       ///< copies
  MMP_UBYTE     ubQuality;      ///< quality
  MMP_UBYTE     ubPaperSize;    ///< paper size
  MMP_UBYTE     ubPaperType;    ///< paper type
  MMP_UBYTE     ubFileType;     ///< file type
  MMP_UBYTE     ubDatePrint;    ///< data print
  MMP_UBYTE     ubFileNamePrint;///< file name print
  MMP_UBYTE     ubImageOptimize;///<image optimize
  MMP_UBYTE     ubLayout;       ///< layout
  MMP_UBYTE     ubFixedSize;    ///<fixed size
  MMP_BYTE      bFilePath[100]; ///<file path
} MMPS_USB_DPS_PRINT_INFO;

typedef struct{
    MMP_ERR (*DevOpen)(MMP_ULONG id);
    MMP_ERR (*DevClose)(MMP_ULONG id);
    MMP_ERR (*DevGetSize)(MMP_ULONG id, MMP_ULONG *TotalSec, MMP_ULONG *SecSize);
    MMP_ERR (*DevRead)(MMP_ULONG id, MMP_ULONG startSec, MMP_ULONG SecLen, void * buf);
    MMP_ERR (*DevWrite)(MMP_ULONG id, MMP_ULONG startSec, MMP_ULONG SecLen, void * buf);
} MMPS_USB_FUNC;

typedef struct usb_ptpstruct
{
  MMP_BOOL bInitialized;
  void *pVendorState;
} MMPS_USB_PTP_STATE;

//==============================================================================
//
//                              ENUMERATIONS
//
//==============================================================================

typedef enum
{
    MMPS_USB_NORMAL,
    MMPS_USB_ISADAPTER,
    MMPS_USB_IDLE
} MMPS_USB_StatusMode;

typedef enum _MMPS_USB_OP_MODE
{
    MMPS_USB_NONE_MODE = 0x0,
    MMPS_USB_PCCAM_MODE,        ///< PCCAM
    MMPS_USB_MSDC_MODE,         ///< MSDC
    MMPS_USB_DPS_MODE,           ///< PICTURE BRIDGE
    MMPS_USB_PTP_MODE,
    MMPS_USB_PCSYNC_MODE,       ///< PCSYNC
    MMPS_USB_MTP_MODE,          ///< MTP
    MMPS_USB_DETECT_MODE,       /// for device detection
    MMPS_USB_ISOTEST_MODE,      //for test USB HB iso-mode
    MMPS_USB_ADAPTER_MODE,      //for USB adapter or Charger used
#if (SUPPORT_MSDC_SCSI_AIT_CMD_MODE)
    MMPS_USB_MSDC_AIT_DEBUG_MODE, //for MSDC SCSI vendor command mode.
#endif
    MMPS_USB_MAX_MODE
} MMPS_USB_OP_MODE;

// DPS setting
typedef enum _MMPS_USB_DPS_QUALITY
{
    MMPS_USB_DPS_QUALITY_DEFAULT = 0,
    MMPS_USB_DPS_QUALITY_NORMAL,
    MMPS_USB_DPS_QUALITY_DRAFT,
    MMPS_USB_DPS_QUALITY_FINE
} MMPS_USB_DPS_QUALITY;

typedef enum _MMPS_USB_DPS_PAPERSIZE
{
    MMPS_USB_DPS_PAPERSIZE_DEFAILT  = 0x00,
    MMPS_USB_DPS_PAPERSIZE_L        = 0x01,
    MMPS_USB_DPS_PAPERSIZE_2L       = 0x02,
    MMPS_USB_DPS_PAPERSIZE_POSTCARD = 0x03,
    MMPS_USB_DPS_PAPERSIZE_CARDSIZE = 0x04,
    MMPS_USB_DPS_PAPERSIZE_100X150  = 0x05,
    MMPS_USB_DPS_PAPERSIZE_4X6      = 0x06,
    MMPS_USB_DPS_PAPERSIZE_8X10     = 0x07,
    MMPS_USB_DPS_PAPERSIZE_A4       = 0x08,
    MMPS_USB_DPS_PAPERSIZE_LETTER   = 0x09,
    MMPS_USB_DPS_PAPERSIZE_A6       = 0x0A,
    MMPS_USB_DPS_PAPERSIZE_LROLL    = 0x81,
    MMPS_USB_DPS_PAPERSIZE_2LROLL   = 0x82,
    MMPS_USB_DPS_PAPERSIZE_100ROLL  = 0x86,
    MMPS_USB_DPS_PAPERSIZE_A4ROLL   = 0x88
} MMPS_USB_DPS_PAPERSIZE;

typedef enum _MMPS_USB_DPS_PAPERTYPE
{
    MMPS_USB_DPS_PAPERTYPE_DEFAULT   =  0x00,
    MMPS_USB_DPS_PAPERTYPE_PLAIN,
    MMPS_USB_DPS_PAPERTYPE_PHOTO,
    MMPS_USB_DPS_PAPERTYPE_FASTPHOTO
} MMPS_USB_DPS_PAPERTYPE;

typedef enum _MMPS_USB_DPS_FILETYPE
{
    MMPS_USB_DPS_FILETYPE_DEFAULT = 0x00,
    MMPS_USB_DPS_FILETYPE_EXIF,
    MMPS_USB_DPS_FILETYPE_JPEG,
    MMPS_USB_DPS_FILETYPE_TIFFEP,
    MMPS_USB_DPS_FILETYPE_FLASHPIX,
    MMPS_USB_DPS_FILETYPE_BMP,
    MMPS_USB_DPS_FILETYPE_CIFF,
    MMPS_USB_DPS_FILETYPE_GIF,
    MMPS_USB_DPS_FILETYPE_JFIF,
    MMPS_USB_DPS_FILETYPE_PCD,
    MMPS_USB_DPS_FILETYPE_PICT,
    MMPS_USB_DPS_FILETYPE_PNG,
    MMPS_USB_DPS_FILETYPE_TIFF,
    MMPS_USB_DPS_FILETYPE_TIFFIT,
    MMPS_USB_DPS_FILETYPE_JP2,
    MMPS_USB_DPS_FILETYPE_JPX
} MMPS_USB_DPS_FILETYPE;

typedef enum _MMPS_USB_DPS_DATAPRINT
{
    MMPS_USB_DPS_DATEPRINT_DEFAULT = 0x00,
    MMPS_USB_DPS_DATEPRINT_OFF,
    MMPS_USB_DPS_DATEPRINT_ON
} MMPS_USB_DPS_DATAPRINT;

typedef enum _MMPS_USB_DPS_FILENAMEPRINT
{
    MMPS_USB_DPS_FILENAMEPRINT_DEFAULT = 0x00,
    MMPS_USB_DPS_FILENAMEPRINT_OFF,
    MMPS_USB_DPS_FILENAMEPRINT_ON
} MMPS_USB_DPS_FILENAMEPRINT;

typedef enum _MMPS_USB_DPS_IMAGEOPTIMIZE
{
    MMPS_USB_DPS_IMAGEOPTIMIZE_DEFAULT = 0x00,
    MMPS_USB_DPS_IMAGEOPTIMIZE_OFF,
    MMPS_USB_DPS_IMAGEOPTIMIZE_ON
} MMPS_USB_DPS_IMAGEOPTIMIZE;

typedef enum _MMPS_USB_DPS_LAYOUT
{
    MMPS_USB_PS_LAYOUT_DEFAULT     =    0x00,
    MMPS_USB_PS_LAYOUT_1U          =    0x01,
    MMPS_USB_PS_LAYOUT_2U          =    0x02,
    MMPS_USB_PS_LAYOUT_3U          =    0x03,
    MMPS_USB_PS_LAYOUT_4U          =    0x04,
    MMPS_USB_PS_LAYOUT_5U          =    0x05,
    MMPS_USB_PS_LAYOUT_6U          =    0x06,
    MMPS_USB_PS_LAYOUT_7U          =    0x07,
    MMPS_USB_PS_LAYOUT_8U          =    0x08,
    MMPS_USB_PS_LAYOUT_9U          =    0x09,
    MMPS_USB_PS_LAYOUT_10U         =    0x0A,
    MMPS_USB_PS_LAYOUT_11U         =    0x0B,
    MMPS_USB_PS_LAYOUT_12U         =    0x0C,
    MMPS_USB_PS_LAYOUT_13U         =    0x0D,
    MMPS_USB_PS_LAYOUT_14U         =    0x0E,
    MMPS_USB_PS_LAYOUT_15U         =    0x0F,
    MMPS_USB_PS_LAYOUT_16U         =    0x10,
    MMPS_USB_PS_LAYOUT_INDEX       =    0xFE,
    MMPS_USB_PS_LAYOUT_BORDERLESS  =    0xFF
}MMPS_USB_DPS_LAYOUT;

typedef enum _MMPS_USB_DPS_FIXEDSIZE
{
    MMPS_USB_DPS_FIXEDSIZE_DEFAULT = 0x00,
    MMPS_USB_DPS_FIXEDSIZE_2X3,
    MMPS_USB_DPS_FIXEDSIZE_3X5,
    MMPS_USB_DPS_FIXEDSIZE_4X6,
    MMPS_USB_DPS_FIXEDSIZE_5X7,
    MMPS_USB_DPS_FIXEDSIZE_8X10,
    MMPS_USB_DPS_FIXEDSIZE_254,
    MMPS_USB_DPS_FIXEDSIZE_110,
    MMPS_USB_DPS_FIXEDSIZE_89,
    MMPS_USB_DPS_FIXEDSIZE_100,
    MMPS_USB_DPS_FIXEDSIZE_6,
    MMPS_USB_DPS_FIXEDSIZE_7,
    MMPS_USB_DPS_FIXEDSIZE_9,
    MMPS_USB_DPS_FIXEDSIZE_10,
    MMPS_USB_DPS_FIXEDSIZE_13,
    MMPS_USB_DPS_FIXEDSIZE_15,
    MMPS_USB_DPS_FIXEDSIZE_18,
    MMPS_USB_DPS_FIXEDSIZE_A4,
    MMPS_USB_DPS_FIXEDSIZE_LETTER
}MMPS_USB_DPS_FIXEDSIZE;

typedef enum _MMPS_USB_DPS_CROPPING
{
    MMPS_USB_DPS_CROPPING_DEFAULT = 0x00,
    MMPS_USB_DPS_CROPPING_OFF,
    MMPS_USB_DPS_CROPPING_ON
}MMPS_USB_DPS_CROPPING;


#define MMPS_USB_DPSHOSTBUF 0x0001
#define MMPS_USB_DPSBUFEND  0x0002

typedef enum _MMPD_USB_PCSYNC_INSTATUS
{
    MMPS_USB_PCSYNC_IN_EMPTY = 0,       ///< in empty
    MMPS_USB_PCSYNC_IN_DATA_READY = 2   ///< in data ready
} MMPS_USB_PCSYNC_INSTATUS;

typedef enum _MMPD_USB_PCSYNC_OUTSTATUS
{
    MMPS_USB_PCSYNC_OUT_EMPTY = 0,      ///< out empty
    MMPS_USB_PCSYNC_OUT_DATA_READY      ///< out data ready
} MMPS_USB_PCSYNC_OUTSTATUS;

typedef enum {
    MMPS_USB_MEMDEV_INIT,
    MMPS_USB_MEMDEV_RESET,
    MMPS_USB_MEMDEV_GETINFO,
    MMPS_USB_MEMDEV_READ,
    MMPS_USB_MEMDEV_WRITE,

    MMPS_USB_MEMDEV_ERR = 0xFF
} MMPS_USB_MEMDEV_CMD;

typedef enum {
    ACK_FALSE,
    ACK_TRUE
} ACK_TYPE;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#ifdef MSDC_WR_FLOW_TEST_EN
extern MMP_ERR MMPD_USB_SetMSDCWriteBuf(MMP_ULONG, MMP_ULONG);
#endif

extern MMP_ERR  MMPS_USB_AdjustVref(MMP_USBPHY_VREF Vref);
extern MMP_ERR  MMPS_USB_AdjustBiasCurrent(MMP_USBPHY_BIAS_CURRENT BiasCurrent);
extern MMP_ERR  MMPS_USB_AdjustSignal(MMP_USBPHY_TX_CUR TxCur,
                                      MMP_USBPHY_TX_CUR_PLUS TxCurPlus,
                                      MMP_USBPHY_SQ SqLevel);
extern MMP_ERR  MMPS_USB_RegisterCallback(MMP_USB_EVENT event,
                                          MMP_USB_Callback *callback);
extern MMP_ERR  MMPS_USB_SetMode(MMPS_USB_OP_MODE ubMode);
extern MMP_ERR  MMPS_USB_GetMode(MMPS_USB_OP_MODE *UsbCurMode);
extern MMP_ERR  MMPS_USB_StopDevice(void);
extern MMP_ERR  MMPS_USB_SetConnect(MMP_BOOL bSetConnect);
extern MMP_ERR  MMPS_USB_ReadPCSYNCInData(MMP_UBYTE *ubMemStart,MMP_ULONG *ulReadSize);
extern MMP_ERR  MMPS_USB_WritePCSYNCOutData(MMP_UBYTE *ubMemStart,MMP_ULONG ulWriteSize);
extern MMPS_USB_StatusMode MMPS_USB_GetStatus(void);
extern MMPS_USB_StatusMode MMPS_USB_GetLastStatus(void);

extern MMP_BOOL MMPS_USB_DetectVBus5V(void);
extern void MMPS_USB_DetectAdaptorOrUSB(void);
extern MMP_UBYTE MMPS_USB_GetWriteFlag(void);
extern MMP_UBYTE MMPS_USB_GetReadFlag(void);
extern MMP_ERR MMPS_USB_DisconnectDevice(void);
/* MSDC related functions */
extern MMP_ERR MMPS_USBMSDC_SetMaxUnitNum(MMP_UBYTE ubMaxUnitCnt);

extern MMP_ERR MMPS_USB_GetMSDC_SCSIBufferSize(MMP_ULONG *pscsi_buf_size, MMP_ULONG *pctl_buf_size);
extern MMP_ERR MMPS_USB_SetMSDC_SCSIBuffer(MMP_ULONG ulscsi_buf, MMP_ULONG ulctl_buf);
extern MMP_ERR MMPS_USB_SetDBGBuffer(MMP_ULONG uldbg_buf, MMP_ULONG uldbg_size);
/* USB HOST related functions */
extern MMP_ERR MMPS_USB_RegDetectCallBack(void *pReadUSBIDTimeoutCallback, void *pOtgSessionTimeoutCallback, void *pDevConnCallback, void *pDevDisconnCallback);
extern MMP_ERR MMPS_USB_TriggerReadUSBID(MMP_ULONG *pulTimerId);
extern MMP_ERR MMPS_USB_ReadUSBID(MMP_UBYTE *pubDevType);
extern MMP_ERR MMPS_USB_StartOTGSession(MMP_ULONG *pulTimerId);
extern MMP_ERR MMPS_USB_StopOTGSession(void);
extern MMP_ERR MMPS_USB_GetDevConnSts(MMP_BOOL *pbStatus);
extern MMP_ERR MMPS_USB_SetDevConnSts(MMP_BOOL pbStatus);
extern MMP_ERR MMPS_USB_EnumUVC(void);
extern MMP_ERR MMPS_USB_GetUVCStreamSts(MMP_BOOL *pbStatus);
extern MMP_ERR MMPS_USB_RegUVCMDCallBack(void *pDevTriggerMDCallback);
extern MMP_ERR MMPS_USB_EnableUVCMD(void);
extern MMP_ERR MMPS_USB_DisableUVCMD(void);
extern MMP_ERR MMPS_USB_SetCheckDevAliveCFG(MMP_ULONG pulCheckDevAliveInterval, void *pDevNoResponseCallback);
extern MMP_ERR MMPS_USB_SetTranTimeoutCFG(MMP_ULONG pulTranTimeoutInterval, void *pDevTranTimeoutCallback);
extern MMP_ERR MMPS_USB_SetFrmRxTimeoutCFG(MMP_ULONG pulFrmRxLostTH, MMP_ULONG pulFrmRxFirstAddGap, void *pDevFrmRxLostTHCallback);
extern MMP_ERR MMPS_USB_SetFrmRxTimeout2CFG(MMP_ULONG pulFrmRxLostTH2, void *pDevFrmRxLostTH2Callback);
extern MMP_ERR MMPS_USB_SetFrmSeqNoLostCFG(MMP_ULONG pulSeqNoLostTH, void *pDevSeqNoLostTHCallback);
extern MMP_ERR MMPS_USB_StopFrmRxClrFIFO(void);
extern MMP_ERR MMPS_USB_SetDropRxFrmCFG(MMP_ULONG ulTotalCnt, MMP_ULONG ulContinCnt, void *pDropRxFrmCallback);

/// @}

#endif // _MMPS_USB_H_
