
/**
 * @file
 * NCC mms parser slideview
 *
 * Slide helper routines used by NCC mms parser
 */

#ifndef __PAR_SLIDEVIEW_H__
#define __PAR_SLIDEVIEW_H__

#include <par_config.h>
#include <par_parse.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MMS_ATTACHMENT_NAME                                  "ES_MovedFile%04d"
#define MMS_ATTACHMENT_FILE_LEN                              30

/*****************************************************************************/
/* API define */

/**
 * Parse the mms which hasn't  smil document
 * \param HandMMS       handle
 * \param pElement      smil element
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
int32_t SmilParserNoSmilMMS(T_MMS_HANDLE * HandMMS,
                            T_MMS_Media_Element * pElement);

/**
 * Parse smil document
 * \param HandMMS       handle
 * \param pUnion
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
int32_t SmilParserSmilMMS(T_MMS_HANDLE * HandMMS, T_MMS_Content_Union * pUnion);

/**
 * Get the element struct pointer by the element name
 * \param pEle      element of smil
 * \param Id        id of smil
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
T_MMS_Media_Element *SmilGetElementById(T_MMS_Media_Element * pEle,
                                        int8_t * Id);

/**
 * Check if the current par has audio element
 * \param SmilView      structure of smil view
 * \param pEle          element pointer
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
int32_t MMSParserAttach(T_Parser_SmilView * SmilView,
                        T_MMS_Media_Element * pEle);

int32_t SMILMoveMediaToAttachment(T_Parser_SmilView * SmilView,
                                  T_MMS_Parser_BasicStructure * BasicStruct,
                                  T_Parser_Attr_Value * Attr);

#ifdef __cplusplus
}
#endif

#endif /* __PAR_SLIDEVIEW_H__ */
