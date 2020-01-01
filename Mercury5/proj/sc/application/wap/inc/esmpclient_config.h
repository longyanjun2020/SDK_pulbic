
#ifndef __ESMPCLIENT_CONFIG_H__
#define __ESMPCLIENT_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Not support the links property of document object */
//#define CJS_NOT_SUPPORT_LINKS_OBJECT

/* Not support the anchors property of document object */
//#define CJS_NOT_SUPPORT_ANCHORS_OBJECT

/* Not support the images property of document object */
//#define CJS_NOT_SUPPORT_IMAGES_OBJECT

/* Create prototype object of Window */
#define CJS_WINDOW_PROTO

/* If data is stored outside, define it into JSPROP_SHARED to reduce the wastage of memory */
#define JSPROP_NORMAL JSPROP_ENUMERATE | JSPROP_SHARED

/* Define the event handling function into object function immediately after define object */
/* #define PRE_COMPILE_EVENT_HANDLER */

/* Compile the executive codes into function or compile the event handling function into object function directly */
#define CJS_EXEC_SCRIPT_BY_FUNCTION

#ifndef CJS_EXEC_SCRIPT_BY_FUNCTION
/**
 * Execute script code by JS_Evaluate function, but in event handling,
 * the opposite function is permanent, can not be deleted .
 */
#define CJS_EXEC_SCRIPT_BY_EVALUATE
#endif /* CJS_EXEC_SCRIPT_BY_FUNCTION */

/* All window object share the standard, client and predinfed objects */
#define CJS_SHARE_NATIVE_OBJECT

/* Start new get field object method */
#define CJS_NEW_GET_FIELDOBJECT_MOTHOD

/* Implement the empty method like document.close */
#define CJS_MACRO_VOID_METHOD

/* Domain available */
#define JS_DOMAIN_AVAILABLE

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESMPCLIENT_CONFIG_H__ */
