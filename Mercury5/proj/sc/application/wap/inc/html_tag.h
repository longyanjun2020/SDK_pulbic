
#ifndef _HTMLTAG_H_
#define _HTMLTAG_H_

#include <ncc_types.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

/*       Element Numbers    */
/* Must Match all tables by element! */
typedef enum _HTMLTAG {
    HTML_TAG_A,                     /* A */
    HTML_TAG_ABBREV,                /* ABBREV */
    HTML_TAG_ACRONYM,               /* ACRONYM */
    HTML_TAG_ADDRESS,               /* ADDRESS */
    HTML_TAG_APPLET,                /* APPLET */
    HTML_TAG_AREA,                  /* AREA */
    HTML_TAG_AU,                    /* AU */
    HTML_TAG_AUTHOR,                /* AUTHOR */
    HTML_TAG_B,                     /* B */
    HTML_TAG_BANNER,                /* BANNER */
    HTML_TAG_BASE,                  /* BASE */
    HTML_TAG_BASEFONT,              /* BASEFONT */
    HTML_TAG_BDO,                   /* BDO */
    HTML_TAG_BGSOUND,               /* BGSOUND */
    HTML_TAG_BIG,                   /* BIG */
    HTML_TAG_BLINK,                 /* BLINK */
    HTML_TAG_BLOCKQUOTE,            /* BLOCKQUOTE */
    HTML_TAG_BODY,                  /* BODY */
    HTML_TAG_BODYTEXT,              /* BODYTEXT */
    HTML_TAG_BQ,                    /* BQ */
    HTML_TAG_BR,                    /* BR */
    HTML_TAG_BUTTON,                /* BUTTON */
    HTML_TAG_CAPTION,               /* CAPTION */
    HTML_TAG_CENTER,                /* CENTER */
    HTML_TAG_CITE,                  /* CITE */
    HTML_TAG_CODE,                  /* CODE */
    HTML_TAG_COL,                   /* COL */
    HTML_TAG_COLGROUP,              /* COLGROUP */
    HTML_TAG_COMMENT,               /* COMMENT */
    HTML_TAG_CREDIT,                /* CREDIT */
    HTML_TAG_DD,                    /* DD */
    HTML_TAG_DEL,                   /* DEL */
    HTML_TAG_DFN,                   /* DFN */
    HTML_TAG_DIR,                   /* DIR */
    HTML_TAG_DIV,                   /* DIV */
    HTML_TAG_DL,                    /* DL */
    HTML_TAG_DLC,                   /* DLC */
    HTML_TAG_DT,                    /* DT */
    HTML_TAG_EM,                    /* EM */
    HTML_TAG_EMBED,                 /* EMBED */
    HTML_TAG_FIELDSET,              /* FIELDSET */
    HTML_TAG_FIG,                   /* FIG */
    HTML_TAG_FN,                    /* FN */
    HTML_TAG_FONT,                  /* FONT */
    HTML_TAG_FORM,                  /* FORM */
    HTML_TAG_FRAME,                 /* FRAME */
    HTML_TAG_FRAMESET,              /* FRAMESET */
    HTML_TAG_H1,                    /* H1 */
    HTML_TAG_H2,                    /* H2 */
    HTML_TAG_H3,                    /* H3 */
    HTML_TAG_H4,                    /* H4 */
    HTML_TAG_H5,                    /* H5 */
    HTML_TAG_H6,                    /* H6 */
    HTML_TAG_HEAD,                  /* HEAD */
    HTML_TAG_HR,                    /* HR */
    HTML_TAG_HTML,                  /* HTML */
    HTML_TAG_HY,                    /* HY */
    HTML_TAG_I,                     /* I */
    HTML_TAG_IFRAME,                /* IFRAME */
    HTML_TAG_IMG,                   /* IMG */
    HTML_TAG_INPUT,                 /* INPUT */
    HTML_TAG_INPUTPAGE,             /* INPUTPAGE */
    HTML_TAG_INS,                   /* INS */
    HTML_TAG_ISINDEX,               /* ISINDEX */
    HTML_TAG_KBD,                   /* KBD */
    HTML_TAG_KEYGEN,                /* KEYGEN */
    HTML_TAG_LABEL,                 /* LABEL */
    HTML_TAG_LEGEND,                /* LEGEND */
    HTML_TAG_LH,                    /* LH */
    HTML_TAG_LI,                    /* LI */
    HTML_TAG_LINK,                  /* LINK */
    HTML_TAG_LISTING,               /* LISTING */
    HTML_TAG_MAP,                   /* MAP */
    HTML_TAG_MARQUEE,               /* MARQUEE */
    HTML_TAG_MATH,                  /* MATH */
    HTML_TAG_MENU,                  /* MENU */
    HTML_TAG_META,                  /* META */
    HTML_TAG_NEXTID,                /* NEXTID */
    HTML_TAG_NEXTPAGE,              /* NEXTPAGE */
    HTML_TAG_NOFRAMES,              /* NOFRAMES */
    HTML_TAG_NOSCRIPT,              /* NOSCRIPT */
    HTML_TAG_NOTE,                  /* NOTE */
    HTML_TAG_OBJECT,                /* OBJECT */
    HTML_TAG_OL,                    /* OL */
    HTML_TAG_OPTGROUP,              /* OPTGROUP */
    HTML_TAG_OPTION,                /* OPTION */
    HTML_TAG_OVERLAY,               /* OVERLAY */
    HTML_TAG_P,                     /* P */
    HTML_TAG_PARAM,                 /* PARAM */
    HTML_TAG_PLAINTEXT,             /* PLAINTEXT */
    HTML_TAG_PRE,                   /* PRE */
    HTML_TAG_Q,                     /* Q */
    HTML_TAG_S,                     /* S */
    HTML_TAG_SAMP,                  /* SAMP */
    HTML_TAG_SCREEN,                /* SCREEN */
    HTML_TAG_SCRIPT,                /* SCRIPT */
    HTML_TAG_SELECT,                /* SELECT */
    HTML_TAG_SHY,                   /* SHY */
    HTML_TAG_SMALL,                 /* SMALL */
    HTML_TAG_SPAN,                  /* SPAN */
    HTML_TAG_SPOT,                  /* SPOT */
    HTML_TAG_STRIKE,                /* STRIKE */
    HTML_TAG_STRONG,                /* STRONG */
    HTML_TAG_STYLE,                 /* STYLE */
    HTML_TAG_SUB,                   /* SUB */
    HTML_TAG_SUP,                   /* SUP */
    HTML_TAG_TAB,                   /* TAB */
    HTML_TAG_TABLE,                 /* TABLE */
    HTML_TAG_TBODY,                 /* TBODY */
    HTML_TAG_TD,                    /* TD */
    HTML_TAG_TEXTAREA,              /* TEXTAREA */
    HTML_TAG_TEXTFLOW,              /* TEXTFLOW */
    HTML_TAG_TFOOT,                 /* TFOOT */
    HTML_TAG_TH,                    /* TH */
    HTML_TAG_THEAD,                 /* THEAD */
    HTML_TAG_TITLE,                 /* TITLE */
    HTML_TAG_TR,                    /* TR */
    HTML_TAG_TT,                    /* TT */
    HTML_TAG_U,                     /* U */
    HTML_TAG_UL,                    /* UL */
    HTML_TAG_VAR,                   /* VAR */
    HTML_TAG_WBR,                   /* WBR */
    HTML_TAG_XMP,                   /* XMP */
    HTML_TAG_ALT_OBJECT,            /* ALT_OBJECT */
    HTML_TAG_DOCUMENT,              /* DOCUMENT */
    HTML_TAG_CDATA,                 /* CDATA */
    HTML_TAG_CHARACTERS,            /* CHARACTERS */
    HTML_TAG_DELETECONTENT,         /* DELETECONTENT */
    HTML_TAG_UNIVERSUAL,            /* UNIVERSUAL */
    HTML_TAG_INVALID                /* INVALID */
} HTMLTAG;

#ifdef __cplusplus
}
#endif

#endif /* _HTMLTAG_H_ */
