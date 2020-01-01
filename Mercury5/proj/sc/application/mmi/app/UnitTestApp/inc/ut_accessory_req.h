/* ut_accessory_req.h */
#ifndef __UT_ACCESSORY_REQ_H__
#define __UT_ACCESSORY_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getAccessory_UT(void);
int   noAccessory_UT(void);
void  releaseAccessory_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_ACCESSORY_REQ_H__ */
