#ifndef __UT_PHB_REQ_H__
#define __UT_PHB_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getPhb_UT(void);
int   noPhb_UT(void);
void  releasePhb_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_PHB_REQ_H__ */
