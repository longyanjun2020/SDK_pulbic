
#ifndef __ESMPCLIENT_EVENT_H__
#define __ESMPCLIENT_EVENT_H__

//#include <jbed_global.h>
#include <libs/jsengine/inc/jsapi.h>
#include <uapps/wap/esmpclient/nccpclient_clientapi.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct __event_spec__
{
    const uint8_t      *type;
    int32_t    keyCode;
    const uint8_t    *timeStamp;
    const void    *target;
}T_CJS_EventSpec;

enum  EVENT_PROP_ID {
        EVENT_TYPE = 0,
        EVENT_KEYCODE,
        EVENT_TIMESTAMP,
        EVENT_TARGET,
};

/**
 * Get event specification.
 * return gEventSpec
 */
T_CJS_EventSpec* cJS_GetEventSpec(void);

/**
 * Reset event specification.
 * return void
 */
void cJS_ResetEventSpec(void);

/**
 * Get the pointer of event object
 * return &gEventSpec
 */
JSObject* cJS_GetGEventObject(void);

/**
 * Get the pointer of event object
 * return &gEventSpec
 */
void* cJS_GetGEventObjectPtr(void);

/**
 * Create a event object and make it as a property of global object(window)
 * \param void
 * \return
 *     JS_TRUE: create successful
 *     JS_FALSE: failed
 */
JSBool cJS_InitEventObject(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESMPCLIENT_EVENT_H__ */
