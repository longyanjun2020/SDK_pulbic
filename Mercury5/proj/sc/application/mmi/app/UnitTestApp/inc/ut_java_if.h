/* ut_java_if.h */
#ifndef __UT_JAVA_IF_H__
#define __UT_JAVA_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getJava_if_UT(void);
int   noJava_if_UT(void);
void  releaseJava_if_UT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_JAVA_IF_H__ */
