/*
   memory layout
 */

#ifndef AACDECODER_RAM_H
#define AACDECODER_RAM_H


#include "aacplus_channel.h"
#include"stereo.h"
#include "aacplus_conceal.h"
#include "aacplus_datastream.h"
#include "aacplus_pns.h"


#define MAX_SYNCHS        10
#define SAMPL_FREQS       12


CAacDecoderChannelInfo * pAacDecoderChannelInfoInitEnh[AAC_DEC_CHANNELS];
CAacDecoderDynamicData * pAacDecoderDynamicDataInitEnh[AAC_DEC_CHANNELS];

int AACPLUS_SetWorkingBuf(int *ptr);

#endif /* #ifndef AAC_RAM_H */
