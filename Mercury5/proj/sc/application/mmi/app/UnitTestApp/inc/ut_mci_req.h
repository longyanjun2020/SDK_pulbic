/* ut_mci_req.h */
#ifndef __UT_MCI_REQ_H__
#define __UT_MCI_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMCI_UT(void);
int   noMCI_UT(void);
void  releaseMCI_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MCI_REQ_H__ */
