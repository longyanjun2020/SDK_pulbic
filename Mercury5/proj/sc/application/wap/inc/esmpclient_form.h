
#ifndef __ESMPCLIENT_FORM_H__
#define __ESMPCLIENT_FORM_H__

#include <libs/jsengine/inc/jsapi.h>
//#include <jbed_global.h>
#include <uapps/wap/wap_service.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef INULL
#define INULL 0
#endif

/**
 * Form object's ID number is begin from 2, 0 is not used,
 * 1 is used to collect form object which is not in any form.
 */
#define FIRST_FORM_ID     0x02

/* Return this number if there's no element which has the same name */
#define NOT_FOUND         0x01

/* Return this value when we find homonymic element before we create an array with this name */
#define FOUND_NOT_EXIST   0x10

/* Return this value when we find homonymic element after we create an array with this name */
#define FOUND_EXIST       0x11

struct  _jsSearchNode {
    const uint8_t   *nodeName;      /* node name */
    JSBool   isArray;               /* tag of whether the array is creaded */
    JSObject *jsObj;                /* the corresponding JS object */
    jsuint   arrayLen;              /* length of corresponding array */
    struct   _jsSearchNode  *next;  /* the pointer to next node */
};
typedef struct _jsSearchNode    T_JS_SearchNode;
typedef struct _jsSearchNode   *T_JS_SearchNodePtr;

/**
 * Free the allocated some structure space which is used to help solving
 * the homonymic problems during creating form object or form element object.
 * \param pHeadNode [in]the head node of the node list
 * \return void
 */
void cJS_FreeSearchList(T_JS_SearchNodePtr *pHeadNode);

/**
 * Judge whether the inserting node's name exists in the search node list.
 *  if yes: modify the accordingly node's array exist attribute.
 *  note: *pRetSearchNodePtr is initialized NULL before call the search function.
 * \param nodeName          [in]the inserting node's name
 * \param pFirstSearchNode  [in]T_JS_SearchNodePtr type.
 *                              It is the first SearchNode in the search list.
 * \param pRetSearchNodePtr [out]if homonymic node exist, the pRetSearchNodePtr is
 *                                assigned the founded node pointer
 *                                else pRetSearchNodePtr continue keeping NULL.
 * \return
 *      -NOT_FOUND:
 *           no homonymic node with the inserting node in search node list
 *       -FOUND_NOT_EXIST:
 *           homonymic node exist, but only one
 *       -FOUND_EXIST:
 *           homonymic node exist, and more than one, in other way,
 *           the form array has been created.
 */
jsint cJS_SearchNodeList(
                 const uint8_t *nodeName,
                 T_JS_SearchNodePtr pFirstSearchNode,
                 T_JS_SearchNodePtr *pRetSearchNodePtr);

/**
 * Create all js field objects of a form element.
 * \param cx           [in]the JSContext pointer
 * \param formObj      [in]the parent form object
 * \param elementsObj  [in]the elements object of the parent form object
 * \param formSystemID [in]the T_DB_ContentlinkAPTR in the browser structure of the form
 * \return
 *      -JS_TRUE when create successfully
 *      -JS_FALSE when failed
 */
JSBool cJS_CreateAllFieldObject(JSContext *cx,
                                JSObject *formObj,
                                JSObject *elementsObj,
                                int32_t formSystemID);

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
JSBool cJS_NewFieldObject(T_DB_FieldNodeIdx iField,
                          T_DB_FieldNodePtr pField,
                          JSContext *cx,
                          JSObject *formObj,
                          JSObject *elementsObj,
                          jsuint elementsLen,
                          JSObject **rFieldObjPtr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESMPCLIENT_FORM_H__ */
