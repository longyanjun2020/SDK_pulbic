#ifndef UDMA_API_H
#define UDMA_API_H

#ifdef _BCB_
#include <vcl.h>
#elif defined(_WIN32)
#include <windows.h>
#endif
#include <stdio.h>

#ifdef __cplusplus 
extern "C" {
#endif
void initUDMA(char *name, int addr, int filelen);
BOOL rreg16(int banknum, int addrori, unsigned short *data);
BOOL wreg16(int banknum, int addrori, int data);
BOOL udma_get(int addr, int size, char *dstbuf);
BOOL udma_put(int addr, int size, char *dstBuf);
#ifdef __cplusplus 
}
#endif

#define wreg(bank, addr, val) wreg16(bank, addr, val)
#define rreg(bank, addr, val) rreg16(bank, addr, &val)


#endif // UDMA_API_H
