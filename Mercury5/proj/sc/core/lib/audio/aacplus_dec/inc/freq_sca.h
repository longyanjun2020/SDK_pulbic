/*
   frequency scale prototypes
 */
#ifndef __FREQ_SCA_H
#define __FREQ_SCA_H

#include "env_extr.h"



Word16
sbrdecUpdateFreqScale(Word16 * v_k_master,
                      Word16 *numMaster,
                      SBR_HEADER_DATA * headerData);

void shellsort(Word16 *in, Word16 n);

Word16
resetFreqBandTables(HANDLE_SBR_HEADER_DATA hHeaderData);


#endif
