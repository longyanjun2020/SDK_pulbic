
#ifndef __WMLCONV_VAR_H__
#define __WMLCONV_VAR_H__

#define VAR_NAME_LEN        31
//#define VAR_VALUE_LEN       255
#define VAR_VALUE_LEN       1024

/* var struct definition of wmlTrans */
typedef struct _Variable_Item
{
    uint8_t VName[VAR_NAME_LEN+1];      /* the name of var */
    uint8_t VValue[VAR_VALUE_LEN+1];    /* the value of var */
} T_Variable_Item;

#define VAR_LEN         64

#define STRING_DEFAULT_LEN      64

#define VAR_NOESC               1
#define VAR_ESCAPE              2
#define VAR_UNESC               3

/**
 * realloc and modify the limtLen
 * \curLen current suffix
 * \limtLen the length we have malloc
 * \increaseLen when realloc, the length we should increase
 */
void fnDBT_StrRealloc(int32_t curLen, int32_t *limtLen, int32_t increaseLen, uint8_t ** srcStr);

/*substituted the var in the value of attrs'.*/
void fnDBT_VarInAttrsSubstituted(uint8_t **attrs);

/**
 * substituted the var with the value of it.
 * \src the source of the string
 * \reuturn the string we have substituted, no var in src now, if the src is invalid, return null.
 */
uint8_t * fnDBT_VarSubstituted(uint8_t *src);

/* the follow functions are belong to wmltranswml.c before */
void insertContent(uint8_t * begin1,uint8_t * end1,uint8_t * begin2,uint8_t * end2);
uint8_t * getAttrValue(uint8_t * begin,uint8_t * end,uint8_t * attrStr);

#endif /* __WMLCONV_VAR_H__ */
