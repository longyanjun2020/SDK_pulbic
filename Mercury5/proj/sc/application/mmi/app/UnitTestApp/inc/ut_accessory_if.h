/* ut_accessory_if.h */
#ifndef __UT_ACCESSORY_IF_H__
#define __UT_ACCESSORY_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getAccessory_If_UT(void);
int   noAccessory_If_UT(void);
void  releaseAccessory_If_UT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_ACCESSORY_IF_H__ */
