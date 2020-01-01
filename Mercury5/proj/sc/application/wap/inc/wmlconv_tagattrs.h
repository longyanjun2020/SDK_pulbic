
#ifndef __WMLCONV_TAGATTRS_H__
#define __WMLCONV_TAGATTRS_H__

#include <wmlconv_tohtml.h>

/**
* WML tag to be transfered
*/
#define TAG_NONE 0x00

#define TAG_CHARACTER   0x10
#define TAG_ANCHOR      0x22
#define TAG_CARD        0x27
#define TAG_BR          0x26
#define TAG_IMG         0x2e
#define TAG_DO          0x28
#define TAG_GO          0x2B
#define TAG_INPUT       0x2F
#define TAG_NOOP        0x31
#define TAG_ONEVENT     0x33
#define TAG_OPTION      0x35
#define TAG_REFRESH     0x36
#define TAG_P           0x20
#define TAG_POSTFIELD   0x21
#define TAG_PREV        0x32
#define TAG_SELECT      0x37
#define TAG_SETVAR      0x3E
#define TAG_TEMPLATE    0x3B
#define TAG_TIMER       0x3C
#define TAG_WML         0x3F
#define TAG_TABLE       0x1F
#define TAG_TR          0x1E
#define TAG_TD          0x1D

/*map of WML tag and HTML tag*/
typedef struct _tagMap  T_DBT_WmlToHtmlTagMap;
struct _tagMap
{
    //uint8_t *    wmlTagName;        /* The name of WML tag*/
    //uint8_t *   htmlTagName;        /* The name of HTML tag */
    // change uint8_t* to char*
    char *    wmlTagName;        /* The name of WML tag*/
    char *   htmlTagName;        /* The name of HTML tag */

    int16_t    wmlTagType;          /* The type of WML tag*/
    int16_t    unUsed;
};

/*Find HTML tag and WML tag type from the map of WML tag and HTML tag*/
uint8_t *  fnDBT_FindTransTag(
                                     const uint8_t *tagName,
                                     int16_t *type
                                    );

/*Find the attribute index from the attribute array*/
int16_t fnDBT_FindAttribute(
                            const uint8_t *toFindAttr,
                            const uint8_t **attrs
                           );

#endif /* __WMLCONV_TAGATTRS_H__ */

