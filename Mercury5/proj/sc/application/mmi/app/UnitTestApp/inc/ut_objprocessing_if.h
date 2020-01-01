/* ut_objprocessing_if.h */
#ifndef __UT_OBJPROCESSING_IF_H__
#define __UT_OBJPROCESSING_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getObjprocessing_If_UT(void);
int   noObjprocessing_If_UT(void);
void  releaseObjprocessing_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_OBJPROCESSING_IF_H__ */
