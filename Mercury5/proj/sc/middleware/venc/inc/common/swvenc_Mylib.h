#ifndef __MYLIB_H_
#define __MYLIB_H_

#include "swvenc_deftypes.h"

#define SAFE_RELEASE(x) { if (x!=NULL) x->Release(); x = NULL; }
#define SAFE_DELETE(x) { if (x!=NULL) delete x; x = NULL; }
#define SAFE_DELETE_ARRAY(x) { if (x!=NULL) delete [] x; x = NULL; }
#define SAFE_CLOSEHANDLE(x) { if (x!=NULL) ::CloseHandle(x); x = NULL; }
#ifdef MIPSDEV
#define SAFE_FREE(x)
#else
#define SAFE_FREE(x) { if (x!=NULL) free(x); x = NULL; }
#endif

static ALWAYSINLINE uint32 bswap(uint32 x)
{
    return ((x >> 24) | ((x & 0x00ff0000) >> 8) | ((x & 0x0000ff00) << 8) | (x << 24));
}

static ALWAYSINLINE int swvenc_log2(int P)
{
	int n=0;
	while (P>0)
	{
		n++;
		P = P>>1;
	}
	return n;
}

#endif
