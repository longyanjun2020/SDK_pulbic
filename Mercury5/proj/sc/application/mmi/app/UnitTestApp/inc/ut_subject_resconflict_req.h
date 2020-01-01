/* ut_accessory_req.h */
#ifndef __UT_SUBJECT_RES_CONFLICT_REQ_H__
#define __UT_SUBJECT_RES_CONFLICT_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getResConflictSubject_UT(void);
int   noResConflictSubject_UT(void);
void  releaseResConflictSubject_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SUBJECT_RES_CONFLICT_REQ_H__ */
