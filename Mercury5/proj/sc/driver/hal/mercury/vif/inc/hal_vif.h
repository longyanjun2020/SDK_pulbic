#ifndef __HAL_VIF__
#define __HAL_VIF__

#include "kernel_vif.h"
#include "kernel_sc_clk_ctl.h"
#include "drv_vif.h"

void HalVif_SensorSWReset(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_IFStatusReset(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_SensorReset(SENSOR_PAD_GROUP_e pad_group, VIF_ONOFF_e OnOff);
void HalVif_SensorPowerDown(SENSOR_PAD_GROUP_e pad_group, VIF_ONOFF_e OnOff);
void HalVif_SensorChannelEnable(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_HDRen(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_HDRSelect(VIF_CHANNEL_e ch, VIF_HDR_SOURCE_e src);
void HalVif_SensorMask(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_IfDeMode(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_EnSWStrobe(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_SWStrobe(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_StrobePolarity(VIF_CHANNEL_e ch, VIF_STROBE_POLARITY_e polarity);
void HalVif_StrobeStart(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_StrobeRef(VIF_CHANNEL_e ch, VIF_STROBE_VERTICAL_START_e startType);
void HalVif_StrobeEnd(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_EnHWStrobe(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_HWStrobeCNT(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_HWLongStrobeEndRef(VIF_CHANNEL_e ch, VIF_STROBE_VERTICAL_START_e startType);
void HalVif_HWStrobeMode(VIF_CHANNEL_e ch, VIF_STROBE_MODE_e strobMode);
void HalVif_SensorFormatLeftSht(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_SensorBitSwap(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_SensorHsyncPolarity(VIF_CHANNEL_e ch, VIF_SENSOR_POLARITY_e polarity);
void HalVif_SensorVsyncPolarity(VIF_CHANNEL_e ch, VIF_SENSOR_POLARITY_e polarity);
void HalVif_SensorFormat(VIF_CHANNEL_e ch, VIF_SENSOR_FORMAT_e format);
void HalVif_SensorRgbIn(VIF_CHANNEL_e ch, VIF_SENSOR_INPUT_FORMAT_e format);
void HalVif_SensorFormatExtMode(VIF_CHANNEL_e ch, VIF_SENSOR_BIT_MODE_e mode);
void HalVif_SensorYc16Bit(VIF_CHANNEL_e ch, VIF_SENSOR_YC_INPUT_FORMAT_e format);
void HalVif_SensorVsDly(VIF_CHANNEL_e ch, VIF_SENSOR_VS_DELAY_e delay);
void HalVif_SensorHsDly(VIF_CHANNEL_e ch, VIF_SENSOR_HS_DELAY_e delay);
void HalVif_ParWidth(VIF_CHANNEL_e ch, unsigned int width);
void HalVif_Bt601ByteintEn(VIF_ONOFF_e OnOff);
void HalVif_Bt601ChSel(VIF_CHANNEL_e ch, unsigned int channel);
void HalVif_Bt656Yc16bitMode(VIF_CHANNEL_e ch, VIF_SENSOR_BT656_FORMAT_e format);
void HalVif_DebugSel(unsigned int sel);
void HalVif_CaptureEn(VIF_CHANNEL_e ch, VIF_ONOFF_e OnOff);
void HalVif_IrqMask(VIF_CHANNEL_e ch, unsigned int mask);
void HalVif_IrqForce(VIF_CHANNEL_e ch, unsigned int mask);
void HalVif_IrqClr(VIF_CHANNEL_e ch, unsigned int mask);
void HalVif_Vif2IspLineCnt0(VIF_CHANNEL_e ch, unsigned int LineCnt);
void HalVif_Vif2IspLineCnt1(VIF_CHANNEL_e ch, unsigned int LineCnt);
unsigned int HalVif_IrqFinalStatus(VIF_CHANNEL_e ch);
unsigned int HalVif_IrqRawStatus(VIF_CHANNEL_e ch);
void HalVif_SelectSource(SENSOR_PAD_GROUP_e pad_group, VIF_CHANNEL_e ch, VIF_CHANNEL_SOURCE_e src, unsigned int bt656_total_ch, unsigned int bt656_cur_ch);
void HalVif_SensorPclkPolarity(VIF_CHANNEL_e ch, VIF_SENSOR_POLARITY_e polarity);
#endif
