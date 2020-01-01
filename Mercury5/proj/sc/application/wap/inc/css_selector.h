
#ifndef _CSS_SELECTOR_H_
#define _CSS_SELECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * The simple selector
 */
typedef struct _CSS_SimpleSelector CSS_SimpleSelector;

/**
 * Container that contains simple selectors
 */
typedef CommonArray CSS_SelectorContainer;

#define CSS_SIMPLE_SELECTOR_PSEUDO_LINK_MASK            (0x01)
#define CSS_SIMPLE_SELECTOR_PSEUDO_VISITED_MASK         (0x02)
#define CSS_SIMPLE_SELECTOR_PSEUDO_ACTIVE_MASK          (0x04)
#define CSS_SIMPLE_SELECTOR_PSEUDO_FOCUS_MASK           (0x08)

/* The following three are not required in wcss */
#define CSS_SIMPLE_SELECTOR_PSEUDO_HOVER_MASK           (0x10)
#define CSS_SIMPLE_SELECTOR_PSEUDO_FIRST_CHILD_MASK     (0x20)
#define CSS_SIMPLE_SELECTOR_PSEUDO_LANG_MASK            (0x40)

#define CSS_SIMPLE_SELECTOR_SET_PSEUDO_LINK(a)          ((a) = ((a) | CSS_SIMPLE_SELECTOR_PSEUDO_LINK_MASK))
#define CSS_SIMPLE_SELECTOR_SET_PSEUDO_VISITED(a)       ((a) = ((a) | CSS_SIMPLE_SELECTOR_PSEUDO_VISITED_MASK))
#define CSS_SIMPLE_SELECTOR_SET_PSEUDO_ACTIVE(a)        ((a) = ((a) | CSS_SIMPLE_SELECTOR_PSEUDO_ACTIVE_MASK))
#define CSS_SIMPLE_SELECTOR_SET_PSEUDO_FOCUS(a)         ((a) = ((a) | CSS_SIMPLE_SELECTOR_PSEUDO_FOCUS_MASK))
#define CSS_SIMPLE_SELECTOR_SET_PSEUDO_HOVER(a)         ((a) = ((a) | CSS_SIMPLE_SELECTOR_PSEUDO_HOVER_MASK))
#define CSS_SIMPLE_SELECTOR_SET_PSEUDO_FIRST_CHILD(a)   ((a) = ((a) | CSS_SIMPLE_SELECTOR_PSEUDO_FIRST_CHILD_MASK))
#define CSS_SIMPLE_SELECTOR_SET_PSEUDO_LANG(a)          ((a) = ((a) | CSS_SIMPLE_SELECTOR_PSEUDO_LANG_MASK))

#define CSS_SIMPLE_SELECTOR_IS_PSEUDO_LINK(a)           ((a) & CSS_SIMPLE_SELECTOR_PSEUDO_LINK_MASK)
#define CSS_SIMPLE_SELECTOR_IS_PSEUDO_VISITED(a)        ((a) & CSS_SIMPLE_SELECTOR_PSEUDO_VISITED_MASK)
#define CSS_SIMPLE_SELECTOR_IS_PSEUDO_ACTIVE(a)         ((a) & CSS_SIMPLE_SELECTOR_PSEUDO_ACTIVE_MASK)
#define CSS_SIMPLE_SELECTOR_IS_PSEUDO_FOCUS(a)          ((a) & CSS_SIMPLE_SELECTOR_PSEUDO_FOCUS_MASK)
#define CSS_SIMPLE_SELECTOR_IS_PSEUDO_HOVER(a)          ((a) & CSS_SIMPLE_SELECTOR_PSEUDO_HOVER_MASK)
#define CSS_SIMPLE_SELECTOR_IS_PSEUDO_FIRST_CHILD(a)    ((a) & CSS_SIMPLE_SELECTOR_PSEUDO_FIRST_CHILD_MASK)
#define CSS_SIMPLE_SELECTOR_IS_PSEUDO_LANG(a)           ((a) & CSS_SIMPLE_SELECTOR_PSEUDO_LANG_MASK)

#define CSS_SIMPLE_SELECTOR_IS_PSEUDO_MATCHED(dst, src) (((dst) & (src)) == (dst))

/* Attribute and pseudo-element are not required in wcss */
#define CSS_SIMPLE_SELECTOR_TYPE_CLASS_MASK         (0x01)
#define CSS_SIMPLE_SELECTOR_TYPE_ID_MASK            (0x02)
#define CSS_SIMPLE_SELECTOR_TYPE_PSEUDO_CLASS_MASK  (0x04)

#define CSS_SIMPLE_SELECTOR_TYPE_SET_CLASS(a)           ((a) = ((a) | CSS_SIMPLE_SELECTOR_TYPE_CLASS_MASK))
#define CSS_SIMPLE_SELECTOR_TYPE_SET_ID(a)              ((a) = ((a) | CSS_SIMPLE_SELECTOR_TYPE_ID_MASK))
#define CSS_SIMPLE_SELECTOR_TYPE_SET_PSEUDO_CLASS(a)    ((a) = ((a) | CSS_SIMPLE_SELECTOR_TYPE_PSEUDO_CLASS_MASK))

#define CSS_SIMPLE_SELECTOR_TYPE_IS_CLASS(a)            ((a) & CSS_SIMPLE_SELECTOR_TYPE_CLASS_MASK)
#define CSS_SIMPLE_SELECTOR_TYPE_IS_ID(a)               ((a) & CSS_SIMPLE_SELECTOR_TYPE_ID_MASK)
#define CSS_SIMPLE_SELECTOR_TYPE_IS_PSEUDO_CLASS(a)     ((a) & CSS_SIMPLE_SELECTOR_TYPE_PSEUDO_CLASS_MASK)

/**
 * Struct of CSS simple selector
 * Example: p#e11 h1 A.oldclass:link{color : red}
 * In this example, p is a simple selector, #e11 is its id. And A is another simple selector,
 * .oldclass is its class name, and :link is its pseudo class name.
 */
struct _CSS_SimpleSelector
{
    HTMLTAG htmlTag;
    int8_t *classId;            /* String of class name or id, every class and id string information are stored here. Such as "#id1.class1.class2" etc.*/
    int16_t type;               /* Simple selector type */
    int16_t pseudoClass;
} ;

/**
 * Check if the tag matchs the given simple selector.
 * Todo: The function is still need to be refactor. The problem is about pseudo class.
 * \param selector the given simple selector
 * \param name tag name
 * \param id tag id
 * \param className tag's class name
 * \return
 *      FALSE if failure
 *      TRUE if success
 */
int32_t CSS_SimpleSelector_isMatched(const CSS_SimpleSelector* selector,
                                    HTMLTAG name,
                                    const int8_t *id,
                                    const int8_t *className,
                                    const int16_t pseudo);


/**
 * Convert SAC simple selector to CSS simple selector
 * \param cssSel pointer to CSS simple selector which is used for stroing result
 * \param sacSel pointer to SAC simpleSelector to be translate.
 * \return
 *      FALSE for failure
 *      TRUE for success
 */
 //welee changed
int32_t CSS_SimpleSelector_convert(CSS_SimpleSelector * cssSel, const SAC_SimpleSelector * sacSel);

/**
 * Create a selector container.
 * \param void
 * \return
 *      Pointer of a new selector container when success
 *      NULL when failure
 */
CSS_SelectorContainer * CSS_SelectorContainer_create();

/**
 * Destroy the given selector container
 * \param container selector container to be destroyed
 * \return void
 */
void CSS_SelectorContainer_destroy(CSS_SelectorContainer ** container);

/**
 * Get next selector from the selector container, the second parameter indicate the current position
 * \param container the pointer of selector container
 * \param current current selector, NULL means the first
 * \return
 *      Pointer of the next selector when success
 *      NULL indicate end of selector container
 */
//extern NCC_INLINE const CSS_SimpleSelector * CSS_SelectorContainer_getNextSelector(const CSS_SelectorContainer * container, const CSS_SimpleSelector * current);
extern const CSS_SimpleSelector * CSS_SelectorContainer_getNextSelector(const CSS_SelectorContainer * container, const CSS_SimpleSelector * current);

/**
 * Duplicate a group of selectors into selector container. The function should be called only once for each new container,
 * otherwise the functions will be faild.
 * \param container the pointer of selector container
 * \param selectors the pointer of selectors
 * \param size size of selectors
 * \return
 *      FALSE for failure
 *      TRUE for success
 */
 // changed
int32_t ectorContainer_fill(CSS_SelectorContainer * container, const CSS_SimpleSelector * selectors, int32_t size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CSS_SELECTOR_H_ */

