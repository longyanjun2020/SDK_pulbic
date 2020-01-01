/* ut_cc_req.h */
#ifndef __UT_CC_REQ_H__
#define __UT_CC_REQ_H__

#include "ut_def.h"

#ifdef __UNITTEST_INTERFACE__
void CC_MakeCallReq_save(int CLIRInfo, u8 *pCallNum, u8 DualID);
#endif    /* __UNITTEST_INTERFACE__ */

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCC_UT(void);
int   noCC_UT(void);
void  releaseCC_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CC_REQ_H__ */
