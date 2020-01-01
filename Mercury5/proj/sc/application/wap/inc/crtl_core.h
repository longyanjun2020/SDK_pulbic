/**
 * @file
 *
 *
 * This file provides the default definitions for
 * functionality normally provided by the standard C
 * runtime library.
 * All CRTL_...() routines are redirected to the
 * equivalent C library ones, but a target platform
 * may override these definitions in its own <crtl_md.h>
 *
 * This file is included in all source files and includes
 * the machine dependent <crtl_core_md.h> which is expected to
 * supply prototypes for these procedures either through
 * inclusion of standard C library headers or its own
 * target specific prototypes/macros.
 *
 * If a macro is simply undefined by <crtl_md.h> then it
 * is assumed that the API concerned is to be implemented
 * directly as a C function; in this case a prototype
 * is supplied automatically by this file.
 *
 * The Dancing Bear gives a warning on unprotected use
 * of CRTL_ words. If you add a new CRTL_ word, you
 * should add the word to %badWord in db2.pl, e.g.
 *
 * "newword" => "CRTL",
 *
 * If the word is a function, but is also being used
 * elsewhere as a variable name, you can constrain
 * the Dancing Bear to only warn on function calls
 * with a trailing ( after the word, e.g.
 *
 * "newfunc(" => "CRTL",
 *
 * The Dancing Bear uses this to generate a regular
 * expression to do the match - it will catch function
 * usage with space between the word and the (. I.e.
 *
 * newfunc (args);
 *
 * will generate a warning.
 */

#ifndef CRTL_CORE_H
#define CRTL_CORE_H

#include <ven_file.h>
#include <ven_os.h>
#include <stdarg.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

//#define CRTL_assert(expression)         NCC_KERNEL_ASSERT((expression))
#define CRTL_assert(expression)
/*
 * ==================== ANSI style string operations ==========================
 */
#define CRTL_strlen(str)                ((int32_t)ven_std_strlen((const char *)(str)))
#define CRTL_strcpy(dst, src)           (ven_std_strcpy ((char *)(dst), (const char *)(src)))
#define CRTL_strncpy(dst, src, n)       (ven_std_strncpy ((char *)(dst), (const char *)(src), (n)))
#define CRTL_strcat(dst, src)           (ven_std_strcat ((char *)(dst), (const char *)(src)))
#define CRTL_strncat(dst, src, n)       (ven_std_strncat ((char *)(dst), (const char *)(src), (n)))
#define CRTL_strchr(str, c)             (int8_t *)(ven_std_strchr ((const char *)(str), (c)))
//#define CRTL_strrchr(str, c)            (strrchr ((str), (c)))
//#define CRTL_strerror(n)                (strerror (n))
#define CRTL_strcmp(s1, s2)             (ven_std_strcmp ((const char *)(s1), (const char *)(s2)))
#define CRTL_strcmpFunc                 ven_std_strcmp
#define CRTL_strncmp(s1, s2, n)         (ven_std_strncmp ((const char *)(s1), (const char *)(s2), (n)))
//#define CRTL_strnicmp(s1, s2, n)        (ven_std_strnicmp ((const char *)(s1), (const char *)(s2), (n)))
//#define CRTL_strcasecmp(s1, s2)       (strcasecmp ((s1), (s2)))
//#define CRTL_strstr(s1, s2)             (int8_t *)(ven_std_strstr ((const char *)(s1), (const char *)(s2)))
#define CRTL_strspn(s1, s2)             (ven_std_strspn((s1), (s2)))
#define CRTL_strcspn(s1, s2)            (ven_std_strcspn((s1), (s2)))
#define CRTL_strtol(str, ptr, base)     (ven_std_strtol((str), (ptr), (base)))
#define CRTL_strtoul(str, ptr, base)    (ven_std_strtol((str), (ptr), (base)))
// #define CRTL_strtoll( str, ptr, base)   (strtoll( (str), (ptr), (base)))
// #define CRTL_strtoull(str, ptr, base)   (strtoull((str), (ptr), (base)))
//#define CRTL_strdup(str)                (strdup((str)))

/* Wide characters operations */
#define CRTL_wstrcpy           ven_std_wstrcpy
#define CRTL_wcsncpy           ven_std_wstrncpy
#define CRTL_wcslen            ven_std_wstrlen
#define CRTL_wcscat            ven_std_wstrcat
#define CRTL_wcsncat           ven_std_wstrncat
#define CRTL_wcscmp            ven_std_wstrcmp
#define CRTL_wcsncmp           ven_std_wstrncmp
#define CRTL_wcsspn            ven_std_wstrspn
#define CRTL_wcscspn           ven_std_wstrcspn
#define CRTL_vswprintf         ven_std_vswprintf
#define CRTL_wcschr            ven_std_wstrchr
#define CRTL_wcstol            ven_std_wstrtol
#define CRTL_swprintf          ven_std_swprintf
#define CRTL_swscanf           ven_std_swscanf

/*
 * ============== ANSI style character classification/translation =============
 */
//#define CRTL_isalpha(c)                 (isalpha(c))
//#define CRTL_isalnum(c)                 (isalnum(c))
#define CRTL_isdigit(c)         (ven_std_isdigit((c)))
#define CRTL_isascii(c)         (ven_std_isascii((c)))
//#define CRTL_islower(c)                 (islower(c))
//#define CRTL_isspace(c)                 (isspace(c))
//#define CRTL_isupper(c)                 (isupper(c))
//#define CRTL_tolower(c)                 (tolower(c))
//#define CRTL_toupper(c)                 (toupper(c))
#define CRTL_atoi(str)                  (ven_std_atoi((const char *)(str)))
#define CRTL_atol(str)                  (ven_std_atoi(str))
#define CRTL_atof(str)                  (ven_std_atof(str))

/*
 * ==================== ANSI style memory operations ==========================
 */
#define CRTL_memcpy(dst, src, n)        (ven_std_memcpy ((dst), (src), (n)))
#define CRTL_memcmp(s1, s2, n)          (ven_std_memcmp ((s1), (s2), (n)))
#define CRTL_memmove(dst, src, n)       (ven_std_memmove ((dst), (src), (n)))
#define CRTL_memset(dst, v, n)          (ven_std_memset ((dst), (v), (n)))

/*
 * ==================== ANSI style memory allocation operations ===============
 */
#define CRTL_malloc(sz)         (NCCCommon_malloc(sz))
#define CRTL_free(ad)           (NCCCommon_free(ad))
#define CRTL_MMS_malloc(sz)         (ven_os_mem_malloc(sz))
#define CRTL_MMS_free(ad)           (ven_os_mem_free(ad))

#define CRTL_calloc(num, sz)    (NCCCommon_calloc((num), (sz)))
#define CRTL_freeFunc                   ven_os_mem_free
extern void * NCCCommon_malloc(uint32_t size);
extern void NCCCommon_free(void * mem);


extern void *NCCPort_os_realloc(void *ptr, int32_t size);
#define CRTL_realloc(ptr, size)     (NCCPort_os_realloc((ptr), size))

#define CRTL_offsetof   offsetof
/*
 * ==================== Stream operations =====================================
 */
#define CRTL_feof(stream)               (ven_file_wfeof((stream)))
#define CRTL_fopen(filename, type)      (fopen((filename), (type)))
#define CRTL_fclose(stream)             (fclose(stream))
#define CRTL_fdopen(fd, mode)           (fdopen((fd), (mode)))

#define CRTL_fflush(stream)             (fflush(stream))
#define CRTL_fgetc(stream)              (fgetc(stream))
#define CRTL_fgets(s, n, stream)        (fgets((s), (n), (stream)))
#define CRTL_fileno(stream)             (fileno(stream))
#define CRTL_fprintf                    NCCPort_os_traceStr
#define CRTL_fputc(c, stream)           (fputc((c), (stream)))
#define CRTL_fputs(s, stream)           (fputs((s), (stream)))
#define CRTL_fread(ptr, size, nitems, stream) (fread((ptr), (size), (nitems), (stream)))
#define CRTL_fseek(stream, offset, ptrname) ven_file_fseek((stream), (offset), (ptrname))
#define CRTL_ftell(stream)              (ven_file_ftell((stream)))
#define CRTL_fwrite(ptr, size, nitems, stream) (fwrite((ptr), (size), (nitems), (stream)))
#define CRTL_printf                     NCCPort_os_traceStr
#define CRTL_putw(w, stream)            (putw((w), (stream)))
#define CRTL_puts(s)                    (puts(s))
#define CRTL_setvbuf(stream, buf, mode, size) (setvbuf((stream), (buf), (mode), (size)))
#define CRTL_IONBF                      _IONBF
#define CRTL_IOLBF                      _IOLBF
#define CRTL_sprintf                    ven_std_sprintf
#define CRTL_sscanf                     ven_std_sscanf
#define CRTL_vprintf                    vprintf
#define CRTL_vfprintf                   vfprintf
#define CRTL_vsprintf                   ven_std_vsprintf
#define CRTL_vsscanf                    vsscanf

#define CRTL_stdin                      stdin
#define CRTL_stdout                     stdout
#define CRTL_stderr                     stderr

// TODO: should delete the following macros
#define CRTL_va_start(args, format)		va_start((args), (format))
#define CRTL_va_end(args)				va_end((args))
#define CRTL_va_arg(args, ptr)          va_arg((args), ptr)
#define CRTL_isxdigit(c) (((c) >= 'A' && (c) <= 'F') || ((c) >= 'a' && (c) <= 'f') || ((c) >= '0' && (c) <= '9'))
/*
 * ==================== varargs argument processing ===========================
 */
/* On some systems (e.g. Linux/PPC) the object defined by "va_list ap;"
 * cannot be simply copied and restored (or passed as an argument to
 * a function) to undo any effect of va_arg(). It may be a pointer to
 * a structure and the va_arg() may have changed state in that
 * structure. We use a CRTL_va_copy to cater for this strange case.
 *
 * CRTL_va_init is used in initialise a va_list in the rare case where we
 * don't use va_start or CRTL_va_copy (usually when the value is known not to
 * be used).
 */

#define CRTL_va_copy(a,b)       (a) = (b)
#define CRTL_va_init(a)         (a) = NULL

/*
 * ==================== Miscellaneous operations ==============================
 */
#define CRTL_getErrno()                 (errno)
#define CRTL_setErrno(val)              do { errno = (val); } while (0)
#define CRTL_jmp_buf                    jmp_buf
#define CRTL_setjmp(env)                (setjmp(env))
#define CRTL_longjmp(env, val)          (longjmp((env), (val)))
#define CRTL_perror(s)                  (perror(s))
//#define CRTL_qsort(arr, n, siz, comp)             (qsort((arr), (n), (siz), (comp)))

/* ==========================================================================*/
/*                      CRTL PROTOTYPES                                      */
/* ==========================================================================*/

/*
 * If a CRTL macro is undefined (and not redefined) by crtl_md.h, the
 * corresponding default function prototype is supplied below
 */

/*
 * ==================== ANSI style string operations ==========================
 */
#ifndef CRTL_strlen
extern size_t CRTL_strlen(const char *str);
#endif

#ifndef CRTL_strcpy
extern char *CRTL_strcpy(char *dst, const char *src);
#endif

#ifndef CRTL_strncpy
extern char *CRTL_strncpy(char *dst, const char *src, size_t nchars);
#endif

#ifndef CRTL_strcat
extern char *CRTL_strcat(char *dst, const char *src);
#endif

#ifndef CRTL_strncat
extern char *CRTL_strncat(char *dst, const char *src, size_t nchars);
#endif

#ifndef CRTL_strchr
extern char *CRTL_strchr(const char *str, int c);
#endif

#ifndef CRTL_strrchr
extern int8_t *CRTL_strrchr(const int8_t *str, int c);
#endif

#ifndef CRTL_strerror
extern char *CRTL_strerror(int errnum);
#endif

#ifndef CRTL_strcmp
extern int CRTL_strcmp(const char *s1, const char *s2);
#endif

#ifndef CRTL_strncmp
extern int CRTL_strncmp(const char *s1, const char *s2, size_t nchars);
#endif

#ifndef CRTL_strnicmp
extern int CRTL_strnicmp(const int8_t *s1, const int8_t *s2, size_t nchars);
#endif

#ifndef CRTL_strcasecmp
extern int CRTL_strcasecmp(const char *s1, const char *s2);
#endif

#ifndef CRTL_strstr
extern int8_t *CRTL_strstr(const int8_t *s1, const int8_t *s2);
#endif

#ifndef CRTL_strspn
extern size_t CRTL_strspn(const char *s1, const char *s2);
#endif

#ifndef CRTL_strcspn
extern size_t CRTL_strcspn(const char *s1, const char *s2);
#endif

#ifndef CRTL_strtol
extern long CRTL_strtol(const char *str, char **ptr, int base);
#endif

#ifndef CRTL_strtoul
extern unsigned long CRTL_strtoul(const char *str, char **ptr, int base);
#endif

#ifndef CRTL_strtoll
extern int64_t CRTL_strtoll(const char *str, char **ptr, int base);
#endif

#ifndef CRTL_strtoull
extern uint64_t  CRTL_strtoull(const char *str, char **ptr, int base);
#endif

#ifndef CRTL_strdup
extern  int8_t * CRTL_strdup(const int8_t *str);
#endif

/*
 * ============== ANSI style character classification/translation =============
 */
#ifndef CRTL_isalpha
extern int CRTL_isalpha(int c);
#endif

#ifndef CRTL_isalnum
extern int CRTL_isalnum(int c);
#endif

#ifndef CRTL_isdigit
extern int CRTL_isdigit(int c);
#endif

#ifndef CRTL_islower
extern int CRTL_islower(int c);
#endif

#ifndef CRTL_isspace
extern int CRTL_isspace(int c);
#endif

#ifndef CRTL_isupper
extern int CRTL_isupper(int c);
#endif

#ifndef CRTL_tolower
extern int CRTL_tolower(int c);
#endif

#ifndef CRTL_toupper
extern int CRTL_toupper(int c);
#endif

#ifndef CRTL_atoi
extern  int32_t CRTL_atoi(const char *str);
#endif

/*
 * ==================== ANSI style memory operations ==========================
 */
#ifndef CRTL_memcpy
extern void *CRTL_memcpy(void *dst, const void *src, size_t nchars);
#endif

#ifndef CRTL_memcmp
extern int CRTL_memcmp(const void *s1, const void *s2, size_t nchars);
#endif

#ifndef CRTL_memmove
extern void *CRTL_memmove(void *dst, const void *src, size_t nchars);
#endif

#ifndef CRTL_memset
extern void *CRTL_memset(void *dst, int value, size_t nbytes);
#endif

/*
 * ==================== ANSI style memory allocation operations ===============
 */
#ifndef CRTL_malloc
extern void *CRTL_malloc(size_t size);
#endif

#ifndef CRTL_free
extern void CRTL_free(void *ptr);
#endif

#ifndef CRTL_calloc
extern void *CRTL_calloc(size_t num, size_t size);
#endif

/*
 * ==================== Stream operations =====================================
 */
#ifndef NO_CRTL_STREAMS
#ifndef CRTL_fopen
extern FILE *CRTL_fopen(const char *filename, const char *type);
#endif

#ifndef CRTL_fclose
extern int CRTL_fclose(FILE *stream);
#endif

#ifndef CRTL_fdopen
extern FILE *CRTL_fdopen(int fildes, const char *type);
#endif

#ifndef CRTL_fflush
extern PUBLICSYMBOL int CRTL_fflush(FILE *stream);
#endif

#ifndef CRTL_fgetc
extern int CRTL_fgetc(FILE *stream);
#endif

#ifndef CRTL_fgets
extern char *CRTL_fgets(char *s, int n, FILE *stream);
#endif

#ifndef CRTL_fileno
extern int CRTL_fileno(FILE *stream);
#endif

#ifndef CRTL_fprintf
extern PUBLICSYMBOL int CRTL_fprintf(FILE *stream, const char *fmt, ...);
#endif

#ifndef CRTL_fputc
extern int CRTL_fputc(int c, FILE *stream);
#endif

#ifndef CRTL_fputs
extern int CRTL_fputs(const char *s, FILE *stream);
#endif

#ifndef CRTL_fread
extern size_t CRTL_fread(void *ptr, size_t size, size_t nitems, FILE *stream);
#endif

#ifndef CRTL_fseek
extern int CRTL_fseek(FILE *stream, long offset, int ptrname);
#endif

#ifndef CRTL_ftell
extern long CRTL_ftell(FILE *stream);
#endif

#ifndef CRTL_fwrite
extern size_t CRTL_fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream);
#endif

#ifndef CRTL_printf
extern PUBLICSYMBOL int CRTL_printf(const char *fmt, ...);
#endif

#ifndef CRTL_putw
extern int CRTL_putw(int w, FILE *stream);
#endif

#ifndef CRTL_puts
extern int CRTL_puts(const char *s);
#endif

#ifndef CRTL_setvbuf
extern int CRTL_setvbuf(FILE *stream, char *buf, int type, size_t size);
#endif

#ifndef CRTL_vprintf
extern PUBLICSYMBOL int CRTL_vprintf(const char *fmt, va_list ap);
#endif

#ifndef CRTL_vfprintf
extern PUBLICSYMBOL int CRTL_vfprintf(FILE *stream, const char *fmt, va_list ap);
#endif

#ifndef CRTL_stdin
extern FILE *CRTL_stdin;
#endif

#ifndef CRTL_stdout
extern FILE *CRTL_stdout;
#endif

#ifndef CRTL_stderr
extern FILE *CRTL_stderr;
#endif

#endif

/*
 * ==================== Formatted string operations ==========================
 */

#ifndef CRTL_sprintf
extern PUBLICSYMBOL int CRTL_sprintf(char *s, const char *fmt, ...);
#endif

#ifndef CRTL_sscanf
extern PUBLICSYMBOL int CRTL_sscanf(const char *s, const char *fmt, ...);
#endif

#ifndef CRTL_vsprintf
extern PUBLICSYMBOL int CRTL_vsprintf(char *s, const char *fmt, va_list ap);
#endif

#ifndef CRTL_vsscanf
extern PUBLICSYMBOL int CRTL_vsscanf(const char *s, const char *fmt, va_list ap);
#endif

/*
 * ==================== varargs argument processing ===========================
 */
#ifndef CRTL_va_copy
extern void CRTL_va_copy(va_list dst, va_list src);
#endif
#ifndef CRTL_va_init
extern void CRTL_va_init(va_list a);
#endif

/*
 * ==================== Miscellaneous operations ==============================
 */
#ifndef CRTL_getErrno
extern int CRTL_getErrno();
#endif

#ifndef CRTL_setErrno
extern void CRTL_setErrno(int newVal);
#endif

#ifndef CRTL_setjmp
extern int CRTL_setjmp(CRTL_jmp_buf env);
#endif

#ifndef CRTL_longjmp
extern void CRTL_longjmp(CRTL_jmp_buf env, int val);
#endif

#ifndef CRTL_perror
extern void CRTL_perror(const char *msg);
#endif

#ifndef CRTL_qsort
extern void CRTL_qsort(void *base, int32_t num, int32_t width, int32_t(*compare)(const void *, const void *));

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* CRTL_CORE_H */

