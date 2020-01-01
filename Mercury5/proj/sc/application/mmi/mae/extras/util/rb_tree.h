/**
 * @file rb_tree.h
 *
 * This header file defines the structures and interfaces for using the red-black tree.
 *
 * This is an implementation of a self-balancing red-black tree to organize a large amount of
 * comparable data which offers worst-case guarantees for tree operations. It uses a default 32-bit
 * variable for key comparison. But the users can have the flexisbility defining their own element
 * structure for storing and retrieving keys and data in the red-black tree, and specify a custom
 * comparison function. Also the implementation doesn't touch the allocation and deletion of the
 * elements in tree. The users shall provide their de/allocator routines.
 *
 * The value of key shall be unique and will be used to order the data automatically. If the
 * comparison function is not specified, the default key variable is used in integer comparison.
 * But the keys can also be treated as pointers for complicated key comparison by using custom
 * comparison function.
 *
 * @version $Id: rb_tree.h 609 2009-04-10 15:49:02Z zinc.chen $
 */

#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include "mmi_mae_common_def.h"

/**
 * The node structure of red-black tree.
 *
 * This is the default element structure to utilize the red-black tree.
 *
 * This structure constructs the red-black tree, and specifys a default key variable for comparison,
 * a default data variable for storing information. It also can be used as the first element of
 * a custom tree node structure for complicated key comparison or data storage.
 */
typedef struct rbt_node_t_
{
	struct rbt_node_t_ *left, *right, *parent; ///< pointers to left/right child and parent nodes
	u16 color; ///< color attribute of red-black tree node (use narrow type for target's 16-bit memory bus)

	u32 key;
	u32 data;
} rbt_node_t;

/**
 * Prototype of tree node's allocator.
 *
 * The allocator is responsible for allocating and initializing the node structure. The parent and
 * children pointers and color field shall be set to zero, and the key field shall be prepared.
 */
typedef rbt_node_t* (*PfnRbtAllocator)(u32 key, u32 data);

/**
 * Prototype of tree node's deallocator.
 *
 * The deallocator is responsible for releasing the node after it is removed from the tree.
 */
typedef void (*PfnRbtDeallocator)(rbt_node_t* p_node);

/**
 * Prototype of tree node's comparison function.
 *
 * The first key is always the value passed to find/insert/remove functions. And the second is
 * retrieved from the key field of node structure while traversing the tree. An evil way to use
 * the red-black tree is to store a pointer in key field which points to the node's custom data
 * structure for comparison.
 */
typedef int (*PfnRbtKeyCompare)(u32 key_desired, u32 key_stored);

/**
 * The main structure of the red-black tree.
 */
typedef struct
{
	rbt_node_t *root; ///< pointer to the root of tree
	u32 count; ///< number of elements in tree

	PfnRbtAllocator fn_allocator; ///< the allocator of tree nodes
	PfnRbtDeallocator fn_deallocator; ///< the deallocator of tree nodes
	PfnRbtKeyCompare fn_compare; ///< function for key comparison
} rbt_tree_t;

/**
 * The structure for a general purpose return value of red-black tree operations.
 */
typedef struct
{
	rbt_node_t *node;
	s16 status, param;
} rbt_info_t;

enum
{
	RBT_COLOR_RED = 0,
	RBT_COLOR_BLACK
};

/**
 * It initializes the red-black tree structure, specifies the allocator/deallocator of tree nodes,
 * and the key comparison function.
 */
void rbt_init(rbt_tree_t *tree, PfnRbtAllocator fn_alloc, PfnRbtDeallocator fn_dealloc, PfnRbtKeyCompare fn_comp);

/**
 * This function inserts an element with the key and data into the tree. The returned status is
 * true if an insertion was made, and false if the tree already contained an element whose key was
 * equivalent to the specified key value. The returned address is where the element was inserted,
 * or where the existing element was located.
 */
rbt_info_t rbt_insert(rbt_tree_t *tree, u32 key, u32 data);

/**
 * This is the hint version of red-black tree insertion function. The hint parameter points to the
 * element which will be the parent of the inserted node. To speed up the operation, it doesn't
 * verify whether the key shall be inserted here or not. Use it carefully or it may cause undetermined
 * result when the hint parameter points to an incorrect position.
 */
rbt_node_t *rbt_insert_at(rbt_tree_t *tree, u32 key, u32 data, rbt_node_t *hint);

/**
 * This function removes an element which matches the specified key from the tree.
 */
void rbt_remove(rbt_tree_t *tree, u32 key);

/**
 * This is the hint version of red-black tree remove function. The node parameter points to the
 * element to be deleted. To speed up the operation, it doesn't verify the position of node. It
 * causes undetermined result if the parameter doesn't point to a valid node of the tree.
 */
void rbt_remove_at(rbt_tree_t *tree, rbt_node_t *node);

/**
 * This function returns the location of an element that has a key equivalent to the specified key,
 * or returns a hint location where the new key would be inserted if no match is found. The returned
 * status is true if an element with the specified key is found, or false if the element points to
 * a hint position.
 */
rbt_info_t rbt_find(rbt_tree_t *tree, u32 key);

/**
 * This function returns the location with a key value that is equal to or greater than that of the
 * specified key. If no lower bound is found, it returns null.
 */
rbt_node_t *rbt_lower_bound(rbt_tree_t *tree, u32 key);

/**
 * It removes all the elements in tree.
 */
void rbt_clear(rbt_tree_t *tree);

#endif // __RB_TREE_H__
