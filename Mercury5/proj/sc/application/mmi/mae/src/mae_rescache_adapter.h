/**
 * @file mae_rescache_adapter.h
 *
 * This header file declares the prototypes of adapted member functions for the image and bitmap
 * classes used in resource cache.
 *
 * It's hard to inherit existing image and bitmap implementation and extend them to suit the need
 * of resource cache without separate allocator and constructor functions for classes in C
 * language. To make it simple, these classes reserve a field in their structure to store the
 * identification for loaded resources regardless of whether being cached or not. Also these
 * classes are implemented a set of adapted member functions. The instances will be overridden
 * with their adapted function table for subsequent operations once they are inserted into the
 * resource cache.
 *
 * @version $Id: mae_rescache_adapter.h 291 2009-02-27 13:08:01Z kenny.wu $
 */

#ifndef __MAE_RESCACHE_ADAPTER_H__
#define __MAE_RESCACHE_ADAPTER_H__

//
// header files
//
#include "mmi_mae_common_def.h"
#include "mae_bitmap_priv.h"

//
// prototypes and structures
//
/// alias prototype for bitmap class
typedef _Bitmap_t RC_Bitmap_t;

/// adapted Rlease() member function for bitmap class
u32 _rc_BitmapRelease(IBitmapExt *pIBitmap);
/**
 * This function overrides a bitmap instance's virtual function table and stores its identification.
 *
 * Make sure the object belongs to the class you expect before wrap it and insert it into cache.
 */
void _rc_WrapBitmap(RC_Bitmap_t *pBitmap, u32 nResId, u32 nResGroup);


#endif // __MAE_RESCACHE_ADAPTER_H__
