#if ! defined( SynthDRV_SynthDRV_h )
#define SynthDRV_SynthDRV_h
/*****************************************************************************/
/* SynthDRV_SynthDRV_h                                                       */
/* SynthDRV.h                                                                */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

#define ASSIGNOR_MODE_STATE         0
#define ASSIGNOR_MODE_CHPRIORITY    1
#define ASSIGNOR_MODE               ASSIGNOR_MODE_STATE

/*****************************************************************************/

typedef struct _ASSIGNOR_VIF {

    DLIST           e;

    void *          vreg;

    void *          wprm;

    unsigned char   vflag;
#define ASSIGNOR_GATE_OFF       0x00
#define ASSIGNOR_GATE_ON        0x01
#define ASSIGNOR_GATE_HOLD      0x02
#define ASSIGNOR_GATE_KILLED    0x04

    unsigned char   ch;
    unsigned char   key;
    unsigned char   velocity;

    short           tune;
    
} ASSIGNOR_VIF, *PASSIGNOR_VIF;

/*---------------------------------------------------------------------------*/

typedef struct _ASSIGNOR_PORT {

    unsigned char   enable;
    unsigned char   voiceNum;
    unsigned char   exceed;

#if        ( ASSIGNOR_MODE == ASSIGNOR_MODE_CHPRIORITY )
    unsigned char   chPriority[ 16 ];
#define ASSIGNOR_CHPRIORITY_INF 0xFF
#define ASSIGNOR_CHPRIORITY_MAX 0x7F
#define ASSIGNOR_CHPRIORITY_MIN 0x00
#endif  /* ( ASSIGNOR_MODE == ASSIGNOR_MODE_CHPRIORITY ) */

    DLIST           queue;

} ASSIGNOR_PORT, *PASSIGNOR_PORT;

/*---------------------------------------------------------------------------*/

typedef struct _SYNTHDRV_CONTEXT {

    void *          wprmContext;    /* wave table */

    PASSIGNOR_VIF   avif;   /* ASSIGNOR_VIF     avif[ POLYPHONY ]         */

    DLIST           free;
    PASSIGNOR_PORT  aport;  /* ASSIGNOR_PORT    aport[ SYNTHDRV_PORTNUM ] */
    //void *          mutex;  /* HANDLE           mutex[ 1 ]                */

} SYNTHDRV_CONTEXT, *PSYNTHDRV_CONTEXT;

/*****************************************************************************/

extern
unsigned char
SynthDrvPortNum(
    void
);

extern
PSYNTHDRV_CONTEXT
SynthDrvCreate(
    void *  synthContext
);

extern
void
SynthDrvDestroy(
    PSYNTHDRV_CONTEXT   C
);

void
SynthDrvLock(
    PSYNTHDRV_CONTEXT   C
);

void
SynthDrvUnlock(
    PSYNTHDRV_CONTEXT   C
);

PASSIGNOR_PORT
SynthDrvOpenPort(
    PSYNTHDRV_CONTEXT   C,
    unsigned char       port,
    unsigned char       voiceNum,
    unsigned char       exceed
);

void
SynthDrvClosePort(
    PSYNTHDRV_CONTEXT   C,
    unsigned char       port
);

PASSIGNOR_VIF
SynthDrvGetNextVoice(
    PSYNTHDRV_CONTEXT   C,
    unsigned char       port,
    PASSIGNOR_VIF       voice
);

PASSIGNOR_VIF
SynthDrvGetNextSameChVoice(
    PSYNTHDRV_CONTEXT   C,
    unsigned char       port,
    unsigned char       ch,
    PASSIGNOR_VIF       voice
);

PASSIGNOR_VIF
SynthDrvGetSameNoteVoice(
    PSYNTHDRV_CONTEXT   C,
    unsigned char       port,
    unsigned char       ch,
    unsigned char       key,
    PASSIGNOR_VIF       voice
);

PASSIGNOR_VIF
SynthDrvAllocVoice(
    PSYNTHDRV_CONTEXT   C,
    unsigned char       port,
    unsigned char       ch,
    unsigned char       key,
    unsigned char       velocity,
    unsigned char *     pDamp
);

extern
void *
SynthDrvWPrmGet(
    PSYNTHDRV_CONTEXT   C,
    unsigned char       bankMsb,
    unsigned char       bankLsb,
    unsigned char       program,
    unsigned char       key
);

void
SynthDrvVoiceKill(
    PASSIGNOR_VIF   voice
);

void
SynthDrvVoiceDamp(
    PASSIGNOR_VIF   voice
);

void
SynthDrvVoiceOff(
    PASSIGNOR_VIF   voice
);

void
SynthDrvVoiceOn(
    PASSIGNOR_VIF   voice,
    void *          wprm,
    short           gainL,
    short           gainR,
    long            tune,
    char            modulation
);

void
SynthDrvVoiceGain(
    PASSIGNOR_VIF   voice,
    short           gainL,
    short           gainR
);

void
SynthDrvVoicePitch(
    PASSIGNOR_VIF   voice,
    long            tune
);

void
SynthDrvVoiceModulation(
    PASSIGNOR_VIF   voice,
    char            modulation
);

/*****************************************************************************/
#endif  /* ! defined( SynthDRV_SynthDRV_h ) */
