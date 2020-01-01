 /*!
 *************************************************************************************
 * \file annexb.h
 *
 * \brief
 *    Annex B byte stream buffer handling.
 *
 *************************************************************************************
 */

#ifndef ANNEXB_H
#define ANNEXB_H

#include "avp_videc_s.h"

#ifdef NO_NAL_PEEK
#include "avp_mvc_types.h"
uchar *NextAnnexbNALU_wH(uchar *buf, int len);
uint32 PeekAnnexbNALU_Header(uchar *bp);
#else
#include "avp_nalucommon.h"
#include "avp_avcPrivate.h"
#include "avp_mvc_decoder.h"

void GetAnnexbNALU(NALU_t *nalu, AVC_HANDLE *hp, VID_SETUP *setup);
uint32 PeekAnnexbNALU_Header(VID_SETUP *setup);
#endif

#endif
