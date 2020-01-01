/* ut_phb_if.h */
#ifndef __UT_PHB_IF_H__
#define __UT_PHB_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getPHB_if_UT(void);
int   noPHB_if_UT(void);
void  releasePHB_if_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_PHB_IF_H__ */
