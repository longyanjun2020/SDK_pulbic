#ifndef __KERNEL_MERCURY5_H__
#define __KERNEL_MERCURY5_H__

#ifndef __KERNEL_H__
#error must include kernel.h instead of kernel_b5.h
#endif

#include "vm_types.ht"
#include "cpu_mem_map.hc"
#include "dma_sources.hc"

#ifdef  __cplusplus
extern "C" {
#endif

#define MAIN_OFFSET 0x00000000

#include "kernel_cmu.h"
#include "kernel_gpio.h"
#include "kernel_itctrl.h"
#include "kernel_axi.h"
#include "kernel_spi.h"
#include "kernel_sysreg.h"
#include "kernel_uart.h"
#include "kernel_emi.h"
#include "kernel_systimer.h"
#include "kernel_i2c.h"
#include "kernel_rf.h"
#include "kernel_dsp.h"
#include "kernel_cp.h"
#include "kernel_keypad.h"
#include "kernel_pwm.h"
#include "kernel_sim.h"
#include "kernel_dma.h"
#include "kernel_audio.h"
#include "kernel_clkgen.h"
#include "kernel_miu.h"
#include "kernel_pll.h"
#include "kernel_padctrl.h"
#include "kernel_adcdma.h"
#include "kernel_paging_spi.h"
#include "kernel_pmu.h"
#include "kernel_scl.h"
#include "kernel_imi.h"
#include "kernel_isp.h"
#include "kernel_csi.h"
#include "kernel_dphy_ana.h"
#include "kernel_dphy_dig.h"
#include "kernel_csi_mac_4lane.h"
#include "kernel_dphy_ana_4lane.h"
#include "kernel_dphy_dig_4lane.h"
#include "kernel_vif.h"
#include "kernel_icp.h"
#include "kernel_mmp.h"
#include "kernel_dmc.h"
#include "kernel_aux.h"
#include "kernel_timer.h"
#include "kernel_gdma.h"
#include "kernel_bdma.h"
#include "kernel_master_spi.h"
#include "kernel_fsp_spi.h"
#include "kernel_fsp2_spi.h"
#include "kernel_qspi.h"
#include "kernel_i2c_mas.h"
#include "kernel_rtc.h"
#include "kernel_sar_adc.h"
#include "kernel_efuse.h"
#include "kernel_dip.h"
#include "kernel_sc_clk_ctl.h"
#include "kernel_dmagen.h"

#ifdef  __cplusplus
}
#endif

#endif  /* __KERNEL_MERCURY5_H__ */

