#ifndef __UT_CORE_REQ_H__
#define __UT_CORE_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCore_UT(void);
int   noCore_UT(void);
void  releaseCore_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CORE_REQ_H__ */
