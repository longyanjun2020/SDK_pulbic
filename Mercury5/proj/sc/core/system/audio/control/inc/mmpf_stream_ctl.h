#ifndef	_MMPF_STREAM_CTL_H_
#define	_MMPF_STREAM_CTL_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_err.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define	AUDIO_CHUNK_FOR_READ 	(1024)
#define	AUDIO_CHUNK_FOR_WRITE 	(512)

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_ERR	MMPF_Audio_SetPlayFileName(MMP_ULONG address);
MMP_ERR MMPF_Audio_ClosePlayFile(void);
MMP_ERR	MMPF_Audio_PresetPlayBuffer(void); 
MMP_ERR	MMPF_Audio_PostsetPlayBuffer(void); 
MMP_ERR MMPF_Audio_GetPlayFileSize(MMP_ULONG *size);

MMP_ERR	MMPF_Audio_PresetEncodeFile(void); 
MMP_ERR	MMPF_Audio_PostsetEncodeFile(void); 

MMP_ERR	MMPF_Audio_TransferDataFromCard(void);
MMP_ERR	MMPF_Audio_TransferDataToCard(MMP_BOOL bSaveAll);
MMP_ERR	MMPF_Audio_FillBufInterruptToHost(void);

MMP_ERR	MMPF_Audio_CreateStreamingSem(void);
MMP_ERR MMPF_Audio_GetStreamingPtr(MMP_ULONG *ulReadPtr, MMP_ULONG *ulReadPtrHigh, 
									MMP_ULONG *ulWritePtr, MMP_ULONG *ulWritePtrHigh);
MMP_ERR	MMPF_Audio_SetStreamingReadPtr(MMP_ULONG ulReadPtr, MMP_ULONG ulReadPtrHigh);
MMP_ERR	MMPF_Audio_SetStreamingWritePtr(MMP_ULONG ulWritePtr, MMP_ULONG ulWritePtrHigh);

MMP_ERR MMPF_Audio_SetParsePath(MMP_UBYTE path);
MMP_UBYTE MMPF_Audio_GetParsePath(void);
MMP_ERR MMPF_Audio_SetParseFormat(MMP_USHORT fmt);
MMP_ERR MMPF_Audio_GetParseFormat(MMP_USHORT *fmt);
MMP_ERR MMPF_Audio_SetParseFileName(MMP_ULONG ulFileNameAddr);
MMP_ERR MMPF_Audio_GetParseFileSize(MMP_ULONG *size);
MMP_ERR MMPF_Audio_SetParseBuffer(MMP_ULONG ulBufStart, MMP_ULONG ulBufSize);
MMP_ERR MMPF_Audio_GetParseBuffer(MMP_ULONG *ulBufStart, MMP_ULONG *ulBufSize);
MMP_ERR MMPF_Audio_SetParseReadPtr(MMP_ULONG ulReadHighPtr, MMP_ULONG ulReadPtr);
MMP_ERR MMPF_Audio_GetParseReadPtr(MMP_ULONG *ulReadHighPtr, MMP_ULONG *ulReadPtr);
MMP_ERR MMPF_Audio_GetParseWritePtr(MMP_ULONG *ulWriteHighPtr, MMP_ULONG *ulWritePtr);
MMP_ERR MMPF_Audio_PresetParseBuffer(MMP_ULONG ulStartPos);
MMP_ERR MMPF_Audio_CloseParseFile(void);
MMP_ERR MMPF_Audio_TransferParseDataFromCard(void);
MMP_ERR MMPF_Audio_PresetPlayFileName(MMP_ULONG ulFileNameAddr);
MMP_ERR MMPF_Audio_SetPlayFileNameFromParser(void);
MMP_ERR MMPF_Audio_SetPlayBufferFromParser(void);

extern MMP_USHORT	MMPF_Audio_SetABRepeatMode(MMP_USHORT command, MMP_ULONG pos);
extern MMP_USHORT	MMPF_Audio_GetDataInterruptToHost(void);

#endif //_MMPF_STREAM_CTL_H_


