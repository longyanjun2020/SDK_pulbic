/* ut_sensormgr_example.h */
#ifndef __UT_SENSORMGR_EXAMPLE_H__
#define __UT_SENSORMGR_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetSensorMgr_Example(void);
s32   NumSensorMgr_Example(void);
void  ReleaseSensorMgr_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SENSORMGR_EXAMPLE_H__ */

