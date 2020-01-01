/* ut_wlan_if.h */
#ifndef __UT_WLAN_IF_H__
#define __UT_WLAN_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getWLan_If_UT(void);
int   noWLan_If_UT(void);
void  releaseWLan_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_WLAN_IF_H__ */
