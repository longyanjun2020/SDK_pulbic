
#ifndef  __IFLAYER_H__
#define __IFLAYER_H__

#include <ncc_types.h>
#include <wap_struct.h>
#include <wap_service.h>

/**< Definition of a anchor chain*/
struct _ifALink {
    T_DB_ANodeIdx iA;
    int16_t unUsed;
    T_DB_AAttrPtr paa;
    struct _ifALink *next;
};
typedef struct _ifALink T_DB_ifALink;
typedef T_DB_ifALink    *T_DB_ifALinkPtr;

/**< Status of struct of table*/
struct _ifTableSuite {
    T_DB_ContentLinkPtr pNode ;
    T_DB_TableNodePtr pTable ;
    T_DB_TrNodePtr pTr ;
    T_DB_TdNodePtr pTd ;
};
typedef struct _ifTableSuite    T_DB_ifTableSuite;
typedef T_DB_ifTableSuite       *T_DB_ifTableSuitePtr;

/**
 * Get chain of anchor.
 * \return Chain of anchor.
 */
void *fnDBContext_GetALink(void);

/**
 * Get pointer of refresh url of browser context.
 */
int8_t * fnDBA_GetRefreshUrlPtr(void);

#endif

