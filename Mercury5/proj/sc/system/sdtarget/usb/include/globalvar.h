///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   globalvar.h
/// @author MStar Semiconductor Inc.
/// @brief  global variable definition header file
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GOLBALVAR_H
#define _GOLBALVAR_H
//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "ms_compiler.h"
#include "stdcomp.h"


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Typedefs
//-------------------------------------------------------------------------------------------------
// USB device mode definition
typedef enum
{
    E_USB_MassStorage = 0,
    E_USB_VirtCOM = 1,
    E_USB_Modem = 2,
    E_USB_PCCAM = 3,
    E_USB_PictureBridge = 4,
    E_USB_OTG = 5
} USB_DEVICE_MODE;

struct devrequest
{
    U8 bmRequestType;
    U8 bRequest;
    U16 wValue;
    U16 wIndex;
    U16 wLength;
};

typedef struct
{
    U16   FIFOSize;
    U16   MaxEPSize;
    U16   FifoRemain;
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

typedef struct vendorCmdStruct_t
{
    U32  totDwldBytes;
    U32  currDwldBytes;
    U32  currUpldBytes;
    U32  currUpldOffset;
    U32  accReadBytes;
    U32  dataBuf_CB;
    U16  PPB2Buf_CB;
    U16  errCode;
    U8   bDwldEnd;
    U8   bUpldStart;
    U8   *ucptrDataBuf;      /* Uncached pointer to data buffer */
    U8   *ptrPPB2Buf;
    U8   *ptrTmpHifBuf;
} vendorCmdStruct;

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
    struct vendorCmdStruct_t volatile   *ptrVCmdStruct;
    U8  volatile    *USB_Msdfn_Dscr;
    U32 volatile    SizeofUSB_Msdfn_Dscr;
}   USB_VAR;

void Clear_TestUnitReady_Flag(void);
bool Get_TestUnitReady_Flag(void);
bool Get_BusResetInMSDFNCMDloop_Flag(void);

//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------

#endif // _GOLBALVAR_H
