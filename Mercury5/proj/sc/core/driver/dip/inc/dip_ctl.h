#ifndef __DIP_CTL_H__
#define __DIP_CTL_H__

#if defined(__GNUC__)
#include "vm_types.ht"
#endif

// Macro
#define DIP_CTL_COLOR_DOMAIN            0x0F00
#define DIP_CTL_COLOR_YUV420            0x0100 & DIP_CTL_COLOR_DOMAIN
#define DIP_CTL_COLOR_YUV420_T16X32     0x0200 & DIP_CTL_COLOR_DOMAIN
#define DIP_CTL_COLOR_YUV422            0x0400 & DIP_CTL_COLOR_DOMAIN

// Enum
typedef enum
{
    DIP_ERR_NONE            = 0x0000,
    DIP_ERR_PARAMETER       = 0x0001,
    DIP_ERR_SEND_MSG        = 0x0002,
    DIP_ERR_GET_MSG         = 0x0004,
    DIP_ERR_CMD             = 0x0008,
    DIP_ERR_GET_INSTANCE    = 0x0010,
    DIP_ERR_REL_INSTANCE    = 0x0020,
    DIP_ERR_COLOR           = 0x0040,
    DIP_ERR_BASE_ADDR       = 0x0080,
    DIP_ERR_WIDTH_HEIGHT    = 0x0100,
    DIP_ERR_LINE_OFFSET     = 0x0200,
    DIP_ERR_OSDB_EN         = 0x0400,
    //
    DIP_ERR_MAX
} DIP_ERR_CODE_e;

typedef enum
{
    DIP_CTL_ROTATE_0 = 0,
    DIP_CTL_ROTATE_90,
    DIP_CTL_ROTATE_180,
    DIP_CTL_ROTATE_270,
    //
    DIP_CTL_ROTATE_UNSUPPORT
} DIP_CTL_ROTATE_e;

typedef enum
{
    DIP_CTL_COLOR_YUV420_UV = DIP_CTL_COLOR_YUV420,
    DIP_CTL_COLOR_YUV420_VU,
    DIP_CTL_COLOR_YUV420_T16X32_UV = DIP_CTL_COLOR_YUV420_T16X32,
    DIP_CTL_COLOR_YUV420_T16X32_VU,
    DIP_CTL_COLOR_YUV422_YUYV = DIP_CTL_COLOR_YUV422,
    DIP_CTL_COLOR_YUV422_YVYU,
    DIP_CTL_COLOR_YUV422_UYVY,
    DIP_CTL_COLOR_YUV422_VYUY,
    //
    DIP_CTL_COLOR_UNSUPPORT
} DIP_CTL_COLOR_e;

// Structure
typedef struct DIPCTL_BUF_ATTR_s
{
    u32                 nWidth;
    u32                 nHeight;
    u32                 nLineOffset;
    DIP_CTL_COLOR_e     eColorFormat;
    u32                 nBaseAddrY;
    u32                 nBaseAddrC;
} DIPCTL_BUF_ATTR_t, *PDIPCTL_BUF_ATTR;

typedef struct DIPCTL_ATTR_s
{
    DIPCTL_BUF_ATTR_t   tSrcBufAttr;
    DIPCTL_BUF_ATTR_t   tDestBufAttr;
    DIP_CTL_ROTATE_e    eRotDegree;
    bool                bMirror;
    bool                bFlip;
    bool                bOsdb;
} DIPCTL_ATTR_t, *PDIPCTL_ATTR;

// Function
DIP_ERR_CODE_e dip_mdl_img_move(PDIPCTL_ATTR pDipCtlAttr, void(*pfnCallback)(void*,void*), void* pCbkParam);
DIP_ERR_CODE_e dip_mdl_img_rotate(PDIPCTL_ATTR pDipCtlAttr, void(*pfnCallback)(void*,void*), void* pCbkParam);
DIP_ERR_CODE_e dip_mdl_img_scaling(PDIPCTL_ATTR pDipCtlAttr, void(*pfnCallback)(void*,void*), void* pCbkParam);
DIP_ERR_CODE_e dip_mdl_img_color_convert(PDIPCTL_ATTR pDipCtlAttr, void(*pfnCallback)(void*,void*), void* pCbkParam);
DIP_ERR_CODE_e dip_mdl_img_osdb(PDIPCTL_ATTR pDipCtlAttr, void(*pfnCallback)(void*,void*), void* pCbkParam);

#endif //__DIP_CTL_H__

