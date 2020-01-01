/* ut_codepage_convert_req.h */
#ifndef __UT_CODEPAGE_CONVERT_H__
#define __UT_CODEPAGE_CONVERT_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCodePageConvert_UT(void);
int   noCodePageConvert_UT(void);
void  releaseCodePageConvert_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CODEPAGE_CONVERT_H__ */
