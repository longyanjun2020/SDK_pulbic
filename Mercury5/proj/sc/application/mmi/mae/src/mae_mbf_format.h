/**
 * \file    mae_mbf_format.h
 * \brief   The document describes the definition of mbf font
 * \author  steve.lee@mstarsemi.com
 * @version $Id: mae_mbf_format.h 291 2009-02-27 13:08:01Z kenny.wu $
 */
#ifndef __MAE_MBF_FORMAT_H__
#define __MAE_MBF_FORMAT_H__

#define MBF_CAPABILITY_WIDTH_MASK         0x0007  // 3 bits for width type in MBF

#define MBF_CAPABILITY_FIXED_WIDTH        0x0000
#define MBF_CAPABILITY_VARIANT_WIDTH_V1   0x0001
//#define MBF_CAPABILITY_VARIANT_WIDTH_V2   0x0002

#define MBF_SIZE_ID                  4
#define MBF_SIZE_FILESIZE            4
#define MBF_SIZE_VERSION             1
#define MBF_SIZE_CAPABILITY          2
#define MBF_SIZE_DEFAULT_CODE        2
#define MBF_SIZE_GLYPH_COUNT         2
#define MBF_SIZE_ASCENT              2
#define MBF_SIZE_DESCENT             2
#define MBF_SIZE_CODE_LIST_COUNT     2
#define MBF_SIZE_BMP_WIDTH           2
#define MBF_SIZE_BMP_HEIGHT          2

// for variant width font version 1
#define MBF_SIZE_BMP_ROWCNT_COUNT    2
// for fixed width font version 1

#define MBF_SIZE_CODE_LIST_SIZE      4
#define MBF_SIZE_BMP_SIZE            4

// for variant width font version 1
#define MBF_SIZE_BMP_ROWCNT_SIZE     4
#define MBF_SIZE_XCORD_ARY_SIZE      4
#define MBF_SIZE_XOFFSET_ARY_SIZE    4
// ~for variant width font version 1

// for fixed width font version 1
#define MBF_SIZE_GLYPH_PER_ROW       2
#define MBF_SIZE_GLYPH_PER_COL       2
#define MBF_SIZE_GLYPH_WIDTH         1
// for fixed width font version 1

#define MBF_SIZE_HEADER_SIZE        48


#define MBF_OFFSET_ID                0
#define MBF_OFFSET_FILESIZE          4
#define MBF_OFFSET_VERSION           8
#define MBF_OFFSET_CAPABILITY       10
#define MBF_OFFSET_DEFAULT_CODE     12
#define MBF_OFFSET_GLYPH_COUNT      14
#define MBF_OFFSET_ASCENT           16
#define MBF_OFFSET_DESCENT          18
#define MBF_OFFSET_CODE_LIST_COUNT  20
#define MBF_OFFSET_BMP_WIDTH        22
#define MBF_OFFSET_BMP_HEIGHT       24

// for variant width font version 1
#define MBF_OFFSET_BMP_ROWCNT_COUNT 26
// ~for variant width font version 1

#define MBF_OFFSET_CODE_LIST_SIZE   28
#define MBF_OFFSET_BMP_SIZE         32

// for variant width font version 1
#define MBF_OFFSET_BMP_ROWCNT_SIZE  36
#define MBF_OFFSET_XCORD_ARY_SIZE   40
#define MBF_OFFSET_XOFFSET_ARY_SIZE 44
// ~for variant width font version

// for fixed width font version 1
#define MBF_OFFSET_GLYPH_PER_ROW    36
#define MBF_OFFSET_GLYPH_PER_COL    38
#define MBF_OFFSET_GLYPH_WIDTH      40
// for fixed width font version 1

//for compressed mbf
#define MBF_COMP_SIZE_TAG_SIZE 4
#define MBF_COMP_SIZE_SPLIT_PER_ROW_SIZE 1
#define MBF_COMP_SIZE_TOTAL_SPLIT_SEGMENT_SIZE 2
#define MBF_COMP_SIZE_ENCODE_BYTE_SIZE 2
#define MBF_COMP_NULL_SEGMENT 0xFFFF
//for compressed mbf

#ifndef MBF_GEN_TOOL
typedef struct
{
	u16  nCode;  //< Start code
	u16  nCount; //< Continuous code count
}_CodeItem_t;

typedef struct
{
	u8   nWidth; //< Width of glyph
	u8   nCount; //< Count of continuous glyphs with the same width
}_WidItem_t;
#endif /* MBF_GEN_TOOL */

#endif /* __MAE_MBF_FORMAT_H__ */
