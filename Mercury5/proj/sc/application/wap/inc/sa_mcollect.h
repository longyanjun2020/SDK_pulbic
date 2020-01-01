
/**
 * @file
 * Collect unused memory unit.
 */

#ifndef _ALYS_MCOLLECT_
#define _ALYS_MCOLLECT_

#include <wap_service.h>

#define MEM_COLLECT_BLOCK 100

/** struct of memory collection info*/
typedef struct _memcollect
{
    int16_t top;
    int16_t bottom;
    int16_t *array;
    int16_t arrayLen;
    int16_t unUsed;
} memcollect;

#ifdef __cplusplus
extern  "C" {
#endif

#ifdef DB_USING_MCOLLECT

/**Get a collected node.
*   \return  unused unit index of base node
*/
int32_t fnDBA_GetNodeCollect(void);

/**Get a collected A node.
*   \return  unused unit index of A node
*/
int32_t fnDBA_GetACollect(void);

/**Get a collected Text node.
*   \return  unused unit index of Text node
*/
int32_t fnDBA_GetTextCollect(void);

/**Add the collected node to the collection array.
*   \param index    index of the collected node
*/
void fnDBA_PushNodeCollect(int16_t index);

/**Add the collected A node to the collection array.
*   \param index    index of the collected A node
*/
void fnDBA_PushACollect(int16_t index);

/**Add the collected TEXT node to the collection array
*   \param index    index of the collected text node
*/
void fnDBA_PushTextCollect(int16_t index);

/**Init collect
*   \return
*/
int32_t fnDBA_InitCollect(void);

/**Free collect data
*   \param collect handle
*   \return
*/
void fnDBA_UnCollect(void * ctxt0);

#ifdef __cplusplus
}
#endif

#endif /* DB_USING_MCOLLECT */
#endif /* _ALYS_MCOLLECT_ */

