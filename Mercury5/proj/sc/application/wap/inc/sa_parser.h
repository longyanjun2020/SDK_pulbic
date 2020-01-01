
/**
 * @file
 *  Semantic Analyser of html/wml document
 */

#ifndef _DBA_PARSER_H_
#define _DBA_PARSER_H_

#include <ncc_types.h>

#include <wap_struct.h>
#include <nccsa.h>
#include <sa_tagattrlists.h>

#define SA_INVALID_INDEX ((uint8_t)-1) /**<invalid select's select index*/

#define DEFAULT_LINKCOLOR 0xff          /**< blue */
#define DEFAULT_VLINKCOLOR  0x800080    /**< red and green */
#define DEFAULT_TEXTCOLOR 0             /**< black */
#define DEFALUT_BGCOLOR   0xffffff      /**< white */

/** the special key */
#define DBA_TAB               0x09
#define DBA_LF                0x0A
#define DBA_HOME              0x0B
#define DBA_FF                0x0C
#define DBA_CR                0x0D

#define DBA_SPACE             ' '
#define DBA_NIL               '\0'

#define DBA_NULL              (int16_t)0

/**color defination*/
#define DBA_COLOR_BLACK       0x00000000
#define DBA_COLOR_GREEN       0x00008000
#define DBA_COLOR_SILVER      0x00C0C0C0
#define DBA_COLOR_LIME        0x0000FF00
#define DBA_COLOR_GRAY        0x00808080
#define DBA_COLOR_OLIVE       0x00808000
#define DBA_COLOR_WHITE       0x00FFFFFF
#define DBA_COLOR_YELLOW      0x00FFFF00
#define DBA_COLOR_MAROON      0x00800000
#define DBA_COLOR_NAVY        0x00000080
#define DBA_COLOR_RED         0x00FF0000
#define DBA_COLOR_BLUE        0x000000FF
#define DBA_COLOR_PURPLE      0x00800080
#define DBA_COLOR_TEAL        0x00008080
#define DBA_COLOR_FUCHSIA     0x00FF00FF
#define DBA_COLOR_AQUA        0x0000FFFF
#define DBA_COLOR_NULL        0xFFFFFFFF

/**list style defination*/

#define DBA_LIST_ITEM_STYLE_INIT            0
#define DBA_LIST_ITEM_STYLE_DISC            1
#define DBA_LIST_ITEM_STYLE_CIRCLE          2
#define DBA_LIST_ITEM_STYLE_SQUARE          3
#define DBA_LIST_ITEM_STYLE_LROMAN          4
#define DBA_LIST_ITEM_STYLE_UROMAN          5
#define DBA_LIST_ITEM_STYLE_LALPHA          6
#define DBA_LIST_ITEM_STYLE_UALPHA          7
#define DBA_LIST_ITEM_STYLE_ARABIC          8
#define DBA_LIST_ITEM_STYLE_NONE            9

#define DBA_LIST_ITEM_STYLE_DEFAULT_OL      DBA_LIST_ITEM_STYLE_ARABIC
#define DBA_LIST_ITEM_STYLE_DEFAULT_UL      DBA_LIST_ITEM_STYLE_DISC

/**the type of control defination*/
#define DBA_INPUT_TEXT           FIELD_TYPE_TEXT                  /**<edit */
#define DBA_INPUT_PASSWORD       FIELD_TYPE_PASSWORD              /**<password edit*/
#define DBA_INPUT_CHECKBOX       FIELD_TYPE_CHECKBOX              /**<check box*/
#define DBA_INPUT_RADIO          FIELD_TYPE_RADIOBOX              /**<radio box*/
#define DBA_INPUT_IMAGE          FIELD_TYPE_IMAGE_SUBMIT          /**<image submit button*/
#define DBA_INPUT_SUBMIT         FIELD_TYPE_TEXT_SUBMIT           /**<submit button*/
#define DBA_INPUT_RESET          FIELD_TYPE_RESET                 /**<reset button*/
#define DBA_INPUT_HIDDEN         FIELD_TYPE_HIDDEN                /**<hidden field*/
#define DBA_INPUT_BUTTON         FIELD_TYPE_BUTTON                /**<push button*/
#define DBA_INPUT_FILE           FIELD_TYPE_FILE                  /**<file*/

#define DBA_OPTION_LIST_SINGLE   FIELD_TYPE_OPTION_LIST_SINGLE     /**<single-check llistbox*/
#define DBA_OPTION_LIST_MULTI    FIELD_TYPE_OPTION_LIST_MULTI      /**<multi-check listbox*/
#define DBA_TEXTAREA             FIELD_TYPE_TEXTAREA               /**<multi-edit*/

#define DBA_BUTTON_TYPE_SUBMIT   FIELD_TYPE_TEXT_SUBMIT           /**<submit button*/
#define DBA_BUTTON_TYPE_RESET    FIELD_TYPE_RESET                 /**<reset button*/
#define DBA_BUTTON_TYPE_BUTTON   FIELD_TYPE_BUTTON               /**<push button*/

#define DBA_SCRIPT_TYPE_UNKNOWN            0
#define DBA_SCRIPT_TYPE_JAVA               1
#define DBA_SCRIPT_TYPE_VB                 2

#define DBA_OBJECT_CONVERTED      -1            /** object element have be transferred to ohter node*/

/**Each bit for a html tag's flag. e.g. 124 htmlflags:
 * tagsFlag[124/32 + 1]
 * tagsFlag[i] has 32 html flags.
 * if tag is the last html flag, so his flag is the bit in 124%32=28th of tagsFlag[3].
 */
#define SET_HTMLTAG_FLAG_FALSE(tagsFlag, tag) (tagsFlag)[(tag) >> 5] &= ~(1 << ((tag) & 31))
#define SET_HTMLTAG_FLAG_TRUE(tagsFlag, tag) (tagsFlag)[(tag) >> 5] |= 1 << ((tag) & 31)
#define GET_HTMLTAG_FLAG(tagsFlag, tag) ((tagsFlag)[(tag) >> 5] & (1 << ((tag) & 31)))
#define SET_HTML_ALL_TAG_FLAG_FALSE() CRTL_memset(NCCBrw_sa_getParseCtxt()->htmlTagsFlag,0,(DBA_HTML_ALL_ELEMENTS/32 + 1) * sizeof(int32_t))
/*when parsing,we would omit "html" and "body" */
#define RESET_HTML_ALL_TAG_FLAG()  \
    CRTL_memset(NCCBrw_sa_getParseCtxt()->htmlTagsFlag,-1,(DBA_HTML_ALL_ELEMENTS/32 + 1) * sizeof(int32_t));\
    SET_HTMLTAG_FLAG_FALSE(NCCBrw_sa_getParseCtxt()->htmlTagsFlag, DBA_HTML_HTML);\
    SET_HTMLTAG_FLAG_FALSE(NCCBrw_sa_getParseCtxt()->htmlTagsFlag, DBA_HTML_BODY)
/*Before parsing a new page,we would reset all tags*/
#define SET_HTML_ALL_TAG_FLAG_TURE()  \
    CRTL_memset(NCCBrw_sa_getParseCtxt()->htmlTagsFlag,-1,(DBA_HTML_ALL_ELEMENTS/32 + 1) * sizeof(int32_t))
#define SA_TAG_NEED_PARSE(tag)  \
                if (NCCBrw_sa_getParseCtxt() == NULL || NCCBrw_sa_getParseCtxt()->htmlTagsFlag == NULL || (DBA_HTML_INVALID != tag && !GET_HTMLTAG_FLAG(NCCBrw_sa_getParseCtxt()->htmlTagsFlag,tag)))\
                    return;


#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    DBA_FALSE,
    DBA_TRUE
}T_DBA_Boolean;

typedef enum{
    DBA_CONTENT_APPEND,     /**< Ignored the linkPos, add the content to the tail of the content link */
    DBA_CONTENT_INSERT_AFTER,   /**< Insert this node after the current link */
    DBA_CONTENT_INSERT_BEFORE   /**< Insert this node before the current link */
}T_DBA_Method;

///Set current context's screen style
/**
*   @param tClolor  the text color
*   @param lColor   the linked color
*   @param vlColor  the unlinked color
*   @param bgColor  the background color
*   @param bFont    the base font
*/
void fnDBA_SetScreenStyle(
    int32_t    tColor,
    int32_t    lColor,
    int32_t    vlColor,
    int32_t    bgColor,
    int32_t    bFont
);

/// Get the base font from the current context
int32_t fnDBA_GetBaseFont(void);

///Insert the node to the content link using the method gived
/**
*   \param  nodeType    the type of the node
*   \param  nodeContent     the content of the node
*   \param  linkPos         the position of the link express
*   \param  method      the method insert a node
*   \return <ul>
*           <li>current content link, if success
*           <li>0, in case of error
*       </ul>
*/
T_DB_ContentLinkIdx fnDBA_ContentAdd(
    T_DB_ContentNodeTp      nodeType,
    T_DB_iPtr               nodeContent,
    T_DB_ContentLinkIdx     linkPos,
    T_DBA_Method            method
);

///Parse the <a> tag
/**
*   \param  attrs  the attribute array
*/
void fnDBA_AParse( const uint8_t   **attrs );

///End parsing the <a> tag
void fnDBA_EndAParse( void );

///Parse the <style> tag
/**
*   \param  attrs  the attribute array
*/
void fnDBA_StyleParse( const uint8_t   **attrs );

/// End parsing the <style> tag
void fnDBA_EndStyleParse( void );

///Parsing the data block
/**
*    \param  value  the data block
*    \param  len    the length of the data block
*/
void fnDBA_CdataParse(
    uint8_t*  value,
    int32_t    len
);

///Parse the text
/**
*   \param  chs     the text we parsed
*   \param  len         the length of the text
*/
void fnDBA_CharactersParse(
    const uint8_t *chs,
    int32_t           len
);

///Get the image buffer from current parsed context
/**
*   \param  buf         to store the image buffer
*/
void fnDBA_GetImgBuf(   void *buf);

///Free the field of the context
/**
*   \param ctxt         the context include the field we wanted to free
*/
void fnDBA_FieldClean( T_DB_ParseCtxtPtr  ctxt );

///Show the tree we design, and the memory we used
void fnDBA_ShowContent( void );

///   End parsing the <table> tag
void fnDBA_EndTableParse( void );

///End parsing the <td> tag
/**
*   \param  num    the tag number of the element
*/
void fnDBA_EndTdParse( T_DBA_HTMLElement    num );

/// parsing the normal tag
/**
*   \param  num    the tag number of the element
*   \param  atts     the attributes of the tag
*/
void fnDBA_NormalParse(T_DBA_HTMLElement  num,uint8_t          **atts   );

/// parsing the invalid tag
/**the content of the tag is treated invalid either.
*   \param  num    the tag number of the element
*   \param  atts     the attributes of the tag
*/
void fnDBA_DeleteContentParse(void);

/// parsing the <base> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_BaseParse(uint8_t   **atts);

/// parsing the <basefont> tag
/**
*   \param  num    the tag number
*   \param  atts     the attributes of the tag
*/
void fnDBA_BaseFontParse(T_DBA_HTMLElement    num,uint8_t **atts    );

/// parsing the bgsound tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_BgSoundParse( uint8_t **atts );

/// parsing the <Blockquote> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_BlockquoteParse( uint8_t **atts );

/// parsing the <body> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_BodyParse(   uint8_t **atts);

/// parsing the <button> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_ButtonParse( uint8_t     **atts );

/// parsing the <div> tag
/**
*   \param  num    the tag number
*   \param  atts     the attributes of the tag
*/
void fnDBA_DivParse(T_DBA_HTMLElement     num,uint8_t             **atts);

/// parsing the <ol> tag
/**
*   \param  num    the tag number
*   \param  atts     the attributes of the tag
*/
void fnDBA_OlParse(T_DBA_HTMLElement   num,uint8_t           **atts);

/// parsing the <dl> tag
/**
*   \param  num    the tag number
*   \param  atts     the attributes of the tag
*/
void fnDBA_DlParse(T_DBA_HTMLElement  num,uint8_t          **atts );

/// parsing the <fieldset> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_FieldsetParse(   uint8_t    **atts );

/// parsing the <frame> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_FrameParse( uint8_t   **atts );

/// parsing the <iframe> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_IFrameParse( uint8_t   **atts    );

/// parsing the <H> tag
/**
*   \param  num    the tag number
*   \param  atts     the attributes of the tag
*/
void fnDBA_HParse(T_DBA_HTMLElement  num,uint8_t          **atts);

/// parsing the <hr> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_HrParse( const uint8_t **atts );

/// parsing the <img> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_ImgParse( uint8_t   **atts   );

/// parsing the <form> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_FormParse( uint8_t   **atts );

/// parsing the <input> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_InputParse( uint8_t     **atts   );

/// parsing the <li> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_LiParse( uint8_t     **atts );

/// parsing the <meta> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_MetaParse(uint8_t   **atts);

/// parsing the <option> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_OptionParse( uint8_t    **atts,int32_t isGroup);

/// parsing the <p> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_PParse( uint8_t    **atts );

/// parsing the <script> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_ScriptParse( uint8_t   **atts );

/// parsing the <select> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_SelectParse( uint8_t      **atts );

/// parsing the <textarea> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_TextareaParse(   uint8_t    **atts );

/// parsing the nonexistent tag
/**
*   \param name  the name of the tag
*   \param  atts     the attributes of the tag
*/
void fnDBA_InvalidParse(uint8_t *name,uint8_t **atts);

///pop elements from the analysis stack
/**
*   \param  num     pop until meeting this element
*/
void fnDBA_PopElements( T_DBA_HTMLElement  num );

///end parsing list tag
/**
*   \param  num     the tag number
*/
void fnDBA_EndListParse( T_DBA_HTMLElement  num );

///end parsing <p> tag
void fnDBA_EndPParse(void);

///pop all the text nodes till the element 'num'
/**
*   \param  num     the tag number
*/
void fnDBA_GetTextNode( T_DBA_HTMLElement num   );

///end parsing <script> tag
void fnDBA_EndScriptParse(void);

///free the context
/**
*   \param  ctxt     the page context
*/
void fnDBA_ParseCtxtFree(T_DB_ParseCtxtPtr ctxt);

///Saving the current context to history list
T_DB_ParseCtxtPtr fnDBA_ReserveParseCtxt(void);

///set the current page context
/**
*   \param  ctxt     the page context
*/
void fnDBA_SetParseCtxt(T_DB_ParseCtxtPtr ctxt);

///reset the context pointer
void fnDBA_ClearParseCtxt(void );

///set parse state
/**
*   \param  state     the state to set (TRUE or FALSE)
*/
void fnDBA_SetParseState(   int32_t   state );

///Analysis parser init
/**
*   \param  url
*/
int32_t fnDB_AnalysisInit(int8_t *url);

/// parsing the <object> tag
/**
*   \param  atts     the attributes of the tag
*/
void sa_objectParse( uint8_t   **atts );

/// parsing the <param> tag
/**
*   \param  atts     the attributes of the tag
*/
void sa_paramParse( uint8_t   **atts );

/**
 * Parsing the <embed> tag.
 * \param  atts     The attributes of the tag
 */
void sa_embedParse(uint8_t **atts);

/// parsing the <area> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_AreaParse( uint8_t   **atts );

/// parsing the <map> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_MapParse( uint8_t   **atts );

/// parsing the <link> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_LinkParse( uint8_t   **atts );

/// parsing the <marquee> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_MarqueeParse( uint8_t   **atts );

/// parsing the <caption> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_CaptionParse( uint8_t **atts );

/// parsing the <table> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_TableParse( uint8_t   **atts );

/// parsing the <tr> tag
/**
*   \param  num    the tag number of the element
*   \param  atts     the attributes of the tag
*/
void fnDBA_TrParse(
    T_DBA_HTMLElement    num,
    uint8_t            **atts
);

/// parsing the <td> tag
/**
*   \param  num    the tag number of the element
*   \param  atts     the attributes of the tag
*/
void fnDBA_TdParse(
    T_DBA_HTMLElement    num,
    uint8_t            **atts
);

///end parsing <caption> tag
void fnDBA_EndCaptionParse(void);

/// parsing the <big> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_BigParse(uint8_t   **atts);

///Parse the </TITLE> tag
void fnDBA_EndTitleParse(void);

/// parsing the <small> tag
/**
*   \param  atts     the attributes of the tag
*/
void fnDBA_SmallParse(uint8_t   **atts);

/// End parsing the <select> tag
void fnDBA_EndSelectParse(void);

///End parse fieldset
void fnDBA_EndFieldsetParse(void);

void sa_handle_error(void);
#ifdef __cplusplus
}
#endif

#endif /*_DBA_PARSER_H_*/
