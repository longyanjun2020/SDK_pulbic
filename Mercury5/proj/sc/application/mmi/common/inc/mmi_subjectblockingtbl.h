/**
 * @file mmi_subjectblockingtbl.h
 *
 * @brief  subject table
 *
 * @author
 *
 */
#ifndef __MMI_SUBJECBLOCKINGTBL_H_
#define __MMI_SUBJECBLOCKINGTBL_H_

#include "mmi_mae_common_def.h"
#include "mmi_SubjectItf.h"

#define MAX_BLOCKING_COND (10)

typedef enum
{
    REQ_BLOCKING_ALL = 1, // All app/req will be blocked

/** Self defined request**/
    REQ_BLOCKING_QQ,
    REQ_BLOCKING_BT_OPP,
    REQ_BLOCKING_CBS,
    REQ_BLOCKING_MULTIMEDIA,
    REQ_BLOCKING_CDWAP,
    REQ_BLOCKING_TUDOU,
    REQ_BLOCKING_END = 0xFFFF
} BLOCKING_Req_e;

typedef struct{
    u32 reqBlockingId;
    u32 blockingCondition[MAX_BLOCKING_COND];
    u32 blockingDescr;
}BlockingCon_t;

#define BEGIN_BLOCKING_TABLE(g_BlockCondTbl) \
    const BlockingCon_t g_BlockCondTbl[] = {

#define END_BLOCKING_TABLE \
    {REQ_BLOCKING_END, {0}, COMMON_TXT_NULL_ID}}

#endif //__MMI_SUBJECBLOCKINGTBL_H_

