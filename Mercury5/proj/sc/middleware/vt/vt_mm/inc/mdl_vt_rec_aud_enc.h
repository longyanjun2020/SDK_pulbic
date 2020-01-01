#ifndef _MDL_VT_REC_AUD_ENC_H_
#define _MDL_VT_REC_AUD_ENC_H_

#define VT_MAR_AMR_HEAP_BUFSIZE 7680


int MdlVtRec_AudEncClose(void);
int MdlVtRec_AudEncOpen(void);
void MdlVtRec_RegAudEncCallback(u16 (*fn)(u8* buf, u16 buf_size, S32 type));
void MdlVtRec_UnRegAudEncCallback(void);
void MdlVtRec_AvpRawAudCallback(void *buf, int buf_size);


#endif

