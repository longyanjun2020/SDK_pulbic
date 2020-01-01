#ifndef H263PPBLOCK_H
#define H263PPBLOCK_H
#include "avp_m4vPrivate.h"

#ifdef WIN32
//#define _DUMP_VLD_
//#define _DUMP_IDCT_
//#define _DUMP_ADB_
//#define _DUMP_MC_
#endif

err_type IntraBlock_shv_adv(M4V_HANDLE *hp, short * block, int block_num, int coded);

#endif
