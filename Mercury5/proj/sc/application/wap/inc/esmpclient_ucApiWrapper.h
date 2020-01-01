
#ifndef __ESMPCLIENT_UCAPIWRAPPER_H__
#define __ESMPCLIENT_UCAPIWRAPPER_H__

#include <libs/jsengine/inc/jsapi.h>
#include <libs/jsengine/inc/jscntxt.h>
#include <libs/jsengine/inc/jsobj.h>
#include <libs/jsengine/inc/jspubtd.h>
#include <libs/jsengine/inc/jstypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define JS_DefineProperty JS_DefinePropertyWrapper
#define JS_DefinePropertyWithTinyId JS_DefinePropertyWithTinyIdWrapper
#define JS_GetProperty JS_GetPropertyWrapper
#define JS_SetProperty JS_SetPropertyWrapper
#define JS_CompileFunction JS_CompileFunctionWrapper
#define JS_EvaluateScript JS_EvaluateScriptWrapper
#define JS_NewStringCopyZ JS_NewStringCopyZWrapper
#define JS_DeleteProperty JS_DeletePropertyWrapper
#define JS_GetStringBytes JS_GetStringBytesWrapper
#define JS_GetStringLength JS_GetStringLengthWrapper

JS_PUBLIC_API(JSBool)
JS_DefinePropertyWrapper(JSContext *cx, JSObject *obj,
        const char *name, jsval value, JSPropertyOp getter,
        JSPropertyOp setter, uintN attrs);

JS_PUBLIC_API(JSBool)
JS_DefinePropertyWithTinyIdWrapper(JSContext *cx, JSObject *obj,
        const char *name, int8 tinyid, jsval value,
        JSPropertyOp getter, JSPropertyOp setter, uintN attrs);

JS_PUBLIC_API(JSBool)
JS_GetPropertyWrapper(JSContext *cx, JSObject *obj, const char *name, jsval *vp);

JS_PUBLIC_API(JSBool)
JS_SetPropertyWrapper(JSContext *cx, JSObject *obj, const char *name, jsval *vp);

JS_PUBLIC_API(JSFunction *)
JS_CompileFunctionWrapper(JSContext *cx, JSObject *obj,
        const char *name, uintN nargs, const char **argnames,
        const char *bytes, size_t length, const char *filename, uintN lineno);

JS_PUBLIC_API(JSBool)
JS_EvaluateScriptWrapper(JSContext *cx, JSObject *obj,
                  const char *bytes, uintN length,
                  const char *filename, uintN lineno,
                  jsval *rval);

JS_PUBLIC_API(JSString *)
JS_NewStringCopyZWrapper(JSContext *cx, const char *s);

JS_PUBLIC_API(JSBool)
JS_DeletePropertyWrapper(JSContext *cx, JSObject *obj, const char *name);

JS_PUBLIC_API(char *)
JS_GetStringBytesWrapper(JSString *str);

JS_PUBLIC_API(size_t)
JS_GetStringLengthWrapper(JSString *str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESMPCLIENT_UCAPIWRAPPER_H__ */
