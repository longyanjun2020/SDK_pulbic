/* ut_def.h */
#ifndef __UT_DEF_H__
#define __UT_DEF_H__

#include "stdio.h"
#include "ut_generate.h"
#include "mmi_mae_common_def.h"
#include "mmi_log.h"

#ifdef __SDK_SIMULATION__
#undef __ENABLE_DLM_SRVUT__
#define WRITE_LOG(flog, __comment__, ...)  fprintf((FILE *)flog, __comment__"\n", ##__VA_ARGS__); fflush((FILE *)flog)
#else
#define WRITE_LOG(flog, __comment__, ...)  LOG_TRACE((unsigned int)flog,__comment__,##__VA_ARGS__)
#endif

#define PCHECK_U( uInput, uTarget, __comment__, idx, flog)  \
	if(uInput!= uTarget) {WRITE_LOG(flog,"\ttest %d : "__comment__" Input: %d, Target: %d",idx,uInput,uTarget);}

#define PCHECK_S(idx, flog, uInput, uTarget, __comment__) \
	if(strcmp(uInput,uTarget)!=0) {WRITE_LOG(flog,"\ttest %d : "__comment__ " Input: %s, Target: %s",idx,uInput,uTarget);}

#define UT_PATH L"fs:/CARD/UnitTest/"
#define UT_MP3_URL UT_PATH L"Mp3.mp3"
#define UT_IMAGE_URL UT_PATH L"GIF.gif"  /* image location*/
#define UT_EMUGAME_URL UT_PATH L"EmuGame.nes"  /* emugame location*/

typedef enum
{
    UT_TEST_SYNC=0,    /* synchronously checking  */
    UT_TEST_ASYNC      /* asynchronously checking */
} UTTestMode;

typedef enum
{
    UT_IDX0_NOT_CHECK=0,    /* Not to do checking for the index 0 test case */
    UT_IDX0_CHECK           /* Do checking for the index 0 test case        */
} UTIdx0Mode;

/* structure for UT */
typedef bool (*ut_fp)(FILE *fn,int idx);

typedef struct ut
{
    char         testname[64];
    ut_fp        sendreq;
    ut_fp        check;
    int          testnum;
    unsigned int nPeriod;    /* this period works only for synchronous checking */
                             /* If it's UT_TEST_IMMEDIATE, the checking function will be  */
                             /* executed immediately. Other than 0, the checking function */
                             /* will be executed after nPeriod mini-seconds.              */
    UTTestMode   eMode;
    UTIdx0Mode   eIdx0Mode;
} UT_t,*pUT_t;

#endif
