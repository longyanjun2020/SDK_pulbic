/* rvstdio.h - This file replaces the ANSI stdio.h for portability. */
/************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/

#if !defined(RV_STDIO_H)
#define RV_STDIO_H

#include "rvccore.h"
#include "rvansi.h"
#include "rverror.h"

#ifdef __cplusplus
extern "C" {
#endif


#if !defined(RV_STDIO_TYPE) || ((RV_STDIO_TYPE != RV_STDIO_ANSI) && \
    (RV_STDIO_TYPE != RV_STDIO_OSE_DEBUG) && \
    (RV_STDIO_TYPE != RV_STDIO_STUB) && \
    (RV_STDIO_TYPE != RV_STDIO_WINCE_DEBUG))
#error RV_STDIO_TYPE not set properly
#endif

#if (RV_OS_TYPE == RV_OS_TYPE_RTK)
extern void *VT_RvVTFopen(char *rvfilename, char *rvtype);
extern long VT_RvVTFclose(void *file_ptr);
extern short VT_RvVTFgets(char *buffer, unsigned long size, void *file_ptr);
extern long VT_RvVTFwrite(char *rvbuffer, unsigned long size, unsigned long tmp, void *file_ptr);
extern long VT_RvVTFflush(void *file_ptr);
extern long VT_RvVTFseek(void *file_ptr, unsigned long offset, unsigned long position);
extern int mdl_vt_stack_printf(int level, int level2, const char *pFmt, ...);
extern int mdl_vt_stack_RvSprintf(char *s, const char *format, ...);
#endif
/********************************************************************************************
 * RvStdioInit - Initializes the stdio module.
 *
 * Must be called once (and only once) before any other functions in the module are called.
 *
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : Always RV_OK
 */
RvStatus RvStdioInit(void);

/********************************************************************************************
 * RvStdioEnd - De-initializes the stdio module.
 *
 * INPUT   : none
 * OUTPUT  : none
 * RETURN  : Always RV_OK
 */
RvStatus RvStdioEnd(void);

#if (RV_STDIO_TYPE == RV_STDIO_ANSI) || \
    (RV_STDIO_TYPE == RV_STDIO_OSE_DEBUG) || \
    (RV_STDIO_TYPE == RV_STDIO_WINCE_DEBUG)

#include <stdio.h>

/* Some of the OS's must have ctype.h for isspace(), tolower(), isdigit(), etc. */
#include <ctype.h>


#if (RV_OS_TYPE != RV_OS_TYPE_WINCE) && \
    (RV_OS_TYPE != RV_OS_TYPE_VXWORKS) && \
    (RV_OS_TYPE != RV_OS_TYPE_PSOS) && \
    (RV_OS_TYPE != RV_OS_TYPE_OSE) && \
    (RV_OS_TYPE != RV_OS_TYPE_NUCLEUS) && \
    (RV_OS_TYPE != RV_OS_TYPE_SYMBIAN) && \
    (RV_OS_TYPE != RV_OS_TYPE_INTEGRITY) && \
    (RV_OS_TYPE != RV_OS_TYPE_OSA) && \
	!((RV_OS_TYPE == RV_OS_TYPE_MOPI) && !defined(_WIN32))
/* nucleus, VxWorks, pSOS, WinCE & OSE keeps 'qsort()' in stdlib.h */
/* MOPI platform doesn't have 'search.h' */
#include <search.h>     /* for 'qsort()' */
#endif

#if (RV_OS_TYPE == RV_OS_TYPE_TRU64) || \
    (RV_OS_TYPE == RV_OS_TYPE_LINUX) || \
    (RV_OS_TYPE == RV_OS_TYPE_SOLARIS) || \
    (RV_OS_TYPE == RV_OS_TYPE_UNIXWARE) || \
    (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)
#include <string.h>
#include <stdlib.h> /* qsort() is kept in stdlib.h in some of these OSs */
#endif



/* Data Types */

/* FILE - represents a ANSI stdio FILE type for streams. */
#define RvFILE     FILE

/* RvFpos_t - represents a ANSI stdio fpos_t type for file position */
#define RvFpos_t   fpos_t
#define RvL_tmpnam L_tmpnam

/* Standard Streams */
#define RvStderr stderr
#define RvStdout stdout
#define RvStdin  stdin

/* Constants */
#define RvEOF    EOF

/* Standard char operations for old WinCE versions */
#if (RV_OS_TYPE == RV_OS_TYPE_WINCE) && (RV_OS_VERSION == RV_OS_WINCE_2_11)
void CharToWChar(RvChar CharIn, WCHAR * wCharOut);
/********************************************************************************************
 * isupper - checks if input character is an uper case letter
 *
 * INPUT   : CharIn		- character to be checked
 * OUTPUT  : none
 * RETURN  : returns a non-zero value if CharIn is an uppercase character 
 */
RVCOREAPI 
RvInt RVCALLCONV __cdecl isupper(
	IN RvInt CharIn);


/********************************************************************************************
 * islower - checks if input character is an lower case letter
 *
 * INPUT   : CharIn		- character to be checked
 * OUTPUT  : none
 * RETURN  : returns a non-zero value if CharInc is a lowercase character  
 */
RVCOREAPI 
RvInt RVCALLCONV __cdecl islower(
	IN RvInt CharIn);


/********************************************************************************************
 * isspace - checks if input character is a white-space character
 *
 * INPUT   : CharIn		- character to be checked
 * OUTPUT  : none
 * RETURN  : returns a non-zero value if CharIn is a white-space character   
 */
RVCOREAPI 
RvInt RVCALLCONV __cdecl isspace(
	IN RvInt CharIn);


/********************************************************************************************
 * isdigit - checks if input character is a digit character
 *
 * INPUT   : CharIn		- character to be checked
 * OUTPUT  : none
 * RETURN  : returns a non-zero value if CharIn is a digit character   
 */
RVCOREAPI 
RvInt RVCALLCONV __cdecl isdigit(
	IN RvInt CharIn);

/********************************************************************************************
 * isalnum - checks if input character is a alphanumeric character
 *
 * INPUT   : CharIn		- character to be checked
 * OUTPUT  : none
 * RETURN  : returns a non-zero value if CharIn is a alphanumeric character   
 */
RVCOREAPI 
RvInt RVCALLCONV __cdecl isalnum(
	IN RvInt CharIn);

/********************************************************************************************
 * strspn - Find the first substring
 *
 * INPUT   : s1		- Null-terminated string to search 
 *			 s2		- Null-terminated character set 
 * OUTPUT  : none
 * RETURN  : an integer value specifying the length of the substring in s1   
 */
RVCOREAPI 
RvSize_t RVCALLCONV __cdecl strspn(
	IN const RvChar * s1, 
	IN const RvChar * s2);

#endif

/* Sorting functions */
#define RvQsort qsort

/* File Operation */
#if (RV_OS_TYPE == RV_OS_TYPE_RTK)
#define RvFopen(a, b) VT_RvVTFopen(a,b)
#define RvFclose(a) VT_RvVTFclose(a)
#define RvFgets(buffer, size, file_ptr) VT_RvVTFgets(buffer, size, file_ptr)
#define RvFwrite(buffer, size, c, file_ptr) VT_RvVTFwrite(buffer, size, c, file_ptr)
#define RvFflush(file_ptr) VT_RvVTFflush(file_ptr)
#define RvFseek(file_ptr, b, c) VT_RvVTFseek(file_ptr, b, c)
#define fflush(file_ptr) VT_RvVTFflush(file_ptr)

#define RvSprintf(buf, y, ...) mdl_vt_stack_RvSprintf(buf, y, ##__VA_ARGS__)
#else
#if (RV_OS_TYPE != RV_OS_TYPE_NUCLEUS) && (RV_OS_TYPE != RV_OS_TYPE_PSOS)
#define RvFopen   fopen
#define RvFreopen freopen
#define RvFlush   fflush
#define RvFclose  fclose
#define RvRemove  remove
#define RvRename  rename
#define RvTmpfile tmpfile
#define RvTmpnam  tmpnam
#define RvSetvbuf setvbuf
#define RvSetbuf  setbuf
#else
#define RvFopen(a, b) NULL
#define RvFclose(a) RvEOF
#endif
#endif

/* Formatted Output */
#define RvVprintf vprintf
#define RvVfprintf vfprintf
#define RvFprintf fprintf
#if (RV_STDIO_TYPE == RV_STDIO_OSE_DEBUG)
#include <dbgprintf.h>
#define RvPrintf dbgprintf
#elif (RV_STDIO_TYPE == RV_STDIO_WINCE_DEBUG)

/********************************************************************************************
 * RvOutputDebugPrintf - De-initializes the stdio module.
 *
 * INPUT   : format		- printf style format
 *			 ...		- printf style parameters that match format
 * OUTPUT  : none
 * RETURN  : lenght of string that was printed
 */
RVCOREAPI 
RvInt RVCALLCONV RvOutputDebugPrintf(
	IN const RvChar		*format,
	IN					...);

#define RvPrintf RvOutputDebugPrintf
#else
#define RvPrintf printf
#define RvOutputDebugPrintf( a ) OutputDebugString((LPCTSTR)a)
#endif


#if ( RV_OS_TYPE == RV_OS_TYPE_RTK )
/* Formatted Input */
#define RvFscanf NULL
/* Character Input ans Output Functions */
#define RvFgetc NULL
//#define RvFgets NULL
#define RvFputc NULL
#define RvFputs NULL
#define RvGetc NULL
#define RvGetchar NULL
#define RvGets NULL
#define RvPutc NULL
#define RvPutchar NULL
#define RvPuts NULL
#define RvUngetc NULL

/* Direct Input and Output Functions */
#define RvFread  NULL
//#define RvFwrite NULL
#else
/* Formatted Input */
#define RvFscanf fscanf
/* Character Input ans Output Functions */
#define RvFgetc fgetc
#define RvFgets fgets
#define RvFputc fputc
#define RvFputs fputs
#define RvGetc getc
#define RvGetchar getchar
#define RvGets gets
#define RvPutc putc
#define RvPutchar putchar
#define RvPuts puts
#define RvUngetc ungetc

/* Direct Input and Output Functions */
#define RvFread  fread
#define RvFwrite fwrite
#endif

/* File Positioning Functions */
#if (RV_OS_TYPE != RV_OS_TYPE_NUCLEUS) && (RV_OS_TYPE != RV_OS_TYPE_PSOS)
#if ( RV_OS_TYPE != RV_OS_TYPE_RTK )
#define RvFseek   fseek
#endif
#define RvFtell   ftell
#define RvRewind  rewind
#define RvFgetpos fgetpos
#define RvFsetpos fsetpos
#else
RvInt RvFseek(RvFILE *stream, long offset, RvInt origin);
#define RvFtell(a)       -1L
#endif

/* Error Functions */
#define RvClearerror clearerror
#define RvFeof       feof
#define RvFerror     ferror
#define RvPerror     perror

#elif (RV_STDIO_TYPE == RV_STDIO_STUB)
#include <stdarg.h>

/* Data Types */
#define RvFILE    RvInt
#define RvFpos_t  RvInt

/* Standard Streams */
#define RvStderr (RvFILE*)0
#define RvStdout (RvFILE*)1
#define RvStdin  (RvFILE*)2

/* Constants */
#define RvEOF -1
#define RvL_tmpnam 32

/* Sorting functions */
#define RvQsort qsort

/* File Operation */
RvFILE* RvFopen(const RvChar* filename, const RvChar* mode);
RvFILE* RvFreopen(const RvChar* filename, const RvChar* mode, RvFILE* stream);
RvInt RvFlush(RvFILE* stream);
RvInt RvFclose(RvFILE* stream);
RvInt RvRemove(const RvChar* filename);
RvInt RvRename(const RvChar* oldname, const RvChar* newname);
RvFILE* RvTmpfile(void);
RvChar* RvTmpnam(RvChar s[RvL_tmpnam]);
RvInt RvSetvbuf(RvFILE stream, RvChar* buf, RvInt mode, RvSize_t size);
void RvSetbuf(RvFILE stream, RvChar* buf);

/* Formatted Output */

/********************************************************************************************
 * RvPrintf - This function implements an ANSI printf style function.
 *
 * INPUT   : format	- A fprintf style format string.
 *			 ...	- A variable argument list.
 * OUTPUT  : none
 * RETURN  : The number of characters written, or negative if an error occured.   
 */
RVCOREAPI 
RvInt RVCALLCONV RvPrintf(
	IN const RvChar	*format, 
	INT				...);

/********************************************************************************************
 * RvFprintf - This function implements an ANSI fprintf style function.
 *
 * INPUT   : stream	- The stream to which to write 
 *			 format	- A fprintf style format string.
 *			 ...	- A variable argument list.
 * OUTPUT  : none
 * RETURN  : The number of characters written, or negative if an error occured.   
 */
RVCOREAPI RvInt RVCALLCONV RvFprintf(
	IN RvFILE			* stream, 
	IN const RvChar		*format, 
	IN					...);

/********************************************************************************************
 * RvVprintf - This function implements an ANSI vprintf style function.
 *
 * INPUT   : format	- A fprintf style format string.
 *			 ...	- A variable argument list.
 * OUTPUT  : none
 * RETURN  : The number of characters written, or negative if an error occured.   
 */
RVCOREAPI RvInt RVCALLCONV RvVprintf(
	IN const RvChar	*format,
	IN va_list		arg);

/********************************************************************************************
 * RvVfprintf - This function implements an ANSI vfprintf style function.
 *
 * INPUT   : stream - The stream to which to write
 *			 format - A vfprintf style format string.
 *			 arg	- A variable argument list.
 * OUTPUT  : none
 * RETURN  : The number of characters written, or negative if an error occured.
 */
RVCOREAPI RvInt RVCALLCONV RvVfprintf(
	IN RvFILE		*stream, 
	IN const RvChar	*format,
	IN va_list		arg);

/* Formatted Input */
/********************************************************************************************
 * RvFscanf - This function implements an ANSI fscanf style function.
 *
 * INPUT   : stream	- The stream from which to read input.
 *			 format	- A sscanf style format string.
 *			 ...	- A variable argument list.
 * OUTPUT  : none
 * RETURN  : The number input items converted, or RvEOF if an error occured.   
 */
RvInt RvFscanf(
	IN RvFILE		*stream, 
	IN const RvChar	*format,
	INT				...);

/********************************************************************************************
 * RvScanf - This function implements an ANSI scanf style function.
 *
 * INPUT   : format	- A sscanf style format string.
 *			 ...	- A variable argument list.
 * OUTPUT  : none
 * RETURN  : The number input items converted, or RvEOF if an error occured.   
 */
RvInt RvScanf(
	IN const RvChar	*format,
	INT				...);

/* Character Input ans Output Functions */
RvInt RvFgetc(RvFILE* stream);
RvChar* RvFgets(RvChar* s, RvInt n, RvFILE* stream);
RvInt RvFputc(RvInt c, RvFILE* stream);
RvInt RvFputs(const RvChar* s, RvFILE* stream);
RvInt RvGetc(RvFILE* stream);
RvInt RvGetchar(void);
RvChar* RvGets(RvChar* s);
RvInt RvPutc(RvInt c, RvFILE* stream);
RvInt RvPutchar(RvInt c);
RvInt RvPuts(const RvChar* s, RvFILE* stream);
RvInt RvUngetc(RvInt c, RvFILE* stream);

/* Direct Input and Output Functions */
RvSize_t RvFread(void* ptr, RvSize_t size, RvSize_t nobj, RvFILE* stream);
RvSize_t RvFwrite(const void* ptr, RvSize_t size, RvSize_t nobj, RvFILE* stream);

/* File Positioning Functions */
RvInt RvFseek(RvFILE* stream, long offset, RvInt origin);
long RvFtell(RvFILE* stream);
void RvRewind(RvFILE* stream);
RvInt RvFgetpos(RvFILE* stream, RvFpos_t* ptr);
RvInt RvFsetpos(RvFILE* stream, const RvFpos_t* ptr);

/* Error Functions */
void RvClearerror(RvFILE* stream);
RvInt RvFeof(RvFILE* stream);
RvInt RvFerror(RvFILE* stream);
void RvPerror(const RvChar* s);

#endif

/********************************************************************************************
 * RvBsearch - Binary search function
 *
 * INPUT   : key
 *			 base
 *			 numOfElements
 *			 elementSize
 *			 compareFunc
 * OUTPUT  : none
 * RETURN  : pointer to found element or NULL
 */
RVCOREAPI void* RVCALLCONV RvBsearch(
    IN const void*     key,
    IN const void*     base,
    IN RvSize_t        numOfElements,
    IN RvSize_t        elementSize,
    IN RvInt (*compareFunc)(const void* key, const void* ));

#ifdef __cplusplus
}
#endif

#endif  /* Include guard */

