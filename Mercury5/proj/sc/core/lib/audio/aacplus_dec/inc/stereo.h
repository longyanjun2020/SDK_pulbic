/*
   joint stereo processing
 */

#ifndef _STEREO_H
#define _STEREO_H


#include "aacplus_FFR_bitbuffer.h"
#include "aacplus_channelinfo.h"

void CJointStereo_Read(AAC_HANDLE_BIT_BUF bs,
                       CJointStereoData *pJointStereoData,
                       Word16 windowGroups,
                       Word16 scaleFactorBandsTransmitted);

void CJointStereo_ApplyMS(CAacDecoderChannelInfo *pAacDecoderChannelInfo[],
                          const Word16 *pScaleFactorBandOffsets,
                          Word16 *pWindowGroupLength,
                          Word16 windowGroups,
                          Word16 scaleFactorBandsTransmitted);

void CJointStereo_ApplyIS(CAacDecoderChannelInfo *pAacDecoderChannelInfo[2],
                          const Word16 *pScaleFactorBandOffsets,
                          Word16 *pWindowGroupLength,
                          Word16 windowGroups,
                          Word16 scaleFactorBandsTransmitted,
                          Word16 CommonWindow);

#endif /* #ifndef STEREO_H */
