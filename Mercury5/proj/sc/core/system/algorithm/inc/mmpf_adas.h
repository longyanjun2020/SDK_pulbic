//==============================================================================
//
//  File        : mmpf_ldws.h
//  Description : INCLUDE File for the Lane Departure Warning System Function
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_LDWS_H_
#define _MMPF_LDWS_H_

#include "includes_fw.h"

/** @addtogroup MMPF_LDWS
@{
*/
#if (VIDEO_R_EN)&&(SUPPORT_ADAS)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

#if (CPU_ID == CPU_A)
typedef enum _MMPF_ADAS_STATE {
    MMPF_ADAS_IDLE_STATE = 0,
    MMPF_ADAS_ACTIVE_STATE,
    MMPF_ADAS_WAIT_FRAME_STATE,
    MMPF_ADAS_FRAME_READY_STATE,
    MMPF_ADAS_OPERATING_STATE,
    MMPF_ADAS_DMA_TRIGGER_STATE,
    MMPF_ADAS_DMA_MOVING_STATE
} MMPF_ADAS_STATE;
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

#if (CPU_ID == CPU_A)
typedef struct _MMPF_ADAS_ATTRIBUTE {
    MMP_ULONG   ulWorkBuf;          ///< the addr of working buffer
    MMP_ULONG   ulWorkBufSize;      ///< the size of working buffer
	MMP_USHORT  usInputW;           ///< the width of input frame to do motion detection
	MMP_USHORT  usInputH;           ///< the height of input frame to do motion detection
	MMP_ULONG   ulInputLumaAddr;    ///< the addr of luma source
	MMP_ULONG   ulLumaSize;         ///< the size of luma image
	MMP_ULONG   ulImgBufAddr;       ///< the addr of dma destination source
    MMP_UBYTE   ubFrameGap;         ///< the gap (frame count) of the two frames for calculation
    MMP_ULONG   ulGapTimeMs;        ///< the gap time in unit of ms
} MMPF_ADAS_ATTRIBUTE;
#endif

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

typedef void MMPF_ADAS_Callback(void);

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

#if (CPU_ID == CPU_A)
MMP_ERR     MMPF_ADAS_ProcessCmd(void);
MMP_BOOL    MMPF_ADAS_IsEnable(void);
MMP_UBYTE   MMPF_LDWS_GetFrameGapConfig(void);
void        MMPF_LDWS_UpdateInputLumaAddr(MMP_ULONG ulSrcLumaAddr);
MMP_UBYTE   MMPF_LDWS_GetFrameGapConfig(void);
MMP_ERR     MMPF_ADAS_DmaCopy(void);
MMP_ERR     MMPF_ADAS_Operate(void);
MMPF_ADAS_STATE MMPF_ADAS_GetState(void);
#endif

#endif // (VIDEO_R_EN)&&(SUPPORT_ADAS)
int adas_main(void);
#endif // _MMPF_LDWS_H_
/// @}
