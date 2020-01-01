#include "sys_MsWrapper_cus_os_mem.h"
#include <drvUSBHost.h>
#include <drvErrno.h>
#include <drvAPIWrapper.h>
#include "mdl_hostuvc_video.h"
#include "mmpf_usbh_ctl.h"

extern UVCH_XFER_CTL    uvch_xfer_ctl;
extern unsigned short   gusUVCRecdFrmBufCnt;

struct uvc_buffer _gUvcfrmbufInfo;

void uvcl_buffer_dump(struct uvc_buffer *buf, int size)
{
    unsigned int addr = (unsigned int)buf->mem;
    int i, j;

    diag_printf("[uvcl] address:%x error %d ->\n", addr, buf->error);
    for (i = 0; i < size ; i = i+16) {
        for (j = 0; j < 16; j++)
            diag_printf("%02x ", *(U8 volatile *)(addr + i+ j));
        diag_printf("\n");
    }
}

int uvcl_buffer_reset(void)
{
    struct uvc_buffer *buf;

    buf = uvcl_get_buffer();
    buf->bytesused = 0;
    buf->writeidx = 0;
    buf->state = UVC_BUF_STATE_READY;
    buf->error = 0;
    buf->FoundSOICnt = 0;
    buf->bframedrop = 0;
    INIT_LIST_HEAD(&buf->queue);
}
/* uvc lite, only raw buffer prepared */
int uvcl_buffer_prepare(struct uvc_buffer *buf, int size)
{
    if(size){

        buf->mem = MsAllocateMem(size);

        if(!buf->mem){
            diag_printf("Failed to allocate host uvc buffer size = %d \n", size);
            return -ENOMEM;
        }

        memset(buf->mem, 0, size);
        buf->length = size;
        buf->bytesused = 0;
        buf->state = UVC_BUF_STATE_READY;
        buf->error = 0;
        diag_printf("[J] uvc raw video buffer %p, size = %d\n", buf->mem, size);
    }
#if MDL_HOSTUVC_COPY_FULL_PACKET
    else {

        int idx;

        buf = uvcl_get_buffer();
        buf->bytesused = 0;
        buf->framesize = uvch_xfer_ctl.buf_ctl.ulBufSize;
        buf->writeidx = 0;
        buf->bufidx = 0;
        buf->FoundSOICnt = 0;
        buf->bframedrop = 0;

        for (idx = 0; idx < gusUVCRecdFrmBufCnt; idx++) {
            buf->pUVCFmrBufAddr[idx] = uvch_xfer_ctl.buf_ctl.ulBufAddr[idx] + UVC_PH_LEN;
        }

        buf->state = UVC_BUF_STATE_READY;
        buf->error = 0;
        INIT_LIST_HEAD(&buf->queue);
    }
#endif

    return 0;
}

struct uvc_buffer *uvcl_get_buffer(void)
{
    return &_gUvcfrmbufInfo;
}

struct uvc_buffer *uvc_queue_next_buffer(struct uvc_video_queue *queue,
        struct uvc_buffer *buf)
{
    struct uvc_buffer *nextbuf;
    unsigned long flags;

    // FIXME
    if (/*(queue->flags & UVC_QUEUE_DROP_CORRUPTED) &&*/ buf->error) {
        buf->error = 0;
        buf->state = UVC_BUF_STATE_QUEUED;
        buf->bytesused = 0;
        //vb2_set_plane_payload(&buf->buf, 0, 0);
        return buf;
    }

    spin_lock_irqsave(&queue->irqlock, flags);
    list_del(&buf->queue);
    if (!list_empty(&queue->irqqueue))
        nextbuf = list_first_entry(&queue->irqqueue, struct uvc_buffer,
                       queue);
    else
        nextbuf = NULL;
    spin_unlock_irqrestore(&queue->irqlock, flags);

    // FIXME
    //buf->state = buf->error ? VB2_BUF_STATE_ERROR : UVC_BUF_STATE_DONE;
    buf->state = UVC_BUF_STATE_DONE;

    return nextbuf;
}
