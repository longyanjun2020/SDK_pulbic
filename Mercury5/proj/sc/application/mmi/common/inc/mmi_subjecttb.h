/**
 * @file mmi_subjecttb.h
 *
 * @brief  subject table 
 *         
 * @author 
 *         
 */
#ifndef __MMI_SUBJECTTB_H_
#define __MMI_SUBJECTTB_H_

#include "mmi_mae_common_def.h"
#include "mmi_SubjectItf.h"

typedef struct {
	char *pName;
	SubjectStatus_e eStartAPStatus;
	SubjectStatus_e eStopAPStatus; 
    MAE_ClsId	clsID;
}SubjectRel_t;

extern const SubjectRel_t g_SbjRelTbl[];

const SubjectRel_t* GetSubjectRel(char *pSbjName, MAE_ClsId clsID);

#endif

