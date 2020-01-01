#if ! defined( WPRM_h )
#define WPRM_h
/*****************************************************************************/
/* WPRM_h                                                                    */
/* WPRM.h                                                                    */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

typedef struct _WPRM_WDAT {

    //const char *          offset;
    signed char *          offset;
    long            length;
    long            loopStart;
    long            loopEnd;
    long            tune;
    long            type;
#define WPRM_WDAT_ONESHOT       0x00000001

} WPRM_WDAT, *PWPRM_WDAT;
//typedef const WPRM_WDAT*	PCWPRM_WDAT;
typedef  WPRM_WDAT*	PCWPRM_WDAT;

/*---------------------------------------------------------------------------*/

typedef struct _WPRM {

    //const WPRM_WDAT*      wdat;
     WPRM_WDAT*      wdat;
    signed char            maxKey;
    signed char            excGroup;
    signed char            flwKey;
    signed char            coarse;
    signed char            lfoFreq;
    signed char            lfoPegDepth;
    signed char            lfoFegDepth;
    signed char            lfoAegDepth;
    signed char            lfoDelay;
    signed char            pegAttackTime;
    signed char            pegDecayTime;
    signed char            pegReleaseTime;
    signed char            pegInitialLevel;
    signed char            pegSustainLevel;
    signed char            pegReleaseLevel;
    signed char            pegDepth;
    signed char            tvfFc;
    signed char            tvfResonance;
    signed char            fegAttackTime;
    signed char            fegDecayTime;
    signed char            fegReleaseTime;
    signed char            fegInitialLevel;
    signed char            fegSustainLevel;
    signed char            fegReleaseLevel;
    signed char            fegDepth;
    signed char            aegAttackTime;
    signed char            aegDecayTime;
    signed char            aegReleaseTime;
    signed char            aegInitialLevel;
    signed char            aegSustainLevel;
    signed char            aegDepth;
    signed char            type;
#define WPRM_TYPE_LFOMODMASK    0x30
#define WPRM_TYPE_LFOMODAEG     0x10
#define WPRM_TYPE_LFOMODFEG     0x20
#define WPRM_TYPE_TVFKFLW       0x04
#define WPRM_TYPE_TVFMASK       0x03
#define WPRM_TYPE_TVFTHRU       0x00
#define WPRM_TYPE_TVFLPF        0x01
#define WPRM_TYPE_TVFHPF        0x02
#define WPRM_TYPE_TVFBPF        0x03
		signed char						aegInitialReleaseLevel;
} WPRM, *PWPRM;

/*---------------------------------------------------------------------------*/

typedef struct _WPRM_PROGRAM {

    signed char            minKey;
    signed char            level;
    signed char            panpot; //ccc
    unsigned char   nRegion;
    //const WPRM*           prm;
    WPRM*           prm;

} WPRM_PROGRAM, *PWPRM_PROGRAM;

/*---------------------------------------------------------------------------*/

typedef struct _WPRM_BANK {

    signed char            bankMsb;
    signed char            bankLsb;
    //const WPRM_PROGRAM*   program[ 128 ];
    WPRM_PROGRAM*   program[ 128 ];

} WPRM_BANK, *PWPRM_BANK;

/*---------------------------------------------------------------------------*/

typedef struct _WPRM_CONTEXT {

    long            nBank;
    //const WPRM_BANK*      pBank;
    WPRM_BANK*      pBank; //ccc

} WPRM_CONTEXT, *PWPRM_CONTEXT;

/*****************************************************************************/

extern
PWPRM_CONTEXT
WPrmGetDefaultContext(
    void
);

extern
void *
WPrmGet(
    PWPRM_CONTEXT   C,
    unsigned char   bankMsb,
    unsigned char   bankLsb,
    unsigned char   program,
    unsigned char   key
);

/*****************************************************************************/
#endif  /* ! defined( WPRM_h ) */
