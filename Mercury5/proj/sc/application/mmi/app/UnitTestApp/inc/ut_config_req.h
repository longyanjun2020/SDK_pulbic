/* ut_config_req.h */
#ifndef __UT_CONFIG_REQ_H__
#define __UT_CONFIG_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCONFIG_UT(void);
int   noCONFIG_UT(void);
void  releaseCONFIG_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CONFIG_REQ_H__ */
