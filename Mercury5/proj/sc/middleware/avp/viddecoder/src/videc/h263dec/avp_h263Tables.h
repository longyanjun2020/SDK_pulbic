#ifndef H263TABLES_H
#define H263TABLES_H

#include "avp_mvc_types.h"

typedef struct m4v_tables_s
{
    uchar zig_zag_scan[64];
    uchar alternate_vertical_scan[64];
    uchar alternate_horizontal_scan[64];
    uchar intra_quant_matrix[64]; // this is default, the current values should be in instance
    uchar inter_quant_matrix[64];

    tab_type MCBPCtabIntra[32];
    tab_type MCBPCtabInter[256];
    tab_type CBPYtab[48];

    tab_type MVtab0[14];
    tab_type MVtab1[96];
    tab_type MVtab2[124];

} m4v_tables_st;

extern const m4v_tables_st m4vTables; // defined in h263Tables.c

#endif /* H263TABLES_H */
