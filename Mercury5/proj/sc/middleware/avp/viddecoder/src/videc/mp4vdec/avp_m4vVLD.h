#ifndef M4VVLD_H
#define M4VVLD_H
#include "avp_h263Tables.h"

/* MPEG-4 */
event_t vldGetDCTCoeff_I(BITSBUF *bs);
event_t vldGetDCTCoeff_I_esc_mode(BITSBUF *bs);
event_t vldGetDCTCoeff_N(BITSBUF *bs);
event_t vldGetDCTCoeff_N_esc_mode(BITSBUF *bs);
event_t vldGetDCTCoeff_IR(BITSBUF *bs);
event_t vldGetDCTCoeff_IR_esc_mode(BITSBUF *bs);
event_t vldGetDCTCoeff_NR(BITSBUF *bs);
event_t vldGetDCTCoeff_NR_esc_mode(BITSBUF *bs);
/* WMV1 */
event_t divxvldTables_I2(M4V_HANDLE *hp);
event_t divxvldTables_N5(M4V_HANDLE *hp);

#define B16_ESCAPE  7    //code length can not be changed...
#define B17_ESCAPE B16_ESCAPE
// set last=0 (keep in the same block), run to max (over 63 quickly), level to 0 (no error coeff) and length to 0xd (the maximal possible codeword length)
#define B16_INVALID ((0 << 15) | (0x1f << 10) | (0 << 5) | (0xd))
//#define B16_INVALID 0x7fff //-1
#define B17_INVALID B16_INVALID
#define B16_ENTRY_NUM (112 + 96 + 128)
#define B17_ENTRY_NUM (112 + 96 + 128)
#ifdef SUPPORT_H263PP
#define I2_ENTRY_NUM  (112 + 96 + 128)
#else
#define I2_ENTRY_NUM 0
#endif

#define B16_ENTRY_START 0
#define B17_ENTRY_START B16_ENTRY_NUM
#define I2_ENTRY_START (B16_ENTRY_NUM+B17_ENTRY_NUM)

extern const tab_type2b tableB16_B17[B16_ENTRY_NUM + B17_ENTRY_NUM + I2_ENTRY_NUM];

#endif /* M4VVLD_H */
