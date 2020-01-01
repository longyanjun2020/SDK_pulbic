#ifndef _RV_HASHU_H
#define _RV_HASHU_H

#include "rvtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

RVCOREAPI
RvSize_t RvHashNextPrime(RvSize_t n);
#define _rvHashNextPrime(n) RvHashNextPrime(n)

#ifdef __cplusplus
}
#endif

#endif

