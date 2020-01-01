/**
 * @file mae_rescache_priv.h
 *
 * This header file defines resource cache's internal data structures, parameters, and the
 * interface for other modules for utilizing the cache. All the prototypes and enum values are
 * declared as private and for inter-module use in MAE kernel only. It doesn't provide a global
 * cache for other applets' and services' access.
 *
 * @version $Id: mae_rescache_priv.h 609 2009-04-10 15:49:02Z zinc.chen $
 */

#ifndef __MAE_RESCACHE_PRIV_H__
#define __MAE_RESCACHE_PRIV_H__

//
// header files
//
#include "mmi_mae_common_def.h"

//
// definitions and macros
//
/// pattern "rEScAChE" to recognize the cacheable objects
/// note that the bit of RC_FCACHED in the lower 16-bit of pattern 1 shall be zero so that
/// initialize an instance with the pattern also implies it has not been cached
#define RC_PATTERN_0 (0x63534572)
#define RC_PATTERN_1 (0x45684341)

/// handles for default resource groups
#define RC_HRES_DEFAULT		0
#define RC_HRES_THEME		1
#define RC_HRES_BASE		2

/// macro to make a resource group id for an instance
#define RC_GROUP(_handle_, _type_) ((u16)(_handle_) << 16 | (u16)(_type_))

//
// prototypes and structures
//
/**
 * The enums for the types of resource instances. It also reserves a bit to distinguish whether the
 * instance is cached or not.
 */
enum
{
    RC_EBITMAP,
	    /// enum for instance types shall not exceed the following value(s)
    RC_FTYPEMASK	= 0x0FFF,
    RC_FCACHED		= 0x8000
};

/**
 * The structure for storing search results.
 */
typedef struct RC_Node_t_ RC_Node_t;
typedef struct RC_Info_t_
{
	RC_Node_t *pNode; ///< it can be the node which contains the specified key, or the node to insert the key
	s16 nStatus; ///< it indicates the specified key is found or not
	s16 nParam; ///< it can be the position of the found key, or where the specified key shall be inserted
} RC_Info_t;

/**
 * The prototype of handles of resource groups.
 */
typedef u16 RC_HRES_t;

//
// private functions
//
/**
 * The initial function of the resource cache module.
 */
MAERet_t MAE_RC_Init(void);

/**
 * This function finds the resource instance with the given id-group identification in cache.
 *
 * It returns the node and position of the instance when the specified id is found, or the node and
 * position where the instance shall be inserted if the id is not found.
 *
 * @param nResId		The id of resource.
 * @param nResGroup	The compound identification of resource handle and type.
 *
 * @return node		The t-tree node where the instance resides, or where it shall be inserted.
 * @return status	It indicates the instance is found or not.
 * @return param	The index of the requested instance in node, or where it shall be inserted.
 */
RC_Info_t MAE_RC_Find(u32 nResId, u32 nResGroup);

/**
 * This function inserts a cache-compatible object into the hint position of resource cache. The
 * cache operation always starts from finding a specific resource id in cache. A new resource
 * instance is created only if the id is not found. The insertion always uses the search result as
 * a hint to avoid another search for new position. Therefore, the insertion shall be executed
 * subsequently to a find operation and before any modification to the cache can happen.
 *
 * After insertion, the t-tree may rebalance itself and shift elements in nodes to conform its
 * properties. So that the hint position may not be the final postion of inserted instance. Do not
 * use it to access elements in the resource cache.
 *
 * Beware that this is not a function to store any interface instances into cache. It deals with
 * only specific classes/types of objects. The resource cache uses specific fields in objects to
 * save their identification and other information. So be sure to insert only compatible objects
 * into the cache.
 *
 * Also note that the objects inserted into cache shall be first overridden with an adapted virtual
 * function table for cache maintenance. Always apply the adapted table to a new instance created
 * by yourself, and only insert the applied new instance into cache. Doing so guarantees that the
 * instance is well-encapsulated before others' access, and minimize the impact of overriding.
 * Since overriding an initialized instance is an evil and dangerous operation, do not apply an
 * adapted table to instances created by others, which may have been overridden with other adapted
 * function tables.
 *
 * Furthermore, inserting bitmap objects into cache is a little different. The bitmap class has
 * complicated connections with the image class. It is used as a canvas for image class to render
 * the decoded results. So the bitmap is usually created by image, and is modified or re-created at
 * some point. It is rarely created directly since in most cases users need decoding routines
 * provided by the image class rather than drawing the canvas themselves. Thus inserting a bitmap
 * is usually achieved by first create a new image instance, export the decoded bitmap and wrap it
 * with adapted function table, then release the connected image instance. This guarantees that the
 * bitmap instance is independent to any existing image, and will not be used as an image's canvas.
 *
 * @param tPos		The hint position (result of find operation) to insert the resource instance.
 * @param nResId		The id of resource.
 * @param nResGroup	The compound identification of resource handle and type.
 * @param pInst		The instance of resource.
 */
MAERet_t MAE_RC_Insert(RC_Info_t tPos, u32 nResId, u32 nResGroup, void *pInst);

/**
 * This function removes the specified resource instance from cache. Always search cache first to
 * find the position of target resource instance.
 *
 * @param tPos		The position of resource instance to be removed.
 */
MAERet_t MAE_RC_Remove(RC_Info_t tPos);

/**
 * This function returns the resource instance at the input position. Search cache first to find
 * the instance position of designate resource id.
 *
 * @param tPos		The position of resource instance.
 */
void *MAE_RC_GetResource(RC_Info_t tPos);

#endif // __MAE_RESCACHE_PRIV_H__
