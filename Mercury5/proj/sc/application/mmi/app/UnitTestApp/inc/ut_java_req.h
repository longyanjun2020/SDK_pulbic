/* ut_java_req.h */
#ifndef __UT_JAVA_REQ_H__
#define __UT_JAVA_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getJava_UT(void);
int   noJava_UT(void);
void  releaseJava_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_JAVA_REQ_H__ */
