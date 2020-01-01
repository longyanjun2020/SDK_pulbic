
#ifndef _CSS_STYLESHEET_H_
#define _CSS_STYLESHEET_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _CSS_StyleSheet CSS_StyleSheet;

/**
 * The struct of style sheet which contains all informations,
 * The parser parses a style sheet and put all needed information into this struct.
 */
struct _CSS_StyleSheet {
    CSS_RulesetContainer * rulesets;
} ;

/**
 * Create a new CSS_StyleSheet.
 * \param void
 * \return
 *      the pointer of new CSS_StyleSheet if success
 *      NULL if fail
 */
CSS_StyleSheet * CSS_createStyleSheet();

/**
 * Destroy a CSS_StyleSheet.
 * \param self the pointer of CSS_StyleSheet to be destroyed.
 * \return void
 */
void CSS_destroyStyleSheet(CSS_StyleSheet ** self);

/**
 * Get ruleset container from style sheet
 * \param ruleset the pointer of ruleset containing the ruleset container.
 * \return
 *      Pointer of ruleset container when success.
 *      NULL when failure.
 */  // 
//NCC_INLINE const CSS_RulesetContainer * CSS_getRulesetContainerFromStyleSheet(const CSS_StyleSheet * styleSheet);
const CSS_RulesetContainer * CSS_getRulesetContainerFromStyleSheet(const CSS_StyleSheet * styleSheet);


/**
 * Append ruleset container to a style sheet
 * \param sytleSheet the pointer of style sheet
 * \param rulesetContainer the pointer of ruleset container to be appended
 * \return void
 */
NCC_INLINE void CSS_StyleSheet_append(CSS_StyleSheet * styleSheet, CSS_RulesetContainer * rulesetContainer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CSS_STYLESHEET_H_ */
