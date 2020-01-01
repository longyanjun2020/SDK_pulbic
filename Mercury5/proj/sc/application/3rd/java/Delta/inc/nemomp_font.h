#ifndef __NEMOMP_FONT_H__
#define __NEMOMP_FONT_H__

/* Sync with ~\src\midp\common\common.h  */
#define GRAPHICS_HCENTER		1
#define GRAPHICS_VCENTER		2
#define GRAPHICS_LEFT			4
#define GRAPHICS_RIGHT			8
#define GRAPHICS_TOP			16
#define GRAPHICS_BOTTOM			32
#define GRAPHICS_BASELINE		64

/* Sync with ~\src\midp\common\common.h  */
#define FONT_SIZE_MEDIUM		0
#define FONT_SIZE_SMALL			8
#define FONT_SIZE_LARGE			16

/* Sync with ~\src\midp\common\common.h  */
#define FONT_FACE_SYSTEM		0
#define FONT_FACE_MONOSPACE		32
#define FONT_FACE_PROPORTIONAL	64

/* Sync with ~\src\midp\common\common.h  */
#define FONT_STYLE_PLAIN		0
#define FONT_STYLE_BOLD			1
#define FONT_STYLE_ITALIC		2
#define FONT_STYLE_UNDERLINED	4

extern void nemomp_font_draw_string(
        nm_int32 pixel,
        short *clip,
        unsigned short *dst,
        nm_int32 dst_width,
        nm_int32 dst_height,
        nm_int32 buffer_size,
        nm_int32 dotted,
        nm_int32 face,
        nm_int32 style,
        nm_int32 size,
        nm_int32 x,
        nm_int32 y,
        nm_int32 anchor,
        const nm_uint16 *chararray,
        nm_int32 n);
        
extern void nemomp_font_get_info(
        nm_int32 face,
        nm_int32 style,
        nm_int32 size,
        nm_int32 *ascent,
        nm_int32 *descent,
        nm_int32 *leading);
        
extern nm_int32 nemomp_font_get_string_width(
            nm_int32 face,
            nm_int32 style,
            nm_int32 size,
            const nm_uint16 *charArray,
            nm_int32 n);

#endif /* __NEMOMP_FONT_H__ */
