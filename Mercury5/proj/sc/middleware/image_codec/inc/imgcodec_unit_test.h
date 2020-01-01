#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

#ifndef _IMGCODEC_UNIT_TEST_H_
#define _IMGCODEC_UNIT_TEST_H_

void *imageCodec_malloc_test(u32 size);
void imageCodec_free_test(void *ptr);
void imageCodec_autoTest(u16 *launcher);

#endif
#endif

