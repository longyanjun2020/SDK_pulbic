#ifndef __MMI_MAE_UNITTEST_DATA__
#define __MMI_MAE_UNITTEST_DATA__


#ifdef __cplusplus
extern "C" {
#endif

#include "wchar.h"

extern void MKernel_SendCompareInfoToUI(void *info, int Len);
extern void MKernel_SendQueryHookFuncData(void *info, int Len);
#define UNIT_TEST_MAX_NAMELEN (260)
#define INIT_TIMEOUT    (3000)

typedef enum _UNIT_TEST_DATA_TYPE
{
    DATA_TYPE_NONE = 0,
	TEXT_TYPE,
	TEMPLATE_TYPE,
	POPUPID_TYPE,
	FILENAME_TYPE,
	FUNCTION_TYPE,
	FUNCADDR_TYPE,
    MAX_DATA_TYPE

} UNIT_TEST_DATA_TYPE;

typedef enum _HOOKFUNC_DATA_TYPE
{
    HOOKFUNC_DATA_INT = 0,
	HOOKFUNC_DATA_STR,
    MAX_HOOKFUNC_DATA_TYPE

} HOOKFUNC_DATA_TYPE;

typedef enum _HOOKFUNC_DATA_QUERY_RST
{
    HOOKFUNC_DATA_QUERY_FAIL = 0,
	HOOKFUNC_DATA_QUERY_SUCCESS,

} HOOKFUNC_DATA_QUERY_RST;


typedef struct _UNIT_TEST_DATA {
	UNIT_TEST_DATA_TYPE nTestDataType;
	char template_id[UNIT_TEST_MAX_NAMELEN];
	char popout_id[UNIT_TEST_MAX_NAMELEN];
	wchar_t text[UNIT_TEST_MAX_NAMELEN];
	char filename[UNIT_TEST_MAX_NAMELEN];
	char function_name[UNIT_TEST_MAX_NAMELEN];
	void* fp;
    int nWaitTime;
	int nCheckResult;
} UNIT_TEST_DATA;

typedef struct _HOOKFUNC_DATA {    
	void *fp;
	char *QueryDataName;
	HOOKFUNC_DATA_TYPE nFuncDataType;
	unsigned char *StrData;
    unsigned int StrBufSize;
    unsigned int *StrLen;
	int *IntData;
	HOOKFUNC_DATA_QUERY_RST *result;
	
} HOOKFUNC_DATA;

void HotPatch(void *oldProc, void *newProc);
void HotUnpatch(void*oldProc);
void HotUnpatch_all(void);
void Query_HookFunc_Data(HOOKFUNC_DATA *data);

#define SEND_UT_FUNCTION_NAME(func_name)  do{UNIT_TEST_DATA data; \
	data.nTestDataType = FUNCTION_TYPE; \
	memset(data.function_name, 0x0, sizeof(char) * UNIT_TEST_MAX_NAMELEN); \
	strcpy(data.function_name, (const char*)func_name);  \
	MKernel_SendCompareInfoToUI((void *)&data, sizeof(UNIT_TEST_DATA)); \
} while(0)


#define SEND_UT_FUNCTION_ADDR(func_fp, func_name)  do{UNIT_TEST_DATA data; \
	data.nTestDataType = FUNCADDR_TYPE; \
	data.fp = func_fp; \
	memset(data.function_name, 0x0, sizeof(char) * UNIT_TEST_MAX_NAMELEN); \
	strcpy(data.function_name, (const char*)func_name);  \
	MKernel_SendCompareInfoToUI((void *)&data, sizeof(UNIT_TEST_DATA)); \
} while(0)


#define SEND_UT_TEXT(text_data, length)  do{UNIT_TEST_DATA data; \
	data.nTestDataType = TEXT_TYPE; \
	memset(data.text, 0x0, sizeof(wchar_t) * UNIT_TEST_MAX_NAMELEN); \
	memcpy(data.text, (const short*)text_data, length*sizeof(wchar_t));  \
	data.text[length] = 0x00; \
	MKernel_SendCompareInfoToUI((void *)&data, sizeof(UNIT_TEST_DATA)); \
} while(0)

#define SEND_UT_TEMPLATE_NAME(func_name)  do{UNIT_TEST_DATA data; \
	data.nTestDataType = TEMPLATE_TYPE; \
	memset(data.template_id, 0x0, sizeof(char) * UNIT_TEST_MAX_NAMELEN); \
	strcpy(data.template_id, (const char*)func_name);  \
	MKernel_SendCompareInfoToUI((void *)&data, sizeof(UNIT_TEST_DATA)); \
} while(0)

#define SEND_UT_POPUP_NAME(func_name)  do{UNIT_TEST_DATA data; \
	data.nTestDataType = POPUPID_TYPE; \
	memset(data.popout_id, 0x0, sizeof(char) * UNIT_TEST_MAX_NAMELEN); \
	strcpy(data.popout_id, (const char*)func_name);  \
	MKernel_SendCompareInfoToUI((void *)&data, sizeof(UNIT_TEST_DATA)); \
} while(0)

#define UT_HOOK_FUNCTION(original_func_fp, hook_func_fp) HotPatch(original_func_fp,hook_func_fp)

#define UT_UNHOOK_FUNCTION(original_func_fp) HotUnpatch(original_func_fp)

#define UT_UNHOOK_ALLFUNCTION() HotUnpatch_all()

#define QUERY_UT_HOOKFUNC_INT_DATA(original_func_fp, data_name, s32_p, ret_p) do{HOOKFUNC_DATA data = {0}; \
    data.fp = original_func_fp; \
    data.nFuncDataType = HOOKFUNC_DATA_INT; \
    data.QueryDataName = data_name; \
    data.IntData = s32_p; \
    data.result = ret_p; \
    Query_HookFunc_Data(&data); \
} while(0)

#define QUERY_UT_HOOKFUNC_STR_DATA(original_func_fp, data_name, u8str_buf, buf_size, str_len, ret_p) do{HOOKFUNC_DATA data = {0}; \
    data.fp = original_func_fp; \
    data.nFuncDataType = HOOKFUNC_DATA_STR; \
    data.QueryDataName = data_name; \
    data.StrData = u8str_buf; \
    data.StrBufSize = buf_size; \
    data.StrLen = str_len; \
    data.result = ret_p; \
    Query_HookFunc_Data(&data); \
} while(0)

#ifdef __cplusplus
}
#endif

#endif
