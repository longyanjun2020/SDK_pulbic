#ifndef MVC_AVIO_H
#define MVC_AVIO_H

typedef enum MVC_UOP_e
{
    UOP_None,
    UOP_Play,
    UOP_Pause,
    UOP_Stop,
    UOP_Step,
    UOP_FFwd,
    UOP_Bkwd,
    UOP_Next,
    UOP_Prev,
    UOP_Quit,
    UOP_Resume,
    UOP_VolUp,
    UOP_VolDown,
    UOP_Mute,
    UOP_UnMute,
    UOP_EQMode,
    UOP_Next_CH,
    UOP_Prev_CH,
    UOP_NextAudio,
    UOP_NextVideo,
    UOP_NextSub,
    UOP_AUD_SPECTRUM,
    UOP_SeekPos,
} MVC_UOP_et;

int mvc_get_uop(MVC_UOP_et *uop, int *param, int block);

#endif /* MVC_AVIO_H */
