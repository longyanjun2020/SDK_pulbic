
/**
 * @file
 * Global head file
 *
 * WAP structure header file
 *
 * <!-- #interface list begin -->
 * \section wap_struct Interface
 * <!-- #interface list end -->
 */

#ifndef  __WAP_STRUCT_H__
#define  __WAP_STRUCT_H__

#include "ncc_types.h"
#include "wap_config.h"
#include "common_array.h"

#ifdef NCC_BROWSER_CSS2
typedef struct _CSS_Manager CSS_Manager;
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _DB_NetMode {
    DB_NETMODE_HTTP,
    DB_NETMODE_WAP,
    DB_NETMODE_FILE
}T_DB_NetMode;

/** HTML content node type */
typedef enum {
    HTML_NODE_NULL,         /** NULL node */
    HTML_NODE_TEXT ,        /** text node */
    HTML_NODE_BR ,          /** BR node */
    HTML_NODE_P ,           /** P node */
    HTML_NODE_A ,           /** A node */
    HTML_NODE_TABLE,        /** TABLE node */
    HTML_NODE_IMG,          /** IMG node */
    HTML_NODE_LINE,         /** HR node */
    HTML_NODE_FIELD,        /** INPUT node */
    HTML_NODE_OBJECT,       /** OBJECT node */
    HTML_NODE_MARQUEE       /** MARQUEE node */
} T_DB_ContentNodeTp;

/* form field type */
typedef enum {
    FIELD_TYPE_TEXT ,               /** edit box */
    FIELD_TYPE_PASSWORD ,           /** password box */
    FIELD_TYPE_CHECKBOX ,           /** checkbox */
    FIELD_TYPE_RADIOBOX ,           /** radiobox */
    FIELD_TYPE_TEXT_SUBMIT,         /** submit button */
    FIELD_TYPE_IMAGE_SUBMIT,        /** image button */
    FIELD_TYPE_RESET,               /** reset button */
    FIELD_TYPE_HIDDEN,              /** hide control */
    FIELD_TYPE_BUTTON,              /** button */
    FIELD_TYPE_FILE,                /** file button */
    FIELD_TYPE_OPTION_LIST_SINGLE,  /** single select */
    FIELD_TYPE_OPTION_LIST_MULTI,   /** multiple select */
    FIELD_TYPE_TEXTAREA             /** multiple edit box */
}T_DB_FieldType;

/* P type */
typedef enum {
    P_TYPE_P_BEGIN ,         /** Begining of tag<p> */
    P_TYPE_P_END ,           /** Ending of tag<p> */
    P_TYPE_H_BEGIN ,         /** Begining of tag<h1>~<h6> */
    P_TYPE_H_END ,           /** Ending of tag<h1>~<h6> */
    P_TYPE_FIELDSET_BEGIN ,  /** Begining of tag<fieldset> */
    P_TYPE_FIELDSET_END ,    /** Ending of tag<fieldset> */
    P_TYPE_DIV_BEGIN ,       /** Begining of tag<div> */
    P_TYPE_DIV_END ,         /** Ending of tag<div> */
    P_TYPE_CENTER_BEGIN,     /** Begining of tag<center> */
    P_TYPE_CENTER_END,       /** Ending of tag<center> */
} T_DB_PType;

/* position information */
struct pos{
    int16_t x;
    int32_t y;
    int32_t height;
    int16_t width;
};

typedef struct pos T_DB_Pos;
typedef T_DB_Pos * T_DB_PosPtr;

/* for indexing nodes */
typedef int32_t T_DB_ContentLinkIdx;
typedef int32_t T_DB_TextNodeIdx;
typedef int32_t T_DB_ANodeIdx;
typedef int32_t T_DB_PNodeIdx;
typedef int32_t T_DB_TableNodeIdx;
typedef int32_t T_DB_TrNodeIdx;
typedef int32_t T_DB_TdNodeIdx;
typedef int32_t T_DB_ImgNodeIdx;
typedef int32_t T_DB_FormNodeIdx;
typedef int32_t T_DB_FieldNodeIdx;
typedef int32_t T_DB_OptionNodeIdx;
typedef int32_t T_DB_ObjectNodeIdx;
typedef int32_t T_DB_LineNodeIdx;
typedef int32_t T_DB_YPosIdx;
typedef int32_t T_DB_BoxIdx;
typedef int32_t T_DB_AttrIdx;
typedef int32_t T_DB_AAttrIdx;

typedef int32_t T_DB_iPtr;

typedef enum _Box_ClearType{
    BOX_CLEAR_TYPE_NONE,
    BOX_CLEAR_TYPE_LEFT,
    BOX_CLEAR_TYPE_RIGHT,
    BOX_CLEAR_TYPE_BOTH,
}Box_ClearType;

typedef enum _Box_DisplayType{
    BOX_DISPLAY_TYPE_INLINE,
    BOX_DISPLAY_TYPE_NONE,
    BOX_DISPLAY_TYPE_WAP_MARQUEE,
}Box_DisplayType;

#define MARQUEE_DEFAULT_WORD_WEIGHT 8

/**
 * move style of the marquee block
 */
typedef enum _Box_MarqueeStyleType{
    BOX_MARQUEE_STYLE_TYPE_SCROLL,
    BOX_MARQUEE_STYLE_TYPE_SLIDE,
    BOX_MARQUEE_STYLE_TYPE_ALTERNATE,
}Box_MarqueeStyleType;

/**
 * the direction of the moving
 */
typedef enum _Box_MarqueeDirType{
    BOX_MARQUEE_DIR_TYPE_RTL, /**< from right to left */
    BOX_MARQUEE_DIR_TYPE_LTR, /**< from left to right */
}Box_MarqueeDirType;

/**
 * marquee loops times type
 */
typedef enum _Box_MarqueeLoopType{
    BOX_MARQUEE_LOOP_INFINITE,
    BOX_MARQUEE_LOOP_INTEGER,
}Box_MarqueeLoopType;

/**
 * marquee speed type
 */
typedef enum _Box_MarqueeSpeed{
    BOX_MARQUEE_SPEED_INVALID,
    BOX_MARQUEE_SPEED_SLOW,
    BOX_MARQUEE_SPEED_NORMAL,
    BOX_MARQUEE_SPEED_FAST,
}Box_MarqueeSpeed;

/**
 * marquee description struct
 */
typedef struct _Box_Marquee{
    Box_MarqueeStyleType    style;
    Box_MarqueeDirType      dir;
    Box_MarqueeSpeed        speed;
    Box_MarqueeLoopType     loopType;
    int32_t                 loop;
    int32_t                 startIndex;
    int32_t                 stopIndex;
    int32_t                 width;
}Box_Marquee;

typedef enum {
    BOX_TOP = 0,
    BOX_RIGHT,
    BOX_BOTTOM,
    BOX_LEFT,
    BOX_NUM_OF_DIMENSION,
} BoxDimension;

typedef enum _BorderStyleType{
    BORDER_STYLE_NONE,
    BORDER_STYLE_HIDDEN,
    BORDER_STYLE_DOTTED,
    BORDER_STYLE_DASHED,
    BORDER_STYLE_SOLID,
    BORDER_STYLE_DOUBLE,
    BORDER_STYLE_GROOVE,
    BORDER_STYLE_RIDGE,
    BORDER_STYLE_INSET,
    BORDER_STYLE_OUTSET,
}BorderStyleType;

#define COLOR_TRANSPARENT       0xff000000

typedef struct _BoxDimSize BoxDimSize;

struct _BoxDimSize
{
    float       width;
    float       height;
};

/** color type */
typedef int32_t ColorType;

#define COLOR_TRANSPARENT_MASK      (0xff000000)
#define COLOR_IS_TRANSPARENT(color) (color & COLOR_TRANSPARENT_MASK)
#define COLOR_SET_TRANSPARENT(color) (color = (int32_t)COLOR_TRANSPARENT_MASK)

typedef struct _BoxAttribute {
    float           margin[BOX_NUM_OF_DIMENSION];
    float           padding[BOX_NUM_OF_DIMENSION];
    float           borderWidth[BOX_NUM_OF_DIMENSION];
    BorderStyleType borderStyle[BOX_NUM_OF_DIMENSION];
    ColorType       borderColor[BOX_NUM_OF_DIMENSION];
    Box_DisplayType display;    /**< display:[ none | -wap-marquee ] */
    Box_Marquee     marquee;
    BoxDimSize      dimSize;
    Box_ClearType   clearType;  /**< clear:[none | left | right | both] */
}BoxAttribute;

///Defining the struct of content link.
struct contentLink{
    T_DB_ContentNodeTp     nodeType;       /*the type of the node*/
    T_DB_Pos    pos;            /*the position of the node*/
    T_DB_ContentLinkIdx  next;           /*the pointer to the next node*/
    T_DB_ContentLinkIdx  startTagIndex; /* if current content is a end node(such as </p>), then the starTag is the index
                                        * of corresponding start node. Otherwise the value of startTag means nothing.
                                        * The initialized value is 0.
                                        */
    T_DB_iPtr  content;        /*the pointer to the content of the node*/
    int16_t     disabled;       /*if the node disabled*/
};

typedef struct contentLink      T_DB_ContentLink;
typedef T_DB_ContentLink*       T_DB_ContentLinkPtr;

///Defining type of option
typedef enum {
    OPTION_TYPE_NORMAL ,        /**<  Normal option*/
    OPTION_TYPE_GROUP ,         /**<  Optgroup*/
    OPTION_TYPE_INGROUP         /**<  Option in Optgroup*/
    }E_OptionFlag;

///Defining the struct of formTable: optionNode
struct optionNode{
    int8_t  *name;                  /**<the name of the entry */
    int8_t  *cp_submit_value;   /**<the value to submit;The memory of it must been allocated by function malloc*/
    int8_t  *optionText;            /**<*/
    int8_t  *onpick;                /**<*/
    uint8_t selectedOrNot;          /** The option is selected or not*/
    uint8_t origionSelectedOrNot;/** The option is selected or not when not changed*/
    T_DB_OptionNodeIdx  pre;   /** the pre entry; if pre = 0; first option */
    T_DB_OptionNodeIdx  next;   /** the next entry; if next = 0; next = NULL */
    T_DB_FieldNodeIdx   parent; /** the parent node */
    E_OptionFlag        optionFlag;       /**< If this is a optgroup */
    int32_t             disabled;         /**< If this is a disable option */
};

typedef struct optionNode         T_DB_OptionNode;
typedef T_DB_OptionNode          *T_DB_OptionNodePtr;

///Defining the struct of fieldNode
 struct fieldNode{
     int8_t             *id;           /*the identification of the form field*/
     int8_t             *name;         /*the name of the form field*/
     int8_t             *iname;         /*the name of the form field for wml select*/
     int8_t             *value;        /*the input value of the form field;malloc*/
     int8_t             *ivalue;        /*the input value of the form field for wml select*/
     int8_t             *origValue;   /*the origin value of the form field*/
     int8_t             *format;

#ifdef DB_USING_SCRIPT
     int8_t             *onClick;      /*the click event*/
     int8_t             *onBlur;       /*the blur event*/
     int8_t             *onChange;     /*when text area changes, this event happens*/
     int8_t             *onFocus;      /*when text area gets the focus, this event happens*/
#endif /*DB_USING_SCRIPT*/

     uint8_t            type;         /*the type of the form field*/
     uint8_t            size;         /*the size of the text display*/
     uint8_t            rows;         /*the rows of TEXTAREA*/
     uint8_t            selectIndex;  /*the select index of single options*/
     int16_t            maxsize;      /*the maxsize of the input value*/
     T_DB_OptionNodeIdx selectList;   /*select options*/
     T_DB_FieldNodeIdx  pre;          /*the pointer to its brother before it*/
     T_DB_FieldNodeIdx  next;         /*the pointer to its brother after it*/
     T_DB_FormNodeIdx   form;         /*******************************************************
                                       *  the pointer to the form which the field belongs to
                                       *  the pointer is an index of the array of form node
                                       *******************************************************/
     T_DB_ImgNodeIdx    img;          /*the pointer to the image button*/
     int16_t            emptyOk;      /*if allow input nothing*/
     int16_t            accessKey;    /*accesskey */
     int8_t             *inputFormat;   /**< -wap-input-format */
     int32_t            inputRequired;  /**< -wap-input-required: [TRUE|FALSE] */
 };

 typedef struct fieldNode          T_DB_FieldNode;
 typedef   T_DB_FieldNode         *T_DB_FieldNodePtr;

///Defining the struct of formNode.
struct formNode{
     int8_t             *id;                 /*the identification of the form node*/
     int8_t             *name;               /*the name of the form node*/
     int8_t             *action;             /*the action of the form,malloc*/
     int8_t             *encType;            /*the enctype of the form*/
#ifdef DB_USING_SCRIPT
     int8_t             *onReset;            /*the reset event*/
     int8_t             *onSubmit;           /*the submit event*/
#endif /*DB_USING_SCRIPT*/
     int16_t            method;             /*the submit method  of the form*/
     T_DB_FieldNodeIdx  firstChild;         /*the pointer to its first child*/
     T_DB_FormNodeIdx   pre;                /*the pointer to its brother before it*/
     T_DB_FormNodeIdx   next;               /*the pointer to its brother after it*/
 };

typedef struct formNode          T_DB_FormNode;
typedef T_DB_FormNode           *T_DB_FormNodePtr;

typedef enum _TextTransformType{
    TEXT_TRANSFORM_NONE,
    TEXT_TRANSFORM_CAPITALIZE,
    TEXT_TRANSFORM_UPPERCASE,
    TEXT_TRANSFORM_LOWERCASE,
}TextTransformType;

/**
 * css property visibility
 */
typedef enum _VisibilityType{
    VISIBILITYTYPE_VISIBLE, /**< visibility: visible */
    VISIBILITYTYPE_HIDDEN,  /**< visibility: hidden */
}VisibilityType;

/**
 * css property vertical-align type define
 */
typedef enum _VerticalAlignType{
    VERTICAL_ALIGN_ERROR,
    VERTICAL_ALIGN_BASELINE,
    VERTICAL_ALIGN_SUB,
    VERTICAL_ALIGN_SUPER,
    VERTICAL_ALIGN_TOP,
    VERTICAL_ALIGN_TEXT_TOP,
    VERTICAL_ALIGN_MIDDLE,
    VERTICAL_ALIGN_BOTTOM,
    VERTICAL_ALIGN_TEXT_BOTTOM,
}VerticalAlignType;

///Defining the struct of textNode.
struct textNode{
    int8_t*           id;             /*  the identification of the text node*/
    int8_t*           content;        /*  the content of text block*/
    int16_t           contentLen;     /*  the length of text block*/
    T_DB_AttrIdx      attr;           /*****************************************************************
                                    *  the index of attribute table that records the attributes
                                    *  of all textNodes and aNodes. By this index ,we can find the
                                    *  attribute of each textNode and anode
                                    *****************************************************************/
    float               indent;         /**< text-indent: */
    TextTransformType   textTransform;  /**< text-transform: */
    VerticalAlignType   verticalAlign;  /**< vertical-align: baseline ... */
    VisibilityType      visibilityType; /**< visiblity: */
    Box_DisplayType     displayType;    /**< display: none,inline, ... */
};

typedef struct textNode          T_DB_TextNode;
typedef T_DB_TextNode           *T_DB_TextNodePtr;

/* In accordance with the definition in nccsa.h */
typedef enum _HTMLTagAlignType{
    HTML_TAG_ALIGN_LEFT     =       0x01,       /* ALIGN_LEFT, */
    HTML_TAG_ALIGN_RIGHT    =       0x04,       /* ALIGN_RIGHT, */
    HTML_TAG_ALIGN_CENTER   =       0x02,       /* ALIGN_CENTER, */
    HTML_TAG_ALIGN_TOP      =       0x08,       /* ALIGN_TOP, */
    HTML_TAG_ALIGN_BOTTOM   =       0x20,       /* ALIGN_BOTTOM, */
    HTML_TAG_ALIGN_MIDDLE   =       0x10,       /* ALIGN_MIDDLE, */
    HTML_TAG_ALIGN_INVALID  =       -1,         /* ALIGN_INVALID, */
}HTMLTagAlignType;

/**
 * the state of the marquee
 */
typedef enum _MarqeeState{
    MARQEE_STATE_NO_MARQEE,
    MARQEE_STATE_MARQEE_BEGIN,
    MARQEE_STATE_MARQEE_END,
}MarqeeState;

/* Defining the struct of pNode */
struct pNode{
    int16_t                 align;          /**< The align attribute of element <p> define as HTMLTagAlignType*/
    int16_t                 type;           /**< Defined by T_DB_PType*/
    int16_t                 nowrap;         /**< 1: nowrap; 0:wrap*/
    int16_t                 nouse;
    int16_t                 boxAttrIndex;   /* the index of box attribute */
    int16_t                 visibilityType; /* here should be T_DB_TextNode */
    ColorType               bgColor;        /* the background color of p node */
    MarqeeState             marqeeState;
    Box_Marquee             boxMarquee;     /* marquee parameter */
};

typedef struct pNode            T_DB_PNode;
typedef T_DB_PNode*             T_DB_PNodePtr;

///Defining the struct of hr
struct lineNode{
    int16_t                 align;     /*the align attribute of element <p>*/
    int16_t                 noShade;
    int16_t                 width;
    int16_t                 size;
};

typedef struct lineNode            T_DB_LineNode;
typedef T_DB_LineNode*             T_DB_LineNodePtr;

///Defining the struct of attribute of element <a>
struct aAttr{
    int8_t              *id;                    /*the identification of the element <a>*/
    int8_t              *href;                  /*the href which the element <a> points to*/
    int8_t              *name;                  /*the name attribute of the element <a>*/

#ifdef DB_USING_SCRIPT
    int8_t              *onClick;               /*the click event: when user clicks the anchor, this event happens*/
    int8_t              *onMouseOver;           /*the mouse over event*/
    int8_t              *onMouseOut;            /*the mouse out event*/
#endif /*DB_USING_SCRIPT*/

    T_DB_AttrIdx        unclickedAttr;          /*****************************************************************
                                                *  the index of attribute table that records the attributes
                                                *  of all textNodes and aNodes. By this index ,we can find the
                                                *  attribute of each textNode and anode. In here, this points to
                                                *  the unclicked text attributes of element <a>
                                                *****************************************************************/
    T_DB_AttrIdx        clickedAttr;            /*****************************************************************
                                                *  the index of attribute table that records the attributes
                                                *  of all textNodes and aNodes. By this index ,we can find the
                                                *  attribute of each textNode and anode. In here, this points to
                                                *  the clicked text attributes of element <a>
                                                *****************************************************************/
    int16_t             accessKey;              /********************************************
                                                *  the value of attribute accesskey.
                                                *  If the accesskey is equal to '0xFF',
                                                *  the attribute accesskey doesn't define
                                                ********************************************/

    int16_t             unUsed;
};

typedef struct  aAttr    T_DB_AAttr;
typedef T_DB_AAttr      *T_DB_AAttrPtr;

 ///Defining the struct of aNode
struct aNode{
    int8_t*             content;              /* the content of element <a>*/
    int16_t             contentLen;           /* the length of text block*/
    T_DB_AAttrIdx       aAttr;                /* the index of A attribute*/
};

typedef struct aNode    T_DB_ANode;
typedef T_DB_ANode*     T_DB_ANodePtr;

struct _TdNode{
    int8_t*     id;             /** ID of the td */
    T_DB_Pos    pos;            /** position and size */
    T_DB_ContentLinkIdx content;    /** index of the first content node of the td */
    int16_t     align;          /** "align" attribute. 0: left, 1: center, 2: right */
    int16_t     valign;         /** "valign" attribute. 0: middle; 1: top; 2: bottom; */
    int16_t     innerHeight;    /** the sum of all the nodes' height included in this td */
    int16_t     rowSpan;        /** "rowspan" attribute. default to 1 */
    int16_t     colSpan;        /** "colspan" attribute. default to 1 */
    int32_t     bgcolor;        /** "bgcolor" attribute. */
    T_DB_TdNodeIdx next;        /** the index of next node */
    int16_t     dummy;          /** for 32 bit align */
    VisibilityType      visibilityType;
};

typedef struct _TdNode T_DB_TdNode;
typedef T_DB_TdNode*   T_DB_TdNodePtr;

struct _TrNode{
    int8_t*         id;         /** ID of the tr */
    int16_t         align;      /** "align" attribute. 0: left, 1: center, 2: right */
    int16_t         valign;     /** "valign" attribute. 0: middle; 1: top; 2: bottom; */
    int32_t         bgcolor;    /** "bgcolor" attribute. */
    T_DB_TdNodeIdx  content;    /** index of the first td of the tr */
    T_DB_TrNodeIdx  next;       /** the index of next node */
};

typedef struct _TrNode T_DB_TrNode;
typedef T_DB_TrNode*   T_DB_TrNodePtr;

struct _TableNode{
    int8_t*         id;         /** ID of the table */
    T_DB_Pos        pos;        /** position and size of the table */
    int16_t         border;     /** "border" attribute */
    int16_t         cellspadding;   /** the width between td and inner element.*/
    int16_t         cellspacing;    /** the width along tds, and between table and tds. */
    T_DB_TrNodeIdx  content;    /** index of first TR node */
    int32_t         bgcolor;    /** "bgcolor" attribute */
    int32_t         width;      /** the width of table. high 16 bits stand for pixel or percentage(1:percentage;0:pixel), low 16 bits stand for the value.*/
};

typedef struct _TableNode T_DB_TableNode;
typedef T_DB_TableNode*   T_DB_TableNodePtr;

///Defining the struct of imgNode
struct imgNode{
    int8_t            *id;              /**<the identification of element <img>*/
    int8_t            *alt;             /**<the value of alt attribute of element <img>*/
    int8_t            *src;             /**<the value of src attribute of element <img>*/
    uint8_t           *data;          /**<the data of image */
    int8_t            *link;            /**<the link of the image*/
#ifdef DB_USING_AREA
    int8_t        *mapname;/*for map/area*/
#endif

    int32_t        imgSize;          /**<the size of image data*/
    int16_t        nouse;
    int16_t        align;         /**<the "align" attribute of element <img>.align = 0: left; 1: center; 2: right;*/
    int8_t         state;         /**<0: the image data hasn't been downloaded; 1: the image data has been downloaded*/
    int8_t         border;  /**<border height*/
    T_DB_AAttrIdx  aindex; /**<index of a attribute*/
    int16_t        hspace;  /**<*/
    int16_t        vspace;  /**<*/
    float          width;       /**<the width of the image*/
    float          height;  /**<the height of the image*/
    float          originalWidth; /**< the original width of img set on page */
    float          originalHeight;/**< the original height of img set on page*/
    int32_t          dspReady;   /**< 1: download success and relayout completely*/
};

typedef struct imgNode          T_DB_ImgNode;
typedef T_DB_ImgNode           *T_DB_ImgNodePtr;

///Defining the struct of imgNode
struct objectNode{
    int8_t            *classId; /**<This attribute may be used to specify the location of an object's implementation via a URI. It may be used together with, or as an alternative to the data attribute, depending on the type of object involved.*/
    int8_t            *codeBase;    /**<This attribute specifies the base path used to resolve relative URIs specified by the classid, data, and archive attributes. When absent, its default value is the base URI of the current document*/
    int8_t            *data;        /**<This attribute may be used to specify the location of the object's data, for instance image data for objects defining images, or more generally, a serialized form of an object which can be used to recreate it. If given as a relative URI, it should be interpreted relative to the codebase attribute*/
    uint8_t          *type;     /**<This attribute specifies the content type for the data specified by data*/
    int8_t            *name;        /**<the name of the object*/
    int8_t        **params; /**<params pairs*/
    uint8_t       *appData; /**<data*/
    int32_t       length;       /**<length*/
    int16_t           width;         /**<the width of the object*/
    int16_t           height;        /**<the height of the object*/
    int16_t       state;          /**<data state*/
    int16_t       unUsed;   /**<Boundary.*/
};

typedef struct objectNode          T_DB_ObjectNode;
typedef T_DB_ObjectNode           *T_DB_ObjectNodePtr;

///Defining the struct of attribute table cell
struct comnAttr{
    int32_t     color;             /**<the color of the text*/
    int32_t     bcolor;            /**<the background color of the text*/
    int16_t     size;              /**<the size of the text*/
   /**
    *  the 0 bit of low byte is "Bold" attribute,
    *  the 1 bit of low byte is "Italic" attribute,
    *  the 2 bit of low byte is "Underline" attribute
    *  the 3 bit of low byte is "strike" attribute
    *  the 4 bit of low byte is "subscript" attribute
    *  the 5 bit of low byte is "superscript" attribute
    *  the 6 bit of low byte is "overline" attribute
    *  the 7 bit of low byte is "smallcaps" attribute
    *  the 8 bit of low byte is "blink" attribute
    *  the 9 bit of low byte is "white-space: nowrap" attribute
    *  the 10 bit of low byte is "float: left" attribute
    *  the 11 bit of low byte is "float: right" attribute
    */
    int16_t     compactAttr;
};

typedef struct comnAttr        T_DB_ComnAttr;
typedef T_DB_ComnAttr         *T_DB_ComnAttrPtr;

typedef enum _HTMLTagCompactAttr{
    HTML_TAG_COMPACT_ATTR_BOLD          =   1,
    HTML_TAG_COMPACT_ATTR_ITALIC        =   1<<1,
    HTML_TAG_COMPACT_ATTR_UNDERLINE     =   1<<2,
    HTML_TAG_COMPACT_ATTR_STRIKE        =   1<<3,
    HTML_TAG_COMPACT_ATTR_SUBSCRIPT     =   1<<4,
    HTML_TAG_COMPACT_ATTR_SUPERSCRIPT   =   1<<5,
    HTML_TAG_COMPACT_ATTR_OVERLINE      =   1<<6,
    HTML_TAG_COMPACT_ATTR_SMALLCAPS     =   1<<7,
    HTML_TAG_COMPACT_ATTR_BLINK         =   1<<8,
    HTML_TAG_COMPACT_ATTR_NOWRAP        =   1<<9,
    HTML_TAG_COMPACT_ATTR_FLOAT_LEFT    =   1<<10,
    HTML_TAG_COMPACT_ATTR_FLOAT_RIGHT   =   1<<11,
}HTMLTagCompactAttr;

#define HTML_TAG_ATTR_SET_BIT(a, b)         ((a) |= (b))
#define HTML_TAG_ATTR_HAVE_BIT(a, b)        ((a) & (b))
#define HTML_TAG_ATTR_CLEAR_BIT(a, b)       ((a) &= (~b))

/* style of list tags */
typedef int32_t HTML_ListAttribute;

typedef struct _HTML_TagStyle{
    T_DB_ComnAttrPtr        textAttr;
    T_DB_PNodePtr           paraAttr;
    T_DB_FieldNodePtr       fieldAttr;
    BoxAttribute            *boxAttr;
    T_DB_TextNodePtr        visualAttr;
    HTML_ListAttribute      listAttr;
}HTML_TagStyle;

#ifdef DB_USING_BGSOUND
typedef struct _tbgSound
{
    int8_t * contentType;/**<content type of the music file*/
    int8_t * src;           /**<url address of the music file*/
    int8_t * data;      /**<data of the music file*/
    int32_t len;            /**<length of the music file*/
    int16_t state;      /**<download state of the music file:1:success 0:pending -1:fail*/
    int16_t loop;       /**<play count of the music file*/
}T_DB_bgSound;
#endif

/* a forward declare for box attribute table, the define of it is in the sa_attribute.h*/
typedef CommonArray BoxAttributeTable;

/**
 * Defining the struct of analyzing context
 * More Comment:
 *          this struct is used by the so-called sa module,layout and render(from a interface)
 *          for more rational refactor, we suggest add a tree data structure for the parser,
 *          then it be covnerted to some other data structure by layout module then THIS ds will
 *          be get used by the render from a interface
 */
struct parseCtxt{
    int8_t                  *encoding;  /**<charset of the page*/
    int8_t                  *base;      /**<base path of the page*/
    int8_t                  *title;     /**<title of the page*/
    int8_t                  *refresh;   /**<refresh of the page*/
    int8_t                  *backward;  /**<backward of the page,for wml only*/
    void                  *imgBuf;            /**<img buffer list*/
    void                  *aLink;             /**<anchor list*/
#ifdef DB_USING_SCRIPT
    void                  *javaCtxt;          /**<js context*/
    int8_t                  *onLoad;            /**<onload attribute of the page*/
    int8_t                  *onUnload;          /**<unload attribute of the page*/
    int8_t                  *domain;            /**<domain attribute of the page*/
#endif /*DB_USING_SCRIPT*/
    int32_t                 textColor;          /**<default text color of the page*/
    int32_t                 linkColor;          /**<default link color of the page*/
    int32_t                 vlinkColor;         /**<default vlink color of the page*/
    int32_t                 bgColor;            /**<default bg color of the page*/
    int16_t                 baseFont;           /**<base font size of the page*/
    int16_t                 compactAttr;     /**< default font-style like italic */
    T_DB_ContentLinkIdx     contentHead;/**<first iPtr of the page*/
    T_DB_ContentLinkIdx     contentCur; /**<current iPtr of the page*/
    T_DB_FormNodeIdx        form;       /**<first form iptr of the page*/
    T_DB_ImgNodeIdx         bgImg;      /**<bg img iptr of the page*/
    int32_t                 parseState; /**<state of parser of the page*/
#ifdef DB_USING_BGSOUND
    T_DB_bgSound            *bgSound;   /**<bg sound struct of the page*/
#endif
#ifdef DB_USING_AREA
    void                  *mapList;   /**<map list of the page*/
#endif
#ifdef DB_USING_MARQUEE
    void                  *marqueeList;/**<marqueeList of the page*/
#endif
    int32_t                 docType;    /**<doc type of the page*/
    int8_t                  *docText;   /**<wml cache of the page*/
    void *                pNodeCollect;/**<main node collect of the page*/
    void *                pACollect;  /**<a node collect of the page*/
    void *                pTextCollect;/**<text node collect of the page*/
#ifdef NCC_BROWSER_CSS2
    CSS_Manager *cssMgr;        /**< css manager handler */
#endif

    /* for different attribute tabel for the PARSED tags*/
    BoxAttributeTable    * boxAttrTable; /* the table ref for box attribute, if the browser dont
                                                support this feature, we can set it as null*/
   int32_t * htmlTagsFlag; /* to indicate whether the tags can be parsed.*/
};

typedef struct parseCtxt      T_DB_ParseCtxt;
typedef T_DB_ParseCtxt       *T_DB_ParseCtxtPtr;

#define BROWSER_FLAG_ISSTOP  0x01

#define BROWSER_FLAG_ERROR_OUT_OF_MEMORY   0x01
#define BROWSER_FLAG_ERROR_MASK            0xFFFF

///charset string length
#define DB_CHARSET_LENGTH 31
///charset string length
#define DB_REFRESHURL_LENGTH 1023
///default local charset,the length must less than DB_CHARSET_LENGTH
#define DB_DEFAULT_CHARSET "UTF-8"
///Defining the struct of browser context struct
struct _browserCtxt{
    int8_t              *version;               /**<version of browser*/
    T_DB_Pos            scrInfo;                    /**<screen info of browser*/
    void              *cookieList;                /**<cookie List of browser*/
    void              *authList;              /**<auth list of browser*/
    void              *httpAliveCtxt;         /**<keepalive http context*/
    void * cpmCtxt;                   /**<context of current parser*/
    int8_t              nativeCharSet[DB_CHARSET_LENGTH+1];/**<local charset*/
    int8_t              refreshUrl[DB_REFRESHURL_LENGTH+1]; /**<doc charset*/
    int16_t             stateFlag;              /**<1st bit:stop flag;2nd bit:if support table;3rd bit:if download img*/
    int16_t             errFlag;
    int16_t             unUsed;
};

typedef struct _browserCtxt      T_DB_BrowserCtxt;
typedef T_DB_BrowserCtxt       *T_DB_BrowserCtxtPtr;

#define MARQUEE_LOOP_DEFAULT -1  /**<Not limited*/
#define MARQUEE_SCROLLAMOUT_DEFAULT 6
#define MARQUEE_SCROLLDELAY_DEFAULT 85
#define MARQUEE_DIRECTION_LEFT      "left"
#define MARQUEE_DIRECTION_RIGHT     "right"
#define MARQUEE_DIRECTION_UP        "up"
#define MARQUEE_DIRECTION_DOWN      "down"

///Defining the struct of marquee element
typedef struct _MarqueeStruct
{
    int8_t * content;                           /**<text content */
    int16_t direction;                      /**<scroll Direction*/
    int16_t width;                          /**<width*/
    int16_t height;                         /**<height*/
    int16_t loop;                           /**<play count*/
    int16_t scrollAmout;                        /**<scroll space every time*/
    int16_t scrollDelay;                        /**<scroll interval*/
}MarqueeStruct;

///Defining the struct of Y pos element
struct _ifYPosLink {
    int32_t y;                                  /**<y pos of the node*/
    T_DB_ContentLinkIdx iNode;                  /**<iptr of the main node*/
    T_DB_YPosIdx next;                          /**<next Y pos element*/
    int16_t nouse;                              /**<next Y pos element*/
};

typedef struct _ifYPosLink  T_DB_ifYPosLink;
typedef T_DB_ifYPosLink     *T_DB_ifYPosLinkPtr;

///Define the struct of box element.
struct _ifBoxLink{
    T_DB_ContentLinkIdx iNode;                  /**< iPtr of the main node.*/
    T_DB_BoxIdx next;                           /**< next box element.*/
};
typedef struct _ifBoxLink  T_DB_ifBoxLink;
typedef T_DB_ifBoxLink     *T_DB_ifBoxLinkPtr;

/* Defining the node for memory manage */
#define INULL                   0
#define DB_MM_STRING            0
#define DB_MM_NODE              1
#define DB_MM_TEXT              2
#define DB_MM_A                 3
#define DB_MM_AATTR             4
#define DB_MM_IMG               5
#define DB_MM_P                 6
#define DB_MM_YPOS              7
#define DB_MM_BOX               8
#define DB_MM_LINE              9
#define DB_MM_FORM              10
#define DB_MM_FIELD             11
#define DB_MM_OPTION            12
#define DB_MM_TABLE             13
#define DB_MM_TR                14
#define DB_MM_TD                15
#define DB_MM_OBJECT            16
#define DB_MM_MAX               17

#define DB_NODEMMGET(index)      (T_DB_ContentLinkPtr)NCCBrw_sa_mmGet(DB_MM_NODE,index)
#define DB_NODEMMAPPEND(pIndex)  (T_DB_ContentLinkPtr)NCCBrw_sa_mmAppend(DB_MM_NODE, pIndex)

#define DB_TEXTMMGET(index)      (T_DB_TextNodePtr)NCCBrw_sa_mmGet(DB_MM_TEXT,index)
#define DB_TEXTMMAPPEND(pIndex)  (T_DB_TextNodePtr)NCCBrw_sa_mmAppend(DB_MM_TEXT, pIndex)

#define DB_AMMGET(index)         (T_DB_ANodePtr)NCCBrw_sa_mmGet(DB_MM_A,index)
#define DB_AMMAPPEND(pIndex)     (T_DB_ANodePtr)NCCBrw_sa_mmAppend(DB_MM_A, pIndex)

#define DB_AATTRMMGET(index)     (T_DB_AAttrPtr)NCCBrw_sa_mmGet(DB_MM_AATTR,index)
#define DB_AATTRMMAPPEND(pIndex) (T_DB_AAttrPtr)NCCBrw_sa_mmAppend(DB_MM_AATTR, pIndex)

#define DB_PMMGET(index)         (T_DB_PNodePtr)NCCBrw_sa_mmGet(DB_MM_P,index)
#define DB_PMMAPPEND(pIndex)     (T_DB_PNodePtr)NCCBrw_sa_mmAppend(DB_MM_P, pIndex)

#define DB_TABLEMMGET(index)     (T_DB_TableNodePtr)NCCBrw_sa_mmGet(DB_MM_TABLE,index)
#define DB_TABLEMMAPPEND(pIndex) (T_DB_TableNodePtr)NCCBrw_sa_mmAppend(DB_MM_TABLE,pIndex)

#define DB_TRMMGET(index)        (T_DB_TrNodePtr)NCCBrw_sa_mmGet(DB_MM_TR,index)
#define DB_TRMMAPPEND(pIndex)    (T_DB_TrNodePtr)NCCBrw_sa_mmAppend(DB_MM_TR,pIndex)

#define DB_TDMMGET(index)        (T_DB_TdNodePtr)NCCBrw_sa_mmGet(DB_MM_TD,index)
#define DB_TDMMAPPEND(pIndex)    (T_DB_TdNodePtr)NCCBrw_sa_mmAppend(DB_MM_TD, pIndex)

#define DB_IMGMMGET(index)       (T_DB_ImgNodePtr)NCCBrw_sa_mmGet(DB_MM_IMG,index)
#define DB_IMGMMAPPEND(pIndex)   (T_DB_ImgNodePtr)NCCBrw_sa_mmAppend(DB_MM_IMG, pIndex)

#define DB_FORMMMGET(index)      (T_DB_FormNodePtr)NCCBrw_sa_mmGet(DB_MM_FORM,index)
#define DB_FORMMMAPPEND(pIndex)  (T_DB_FormNodePtr)NCCBrw_sa_mmAppend(DB_MM_FORM, pIndex)

#define DB_FIELDMMGET(index)     (T_DB_FieldNodePtr)NCCBrw_sa_mmGet(DB_MM_FIELD,index)
#define DB_FIELDMMAPPEND(pIndex) (T_DB_FieldNodePtr)NCCBrw_sa_mmAppend(DB_MM_FIELD, pIndex)

#define DB_OPTIONMMGET(index)    (T_DB_OptionNodePtr)NCCBrw_sa_mmGet(DB_MM_OPTION,index)
#define DB_OPTIONMMAPPEND(pIndex) (T_DB_OptionNodePtr)NCCBrw_sa_mmAppend(DB_MM_OPTION, pIndex)

#define DB_YPOSMMGET(index)     (T_DB_ifYPosLinkPtr)NCCBrw_sa_mmGet(DB_MM_YPOS,index)
#define DB_YPOSMMAPPEND(pIndex) (T_DB_ifYPosLinkPtr)NCCBrw_sa_mmAppend(DB_MM_YPOS, pIndex)

#define DB_BOXMMGET(index)      (T_DB_ContentLinkPtr)NCCBrw_sa_mmGet(DB_MM_BOX,index)
#define DB_BOXMMAPPEND(pIndex)  (T_DB_ContentLinkPtr)NCCBrw_sa_mmAppend(DB_MM_BOX, pIndex)

#define DB_OBJECTMMGET(index)   (T_DB_ObjectNodePtr)NCCBrw_sa_mmGet(DB_MM_OBJECT,index)
#define DB_OBJECTAPPEND(pIndex) (T_DB_ObjectNodePtr)NCCBrw_sa_mmAppend(DB_MM_OBJECT, pIndex)

#define DB_LINEMMGET(index)     (T_DB_LineNodePtr)NCCBrw_sa_mmGet(DB_MM_LINE,index)
#define DB_LINEMMAPPEND(pIndex) (T_DB_LineNodePtr)NCCBrw_sa_mmAppend(DB_MM_LINE, pIndex)

#ifdef __cplusplus
}
#endif

#endif /* __WAP_STRUCT_H__ */
