#ifndef _MMIOAPI_H_
#define _MMIOAPI_H_

//#include <cyg/infra/diag.h>

#ifdef __cplusplus
extern "C" {
#endif

    //RIU access
    int MMIO_RIURead16(unsigned short addr, unsigned short* pData);
    int MMIO_RIUWrite16(unsigned short addr, unsigned short data);

    //MIU access
    int MIURead(char* dstBuf, int dstLen, unsigned long addr, int endian/*, char* pbuf*/);
    int MIUWrite(char* srcBuf, int srcLen, unsigned long addr, int endian/*, BYTE* pbuf*/);
#ifdef __cplusplus
}
#endif

#endif
