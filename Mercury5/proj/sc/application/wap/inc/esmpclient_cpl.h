
#ifndef __ESMPCLIENT_CPL_H__
#define __ESMPCLIENT_CPL_H__

//#include "jspubtd.h"

#ifndef MAX_URL_LENGTH
#define MAX_URL_LENGTH 1024
#endif

#ifndef MAX_TIMEOUT_ITEMS
#define MAX_TIMEOUT_ITEMS 1024
#endif

typedef struct jsc_Timeout
{
	int32_t used;
	int32_t second;
	int32_t cycle;
	int32_t flag;
	void * func;
	uint32_t argc;
	int32_t * argv;
	void * obj;
}JSCTimeOut;

typedef enum 
{
	DLG_TYPE_NONE = 0,
	DLG_TYPE_ALERT,
	DLG_TYPE_CONFIRM
}DialogType;
typedef struct js_prompt_dialog
{
#define MAX_INFO_LEN 256
	DialogType DlgType;
    int32_t infoLen;
	int8_t msg[MAX_INFO_LEN];
}JsPromptDlg;

typedef struct
{
#define JsWndDlg_NONE 	0
#define JsWndDlg_OK 	1
#define JsWndDlg_CANCEL	2
	int32_t semID;	//semaphore id
	int32_t	active;	// active or not flag
	int32_t userValue; // user confirm info,  OK?, CANCLE? action;
}wndJsSemaphore;

extern wndJsSemaphore gDlgSemphore;	//defined in esmpclient_api.c

typedef int32_t(* brwJsAlertFunc)(const uint8_t* p);						// alert dialog
typedef int32_t(* brwJsConfirmFunc)(uint8_t* p1, uint8_t* p2, uint8_t* p3);	// confirm dialog

//extern JsPromptDlg	gPromptDlg;

extern int32_t CPL_esmpclient_submit(int32_t formid);

extern void CPL_esmpclient_reset(int32_t);

extern void CPL_esmpclient_loseFocus(int32_t);

extern void CPL_esmpclient_focus(int32_t sysid);

extern void CPL_esmpclient_select(int32_t);

extern void CPL_esmpclient_back(void);

extern void CPL_esmpclient_forward(void);

extern void CPL_esmpclient_go(int32_t);

extern int32_t CPL_esmpclient_confirm(uint8_t*, uint8_t*, uint8_t*);

extern void CPL_esmpclient_alert(const uint8_t*);

extern int32_t CPL_esmpclient_promptNum(uint8_t*, uint8_t*); 

extern int32_t CPL_esmpclient_prompt(uint8_t*, uint8_t*, int32_t);

extern int32_t CPL_esmpclient_setTimeout(int32_t second, int32_t cycle, int32_t flag,
								  void * func, uint32_t argc, int32_t * argv,
								  void * obj);

extern void CPL_esmpclient_clearTimeout(int32_t timerid);

extern void CPL_esmpclient_doTimeout(void);

extern void CPL_esmpclient_RegisterAlertFunc(brwJsAlertFunc fun);	//register alert dialog function

extern void CPL_esmpclient_RegisterConfirmFunc(brwJsConfirmFunc fun);//register confirm dialog function

#endif

