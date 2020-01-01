/**
* @file    mmi_atvapp_esgtagstack.h
* @version
* @brief   general television applet header file.
*
*/
#ifndef __MMI_ATVAPP_ESGTAGSTACK_H__
#define __MMI_ATVAPP_ESGTAGSTACK_H__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define ESGSTACK_PEEK_TOP	1

/*=============================================================*/
// Data type definition
/*=============================================================*/
struct ESGTagStack_tag;
typedef struct ESGTagStack_tag ESGTagStack_t;

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
ESGTagStack_t *ESGTagStack_New(void);
void ESGTagStack_Release(ESGTagStack_t *s);
boolean ESGTagStack_Push(ESGTagStack_t *s, int data);
boolean ESGTagStack_Pop(ESGTagStack_t *s, int *outVal);
boolean ESGTagStack_Peek(ESGTagStack_t *s, int peekPos, int *outVal);
boolean ESGTagStack_IsEmpty(ESGTagStack_t *s);

#endif	//__MMI_ATVAPP_ESGTAGSTACK_H__

