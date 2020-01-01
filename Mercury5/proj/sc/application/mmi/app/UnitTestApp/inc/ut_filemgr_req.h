#ifndef __UT_FILEMGR_REQ_H__
#define __UT_FILEMGR_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getFileMgr_UT(void);
int   noFileMgr_UT(void);
void  releaseFileMgr_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_FILEMGR_REQ_H__ */
