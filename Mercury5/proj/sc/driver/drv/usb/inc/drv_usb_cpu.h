#include "type.h"
#include "sys_sys.h"
#include "drv_usb_handler.h"
#include "hal_usb_config.h"

#define M_FIFO_EP0         (0x20<<OffShift)
#define FIFO_ADDRESS(e)  (otgRegAddress + (e<<3) + M_FIFO_EP0)

void USB_DRC_Fifo_Read(U8 *dstP,U8 ep,USB_VAR *gUSBStruct);
void USB_DRC_Fifo_Write(U8 *srcP,U8 ep,USB_VAR *gUSBStruct);
