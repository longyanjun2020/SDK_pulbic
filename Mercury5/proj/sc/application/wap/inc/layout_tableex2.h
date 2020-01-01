
/**
 * @file
 * implementation of browser table layout.
 */

#ifndef __LAYOUT_TABLEEX2_H__
#define __LAYOUT_TABLEEX2_H__

#include <layout.h>
#include <wap_service.h>

struct _ColInfo{
    int16_t remainingRowspan;
    int16_t remainingHeight;
    T_DB_TdNodePtr pSpanningTd;

    int32_t sumWidth;
    int32_t minWidth;
    int32_t maxWidth;

    int32_t width;
    struct _ColInfo *next;
} ;
typedef struct _ColInfo ColInfo, *pColInfo;

/** ColInfo functions */
static pColInfo getColInfo( pColInfo *ppRoot, int16_t index );
static void clearColInfo( pColInfo *ppRoot );
static int16_t getColInfoCount( pColInfo pRoot );

/** AUX functions */
static void collapseTable(T_DB_ContentLinkPtr pCurrent);

static void doTdValign(T_DB_TdNodePtr pTd , int16_t cellpadding);
static void reSetInnerHeight(int16_t iInnerNode, int16_t offset);

static T_DB_ContentLinkIdx calculateTdContentWidth(
                                                   T_DB_TdNodePtr pTd,
                                                   int16_t *pMaxWidth,
                                                   int16_t *pMinWidth);

/** Process cell AUX  */
static int16_t doSpans(
                       T_DB_TdNodePtr pTd,
                       pColInfo *ppRoot,
                       int16_t colnum);

static void decreaseRowSpans( pColInfo *ppRoot );

/** Process table functions */
static void doTableLayout(
                            T_DB_ContentLinkPtr pCurrent,
                            T_DB_LayoutState *pState,
                            int16_t screenWidth,
                            pColInfo *ppColInfoRoot);

static int16_t preProcessColInfo(
                                 pColInfo *ppRoot,
                                 int16_t screenWidth,
                                 int16_t desiredTableWidth,  //
                                 int16_t cellspacingwidth);  

void fnDB_processTableNodeEx2(
                                T_DB_ContentLinkPtr pCurrent,
                                T_DB_LayoutState *pState,
                                int16_t screenWidth);

void fnDB_moveTable(
                      T_DB_ContentLinkPtr pCurrent,
                      int16_t offsetX,
                      int16_t offsetY);

#endif /* __LAYOUT_TABLEEX2_H__ */
