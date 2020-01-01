#ifndef __IH263V_H_
#define __IH263V_H_

#if 0

//////////////////////////////////////////////////////////////////////////
// External interface of encoder library
//////////////////////////////////////////////////////////////////////////

/*! Encoder generic settings
 * NOTE 1: Negative values implies "don't care".
 */
typedef struct {
    int version;
    int nWidth, nHeight;
    float fFramerate;
    int nDispAspectRatioX, nDispAspectRatioY;
    int nGOPICount, nGOPPCount, nGOPBCount;
    int nSQ;
    unsigned char reserved[88];
} VEncGenSetting;

enum RateCtrlMode {
    VENC_CONST_QUALITY = 1,
    VENC_CONST_BITRATE = 2,
    VENC_CONST_VARIABLE_BITRATE = 3
};

/*! Encoder rate control settings
* NOTE 1: Negative values implies "don't care".
*/
typedef struct {
    RateCtrlMode Mode;
    int nIQ, nPQ, nBQ;
    int nBitrate;
    int nMaxBitrate;
    unsigned char reserved[40];
} VEncRateCtrlSetting;

#endif

#endif  // __IH263V_H_
