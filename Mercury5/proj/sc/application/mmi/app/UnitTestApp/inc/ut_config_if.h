/* ut_config_if.h */
#ifndef __UT_CONFIG_IF_H__
#define __UT_CONFIG_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getConfig_If_UT(void);
int   noConfig_If_UT(void);
void  releaseConfig_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CONFIG_IF_H__ */
