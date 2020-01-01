/** @file mmpf_streaming.h
@brief Common used streaming structure and interfaces
@author Truman Yang

*/
#ifndef _MMPF_STREAMING_H_
#define _MMPF_STREAMING_H_

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

void MMPF_StreamingTimer_Start(void);
void MMPF_StreamingTimer_Stop(void);
void MMPF_StreamingTimer_KeepTimerAlive(MMP_UBYTE bEn);
void MMPF_StreamingTimer_SetMs(MMP_ULONG ulMs);
MMP_ULONG MMPF_StreamingTimer_GetMs(void);

#endif //_MMPF_STREAMING_H_
