/* ut_profile_if.h */
#ifndef __UT_PROFILE_IF_H__
#define __UT_PROFILE_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getProfile_If_UT(void);
int   noProfile_If_UT(void);
void  releaseProfile_If_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_PROFILE_IF_H__ */
