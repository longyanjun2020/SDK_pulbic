//-----------------------------------------------------------------------------
//Include Files
//-----------------------------------------------------------------------------

#ifndef _STREAMBUF_H
#define _STREAMBUF_H

//#include <sys/bsdtypes.h>
//#include <cyg/kernel/kapi.h>
//#include <cyg/infra/diag.h>
//#include <cyg/hal/plf_intr.h>
//#include "msmcomm.h"
#include "vm_types.ht"

//#include "sys_rtk_vmrtkho.h"
//#include "vm_stdio.ho"
#include "sys_vm_dbg.ho"
#include "sys_traces.ho"
#include "ms_io.h"
#include "mdl_mmaudio_msmerror.h"

typedef struct _stream_ring_buf{
    s32 s32widx;
    u32 u32wcycle;
    u32 padding1[6]; // 32bytes aligned

    s32 s32ridx;
    u32 u32rcycle;
    u32 padding2[6]; // 32bytes aligned

    u8 *u32RingMMIBaseAddr;
    u8 *u32RingM3BaseAddr;

    s32 s32ringbufsize;
    u32 u32ringinit;
    u32 u32ring_off_t;
    s32 s32m3bufflag;
    s32 s32endflag;
    u32 padding3[1]; // 32bytes aligned

} stream_ring_buffer;

typedef enum
{
    RING_STREAM_FLAG_R   = 1,
    RING_STREAM_FLAG_W   = 2,
}RINGSTREAM_FLAG;

extern void fnStreamRingBufInit(u8 *baseaddr, u32 buflen, void *ring_ptr, u8 rwflag);
extern u32 fnPushStreamRingBuf(u8* PBuffer, s32 s32Len, void *ring_pptr);
extern u32 fnPopStreamRingBuf(u8* PBuffer, s32 s32Len, void *ring_pptr);
extern s32 fngetStreamBufSize(void *ring_pptr);
extern s32 fngetStreamFreeSize(void *ring_pptr);
extern s32 fncheckStreamEnd(void *ring_pptr);


#endif
