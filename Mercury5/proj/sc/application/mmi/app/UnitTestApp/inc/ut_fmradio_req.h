/* ut_fmradio_req.h */
#ifndef __UT_FMRADIO_H__
#define __UT_FMRADIO_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getFMRadio_UT(void);
int   noFMRadio_UT(void);
void  releaseFMRadio_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_FMRADIO_H__ */
