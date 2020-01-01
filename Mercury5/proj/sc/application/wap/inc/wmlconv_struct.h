
#ifndef __WMLCONV_STRUCT_H__
#define __WMLCONV_STRUCT_H__

#include <ncc_types.h>

#ifdef NCC_BROWSER_WMLCONV_MODULE_TEST
#undef      static
#define     static
#define NCCBrw_sa_malloc malloc
#define NCCBrw_sa_realloc realloc
#define NCCBrw_sa_free2 free
#define NCCBrw_sa_free(c) free(*c)
#define NCCBrw_sa_strDup strdup
#endif

struct _wthStackNode        /* stack node*/
{
    uint8_t *characters;    /* characterdata*/
    uint8_t **attributes;   /* tag attributes*/
    int16_t elmtType;       /* element type, ELEMENT_START OR ELEMENT_END*/
    int16_t tagType;        /* tag type*/
};
typedef struct _wthStackNode T_DBT_StackNode;
typedef T_DBT_StackNode * T_DBT_StackNodePtr;

struct _wthHtmlNameNode
{
    uint8_t *name;
};
typedef struct _wthHtmlNameNode T_DBT_HtmlNameNode;
typedef struct _wthHtmlNameNode * T_DBT_HtmlNameNodePtr;

struct _wthWorkStack        /* wml trans to html work stack*/
{
    int32_t depth;          /* depth of the stack*/
    int32_t top;            /* top of the stack*/
    int32_t type;           /* stack type */
    void * data;            /* data of the stack*/
};
typedef struct _wthWorkStack T_DBT_WorkStack;
typedef T_DBT_WorkStack * T_DBT_WorkStackPtr;

/* a struct can describe the WML or HTML tagnode.*/
struct _elementData
{
    uint8_t *name;          /* the name of tag*/
    uint8_t **attributes;   /* the attrs of the tag*/
    uint8_t *characters;    /* the characters(content exclude the child tag) of the tag */
};
typedef struct _elementData T_DBT_ElementData;
typedef T_DBT_ElementData * T_DBT_ElementDataPtr;

struct _wthTemplateDoNode
{
    T_DBT_ElementDataPtr htmlElmt;      /* the htmlElmt of do */
    uint8_t *name;                      /* the name of attr of do */
    struct _wthTemplateDoNode *next;    /* next node of do */
};
typedef struct _wthTemplateDoNode T_DBT_TemplateDoNode;
typedef struct _wthTemplateDoNode * T_DBT_TemplateDoNodePtr;


/**
 * wmlTransHandler:
 *     used to save work stack and some data
 */
struct _wmlTransDataStruct
{
    T_DBT_WorkStackPtr workStack;            /* the stack for trans block*/
    T_DBT_WorkStackPtr htmlNameStack;        /* the stack for error handle*/
    T_DBT_TemplateDoNodePtr wmlTemplateData; /* the template block*/

    uint8_t             *xmlEncoding;        /* encoding of wml*/
    uint8_t             *ontimer;            /* ontimer url*/
    uint8_t             *onenterforward;     /* onenterforward url*/
    uint8_t             *onenterbackward;    /* onenterbackward url*/
    uint8_t             *timer;              /* the value of timer*/

    uint8_t             *cdata;              /* cdata content*/

    int16_t             cdataFlag;           /* the flag of cdata*/
    int16_t             curTransTagType;     /* current main trans tag*/
    int16_t             templateContentFlag; /* the flag whether content template tag*/
    int16_t             needPush;            /* whether need to push do and child tag of do onto stack */

    int32_t             isTable;             /* whether current is table process. 1: is; 0: is'nt */
    int16_t             tableColumn;         /* columns of table*/
    int16_t             trColumn;            /* current columns of tr*/
    uint8_t             *tableAlign;         /* the align of table columns, L:left; C:center; R:right; D:default */
    int16_t             cdataCurLen;         /* cur length of cdata.*/
    int16_t             isCdataBeforTag;     /* whether is cdata befor tag.*/
    int16_t             pmode;               /* 1: nowrap; 0:wrap*/
    int16_t             pPreMode;            /* 1: nowrap; 0:wrap*/
    int16_t             pIsEmpty;           /* 1: empty; 0: not empty*/
    int16_t             nouse;               /* for struct align*/
};
typedef struct _wmlTransDataStruct wmlTransContext;
typedef wmlTransContext *wmlTransContextPtr;

#endif /* __WMLCONV_STRUCT_H__ */
