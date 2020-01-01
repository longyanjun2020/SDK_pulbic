
/**
 * @file
 * Browser Layout Service Layer
 *
 * Service API exposed by the Browser Layout.
 *
 * <!-- #interface list begin -->
 * \section ncclayout Interface
 * -    NCCBrw_layout_getLayoutWidth()
 * -    NCCBrw_layout_doLayout()
 * -    NCCBrw_layout_getCurrentProcessingHeight()
 * -    NCCBrw_layout_getCurrentProcessingNodeIndex()
 * -    NCCBrw_layout_reset()
 * -    NCCBrw_layout_setCurrentProcessingHeight()
 * -    NCCBrw_layout_setCurrentProcessingNodeIndex()
 * -    NCCBrw_layout_needRedisplay()
 * -    NCCBrw_layout_resetDisplayFlag()
 * -    NCCBrw_layout_create()
 * -    NCCBrw_layout_destroy()
 * <!-- #interface list end -->
 */

#ifndef __NCC_LAYOUT_H__
#define __NCC_LAYOUT_H__

#include "wap_config.h"
#include "wap_struct.h"

#ifdef NCC_BROWSER_DUMP_LAYOUT
#include <ncclayout_dump.h>
#endif /* NCC_BROWSER_DUMP_LAYOUT */

#ifdef __cplusplus
extern  "C" {
#endif

struct _LayoutState;

#define DEFAULT_IMG_WIDTH 14  /**< the width of img when not downloaded */
#define DEFAULT_IMG_HEIGHT 16 /**< the height of img when not downloaded */
#define DEFAULT_SELECT_SYMBOL_WIDTH 24  /**< default width of select symbol width */
#define TABLE_MAX_COL 10                /**< the max number of column(when the real number of column is over the limit, the table element is to be collapsed down) */
#define MAX_TD_LINE     5               /**< the max number of lines in TD */

/**
 * For inspecting internal state of the layout module for testing purpose.
 * Will be removed when refactoring done.
 *
 * \return the global state structure of layout
 */
const struct _LayoutState * NCCBrw_layout_getContext(void);

/**
 * Reset the handle of layout.
 * \return
 */
void NCCBrw_layout_reset(void);

/**
 * Call this function to do layout. This function is the entrance of layout module.
 * Every time we call this function, we may have handled many nodes  of the chained list,
 * then we return the last node we've just handled.
 *
 * \param iRoot the start node's index of layout
 * \return the index of the last node
 */
T_DB_ContentLinkPtr NCCBrw_layout_doLayout(T_DB_ContentLinkIdx iRoot);

/**
 * Get the index of the last node of current parsing process
 * \return Return the index of the last node.
 */
T_DB_ContentLinkIdx NCCBrw_layout_getCurrentProcessingNodeIndex(void);

/**
 * Get the index of the last node of current process
 * \param index  the index of the last node.
 * \return
 */
void NCCBrw_layout_setCurrentProcessingNodeIndex(T_DB_ContentLinkIdx index);

/**
 * Get the height of the current process, it is included in the handle of layout
 * \return the height
 */
int32_t NCCBrw_layout_getCurrentProcessingHeight(void);

/**
 * Set the height of the current process, it is included in the handle of layout
 * \param  height the specific height
 * \return
 */
void NCCBrw_layout_setCurrentProcessingHeight(int32_t height);

/**
 * Determine whether re-display is needed based on startypos.
 * the redisplay isn't needed if the startypos is between
 * the logical position of the top screen and the bottom screen.
 * \param beginy the upper logical position of the screen
 * \param endy the lower logical position of the screen
 * \return Return TRUE if needed;otherwise retrun FALSE.
 */
int32_t NCCBrw_layout_needRedisplay(int16_t beginy, int16_t endy);

/**
 * Reset the display of layout.
 * \return
 */
void NCCBrw_layout_resetDisplayFlag(void);

/**
 * Get the width of  display area.
 * \return the width of the display area.
 */
int32_t NCCBrw_layout_getLayoutWidth(void);

/* forward delaration */
typedef struct _LayoutState T_DB_LayoutState;
/**
 * create a layout handler
 * \param void
 * \return
 *      pointer to created handler if success
 *      NULL if fail
 */
T_DB_LayoutState *NCCBrw_layout_create(void);

/**
 * Destroy layout handler
 * \param layout pointer to layout state to be destroyed
 * \return void
 */
void NCCBrw_layout_destroy(T_DB_LayoutState **layout);

#ifdef __cplusplus
}
#endif

#endif /* __NCC_LAYOUT_H__ */

