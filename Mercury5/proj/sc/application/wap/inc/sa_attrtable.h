
/**
 * @file
 * Manage attribute table
 */

#ifndef _ATTRTABLE_H_
#define _ATTRTABLE_H_

#include <wap_struct.h>

#ifdef __cplusplus
extern "C" {
#endif

/** the struct of attribute table */
struct attrTable{
    T_DB_ComnAttrPtr   table;
    int16_t            len;
    int16_t            pointer;
};

typedef struct attrTable       T_DBA_AttrTable;
typedef T_DBA_AttrTable       *T_DBA_AttrTablePtr;

/**Add a attribute cell 'attr' to the attribute table
*  if the cell 'attr' is exist in the attribute table, don't add.
*
*   \param attr  the attribute we wanted to add
*   \return  the attribute table pointer
*/
int32_t fnDBA_AttrTableAdd(T_DB_ComnAttr attr   );

/**Get the current attribute table
*   \return
*/
void* fnDBA_AttrTableReserve(void);

/**Setting the current attribute table is atb
*   \param atb   the attribute table
*/
void fnDBA_AttrTableSet(void *atb);

/**Clear every attribute of the table, and clear the table
*   \param atb   the attribute table
*/
void fnDBA_AttributeClear(void *atb);

/**Initiate the attribute table and it's elements.
*   \param atb   the attribute table
*/
int32_t fnDBA_AttrTableInit(void);

/**Initiate the attribute table and it's elements.
*   \param atb   the attribute table
*/
void fnDBA_AttrTabelSet(T_DBA_AttrTablePtr atb);

/**
 * The structure of Box Attrbutes table(a pool management mechanism)
 */
//typedef CommonArray BoxAttributeTable;

/* the invalid index of box attribute */
#define BOX_ATTRIBUTE_INVALID_INDEX (-1)
#define BOX_ATTRIBUTE_DEFAULT_INDEX (0)

/**
 * create a box attribute table
 *
 * \param void
 *
 * \return the pointer to the newly created BoxAttributeTable
 */
BoxAttributeTable *BoxAttributeTable_create(void);

/**
 * destory a box attribute table
 *
 * \param the pointer to the newly created BoxAttributeTable
 *
 * \return void
 */
void BoxAttributeTable_destroy(BoxAttributeTable ** table);

/**
 * add a box attribute into the table, and return the index of the added attribute
 *
 * \param table the ref of AttributeTable
 * \param boxAttr the box attribute to be added
 *
 * \return the index of the added box attribute
 */
int32_t BoxAttributeTable_addAttribute(BoxAttributeTable *table, BoxAttribute boxAttr);

#ifdef __cplusplus
}
#endif

#endif /*_ATTRTABLE_H_*/
