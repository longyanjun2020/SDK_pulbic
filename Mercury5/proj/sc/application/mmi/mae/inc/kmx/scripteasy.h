
/*

    ScriptEasy Interface.

    Version 1.11

    Copyright (C) 2000-2009 Beijing Komoxo Inc.
    All rights reserved.

*/

#ifndef SCRIPTEASY_H
#define SCRIPTEASY_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************
 *                                                                         *
 * Basic data types                                                        *
 *                                                                         *
 ***************************************************************************/

#ifndef TRUE
    #define TRUE            1
#endif

#ifndef FALSE
    #define FALSE           0
#endif

typedef int                 sebool;

typedef int                 sestatus;

typedef unsigned int        secolor;

/* For UTF-16 character and string */
typedef unsigned short      seunichar16;

/* For UTF-32 character and string */
typedef unsigned int        seunichar32;

typedef struct
{
    int     left;
    int     top;
    int     right;
    int     bottom;
} SeRectangle;

typedef struct
{
    int     num_total_lines;
    int     num_visible_lines;
    int     first_visible_line;
    int     caret_line;
    int     text_height;
    int     max_line_height;
} SeScrollInfo;

/***************************************************************************
 *                                                                         *
 * Status codes                                                            *
 *                                                                         *
 ***************************************************************************/

#define SE_STATUS_OK                        0

#define SE_STATUS_VISIBLE                   1
#define SE_STATUS_INVISIBLE                 2
#define SE_STATUS_OUTSIDE                   3
#define SE_STATUS_NO_TEXT                   4
#define SE_STATUS_OUT_OF_START              5
#define SE_STATUS_OUT_OF_END                6

#define SE_STATUS_INVALID_PARAMETER         -1
#define SE_STATUS_INVALID_DEVICE_CONTEXT    -2
#define SE_STATUS_TEXT_ILL_FORMED           -3
#define SE_STATUS_MARKUP_ILL_FORMED         -4
#define SE_STATUS_TEXT_TOO_LONG             -5
#define SE_STATUS_NO_FONT                   -6
#define SE_STATUS_NOT_INITIALIZED           -7
#define SE_STATUS_OUT_OF_MEMORY             -8
#define SE_STATUS_FONT_IN_USE               -9

/***************************************************************************
 *                                                                         *
 * Initialization/Cleanup                                                  *
 *                                                                         *
 ***************************************************************************/

typedef unsigned int (*SeFontAccessFunc)(
    void*           name,
    void*           buffer,
    unsigned int    offset,
    unsigned int    size);

typedef struct
{
    int                 language;
    const void*         language_data;
    const void*         font_table;
    const void*         logical_font_table;
    SeFontAccessFunc    font_access_callback;
    void*               mem_pool;
    int                 mem_pool_size;
    void*               cache_mem_pool;
    int                 cache_mem_pool_size;
} SeInitInfo;

const char* se_get_version(void);

const void* se_get_thai_language_data(void);

sestatus se_initialize(const SeInitInfo* init_info);
sestatus se_cleanup(void);

sestatus se_set_language(
    int                 language,
    const void*         language_data);

sestatus se_set_font_table(
    const void*         physical_font_table,
    const void*         logical_font_table,
    SeFontAccessFunc    font_access_callback);

sestatus se_set_cache(
    void*               cache_mem_pool,
    int                 cache_mem_pool_size);

sestatus se_set_chip_param(void* chip_param);

/***************************************************************************
 *                                                                         *
 * Data type: SeRectangle                                                  *
 *                                                                         *
 ***************************************************************************/

void se_set_rect(
    SeRectangle*        r,
    int                 left,
    int                 top,
    int                 right,
    int                 bottom);

void se_copy_rect(
    SeRectangle*        dst,
    const SeRectangle*  src);

sebool se_is_rect_equal(
    const SeRectangle*  r1,
    const SeRectangle*  r2);

void se_set_empty_rect(
    SeRectangle*        r);

sebool se_is_rect_empty(
    const SeRectangle*  r);

sebool se_point_inside_rect(
    const SeRectangle*  r,
    int                 x,
    int                 y);

void se_offset_rect(
    SeRectangle*        r,
    int                 dx,
    int                 dy);

void se_inflate_rect(
    SeRectangle*        r,
    int                 dx,
    int                 dy);

sebool se_intersect_rect(
    SeRectangle*        dst,
    const SeRectangle*  src1,
    const SeRectangle*  src2);

sebool se_union_rect(
    SeRectangle*        dst,
    const SeRectangle*  src1,
    const SeRectangle*  src2);

/***************************************************************************
 *                                                                         *
 * Data type: secolor                                                      *
 *                                                                         *
 ***************************************************************************/

secolor se_color_rgb(
    unsigned char       red,
    unsigned char       green,
    unsigned char       blue);

secolor se_color_rgba(
    unsigned char       red,
    unsigned char       green,
    unsigned char       blue,
    unsigned char       alpha);

unsigned char se_color_red(secolor color);
unsigned char se_color_green(secolor color);
unsigned char se_color_blue(secolor color);
unsigned char se_color_alpha(secolor color);

secolor se_color_set_red(secolor color, unsigned char red);
secolor se_color_set_green(secolor color, unsigned char green);
secolor se_color_set_blue(secolor color, unsigned char blue);
secolor se_color_set_alpha(secolor color, unsigned char alpha);

/***************************************************************************
 *                                                                         *
 * Text output                                                             *
 *                                                                         *
 ***************************************************************************/

#define SE_MAX_TEXT_LENGTH          1023
#define SE_MAX_OPT_TEXT_LENGTH      20481
#define SE_MAX_MULTILINE_EDITOR_TEXT_LENGTH     20480
#define SE_MAX_SINGLELINE_EDITOR_TEXT_LENGTH    1023
#define SE_MAX_VIEWER_TEXT_LENGTH   2047
#define SE_MAX_FONT_SIZE            127

#define SE_LOGFONT_BOLD             0x01
#define SE_LOGFONT_ITALIC           0x02
#define SE_LOGFONT_UNDERLINE        0x04
#define SE_LOGFONT_STRIKETHROUGH    0x08
#define SE_LOGFONT_PREFERRED        0x10
#define SE_LOGFONT_MONO             0x20

typedef struct
{
    unsigned short  size;
    unsigned char   attr;
    unsigned char   id;
} SeLogFont;

#define SE_BITMAP_MONO              0
#define SE_BITMAP_GRAY_4            1
#define SE_BITMAP_GRAY_16           2
#define SE_BITMAP_GRAY_256          3

typedef struct
{
    int     format;
    int     width;
    int     height;
    int     pitch;
    void*   buffer;
} SeBitmap;

#define SE_FLAG_MULTILINE           0x0001
#define SE_FLAG_OPAQUE              0x0002
#define SE_FLAG_MARKUP              0x0004
#define SE_FLAG_BORDER              0x0008
#define SE_FLAG_SHADOW              0x0010
#define SE_FLAG_PASSWORD            0x0020
#define SE_FLAG_WRAPCHAR            0x0040
#define SE_FLAG_DIVIDER             0x8000

#define SE_ALIGN_LEFT               0
#define SE_ALIGN_CENTER             1
#define SE_ALIGN_RIGHT              2

#define SE_ELLIPSIZE_NONE           0
#define SE_ELLIPSIZE_START          1
#define SE_ELLIPSIZE_MIDDLE         2
#define SE_ELLIPSIZE_END            3

typedef struct
{
    int             device_width;
    int             device_height;
    void*           device_data;

    void (*draw_pixel)(
        void*               device_data,
        int                 x,
        int                 y,
        secolor             color);

    void (*draw_bitmap)(
        void*               device_data,
        int                 x_dst,
        int                 y_dst,
        const SeBitmap*     bitmap,
        int                 x_src,
        int                 y_src,
        int                 width,
        int                 height,
        secolor             color);

    void (*draw_rect)(
        void*               device_data,
        const SeRectangle*  rect,
        secolor             color);

    void (*revert_rect)(
        void*               device_data,
        const SeRectangle*  rect);

    void (*draw_divider) (
        void*               device_data,
        const SeRectangle*  rect,
        const SeRectangle*  clip);

    void (*update)(
        void*               device_data,
        const SeRectangle*  rect);

    SeRectangle     clip;

    SeLogFont       font;
    int             text_flags;
    secolor         text_color;
    secolor         bk_color;
    int             alignment;

    /* For single-line text output */
    int             ellipsize;
    int             ellipsize_width;

    /* For multi-line text output */
    int             wrap_width;
    int             line_spacing;
} SeDeviceContext;

sestatus se_draw_pixel(
    const SeDeviceContext* dc,
    int                 x,
    int                 y,
    secolor             color);

sestatus se_draw_line(
    const SeDeviceContext* dc,
    int                 x1,
    int                 y1,
    int                 x2,
    int                 y2,
    secolor             color);

sestatus se_draw_rect(
    const SeDeviceContext* dc,
    const SeRectangle*  rect,
    secolor             color);

sestatus se_check_markup(
    const seunichar16*  text,
    int                 length);

sestatus se_get_text_line_height(
    const SeDeviceContext* dc,
    int*                height);

sestatus se_get_text_extent(
    const SeDeviceContext* dc,
    const seunichar16*  text,
    int                 length,
    int*                width,
    int*                height,
    int*                lines);

sestatus se_draw_text(
    const SeDeviceContext* dc,
    int                 x,
    int                 y,
    const seunichar16*  text,
    int                 length);

sestatus se_draw_text_ext(
    const SeDeviceContext* dc,
    const SeRectangle*  rect,
    const seunichar16*  text,
    int                 length);

sestatus se_analysis_next_page(
    const SeDeviceContext* dc,
    const seunichar16*  text,
    int                 length,
    int*                page_end_offset);

sestatus se_analysis_next_line(
    const SeDeviceContext* dc,
    const seunichar16*  text,
    int                 length,
    int*                line_end_offset,
    int*                line_width);

sestatus se_draw_char(
    const SeDeviceContext*  input_dc,
    int                     x,
    int                     y,
    seunichar16             c);

sestatus se_get_char_extent(
    const SeDeviceContext*  input_dc,
    seunichar16             c,
    SeRectangle             *logical_rect,
    SeRectangle             *ink_rect);

sestatus se_get_char_font_id(
    const SeDeviceContext*  input_dc,
    seunichar16             c,
    int                     *font_id);

sestatus se_draw_text_opt(
    const SeDeviceContext* dc,
    int                 x,
    int                 y,
    const seunichar16*  text,
    int                 length);

sestatus se_get_text_extent_opt(
    const SeDeviceContext* dc,
    const seunichar16*  text,
    int                 length,
    int*                width,
    int*                height,
    int*                lines);

sestatus se_analysis_next_line_opt(
    const SeDeviceContext* dc,
    const seunichar16*  text,
    int                 length,
    int*                line_end_offset,
    int*                line_width);

/***************************************************************************
 *                                                                         *
 * Text editor                                                             *
 *                                                                         *
 ***************************************************************************/

typedef struct tagSeEditor SeEditor;

typedef struct
{
    secolor             bk_color;
    secolor             text_color;
    secolor             comp_bk_color;
    secolor             comp_text_color;
} SeEditorPalette;

typedef struct
{
    int                 flags;
    const SeDeviceContext* dc;
    int                 max_buffer;
    const seunichar16*  text;
    int                 text_length;
    SeRectangle         pos;
    SeRectangle         margin;
    SeEditorPalette     palette;

    /* External memory management routines */
    void* (*malloc) (unsigned int size);
    void* (*realloc) (void* ptr, unsigned int size);
    void  (*free) (void* ptr);
} SeEditorInit;

typedef struct
{
    const seunichar16*  text_before_caret;
    int                 text_before_caret_length;
    const seunichar16*  text_after_caret;
    int                 text_after_caret_length;
} SeEditorInputContext;

/* Constructor and destructor */

sestatus se_editor_create(
    const SeEditorInit* init,
    SeEditor**          editor);

sestatus se_editor_destroy(
    SeEditor*           editor);

/* Properties */

sestatus se_editor_get_flags(
    const SeEditor*     editor,
    int*                flags);

sestatus se_editor_get_max_buffer(
    const SeEditor*     editor,
    int*                max_buffer);

/* Painting and display */

sestatus se_editor_set_device_context(
    SeEditor*           editor,
    const SeDeviceContext* dc);

sestatus se_editor_set_clip(
    SeEditor*           editor,
    const SeRectangle   *clip);

sestatus se_editor_set_font_size(
    SeEditor*           editor,
    unsigned short      font_size);

sestatus se_editor_set_preferred_font_id(
    SeEditor*           editor,
    unsigned char       font_id);

sestatus se_editor_get_pos(
    const SeEditor*     editor,
    SeRectangle*        pos);

sestatus se_editor_set_pos(
    SeEditor*           editor,
    const SeRectangle*  pos);

sestatus se_editor_get_caret_pos(
    const SeEditor*     editor,
    SeRectangle*        pos);

sestatus se_editor_get_margin(
    const SeEditor*     editor,
    SeRectangle*        margin);

sestatus se_editor_set_margin(
    SeEditor*           editor,
    const SeRectangle*  margin);

sestatus se_editor_get_palette(
    const SeEditor*     editor,
    SeEditorPalette*    palette);

sestatus se_editor_set_palette(
    SeEditor*           editor,
    const SeEditorPalette* palette);

sestatus se_editor_paint(
    SeEditor*           editor);

sestatus se_editor_lock(
    SeEditor*           editor);

sestatus se_editor_unlock(
    SeEditor*           editor);

/* Text manipulating */

sestatus se_editor_set_text(
    SeEditor*           editor,
    const seunichar16*  text,
    int                 length);

sestatus se_editor_get_text(
    const SeEditor*     editor,
    const seunichar16** text,
    int*                length,
    int*                num_chars);

sestatus se_editor_clear_content(
    SeEditor*           editor);

sestatus se_editor_backspace(
    SeEditor*           editor);

sestatus se_editor_insert_text(
    SeEditor*           editor,
    const seunichar16*  text,
    int                 length);

sestatus se_editor_build_layout(SeEditor* editor);

/* Caret handling */

sestatus se_editor_switch_caret(
    SeEditor*           editor);

sestatus se_editor_show_caret(
    SeEditor*           editor);

sestatus se_editor_hide_caret(
    SeEditor*           editor);

sestatus se_editor_is_caret_visible(
    const SeEditor*     editor);

sestatus se_editor_move_caret_left(
    SeEditor*           editor);

sestatus se_editor_move_caret_right(
    SeEditor*           editor);

sestatus se_editor_move_caret_up(
    SeEditor*           editor);

sestatus se_editor_move_caret_down(
    SeEditor*           editor);

sestatus se_editor_locate_caret(
    SeEditor*           editor,
    int                 x,
    int                 y);

sestatus se_editor_get_caret_by_pos(
    SeEditor*           editor,
    int                 x,
    int                 y,
	int*				caret_text_index);

sestatus se_editor_get_scroll_info(
    const SeEditor*     editor,
    SeScrollInfo*       info);

sestatus se_editor_set_first_visible_line(
    SeEditor*     editor,
    int           first_visible_line);

sestatus se_editor_get_caret_text_index(
    const SeEditor*     editor,
    int                 *text_index);

sestatus se_editor_set_caret_text_index(
    SeEditor*           editor,
    int                 text_index);

sestatus se_editor_set_selection(
    SeEditor            *editor,
    int                 start,
    int                 end);

sestatus se_editor_get_selection(
    const SeEditor      *editor,
    int                 *start,
    int                 *end);
sestatus se_editor_get_caret(const SeEditor* editor, int* caret);
sestatus se_editor_cancel_selection(
    SeEditor* editor);

sestatus se_editor_get_line_info(
    const SeEditor  *editor,
    int             line_index,
    int             *start_index,
    int             *length);

sestatus se_editor_get_line_from_index(
    const SeEditor  *editor,
    int             index,
    int             *line_index);

/***************************************************************************
 *                                                                         *
 * Text viewer                                                             *
 *                                                                         *
 ***************************************************************************/

typedef struct tagSeViewer SeViewer;

typedef struct
{
    secolor             bk_color;
    secolor             text_color;
} SeViewerPalette;

typedef struct
{
    int                 flags;
    const SeDeviceContext* dc;
    const seunichar16*  text;
    int                 text_length;
    SeRectangle         pos;
    SeRectangle         margin;
    SeViewerPalette     palette;
} SeViewerInit;

/* Constructor and destructor */

sestatus se_viewer_create(
    const SeViewerInit* init,
    SeViewer**          viewer);

sestatus se_viewer_destroy(
    SeViewer*           viewer);

/* Properties */

sestatus se_viewer_get_flags(
    const SeViewer*     viewer,
    int*                flags);

/* Painting and display */

sestatus se_viewer_get_pos(
    const SeViewer*     viewer,
    SeRectangle*        pos);

sestatus se_viewer_set_pos(
    SeViewer*           viewer,
    const SeRectangle*  pos);

sestatus se_viewer_get_margin(
    const SeViewer*     viewer,
    SeRectangle*        margin);

sestatus se_viewer_set_margin(
    SeViewer*           viewer,
    const SeRectangle*  margin);

sestatus se_viewer_get_palette(
    const SeViewer*     viewer,
    SeViewerPalette*    palette);

sestatus se_viewer_set_palette(
    SeViewer*           viewer,
    const SeViewerPalette* palette);

sestatus se_viewer_paint(
    SeViewer*           viewer);

sestatus se_viewer_lock(
    SeViewer*           viewer);

sestatus se_viewer_unlock(
    SeViewer*           viewer);

/* Text manipulating */

sestatus se_viewer_get_text(
    const SeViewer*     viewer,
    const seunichar16** text,
    int*                length,
    int*                num_chars);

sestatus se_viewer_set_text(
    SeViewer*           viewer,
    const seunichar16*  text,
    int                 length);

/* Scroll handling */

sestatus se_viewer_scroll_up(
    SeViewer*           viewer);

sestatus se_viewer_scroll_down(
    SeViewer*           viewer);

sestatus se_viewer_scroll_home(
    SeViewer*           viewer);

sestatus se_viewer_scroll_end(
    SeViewer*           viewer);

sestatus se_viewer_get_scroll_info(
    const SeViewer*     viewer,
    SeScrollInfo*       info);

/***************************************************************************
 *                                                                         *
 * Extention Routines                                                      *
 *                                                                         *
 ***************************************************************************/

typedef unsigned char (*SeTransformAlphaFunc) (unsigned char alpha);
void se_ext_set_pure_color_bg_actived(int bValue);
sebool se_ext_565_alpha_blending_pcb(
    unsigned short          fg_color,
    unsigned short          bg_color,
    const SeBitmap*         bitmap,
    int                     x_src,
    int                     y_src,
    int                     width,
    int                     height,
    unsigned short          *dest,
    int                     device_width,
    SeTransformAlphaFunc    transform_alpha);

/***************************************************************************
 *                                                                         *
 * List of language data                                                   *
 *                                                                         *
 ***************************************************************************/

extern const char se_thai_language_data[];

/***************************************************************************
 *                                                                         *
 * List of language codes                                                  *
 *                                                                         *
 ***************************************************************************/

#define SE_LANG_AA              0       /* Afar                            */
#define SE_LANG_AB              1       /* Abkhazia                        */
#define SE_LANG_AF              2       /* Afrikaans                       */
#define SE_LANG_AM              3       /* Amharic                         */
#define SE_LANG_AR              4       /* Arabic                          */
#define SE_LANG_AS              5       /* Assamese                        */
#define SE_LANG_AST             6       /* Asturian                        */
#define SE_LANG_AVA             7       /* Avaric                          */
#define SE_LANG_AY              8       /* Aymara                          */
#define SE_LANG_AZ              9       /* Azerbaijani                     */
#define SE_LANG_AZ_IR           10      /* Azerbaijani in Iran             */
#define SE_LANG_BA              11      /* Bashkir                         */
#define SE_LANG_BAM             12      /* Bambara                         */
#define SE_LANG_BE              13      /* Byelorussian                    */
#define SE_LANG_BG              14      /* Bulgarian                       */
#define SE_LANG_BH              15      /* Bihari (Devanagari script)      */
#define SE_LANG_BHO             16      /* Bhojpuri (Devanagari script)    */
#define SE_LANG_BI              17      /* Bislama                         */
#define SE_LANG_BIN             18      /* Edo or Bini                     */
#define SE_LANG_BN              19      /* Bengali (Bengali script)        */
#define SE_LANG_BO              20      /* Tibetan                         */
#define SE_LANG_BR              21      /* Breton                          */
#define SE_LANG_BS              22      /* Bosnian                         */
#define SE_LANG_BUA             23      /* Buriat (Buryat)                 */
#define SE_LANG_CA              24      /* Catalan                         */
#define SE_LANG_CE              25      /* Chechen                         */
#define SE_LANG_CH              26      /* Chamorro                        */
#define SE_LANG_CHM             27      /* Mari (Lower & Upper Cheremis)   */
#define SE_LANG_CHR             28      /* Cherokee                        */
#define SE_LANG_CO              29      /* Corsican                        */
#define SE_LANG_CS              30      /* Czech                           */
#define SE_LANG_CU              31      /* Old Church Slavonic             */
#define SE_LANG_CV              32      /* Chuvash                         */
#define SE_LANG_CY              33      /* Welsh                           */
#define SE_LANG_DA              34      /* Danish                          */
#define SE_LANG_DE              35      /* German                          */
#define SE_LANG_DZ              36      /* Dzongkha                        */
#define SE_LANG_EL              37      /* Greek                           */
#define SE_LANG_EN              38      /* English                         */
#define SE_LANG_EO              39      /* Esperanto                       */
#define SE_LANG_ES              40      /* Spanish                         */
#define SE_LANG_ET              41      /* Estonian                        */
#define SE_LANG_EU              42      /* Basque                          */
#define SE_LANG_FA              43      /* Persian                         */
#define SE_LANG_FI              44      /* Finnish                         */
#define SE_LANG_FJ              45      /* Fijian                          */
#define SE_LANG_FO              46      /* Faroese                         */
#define SE_LANG_FR              47      /* French                          */
#define SE_LANG_FUL             48      /* Fulah (Fula)                    */
#define SE_LANG_FUR             49      /* Friulian                        */
#define SE_LANG_FY              50      /* Frisian                         */
#define SE_LANG_GA              51      /* Irish                           */
#define SE_LANG_GD              52      /* Scots Gaelic                    */
#define SE_LANG_GEZ             53      /* Ethiopic (Geez)                 */
#define SE_LANG_GL              54      /* Galician                        */
#define SE_LANG_GN              55      /* Guarani                         */
#define SE_LANG_GU              56      /* Gujarati                        */
#define SE_LANG_GV              57      /* Manx Gaelic                     */
#define SE_LANG_HA              58      /* Hausa                           */
#define SE_LANG_HAW             59      /* Hawaiian                        */
#define SE_LANG_HE              60      /* Hebrew                          */
#define SE_LANG_HI              61      /* Hindi (Devanagari script)       */
#define SE_LANG_HO              62      /* Hiri Motu                       */
#define SE_LANG_HR              63      /* Croatian                        */
#define SE_LANG_HU              64      /* Hungarian                       */
#define SE_LANG_HY              65      /* Armenian                        */
#define SE_LANG_IA              66      /* Interlingua                     */
#define SE_LANG_IBO             67      /* Igbo (Ibo)                      */
#define SE_LANG_ID              68      /* Indonesian                      */
#define SE_LANG_IE              69      /* Interlingue                     */
#define SE_LANG_IK              70      /* Inupiaq (Inupiak, Eskimo)       */
#define SE_LANG_IO              71      /* Ido                             */
#define SE_LANG_IS              72      /* Icelandic                       */
#define SE_LANG_IT              73      /* Italian                         */
#define SE_LANG_IU              74      /* Inuktitut                       */
#define SE_LANG_JA              75      /* Japaness                        */
#define SE_LANG_KA              76      /* Georgian                        */
#define SE_LANG_KAA             77      /* Kara-Kalpak (Karakalpak)        */
#define SE_LANG_KI              78      /* Kikuyu                          */
#define SE_LANG_KK              79      /* Kazakh                          */
#define SE_LANG_KL              80      /* Greenlandic                     */
#define SE_LANG_KM              81      /* Khmer                           */
#define SE_LANG_KN              82      /* Kannada                         */
#define SE_LANG_KO              83      /* Korean                          */
#define SE_LANG_KOK             84      /* Kokani (Devanagari script)      */
#define SE_LANG_KS              85      /* Kashmiri (Devanagari script)    */
#define SE_LANG_KU              86      /* Kurdish                         */
#define SE_LANG_KU_IR           87      /* Kurdish in Iran                 */
#define SE_LANG_KUM             88      /* Kumyk                           */
#define SE_LANG_KV              89      /* Komi (Komi-Permyak/Komi-Siryan) */
#define SE_LANG_KW              90      /* Cornish                         */
#define SE_LANG_KY              91      /* Kirgiz                          */
#define SE_LANG_LA              92      /* Latin                           */
#define SE_LANG_LB              93      /* Luxembourgish (Letzeburgesch)   */
#define SE_LANG_LEZ             94      /* Lezghian (Lezgian)              */
#define SE_LANG_LN              95      /* Lingala                         */
#define SE_LANG_LO              96      /* Lao                             */
#define SE_LANG_LT              97      /* Lithuanian                      */
#define SE_LANG_LV              98      /* Latvian                         */
#define SE_LANG_MG              99      /* Malagasy                        */
#define SE_LANG_MH              100     /* Marshallese                     */
#define SE_LANG_MI              101     /* Maori                           */
#define SE_LANG_MK              102     /* Macedonian                      */
#define SE_LANG_ML              103     /* Malayalam                       */
#define SE_LANG_MN              104     /* Mongolian                       */
#define SE_LANG_MO              105     /* Moldavian                       */
#define SE_LANG_MR              106     /* Marathi (Devanagari script)     */
#define SE_LANG_MT              107     /* Maltese                         */
#define SE_LANG_MY              108     /* Burmese (Myanmar)               */
#define SE_LANG_NB              109     /* Norwegian Bokmal                */
#define SE_LANG_NDS             110     /* Low Saxon                       */
#define SE_LANG_NE              111     /* Nepali (Devanagari script)      */
#define SE_LANG_NL              112     /* Dutch                           */
#define SE_LANG_NN              113     /* Norwegian Nynorsk               */
#define SE_LANG_NO              114     /* Norwegian                       */
#define SE_LANG_NY              115     /* Chichewa                        */
#define SE_LANG_OC              116     /* Occitan                         */
#define SE_LANG_OM              117     /* Oromo or Galla                  */
#define SE_LANG_OR              118     /* Oriya                           */
#define SE_LANG_OS              119     /* Ossetic                         */
#define SE_LANG_PA              120     /* Punjabi (Gurumukhi script)      */
#define SE_LANG_PL              121     /* Polish                          */
#define SE_LANG_PS_AF           122     /* Pashto in Afghanistan           */
#define SE_LANG_PS_PK           123     /* Pashto in Pakistan              */
#define SE_LANG_PT              124     /* Portuguese                      */
#define SE_LANG_RM              125     /* Rhaeto-Romance                  */
#define SE_LANG_RO              126     /* Romanian                        */
#define SE_LANG_RU              127     /* Russian                         */
#define SE_LANG_SA              128     /* Sanskrit (Devanagari script)    */
#define SE_LANG_SAH             129     /* Yakut                           */
#define SE_LANG_SCO             130     /* Scots                           */
#define SE_LANG_SE              131     /* North Sami                      */
#define SE_LANG_SEL             132     /* Selkup (Ostyak-Samoyed)         */
#define SE_LANG_SH              133     /* Serbo-Croatian                  */
#define SE_LANG_SI              134     /* Sinhala (Sinhalese)             */
#define SE_LANG_SK              135     /* Slovak                          */
#define SE_LANG_SL              136     /* Slovenian                       */
#define SE_LANG_SM              137     /* Samoan                          */
#define SE_LANG_SMA             138     /* South Sami                      */
#define SE_LANG_SMJ             139     /* Lule Sami                       */
#define SE_LANG_SMN             140     /* Inari Sami                      */
#define SE_LANG_SMS             141     /* Skolt Sami                      */
#define SE_LANG_SO              142     /* Somali                          */
#define SE_LANG_SQ              143     /* Albanian                        */
#define SE_LANG_SR              144     /* Serbian                         */
#define SE_LANG_SV              145     /* Swedish                         */
#define SE_LANG_SW              146     /* Swahili                         */
#define SE_LANG_SYR             147     /* Syriac                          */
#define SE_LANG_TA              148     /* Tamil                           */
#define SE_LANG_TE              149     /* Telugu                          */
#define SE_LANG_TG              150     /* Tajik                           */
#define SE_LANG_TH              151     /* Thai                            */
#define SE_LANG_TI_ER           152     /* Eritrean Tigrinya               */
#define SE_LANG_TI_ET           153     /* Ethiopian Tigrinya              */
#define SE_LANG_TIG             154     /* Tigre                           */
#define SE_LANG_TK              155     /* Turkmen                         */
#define SE_LANG_TL              156     /* Tagalog                         */
#define SE_LANG_TN              157     /* Tswana                          */
#define SE_LANG_TO              158     /* Tonga                           */
#define SE_LANG_TR              159     /* Turkish                         */
#define SE_LANG_TS              160     /* Tsonga                          */
#define SE_LANG_TT              161     /* Tatar                           */
#define SE_LANG_TW              162     /* Twi                             */
#define SE_LANG_TYV             163     /* Tuvinian                        */
#define SE_LANG_UG              164     /* Uighur                          */
#define SE_LANG_UK              165     /* Ukrainian                       */
#define SE_LANG_UR              166     /* Urdu                            */
#define SE_LANG_UZ              167     /* Uzbek                           */
#define SE_LANG_VEN             168     /* Venda                           */
#define SE_LANG_VI              169     /* Vietnamese                      */
#define SE_LANG_VO              170     /* Volapuk                         */
#define SE_LANG_VOT             171     /* Votic                           */
#define SE_LANG_WA              172     /* Walloon                         */
#define SE_LANG_WEN             173     /* Sorbian                         */
#define SE_LANG_WO              174     /* Wolof                           */
#define SE_LANG_XH              175     /* Xhosa                           */
#define SE_LANG_YAP             176     /* Yapese                          */
#define SE_LANG_YI              177     /* Yiddish                         */
#define SE_LANG_YO              178     /* Yoruba                          */
#define SE_LANG_ZH_CN           179     /* Chinese (simplified)            */
#define SE_LANG_ZH_HK           180     /* Chinese (Hong Kong)             */
#define SE_LANG_ZH_MO           181     /* Chinese (Macau)                 */
#define SE_LANG_ZH_SG           182     /* Chinese (Singapore)             */
#define SE_LANG_ZH_TW           183     /* Chinese (traditional)           */
#define SE_LANG_ZU              184     /* Zulu                            */

#ifdef __cplusplus
}
#endif

#endif /* SCRIPTEASY_H */
