#ifndef __WMA_DECODER_STRUCT_INCLUDE_FILE__
#define __WMA_DECODER_STRUCT_INCLUDE_FILE__


//////////////////// asfwmatypes.h ///////////////////////
//For FFT & adaptToSubFrameConfig
typedef struct {
    BP1Type sin_PIby4cSB;     // sin( pi/(4*cSB) ) * nF2BP1 for DCT and inverseTransform
    BP1Type cos_PIby4cSB;     // cos( pi/(4*cSB) ) * nF2BP1 for DCT and inverseTransform
   BP1Type sin_3PIby4cSB;     // sin( 3*pi/(4*cSB) ) * nF2BP1 for DCT
   BP1Type cos_3PIby4cSB;     // cos( 3*pi/(4*cSB) ) * nF2BP1 for DCT
   BP1Type sin_PIbycSB;    // sin( pi/cSB ) * nF2BP1 for DCT
   BP1Type cos_PIbycSB;    // cos( pi/cSB ) * nF2BP1 for DCT
   BP1Type sin_2PIbycSB;      // sin( pi/(cSB/2) ) * nF2BP1 for FFT
   BP1Type cos_2PIbycSB;      // cos( pi/(cSB/2) ) * nF2BP1 for FFT
   BP1Type sin_PIby2cSB;      // sin( pi/(2*cSB) ) * nF2BP1 for inverseTransform
   BP1Type cos_PIby2cSB;      // cos( pi/(2*cSB) ) * nF2BP1 for inverseTransform
   BP1Type two_sin_PIbycSB;   // 2 * sin( pi/cSB ) * nF2BP1 for DCT
#ifdef ENABLE_LPC
    BP2Type sin_4PIbycSB;       // sin( 4*pi/cSB ) * nF2BP2 for LPC
    BP2Type cos_4PIbycSB;       // sin( 4*pi/cSB ) * nF2BP2 for LPC
#endif
}SinCosTable;


// ======================================================================
// Windows Media Audio (common)

#define MM_MSFT_ACM_WMAUDIO  39

#define WMAUDIO_BITS_PER_SAMPLE    16 // just an uncompressed size...
#define WMAUDIO_MAX_CHANNELS       2

#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
typedef  struct tWAVEFORMATEX
{
    WORD    wFormatTag;         /* format type */
    WORD    nChannels;          /* number of channels (i.e. mono, stereo...) */
    DWORD   nSamplesPerSec;     /* sample rate */
    DWORD   nAvgBytesPerSec;    /* for buffer estimation */
    WORD    nBlockAlign;        /* block size of data */
    WORD    wBitsPerSample;     /* number of bits per sample of mono data */
    WORD    cbSize;             /* the count in bytes of the size of */

}   WAVEFORMATEX;
typedef const WAVEFORMATEX *LPCWAVEFORMATEX;
#endif // _WAVEFORMATEX_
// ======================================================================
// Windows Media Audio V1 (a.k.a. "MSAudio")

#define WAVE_FORMAT_MSAUDIO1  0x0160
#define MM_MSFT_ACM_MSAUDIO1  39

typedef struct msaudio1waveformat_tag {
    WAVEFORMATEX wfx;
    WORD         wSamplesPerBlock; // only counting "new" samples "= half of what will be used due to overlapping
    WORD         wEncodeOptions;
} MSAUDIO1WAVEFORMAT;

//typedef MSAUDIO1WAVEFORMAT FAR  *LPMSAUDIO1WAVEFORMAT;

#define MSAUDIO1_BITS_PER_SAMPLE    WMAUDIO_BITS_PER_SAMPLE
#define MSAUDIO1_MAX_CHANNELS       WMAUDIO_MAX_CHANNELS
#define MSAUDIO1_WFX_EXTRA_BYTES    (sizeof(MSAUDIO1WAVEFORMAT) - sizeof(WAVEFORMATEX))


// ======================================================================
// Windows Media Audio V2

#define WAVE_FORMAT_WMAUDIO2  0x0161
#define MM_MSFT_ACM_WMAUDIO2  101

typedef struct wmaudio2waveformat_tag {
    WAVEFORMATEX wfx;
    DWORD        dwSamplesPerBlock; // only counting "new" samples "= half of what will be used due to overlapping
    WORD         wEncodeOptions;
    DWORD        dwSuperBlockAlign; // the big size...  should be multiples of wfx.nBlockAlign.
} WMAUDIO2WAVEFORMAT;

//typedef WMAUDIO2WAVEFORMAT FAR  *LPWMAUDIO2WAVEFORMAT;

#define WMAUDIO2_BITS_PER_SAMPLE    WMAUDIO_BITS_PER_SAMPLE
#define WMAUDIO2_MAX_CHANNELS       WMAUDIO_MAX_CHANNELS
#define WMAUDIO2_WFX_EXTRA_BYTES    (sizeof(WMAUDIO2WAVEFORMAT) - sizeof(WAVEFORMATEX))

// ======================================================================
// Windows Media Audio V3

#if !defined (WAVE_FORMAT_WMAUDIO_LOSSLESS)
#define WAVE_FORMAT_WMAUDIO_LOSSLESS  0x0163
#endif

#if !defined (WAVE_FORMAT_WMAUDIO3)
#define WAVE_FORMAT_WMAUDIO3  0x0162

typedef struct wmaudio3waveformat_tag {
  WAVEFORMATEX wfx;
  WORD         wValidBitsPerSample; // bits of precision 
  DWORD        dwChannelMask;       // which channels are present in stream 
  DWORD        dwReserved1;
  DWORD        dwReserved2;
  WORD         wEncodeOptions;
  WORD         wReserved3;
} WMAUDIO3WAVEFORMAT;

//typedef WMAUDIO3WAVEFORMAT FAR *LPWMAUDIO3WAVEFORMAT;
#define WMAUDIO3_WFX_EXTRA_BYTES    (sizeof(WMAUDIO3WAVEFORMAT) - sizeof(WAVEFORMATEX))
#endif // WAVE_FORMAT_WMAUDIO3


typedef struct tGUID
{
    unsigned int   Data1;
    unsigned short  Data2;
    unsigned short  Data3;
    unsigned char   Data4[ 8 ];
}GUID;

#ifndef _WAVEFORMATEXTENSIBLE_
#define _WAVEFORMATEXTENSIBLE_
typedef struct 
{
    WAVEFORMATEX Format;       /* The traditional wave file header */
    union {
        unsigned short wValidBitsPerSample; /* bits of precision */
        unsigned short wSamplesPerBlock;    /* valid if wBitsPerSample==0 */
        unsigned short wReserved;           /* If neither applies, set to zero */
    } Samples;
    unsigned long    dwChannelMask;        /* which channels are present in stream */
    GUID SubFormat;           /* specialization */
} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;

#endif // _WAVEFORMATEXTENSIBLE_ 




typedef  struct tAsfXAcmAudioErrorMaskingData
{
    BYTE    span;
//    WORD    virtualPacketLen;
//    WORD    virtualChunkLen;
//    WORD    silenceLen;
//    BYTE    silence[1];

}   AsfXAcmAudioErrorMaskingData;

typedef  struct tAsfXSignatureAudioErrorMaskingData
{
    DWORD maxObjectSize;
//   WORD  chunkLen;
//   WORD  signatureLen;
//   BYTE  signature[1];

}   AsfXSignatureAudioErrorMaskingData;

typedef struct tPACKET_PARSE_INFO_EX
{
    WMA_BOOl fParityPacket;
    DWORD cbParseOffset;

    WMA_BOOl fEccPresent;
    BYTE bECLen;

    BYTE bPacketLenType;
    DWORD cbPacketLenTypeOffset;

    BYTE bPadLenType;
    BYTE bSequenceLenType;

    WMA_BOOl fMultiPayloads;

    BYTE bOffsetBytes;

    BYTE bOffsetLenType;

    DWORD cbPacketLenOffset;

    DWORD cbExplicitPacketLength; 

    DWORD cbSequenceOffset;
    
    DWORD dwSequenceNum; 

    DWORD cbPadLenOffset;
    DWORD cbPadding;

    DWORD dwSCR;
    WORD wDuration;

    BYTE bPayLenType;
    BYTE bPayBytes;
    DWORD cbPayLenTypeOffset;

    DWORD cPayloads;

}   PACKET_PARSE_INFO_EX;

typedef struct tPAYLOAD_MAP_ENTRY_EX
{
    WORD cbPacketOffset;
    WORD cbTotalSize;

    BYTE bStreamId;
    BYTE bObjectId;

    DWORD cbObjectOffset;
    DWORD cbObjectSize;
    DWORD msObjectPres;

    BYTE cbRepData;
    BYTE bJunk;
    WORD cbPayloadSize;
    
    WORD wBytesRead;
    WORD wTotalDataBytes;
    BYTE bSubPayloadState;
    BYTE bIsCompressedPayload;
    BYTE bNextSubPayloadSize;
    WORD wSubpayloadLeft;
    DWORD dwDeltaTime;
    WORD  wSubCount;    

}   PAYLOAD_MAP_ENTRY_EX;

//////////////////////////////////////////////////////////////////////////


typedef enum _PCMData {
    PCMDataPCM        = 0,
    PCMDataIEEE_FLOAT = 1,
} PCMData;


typedef struct {
    WMA_U32 nSamplesPerSec;               
    WMA_U32 nChannels;
    //WMA_U32 nChannelMask;
    WMA_U32 nValidBitsPerSample;
    WMA_U32 cbPCMContainerSize;
    //PCMData pcmData;
}PCMFormat;

typedef struct {
    WMA_U16 wFormatTag;
    WMA_U16 nChannels;
    WMA_U32 nSamplesPerSec;
    WMA_U32 nAvgBytesPerSec;
    WMA_U16 nBlockAlign;
    WMA_U16 nValidBitsPerSample;
    //WMA_U32 nChannelMask;
    WMA_U16 wEncodeOpt;
 //   WMA_U16 wAdvancedEncodeOpt;
 //   WMA_U32 dwAdvancedEncodeOpt2;
} WMAFormat;


typedef struct _audecInputBufferInfo {
    WMA_U8*   pbIn;
    WMA_U32   cbIn;
    WMA_Bool  fNewPacket;
    WMA_Bool  fNoMoreInput;
    WMA_Bool  fTime;
    WMA_I64   rtTime;
    WMA_I32   cSkipBits;
    void*     pfnDescramble;
} audecInputBufferInfo;

typedef WMARESULT (*PFNGETMOREDATA)(void* dwUser, audecInputBufferInfo*);


typedef enum _audecState {
  audecStateDone = 0,
  audecStateInput,
  audecStateDecode,
  audecStateGetPCM
} audecState;

// If you use any of the structures below, please memset() the entire struct to 0 before setting its fields.
// This will ensure reasonable default behavior if a new member is added but the calling code is not updated.

typedef struct _audecInitParams {
    WMA_I32 iMemBufUsed; // [out]
    PFNGETMOREDATA pfnGetMoreData; // [in] set to NULL for normal (callbackless) mode
    void*    dwUser; // [in] context for pfnGetMoreData (ignored if pfnGetMoreData==NULL)
    WMA_Bool fSPDIF; // [in] TRUE for SPDIF mode, FALSE for packetized (normal) mode
} audecInitParams;

typedef struct _audecInputParams {
    WMA_I32 cSkipBits;         // SPDIF only - see above
    void* pfnDescramble;
} audecInputParams;

typedef struct _audecDecodeParams {
    WMA_I32 cbFrameBytesInLastBuffer; // [out] SPDIF only, obsolete - superseded by an SPDIF payload header field
} audecDecodeParams;

typedef struct _audecGetPCMParams {
    WMA_U32 dwReserved;
} audecGetPCMParams;




#define WMA_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
#define WMA_IsEqualGUID(rguid1, rguid2) (!memcmp((void *)rguid1, (void *)rguid2, sizeof(GUID)))



#define LTRT_SRC_CHANNELS (6)


typedef struct CSpeechObjectDecoder CSpeechObjectDecoder;
//
typedef enum {BEGIN_PACKET, SEEK_TO_NEXT_PACKET, BEGIN_FRAME, FRAME_HDR, BEGIN_SUBFRAME, DECODE_SUBFRAME,
    DECODE_TRAILERBIT, END_SUBFRAME1, END_SUBFRAME2} DecodeStatus;
typedef enum {FHDR_DONE, FHDR_SIZE, FHDR_PREV, FHDR_ADJUST_TIMESTAMP} FHdrDecodeStatus; 
typedef enum {SUBFRM_HDR, SUBFRM_COEFDEC_LOSSY, SUBFRM_COEFDEC_MLLM,
    SUBFRM_COEFDEC_PLLM, SUBFRM_REC_MLLM, SUBFRM_REC_LOSSY, SUBFRM_REC_PLLM,
    SUBFRM_SAVE_PREV, SUBFRM_DONE} SubFrmDecodeStatus;
typedef enum {HDR_SIZE, HDR_RAWPCM, HDR_SEEKABLE, HDR_QUANT,
    HDR_V3_QUANT_MODIFIER, HDR_NOISE1, HDR_NOISE2, HDR_MSKUPD, HDR_BARK, HDR_DONE,
    HDR_INFO_SEEKABLE_BEGIN, HDR_DO_ACFILTER,  
    HDR_ACFILTER_ORDER, HDR_ACFILTER_SCALING, HDR_ACFILTER, HDR_MCLMS_ORDER, HDR_MCLMS_SCALING, HDR_MCLMS_SEND,
    HDR_MCLMS_COEFF_BITS, HDR_MCLMS_COEFF_A,HDR_MCLMS_COEFF_B,
    HDR_RES_MEM_SCALING, HDR_QSTEPSIZE_B4_PLLM, HDR_PURE_IN_MLLM_FIRST_FRM, HDR_MLLM_FILTER, HDR_V3_LPC_COEF,
    HDR_MLTCHL_MIX_SEQ, HDR_PADDED_ZEROS, HDR_PADDED_ZEROS_B, HDR_V2_POWER} HdrDecodeStatus; //and a lot more

typedef enum {VLC, FRAME_END, NORMAL, ESCAPE, TBL_INDEX, ESCAPE_LEVEL, ESCAPE_RUN} RunLevelStatus;


typedef enum {STEREO_INVALID = -1, STEREO_LEFTRIGHT = 0, STEREO_SUMDIFF} StereoMode;
typedef enum {RLCTBL_SM=0, RLCTBL_SS} RlcTblType;
typedef enum {CONFIG_CURRFRM = 0, CONFIG_NEXTFRM = 1} ConfigFrame;
#define BITDEPTH_ID(validBits, bytePerSample)  (((validBits - 1) << 2) | (bytePerSample - 1))

typedef enum {BITDEPTH_24   = BITDEPTH_ID(24, 3),
              BITDEPTH_2024 = BITDEPTH_ID(20, 3),
              BITDEPTH_16   = BITDEPTH_ID(16, 2)} BITDEPTH;

typedef enum {CODEC_NULL, CODEC_STEADY, CODEC_DONE, CODEC_BEGIN, CODEC_LAST, CODEC_ONHOLD, CODEC_HEADER, CODEC_DATA} Status;
typedef enum {FMU_DONE = 0, FMU_QUANTIZE, FMU_PROCESS} FMU_STATUS;
typedef enum {FFT_FORWARD = 0, FFT_INVERSE} FftDirection;






typedef struct WmaGetDataParam
{
    void *m_dwUser;
    Bool m_fTimeIsValid;
    I64  m_iTime;
} WmaGetDataParam;


typedef FastFloat QuantStepType;
typedef WMA_U32 BPSType;

// currently only needed for cx, but good structure to have to store per
// channel elements which should not be separate for encoder buckets
// don't put ifdef around elements here, otherwise we end up with 0 element
// structure for non BUILD_WMAPROLBRV2 builds (which may be bad??)
typedef struct SubFrameConfigInfo
{ 
    I16  m_cSubFrame;
    I16* m_rgiSizeBuf; //include prev and next subfrm
    I16* m_rgiSubFrameSize;
    I16* m_rgiSubFrameStart;
    WMA_U8*  m_rgfMaskUpdate;

} SubFrameConfigInfo;

typedef struct  
{
    //whenever the memory gest moved to buckets, update is needed
    // Decoder and Global Members
    I32*           m_rgiCoefQ;                      //quantized coef
    Int*           m_rgiMaskQ;                      //quantized maskq ((could be I16))

    WMA_U8*            m_rgbBandNotCoded;               //band not coded
    FastFloat*     m_rgffltSqrtBWRatio;             //MidRate/LowRate for Bands not coded
    Int*           m_rgiNoisePower;
    const WMA_U16*     m_rgiHuffDecTbl;                 //decoder only

    const WMA_U16*     m_rgiRunEntry;                   //decoder only        
    const WMA_U16*     m_rgiLevelEntry;                 //decoder only
    Int            m_cSubbandActual;
    Int            m_iPower;                        //channel power
    Int            m_iActualPower;                  // Power as suggested by CoefQ/CoefRecon
    UInt*          m_rguiWeightFactor;              //weighting factor
    CBT*           m_rgiCoefRecon;                  //reconstructed coef
    CBT*           m_rgiPCMBuffer;                  // PCM output buffer pointer
    Int            m_iMaxMaskQ; 
    StereoMode     m_stereoMode;                    // would be per bucket per channel

#define CURRGETPCM_INVALID  0x7FFF

    //wchen: these were defined as V4V5_COMPARE, retired
    //wchen: we may not need these to the lookup table case
    BP2Type        m_fiSinRampUpStart;
    BP2Type        m_fiCosRampUpStart;
    BP2Type        m_fiSinRampUpPrior;
    BP2Type        m_fiCosRampUpPrior;
    BP2Type        m_fiSinRampUpStep;

    I16            m_iCurrSubFrame;                    // for tiling
    I16            m_iCurrCoefPosition;   // current subframe starting point    
    I16            m_cSubFrameSampleHalf;
    I16            m_cSubbandAdjusted;
    I16            m_iSizePrev;
    I16            m_iSizeCurr;
    I16            m_iSizeNext;
    I16            m_iCoefRecurQ1;
    I16            m_iCoefRecurQ2;
    I16            m_iCoefRecurQ3;
    I16            m_iCoefRecurQ4;

    Int     m_cSubFrameSampleHalfAdjusted;

    // The following is NOT YET INTEGERIZED but after it is,
    // it should be moved into the #ifndef BUILD_INTEGER above
    CoefType*      m_rgCoefRecon;                //reconstructed coef soon to be removed
    CoefType *m_rgCoefReconBase;
    FinalWeightType m_wtMaxWeight;
    SubFrameConfigInfo* m_rgsubfrmconfig;             // Use CONFIG_CURRFRM  & CONFIG_NEXTFRM for indexing.
    WMA_U16 m_cLastCodedIndex;  // To reduce decoder complexity in V3 & use in fex
    //WMA_U32 m_cSamplesLeft;

} PerChannelInfo;


typedef struct tagRandState {
        I32 iPrior;         // prior value
        WMA_U32 uiRand;         // current value
} tRandState;

typedef struct CAudioObjects CAudioObject;

typedef enum {LPC_MODE=0,BARK_MODE} WeightMode;


typedef struct TileConfigInfo
{
    SubFrameConfigInfo *m_psfci;
    Int m_iSubFrame; // index of subframe withing SubFrameConigInfo
    Int m_iSubFrameSize;
    Int m_iSubFrameStart;
    Int m_cChannels;
    WMA_U32 m_uChannelMask;
    WMA_U8  m_bCodingFex;
    Int m_iCodingFexMaxFreq;
} TileConfigInfo;

typedef struct CAudioObjects
{
    //Step Size
    QuantStepType  m_qstQuantStep;

    // packetization (has nothing to do with the rest)
    Int m_iPacketCurr;
    Int m_cBitPackedFrameSize;
//    Int m_cBitPacketLength;

    //utility vars for entropy decoding for high rate only
    I32 m_cRunOfZeros;
    I32 m_iLevel; 
    Int m_iSign;
    WMA_U16 m_cChannel;
    // original number of channels
    //WMA_U16 m_cOrigChannel;
    // channels coded using base codec
    //WMA_U16 m_cCodedChannel;
    //WMA_U16 m_cSaveChannel;


    Bool    m_fNoiseSub; 
    BPSType m_BitsPerSample;
    BPSType m_WeightedBitsPerSample;

    Int m_iMaxEscSize;          // in bits
//    Int m_iMaxEscLevel;         // (1<<m_iMaxEscSize)
    
    Int     m_iVersion;
    I32     m_iEncodeOpt;
//    I32     m_iAdvancedEncodeOpt;
//    WMA_U32     m_uAdvancedEncodeOpt2;
    Status  m_codecStatus;          //current status of the codec
    Bool    m_fSeekAdjustment;
    Int     m_iSamplingRate;        //audio sampling rate in Hz
    Int     m_cBytePerSec;
    WMA_U32     m_nBytePerSample;
    WMA_U32     m_nBitsPerSample;       // Same as m_nBytePerSample * 8, just avoid the calculation
    //BITDEPTH m_iBitDepthSelector;
    PCMData  m_dataType;
//    WMA_U32     m_nChannelMask;
//    WMA_U32     m_nOrigChannelMask;
//    WMA_U32     m_nCodedChannelMask;
//    WMA_U32     m_nSaveChannelMask;
    WMA_U16     m_nValidBitsPerSample;

    I32     m_iPCMSampleMin;
    I32     m_iPCMSampleMax;    
    I16     m_iCurrReconCoef;       //which coef we are doing; util. var for state machine
    Bool    m_fAllowSuperFrame;
    Bool    m_fAllowSubFrame;
    Bool    m_fV5Lpc;

    Int     m_iSubFrameSizeWithUpdate;
    Int     m_iMaxSubFrameDiv;      //maximum no. division into subwindows
    Int     m_cMinSubFrameSample;   //min size of subframes in current frame; many change from frame to frame
    Int     m_cMinSubFrameSampleHalf;   //min size of subframes in current frame; many change from frame to frame
    //Int     m_cMinSubFrameSampleQuad;   //min size of subframes in current frame; many change from frame to frame
    Int     m_cPossibleWinSize;

    //should be reset every subfrm in next version
    Int     m_cBitsSubbandMax;      //no. of bits for m_cSubband; 
    Int     m_cFrameSample;         //no. of input/output samples = 2 * cSubband
    Int     m_cFrameSampleHalf;     //no. of input/output samples = cSubband
                                               // prefast Integer overflow annotation winos #1121910
    //Int     m_cFrameSampleQuad;     //no. of input/output samples = cSubband / 2

    Int     m_cLowCutOff;           //How many coeffs to zero at the low end of spectrum
    Int     m_cHighCutOff;          //How many coeffs to zero at the high end of spectrum
    Int     m_cLowCutOffLong;
    Int     m_cHighCutOffLong;      

    Int     m_iWeightingMode;
    StereoMode  m_stereoMode;       // left-right or sum-difference coding 
    Int     m_iEntropyMode;         //entropy coding mode
    //Float   m_fltDitherLevel;       //=.12; Relative intensity of Roberts' pseudo-random noise quantization
    Int     m_iQuantStepSize;
    BP2Type m_fltDctScale;
    Int     m_cValidBarkBand;       //valid bark band in range; some are out of range in the subband decompositio
    const Int*  m_rgiBarkIndex;     //corresponding coef index for each valid bark
    //Int     m_cSubWooferCutOffIndex;//zeros after this
    I32*    m_rgiCoefQ;             // just a pointer

    //random accessed memory
    //overall
    PerChannelInfo* m_rgpcinfo; //this is just a pointer now

    //transform
    Int         m_iCoefReconSize;
    CBT*    m_rgiCoefReconOrig;
    Int m_iCoefBufSize;

    //weighting
    Int*    m_rgiMaskQ;
    Int*    m_rgcValidBarkBand;
    Int*    m_rgiBarkIndexOrig;

    I32        *m_rgiDiscardSilence;
    I32         m_iPCMReconStart;   // the start point in PCM recon buffer for output
    I32         m_iPCMReconEnd;     // the end point in PCM recon buffer
    //Float   m_fltFirstNoiseFreq;
    int     i_fltFirstNoiseFreq;
    int     m_ifltFirstNoiseFreq;
    Int     m_iFirstNoiseBand;
    Int     m_iFirstNoiseIndex;

    //only used for NoiseSub mode
    Int*        m_rgiFirstNoiseBand;
    WMA_U8*         m_rgbBandNotCoded;
    FastFloat*  m_rgffltSqrtBWRatio;
    Int*        m_rgiNoisePower;
    UInt   *m_rguiWeightFactor;   //share with m_rgiMaskQ when bark
    WMA_U32 m_iFrameNumber; // frame counter to the common code

    // 1/2^n and 2^n transforms
    //Bool    m_fHalfTransform;
    //Bool    m_fPad2XTransform;
    Int     m_iXformSamplingRate;
    //Int     m_iAdjustSizeShiftFactor;
    //Bool    m_fWMAProHalfTransform;  // To reduce WMA Pro decoder memory requirements for half-transform
        
    // the following values are adjusted to reflect HalfTransform or PAd2XTransform
    // They are used for the DCT and for Reconstruction.
    Int     m_cFrameSampleAdjusted; 
    Int     m_cFrameSampleHalfAdjusted;
    Int     m_cHighCutOffAdjusted;
    // m_iCoefRecurQ1..4 and Trig values only exist in their adjusted states
    // Function Pointers
    USE_MIPS32 WMARESULT (*aupfnInverseQuantize) (struct CAudioObjects* pau,
        PerChannelInfo* ppcinfo, Int* rgiWeightFactor);
    WMARESULT (*aupfnGetNextRun) (void* paudec, PerChannelInfo* ppcinfo);
    //WMARESULT (*aupfnReconSample) (struct CAudioObjects* pau, I32* piOutput, WMA_U16 cSamples);
    USE_MIPS32 WMARESULT (*aupfnDctIV) (CAudioObject* pau, CoefType* rgiCoef, BP2Type fltAfterScaleFactor, WMA_U32 *piMagnitude,
        const Int cSubbandAdjusted, const Int iFrameNumber,
        const Int iCurrSubFrame, const Int cFrameSampleAdjusted,
        const Int cSubFrameSampleAdjusted);

    tRandState m_tRandState;
    //CoefType      *m_rgfltCoefDst;           // Temporary for inverse channel transform in V3.
    //CoefType     **m_rgpfltCoefGrpSrc;       // Temporary for inverse channel transform in V3.

    // V3 stuff: These are really in encoder buckets or decoder.
 //   Int     m_cChannelGroup;
    I16     m_cChInTile;                    //how many src channels are included
    I16*    m_rgiChInTile;                  //which src chs are included
    //Bool m_fByteAlignFrame;
    //Bool m_fWriteFrameSize;
 //   Int m_cComprFrameSizeBits;
 //   Int m_cBitsBytePacketLength;
 //   Int m_cBitsBitsPacketLength;
 //   Int m_cBytePacketLength; 

    I32     m_iSampleMaxValue;
    I32     m_iSampleMinValue;
    WMA_U16     m_cLastCodedIndex;     // To reduce decoder complexity in V3
    // Temporary space required for auGetPCM
    //WMA_U16  *m_rgcSamplesREQ;
    Int *m_rgiCurrSubframe;
    Bool m_fUES;
    Int  m_iFrameStart; // 1/4 frame size into starting point of frame
}CAudioObject_t;


typedef struct CAudioObjectDecoders CAudioObjectDecoder;

typedef struct CWMAInputBitStream {

//wchen: add for streaming mode
    PFNGETMOREDATA  m_pfnGetMoreData;
    void*           m_pUser;
    CAudioObjectDecoder*  m_dwOwner; // not really 'dw' these days

    WMA_U32     m_dwHeaderBuf;      // hold the packet header data
    WMA_U32     m_dwHeaderBufTemp;  // temporarilly, until frame end

    // The following four variables, while similar in spirit, are used in
    // slightly different ways in packet (normal) mode vs SPDIF mode.
    // In SPDIF mode, BufferBegin refers to the most recent buffer supplied
    // by the caller, and Buffer refers to the current section between gaps.
    // In normal mode, BufferBegin is what it says below and Buffer is the
    // most recent buffer supplied by the caller.
    //
    // Historical note: m_cbInputBuffer and m_pbInputBuffer below could probably
    // be used just as effectively in SPDIF mode.  However, they were only added
    // in v10 and did not exist in v9 at the time the modification to use
    // m_pBufferBegin and m_cbBufferBegin for SPDIF was made in v9.  The SPDIF
    // modification made in v9 was then propagated to v10 verbatim, without
    // converting the SPDIF code to use m_pbInputBuffer and m_cbInputBuffer.
    //
    WMA_U8      *m_pBufferBegin;    // begining of packet for reset
    WMA_U32     m_cbBuflenBegin;    // used in association of m_pBufferBegin  

    // An input is equal or smaller than a packet. For example, packet size is
    // 1024 bytes and one input size is 256 bytes. Input must be aligned with
    // packet. m_pBufferBegin points to the current packet header if 
    // the current input is aligned with the current packet. Otherwise, it is
    // meaningless. m_pbInputBuffer points to the current input buffer head.
    // m_cbInputBuffer is the size of current input.
    // m_pBuffer points to the the head of remaining (undecoded) bytes in input buffer.
    // Fractional bits are saved in m_dwDot and m_dwDotT.
    WMA_U8 *    m_pbInputBuffer;    // point to the beginning of the input buffer. 
                                //Doens't change until get a new input in ibstrmAttach
    WMA_U32     m_cbInputBuffer;    // size of the input buffer. 
                                //Doens't change until get a new input in ibstrmAttach
    WMA_U8     *m_pBuffer;         // This guy moves forward when we decoding bits.
    WMA_U32    m_cbBuflen;         // This guy decrease when we decoding bits.
    WMA_U32     m_dwDot;
    WMA_U32     m_dwBitsLeft;
    WMA_U32     m_dwDotT;           // hold extra bits for m_dwDot
    WMA_U32    m_cBitDotT;         
    Int     m_iPrevPacketNum;
    Bool    m_fAllowPackets;
    Bool    m_fSuppressPacketLoss;
    
    Int     m_cFrmBitCnt;

    // SPDIF gap
    //Bool m_fDeferredGap;
    //WMA_U32  m_cbToDeferredGap;

    Bool m_fNoMoreInput;
    //WMA_U32  m_cbLastProcessedGapLocationBackFromEndOfLastBuffer;
    WMA_U8  m_uLastHeaderByte;

} CWMAInputBitStream;


//typedef struct 
//{
//    WMA_U16 nPlayerOpt;        // Bit fields based on above defines
//    WMA_I32 *rgiMixDownMatrix; // Can be null to invoke defaults
//    WMA_I32 iPeakAmplitudeRef;
//    WMA_I32 iRmsAmplitudeRef;
//    WMA_I32 iPeakAmplitudeTarget;
//    WMA_I32 iRmsAmplitudeTarget;
//    WMA_I16 nDRCSetting;       // Dynamic range control setting
//    WMA_I32 iLtRtBufsize;
//    WMA_I32 iLtRtQuality;
//}WMAPlayerInfo;

typedef struct CAudioObjectDecoders 
{
    CAudioObject* pau;
    PerChannelInfo* m_rgpcinfo; //this is just a pointer now
    
    //packetization stuff
    Bool  m_fPacketLoss;
    I16   m_cFrmInPacket;
    //Bool  m_bGotValidFilterInfo; // Have we decoded valid LMS filter info?
  
    DecodeStatus       m_decsts;
    SubFrmDecodeStatus m_subfrmdecsts;
    HdrDecodeStatus    m_hdrdecsts;
    FHdrDecodeStatus   m_fhdrdecsts;
    RunLevelStatus     m_rlsts;
    //I32                m_iSubfrmEscDataBits;

    Int                m_cBitSeekToNextPacket;
    //WMA_U32                m_cBitsOverCurrPkt;

    Int                m_cChannelsLeft;
    Int                m_iSign;

    // V3 LLM. Chao. Added. more varibles to record decoder status for supporting decoder onhold/resume.
    //I8                 m_iCurrPart;            //which part we are doing
    //I16                m_iLMSCurrCoeff;
    //I16                m_iCurrLPCCoef; //which lpc filter coefficient we are doing.

    // Common to V2, V3
    I16                m_iChannel;  //current channel we are doing
    I16                m_iBand;     //current band we are doing
    I16                m_iTtlNTBs;
    Bool               m_fNewTimeBase;

    Bool               m_iContinuousDecodeCountdown; // Countdown to first packet w/ continuous adj
    I64                m_iNewTimeBase;//in 100nano second
    I64                m_iNewTimeBaseTemp;// The second (later one) NewTimeBase.
    I64                m_iCurrPresTime;//in samples

    WMA_U8**           m_rgpiRecon; // Used to manage recon pointers in audecGetPCM

    // iCurrReconCoef is in pau.
    //WMA_U16                m_iDivisorWidth;
    //WMA_U32                m_iResQ;
    //WMA_U32                m_iResQBits;
    //WMA_U32                m_iRem;
    Bool               m_fLastSubFrame;
    CWMAInputBitStream m_ibstrm;
    I16                m_cMaxRun;
    I16                m_iMaxLevelInVlc;


    // INTERPOLATED_DOWNSAMPLE
    //Bool    m_fUpsample2x;
    //Bool    m_fLowPass;             // Specify independently of downsampling
    //Bool    m_fResample;          // Eg, Downsample 32kHz output to 22kHz for some devices
    //Int     m_iInterpolSrcBlkSize;  // Size of 1 indivisible source block
    //Int     m_iInterpolDstBlkSize;  // Size of 1 indivisible destination block

    Int     m_iDstSamplingRate;
    //Int     m_iInterpolCurPos;
    Int        m_cDstChannel;          // Destination channels
    //WMA_U32        m_nDstChannelMask;      // Destination channel mask
    WMA_U32        m_nDstBytePerSample;    // Destination resolution, bytes per sample
    //WMAPlayerInfo m_wmapi;

    WMARESULT (*m_pfnDecodeSubFrame) (CAudioObjectDecoder* paudec);  //Nelson 2009/06/17
    WMARESULT (*m_pfnDecodeCoefficient) (CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo);   
    void      (*m_pfnResetEntropyCoder)(CAudioObjectDecoder *paudec);
    audecState m_externalState; // which public function should be called next
    Bool m_fNeedHeader;
    WMA_U32 m_cSamplesReady;
                                // Is the current frame broken? (bit stream corruption)
    Bool m_bBrokenFrame;        // This determines whether the call to GetPCM should be made
                                // Impacts only scenarios where GetPCM is called with a small buffer.

    WMARESULT (*m_pprvNewInputBuffer)(CAudioObjectDecoder *paudec, audecInputBufferInfo *pBuf);

} CAudioObjectDecoder_t; 

/////////////////////////////////////////////////////////////////////////

/* parser state  */
typedef enum
{
  //  csWMA_NotValid = 0,

    csWMA_HeaderStart,
  //  csWMA_HeaderError,

    csWMA_NewAsfPacket,

    /* packet parsing states */

    csWMA_DecodePayloadStart,
    csWMA_DecodePayload,
    csWMA_DecodeAudioData,
    csWMA_DecodePayloadEnd,
    csWMA_DecodeCompressedPayload,

    csWMA_End_

} tWMAParseState;


typedef struct tagWMA_MetaDataDescRecords 
{
    WORD     wLangIdIndex;   // Specifies the index of the language ID in the Language List Object
    WORD     wStreamNumber;  // Specifies whether the entry applies to a specific media stream or 
                                // whether it applies to the whole file. A value of 0 in this field 
                                // indicates that it applies to the whole file; otherwise, the entry 
                                // applies only to the indicated stream number.
    WORD     wNameLenth;     // Specifies the number of valid bytes stored in the Name field.
    WORD     wDataType;      // Specifies the type of information being stored. The following values are recognized:
                                // Value Type   Description
                                //  0x0000      Unicode string. The data consists of a sequence of Unicode characters.
                                //  0x0001      BYTE array. The type of the data is implementation-specific.
                                //  0x0002      WMA_BOOl. The data is 2 bytes long and should be interpreted as a 16-bit unsigned integer. Only 0x0000 or 0x0001 are permitted values.
                                //  0x0003      DWORD. The data is 4 bytes long and should be interpreted as a 32-bit unsigned integer.
                                //  0x0004      QWORD. The data is 8 bytes long and should be interpreted as a 64-bit unsigned integer.
                                //  0x0005      WORD. The data is 2 bytes long and should be interpreted as a 16-bit unsigned integer.
                                //  0x0006      GUID. The data is 8 bytes long and should be interpreted as a 128-bit GUID.
                                //  0x8000      Extended Unicode string. The data consists of a sequence of Unicode characters.
                                //  0x8001      Extended BYTE array. The type of the data is implementation-specific.
                                //  0x8002      Extended WMA_BOOl. The data is 2 bytes long and should be interpreted as a 16-bit unsigned integer.  Only 0x0000 or 0x0001 are permitted values.
                                //  0x8003      Extended DWORD. The data is 4 bytes long and should be interpreted as a 32-bit unsigned integer.
                                //  0x8004      Extended QWORD. The data is 8 bytes long and should be interpreted as a 64-bit unsigned integer.
                                //  0x8005      Extended WORD. The data is 2 bytes long and should be interpreted as a 16-bit unsigned integer.
                                //  0x8006      Extended GUID. The data is 8 bytes long and should be interpreted as a 128-bit GUID.
    DWORD     dwDataLength;    // Specifies the length in bytes of the Data field.
    WORD      *pwName;        // Specifies the name that uniquely identifies the attribute being described. Names are case-sensitive.
    BYTE      *pData;         // Specifies the actual metadata being stored. The Data field should be interpreted according to the value 
                                // stored in the Data Type field. If the Data Type is one of the extended values, this field may not contain 
                                //any data if the file is being streamed over the wire.
} WMA_MetaDataDescRecords;


typedef struct tagWMA_MetaDataEntry 
{
    WORD     m_wDescRecordsCount;
    WMA_MetaDataDescRecords *pDescRec;
} WMA_MetaDataEntry;


#define FILEPROPFLAG_BROADCAST   1


enum {
    ECD_STRING = 0,
    ECD_BINARY = 1,
    ECD_BOOL = 2,
    ECD_DWORD = 3,
    ECD_QWORD = 4,
    ECD_WORD = 5
};

typedef struct _ECD_DESCRIPTOR {
    tWMA_U16         cbName;
    tWMA_U16     *pwszName;
    tWMA_U16         data_type;
    tWMA_U16         cbValue;
    union {
        tWMA_U16 *pwszString;
        tWMA_U8 *pbBinary;
        tWMA_Bool *pfBool;
        tWMA_U32 *pdwDword;
        tWMA_U64 *pqwQword;
        tWMA_U16  *pwWord;
    } uValue;
} ECD_DESCRIPTOR;


typedef struct tagWMAExtendedContentDescription
{
    tWMA_U16 cDescriptors;             // number of descriptors
    ECD_DESCRIPTOR *pDescriptors;  // pointer to all the descriptors
} tWMAExtendedContentDesc;


typedef enum tagWMAFileStatus
{
    cWMA_NoErr,                 /* -> always first entry */
                                /* remaining entry order is not guaranteed */
    cWMA_Failed,
    cWMA_BadArgument,
    cWMA_BadAsfHeader,
    cWMA_BadPacketHeader,
    cWMA_BrokenFrame,
    cWMA_NoMoreFrames,
    cWMA_BadSamplingRate,
    cWMA_BadNumberOfChannels,
    cWMA_BadVersionNumber,
    cWMA_BadWeightingMode,
    cWMA_BadPacketization,

    cWMA_BadDRMType,
    cWMA_DRMFailed,
    cWMA_DRMUnsupported,

    cWMA_DemoExpired,

    cWMA_BadState,
    cWMA_Internal,               /* really bad */
    cWMA_NoMoreDataThisTime 
} tWMAFileStatus;


typedef enum tagWMAFileVersion
{
    cWMA_V1 = 1,
    cWMA_V2 = 2

} tWMAFileVersion;


typedef enum tagWMAFileChannels
{
    cWMA_C_Mono = 1,
    cWMA_C_Stereo = 2

} tWMAFileChannels;


typedef  struct tagWMAFileHeader
{
    tWMAFileVersion version;         /* version of the codec */
    tWMA_U32 sample_rate;  /* sampling rate */
    tWMAFileChannels num_channels;   /* number of audio channels */
    tWMA_U32 duration;               /* of the file in milliseconds */
    tWMA_U32 bitrate;                /* bit-rate of the WMA bitstream */
} tWMAFileHeader;


typedef struct tagWMAFileContDesc
{
    /* *_len: as [in], they specify how large the corresponding
     *        buffers below are.
     *        as [out], they specify how large the returned
     *        buffers actually are.
     */

    tWMA_U16 title_len;
    tWMA_U16 author_len;
    tWMA_U16 copyright_len;
    tWMA_U16 description_len;   /* rarely used */
    tWMA_U16 rating_len;        /* rarely used */

    /* these are two-byte strings
     *   for ASCII-type character set, to convert these
     *   into a single-byte characters, simply skip
     *   over every other bytes.
     */

    unsigned char *pTitle;
    unsigned char *pAuthor;
    unsigned char *pCopyright;
    unsigned char *pDescription;
    unsigned char *pRating;

} tWMAFileContDesc;


typedef  struct tagWMAFileLicParams
{
    unsigned char *pPMID;       /* portable media id */
    tWMA_U32 cbPMID;            /* length of the pPMID buffer */

} tWMAFileLicParams;


typedef void * tHWMAFileState;
typedef  struct tagWMADateParams
{
    tWMA_U16 year;
    tWMA_U8 month;
    tWMA_U8 day;
} tWMADateParams;  



typedef  struct tagWMAFileHdrState
{
    unsigned char internal[ 
        
        // these offsets are dependent upon two factors
        // in wmaudio_type.h: the packing alignment and
        // the size of a pointer. Since the members of
        // 'tWMAFileHdrStateInternal' are not sorted by
        // size, this causes dead space to be inserted
        // between many members, and makes determining
        // the total size of the structure a real PITA.
        // Getting correct #'s between x86, x64, & PPC
        // builds has been a hassle.

        216 + 8 * sizeof(void*)

    ]; // additional 4 bytes for MBR support
    // unsigned char internal[212];
} tWMAFileHdrState;

#define DESC_NAME_MAX_LENGTH   64
typedef struct _MarkerEntry {
    QWORD   m_qOffset;
    QWORD   m_qtime;
    tWMA_U16    m_wEntryLen;
    tWMA_U32   m_dwSendTime;
    tWMA_U32   m_dwFlags;
    tWMA_U32   m_dwDescLen;
    tWMA_U16   m_pwDescName[DESC_NAME_MAX_LENGTH];
} MarkerEntry;

/* internal structure for the ASF header parsing */
typedef struct tagWMAFileHdrStateInternal
{
    U64     currPacketOffset;     /* not just for packets */
    U64     nextPacketOffset;

    /* ASF header */

    DWORD   cbHeader;
    DWORD   cbPacketSize;
    DWORD   cbAudioSize;
    DWORD   cPackets;
    DWORD   msDuration;
    DWORD   msPreroll;
    U64     cbFirstPacketOffset;
    U64     cbLastPacketOffset;
    DWORD   dwFilePropertiesFlags;

    /* audio prop */
    WORD    nVersion;
    WORD    wFormatTag;
    DWORD   nSamplesPerSec;
    DWORD   nAvgBytesPerSec;
    DWORD   nBlockAlign;
    WORD    nChannels;
    DWORD   nSamplesPerBlock;
    WORD    nEncodeOpt;
    WORD    nAdvancedEncodeOpt;
    DWORD   nAdvancedEncodeOpt2;
    
    // Added in V9
    WORD    wPCMFormatTag;
    WORD    wBitsPerSample; // container size
    WORD    wValidBitsPerSample; // actual valid data depth in the decoded stream
    DWORD   dwChannelMask;
    GUID    SubFormat;
    WORD    wOriginalBitDepth; // actual valid data depth in the original source (informational)
    
    /* DRM */
    
    BYTE    pbSecretData[32];
    DWORD   cbSecretData;
    BYTE    pbType[16];
    BYTE    pbKeyID[32];


    /* Content Description */
   tWMAFileContDesc     *m_pDesc;

    /* Extended Content Description */

    tWMAExtendedContentDesc *m_pECDesc;

    /* Marker */
    DWORD   m_dwMarkerNum;
    MarkerEntry *m_pMarker;

    /* License Store */
   // DWORD   m_dwLicenseLen;
    BYTE   *m_pLicData;

// Members added by Amit 
    WORD    wAudioStreamId;
    WMA_MetaDataEntry *ptMetaDataEntry;

    // Members added by Naveen for MBR support
    WORD    wTargetAudioStreamNumber;
    WORD    cAudioStreams;

} tWMAFileHdrStateInternal;

//typedef void * WMADecHANDLE;

/* internal structure for the WMAudio library state */
typedef struct tagWMAFileStateInternal
{
    tWMAFileHdrStateInternal hdr_parse;

    /* parse_state */
    
    tWMAParseState parse_state;

    /* payload parsing */

    U64   cbPayloadOffset;
    U64   cbPayloadLeft;
    U64   total_payload_size; //total payload size ; add for AV by Nelson 2010/03/23

    WMA_BOOl  bBlockStart;
    DWORD cbBlockLeft;

    /* packet parsing */

    PACKET_PARSE_INFO_EX ppex;

    PAYLOAD_MAP_ENTRY_EX payload;
    DWORD iPayload;
    WORD wPayStart;
    WORD AV_WMA_FLAG;    // add for AV by Nelson 2010/03/23

    WMA_BOOl    bHasDRM;
    DWORD   nSampleCount;
    void* hSPDTX;   // handle to spdif transmitter state machine
    char* szmdata;  // content descriptor metadata for spdif transmitter
    BYTE* pbIn;     // used only by spdif transmitter ( for input buffer )
    DWORD cbIn;     // used only by spdif transmitter ( for input buffer )
    DWORD nLeadingBursts;     // leading empty spdif bursts
    DWORD nTrailingBursts;    // trailing empty spdif bursts

    void* hWMA;     // handle to audio decoder
    audecState audecState; // audio decoder state

    BYTE *pCallBackBuffer;
   void *pPlayerInfo;
} tWMAFileStateInternal;



typedef enum { ModeLookFor, ModePeek, ModeGetFlush, ModePktHdr } GetMoreDataMode;
#define MASKQ_RESAMPLE_OFFSET 6
typedef struct MaskResampleInfo
{
   Int iMaskResampleRatio;
   Int iMaskResampleRatioPow;
   Int cValidBarkBandLatestUpdate;
} MaskResampleInfo;

typedef struct utemp_64
{
   unsigned int lo;
   unsigned int hi;
}utemp_64;

#define m_cSubband m_cSubFrameSampleHalf //to be used as in freq. domain

/*
typedef enum FexMvRangeType
{
    MvRangeBase = 0,
    MvRangePrevBand = 1,
    MvRangeFullNoOverwriteBase = 2,
    MvRangeFullOverwriteBase = 3
} FexMvRangeType;
*/

// =================================================================

extern const UInt getMask [33];
//for high rates only
extern const WMA_U32    g_rgiBarkFreqV2   [];
extern const WMA_U16    g_rgiHuffDecTblMsk[];
extern const WMA_U16    g_rgiHuffDecTbl16smOb[];
extern const WMA_U16    gRun16smOb[];   //can be a byte
extern const WMA_U16    gLevel16smOb[]; //can be a byte
extern const WMA_U16    g_rgiHuffDecTbl16ssOb[];
extern const WMA_U16    gRun16ssOb[];   //can be a byte
extern const WMA_U16    gLevel16ssOb[]; //can be a byte
extern GUID CLSID_CAsfHeaderObjectV0;
extern GUID CLSID_CAsfPropertiesObjectV2;
extern GUID CLSID_CAsfStreamPropertiesObjectV1;
extern GUID CLSID_CAsfContentDescriptionObjectV0;
extern GUID CLSID_AsfXAcmAudioErrorMaskingStrategy;
extern GUID CLSID_AsfXSignatureAudioErrorMaskingStrategy;
extern GUID CLSID_AsfXStreamTypeAcmAudio;
extern GUID CLSID_AsfXStreamTypeAcmVideo;
extern GUID CLSID_CAsfContentEncryptionObject;
extern GUID CLSID_CAsfExtendedContentDescObject;
extern GUID CLSID_CAsfMarkerObjectV0;
extern GUID CLSID_CAsfLicenseStoreObject;
extern GUID CLSID_CAsfStreamPropertiesObjectV2;
extern GUID CLSID_CAsfExtendedStreamPropertiesObject;
extern GUID CLSID_AsfXStreamTypeDRMAuxData;
extern GUID CLSID_CAsfClockObjectV0;
extern GUID CLSID_AsfXMetaDataObject;
extern GUID CLSID_CAsfPacketClock1;



//for all other rates
extern const WMA_U16    g_rgiHuffDecTbl44smOb[];
extern const WMA_U16    gRun44smOb[];   //can be a byte
extern const WMA_U16    gLevel44smOb[];

extern const WMA_U16    g_rgiHuffDecTbl44ssOb[];
extern const WMA_U16    gRun44ssOb[];
extern const WMA_U16    gLevel44ssOb[]; //can be a byte

extern const WMA_U16    g_rgiHuffDecTbl44smQb[];
extern const WMA_U16    gRun44smQb[];
extern const WMA_U16    gLevel44smQb[];  //can be a byte

extern const WMA_U16    g_rgiHuffDecTbl44ssQb[];
extern const WMA_U16    gRun44ssQb[];
extern const WMA_U16    gLevel44ssQb[];  //can be a byte

extern const WMA_U16    g_rgiHuffDecTblNoisePower[];

extern QuantStepType g_qstQStepLUT[258];
extern   UInt g_SqrtFraction[1+SQRT_FRACTION_TABLE_SIZE];
extern   UInt g_InverseFraction[1+INVERSE_FRACTION_TABLE_SIZE];
extern   UInt g_InvQuadRootFraction[1+INVQUADROOT_FRACTION_TABLE_SIZE];
extern   UInt g_InvQuadRootExponent[BITS_LP_SPEC_POWER+1];
extern const MaskPowerType rgiMaskMinusPower10[MASK_MINUS_POWER_TABLE_SIZE];
extern const MaskPowerType rgiMaskPlusPower10[MASK_PLUS_POWER_TABLE_SIZE];
extern const SinCosTable * const rgSinCosTables[SINCOSTABLE_ENTRIES];

#ifndef __MIPS_4KE__
extern tWMA_I64 wma_macr_a0;
#endif  


#endif
