#ifndef __UT_FILEMGR_EXAMPLE_REQ_H__
#define __UT_FILEMGR_EXAMPLE_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getFileMgrExample_UT(void);
int   noFileMgrExample_UT(void);
void  releaseFileMgrExample_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_FILEMGR_EXAMPLE_REQ_H__ */
