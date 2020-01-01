/*
 * mplib - a library that enables you to edit ID3 tags
 *
 * Copyright (c) 2001,2002,2003,2004,2005,2006 Stefan Podkowinski
 *               2006                          Michal Kowalczuk
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the author nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __MPLIB_H
#define __MPLIB_H


/* __BEGIN_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names.  Use __END_DECLS at
   the end of C declarations. */
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

/* __P is a macro used to wrap function prototypes, so that compilers
   that don't understand ANSI C prototypes still work, and ANSI C
   compilers can issue warnings about type mismatches. */
#undef __P

#if 0
#if defined (__STDC__) || defined (_AIX) \
        || (defined (__mips) && defined (_SYSTYPE_SVR4)) \
        || defined(WIN32) || defined(__cplusplus)

# define __P(protos) protos
#else
# define __P(protos) ()
#endif
#else
#define __P(protos) protos
#endif

__BEGIN_DECLS


/*!
 *\mainpage mplib API reference
 *\section About About this document
 * This is an automatically generated description of the mplib
 * API. It contains informations about existing functions,
 * structures and macros.
 *
 * The most interesting file while working with mplib is the global
 * include file, mplib.h. You'll find it useful for reference on how
 * to call code in mplib. Have a look on the
 * <a href="globals_func.html">global function index</a> as well.
 *
 * You may also download this document in PDF format
 * <a href="http://sourceforge.net/project/showfiles.php?group_id=18409&package_id=16482">here</a>.
 *
 *
 */


/*************************************/
/*             Defines               */
/*************************************/



/*************************************/
/*              errno values         */
/*************************************/
#define MP_EERROR 1
#define MP_EFNF 2
#define MP_EFCOMPR 3
#define MP_EFENCR 4
/*define MP_EUNICODE 5*/
#define MP_EVERSION 6


#if 0
#define ID3_DBG_MSG(fmt, args...)                             \
        {                                                     \
            diag_printf("[%s] (%d) ", __FUNCTION__,__LINE__); \
            diag_printf(fmt, ##args);                         \
        }
#else
//#define ID3_DBG_MSG(fmt, args...)
#endif

#include "mdl_vfs_file.ho"
#include "ms_io.h"
#include "id3.h"
#include "esl_aud_itf.h"
#ifndef __off_t
#define __off_t
#endif
#ifndef __size_t
#define __size_t
typedef unsigned int size_t;
#endif

typedef long off_type;

/*************************************/
/*        Structs and company        */
/*************************************/

/** Header structure with 4 segments containing 32 bit header information */
typedef struct _mpeg_header
{
  unsigned int syncword; /** Sync Word */
  unsigned int version; /** Version number */
  unsigned int layer; /** Layer number */
  unsigned int protbit; /** Protection Bit */
  unsigned int bitrate; /** kbit/sec */
  unsigned int samplingfreq; /** hz */
  unsigned int padbit; /** Padding bit */
  unsigned int privbit; /** Private Bit */
  unsigned int mode; /** Stereo, Joint-Stereo, Dual-Channel, Mono */
  unsigned int mode_ext; /** Mode extension */
  unsigned int copyright; /** Copyright yes/no */
  unsigned int originalhome; /** Original datastream yes/no */
  unsigned int emphasis; /** Emphasis bits */
} mpeg_header;


/** Generic tag structure */
typedef struct _id3_tag
{
  int version; /** tags version, either 1 or 2 or -1 if not supported */
  void *tag; /** pointer to specific struct */
} id3_tag;


/** list of tags found in file */
typedef struct _id3_tag_list
{
  id3_tag *tag;
  struct _id3_tag_list *next;
  struct _id3_tag_list *first;
} id3_tag_list;


/*
 * The following structures are ment as low-level data holders. I strongly
 * suggest you to use the appropriate generic functions below to access them.
 */

/* V 1 */

/** ID3v1 tag structure */
typedef struct _id3v1_tag
{
  char *title;
  char *artist;
  char *album;
  char *year;
  char *comment;
  unsigned char track; /** track binary encoded */
  unsigned char genre; /** index on genre list - 0xFF for null */
} id3v1_tag;


/* V 2 */

/** ID3v2 Frame structure */
typedef struct _id3v2_frame
{
  char  frame_id[4]; /** The frame id e.g. TALB */
  unsigned char status_flag;
  unsigned char format_flag;
  //char *data;
  unsigned int data_size; /** frame size excluding header, incl. enc.,lang.,etc.
				  (total frame size - 10) */
} id3v2_frame;

/** Single linked list referencing a number of frames */
typedef struct _id3v2_frame_list
{
  struct _id3v2_frame *data;
  struct _id3v2_frame_list *next;
  struct _id3v2_frame_list *start;
} id3v2_frame_list;

/** ID3v2 Extended Header structure */
typedef struct _id3v2_extended_header
{
  unsigned long size;
  char *flag_bytes;
  unsigned int no_flag_bytes;
  unsigned int is_update;
  unsigned int crc_data_present;
  unsigned char crc_data_length;
  unsigned char* crc_data;
  unsigned int restrictions;
  unsigned char restrictions_data_length;
  unsigned char* restrictions_data;
} id3v2_extended_header;

/** ID3v2 Header structure */
typedef struct _id3v2_header
{
  /** Version 2.minor.revision */
  unsigned int version_minor;
  unsigned int version_revision;
  char flags; /** Flags - should only be set by mplib and does only contain
		   the following infos */
  unsigned int unsyncronization;
  unsigned int has_extended_header;
  unsigned int is_experimental;
  unsigned int has_footer;
  unsigned long total_tag_size; /** is size of all tag elements including
				   header and footer (each 10 bytes) */
  id3v2_extended_header *extended_header;   /** Extended header */
} id3v2_header;


/** ID3v2 tag structure */
typedef struct _id3v2_tag
{
  id3v2_header *header;
  id3v2_frame_list *frame_list;
} id3v2_tag;

/** A fields content unparsed */
typedef struct _id3_content
{
  unsigned int compressed;
  unsigned int encrypted;
  char *data;
  unsigned int length;
} id3_content;

/** Character encodings list */
/*
labeled encoding byte order byte sequence
UTF-16LE little-endian 34 6C, 7A 00, 34 D8 1E DD
UTF-16BE big-endian 6C 34, 00 7A, D8 34 DD 1E
UTF-16 little-endian, with BOM FF FE, 34 6C, 7A 00, 34 D8 1E DD
UTF-16 big-endian, with BOM FE FF, 6C 34, 00 7A, D8 34 DD 1E
*/
#if 0
typedef enum _id3_encoding
{
  mp_iso_8859_1 = MP_ISO_8859_1,
  mp_utf16 = MP_UTF16,
  mp_utf16be = MP_UTF16BE,
  mp_utf8 = MP_UTF8
} id3_encoding;

/** Content type for regular text */
typedef struct _id3_text_content
{
  id3_encoding encoding;
  char *text; /** Null terminated text */
} id3_text_content;

/** Content type for comment fields */
typedef struct _id3_comment_content
{
  id3_encoding encoding;
  char *language; /** ISO Language code */
  char *short_descr; /** Null term. content short description */
  char *text; /** Null terminated text */
} id3_comment_content;
#endif
/***************************************/
/*               Functions             */
/***************************************/
s32 mp_get_tag_total_len_from_file
(
    const ms_fnchar *filename, 
    u32 *u32Id3BufLen
);

s32
mp_get_tag_total_len_from_fd
(
    MSFILE fd,
    u32 *u32Id3BufLen
);

s32
mp_get_tag_total_len
(
    size_t (*read_func)(void *, size_t, void *),
    off_type (*lseek_func)(off_type, int, void *),
    void *arg,
    u32 *u32Id3BufLen
);


/**
 * Allocates a MPEG header structure from a file.
 * @param path          The filename
 * @return              A pointer to a new initialized header structure - NULL on IO Error
 */
//extern mpeg_header *mp_get_mpeg_header_from_file __P((const char* path));


/**
 * Gets the header structure from a file descriptor.
 * @param fd            The file descriptor
 * @return              A pointer to a new initialized header structure - NULL on IO Error
 */
//extern mpeg_header *mp_get_mpeg_header_from_fd __P((int fd));


/**
 * Frees a mpeg header structure.
 * @param str           The allocated mpeg header
 */
//Jerry 2007.5.15 #define mp_free_mpeg_header(str) xfree(str)


/** Allocates a label with the appropriate header field value as a string */
//extern char *mp_get_str_version __P((const mpeg_header*));
/** Allocates a label with the appropriate header field value as a string */
//extern char *mp_get_str_layer __P((const mpeg_header*));
/** Allocates a label with the appropriate header field value as a string */
//extern char *mp_get_str_bitrate __P((const mpeg_header*));
/** Allocates a label with the appropriate header field value as a string */
//extern char *mp_get_str_samplingfreq __P((const mpeg_header*));
/** Allocates a label with the appropriate header field value as a string */
//extern char *mp_get_str_mode __P((const mpeg_header*));


/**
 * Allocates and fills a list of tags found in the given file. This list
 * will contain at least one and at most two tags or is NULL if no tags
 * have been found.
 * This function prepares argument and calls mp_get_tag_list() function.
 * @param path              The files name to search for tags
 * @return                  A pointer to a initialized list struct or null if no tags
 *                          have been found
 */
extern s32 mp_get_tag_content_from_file(const ms_fnchar *fileName, u8 *id3Buf,esl_AudID3V1Info_t *id3Info);

/**
 * Allocates and fills a list of tags found in the given file. This list
 * will contain at least one and at most two tags or is NULL if no tags
 * have been found.
 * This function prepares argument and calls mp_get_tag_list() function.
 * @param fd                The file descriptor
 * @return                  A pointer to a initialized list struct or null if no tags
 *                          have been found
 */
extern s32 mp_get_tag_content_from_fd(MSFILE fd, u8 *id3Buf, esl_AudID3V1Info_t *id3Info);


/**
 * Allocates and fills a list of tags found in the given memory buffer. This
 * list will contain at least one and at most two tags or is NULL if no tags
 * have been found.
 * This function prepares argument and calls mp_get_tag_list() function.
 * @param buf           Pointer to buffer to search for tags
 * @param s             Size of the buffer
 * @return              A pointer to a initialized list struct or null if no tags
 *                      have been found
 */
extern id3_tag_list* mp_get_tag_list_from_mem(void * buf, size_t s);

/**
 * Allocates and fills a list of tags using read and seek wrapper functions.
 * @param read_func     Pointer to function that reads
 * @param lseek_func    Pointer to function that seeks
 * @param arg           Pointer to argument for read and seek wrapper functions
 * @return              A pointer to a initialized list struct or null if no tags
 *                      have been found
 */
extern s32 mp_get_tag_content(size_t (*read_func)(void *, size_t, void *),
						off_type (*lseek_func)(off_type, int, void *),
		void *arg, u8 *id3Buf, esl_AudID3V1Info_t *id3Info);

extern void
mp_get_tag_content_from_v1(esl_AudID3V1Info_t *id3Info, ID3V1TagContent* id3v1TagBuf, u8 *id3Buf, u8 type);


/** Frees a tag list beginning with the given element XXX. */
//extern void mp_free_list (id3_tag_list*);


/**
 * Gets the first content found of a specified field in the given tag and
 * allocates a struct.
 * @param t             The tag
 * @param f             The fields identifier
 *
 * @return              The new allocated content for the specified field or NULL
 * On NULL:  errno set to the following values
 * - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 * - MP_EFNF     - Field does not exists in tag /invalid identifier
 * - MP_EVERSION - Tag has a version set that is not supported by the library
 */
//extern id3_content* mp_get_content (const id3_tag* t, int f);

/**
 * It's posible that a tag has multiple ocurances of a field,
 * use this function to get a specified field by position. The first
 * ocurance of the field in the tag is 0.
 * e.g.: To get the third comment in an id3v2 tag use
 * mp_get_content_at_pos(tag, MP_COMMENT, 2);
 * @param t             The tag
 * @param f             The fields identifier
 * @param pos           The content position in the tag
 * @return              @see mp_get_content()
 */
//extern id3_content* mp_get_content_at_pos __P((const id3_tag* t, int f, int pos));

/**
 * Gets a custom fields content and allocates a struct. This function can
 * only be applied to ID3v2 tags. It will lookup a by the given identifier
 * and return its content.
 * @param t             The tag
 * @param f             The field names identifier e.g. ENCR
 * @return              @see mp_get_content()
 */
//extern id3_content* mp_get_content_custom __P((const id3_tag* t, const char* f));

/**
 * See mp_get_content_at_pos() and mp_get_content_custom()
 * @param t             The tag
 * @param f             The field names identifier e.g. ENCR
 * @param pos           The content position in the tag
 * @return              @see mp_get_content()
 */
//extern id3_content* mp_get_content_custom_at_pos __P((const id3_tag* t, const char* f, int pos));

/** Frees a content struct */
//jerry 2007.5.15 extern void mp_free_content __P((id3_content*));
/** Frees a text struct */
//jerry 2007.5.15 extern void mp_free_text_content __P((id3_text_content*));
/** Frees a comment struct */
//jerry 2007.5.15 extern void mp_free_comment_content __P((id3_comment_content*));


/**
 * Copys the value of a specified field into the given tag. The content
 * argument may be freed after using this function. The way a content
 * is represented in a tag depends from the tags version and kind of field.
 * I.e. it may be nessecary to represent a track number as a binary value in a v1
 * tag or to embeded it into a frame for a v2 tag. The caller just needs to
 * give the correct identifier with the value as a id3_content and to take
 * care of freeing the id3_content value afterwards.
 * @param t             The tag to edit
 * @param field         The fields identifier
 * @param content       The fields new content
 * @return              0  success or one of the following errors
 *  - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 *  - MP_EFNF     - Field does not exists in tag /invalid identifier
 *  - MP_EVERSION - Function isn't able to handle a tag of this version
 */
//extern int mp_set_content __P((id3_tag* t, const int field, id3_content* content));

/**
 * Copys the value of a specified field into the given tag.
 * This function allows to specify a certain frame position.
 * @see mp_set_content(id3_tag* t, int field, id3_content* content)
 * @param t             The tag to edit
 * @param field         The fields identifier
 * @param content       The fields new content
 * @param pos           The frame position that should be used
 * @return              0  success or one of the following errors
 *  - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 *  - MP_EFNF     - Field does not exists in tag /invalid identifier
 *  - MP_EVERSION - Function isn't able to handle a tag of this version
 */
//extern int mp_set_content_at_pos __P((id3_tag* t, const int field, id3_content* content, int pos));

/**
 * Sets up a new custom field with the given value.
 * @param t             The tag to edit
 * @param field         The new fields name - A four chars upper case identifier e.g. ENCR
 * @param content       The fields new content
 * @return              See mp_set_content
 */
//extern int mp_set_custom_content __P((id3_tag* t, char* field, id3_content* content));

/**
 * Sets up a new custom field with the given value on a certain frame position.
 * @param t             The tag to edit
 * @param field         The new fields name - A four chars upper case identifier e.g. ENCR
 * @param content       The fields new content
 * @param pos           The frame position that should be used
 * @return              See mp_set_content
 */
//extern int mp_set_custom_content_at_pos __P((id3_tag* t, char* field, id3_content* content, int pos));

/**
 * Writes the tag to the specified file.
 * @param ls            The tag list to be added to file - may be NULL for deleting all tags
 * @param path          The filename
 * @return              0 on success or one of the following errors
 *  - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 *  - MP_EVERSION - Function isn't able to handle a tag of this version
 */
//extern int mp_write_to_file __P((const id3_tag_list* ls, const char* path));

/**
 * Writes the tag to the specified file.
 * @param ls            The tag list to be added to file - may be NULL for deleting all tags
 * @param fd            The file descriptor
 * @return              0 on success or one of the following errors
 *  - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 *  - MP_EVERSION - Function isn't able to handle a tag of this version
 */
//extern int mp_write_to_fd __P((const id3_tag_list* ls, const int fd));

/**
 * Deletes all tags in file.
 * @param path          The filename
 * @return              0 on success
 */
//extern int mp_del_tags_from_file __P((const char* path));

/**
 * Deletes all tags in file.
 * @param fd            The file descriptor
 * @return              0 on success
 */
//extern int mp_del_tags_from_fd __P((const int fd));

/**
 * Deletes all tags in file with the specified version.
 * @param path          The filename
 * @param version       Version of the tag that should be deleted
 * @return              0 on success
 */
//extern int mp_del_tags_by_ver_from_file __P((const char* path, const int version));

/**
 * Deletes all tags in file with the specified version.
 * @param fd            The file descriptor
 * @param version       Version of the tag that should be deleted
 * @return              0 on success
 */
//extern int mp_del_tags_by_ver_from_fd __P((int fd, const int version));

/**
 * Converts a tag to id3v1 tag format.
 * @param t             The tag to be converted
 * @return              0 on success or one of the following errors
 *  - MP_EVERSION - Function isn't able to handle a tag of this version
 */
//extern int mp_convert_to_v1 __P((id3_tag* t));

/**
 * Converts a tag to id3v2 tag format.
 * @param t             The tag to be converted
 * @return              0 on success or one of the following errors
 *  - MP_EVERSION - Function isn't able to handle a tag of this version
 */
//extern int mp_convert_to_v2 __P((id3_tag* t));

/**
 * Checks wether the given value would be a valid v1 field.
 * @param field         The field
 * @param value         The value
 * @return              0 if test failed
 */
//extern int mp_is_valid_v1_value __P((int field, char* value));

/**
 * Parses the artist field.
 * On NULL:  errno set to the following values
 * - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 * - MP_EFENCR   - The value for this field has been encrypted and can thus not be retrieved
 * - MP_EFCOMPR  - The value for this field has been compressed and can thus not be retrieved
 *
 * @param content       the content to parse
 * @return              A pointer to a new initialized structure suitable for the content or NULL
 */
//extern id3_text_content *mp_parse_artist __P((const id3_content* content));

/**
 * Parses the title field.
 * On NULL:  errno set to the following values
 * - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 * - MP_EFENCR   - The value for this field has been encrypted and can thus not be retrieved
 * - MP_EFCOMPR  - The value for this field has been compressed and can thus not be retrieved
 *
 * @param content       the content to parse
 * @return              A pointer to a new initialized structure suitable for the content or NULL
 */
//extern id3_text_content *mp_parse_title __P((const id3_content* content));

/**
 * Parses the album field.
 * On NULL:  errno set to the following values
 * - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 * - MP_EFENCR   - The value for this field has been encrypted and can thus not be retrieved
 * - MP_EFCOMPR  - The value for this field has been compressed and can thus not be retrieved
 *
 * @param content       the content to parse
 * @return              A pointer to a new initialized structure suitable for the content or NULL
 */
//extern id3_text_content *mp_parse_album __P((const id3_content* content));

/**
 * Parses the year field.
 * On NULL:  errno set to the following values
 * - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 * - MP_EFENCR   - The value for this field has been encrypted and can thus not be retrieved
 * - MP_EFCOMPR  - The value for this field has been compressed and can thus not be retrieved
 *
 * @param content       the content to parse
 * @return              A pointer to a new initialized structure suitable for the content or NULL
 */
//extern id3_text_content *mp_parse_year __P((const id3_content* content));

/**
 * Parses the genre field.
 * On NULL:  errno set to the following values
 * - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 * - MP_EFENCR   - The value for this field has been encrypted and can thus not be retrieved
 * - MP_EFCOMPR  - The value for this field has been compressed and can thus not be retrieved
 *
 * @param content       the content to parse
 * @return              A pointer to a new initialized structure suitable for the content or NULL
 */
//extern id3_text_content *mp_parse_genre __P((const id3_content* content));

/**
 * Parses the track field.
 * On NULL:  errno set to the following values
 * - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 * - MP_EFENCR   - The value for this field has been encrypted and can thus not be retrieved
 * - MP_EFCOMPR  - The value for this field has been compressed and can thus not be retrieved
 *
 * @param content       the content to parse
 * @return              A pointer to a new initialized structure suitable for the content or NULL
 */
//extern id3_text_content *mp_parse_track __P((const id3_content* content));

/**
 * Generic function for parsing text fields.
 * On NULL:  errno set to the following values
 * - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 * - MP_EFENCR   - The value for this field has been encrypted and can thus not be retrieved
 * - MP_EFCOMPR  - The value for this field has been compressed and can thus not be retrieved
 *
 * @param content       the content to parse
 * @return              A pointer to a new initialized structure suitable for the content or NULL
 */
extern s32 mp_parse_text(const char* content, u32 len, esl_AudID3TextInfo_t *id3TagInfo);

/**
 * Parses the comment field.
 * On NULL:  errno set to the following values
 * - MP_EERROR   - General failure: may occure on wrong usage, but should never happen
 * - MP_EFENCR   - The value for this field has been encrypted and can thus not be retrieved
 * - MP_EFCOMPR  - The value for this field has been compressed and can thus not be retrieved
 *
 * @param content       the content to parse
 * @return              A pointer to a new initialized structure suitable for the content or NULL
 */
//extern id3_comment_content *mp_parse_comment __P((const id3_content* content));
extern s32 mp_parse_comment(const char* content, u32 len, esl_AudID3TextInfo_t *id3TagInfo);


/**
 * Assembles content from a comont text content.
 * @param text      the text
 * @param enc       the texts encoding (NULL)
 * @return          A pointer to a new initialized content structure
 */
extern void mp_assemble_text_content(esl_AudID3TextInfo_t* id3TextTag, const char* text,  EncodingScheme enc);

/**
 * Assembles content from a comment.
 * @param text      the text
 * @param descr     a short describtion to the text (NULL)
 * @param enc       the texts encoding
 * @param lang      the comments language (NULL)
 * @return          A pointer to a new initialized content structure
 */
extern void mp_assemble_comment_content(esl_AudID3TextInfo_t* id3TextTag, const char* text, const char* short_descr, EncodingScheme enc, const char* lang);

/**
 * Gets a new allocated tag.
 * @return new allocated tag
 */
//extern id3_tag* mp_alloc_tag __P((void));

/**
 * Gets a new allocated tag with the specified version.
 * @return new allocated tag with specified version
 */
//extern id3_tag* mp_alloc_tag_with_version __P((int));

/**
 * Frees tag struct.
 * @param t the tag to free
 */
//extern void mp_free_tag __P((id3_tag* t));


typedef struct _mem_arg
{
	unsigned int buf;
	size_t size;
	unsigned int act;
} mem_arg;

typedef struct _file_arg
{
	MSFILE fd;
} file_arg;


__END_DECLS

#endif /* __MPLIB_H */
