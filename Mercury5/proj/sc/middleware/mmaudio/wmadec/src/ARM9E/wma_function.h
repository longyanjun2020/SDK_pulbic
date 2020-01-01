#ifndef __WMA_DECODER_FUNCTION_INCLUDE_FILE__
#define __WMA_DECODER_FUNCTION_INCLUDE_FILE__


WMARESULT prvDecodeQuantStepV2 (CAudioObjectDecoder* paudec);
void    prvSetDecTable  (CAudioObjectDecoder* paudec,  PerChannelInfo* ppcinfo, I16 iSet);
void    USE_MIPS32 prvGetBandWeightLowRate (CAudioObjectDecoder* paudec);

WMARESULT huffDecGet(const WMA_U16 *pDecodeTable, CWMAInputBitStream *bitstream,
                     WMA_U32* puBitCnt, WMA_U32 *puResult, WMA_U32* puSign);

////////////////////////////////////////////////////////////////////////////////////////////////
void* audecNew (void *pMemBuf,const WMA_I32 iMemBufSize);
WMARESULT audecCheckInitParams(WMAFormat*, PCMFormat*, /*WMAPlayerInfo *pPI,*/
                               audecInitParams* pParams);
WMARESULT audecInit (void* paudec, WMAFormat* pWMAFormat, PCMFormat* pPCMFormat,
                                   /*WMAPlayerInfo *pPI,*/ audecState *paudecState,
                                   audecInitParams* pParams);
WMARESULT audecReset (void* paudec);
WMARESULT audecInput (void* paudec,
                      WMA_U8* pbIn, // [in]
                      WMA_U32 cbIn,
                      WMA_Bool  fNewPacket,
                      WMA_Bool fNoMoreInput,
                      WMA_Bool  fTime,
                      WMA_I64 rtTime,
                      audecState* paudecState, // [out]
                      audecInputParams* pParams // [in]
                     );
WMARESULT audecDecode (void* paudec,
                       WMA_U32* pcSamplesReady, // [out] - how much is availble from GetPCM()
                       audecState* paudecState, // [out]
                       audecDecodeParams* pParams // [out]
                      );

WMARESULT audecGetPCM (void* paudec,
                       WMA_U32 cSamplesRequested, // up to *pcSamplesReady (from audecDecode())
                       WMA_U32 *pcSamplesReturned, // [out] redundant with *pcbDstUsed below
                       WMA_U8* pbDst,
                       WMA_U32 cbDstLength, // ~ redundant with cSamplesRequested
                       WMA_U32* pcbDstUsed, // [out] redundant with *pcSamplesReturned above
                       /*WMA_I64* prtTime,*/ // [out] time stamp (in 100ns) of 1st sample returned
                       audecState *paudecState, // [out]
                       /*WMAPlayerInfo *pWmaPI,*/ // [in] - dynamic configuration of some Init params
                       audecGetPCMParams* pParams
                      );

tWMAFileStatus WMAFileDecodeCreate (tHWMAFileState* phstate);


tWMAFileStatus WMAFileDecodeInitEx (tHWMAFileState phstate, tWMA_U16 nDecoderFlags,
                                    tWMA_Bool bDropPacket, 
                                    tWMA_U32 nDstChannelMask,   
                                    tWMA_U32 nInterpResampRate,
                                    PCMFormat* pPCMFormat,
                                    tWMA_U16 wTargetAudioStream,
                                    WMA_U16  *VideoAudio_flag);

tWMAFileStatus AV_DecodeInitEx (tHWMAFileState phstate, unsigned char *config_data, int config_size);

extern tWMA_U32 WMAFileCBGetData (
    tHWMAFileState hstate,
    tWMA_U64 offset,
    tWMA_U32 num_bytes,
    tWMA_U8  **ppData);

extern tWMA_U32 WMAFileCBGetLicenseData (
    tHWMAFileState *pstate,
    tWMA_U32 offset,
    tWMA_U32 num_bytes,
    tWMA_U8  **ppData);
tWMAFileStatus WMAFileDecodeClose (tHWMAFileState* phstate);
tWMAFileStatus WMAFileDecodeInfo (tHWMAFileState hstate, tWMAFileHeader *hdr);
tWMAFileStatus WMAFileExtendedContentDesc (tHWMAFileState hstate, const tWMAExtendedContentDesc **pECDesc);
tWMAFileStatus WMAFileDecodeData (tHWMAFileState hstate, tWMA_U32 *pnDecodedSamples);
tWMA_U32 WMAFileGetPCM (tHWMAFileState hstate,
    tWMA_I16 *pi16Channel0, tWMA_I16 *pi16Channel1,
    tWMA_U32 iSizeOfChannel0,
    tWMA_U32 max_nsamples/*,
    tWMA_I64* piTimeStamp*/);
tWMAFileStatus WMAFileSeek (tHWMAFileState hstate, tWMA_U32 msSeek, tWMA_U32 *pmsActual);
tWMAFileStatus WMAFileSeekBase(tHWMAFileState hstate,
                                tWMA_U32 * pmsSeek,
                                tWMA_U32 * piPacket,
                                tWMA_U32 * pmsActual,
                                tWMA_Bool fProWMAEncoder,
                                tWMA_Bool fSeekToPacket);
WMARESULT prvDecodeInfo (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeData (CAudioObjectDecoder* paudec, WMA_U16* pcSampleReady,
                           I16* pcSampleSeekAdj);

WMARESULT prvDecodeFrameHeader (CAudioObjectDecoder* paudec);

void prvResetRunLevelState(CAudioObjectDecoder *paudec);

WMARESULT prvDecodeSubFrame (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeSubFrameHighRate (CAudioObjectDecoder* paudec);

WMARESULT prvDecodeSubFrameHeader (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeSubFrameHeaderLpc (CAudioObjectDecoder* paudec);
WMARESULT prvDecodeSubFrameHeaderNoiseSub (CAudioObjectDecoder* paudec);
WMARESULT prvGetNextRunDEC (void* pvoid, PerChannelInfo* ppcinfo);
USE_MIPS32 WMARESULT auReconCoefficentsHighRate (CAudioObject* pau, void* pcaller,PerChannelInfo* ppcinfo);

/////////////////////////////////////////////////////////////////

WMARESULT prvNewInputBuffer(CAudioObjectDecoder* paudec, audecInputBufferInfo* pBuf);

WMARESULT prvUpdateSubFrameConfig (CAudioObjectDecoder* paudec, Int iSizeNext);

WMARESULT prvDecodeCoefficientMono(CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo);
WMARESULT prvDecodeCoefficientStereo(CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo);
WMARESULT prvDecodeRunLevel  (CAudioObjectDecoder* paudec, PerChannelInfo* ppcinfo,Int iCoefFirst,Int iCoefLim);
//Int prvNumDstSamplesFromXFormSamples(CAudioObjectDecoder *paudec,Int nTransformSamples);
//void prvInterpolateInit(CAudioObjectDecoder *paudec, Int iSrcSampleRate,Int iDstSampleRate);
void *wma_mallocAligned(unsigned int size, int align_log);
void *wma_malloc(int size);


WMARESULT WMAFileGetInput (tWMAFileStateInternal *pInt, WMA_U8 **ppBuffer, WMA_U32 *pcbBuffer, WMAFileGetInputParam*);
tWMAFileStatus WMAF_UpdateNewPayload (tWMAFileStateInternal *pInt);

WMAERR WMA_LoadObjectHeader(tWMAFileHdrStateInternal *pInt, GUID *pObjectId, QWORD *pqwSize);
WMAERR WMA_LoadHeaderObject(tWMAFileHdrStateInternal *pInt, int isFull);
WMAERR WMA_LoadPropertiesObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize, int isFull);
WMAERR WMA_LoadAudioObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize, int isFull, WMA_U16  *VideoAudio_flag);
WMAERR WMA_LoadEncryptionObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize);
WMAERR WMA_LoadContentDescriptionObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize);
WMAERR WMA_LoadExtendedContentDescObject(tWMAFileHdrStateInternal *pInt, DWORD cbSize);
WMAERR WMA_ParseAsfHeader(tWMAFileHdrStateInternal *pInt, int isFull, WMA_U16  *VideoAudio_flag);
WMAERR WMA_ParsePacketHeader(tWMAFileStateInternal *pInt);
WMAERR WMA_ParsePayloadHeader(tWMAFileStateInternal *pInt);

WMAERR AV_AsfHeader(tWMAFileHdrStateInternal *pInt, unsigned char *config_data, int config_size);


void        ibstrmInit (CWMAInputBitStream* pibstrm, CAudioObjectDecoder* pOwner);
WMARESULT   ibstrmAttach(CWMAInputBitStream *pibstrm,   WMA_U8* pbSrc, I32 cbSrc, Bool fNewPacket, Bool fNoMoreInput, Int iVersion);
void ibstrmReset(CWMAInputBitStream *pibstrm);
void        ibstrmFlushOldBits(CWMAInputBitStream *pibs);
void        ibstrmResetPacket(CWMAInputBitStream *pibstrm); // reset to the beginning of packet
void        ibstrmLoadBits(CWMAInputBitStream *pibs, I32 iFirstBit, WMA_U8 uByte);
WMARESULT   ibstrmGetMoreData(CWMAInputBitStream *pibstrm, GetMoreDataMode mode, WMA_U32 cBitsNeeded);
WMARESULT   ibstrmPeekBits (CWMAInputBitStream *pibstrm, register UInt dwNumBits,
                            WMA_U32 *piNumBits);
WMARESULT   ibstrmLookForBits (CWMAInputBitStream *pibstrm, UInt dwNumBits);
WMARESULT   ibstrmFlushBits (CWMAInputBitStream *pibstrm, register UInt dwNumBits);
WMARESULT ibstrmGetBits (CWMAInputBitStream* pibstrm, register UInt dwNumBits,
                                    WMA_U32 *piResult);

WMARESULT prvInitCommonParameters(CAudioObject *pau,
                                  Int           iVersionNumber,
                                  Bool          fUES,
                                  Int           cSubband, 
                                  Int           cSamplePerSec, 
                                  WMA_U16           cChannel, 
                                  WMA_U32           nBytePerSample,
                                  WMA_U16           nValidBitsPerSample,
                                  //WMA_U32           nChannelMask,
                                  Int           cBytePerSec, 
                                  Int           cbPacketLength,
                                  WMA_U16           iEncodeOpt,
                                  //WMA_U16           uAdvancedEncodeOpt,
                                  //WMA_U32           uAdvancedEncodeOpt2,
                                  Int           iOutputSamplingRate,
                                  PCMData       dataType/*,
                                  WMAPlayerInfo *pWmaPlayerInfo*/);
WMARESULT prvInitCommonSecondaryFixed(CAudioObject *pau);
WMARESULT prvInitCommonAllocate(CAudioObject *pau, Bool bEncoder);
WMARESULT prvInitCommonResetOperational(CAudioObject *pau);
WMARESULT prvInitCommonSetFunctionPtrs(CAudioObject *pau);
WMARESULT prvResetPcInfoCommon(CAudioObject* pau, PerChannelInfo* rgpcinfo);
Int prvShiftTimeIndex(CAudioObject *pau);
QuantStepType qstCalcQuantStep( const Int iQuantStepSize, const Int cLeftShiftBits );
QuantFloat USE_MIPS32 prvWeightedQuantization(CAudioObject *pau, PerChannelInfo *ppcinfo, Int iBark);
void SetActualPower(const I32 *piCoefQ, const I32 iCount,
                    PerChannelInfo *ppcinfo, const Status codecStatus);
void SetActualPowerHighRate(const CBT *piCoefRecon, const int iCount,
                    PerChannelInfo *ppcinfo, const Status codecStatus);

//for noise sub and low rates only
WMARESULT prvInitNoiseSubSecondaryFixed (CAudioObject* pau);
WMARESULT prvInitNoiseSubSecondaryAllocated (CAudioObject* pau);
USE_MIPS32 WMARESULT prvInverseQuantizeMidRate (CAudioObject* pau, PerChannelInfo* ppcinfo, Int* rgiWeightFactor);
USE_MIPS32 WMARESULT prvInverseQuantizeLowRate (CAudioObject* pau, PerChannelInfo* ppcinfo, Int* rgiWeightFactor);
//private lpc functions
USE_MIPS32 WMARESULT prvLpcToSpectrum (CAudioObject* pau, const LpType* rgfltLpcCoef, PerChannelInfo* ppcinfo);
void prvInitInverseQuadRootTable (CAudioObject* pau);
WMA_I32 msaudioGetSamplePerFrame (WMA_I32   cSamplePerSec, 
                              WMA_U32   dwBitPerSec, 
                              WMA_I32   iVersion,
                              WMA_U16   wEncOpt);
CAudioObject* auNew (void);
WMARESULT prvInitOutputSampleFormatParameters(CAudioObject *pau,WMA_U32 nBytePerSample,PCMData dataType);
WMARESULT auInvChannelXForm (CAudioObject *pau);
void    auPreGetPCM (CAudioObject* pau, WMA_U16* pcSampleDecoded, I16* pcSamplesSeekAdj, Bool fSPDIF);
USE_MIPS32 WMARESULT auSubframeRecon(CAudioObject *pau);
WMARESULT auGetPCM (CAudioObject* pau, void* pHandle, WMA_U16* pcSample, WMA_U8** ppbDst, WMA_U32 cbDstLength, WMA_U16 cChannel);

void prvGetFramePCM( CAudioObject* pau, Int *piFramePCM );

void prvShiftPCMBuffer( CAudioObject* pau );
void prvCalcQ1Q2(const I16 iSizePrev, const I16 iSizeCurr,I16 *piCoefRecurQ1, I16 *piCoefRecurQ2);
void prvCalcQ3Q4(const I16 iSizeCurr, const I16 iSizeNext,const Int cSubFrameSampleHalfAdjusted,
                 I16 *piCoefRecurQ3, I16 *piCoefRecurQ4);
void prvInitDiscardSilence(CAudioObject *pau);
WMARESULT auReconSample(CAudioObject* pau, I32* piOutput, WMA_U16 cSamples);
WMARESULT auAdaptToSubFrameConfig (CAudioObject* pau);
WMARESULT auAdaptToSubFrameConfigDEC (CAudioObject* pau);
WMARESULT prvAdaptTrigToSubframeConfig(CAudioObject *pau);
void    auUpdateMaxEsc(CAudioObject* pau, Int iQuantStepSize);
USE_MIPS32 WMARESULT auDctIV(CAudioObject* pau, CoefType* rgiCoef, BP2Type fltAfterScaleFactor, WMA_U32 *piMagnitude,
                  const Int cSubbandAdjusted, const Int iFrameNumber,const Int iCurrSubFrame, const Int cFrameSampleAdjusted,
                  const Int cSubFrameSampleAdjusted);
void    auResampleWeightFactorLPC (CAudioObject* pau, PerChannelInfo* ppcinfo);
void    auLsp2lpc(CAudioObject* pau, WMA_U8 *lsfQ, LpType *lpc, Int order);
void    prvSetBarkIndex (CAudioObject* pau);
WMARESULT prvInverseQuantizeHighRate (CAudioObject* pau, PerChannelInfo* ppcinfo, Int* rgiWeightFactor);
USE_MIPS32 void    prvFFT4DCT(CoefType data[], Int nLog2np, FftDirection fftDirection);
#endif

