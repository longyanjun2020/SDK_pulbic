
/**
 * @file
 *  Tags define
 */

#ifndef  _DBA_TAGATTRLISTS_H_
#define _DBA_TAGATTRLISTS_H_

#include <ncc_types.h>
#include <ctype.h>

#define IsNmStart(c) (isalpha((uint8_t)c))

/** Pyramid and Mips can't uppercase non-alpha */
#define TOLOWER(c) (CRTL_isupper((uint8_t)c) ? CRTL_tolower((uint8_t)c) : ((uint8_t)c))
#define TOUPPER(c) (CRTL_islower((uint8_t)c) ? CRTL_toupper((uint8_t)c) : ((uint8_t)c))

#ifdef __cplusplus
extern "C" {
#endif

    /*       Element Numbers    */
    /* Must Match all tables by element! */
    typedef enum _HTMLElement {
        DBA_HTML_A,//0
            DBA_HTML_ABBREV,
            DBA_HTML_ACRONYM,
            DBA_HTML_ADDRESS,
            DBA_HTML_APPLET,
            DBA_HTML_AREA,
            DBA_HTML_AU,
            DBA_HTML_AUTHOR,
            DBA_HTML_B,
            DBA_HTML_BANNER,
            DBA_HTML_BASE,//10
            DBA_HTML_BASEFONT,
            DBA_HTML_BDO,
            DBA_HTML_BGSOUND,
            DBA_HTML_BIG,
            DBA_HTML_BLINK,
            DBA_HTML_BLOCKQUOTE,
            DBA_HTML_BODY,
            DBA_HTML_BODYTEXT,
            DBA_HTML_BQ,
            DBA_HTML_BR,//20
            DBA_HTML_BUTTON,
            DBA_HTML_CAPTION,
            DBA_HTML_CENTER,
            DBA_HTML_CITE,
            DBA_HTML_CODE,
            DBA_HTML_COL,
            DBA_HTML_COLGROUP,
            DBA_HTML_COMMENT,
            DBA_HTML_CREDIT,
            DBA_HTML_DD,//30
            DBA_HTML_DEL,
            DBA_HTML_DFN,
            DBA_HTML_DIR,
            DBA_HTML_DIV,
            DBA_HTML_DL,
            DBA_HTML_DLC,
            DBA_HTML_DT,
            DBA_HTML_EM,
            DBA_HTML_EMBED,
            DBA_HTML_FIELDSET,//40
            DBA_HTML_FIG,
            DBA_HTML_FN,
            DBA_HTML_FONT,
            DBA_HTML_FORM,
            DBA_HTML_FRAME,
            DBA_HTML_FRAMESET,
            DBA_HTML_H1,
            DBA_HTML_H2,
            DBA_HTML_H3,
            DBA_HTML_H4,//50
            DBA_HTML_H5,
            DBA_HTML_H6,
            DBA_HTML_HEAD,
            DBA_HTML_HR,
            DBA_HTML_HTML,
            DBA_HTML_HY,
            DBA_HTML_I,
            DBA_HTML_IFRAME,
            DBA_HTML_IMG,
            DBA_HTML_INPUT,//60
            DBA_HTML_INPUTPAGE,
            DBA_HTML_INS,
            DBA_HTML_ISINDEX,
            DBA_HTML_KBD,
            DBA_HTML_KEYGEN,
            DBA_HTML_LABEL,
            DBA_HTML_LEGEND,
            DBA_HTML_LH,
            DBA_HTML_LI,
            DBA_HTML_LINK,//70
            DBA_HTML_LISTING,
            DBA_HTML_MAP,
            DBA_HTML_MARQUEE,
            DBA_HTML_MATH,
            DBA_HTML_MENU,
            DBA_HTML_META,
            DBA_HTML_NEXTID,
            DBA_HTML_NEXTPAGE,
            DBA_HTML_NOFRAMES,
            DBA_HTML_NOSCRIPT,
            DBA_HTML_NOTE,//80
            DBA_HTML_OBJECT,
            DBA_HTML_OL,
            DBA_HTML_OPTGROUP,
            DBA_HTML_OPTION,
            DBA_HTML_OVERLAY,
            DBA_HTML_P,
            DBA_HTML_PARAM,
            DBA_HTML_PLAINTEXT,
            DBA_HTML_PRE,
            DBA_HTML_Q,
            DBA_HTML_S,//90
            DBA_HTML_SAMP,
            DBA_HTML_SCREEN,
            DBA_HTML_SCRIPT,
            DBA_HTML_SELECT,
            DBA_HTML_SHY,
            DBA_HTML_SMALL,
            DBA_HTML_SPAN,
            DBA_HTML_SPOT,
            DBA_HTML_STRIKE,
            DBA_HTML_STRONG,//100
            DBA_HTML_STYLE,
            DBA_HTML_SUB,
            DBA_HTML_SUP,
            DBA_HTML_TAB,
            DBA_HTML_TABLE,
            DBA_HTML_TBODY,
            DBA_HTML_TD,
            DBA_HTML_TEXTAREA,
            DBA_HTML_TEXTFLOW,
            DBA_HTML_TFOOT, //110
            DBA_HTML_TH,
            DBA_HTML_THEAD,
            DBA_HTML_TITLE,
            DBA_HTML_TR,
            DBA_HTML_TT,
            DBA_HTML_U,
            DBA_HTML_UL,
            DBA_HTML_VAR,
            DBA_HTML_WBR,
            DBA_HTML_XMP,//120
            DBA_HTML_ALT_OBJECT,
            DBA_HTML_DOCUMENT,
            DBA_HTML_CDATA,
            DBA_HTML_CHARACTERS,
            DBA_HTML_DELETECONTENT,
            DBA_HTML_INVALID
} T_DBA_HTMLElement;

/*************************************************************************
*  HTML_ELEMENTS:     number of elements visible to MiniBrowser code in
*                      general, alphabetic (ASCII) order.
*  HTML_ALL_ELEMENTS: number of elements visible to SGML parser,
*                     additional variant(s) at end.
*************************************************************************/
#define DBA_HTML_ALL_ELEMENTS  124

/** SGML content types */
typedef enum _SGMLContent {
    SGML_EMPTY,       /**< No content. */
    SGML_LITTERAL, /**<Literal character data.  Recognize exact close tag only.Old www server compatibility only!  Not SGML*/
    SGML_CDATA,     /**<Character data.  Recognize </ only. (But we treat it just as SGML_LITTERAL.*/
    SGML_RCDATA, /**<Replaceable character data. Should recognize </ and &ref;(but we treat it like SGML_MIXED for old times' sake).*/
    SGML_MIXED,    /**< Elements and parsed character data. Recognize all markup. */
    SGML_ELEMENT,  /**< Any data found should be regarded as an error. (But we treat it just like SGML_MIXED.)*/
    SGML_PCDATA /**<Should contain no elements but &ref; is parsed. (We treat it like SGML_CDATA wrt.
                    contained tags, i.e. pass them on literally, i.e. like we should treat SGML_RCDATA) (added by KW).*/
} T_DBA_SGMLContent;

typedef struct{
    //int8_t *    name;       /**< The (constant) name of the attribute */
	char *    name;
} attr;

/********************************************************************
*       A tag structure describes an SGML element.
*   name        is the string which comes after the tag opener "<".
*   attributes  points to a zero-terminated array of attribute names.
*   litteral    determines how the SGML engine parses the characters
*           within the element.  If set, tag openers are ignored
*           except for that which opens a matching closing tag.
********************************************************************/
typedef struct _tag  T_DBA_HTTag;

struct _tag{
    char *               name;                /**< The name of the tag */
    const attr *                 attributes;          /**< The list of acceptable attributes */
    int32_t     number_of_attributes;           /**< Number of possible attributes */
    #if 0
    T_DBA_SGMLContent      contents;            /**< End only on end tag @@ */
    int32_t tagclass,
            contains,                       /**< which classes of elements this one can contain directly */
            icontains,                      /**< which classes of elements this one can contain indirectly */
            contained,                      /**< in which classes can this tag be contained  */
            icontained,                     /**< in which classes can this tag be indirectly contained  */
            canclose;                       /**< which classes of elements can this one close
                                if something looks wrong  */
    int32_t flags;
    #endif
};

/** Attribute numbers
  Identifier is HTML_<element>_<attribute>.*/
#define DBA_HTML_A_ACCESSKEY        0
#define DBA_HTML_A_CHARSET          1 /**< i18n draft, added tentatively - KW */
#define DBA_HTML_A_CLASS            2
#define DBA_HTML_A_CLEAR            3
#define DBA_HTML_A_COORDS           4
#define DBA_HTML_A_DIR              5
#define DBA_HTML_A_HREF             6
#define DBA_HTML_A_ID               7
#define DBA_HTML_A_ISMAP            8
#define DBA_HTML_A_LANG             9
#define DBA_HTML_A_MD              10
#define DBA_HTML_A_NAME            11
#define DBA_HTML_A_NOTAB           12
#define DBA_HTML_A_ONCLICK         13
#define DBA_HTML_A_ONMOUSEOUT      14
#define DBA_HTML_A_ONMOUSEOVER     15
#define DBA_HTML_A_REL             16
#define DBA_HTML_A_REV             17
#define DBA_HTML_A_SHAPE           18
#define DBA_HTML_A_STYLE           19
#define DBA_HTML_A_TABINDEX        20
#define DBA_HTML_A_TARGET          21
#define DBA_HTML_A_TITLE           22
#define DBA_HTML_A_TYPE            23
#define DBA_HTML_A_URN             24
#define DBA_HTML_A_ATTRIBUTES      25

#define DBA_HTML_ADDRESS_CLASS      0
#define DBA_HTML_ADDRESS_CLEAR      1
#define DBA_HTML_ADDRESS_DIR        2
#define DBA_HTML_ADDRESS_ID         3
#define DBA_HTML_ADDRESS_LANG       4
#define DBA_HTML_ADDRESS_NOWRAP     5
#define DBA_HTML_ADDRESS_STYLE      6
#define DBA_HTML_ADDRESS_TITLE      7
#define DBA_HTML_ADDRESS_ATTRIBUTES 8

#define DBA_HTML_APPLET_ALIGN       0
#define DBA_HTML_APPLET_ALT         1
#define DBA_HTML_APPLET_CLASS       2
#define DBA_HTML_APPLET_CLEAR       3
#define DBA_HTML_APPLET_CODE        4
#define DBA_HTML_APPLET_CODEBASE    5
#define DBA_HTML_APPLET_DIR         6
#define DBA_HTML_APPLET_DOWNLOAD    7
#define DBA_HTML_APPLET_HEIGHT      8
#define DBA_HTML_APPLET_HSPACE      9
#define DBA_HTML_APPLET_ID         10
#define DBA_HTML_APPLET_LANG       11
#define DBA_HTML_APPLET_NAME       12
#define DBA_HTML_APPLET_STYLE      13
#define DBA_HTML_APPLET_TITLE      14
#define DBA_HTML_APPLET_VSPACE     15
#define DBA_HTML_APPLET_WIDTH      16
#define DBA_HTML_APPLET_ATTRIBUTES 17

#define DBA_HTML_AREA_ALT           0
#define DBA_HTML_AREA_CLASS         1
#define DBA_HTML_AREA_CLEAR         2
#define DBA_HTML_AREA_COORDS        3
#define DBA_HTML_AREA_DIR           4
#define DBA_HTML_AREA_HREF          5
#define DBA_HTML_AREA_ID            6
#define DBA_HTML_AREA_LANG          7
#define DBA_HTML_AREA_NOHREF        8
#define DBA_HTML_AREA_NONOTAB       9
#define DBA_HTML_AREA_ONCLICK      10
#define DBA_HTML_AREA_ONMOUSEOUT   11
#define DBA_HTML_AREA_ONMOUSEOVER  12
#define DBA_HTML_AREA_SHAPE        13
#define DBA_HTML_AREA_STYLE        14
#define DBA_HTML_AREA_TABINDEX     15
#define DBA_HTML_AREA_TARGET       16
#define DBA_HTML_AREA_TITLE        17
#define DBA_HTML_AREA_ATTRIBUTES   18

#define DBA_HTML_BASE_HREF          0
#define DBA_HTML_BASE_TARGET        1
#define DBA_HTML_BASE_TITLE         2
#define DBA_HTML_BASE_ATTRIBUTES    3

#define DBA_HTML_BGSOUND_CLASS      0
#define DBA_HTML_BGSOUND_CLEAR      1
#define DBA_HTML_BGSOUND_DIR        2
#define DBA_HTML_BGSOUND_ID         3
#define DBA_HTML_BGSOUND_LANG       4
#define DBA_HTML_BGSOUND_LOOP       5
#define DBA_HTML_BGSOUND_SRC        6
#define DBA_HTML_BGSOUND_STYLE      7
#define DBA_HTML_BGSOUND_TITLE      8
#define DBA_HTML_BGSOUND_ATTRIBUTES 9

#define DBA_HTML_BODY_ALINK         0
#define DBA_HTML_BODY_BACKGROUND    1
#define DBA_HTML_BODY_BGCOLOR       2
#define DBA_HTML_BODY_CLASS         3
#define DBA_HTML_BODY_CLEAR         4
#define DBA_HTML_BODY_DIR           5
#define DBA_HTML_BODY_ID            6
#define DBA_HTML_BODY_LANG          7
#define DBA_HTML_BODY_LINK          8
#define DBA_HTML_BODY_ONLOAD        9
#define DBA_HTML_BODY_ONUNLOAD     10
#define DBA_HTML_BODY_STYLE        11
#define DBA_HTML_BODY_TEXT         12
#define DBA_HTML_BODY_TITLE        13
#define DBA_HTML_BODY_VLINK        14
#define DBA_HTML_BODY_ATTRIBUTES   15

#define DBA_HTML_BODYTEXT_CLASS     0
#define DBA_HTML_BODYTEXT_CLEAR     1
#define DBA_HTML_BODYTEXT_DATA      2
#define DBA_HTML_BODYTEXT_DIR       3
#define DBA_HTML_BODYTEXT_ID        4
#define DBA_HTML_BODYTEXT_LANG      5
#define DBA_HTML_BODYTEXT_NAME      6
#define DBA_HTML_BODYTEXT_OBJECT    7
#define DBA_HTML_BODYTEXT_REF       8
#define DBA_HTML_BODYTEXT_STYLE     9
#define DBA_HTML_BODYTEXT_TITLE    10
#define DBA_HTML_BODYTEXT_TYPE     11
#define DBA_HTML_BODYTEXT_VALUE    12
#define DBA_HTML_BODYTEXT_VALUETYPE  13
#define DBA_HTML_BODYTEXT_ATTRIBUTES 14

#define DBA_HTML_BQ_CITE             0
#define DBA_HTML_BQ_CLASS            1
#define DBA_HTML_BQ_CLEAR            2
#define DBA_HTML_BQ_DIR              3
#define DBA_HTML_BQ_ID               4
#define DBA_HTML_BQ_LANG             5
#define DBA_HTML_BQ_NOWRAP           6
#define DBA_HTML_BQ_STYLE            7
#define DBA_HTML_BQ_TITLE            8
#define DBA_HTML_BQ_ATTRIBUTES       9

#define DBA_HTML_BUTTON_CLASS       0
#define DBA_HTML_BUTTON_CLEAR       1
#define DBA_HTML_BUTTON_DIR         2
#define DBA_HTML_BUTTON_DISABLED    3
#define DBA_HTML_BUTTON_ID          4
#define DBA_HTML_BUTTON_LANG        5
#define DBA_HTML_BUTTON_NAME        6
#define DBA_HTML_BUTTON_ONBLUR     7
#define DBA_HTML_BUTTON_ONCLICK      8
#define DBA_HTML_BUTTON_ONFOCUS     9
#define DBA_HTML_BUTTON_STYLE       10
#define DBA_HTML_BUTTON_TABINDEX   11
#define DBA_HTML_BUTTON_TITLE      12
#define DBA_HTML_BUTTON_TYPE       13
#define DBA_HTML_BUTTON_VALUE      14
#define DBA_HTML_BUTTON_ATTRIBUTES 15

#define DBA_HTML_CAPTION_ACCESSKEY  0
#define DBA_HTML_CAPTION_ALIGN      1
#define DBA_HTML_CAPTION_CLASS      2
#define DBA_HTML_CAPTION_CLEAR      3
#define DBA_HTML_CAPTION_DIR        4
#define DBA_HTML_CAPTION_ID         5
#define DBA_HTML_CAPTION_LANG       6
#define DBA_HTML_CAPTION_STYLE      7
#define DBA_HTML_CAPTION_TITLE      8
#define DBA_HTML_CAPTION_ATTRIBUTES 9

#define DBA_HTML_COL_ALIGN          0
#define DBA_HTML_COL_CHAR           1
#define DBA_HTML_COL_CHAROFF        2
#define DBA_HTML_COL_CLASS          3
#define DBA_HTML_COL_CLEAR          4
#define DBA_HTML_COL_DIR            5
#define DBA_HTML_COL_ID             6
#define DBA_HTML_COL_LANG           7
#define DBA_HTML_COL_SPAN           8
#define DBA_HTML_COL_STYLE          9
#define DBA_HTML_COL_TITLE         10
#define DBA_HTML_COL_VALIGN        11
#define DBA_HTML_COL_WIDTH         12
#define DBA_HTML_COL_ATTRIBUTES    13

#define DBA_HTML_CREDIT_CLASS       0
#define DBA_HTML_CREDIT_CLEAR       1
#define DBA_HTML_CREDIT_DIR         2
#define DBA_HTML_CREDIT_ID          3
#define DBA_HTML_CREDIT_LANG        4
#define DBA_HTML_CREDIT_STYLE       5
#define DBA_HTML_CREDIT_TITLE       6
#define DBA_HTML_CREDIT_ATTRIBUTES  7

#define DBA_HTML_DIV_ALIGN          0
#define DBA_HTML_DIV_CLASS          1
#define DBA_HTML_DIV_CLEAR          2
#define DBA_HTML_DIV_DIR            3
#define DBA_HTML_DIV_ID             4
#define DBA_HTML_DIV_LANG           5
#define DBA_HTML_DIV_STYLE          6
#define DBA_HTML_DIV_TITLE          7
#define DBA_HTML_DIV_ATTRIBUTES     8

#define DBA_HTML_DL_CLASS           0
#define DBA_HTML_DL_CLEAR           1
#define DBA_HTML_DL_COMPACT         2
#define DBA_HTML_DL_DIR             3
#define DBA_HTML_DL_ID              4
#define DBA_HTML_DL_LANG            5
#define DBA_HTML_DL_STYLE           6
#define DBA_HTML_DL_TITLE           7
#define DBA_HTML_DL_ATTRIBUTES      8

#define DBA_HTML_EMBED_ALIGN        0
#define DBA_HTML_EMBED_ALT          1
#define DBA_HTML_EMBED_BORDER       2
#define DBA_HTML_EMBED_CLASS        3
#define DBA_HTML_EMBED_CLEAR        4
#define DBA_HTML_EMBED_DIR          5
#define DBA_HTML_EMBED_HEIGHT       6
#define DBA_HTML_EMBED_ID           7
#define DBA_HTML_EMBED_IMAGEMAP     8
#define DBA_HTML_EMBED_ISMAP        9
#define DBA_HTML_EMBED_LANG        10
#define DBA_HTML_EMBED_MD          11
#define DBA_HTML_EMBED_NAME        12
#define DBA_HTML_EMBED_NOFLOW      13
#define DBA_HTML_EMBED_PARAMS      14
#define DBA_HTML_EMBED_PLUGINSPACE 15
#define DBA_HTML_EMBED_SRC         16
#define DBA_HTML_EMBED_STYLE       17
#define DBA_HTML_EMBED_TITLE       18
#define DBA_HTML_EMBED_TYPE        19
#define DBA_HTML_EMBED_UNITS       20
#define DBA_HTML_EMBED_USEMAP      21
#define DBA_HTML_EMBED_WIDTH       22
#define DBA_HTML_EMBED_ATTRIBUTES  23

#define DBA_HTML_FIELDSET_CLASS     0
#define DBA_HTML_FIELDSET_CLEAR     1
#define DBA_HTML_FIELDSET_DIR       2
#define DBA_HTML_FIELDSET_ID        3
#define DBA_HTML_FIELDSET_LANG      4
#define DBA_HTML_FIELDSET_STYLE     5
#define DBA_HTML_FIELDSET_TITLE     6
#define DBA_HTML_FIELDSET_ATTRIBUTES 7

#define DBA_HTML_FIG_ALIGN          0
#define DBA_HTML_FIG_BORDER         1
#define DBA_HTML_FIG_CLASS          2
#define DBA_HTML_FIG_CLEAR          3
#define DBA_HTML_FIG_DIR            4
#define DBA_HTML_FIG_HEIGHT         5
#define DBA_HTML_FIG_ID             6
#define DBA_HTML_FIG_IMAGEMAP       7
#define DBA_HTML_FIG_ISOBJECT       8
#define DBA_HTML_FIG_LANG           9
#define DBA_HTML_FIG_MD            10
#define DBA_HTML_FIG_NOFLOW        11
#define DBA_HTML_FIG_SRC           12
#define DBA_HTML_FIG_STYLE         13
#define DBA_HTML_FIG_TITLE         14
#define DBA_HTML_FIG_UNITS         15
#define DBA_HTML_FIG_WIDTH         16
#define DBA_HTML_FIG_ATTRIBUTES    17

#define DBA_HTML_FN_CLASS           0
#define DBA_HTML_FN_CLEAR           1
#define DBA_HTML_FN_DIR             2
#define DBA_HTML_FN_ID              3
#define DBA_HTML_FN_LANG            4
#define DBA_HTML_FN_STYLE           5
#define DBA_HTML_FN_TITLE           6
#define DBA_HTML_FN_ATTRIBUTES      7

#define DBA_HTML_FONT_CLASS         0
#define DBA_HTML_FONT_CLEAR         1
#define DBA_HTML_FONT_COLOR         2
#define DBA_HTML_FONT_DIR           3
#define DBA_HTML_FONT_FACE          4
#define DBA_HTML_FONT_ID            5
#define DBA_HTML_FONT_LANG          6
#define DBA_HTML_FONT_SIZE          7
#define DBA_HTML_FONT_STYLE         8
#define DBA_HTML_FONT_ATTRIBUTES    9

#define DBA_HTML_FORM_ACCEPT_CHARSET  0 /**< HTML 4.0 draft - kw */
#define DBA_HTML_FORM_ACTION        1
#define DBA_HTML_FORM_CLASS         2
#define DBA_HTML_FORM_CLEAR         3
#define DBA_HTML_FORM_DIR           4
#define DBA_HTML_FORM_ENCTYPE       5
#define DBA_HTML_FORM_ID            6
#define DBA_HTML_FORM_LANG          7
#define DBA_HTML_FORM_METHOD        8
#define DBA_HTML_FORM_NAME          9
#define DBA_HTML_FORM_ONRESET         10
#define DBA_HTML_FORM_ONSUBMIT      11
#define DBA_HTML_FORM_SCRIPT        12
#define DBA_HTML_FORM_STYLE         13
#define DBA_HTML_FORM_SUBJECT       14
#define DBA_HTML_FORM_TARGET        15
#define DBA_HTML_FORM_TITLE         16
#define DBA_HTML_FORM_ATTRIBUTES    17

#define DBA_HTML_FRAME_ID            0
#define DBA_HTML_FRAME_LONGDESC      1
#define DBA_HTML_FRAME_MARGINHEIGHT  2
#define DBA_HTML_FRAME_MARGINWIDTH   3
#define DBA_HTML_FRAME_NAME          4
#define DBA_HTML_FRAME_NORESIZE      5
#define DBA_HTML_FRAME_SCROLLING     6
#define DBA_HTML_FRAME_SRC           7
#define DBA_HTML_FRAME_ATTRIBUTES    8

#define DBA_HTML_FRAMESET_COLS      0
#define DBA_HTML_FRAMESET_ROWS      1
#define DBA_HTML_FRAMESET_ATTRIBUTES 2

#define DBA_HTML_GEN_CLASS          0
#define DBA_HTML_GEN_CLEAR          1
#define DBA_HTML_GEN_DIR            2
#define DBA_HTML_GEN_ID             3
#define DBA_HTML_GEN_LANG           4
#define DBA_HTML_GEN_STYLE          5
#define DBA_HTML_GEN_TITLE          6
#define DBA_HTML_GEN_ATTRIBUTES     7

#define DBA_HTML_H_ALIGN            0
#define DBA_HTML_H_CLASS            1
#define DBA_HTML_H_CLEAR            2
#define DBA_HTML_H_DINGBAT          3
#define DBA_HTML_H_DIR              4
#define DBA_HTML_H_ID               5
#define DBA_HTML_H_LANG             6
#define DBA_HTML_H_MD               7
#define DBA_HTML_H_NOWRAP           8
#define DBA_HTML_H_SEQNUM           9
#define DBA_HTML_H_SKIP            10
#define DBA_HTML_H_SRC             11
#define DBA_HTML_H_STYLE           12
#define DBA_HTML_H_TITLE           13
#define DBA_HTML_H_ATTRIBUTES      14

#define DBA_HTML_HR_ALIGN           0
#define DBA_HTML_HR_CLASS           1
#define DBA_HTML_HR_CLEAR           2
#define DBA_HTML_HR_DIR             3
#define DBA_HTML_HR_ID              4
#define DBA_HTML_HR_MD              5
#define DBA_HTML_HR_NOSHADE         6
#define DBA_HTML_HR_SIZE            7
#define DBA_HTML_HR_SRC             8
#define DBA_HTML_HR_STYLE           9
#define DBA_HTML_HR_TITLE          10
#define DBA_HTML_HR_WIDTH          11
#define DBA_HTML_HR_ATTRIBUTES     12

#define DBA_HTML_IFRAME_ALIGN         0
#define DBA_HTML_IFRAME_FRAMEBORDER   1
#define DBA_HTML_IFRAME_HEIGHT        2
#define DBA_HTML_IFRAME_ID            3
#define DBA_HTML_IFRAME_LONGDESC      4
#define DBA_HTML_IFRAME_MARGINHEIGHT  5
#define DBA_HTML_IFRAME_MARGINWIDTH   6
#define DBA_HTML_IFRAME_NAME          7
#define DBA_HTML_IFRAME_SCROLLING     8
#define DBA_HTML_IFRAME_SRC           9
#define DBA_HTML_IFRAME_STYLE        10
#define DBA_HTML_IFRAME_WIDTH        11
#define DBA_HTML_IFRAME_ATTRIBUTES   12

#define DBA_HTML_IMG_ALIGN           0
#define DBA_HTML_IMG_ALT             1
#define DBA_HTML_IMG_BORDER          2
#define DBA_HTML_IMG_CLASS           3
#define DBA_HTML_IMG_CLEAR           4
#define DBA_HTML_IMG_DIR             5
#define DBA_HTML_IMG_HEIGHT          6
#define DBA_HTML_IMG_HSPACE          7
#define DBA_HTML_IMG_ID              8
#define DBA_HTML_IMG_ISMAP           9
#define DBA_HTML_IMG_ISOBJECT        10
#define DBA_HTML_IMG_LANG           11
#define DBA_HTML_IMG_LOCALSRC       12
#define DBA_HTML_IMG_LONGDESC       13
#define DBA_HTML_IMG_MD             14
#define DBA_HTML_IMG_SRC            15
#define DBA_HTML_IMG_STYLE          16
#define DBA_HTML_IMG_TITLE          17
#define DBA_HTML_IMG_UNITS          18
#define DBA_HTML_IMG_USEMAP         19
#define DBA_HTML_IMG_VSPACE         20
#define DBA_HTML_IMG_WIDTH          21
#define DBA_HTML_IMG_ATTRIBUTES     22

#define DBA_HTML_INPUT_ACCEPT           0
#define DBA_HTML_INPUT_ACCEPT_CHARSET   1 /**< RFC 2070 HTML i18n - kw */
#define DBA_HTML_INPUT_ACCESSKEY        2
#define DBA_HTML_INPUT_ALIGN            3
#define DBA_HTML_INPUT_ALT              4
#define DBA_HTML_INPUT_CHECKED          5
#define DBA_HTML_INPUT_CLASS            6
#define DBA_HTML_INPUT_CLEAR            7
#define DBA_HTML_INPUT_DIR              8
#define DBA_HTML_INPUT_DISABLED         9
#define DBA_HTML_INPUT_EMPTYOK          10
#define DBA_HTML_INPUT_ERROR            11
#define DBA_HTML_INPUT_FORMAT           12
#define DBA_HTML_INPUT_HEIGHT           13
#define DBA_HTML_INPUT_ID               14
#define DBA_HTML_INPUT_LANG        15
#define DBA_HTML_INPUT_MAX         16
#define DBA_HTML_INPUT_MAXLENGTH   17
#define DBA_HTML_INPUT_MD          18
#define DBA_HTML_INPUT_MIN         19
#define DBA_HTML_INPUT_NAME        20
#define DBA_HTML_INPUT_NOTAB       21
#define DBA_HTML_INPUT_ONBLUR      22
#define DBA_HTML_INPUT_ONCHANGE    23
#define DBA_HTML_INPUT_ONCLICK     24
#define DBA_HTML_INPUT_ONFOCUS     25
#define DBA_HTML_INPUT_ONSELECT    26
#define DBA_HTML_INPUT_SIZE        27
#define DBA_HTML_INPUT_SRC         28
#define DBA_HTML_INPUT_STYLE       29
#define DBA_HTML_INPUT_TABINDEX    30
#define DBA_HTML_INPUT_TITLE       31
#define DBA_HTML_INPUT_TYPE        32
#define DBA_HTML_INPUT_VALUE       33
#define DBA_HTML_INPUT_WIDTH       34
#define DBA_HTML_INPUT_ATTRIBUTES  35

#define DBA_HTML_ISINDEX_ACTION     0  /**< Treat as synonym for HREF. - JERRY */
#define DBA_HTML_ISINDEX_DIR        1
#define DBA_HTML_ISINDEX_HREF       2  /**< HTML 3.0 "action". - JERRY */
#define DBA_HTML_ISINDEX_ID         3
#define DBA_HTML_ISINDEX_LANG       4
#define DBA_HTML_ISINDEX_PROMPT     5  /**< HTML 3.0 "prompt". - JERRY */
#define DBA_HTML_ISINDEX_TITLE      6
#define DBA_HTML_ISINDEX_ATTRIBUTES 7

#define DBA_HTML_KEYGEN_CHALLENGE   0
#define DBA_HTML_KEYGEN_CLASS       1
#define DBA_HTML_KEYGEN_DIR         2
#define DBA_HTML_KEYGEN_ID          3
#define DBA_HTML_KEYGEN_LANG        4
#define DBA_HTML_KEYGEN_NAME        5
#define DBA_HTML_KEYGEN_STYLE       6
#define DBA_HTML_KEYGEN_TITLE       7
#define DBA_HTML_KEYGEN_ATTRIBUTES  8

#define DBA_HTML_LABEL_ACCESSKEY    0
#define DBA_HTML_LABEL_CLASS        1
#define DBA_HTML_LABEL_CLEAR        2
#define DBA_HTML_LABEL_DIR          3
#define DBA_HTML_LABEL_FOR          4
#define DBA_HTML_LABEL_ID           5
#define DBA_HTML_LABEL_LANG         6
#define DBA_HTML_LABEL_ONCLICK      7
#define DBA_HTML_LABEL_STYLE        8
#define DBA_HTML_LABEL_TITLE        9
#define DBA_HTML_LABEL_ATTRIBUTES  10

#define DBA_HTML_LEGEND_ACCESSKEY   0
#define DBA_HTML_LEGEND_ALIGN       1
#define DBA_HTML_LEGEND_CLASS       2
#define DBA_HTML_LEGEND_CLEAR       3
#define DBA_HTML_LEGEND_DIR         4
#define DBA_HTML_LEGEND_ID          5
#define DBA_HTML_LEGEND_LANG        6
#define DBA_HTML_LEGEND_STYLE       7
#define DBA_HTML_LEGEND_TITLE       8
#define DBA_HTML_LEGEND_ATTRIBUTES  9

#define DBA_HTML_LI_CLASS           0
#define DBA_HTML_LI_CLEAR           1
#define DBA_HTML_LI_DINGBAT         2
#define DBA_HTML_LI_DIR             3
#define DBA_HTML_LI_ID              4
#define DBA_HTML_LI_LANG            5
#define DBA_HTML_LI_MD              6
#define DBA_HTML_LI_SKIP            7
#define DBA_HTML_LI_SRC             8
#define DBA_HTML_LI_STYLE           9
#define DBA_HTML_LI_TITLE          10
#define DBA_HTML_LI_TYPE           11
#define DBA_HTML_LI_VALUE          12
#define DBA_HTML_LI_ATTRIBUTES     13

#define DBA_HTML_LINK_CHARSET       0 /**< RFC 2070 HTML i18n - kw */
#define DBA_HTML_LINK_CLASS         1
#define DBA_HTML_LINK_HREF          2
#define DBA_HTML_LINK_ID            3
#define DBA_HTML_LINK_MEDIA         4
#define DBA_HTML_LINK_REL           5
#define DBA_HTML_LINK_REV           6
#define DBA_HTML_LINK_STYLE         7
#define DBA_HTML_LINK_TARGET        8
#define DBA_HTML_LINK_TITLE         9
#define DBA_HTML_LINK_TYPE         10
#define DBA_HTML_LINK_ATTRIBUTES   11

#define DBA_HTML_MAP_CLASS          0
#define DBA_HTML_MAP_CLEAR          1
#define DBA_HTML_MAP_DIR            2
#define DBA_HTML_MAP_ID             3
#define DBA_HTML_MAP_LANG           4
#define DBA_HTML_MAP_NAME           5
#define DBA_HTML_MAP_STYLE          6
#define DBA_HTML_MAP_TITLE          7
#define DBA_HTML_MAP_ATTRIBUTES     8

#define DBA_HTML_MARQUEE_CLASS          0
#define DBA_HTML_MARQUEE_DIRECTION      1
#define DBA_HTML_MARQUEE_HEIGHT         2
#define DBA_HTML_MARQUEE_LOOP           3
#define DBA_HTML_MARQUEE_SCROLLAMOUT    4
#define DBA_HTML_MARQUEE_SCROLLDELAY    5
#define DBA_HTML_MARQUEE_WIDTH          6
#define DBA_HTML_MARQUEE_ATTRIBUTES     7

#define DBA_HTML_MATH_BOX           0
#define DBA_HTML_MATH_CLASS         1
#define DBA_HTML_MATH_CLEAR         2
#define DBA_HTML_MATH_DIR           3
#define DBA_HTML_MATH_ID            4
#define DBA_HTML_MATH_LANG          5
#define DBA_HTML_MATH_STYLE         6
#define DBA_HTML_MATH_TITLE         7
#define DBA_HTML_MATH_ATTRIBUTES    8

#define DBA_HTML_META_CONTENT       0
#define DBA_HTML_META_HTTP_EQUIV    1
#define DBA_HTML_META_NAME          2
#define DBA_HTML_META_ATTRIBUTES    3

#define NEXTID_N                0

#define DBA_HTML_NEXTPAGE_HREF              0
#define DBA_HTML_NEXTPAGE_ATTRIBUTES        1

#define DBA_HTML_INPUTPAGE_HREF             0
#define DBA_HTML_INPUTPAGE_ATTRIBUTES       1

#define DBA_HTML_SCREEN_WIDTH       0
#define DBA_HTML_SCREEN_HEIGHT      1
#define DBA_HTML_SCREEN_ATTRIBUTES  2

#define DBA_HTML_NOTE_CLASS         0
#define DBA_HTML_NOTE_CLEAR         1
#define DBA_HTML_NOTE_DIR           2
#define DBA_HTML_NOTE_ID            3
#define DBA_HTML_NOTE_LANG          4
#define DBA_HTML_NOTE_MD            5
#define DBA_HTML_NOTE_ROLE          6 /**< Old name for CLASS - JERRY */
#define DBA_HTML_NOTE_SRC           7
#define DBA_HTML_NOTE_STYLE         8
#define DBA_HTML_NOTE_TITLE         9
#define DBA_HTML_NOTE_ATTRIBUTES   10

#define DBA_HTML_OBJECT_ALIGN       0
#define DBA_HTML_OBJECT_BORDER      1
#define DBA_HTML_OBJECT_CLASS       2
#define DBA_HTML_OBJECT_CLASSID     3
#define DBA_HTML_OBJECT_CODEBASE    4
#define DBA_HTML_OBJECT_CODETYPE    5
#define DBA_HTML_OBJECT_DATA        6
#define DBA_HTML_OBJECT_DECLARE     7
#define DBA_HTML_OBJECT_DIR         8
#define DBA_HTML_OBJECT_HEIGHT      9
#define DBA_HTML_OBJECT_HSPACE     10
#define DBA_HTML_OBJECT_ID         11
#define DBA_HTML_OBJECT_ISMAP      12
#define DBA_HTML_OBJECT_LANG       13
#define DBA_HTML_OBJECT_NAME       14
#define DBA_HTML_OBJECT_NOTAB      15
#define DBA_HTML_OBJECT_SHAPES     16
#define DBA_HTML_OBJECT_STANDBY    17
#define DBA_HTML_OBJECT_STYLE      18
#define DBA_HTML_OBJECT_TABINDEX   19
#define DBA_HTML_OBJECT_TITLE      20
#define DBA_HTML_OBJECT_TYPE       21
#define DBA_HTML_OBJECT_USEMAP     22
#define DBA_HTML_OBJECT_VSPACE     23
#define DBA_HTML_OBJECT_WIDTH      24
#define DBA_HTML_OBJECT_ATTRIBUTES 25

#define DBA_HTML_OL_CLASS           0
#define DBA_HTML_OL_CLEAR           1
#define DBA_HTML_OL_COMPACT         2
#define DBA_HTML_OL_CONTINUE        3
#define DBA_HTML_OL_DIR             4
#define DBA_HTML_OL_ID              5
#define DBA_HTML_OL_LANG            6
#define DBA_HTML_OL_SEQNUM          7
#define DBA_HTML_OL_START           8
#define DBA_HTML_OL_STYLE           9
#define DBA_HTML_OL_TITLE          10
#define DBA_HTML_OL_TYPE           11
#define DBA_HTML_OL_ATTRIBUTES     12

#define DBA_HTML_OPTGROUP_CLASS         0
#define DBA_HTML_OPTGROUP_LABEL         1
#define DBA_HTML_OPTGROUP_DISABLED      2
#define DBA_HTML_OPTGROUP_ATTRIBUTES    3
#define DBA_HTML_OPTION_CLASS       0
#define DBA_HTML_OPTION_CLEAR       1
#define DBA_HTML_OPTION_DIR         2
#define DBA_HTML_OPTION_DISABLED    3
#define DBA_HTML_OPTION_ERROR       4
#define DBA_HTML_OPTION_ID          5
#define DBA_HTML_OPTION_LABEL       6
#define DBA_HTML_OPTION_LANG        7
#define DBA_HTML_OPTION_ONPICK      8
#define DBA_HTML_OPTION_SELECTED    9
#define DBA_HTML_OPTION_SHAPE      10
#define DBA_HTML_OPTION_STYLE      11
#define DBA_HTML_OPTION_TITLE      12
#define DBA_HTML_OPTION_VALUE      13
#define DBA_HTML_OPTION_ATTRIBUTES 14

#define DBA_HTML_OVERLAY_CLASS      0
#define DBA_HTML_OVERLAY_HEIGHT     1
#define DBA_HTML_OVERLAY_ID         2
#define DBA_HTML_OVERLAY_IMAGEMAP   3
#define DBA_HTML_OVERLAY_MD         4
#define DBA_HTML_OVERLAY_SRC        5
#define DBA_HTML_OVERLAY_STYLE      6
#define DBA_HTML_OVERLAY_TITLE      7
#define DBA_HTML_OVERLAY_UNITS      8
#define DBA_HTML_OVERLAY_WIDTH      9
#define DBA_HTML_OVERLAY_X         10
#define DBA_HTML_OVERLAY_Y         11
#define DBA_HTML_OVERLAY_ATTRIBUTES 12

#define DBA_HTML_P_ALIGN            0
#define DBA_HTML_P_CLASS            1
#define DBA_HTML_P_CLEAR            2
#define DBA_HTML_P_DIR              3
#define DBA_HTML_P_ID               4
#define DBA_HTML_P_LANG             5
#define DBA_HTML_P_NOWRAP           6
#define DBA_HTML_P_STYLE            7
#define DBA_HTML_P_TITLE            8
#define DBA_HTML_P_ATTRIBUTES       9

#define DBA_HTML_PARAM_ACCEPT       0
#define DBA_HTML_PARAM_ACCEPT_CHARSET  1
#define DBA_HTML_PARAM_ACCEPT_ENCODING 2
#define DBA_HTML_PARAM_CLASS        3
#define DBA_HTML_PARAM_CLEAR        4
#define DBA_HTML_PARAM_DATA         5
#define DBA_HTML_PARAM_DIR          6
#define DBA_HTML_PARAM_ID           7
#define DBA_HTML_PARAM_LANG         8
#define DBA_HTML_PARAM_NAME         9
#define DBA_HTML_PARAM_OBJECT      10
#define DBA_HTML_PARAM_REF         11
#define DBA_HTML_PARAM_STYLE       12
#define DBA_HTML_PARAM_TITLE       13
#define DBA_HTML_PARAM_TYPE        14
#define DBA_HTML_PARAM_VALUE       15
#define DBA_HTML_PARAM_VALUEREF    16  /**< Use VALUETYPE (DATA|REF|OBJECT). - JERRY */
#define DBA_HTML_PARAM_VALUETYPE   17
#define DBA_HTML_PARAM_ATTRIBUTES  18

#define DBA_HTML_SCRIPT_CLASS       0
#define DBA_HTML_SCRIPT_CLEAR       1
#define DBA_HTML_SCRIPT_DIR         2
#define DBA_HTML_SCRIPT_EVENT       3
#define DBA_HTML_SCRIPT_FOR         4
#define DBA_HTML_SCRIPT_ID          5
#define DBA_HTML_SCRIPT_LANG        6
#define DBA_HTML_SCRIPT_LANGUAGE    7
#define DBA_HTML_SCRIPT_NAME        8
#define DBA_HTML_SCRIPT_SCRIPTENGINE 9
#define DBA_HTML_SCRIPT_SRC        10
#define DBA_HTML_SCRIPT_STYLE      11
#define DBA_HTML_SCRIPT_TITLE      12
#define DBA_HTML_SCRIPT_TYPE       13
#define DBA_HTML_SCRIPT_ATTRIBUTES 14

#define DBA_HTML_SELECT_ALIGN       0
#define DBA_HTML_SELECT_CLASS       1
#define DBA_HTML_SELECT_CLEAR       2
#define DBA_HTML_SELECT_DIR         3
#define DBA_HTML_SELECT_DISABLED    4
#define DBA_HTML_SELECT_ERROR       5
#define DBA_HTML_SELECT_HEIGHT      6
#define DBA_HTML_SELECT_ID          7
#define DBA_HTML_SELECT_INAME       8
#define DBA_HTML_SELECT_IVALUE      9
#define DBA_HTML_SELECT_LANG        10
#define DBA_HTML_SELECT_MD          11
#define DBA_HTML_SELECT_MULTIPLE   12
#define DBA_HTML_SELECT_NAME       13
#define DBA_HTML_SELECT_NOTAB      14
#define DBA_HTML_SELECT_ONBLUR     15
#define DBA_HTML_SELECT_ONCHANGE   16
#define DBA_HTML_SELECT_ONCLICK    17
#define DBA_HTML_SELECT_ONFOCUS    18
#define DBA_HTML_SELECT_SIZE       19
#define DBA_HTML_SELECT_STYLE      20
#define DBA_HTML_SELECT_TABINDEX   21
#define DBA_HTML_SELECT_TITLE      22
#define DBA_HTML_SELECT_UNITS      23
#define DBA_HTML_SELECT_VALUE      24
#define DBA_HTML_SELECT_WIDTH      25
#define DBA_HTML_SELECT_ATTRIBUTES 26

#define DBA_HTML_STYLE_DIR          0
#define DBA_HTML_STYLE_LANG         1
#define DBA_HTML_STYLE_MEDIA        2
#define DBA_HTML_STYLE_TITLE        3
#define DBA_HTML_STYLE_TYPE         4
#define DBA_HTML_STYLE_ATTRIBUTES   5

#define DBA_HTML_TAB_ALIGN          0
#define DBA_HTML_TAB_CLASS          1
#define DBA_HTML_TAB_CLEAR          2
#define DBA_HTML_TAB_DIR            3
#define DBA_HTML_TAB_DP             4
#define DBA_HTML_TAB_ID             5
#define DBA_HTML_TAB_INDENT         6
#define DBA_HTML_TAB_LANG           7
#define DBA_HTML_TAB_STYLE          8
#define DBA_HTML_TAB_TITLE          9
#define DBA_HTML_TAB_TO            10
#define DBA_HTML_TAB_ATTRIBUTES    11

#define DBA_HTML_TABLE_ALIGN        0
#define DBA_HTML_TABLE_BGCOLOR      1
#define DBA_HTML_TABLE_BORDER       2
#define DBA_HTML_TABLE_CELLPADDING  3
#define DBA_HTML_TABLE_CELLSPACING  4
#define DBA_HTML_TABLE_CLASS        5
#define DBA_HTML_TABLE_DIR          6
#define DBA_HTML_TABLE_FRAME        7
#define DBA_HTML_TABLE_ID           8
#define DBA_HTML_TABLE_LANG         9
#define DBA_HTML_TABLE_RULES       10
#define DBA_HTML_TABLE_STYLE       11
#define DBA_HTML_TABLE_SUMMARY     12
#define DBA_HTML_TABLE_TITLE       13
#define DBA_HTML_TABLE_WIDTH       14
#define DBA_HTML_TABLE_ATTRIBUTES  15

#define DBA_HTML_TD_ALIGN           0
#define DBA_HTML_TD_AXES            1
#define DBA_HTML_TD_AXIS            2
#define DBA_HTML_TD_BACKGROUND      3
#define DBA_HTML_TD_BGCOLOR         4
#define DBA_HTML_TD_CHAR            5
#define DBA_HTML_TD_CHAROFF         6
#define DBA_HTML_TD_CLASS           7
#define DBA_HTML_TD_CLEAR           8
#define DBA_HTML_TD_COLSPAN         9
#define DBA_HTML_TD_DIR            10
#define DBA_HTML_TD_DP             11
#define DBA_HTML_TD_HEIGHT         12
#define DBA_HTML_TD_ID             13
#define DBA_HTML_TD_LANG           14
#define DBA_HTML_TD_NOWRAP         15
#define DBA_HTML_TD_ROWSPAN        16
#define DBA_HTML_TD_STYLE          17
#define DBA_HTML_TD_TITLE          18
#define DBA_HTML_TD_VALIGN         19
#define DBA_HTML_TD_WIDTH          20
#define DBA_HTML_TD_ATTRIBUTES     21

#define DBA_HTML_TEXTAREA_ACCEPT_CHARSET  0 /**< RFC 2070 HTML i18n - kw */
#define DBA_HTML_TEXTAREA_ACCESSKEY 1
#define DBA_HTML_TEXTAREA_ALIGN     2
#define DBA_HTML_TEXTAREA_CLASS     3
#define DBA_HTML_TEXTAREA_CLEAR     4
#define DBA_HTML_TEXTAREA_COLS      5
#define DBA_HTML_TEXTAREA_DIR       6
#define DBA_HTML_TEXTAREA_DISABLED  7
#define DBA_HTML_TEXTAREA_ERROR     8
#define DBA_HTML_TEXTAREA_ID        9
#define DBA_HTML_TEXTAREA_LANG      10
#define DBA_HTML_TEXTAREA_NAME     11
#define DBA_HTML_TEXTAREA_NOTAB    12
#define DBA_HTML_TEXTAREA_ONBLUR   13
#define DBA_HTML_TEXTAREA_ONCHANGE 14
#define DBA_HTML_TEXTAREA_ONCLICK  15
#define DBA_HTML_TEXTAREA_ONFOCUS  16
#define DBA_HTML_TEXTAREA_ONSELECT 17
#define DBA_HTML_TEXTAREA_ROWS     18
#define DBA_HTML_TEXTAREA_STYLE    19
#define DBA_HTML_TEXTAREA_TABINDEX 20
#define DBA_HTML_TEXTAREA_TITLE    21
#define DBA_HTML_TEXTAREA_ATTRIBUTES 22

#define DBA_HTML_TR_ALIGN           0
#define DBA_HTML_TR_BGCOLOR         1
#define DBA_HTML_TR_CHAR            2
#define DBA_HTML_TR_CHAROFF         3
#define DBA_HTML_TR_CLASS           4
#define DBA_HTML_TR_CLEAR           5
#define DBA_HTML_TR_DIR             6
#define DBA_HTML_TR_DP              7
#define DBA_HTML_TR_HEIGHT          8
#define DBA_HTML_TR_ID              9
#define DBA_HTML_TR_LANG            10
#define DBA_HTML_TR_NOWRAP          11
#define DBA_HTML_TR_STYLE           12
#define DBA_HTML_TR_TITLE           13
#define DBA_HTML_TR_VALIGN          14
#define DBA_HTML_TR_WIDTH           15
#define DBA_HTML_TR_ATTRIBUTES      16

#define DBA_HTML_UL_CLASS           0
#define DBA_HTML_UL_CLEAR           1
#define DBA_HTML_UL_COMPACT         2
#define DBA_HTML_UL_DINGBAT         3
#define DBA_HTML_UL_DIR             4
#define DBA_HTML_UL_ID              5
#define DBA_HTML_UL_LANG            6
#define DBA_HTML_UL_MD              7
#define DBA_HTML_UL_PLAIN           8
#define DBA_HTML_UL_SRC             9
#define DBA_HTML_UL_STYLE          10
#define DBA_HTML_UL_TITLE          11
#define DBA_HTML_UL_TYPE           12
#define DBA_HTML_UL_WRAP           13
#define DBA_HTML_UL_ATTRIBUTES     14

#define DBA_HTML_BIG_STYLE          5

#define DBA_HTML_SMALL_STYLE        5

/**Find the attributes in the attributes table using the gived tag number.
*   \param  current_tag     the tag number
*   \param  attrStr         the attributes array
*   \return <ul>
*           <li>the index in attributes table
*           <li>-1, otherwise
*        </ul>
*/
int32_t fnDBA_FindAttr(
    int32_t     current_tag,
    const int8_t* attrStr
);

#ifdef __cplusplus
}
#endif

#endif /*_DBA_TAGATTRLISTS_H_*/
