// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_internal.h 235 2009-09-21 07:40:56Z nazy $
#ifndef __XLITE_E_INTERNAL_H__
#define __XLITE_E_INTERNAL_H__

#include "xLite_internal.h"

//////////////////////////////////////////////////////////////////////////
// Configure

#define XLITE_E_ERROR_ADDON_UNSUPPORTED						-100L


// Support addon-pcx library
#define xlite_E_addon_pcx					1
// Support addon-gif library
#define xlite_E_addon_gif					1

#define xlite_E_addon_jpg					1

// support addon-j10 library
#define xlite_E_addon_sprite_j10			1
// support addon-j10 library
#define xlite_E_addon_tilemap_j11			1
// has own font
#define xlite_E_use_font_c					1

// types
#include "xLite_E_type.h"
// Utilite
#include "xLite_E_util.h"
// image
#include "xLite_E_image.h"
// Image GIF
#include "xLite_E_image_GIF.h"

#include "xLite_E_image_JPG.h"

// Image storage
#include "xLite_E_image_storage.h"
// rectangle
#include "xLite_E_rect.h"
// raster
#include "xLite_E_raster.h"
// graphics
#include "xLite_E_graphics.h"
// list
#include "xLite_E_list.h"

#if 0
// Resource
#include "xLite_E_resource.h"
// vfs system
#include "xLite_E_vfs.h"
#endif

// storage
#include "xlite_E_storage.h"
// log system
//#include "xLite_E_log.h"
// http util
#include "xLite_E_http.h"
// text render
#include "xLite_E_text_render.h"
// sprite
#include "xLite_E_sprite.h"
// sprite render
#include "xLite_E_sprite_render.h"
// tilemap 
#include "xLite_E_tilemap.h"
// Tilemap Render
#include "xLite_E_tilemap_render.h"

#endif
