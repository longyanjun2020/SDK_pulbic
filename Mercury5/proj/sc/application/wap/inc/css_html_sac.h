
#ifndef _CSS_HTML_SAC_H_
#define _CSS_HTML_SAC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _HTML_SAC_Handler HTML_SAC_Handler;

/**
 * Create a HTML SAC handler add set all callback handler.
 * \param void
 * \return
 *      Pointer of new HMTL_SAC_Handle when success.
 *      NULL when fail
 */
SAC_Handler * HTML_SAC_createHandler(void);

/**
 * Get associate StyleSheet from HTML SAC handler for CSS_Manager,
 * And, this function only be called interiorly by the css manager which just do  read operations
 * on stylesheet, so the return value type is set as const
 *
 * \param self sac handler to get
 * \return the address of CSS style sheet
 */
const CSS_StyleSheet * HTML_SAC_getStyleSheet(HTML_SAC_Handler * self);

/**
 * Destroy a HTML SAC handler.
 * \param self the pointer of handler to be destroyed.
 * \return void
 */
void HTML_SAC_destroyHandler(SAC_Handler ** self);

/**
 * Clear property buffer. The parser need to clear property buffer while parse inline style.
 * \param self the pointer to handler.
 * \return void
 */
void HTML_SAC_clearPropertyBuffer(SAC_Handler * self);

/**
 * Get property buffer.
 * \param self the pointer to handler.
 * \return
 *      pointer to property buffer if success
 *      NULL if failed
 */
const CommonArray * HTML_SAC_getPropertyBuffer(SAC_Handler * self);

/**
 * Set the CSS source type
 * \param self the pointer to handler.
 * \param srcType the source type of current CSS
 * \return void
 */
void HTML_SAC_setSourceType(HTML_SAC_Handler * self, CSS_SourceType srcType);

/**
 * set the destructor for the property buffer
 *
 * \param handler the SAC_Handler of html
 * \param destructor the ref to the desctructor
 * \return void
 */
void  HTML_SAC_propertyBuffer_setDestructor(SAC_Handler * handler, CommonArrayElementDestructor destructor);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CSS_HTML_SAC_H_ */
