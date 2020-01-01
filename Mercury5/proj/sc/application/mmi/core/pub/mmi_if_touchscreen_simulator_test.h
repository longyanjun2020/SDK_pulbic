#ifdef __PC_SIMULATOR__
#if  defined(__PC_SIMULATOR__) && defined(__MULTI_TOUCH__)
//#define __TEST_MULTI_TOUCH__
#endif //__PC_SIMULATOR__


#ifdef __TEST_MULTI_TOUCH__
#include "mmi_mae_common_def.h"
#include "mmi_mae_handler.h"
extern void *g_pITouchSrv;
extern u32 g_nTestIndex;
extern boolean g_bLock ;
void mmi_ts_set_touchsrv(void *pTouchSrv);
void *mmi_ts_get_touchsrv(void);
void mmi_ts_coordinate_testif(IBase* pRecipient, struct vm_msg *pData);
void mmi_ts_set_lock_touchscreen(boolean bLock);
void mmi_ts_timerTest1(void *pUserData);
void mmi_ts_timerTest2(void *pUserData);
void mmi_ts_timerTest3(void *pUserData);
void mmi_ts_timerTest4(void *pUserData);
void mmi_ts_timerTest5(void *pUserData);
void mmi_ts_timerTest6(void *pUserData);
void mmi_ts_timerTest7(void *pUserData);
void mmi_ts_timerTest8(void *pUserData);
void mmi_ts_timerTest9(void *pUserData);
void mmi_ts_timerTest10(void *pUserData);
void mmi_ts_timerTest11(void *pUserData);
void mmi_ts_timerTest12(void *pUserData);
void mmi_ts_timerTest13(void *pUserData);
void mmi_ts_timerTest14(void *pUserData);

void mmi_ts_TouchSrvTest1(void *pUserData);
void mmi_ts_TouchSrvTest2(void *pUserData);
void mmi_ts_TouchSrvTest3(void *pUserData);
void mmi_ts_TouchSrvTest4(void *pUserData);
void mmi_ts_TouchSrvTest5(void *pUserData);

#endif //defined(__PC_SIMULATOR__) && defined(__MULTI_TOUCH__)
#endif //__PC_SIMULATOR__