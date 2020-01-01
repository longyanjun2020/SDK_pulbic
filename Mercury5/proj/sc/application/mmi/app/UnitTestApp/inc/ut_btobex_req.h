/* ut_btobex_req.h */
#ifndef __UT_BTOBEX_REQ_H__
#define __UT_BTOBEX_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getBTOBEX_UT(void);
int   noBTOBEX_UT(void);
void  releaseBTOBEX_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_BTOBEX_REQ_H__ */
