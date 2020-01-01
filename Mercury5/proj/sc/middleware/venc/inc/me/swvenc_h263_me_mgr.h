#ifndef _ME_DATA_H_
#define _ME_DATA_H_

#define _ME_ML_FULL_
#define _ME_ML_SUB2_

#include "swvenc_udma_share.h"
#include "swvenc_IntraUpdate.h"
#if defined(USE_SWHW_PIPELINE) && defined(OUTPUT_CRC)
    #include "swvenc_CheckSum.h"
#endif

// ---------------------------------------------------------------
// Motion Estimation Method Selection
//
// ---------------------------------------------------------------
// Pixel-Level: Cost function
#define P_NUMBER		0x04//0x06
#define P_HALFQUAD_EJO  0x00
#define P_QUAD_EJO		0x01
#define P_HALF_EJO		0x02
#define P_FULL_EJO		0x03
// #define P_QUADSAMPLE    0x04
// #define P_FULLSAMPLE    0x05

// Search-Level: Search algorithm
#define SLevelFunc MVFAST
#define InitSLevelFunc InitMVFAST
// #define SLevelFunc FullSearch
// #define InitSLevelFunc

// MB-level: MV-field guessing
#define M_NUMBER        0x02
#define M_FULLCAL       0x00
#define M_SUB2CAL       0x01	// Only half number of MB's will entering SLevel function

#define HALFMEBUF_STRIDE 20
// ----------------------------------------------
// !!! Need External Data from ME users !!!
// ----------------------------------------------
// motion estimation buffer pointers
extern uint8 *cur;
extern uint8 *pre;
// motion vector arrary
extern point_t *MVArray;
// array of SAD's of best and zero MV's
extern uint16 *BestMvSadArray;


typedef struct {
	// Diff/DCT/iDCT buffer	
    MEMMAP_t m_pDiffBuf;//int16 m_pDiffBuf[384];

	int esterr;
	point_t *pptCurMV;
	point_t ptPredMV;

	int cur_right_for, cur_down_for;
	int right_for, down_for;
	int right_half_for, down_half_for;
	int idx_x, idx_y;   // Used to index temporary subpel buffer

	// Mode decision
	unsigned int MBType;
	Bool bCoded;

	// Current MB info
	int mi, mj, mk, px, py;
#ifdef USE_QMEM
       int new_mi,new_mj;
       uint8 *last_rec_u,*last_rec_v;
#endif

	// Current block info
	uint8* block_start[6];
	uint8* block_rec_start[6];
	int m_BlockVar[6];
	int m_BlockSum[6];
    int m_IntraDCOffset[6];

    int nMbQuant;   // QP for Q/IQ
    int nOldQuant;  // Store previous nMbQuant so that can be restored when skip-mb.

#if defined(USE_SWHW_PIPELINE) && defined(OUTPUT_CRC)
    adler_ctx crcDCT[6];
    adler_ctx crcIDCT[6];
#endif
} MBINFO_t;

typedef struct _MotEstContext {
	// Input 
	int ME_BUF_W;
	int ME_BUF_H;
	int SQ;

	// Derived
	int ME_TOTALPIXEL;
	int ME_TOTALBLOCK;
	// block number of horizontal and vertical axes
	int ME_BLOCKNUMX;
	int ME_BLOCKNUMY;
	// SQ
	int PLevel;
	int MLevel;
	// State variables
	int bNewMb;
	uint8* pbCurMb;
    // MVFAST jump-out threshold bias
    int bias;

    // Best SAD array
    uint16* pBestSadBuffer; // Must be allocated according to image resolution.
} MotEstContext;

// -------------------------------------------------------------
//
// Export Functions
//
// -------------------------------------------------------------
extern void me_Begin(MotEstContext* ctx);
extern void me_Finish(void);

extern void me_CurMbME_Forward(MotEstContext* ctx, IntraUpdateContext* iuctx, point_t* pptPMV, int bx, int by, int blk_idx, int nQscale);
extern void me_CurMbME_Forward_spel(MotEstContext* ctx, IntraUpdateContext* iuctx, MBINFO_t* MbInfo, uint8 HalfBuf[3][17][HALFMEBUF_STRIDE], int px, int py);

/********** Global Function **********/


// ----------------------------------------------------------------------------
//
//                The following are used for calculation of MAD
//
// ----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////
// To achieve faster speed without obeying its purpose,			  //	
// return value is not devided by BLOCKSIZE*BLOCKSIZE.			  //
// That is, real MAD is ReturnValue/(BLOCKSIZE*BLOCKSIZE).		  //
////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------
// Calculate the MAD between this block and prediction block using
// Every Pixel in the block
// ----------------------------------------------------------------
// n: N   Frame Block Position
// m: N-1 Frame Block Position
// int CalFullMAD(int nx,int ny,int mx,int my);
// int CalQuadMAD(int nx,int ny,int mx,int my);

// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Motion Estimation : Pixel Level 
// 
//      nx     : x coordinate in pixel in current frame
//      ny     : y coordinate in pixel in current frame
//      mx     : x coordinate in pixel in predicted frame
//      my     : y coordinate in pixel in predicted frame
//
// Description : Now implementation includes 
//
//                       FullMAD,
//                       QuadMAD,
//                       EJO,
//                       EJOQuad
//
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// function pointer array
extern int (*const PixelLevelFunction[P_NUMBER])(MotEstContext* ctx, int, int, int, int);
// One of the entry in PixelLevelFunction[]
extern int (*lpPixelLevelFunction)(MotEstContext* ctx, int, int, int, int);

int EarlyJumpOut(MotEstContext* ctx, int nx, int ny, int mx, int my);

// ----------------------------------------------------------------------------

// Initialize Early Jump Out Sequence
void EJO_INIT_SeqSum(MotEstContext* ctx);


// MVFAST Algorithm
point_t MVFAST(MotEstContext* ctx, IntraUpdateContext* iuctx, point_t* pptPMV, int x, int y, int Index);
void InitMVFAST(MotEstContext* ctx);

// Full Search
point_t FullSearch(MotEstContext* ctx, point_t* pptPMV, int x, int y);

// To avoid duplicated candidate checking
extern short g_sCurMbNumber;
extern short g_TravelledMap[31][31];  // [Y][X]. X,Y: -15 to 15


#endif
