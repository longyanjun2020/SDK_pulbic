#ifndef _MMPF_AUI_CTL_H_
#define _MMPF_AUI_CTL_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "config_fw.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================
#if (AUDIO_P_EN==0)
		#define AUI_DEC_SIZEOF_TOTAL_WORKING_BUF 4 //0
#endif
#if (WAV_P_EN)
    #define AUI_DEC_SIZEOF_TOTAL_WORKING_BUF    WAVDEC_BUFFER_SIZE
#endif

#if (MP3_P_EN)
#ifdef AUI_DEC_SIZEOF_TOTAL_WORKING_BUF
    #if (MP3DEC_BUFFER_SIZE > AUI_DEC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUI_DEC_SIZEOF_TOTAL_WORKING_BUF
    #define AUI_DEC_SIZEOF_TOTAL_WORKING_BUF    MP3DEC_BUFFER_SIZE
    #endif
#else
    #define AUI_DEC_SIZEOF_TOTAL_WORKING_BUF    MP3DEC_BUFFER_SIZE
#endif
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_AUI_DATAPATH {
    MMPF_AUI_DATAPATH_CARD,     ///< Card mode
    MMPF_AUI_DATAPATH_MMP_MEM,  ///< MMP stacked memory mode
    MMPF_AUI_DATAPATH_MAX
} MMPF_AUI_DATAPATH;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _MMPF_AUI_RINGBUF {
    MMP_ULONG ulBufStart;
    MMP_ULONG ulBufSize;
    MMP_ULONG ulReadPtr;
    MMP_ULONG ulWritePtr;
    MMP_ULONG ulReadPtrHigh;
    MMP_ULONG ulWritePtrHigh;
} MMPF_AUI_RINGBUF;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

// Streaming part
MMP_ERR     MMPF_AuiStream_CreateSem(void);
MMP_ERR 	MMPF_AuiStream_SetPlayFileName(MMP_ULONG ulFileNameAddr);
MMP_ERR     MMPF_AuiStream_PresetPlayFileName(MMP_ULONG ulFileNameAddr);
MMP_ERR 	MMPF_AuiStream_GetPlayFileSize(MMP_ULONG *size);
MMP_ERR     MMPF_AuiStream_GetPlayRemainFileSize(MMP_ULONG *size);
MMP_ERR  	MMPF_AuiStream_SetPlayBuffer(MMP_ULONG ulBufStart, MMP_ULONG ulBufSize);
MMP_ERR  	MMPF_AuiStream_GetPlayBuffer(MMP_ULONG *ulBufStart, MMP_ULONG *ulBufSize);
MMP_ERR  	MMPF_AuiStream_SetReadPtr(MMP_ULONG ulReadHighPtr, MMP_ULONG ulReadPtr);
MMP_ERR  	MMPF_AuiStream_GetReadPtr(MMP_ULONG *ulReadHighPtr, MMP_ULONG *ulReadPtr);
MMP_ERR     MMPF_AuiStream_GetWritePtr(MMP_ULONG *ulWriteHighPtr, MMP_ULONG *ulWritePtr);
MMP_ERR     MMPF_AuiStream_SetWritePtr(MMP_ULONG ulWriteHighPtr, MMP_ULONG ulWritePtr);
MMP_ERR  	MMPF_AuiStream_PresetPlayBuffer(MMP_ULONG ulStartPos);
MMP_ERR  	MMPF_AuiStream_TransferDataFromCard(void);
MMP_ERR  	MMPF_AuiStream_ClosePlayFile(void);

// Parser part
MMP_ERR 	MMPF_AuiStream_SetParseFileName(MMP_ULONG ulFileNameAddr);
MMP_ERR 	MMPF_AuiStream_GetParseFileSize(MMP_ULONG *size);
MMP_ERR     MMPF_AuiStream_SetParseBuffer(MMP_ULONG ulBufStart, MMP_ULONG ulBufSize);
MMP_ERR     MMPF_AuiStream_GetParseBuffer(MMP_ULONG *ulBufStart, MMP_ULONG *ulBufSize);
MMP_ERR  	MMPF_AuiStream_SetParseReadPtr(MMP_ULONG ulReadHighPtr, MMP_ULONG ulReadPtr);
MMP_ERR  	MMPF_AuiStream_GetParseReadPtr(MMP_ULONG *ulReadHighPtr, MMP_ULONG *ulReadPtr);
MMP_ERR     MMPF_AuiStream_GetParseWritePtr(MMP_ULONG *ulWriteHighPtr, MMP_ULONG *ulWritePtr);
MMP_ERR  	MMPF_AuiStream_PresetParseBuffer(MMP_ULONG ulStartPos);
MMP_ERR  	MMPF_AuiStream_TransferParseDataFromCard(void);
MMP_ERR  	MMPF_AuiStream_CloseParseFile(void);
MMP_ERR     MMPF_Aui_SetParsePath(MMP_UBYTE path);
MMP_UBYTE   MMPF_Aui_GetParsePath(void);
MMP_ERR  	MMPF_Aui_SetParseFormat(MMP_USHORT decodefmt);
MMP_ERR  	MMPF_Aui_GetParseFormat(MMP_USHORT *decodefmt);

// Decoder part
MMP_ERR  	MMPF_Aui_GetWorkingBuffer(MMP_ULONG *ulWorkingBuffer, MMP_ULONG *ulWorkingBufferSize);
MMP_ERR     MMPF_Aui_SetPlayPath(MMP_UBYTE path);
MMP_UBYTE   MMPF_Aui_GetPlayPath(void);
MMP_ERR  	MMPF_Aui_SetPlayFormat(MMP_USHORT decodefmt);
MMP_ERR  	MMPF_Aui_GetPlayFormat(MMP_USHORT *decodefmt);
MMP_ERR  	MMPF_Aui_SetPlayStatus(MMP_USHORT playstatus);
MMP_ERR  	MMPF_Aui_GetPlayStatus(MMP_USHORT *playstatus);
MMP_ERR  	MMPF_Aui_GetPlayOp(MMP_USHORT *playop);
MMP_ERR		MMPF_Aui_SetMP3DecodeOp(MMP_USHORT op, MMP_ULONG *parameter);
MMP_ERR		MMPF_Aui_SetWAVDecodeOp(MMP_USHORT op, MMP_ULONG *parameter);
MMP_ERR		MMPF_Aui_SetAMRDecodeOp(MMP_USHORT op, MMP_ULONG *parameter);

#endif //_MMPF_AUI_CTL_H_
