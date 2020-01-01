
#ifndef _CSS_VALUE_H_
#define _CSS_VALUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define CSS_MAX_STRLEN          (512)
#define CSS_FLOAT_TOLERANCE     (1e-3)

typedef enum _SAC_CSSValueType {

    /* Operators */
    /*
       Note that these operators have no meaning for the parser,
       it's up to the user to interpret each operators.
     */
    SAC_OPERATOR_COMMA,         /* , */
    SAC_OPERATOR_PLUS,          /* + */
    SAC_OPERATOR_MINUS,         /* - */
    SAC_OPERATOR_MULTIPLY,      /* * */
    SAC_OPERATOR_SLASH,         /* / */
    SAC_OPERATOR_MOD,           /* % */
    SAC_OPERATOR_EXP,           /* ^ */
    SAC_OPERATOR_LT,            /* < */
    SAC_OPERATOR_GT,            /* > */
    SAC_OPERATOR_LE,            /* <= */
    SAC_OPERATOR_GE,            /* >= */
    SAC_OPERATOR_TILDE,         /* ~ */
    SAC_INHERIT,                /* identifier inherit */
    /* Integers and reals numbers */
    SAC_INTEGER,
    SAC_REAL,
    /* Relative lengths */
    SAC_LENGTH_EM,              /* em */
    SAC_LENGTH_EX,              /* ex */
    SAC_LENGTH_PIXEL,           /* px */
    /* Absolute lengths */
    SAC_LENGTH_INCH,            /* in */
    SAC_LENGTH_CENTIMETER,      /* cm */
    SAC_LENGTH_MILLIMETER,      /* mm */
    SAC_LENGTH_POINT,           /* pt */
    SAC_LENGTH_PICA,            /* pc */

    /* Percentages */
    SAC_PERCENTAGE,
    /* URI */
    SAC_URI,
    /* Counters */
    SAC_COUNTER_FUNCTION, SAC_COUNTERS_FUNCTION,
    /* RGB Colors */
    SAC_RGBCOLOR,               /* rgb(0, 0, 0) and #000 #000000 */
    /* Angles */
    SAC_DEGREE, SAC_GRADIAN, SAC_RADIAN,
    /* Times */
    SAC_MILLISECOND, SAC_SECOND,
    /* Frequencies */
    SAC_HERTZ, SAC_KILOHERTZ,
    /* Misc */
    SAC_IDENT,                  /* any ident except inherit ! */
    SAC_STRING_VALUE, SAC_ATTR, /* attribute */
    SAC_RECT_FUNCTION,          /* rect shape function */
    SAC_UNICODERANGE,
    /* sub expressions */
    SAC_SUB_EXPRESSION,         /* (a) (a + b) (normal/none) */
    /* Unknown values */
    SAC_FUNCTION,               /* unknown function */
    SAC_DIMENSION               /* unknown dimension */
} SAC_CSSValueType;

/**
 * struct for the parsed propertys' value
 *
 * case: p { font-size: 12px; color: green;}
 *      while the css parser parse this rule, the value of the 'font-size' and '12px' be saved
 *  into this term struct, and  be added into a SAC_Expr (as a common array) for css_sac callback's
 *  use
 */
typedef CommonArray SAC_Expr;
typedef struct _SAC_Term SAC_Term;

void termDestructor(SAC_Term *term);
/* operation macros for the  SAC_Expr */
#define SAC_expr_create()       commonArrayNew(1, sizeof(SAC_Term), COMMON_ARRAY_GROW_BY_ADD, (CommonArrayElementDestructor)termDestructor)
#define SAC_expr_create_no_cb()       commonArrayNew(1, sizeof(SAC_Term), COMMON_ARRAY_GROW_BY_ADD, NULL)
#define SAC_expr_destroy(expr)  commonArrayDestroy(&expr)

typedef struct _SAC_Function SAC_Function;

struct _SAC_Function{
    int8_t * funcName;
    SAC_Expr * param;
};

typedef struct _SAC_CSSValue SAC_CSSValue;

struct _SAC_CSSValue {
    SAC_CSSValueType cssValueType;

    //union {
        /* SAC_RGBCOLOR */
        int32_t intValue;

        /* SAC_REAL */
        float floatValue;

        int8_t *strValue;

        /* signed */
        /* SAC_COUNTER_FUNCTION */
        /* SAC_COUNTERS_FUNCTION */

        /* SAC_FUNCTION */
        SAC_Function funcValue;

        /* SAC_RECT_FUNCTION */
    //};
};

#ifdef __cplusplus
}
#endif
#endif                          /* _CSS_VALUE_H_ */
