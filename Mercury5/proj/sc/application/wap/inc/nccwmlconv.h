
/**
 * @file nccwmlconv.h
 * Wml Conversion Service Layer
 *
 * Service API exposed by the wml conversion.
 *
 * <!-- #interface list begin -->
 * \section nccwmlconv Interface
 * - NCCBrw_wmlconv_varInit()
 * - NCCBrw_wmlconv_varFree()
 * - NCCBrw_wmlconv_varSet()
 * - NCCBrw_wmlconv_varGet()
 * - NCCBrw_wmlconv_varReset()
 * - NCCBrw_wmlconv_getWmlTransCtxData()
 * - NCCBrw_wmlconv_getWmlTransParserDesc()
 * - NCCBrw_wmlconv_checkInputFormat()
 * - NCCBrw_wmlconv_checkAccess()
 * - NCCBrw_wmlconv_wbxmlToWml()
 * - NCCBrw_wmlconv_varSetFromAttr()
 * <!-- #interface list end -->
 */

#ifndef __NCC_WMLCONV_H__
#define __NCC_WMLCONV_H__

#include <wap_service.h>

#ifdef __cplusplus
extern  "C" {
#endif

/**
 * Initialize the vars of wml, a pool of var will be allocated.
 */
int32_t NCCBrw_wmlconv_varInit(void);

/**
 * Release the var of wml, it will free the memory used for var pool.
 */
void NCCBrw_wmlconv_varFree(void);

/**
 * Set the a var of wml into the var pool
 * \param name the name of the var you want to set.
 * \param value the value of the var you want to set.
 * \return void.
 */
void NCCBrw_wmlconv_varSet(uint8_t * name ,uint8_t * value);

/**
 * Get the value of the var named as the name.
 * \param name the var you want get
 * \return the value of the var in the var pool
 */
uint8_t * NCCBrw_wmlconv_varGet(uint8_t * name);

/**
 * Delete all the vars in the var pool.
 */
void NCCBrw_wmlconv_varReset(void);

/**
 *Get wml trans context data.
 * This context data
 * contains all the info when we trans a wml file.
 * \return context data pointer
 */
void* NCCBrw_wmlconv_getWmlTransCtxData(void);

/**
 *Get wml trans parser desc.
 * This desc contains all the
 * handlers resolved in wmlTrans module, other modules can use
 * those handlers to process a wml file.
 * \return desc pointer
 */
void* NCCBrw_wmlconv_getWmlTransParserDesc(void);

/**
 *check if access success
 * \param   inputString
 * \pram    formatString
 * \return      1.SUCCESS/IGNORE(1) means input is correct
 *              2.FAILED(0) means input is not correct
 */
int32_t NCCBrw_wmlconv_checkInputFormat(int8_t * inputString,int8_t * formatString);

/**
 *check if access success
 * \param   wmlbuffer       wml buffer
 * \pram    referringurl    referring url
 * \return  if access success
 */
int32_t NCCBrw_wmlconv_checkAccess(int8_t * wmlbuffer,int8_t * referringurl);

/**
 *convert wbxml to wml document,maybe outofdate
 * \param   wbStream    buffer pointer of wbxml document
 * \param   bufLen      length of wbxml document
 * \return
 *          -success    :pointer of wml
 *          -fail       :NULL
 */
uint8_t * NCCBrw_wmlconv_wbxmlToWml(uint8_t *wbStream,uint32_t bufLen);

/**
 * Excute vars setting.
 * \param   attr    vars pair
 * \param   method  method type of the request. This value should be #DBA_FORM_METHOD_POST or #DBA_FORM_METHOD_GET.
 * \param   enctype the format of certificate object to be exported, TRUE : multipart/form-data; FALSE : others
 * \return  Return the additional data of postfiled of wml
 */
int8_t * NCCBrw_wmlconv_varSetFromAttr(int8_t **attr, int32_t *method, int32_t enctype);

#ifdef __cplusplus
}
#endif

#endif  /*__NCC_WMLCONV_H__*/

