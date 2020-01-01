#ifndef FW_PORTING_H
#define FW_PORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif    /* end of #ifdef __cplusplus */

void fw_printf( const char * format , ...);
void fw_sprintf_s( char *buf, size_t sizeOfBuffer, const char * format , ...);

#ifdef __cplusplus
 }
 #endif    /* end of #ifdef __cplusplus */

#endif
