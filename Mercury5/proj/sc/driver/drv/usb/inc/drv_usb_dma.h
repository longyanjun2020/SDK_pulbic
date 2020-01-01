#ifndef _MS_DMA_H_
#define _MS_DMA_H_

#include "hal_usb_config.h"


#define M_REG_DMA_INTR               (0x200<<OffShift)

#define MIN_DMA_TRANSFER_BYTES       64

#define DMA_TX                     0x2
#define DMA_RX                     0x0

#define DMA_MODE_ONE               0x4
#define DMA_MODE_ZERO              0x0

#define DMA_IRQ_ENABLE             0x8
#define DMA_IRQ_DISABLE            0x0

#define DMA_ENABLE_BIT          0x0001

#define DMA_BurstMode        0x03

#define RXCSR2_MODE1  (M_RXCSR2_AUTOCLEAR | M_RXCSR2_DMAENAB | M_RXCSR2_DMAMODE)
#define TXCSR2_MODE1  (M_TXCSR2_DMAENAB | M_TXCSR2_AUTOSET | M_TXCSR2_DMAMODE | M_TXCSR2_MODE)

#define DMA_TX_ZERO_IRQ       (DMA_TX | DMA_MODE_ZERO | DMA_IRQ_ENABLE)
#define DMA_TX_ONE_IRQ       (DMA_TX | DMA_MODE_ONE | DMA_IRQ_ENABLE)
#define DMA_RX_ONE_IRQ       (DMA_RX | DMA_MODE_ONE | DMA_IRQ_ENABLE)

#define DMA_BUSERROR_BIT        0x0100

#define DMA_ENDPOINT_SHIFT           4


#define DMA_BASE_ADDRESS()         otgRegAddress + (0x200<<OffShift)

#define DMA_ADDR_REGISTER(channel)  (U16 volatile*)(DMA_BASE_ADDRESS() + ((0x10 * (channel - 1) + 8)<<OffShift))
#define DMA_COUNT_REGISTER(channel) (U16 volatile*)(DMA_BASE_ADDRESS() + ((0x10 * (channel - 1) + 0xc)<<OffShift))
#define DMA_CNTL_REGISTER(channel)  (U16 volatile *)(DMA_BASE_ADDRESS() + ((0x10 * (channel - 1) + 4)<<OffShift))

#define EP_IRQ_ENABLE                1
#define EP_IRQ_DISABLE               0
#define EP_IRQ_RX                    0
#define EP_IRQ_TX                    2

#define DMA_MODE_MASK              (DMA_TX | DMA_MODE_ONE)


#define Enable_TX_EP_Interrupt(endpoint) \
      Control_EP_Interrupt(endpoint, (EP_IRQ_ENABLE | EP_IRQ_TX),gUSBStruct);

#define Enable_RX_EP_Interrupt(endpoint) \
      Control_EP_Interrupt(endpoint, (EP_IRQ_ENABLE | EP_IRQ_RX),gUSBStruct);

#define Disable_TX_EP_Interrupt(endpoint) \
      Control_EP_Interrupt(endpoint, (EP_IRQ_DISABLE | EP_IRQ_TX),gUSBStruct);

#define Disable_RX_EP_Interrupt(endpoint) \
      Control_EP_Interrupt(endpoint, (EP_IRQ_DISABLE | EP_IRQ_RX),gUSBStruct);


void USB_DMA_IRQ_Handler(U8 ch,USB_VAR *gUSBStruct);
S8 USB_Set_DMA(S8 ep, U32 mode, U32 maxsize, USB_VAR *gUSBStruct, S8 ch);
S8 Get_DMA_Channel(USB_VAR *gUSBStruct);
#endif
