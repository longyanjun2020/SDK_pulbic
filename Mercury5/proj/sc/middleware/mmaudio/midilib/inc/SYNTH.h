#if ! defined( DEVICE_SYNTH_SYNTH_h )
#define DEVICE_SYNTH_SYNTH_h
/*****************************************************************************/
/* DEVICE_SYNTH_SYNTH_h                                                      */
/* SYNTH.h                                                                   */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

#ifdef BENCHMARK
//#define BENCHMARK_STMT(stmt)    stmt
#else
//#define BENCHMARK_STMT(stmt)
#endif

//#define MIDI_NOMIPS16  __attribute__((nomips16))
#define MIDI_NOMIPS16

//BENCHMARK_STMT(extern long total_tones);
//BENCHMARK_STMT(extern long max_voices);

typedef struct _VREG_OSC {

    signed char *          ofst;
    long            start;
    long            end;
    long            phase;
    long            phInc;
    long            type;

} VREG_OSC, *PVREG_OSC;

/*---------------------------------------------------------------------------*/

typedef struct _VREG_PEG {

    short           cur;
    short           ratio;
    short           nextRatio;
    short           frames;
    short           target;
    short           next;

} VREG_PEG, *PVREG_PEG;

/*---------------------------------------------------------------------------*/

typedef struct _VREG_AEG {

    short           cur;
    short           ratio;
    short           nextRatio;
    short           frames;
    short           target;
    short           next;
    short           depthL;
    short           depthR;
	short			prevL;
	short			prevR;

} VREG_AEG, *PVREG_AEG;

/*---------------------------------------------------------------------------*/

typedef struct _VREG_FEG {

    short           cur;
    short           ratio;
    short           nextRatio;
    short           frames;
    short           target;
    short           next;

} VREG_FEG, *PVREG_FEG;

/*---------------------------------------------------------------------------*/

typedef struct _VREG_TVF {

    unsigned short  type;
#define VREG_TVF_THRU           0x0000
#define VREG_TVF_LPF            0x0001
#define VREG_TVF_HPF            0x0002
#define VREG_TVF_BPF            0x0003

    unsigned short  ztheta;
    unsigned short  zthMin;
    unsigned short  zthMax;
    short           mq;

    long           z1;
    long           z2;

} VREG_TVF, *PVREG_TVF;

/*---------------------------------------------------------------------------*/

typedef struct _VREG_LFO {

    long            cur;
    long            ratio;
    long            ratioStack;
    short           frames;
    short           pegDepthN;
    short           aegDepthN;
    short           fegDepthN;

} VREG_LFO, *PVREG_LFO;

/*---------------------------------------------------------------------------*/

typedef struct _VREG_PRM {

    VREG_OSC        osc;		// +0
    VREG_PEG        peg;    // +4
    VREG_AEG        aeg;    // +8
    VREG_FEG        feg;    // +12
    VREG_TVF        tvf;    // +16
    VREG_LFO        lfo;    // +20

} VREG_PRM, *PVREG_PRM;

/*---------------------------------------------------------------------------*/

typedef struct _VREG {

    unsigned short  stat;
#define VREG_STAT_INF               0xFFFF
#define VREG_STAT_MAX               0x7FFF
#define VREG_STAT_MIN               0x0020

    unsigned char   ctrl;
#define VREG_CTRL_VON               ( VREG_CTRL_OSC | VREG_CTRL_ATTACK )
#define VREG_CTRL_OSC               0x01
#define VREG_CTRL_ATTACK            0x10
#define VREG_CTRL_STARTED           0x20

    unsigned char   damp;
#define VREG_DAMP_COUNT             1 //4
#define VREG_DAMP_RATIO             0 //0x7333  /* 4 Cur frame : -60dB */

    VREG_PRM        prm0;
    VREG_PRM        prm1;
    unsigned short  prmSw;

    //void *          mutex;          /* HANDLE mutex[ 1 ] */

} VREG, *PVREG;

/*---------------------------------------------------------------------------*/

typedef struct _SYNTH_CONTEXT {

    PVREG           vreg;   /* VREG vreg[ POLYPHONY ] */
		unsigned char		poly;

} SYNTH_CONTEXT, *PSYNTH_CONTEXT;

/*****************************************************************************/

extern
unsigned char
SynthPolyphony(
    PSYNTH_CONTEXT  C
);

extern
PSYNTH_CONTEXT
SynthCreate(
    void
);

extern
void
SynthDestroy(
    PSYNTH_CONTEXT  C
);

extern
void
SynthFrame(
    PSYNTH_CONTEXT  C,
    long *          frame
);

/*****************************************************************************/
//=====================================================

extern void  MIDI_NOMIPS16
synthVoiceFramef_lpf(
		PVREG 					vreg,
		PVREG_PRM 			prm,
		long * 				 frame
);
extern void  MIDI_NOMIPS16
synthVoiceFrame_lpf(
		PVREG 					vreg,
		PVREG_PRM 			prm,
		long * 				 frame
);
extern void MIDI_NOMIPS16
synthVoiceFramef_hpf(
		PVREG 					vreg,
		PVREG_PRM 			prm,
		long * 				 frame
);
extern void MIDI_NOMIPS16
synthVoiceFrame_hpf(
		PVREG 					vreg,
		PVREG_PRM 			prm,
		long * 				 frame
);
extern void MIDI_NOMIPS16
synthVoiceFramef_bpf(
		PVREG 					vreg,
		PVREG_PRM 			prm,
		long * 				 frame
);
extern void MIDI_NOMIPS16
synthVoiceFrame_bpf(
		PVREG 					vreg,
		PVREG_PRM 			prm,
		long * 				 frame
);
extern void MIDI_NOMIPS16
synthVoiceFramef_thru(
		PVREG 					vreg,
		PVREG_PRM 			prm,
		long * 				 frame
);
extern void MIDI_NOMIPS16
synthVoiceFrame_thru(
		PVREG 					vreg,
		PVREG_PRM 			prm,
		long * 				 frame
);
extern unsigned short
synthVoiceFrame(
		PSYNTH_CONTEXT	C,
		PVREG 					vreg,
		long * 				 frame,
		unsigned char 	v
);

//=====================================================
#endif  /* ! defined( DEVICE_SYNTH_SYNTH_h ) */
