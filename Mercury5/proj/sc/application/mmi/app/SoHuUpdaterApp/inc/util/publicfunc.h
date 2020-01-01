#ifndef SG_PUBBLICFUNC__H__
#define SG_PUBBLICFUNC__H__

#include "mmi_mae_resource.h"

#define   SG_SUCCESS        0
#define   SG_FAILED        -1

#define   SG_UINT8      u8
#define   SG_INT8       s8
#define   SG_UINT16     u16
#define   SG_INT16      s16
#define   SG_UINT32     u32
#define   SG_INT32      s32

#define   SG_MEMSET     memset
#define   SG_MEMCPY     memcpy
#define   SG_MEMCMP     memcmp
#define   SG_MALLOC     MALLOC
#define   SG_FREE       FREE
#define   SG_STRLEN     strlen
#define   SG_STRCPY     strcpy
#define   SG_STRCAT     strcat
#define   SG_STRSTR     strstr
#define   SG_STRCHR     strchr
#define   SG_SPRINTF    sprintf
#define   SG_WSTRCAT    wcscat
//#define   SG_GETUTCSEC  GETUTCSECONDS

#define   SG_DATATIME_LEN        15

extern void	        SG_STRLEFT(unsigned char*, unsigned char, unsigned char*, unsigned char);
extern void	        SG_STRRIGHT(unsigned char*, unsigned char, unsigned char*, unsigned char);
extern char*        SG_STRRCHR(const char *, int);
extern void         SG_B2C(char *source, char *dest, int);
extern char         SG_UTF8_TO_UCS2(unsigned short *, unsigned char *);
extern char         SG_UTF8_TO_UCS2_STRING(unsigned char *, int, unsigned char *);
extern void         SG_GET_DATATIME(char *);
extern int         SG_MEMBLURCMP(char *,const char *,int);
#endif
