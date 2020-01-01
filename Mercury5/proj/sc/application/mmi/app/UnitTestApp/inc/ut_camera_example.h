/* ut_camera_example.h */
#ifndef __UT_CAMERA_EXAMPLE_H__
#define __UT_CAMERA_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetCamera_Example(void);
int   NumCamera_Example(void);
void  ReleaseCamera_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CAMERA_EXAMPLE_H__ */
