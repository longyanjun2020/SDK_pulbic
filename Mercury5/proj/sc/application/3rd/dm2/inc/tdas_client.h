/******************************************************************************
TDAS Implementation Kit

  Confidential Information - Limited distribution to authorized persons only.
  This material is protected under international copyright laws as an 
  unpublished work. Do not copy. 
  Copyright (C) 2004-2008 Dolby Laboratories Inc. All rights reserved.

	File:           tdas_client.h
	Contributors:	Roger Butler
	Description:    C implementation for DSPs
	  
******************************************************************************/

#ifndef TDAS_H
#define TDAS_H
#define MEM_UTIL_FUNCTIONS

#ifdef MEM_UTIL_FUNCTIONS
/* Function pointer typedefs for external linkages of memory utilities.
 * 
 * Note : There is an extra alignment parameter for tFnPtr_mem_alloc, 
 * compared to stdlib::malloc().
 */
typedef void *(* tFnPtr_mem_alloc)(size_t size); 
typedef void (* tFnPtr_mem_free)(void *p);
typedef void *(* tFnPtr_mem_set) (void *buf, int ch, size_t count);
typedef void *(* tFnPtr_mem_cpy) (void *to, const void *from, size_t count);

/* tdas_mem_utils_init() allows redefinition of the memory utility functions by 
 * specific DSP platform for TDAS lib.
 *
 * It is optionally called IMMEDIATELY prior to the first instance of TDAS object creation via tdas_open().
 * 
 * If a null function pointer is supplied as any of the parameters then,
 * that particular memory utility function will remain as the defaults specified 
 * for the particular DSP platform.
 *
 * It is up to User App to ensure the malloc function and free function are complimentary.
 */
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
#ifdef SYMBIAN_DLL
IMPORT_C
#endif //SYMBIAN_DLL
int tdas_mem_utils_init(    tFnPtr_mem_alloc my_tdas_mem_alloc, 
                            tFnPtr_mem_free my_tdas_mem_free,
                            tFnPtr_mem_cpy my_tdas_mem_cpy,
                            tFnPtr_mem_set my_tdas_mem_set);
#ifdef __cplusplus
}
#endif //__cplusplus
#endif

/* Open TDAS. Memory is allocated by this function. If a particular DSP 
 * implementation is not allowed to allocate memory then this function must
 * be overridden for that platform. A pointer to the state will be returned,
 * which must be passed into the other functions in this API.
 */
#ifdef __cplusplus
extern "C" {
#endif
#ifdef SYMBIAN_DLL
IMPORT_C
#endif
void *tdas_open(void);
#ifdef __cplusplus
}
#endif

/* This must be called to close TDAS. Pass in the state pointer allocated
 * by tdas_open().
 */
#ifdef __cplusplus
extern "C" {
#endif
#ifdef SYMBIAN_DLL
IMPORT_C
#endif
void tdas_close(void *v_tdas);
#ifdef __cplusplus
}
#endif

/* This function processes a block of samples. v_tdas must have been 
 * returned from tdas_open(). 
 * 
 * The input buffer (in) is a pre-allocated buffer, that can contain
 * either interleaved or non-interleaved samples from each channel.  The number
 * of input channels is set through the TDAS_IN_CHANS bundle parameter,
 * while the channel format (interleaved/non-interleaved) is set through the
 * TDAS_IN_CHAN_FORMAT bundle parameter.
 *
 * The ouput buffer (out) is also pre-allocated.  The output samples can also
 * be interleaved or non-interleaved, depending on what has been set for
 * the TDAS_IN_CHAN_FORMAT bundle parameter.
 *
 * n_samples is the number of samples in the input buffer, per channel.
 *
 * When the input buffer contains interleaved samples, corresponding samples
 * from each channel are placed contiguously.  e.g. for stereo input and
 * n_samples = n, the samples in the input buffer are laid out as follows:
 * L0 R0 L1 R1 L2 R2 ... Ln Rn
 *
 * When the input buffer contains non-interleaved samples, all available 
 * samples for a channel are contiguous.  e.g. for stereo input and
 * n_samples = n, the samples in the input buffer are laid out as follows:
 * L0 L1 L2 ... Ln R0 R1 R2 ... Rn
 *
 * Similar reasoning is applied for the logical positioning of samples
 * in the output buffer.  The number of output channels is two (stereo) in
 * all standard operating conditions.  (There are various TDAS
 * configurations possible that will result in four channel output, but 
 * these are intended for diagnostic purposes only, not for normal
 * operation exposed to the end-user.)
 *
 * The amount of memory that needs to be allocated for the input buffer is:
 *      <no. input channels> * n_samples * sizeof(IO_DATUM)
 * 
 * The amount of memory that needs to be allocated for the output buffer is:
 *      <no. output channels> * n_samples * sizeof(IO_DATUM) * <rate multiplier>
 * where <rate multiplier> is the ratio between the output sample rate and
 * the input sample rate, specified through the TDAS_RATE_MULTIPLIER
 * bundle parameter.  <rate multiplier> thus also affects the number of
 * samples per channel for the output buffer:
 *      <no. output samples per channel> = n_samples * <rate multiplier>
 * 
 * It is permissible for in and out to point to the same memory location, as
 * long as all of the following conditions are met:
 * - The number of input channels is greater than or equal to the number of
 *   output channels.
 * - The input sample rate is equal to the output sample rate.
 */
#ifdef __cplusplus
extern "C" {
#endif
#ifdef SYMBIAN_DLL
IMPORT_C
#endif
#ifdef TDAS_PROCESS_NSAMPLES_CHECK
int
#else
void 
#endif
tdas_process(void *v_tdas, IO_DATUM *in, IO_DATUM *out, int n_samples);
#ifdef __cplusplus
}
#endif

/* Features */
#define TDAS_BUNDLE 0
#define TDAS_M2S 1
#define TDAS_SSE 2
#define TDAS_SSH 3 
#define TDAS_SLC 4
#define TDAS_VOL 5
#define TDAS_NB 6
#define TDAS_GEQ 7
#define TDAS_MUP 8
#define TDAS_MSR 9
#define TDAS_HFE 10
#define TDAS_FADE 11
#define TDAS_N_FEATURES 12 /* TDAS_N_FEATURES includes the TDAS bundle itself. */

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define TDAS_VERSION		 0	/* set on initialisation, don't overwrite */
#define TDAS_SAMPLERATE		 1
#define TDAS_IN_CHANS		 2
#define TDAS_IN_MATRIX		 3
#define TDAS_BYPASS			 4
#define TDAS_RATE_MULTIPLIER 5
#define TDAS_IN_CHAN_FORMAT  6
#define TDAS_DOWNMIX_CONFIG  7  /* DIAGNOSTIC USE: For testing downmixer */
#ifndef SUPPORT_MONO_CHANNEL_OUTPUT 
#define TDAS_PARAMLIST_LEN	8
#else
#define TDAS_OUT_CHANS		8
#define TDAS_PARAMLIST_LEN	9
#endif

/* TDAS_SAMPLERATE - indices of supported sample rates */
#define SAMPLERATE_48000		 0
#define SAMPLERATE_44100		 1
#define SAMPLERATE_32000		 2
#define SAMPLERATE_24000         3
#define SAMPLERATE_22050         4
#define SAMPLERATE_16000         5
#define SAMPLERATE_12000         6
#define SAMPLERATE_11025         7
#define SAMPLERATE_8000          8
#define N_SAMPLERATES	         9

#define SAMPLERATE_MAX           SAMPLERATE_48000

/* TDAS feature processing can take place at the following
 * sample rates: 48, 44.1, 32, 24 kHz.
 */
#define TDAS_N_SAMPLERATES   (SAMPLERATE_24000 + 1)

/* TDAS_RATE_MULTIPLIER -
 * Identifiers for the supported upsampler multiplier values. */
#define SAMPLERATE_MULTIPLIER_1         0
#define SAMPLERATE_MULTIPLIER_2         1
#define SAMPLERATE_MULTIPLIER_4         2
#define TDAS_N_SAMPLERATE_MULTIPLIERS   3 

/* TDAS_IN_CHANS - refer to channel enumeration in docs */
/* Note - the ordering of the channel configurations in this
 * enum has been deliberately kept consistent with those in
 * Dolby Digital.
 */
enum 
{
	CHANS_RESERVED = 0,
	CHANS_C,
	CHANS_L_R,
	CHANS_L_C_R,
	CHANS_L_R_S,
	CHANS_L_C_R_S,
	CHANS_L_R_Ls_Rs,
	CHANS_L_C_R_Ls_Rs,
    CHANS_RESERVED_2 = 8,
	CHANS_C_LFE,
	CHANS_L_R_LFE,
	CHANS_L_C_R_LFE,
	CHANS_L_R_S_LFE,
	CHANS_L_C_R_S_LFE,
	CHANS_L_R_Ls_Rs_LFE,
	CHANS_L_C_R_Ls_Rs_LFE,
    TDAS_N_IN_CHANS,
}; 
#define TDAS_MAX_IN_CHANS 6  /* 5.1 channel input */

/*
 * TDAS_IN_MATRIX - Determines, for 2-channel input (TDAS_IN_CHANS = CHANS_L_R),
 *                      how they are mixed to form the 2-channel signal processed by TDAS.
 *      0: stereo - left and right input channels are treated normally.
 *                  i.e. TDAS processes L, R
 *		1: channel one mono - right channel is replaced by left input channel internally.
 *                            i.e. TDAS processes L, L
 *      2: channel two mono - left channel is replaced by the right input channel internally.
 *                            i.e. TDAS processes R, R
 *		3: dual mono - both channels are summed and replicated to both channels internally.
 *                     i.e. TDAS processes (L+R), (L+R)
 */
enum
{
	MATRIX_STEREO,
	MATRIX_LEFT,
	MATRIX_RIGHT,
	MATRIX_DUALMONO
};
#define TDAS_N_IN_MATRICES		4

/*
 * TDAS_IN_CHAN_FORMAT - 0: interlaced channels
 *                           1: de-interlaced channels
 */
enum
{
    CHAN_FORMAT_INTERLACED,
    CHAN_FORMAT_DEINTERLACED,
    TDAS_N_CHAN_FORMATS
};

/* Identifiers for the valid internal TDAS channel configurations. 
 * They are also used to specify the TDAS_DOWNMIX_CONFIG bundle
 * parameter.
 *
 * TDAS_DOWNMIX_CONFIG - 0: downmix to shuffled L/R channels (2 channels)
 *                           1: downmix to L, R channels (2 channels)
 *                           2: downmix to shuffled L/R, shuffled Ls/Rs channels (4 channels)
 *                           3: downmix to L, R, Ls, Rs channels (4 channels)
 */
enum
{
    INTERNAL_CHANS_SHUFFLED_L_R,
    INTERNAL_CHANS_UNSHUFFLED_L_R,
    INTERNAL_CHANS_SHUFFLED_L_R_Ls_Rs,
    INTERNAL_CHANS_UNSHUFFLED_L_R_Ls_Rs,
    TDAS_N_INTERNAL_CHAN_CONFIGS
};

/* Under normal operation, TDAS produces stereo output,
 * but can also generate 4-channel (L, R, Ls, Rs) output.
 */
#define TDAS_N_OUT_CHANS_MAX        4
#define TDAS_N_OUT_CHANS_STEREO		2

/* TDAS_BYPASS - bypass defeated (0) or bypass on (1) */
#define TDAS_N_BYPASSES			2

#define TDAS_HEADROOM_SHIFT		2 /* scale factor for boost coeffs */

#define TDAS_HEADROOM_POLYN_SHIFT	3 /* scale factor used in polynomial calculations for headroom */

#define TDAS_DB_SCALE			5 /* right shifts used to represent a 
									   * dB integer (up to 31dB) as a coeff 
									   */ 

/* TRUE/FALSE */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define M2S_ENABLE			0	/* all features have enable as first param */
#define M2S_DETECTOR		1
#define M2S_PARAMLIST_LEN	2

/* M2S_ENABLE - 0 is feature off, 1 is feature on */
#define M2S_N_ENABLES		2

/* M2S_DETECTOR - 0 is mono detection off, 1 is mono detection on */
#define M2S_N_DETECTORS	2

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define SSH_ENABLE			0	/* all features have enable as first param */
#define SSH_MODE			1
#define SSH_PARAMLIST_LEN	2

/* SSH_ENABLE - 0 is feature off, 1 is feature on */
#define SSH_N_ENABLES		2

/* SSH_MODE - the modes are a combination of distance and width, as 
 * described in the system integration manual
 */
#define SSH_N_MODES		7	/* 7 distance/width combinations */

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define SSE_ENABLE			0	/* all features have enable as first param */
#define SSE_WIDTH			1
#define SSE_SPK_MODE		2
#define SSE_PARAMLIST_LEN	3

/* SSE_ENABLE - 0 is feature off, 1 is feature on */
#define SSE_N_ENABLES		2

/* SSE_WIDTH - 0 is half width, 1 is full width */
#define SSE_N_WIDTHS		2

/* Define mode index */
#define SSE_HALF_MODE		0
#define SSE_FULL_MODE		1

/* SSE_SPK_MODE - 0 is narrow, 1 is normal and 2 is binarual mode */
#define SSE_N_SPK_MODES	3

#define SSE_NORMAL_MODE   0
#define SSE_NARROW_MODE	1
#define SSE_BINAURAL_MODE 2

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define SLC_ENABLE			0	/* all features have enable as first param */
#define SLC_LEVEL			1
#define SLC_DEPTH			2
#define SLC_PARAMLIST_LEN	3

/* SLC_ENABLE - 0 is feature off, 1 is feature on */
#define SLC_N_ENABLES		2

/* SLC_LEVEL - discrete input audio levels, 0-6, 0 is really loud music,
 *                   6 is quiet film
 */
#define SLC_N_LEVELS		7

/* SLC_DEPTH - depth of effect, 0 is light, 1 is medium, 2 is 
 * comprehensive
 */
#define SLC_N_DEPTHS		3	/* night, evening, and midnight */

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define VOL_ENABLE			0	/* all features have enable as first param */
#define VOL_GAIN_INTERNAL	    1
#define VOL_GAIN_EXTERNAL	2
#define VOL_GAIN_TYPE		3
#define VOL_BALANCE			4
#define VOL_MUTE			5				
#define VOL_PARAMLIST_LEN	6

/* VOL_ENABLE - 0 is feature off, 1 is feature on */
#define VOL_N_ENABLES		2

/*
 * Volume is defined as 2^(VOL_BITS_IN_GAIN-1) discrete steps.
 */
#define VOL_BITS_IN_GAIN		8
#define VOL_N_GAINS_TDAS	    (1<<(VOL_BITS_IN_GAIN))
#define VOL_N_GAINS_EXTERNAL	(1<<(VOL_BITS_IN_GAIN))

/* VOL_GAIN_TYPE - 0 is linear gain, 1 is log gain */
#define VOL_N_GAIN_TYPES		2

enum {VOL_LINEAR, VOL_LOGARITHMIC};

/* VOL_BALANCE
 * This is specified as a signed integer value from -128 to 127.
 * -128 corresponds with audio fully panned to the left,
 * 127 corresponds with audio fully panned to the right.
 */
#define VOL_BITS_IN_BALANCE	(VOL_BITS_IN_GAIN-1)
#define VOL_BALANCE_MIN		(-1<<VOL_BITS_IN_BALANCE)
#define VOL_BALANCE_MAX		((1<<VOL_BITS_IN_BALANCE)-1)


/* VOL_MUTE - 0 is not muted, 1 is muted */
#define VOL_N_MUTES		2

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define NB_ENABLE			0	/* all features have enable as first param */
#define NB_CUTOFF			1
#define NB_BOOST			2
#define NB_LEVEL			3
#define NB_PARAMLIST_LEN	4

/* NB_ENABLE - 0 is feature off, 1 is feature on */
#define NB_N_ENABLES		2

/* NB_CUTOFF - discrete cutoff frequencies, as described in the 
 * system integration manual 
 */
#define NB_N_CUTOFFS		24

/* NB_BOOST - discrete boost levels, as described in the 
 * system integration manual
 */
#define NB_N_BOOSTS		7

/* NB_LEVEL - defines the output capabilities of your speakers, as 
 * described in the system integration manual
 */
#define NB_N_LEVELS		7

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define GEQ_ENABLE			0	/* all features have enable as first param */
#define GEQ_NBANDS			1
#define GEQ_PREAMP			2
#define GEQ_MAXBOOST		3
#define GEQ_BAND1			4   /* all geq bands must be sequential */
#define GEQ_BAND2			5
#define GEQ_BAND3			6
#define GEQ_BAND4			7
#define GEQ_BAND5			8
#define GEQ_BAND6			9
#define GEQ_BAND7			10
#define GEQ_PARAMLIST_LEN	11

#define GEQ_STEP_BITS		2	
#define GEQ_STEP			(1<<GEQ_STEP_BITS)	  /* 0.25 dB step size */
			
#define GEQ_MINGAIN			-12<<GEQ_STEP_BITS  /* minimum allowed gain in dB */
#define GEQ_MAXGAIN			12<<GEQ_STEP_BITS   /* maximum allowed gain in dB */

/* limits are applied to the range of preamp and maxboost */
#define GEQ_MIN_PREAMP		GEQ_MINGAIN	
#define GEQ_MAX_PREAMP		0

#define GEQ_MIN_MAXBOOST	0
#define GEQ_MAX_MAXBOOST	GEQ_MAXGAIN

/* Default GEQ settings */
#define GEQ_DEFAULT_PREAMP  0					/* default to 0dB */
#define GEQ_DEFAULT_MAXBOOST (6<<GEQ_STEP_BITS) /* default to 6dB */

/* GEQ_ENABLE - 0 is feature off, 1 is feature on */
#define GEQ_N_ENABLES		2

/* GEQ_NBANDS */
#define GEQ_N_BANDS_MIN		2
#define GEQ_N_BANDS_MAX		7

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define MUP_ENABLE		0	/* all features have enable as first param */
#define MUP_PARAMLIST_LEN	1

/* Number of MUP enable modes - 0 is feature off, 1 is feature on */
#define MUP_N_ENABLES		2

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define MSR_ENABLE          0	/* all features have enable as first param */
#define MSR_PARAMLIST_LEN   1

/* Number of MSR enable modes - 0 is feature off, 1 is feature on */
#define MSR_N_ENABLES		2

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define HFE_ENABLE			0	/* all features have enable as first param */
#define HFE_DEPTH			1
#define HFE_PARAMLIST_LEN	2

/* HFE_ENABLE - 0 is feature off, 1 is feature on */
#define HFE_N_ENABLES		2

#define HFE_N_DEPTHS		7

/*---------------------------------------------------------------------------*/

/* Parameters are indexed in the state structure by their position in the 
 * array. Each parameter is of type INTEGER.
 */
#define FADE_ENABLE			0	/* all features have enable as first param */
#define FADE_TARGET			1
#define FADE_TIME			2
#define FADE_PARAMLIST_LEN	3

/* FADE_ENABLE - 0 is feature off, 1 is feature on */
#define FADE_N_ENABLES		2

#define FADE_TIME_LUT_SCALE_SHIFT	5												/* 1 << 5 = 32 msec increments */
#define FADE_TIME_LUT_MAX_INDEX		31

#define FADE_TIME_LUT_MAX_VAL		(FADE_TIME_LUT_MAX_INDEX << FADE_TIME_LUT_SCALE_SHIFT)

#define FADE_TIME_MIN (1 << FADE_TIME_LUT_SCALE_SHIFT)								/* 32   msec */
#define FADE_TIME_MAX ((FADE_TIME_LUT_MAX_INDEX << FADE_TIME_LUT_SCALE_SHIFT) * 4)	/* 3968 msec */

#endif /* TDAS_H */

