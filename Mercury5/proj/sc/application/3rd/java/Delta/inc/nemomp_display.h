#ifndef __NEMOMP_DISPLAY_H__
#define __NEMOMP_DISPLAY_H__

typedef enum JUI_SCREEN_MODE_ENUM
{
    NM_DISPLAY_MODE_NORMAL,
    NM_DISPLAY_MODE_FULL,
} nm_display_mode_enum;

#define  NM_COLOR_RGB_TO_PIXEL(R,G,B)	( (nm_uint16)(((B)&0xf8)>>3)|(((G)&0xfc)<<3)|(((R)&0xf8)<<8) ) // 565

extern nm_uint16 **display_buffer_address; // 20090210: Added
extern nm_uint16 *java_lcd_buffer;
///extern nm_uint16 *j9_display_lcd_buffer; //  20090210: Removed; 20081224: Moved from midp\helpers.c
     
extern nm_int32 nemomp_display_initialize(void);
extern void nemomp_display_finalize(void);
extern void nemomp_display_set_screen_mode(nm_display_mode_enum mode);
extern void nemomp_display_get_displayable_area(
        nm_int32 *x,
        nm_int32 *y,
        nm_int32 *width,
        nm_int32 *height);
extern nm_int32 nemomp_display_get_display_x(void); // 20081118: Added
extern nm_int32 nemomp_display_get_display_y(void); // 20081118: Added
extern nm_int32 nemomp_display_get_display_width(void);
extern nm_int32 nemomp_display_get_display_height(void);
extern void nemomp_display_get_properties(nm_int32 *width, nm_int32 *height, nm_int32 *adornedHeight, nm_int32 *depth, nm_int32 *numAlphaLevels); // 20081118: Changed
extern void nemomp_display_refresh_lcd(nm_int32 x1, nm_int32 y1, nm_int32 x2, nm_int32 y2);
extern void nemomp_display_clear_screen(void);
extern nm_char* nemomp_jpeg_decodeimage(nm_char *buffer,
                                  nm_int32 length,
                                  nm_int32(*image_alloc)(nm_int32 width, nm_int32 height, nm_char **dst),
                                  nm_char **errThrowClassName);

extern nm_char* nemomp_gif_decodeimage(nm_char *buffer,
                                  nm_int32 length,
                                  nm_bool* gifTrans,
                                  nm_int32(*image_alloc)(nm_int32 width, nm_int32 height, nm_char **dst),
                                  nm_char **errThrowClassName);


// 20081124: Added
extern nm_int32* nemomp_png_decodeimage(nm_char *buffer,
                                  nm_int32 length,
                                  nm_int32(*image_alloc)(nm_int32 width, nm_int32 height, nm_char **dst),
                                  nm_char **errThrowClassName);

extern void nemomp_display_show_logo(void);

#endif /* __NEMOMP_DISPLAY_H__ */
