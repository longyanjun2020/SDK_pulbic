// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_type.h 209 2009-07-21 02:24:47Z nazy $
#ifndef __XLITE_E_TYPE_H__
#define __XLITE_E_TYPE_H__


/*!
 * @file xLite_E_type.h
 * @brief 引擎类型定义
 */


#define XLITE_E_IMAGE_NO_FLAG						0x00
#define XLITE_E_IMAGE_SHARE_BUFFER					0x01
#define XLITE_E_IMAGE_HAS_LINE_ADDRESS				0x02
#define XLITE_E_IMAGE_SHARE_PALETTE					0x04	
#define XLITE_E_IMAGE_STATIC						0x08	/*!< 静态图片,从缓冲恢复的时候使用 */

#define XLITE_E_IMAGE_ERR_NO_ERROR					0x00
#define XLITE_E_IMAGE_ERR_SOURCE_TOO_LARGE			-1L
#define XLITE_E_IMAGE_ERR_PF_NOT_MATCH				-2L


#define	XLITE_RED_MASK								(0x1F << 11)
#define	XLITE_GREEN_MASK							(0x3F << 5)
#define	XLITE_BLUE_MASK								(0x1F)


/*!
 * @brief 像素格式定义
 * @sa xLite_E_util.h
 */
typedef enum
{
	xlite_pf_unknown = 0,			/*!< 未知/不合法的像素格式 */
	xlite_pf_rgb_444,				/*!< 像素由12bits组成,占用16bits(2bytes)*/
	xlite_pf_rgb_565,				/*!< 像素由16bits组成,占用16bits(2bytes),该格式为引擎默认的屏幕缓冲格式*/
	xlite_pf_rgb_888,				/*!< 像素由24bits组成,占用24bits(3bytes)*/
	xlite_pf_index_8,				/*!< 像素为一个索引到一个256色调色板的值,占用8bits(1byte),该格式可被引擎绘制*/
	xlite_pf_index_1				/*!< 像素为单bit的值,占用1bit,该格式被某些函数支持 */
} xlite_pixel_format;

//////////////////////////////////////////////////////////////////////////
// xlite_E_image.h
//////////////////////////////////////////////////////////////////////////


/*!
 * @struct xlite_image xLite_E_type.h xLite_E_image.h
 * @brief 保存图形资源的数据
 * @sa xLite_E_image.h
 */
typedef struct  
{
	xl_uint32			flags;				/*!< 标志位 */
	xl_uint16			width;				/*!< 图形的宽度 */
	xl_uint16			height;				/*!< 图形的高度 */

	xlite_pixel_format	pf;					/*!< 图形的像素格式 */

	
	xl_uint32			buffer_length;		/*!< 图形的缓冲的长度 */
	
	xl_uint16			bytes_per_line;		/*!< 图形缓冲每行占用的字节数 */
	xl_uint16			palette_length;		/*!< 图形调色板占用的字节数 */

	xl_void*			buffer;				/*!< 图形缓冲的指针 */
	xl_void*			palette;			/*!< 图形调色板的指针 */
	xl_void**			line_address;		/*!< 图形行地址的指针 */
} xlite_image;

typedef xlite_image*	xlite_himage;




/*
 * @typedef GIF decoder handle
 */
typedef xl_void*		xlite_gif_hdecoder;



//////////////////////////////////////////////////////////////////////////
/*!
 * @struct xlite_point xLite_E_type.h
 * @brief 2D点结构
 */
typedef struct  
{
	xl_int32			x;
	xl_int32			y;
} xlite_point;

/*!
 * @brief 声明一个xlite_point并且赋值
 */
#define xlite_E_point_def(pointname,x,y)		xlite_point pointname = { (x), (y), }

//////////////////////////////////////////////////////////////////////////
// xLite_E_rect.h

/*!
 * @brief 保存矩形数据的结构
 * @sa xLite_E_rect.h
 */
typedef struct  
{
	xl_int32			left;				/*!< 矩形的左边坐标 */
	xl_int32			right;				/*!< 矩形的右边坐标 */
	xl_int32			top;				/*!< 矩形的顶部坐标 */
	xl_int32			bottom;				/*!< 矩形的底部坐标 */
} xlite_rect;

/*!
 * @brief 声明一个xlite_rect并且赋值
 */
#define xlite_E_rect_def(rectname,left,top,right,bottom)					\
	xlite_rect rectname = { (left), (right), (top), (bottom) }

//////////////////////////////////////////////////////////////////////////
// xLite_E_raster.h
//////////////////////////////////////////////////////////////////////////

/*
 * 放缩表,内部使用
 */
typedef struct  
{
	xl_uint16*	table;
	xl_uint32	length;
	xl_uint32	max_length;
} xlite_clip_stretch_table;


/*
 *  绘制图片的剪裁数据,内部使用
 */
typedef struct  
{
	// source rectangle
	xlite_rect source_rect;		
	// target rectangle
	xlite_rect target_rect;
	
	// stretch table of horizontal
	xlite_clip_stretch_table horz_tbl;
	// stretch table of vertical
	xlite_clip_stretch_table vert_tbl;
} xlite_clip_data;



/*
 * 绘制直线的剪裁数据,内部使用
 */
typedef struct  
{
//	xl_bool is_out_screen;
//	xlite_rect canvas_rect;
	xlite_point pt1;
	xlite_point pt2;
} xlite_line_clip_data;


/*! @typedef xl_uint8 xlite_flip_mode */
typedef xl_uint8			xlite_flip_mode;

/*! 无翻转模式 */
#define XLITE_FLIP_NONE		0x00
/*! 水平翻转源图 */
#define XLITE_FLIP_HORZ		0x01
/*! 垂直翻转源图 */
#define XLITE_FLIP_VERT		0x02
/*! 水平且垂直反转源图 */
#define XLITE_FLIP_HORZVERT	(XLITE_FLIP_VERT | XLITE_FLIP_HORZ)

#define XLITE_FLIP_INVALID	0xFF

/*!
 * @brief 像素混合模式
 */
typedef enum
{
	xlite_blend_copy = 0,			/*!< 复制 */
	xlite_blend_func,				/*!< 使用混合函数,速度慢 */

	xlite_blend_invalid = 0xFF
} xlite_blend_mode;

#define XLITE_HALF_ALPHA	16

/*! 空的混合函数 */
#define XLITE_BLEND_COLOR_NULL				0xFF
/*! 使用颜色叠加混合 */
#define XLITE_BLEND_COLOR_ADDITIVE			0
/*! 使用alpha混合 */
#define XLITE_BLEND_COLOR_ALPHA				1
/*! 使用1/4叠加混合 */
#define XLITE_BLEND_COLOR_QUARTER_ADDITIVE	2
/*! 使用自定义混合 */
#define XLITE_BLEND_COLOR_USER				3





typedef xl_uint8*(* xlite_E_raster_locate_buffer_func)(xlite_himage,const xlite_rect*,xl_int32*,xl_int32*);
typedef xl_void (* xlite_E_raster_bitblt_buffer_func)(xl_void*,xl_uint16*,xl_uint32,xl_uint8*,xl_uint16*,xl_int32,xl_int32,xl_int32,xl_int32);
typedef xl_void (* xlite_E_raster_stretch_buffer_func)(xl_void*,xl_uint16*,xl_uint32,xl_uint8*,xl_uint16*,xl_int32,xl_int32,xl_int32,xl_int32,xlite_clip_stretch_table*,xlite_clip_stretch_table*);
typedef xl_uint16 (* xlite_E_raster_blend_color_func)(xl_void*,xl_uint16,xl_uint16);
typedef xl_void (* xlite_E_raster_draw_hv_line_func)(xl_void*,xlite_himage,xl_int32,xl_int32,xl_uint32,xl_uint16);
typedef xl_void (* xlite_E_raster_draw_line_func)(xl_void*,xlite_himage,xl_int32,xl_int32,xl_int32,xl_int32,xl_uint16);
typedef xl_void (* xlite_E_raster_fill_rectangle_func)(xl_void*,xlite_himage,const xlite_rect*,xl_uint16);


/*!
 * @brief 保存2D绘制器数据的结构
 * @sa xLite_E_raster.h
 */
typedef struct  
{
	xl_uint8				key_color_index;						/*!< 透明色索引 */
	xl_uint8				palette_offset;							/*!< 调色板偏移 */
	xl_uint8				alpha_value;							/*!< alpha 值 */
	xlite_flip_mode			flip_mode;								/*!< 翻转模式 */

	
	xl_bool					has_user_clip_rect;						/*!< 是否有用户自定义的剪裁区 */
	xlite_rect				user_clip_rect;							/*!< 用户自定义剪裁矩形 */
	xlite_clip_data			clip_data;								/*!< 绘制剪裁数据 */
	xlite_line_clip_data	line_clip_data;							/*!< 绘制直线剪裁数据 */

	xl_bool					filte_key_color;						/*!< 是否过滤透明色 */
	xlite_blend_mode		blend_mode;								/*!< 当前像素混合模式 */
	
	// Function Pointer
	xlite_E_raster_locate_buffer_func	locate_buffer;				/*!< Function Pointer */
	xlite_E_raster_bitblt_buffer_func	bitblt_buffer;				/*!< Function Pointer */
	xlite_E_raster_stretch_buffer_func	stretch_buffer;				/*!< Function Pointer */
	xlite_E_raster_blend_color_func		blend_color;				/*!< Function Pointer */
	xlite_E_raster_draw_hv_line_func	draw_horz_line;				/*!< Function Pointer */
	xlite_E_raster_draw_hv_line_func	draw_vert_line;				/*!< Function Pointer */
	xlite_E_raster_draw_line_func		draw_line;					/*!< Function Pointer */
	xlite_E_raster_fill_rectangle_func	fill_rectangle;				/*!< Function Pointer */
} xlite_raster;



//////////////////////////////////////////////////////////////////////////
// xLite_E_graphics.h
//////////////////////////////////////////////////////////////////////////

#define XLITE_TEXT_SIZE_SMALL						0
#define XLITE_TEXT_SIZE_MEDIUM						1
#define XLITE_TEXT_SIZE_LARGE						2

typedef struct  
{
	xl_uint8		key_color_index;
	xl_uint8		palette_offset;
	xl_uint8		alpha_value;
	xlite_flip_mode	flip_mode;
	xl_uint8		is_filte_key_color;
	xl_uint8		has_user_clip;
	xlite_rect		user_clip;

} xlite_raster_state;



/*!
 * @brief Graphics数据结构
 */
typedef struct  
{
	xlite_himage	surface;		/*! Graphics 绘制目标图形 */
	xlite_raster	raster;			/*! Graphics 引用的2D绘制器指针 */

	xlite_raster_state	raster_state;	/*! 保存渲染器状态 */

	// 保存当前的文字状态,add by ken
	xl_color		text_color;
	// 当前的文字大小
	xl_int32		text_size;
	
} xlite_graphics;


//////////////////////////////////////////////////////////////////////////
// xLite_list.h
//////////////////////////////////////////////////////////////////////////

/*!
 * @brief 双向链表节点数据
 */
typedef struct  
{
	xl_void*	data;		/*!< 数据 */
	xl_void*	prev;		/*!< 指向前一个节点 */
	xl_void*	next;		/*!< 指向后一个节点 */
} xlite_list_node;

/*!
 * @brief 双向链表数据结构
 */
typedef struct  
{
	xlite_list_node* head;					/*!< 链表中第一个节点 */
	xlite_list_node* tail;					/*!< 链表中最后一个节点 */
	xl_uint32 number_nodes;					/*!< 链表中的节点数量 */
	
	xl_uint32 node_pool_size;				/*!< 链表节点池大小 */
	xl_uint32 number_node_in_pool;			/*!< 当前链表节点池中节点数量 */
	xlite_list_node* pool_nodes;			/*!< 节点池中第一个节点 */
} xlite_list;


//////////////////////////////////////////////////////////////////////////
// xlite_E_text_render.h
//////////////////////////////////////////////////////////////////////////
#define XLITE_E_TEXT_RENDER_FLAG_NONE			0x00
#define XLITE_E_TEXT_RENDER_FLAG_ALIGN_LEFT		0x01
#define XLITE_E_TEXT_RENDER_FLAG_ALIGN_CENTER	0x02
#define XLITE_E_TEXT_RENDER_FLAG_ALIGN_RIGHT	0x04
#define XLITE_E_TEXT_RENDER_FLAG_ALIGN_TOP		0x08
#define XLITE_E_TEXT_RENDER_FLAG_ALIGN_VCENTER	0x10
#define XLITE_E_TEXT_RENDER_FLAG_ALIGN_BOTTOM	0x20
#define XLITE_E_TEXT_RENDER_FLAG_MULTI_LINE		0x40
#define XLITE_E_TEXT_RENDER_FLAG_AUTO_CLIP		0x80

// 保存的一些设置
typedef struct  
{
	// 行间距
	xl_int32 line_space;
	// 字符间距
	xl_int32 char_space;
} xlite_text_render_properties;


//////////////////////////////////////////////////////////////////////////
// xlite_E_storage.h
//////////////////////////////////////////////////////////////////////////

#define XLITE_E_STORAGE_FLAG_NONE				0x00
#define XLITE_E_STORAGE_FLAG_AUTO_DELETE		0x01


typedef xl_void (* xlite_E_storage_delete_data_callback)(xl_void* data,xl_void* param);

/*
 * @brief 存储器通用节点信息
 */
typedef struct  
{
	xl_uint16 ref_num;
	xl_uint32 hash;
	xl_void* data;
} xlite_storage_node;

typedef struct  
{
	xlite_list node_list;
	xlite_E_storage_delete_data_callback delete_data_callback;
	xl_void* callback_param;
} xlite_storage;


//////////////////////////////////////////////////////////////////////////
// xLite_E_image_storage.h
//////////////////////////////////////////////////////////////////////////

/*!
 * @brief 图像存储器
 */
typedef struct
{
	xlite_storage storage_impl;
} xlite_image_storage;





//////////////////////////////////////////////////////////////////////////
// xLite_E_sprite.h
//////////////////////////////////////////////////////////////////////////

/*! 
 * @brief 精灵读取图形资源加载回调函数
 */
typedef xlite_himage (* xlite_E_sprite_on_load_image)(xl_uint32 hash);

/*!
 * @brief 精灵的碰撞绑定盒
 */
typedef struct  
{
	xl_uint8	flags;			/*!< 用户自定义标志位 */
	xl_uint16	pos_pv_index;	/*!< 碰撞盒坐标 */
	xl_uint16	size_pv_index;	/*!< 碰撞盒尺寸 */
} xlite_sprite_bbox;


/*!
 * @brief 精灵中使用的成对数值
 */
typedef struct  
{
	xl_uint16	value_1;		/*!< 数值1 */
	xl_uint16	value_2;		/*!< 数值2 */
} xlite_sprite_pair_value;

typedef xlite_sprite_pair_value*				xlite_sprite_pv_ptr;

/*!
 * @brief 精灵的帧数据层
 */
typedef struct  
{
//	xl_uint8				offset_pal;				/*!< 调色板偏移 */
	xlite_flip_mode			flip_mode;				/*!< 翻转模式 */
	xl_uint16				dest_pos_pv_index;		/*!< 目标坐标 */
	xl_uint16				dest_size_pv_index;		/*!< 目标尺寸 */
	xl_uint16				src_pos_pv_index;		/*!< 源图坐标 */
	xl_uint16				src_image_index;		/*!< 源图的索引 */
//	xlite_himage			src_image;				/*!< 源图资源 */
	xl_uint16				dummy;					/*!< 这里为了让结构4字节对齐*/
} xlite_sprite_frame_data_layer;

/*!
 * @brief 精灵的帧数据结构
 */
typedef struct  
{
	xl_uint32	number_layer;						/*!< 帧数据中的层数量*/
	xlite_rect  rectangle;
	xlite_sprite_frame_data_layer*	layers;			/*!< 帧数据层数组 */
} xlite_sprite_frame_data;

/*!
 * @brief 精灵逻辑帧结构
 */
typedef struct  
{
	xlite_flip_mode				flip_mode;			/*!< 翻转模式 */
	xl_uint16					dest_pos_pv_index;	/*!< 目标坐标 */
	xl_uint16					interval;			/*!< 该帧停留时间 */
	xl_uint16					number_bbox;		/*!< 碰撞盒的数量 */
	xlite_sprite_bbox*			bboxes;				/*!< 碰撞盒结构指针*/
	xlite_sprite_frame_data*	frame_data;			/*!< 该逻辑帧使用的帧数据指针 */
} xlite_sprite_frame;

/*!
 * @brief 精灵动作结构
 */
typedef struct  
{
	xlite_flip_mode		flip_mode;				/*!< 翻转模式 */
	xl_uint16			id;						/*!< 动作ID */
	xl_uint16			ref_id;					/*!< 引用ID */
	xl_uint16			number_frames;			/*!< 动作中包含的逻辑帧数量 */
	xlite_sprite_frame* frames;					/*!< 逻辑帧结构指针 */
} xlite_sprite_action;

/*!
 * @brief 精灵数据结构
 */
typedef struct  
{
	xl_uint32			hash;					/*!< 该精灵数据的Hash值 */
	xl_uint8			number_images;			/*!< 精灵数据引用的图片数量 */
	xlite_himage*		images;					/*!< 精灵数据引用的图片指针数组 */
	

	xl_uint16			anthor_pv_index;		/*!< 锚点的PV数组索引 */
	xl_uint16			size_pv_index;			/*!< 精灵尺寸的PV数组索引 */


	xl_uint32 number_actions;					/*!< 精灵数据包含的动作数 */
	xlite_sprite_action*		actions;		/*!< 动作数组指针 */

	xl_uint32 number_frame_data;				/*!< 精灵数据包含的帧数据数量 */
	xlite_sprite_frame_data*	frame_data;		/*!< 帧数据数组指针 */

	xlite_sprite_pair_value* pair_values;		/*!< PV数组指针 */

	xl_uint8*			mem_pool;				/*!< 内存池 */
	xl_uint32			pool_size;				/*!< 当前的内存池大小 */
	xl_uint32			pool_alloc_size;		/*!< 内存池已分配大小 */
} xlite_sprite_data;



/*!
 * @brief 精灵管理器结构
 */
typedef struct  
{
	xlite_image_storage*	image_storage;	/*!< 图片管理器 */
	xlite_storage			storage_impl;	/*!< 管理器 */
} xlite_sprite_storage;



//////////////////////////////////////////////////////////////////////////
// xlite_E_tilemap.h
//////////////////////////////////////////////////////////////////////////
/*! 
 * @brief 地图读取图形资源加载回调函数
 */
typedef xlite_himage (* xlite_E_tilemap_on_load_image)(xl_uint32 hash);
typedef xlite_sprite_data* (*xlite_E_tilemap_on_load_sprite)(xl_uint32 hash);

typedef struct  
{
	xlite_E_tilemap_on_load_image	load_image;
	xlite_E_tilemap_on_load_sprite	load_sprite;
} xlite_tilemap_load_callback;


#define	XLITE_E_TILEMAP_RESOURCE_IMAGE				1
#define XLITE_E_TILEMAP_RESOURCE_SPRITE				2


typedef struct  
{
	xl_uint8 type;
} xlite_tilemap_item_base;

typedef struct  
{
	xlite_tilemap_item_base base;
	xlite_flip_mode	flip_mode;
//	xl_uint8	blend_mode;				// Not support blend mode
	xl_uint8	key_color_filte;
	xl_uint8	resource_index;
	xl_int16	src_x;
	xl_int16	src_y;
	xl_uint16	src_w;
	xl_uint16	src_h;
} xlite_tilemap_item_image;

typedef struct  
{
	xlite_tilemap_item_base base;
	xl_uint16	action_id;
	xl_uint8	resource_index;
} xlite_tilemap_item_sprite;

typedef struct 
{
	xl_uint16 number_items;
	xlite_tilemap_item_base** items;
} xlite_tilemap_item_pool;


typedef struct  
{
	xl_uint8	type;
	xl_uint8	flags;
} xlite_tilemap_layer_data_base;

typedef struct
{
	xlite_tilemap_layer_data_base base;
	xlite_tilemap_item_pool item_pool;
	xl_int16 row;
	xl_int16 column;
	xl_uint16 tile_width;
	xl_uint16 tile_height;
	xl_uint16**	tile_item_index;
} xlite_tilemap_layer_data_tile;


typedef struct
{
	xl_uint16	flags;
	xl_uint16	item_index;
	xl_int16	x;
	xl_int16	y;
} xlite_tilemap_layer_data_free_item; 

typedef struct  
{
	xlite_tilemap_layer_data_base base;
	xl_uint16	count;
	xl_uint8	sort_method;
	xlite_tilemap_item_pool item_pool;
	xlite_tilemap_layer_data_free_item* items;
} xlite_tilemap_layer_data_free;

typedef struct  
{
	xlite_tilemap_layer_data_base base;
	xl_uint8 flag_bytes;
	xl_int16 row;
	xl_int16 column;
	xl_void** flags;
} xlite_tilemap_layer_data_tileflag;

typedef struct  
{
	xl_uint8 flags;
	xl_uint8 layer_index;
	xl_uint8 data_index;
	xl_int16 offset_x;
	xl_int16 offset_y;
	xl_uint16 bk_color;
	
} xlite_tilemap_layer;


typedef struct  
{
	xl_uint8 type;
	xl_uint32 hash;
	xl_void* data;
} xlite_tilemap_resource;

typedef struct  
{
	xl_uint32 hash;
	xl_uint8 scene_index;
	xl_uint8 number_layers;
	xl_uint8 number_resource;
	xlite_tilemap_layer_data_base** layer_data;
	xlite_tilemap_layer* layers;

	xl_uint8* mem_pool;
	xl_uint32 pool_size;
	xl_uint32 pool_alloc_size;

	
	xlite_tilemap_resource* resources;
} xlite_tilemap_data;


typedef struct
{
	xlite_sprite_storage*	sprite_storage;
	xlite_image_storage*	image_storage;
	xlite_storage			storage_impl;
} xlite_tilemap_storage;

//////////////////////////////////////////////////////////////////////////
// J11 tilemap
//////////////////////////////////////////////////////////////////////////

typedef struct  
{
	xl_uint16	value_1;
	xl_uint16	value_2;
} xlite_tilemap_j11_pair_value;

typedef struct
{
	xl_uint8 type;
	xl_uint8 added;
	xl_uint32 hash;
} xlite_tilemap_j11_resource;

typedef struct  
{
	xl_uint8 flags;
	xl_uint8 layer_data_index;
	xl_uint16 bk_color;
	xl_int16 offset;			/*! this is Index of pair values array. */
} xlite_tilemap_j11_layer;

typedef struct  
{
	xl_uint8 number_layers;
	xlite_tilemap_j11_layer* layers;
} xlite_tilemap_j11_scene;


typedef struct  
{
	const xl_uint8* buffer;
	xl_uint32 buffer_length;
	xl_uint32 current_pos;
	
	xl_uint32 hash;
	
	xlite_tilemap_j11_resource* resources;
	const xl_uint8* pair_value_buf;
	
	
	xlite_tilemap_j11_scene*	scenes;

	xl_uint8 number_scene;
	xl_uint8 number_resources;
	xl_uint8 number_frame_data;
	xl_uint8 last_error;


	xl_uint16* frame_data_size;
	const xl_uint8* frame_data_ptr;
	

	xl_uint8* mem_pool;
	xl_uint32 pool_size;
	xl_uint32 pool_alloc_size;

	xlite_E_tilemap_on_load_image load_image;
	xlite_E_tilemap_on_load_sprite load_sprite;
} xlite_tilemap_j11_decoder;


//////////////////////////////////////////////////////////////////////////
// xLite_E_tilemap_render
//////////////////////////////////////////////////////////////////////////
#define XLITE_E_TILEMAP_RENDER_FLAG_ENABLE_CACHE			0x01
#define XLITE_E_TILEMAP_RENDER_FLAG_ENABLE_SPRITE_UPDATING	0x02

typedef struct  
{
	xl_int16 x;
	xl_int16 y;
} xlite_tilemap_render_map_pos;


#define XLITE_E_TILEMAP_CACHE_UPDATE_ALL						0x04
#define XLITE_E_TILEMAP_CACHE_UPDATE_HORZ						0x01
#define XLITE_E_TILEMAP_CACHE_UPDATE_VERT						0x02
#define XLITE_E_TILEMAP_CACHE_UPDATE_NONE						0x00

typedef struct  
{
	xl_uint8 update_status;
	xlite_himage image;		// cached image
	xlite_tilemap_render_map_pos cached_pos;			// cached data position
	
	xl_int16 horz_update_left;
	xl_int16 horz_update_right;
	xl_int16 vert_update_top;
	xl_int16 vert_update_bottom;
} xlite_tilemap_render_cache;




typedef struct  
{
	xl_uint8	flags;		// flags of render
	xlite_tilemap_render_cache* cache;
	xlite_tilemap_data* data;
	xlite_graphics*	graphics;
	xlite_rect viewport;		// view port

	xlite_tilemap_render_map_pos map_pos;
} xlite_tilemap_render;




//////////////////////////////////////////////////////////////////////////
// xLite_E_http.h
//////////////////////////////////////////////////////////////////////////

/*! max URL length */
#define XLITE_E_HTTP_MAX_URL_LENGTH						0xFF
// host max length
#define XLITE_E_HTTP_MAX_HOST_LENGTH					64
// max uri length
#define XLITE_E_HTTP_MAX_URI_LENGTH						(XLITE_E_HTTP_MAX_URL_LENGTH - XLITE_E_HTTP_MAX_HOST_LENGTH - 7)
// max header length
#define XLITE_E_HTTP_MAX_HEADER_LENGTH					1024
// Buffer Length
#define XLITE_E_HTTP_BUFFER_LENGTH						20480
// HTTP行的长度
#define XLITE_E_HTTP_MAX_LINE_LENGTH					1024
// Value的最长的长度
#define XLITE_E_HTTP_MAX_VALUE_LENGTH					96
// Http-method
#define XLITE_E_HTTP_METHOD_GET							0x00
#define XLITE_E_HTTP_METHOD_POST						0x01
// Http connection
#define XLITE_E_HTTP_CONN_CLOSE							0x00
#define XLITE_E_HTTP_CONN_KEEP_ALIVE					0x01
// header
#define XLITE_E_HTTP_HEADER_USER_AGENT					"GTS_GTSBOX"
// 最大同时开辟会话个数
#define XLITE_E_HTTP_MAX_SESSION_OPEN					3
// 默认超时ms
#define XLITE_E_HTTP_TIMEOUT							30000

//////////////////////////////////////////////////////////////////////////
// Error no
//////////////////////////////////////////////////////////////////////////
#define XLITE_E_HTTP_ERR_SUCCESS						0
#define XLITE_E_HTTP_ERR_GETHOSTBYNAME					-1
#define XLITE_E_HTTP_ERR_CONNECT_FAIL					-2
#define XLITE_E_HTTP_ERR_BUFFER_OVERFLOW				-3
#define XLITE_E_HTTP_ERR_INVALID_URL					-4
#define XLITE_E_HTTP_ERR_NO_SERVICE						-5
#define XLITE_E_HTTP_ERR_REQUEST_EXIST					-6
#define XLITE_E_HTTP_ERR_NOT_ENOUGH_MEMORY				-7
#define XLITE_E_HTTP_ERR_SEND_FAIL						-8
#define XLITE_E_HTTP_ERR_RECEIVE_FAIL					-9
#define XLITE_E_HTTP_ERR_MAX_SESSION					-10
#define XLITE_E_HTTP_ERR_TIMEOUT						-11
#define XLITE_E_HTTP_ERR_RESPONSE							-12

#ifndef XLITE_NO_NETWORK
// HTTP 事件
typedef enum
{
	// HTTP连接建立/失败
	xlite_http_connect = 0,
	// HTTP数据缓冲区空
	xlite_http_buffer_sent,
	// 接收到HTTP行
	xlite_http_line_recv,
	// HTTP头接收完毕
	xlite_http_head_recv,
	// 接收到http body
	xlite_http_body_recv,
	// HTTP请求中断
	xlite_http_close,
	// HTTP会话出错，关闭当前会话
	xlite_http_error
} xlite_http_event;



// Http事件回调
// 当事件为 xlite_http_buffer_sent的时候
// 如果返回0说无数据可以写了,否则返回继续写的数据长度
// 当时间为 xlite_http_line_recv的时候
// code为line的长度
// 当事件为 xlite_http_body_recv的时候
// code为当前body在缓冲区的长度
// 返回0说明还没有处理,否则返回处理的字节数
typedef xl_int32 (* xlite_E_http_event_handler)(xlite_http_event,xl_int32 code,xl_void* session);


// HTTP 请求
typedef struct  
{
	// proxy type
	xl_uint8 use_proxy;
	// url
	xl_char url[XLITE_E_HTTP_MAX_URL_LENGTH + 1];
	// url length
	xl_uint32 url_len;
	// url only hash
	xl_uint32 url_hash;
	// Proxy Server addr
	xlite_socket_sockaddr_struct proxy_addr;
	// header
	xl_char *header;
	// header length
	xl_uint32 header_len;
	// body length
	xl_uint32 body_len;

	// handler
	xlite_E_http_event_handler handler;
} xlite_http_request;


#define XLITE_E_HTTP_SESSION_CLOSE						0x00
#define XLITE_E_HTTP_SESSION_QUERY_HOST					0x01		// gethostbyname
#define XLITE_E_HTTP_SESSION_CONNECTING					0x02
#define XLITE_E_HTTP_SESSION_CONNECTED					0x03
#define XLITE_E_HTTP_SESSION_SENDING					0x04
#define XLITE_E_HTTP_SESSION_SENT						0x05
#define XLITE_E_HTTP_SESSION_RECEIVING					0x06
#define XLITE_E_HTTP_SESSION_RECEIVED					0x07
#define XLITE_E_HTTP_SESSION_ERROR						0x08		//something wrong, close session

// HTTP Session
typedef struct  
{
	// 当前Session的状态
	xl_uint8 state;
// 	// 连接方式
// 	xl_uint8 http_conn;
// 	// method
// 	xl_uint8 http_method;
	// HTTP头是否已经收完了
	xl_uint8 http_head_recv;
	// HTTP 响应码
	xl_int32 http_response_code;
	// 连接socket
	xlite_socket sock;
	// 连接的地址
	xlite_socket_sockaddr_struct conn_addr;
	// 目标URL
	xl_char dest_url[XLITE_E_HTTP_MAX_URL_LENGTH + 1];
	// Host
	xl_char dest_host[XLITE_E_HTTP_MAX_HOST_LENGTH + 1];
	// 目标端口
	xl_uint32 dest_port;
	// 目标URI
	xl_char dest_uri[XLITE_E_HTTP_MAX_URI_LENGTH + 1];
	// Data buffer
	xl_uint8 buffer[XLITE_E_HTTP_BUFFER_LENGTH];
	// 当前发送的长度
	xl_uint16 buf_pos;
	// 当前buffer中有效内容的长度
	xl_uint16 buf_length;
	// header
	xl_char header[XLITE_E_HTTP_MAX_HEADER_LENGTH];
	// header长度
	xl_int32 header_length;		
	// Body 的长度,如果body_length为-1的话,说明还在解析http头
	xl_int32 body_length;		
	// 已经处理(send or receive)完成的长度(包括header和body)
	xl_int32 finished_length;		
	// HTTP回调函数地址
	xlite_E_http_event_handler http_event_handler;
	// 错误信息
	xl_int32 error_code;
	// 连接timeout
	xl_int32 conn_timeout;
	// 发送timeout
	xl_int32 send_timeout;
	// 接受timeout
	xl_int32 recv_timeout;
	// 最后成功操作时间
	xl_int32 last_act_time;
	//net和wap的标志
	xl_bool net_or_wap;

} xlite_http_session;


#endif


typedef struct  
{
	xlite_socket_sockaddr_struct conn_addr;
	xl_char dest_url[XLITE_E_HTTP_MAX_URL_LENGTH + 1];
	xl_uint32 dest_port;
} xlite_http_host;

#endif
