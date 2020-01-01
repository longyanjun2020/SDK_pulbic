
#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * FOR UNIT
 * for eg: 2cm's unit is CSS_PROP_VALUE_UNIT_CM
 */

typedef enum _CSS_PropertyValueUnit {
    CSS_PROP_VALUE_UNIT_ERROR = -1,
    CSS_PROP_VALUE_UNIT_NONE, /* After the '0' length, the unit identifier is optional. */
    CSS_PROP_VALUE_UNIT_EM,
    CSS_PROP_VALUE_UNIT_EX,
    CSS_PROP_VALUE_UNIT_PX,
    CSS_PROP_VALUE_UNIT_IN,
    CSS_PROP_VALUE_UNIT_CM,
    CSS_PROP_VALUE_UNIT_MM,
    CSS_PROP_VALUE_UNIT_PT,
    CSS_PROP_VALUE_UNIT_PC,
    CSS_PROP_VALUE_UNIT_HZ,
    CSS_PROP_VALUE_UNIT_KHZ,
    CSS_PROP_VALUE_UNIT_DEG,
    CSS_PROP_VALUE_UNIT_GRAD,
    CSS_PROP_VALUE_UNIT_RAD,
    CSS_PROP_VALUE_UNIT_S,
    CSS_PROP_VALUE_UNIT_MS,
}CSS_PropertyValueUnit;

/**
 * the style for struct _CSS_Property.property, get/set by *_PROP_VALUE_TYPE
 */
typedef enum _CSS_PropertyValueType {
/* common value type */
    CSS_PROP_VALUE_TYPE_ERROR = -1,
    CSS_PROP_VALUE_TYPE_NONE,
    CSS_PROP_VALUE_TYPE_HAVE_EXTENSION,
    CSS_PROP_VALUE_TYPE_USER_AGENT_DEPENDENT,   /**< depends on user agent's value*/
    CSS_PROP_VALUE_TYPE_UNSPECIFY,  /**< the author don't specify in shorthand.
                                     * ref: http://www.w3.org/TR/REC-CSS2/box.html#propdef-border-top-color
                                     */
    CSS_PROP_VALUE_TYPE_NORMAL,
    CSS_PROP_VALUE_TYPE_COLOR,
    CSS_PROP_VALUE_TYPE_TRANSPARENT,
    CSS_PROP_VALUE_TYPE_LENGTH,
    CSS_PROP_VALUE_TYPE_PERCENTAGE,
    CSS_PROP_VALUE_TYPE_INTEGER,
    CSS_PROP_VALUE_TYPE_STRING,
    CSS_PROP_VALUE_TYPE_AUTO,
    CSS_PROP_VALUE_TYPE_MEDIUM,
    CSS_PROP_VALUE_TYPE_URI,
    CSS_PROP_VALUE_TYPE_HIDDEN,
    CSS_PROP_VALUE_TYPE_TOP,
    CSS_PROP_VALUE_TYPE_CENTER,
    CSS_PROP_VALUE_TYPE_BOTTOM,
    CSS_PROP_VALUE_TYPE_LEFT,
    CSS_PROP_VALUE_TYPE_RIGHT,
    CSS_PROP_VALUE_TYPE_MIDDLE,
    CSS_PROP_VALUE_TYPE_SCROLL,
    CSS_PROP_VALUE_TYPE_INHERIT,

/**
 * sub types for CSS_PROPERTY_BACKGROUND_REPEAT
 */
    CSS_PROP_REPEAT_TYPE_REPEAT,
    CSS_PROP_REPEAT_TYPE_REPEAT_X,
    CSS_PROP_REPEAT_TYPE_REPEAT_Y,
    CSS_PROP_REPEAT_TYPE_NO_REPEAT,

/**
 * sub types for CSS_PROPERTY_BACKGROUND_ATTACHMENT
 */
    CSS_PROP_ATTACHMENT_TYPE_FIXED,

/**
 * sub types for CSS_PROPERTY_BACKGROUND_POSITION
 */
    CSS_PROP_BACKGROUND_POSITION_TYPE_PERCENTAGE,
    CSS_PROP_BACKGROUND_POSITION_TYPE_LENGTH,

    /* FOR FONT_SIZE */
    CSS_PROP_FONT_SIZE_ABSOLUTE,
    CSS_PROP_FONT_SIZE_ABSOLUTE_XX_SMALL,
    CSS_PROP_FONT_SIZE_ABSOLUTE_X_SMALL,
    CSS_PROP_FONT_SIZE_ABSOLUTE_SMALL,
    CSS_PROP_FONT_SIZE_ABSOLUTE_LARGE,
    CSS_PROP_FONT_SIZE_ABSOLUTE_X_LARGE,
    CSS_PROP_FONT_SIZE_ABSOLUTE_XX_LARGE,
    CSS_PROP_FONT_SIZE_RELATIVE,
    CSS_PROP_FONT_SIZE_RELATIVE_SMALLER,
    CSS_PROP_FONT_SIZE_RELATIVE_LARGER,

    /* FOR FONT_STYLE */
    CSS_PROP_FONT_STYLE_ITALIC,
    CSS_PROP_FONT_STYLE_OBLIQUE,

    /* FOR FONT_WEIGHT */
    CSS_PROP_FONT_WEIGHT_BOLD,
    CSS_PROP_FONT_WEIGHT_BOLDER,
    CSS_PROP_FONT_WEIGHT_LIGHTER,
    CSS_PROP_FONT_WEIGHT_100,
    CSS_PROP_FONT_WEIGHT_200,
    CSS_PROP_FONT_WEIGHT_300,
    CSS_PROP_FONT_WEIGHT_400,
    CSS_PROP_FONT_WEIGHT_500,
    CSS_PROP_FONT_WEIGHT_600,
    CSS_PROP_FONT_WEIGHT_700,
    CSS_PROP_FONT_WEIGHT_800,
    CSS_PROP_FONT_WEIGHT_900,

    /* FOR FONT_FAMILY */
    CSS_PROP_FONT_FAMILY_SERIF,
    CSS_PROP_FONT_FAMILY_SANS_SERIF,
    CSS_PROP_FONT_FAMILY_CURSIVE,
    CSS_PROP_FONT_FAMILY_FANTASY,
    CSS_PROP_FONT_FAMILY_MONOSPACE,
    CSS_PROP_FONT_FAMILY_USER_DEFINE,

    /* FOR FONT_VARIANT */
    CSS_PROP_FONT_VARIANT_SMALLCAPS,

    /* FOR FONT_VARIANT */
    /* FOR BOARDER-WIDTH */
    CSS_PROP_BORDER_WIDTH_THIN,
    CSS_PROP_BORDER_WIDTH_THICK,

    /* FOR BOARDER-STYLE */
    CSS_PROP_BORDER_STYLE_DOTTED,
    CSS_PROP_BORDER_STYLE_DASHED,
    CSS_PROP_BORDER_STYLE_SOLID,
    CSS_PROP_BORDER_STYLE_DOUBLE,
    CSS_PROP_BORDER_STYLE_GROOVE,
    CSS_PROP_BORDER_STYLE_RIDGE,
    CSS_PROP_BORDER_STYLE_INSET,
    CSS_PROP_BORDER_STYLE_OUTSET,

    /* FOR LIST-STYLE-TYPE */
    CSS_PROP_LIST_STYLE_TYPE_DISC,
    CSS_PROP_LIST_STYLE_TYPE_CIRCLE,
    CSS_PROP_LIST_STYLE_TYPE_SQUARE,
    CSS_PROP_LIST_STYLE_TYPE_DECIMAL,
    CSS_PROP_LIST_STYLE_TYPE_DECIMAL_LEADING_ZERO,
    CSS_PROP_LIST_STYLE_TYPE_LOWER_ROMAN,
    CSS_PROP_LIST_STYLE_TYPE_UPPER_ROMAN,
    CSS_PROP_LIST_STYLE_TYPE_LOWER_GREEK,
    CSS_PROP_LIST_STYLE_TYPE_LOWER_ALPHA,
    CSS_PROP_LIST_STYLE_TYPE_LOWER_LATIN,
    CSS_PROP_LIST_STYLE_TYPE_UPPER_ALPHA,
    CSS_PROP_LIST_STYLE_TYPE_UPPER_LATIN,
    CSS_PROP_LIST_STYLE_TYPE_HEBREW,
    CSS_PROP_LIST_STYLE_TYPE_ARMENIAN,
    CSS_PROP_LIST_STYLE_TYPE_GEORGIAN,
    CSS_PROP_LIST_STYLE_TYPE_CJK_IDEOGRAPHIC,
    CSS_PROP_LIST_STYLE_TYPE_HIRAGANA,
    CSS_PROP_LIST_STYLE_TYPE_KATAKANA,
    CSS_PROP_LIST_STYLE_TYPE_HIRAGANA_IROHA,
    CSS_PROP_LIST_STYLE_TYPE_KATAKANA_IROHA,

    /* FOR LIST-STYLE-POSITION */
    CSS_PROP_LIST_STYLE_POSITION_INSIDE,
    CSS_PROP_LIST_STYLE_POSITION_OUTSIDE,

    /* FOR TEXT-ALIGN */
    CSS_PROP_TEXT_ALIGN_JUSTIFY,

    /* FOR TEXT-TRANSFORM */
    CSS_PROP_TEXT_TRANSFORM_CAPITALIZE,
    CSS_PROP_TEXT_TRANSFORM_UPPERCASE,
    CSS_PROP_TEXT_TRANSFORM_LOWERCASE,

    /* FOR TEXT-DECORATION */
    CSS_PROP_TEXT_DECORATION_UNDERLINE,
    CSS_PROP_TEXT_DECORATION_OVERLINE,
    CSS_PROP_TEXT_DECORATION_LINE_THROUGH,
    CSS_PROP_TEXT_DECORATION_BLINK,

    /* FOR VISIBILITY */
    CSS_PROP_VISIBILITY_VISIBLE,
    CSS_PROP_VISIBILITY_COLLAPSE,

    /* FOR CLEAR */
    CSS_PROP_CLEAR_TYPE_BOTH,

    /* FOR VERTICAL-ALIGN */
    CSS_PROP_VERTICAL_ALIGN_BASELINE,
    CSS_PROP_VERTICAL_ALIGN_SUB,
    CSS_PROP_VERTICAL_ALIGN_SUPER,
    CSS_PROP_VERTICAL_ALIGN_TEXT_TOP,
    CSS_PROP_VERTICAL_ALIGN_TEXT_BOTTOM,

    /* FOR DISPLAY */
    CSS_PROP_DISPLAY_INLINE,
    CSS_PROP_DISPLAY_BLOCK,
    CSS_PROP_DISPLAY_LIST_ITEM,
    CSS_PROP_DISPLAY_RUN_IN,
    CSS_PROP_DISPLAY_COMPACT,
    CSS_PROP_DISPLAY_MARKER,
    CSS_PROP_DISPLAY_TABLE,
    CSS_PROP_DISPLAY_INLINE_TABLE,
    CSS_PROP_DISPLAY_TABLE_ROW_GROUP,
    CSS_PROP_DISPLAY_TABLE_HEADER_GROUP,
    CSS_PROP_DISPLAY_TABLE_FOOTER_GROUP,
    CSS_PROP_DISPLAY_TABLE_ROW,
    CSS_PROP_DISPLAY_TABLE_COLUMN_GROUP,
    CSS_PROP_DISPLAY_TABLE_COLUMN,
    CSS_PROP_DISPLAY_TABLE_CELL,
    CSS_PROP_DISPLAY_TABLE_CAPTION,
    CSS_PROP_DISPLAY_WAP_MARQUEE,

    /* FOR WHITE SPACE*/
    CSS_PROP_WHITE_SPACE_TYPE_PRE,
    CSS_PROP_WHITE_SPACE_TYPE_NOWRAP,

    /* WAP Extension */
    /* Marquee dir */
    CSS_PROP_WAP_MARQUEE_DIR_TYPE_LTR,
    CSS_PROP_WAP_MARQUEE_DIR_TYPE_RTL,

    /* Marquee Loop */
    CSS_PROP_WAP_MARQUEE_LOOP_TYPE_INFINITE,

    /* Marquee style */
    CSS_PROP_WAP_MARQUEE_STYLE_SLIDE,
    CSS_PROP_WAP_MARQUEE_STYLE_ALTERNATE,

    /* Marquee speed */
    CSS_PROP_WAP_MARQUEE_SPEED_SLOW,
    CSS_PROP_WAP_MARQUEE_SPEED_FAST,

    /* -wap-input-format */
    CSS_PROP_WAP_INPUT_REQUIRED_TYPE_TRUE,
    CSS_PROP_WAP_INPUT_REQUIRED_TYPE_FALSE,

} CSS_PropertyValueType;

typedef enum _TextDecorationStyle{
    TEXT_DECORATION_STYLE_UNDERLINE = 1,
    TEXT_DECORATION_STYLE_OVERLINE = 2,
    TEXT_DECORATION_STYLE_LINE_THROUGH = 4,
    TEXT_DECORATION_STYLE_BLINK = 8,
}TextDecorationStyle;

#define  TEXT_DECORATION_INIT_STYLE(_dst)           ((_dst) = 0)
#define  TEXT_DECORATION_ADD_STYLE(_dst, _style)    ((_dst) |= (_style))
#define  TEXT_DECORATION_HAVE_STYLE(_dst, _style)   ((_dst) & (_style))
/**
 * for eg: background-position: left  2cm
 * the left's infomation is saved as :
 *          type    = CSS_PROP_VALUE_TYPE_LEFT
 *          unit    (not used)
 *          value   (not used)
 * the 2cm's infomation is saved as :
 *          type    = CSS_PROP_BACKGROUND_POSITION_TYPE_LENGTH
 *          unit    = CSS_PROP_VALUE_UNIT_CM
 *          value   = 2
 */
typedef struct _CSS_PositionValue {
    int8_t type;
    int8_t unit;
    int16_t value;
} CSS_PositionValue;

/* see CSS_PositionValue*/
typedef struct _CSS_Position {
    CSS_PositionValue x;
    CSS_PositionValue y;
} CSS_Position;

/**
 * CSS property struct
 *
 * case: p{ background: green url("./jpg")},
 * the converted 'background' will be stored into property
 * the green and url value will be stored into the union
 */
//typedef struct _CSS_Property CSS_Property;
struct _CSS_Property {
    uint32_t property;

    //union {
        float   floatValue;
        int32_t intValue;
        void *pextend;
    //};
};

/**
 * A container which contains properties
 */
typedef CommonArray CSS_PropertyContainer;

#define CSS_PROP_NAME_MASK                                   0xff000000
#define CSS_PROP_UNIT_MASK                                   0x00ff0000
/* for !important rule */
#define CSS_PROP_PRIO_MASK                                   0x00008000
/* for cascading rule, see spec.6.4 */
#define CSS_PROP_ORIGIN_MASK                                 0x00006000
#define CSS_PROP_VALUE_TYPE_MASK                             0x00000fff

/**
 * Get the name key of property.
 */
#define GET_PROP_NAME_KEY(a)                                (((a) & CSS_PROP_NAME_MASK) >> 24)

/**
 * Set the name key of property.
 */
#define SET_PROP_NAME_KEY(dst, src)                         ((dst) = ((((src) << 24) & CSS_PROP_NAME_MASK)|((dst) & ~CSS_PROP_NAME_MASK)))

/**
 * Get the unit key of property.
 */
#define GET_PROP_UNIT_KEY(a)                                (((a) & CSS_PROP_UNIT_MASK) >> 16)

/**
 * Set the unit key of property.
 */
#define SET_PROP_UNIT_KEY(dst, src)                         ((dst) = ((((src) << 16) & CSS_PROP_UNIT_MASK)|((dst) & ~CSS_PROP_UNIT_MASK)))

/**
 * Get the prio key of property.
 */
#define GET_PROP_PRIO_KEY(a)                                (((a) & CSS_PROP_PRIO_MASK) >> 15)

/**
 * Set the prio key of property.
 */
#define SET_PROP_PRIO_KEY(dst, src)                         ((dst) = ((((src) << 15) & CSS_PROP_PRIO_MASK)|((dst) & ~CSS_PROP_PRIO_MASK)))

/**
 * Get the value key of property.
 */
#define GET_PROP_VALUE_TYPE(a)                              ((a) & CSS_PROP_VALUE_TYPE_MASK)

/**
 * Get the value key of property.
 */
#define SET_PROP_VALUE_TYPE(dst,src)                        ((dst) = (((src) & CSS_PROP_VALUE_TYPE_MASK)|((dst) & ~CSS_PROP_VALUE_TYPE_MASK)))

/**
 * Set the origin key of property
 */
#define SET_PROP_ORIGIN_KEY(_dst_, _key_)                   ((_dst_) = ( (((_key_) << 13) & CSS_PROP_ORIGIN_MASK) | ((_dst_) & ~CSS_PROP_ORIGIN_MASK)) )

/**
 * Get the origin key of property
 */
#define GET_PROP_ORIGIN_KEY(_a_)                            (((_a_) & CSS_PROP_ORIGIN_MASK) >> 13)

/**
 * The Origin of CSS Property.
 * See CSS2 spec. 6.4 for more detail
 */
typedef enum _CSS_PropertyOrigin {
    CSS_PROPERTY_ORIGIN_UNKNOW = 0,
    CSS_PROPERTY_ORIGIN_UA,             /* it comes from a user agent */
    CSS_PROPERTY_ORIGIN_USER,           /* user specify */
    CSS_PROPERTY_ORIGIN_AUTHOR          /* comes from author */
} CSS_PropertyOrigin ;

/**
 * The name key of CSS property.
 */
typedef enum _CSS_PropertyNameType {
    CSS_PROPERTY_UNKNOWN = 0,
    CSS_PROPERTY_COLOR,         /* =color */    /* The order of CSS_PROPERTY_COLOR is risen because some other properties' default value, such as CSS_BORDER_COLOR
                                                 * depend on the value of this property, so it must be assigned before other properties which
                                                 * depond on it in the cycle of assignment, more detail please see CSS2 spec 8.5.4 */
    CSS_PROPERTY_AZIMUTH,   /* =azimuth */
    CSS_PROPERTY_BACKGROUND,    /* =background */
    CSS_PROPERTY_BACKGROUND_ATTACHMENT, /* =background-attachment */
    CSS_PROPERTY_BACKGROUND_COLOR,      /* =background-color */
    CSS_PROPERTY_BACKGROUND_IMAGE,      /* =background-image */
    CSS_PROPERTY_BACKGROUND_POSITION,   /* =background-position */
    CSS_PROPERTY_BACKGROUND_REPEAT,     /* =background-repeat */
    CSS_PROPERTY_BORDER,        /* =border */
    CSS_PROPERTY_BORDER_COLLAPSE,       /* =border-collapse */
    CSS_PROPERTY_BORDER_SPACING,        /* =border-spacing */
    CSS_PROPERTY_BORDER_STYLE,  /* =border-style */
    CSS_PROPERTY_BORDER_WIDTH,  /* =border-width */
    CSS_PROPERTY_BORDER_COLOR,  /* =border-color */
    CSS_PROPERTY_BORDER_TOP,    /* =border-top */
    CSS_PROPERTY_BORDER_RIGHT,  /* =border-right */
    CSS_PROPERTY_BORDER_BOTTOM, /* =border-bottom */
    CSS_PROPERTY_BORDER_LEFT,   /* =border-left */
    CSS_PROPERTY_BORDER_TOP_COLOR,      /* =border-top-color */
    CSS_PROPERTY_BORDER_RIGHT_COLOR,    /* =border-right-color */
    CSS_PROPERTY_BORDER_BOTTOM_COLOR,   /* =border-bottom-color */
    CSS_PROPERTY_BORDER_LEFT_COLOR,     /* =border-left-color */
    CSS_PROPERTY_BORDER_TOP_STYLE,      /* =border-top-style */
    CSS_PROPERTY_BORDER_RIGHT_STYLE,    /* =border-right-style */
    CSS_PROPERTY_BORDER_BOTTOM_STYLE,   /* =border-bottom-style */
    CSS_PROPERTY_BORDER_LEFT_STYLE,     /* =border-left-style */
    CSS_PROPERTY_BORDER_TOP_WIDTH,      /* =border-top-width */
    CSS_PROPERTY_BORDER_RIGHT_WIDTH,    /* =border-right-width */
    CSS_PROPERTY_BORDER_BOTTOM_WIDTH,   /* =border-bottom-width */
    CSS_PROPERTY_BORDER_LEFT_WIDTH,     /* =border-left-width */
    CSS_PROPERTY_BOTTOM,        /* =bottom */
    CSS_PROPERTY_CAPTION_SIDE,  /* =caption-side */
    CSS_PROPERTY_CLEAR,         /* =clear */
    CSS_PROPERTY_CLIP,          /* =clip */
    CSS_PROPERTY_CONTENT,       /* =content */
    CSS_PROPERTY_COUNTER_INCREMENT,     /* =counter-increment */
    CSS_PROPERTY_COUNTER_RESET, /* =counter-reset */
    CSS_PROPERTY_CUE,           /* =cue */
    CSS_PROPERTY_CUE_AFTER,     /* =cue-after */
    CSS_PROPERTY_CUE_BEFORE,    /* =cue-before */
    CSS_PROPERTY_CURSOR,        /* =cursor */
    CSS_PROPERTY_DIRECTION,     /* =direction */
    CSS_PROPERTY_DISPLAY,       /* =display */
    CSS_PROPERTY_ELEVATION,     /* =elevation */
    CSS_PROPERTY_EMPTY_CELLS,   /* =empty-cells */
    CSS_PROPERTY_FLOAT,         /* =float */
    CSS_PROPERTY_FONT,          /* =font */
    CSS_PROPERTY_FONT_FAMILY,   /* =font-family */
    CSS_PROPERTY_FONT_SIZE,     /* =font-size */
    CSS_PROPERTY_FONT_SIZE_ADJUST,      /* =font-size-adjust */
    CSS_PROPERTY_FONT_STRETCH,  /* =font-stretch */
    CSS_PROPERTY_FONT_STYLE,    /* =font-style */
    CSS_PROPERTY_FONT_VARIANT,  /* =font-variant */
    CSS_PROPERTY_FONT_WEIGHT,   /* =font-weight */
    CSS_PROPERTY_HEIGHT,        /* =height */
    CSS_PROPERTY_LEFT,          /* =left */
    CSS_PROPERTY_LETTER_SPACING,        /* =letter-spacing */
    CSS_PROPERTY_LINE_HEIGHT,   /* =line-height */
    CSS_PROPERTY_LIST_STYLE,    /* =list-style */
    CSS_PROPERTY_LIST_STYLE_IMAGE,      /* =list-style-image */
    CSS_PROPERTY_LIST_STYLE_POSITION,   /* =list-style-position */
    CSS_PROPERTY_LIST_STYLE_TYPE,       /* =list-style-type */
    CSS_PROPERTY_MARGIN,        /* =margin */
    CSS_PROPERTY_MARGIN_TOP,    /* =margin-top */
    CSS_PROPERTY_MARGIN_RIGHT,  /* =margin-right */
    CSS_PROPERTY_MARGIN_BOTTOM, /* =margin-bottom */
    CSS_PROPERTY_MARGIN_LEFT,   /* =margin-left */
    CSS_PROPERTY_MARKER_OFFSET, /* =marker-offset */
    CSS_PROPERTY_MARKS,         /* =marks */
    CSS_PROPERTY_MAX_HEIGHT,    /* =max-height */
    CSS_PROPERTY_MAX_WIDTH,     /* =max-width */
    CSS_PROPERTY_MIN_HEIGHT,    /* =min-height */
    CSS_PROPERTY_MIN_WIDTH,     /* =min-width */
    CSS_PROPERTY_ORPHANS,       /* =orphans */
    CSS_PROPERTY_OUTLINE,       /* =outline */
    CSS_PROPERTY_OUTLINE_COLOR, /* =outline-color */
    CSS_PROPERTY_OUTLINE_STYLE, /* =outline-style */
    CSS_PROPERTY_OUTLINE_WIDTH, /* =outline-width */
    CSS_PROPERTY_OVERFLOW,      /* =overflow */
    CSS_PROPERTY_PADDING,       /* =padding */
    CSS_PROPERTY_PADDING_TOP,   /* =padding-top */
    CSS_PROPERTY_PADDING_RIGHT, /* =padding-right */
    CSS_PROPERTY_PADDING_BOTTOM,        /* =padding-bottom */
    CSS_PROPERTY_PADDING_LEFT,  /* =padding-left */
    CSS_PROPERTY_PAGE,          /* =page */
    CSS_PROPERTY_PAGE_BREAK_AFTER,      /* =page-break-after */
    CSS_PROPERTY_PAGE_BREAK_BEFORE,     /* =page-break-before */
    CSS_PROPERTY_PAGE_BREAK_INSIDE,     /* =page-break-inside */
    CSS_PROPERTY_PAUSE,         /* =pause */
    CSS_PROPERTY_PAUSE_AFTER,   /* =pause-after */
    CSS_PROPERTY_PAUSE_BEFORE,  /* =pause-before */
    CSS_PROPERTY_PITCH,         /* =pitch */
    CSS_PROPERTY_PITCH_RANGE,   /* =pitch-range */
    CSS_PROPERTY_PLAY_DURING,   /* =play-during */
    CSS_PROPERTY_POSITION,      /* =position */
    CSS_PROPERTY_QUOTES,        /* =quotes */
    CSS_PROPERTY_RICHNESS,      /* =richness */
    CSS_PROPERTY_RIGHT,         /* =right */
    CSS_PROPERTY_SIZE,          /* =size */
    CSS_PROPERTY_SPEAK,         /* =speak */
    CSS_PROPERTY_SPEAK_HEADER,  /* =speak-header */
    CSS_PROPERTY_SPEAK_NUMERAL, /* =speak-numeral */
    CSS_PROPERTY_SPEAK_PUNCTUATION,     /* =speak-punctuation */
    CSS_PROPERTY_SPEECH_RATE,   /* =speech-rate */
    CSS_PROPERTY_STRESS,        /* =stress */
    CSS_PROPERTY_TABLE_LAYOUT,  /* =table-layout */
    CSS_PROPERTY_TEXT_ALIGN,    /* =text-align */
    CSS_PROPERTY_TEXT_DECORATION,       /* =text-decoration */
    CSS_PROPERTY_TEXT_INDENT,   /* =text-indent */
    CSS_PROPERTY_TEXT_SHADOW,   /* =text-shadow */
    CSS_PROPERTY_TEXT_TRANSFORM,        /* =text-transform */
    CSS_PROPERTY_TOP,           /* =top */
    CSS_PROPERTY_UNICODE_BIDI,  /* =unicode-bidi */
    CSS_PROPERTY_VERTICAL_ALIGN,        /* =vertical-align */
    CSS_PROPERTY_VISIBILITY,    /* =visibility */
    CSS_PROPERTY_VOICE_FAMILY,  /* =voice-family */
    CSS_PROPERTY_VOLUME,        /* =volume */
    CSS_PROPERTY_WHITE_SPACE,   /* =white-space */
    CSS_PROPERTY_WIDOWS,        /* =widows */
    CSS_PROPERTY_WIDTH,         /* =width */
    CSS_PROPERTY_WORD_SPACING,  /* =word-spacing */
    CSS_PROPERTY_Z_INDEX,       /* =z-index */

    /* for wap extension*/
    CSS_PROPERTY_WAP_MARQUEE_DIR,       /* -wap-marquee-dir */
    CSS_PROPERTY_WAP_MARQUEE_LOOP,      /* -wap-marquee-loop */
    CSS_PROPERTY_WAP_MARQUEE_STYLE,     /* -wap-marquee-style */
    CSS_PROPERTY_WAP_MARQUEE_SPEED,     /* -wap-marquee-speed */
    CSS_PROPERTY_WAP_INPUT_REQUIRED,    /* -wap-input-required */
    CSS_PROPERTY_WAP_INPUT_FORMAT,      /* -wap-input-format */

    CSS_PROPERTY_NUM_OF_PROPERTIES,  /* total number */
} CSS_PropertyNameType;

/* FOR COLOR */
typedef enum _CSSColorType{
     CSS_PROP_COLOR_UNKNOWN   =    0xFF000000,
     CSS_PROP_COLOR_AQUA      =    0x00FFFF,
     CSS_PROP_COLOR_BLACK     =    0x000000,
     CSS_PROP_COLOR_BLUE      =    0x0000FF,
     CSS_PROP_COLOR_FUCHSIA   =    0xFF00FF,
     CSS_PROP_COLOR_GRAY      =    0x808080,
     CSS_PROP_COLOR_GREEN     =    0x008000,
     CSS_PROP_COLOR_LIME      =    0x00FF00,
     CSS_PROP_COLOR_MAROON    =    0x800000,
     CSS_PROP_COLOR_NAVY      =    0x000080,
     CSS_PROP_COLOR_OLIVE     =    0x808000,
     CSS_PROP_COLOR_ORANGE    =    0xFFA500,
     CSS_PROP_COLOR_PURPLE    =    0x800080,
     CSS_PROP_COLOR_RED       =    0xFF0000,
     CSS_PROP_COLOR_SILVER    =    0xC0C0C0,
     CSS_PROP_COLOR_TEAL      =    0x008080,
     CSS_PROP_COLOR_WHITE     =    0xFFFFFF,
     CSS_PROP_COLOR_YELLOW    =    0xFFFF00,
}CSSColorType;

/**
 * get the enum property name key by the name string
 * \param str name string
 * \return enum property name key
 */
//int32_t CSS_propertyNameToKey(const int8_t * str);  //

/**
 * get the color value by name
 * \param str color name
 * \return color value
 */
int32_t css_getColorValue(const int8_t * str);

/**
 * get the property value by property value string
 *
 * \param str property value string
 *
 * \return color value
 */
CSS_PropertyValueType CSS_propertyValueNameToType(const int8_t * str);

typedef CommonArray CSS_PropertyArray;
/**
 * set property value
 * \param cssPropertyArray output point
 * \param propNameKey property name key
 * \param cssExpr value array
 * \return TRUE set declarations success
 *         FALSE set failed
 */
int32_t CSS_propertyArray_SetValues(
                                    CSS_PropertyArray * cssPropertyArray,
                                    CSS_PropertyNameType propNameKey,
                                    const SAC_Expr * cssExpr);

/**
 * Destroy the members of property. It's a destructor for common array.
 * \param property property to be destroyed
 * \return void
 */
void CSS_Property_destructor(CSS_Property * property);

/**
 * Create a property container.
 * \param void
 * \return
 *      Pointer of a new property container when success
 *      NULL when failure
 */
CSS_PropertyContainer *CSS_PropertyContainer_create();

/**
 * Destroy the given property container
 * \param container property container to be destroyed
 * \return void
 */
void CSS_PropertyContainer_destroy(CSS_PropertyContainer ** container);

/**
 * Get next property from the property container, the second parameter indicate the current position
 * \param container the pointer of property container
 * \param current current property, NULL means the first
 * \return
 *      Pointer of the next property when success
 *      NULL indicate end of property container
 */
extern NCC_INLINE const CSS_Property *CSS_PropertyContainer_getNextProperty(
    const CSS_PropertyContainer * container,
    const CSS_Property * current);

/**
 * Duplicate a group of properties and put them into property container. The function should be called
 * only once for each new container, otherwise the functions will be faild.
 * \param container the pointer of property container
 * \param properties the pointer of properties to be duplicate
 * \param size size of properties
 * \return
 *      FLASE for failure
 *      TRUE for success
 */
uint32_t CSS_PropertyContainer_fill(
                                  CSS_PropertyContainer * container,
                                  const CSS_Property * properties,
                                  int32_t size);

/**
 * compare two float numbers if them equal.
 * \param a the first float number.
 * \param b the secodn float number.
 * \return
 *      FLASE for failure
 *      TRUE for success
 */
int32_t CSS_floatIsEqual(float a, float b);

/**
 * destructor for css property
 *
 * \param void *, pointer to the property
 * \return void
 */
void CSS_property_destructor(CSS_Property *property);

#ifdef __cplusplus
}
#endif
#endif                          /* __PROPERTY_H__ */
