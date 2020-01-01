#ifndef _RATECTRL_H_
#define _RATECTRL_H_

#include "swvenc_deftypes.h"

#define MAX_FRAMERATE   30

typedef enum RC_METHOD {
    CONST_QUALITY = 1,  //!< Constant qscale: rate control module should not be evolved.
    CONST_BITRATE = 2,  //!< Constant bitrate
    VARIABLE_BITRATE = 3,    //!< Variable bitrate with target average bitrate; 
                                    //!< instant maximal and minimal bitrate is not restricted.
    CONSTRAINED_VARIABLE_BITRATE = 4,    //!< Variable bitrate with target average bitrate; 
                                    //!< instant maximal bitrate is restricted.
    STRICT_CONST_BITRATE = 5,
} RC_METHOD;

typedef enum RC_GRANULARITY {
    FRAMELEVELRC = 1,   //!< All MB's in one frame uses the same qscale.
    MBLEVELRC = 2       //!< Allow qscale changing within frame, for better target bit-count achievement.
} RC_GRANULARITY;

/* Input for rate control */
typedef struct {
    int nWidth, nHeight;
    float fTargetFrameRate, fMinFrameRate;
    int m_nBitrate;
    int nPCount;    // Number of P-frames betweeen I-frames
    RC_GRANULARITY rcGranularity;
    RC_METHOD rcMethod;
} H263RCInfo;

typedef struct RateCtrl_t {
	/* Input parameters */

	int m_nWidth, m_nHeight;
	float m_fTargetFrameRate, m_fMinFrameRate;
	int m_nBitrate;
	int m_nPCount;
	RC_GRANULARITY m_rcGranularity;
	RC_METHOD m_rcMethod;
	// Derived variables
	float m_fAvgBitsPerFrame;

	/* rate control variables */

	int m_nFrameCount;  // How many frame coded
	int m_nBufFullness;  // Rate control buffer
	int64 m_nTotalBits;
	// Last-frame status
	int m_nLastFrameBits, m_nLastFrameAvgQP;
	int m_nLastTargetBits;

	/* Bitrate usage compensation */
	int m_nTargetFullness;
	int m_nDeputyCount, m_nMinDeputyCount;

	/* Variable bitrate */
	float m_fLongTermQP;

	// Model parameters
	int m_nTargetBits;   // target number of bits of current frame
	int m_nNFrame;    // number of macroblocks in a frame

    /* Dynamic framerate by frame-dropping (i.e., dummy-P frames) */
    unsigned char m_bDropFrameEnabled;  // Enabled when min-framerate < max-framerate.
    // Deteremine drop level by checking bad frame count inside a window of "real"-encoded frames.
    unsigned int m_nBadFrameCount;  // How many bad-quality frame inside the window.
    unsigned int m_nChkWinIndex;    // How many "real"-encoded frame being monitored so far.
                                    // When exceeding m_nChkWinSize, will determine new drop-level.
    unsigned int m_nChkWinSize;     // The size of window.
    // 
    unsigned int m_nMaxDropLevel;   // The number of maximal dropped frame count inside one second.
                                    // This is a constant according to Min&Max framerate.
    unsigned int m_nCurDropLevel;   // The current-adopted dropped level.
    unsigned int m_nAllFrameIndex;  // How many frame encoded (including dummy-P's).
    unsigned int m_nRealFrameIndex; // How many "real"-encoded frame so far.

    /* STRICT_CONST_BITRATE */
    unsigned int m_nRunWinIndex;
    unsigned int m_nRunWinSize; // Should exceed m_nRunWinMaxSize and then freezed.
    unsigned int m_nRunWinMaxSize;
    unsigned int m_RunWinArray[MAX_FRAMERATE]; // Stored historic frame-size in bits
    int m_nRunWinResidue;   // Accumulated bitrate over-usage.
    int m_nRunWinDummyCount;    // How many dummy frame encoded before current frame.
    int m_nEncodedPCount;       // To compensate forcedI frame
} RateCtrl_t;

void rc_Create(RateCtrl_t* rcctx);
void rc_Destroy(RateCtrl_t* rcctx);
// Global
void rc_Init(RateCtrl_t* rcctx, H263RCInfo* pRCInfo);
void rc_Finish(RateCtrl_t* rcctx);
// Each frame
int rc_CheckSkippedFrame(RateCtrl_t* rcctx);
int rc_InitFrame(RateCtrl_t* rcctx, char chFrameType);    // Return the initial frame qp
void rc_UpdateFrame(RateCtrl_t* rcctx, int totalUsedBits, Bool bDummyFrame);

int rc_GetMbQuant(RateCtrl_t* rcctx, int nPrvQP, int nMbIndex, int nTotalBits);
void rc_UpdateMbQuant(RateCtrl_t* rcctx, int nQP);

#endif
