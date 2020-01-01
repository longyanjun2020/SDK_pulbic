#ifndef _FPGAAPI_H_
#define _FPGAAPI_H_

#define RET_OK 1
#if defined(_SOC_) || defined(_SIM_)
#include "MMIOApi.h"
#define FPGA_Connect()
#define FPGA_RIURead16      MMIO_RIURead16
#define FPGA_RIUWrite16     MMIO_RIUWrite16

#else //defined(_SOC_) || defined(_SIM_)
#ifdef _UDMA_
#include "windows.h"
#include "UDMAapi.h"
#define FPGA_Connect         UDMA_Connect
#define FPGA_RIURead16       UDMA_RIURead16
#define FPGA_RIUWrite16      UDMA_RIUWrite16
#define FPGA_MIURead         UDMAOP_DMAGet
#define FPGA_MIUWrite        UDMAOP_DMAPut
#define FPGA_MIUReadFile     UDMAOP_DMAGetFile
#define FPGA_MIUWriteFile    UDMAOP_DMAPutFile
#elif defined(_HIF_)
#include "HIFapi.h"
#define FPGA_Connect         HIF_Connect
#define FPGA_RIURead16       HIF_RIURead16
#define FPGA_RIUWrite16      HIF_RIUWrite16
#define FPGA_MIURead         HIF_MIURead
#define FPGA_MIUWrite        HIF_MIUWrite
#else
#error "you have to define _UDMA_ or _HIF_!!!"
#endif
#endif //defined(_SOC_) || defined(_SIM_)

#endif
