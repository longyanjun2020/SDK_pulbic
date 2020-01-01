
#ifndef __ESMPCLIENT_INNERAPI_H__
#define __ESMPCLIENT_INNERAPI_H__
////#include <jbed_global.h>
#include <uapps/wap/esmpclient/esmpclient_config.h>
#include <libs/jsengine/inc/jsfun.h>
#include <libs/jsengine/inc/jscntxt.h>
#include <libs/jsengine/inc/jsapi.h>
#include <libs/jsengine/inc/jsutil.h>
#include <libs/jsengine/inc/jsscope.h>
#include <uapps/wap/esmpclient/esmpclient_nodelist.h>
#include <uapps/wap/wap_struct.h>
#include <uapps/wap/wap_service.h>
#include <whttp/nccwhttp.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* mainly for document.imges.length, document.links.length */
#define ID_IS_LENGTHATOM(id)  \
        (ID_TO_VALUE((jsid)(cx->runtime->atomState.lengthAtom)) == (id))

/* Support document.write in event handling */
#define SUPPORT_WRITE_IN_EVENT

/* Set the first parameter into script code when setting timer */
#define CJS_STRING_FLAG     0

/* Set the first parameter into js function when setting timer */
#define CJS_FUNCTION_FLAG   1

/* The first parameter is invalid */
#define CJS_INVALID_FLAG    -1

/* Get pointer to object by its ID */
#define GET_PRIVATE_BY_ID

#ifdef GET_PRIVATE_BY_ID

#define CJS_SET_OBJECT_PRIVATE(cx, obj, idorptr) \
        cJS_SetPrivateByID(cx, obj, idorptr)

#define CJS_GET_OBJECT_PRIVATE(cx, obj, objType) \
        cJS_GetPrivateByID(cx, obj, objType)

#else /* GET_PRIVATE_BY_ID */

#define CJS_SET_OBJECT_PRIVATE(cx, obj, idorptr) \
        JS_SetPrivate(cx, obj, idorptr)
#define CJS_GET_OBJECT_PRIVATE(cx, obj, objType) \
        JS_GetPrivate(cx, obj)

#endif/* GET_PRIVATE_BY_ID */

#ifdef GET_PRIVATE_BY_ID
/**
 * Get pointer of object by system ID.
 * First get system ID via object class and object type, then get pointer of object by system ID.
 * \param cx      [in]Pointer of JSContext
 * \param obj     [in]Pointer of object class
 * \param objType [in]Type of object
 * \return
 *      -Pointer of JSObject when get successfully
 *      -NULL when failed
 */
void * cJS_GetPrivateByID(JSContext* cx, JSObject* obj, int16_t objType);

/**
 * Get pointer of object by system ID directly.
 * \param objType  [in]Type of object
 * \param systemID [in]object's system ID
 * \return
 *      -Pointer of JSObject when get successfully
 *      -NULL when failed in getting
 */
void * cJS_GetPtrByID(int16_t objType, int32_t systemID);

/**
 * Set object's system ID.
 * \param cx       [in]Pointer of JSContext
 * \param obj      [in]Pointer of object class
 * \param idorptr: [in]Object's ID or pointer of object
 * \return
 *      -JS_TRUE when success
 *      _JS_FALSE when failed
 */
JSBool cJS_SetPrivateByID(JSContext* cx, JSObject* obj, int32_t idorptr);
#endif /* GET_PRIVATE_BY_ID */

/**
 * Initialize standard classes and some client classes.
 * \param cx        [in]the JSContext pointer
 * \param WindowObj [in]the global object(window)
 * \return
 *      -JS_TRUE when success
 *      -JS_FALSE when failed
 */
JSBool cJS_InitClientAndStandardClasses(JSContext *cx, JSObject *WindowObj);

/**
 * Create a crypto object and make it as a property of global object(window)
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \return JSObject
 *     JSObject: succeed to create crypto class
 *     NULL:  failed
 */
JSObject * cJS_InitOptionClass(JSContext *cx, JSObject *obj);

/* Implement refister method of crypto class */
#define JS_HAVE_CRYPTO_INIT_CLASS
#ifdef JS_HAVE_CRYPTO_INIT_CLASS
/**
 * Create a crypto object and make it as a property of global object(window)
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \return JSObject
 *     JSObject: succeed to create crypto class
 *     NULL:  failed
 */
JSObject * cJS_InitCryptoClass(JSContext *cx, JSObject *obj);
#endif/* JS_HAVE_CRYPTO_INIT_CLASS */

/* Implement refister method of document class */
#define JS_HAVE_DOCUMENT_INIT_CLASS
#ifdef  JS_HAVE_DOCUMENT_INIT_CLASS
/**
 * Create a document object and make it as a property of global object(window)
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \return JSObject
 *     JSObject: succeed to create document class
 *     NULL:  failed
 */
JSObject * cJS_InitDocumentClass(JSContext *cx, JSObject *obj);
#endif /* JS_HAVE_DOCUMENT_INIT_CLASS */

/* Implement refister method of form class */
#define JS_HAVE_FORM_INIT_CLASS
#ifdef JS_HAVE_FORM_INIT_CLASS
/**
 * Create a form object and make it as a property of document object
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \return JSObject
 *     JSObject when create form object successfully
 *     NULL when failed in creating
 */
JSObject * cJS_InitFormClass(JSContext *cx, JSObject *obj);
#endif /* JS_HAVE_FORM_INIT_CLASS */

/* Implement refister method of field class */
#define JS_HAVE_FIELD_INIT_CLASS
#ifdef JS_HAVE_FIELD_INIT_CLASS
/**
 * Create a field object and make it as a property of a from
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \return
 *     -JSObject: successful
 *     -NULL:  failed
 */
JSObject * cJS_InitFormFieldClass(JSContext *cx, JSObject *obj);
#endif /* JS_HAVE_FIELD_INIT_CLASS */

#ifndef CJS_NOT_SUPPORT_IMAGES_OBJECT
/**
 * Init image class for window prototype object.
 * \param cx  the JS context
 * \param obj the corresponding object for execute
 * \return
 *     JSObject: prototype object for image when succeed.
 *     NULL:  failed
 */
JSObject * cJS_InitImageClass(JSContext *cx, JSObject *obj);

/**
 * Create images collection Object.
 * \param cx the JSContext pointer
 * \param parent its parent object.
 * \return
 *      -new created images collection Object when success
 *      -NULL when failed
 */
JSObject * cJS_newImagesCollection(JSContext *cx, JSObject *parent);
#endif

/* Dynamic create link object */
#ifndef CJS_NOT_SUPPORT_LINKS_OBJECT
/**
 * Init link class for window prototype object.
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \return
 *     JSObject: succeed to create link class
 *     NULL:  failed
 */
JSObject * cJS_InitLinkClass(JSContext *cx, JSObject *obj);

/**
 * Init area class for window prototype object.
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \return
 *     JSObject: succeed to create area class
 *     NULL:  failed
 */
JSObject *cJS_InitAreaClass(JSContext *cx, JSObject *obj);

/**
 * Create a new area object.
 * \param cx JS Engine's context.
 * \param parent the parent object.
 * \param privData the private data for this area object.
 * \return the new created object.
 *      -the new AreaObject when create successfully
 *      -NULL when failed
 */
JSObject *cJS_newAreaObject(JSContext *cx,
                            JSObject *parent,
                            void *privData);

/**
 * Create a new link object.
 * \param cx JS Engine's context.
 * \param parent the parent object.
 * \param privData the private data for this link object.
 * \return the new created linkobject.
 *      -the new link object when create successfully
 *      -NULL when failed
 */
JSObject *cJS_newLinkObject( JSContext *cx,
                             JSObject *parent,
                             void *privData );

/**
 * Finalize callback of link or area object.
 * \param cx  [in]JS context
 * \param obj [in]the corresponding object.
 */
void cJS_linksElem_Finalize(JSContext *cx, JSObject *obj);

/**
 * Create links collection Object.
 * \param cx the JSContext pointer
 * \param parent its parent object.
 * \return
 *      -new created links collection Object when success
 *      -NULL when failed
 */
JSObject * cJS_newLinksCollection(JSContext *cx, JSObject *parent);
#endif /* CJS_NOT_SUPPORT_LINKS_OBJECT */

#ifndef CJS_NOT_SUPPORT_ANCHORS_OBJECT
/**
 * Create anchors collection Object.
 * \param cx the JSContext pointer
 * \param parent its parent object.
 * \return
 *      -new created anchors collection Object when success
 *      -NULL when failed
 */
JSObject * cJS_newAnchorsCollection(JSContext *cx, JSObject *parent);
#endif /* CJS_NOT_SUPPORT_ANCHORS_OBJECT */

/**
 * Create history object.
 * \param cx        [in]the JS context
 * \param globalObj [in]global object(window)
 * \return
 *      -JS_FALSE when field in creating
 *      -JS_TURE when create successfully
 */
JSBool cJS_NewHistoryObject(JSContext *cx, JSObject *globalObj);

/**
 * Create a navigator object.
 * \param cx        [in]JS context.
 * \param globalObj [in]the window object(global)
 * \return
 *      -JS_TRUE when create successfully
 *      -JS_FALSE when failed
 */
JSBool cJS_NewNavigatorObject(JSContext *cx, JSObject *globalObj);

/**
 * Create a location object.
 * \param cx        [in]JS context.
 * \param globalObj [in]the window object(global)
 * \return
 *      -JS_TRUE when create successfully
 *      -JS_FALSE when failed
 */
JSBool cJS_NewLocationObject(JSContext *cx, JSObject *globalObj);

/* Use in url handling */
/* Define array of location properties */
enum URL_PROPS {
        URL_HREF = 0,
        URL_PROTOCOL = URL_STORE_SCHEME,
        URL_HOSTNAME = URL_STORE_HOSTNAME,
        URL_HOST = URL_STORE_HOSTINFO,
        URL_PORT = URL_STORE_PORT,
        URL_PATHNAME = URL_STORE_PATH,
        URL_HASH = URL_STORE_FRAGMENT,
        URL_SEARCH = URL_STORE_QUERY,
};

/**
 * Set a new value for one property and modify the browser' node .
 * note: the item may be malloced or not
 * \param cx             [in]the JSContext pointer
 * \param origValuep     [in/out]the pointer of node' item which will be update.
 * \param newValue       [in]the item's new value which type is jsval
 * \param IsMallocedItem [in]the flag of whether the item is malloced
 * \return
 *      -JS_TRUE when success
 *      -JS_FALSE when failed
 */
JSBool cJS_UpdateNodeItem(JSContext *cx, void **origValuep, jsval newValue, JSBool IsmallocedItem);

/**
 * Set a new value for one property and modify the browser's node by uint8_t* new value.
 * \param cx             [in]the JSContext pointer
 * \param origValuep     [in/out]the pointer of node' item which will be update.
 * \param newValue       [in]the item's new value which type is uint8_t*
 * \param len            [in]the length of the new value
 * \param IsMallocedItem [in]the flag of whether the item is malloced
 * \return
 *      -JS_TRUE when success
 *      -JS_FALSE when failed
 */
JSBool cJS_UpdateNodeItemByBytes( JSContext *cx,
                                  void **origValuep,
                                  const uint8_t *newValue,
                                  uint32_t len,
                                  JSBool IsmallocedItem );

/**
 * Get form index via the field's system id.
 * \param fieldSystemID [in]field's system id
 * \return
 *      -INVALID_FORM_ID(-1) when failed
 *      -form index when get successfully
 */
T_DB_FormNodeIdx cJS_GetFormIndexByFieldSystemID(jsint fieldSystemID);

/**
 * Get the system ID of field object from field js object
 *  \param cx        [in]the js context pointer
 *  \param obj       [in]the pointer to js field Object
 *  \param pSystemID [out]the system id of the field
 *  \return
 *       -JS_TRUE: success
 *       -JS_FALSE: failed
 */
JSBool cJS_GetSystemIDByObject(JSContext *cx, JSObject *obj, int16_t *pSystemID);

/**
 * Combine URL.
 * \param cx          [in]the JS context
 * \param locationObj [in]current location object
 * \param newPartVal  [in]new value which will be combined with old URL
 * \param partType    [in]type of part which we want to get to combine
 * \return
 *      -NULL when failed in combinning
 *      -newHref(uint8_t) when combine successfully
 */
uint8_t * cJS_CombineUrl(JSContext *cx, JSObject *locationObj, jsval newPartVal, jsint partType);

/**
 * Get base path by relative path.
 * \param href [in]page's relative path
 * \return
 *      -basepath when success
 *      -NULL when failed
 */
uint8_t * cJS_URLResolve(const uint8_t *href);

/**
 * Get a specified type's part value from a url
 * \param url      [in]URL
 * \param partType [in]type of which we want to get
 * \return
 *      -NULL when failed in getting
 *      -part(uint8_t) when get successfully
 */
uint8_t * cJS_GetUrlPartsValue(const uint8_t *url, jsuint partType);

/**
 * Get a part of url and evaluate it to *vp.
 * \param vp       [out]store the part of url
 * \param url      [in]URL
 * \param partType [in]type of the part which we want to get
 * \return void
 */
void cJS_GetURLPart(jsval *vp, const uint8_t *url, jsuint partType);

/**
 * Get JS Context pointer.
 * \param void
 * \return JSContext
 */
JSContext * cJS_GetContext(void);

/**
 * Create the prototype object of window object when JS Engine Initialized
 * \param void
 * \return
 *      -JS_TRUE when success
 *      -JS_FALSE when failed
 */
JSBool cJS_NewWindowProto(void);

/**
 * Get current document object pointer.
 * \param void
 * \return documentObj
 */
JSObject * cJS_GetDocumentObj(void);

/**
 * Get current forms object pointer.
 * \param void
 * \return formsObj
 */
JSObject * cJS_GetFormsObj(void);

JSObject * cJS_GetLocationObj(void);

#ifndef CJS_WINDOW_PROTO
JSObject * cJS_GetNavigatorObj(void);
JSObject * cJS_GetHistoryObj(void);
void * cJS_GetNavigatorObjPtr(void);
void * cJS_GetLocationObjPtr(void);
void * cJS_GetHistoryObjPtr(void);
#endif

JSBool cJS_VoidMethod(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);

/**
 * Get field object via its system id.
 * \param fieldSystemID [in]the field object system ID
 * \return
 *      -NULL when failed in getting
 *      -field object when successful
 */
JSObject * cJS_GetFieldObj(jsint fieldSysId);

/**
 * Get form object via its system id.
 * \param formSysId [in]the form object system ID
 * \return
 *      -NULL when failed in getting
 *      -form object when successful
 */
JSObject * cJS_GetFormObj(jsint formSysId);

/**
 * Create a js field objec.
 * \param iField       [in]the T_DB_ContentlinkAPTR in the browser structure
 * \param pField       [in]the field structure in browser structure
 * \param cx           [in]the JSContext pointer
 * \param formObj      [in]the parent form object
 * \param elementsObj  [in]the elements object of the parent form object
 * \param elementsLen  [in]the length of the elements Object
 * \param rFieldObjPtr [out]the pointer of created field Object's pointer
 * \return
 *      -JS_TRUE when create successfully
 *      -JS_FALSE when failed in creating
 */
JSBool cJS_NewFieldObject( T_DB_FieldNodeIdx iField,
                           T_DB_FieldNodePtr pField,
                           JSContext *cx,
                           JSObject *formObj,
                           JSObject *elementsObj,
                           jsuint elementsLen,
                           JSObject **rFieldObjPtr);

/**
 * Create a js form object.
 * \param cx       [in]the JSContext pointer
 * \param formsObj [in/out]the forms object of the document object
 * \param formsLen [in/out]the length of the forms Object
 * \param systemID [out]the T_DB_ContentlinkAPTR in the browser structure of the form
 * \param rFormObj [out]the pointer of created form Object's pointer
 * \return
 *      -JS_TRUE when create successfully
 *      -JS_FALSE when failed in creating
 */
JSBool cJS_NewFormObject( JSContext *cx,
                          JSObject *formsObj,
                          jsuint formsLen,
                          int32_t systemId,
                          JSObject **rFormObj);

/**
 * Create an option object.
 * \param cx      [in]JS context
 * \param pOption [in]pointer of option obj in js engine
 * \param pObj    [out]pointer of option obj pointer in browser
 * \return
 *      -JS_FALSE when failed
 *      -JS_TRUE when success
 */
JSBool cJS_NewOptionObject(JSContext *cx, int32_t iOption, JSObject **pObj);

/**
 * Create options collection Object.
 * \param cx the JSContext pointer
 * \param priData the private data for options collection object.
 * \return
 *      -new created options collection Object when success
 *      -NULL when failed
 */
JSObject * cJS_newOptionsCollection(JSContext *cx, cjsOptsPriData *priData);

#ifdef SUPPORT_VARIANT_ARRAY

JSObject * cJS_NewVariantArrayObject(JSContext *cx);
JSBool cJS_SetVariantElement(JSContext *cx, JSObject *obj, jsval *vp);
JSBool cJS_GetVariantElement(JSContext *cx, JSObject *obj, jsuint index, jsval *vp);
JSBool cJS_GetVariantArrayLength(JSContext *cx, JSObject *obj, jsuint *length);

#endif /* SUPPORT_VARIANT_ARRAY */

/**
 * Get anchor's attribute pointer via its content pointer
 * \param aNodeIndex [in]the index of the node
 * \return
 *      -NULL when failed
 *      -attribute pointer when success
 */
T_DB_AAttrPtr cJS_GetAttrNodePtr(int16_t aNodeIndex);

/**
 * Convert a int32_t value to a string, such as 0xabcd21 to "abcd21"
 *  note: need a char henStr[8] array for a param.
 * \param intVal    [in]a int32_t value
 * \param henStr[8] [out]a string presenting a int32_t value
 * \return void
 */
void cJS_Int2HexStr(int32_t intVal, uint8_t henStr[8]);

/**
 * Convert a string color to a int32_t value color,
 *  such as "abcd21" or "0xabcd21 to 0xabcd21 or "red" to 0xff0000
 * \param hexStrColor [in]a string presenting certain color
 * \return
 *      -a int32_t value presenting a certain color
 */
int32_t cJS_HexStr2IntColor(const uint8_t *hexStrColor);

/* not use now */
void fnDBA_strncpy(uint8_t *destStr, uint8_t *srcStr, int32_t len);

/**
 * Get client object's properties
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \param id  [in]the property's identification
 * \param vp  [out]value of the property
 * \return
 *      -JS_TRUE when get successfully
 */
JSBool Void_GetProperty (JSContext *cx, JSObject *obj, jsval id, jsval *vp);

/**
 * Get client object's properties
 * \param cx  [in]the JS context
 * \param obj [in]the corresponding object for execute
 * \param id  [in]the property's identification
 * \param vp  [out]value of the property
 * \return
 *      -JS_TRUE when set successfully
 */
JSBool Void_SetProperty (JSContext *cx, JSObject *obj, jsval id, jsval *vp);

typedef struct _init_object_params {
    JSObject* windowObj_ptr;
    JSObject* documentObj_ptr;
    JSObject* formsObj_ptr;
}CJS_InitObjectsParams;

/**
 * Initialize global variants such as window object, document object, etc
 *  when open a new document.
 * \param init_params_ptr [in]Pointer of object which includes all we want to initialize
 * \return void
 */
void cJS_InitObjects(CJS_InitObjectsParams* init_parasm_ptr);

/**
 * Get current URL's hostname
 * \param cx [in]the JS context
 * \return if success return hostname, or return NULL
 */
uint8_t * cJS_GetHostname(JSContext *cx);

/**
 * Get the document color, such as fgcolor, bgcolor, linkcolor and vlinkcolor.
 * \param vp        [out]jsval pointer ,which is used to store the getted color
 * \param colorType [in]imply the type to get, such as fgcolor, ...vlinkcolor
 * \return void
 */
void cJS_GetDocColor(jsval *vp, jsint colorType);

/**
 * Set the document color, such as fgcolor, bgcolor, linkcolor and vlinkcolor
 * \param colorVal  [in]jsval type, a jsint or JSString
 * \param colorType [in]imply the type to set, such as fgcolor, ...vlinkcolor
 * \return void
 */
void cJS_SetDocColor(jsval colorVal, jsint colorType);

/**
 * Start to load a new page.
 * \param href [in]the new page's URL
 * \return void
 */
void cJS_LoadUrl(const uint8_t *href);

/**
 * Get window prototype.
 * \param void
 * \return window prototype
 */
JSObject * cJS_GetWindowProto(void);

/**
 * Get the pointer of window prototype.
 * \param void
 * \return pointer of window prototype
 */
void * cJS_GetWindowProtoPtr(void);

#define   NO_TYPE   -1
/**
 * Create predefined JS object.
 * \param void
 * \return
 *      -JS_FALSE when js context is NULL
 */
JSBool fnDBJS_CreatePreDefinedObject(void);

/**
 * Do event which was appointed.
 * \param obj        [in]the corresponding object on with event was trigged
 * \param scriptCode [in]the corresponding script statements
 * \param codeType   [in]the event type
 * \return
 *      -false when failed
 *      -true when success
 */
int32_t cJS_DoEventScript(void *obj, const uint8_t *scriptCode, int32_t codeType);

#define CJS_HREF_IS_SCRIPT(href) ( !CRTL_strncmp(href, CJS_STR_JAVASCRIPT, 11) || \
                                   !CRTL_strncmp(href, CJS_STR_ECMASCRIPT, 11) )

/**
 * Reset branch callback's called count
 * when start to evaluate a new JavaScript codes block or new event handler.
 */
void cJS_resetBranchCalledCount(void);

/**
 * Implement the JS code which is about Link object.
 * \param linkSystemID [in]link object's system id
 * \param linkScript   [in]the script which is about link class
 * \param eventType    [in]type of the event which is triggered
 * \return
 *      -TRUE when linkScript is NULL or implement successfully
 *      -FALSE when failed
 */
int32_t fnJS_ExecLinkScript(int32_t linkSystemID, const uint8_t* linkScript, int32_t eventType);

/* Store systemID by JS_GetReservedSlot() and JS_SetReservedSlot() methods */
#define CJS_SYSTEM_ID_SLOT      0
#define CJS_FORM_ID_SLOT        1

typedef enum cJSEventNum {
#define EVENT_DEF(eventMacro, eventNumber, eventName) \
    eventMacro = eventNumber,
#include <uapps/wap/esmpclient/esmpclient_event.msg>
#undef EVENT_DEF
    cJS_Event_Limit
} T_CJS_EventNum;
/* extern const uint8_t* gEventBytesType[]; */

#ifdef __cplusplus
}
#endif/* __cplusplus */

#endif /* __ESMPCLIENT_INNERAPI_H__ */
