#ifndef DRV_MFD_PUB_H
#define DRV_MFD_PUB_H

int MVC_API vidInitDecoder_hantro(int *handle, VID_SETUP *setup, uint8_t *decbuf, int *p_decbuf_size);
int MVC_API vidDecFrame_hantro(int handle, VID_SETUP *setup, VID_PICTURE *pic);
int MVC_API vidGetLastFrame_hantro(int handle, VID_SETUP *setup, VID_PICTURE *pic);
int MVC_API vidFiniDecoder_hantro(int handle);
#endif //DRV_MFD_PUB_H