/* ut_mms_req.h */
#ifndef __UT_MMS_REQ_H__
#define __UT_MMS_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMMS_UT(void);
int   noMMS_UT(void);
void  releaseMMS_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MMS_REQ_H__ */
