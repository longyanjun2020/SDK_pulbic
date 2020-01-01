/* ut_share_data.h */
#ifndef __UT_SHARE_DATA_H__
#define __UT_SHARE_DATA_H__

typedef struct _UT_GlobalData_t
{
    void *MAE_Shell;
} UT_GlobalData_t,*pUT_GlobalData_t;

void UT_SetGlobalData(UT_GlobalData_t *pGlobalData);

#endif    /* __UT_SHARE_DATA_H__ */
