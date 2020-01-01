#ifndef _MS_MDL_USB_MAIN_H_
#define _MS_MDL_USB_MAIN_H_

//#define _USBMMLTEST
//#define _USBWHITEBOX
#include "mdl_usb_pub.h"

typedef enum
{
    /* Genie */
    EVENT_USBGENIE_READ_DONE=0,             ///< Reading data from PC is completed
    EVENT_USBGENIE_WRITE_DONE,            ///< Writing data to PC is completed
    EVENT_USBGENIE_CONNECTED,             ///< Virtual COM port is connected to PC
    EVENT_USBGENIE_DISCONNECTED,
   // EVENT_USBCDC_SET_LINESTATE,
    //EVENT_USBCDC_SET_LINECODING,

} USBFUNGENIEEVENT_e;

#define    EVENT_PC_SUSPEND    0
#define    EVENT_PC_RESUME	   1
#define    EVENT_PC_REMOVE	   2


#define    USB_MassStorage   0
#define    USB_VirtCOM       1
#define    USB_Modem         2
#define    USB_PCCAM         3
#define    USB_PictureBridge 4
#define    USB_OTG           5
#define    USB_ReadSts       6

//-----------------------------------------------------------------------------
// Macro Definition
//-----------------------------------------------------------------------------
#define USBMsg_t                                vm_msg_t
#define USB_MALLOC(Type_t, nSize)                       ((Type_t *)MsAllocateMem(nSize))
#define USB_MFREE(pMem)                                     MsReleaseMemory((void **)&pMem)
#define USB_MEMSET(pMem, nVal, nSize)               memset(pMem, nVal, nSize)
#define USB_MEMCPY(pDst, pSrc, nSize)                   memcpy(pDst, pSrc, nSize)
#define USB_MEMCMP(pMem1, pMem2, nSize)         memcmp(pMem1, pMem2, nSize)
#define USB_SENDMSG(eMailbox, pMsg)                 MsSend(eMailbox, pMsg)

////////////////////////////
#ifdef EnterPrint
#define ENTER_MSG(fmt, args...)                               \
        {                                                     \
            diag_printf("[%s] (%d) ", __FUNCTION__,__LINE__); \
            diag_printf(fmt, ##args);                         \
        }
#else
#define ENTER_MSG(fmt, args...)
#endif
//#define USB_PC_REMOVED 1

s32 MdlUsbMainUseCaseGetStatus(void);
void MdlUsbMainUseCaseGetStatusCB(u16 nPcAttach);
s32 MdlUsbMainUseCaseOpenDevice(u8 nDevMode);
s32 MdlUsbMainUseCaseCloseDevice(void);
#if 0
typedef enum
{
    /* Virtual COM */
    EVENT_USBCDC_READ_DONE=0,             ///< Reading data from PC is completed
    EVENT_USBCDC_WRITE_DONE,            ///< Writing data to PC is completed
    EVENT_USBCDC_CONNECTED,             ///< Virtual COM port is connected to PC
    EVENT_USBCDC_DISCONNECTED,
    EVENT_USBCDC_SET_LINESTATE,
    EVENT_USBCDC_SET_LINECODING,

} USBFUNCDCEVENT_e;
s32 MdlUsbMainCdcCallbackRegister(u8 nUsbEvent, void *pfUsbFun);
s32 MdlUsbMainCdcCallbackUnRegister(u8 nUsbEvent);
void MdlUsbMainCdcRead(u8* pRbuffer, u16* pwAmount, u16 nMax);
s32 MdlUsbMainCdcWrite(u8 *pWbuffer, u16 nLen);
s32 MdlUsbMainCdcSerialStateNotifify(u16 nCdcNotification);
void MdlUsbMainCdcGetLineCoding(void* pLineCoding);
void MdlUsbMainTaskInit(void);
void MdlUsbMainTaskParseMsg(void *pMessage);
#endif
s32 MdlUsbMainCdcMuxCallbackRegister(u8 nUsbEvent, void *pfUsbFun);
s32	MdlUsbMainCdcMuxCallbackUnRegister(u8 nUsbEvent);
void MdlUsbMainCommPcEventSuspendCB(void);
void MdlUsbMainCommPcEventResumeCB(void);
void MdlUsbMainCommPcEventRemoveCB(void);
void MdlUsbMainCdcPcEventDataReadCB(void);
void MdlUsbMainCdcPcEventDataWriteDoneCB(void);
void MdlUsbMainCdcPcEventSetLineStateCB(s16 nLineState);
void MdlUsbMainCdcPcEventSetLineCodindCB(void* pLineCoding);
u8 MdlUsbMainCdcGetLineState(void);
//static void MdlUsbMainUseCaseCallback(void *pUseCaseParam, u32 nUseCaseParamSize, u32 nUserData);
#if defined(__USB_ENABLE__)
void MdlUsbTaskParseMsg(void *pMessage);
void MdlUsbMainGenieRead(u8* pRbuffer, u16* pwAmount, u16 nMax);
s32 MdlUsbMainGenieWrite(u8 *pWbuffer, u16 nLen);
s32 MdlUsbMainGenieCallbackRegister(u8 nUsbEvent, void *pfUsbFun);
s32 MdlUsbMainGenieCallbackUnRegister(u8 nUsbEvent);
void MdlUsbEnableDebugPort(U8 option);
#endif
#ifdef ENABLE_PictBridge
void MdlUsbMainPbPntEventUpdateStatusCB(u16 nJobSts, u16 nPntSts);
#endif
#endif   //_MS_MDL_USB_MAIN_H_

