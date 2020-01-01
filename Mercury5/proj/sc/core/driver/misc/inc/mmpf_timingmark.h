//==============================================================================
//
//  File        : mmpf_timingmark.h
//  Description : Firmware Timing Mark
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

#define SUPPORT_TIMING_MARK             (0)

#define TIMING_GROUP_BOOT                   0x00000001
#define TIMING_GROUP_CAPTURE                0x00000002
#define TIMING_GROUP_VIDEO_RECORD           0x00000004
#define TIMING_GROUP_MOTOR                  0x00000008

void MMPF_TimingInit( MMP_ULONG uiItems );
void MMPF_TimingStart(MMP_ULONG uiGroups);
void MMPF_TimingStop(void);
void MMPF_TimingResume(void);
void MMPF_TimingDump( MMP_ULONG uiFlags );
void MMPF_TimingMark( MMP_ULONG uiGroup, char* szString );
void MMPF_TimingMarkF( MMP_ULONG uiGroup,  char* szFormat, ... );
void MMPF_TimingRestart(void); //Mark TBD.

