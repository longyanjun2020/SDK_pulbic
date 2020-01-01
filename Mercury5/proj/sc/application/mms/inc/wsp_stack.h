
#include <nccwsp.h>

#ifndef __WSP_STACK_H__
#define __WSP_STACK_H__

#ifdef __cplusplus
extern "C"{
#endif

#define wap_begin              NCCWsp_begin
#define Wap_SetTimeOut         NCCWsp_setMaxRcr
#define Wap_Peek_Ok            NCCWsp_peekReady
#define BeginToLoad            NCCWsp_get
#define PeekGetData            NCCWsp_peekGetData
#define Dwap_Send              NCCWsp_post
#define wap_exit               NCCWsp_exit
#define wap_setparam           NCCWsp_setParam
#define fnWap_GetRcvCount      NCCWsp_getRecvCount
#define fnWap_ResetTransCount  fnWAP_resetTransCount

#ifdef __cplusplus
}
#endif

#endif/* __WSP_STACK_H__ */

