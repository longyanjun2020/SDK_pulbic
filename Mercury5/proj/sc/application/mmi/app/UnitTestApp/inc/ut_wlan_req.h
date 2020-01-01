/* ut_wlan_req.h */
#ifndef __UT_WLAN_REQ_H__
#define __UT_WLAN_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getWLan_UT(void);
int   noWLan_UT(void);
void  releaseWLan_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_WLAN_REQ_H__ */
