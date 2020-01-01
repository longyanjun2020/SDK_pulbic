/*
   declaration of constant tables
 */
#ifndef ROM_H
#define ROM_H

#include "ffr.h"
#include "fft.h"
#include "psy_const.h"
#include "tns_param.h"


extern const Word32 ShortWindowSine [FRAME_LEN_SHORT/2];

/*
  form factor
*/
extern const Word32 formfac_sqrttable[96];

/*
  quantizer
*/
extern const Word32 mTab_3_4[512];
extern const Word32 mTab_4_3[512];
/*! $2^{-\frac{n}{16}}$ table */
extern const Word16 pow2tominusNover16[17] ;

extern Word32 specExpMantTableComb_enc[4][14];
extern const UWord8 specExpTableComb_enc[4][14];

extern const Word16 quantBorders[4][4];

extern const Word16 quantRecon0[4];
extern const Word16 quantRecon1[4];
extern const Word16 quantRecon2[4];
/*
  huffman
*/
extern const UWord16 huff_ltab1_2[3][3][3][3];
extern const UWord16 huff_ltab3_4[3][3][3][3];
extern const UWord16 huff_ltab5_6[9][9];
extern const UWord16 huff_ltab7_8[8][8];
extern const UWord16 huff_ltab9_10[13][13];
extern const UWord16 huff_ltab11[17][17];
extern const UWord16 huff_ltabscf[121];
extern const UWord16 huff_ctab1[3][3][3][3];
extern const UWord16 huff_ctab2[3][3][3][3];
extern const UWord16 huff_ctab3[3][3][3][3];
extern const UWord16 huff_ctab4[3][3][3][3];
extern const UWord16 huff_ctab5[9][9];
extern const UWord16 huff_ctab6[9][9];
extern const UWord16 huff_ctab7[8][8];
extern const UWord16 huff_ctab8[8][8];
extern const UWord16 huff_ctab9[13][13];
extern const UWord16 huff_ctab10[13][13];
extern const UWord16 huff_ctab11[17][17];
extern const UWord32 huff_ctabscf[121];



/*
  misc
*/

extern const UWord8 sfb_16000_long_1024[];
extern const UWord8 sfb_16000_short_128[];
extern const UWord8 sfb_22050_long_1024[];
extern const UWord8 sfb_22050_short_128[];
extern const UWord8 sfb_24000_long_1024[];
extern const UWord8 sfb_24000_short_128[];
extern const UWord8 sfb_32000_long_1024[];
extern const UWord8 sfb_32000_short_128[];
extern const UWord8 sfb_44100_long_1024[];
extern const UWord8 sfb_44100_short_128[];
extern const UWord8 sfb_48000_long_1024[];
extern const UWord8 sfb_48000_short_128[];
extern const Word32 m_log2_table[INT_BITS];

/*
  TNS
*/
extern const TNS_MAX_TAB_ENTRY tnsMaxBandsTab[3];
extern const TNS_CONFIG_TABULATED  p_8000_mono_long;
extern const TNS_CONFIG_TABULATED  p_8000_mono_short;
extern const TNS_CONFIG_TABULATED  p_8000_stereo_long;
extern const TNS_CONFIG_TABULATED  p_8000_stereo_short;
extern const TNS_CONFIG_TABULATED  p_16000_mono_long;
extern const TNS_CONFIG_TABULATED  p_16000_mono_short;
extern const TNS_CONFIG_TABULATED  p_16000_stereo_long;
extern const TNS_CONFIG_TABULATED  p_16000_stereo_short;
extern const TNS_CONFIG_TABULATED  p_24000_mono_long;
extern const TNS_CONFIG_TABULATED  p_24000_mono_short;
extern const TNS_CONFIG_TABULATED  p_24000_stereo_long;
extern const TNS_CONFIG_TABULATED  p_24000_stereo_short;
extern const TNS_CONFIG_TABULATED  p_32000_mono_long;
extern const TNS_CONFIG_TABULATED  p_32000_mono_short;
extern const TNS_CONFIG_TABULATED  p_32000_stereo_long;
extern const TNS_CONFIG_TABULATED  p_32000_stereo_short;
extern const TNS_INFO_TAB tnsInfoTab[4];
extern const Word32 tnsCoeff3[8];
extern const Word32 tnsCoeff3Borders[8];
extern const Word32 tnsCoeff4[16];
extern const Word32 tnsCoeff4Borders[16];
#endif
