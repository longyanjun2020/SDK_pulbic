
/**
 * @file
 * implementation of public structure of layout module.
 */

#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include <wap_service.h>
#include <common_stack.h>

#ifdef __cplusplus
extern "C" {
#endif

/** record the status info while processing */
struct _LayoutState
{
    int16_t x;                              /**< x position */
    int32_t y;                              /**< y position */
    int16_t align;                          /**< the line align */

    /** the type of flag, including IMG, BR and P.
     * if the type is IMG, the higher 8 bits
     * stands for the img align.
     * if the type is other two, the higher 8 bits
     * means nothing.
     */
    int16_t flag;

    T_DB_ContentLinkPtr pLineLeader;        /**< the pointer to the first node of a logical line */
    T_DB_ContentLinkPtr pLastPNode;         /**< the pointer to the last node of a logical line */
    T_DB_ContentLinkPtr pFieldset;         /**< for block Element, such as fieldset. etc */

    T_DB_ContentLinkIdx indexCurrentProcessingNode;  /**< the index of node current processing */
    int32_t layCurrentProcessingHeight;     /**< the  current height of logical */
    T_DB_Pos lastbr;                        /**< the last br node processed last time */

    int16_t gsolidwidth;                    /**< the width of a solid node, ex: img */
    int16_t startypos;                      /**< the y position when start each time, it can be assistant to layout */
    int16_t layInTable;                     /**< a flag whether current node is a inner node of a table. 1:yes 0:no */

    int16_t blockLRmHight;                  /**< when deal with block.we will still layout other element around it. such as <img align='left'>*/

    int16_t contentLeftEdge;                /**< record the left edge position of content, every line's layout begin at this position */
    int16_t contentRightEdge;               /**< record the right edge position of content, every line's layout end at this postion */
    int16_t leftBlockWidth;                 /**< record the width of left block */
    int16_t rightBlockWidth;                /**< record the width of right block */

    int16_t blockRRmHight;                  /**< when deal with block.we will still layout other element around it. such as <img align='left'>*/
    int16_t screenWidth;                    /**< screen with.*/
    int16_t blockLayInTableEndY;            /**< the y point of the block, it is used to calculate td height.*/
    
    int16_t virScreenWidth;   /**< for nowrap mode*/
    int16_t preScreenWidth;   /**< for nowrap mode*/
    int16_t nouse;
    /*
     * The reference of box attribute table.
     * the table is used for lookup box attribute for every node.
     */
    const BoxAttributeTable             *boxAttrTableRef;
    T_DB_ContentLinkPtr     lastNode;      /**< the last node that is processed */
};
//typedef struct _LayoutState T_DB_LayoutState;

#define VIRTUAL_SCR_MAX_WIDTH 0x7000

#define LAYOUT_SCREEN_WIDTH     300
#define LAYOUT_SCREEN_HEIGHT    250
#define FLAG_ALIGN_IMG          0x01    /**< define flags*/
#define FLAG_LAST_IS_BR         0x02
#define FLAG_LAST_IS_P          0x04
#define FLAG_LAST_IS_P_BEGIN    0x08
#define FLAG_LAST_IS_P_END      0x10

#define USE_SCREENWIDTH_AS_TABLEWIDTH 0
#define COLLAPSE_TABLE_IF_OVER_WIDTH 1
#define COLLAPSE_TABLE_IF_EXCEED_COL_COUNT 1

#ifdef DB_USING_XHTML_LIMIT
#define LAYOUT_SKIP_BR  0               /**< 1:skip 0:don't skip */
#else
#define LAYOUT_SKIP_BR  1               /**< 1:skip 0:don't skip */
#endif

#define MAX_SCROLL_HEIGHT 0x50000
#define DEFAULT_NULLHEIGHTROW 14        /**< the new line height when the line height is 0 */

#define FONT_WIDTH_STYLE_EQUAL              1
#define FONT_WIDTH_STYLE_NOTEQUAL_DGUI      2
#define FONT_WIDTH_STYLE_NOTEQUAL_UNDEFINE  3
#define FONT_WIDTH_STYLE  FONT_WIDTH_STYLE_NOTEQUAL_DGUI

#define DEFAULTATTR 0                   /**< the default index of a font attribute (used for dealing with the new blank line) */
#define DEFAULTLINEAUTOBREAK 3          /**< the number of auto break line permitted */

/* Image dimensions */
#define DEFAULT_IMAGEWIDTH      20      /**< the default width of IMG element */
#define DEFAULT_IMG_FAIL_WIDTH  20      /**< the default width of IMG element when download is not completed */
#define DEFAULT_IMG_FAIL_HEIGHT 20      /**< the default height of IMG element when download is not complete */

/* Table dimensions */
#define DEFAULT_TABLE_CELL_WIDTH    30  /**< the default cell width of table element */

/* Line dimensions */
#define DEFAULT_LINEHEIGHT          NCCPort_brwagent_getFontHeight(0)    /**< the default height of line element */
#define DEFAULT_LINEWIDTH           50  /**< the default width of line element 50 */
#define DEFAULT_LINEMARGIN          4   /**< the default margin of line element */
#define DEFAULT_ELEMENT_SPACE       4   /**< the default space between elements */
#define DEFAULT_TEXT_NODEMARGIN     0   /**< the default margin of text node */
#define DEFAULT_FIELD_ROW_LINES     4

#define DEFAULT_FIELDSET_INNERPADDING 2 /**< the default padding of inner fieldset. */

/* Field dimensions */
#define DEFAULT_FIELDSTRLEN         6   /**< the default length of string in field element */
#define DEFAULT_FIELDFONTWIDTH      8 /**< the default font width in field element */
//#define DEFAULT_FIELDFONTHEIGHT     20    /**< the default font height in field element */
#define DEFAULT_FIELDFONTHEIGHT     NCCPort_brwagent_getFontHeight(0) + 6   /**< the default font height in field element */

#define DEFAULT_FIELDFONTPADDING    1   /**< the default font padding in field element */
#define DEFAULT_FIELDMARGIN         2   /**< the default margin in field element */

/* Text Field dimensions */
#define DEFAULT_TEXTFIELDSIZE       10  /**< the default text size in textfield */

#ifdef DB_USING_XHTML_LIMIT
#define DEFAULT_TEXTFIELDROWS       1   /**< the default size of rows in textfield */
#else
#define DEFAULT_TEXTFIELDROWS       4   /**< the default size of rows in textfield */
#endif

#define DEFAULT_BUTTONEXTRAWIDTH    5   /**< the default extra width of button element */
#define DEFAULT_BUTTONEXTRAHEIGHT   2   /**< the default extra height of button element */
#define DEFAULT_AREAEXTRAWIDTH      8   /**< the default extra width of text area */
#define IMAGESUBMITTEMPSIZE         6   /**< the default size of imageSubmit element */

#ifndef MAX
#define MAX(x, y) ((x)>(y) ? (x) : (y) )
#endif

#ifndef MIN
#define MIN(x, y) ((x)<(y) ? (x) : (y) )
#endif

/**
 * Do layout.This function is the main function layout.In this function,
 * it calls different kinds of function to handle different types of node of chained list.
 * \param iRoot the index of start node
 * \param *pState the status info of layout
 * \param pSrnInfo the info of screen
 * \param whether to ignore the table node
 * \return the last node of layout
 */
T_DB_ContentLinkIdx fnDB_doLayout(T_DB_ContentLinkIdx iRoot,
                                  T_DB_LayoutState *pState,
                                  T_DB_PosPtr pSrnInfo);

/**
 * This function does the follows:
 * 1. find out the highest node in current line;
 * 2. do align among the nodes in current line;
 * 3. set layState x = 0, y += maxheight;
 * \param pCurrent the pointer of current node, used to control the loop
 * \param *pState the current status info of layout
 * \param screenWidth the width of the screen
 * \return void
 */
void doCR(T_DB_ContentLinkPtr pCurrent,
          T_DB_LayoutState *pState,
          int16_t screenWidth);

/**
 * Do the layout of solid block
 * \param pCurrent the pointer of current node
 * \param *pState the status info of layout
 * \param screenWidth the width of screen
 * \return void
 */
void doBlock(T_DB_ContentLinkPtr pCurrent,
             T_DB_LayoutState *pState,
             int16_t screenWidth);

/**
 * Get the height of current line
 * \param pCurrent the pointer of current node
 * \param *pState the status info of layout
 * \return the bottom position of current line
 */
int32_t getRowHeight(T_DB_ContentLinkPtr pCurrent, T_DB_LayoutState *pState);

/**
 * Word wrapping for UTF-8 encoded text
 *
 * @param text      UTF-8 encoded string
 * @param textLen   Length of the string
 * @param fontsize  Font size
 * @param fontStyles Specfies font styles:
 *       <li>bit 0(0x01): bold</li>
 *       <li>bit 1(0x02): italicized</li>
 *       <li>bit 2(0x04): underline</li>
 *       <li>bit 3(0x08): strikethrough</li>
 *       <li>bit 4(0x10): subscript</li>
 *       <li>bit 5(0x20): superscript</li>
 * @param maxWidth  Max width available
 * @param width     [output] The actual width of the displable part of the string
 *
 * @return Max number of characters can be displayed within maxWidth
 */
int32_t getWordWrapOffset(const uint8_t *text,
                          int32_t textLen,
                          int32_t fontSize,
                          int32_t fontStyles,
                          int32_t maxWidth,
                          int32_t *width);

/**
 * get width of the specified text.
 *
 * @param str   UTF-8 encoded string
 * @param len   number of the bytes
 * @param fontsize  Font size
 * @param fontStyles Specfies font styles:
 *       <li>bit 0(0x01): bold</li>
 *       <li>bit 1(0x02): italicized</li>
 *       <li>bit 2(0x04): underline</li>
 *       <li>bit 3(0x08): strikethrough</li>
 *       <li>bit 4(0x10): subscript</li>
 *       <li>bit 5(0x20): superscript</li>
 *
 * @return width of the text
 */
int32_t getTextWidth(const uint8_t *str,
        int32_t len,
        int32_t fontSize,
        int32_t fontStyles);

/**
 * get width of the text displayed using system default font.
 *
 * @param str   UTF-8 encoded string
 * @param len   number of the bytes
 *
 * @return width of the text
 */
int32_t getSysTextWidth(const uint8_t * str, int32_t len);

/**
 * Find the word that has largest display width (but not essentially longest
 * itself) in the specified string and return the width.
 *
 * @param str   UTF-8 encoded string
 * @param len   number of the bytes
 * @param fontsize  Font size
 * @param fontStyles Specfies font styles:
 *       <li>bit 0(0x01): bold</li>
 *       <li>bit 1(0x02): italicized</li>
 *       <li>bit 2(0x04): underline</li>
 *       <li>bit 3(0x08): strikethrough</li>
 *       <li>bit 4(0x10): subscript</li>
 *       <li>bit 5(0x20): superscript</li>
 *
 * @return width of the word
 */
int32_t getLongestWordWidth(const uint8_t *str,
                            int32_t len,
                            int32_t fontSize,
                            int32_t fontStyles);
/**
 * Deal with the layout of field.
 * \param pCurrent the current pointer of node
 * \param screenWidth the width of the screen
 * \param *pWidth the pointer of the field width
 * \param *pHeight the pointer of the field height
 * \return void
 */
void fnDB_calculateFieldSize(T_DB_ContentLinkPtr pCurrent,
                             int16_t screenWidth,
                             int16_t *pWidth,
                             int16_t *pHeight);

/**
 * Do layout of a text node.
 *
 * @param pCurrent the pointer of current node
 * @param pState the pointer of the layout status
 * @param screenWidth the width of the screen
 */
void processTextNode(T_DB_ContentLinkPtr pCurrent,
                     T_DB_LayoutState * pState,
                     int16_t screenWidth);

/**
 * Do ayout of a hyperlink (A) node.
 *
 * @param pCurrent the pointer of current node
 * @param pState the pointer of layout status
 * @param screenWidth the width of the screen
 */
void processANode(T_DB_ContentLinkPtr pCurrent,
                  T_DB_LayoutState *pState,
                  int16_t screenWidth);

/**
 * Deal with the table Node.
 * \param pCurrent the current pointer of the node
 * \param *pState the pointer of the layout state
 * \param screenWidth the width of the screen
 * \return void
 */
void fnDB_processTableNodeEx2(T_DB_ContentLinkPtr pCurrent,
                              T_DB_LayoutState *pState,
                              int16_t screenWidth);

/**
 * Move table according to the offset.
 * \param pCurrent the current pointer of the node
 * \param offsetX the x offset
 * \param offsetY the y offset
 * \return void
 */
void fnDB_moveTable(T_DB_ContentLinkPtr pCurrent,
                    int16_t offsetX,
                    int16_t offsetY);

/**
 * Download the image data which is recognized and then modify the node attribute accordingly
 * \param pCurrent the pointer of current node
 * \return void
 */
void fnDB_processAInImgNodeChange(T_DB_ContentLinkPtr pCurrent);

/**
 * Deal with layout of the IMG node, if the img hasn't been downloaded yet.
 * display the alt text
 * \param pCurrent the pointer of current node
 * \param pState the pointer of layout status
 * \param screenWidth the width of the screen
 * \return void
 */
void fnDB_processAInImgNode(T_DB_ContentLinkPtr pCurrent,
                            T_DB_LayoutState *pState,
                            int16_t screenWidth);

#ifdef TRACE_ON
/**
 * Convert node type to printable string
 *
 * \param node type: the type of the layout result tree
 * \return char* : the printable string
 */
const int8_t * getNodeType(int32_t nodetype);
#endif /* TRACE_ON */

#ifdef __cplusplus
}
#endif

#endif /* __LAYOUT_H__ */
