
/**
 * @file
 * NCC mms parser parse
 *
 * Parse helper routines used in NCC mms smil parsing
 */

#ifndef __PAR_PARSE_H__
#define __PAR_PARSE_H__

#include <par_config.h>
#include <nccmms_par.h>
#include <cps_common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PARSER_TAG_BEGIN                                     0x01       /* tag begin */
#define PARSER_TAG_END                                       0x02       /* tag end */
#define PARSER_TAG_EMPTY                                     0x03       /* tag empty */

#define MMS_REGION_ARRAY_LEN                                 20
#define MMS_REGION_ID_LEN                                    40

#define MMS_REGION_TAG_PERCENT                               "%"
#define MMS_REGION_TAG_PIXEL                                 "px"

#define MMS_SMIL_KEYWORD_PARA_ELEMENT                        "param"
#define MMS_SMIL_KEYWORD_PARA_NAME                           "name"
#define MMS_SMIL_KEYWORD_PARA_VALUE                          "value"
#define MMS_SMIL_KEYWORD_PARA_VALUETYPE                      "valuetype"
#define MMS_SMIL_KEYWORD_PARA_TYPE                           "type"

#define MMS_SMIL_PARA_BGCOLOR                                "background-color"
#define MMS_SMIL_PARA_FGCOLOR                                "foreground-color"
#define MMS_SMIL_PARA_TEXTATTRIBUTE                          "textattribute"
#define MMS_SMIL_PARA_TEXTSIZE                               "textsize"

#define MMS_SMIL_DEFAULT_NAME                                "#d*e#f*a#u*l#t*"

enum MMS_LAYOUT_CLASS {
    MMS_NOMAL_ROOT_LAYOUT = 0,
    MMS_ERROR_ROOT_LAYOUT
};

enum MMS_LAYOUT_MODE {
    MMS_LAYOUT_INVALID_MODE = 0,
    MMS_LAYOUT_UP_IMAGE_DOWN_TEXT,
    MMS_LAYOUT_UP_TEXT_DOWN_IMAGE,
    MMS_LAYOUT_LEFT_TEXT_RIGHT_IMAGE,
    MMS_LAYOUT_LEFT_IMG_RIGHT_TEXT
};

typedef enum _Par_Media_Type {
    SMIL_PAR_TEXT_MEDIA = 0,
    SMIL_PAR_IMAGE_MEDIA,
    SMIL_PAR_AUDIO_MEDIA,
    SMIL_PAR_VIDEO_MEDIA,
    SMIL_PAR_REF
} T_Par_Media_Type;

/* define the attribute value */
typedef struct _Parser_Attr_Value {
    int8_t *Name;               /**< the name of the attribute */
    int8_t *Value;              /**< the value of the attribute  */
    struct _Parser_Attr_Value *Next;    /**<  the next struct pointer  */
} T_Parser_Attr_Value;

/* define the tag value */
typedef struct _Parser_Tag_Value {
    int32_t Type;               /**< the type of the TAg. Begin end or empty */
    int8_t *Name;               /**< the name of the Tag   */
    T_Parser_Attr_Value *Attr;  /**< the attribute of the smil tag */
} T_Parser_Tag_Value;

typedef struct _Parser_Para_Node {
    int8_t *Name;
    int8_t *Value;
    struct _Parser_Para_Node *Next;
} T_Parser_Para_Node;

typedef struct _Parser_Para_Link {
    int32_t Total;
    struct _Parser_Para_Node *Next;
} T_Parser_Para_Link;

/* layout struct define */
typedef struct _Parser_Layout {
    int32_t Width;              /**< the width of the layout  */
    int32_t Height;             /**< the heigth of the layout  */
    int8_t BGColor[MMS_BGCOLOR_LEN];
    T_Parser_Region *Region;    /**<  the region pointer list of the layout */
} T_Parser_Layout;

typedef struct MMS_Region_record {
    int8_t *height;
    int8_t *width;
    int8_t *left;
    int8_t *top;
    T_Parser_Region *ParserRegion;
    struct MMS_Region_record *next;
} T_MMS_Region_Record;

/**********************************************************************************************/
/*    API define   */
/**********************************************************************************************/

/**
 * Check if the string is an tag
 * \param Tag   the string pointer
 * \return <ul>
 *      <li> index of the tag       if success
 *      <li> -1             if failed
 *     </ul>
 */
int16_t SmilIsTag(const int8_t * Tag);  /* check if the string is the supported tag  */

/**
 * Init the parse module
 * \param HandMMS       handle
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
int32_t SmilParserInit(T_MMS_HANDLE ** HandMMS);

/**
 * Add one par struct into the struct list
 * \param HandMMS       handle
 * \param Par           the par element struct pointer
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
int32_t SmilAddPar(T_Parser_SmilView * SmilView, T_Parser_SmilPar * Par);

/**
 * Parse the smil layout element
 * \param HandMMS		handle
 * \param Smilbuf		smil buffer
 * \param totalLen		length of smil buffer
 * \return <ul>
 *		<li> layout struct		if success
 *		<li> NULL			if failed
 *	   </ul>
 */
T_Parser_Layout *SmilParseLayout(T_MMS_HANDLE * HandMMS, int8_t ** Smilbuf,
                                 int32_t * totalLen);

/**
 * Parse the smil par element
 * \param SmilView      struct of smil
 * \param Element       smil element
 * \param Smilbuf       buffer of smil
 * \param totalLen      total len of this smil
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
int32_t SmilParsePar(T_Parser_SmilView * SmilView,
                     T_MMS_Media_Element * Element, int8_t ** Smilbuf,
                     int32_t * totalLen);
int32_t SmilParseHead(T_MMS_HANDLE * HandMMS, int8_t ** Smilbuf,
                      int32_t * totalLen);
int32_t SmilParseBody(T_MMS_HANDLE * HandMMS, T_MMS_Media_Element * Element,
                      int8_t ** Smilbuf, int32_t * totalLen);

/**
 * Free the parser's resource
 * \param HandMMS       handle
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
int32_t SmilParserClean(T_MMS_HANDLE ** HandMMS);

/**
 * Get the ref's data by the id
 * \param Element       smil element pointer
 * \param pRef          reference
 * \param Id            id of element
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
int32_t SmilGetRefDataById(T_MMS_Media_Element * Element, T_Parser_Ref * pRef,
                           int8_t * Id);
int32_t SMILCalculateRegion(T_MMS_ScreenSize * ScreenSize,
                            T_Parser_Layout * Layout,
                            struct MMS_Region_record *Region);
void SmilFreeRegionRecord(T_MMS_Region_Record * Reg);
int32_t SmilAnalyseRegionData(MMS_BasicRegion * DesPos,
                              T_Parser_SmilView * SmilView,
                              T_MMS_ScreenSize * ScreenSize,
                              enum MMS_REGION_FLAG region_flag);
void SmilGetPercentValueByRootLayout(T_Parser_Layout * Layout,
                                     struct MMS_Region_record *Region);
void SmilGetValueWithoutRootLayout(T_Parser_Region * Region,
                                   struct MMS_Region_record *RegionRec);

/**
 * Verification layout
 * \param  *PosText    the point of the text region
 * \param  *PosImage   the point of the image region
 * \param  int32_t horizontalvertical  the layout
 *
 * \return <ul>
 *             <li>when correct,return#TRUE
 *             <li>when incorrect,return#FALSE
 *             <li>when invalid,return#MMS_LAYOUT_INVALID_MODE
 *         </ul>
 */
int32_t smillayoutverification(MMS_BasicRegion * PosText,
                               MMS_BasicRegion * PosImage,
                               int32_t updown_leftright);

/**
 * Get the text's data by the id
 * \param Element       element of smil
 * \param pText         smil text
 * \param Id            id of the element
 * \return <ul>
 *      <li> TRUE           if success
 *      <li> FALSE          if failed
 *     </ul>
 */
int32_t SMILGetTextById(T_MMS_Media_Element * Element, T_Parser_Text * pText,
                        int8_t * Id);

int32_t SMILGetMediaById(T_MMS_Media_Element * Element,
                         T_MMS_Parser_BasicStructure * Basicstruct,
                         int8_t * Id);
void SMILClearBasicStruct(T_MMS_Parser_BasicStructure * BasicStruct);

#ifdef __cplusplus
}
#endif

#endif /* __PAR_PARSE_H__ */
