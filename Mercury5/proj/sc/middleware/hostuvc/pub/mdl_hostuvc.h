
#ifndef _MDL_HOST_UVC_H_
#define _MDL_HOST_UVC_H_

#include "drvUSBHost.h"

int 				uvcl_init(void);
void 				uvcl_cleanup(void);
void 				uvcl_check_iso_frame_status(struct urb *urb,int Index);
struct urb * 		uvcl_get_single_urb(void);
void 				uvcl_set_single_urb(struct urb * urb);
void 				uvcl_streaming_enable(bool en);
void 				uvcl_trigger_urb(u32 ulStartAddr);
int 				uvcl_get_VIDPID(unsigned char bEndian,void * pDstaddr);
unsigned char 		uvcl_find_entity_id_by_type(unsigned short type);
unsigned char 		uvcl_find_interface_num(unsigned char subclass);
int 				uvcl_control_transfer(unsigned char reqtype, unsigned char query,\
											unsigned short idx, unsigned short val,\
											void *data, unsigned short size);
int 				uvcl_is_mdl_done(void);
void 				uvcl_process_URB(bool bISOMode);
#endif /* _MDL_HOST_UVC_H_ */
