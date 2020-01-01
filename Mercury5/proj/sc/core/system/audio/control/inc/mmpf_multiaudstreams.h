#ifndef _MMPF_MULTIAUDSTREAMS_H_
#define _MMPF_MULTIAUDSTREAMS_H_

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

AUTL_RINGBUF *MMPF_Audio_GetStreamBufHandle(void);
void MMPF_Audio_InitInStreamBufHandle(MMP_SHORT *sBufAddr, MMP_ULONG ulBufSize);
void MMPF_Audio_AdvanceInStreamBufReadPtr(MMP_ULONG ulSize);
void MMPF_Audio_AdvanceInStreamBufWritePtr(MMP_ULONG ulSize);
MMP_ULONG MMPF_Audio_InStreamBufDataAvailable(void);
MMP_ULONG MMPF_Audio_InStreamBufFreeSpace(void);
MMP_BOOL MMPF_Audio_InStreamBufFull(void);
void MMPF_Audio_ReadInStreamBuf(MMP_SHORT *target, MMP_ULONG samples);
void MMPF_Audio_WriteInStreamBuf(MMP_SHORT *data, MMP_ULONG samples);

#endif //_MMPF_MULTIAUDSTREAMS_H_