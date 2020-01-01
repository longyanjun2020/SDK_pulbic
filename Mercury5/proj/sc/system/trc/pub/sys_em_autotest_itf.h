#ifndef __SYS_EM_AUTOTEST_ITF_H__
#define __SYS_EM_AUTOTEST_ITF_H__

#if defined(__FT_AUTO_TEST__)

extern int setSim1Number(char*);
extern int getSim1Number(char*);
extern int setSim2Number(char*);
extern int getSim2Number(char*);
extern int setMoNumber(char*);
extern int getMoNumber(char*);
extern int getSmsResultNumber(char*);
extern int setSmsResultNumber(char*);

extern int autoTest_SetTestMode(int);
extern void autoTest_startTest(int, int);


#endif // __FT_AUTO_TEST__

#endif
