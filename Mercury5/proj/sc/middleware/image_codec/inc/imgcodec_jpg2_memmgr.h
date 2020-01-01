#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

/****************************************************************************/
/*  File    :           imgcodec_memmgr.h                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   :        Const and Structures used by GIF/JPEG/BMP decoders     */
/*                                                                          */
/****************************************************************************/

#ifndef _IMGCODEC_JPG2_MEMMGR_H_
#define _IMGCODEC_JPG2_MEMMGR_H_

#include "imgcodec_common.h"
#define jpg_malloc img_malloc
#define jpg_free   img_free
#define jpg_strcpy img_strcpy
#define jpg_strlen img_strlen
#define jpg_memcmp img_memcmp
#define jpg_memcpy img_memcpy
#define jpg_memset img_memset

#define jpg_trace1 img_trace1
#define jpg_trace2 img_trace2
#define jpg_error1 img_error1
#define jpg_error2 img_error2

#define EMS_OFFSET   2
#define WBMP_OFFSET  4


/*
* Define BITS_IN_JSAMPLE as either
*   8   for 8-bit sample values (the usual setting)
*   12  for 12-bit sample values
* Only 8 and 12 are legal data precisions for lossy JPEG according to the
* JPEG standard, and the IJG code does not support anything else.
* We do not support run-time selection of data precision.
*/

#define BITS_IN_JSAMPLE  8	/* use 8 or 12 */


/*
* Maximum number of components (color channels) allowed in JPEG image.
* To meet the letter of the JPEG spec, set this to 255.  However, darn
* few applications need more than 4 channels (maybe 5 for CMYK + alpha
* mask).  We recommend 10 as a reasonable compromise; use 4 if you are
* really short on memory.  (Each allowed component costs a hundred or so
* bytes of storage, whether actually used in an image or not.)
*/

#define MAX_COMPONENTS  3	/* maximum number of image components */


/*
* Basic data types.
* You may need to change these if you have a machine with unusual data
* type sizes; for example, "char" not 8 bits, "short" not 16 bits,
* or "long" not 32 bits.  We don't care whether "int" is 16 or 32 bits,
* but it had better be at least 16.
*/

/* Representation of a single sample (pixel element value).
* We frequently allocate large arrays of these, so it's important to keep
* them small.  But if you have memory to burn and access to char or short
* arrays is very slow on your hardware, you might want to change these.
*/

typedef unsigned char JSAMPLE;
#define GETJSAMPLE(value)  ((int) (value))

#define MAXJSAMPLE	255
#define CENTERJSAMPLE	128


/* Representation of a DCT frequency coefficient.
* This should be a signed value of at least 16 bits; "short" is usually OK.
* Again, we allocate large arrays of these, but you can change to int
* if you have memory to burn and "short" is really slow.
*/

typedef u32 JCOEF;

/* Compressed datastreams are represented as arrays of JOCTET.
* These must be EXACTLY 8 bits wide, at least once they are written to
* external storage.  Note that when using the stdio data source/destination
* managers, this is also the data type passed to fread/fwrite.
*/

typedef u8 JOCTET;
#define GETJOCTET(value)  (value)


typedef u8 UINT8;

/* UINT16 must hold at least the values 0..65535. */

typedef u16 UINT16;

/* INT16 must hold at least the values -32768..32767. */

typedef s16 INT16;

/* INT32 must hold at least signed 32-bit values. */

typedef s32 INT32;

/* Datatype used for image dimensions.  The JPEG standard only supports
* images up to 64K*64K due to 16-bit fields in SOF markers.  Therefore
* "unsigned int" is sufficient on all machines.  However, if you need to
* handle larger images and you don't mind deviating from the spec, you
* can change this datatype.
*/

//typedef u32 JDIMENSION;

#define JPEG_MAX_DIMENSION  65500L  /* a tad under 64K to prevent overflows */


/* This macro is used to declare a "method", that is, a function pointer.
* We want to supply prototype parameters if the compiler can cope.
* Note that the arglist parameter must be parenthesized!
* Again, you can customize this if you need special linkage keywords.
*/

#define JMETHOD(type,methodname,arglist)  type (*methodname) ()


/*
* Ordering of RGB data in scanlines passed to or from the application.
* If your application wants to deal with data in the order B,G,R, just
* change these macros.  You can also deal with formats such as R,G,B,X
* (one extra byte per pixel) by changing RGB_PIXELSIZE.  Note that changing
* the offsets will also change the order in which colormap data is organized.
* RESTRICTIONS:
* 1. The sample applications cjpeg,djpeg do NOT support modified RGB formats.
* 2. These macros only affect RGB<=>YCbCr color conversion, so they are not
*    useful if you are using JPEG color spaces other than YCbCr or grayscale.
* 3. The color quantizer modules will not behave desirably if RGB_PIXELSIZE
*    is not 3 (they don't understand about dummy color components!).  So you
*    can't use color quantization if you change that value.
*/

#define RGB_RED	        0// Offset of Red in an RGB scanline element
#define RGB_GREEN       1// Offset of Green
#define RGB_BLUE        2// Offset of Blue
#define RGB_PIXELSIZE   3// JSAMPLEs per RGB scanline element


/* On some machines (notably 68000 series) "int" is 32 bits, but multiplying
* two 16-bit shorts is faster than multiplying two ints.  Define MULTIPLIER
* as short on such a machine.  MULTIPLIER must be at least 16 bits wide.
*/

#ifndef MULTIPLIER
#define MULTIPLIER  int		/* type for fastest integer multiply */
#endif


#define size_t unsigned int
#define MEMZERO(target,size)	jpg_memset((void *)(target), 0, (size_t)(size))
#define MEMCOPY(dest,src,size)	jpg_memcpy((void *)(dest), (const void *)(src), (size_t)(size))



#define SIZEOF(object)	((size_t) sizeof(object))




#define JPEG_LIB_VERSION  62	/* Version 6b */


/* Various constants determining the sizes of things.*/
/* All of these are specified by the JPEG standard, so don't change them */
/* if you want to be compatible.*/


#define DCTSIZE		    8	/* The basic DCT block is 8x8 samples */
#define DCTSIZE2	    64	/* DCTSIZE squared; # of elements in a block */
#define NUM_QUANT_TBLS      4	/* Quantization tables are numbered 0..3 */
#define NUM_HUFF_TBLS       4	/* Huffman tables are numbered 0..3 */
#define NUM_ARITH_TBLS      16	/* Arith-coding tables are numbered 0..15 */
#define MAX_COMPS_IN_SCAN   4	/* JPEG limit on # of components in one scan */
#define MAX_SAMP_FACTOR     4	/* JPEG limit on sampling factors */
#ifndef D_MAX_BLOCKS_IN_MCU
#define D_MAX_BLOCKS_IN_MCU   10 /* decompressor's limit on blocks per MCU */
#endif


/* Data structures for images (arrays of samples and of DCT coefficients).	*/
/* On 80x86 machines, the image arrays are too big for near pointers,		*/
/* but the pointer arrays can fit in near memory.							      */


typedef JSAMPLE *JSAMPROW;	/* ptr to one image row of pixel samples. */
typedef JSAMPROW *JSAMPARRAY;	/* ptr to some rows (a 2-D sample array) */
typedef JSAMPARRAY *JSAMPIMAGE;	/* a 3-D sample array: top index is color */

typedef JCOEF JBLOCK[DCTSIZE2];	/* one block of coefficients */
typedef JBLOCK  *JBLOCKROW;	/* pointer to one row of coefficient blocks */
typedef JBLOCKROW *JBLOCKARRAY;		/* a 2-D array of coefficient blocks */
typedef JBLOCKARRAY *JBLOCKIMAGE;	/* a 3-D array of coefficient blocks */

typedef JCOEF  *JCOEFPTR;	/* useful in a couple of places */


/* Types for JPEG compression parameters and working tables. */


/* DCT coefficient quantization tables. */

typedef struct {
    u16 quantval[DCTSIZE2];

} JQUANT_TBL;


/* Huffman coding tables. */

typedef struct {
    /* These two fields directly represent the contents of a JPEG DHT marker */
    u8 bits[17];		/* bits[k] = # of symbols with codes of */
    /* length k bits; bits[0] is unused */
    u8 huffval[256];		/* The symbols, in order of incr code length */


} JHUFF_TBL;


/* Basic info about one component (color channel). */

typedef struct {
    /* These values are fixed over the whole image. */
    /* For compression, they must be supplied by parameter setup; */
    /* for decompression, they are read from the SOF marker. */
    int component_id;		/* identifier for this component (0..255) */
    int component_index;		/* its index in SOF or cinfo->comp_info[] */
    int h_samp_factor;		/* horizontal sampling factor (1..4) */
    int v_samp_factor;		/* vertical sampling factor (1..4) */
    int quant_tbl_no;		/* quantization table selector (0..3) */
    /* These values may vary between scans. */
    /* For compression, they must be supplied by parameter setup; */
    /* for decompression, they are read from the SOS marker. */
    /* The decompressor output side may not use these variables. */
    int dc_tbl_no;		/* DC entropy table selector (0..3) */
    int ac_tbl_no;		/* AC entropy table selector (0..3) */

    /* Remaining fields should be treated as private by applications. */

    /* These values are computed during compression or decompression startup: */
    /* Component's size in DCT blocks.
    * Any dummy blocks added to complete an MCU are not counted; therefore
    * these values do not depend on whether a scan is interleaved or not.
    */
    u32 width_in_blocks;
    u32 height_in_blocks;
    /* Size of a DCT block in samples.  Always DCTSIZE for compression.
    * For decompression this is the size of the output from one DCT block,
    * reflecting any scaling we choose to apply during the IDCT step.
    * Values of 1,2,4,8 are likely to be supported.  Note that different
    * components may receive different IDCT scalings.
    */
    int DCT_scaled_size;
    /* The downsampled dimensions are the component's actual, unpadded number
    * of samples at the main buffer (preprocessing/compression interface), thus
    * downsampled_width = ceil(image_width * Hi/Hmax)
    * and similarly for height.  For decompression, IDCT scaling is included, so
    * downsampled_width = ceil(image_width * Hi/Hmax * DCT_scaled_size/DCTSIZE)
    */
    u32 downsampled_width;	 /* actual width in samples */
    u32 downsampled_height; /* actual height in samples */
    /* This flag is used only for decompression.  In cases where some of the
    * components will be ignored (eg grayscale output from YCbCr image),
    * we can skip most computations for the unused components.
    */
    bool component_needed;	/* do we need the value of this component? */

    /* These values are computed before starting a scan of the component. */
    /* The decompressor output side may not use these variables. */
    int MCU_width;		/* number of blocks per MCU, horizontally */
    int MCU_height;		/* number of blocks per MCU, vertically */
    int MCU_blocks;		/* MCU_width * MCU_height */
    int MCU_sample_width;		/* MCU width in samples, MCU_width*DCT_scaled_size */
    int last_col_width;		/* # of non-dummy blocks across in last MCU */
    int last_row_height;		/* # of non-dummy blocks down in last MCU */

    /* Saved quantization table for component; NULL if none yet saved.
    * See jdinput.c comments about the need for this information.
    * This field is currently used only for decompression.
    */
    JQUANT_TBL * quant_table;

    /* Private per-component storage for DCT or IDCT subsystem. */
    void * dct_table;
} jpeg_component_info;


/* The decompressor can save APPn and COM markers in a list of these: */

typedef struct jpeg_marker_struct * jpeg_saved_marker_ptr;

struct jpeg_marker_struct {
    jpeg_saved_marker_ptr next;	/* next in list, or NULL */
    u8 marker;			/* marker code: JPEG_COM, or JPEG_APP0+n */
    unsigned int original_length;	/* # bytes of data in the file */
    unsigned int data_length;	/* # bytes of data saved at data[] */
    JOCTET  * data;		/* the data contained in the marker */
    /* the marker length word is not counted in data_length or original_length */
};

/* Known color spaces. */

typedef enum {
    JCS_UNKNOWN,		/* error/unspecified */
    JCS_GRAYSCALE,		/* monochrome */
    JCS_RGB,		/* red/green/blue */
    JCS_YCbCr,		/* Y/Cb/Cr (also known as YUV) */
    JCS_CMYK,		/* C/M/Y/K */
    JCS_YCCK		/* Y/Cb/Cr/K */
} J_COLOR_SPACE;

/* DCT/IDCT algorithm options. */

typedef enum {
    JDCT_IFAST		/* faster, less accurate integer method  the only one implemented*/
} J_DCT_METHOD;


/* Common fields between JPEG compression and decompression master structs. */

#define jpeg_common_fields \
struct jpeg_memory_mgr * mem	/* Memory manager module */\

/* Routines that are to be used by both halves of the library are declared
* to receive a pointer to this structure.  There are no actual instances of
* jpeg_common_struct, only of jpeg_compress_struct and jpeg_decompress_struct.
*/
struct jpeg_common_struct {
    jpeg_common_fields;		/* Fields common to both master struct types */

};

typedef struct jpeg_common_struct * j_common_ptr;
typedef struct jpeg_compress_struct * j_compress_ptr;
typedef struct jpeg_decompress_struct * j_decompress_ptr;


/* Master record for a decompression instance */

struct jpeg_decompress_struct {
    jpeg_common_fields;		/* Fields shared with jpeg_compress_struct */
    bool isGetDc;
    u16 y1;
    u16 y2;
    u16 x1;
    u16 x2;


    /* Source of compressed data */
    struct jpeg_source_mgr * src;

    /* Basic description of image --- filled in by jpeg_read_header(). */
    /* Application may inspect these values to decide how to process image. */

    u32 image_width;	/* nominal image width (from SOF marker) */
    u32 image_height;	/* nominal image height */
    int num_components;		/* # of color components in JPEG image */
    J_COLOR_SPACE jpeg_color_space; /* colorspace of JPEG image */

    /* Decompression processing parameters --- these fields must be set before
    * calling jpeg_start_decompress().  Note that jpeg_read_header() initializes
    * them to default values.
    */

    J_COLOR_SPACE out_color_space; /* colorspace for output */


    J_DCT_METHOD dct_method;	/* IDCT algorithm selector */
    bool do_fancy_upsampling;	/* TRUE=apply fancy upsampling */

    /* these are significant only in buffered-image mode: */

    /* Description of actual output image that will be returned to application.
    * These fields are computed by jpeg_start_decompress().
    * You can also use jpeg_calc_output_dimensions() to determine these values
    * in advance of calling jpeg_start_decompress().
    */

    u32 output_width;	/* scaled image width */
    u32 output_height;	/* scaled image height */
    int out_color_components;	/* # of color components in out_color_space */
    int output_components;	/* # of color components returned */
    /* output_components is 1 (a colormap index) when quantizing colors;
    * otherwise it equals out_color_components.
    */
    int rec_outbuf_height;	/* min recommended height of scanline buffer */
    /* If the buffer passed to jpeg_read_scanlines() is less than this many rows
    * high, space and time will be wasted due to unnecessary data copying.
    * Usually rec_outbuf_height will be 1 or 2, at most 4.
    */

    /* When quantizing colors, the output colormap is described by these fields.
    * The application can supply a colormap by setting colormap non-NULL before
    * calling jpeg_start_decompress; otherwise a colormap is created during
    * jpeg_start_decompress or jpeg_start_output.
    * The map has out_color_components rows and actual_number_of_colors columns.
    */


    /* State variables: these variables indicate the progress of decompression.
    * The application may examine these but must not modify them.
    */

    /* Row index of next scanline to be read from jpeg_read_scanlines().
    * Application may use this to control its processing loop, e.g.,
    * "while (output_scanline < output_height)".
    */
    u32 output_scanline;	/* 0 .. output_height-1  */

    /* Current input scan number and number of iMCU rows completed in scan.
    * These indicate the progress of the decompressor input side.
    */
    int input_scan_number;	/* Number of SOS markers seen so far */
    u32 input_iMCU_row;	/* Number of iMCU rows completed */

    /* The "output scan number" is the notional scan being displayed by the
    * output side.  The decompressor will not allow output scan/row number
    * to get ahead of input scan/row, but it can fall arbitrarily far behind.
    */
    int output_scan_number;	/* Nominal scan number being displayed */
    u32 output_iMCU_row;	/* Number of iMCU rows read */

    /* Current progression status.  coef_bits[c][i] indicates the precision
    * with which component c's DCT coefficient i (in zigzag order) is known.
    * It is -1 when no data has yet been received, otherwise it is the point
    * transform (shift) value for the most recent scan of the coefficient
    * (thus, 0 at completion of the progression).
    * This pointer is NULL when reading a non-progressive file.
    */
    int (*coef_bits)[DCTSIZE2];	/* -1 or current Al value for each coef */

    /* Internal JPEG parameters --- the application usually need not look at
    * these fields.  Note that the decompressor output side may not use
    * any parameters that can change between scans.
    */

    /* Quantization and Huffman tables are carried forward across input
    * datastreams when processing abbreviated JPEG datastreams.
    */

    JQUANT_TBL * quant_tbl_ptrs[NUM_QUANT_TBLS];
    /* ptrs to coefficient quantization tables, or NULL if not defined */

    JHUFF_TBL * dc_huff_tbl_ptrs[NUM_HUFF_TBLS];
    JHUFF_TBL * ac_huff_tbl_ptrs[NUM_HUFF_TBLS];
    /* ptrs to Huffman coding tables, or NULL if not defined */

    /* These parameters are never carried across datastreams, since they
    * are given in SOF/SOS markers or defined to be reset by SOI.
    */

    int data_precision;		/* bits of precision in image data */

    jpeg_component_info * comp_info;
    /* comp_info[i] describes component that appears i'th in SOF */

    u32 restart_interval; /* MCUs per restart interval, or 0 for no restart */

    /* These fields record data obtained from optional markers recognized by
    * the JPEG library.
    */
    bool saw_JFIF_marker;	/* TRUE iff a JFIF APP0 marker was found */
    /* Data copied from JFIF marker; only valid if saw_JFIF_marker is TRUE: */
    u8 JFIF_major_version;	/* JFIF version number */
    u8 JFIF_minor_version;
    u8 density_unit;		/* JFIF code for pixel size units */
    u16 X_density;		/* Horizontal pixel density */
    u16 Y_density;		/* Vertical pixel density */
    bool saw_Adobe_marker;	/* TRUE iff an Adobe APP14 marker was found */
    u8 Adobe_transform;	/* Color transform code from Adobe marker */

    bool CCIR601_sampling;	/* TRUE=first samples are cosited */

    /* Aside from the specific data retained from APPn markers known to the
    * library, the uninterpreted contents of any or all APPn and COM markers
    * can be saved in a list for examination by the application.
    */
    jpeg_saved_marker_ptr marker_list; /* Head of list of saved markers */

    /* Remaining fields are known throughout decompressor, but generally
    * should not be touched by a surrounding application.
    */

    /*
    * These fields are computed during decompression startup
    */
    int max_h_samp_factor;	/* largest h_samp_factor */
    int max_v_samp_factor;	/* largest v_samp_factor */

    int min_DCT_scaled_size;	/* smallest DCT_scaled_size of any component */

    u32 total_iMCU_rows;	/* # of iMCU rows in image */
    /* The coefficient controller's input and output progress is measured in
    * units of "iMCU" (interleaved MCU) rows.  These are the same as MCU rows
    * in fully interleaved JPEG scans, but are used whether the scan is
    * interleaved or not.  We define an iMCU row as v_samp_factor DCT block
    * rows of each component.  Therefore, the IDCT output contains
    * v_samp_factor*DCT_scaled_size sample rows of a component per iMCU row.
    */

    JSAMPLE * sample_range_limit; /* table for fast range-limiting */

    /*
    * These fields are valid during any one scan.
    * They describe the components and MCUs actually appearing in the scan.
    * Note that the decompressor output side must not use these fields.
    */
    int comps_in_scan;		/* # of JPEG components in this scan */
    jpeg_component_info * cur_comp_info[MAX_COMPS_IN_SCAN];
    /* *cur_comp_info[i] describes component that appears i'th in SOS */

    u32 MCUs_per_row;	/* # of MCUs across the image */
    u32 MCU_rows_in_scan;	/* # of MCU rows in the image */

    int blocks_in_MCU;		/* # of DCT blocks per MCU */
    int MCU_membership[D_MAX_BLOCKS_IN_MCU];
    /* MCU_membership[i] is index in cur_comp_info of component owning */
    /* i'th block in an MCU */

    int Ss, Se, Ah, Al;		/* progressive JPEG parameters for scan */

    /* This field is shared between entropy decoder and marker parser.
    * It is either zero or the code of a JPEG marker that has been
    * read from the data source, but has not yet been processed.
    */
    int unread_marker;

    /*
    * Links to decompression subobjects (methods, private variables of modules)
    */
    struct jpeg_decomp_master * master;
    struct jpeg_d_main_controller * main;
    struct jpeg_d_coef_controller * coef;
    struct jpeg_d_post_controller * post;
    struct jpeg_input_controller * inputctl;
    struct jpeg_marker_reader *marker;
    struct jpeg_entropy_decoder * entropy;
    struct jpeg_inverse_dct * idct;
    struct jpeg_upsampler * upsample;
    struct jpeg_color_deconverter * cconvert;
};


struct jpeg_source_mgr {
    const JOCTET * next_input_byte; /* => next byte to read from buffer */
    size_t bytes_in_buffer;	/* # of bytes remaining in buffer */

};




/* Memory manager object.
* Allocates "small" objects (a few K total), "large" objects (tens of K),
* and "really big" objects (virtual arrays with backing store if needed).
* The memory manager does not allow individual objects to be freed; rather,
* each created object is assigned to a pool, and whole pools can be freed
* at once.  This is faster and more convenient than remembering exactly what
* to free, especially where malloc()/free() are not too speedy.
* NB: alloc routines never return NULL.  They exit to error_exit if not
* successful.
*/

#define JPOOL_PERMANENT	0	/* lasts until master record is destroyed */
#define JPOOL_IMAGE	1	/* lasts until done with image/datastream */
#define JPOOL_NUMPOOLS	2

struct jpeg_memory_mgr {
    /* Method pointers */

    /* Limit on memory allocation for this JPEG object.  (Note that this is
    * merely advisory, not a guaranteed maximum; it only affects the space
    * used for virtual-array buffers.)  May be changed by outer application
    * after creating the JPEG object.
    */

    /* Maximum allocation request accepted by alloc_large. */
    long max_alloc_chunk;
};


/* Routine signature for application-supplied marker processing methods.
* Need not pass marker code since it is stored in cinfo->unread_marker.
*/
typedef JMETHOD(bool, jpeg_marker_parser_method, (j_decompress_ptr cinfo));


/* Initialization of JPEG compression objects.
* jpeg_create_compress() and jpeg_create_decompress() are the exported
* names that applications should call.  These expand to calls on
* jpeg_CreateCompress and jpeg_CreateDecompress with additional information
* passed for version mismatch checking.
* NB: you must set up the error-manager BEFORE calling jpeg_create_xxx.
*/

#define jpeg_create_decompress(cinfo) \
    jpeg_CreateDecompress((cinfo), JPEG_LIB_VERSION, \
    (size_t) sizeof(struct jpeg_decompress_struct))
/* Return value is one of: */
#define JPEG_SUSPENDED		0 /* Suspended due to lack of input data */
#define JPEG_HEADER_OK		1 /* Found valid image datastream */
#define JPEG_HEADER_TABLES_ONLY	2 /* Found valid table-specs-only datastream */

/* Return value is one of: */
#define JPEG_REACHED_SOS	1 /* Reached start of new scan */
#define JPEG_REACHED_EOI	2 /* Reached end of image */
#define JPEG_ROW_COMPLETED	3 /* Completed one iMCU row */
#define JPEG_SCAN_COMPLETED	4 /* Completed last iMCU row of a scan */


/*
* Object interface for djpeg's output file encoding modules
*/

typedef struct djpeg_dest_struct * djpeg_dest_ptr;

struct djpeg_dest_struct {

    /* Output pixel-row buffer.  Created by module init or start_output.
    * Width is cinfo->output_width * cinfo->output_components;
    * height is buffer_height.
    */
    JSAMPARRAY buffer;
    u32 buffer_height;
};

/*
* The macro MAX_ALLOC_CHUNK designates the maximum number of bytes that may
* be requested in a single call to jpeg_get_large (and jpeg_get_small for that
* matter, but that case should never come into play).  This macro is needed
* to model the 64Kb-segment-size limit of far addressing on 80x86 machines.
* On those machines, we expect that jconfig.h will provide a proper value.
* On machines with 32-bit flat address spaces, any large constant may be used.
*
* NB: jmemmgr.c expects that MAX_ALLOC_CHUNK will be representable as type
* size_t and will be a multiple of sizeof(align_type).
*/

#ifndef MAX_ALLOC_CHUNK		/* may be overridden in jconfig.h */
#define MAX_ALLOC_CHUNK  1000000000L
#endif


/* Declarations for both compression & decompression */

typedef enum {			/* Operating modes for buffer controllers */
    JBUF_PASS_THRU,		/* Plain stripwise operation */
    /* Remaining modes require a full-image buffer to have been created */
    JBUF_SAVE_AND_PASS	/* Run both subobjects, save output */
} J_BUF_MODE;


/* Declarations for decompression modules */

/* Master control module */
struct jpeg_decomp_master {
    JMETHOD(void, prepare_for_output_pass, (j_decompress_ptr cinfo));
    JMETHOD(void, finish_output_pass, (j_decompress_ptr cinfo));

    /* State variables made visible to other modules */
    bool is_dummy_pass;	/* True during 1st pass for 2-pass quant */
};

/* Input control module */
struct jpeg_input_controller {
    JMETHOD(int, consume_input, (j_decompress_ptr cinfo));
    JMETHOD(void, reset_input_controller, (j_decompress_ptr cinfo));
    JMETHOD(bool, start_input_pass, (j_decompress_ptr cinfo));
    JMETHOD(void, finish_input_pass, (j_decompress_ptr cinfo));

    /* State variables made visible to other modules */
    bool has_multiple_scans;	/* True if file has multiple scans */
    bool eoi_reached;		/* True when EOI has been consumed */
};

/* Main buffer control (downsampled-data buffer) */
struct jpeg_d_main_controller {
    JMETHOD(void, start_pass, (j_decompress_ptr cinfo, J_BUF_MODE pass_mode));
    JMETHOD(void, process_data, (j_decompress_ptr cinfo,
        JSAMPARRAY output_buf, u32 *out_row_ctr,
        u32 out_rows_avail));
};

/* Coefficient buffer control */
struct jpeg_d_coef_controller {
    JMETHOD(void, start_input_pass, (j_decompress_ptr cinfo));
    JMETHOD(int, consume_data, (j_decompress_ptr cinfo));
    JMETHOD(void, start_output_pass, (j_decompress_ptr cinfo));
    JMETHOD(int, decompress_data, (j_decompress_ptr cinfo,
        JSAMPIMAGE output_buf, bool));

};

/* Decompression postprocessing (color quantization buffer control) */
struct jpeg_d_post_controller {
    JMETHOD(void, start_pass, (j_decompress_ptr cinfo, J_BUF_MODE pass_mode));
    JMETHOD(void, post_process_data, (j_decompress_ptr cinfo,
        JSAMPIMAGE input_buf,
        u32 *in_row_group_ctr,
        u32 in_row_groups_avail,
        JSAMPARRAY output_buf,
        u32 *out_row_ctr,
        u32 out_rows_avail));
};

/* Marker reading & parsing */
struct jpeg_marker_reader {
    /* State of marker reader --- nominally internal, but applications
    * supplying COM or APPn handlers might like to know the state.
    */
    bool saw_SOI;		/* found SOI? */
    bool saw_SOF;		/* found SOF? */
    int next_restart_num;		/* next restart number expected (0-7) */
    unsigned int discarded_bytes;	/* # of bytes skipped looking for a marker */
};

/* Entropy decoding */
struct jpeg_entropy_decoder {
    JMETHOD(bool, start_pass, (j_decompress_ptr cinfo));
    JMETHOD(bool, decode_mcu, (j_decompress_ptr cinfo,
        JBLOCKROW *MCU_data));

    /* This is here to share code between baseline and progressive decoders; */
    /* other modules probably should not use it */
    bool insufficient_data;	/* set TRUE after emitting warning */
};

/* Inverse DCT (also performs dequantization) */
typedef JMETHOD(void, inverse_DCT_method_ptr,
                (j_decompress_ptr cinfo, jpeg_component_info * compptr,
                JCOEFPTR coef_block,
                JSAMPARRAY output_buf, u32 output_col));

struct jpeg_inverse_dct {
    JMETHOD(void, start_pass, (j_decompress_ptr cinfo));
    /* It is useful to allow each component to have a separate IDCT method. */
    inverse_DCT_method_ptr inverse_DCT[MAX_COMPONENTS];
};

/* Upsampling (note that upsampler must also call color converter) */
struct jpeg_upsampler {
    JMETHOD(void, start_pass, (j_decompress_ptr cinfo));
    JMETHOD(void, upsample, (j_decompress_ptr cinfo,
        JSAMPIMAGE input_buf,
        u32 *in_row_group_ctr,
        u32 in_row_groups_avail,
        JSAMPARRAY output_buf,
        u32 *out_row_ctr,
        u32 out_rows_avail));

    bool need_context_rows;	/* TRUE if need rows above & below */
};

/* Colorspace conversion */
struct jpeg_color_deconverter {
    JMETHOD(void, start_pass, (j_decompress_ptr cinfo));
    JMETHOD(void, color_convert, (j_decompress_ptr cinfo,
        JSAMPIMAGE input_buf, u32 input_row,
        JSAMPARRAY output_buf, int num_rows));
};

/* Color quantization or color precision reduction */
struct jpeg_color_quantizer {
    JMETHOD(void, start_pass, (j_decompress_ptr cinfo, bool is_pre_scan));
    JMETHOD(void, color_quantize, (j_decompress_ptr cinfo,
        JSAMPARRAY input_buf, JSAMPARRAY output_buf,
        int num_rows));
    JMETHOD(void, finish_pass, (j_decompress_ptr cinfo));
    JMETHOD(void, new_color_map, (j_decompress_ptr cinfo));
};


/* Miscellaneous useful macros */

#undef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#undef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))


/* We assume that right shift corresponds to signed division by 2 with
* rounding towards minus infinity.  This is correct for typical "arithmetic
* shift" instructions that shift in copies of the sign bit.  But some
* C compilers implement >> with an unsigned shift.  For these machines you
* must define RIGHT_SHIFT_IS_UNSIGNED.
* RIGHT_SHIFT provides a proper signed right shift of an INT32 quantity.
* It is only applied with constant shift counts.  SHIFT_TEMPS must be
* included in the variables of any routine using RIGHT_SHIFT.
*/

#ifdef RIGHT_SHIFT_IS_UNSIGNED
#define SHIFT_TEMPS	INT32 shift_temp;
#define RIGHT_SHIFT(x,shft)  \
    ((shift_temp = (x)) < 0 ? \
    (shift_temp >> (shft)) | ((~((INT32) 0)) << (32-(shft))) : \
    (shift_temp >> (shft)))
#else
#define SHIFT_TEMPS
#define RIGHT_SHIFT(x,shft)	((x) >> (shft))
#endif



/* Macros to simplify using the error and trace message stuff */
/* The first parameter is either type of cinfo pointer */

/* Fatal errors (print message and exit) */
#define ERREXIT(message)                 vm_dbgError(IMGCODEC_LV2, message)


#define MAKESTMT(stuff)		do { stuff } while (0)

/* Nonfatal errors (we can keep going, but the data is probably corrupt) */
#define WARNMS(message)  vm_dbgTrace(IMGCODEC_LV2, message)


/* Informational/debugging messages */
#define TRACEMS(cinfo,lvl,code) vm_dbgTrace(IMGCODEC_LV2, "(JPG)TRACEMS")



/* Derived data constructed for each Huffman table */

#define HUFF_LOOKAHEAD	8	/* # of bits of lookahead */

typedef struct {
    /* Basic tables: (element [0] of each array is unused) */
    INT32 maxcode[18];		/* largest code of length k (-1 if none) */
    /* (maxcode[17] is a sentinel to ensure jpeg_huff_decode terminates) */
    INT32 valoffset[17];		/* huffval[] offset for codes of length k */
    /* valoffset[k] = huffval[] index of 1st symbol of code length k, less
    * the smallest code of length k; so given a code of length k, the
    * corresponding symbol is huffval[code + valoffset[k]]
    */

    /* Link to public Huffman table (needed only in jpeg_huff_decode) */
    JHUFF_TBL *pub;

    /* Lookahead tables: indexed by the next HUFF_LOOKAHEAD bits of
    * the input data stream.  If the next Huffman code is no more
    * than HUFF_LOOKAHEAD bits long, we can obtain its length and
    * the corresponding symbol directly from these tables.
    */
    int look_nbits[1<<HUFF_LOOKAHEAD]; /* # bits, or 0 if too long */
    UINT8 look_sym[1<<HUFF_LOOKAHEAD]; /* symbol, or unused */
} d_derived_tbl;


/*
* Fetching the next N bits from the input stream is a time-critical operation
* for the Huffman decoders.  We implement it with a combination of inline
* macros and out-of-line subroutines.  Note that N (the number of bits
* demanded at one time) never exceeds 15 for JPEG use.
*
* We read source bytes into get_buffer and dole out bits as needed.
* If get_buffer already contains enough bits, they are fetched in-line
* by the macros CHECK_BIT_BUFFER and GET_BITS.  When there aren't enough
* bits, jpeg_fill_bit_buffer is called; it will attempt to fill get_buffer
* as full as possible (not just to the number of bits needed; this
* prefetching reduces the overhead cost of calling jpeg_fill_bit_buffer).
* Note that jpeg_fill_bit_buffer may return FALSE to indicate suspension.
* On TRUE return, jpeg_fill_bit_buffer guarantees that get_buffer contains
* at least the requested number of bits --- dummy zeroes are inserted if
* necessary.
*/

typedef INT32 bit_buf_type;	/* type of bit-extraction buffer */
#define BIT_BUF_SIZE  32	/* size of buffer in bits */

/* If long is > 32 bits on your machine, and shifting/masking longs is
* reasonably fast, making bit_buf_type be long and setting BIT_BUF_SIZE
* appropriately should be a win.  Unfortunately we can't define the size
* with something like  #define BIT_BUF_SIZE (sizeof(bit_buf_type)*8)
* because not all machines measure sizeof in 8-bit bytes.
*/

typedef struct {		/* Bitreading state saved across MCUs */
    bit_buf_type get_buffer;	/* current bit-extraction buffer */
    int bits_left;		/* # of unused bits in it */
} bitread_perm_state;

typedef struct {		/* Bitreading working state within an MCU */
    /* Current data source location */
    /* We need a copy, rather than munging the original, in case of suspension */
    const JOCTET * next_input_byte; /* => next byte to read from source */
    size_t bytes_in_buffer;	/* # of bytes remaining in source buffer */
    /* Bit input buffer --- note these values are kept in register variables,
    * not in this struct, inside the inner loops.
    */
    bit_buf_type get_buffer;	/* current bit-extraction buffer */
    int bits_left;		/* # of unused bits in it */
    /* Pointer needed by jpeg_fill_bit_buffer. */
    j_decompress_ptr cinfo;	/* back link to decompress master record */
} bitread_working_state;

/* Macros to declare and load/save bitread local variables. */
#define BITREAD_STATE_VARS  \
    register bit_buf_type get_buffer;  \
    register int bits_left;  \
    bitread_working_state br_state

#define BITREAD_LOAD_STATE(cinfop,permstate)  \
    br_state.cinfo = cinfop; \
    br_state.next_input_byte = cinfop->src->next_input_byte; \
    br_state.bytes_in_buffer = cinfop->src->bytes_in_buffer; \
    get_buffer = permstate.get_buffer; \
    bits_left = permstate.bits_left;

#define BITREAD_SAVE_STATE(cinfop,permstate)  \
    cinfop->src->next_input_byte = br_state.next_input_byte; \
    cinfop->src->bytes_in_buffer = br_state.bytes_in_buffer; \
    permstate.get_buffer = get_buffer; \
    permstate.bits_left = bits_left

/*
* These macros provide the in-line portion of bit fetching.
* Use CHECK_BIT_BUFFER to ensure there are N bits in get_buffer
* before using GET_BITS, PEEK_BITS, or DROP_BITS.
* The variables get_buffer and bits_left are assumed to be locals,
* but the state struct might not be (jpeg_huff_decode needs this).
*	CHECK_BIT_BUFFER(state,n,action);
*		Ensure there are N bits in get_buffer; if suspend, take action.
*      val = GET_BITS(n);
*		Fetch next N bits.
*      val = PEEK_BITS(n);
*		Fetch next N bits without removing them from the buffer.
*	DROP_BITS(n);
*		Discard next N bits.
* The value N should be a simple variable, not an expression, because it
* is evaluated multiple times.
*/

#define CHECK_BIT_BUFFER(state,nbits,action) \
{ if (bits_left < (nbits)) {  \
    if (! jpeg_fill_bit_buffer(&(state),get_buffer,bits_left,nbits))  \
{ action; }  \
    get_buffer = (state).get_buffer; bits_left = (state).bits_left; } }

#define GET_BITS(nbits) \
    (((int) (get_buffer >> (bits_left -= (nbits)))) & ((1<<(nbits))-1))

#define PEEK_BITS(nbits) \
    (((int) (get_buffer >> (bits_left -  (nbits)))) & ((1<<(nbits))-1))

#define DROP_BITS(nbits) \
    (bits_left -= (nbits))



/*
* Code for extracting next Huffman-coded symbol from input bit stream.
* Again, this is time-critical and we make the main paths be macros.
*
* We use a lookahead table to process codes of up to HUFF_LOOKAHEAD bits
* without looping.  Usually, more than 95% of the Huffman codes will be 8
* or fewer bits long.  The few overlength codes are handled with a loop,
* which need not be inline code.
*
* Notes about the HUFF_DECODE macro:
* 1. Near the end of the data segment, we may fail to get enough bits
*    for a lookahead.  In that case, we do it the hard way.
* 2. If the lookahead table contains no entry, the next code must be
*    more than HUFF_LOOKAHEAD bits long.
* 3. jpeg_huff_decode returns -1 if forced to suspend.
*/

#define HUFF_DECODE(result,state,htbl,failaction,slowlabel) \
{ register int nb, look; \
    if (bits_left < HUFF_LOOKAHEAD) { \
    if (! jpeg_fill_bit_buffer(&state,get_buffer,bits_left, 0)) {failaction;} \
    get_buffer = state.get_buffer; bits_left = state.bits_left; \
    if (bits_left < HUFF_LOOKAHEAD) { \
    nb = 1; goto slowlabel; \
    } \
    } \
    look = PEEK_BITS(HUFF_LOOKAHEAD); \
    if ((nb = htbl->look_nbits[look]) != 0) { \
    DROP_BITS(nb); \
    result = htbl->look_sym[look]; \
    } else { \
    nb = HUFF_LOOKAHEAD+1; \
slowlabel: \
    if ((result=jpeg_huff_decode(&state,get_buffer,bits_left,htbl,nb)) < 0) \
{ failaction; } \
    get_buffer = state.get_buffer; bits_left = state.bits_left; \
    } \
}





/*
* A forward DCT routine is given a pointer to a work area of type DCTELEM[];
* the DCT is to be performed in-place in that buffer.  Type DCTELEM is int
* for 8-bit samples, INT32 for 12-bit samples.  (NOTE: Floating-point DCT
* implementations use an array of type FAST_FLOAT, instead.)
* The DCT inputs are expected to be signed (range +-CENTERJSAMPLE).
* The DCT outputs are returned scaled up by a factor of 8; they therefore
* have a range of +-8K for 8-bit data, +-128K for 12-bit data.  This
* convention improves accuracy in integer implementations and saves some
* work in floating-point ones.
* Quantization of the output coefficients is done by jcdctmgr.c.
*/

#if BITS_IN_JSAMPLE == 8
typedef int DCTELEM;		/* 16 or 32 bits is fine */
#else
typedef INT32 DCTELEM;		/* must have 32 bits */
#endif

typedef JMETHOD(void, forward_DCT_method_ptr, (DCTELEM * data));
typedef JMETHOD(void, float_DCT_method_ptr, (FAST_FLOAT * data));


/*
* An inverse DCT routine is given a pointer to the input JBLOCK and a pointer
* to an output sample array.  The routine must dequantize the input data as
* well as perform the IDCT; for dequantization, it uses the multiplier table
* pointed to by compptr->dct_table.  The output data is to be placed into the
* sample array starting at a specified column.  (Any row offset needed will
* be applied to the array pointer before it is passed to the IDCT code.)
* Note that the number of samples emitted by the IDCT routine is
* DCT_scaled_size * DCT_scaled_size.
*/


/*
* Each IDCT routine has its own ideas about the best dct_table element type.
*/

typedef MULTIPLIER  ISLOW_MULT_TYPE; // short or int, whichever is faster
#if BITS_IN_JSAMPLE == 8
typedef MULTIPLIER IFAST_MULT_TYPE;// 16 bits is OK, use short if faster
#define IFAST_SCALE_BITS  2        // fractional bits in scale factors
#else
typedef INT32 IFAST_MULT_TYPE;     // need 32 bits for scaled quantizers
#define IFAST_SCALE_BITS  13       // fractional bits in scale factors
#endif

/*
* Each IDCT routine is responsible for range-limiting its results and
* converting them to unsigned form (0..MAXJSAMPLE).  The raw outputs could
* be quite far out of range if the input data is corrupt, so a bulletproof
* range-limiting step is required.  We use a mask-and-table-lookup method
* to do the combined operations quickly.  See the comments with
* prepare_range_limit_table for more info.
*/

#define IDCT_range_limit(cinfo)  ((cinfo)->sample_range_limit + CENTERJSAMPLE)

#define RANGE_MASK  (MAXJSAMPLE * 4 + 3) /* 2 bits wider than legal samples */

/*
* Macros for handling fixed-point arithmetic; these are used by many
* but not all of the DCT/IDCT modules.
*
* All values are expected to be of type INT32.
* Fractional constants are scaled left by CONST_BITS bits.
* CONST_BITS is defined within each module using these macros,
* and may differ from one module to the next.
*/

#define ONE	((INT32) 1)
#define CONST_SCALE (ONE << CONST_BITS)


/* Descale and correctly round an INT32 value that's scaled by N bits.
* We assume RIGHT_SHIFT rounds towards minus infinity, so adding
* the fudge factor is correct for either sign of X.
*/

#define DESCALE(x,n)  RIGHT_SHIFT((x) + (ONE << ((n)-1)), n)

/* Multiply an INT32 variable by an INT32 constant to yield an INT32 result.
* This macro is used only when the two inputs will actually be no more than
* 16 bits wide, so that a 16x16->32 bit multiply can be used instead of a
* full 32x32 multiply.  This provides a useful speedup on many machines.
* Unfortunately there is no way to specify a 16x16->32 multiply portably
* in C, but some C compilers will do the right thing if you provide the
* correct combination of casts.
*/

#ifdef SHORTxSHORT_32		/* may work if 'int' is 32 bits */
#define MULTIPLY16C16(var,const)  (((INT16) (var)) * ((INT16) (const)))
#endif
#ifdef SHORTxLCONST_32		/* known to work with Microsoft C 6.0 */
#define MULTIPLY16C16(var,const)  (((INT16) (var)) * ((INT32) (const)))
#endif

#ifndef MULTIPLY16C16		/* default definition */
#define MULTIPLY16C16(var,const)  ((var) * (const))
#endif

/* Same except both inputs are variables. */

#ifdef SHORTxSHORT_32		/* may work if 'int' is 32 bits */
#define MULTIPLY16V16(var1,var2)  (((INT16) (var1)) * ((INT16) (var2)))
#endif

#ifndef MULTIPLY16V16		/* default definition */
#define MULTIPLY16V16(var1,var2)  ((var1) * (var2))
#endif


/* Master record for a compression instance */

struct jpeg_compress_struct
{
    jpeg_common_fields; // Fields shared with jpeg_decompress_struct
    u32 image_width;    // input image width
    u32 image_height;   // input image height

    // dimension for part decoder
    u32  x1;
    u32  x2;
    u32  y1;
    u32  y2;

    // State variable: index of next scanline to be written to
    // jpeg_write_scanlines().  Application may use this to control its
    // processing loop, e.g., "while (next_scanline < image_height)".
    //
    u32 next_scanline;  // 0 .. image_height-1
    //u32 resizingFactor;
};


/*
* Object interface for cjpeg's source file decoding modules
*/

typedef struct cjpeg_source_struct * cjpeg_source_ptr;

struct cjpeg_source_struct {
    JMETHOD(bool, start_input,    (j_compress_ptr cinfo, cjpeg_source_ptr sinfo));
    JMETHOD(u32,  get_pixel_rows, (j_compress_ptr cinfo, cjpeg_source_ptr sinfo, u8 *BufferOut, u32 outputImageType));
    JMETHOD(void, finish_input,   (j_compress_ptr cinfo, cjpeg_source_ptr sinfo));
};

typedef struct _st_imgcodec_method_
{
    JMETHOD(bool, start_input,    (j_compress_ptr cinfo, cjpeg_source_ptr sinfo));
    JMETHOD(u32,  get_pixel_rows, (j_compress_ptr cinfo, cjpeg_source_ptr sinfo, u8 *BufferOut, u32 outputImageType));
    JMETHOD(void, finish_input,   (j_compress_ptr cinfo, cjpeg_source_ptr sinfo));
}IMGCODEC_METHOD,*PIMGCODEC_METHOD;

#define imgcodec_mem_create_compress_macro(cinfo) \
    imgcodec_mem_create_compress((cinfo), JPEG_LIB_VERSION, \
    (size_t) sizeof(struct jpeg_compress_struct))


/* Expanded data source object for stdio input */

typedef struct {
    struct jpeg_source_mgr pub;	/* public fields */
    JOCTET * buffer;		/* start of buffer */
    bool start_of_file;	/* have we gotten any data yet? */
} my_source_mgr;

typedef my_source_mgr * my_src_ptr;


/* Private buffer controller object */

typedef struct {
    struct jpeg_d_coef_controller pub; /* public fields */

    /* These variables keep track of the current location of the input side. */
    /* cinfo->input_iMCU_row is also used for this. */
    u32 MCU_ctr;		/* counts MCUs processed in current row */
    int MCU_vert_offset;		/* counts MCU rows within iMCU row */
    int MCU_rows_per_iMCU_row;	/* number of such rows needed */

    /* The output side's location is represented by cinfo->output_iMCU_row. */

    /* In single-pass modes, it's sufficient to buffer just one MCU.
    * We allocate a workspace of D_MAX_BLOCKS_IN_MCU coefficient blocks,
    * and let the entropy decoder write into that workspace each time.
    * (On 80x86, the workspace is FAR even though it's not really very big;
    * this is to keep the module interfaces unchanged when a large coefficient
    * buffer is necessary.)
    * In multi-pass modes, this array points to the current MCU's blocks
    * within the virtual arrays; it is used only by the input side.
    */
    JBLOCKROW MCU_buffer[D_MAX_BLOCKS_IN_MCU];


} my_coef_controller;

typedef my_coef_controller * my_coef_ptr;



typedef struct {
    struct jpeg_color_deconverter pub; /* public fields */

    /* Private state for YCC->RGB conversion */
    int * Cr_r_tab;		/* => table for Cr to R conversion */
    int * Cb_b_tab;		/* => table for Cb to B conversion */
    INT32 * Cr_g_tab;		/* => table for Cr to G conversion */
    INT32 * Cb_g_tab;		/* => table for Cb to G conversion */
} my_color_deconverter;

typedef my_color_deconverter * my_cconvert_ptr;


/* Private subobject for this module */

typedef struct {
    struct jpeg_inverse_dct pub;	/* public fields */

    /* This array contains the IDCT method code that each multiplier table
    * is currently set up for, or -1 if it's not yet set up.
    * The actual multiplier tables are pointed to by dct_table in the
    * per-component comp_info structures.
    */
    int cur_method[MAX_COMPONENTS];
} my_idct_controller;

typedef my_idct_controller * my_idct_ptr;



/*
* Expanded entropy decoder object for Huffman decoding.
*
* The savable_state subrecord contains fields that change within an MCU,
* but must not be updated permanently until we complete the MCU.
*/

typedef struct {
    int last_dc_val[MAX_COMPS_IN_SCAN]; /* last DC coef for each component */
} savable_state;

/* This macro is to work around compilers with missing or broken
* structure assignment.  You'll need to fix this code if you have
* such a compiler and you change MAX_COMPS_IN_SCAN.
*/

#ifndef NO_STRUCT_ASSIGN
#define ASSIGN_STATE(dest,src)  ((dest) = (src))
#else
#if MAX_COMPS_IN_SCAN == 4
#define ASSIGN_STATE(dest,src)  \
    ((dest).last_dc_val[0] = (src).last_dc_val[0], \
    (dest).last_dc_val[1] = (src).last_dc_val[1], \
    (dest).last_dc_val[2] = (src).last_dc_val[2], \
    (dest).last_dc_val[3] = (src).last_dc_val[3])
#endif
#endif


typedef struct {
    struct jpeg_entropy_decoder pub; /* public fields */

    /* These fields are loaded into local variables at start of each MCU.
    * In case of suspension, we exit WITHOUT updating them.
    */
    bitread_perm_state bitstate;	/* Bit buffer at start of MCU */
    savable_state saved;		/* Other state at start of MCU */

    /* These fields are NOT loaded into local working state. */
    unsigned int restarts_to_go;	/* MCUs left in this restart interval */

    /* Pointers to derived tables (these workspaces have image lifespan) */
    d_derived_tbl * dc_derived_tbls[NUM_HUFF_TBLS];
    d_derived_tbl * ac_derived_tbls[NUM_HUFF_TBLS];

    /* Precalculated info set up by start_pass for use in decode_mcu: */

    /* Pointers to derived tables to be used for each block within an MCU */
    d_derived_tbl * dc_cur_tbls[D_MAX_BLOCKS_IN_MCU];
    d_derived_tbl * ac_cur_tbls[D_MAX_BLOCKS_IN_MCU];
    /* Whether we care about the DC and AC coefficient values for each block */
    bool dc_needed[D_MAX_BLOCKS_IN_MCU];
    bool ac_needed[D_MAX_BLOCKS_IN_MCU];
} huff_entropy_decoder;

typedef huff_entropy_decoder * huff_entropy_ptr;

/* Private state */

typedef struct {
    struct jpeg_input_controller pub; /* public fields */

    bool inheaders;		/* TRUE until first SOS is reached */
} my_input_controller;

typedef my_input_controller * my_inputctl_ptr;


/* Private buffer controller object */

typedef struct {
    struct jpeg_d_main_controller pub; /* public fields */

    /* Pointer to allocated workspace (M or M+2 row groups). */
    JSAMPARRAY buffer[MAX_COMPONENTS];

    bool buffer_full;		/* Have we gotten an iMCU row from decoder? */
    u32 rowgroup_ctr;	/* counts row groups output to postprocessor */

    /* Remaining fields are only used in the context case. */

    /* These are the master pointers to the funny-order pointer lists. */
    JSAMPIMAGE xbuffer[2];	/* pointers to weird pointer lists */

    int whichptr;			/* indicates which pointer set is now in use */
    int context_state;		/* process_data state machine status */
    u32 rowgroups_avail;	/* row groups available to postprocessor */
    u32 iMCU_row_ctr;	/* counts iMCU rows to detect image top/bot */
} my_main_controller;

typedef my_main_controller * my_main_ptr;


/* Private state */

typedef struct {
    struct jpeg_marker_reader pub; /* public fields */

    /* Application-overridable marker processing methods */
    jpeg_marker_parser_method process_COM;
    jpeg_marker_parser_method process_APPn[16];

    /* Limit on marker data length to save for each marker type */
    unsigned int length_limit_COM;
    unsigned int length_limit_APPn[16];

    /* Status of COM/APPn marker saving */
    jpeg_saved_marker_ptr cur_marker;	/* NULL if not processing a marker */
    unsigned int bytes_read;		/* data bytes read so far in marker */
    /* Note: cur_marker is not linked into marker_list until it's all read. */
} my_marker_reader;

typedef my_marker_reader * my_marker_ptr;




/* Private buffer controller object */

typedef struct {
    struct jpeg_d_post_controller pub; /* public fields */

    /* Color quantization source buffer: this holds output data from
    * the upsample/color conversion step to be passed to the quantizer.
    * For two-pass color quantization, we need a full-image buffer;
    * for one-pass operation, a strip buffer is sufficient.
    */
    JSAMPARRAY buffer;		/* strip buffer, or current strip of virtual */
    u32 strip_height;	/* buffer size in rows */
    /* for two-pass mode only: */
    u32 starting_row;	/* row # of first row in current strip */
    u32 next_row;		/* index of next row to fill/empty in strip */
} my_post_controller;

typedef my_post_controller * my_post_ptr;


/* Private state */

typedef struct {
    struct jpeg_decomp_master pub; /* public fields */

    int pass_number;		/* # of passes completed */

    bool using_merged_upsample; /* TRUE if using merged upsample/cconvert */


} my_decomp_master;

typedef my_decomp_master * my_master_ptr;

/* Private subobject */


/* Pointer to routine to upsample a single component */
typedef JMETHOD(void, upsample1_ptr,
                (j_decompress_ptr cinfo, jpeg_component_info * compptr,
                JSAMPARRAY input_data, JSAMPARRAY * output_data_ptr));

typedef struct {
    struct jpeg_upsampler pub;	/* public fields */

    /* Color conversion buffer.  When using separate upsampling and color
    * conversion steps, this buffer holds one upsampled row group until it
    * has been color converted and output.
    * Note: we do not allocate any storage for component(s) which are full-size,
    * ie do not need rescaling.  The corresponding entry of color_buf[] is
    * simply set to point to the input data array, thereby avoiding copying.
    */
    JSAMPARRAY color_buf[MAX_COMPONENTS];

    /* Per-component upsampling method pointers */
    upsample1_ptr methods[MAX_COMPONENTS];

    int next_row_out;		/* counts rows emitted from color_buf */
    u32 rows_to_go;	/* counts rows remaining in image */

    /* Height of an input row group for each component. */
    int rowgroup_height[MAX_COMPONENTS];

    /* These arrays save pixel expansion factors so that int_expand need not
    * recompute them each time.  They are unused for other upsampling methods.
    */
    UINT8 h_expand[MAX_COMPONENTS];
    UINT8 v_expand[MAX_COMPONENTS];
} my_upsampler;

typedef my_upsampler * my_upsample_ptr;


#ifndef ALIGN_TYPE		/* so can override from jconfig.h */
#define ALIGN_TYPE  double
#endif

typedef union small_pool_struct * small_pool_ptr;

typedef union small_pool_struct {
    struct {
        small_pool_ptr next;	/* next in list of pools */
        size_t bytes_used;		/* how many bytes already used within pool */
        size_t bytes_left;		/* bytes still available in this pool */
    } hdr;
    ALIGN_TYPE dummy;		/* included in union to ensure alignment */
} small_pool_hdr;

typedef union large_pool_struct * large_pool_ptr;

typedef union large_pool_struct {
    struct {
        large_pool_ptr next;	/* next in list of pools */
        size_t bytes_used;		/* how many bytes already used within pool */
        size_t bytes_left;		/* bytes still available in this pool */
    } hdr;
    ALIGN_TYPE dummy;		/* included in union to ensure alignment */
} large_pool_hdr;


/*
* Here is the full definition of a memory manager object.
*/

typedef struct {
    struct jpeg_memory_mgr pub;	/* public fields */

    /* Each pool identifier (lifetime class) names a linked list of pools. */
    small_pool_ptr small_list[JPOOL_NUMPOOLS];
    large_pool_ptr large_list[JPOOL_NUMPOOLS];

    /* Since we only have one lifetime class of virtual arrays, only one
    * linked list is necessary (for each datatype).  Note that the virtual
    * array control blocks being linked together are actually stored somewhere
    * in the small-pool list.
    */

    /* This counts total space obtained from jpeg_get_small/large */
    long total_space_allocated;

    /* alloc_sarray and alloc_barray set this value for use by virtual
    * array routines.
    */
    u32 last_rowsperchunk;	/* from most recent alloc_sarray/barray */
} my_memory_mgr, *my_mem_ptr;



/* API for Memory Management sub-module used by BMP/GIF/JPEG decoders */
void * imgcodec_mem_alloc_small (j_common_ptr cinfo, int pool_id, size_t sizeofobject);
void  * imgcodec_mem_alloc_large (j_common_ptr cinfo, int pool_id, size_t sizeofobject);
JSAMPARRAY imgcodec_mem_alloc_sarray (j_common_ptr cinfo, int pool_id, u32 samplesperrow, u32 numrows);
bool imgcodec_mem_create_compress (j_compress_ptr cinfo, int version, size_t structsize);
bool imgcodec_mem_jinit_memory_mgr (j_common_ptr cinfo);
void imgcodec_mem_destroy (j_common_ptr cinfo);

#endif /* __MEM_MGT_H__*/
#endif

