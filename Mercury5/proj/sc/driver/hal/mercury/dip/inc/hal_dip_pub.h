#ifndef __HAL_DIP_PUB_H_
#define __HAL_DIP_PUB_H_

// Macro
#define NULL                    ((void *)0)
#define DIP_INVALID_HANDLE      (NULL)
#define DIP_RET_FAIL            (0)
#define DIP_RET_SUCCESS         (1)
#define FALSE                   (0)
#define TRUE                    (1)

// Data type
typedef int             BOOL;
typedef void*           HDIP;

// Enum
typedef enum
{
    DIP_COLOR_FORMAT_YUV420 = 0,
    DIP_COLOR_FORMAT_YUV420_TILE16X32 = 1,
    DIP_COLOR_FORMAT_YUV420_TILE32X16 = 2,
    DIP_COLOR_FORMAT_YUV420_TILE32X32 = 3,
    DIP_COLOR_FORMAT_YUV422 = 4,
    DIP_COLOR_FORMAT_UNSUPPORT
} DIPCOLORFORMAT_e;

typedef enum
{
    DIP_ROTATE_0 = 0,
    DIP_ROTATE_90 = 1,
    DIP_ROTATE_270 = 2,
    DIP_ROTATE_UNSUPPORT
} DIPROTATE_e;

// Callback
typedef void    (*PfnDipCallback) (unsigned int param1, unsigned int param2);

#endif //__HAL_DIP_PUB_H_
