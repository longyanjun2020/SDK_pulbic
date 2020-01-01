/* ut_vendor_if.h */
#ifndef __UT_VENDOR_IF_H__
#define __UT_VENDOR_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getVendor_IF_UT(void);
int   noVendor_IF_UT(void);
void  releaseVendor_IF_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_VENDOR_IF_H__ */
