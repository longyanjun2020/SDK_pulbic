#if ! defined( SynthAPI_SynthAPI_h )
#define SynthAPI_SynthAPI_h
/*****************************************************************************/
/* SynthAPI_SynthAPI_h                                                       */
/* SynthAPI.h                                                                */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

typedef struct _SYNTHAPI_CHPRM {

    unsigned char   isDrum;
    unsigned char   bankMsb;    /* 0...127 */
    unsigned char   bankLsb;    /* 0...127 */
    unsigned char   program;    /* 0...127 */
    unsigned char   volume;     /* 0...127 */
    signed char            panpot;     /* -64...63 */ //ccc fix, char is unsigned in sde
    unsigned char   expression; /* 0...127 */
    unsigned char   modulation; /* 0...127 */
    unsigned char   pressure;   /* 0...127 */
    unsigned char   hold;       /* 0:off...127:hold */
    short           bend;       /* -8192...8191 */
    unsigned short  sens;       /* 0...16383 : ( 100 / 128 ) * sens cent */
#define RPN_SENS_STEP   128
    short           fine;       /* -8192...8191 : ( 100 / 8192 ) * fine cent */
#define RPN_FINE_STEP   128
    signed char            coarse;     /* -64...63 */ //ccc fix, char is unsigned in sde
#define RPN_COARSE_STEP 1
    unsigned char   xrpn;       /* state of rpn|nrpn */
#define XRPN_IS_NONE    0
#define XRPN_IS_RPN     1
#define XRPN_IS_NRPN    2
    unsigned char   rpnH;       /* rpn(H) */
    unsigned char   rpnL;       /* rpn(L) */
    unsigned char   nrpnH;      /* nrpn(H) */
    unsigned char   nrpnL;      /* nrpn(L) */
#define XRPN_NULL       0x7F

    unsigned short  chGainL;    /* 0...32768 */
    unsigned short  chGainR;    /* 0...32768 */

} SYNTHAPI_CHPRM, *PSYNTHAPI_CHPRM;

/*---------------------------------------------------------------------------*/

typedef struct _SYNTHAPI_CONTEXT {

    void *              synthDrvContext;

    unsigned char       port;

    unsigned char       volume;     /* 0...127 */
    signed char                balance;    /* -64...63 */ //ccc fix, char is unsigned in sde
    short               fine;       /* -8192...8191 : ( 100 / 8192 ) * fine */
    signed char                coarse;     /* -64...63 */ //ccc fix, char is unsigned in sde

    SYNTHAPI_CHPRM      chPrm[ 16 ];

} SYNTHAPI_CONTEXT, *PSYNTHAPI_CONTEXT;

/*****************************************************************************/

extern
PSYNTHAPI_CONTEXT
SynthApiCreate(
    void*              synthDrvContext,
    unsigned char       port,
    unsigned char       voiceNum
);

extern
void
SynthApiDestroy(
    PSYNTHAPI_CONTEXT   C
);

extern
int
SynthApiProc(
    PSYNTHAPI_CONTEXT   C,
    unsigned long       command,
    void *              parameter,
    unsigned long       length
);

extern
int
SynthApiReset(
    PSYNTHAPI_CONTEXT   C
);

extern
int
SynthApiStart(
    PSYNTHAPI_CONTEXT   C
);

extern
int
SynthApiStop(
    PSYNTHAPI_CONTEXT   C
);

/*****************************************************************************/

#define SYNTHAPI_MASTERVOLUME                   0x00000002
#define SYNTHAPI_MASTERBALANCE					0x00000003
#define SYNTHAPI_MASTERCOARSETUNE               0x00000004
#define SYNTHAPI_KILL                           0x00000006
#define SYNTHAPI_META                           0x00000007
#define SYNTHAPI_NOTEOFF                        0x00000008
#define SYNTHAPI_NOTEON                         0x00000009
#define SYNTHAPI_KEYPRESSURE                    0x0000000A
#define SYNTHAPI_CONTROLCHANGE                  0x0000000B
#define SYNTHAPI_PROGRAMCHANGE                  0x0000000C
#define SYNTHAPI_CHANNELPRESSURE                0x0000000D
#define SYNTHAPI_PITCHBEND                      0x0000000E
#define SYNTHAPI_SYSTEM                         0x0000000F
#define SYNTHAPI_NUM                            0x00000010

/*****************************************************************************/

#define SynthApiMasterVolume( C, volume )                                     \
        SynthApiProc(                                                         \
            C,                                                                \
            SYNTHAPI_MASTERVOLUME,                                            \
            (void *)( (unsigned long)(volume) ),                              \
            0                                                                 \
        )
#define SynthApiMasterBalance( C, balance )                                   \
        SynthApiProc(                                                         \
            C,                                                                \
            SYNTHAPI_MASTERBALANCE,                                           \
            (void *)( (unsigned long)(balance) ),                             \
            0                                                                 \
        )
#define SynthApiMasterCoarseTune( C, coarse )                                 \
		SynthApiProc(                                                         \
            C,                                                                \
            SYNTHAPI_MASTERCOARSETUNE,                                        \
            (void *)( (unsigned long)(coarse) ),                              \
            0                                                                 \
        )
#define SynthApiKill( C )   SynthApiProc( C, SYNTHAPI_KILL, 0, 0 )
#define SynthApiMeta( C, data, length )                                       \
        SynthApiProc( C, SYNTHAPI_META, (void *)data, length )
#define SynthApiNoteOff( C, ch, key )                                         \
        SynthApiProc(                                                         \
            C,                                                                \
            SYNTHAPI_NOTEOFF,                                                 \
            (void *)(                                                         \
                ( (unsigned long)(ch) ) | ( ( (unsigned long)(key) ) << 8 )   \
            ),                                                                \
            0                                                                 \
        )
#define SynthApiNoteOn( C, ch, key, velocity )                                \
        SynthApiProc(                                                         \
            C,                                                                \
            SYNTHAPI_NOTEON,                                                  \
            (void *)(                                                         \
                ( (unsigned long)(ch) )                                       \
              | ( ( (unsigned long)(key) ) << 8 )                             \
              | ( ( (unsigned long)(velocity) ) << 16 )                       \
            ),                                                                \
            0                                                                 \
        )
#define SynthApiControlChange( C, ch, arg1, arg2 )                            \
        SynthApiProc(                                                         \
            C,                                                                \
            SYNTHAPI_CONTROLCHANGE,                                           \
            (void *)(                                                         \
                ( (unsigned long)(ch) )                                       \
              | ( ( (unsigned long)(arg1) ) << 8 )                            \
              | ( ( (unsigned long)(arg2) ) << 16 )                           \
            ),                                                                \
            0                                                                 \
        )
#define SynthApiProgramChange( C, ch, program )                               \
        SynthApiProc(                                                         \
            C,                                                                \
            SYNTHAPI_PROGRAMCHANGE,                                           \
            (void *)(                                                         \
                ( (unsigned long)(ch) )                                       \
              | ( ( (unsigned long)(program) ) << 8 )                         \
            ),                                                                \
            0                                                                 \
        )
#define SynthApiChannelPressure( C, ch, pressure )                            \
        SynthApiProc(                                                         \
            C,                                                                \
            SYNTHAPI_CHANNELPRESSURE,                                         \
            (void *)(                                                         \
                ( (unsigned long)(ch) )                                       \
              | ( ( (unsigned long)(pressure) ) << 8 )                        \
            ),                                                                \
            0                                                                 \
        )
#define SynthApiPitchBend( C, ch, bendL, bendH )                              \
        SynthApiProc(                                                         \
            C,                                                                \
            SYNTHAPI_PITCHBEND,                                               \
            (void *)(                                                         \
                ( (unsigned long)(ch) )                                       \
              | ( ( (unsigned long)(bendL) ) << 8 )                           \
              | ( ( (unsigned long)(bendH) ) << 16 )                          \
            ),                                                                \
            0                                                                 \
        )
#define SynthApiSystemExclusive( C, data, length )                            \
        SynthApiProc( C, SYNTHAPI_SYSTEM, (void *)(data), length )

/*****************************************************************************/
#endif  /* ! defined( SynthAPI_SynthAPI_h ) */
