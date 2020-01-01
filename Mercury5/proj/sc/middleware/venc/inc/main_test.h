
#ifndef _MAIN_TEST_H_
#define _MAIN_TEST_H_

#ifdef IOCTL_TEST
#define MIU_OFFSET 0xa0000000
#else
#define MIU_OFFSET 0x00000000
#endif


#define CODED_BUF_SIZE (40*1024)
#define CODED_FRAME_SIZE (128*1024)
#define SWENC_GBUF_SIZE (512*1024)
#define MAX_INT_VALUE 0x7fffffff


#ifdef MIPSDEV
#include "utility.h"
#include "mstar_api.h"

#define MYFILE int
#define fopen(file, a) fs_open(file, O_RDWR|O_CREAT)
#define fclose close
#define fwrite(buf, unit, size, file) write(file, buf, size*unit)
#define fread(buf, unit, size, file) read(file, buf, size*unit)
#define FOPEN_FAIL(x) ((x)<0)
#define clock_t uint32_t //unsigned long

#elif defined(WIN32)

#define MYFILE FILE*
#define FOPEN_FAIL(x) ((x)==0)

#else

#define MYFILE FILE*
#define FOPEN_FAIL(x) ((x)==0)

#endif

#endif

