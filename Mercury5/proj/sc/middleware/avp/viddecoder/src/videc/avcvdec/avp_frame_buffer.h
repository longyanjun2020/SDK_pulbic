#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
/**************************************************
	This file contains operations on frame buffer.
 **************************************************/
#include "avp_defines.h"
#include "avp_mbuffer.h"
#include "avp_avcPrivate.h"

/* for vidInitDecoder() */
void reset_storable_picture(DecodedPictureBuffer *pdpb, uint8 num_ref_frames);
StorablePicture* alloc_storable_picture(PictureStructure structure,
                                        int size_x, int size_y,
                                        int size_x_cr, int size_y_cr,
                                        uint8 *decbuf, int decbuf_Size, int *totalused,
                                        avc_header* hdra,
                                        AVC_HANDLE* hp);
int init_global_buffers(AVC_HANDLE *hp,	unsigned char *decbuf, int decbuf_Size, int *totalused);

/* for vidDecFrame() */
void fill_frame_num_gap(AVC_HANDLE *hp, avc_header *hdra);
void init_reorder_lists(avc_header *hdra, mcRemappedCommand *p_rmc_f, mcRemappedCommand *p_rmc_b, unsigned int reordering_flag[2]);
void idr_flush_dpb(avc_header* hdra, int offsetFlag_Y);
void avcGetFrame(VID_HANDLE *hp, VID_PICTURE *pic);

#endif
