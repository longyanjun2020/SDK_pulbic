// usb event

/** @addtogroup MMPF_USB
@{
*/

#define PCSYNC_STATUS_USB_PLUG_IN    0x1000

#define PCSYNC_STATUS_USB_INT_ON    0x0100

#define PCSYNC_STATUS_IN_READY       0x0001
#define PCSYNC_STATUS_IN_DATA        0x0002
#define PCSYNC_STATUS_IN_SIZE        0x0004
#define PCSYNC_STATUS_IN_CLOSE       0x0008
#define PCSYNC_STATUS_OUT_READY      0x0010
#define PCSYNC_STATUS_OUT_DATA       0x0020
#define PCSYNC_STATUS_OUT_SIZE       0x0040
#define PCSYNC_STATUS_OUT_CLOSE      0x0080

// pcsync finish state
#define PCSYNC_STATE_IN_OPEN    0x01
#define PCSYNC_STATE_IN_RECV    0x02
#define PCSYNC_STATE_IN_FINISH  0x04
#define PCSYNC_STATE_IN_KNOW    0x08
#define PCSYNC_STATE_OUT_OPEN   0x10
#define PCSYNC_STATE_OUT_SEND   0x20
#define PCSYNC_STATE_OUT_FINISH 0x40

#ifdef exUSBPCSYNC

MMP_UBYTE  PCSYNCState;

MMP_UBYTE  UsbIntClose;

MMP_UBYTE  BulkINReady;
MMP_UBYTE  SetBulkInFlag;

MMP_UBYTE  PCSYNCInCheck;

MMP_UBYTE  BulkInPknLo;
MMP_UBYTE  BulkInPknHi;
MMP_UBYTE  BulkInLt;

MMP_UBYTE  PCSYNCInSizeLo;
MMP_UBYTE  PCSYNCInSizeMi;
MMP_UBYTE  PCSYNCInSizeHi;

MMP_UBYTE  PCSYNCOutSizeLo;
MMP_UBYTE  PCSYNCOutSizeMi;
MMP_UBYTE  PCSYNCOutSizeHi;

MMP_UBYTE  PCSYNCOutAllSizeLo;
MMP_UBYTE  PCSYNCOutAllSizeMi;
MMP_UBYTE  PCSYNCOutAllSizeHi;

MMP_UBYTE  PCSYNCOutSizeZero;

#else

extern MMP_UBYTE  PCSYNCState;

extern MMP_UBYTE  UsbIntClose;

extern  MMP_UBYTE  BulkINReady;
extern  MMP_UBYTE  SetBulkInFlag;

extern MMP_UBYTE  PCSYNCInCheck;

extern MMP_UBYTE  BulkInPknLo;
extern MMP_UBYTE  BulkInPknHi;
extern MMP_UBYTE  BulkInLt;

extern MMP_UBYTE  PCSYNCInSizeLo;
extern MMP_UBYTE  PCSYNCInSizeMi;
extern MMP_UBYTE  PCSYNCInSizeHi;

extern MMP_UBYTE  PCSYNCOutSizeLo;
extern MMP_UBYTE  PCSYNCOutSizeMi;
extern MMP_UBYTE  PCSYNCOutSizeHi;

extern MMP_UBYTE  PCSYNCOutAllSizeLo;
extern MMP_UBYTE  PCSYNCOutAllSizeMi;
extern MMP_UBYTE  PCSYNCOutAllSizeHi;

extern MMP_UBYTE  PCSYNCOutSizeZero;

#endif // #ifdef exUSBPCSYNC
/// @}