#ifndef __NEMOMP_STANDARD_H__
#define __NEMOMP_STANDARD_H__

#include <stdarg.h>
#include "nemomp.h"

#ifndef NULL
#ifdef __cplusplus
#define NULL    (0)
#else
#define NULL    ((void *)0)
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

char* nemomp_strcat (char* dst, const char* str);
char* nemomp_strchr(const char *str, int c); // 20081128: Changed
char* nemomp_strrchr(const char *str, int c); // 20091209: Changed
int nemomp_strcmp(const char *str1, const char *str2);

char* nemomp_strcpy(char *str1, const char *str2);
///nemomp_strcspn X
///nemomp_stricmp X
int nemomp_strlen(const char *str);
char* nemomp_strncat(char *str1, const char *str2, int n);
int nemomp_strncmp(const char *str1, const char *str2, int n);
///nemomp_strnicmp X
char* nemomp_strncpy(char *str1, const char *str2, int n);
///nemomp_strspn X
char* nemomp_strtok(char *str1, const char *str2);
//nemomp_strtol X

void nemomp_printf(char *fmt, ...);

int nemomp_sprintf(char* buffer, char *fmt, ...);

int nemomp_vsprintf(char *str, const char *format, va_list arg);
///nemomp_sscanf X
int nemomp_memcmp(const void *str1, const void *str2, int n);
void* nemomp_memcpy(void *str1, const void *str2, int n);
void* nemomp_memmove(void *str1, const void *str2, int n);
void* nemomp_memset(void *str, int c, int n);
int nemomp_atoi(char* string);
///nemomp_isdigit X
void nemomp_itoa(char *dec_buffer, unsigned int dec); // 20081124: Added
///nemomp_isascii X

#ifdef __JAVA_JTWI__
#define nemomp_sscanf	sscanf // 20090218: Added
#endif

// 20081128: Added
#define NM_IS_SPACE(c) ((c) == ' ' || (c) == '\r' || (c) == '\n' || (c) == '\t')
#define NM_GET_PROP_BUFFER_SIZE		(15000)

// 20081128: Added
char* nemomp_get_prop(char* textBuf, char* name, int* length, char * operationBuffer) ;

#ifdef __cplusplus
}
#endif

#endif /* __NEMOMP_STANDARD_H__ */

