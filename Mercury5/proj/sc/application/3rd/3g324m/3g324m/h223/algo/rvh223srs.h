/******************************************************************************
        Copyright (c) 2005 RADVISION Inc. and RADVISION Ltd.
*******************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
******************************************************************************/
#ifndef _SRS_H_
#define _SRS_H_

#include "rvtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*

 Instructions for use of SRS encoding/decoding:

 General:
		SRS is a systematic block-encoding scheme. 
		"Systematic" means that the parity is appended to the block, leaving the data 
		unchanged. This implies, for example, that the AL-SDU* header can be read without
      SRS decoding.
		The H223 protocol specifies symbol size of 8 bits, which translates to blocks of 
		255 bytes or less. The symbol size also implies encoding of whole bytes only.

 E_target:
      H223 specified (in D.4.1.7.3) that the SRS code shall encode using a parameter
      called e_target which is part of the transmission configuration. This parameter,
		which ranges from 1 to just under 128, determines THE NUMBER OF PARITY BYTES in
		each 255 byte block. E_target is called SRS_PARITY_SIZE in the implementation below.
		Example:
		    If E_target === SRS_PARITY_SIZE == 32, each block will contain up to 223 data
			bytes and exactly 32 parity bytes.
		The higher the E_target value, the more parity bytes there are and the better the
      error-correction ability. The down side is in bandwidth (obvious) and in the CPU
		time which will be required to correct errors (which may be significant - see below).
      
 How to encode:
      1. Decide on the E_target (SRS_PARITY_SIZE) parameter size.
      2. Compute data_block_size = 255-SRS_PARITY_SIZE
		3. For each data_block_size data bytes
		4.		Copy them to the AL-PDU buffer (possibly transmitting them)
		5.		Call SRS_encode_parity, with the "parity" param pointing either
				directly into the AL-PDU buffer or a side-buffer of size SRS_PARITY_SIZE

 How to decode: Same idea, in blocks of 255 bytes (or less) of the AL-PDU.
		Note the unlike the encoding which does not change the source buffer, the decoder
		will need to change the source if there are errors.

 CPU / memory requirements:
		Memory requirement: 65.5K of pre-defined static tables, plus under 6K stack
      CPU: Encoding is quick: data_block_size*SRS_PARITY_SIZE table lookups and XORs
           Decoding is similar, as long as there are no errors.
           If there are errors, the complexity of error correction is dependent
           on the e_target parameter. It's both O(e_target^3) and O(e_target^2 * data_block_size)
           SRS provides very strong error-correction but with CPU requirements which are
			 somewhat higher than other algorithms.
*/


void RvH223SrsEncodeParity (int srsParitySize, RvUint8* buf, int buf_size, RvUint8* parity);
/* buf_size if data-only, that is 255-SRS_PARITY_SIZE or less */

int  RvH223SrsDecode(int srsParitySize, RvUint8* buf, int buf_size);
/* buf_size includes the parity, that is 255 or less */


#define SRS_DECODE_FAILED	0	// Cannot correct
#define SRS_DECODE_FIXED	1	// Error(s) corrected
#define SRS_DECODE_CORRECT	2	// Nothing to correct (we think)

#define SRS_MAX_PARITY_SIZE 128   // Since the H223 SRS block is 255 bytes long and this at most half of that

/*
     H223 primitive poly of degree 8 (see D.4.1.7.3)
     The high order 1 bit in the poly value is, as always, implicit
     (x^8) + x^4 + x^3 + x^2 + 1 
     Needed for: SRS_print_all_tables() in srs_dev_create_tables.c
     Sidenote: This is the most commonly used poly of deg 8
*/

#define H223_PRIMITIVE_POLY 0x1D 



#ifdef __cplusplus
}
#endif

#endif /* _SRS_H_ */

