
#ifndef __ESMPCLIENT_WINDOW_H__
#define __ESMPCLIENT_WINDOW_H__

#include <libs/jsengine/inc/jsapi.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Define propreties of Window object.
 */
enum   WIN_PROPS {
        WIN_DEF_STATUS = 0,
        WIN_STATUS,
        WIN_LOCATION,

        /* We do not support the next properties */
        WIN_DOMAIN,
        WIN_OPENER,
        WIN_SCREEN,
};

/**
 * Define Window object.
 */
extern const JSClass Window_class;

/**
 * Define the array of Window object properties.
 */
extern JSPropertySpec WindowProperties[];

/**
 * Define the array of Window object functions.
 */
extern JSFunctionSpec WindowMethods[];

/**
 * Get window's properties.
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \param id  [in]the property's identification
 * \param vp  [out]value of the property
 * \return
 *      -JS_TRUE when get successfully
 *      -JS_FALSE when failed in getting
 */
JSBool GetWindowProperty (JSContext *cx, JSObject *obj, jsval id, jsval *vp);

/**
 * Set window's properties.
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \param id  [in]the property's identification
 * \param vp  [in]value of the property we want to set
 * \return
 *      -JS_TRUE when set successfully
 *      -JS_FALSE when failed in setting
 */
JSBool SetWindowProperty (JSContext *cx, JSObject *obj, jsval id, jsval *vp);

/**
 * Create a window object.
 * \param void
 * \return
 *      -JS_TRUE when success
 *      -JS_FALSE when failed
 */
JSBool cJS_NewWindowObject(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESMPCLIENT_WINDOW_H__ */
