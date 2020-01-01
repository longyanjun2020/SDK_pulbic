#ifndef	_MMPF_I2S_CTL_H_
#define	_MMPF_I2S_CTL_H_

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

void MMPF_I2S_SetMclkMode(MMP_UBYTE ch, MMP_I2S_MCLK_MODE mclk_mode);
void MMPF_I2S_SetUsbModeFreq(MMP_UBYTE ch, MMP_ULONG mclk_freq);
void MMPF_I2S_SetMclkFreq(MMP_UBYTE ch, MMP_ULONG fs);
void MMPF_I2S_EnableDataOutput(MMP_UBYTE ch, MMP_BOOL bEnable);
void MMPF_I2S_EnableMclk(MMP_UBYTE ch, MMP_I2S_WORK_MODE workMode, MMP_BOOL bEnable);
void MMPF_I2S_SetOutBitWidth(MMP_UBYTE ch, MMP_I2S_OUT_BITS outputBitSize);
void MMPF_I2S_SetLRckPolarity(MMP_UBYTE ch, MMP_I2S_WS_POLARITY lrckPolarity);
void MMPF_I2S_SetInBitAlign(MMP_UBYTE ch, MMP_UBYTE ubInBitAlign);
void MMPF_I2S_SetOutBitAlign(MMP_UBYTE ch, MMP_UBYTE ubOutBitAlign);
void MMPF_I2S_SetWorkMode(MMP_UBYTE ch, MMP_I2S_WORK_MODE workingMode);
void MMPF_I2S_SetI2SMclkMode(MMP_UBYTE ch, MMP_I2S_MCLK_MODE mclkMode);
void MMPF_I2S_SetOutBySDI(MMP_UBYTE ch, MMP_BOOL bOutputBySDI);
void MMPF_I2S_SetInFromSDO(MMP_UBYTE ch, MMP_BOOL bInputFromSDO);
void MMPF_I2S_SetOutDataDelayMode(MMP_UBYTE ch, MMP_I2S_DELAY_MODE outDataDelayMode);
void MMPF_I2S_SetPadConfig(MMP_UBYTE ch, MMP_UBYTE ubPad);

#endif //_MMPF_I2S_CTL_H_
