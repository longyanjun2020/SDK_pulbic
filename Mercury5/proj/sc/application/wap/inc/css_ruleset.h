
#ifndef _CSS_RULESET_H_
#define _CSS_RULESET_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _CSS_Ruleset CSS_Ruleset;

typedef CommonArray CSS_RulesetContainer ;

struct _CSS_Ruleset
{
    CSS_SelectorContainer * selectors;
    CSS_PropertyContainer * properties;
};

/* Funtions for CSS_Ruleset */

/**
 * Get selector container from ruleset list
 * \param ruleset the pointer of ruleset containing the selector container.
 * \return
 *      Pointer of selector container when success.
 *      NULL when failure.
 */
//NCC_INLINE const CSS_SelectorContainer * CSS_Ruleset_getSelectorContainer(const CSS_Ruleset * ruleset);
const CSS_SelectorContainer * CSS_Ruleset_getSelectorContainer(const CSS_Ruleset * ruleset);

/**
 * Set selector container to a ruleset
 * \param ruleset the pointer of ruleset
 * \param selectorContainer the pointer of selector container to be set
 * \return void
 */
//NCC_INLINE void CSS_Ruleset_setSelectorContainer(CSS_Ruleset * ruleset, CSS_SelectorContainer * selectorContainer);
void CSS_Ruleset_setSelectorContainer(CSS_Ruleset * ruleset, CSS_SelectorContainer * selectorContainer);

/**
 * Get property container from a ruleset
 * \param ruleset the pointer of ruleset containing the property container.
 * \return
 *      Pointer of property container when success.
 *      NULL when failure.
 */
//NCC_INLINE const CSS_PropertyContainer * CSS_Ruleset_getPropertyContainer(const CSS_Ruleset * ruleset);
const CSS_PropertyContainer * CSS_Ruleset_getPropertyContainer(const CSS_Ruleset * ruleset);

/**
 * Set property container to a ruleset
 * \param ruleset the pointer of ruleset
 * \param propertyContainer the pointer of property container to be set
 * \return void
 */
//NCC_INLINE void CSS_Ruleset_setPropertyContainer(CSS_Ruleset * ruleset, CSS_PropertyContainer * propertyContainer);
void CSS_Ruleset_setPropertyContainer(CSS_Ruleset * ruleset, CSS_PropertyContainer * propertyContainer);

/* Funtions for CSS_RulesetContainer */

/**
 * Create a ruleset container.
 * \param void
 * \return
 *      Pointer of a new ruleset container when success
 *      NULL when failure
 */
CSS_RulesetContainer * CSS_RulesetContainer_create();

/**
 * Destroy the given ruleset container
 * \param container ruleset container to be destroyed
 * \return void
 */
void CSS_RulesetContainer_destroy(CSS_RulesetContainer ** container);

/**
 * Get next ruleset from the ruleset container, the second parameter indicate the current position
 * \param container the pointer of ruleset container
 * \param current current ruleset, NULL means the first
 * \return
 *      Pointer of the next ruleset when success
 *      NULL indicate end of ruleset container
 */  // 
//extern NCC_INLINE const CSS_Ruleset * CSS_RulesetContainer_getNext(const CSS_RulesetContainer * container, const CSS_Ruleset * current);
extern const CSS_Ruleset * CSS_RulesetContainer_getNext(const CSS_RulesetContainer * container, const CSS_Ruleset * current);


/**
 * Append a group of rulesets into ruleset container
 * \param container the pointer of ruleset container
 * \param rulesets the pointer of rulesets
 * \param num number of rulesets
 * \return
 *      FALSE for failure
 *      TRUE for success
 */
int32_t CSS_RulesetContainer_append(CSS_RulesetContainer * container, const CSS_Ruleset * rulesets, int32_t num);

/**
 * Sort the rulesets in CSS_RulesetContainer by their specificity.
 * There's four rules for sepecificity:
 * 1. count the number of ID attributes in the selector (= a)
 * 2. count the number of other attributes and pseudo-classes in the selector (= b)
 * 3. count the number of element names in the selector (= c)
 * 4. ignore pseudo-elements.
 * Concatenating the three numbers a-b-c (in a number system with a large base) gives the specificity.
 * For example:
 *      UL OL LI.red  {}   a=0 b=1 c=3 -> specificity = 0 - 1 - 3
 *      LI.red.level  {}   a=0 b=2 c=1 -> specificity = 0 - 2 - 1
 *      #x34y         {}   a=1 b=0 c=0 -> specificity = 1 - 0 - 0
 * So #x34y is the most specific rule and 'LI.red.level' is the least rule.
 * \param container the pointer of the ruleset container.
 * \return
 *      TRUE if success.
 *      FALSE if failed.
 */
uint32_t CSS_RulesetContainer_sortBySpecificity (CSS_RulesetContainer * container);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CSS_RULESET_H_ */
