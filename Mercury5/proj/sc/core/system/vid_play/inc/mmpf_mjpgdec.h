#ifndef _MMPF_MJPGDEC_H_
#define _MMPF_MJPGDEC_H_

#include "config_fw.h"
#include "mmpf_typedef.h"
#include "mmp_media_def.h"
#include "mmpf_media_struct.h"
#include "mmpf_viddec_def.h"

typedef struct _MMPF_DSC_DEC_MJPEG_BUFFER {

    MMP_ULONG  	ulDecompressStart;
    MMP_ULONG  	ulDecompressEnd;
    MMP_ULONG  	ulWidth;
    MMP_ULONG  	ulHeight;
} MMPF_DSC_DEC_MJPEG_BUFFER;

MMP_HANDLE MMPF_MJPGDEC_Open(MMPF_VIDEO_FUNC *func);

#endif
