#if ! defined( VOICE_h )
#define VOICE_h
/*****************************************************************************/
/* VOICE_h                                                                   */
/* VOICE.h                                                                   */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

extern
void
VoiceKill(
    PVREG   vreg
);

extern
void
VoiceDamp(
    PVREG   vreg
);

extern
void
VoiceOff(
    PVREG   vreg,
    PWPRM   wprm
);

extern
void
VoiceOn(
    PVREG           vreg,
    PWPRM           wprm,
    unsigned char   key,
    short           gainL,
    short           gainR,
    long            tune,
    char            modulation
);

extern
void
VoiceGain(
    PVREG   vreg,
    PWPRM   wprm,
    short   gainL,
    short   gainR
);

extern
void
VoicePitch(
    PVREG           vreg,
    PWPRM           wprm,
    unsigned char   key,
    long            tune
);

extern
void
VoiceModulation(
    PVREG           vreg,
    PWPRM           wprm,
    char            modulation
);

/*****************************************************************************/
#endif  /* ! defined( VOICE_h ) */
