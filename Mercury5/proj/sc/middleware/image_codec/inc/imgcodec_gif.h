#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

/****************************************************************************\
  \file     imgcodec_gif.h
--------------------------------------------------------------------------
  \brief    functions to implement the animation gif
  \date     Last update 2007/07/17
  \warning  This software is protected by Copyright and the information
            contained herein is confidential. Distribution, reproduction
            as well as exploitation and transmission of its contents is
            not allowed except if expressly permitted. Infringments
            result in damage claims.
            Copyright : Morning Star 2007/07 ~ 2011/07

Historical :

  The original software decoder is from MSF, they implement the decoder
in MMK and the image decoder is tied with the display system tightly.
To modulize each system component and merge the hardware decoder, in our new design,
we will isolate the image decoder to be a system module.
  It supports standard bitmap, gif, png, jpeg and wavcom specific bmp format.
-----------------------------------------------------------------------------
    Date  | Author  | Err  |  Modification
----------+---------+------+-----------------------------------------------
 17.07.07 | Alex    |      | Modify to support background color
----------+---------+------+-----------------------------------------------
\****************************************************************************/
#ifndef _IMGCODEC_GIF_H_
#define _IMGCODEC_GIF_H_

#include "imgcodec_common.h"

#define	MAX_LZW_BITS	12	/* maximum LZW code size */
#define LZW_TABLE_SIZE	(1<<MAX_LZW_BITS) /* # of possible LZW symbols */

//=========================================================
// This section is for packed byte in each extension
#define GIF_HEADER_COLORTAB_EXIST           0x80
#define GIF_HEADER_COLOR_RESOLUTION         0x70
#define GIF_HEADER_SORT_FLAG                0x08
#define GIF_HEADER_COLOR_TABLE_SIZE         0x07

#define GIF_IMGDESC_LOCAL_PALETTE_EXIST     0x80
#define GIF_IMGDESC_INTERLACED_FLAG         0x40
#define GIF_IMGDESC_SORT_FLAG               0x20
#define GIF_IMGDESC_PALETTE_SIZE            0x07

#define GIF_GCEXT_DISPOSAT_MASK             0x1C
#define GIF_GCEXT_INPUT_MASK                0x02
#define GIF_GCEXT_TRANPARENT_MASK           0x01

#define GIF_GCEXT_DISPOSAT_SHIFT            2
#define GIF_GCEXT_INPUT_SHIFT               1


#ifdef __ARMCC_VERSION
#define RVCT_PACKED __packed
#define GNU_PACKED
#elif defined __GNUC__
#define RVCT_PACKED
#define GNU_PACKED __attribute__((packed))
#elif defined _MSC_VER
#define RVCT_PACKED
#define GNU_PACKED
#endif

//=========================================================
// This section defines necessary structures
#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

typedef RVCT_PACKED struct _st_gif_identifier_
{
    u8      Introducer;
    u8      Label;
}GNU_PACKED CODECGIF_IDENTIFIER,*PCODECGIF_IDENTIFIER;

typedef RVCT_PACKED struct _st_gif_graphic_control_extension_
{
    u8      size;
    u8      Packed;
    u16     DelayTime;
    u8      TransparentIndex;
    u8      Terminator;
}GNU_PACKED CODECGIF_GCEXT,*PCODECGIF_GCEXT;

typedef RVCT_PACKED struct _st_gif_app_extension_
{
    u8      size;
    u8      Identifier[8];
    u8      Authentication[3];
}GNU_PACKED CODECGIF_APPEXT,*PCODECGIF_APPEXT;

typedef struct _st_gif_palette_
{
    u8      r;
    u8      g;
    u8      b;
}GIF_PALETTE,*PGIF_PALETTE;


//=========================================================
// Be carefule here!!
// sizeof() will return this structrue size as 14
// Because we use u16 in this structure, system will force to allocate
// 2-bytes- aligned size for it!
// Remember to decrease the returned value !!
typedef RVCT_PACKED struct _st_img_gif_header_
{
    u8              Signature[3];
    u8              Version[3];
    u16             width;
    u16             height;
    u8              PackedField;
    u8              BKColorIndex;
    u8              Aspecttatio;
}GNU_PACKED CODECGIF_HEADER,*PCODECGIF_HEADER;

//=========================================================
// Be carefule here!!
// sizeof() will return this structrue size as 14
// Because we use u16 in this structure, system will force to allocate
// 2-bytes- aligned size for it!
// Remember to decrease the returned value !!
typedef RVCT_PACKED struct _st_gif_plain_text_extension_
{
    u8      size;
    u16     left;
    u16     top;
    u16     width;
    u16     height;
    u8      cellwidth;
    u8      cellheight;
    u8      FGColor;
    u8      BKColor;
}GNU_PACKED CODECGIF_TEXTEXT,*PCODECGIF_TEXTEXT;

typedef RVCT_PACKED struct _st_gif_image_descriptor_
{
    u8      Separator;
    u16     left;
    u16     top;
    u16     width;
    u16     height;
    u8      packed;
}GNU_PACKED CODECGIF_IMGDESC,*PCODECGIF_IMGDESC;

typedef RVCT_PACKED struct _st_gif_picture_unit_
{
    u16     left;   // X coordination of top-left corner
    u16     top;    // Y coordination of top-left corner
    u16     width;  // width of the picture unit
    u16     height; // height of the picture unit
    u8      interlaced;
    u8      sort;
    u8      *palette;
    u16     palettesize;
}GNU_PACKED CODECGIF_PICUNIT, *PCODECGIF_PICUNIT;

typedef struct _st_gif_control_unit_
{
    u8      transparent;    // Tranparency index is given or not
    u8      colorkeyindex;  // The index of the transparent color
    u8      disposal;       // Disposal Method
    u8      userinput;      // User input is expected
    u32     delaytime;      // # of 1/100 sec to wait until next process after the graph is rendered.
}CODECGIF_CTRLUNIT, *PCODECGIF_CTRLUNIT;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

typedef struct _st_gif_decoder_context_
{
    u8  *GlobalPalette;         // GIF colormap (converted to my format)
    u8  *LocalPalette;
    u8  *ActivePalette;         // GIF colormap (converted to my format)
    u16  GlobalPaletteSize;
    u16  LocalPaletteSize;
    u16  ActivePaletteSize;

    // State for LZW_FetchCode and LZW_GetByte
    u8   code_buf[256+4];       // current input data block
    u32  last_byte;             // # of bytes in code_buf
    u32  last_bit;              // # of bits in code_buf
    u32  cur_bit;               // next bit index to read
    bool out_of_blocks;         // TRUE if hit terminator data block

    u16  input_code_size;	    // codesize given in GIF file
    u16  clear_code,end_code;   // values for Clear and End codes

    u16  code_size;             // current actual code size
    u16  code_mask;             // current code mask according to code_size
    u16  limit_code;            // 2^code_size
    u16  max_code;              // first unused code value
    bool first_time;            // flags first call to LZW_GetByte

    // Private state for LZW_GetByte
    u16  oldcode;               // previous LZW symbol
    u16  firstcode;             // first byte of oldcode's expansion

    // LZW symbol table and expansion stack
    u16 *symbol_head;           // => table of prefix symbols
    u8  *symbol_tail;           // => table of suffix bytes
    u8  *symbol_stack;          // => stack for symbol expansions
    u8  *sp;                    // stack pointer


    CODECGIF_CTRLUNIT   control;
    CODECGIF_CTRLUNIT   prevControl;
    u8                  prevDisposal;
    u8                  hasNextFrame;
    u8                  is_interlaced;
    u16                 left;   // input image left
    u16                 top;    // input image top
    u16                 width;  // input image left
    u16                 height; // input image top
    u16                 prevLeft;   // input image left
    u16                 prevTop;    // input image top
    u16                 prevWidth;  // input image left
    u16                 prevHeight; // input image top
    u16                 uCurrFrame;
    u32                 posDataStart;

    u8   bkR;
    u8   bkG;
    u8   bkB;

    void *pRender;
    ImgFSFunc_st *pFuncFS;
} CODECGIF_SOURCE, *PCODECGIF_SOURCE;


IMGCODEC_FORMAT CodecGIF_CheckGIF(u8* pBuff);
void CodecGIF_Loader(PIMGCODEC_CONTEXT context_op_p);
s32  CodecGIF_GetInfoEx(ImgFSFunc_st *pFfuncFS, Image_Info_t *pInfo);

#endif//_IMGCODEC_GIF_H_
#endif

