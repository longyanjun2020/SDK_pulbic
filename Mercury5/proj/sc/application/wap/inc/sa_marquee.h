
/**
 * @file
 * Deal <marquee> Tag
 */

#ifndef __ALYS_MARQUEE_H
#define __ALYS_MARQUEE_H

#ifdef __cplusplus
extern "C" {
#endif

/**Destroy marquee list
*   \param  ctxt          the context of a page
*/
void fnDBA_DropMarquee(T_DB_ParseCtxtPtr  ctxt);

/**Reset the content of a marquee item
*   \param  item        pointer to a marquee item
*   \param  content        pointer to the content
*/
void fnDBA_MarqueeSetContent(void * item,int8_t * content);

/**add a marquee item to the marquee list
*   \param  content     pointer to the marquee content
*   \param  direction       direction
*   \param  height          height
*   \param  width           width
*   \param  loop            loop times
*   \param  scrollamout     pixels to scroll each time
*   \param  scrolldelay     delay time of scroll each time(milliseconds)
*   \param  index           the index of the marquee item in the marquee list
*   \return     the index of the marquee item in the marquee list
*/
void * fnDBA_AddMarqueeToList(
    int8_t * content,
    int8_t * direction,
    int8_t * height,
    int8_t * width,
    int8_t * loop,
    int8_t * scrollamout,
    int8_t * scrolldelay,
    int16_t * index
);

#ifdef __cplusplus
}
#endif

#endif
