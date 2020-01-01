#ifndef __USBISR_RAM__
#define __USBISR_RAM__

#include "globalvar.h"

void MDrv_USB_CmdLoop_win(void);
void USB_DRC_Interrupt_win(USB_VAR *gUSBStruct);
void MDrv_USB_DrcSwitchOffUsb(void);

#endif

