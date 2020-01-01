/* ut_objprocessing_req.h */
#ifndef __UT_OBJPROCESSING_REQ_H__
#define __UT_OJBPROCESSING_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getObjprocessing_UT(void);
int   noObjprocessing_UT(void);
void  releaseObjprocessing_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_OJBPROCESSING_REQ_H__ */
