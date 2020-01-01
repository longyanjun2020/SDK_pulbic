#ifndef _DCT_IDCT_H_
#define _DCT_IDCT_H_

#include "swvenc_deftypes.h"
#include "swvenc_fastmath.h"

// The external interfaces are:
//  ForwardDCTFunction
//  InitInverseDCTFunction
//  InverseDCTFunction

// DCT function: Must choose one
#define MPEGC_DCT
//#define MSTAR_MFE_DCT	// MFE, JPE'09 cModel

// IDCT function: Must choose one
// #define MPEGC_IDCT
//#define MSTAR_JPD_IDCT	// BIG3-JPD cModel
#define DIVX_IDCT

extern int16 *gpDctInBuf;
extern int16 *gpDctOutBuf;

#ifdef MPEGC_IDCT
	void swvenc_idct_23002_2_addblock(int16 *P, uchar *Dst, int width, int isIntra, int is4x4, uint32 nNotDCOnly, int lpos);

	#define InitInverseDCTFunction
	#define InverseDCTFunction		swvenc_idct_23002_2_addblock
#elif defined(MSTAR_JPD_IDCT)
	void MstarJpdIdctInit();
	void jpeg_idct_8x8(int16* pInBuf, int16* outcoeff);

	#define InitInverseDCTFunction MstarJpdIdctInit()
	#define InverseDCTFunction		jpeg_idct_8x8
#elif defined(DIVX_IDCT)
	void swvenc_divx_idct_generic_addblock(int16 *P, uchar *Dst, int width, int isIntra, int is4x4, uint32 nNotDCOnly, int lpos);

	#define InitInverseDCTFunction
	#define InverseDCTFunction		swvenc_divx_idct_generic_addblock
#endif

#ifdef MPEGC_DCT
	void swvenc_fdct_23002_2(short* pInBlock, int16* pOutBlock, int is4x4);

	#define ForwardDCTFunction swvenc_fdct_23002_2

    void dct23002_GenQuantJumpOutArray(int pJumpOut[2][64], int QP);
#elif defined(MSTAR_MFE_DCT)
	void Mstar_fdct(short* pInBlock, int16* pOutBlock, int is4x4);
	
	#define ForwardDCTFunction Mstar_fdct
#endif


#endif  // _DCT_IDCT_H_
