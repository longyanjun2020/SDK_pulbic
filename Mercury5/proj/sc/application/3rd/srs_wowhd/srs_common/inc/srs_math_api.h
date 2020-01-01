/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  Basic arithmetic functions header file
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id: //srstech/srs_common/std_fxp/include/srs_math_api.h#9 $
 *  $Author: zesenz $
 *  $Date: 2011/02/16 $
********************************************************************************/

#ifndef __SRS_MATH_API_H__
#define __SRS_MATH_API_H__

#include "srs_typedefs.h"

//32x16=high 32-bit MSB:
//Note: acc and in32 cannot be the same variable
#define SRS_FXP32X16(acc, in32, in16) do{															\
									acc = (srs_int32)(srs_uint16)(in32) * (srs_int32)(in16);		\
									acc += 0x8000;													\
									acc >>= 16;														\
									acc += ((in32)>>16) * (srs_int32)(in16);						\
								  }while(0)


#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

srs_int32  SRS_CountLeadingZeroes(srs_uint32 xIn);
srs_uint32 SRS_FxpSqrt(srs_uint32 xIn);
srs_uint32 SRS_FxpPow2_32(srs_uint32 x);
srs_uint32 SRS_FxpPow2_16(srs_uint16 x);
srs_int32  SRS_FxpLog2(srs_uint32 x);
srs_int32 SRS_CalRecipro(srs_int32 d, int *iwl);

void	SRS_ApplyGain(srs_int32 *audioIO, int blockSize, srs_int16 gain, int gainIwl);	//performs X*gain
void	SRS_ApplyGainWithAnticlip16(srs_int32 *audioIO, int blockSize, srs_int16 gain);	//performs X*gain, then applies anticlip, using 16-bit anticlip table
void	SRS_ApplyGainWithAnticlip32(srs_int32 *audioIO, int blockSize, srs_int16 gain);	//performs X*gain, then applies anticlip, using 32-bit anticlip table

void	SRS_MixAndScale(srs_int32 *audioIO, srs_int32 *y, int blockSize, srs_int16 gain, int gainIwl); //performs (AudioIO+Y)*gain

void	SRS_LeftShift8Bits(srs_int32 *audio, int blockSize);
void	SRS_RightShift8Bits(srs_int32 *audio, int blockSize);

void	SRS_PowXY(srs_int32 *out, int *oiwl, srs_uint32 x, int xiwl, srs_int32 y, int yiwl);

srs_int32	SRS_Div(int oiwl, srs_int32 x, int xiwl, srs_int32 y, int yiwl);


#ifdef __cplusplus
}
#endif /*__cplusplus*/


#endif /*__SRS_MATH_API_H__*/

