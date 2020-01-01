#ifndef __HE_AAC_DECODER_SBR_CONSTANTS_H__
#define __HE_AAC_DECODER_SBR_CONSTANTS_H__

#define T_HFGEN 8
#define T_HFADJ 2

#define EXT_SBR_DATA     13
#define EXT_SBR_DATA_CRC 14

#define FIXFIX 0
#define FIXVAR 1
#define VARFIX 2
#define VARVAR 3

#define LO_RES 0
#define HI_RES 1

#define NO_TIME_SLOTS_960 15
#define NO_TIME_SLOTS     16
#define RATE              2
#define NO_TIME_SLOTS_RATE  NO_TIME_SLOTS*RATE
#define SBR_RATE           2

#define NOISE_FLOOR_OFFSET 6


#ifdef PS_DEC
/* constants */
#define NEGATE_IPD_MASK            (0x80)
#define EXTENSION_ID_PS 2
#define QMF_SHORT_DELAY_BAND     35 
#define QMF_ALLPASS_BAND         22


#define BORDER_POS_0     0
//#define NUM_QMF_SLOTS    32

#define MAX_PS_ENVELOPES 5
#define NO_ALLPASS_LINKS 3

#define HYBRID_FRAME_SIZE 0x20
#endif


#define MAX_ENVELOPES            5
#define MAX_NOISE_ENVELOPES      2
#define SBR_ENERGY_PAN_OFFSET   12
#define DECAY_COUPLING           1
#define DECAY                    1
#define MAX_FREQ_COEFFS         48
#define TIME                      1
#define FREQ                      0
#define MAX_NOISE_COEFFS         5
#define MAX_INVF_BANDS          MAX_NOISE_COEFFS
#define SBR_AMP_RES_3_0         1
#define SBR_MAX_ENERGY          35
#define LOW_RES                 0
#define HIGH_RES                1


#define COUPLING_OFF    0
#define COUPLING_LEVEL  1
#define COUPLING_BAL    2
  
  
#define SBR_NOT_INITIALIZED   0
#define UPSAMPLING            1
#define SBR_ACTIVE            2

#define MAXNRELEMENTS         2
#define MAXSBRBYTES          (255+14)


// default SBR CRC G(x) = x^10 + x^9 + x^5 + x^4 + x + 1 
#define SBR_CRC_POLY                  0x0233
#define SBR_CRC_MASK                  0x0200
#define SBR_CRC_START                 0x0000
#define SBR_CRC_RANGE                 0x03FF


#define sbr_abs(A) (((A) > 0) ? (A) : (-(A)))

#endif

