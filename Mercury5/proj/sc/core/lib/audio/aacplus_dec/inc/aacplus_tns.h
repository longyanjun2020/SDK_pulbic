/*
   temporal noise shaping tool 
 */

#ifndef AACPLUS_TNS_H
#define AACPLUS_TNS_H

#include "aacplus_channelinfo.h"
#include "aacplus_FFR_bitbuffer.h"


Flag TnsPresent(CTnsData *pTnsData);

void CTns_Apply (CAacDecoderChannelInfo *pAacDecoderChannelInfo,
                 Word16 maxSfb);

Word16 CTns_Read(AAC_HANDLE_BIT_BUF bs,
                 CAacDecoderChannelInfo *pAacDecoderChannelInfo);


#endif /* #ifndef TNS_H */
