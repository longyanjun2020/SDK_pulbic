#ifndef M4VBLOCK_H
#define M4VBLOCK_H

#define TOP  0x1
#define LEFT 0x2
#define NONE 0x0 // why needs it, still not clear...

//for indexing ac_store_top[mb_x][b][0..6] and ac_store_left[b][0..6]
// 0, 1, 2, 3, 4, 5 => 0, 1, 2, 3
#define b2i_TOP(b)  MUX((b)>3, ((b)&0x01)+2, (b)&(TOP))
#define b2i_LEFT(b) MUX((b)>3, ((b)&0x01)+2, ((b)&(LEFT))!=0)
//#define b2i_LEFT(b) (((b)>>1)+((b)==5))

#if 0//def _AG_S32_
#define get_dct_dc_size_lum(bs) get_dct_dc_size_xxxx(bs, 1)
#define get_dct_dc_size_chr(bs) get_dct_dc_size_xxxx(bs, 0)
int /*ATTR_INST16*/ get_dct_dc_size_xxxx(int bs, int luma);
#else
int ATTR_INST16 get_dct_dc_size_lum(BITSBUF *bs); //Table B-13, P214
int ATTR_INST16 get_dct_dc_size_chr(BITSBUF *bs); //Table B-14, P214
#endif
int get_dc_differential(BITSBUF *bs, int dct_dc_size); //Table B-15, P215

err_type mp4vIntraBlock(M4V_HANDLE *hp, short *RESTRICT block, int block_num, int coded); //can't use ATTR_INST16
err_type mp4vInterBlock(M4V_HANDLE *hp, short *RESTRICT block, int block_num); //can't ATTR_INST16

void mp4v_dc_recon(M4V_HANDLE *hp, int block_num, short * RESTRICT dc_value, int32 dc_scaler);
void ac_rescale_recon_store(M4V_HANDLE *hp, int block_num, short * RESTRICT psBlock, uint1 ac_pred_flag); //can't use ATTR_INST16

#ifdef SUPPORT_WMV
void wmv3_dc_recon(M4V_HANDLE *hp, int block_num, short * RESTRICT dc_value, uint32 dc_scaler);
void rescue_predict_mb4mv_wmv3(M4V_HANDLE *hp);
void rescue_predict_mb_wmv3(M4V_HANDLE *hp);
#endif

void CvtFieldToFrame(short *block); // Convert field blocks to frame blocks

#endif // M4VBLOCK_H
