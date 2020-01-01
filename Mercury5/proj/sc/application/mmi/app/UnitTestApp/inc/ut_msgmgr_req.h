/* ut_msgmgr_req.h */
#ifndef __UT_MSGMGR_REQ_H__
#define __UT_MSGMGR_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMsgmgr_UT(void);
int   noMsgmgr_UT(void);
void  releaseMsgmgr_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MSGMGR_REQ_H__ */
