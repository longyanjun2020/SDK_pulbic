//==============================================================================
//
//  File        : mmpf_clksync.h
//  Description : Header function of record audio/video clock sync
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================
#ifndef _MMPF_CLKSYNC_H_
#define _MMPF_CLKSYNC_H_

#include "lib_retina.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#if (VR_AVSYNC_METHOD == VR_AVSYNC_REF_VID)
/* How many times to skip A/V sync in the beginning
 */
#define AVSYNC_SKIP_CNT                     (1)    // Skip the first interval
/* The interval (in unit of sec) to examine audio/video time, and adjust
 * audio clock if necessary
 */
#define AVSYNC_INTERVAL_SEC                 (2)
#define AVSYNC_INTERVAL_MS                  (2000) // AVSYNC_INTERVAL_SEC *1000
/* Don't adjust audio clock if audio/video time diff is under the tolerance.
 * (in unit of ms)
 */
#define AVSYNC_DIFF_TOLERANCE               (20)
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

#if (VR_AVSYNC_METHOD == VR_AVSYNC_REF_VID)
/**
 @brief A/V sync control parameters
*/
typedef struct _MMPF_VIDREC_AVSYNC_CTL {
    MMP_ULONG   ulSnrIn;            /* Number of sensor input            */
    MMP_ULONG   ulSnrFpsInc;        /* Sensor FPS increment              */
    MMP_ULONG   ulSnrFpsIncx1000;   /* Sensor FPS increment x 1000       */
    MMP_ULONG   ulSnrFpsResol;      /* Sensor FPS resolution             */
    MMP_ULONG   ulSnrAccIn;         /* Accumulated sensor input number   */
    MMP_ULONG   ulSnrTick;          /* Current time in view of sensor in */

    MMP_ULONG   ulVidFrame;         /* Total number of video frames out  */
    MMP_ULONG   ulVidFpsInc;        /* Video FPS increment               */
    MMP_ULONG   ulVidFpsIncx1000;   /* Video FPS increment x 1000        */
    MMP_ULONG   ulVidFpsResol;      /* Video FPS resolution              */
    MMP_ULONG   ulVidTick;          /* Current time in view of video out */

    MMP_ULONG   ulAudSample;        /* Number of audio samples           */
    MMP_ULONG   ulAudSrateHz;       /* Audio sample rate in unit of Hz   */

    MMP_ULONG   ulSkipSync;         /* Times to skip sync in beginning   */
    MMP_ULONG   ulTolerance;        /* Tolerance of audio samples diff   */
    MMP_ULONG   ulFractPerSample;   /* Fraction step for one aud sample  */
    MMP_ULONG   ulLastChkTick;      /* Last time tick to check A/V sync  */
} MMPF_VIDREC_AVSYNC_CTL;
#endif

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/* For video recording A/V sync (refer to video time) */
#if (VR_AVSYNC_METHOD == VR_AVSYNC_REF_VID)
void MMPF_ClkSync_Init(MMP_BOOL enable);
void MMPF_ClkSync_SetResetEn(void);
void MMPF_ClkSync_SetInFrameRate(MMP_ULONG inc, MMP_ULONG resol);
void MMPF_ClkSync_SetOutFrameRate(MMP_ULONG inc, MMP_ULONG resol);
void MMPF_ClkSync_SetSampleRate(MMP_ULONG sample_rate);
void MMPF_ClkSync_AdvanceAudSample(MMP_ULONG samples);
void MMPF_ClkSync_RefreshClk(MMP_UBYTE ubSnrIn, MMP_UBYTE ubVidOut);

MMP_ULONG MMPF_ClkSync_GetInTick(void);
MMP_ULONG MMPF_ClkSync_GetOutTick(void);
#endif

#endif //_MMPF_CLKSYNC_H_
