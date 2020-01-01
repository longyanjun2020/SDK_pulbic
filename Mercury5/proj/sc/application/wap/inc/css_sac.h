
#ifndef _CSS_SAC_H_
#define _CSS_SAC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SAC_FLOAT_TOLERANCE (1e-3)
/**
 * array of the sac simple selector
 */
typedef CommonArray SAC_SimpleSelectorArray;

/**
 * struct of selector.
 * this structure is used for transmit parsed selectors and properties from css_parser
 * to sac callback functions
 */
typedef struct _SAC_Selector SAC_Selector;

struct _SAC_Selector {
    SAC_SimpleSelectorArray *simpleSelArray;        /**< simple selector common array */
};

/**
 * type of simple selector
 * for eg: p {color:red} , this ruleset's selector type is SIMPLE_SELECTOR_TYPE_TYPE_SELECTOR
 */
typedef enum _SimpleSelectorType {
    SIMPLE_SELECTOR_TYPE_UNKNOWN,                          /**< unknow type */
    SIMPLE_SELECTOR_TYPE_UNIVERSAL_SELECTOR,               /**< universal selector like "*" */
    SIMPLE_SELECTOR_TYPE_TYPE_SELECTOR,               /**< a tag like "p, body" */
} SimpleSelectorType;

/**
 * type of additional selector
 * for eg: #id {color:red} ,
 * this ruleset's addtional selector type is ADDITIONAL_SELECTOR_TYPE_ID_SELECTOR
 */
typedef enum _AdditionSelectorType {
    ADDITIONAL_SELECTOR_TYPE_UNKNOWN,                          /**< unknow type */
    ADDITIONAL_SELECTOR_TYPE_CLASS_SELECTOR,              /**< class like ".class1" */
    ADDITIONAL_SELECTOR_TYPE_ID_SELECTOR,                 /**< id like "#id1" */
    ADDITIONAL_SELECTOR_TYPE_ATTR_SELECTOR,               /**< attrib like "[attr=val]" */
    ADDITIONAL_SELECTOR_TYPE_PSEUDO_SELECTOR,             /**< pseudo type like ":link" */
} AdditionSelectorType;

/**
 * type of selector combinator
 * for eg: p h {color:red} ,
 * this ruleset's SelectorCombinator is SELECTOR_COMBINATOR_DESCENDANT
 */
typedef enum _SelectorCombinator {
    SELECTOR_COMBINATOR_UNKNOWN,
    SELECTOR_COMBINATOR_INIT,
    SELECTOR_COMBINATOR_DESCENDANT,
    SELECTOR_COMBINATOR_ADJACENT,
    SELECTOR_COMBINATOR_CHILD,
} SelectorCombinator;

/**
 * array of the additional selector
 * for eg h.class#id, the class is the first element of the array while id is the second element
 */
typedef CommonArray AdditionalSelectorArray;

/**
 * type for the Pseudo classes and elements
 * for eg, the :link's type is SELECTOR_PSEUDO_LINK
 */
typedef enum _PseudoType {
    SELECTOR_PSEUDO_LINK,
    SELECTOR_PSEUDO_VISITED,
    SELECTOR_PSEUDO_ACTIVE,
    SELECTOR_PSEUDO_FOCUS,
    SELECTOR_PSEUDO_FIRST_CHILD,
    SELECTOR_PSEUDO_HOVER,
} PseudoType;

/**
 * struct for the additional selector
 * for eg: #id, this addtional selector's type is ADDITIONAL_SELECTOR_TYPE_ID_SELECTOR while idName is "id"
 */
typedef struct _AdditionalSelector {
    AdditionSelectorType type;
    //union {
        int8_t *className;
        int8_t *idName;
        int8_t *attrName;
        PseudoType pseudo;
    //};
} AdditionalSelector;

/**
 * struct of simple selector
 * this structure is used for transmit parsed selectors and properties from css_parser
 * to sac callback functions
 *
 * for eg: p + h for "+ h" the '+' is stored in to the h's combinator
 */
typedef struct _SAC_SimpleSelector SAC_SimpleSelector;

struct _SAC_SimpleSelector {
    SimpleSelectorType type;   /**< simple selector type */
    int8_t *name;                /**< content of the simple selector with null character to terminate*/

    SelectorCombinator combinator; /**< the combinator between THIS simple selector
                                            and PREVIOUS simple selectors */
    AdditionalSelectorArray *addSelArray; /**< the additional selector for this simple selector*/
};

/**
 * the operator type for term
 *
 * case: P { font:12px/14px }, the type for the term should be set as TERM_OPERATOR_SLASH
 */
enum _TermOperatorType {
    TERM_OPERATOR_ERROR,            /**< error operator */
    TERM_OPERATOR_SLASH,                /**< "/" */
    TERM_OPERATOR_COMMA,                /**< "," */
    TERM_OPERATOR_EMPTY,                /**< empty */
};
typedef enum _TermOperatorType TermOperatorType;

/**
 * struct for the parsed property value
 *
 * case: p { font-size: 12px},
 *      while the css parser parse this rule, the value of the 'font-size' and '12px' be saved
 *  into this term struct, and  be added into a SAC_Expr (as a common array) for css_sac callback's
 *  use
 */
//typedef struct _SAC_Term SAC_Term;
struct _SAC_Term {
    TermOperatorType op;
    SAC_CSSValue cssValue;
};

typedef struct _CSS_Property CSS_Property;
typedef struct _SAC_Handler SAC_Handler;
typedef struct _SAC_Parser SAC_Parser;

//typedef enum _CSS_AttachDocType CSS_AttachDocType;

typedef int32_t SAC_BOOL;

#define SAC_SELECTOR                                         int32_t    /* For temporary using. */
#define SAC_FATALl_ERROR                                     int32_t
#define SAC_ERROR                                            int32_t

/**
 * -wap-input-type format type
 */
typedef enum _WapInputType{
    WAP_INPUT_TYPE_A,       /**< entry of any uppercase letter, symbol, or punctuation character. Numeric characters are excluded. */
    WAP_INPUT_TYPE_a,       /**< entry of any lowercase letter, symbol, or punctuation character. Numeric characters are excluded. */
    WAP_INPUT_TYPE_N,       /**< entry of any numeric character. */
    WAP_INPUT_TYPE_n,       /**< entry of any numeric, symbol, or punctuation character. */
    WAP_INPUT_TYPE_X,       /**< entry of any uppercase letter, numeric character, symbol, or punctuation character. */
    WAP_INPUT_TYPE_x,       /**< entry of any lowercase letter, numeric character, symbol, or punctuation character. */
    WAP_INPUT_TYPE_M,       /**< entry of any character valid in the current languages, including any letter, numeric, symbol, or punctuation
                                 character. If the language supports case and the device supports both upper and lower case entry, the user
                                 agent may choose to default to uppercase entry mode but MUST allow entry of any character. */
    WAP_INPUT_TYPE_m,       /**< entry of any character valid in the current languages, including any letter, numeric, symbol, or punctuation
                                 character. If the language supports case and the device supports both upper and lower case entry, the user
                                 agent may choose to default to lowercase entry mode but MUST allow entry of any character. */
    WAP_INPUT_TYPE_CHAR,    /**< special charactor */
}WapInputType;

/**
 * struct of css parser
 */
struct _SAC_Parser {
    SAC_Handler *sacHandler;
    enum {
        PARSE_STYLESHEET,
        PARSE_INLINE,
        PARSE_IMPORT,
    } curParseType;             /* maybe more... */
};
/**
 * The SAC handler. An instance of self class is to
 * be passed to the CSS parser. The fun(s) will be invoked while
 * a particular event happens. See HTTP://www.w3.org/Style/CSS/SAC/
 * for more details.
 */

struct _SAC_Handler {
    /* Callback functions used by SAC parser */
    void (*startDocument) (SAC_Handler * self);

    void (*endDocument) (SAC_Handler * self);

    void (*comment) (SAC_Handler * self, const int8_t * data);

    void (*ignorableAtRule) (SAC_Handler * self, const int8_t * atRule);

    void (*namespaceDeclaration) (SAC_Handler * self, const int8_t * prefix, const int8_t * uri);

    void (*import) (SAC_Handler * self,
                    const int8_t * base,
                    const int8_t * uri,
                    const int8_t * media[],
                    const int8_t * defaultNamepaceURI);

    void (*startMedia) (SAC_Handler * self, const int8_t * media[]);

    void (*endMedia) (SAC_Handler * self, const int8_t * media[]);

    void (*startPage) (SAC_Handler * self, const int8_t * name, const int8_t * pseudoPage);

    void (*endPage) (SAC_Handler * self, const int8_t * name, const int8_t * pseudoPage);

    void (*startFontFace) (SAC_Handler * self);

    void (*endFontFace) (SAC_Handler * self);

    void (*startSelector) (SAC_Handler * self, const CommonArray * selectors);

    void (*endSelector) (SAC_Handler * self, const CommonArray * selectors);

    void (*property) (SAC_Handler * self,
                      const int8_t * propertyName,
                      const SAC_Expr * cssExpr,
                      SAC_BOOL important);

    void (*fatalError) (SAC_Handler * self, const SAC_FATALl_ERROR * fatalError);

    void (*error) (SAC_Handler * self, const SAC_ERROR * error);
    /* Call back functions end. */
};

/**
 * CSS parser interface
 * \param parser SAC parser
 * \param cssContent CSS content NOTE: expect for UTF-8 encoding
 * \param len the length of cssContent
 * \return 1 for success 0 for failed
 */
int32_t SAC_parseStyleSheet(SAC_Parser * parser, const int8_t * cssContent, int32_t len);

/**
 * CSS parse style declaration(the same as inline style) interface
 * \param parser SAC parser
 * \param cssContent CSS content NOTE: expect for UTF-8 encoding
 * \param len the length of cssContent
 * \return TRUE for success FALSE for failed
 */
int32_t SAC_parseStyleDeclaration(SAC_Parser * parser, const int8_t * cssContent, int32_t len);
/**
 * Create a new SAC handler
 * \return
 *      the pointer of created SAC parser
 *      NULL if fail
 */
SAC_Parser *SAC_createParser(void);

/**
 * Set a new SAC handler to parser.
 * \param parser parser to set
 * \param sacHandler SAC handler to be set
 * \return void
 */
void SAC_setSACHandler(SAC_Parser * parser, SAC_Handler * sacHandler);

/**
 * Get a current used SAC handler.
 * \param parser parser to get
 *      the pointer of SAC handler.
 *      NULL if empty
 */
SAC_Handler *SAC_getSACHandler(SAC_Parser * parser);

/**
 * Destroy a SAC parser.
 * \param self handler to be destroyed.
 * \return void
 */
void SAC_destroyParser(SAC_Parser ** parser);

/**
 * create a simple selector
 * \return SAC_SimpleSelector * the new created simple selector , NULL if failed
 */
SAC_SimpleSelector *SAC_SimpleSelector_create();

/**
 * create a simple selector
 *
 * \param SAC_SimpleSelector ** the simple selector  to be destroyed
 * \return void
 */
void SAC_SimpleSelector_destroy(SAC_SimpleSelector ** simpleSel);

#ifdef __cplusplus
}
#endif

#endif                          /* _CSS_SAC_H_ */
