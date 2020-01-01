#ifndef __CUS_AUTOTEST_H__
#define __CUS_AUTOTEST_H__
#if defined(__FT_AUTO_TEST__)

#include "cus_os.hc"
#include "mdl_keypad_pub.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_msg.h"

// For send SMS result
#include "ven_os.h"
#include "ven_msg.h"
#include "ven_handle.h"

// Auto test messages
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "cus_autotest_message_define__.hi"
};

typedef unsigned short Boolean;

// In running target side script, task id is meaningless
// Here just add for compile
typedef unsigned short TaskId;
#define DUT     1
#define REMOTE  2
#define TCT     3

#define MST1_TASK_ID    1

#define atiDestTask     1
#define bammDestTask    2

#define setTmtLogLevelReq1      1
#define setTestBufLogLevelReq   2

// In running target side script, CheckFunctionPtr, checkTestBufRsp,
// BAPI, and END are all dummy
typedef int CheckFunctionPtr;
typedef int VargFunctionPtr;
typedef void BAPI;

typedef struct
{
    u32  	nStatus;
    ascii 	strTestCase[64+1];
} tst_testStatusInd;


typedef struct
{
    u8 senderNum[312];
    u8 subjectInfo[312+1];
    u8 attachement[256];
    u8 eSIMModule; // for outbox saving to store imsi
}tst_SendMMSReq_t;

typedef struct _tst_testCaseItem
{
    BAPI (*fp)(void);
    char description[32];
    int nTestCount;
    int nResult;
}tst_testCaseItem;

typedef struct _tst_testCaseGroup
{
    u32 uTestCaseNum;
    tst_testCaseItem* pTestCaseItem;
}tst_testCaseGroup;

typedef struct _tst_testKeyRsp
{
    u16 keyCode;
    u16 keyPress;
}tst_testKeyRsp;

//typedef union
//{
//    tst_testCaseGroup testCaseGroup;
//} vm_msgBody_t;

enum _tst_testResult
{
    TEST_RESULT_UNKNOWN = 0,
    TEST_RESULT_PASS    = 1,
    TEST_RESULT_FAIL    = 2,
    TEST_RESULT_NA      = 3
};

enum _tst_testMode
{
    TEST_UNKNOWN_MODE   = 0,
    TEST_MASTER_MODE    = 1,
    TEST_SLAVE_MODE     = 2
};

enum _tst_testStatus
{
    TEST_CASE_START         = 1,
    TEST_CASE_IN_PROGRESS   = 2,
    TEST_END                = 3
};

// WARNING: This is for checkExSync() API porting and will impact other codes
// Be sure to avoid any conflict if inculde this file
#if defined(END)
#undef END
#endif
#define END     1


#define checkTestBufRsp     1

#define KEY_LONG_PRESS_ATCMD_NUM        16
#define KEY_SHORT_PRESS_ATCMD_NUM       15
#define AT_COMMAND_MAX_LEN              256

#define LONG_PRESS      0
#define SHORT_PRESS     1

#define OP_OR	0
#define OP_AND	1

#define STD_BLOCK_TIMEOUT   180000

#define CHECK_TESTBUF_RETRY_INTERVAL    500

typedef enum BlockingTag
{
    BLOCK,
    GO
} Blocking;

typedef enum StepExitCodeTag
{
    STEP_SUCCESS,
    TERMINATE_TESTSUITE,
    TERMINATE_TESTSCRIPT,  /* This implies moving to the next TestScript */
    TERMINATE_MACROSTEP,   /* This implies moving to the next MacroStep */
    REPEAT_MACROSTEP,
    REPEAT_TESTSCRIPT,
    NEXT_MACROSTEP,
    IGNORE_SIG,
    INITIALISE,
    STEP_CONTINUE,
    TERMINATE_TESTSCRIPT_FAIL,  /* This implies moving to the next TestScript */
    TERMINATE_MACROSTEP_FAIL,   /* This implies moving to the next MacroStep */
    REPEAT_MACROSTEP_FAIL,
    REPEAT_TESTSCRIPT_FAIL,
    NEXT_MACROSTEP_FAIL,
    TERMINATE_TESTSCRIPT_UNDEF,  /* This implies moving to the next TestScript */
    TERMINATE_MACROSTEP_UNDEF,   /* This implies moving to the next MacroStep */
    REPEAT_MACROSTEP_UNDEF,
    REPEAT_TESTSCRIPT_UNDEF,
    NEXT_MACROSTEP_UNDEF,
    TERMINATE_TESTSCRIPT_PASS,  /* This implies moving to the next TestScript */
    TERMINATE_MACROSTEP_PASS,   /* This implies moving to the next MacroStep */
    REPEAT_MACROSTEP_PASS,
    REPEAT_TESTSCRIPT_PASS,
    NEXT_MACROSTEP_PASS
} StepExitCode;


// Sync with MS_VKeyCode enum in Dev_vkey.h
enum MS_ScriptVKeyCode
{
	VKEY_OK = KEY_OK,
	VKEY_MEN    ,
	VKEY_LEFT   ,
	VKEY_PHB    ,
	VKEY_RIGHT  ,
	VKEY_ONOFF  ,
	VKEY_CLR    ,
	VKEY_PLUS   ,
	VKEY_SEND   ,
	VKEY_SEND2  ,
	VKEY_END    ,
	VKEY_MINUS  ,
	VKEY_1      ,
	VKEY_2      ,
	VKEY_3      ,
	VKEY_4      ,
	VKEY_5      ,
	VKEY_6      ,
	VKEY_7      ,
	VKEY_8      ,
	VKEY_9      ,
	VKEY_STAR   ,
	VKEY_0      ,
	VKEY_HASH   ,
	VKEY_MSG    ,
	VKEY_MAIL   ,
	VKEY_FSTDL1 ,
	VKEY_FSTDL2 ,
	VKEY_FSTDL3 ,
	VKEY_FSTDL4 ,
	VKEY_REDIAL ,
	VKEY_HOOKOFF_DUMMY,
	VKEY_HOOK ,
	VKEY_UP     ,
	VKEY_DOWN   ,
	VKEY_FLAPON ,
	VKEY_FLAPOFF,
	VKEY_SIDE_UP,
	VKEY_SIDE_DN,
	VKEY_SKLEFT ,
	VKEY_SKRIGHT,
	VKEY_HEADSET,
	VKEY_CLEAR  ,
	VKEY_ACTION  ,
	VKEY_CAMERA ,
	VKEY_MP3,
	VKEY_POWERMODE,
	VKEY_FASTFORWARD,
	VKEY_REWIND,
	VKEY_WTEST_DUMMY_KEY = 0xFD,
	VKEY_SAME = 0xFE,
	VKEY_DUMMY   = 0xFF
};

void cus_targetSendKeyMsg(u8);
void cus_targetSendLongPressKeyMsg(u8, int);
Boolean macroStep(tst_testCaseItem*);
Boolean internalSendKeySync(TaskId, int, int, int, Boolean);
void autoTest_startTest(int, int);
Boolean autoTest_AddResultRecord(char*);
Boolean autoTest_ResetResultRecord(void);
void record_autotest_result(char*, u32);

Boolean autoTest_AddSmsResultRecord(char*);
Boolean autoTest_ResetSmsResultRecord(void);
Boolean autoTest_SendSmsResult(char*, u32);
Boolean autoTest_SendTriggerSms(char*, u32);
Boolean autoTest_SendMmsResult(void);
void autoTest_SendStatusInd(char*, int);

int autoTest_setAntfLogFileName(char*);
int autoTest_getAntfLogFileName(char*);

int autoTest_SetTestMode(int);
int autoTest_GetTestMode(void);

void autoTest_LockKeypad(void);
void autoTest_UnlockKeypad(void);
void autoTest_LockTouchpad(void);
void autoTest_UnlockTouchpad(void);

int autoTest_SetCancelStatus(void);
int autoTest_GetCancelStatus(void);

// Test case definitions
BAPI Sanity_Test_XMMI_3_1_test(void);
BAPI FT_Test_XMMI_Initialize_test(void);
BAPI FT_Test_XMMI_auto_keypad_lock_off_test(void);
BAPI FT_Test_XMMI_MO_Call_test(void);
BAPI FT_Test_XMMI_Phone2_MO_Call_test(void);
BAPI FT_Test_XMMI_MO_SMS_test(void);
BAPI FT_Test_XMMI_MO_MMS_test(void);
BAPI FT_Test_XMMI_MT_MMS_test(void);
BAPI FT_Test_XMMI_WAP_test(void);
BAPI FT_Test_XMMI_MT_Call_test(void);
BAPI FT_Test_XMMI_Phone2_MT_Call_test(void);
BAPI FT_Test_XMMI_SS_test(void);
BAPI FT_Test_XMMI_FM_test(void);
//BAPI FT_Test_XMMI_CB_test(void);

int getSmsResultNumber(char*);
int getMoNumber(char*);

// Dummy command
#define beginMarkerNew  beginMarkerSync
#define failMarkerNew   failMarkerSync
#define passMarkerNew   passMarkerSync
#define sendNew         sendSync
#define delayNew        delaySync
#define checkExNew      checkExSync
#define sendKeyNew      sendKeySync

#endif // __FT_AUTO_TEST__

#endif

