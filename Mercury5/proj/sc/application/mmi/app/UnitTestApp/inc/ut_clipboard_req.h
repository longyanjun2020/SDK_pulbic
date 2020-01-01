/* ut_clipboard_req.h */
#ifndef __UT_CLIPBOARD_REQ_H__
#define __UT_CLIPBOARD_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getClipboard_UT(void);
int   noClipboard_UT(void);
void  releaseClipboard_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CLIPBOARD_REQ_H__ */
