/* ut_msgmgr_if.h */
#ifndef __UT_MSGMGR_IF_H__
#define __UT_MSGMGR_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMsgmgr_If_UT(void);
int   noMsgmgr_If_UT(void);
void  releaseMsgmgr_If_UT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MSGMGR_IF_H__ */
