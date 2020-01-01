#ifndef __UT_MMS_IF_H__
#define __UT_MMS_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMms_if_UT(void);
int   noMms_if_UT(void);
void  releaseMms_if_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MMS_IF_H__ */
