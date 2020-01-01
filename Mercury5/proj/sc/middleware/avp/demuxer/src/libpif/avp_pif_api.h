#ifndef PIF_API_H
#define PIF_API_H

#include <stdio.h>
#include "avp_pif.h"

#ifdef __cplusplus
extern "C" {
#endif
void initPIF();
void checkRetVal(pif_err_t rv);
#ifdef __cplusplus
}
#endif

#define wreg(bank, addr, val) { \
    int addr2; \
    pif_err_t rv; \
    addr2 = ((1<<15) | ((bank)<<8) | ((addr)*2))>>1; \
	rv = pif_write(PIF_DEFAULT_SID, addr2, (val)); \
    checkRetVal(rv); \
}

#define rreg(bank, addr, val) { \
    int addr2; \
    pif_err_t rv; \
    addr2 = ((1<<15) | ((bank)<<8) | ((addr)*2))>>1; \
    rv = pif_read(PIF_DEFAULT_SID, addr2, &val); \
	checkRetVal(rv); \
}

#endif // PIF_API_H
