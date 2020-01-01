/*
   aacPlus-specific Payload Extraction
 */
#ifndef _AACPLUSCHECK_H
#define _AACPLUSCHECK_H

#include "aacplus_FFR_bitbuffer.h"

int aacPlusCheckForPayload(AAC_HANDLE_BIT_BUF bs,
                           SBRBITSTREAM *streamSBR,
                            Word16 prev_element);

signed char aacPlusGetPayload(AAC_HANDLE_BIT_BUF bs,
                        SBR_ELEMENT_STREAM *streamSBR);


#endif
