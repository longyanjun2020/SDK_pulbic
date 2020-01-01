#ifndef M4VMBLOCK_H
#define M4VMBLOCK_H

#include "avp_m4vPrivate.h"

#define DQ(q) (((QUANT_TYPE)(q))-1-INONZERO(((QUANT_TYPE)(q))-1,2))
//#define ADD_DQ(q, dq)  (q) +=DQ(dq); (q) = MUX((q) > 31, 31, MUX((q) < 1, 1, (q)));
#define ADD_DQ(q, dq)  (q) +=DQ(dq); (q) = myUCLIP((q), 1, 31);

//int macroblock(M4V_HANDLE *hp);
err_type mp4v_macroblock_i_vop(M4V_HANDLE *hp);
err_type mp4v_macroblock_p_vop(M4V_HANDLE *hp); //can't use ATTR_INST16
err_type mp4v_macroblock_b_vop(M4V_HANDLE *hp);
err_type mp4v_macroblock_gmc_vop(M4V_HANDLE *hp);
#ifdef USE_ROW_BUFFER
void mp4v_rowbuf_padding_2_framebuf(M4V_HANDLE *hp);
#endif

void macroblock_ec(M4V_HANDLE *hp);

err_type ATTR_INST16 mp4v_getMCBPC_i_vop(BITSBUF *bs);
err_type ATTR_INST16 mp4v_getMCBPC_p_vop(BITSBUF *bs);
int ATTR_INST16 mp4v_getCBPY(BITSBUF *bs);

#endif // M4VMBLOCK_H
