//==============================================================================
//
//  File        : AHC_USBHost.c
//  Description : AHC USB Host function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "ahc_usbhost.h"
#include "ahc_video.h"
#include "ahc_usb.h"
#include "ahc_display.h"
#include "ahc_capture.h"
#include "mmpf_usbuvc.h"
#include "mmpf_usbh_uvc.h"
#include "lib_retina.h"
#include "mmp_rtc_inc.h"
#include "mmps_usb.h"
#include "mmps_3gprecd.h"
#include "mmps_uvcrecd.h"
#include "mmpf_scaler.h"
#include "usb_cfg.h"
#include "MenuSetting.h"
#include "mdtc_cfg.h"
#include "snr_cfg.h"
#include "mmpf_usbh_ctl.h"
#include "component_cfg.h"

#if (UVC_HOST_VIDEO_ENABLE)

extern unsigned short  gusUVCRxEpBufCnt;
extern unsigned short  gusUVCRxEpBufSz;
extern unsigned int    gulUVCRxEpFullBufSz;

/*===========================================================================
 * Global variable
 *===========================================================================*/

static UVC_NALU_CFG m_stAhcHuvcNaluTBL[MMPS_3GPRECD_UVC_CFG_MAX_NUM] = {0};

static UVC_NALU_CFG m_stAhcHuvcNaluTblBulk[MMPS_3GPRECD_UVC_CFG_MAX_NUM] =
{
{{0x4D,0x11,0x55,0x84,0x0,0x0,0x0,0x0}, // {{"8437"},
 {{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3F,0x0B,0x04,0,0,0x1B,0x04}}},
{{0x4D,0x11,0x51,0x84,0x0,0x0,0x0,0x0}, // {{"8451"},
 {{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04}}},
{{0x17,0x1B,0x10,0x02,0x0,0x0,0x0,0x0}, // Zz1
 {{0x30,0x3D,0x09,0x04,0,0,0x19,0x04},{0x30,0x3D,0x09,0x04,0,0,0x19,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3F,0x0B,0x04,0,0,0x1B,0x04}}},
{{0x45,0x0C,0xAB,0x64,0x0,0x0,0x0,0x0}, // SN9C5256
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0xA3,0x05,0x30,0x92,0x0,0x0,0x0,0x0}, // SNx158y
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0xCF,0x1B,0x95,0x2B,0x0,0x0,0x0,0x0}, // x198 H42
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0x3F,0x1B,0x01,0x83,0x0,0x0,0x0,0x0}, //JX-V01
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0x4D,0x11,0x28,0x83,0x0,0x0,0x0,0x0}, //{{"8328"},
 {{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3F,0x0B,0x04,0,0,0x1B,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04}}},
{{0x45,0x0C,0x66,0x63,0x0,0x0,0x0,0x0}, //6366
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0x4D,0x11,0x00,0x8C,0x0,0x0,0x0,0x0}, //{{"8339"},
 {{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x4B,0x17,0x04,0,0,0x27,0x04},{0x30,0x4D,0x19,0x04,0,0,0x29,0x04}}}
};

static UVC_NALU_CFG m_stAhcHuvcNaluTblISO[MMPS_3GPRECD_UVC_CFG_MAX_NUM] =
{
{{0x4D,0x11,0x55,0x84,0x0,0x0,0x0,0x0}, // {{"8437"},
 {{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3F,0x0B,0x04,0,0,0x1B,0x04}}},
{{0x45,0x0C,0x00,0x63,0x0,0x0,0x0,0x0}, // SN9C216
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0x17,0x1B,0x10,0x02,0x0,0x0,0x0,0x0}, // Zz1
 {{0x30,0x3D,0x09,0x04,0,0,0x19,0x04},{0x30,0x3D,0x09,0x04,0,0,0x19,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3F,0x0B,0x04,0,0,0x1B,0x04}}},
{{0x45,0x0C,0xAB,0x64,0x0,0x0,0x0,0x0}, // SN9C5256
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0xA3,0x05,0x30,0x92,0x0,0x0,0x0,0x0}, // SNx158y
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0xCF,0x1B,0x95,0x2B,0x0,0x0,0x0,0x0}, // x198 H42
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0x3F,0x1B,0x01,0x83,0x0,0x0,0x0,0x0}, //JX-V01
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0x4D,0x11,0x28,0x83,0x0,0x0,0x0,0x0}, //{{"8328"},
 {{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3F,0x0B,0x04,0,0,0x1B,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04}}},
{{0x45,0x0C,0x66,0x63,0x0,0x0,0x0,0x0}, //6366
 {{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04},{0x30,0x58,0x24,0x04,0x17,0x0C,0x4F,0x04}}},
{{0x4D,0x11,0x00,0x8C,0x0,0x0,0x0,0x0}, //{{"8339"},
 {{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x3E,0x0A,0x04,0,0,0x1A,0x04},{0x30,0x4B,0x17,0x04,0,0,0x27,0x04},{0x30,0x4D,0x19,0x04,0,0,0x29,0x04}}}
};

/* guidExtensionCode */
static MMP_ULONG glUvcGuidEUTblBulk[MMPS_3GPRECD_UVC_CFG_MAX_NUM][(CS_INTERFACE_DESCR_GUID_SZ/(sizeof(MMP_ULONG)))] =
{
{GUID_EC_AIT_0,  GUID_EC_AIT_1,  GUID_EC_AIT_2,  GUID_EC_AIT_3},    // {{"8437"},
{GUID_EC_AIT_0,  GUID_EC_AIT_1,  GUID_EC_AIT_2,  GUID_EC_AIT_3},    // {{"8451"},
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // Zz1
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // SN9C5256
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // SNx158y
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // x198 H42
{GUID_JX_SONIX_0,GUID_JX_SONIX_1,GUID_JX_SONIX_2,GUID_JX_SONIX_3},  // JX-V01
{GUID_EC_AIT_0,  GUID_EC_AIT_1,  GUID_EC_AIT_2,  GUID_EC_AIT_3},    // {{"8328"},
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // 6366
{GUID_EC_AIT_0,  GUID_EC_AIT_1,  GUID_EC_AIT_2,  GUID_EC_AIT_3},    // {{"8339"},
};

static MMP_ULONG glUvcGuidEUTblISO[MMPS_3GPRECD_UVC_CFG_MAX_NUM][(CS_INTERFACE_DESCR_GUID_SZ/(sizeof(MMP_ULONG)))] =
{
{GUID_EC_AIT_0,  GUID_EC_AIT_1,  GUID_EC_AIT_2,  GUID_EC_AIT_3},    // {{"8437"},
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // SN9C216
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // SN9C216
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // Zz1
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // SNx158y
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},  // x198 H42
{GUID_JX_SONIX_0,GUID_JX_SONIX_1,GUID_JX_SONIX_2,GUID_JX_SONIX_3},  // JX-V01
{GUID_EC_AIT_0,  GUID_EC_AIT_1,  GUID_EC_AIT_2,  GUID_EC_AIT_3},	// {{"8328"},
{GUID_EC_SONIX_0,GUID_EC_SONIX_1,GUID_EC_SONIX_2,GUID_EC_SONIX_3},	// 6366
{GUID_EC_AIT_0,  GUID_EC_AIT_1,  GUID_EC_AIT_2,  GUID_EC_AIT_3},    // {{"8339"},
};

// H264 (1920x1080)
static MMP_UBYTE m_VsProbeCtl_8437[] =
{
#if 1 //TBD???
    0x01, 0x00, 0x03, 0x05, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x60, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00
#else
    0x01, 0x00, 0x03, 0x11, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00
#endif
};

// H264 (1280x720)
static MMP_UBYTE m_VsProbeCtl_8451[] =
{
    0x01, 0x00, 0x03, 0x01, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x60, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_64AB[] =
{
    0x00, 0x00, 0x01, 0x01, 0x80, 0x1A, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_64AB_1[] =
{
    0x01, 0x00, 0x02, 0x02, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_64AB_2[] =
{
    0x01, 0x00, 0x02, 0x01, 0x80, 0x1A, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_64AB_3[] =
{
    0x00, 0x00, 0x01, 0x01, 0x40, 0x42, 0x0F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x1C, 0x00, 0x00, 0x0C,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_64AB_4[] =
{
    0x01, 0x00, 0x02, 0x01, 0x80, 0x1A, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, UVC_DWMAXVIDEOFRAMESIZE_DESC(ISO_MJPEG_MAX_VIDEO_FRM_SIZE), 0x00, 0x0C,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_6366_1[] =
{
	0x00, 0x00, 0x01, 0x01, 0x15, 0x16, 0x05, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_6366_2[] =
{
	0x00, 0x00, 0x01, 0x01, 0x15, 0x16, 0x05, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00,
	0x00, 0x00, 0x4D, 0x22, 0x1C, 0x00, 0x00, 0x00,
	0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_6366_3[] =
{
	0x00, 0x00, 0x01, 0x01, 0x15, 0x16, 0x05, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00,
	0x00, 0x00, 0x4D, 0x22, 0x1C, 0x00, 0x00, 0x00,
	0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_6366_4[] =
{
	0x00, 0x00, 0x01, 0x01, 0x15, 0x16, 0x05, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00,
	0x00, 0x00, 0x4D, 0x22, 0x1C, 0x00, 0x40, 0x06,
	0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_8301_1[] =
{
    0x00, 0x00, 0x01, 0x01, 0x80, 0x1A, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x60, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_8301_2[] =
{
    0x00, 0x00, 0x01, 0x01, 0x80, 0x1A, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x60, 0x09, 0x00, 0xB0, 0x03,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_6300[] =
{
    0x79, 0xD2, 0x01, 0x01, 0x80, 0x1A, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x59, 0x07, 0x00, 0x60, 0x09, 0x00, 0xBF, 0x2A,
    0x40, 0xD4
};

static MMP_UBYTE m_VsProbeCtl_PID_6300_1[] =
{
    0x01, 0x00, 0x02, 0x01, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_6300_2[] =
{
    0x79, 0xD2, 0x01, 0x01, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x59, 0x07, 0x00, 0x60, 0x09, 0x00, 0x00, 0x0C,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_6300_3[] =
{
    0x01, 0x00, 0x02, 0x01, 0x15, 0x16, 0x05, 0x00,
    //0x01, 0x00, 0x02, 0x02, 0x15, 0x16, 0x05, 0x00,  //352x288
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x59, 0x07, UVC_DWMAXVIDEOFRAMESIZE_DESC(ISO_MJPEG_MAX_VIDEO_FRM_SIZE), 0x00, 0x0C,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_9230_1[] =
{
    0x00, 0x00, 0x01, 0x01, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_9230_2[] =
{
    0x00, 0x00, 0x01, 0x01, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00,
    0x00, 0x00, 0x4D, 0x22, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_9230_3[] =
{
    0x00, 0x00, 0x01, 0x01, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00,
    0x00, 0x00, 0x4D, 0x22, 0x1C, 0x00, 0x40, 0x06,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_2B95_1[] =
{
    0x00, 0x00, 0x01, 0x01, 0x80, 0x1A, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00
};

static MMP_UBYTE m_VsProbeCtl_PID_2B95_2[] =
{
    0x00, 0x00, 0x01, 0x01, 0x80, 0x1A, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x1C, 0x00, 0xF4, 0x0B,
    0x00, 0x00
};

static MMP_UBYTE m_VsCommitCtl_8437[] =
{
#if 1 //TBD???
    0x01, 0x00, 0x03, 0x05, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x20,
    0x00, 0x00
#else
    0x01, 0x00, 0x03, 0x11, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x26, 0x20, 0x00, 0x00, 0x20,
    0x00, 0x00
#endif
};

static MMP_UBYTE m_VsCommitCtl_8451[] =
{
    0x01, 0x00, 0x03, 0x01, 0x15, 0x16, 0x05, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x20,
    0x00, 0x00
};

static MMP_UBYTE m_XuCmdIspx02[] =
{
    0x02, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdIspx04[] =
{
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdIspx08x80_8437[] =
{
    0x08, 0x80, UVC_DWMAXVIDEOFRAMESIZE_DESC(AIT_MJPEG_MAX_VIDEO_FRM_SIZE), 0x00, 0x00
};

static MMP_UBYTE m_XuCmdIspx08xFF_8437[] =
{
    0x08, 0xFF, UVC_DWMAXVIDEOFRAMESIZE_DESC(INIT_DEV_MJPEG_BITRATE), 0x00, 0x00
};

static MMP_UBYTE m_XuCmdIspx08_8451[] =
{
    0x08, 0xFF, 0x40, 0x1F, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdIspx09[] =
{
    0x09, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 //default as 60Hz.
};

static MMP_UBYTE m_XuCmdIspx0B[] =
{
    0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdIspx11[] =
{
    0xFF, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdIspx29[] = //NV12 mirror only
{
    0xFF, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx09_h264[] =
{
    0x09, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx0B[] =
{
    0x0B, 0x13, 0x40, 0x01, 0xB4, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx0E[] =
{
    0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx0C_8437[] =
{
    0x0C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx0C_8451[] =
{
    0x0C, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*
static MMP_UBYTE m_XuCmdMmpx16[] =
{
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
*/

static MMP_UBYTE m_XuCmdMmpx21[] =
{
    0x21, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx22[] =
{
    0x22, 0xDF, 0x07, 0x01, 0x01, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx23_h264[] =
{
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx23_yuv[] =
{
    0x23, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx24[] =
{
    0x24, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 //toggle on (current selected stream)
    //0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 //toggle off (current selected stream)
};

static MMP_UBYTE m_XuCmdMmpx25_h264[] =
{
    0x25,  0x01,  0x80,  0x07,  0x38,  0x04,  0x1E, 0xC8 //16Mbps, 1920x1080
    //0x25,  0x01,  0x80,  0x07,  0x38,  0x04,  0x1E, 0x64 //8Mbps, 1920x1080
    //0x25,  0x01,  0x80,  0x07,  0x38,  0x04,  0x1E, 0x32 //4Mbps, 1920x1080
    //0x25,  0x01,  0x00,  0x05,  0xD0,  0x02,  0x1E, 0x64 //8Mbps, 1280x720
    //0x25,  0x01,  0x00,  0x05,  0xD0,  0x02,  0x1E, 0x32 //4Mbps, 1280x720
    //0x25,  0x01,  0x00,  0x05,  0xD0,  0x02,  0x1E, 0x19 //2Mbps, 1280x720
    //0x25,  0x01,  0x80,  0x02,  0x68,  0x01,  0x1E, 0x30 //3840Kbps, 640x360
    //0x25,  0x01,  0x80,  0x02,  0x68,  0x01,  0x1E, 0x24 //2880Kbps, 640x360
    //0x25,  0x01,  0x80,  0x02,  0x68,  0x01,  0x1E, 0x18 //1920Kbps, 640x360
};

static MMP_UBYTE m_XuCmdMmpx25_yuv[] =
{
    //320x180
#if (DEVICE_YUV_TYPE==ST_YUY2)
     0x25,  0x03,  0x40,  0x01,  0xB4,  0x00,  0x7E,  0x0A
#elif (DEVICE_YUV_TYPE==ST_NV12)
     0x25,  0x04,  0x40,  0x01,  0xB4,  0x00,  0x7E,  0x0A
#endif
};

static MMP_UBYTE m_XuCmdMmpx25_mjpg[] =
{
    0x25,  0x02,  0x00,  0x05,  0xD0,  0x02,  0x1E, 0x19 //2Mbps, 1280x720
};

static MMP_UBYTE m_XuCmdMmpx29[] =
{
    0x29, 0xFF, UVC_DEV_MD_DIV_W, UVC_DEV_MD_DIV_H, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx2A[] =
{
    0x2A, 0x02, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmpx2B[] =
{
    0x2B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#if 0
static MMP_UBYTE m_XuCmdMmpx30[] =
{
    0x30, 0x02, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdSetData32[] =
{
     'T',  'h',  'i',  's',  ' ',  'i',  's',  ' ',
     'a',  ' ',  'T',  'e',  'x',  't',  ' ',  'S',
     't',  'r',  'i',  'n',  'g',  '.', 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmp16x01[] =
{
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmp16x02_x01[] =
{
    0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static MMP_UBYTE m_XuCmdMmp16x02_x02[] =
{
    0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#endif

static MMP_UBYTE m_XuCmdx01x1F[] =
{
    0x1F, 0x10, 0x00, 0xFF
};

static MMP_ULONG                    m_ulAhcHUVCDataLength = 0;
static MMP_UBYTE                    m_ubAhcHUVCDataBuf[2048];
static UINT32                       m_u32AhcHUVCError = 0;

UINT16                              gsAhcUsbhSensor = USBH_SENSOR;

static UVC_HOST_CFG                 m_stAhcHUVCCfg = {0};

#if (MOTION_DETECTION_EN)
static MMP_UBYTE                    m_ubAhcHuvcMDSensitivity = UVC_DEV_MD_SENSITIVITY;
#endif

static MMP_BOOL                     m_bAhcUVCDeviceEnabled = MMP_FALSE;

static MMP_ULONG                    m_ulFrameInterval = 400000; // 25fps

/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern MMP_USHORT gsAhcScdSensor;
extern AHC_BOOL gbAhcDbgBrk;

/*===========================================================================
 * Extern function
 *===========================================================================*/

#if (MOTION_DETECTION_EN)
void VRMotionDetectCB(void);
#endif

static AHC_BOOL AHC_HostUVC_GetRTCTime(UINT8 *pu8Stream);
static AHC_BOOL AHC_HostUVC_IsDecMjpeg2Prevw(void);

void MMPF_USBH_CheckJpegEOIEveryPacketEnable(MMP_BOOL ubCheckJPGEOIEnable);
extern void ncam_set_rear_cam_ready(int state);

/*===========================================================================
 * Function prototype
 *===========================================================================*/

#if 0
void ____Internal_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_OpenUVCCb8437
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_OpenUVCCb8437(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Open UVC 8437/51 CB\r\n"));

    // EU1_SET_ISP
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_ISP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_ISP, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_GET_ISP_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_ISP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_ISP_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_SET_FW_DATA
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_FW_DATA, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_FW_DATA, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_SET_MMP
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_MMP, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_GET_MMP_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_MMP_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_SET_ISP_EX
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_ISP_EX, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_ISP_EX, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_GET_ISP_EX_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_ISP_EX_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_ISP_EX_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_READ_MMP_MEM
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_READ_MMP_MEM, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_READ_MMP_MEM, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_WRITE_MMP_MEM
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_WRITE_MMP_MEM, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_WRITE_MMP_MEM, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_GET_CHIP_INFO
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_CHIP_INFO, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_CHIP_INFO, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_GET_DATA_32
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_DATA_32, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_DATA_32, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_SET_DATA_32
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_DATA_32, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_DATA_32, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_SET_MMP_CMD16
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP_CMD16, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_MMP_CMD16, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU1_GET_MMP_CMD16_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_CMD16_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_MMP_CMD16_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // CT_EXPOSURE_TIME_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // CT_AE_PRIORITY_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // CT_IRIS_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_IRIS_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // CT_ZOOM_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // CT_PANTILT_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // PU_BRIGHTNESS_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_BRIGHTNESS_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // PU_CONTRAST_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_CONTRAST_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    #if 0
    // PU_HUE_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_HUE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    #endif

    // PU_SATURATION_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_SATURATION_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // PU_SHARPNESS_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_SHARPNESS_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    #if 0
    // PU_GAMMA_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_GAMMA_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    #endif

    // PU_WHITE_BALANCE_TEMPERATURE_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // PU_BACKLIGHT_COMPENSATION_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // PU_GAIN_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_GAIN_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // PU_POWER_LINE_FREQUENCY_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    gusUVCRxEpBufSz = 8*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_StartUVCCb8437
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_StartUVCCb8437(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;
    AHC_BOOL ahcRet = AHC_TRUE;

    AHC_DBG_MSG(1, FG_YELLOW("Start UVC 8437 CB\r\n"));

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx0C_8437); // Select Stream Layout

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_h264); // Select Multicast Stream ID
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx25_h264); //Multicast Commit
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx09_h264); //GOP Commit
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx24); //Toggle Layer Control

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_yuv); //Select Multicast Stream ID
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx25_yuv); //Multicast Commit
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx24); //Toggle Layer Control

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    ahcRet = AHC_HostUVC_ResetDevTime();
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); }

#if (MOTION_DETECTION_EN)
    m_XuCmdMmpx29[1] = 0xFF;
    m_XuCmdMmpx29[2] = UVC_DEV_MD_DIV_W;
    m_XuCmdMmpx29[3] = UVC_DEV_MD_DIV_H;

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx29); // MD reset
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    ahcRet = AHC_HostUVC_SetMDSensitivity(m_ubAhcHuvcMDSensitivity);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); }
#endif

    eRetErr = HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf); //VS_PROBE_CONTROL => UVC_DMA_SIZE => transaction
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_8437); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf); //VS_PROBE_CONTROL => UVC_DMA_SIZE => transaction
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsCommitCtl_8437); //VS_COMMIT_CONTROL
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    //HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx04);
}

static void AHC_HostUVC_OpenUVCCb8328(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    RTNA_DBG_Str0("Open UVC 8328 CB\r\n");
    //EU1_SET_ISP
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_ISP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_ISP, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_ISP_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_ISP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_ISP_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_SET_FW_DATA
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_FW_DATA, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_FW_DATA, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_SET_MMP
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_MMP, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_MMP_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_MMP_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    //EU1_SET_ISP_EX
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_ISP_EX, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_ISP_EX, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_ISP_EX_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_ISP_EX_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_ISP_EX_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_READ_MMP_MEM
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_READ_MMP_MEM, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_READ_MMP_MEM, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_WRITE_MMP_MEM
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_WRITE_MMP_MEM, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_WRITE_MMP_MEM, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_CHIP_INFO
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_CHIP_INFO, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_CHIP_INFO, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_DATA_32
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_DATA_32, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_DATA_32, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_SET_DATA_32
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_DATA_32, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_DATA_32, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_SET_MMP_CMD16
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP_CMD16, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_MMP_CMD16, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_MMP_CMD16_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_CMD16_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_MMP_CMD16_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_EXPOSURE_TIME_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_AE_PRIORITY_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_IRIS_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_IRIS_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_ZOOM_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_PANTILT_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_BRIGHTNESS_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_BRIGHTNESS_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_CONTRAST_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_CONTRAST_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    #if (0)
    // PU_HUE_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_HUE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    #endif
    // PU_SATURATION_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_SATURATION_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_SHARPNESS_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_SHARPNESS_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    #if (0)
    // PU_GAMMA_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_GAMMA_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    #endif
    // PU_WHITE_BALANCE_TEMPERATURE_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_BACKLIGHT_COMPENSATION_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_GAIN_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_GAIN_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_POWER_LINE_FREQUENCY_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    gusUVCRxEpBufSz = 8*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;
}

static void AHC_HostUVC_StartUVCCb8328(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;
    AHC_BOOL ahcRet = AHC_TRUE;

    RTNA_DBG_Str0("Start UVC 8328 CB\r\n");

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx0C_8437); //Select Stream Layout

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

#if(1)//H264 stream
	m_XuCmdMmpx23_h264[1] = 0;
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_h264); //Select Multicast Stream ID
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx25_h264); //Multicast Commit
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx09_h264); //GOP Commit
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx24); //Toggle Layer Control

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
#endif

#if(1)//MJPEG stream
	m_XuCmdMmpx23_yuv[1] = 3;
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_yuv); //Select Multicast Stream ID
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx25_yuv); //Multicast Commit
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx24); //Toggle Layer Control
#endif

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    ahcRet = AHC_HostUVC_ResetDevTime();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

#if (MOTION_DETECTION_EN)
    m_XuCmdMmpx29[1] = 0xFF;
    m_XuCmdMmpx29[2] = UVC_DEV_MD_DIV_W;
    m_XuCmdMmpx29[3] = UVC_DEV_MD_DIV_H;
    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx29); // MD reset
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    ahcRet = AHC_HostUVC_SetMDSensitivity(m_ubAhcHuvcMDSensitivity);
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }
#endif

    eRetErr = HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf); //VS_PROBE_CONTROL => UVC_DMA_SIZE => transaction
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_8437); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf); //VS_PROBE_CONTROL => UVC_DMA_SIZE => transaction
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsCommitCtl_8437); //VS_COMMIT_CONTROL
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    //HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx04);
}

static void AHC_HostUVC_OpenUVCCb8339(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    RTNA_DBG_Str0("Open UVC 8339 CB\r\n");
    //EU1_SET_ISP
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_ISP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_ISP, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_ISP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_ISP_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_ISP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_ISP_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_SET_FW_DATA
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_FW_DATA, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_FW_DATA, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_FW_DATA, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_SET_MMP
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_MMP, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_MMP, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_MMP_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_MMP_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    //EU1_SET_ISP_EX
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_ISP_EX, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_ISP_EX, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_ISP_EX, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_ISP_EX_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_ISP_EX_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_ISP_EX_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_ISP_EX_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_READ_MMP_MEM
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_READ_MMP_MEM, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_READ_MMP_MEM, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_READ_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_WRITE_MMP_MEM
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_WRITE_MMP_MEM, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_WRITE_MMP_MEM, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_WRITE_MMP_MEM, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_CHIP_INFO
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_CHIP_INFO, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_CHIP_INFO, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_CHIP_INFO, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_DATA_32
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_DATA_32, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_DATA_32, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_SET_DATA_32
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_DATA_32, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_DATA_32, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_DATA_32, 32, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_SET_MMP_CMD16
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP_CMD16, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_SET_MMP_CMD16, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_SET_MMP_CMD16, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU1_GET_MMP_CMD16_RESULT
    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_CMD16_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_INFO_CMD, EU1_GET_MMP_CMD16_RESULT, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MIN_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_MAX_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_RES_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_DEF_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_EXPOSURE_TIME_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_AE_PRIORITY_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_AE_PRIORITY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_IRIS_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_IRIS_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVCCmd(GET_CUR_CMD, VC_REQUEST_ERROR_CODE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_ZOOM_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_ZOOM_ABSOLUTE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // CT_PANTILT_ABSOLUTE_CONTROL
    eRetErr = HUVCGetCTCmd(GET_INFO_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MIN_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_MAX_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_RES_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetCTCmd(GET_DEF_CMD, CT_PANTILT_ABSOLUTE_CONTROL, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_BRIGHTNESS_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_BRIGHTNESS_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_BRIGHTNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_CONTRAST_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_CONTRAST_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_CONTRAST_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    #if (0)
    // PU_HUE_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_HUE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_HUE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    #endif
    // PU_SATURATION_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_SATURATION_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_SATURATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_SHARPNESS_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_SHARPNESS_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_SHARPNESS_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    #if (0)
    // PU_GAMMA_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_GAMMA_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_GAMMA_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    #endif
    // PU_WHITE_BALANCE_TEMPERATURE_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD,  PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_BACKLIGHT_COMPENSATION_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_GAIN_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_GAIN_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_GAIN_CONTROL, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // PU_POWER_LINE_FREQUENCY_CONTROL
    eRetErr = HUVCGetPUCmd(GET_INFO_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MIN_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_MAX_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_RES_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetPUCmd(GET_DEF_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    gusUVCRxEpBufSz = 48*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;
}

static void AHC_HostUVC_StartUVCCb8339(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;
    AHC_BOOL ahcRet = AHC_TRUE;

    RTNA_DBG_Str0("Start UVC 8339 CB\r\n");

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx0C_8437); //Select Stream Layout

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

#if(1)//H264 stream
	m_XuCmdMmpx23_h264[1] = USB_STRM_ID_H264; // Stream ID 0
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_h264); //Select Multicast Stream ID
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx25_h264); //Multicast Commit
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx09_h264); //GOP Commit
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx24); //Toggle Layer Control

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
#endif

#if(1)//MJPEG stream
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_yuv); //Select Multicast Stream ID
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx25_yuv); //Multicast Commit
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx24); //Toggle Layer Control
#endif

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    ahcRet = AHC_HostUVC_ResetDevTime();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

#if (MOTION_DETECTION_EN)
    m_XuCmdMmpx29[1] = 0xFF;
    m_XuCmdMmpx29[2] = UVC_DEV_MD_DIV_W;
    m_XuCmdMmpx29[3] = UVC_DEV_MD_DIV_H;
    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx29); // MD reset
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    ahcRet = AHC_HostUVC_SetMDSensitivity(m_ubAhcHuvcMDSensitivity);
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }
#endif

    eRetErr = HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf); //VS_PROBE_CONTROL => UVC_DMA_SIZE => transaction
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_8437); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf); //VS_PROBE_CONTROL => UVC_DMA_SIZE => transaction
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsCommitCtl_8437); //VS_COMMIT_CONTROL
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    //HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx04);
}

static void AHC_HostUVC_StartUVCCb8451(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;
    AHC_BOOL ahcRet = AHC_TRUE;

    AHC_DBG_MSG(1, FG_YELLOW("Start UVC 8451 CB\r\n"));

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx0C_8451); //set signal type
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx0B); //set Encoding Resolution (NV12)

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx25_h264); //Multicast Commit
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx09_h264); //GOP Commit
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx24); //Toggle Layer Control
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_ISP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx02); //set stFrameRate
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_ISP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx25_yuv); //Multicast Commit
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx24); //Toggle Layer Control

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    ahcRet = AHC_HostUVC_ResetDevTime();
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); }

#if (MOTION_DETECTION_EN)
    m_XuCmdMmpx29[1] = 0xFF;
    m_XuCmdMmpx29[2] = UVC_DEV_MD_DIV_W;
    m_XuCmdMmpx29[3] = UVC_DEV_MD_DIV_H;

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx29); // MD reset
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    ahcRet = AHC_HostUVC_SetMDSensitivity(m_ubAhcHuvcMDSensitivity);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); }
#endif

    eRetErr = HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_8451); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf); //VS_PROBE_CONTROL => UVC_DMA_SIZE => transaction
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsCommitCtl_8451); //VS_COMMIT_CONTROL
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_ISP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx08_8451);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_ISP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    //HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx04);
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_OpenUVCCb_PID_0210
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_OpenUVCCb_PID_0210(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Open UVC PID 0210 CB\r\n"));

    // VS_PROBE_CONTROL
    eRetErr = HUVCGetVSCmd(GET_DEF_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // EU3 x01
    eRetErr = HUVCGetEU3Cmd(GET_LEN_CMD, 0x01, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU3Cmd(GET_INFO_CMD, 0x01, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU3Cmd(SET_CUR_CMD, 0x01, 4, m_XuCmdx01x1F);
    eRetErr |= HUVCGetEU3Cmd(GET_CUR_CMD, 0x01, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU3Cmd(SET_CUR_CMD, 0x01, 4, m_XuCmdx01x1F);
    eRetErr |= HUVCGetEU3Cmd(GET_CUR_CMD, 0x01, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // GET_DESCRIPTOR, STRING_DESC
    //HUVCGetStdDevCmd(GET_DESCRIPTOR,((STRING_DESCR<<8)|0x05),0x0409,0xFF,&m_ulAhcHUVCDataLength,m_ubAhcHUVCDataBuf);
    gusUVCRxEpBufSz = 8*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_StartUVCCb_PID_0210
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_StartUVCCb_PID_0210(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Start UVC PID 0210 CB\r\n"));

    //VS_PROBE_CONTROL
    eRetErr = HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    //
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    //
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    //
    eRetErr = HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_3); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    //
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_3); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    //
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsProbeCtl_PID_64AB_4); //VS_COMMIT_CONTROL

    // SET_INTERFACE, 1.6
    eRetErr |= HUVCSetStdIfCmd(SET_INTERFACE,0x06,0x01,0,NULL);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_OpenUVCCb_PID_64AB
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_OpenUVCCb_PID_64AB(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Open UVC PID 64AB CB\r\n"));

    // VS_PROBE_CONTROL
    eRetErr = HUVCGetVSCmd(GET_DEF_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    // Get frame rate as device's default setting
    m_ulFrameInterval = get_unaligned_le32(m_ubAhcHUVCDataBuf + 4);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

    // EU x02
    eRetErr = HUVCGetEU3Cmd(GET_LEN_CMD, 0x01, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU3Cmd(GET_INFO_CMD, 0x01, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU3Cmd(SET_CUR_CMD, 0x01, 4, m_XuCmdx01x1F);
    eRetErr |= HUVCGetEU3Cmd(GET_CUR_CMD, 0x01, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU3Cmd(SET_CUR_CMD, 0x01, 4, m_XuCmdx01x1F);
    eRetErr |= HUVCGetEU3Cmd(GET_CUR_CMD, 0x01, 4, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    // GET_DESCRIPTOR, STRING_DESC
    eRetErr |= HUVCGetStdDevCmd(GET_DESCRIPTOR,((STRING_DESCR<<8)|0x05),0x0409,0xFF,&m_ulAhcHUVCDataLength,m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    gusUVCRxEpBufSz = 8*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_StartUVCCb_PID_64AB
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_StartUVCCb_PID_64AB(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Start UVC PID 64AB CB\r\n"));

    //VS_PROBE_CONTROL
    eRetErr = HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_3); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_3); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_64AB_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    // Set frame rate as device's default setting
    put_unaligned_le32(m_ulFrameInterval, m_VsProbeCtl_PID_64AB_4 + 4);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsProbeCtl_PID_64AB_4); //VS_COMMIT_CONTROL

    // SET_INTERFACE, 1.3
    //HUVCSetStdIfCmd(SET_INTERFACE,0x06,0x01,0,NULL);
    //eRetErr |= HUVCSetStdIfCmd(SET_INTERFACE,0x03,0x01,0,NULL); // Move to Hostuvc
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
}

static void AHC_HostUVC_OpenUVCCb_PID_6366(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    RTNA_DBG_Str0("Open UVC PID 6366 CB\r\n");
	if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }
    gusUVCRxEpBufSz = 8*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;

}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoStartUVCCb_PID_6366
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_StartUVCCb_PID_6366(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    RTNA_DBG_Str0("Start UVC PID 6366 CB\r\n");

	eRetErr = HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6366_1); //VS_PROBE_CONTROL
	eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6366_2); //VS_PROBE_CONTROL
	eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6366_3); //VS_PROBE_CONTROL
	eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
	eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsProbeCtl_PID_6366_4); //VS_PROBE_CONTROL
	eRetErr |= HUVCSetStdIfCmd(SET_INTERFACE,0x03,0x01,0,NULL); //use IF 3, due to not support ISO high-bandwidth

	if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_OpenUVCCb_PID_8301
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_OpenUVCCb_PID_8301(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Open UVC PID 8301 CB\r\n"));
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    gusUVCRxEpBufSz = 8*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_StartUVCCb_PID_64AB
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_StartUVCCb_PID_8301(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Start UVC PID 8301 CB\r\n"));
#if 0
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_8301_1); //VS_PROBE_CONTROL
#endif

    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_8301_1); //VS_PROBE_CONTROL

    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsProbeCtl_PID_8301_2); //VS_PROBE_CONTROL

#if 0 // TBD
    // This hardcoding is from Sunplus different FW with the same PID/VID.
    if (gUsbh_UvcDevInfo.wSzConfigDesc == (0x00F9)) {
        eRetErr |= HUVCSetStdIfCmd(SET_INTERFACE, 0x02, 0x01, 0,NULL);
    }
    else if (gUsbh_UvcDevInfo.wSzConfigDesc == (0x0141)) {
        eRetErr |= HUVCSetStdIfCmd(SET_INTERFACE, 0x06, 0x01, 0,NULL);
    }
    else {
        AHC_DBG_ERR(1, "UVC device descriptor length error!\r\n");
    }
#endif
    if(eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(eRetErr,0); }
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_OpenUVCCb_PID_9230
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_OpenUVCCb_PID_9230(void)
{
    AHC_DBG_MSG(1, FG_YELLOW("Open UVC PID 9230 CB\r\n"));
    gusUVCRxEpBufSz = 8*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_StartUVCCb_PID_9230
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_StartUVCCb_PID_9230(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Start UVC PID 9230 CB\r\n"));

    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_9230_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_9230_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsProbeCtl_PID_9230_3); //VS_PROBE_CONTROL
    eRetErr |= HUVCSetStdIfCmd(SET_INTERFACE,0x02,0x01,0,NULL); //use IF 3, due to not support ISO high-bandwidth
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_OpenUVCCb_PID_2B95
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_OpenUVCCb_PID_2B95(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Open UVC PID 2B95 CB\r\n"));
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    gusUVCRxEpBufSz = 8*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_StartUVCCb_PID_2B95
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_StartUVCCb_PID_2B95(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Start UVC PID 2B95 CB\r\n"));

    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_2B95_1); //VS_PROBE_CONTROL

    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_2B95_1); //VS_PROBE_CONTROL

    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsProbeCtl_PID_2B95_2); //VS_PROBE_CONTROL

    eRetErr |= HUVCSetStdIfCmd(SET_INTERFACE,0x02,0x01,0,NULL); //use IF 3, due to not support ISO high-bandwidth
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_OpenUVCCb_PID_6300
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_OpenUVCCb_PID_6300(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Open UVC PID 6300 CB\r\n"));

    // VS_PROBE_CONTROL
    eRetErr = HUVCGetVSCmd(GET_DEF_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    // EU x03
    eRetErr |= HUVCGetEU3Cmd(GET_LEN_CMD, 0x01, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU3Cmd(GET_INFO_CMD, 0x01, 1, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU3Cmd(SET_CUR_CMD, 0x01, 4, m_XuCmdx01x1F);
    eRetErr |= HUVCSetEU3Cmd(SET_CUR_CMD, 0x01, 4, m_XuCmdx01x1F);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    // GET_DESCRIPTOR, STRING_DESC
    //HUVCGetStdDevCmd(GET_DESCRIPTOR,((STRING_DESCR<<8)|0x05),0x0409,0xFF,&m_ulAhcHUVCDataLength,m_ubAhcHUVCDataBuf);
    gusUVCRxEpBufSz = 8*1024;
    gulUVCRxEpFullBufSz = gusUVCRxEpBufSz*gusUVCRxEpBufCnt;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_StartUVCCb_PID_6300
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_StartUVCCb_PID_6300(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Start UVC PID 6300 CB\r\n"));

    //VS_PROBE_CONTROL
    eRetErr = HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    //
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    //
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    //
    eRetErr = HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    //
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_2); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    //
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl_PID_6300_1); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsProbeCtl_PID_6300_3); //VS_COMMIT_CONTROL

    // SET_INTERFACE, 1.3
    //HUVCSetStdIfCmd(SET_INTERFACE,0x06,0x01,0,NULL);
    eRetErr |= HUVCSetStdIfCmd(SET_INTERFACE,0x03,0x01,0,NULL); //use IF 3, due to 8428 not support ISO high-bandwidth
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_StartCb8589
//  Description :
//------------------------------------------------------------------------------
static void AHC_HostUVC_StartCb8589(void)
{
    //MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_DBG_MSG(1, FG_YELLOW("Start UVC 8589 CB\r\n"));

#if 0 //Not support now.
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP_CMD16, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP_CMD16, 16, m_XuCmdMmp16x02_x01); // SEC TV options

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_MMP_CMD16_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_CMD16_RESULT, 16, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP_CMD16, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP_CMD16, 16, m_XuCmdMmp16x02_x02); // SEC TV options
    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_MMP_CMD16, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP_CMD16, 16, m_XuCmdMmp16x01); //set signal type
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_PROBE_CONTROL, 26, m_VsProbeCtl); //VS_PROBE_CONTROL
    eRetErr |= HUVCGetVSCmd(GET_CUR_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetVSCmd(GET_MAX_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf); //VS_PROBE_CONTROL => UVC_DMA_SIZE => transaction
    eRetErr |= HUVCGetVSCmd(GET_MIN_CMD, VS_PROBE_CONTROL, 26, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    eRetErr |= HUVCSetVSCmd(SET_CUR_CMD, VS_COMMIT_CONTROL, 26, m_VsCommitCtl); //VS_COMMIT_CONTROL

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_SET_ISP, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx08_8451);

    eRetErr |= HUVCGetEU1Cmd(GET_LEN_CMD, EU1_GET_ISP_RESULT, 2, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_ISP_RESULT, 8, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);

    //HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx04);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
#endif
}

#if 0
void ____Error_CB_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoReadErrorType
//  Description :
//------------------------------------------------------------------------------
void AHC_HostUVCVideoReadErrorType(UINT32 *pu32ErrType)
{
    *pu32ErrType = m_u32AhcHUVCError;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoClearError
//  Description :
//------------------------------------------------------------------------------
void AHC_HostUVCVideoClearError(UINT32 u32ErrorType)
{
    m_u32AhcHUVCError &= ~(u32ErrorType);
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoSetEp0TimeoutCB
//  Description :
//------------------------------------------------------------------------------
void AHC_HostUVCVideoSetEp0TimeoutCB(void)
{
    m_u32AhcHUVCError |= UVC_HOST_ERROR_EP0_TIMEOUT;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoSetEp0TimeoutCB
//  Description :
//------------------------------------------------------------------------------
void AHC_HostUVCVideoSetTranTimeoutCB(void)
{
    m_u32AhcHUVCError |= UVC_HOST_ERROR_TRAN_TIMEOUT;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoSetFrmRxTimeoutCB
//  Description :
//------------------------------------------------------------------------------
void AHC_HostUVCVideoSetFrmRxTimeoutCB(void)
{
    m_u32AhcHUVCError |= UVC_HOST_ERROR_FRM_RX_LOST;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoSetFrmRxTimeout2CB
//  Description :
//------------------------------------------------------------------------------
void AHC_HostUVCVideoSetFrmRxTimeout2CB(void)
{
    m_u32AhcHUVCError |= UVC_HOST_ERROR_FRM_RX_LOST_TH_2;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoSetFrmSeqNoLostCB
//  Description :
//------------------------------------------------------------------------------
void AHC_HostUVCVideoSetFrmSeqNoLostCB(void)
{
    m_u32AhcHUVCError |= UVC_HOST_ERROR_SEQ_NO_LOST;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoSetFrmRxDropCB
//  Description :
//------------------------------------------------------------------------------
void AHC_HostUVCVideoSetFrmRxDropCB(void)
{
    m_u32AhcHUVCError |= UVC_HOST_ERROR_FRM_RX_LOST_TH_2; // Share with FRM RX lost 2.  Disconnect device.
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVCVideoDevDisconnectedCB
//  Description :
//------------------------------------------------------------------------------
void AHC_HostUVCVideoDevDisconnectedCB(void)
{
    m_u32AhcHUVCError |= UVC_HOST_ERROR_DISCONNECTED;
}

#if 0
void ____Set_Dev_Attr_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetMDCuttingWindows
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetMDCuttingWindows(MMP_UBYTE ubWidth, MMP_UBYTE ubHeight)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    m_XuCmdMmpx29[1] = 0x01;
    m_XuCmdMmpx29[2] = ubWidth;
    m_XuCmdMmpx29[3] = ubHeight;

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx29);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetMDSensitivity
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetMDSensitivity(MMP_UBYTE ubSensitivity)
{
    MMP_USHORT  usMdBlkNum = 0;
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    if (ubSensitivity > UVC_DEV_MD_MAX_SENSITIVITY) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);
        return AHC_FALSE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    #if (MOTION_DETECTION_EN)
    m_ubAhcHuvcMDSensitivity = ubSensitivity;
    #endif

    ahcRet = AHC_HostUVC_SetMDCuttingWindows(UVC_DEV_MD_DIV_W, UVC_DEV_MD_DIV_H);
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    for (usMdBlkNum = 0; usMdBlkNum < (UVC_DEV_MD_DIV_W*UVC_DEV_MD_DIV_H); usMdBlkNum++) {
        m_XuCmdMmpx2A[2] = usMdBlkNum & 0xFF;
        m_XuCmdMmpx2A[3] = (usMdBlkNum>>8) & 0xFF;
        m_XuCmdMmpx2A[4] = ubSensitivity;    // device FW dependent 0~40
        eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx2A);
    }
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_GetDevFwVersion
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_GetDevFwVersion(UINT16* pu16Major, UINT16* pu16Minor, UINT16* pu16Build)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    UINT32      u32DataLength = 0;
    UINT8       u8FwVersionBuf[8] = {0};

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx0B);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_ISP_RESULT, 8, &u32DataLength, u8FwVersionBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    if (u8FwVersionBuf[0] != 0x00) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE; }

    *pu16Major = (u8FwVersionBuf[2]<<8) | u8FwVersionBuf[3];
    *pu16Minor = (u8FwVersionBuf[4]<<8) | u8FwVersionBuf[5];
    *pu16Build = (u8FwVersionBuf[6]<<8) | u8FwVersionBuf[7];

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_ResetDevTime
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_ResetDevTime(void)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    if (bUVCStates != MMP_TRUE) {
        return AHC_FALSE;
    }

    ahcRet = AHC_HostUVC_GetRTCTime(&m_XuCmdMmpx22[0]);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx22); // RTC
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_ForceIFrame
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_ForceIFrame(void)
{
    MMP_BOOL    bPrvwStatus = MMP_TRUE;
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPF_USBH_GetUVCPrevwSts(&bPrvwStatus);
    if ((eRetErr != MMP_ERR_NONE) || (bPrvwStatus != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_h264); //Select Multicast Stream ID
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx04);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetOSD
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetOSD(const char *pstring, UINT16 u16OffsetX, UINT16 u16OffsetY, UVC_XU_OSD_INDEX eDisplayMode)
{
    UINT32      u32Loop = 0;
    UBYTE       cosd_string[UVC_MAX_OSD_STRING_LEN] = {0};
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    if (eDisplayMode >= UVC_XU_OSD_MAX_SUPPORT_NUM) {
        AHC_DBG_ERR(1, FG_RED("[ERR] HostUVC_SetOSD\r\n"), __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }

    // Max string length is 32.
    for (u32Loop = 0; u32Loop < UVC_MAX_OSD_STRING_LEN; ++u32Loop) {
        if (*(pstring + u32Loop) == '\0') {
            break;
        }
    }
    memset((void *)cosd_string, 0x0, UVC_MAX_OSD_STRING_LEN);
    memcpy((void *)cosd_string, (void *)pstring, u32Loop);

    if (u32Loop == UVC_MAX_OSD_STRING_LEN) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);
        return AHC_FALSE;
    }

    m_XuCmdMmpx21[0x01] = eDisplayMode;
    m_XuCmdMmpx21[0x02] = (UINT8)(u16OffsetX & 0xFF);
    m_XuCmdMmpx21[0x03] = (UINT8)((u16OffsetX >> 8) & 0xFF);
    m_XuCmdMmpx21[0x04] = (UINT8)(u16OffsetY & 0xFF);
    m_XuCmdMmpx21[0x05] = (UINT8)((u16OffsetY >> 8) & 0xFF);

    //HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, STREAMVIEW_MP8_23);
    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_h264);
    eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx21);

    if (eDisplayMode == UVC_XU_OSD_TEXT_ENABLE) {
        eRetErr |= HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_DATA_32, UVC_MAX_OSD_STRING_LEN, cosd_string); //TEXT
    }

    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetImageFlip
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetImageFlip(UVC_IMAGE_FLIP eFlipOption)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    switch(eFlipOption) {
    case UVC_IMAGE_FLIP_UPSIDE_DOWN:
        m_XuCmdIspx11[0x2] = 0x1;
        break;
    case UVC_IMAGE_FLIP_MIRROR:
        m_XuCmdIspx11[0x2] = 0x2;
        break;
    case UVC_IMAGE_FLIP_BLACK_IMAGE:
        m_XuCmdIspx11[0x2] = 0x4;
        break;
    default:
        m_XuCmdIspx11[0x2] = 0x0;
        break;
    }

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx11);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetNV12Mirror
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetNV12Mirror(AHC_BOOL bMirrorEn)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    if (bMirrorEn == MMP_TRUE) {
        m_XuCmdIspx29[0x2] = 0x1;
    }
    else {
        m_XuCmdIspx29[0x2] = 0x0;
    }

    if (HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx29) != MMP_ERR_NONE)
    {
        AHC_DBG_ERR(1, FG_RED("[ERR] HostUVC_SetNV12Mirror\r\n"));
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetFlicker
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetFlicker(UVC_FLICKER_INDEX eFlickerIdx)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    UINT32      u32DataLength = 0;
    UINT8       u8FlickerResultBuf[8] = {0};

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    if (eFlickerIdx >= UVC_FLICKER_MAX) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);
        return AHC_FALSE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    m_XuCmdIspx09[1] = eFlickerIdx;

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx09);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_ISP_RESULT, 8, &u32DataLength, u8FlickerResultBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    if (u8FlickerResultBuf[0] != 0x00) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); return AHC_FALSE; }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetLedFlicker
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetLedFlicker(UINT8 u8Flag)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    if (u8Flag == 0) {
        m_XuCmdMmpx0E[2] = 0x0;
    }
    else {
        m_XuCmdMmpx0E[2] = 0x1;
    }

    HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx0E); // set LED flicker

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUBackLightCompensation
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUBackLightCompensation(UINT16 u16BackLightCompensationLevel)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr= MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u16BackLightCompensationLevel & 0xFF);
    ubDataBuf[1] = (MMP_UBYTE)((u16BackLightCompensationLevel >> 8) & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_BACKLIGHT_COMPENSATION_CONTROL, 2, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUBrightness
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUBrightness(UINT16 u16BrightnessLevel)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u16BrightnessLevel & 0xFF);
    ubDataBuf[1] = (MMP_UBYTE)((u16BrightnessLevel >> 8) & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_BRIGHTNESS_CONTROL, 2, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUContrast
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUContrast(UINT16 u16ContrastLevel)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u16ContrastLevel & 0xFF);
    ubDataBuf[1] = (MMP_UBYTE)((u16ContrastLevel >> 8) & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_CONTRAST_CONTROL, 2, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUGain
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUGain(UINT16 u16GainLevel)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u16GainLevel & 0xFF);
    ubDataBuf[1] = (MMP_UBYTE)((u16GainLevel >> 8) & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_GAIN_CONTROL, 2, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUPowerLineFrequency
//  Description : 0: Disabled, 1: 50 Hz, 2: 60 Hz
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUPowerLineFrequency(UINT8 u8PowerLineFrequency)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u8PowerLineFrequency & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_POWER_LINE_FREQUENCY_CONTROL, 1, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUHue
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUHue(UINT16 u16HueLevel)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u16HueLevel & 0xFF);
    ubDataBuf[1] = (MMP_UBYTE)((u16HueLevel >> 8) & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_HUE_CONTROL, 2, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUSaturation
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUSaturation(UINT16 u16SaturationLevel)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u16SaturationLevel & 0xFF);
    ubDataBuf[1] = (MMP_UBYTE)((u16SaturationLevel >> 8) & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_SATURATION_CONTROL, 2, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUSharpness
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUSharpness(UINT16 u16SharpnessLevel)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u16SharpnessLevel & 0xFF);
    ubDataBuf[1] = (MMP_UBYTE)((u16SharpnessLevel >> 8) & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_SHARPNESS_CONTROL, 2, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUGamma
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUGamma(UINT16 u16GammaLevel)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u16GammaLevel & 0xFF);
    ubDataBuf[1] = (MMP_UBYTE)((u16GammaLevel >> 8) & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_GAMMA_CONTROL, 2, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUWhiteBalanceTemperature
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUWhiteBalanceTemperature(UINT16 u16WhiteBalanceTemperature)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u16WhiteBalanceTemperature & 0xFF);
    ubDataBuf[1] = (MMP_UBYTE)((u16WhiteBalanceTemperature >> 8) & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_WHITE_BALANCE_TEMPERATURE_CONTROL, 2, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetPUWhiteBalanceTemperatureAuto
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetPUWhiteBalanceTemperatureAuto(UINT8 u8WhiteBalanceTemperatureAuto)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataBuf[8] = {0};

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = (MMP_UBYTE)(u8WhiteBalanceTemperatureAuto & 0xFF);

    eRetErr = HUVCSetPUCmd(SET_CUR_CMD, PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL, 1, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetMjpegBitrate
//  Description : Set UVC MJPEG stream bitrate
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetMjpegBitrate(UINT32 u32Kbps)
{
    AHC_BOOL ahcRet = MMP_TRUE;

    if (MMP_FALSE == AHC_HostUVC_IsDecMjpeg2Prevw()) {
        AHC_DBG_ERR(1, FG_RED("[ERR] Not commit Mjpeg stream!\r\n"));
        ahcRet = AHC_FALSE;
    }
    else if (0 == u32Kbps) {
        AHC_DBG_ERR(1, FG_RED("[ERR] Commit Mjpeg stream wrong bitrate %dkbps!\r\n"), u32Kbps);
        ahcRet = AHC_FALSE;
    }
    else {
        /* Multicast select MJPEG stream ID */
        HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_yuv);

        /* Set bitrate */
        m_XuCmdIspx08xFF_8437[2] = (u32Kbps & 0xFF);
        m_XuCmdIspx08xFF_8437[3] = ((u32Kbps >> 8) & 0xFF);
        m_XuCmdIspx08xFF_8437[4] = ((u32Kbps >> 16) & 0xFF);
        m_XuCmdIspx08xFF_8437[5] = ((u32Kbps >> 24) & 0xFF);
        HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx08xFF_8437); /* bitrate */

        ahcRet = AHC_TRUE;
    }
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetMjpegFrmSz
//  Description : Set UVC MJPEG stream frame size
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetMjpegFrmSz(UINT32 ulKBytes)
{
    MMP_ULONG   ulFrmSz = 0;
    AHC_BOOL    ahcRet = MMP_TRUE;

    if (MMP_FALSE == AHC_HostUVC_IsDecMjpeg2Prevw()) {
        AHC_DBG_ERR(1, FG_RED("[ERR] Not commit Mjpeg stream!\r\n"));
        ahcRet = AHC_FALSE;
    }
    else if (0 == ulKBytes) {
        AHC_DBG_ERR(1, FG_RED("[ERR] Commit Mjpeg stream wrong frame size %dKB!\r\n"), ulKBytes);
        ahcRet = AHC_FALSE;
    }
    else {
        /* Multicast select MJPEG stream ID */
        HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx23_yuv);

        /* Set frame size */
        ulFrmSz = ulKBytes << 10;

        m_XuCmdIspx08x80_8437[2] = (ulFrmSz & 0xFF);
        m_XuCmdIspx08x80_8437[3] = ((ulFrmSz >> 8) & 0xFF);
        m_XuCmdIspx08x80_8437[4] = ((ulFrmSz >> 16) & 0xFF);
        m_XuCmdIspx08x80_8437[5] = ((ulFrmSz >> 24) & 0xFF);
        HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_ISP, 8, m_XuCmdIspx08x80_8437); /* max frame size */

        ahcRet = AHC_TRUE;
    }
    return ahcRet;
}

#if 0
void ____Public_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_GetDevChipName
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_GetDevChipName(UVC_DEVICE_NAME_INDEX *pUVCDeviceName)
{
    if (MMP_IsUSBCamIsoMode())
        memcpy((MMP_UBYTE*)m_stAhcHuvcNaluTBL, (MMP_UBYTE*)m_stAhcHuvcNaluTblISO, sizeof(m_stAhcHuvcNaluTBL));
    else
        memcpy((MMP_UBYTE*)m_stAhcHuvcNaluTBL, (MMP_UBYTE*)m_stAhcHuvcNaluTblBulk, sizeof(m_stAhcHuvcNaluTBL));

    if (gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[0].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[0].ubDevStrInfo[1] << 8) +
                                      ((UINT32)m_stAhcHuvcNaluTBL[0].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[0].ubDevStrInfo[3] << 24))) {
        *pUVCDeviceName = UVC_DEVICE_NAME_8437;
    }
    else if (gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[1].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[1].ubDevStrInfo[1] << 8) +
                                           ((UINT32)m_stAhcHuvcNaluTBL[1].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[1].ubDevStrInfo[3] << 24))) {
        if (MMP_IsUSBCamIsoMode()) {
            *pUVCDeviceName = UVC_DEVICE_NAME_PID_6300;
        }
        else {
            *pUVCDeviceName = UVC_DEVICE_NAME_8451;
        }
    }
    else if (gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[2].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[2].ubDevStrInfo[1] << 8) +
                                           ((UINT32)m_stAhcHuvcNaluTBL[2].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[2].ubDevStrInfo[3] << 24))) {
        *pUVCDeviceName = UVC_DEVICE_NAME_PID_0210;
    }
    else if (gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[3].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[3].ubDevStrInfo[1] << 8) +
                                           ((UINT32)m_stAhcHuvcNaluTBL[3].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[3].ubDevStrInfo[3] << 24))) {
        *pUVCDeviceName = UVC_DEVICE_NAME_PID_64AB;
    }
    else if (gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[4].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[4].ubDevStrInfo[1] << 8) +
                                           ((UINT32)m_stAhcHuvcNaluTBL[4].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[4].ubDevStrInfo[3] << 24))) {
        *pUVCDeviceName = UVC_DEVICE_NAME_PID_9230;
    }
    else if (gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[5].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[5].ubDevStrInfo[1] << 8) +
                                           ((UINT32)m_stAhcHuvcNaluTBL[5].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[5].ubDevStrInfo[3] << 24))) {
        *pUVCDeviceName = UVC_DEVICE_NAME_PID_2B95;
    }
    else if (gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[6].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[6].ubDevStrInfo[1] << 8) +
                                           ((UINT32)m_stAhcHuvcNaluTBL[6].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[6].ubDevStrInfo[3] << 24))) {
        *pUVCDeviceName = UVC_DEVICE_NAME_PID_8301;
    }
    else if(gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[7].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[7].ubDevStrInfo[1] << 8) +
                                           ((UINT32)m_stAhcHuvcNaluTBL[7].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[7].ubDevStrInfo[3] << 24))){
		*pUVCDeviceName = UVC_DEVICE_NAME_PID_8328;
	}
	else if(gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[8].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[8].ubDevStrInfo[1] << 8) +
                                           ((UINT32)m_stAhcHuvcNaluTBL[8].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[8].ubDevStrInfo[3] << 24))){
		*pUVCDeviceName = UVC_DEVICE_NAME_PID_6366;
	}
    else if(gUsbh_UvcDevInfo.ulVIDPID == (((UINT32)m_stAhcHuvcNaluTBL[9].ubDevStrInfo[0] << 0) + ((UINT32)m_stAhcHuvcNaluTBL[9].ubDevStrInfo[1] << 8) +
                                          ((UINT32)m_stAhcHuvcNaluTBL[9].ubDevStrInfo[2] << 16) + ((UINT32)m_stAhcHuvcNaluTBL[9].ubDevStrInfo[3] << 24))){
       *pUVCDeviceName = UVC_DEVICE_NAME_PID_8339;
    }
    else {
        *pUVCDeviceName = UVC_DEVICE_NAME_MAX_SUPPORT_NUM;
        AHC_DBG_ERR(1, "UnKnown USB PID\r\n");
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_GetDevChipInfo
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_GetDevChipInfo(UINT32 *pu32UVCDevVIDPID)
{
#if defined( __RTK_OS__ )
    uvcl_get_VIDPID(0, (void*)pu32UVCDevVIDPID);
#else
    MMP_ULONG   ulDataLength = 0;
    MMP_UBYTE   ubDataBuf[EU1_GET_CHIP_INFO_LEN] = {0};
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    memset(ubDataBuf, 0x0, EU1_GET_CHIP_INFO_LEN);

    eRetErr = HUVCGetStdDevCmd(GET_DESCRIPTOR, (DEVICE_DESCR<<8), 0, 0x12, &m_ulAhcHUVCDataLength, m_ubAhcHUVCDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    ubDataBuf[0] = m_ubAhcHUVCDataBuf[DEVICE_DESCR_VID_LO_OFST];
    ubDataBuf[1] = m_ubAhcHUVCDataBuf[DEVICE_DESCR_VID_HI_OFST];
    ubDataBuf[2] = m_ubAhcHUVCDataBuf[DEVICE_DESCR_PID_LO_OFST];
    ubDataBuf[3] = m_ubAhcHUVCDataBuf[DEVICE_DESCR_PID_HI_OFST];
    ubDataBuf[4] = 0;

    ulDataLength = 4;

    *pu32UVCDevVIDPID = ((UINT32)ubDataBuf[0] << 0) + ((UINT32)ubDataBuf[1] << 8) + ((UINT32)ubDataBuf[2] << 16) + ((UINT32)ubDataBuf[3] << 24);
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_GetRTCTime
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_GetRTCTime(UINT8 *pu8Stream)
{
    AHC_RTC_TIME stAhcRtcTime;

    if (pu8Stream == NULL) {
        return AHC_FALSE;
    }

    AHC_RTC_GetTime(&stAhcRtcTime);

    *(pu8Stream + 1) = (UINT8)(stAhcRtcTime.uwYear & 0x00FF);
    *(pu8Stream + 2) = (UINT8)((stAhcRtcTime.uwYear >> 8) & 0x00FF);
    *(pu8Stream + 3) = (UINT8)(stAhcRtcTime.uwMonth & 0x00FF);
    *(pu8Stream + 4) = (UINT8)(stAhcRtcTime.uwDay & 0x00FF);
    *(pu8Stream + 5) = (UINT8)(stAhcRtcTime.uwHour & 0x00FF); //Get always be 24 format
    *(pu8Stream + 6) = (UINT8)(stAhcRtcTime.uwMinute & 0x00FF);
    *(pu8Stream + 7) = (UINT8)(stAhcRtcTime.uwSecond & 0x00FF);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_IsDecMjpeg2Prevw
//  Description : AP common I/F to decide if UVC decode MJPEG to preview
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_IsDecMjpeg2Prevw(void)
{
    AHC_BOOL bDecMjpeg2Prevw = AHC_FALSE;

    /* AP make decision if request driver decode Mjpeg to preview */
    if (m_stAhcHUVCCfg.ubCmitUVCStrmTyp & BM_USB_STRM_MJPEG)
    {
        bDecMjpeg2Prevw = MMP_TRUE;
    }

    return bDecMjpeg2Prevw;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetWinAttribute
//  Description : TBD, dummy function now
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_SetWinAttribute(    UINT8  u8WinID,
                                                UINT16 u16DisplayW, UINT16 u16DisplayH,
                                                UINT16 u16OffsetX,  UINT16 u16OffsetY,
                                                UINT8  sFitMode, AHC_BOOL bRotate)
{
#if 0
    MMP_DISPLAY_DISP_ATTR   stDispAttr;
    MMP_SCAL_FIT_RANGE      stFitrange;
    MMP_SCAL_GRAB_CTRL      stDispGrabctl;
    UINT16                  u16OldWinID = 0;
    UINT16                  u16OldWinW = 0, u16OldWinH = 0, u16OldDispW = 0, u16OldDispH = 0;
    UINT16                  u16OldOffsetX = 0, u16OldOffsetY = 0;
    MMP_USHORT              usDispColor;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    AHC_BOOL                ahcRet = AHC_TRUE;

    if (MMP_IsUSBCamIsoMode() && MMP_IsSupportDecMjpegToPreview())
    {
        ahcRet = AHC_HostUVC_SetWinActive(u8WinID, AHC_FALSE);
        if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); }

        eRetErr = MMPS_HUVC_GetDecMjpegToPreviewDispAttr(  &u16OldWinID,
                                                        &u16OldOffsetX, &u16OldOffsetY,
                                                        &u16OldWinW,    &u16OldWinH,
                                                        &u16OldDispW,   &u16OldDispH,
                                                        &usDispColor);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);}

        stDispAttr.bMirror = MMP_FALSE;
        stDispAttr.usStartX = 0;
        stDispAttr.usStartY = 0;

        if (AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
        {
            stDispAttr.usDisplayWidth    = u16OldWinW;
            stDispAttr.usDisplayHeight   = u16OldWinH;
            stDispAttr.usDisplayOffsetX  = (MMP_USHORT)u16OffsetX;
            stDispAttr.usDisplayOffsetY  = (MMP_USHORT)u16OffsetY;
            stDispAttr.rotatetype        = MMP_DISPLAY_ROTATE_NO_ROTATE;
        }
        else
        {
        #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
            stDispAttr.usDisplayWidth    = u16OldWinW;
            stDispAttr.usDisplayHeight   = u16OldWinH;
            stDispAttr.usDisplayOffsetX  = (MMP_USHORT)usOffsetX;
            stDispAttr.usDisplayOffsetY  = (MMP_USHORT)usOffsetY;
            stDispAttr.rotatetype        = MMP_DISPLAY_ROTATE_NO_ROTATE;
        #elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
            stDispAttr.usDisplayWidth    = FLOOR16(u16OldWinH);
            stDispAttr.usDisplayHeight   = (u16OldWinW);
            stDispAttr.usDisplayOffsetX  = (MMP_USHORT)u16OffsetX;
            stDispAttr.usDisplayOffsetY  = (MMP_USHORT)u16OffsetY;
            stDispAttr.rotatetype        = MMP_DISPLAY_ROTATE_NO_ROTATE;
        #endif
        }

        eRetErr = MMPF_Display_SetWinToDisplay(u8WinID, &stDispAttr);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

        /* Window Scaling */
        stFitrange.fitmode        = sFitMode;
        stFitrange.scalerType     = MMP_SCAL_TYPE_WINSCALER;

        if (AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
        {
            stFitrange.ulInWidth      = CUR_DEV_64AB_W >> 1;
            stFitrange.ulInHeight     = CUR_DEV_64AB_H >> 1;
            stFitrange.ulOutWidth     = (MMP_USHORT)u16DisplayW;
            stFitrange.ulOutHeight    = (MMP_USHORT)u16DisplayH;
        }
        else
        {
        #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
            stFitrange.ulInWidth      = CUR_DEV_64AB_W >> 1;
            stFitrange.ulInHeight     = CUR_DEV_64AB_H >> 1;
            stFitrange.ulOutWidth     = (MMP_USHORT)usDisplayW;
            stFitrange.ulOutHeight    = (MMP_USHORT)usDisplayH;
        #elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
            stFitrange.ulInWidth      = FLOOR16(CUR_DEV_64AB_H >> 1);
            stFitrange.ulInHeight     = (CUR_DEV_64AB_W >> 1);
            stFitrange.ulOutWidth     = (MMP_USHORT)u16DisplayW;
            stFitrange.ulOutHeight    = (MMP_USHORT)u16DisplayH;
        #endif
        }

        stFitrange.ulInGrabX      = 1;
        stFitrange.ulInGrabY      = 1;
        stFitrange.ulInGrabW      = stFitrange.ulInWidth;
        stFitrange.ulInGrabH      = stFitrange.ulInHeight;
        stFitrange.ubChoseLit     = 0;

        eRetErr = MMPF_Scaler_GetGCDBestFitScale(&stFitrange, &stDispGrabctl);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

        eRetErr = MMPF_Display_SetWinScaling(u8WinID, &stFitrange, &stDispGrabctl);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    }
    else //AIT 8451 or AIT8455
    {
        MMP_DISPLAY_WIN_ATTR    winAttr;
        MMP_USHORT              usW = 0;
        MMP_USHORT              usH = 0;

        /* Config YUV */
        switch(m_stAhcHUVCCfg.sYUVResol){
        case UVC_YUV_RESOL_90P:
            usW = 160;
            usH = 90;
            break;
        case UVC_YUV_RESOL_240P:
            usW = 320;
            usH = 240;
            break;
        case UVC_YUV_RESOL_360P:
            usW = 640;
            usH = 360;
            break;
        case UVC_YUV_RESOL_480P:
            usW = 640;
            usH = 480;
            break;
        case UVC_YUV_RESOL_180P:
        default:
            usW = 320;
            usH = 180;
            break;
        }

        ahcRet = AHC_HostUVC_SetWinActive(u8WinID, AHC_FALSE);
        if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet);}

        eRetErr = MMPS_HUVC_GetDecMjpegToPreviewDispAttr(  &u16OldWinID,
                                                        &u16OldOffsetX, &u16OldOffsetY,
                                                        &u16OldWinW,    &u16OldWinH,
                                                        &u16OldDispW,   &u16OldDispH,
                                                        &usDispColor);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

        eRetErr = MMPS_Display_GetWinAttributes(u8WinID, &winAttr);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); }

        if (CAM_CHECK_USB(USB_CAM_AIT) && MMP_GetAitCamStreamType() == AIT_REAR_CAM_STRM_MJPEG_H264) {
            usW = u16OldWinW;
            usH = u16OldWinH;
        }

        /* For NV12 Format */
    #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        winAttr.usWidth             = usW;
        winAttr.usHeight            = usH;
        winAttr.usLineOffset        = winAttr.usWidth;
        winAttr.colordepth          = MMP_DISPLAY_WIN_COLORDEPTH_YUV420_INTERLEAVE;
    #elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        winAttr.usWidth             = FLOOR16(usH);
        winAttr.usHeight            = (usW);
        winAttr.usLineOffset        = (winAttr.usWidth);
        winAttr.colordepth          = MMP_DISPLAY_WIN_COLORDEPTH_YUV420_INTERLEAVE;
    #endif

        //eRetErr = MMPF_Display_SetWinAttributes(u8WinID, &winAttr); // Set GOP by component
        //if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);}

        stDispAttr.bMirror           = MMP_FALSE;
        stDispAttr.usStartX          = 0;
        stDispAttr.usStartY          = 0;

    #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        stDispAttr.usDisplayWidth    = usW;
        stDispAttr.usDisplayHeight   = usH;
        stDispAttr.usDisplayOffsetX  = (MMP_USHORT)usOffsetX;
        stDispAttr.usDisplayOffsetY  = (MMP_USHORT)usOffsetY;
        stDispAttr.rotatetype        = MMP_DISPLAY_ROTATE_NO_ROTATE;
    #elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        stDispAttr.usDisplayWidth    = FLOOR16(usH);
        stDispAttr.usDisplayHeight   = (usW);
        stDispAttr.usDisplayOffsetX  = (MMP_USHORT)u16OffsetX;
        stDispAttr.usDisplayOffsetY  = (MMP_USHORT)u16OffsetY;
        stDispAttr.rotatetype        = MMP_DISPLAY_ROTATE_NO_ROTATE;
    #endif

        eRetErr = MMPF_Display_SetWinToDisplay(u8WinID, &stDispAttr);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

        /* Window Scaling */
        stFitrange.fitmode        = MMP_SCAL_FITMODE_OPTIMAL;
        stFitrange.scalerType     = MMP_SCAL_TYPE_WINSCALER;

    #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        stFitrange.ulInWidth      = usW;
        stFitrange.ulInHeight     = usH;
        stFitrange.ulOutWidth     = (MMP_USHORT)usDisplayW;
        stFitrange.ulOutHeight    = (MMP_USHORT)usDisplayH;
    #elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        stFitrange.ulInWidth      = FLOOR16(usH);
        stFitrange.ulInHeight     = (usW);
        stFitrange.ulOutWidth     = (MMP_USHORT)u16DisplayW;
        stFitrange.ulOutHeight    = (MMP_USHORT)u16DisplayH;
    #endif
        stFitrange.ulInGrabX      = 1;
        stFitrange.ulInGrabY      = 1;
        stFitrange.ulInGrabW      = stFitrange.ulInWidth;
        stFitrange.ulInGrabH      = stFitrange.ulInHeight;
        stFitrange.ubChoseLit     = 0;

        eRetErr = MMPF_Scaler_GetGCDBestFitScale(&stFitrange, &stDispGrabctl);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

        eRetErr = MMPF_Display_SetWinScaling(u8WinID, &stFitrange, &stDispGrabctl);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    }
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetCmitStrmType
//  Description : AP set commit stream type and decide preview stream type
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_SetCmitStrmType(UINT8 u8CmitStrmType)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if (u8CmitStrmType & BM_USB_STRM_MJPEG) {
        m_stAhcHUVCCfg.ubCmitUVCStrmTyp = u8CmitStrmType;
        MMPS_HUVC_SetPrevwStrmTyp(ST_MJPEG);
        ahcRet = AHC_TRUE;
    }
    else if (u8CmitStrmType & BM_USB_STRM_NV12) {
        m_stAhcHUVCCfg.ubCmitUVCStrmTyp = u8CmitStrmType;
        MMPS_HUVC_SetPrevwStrmTyp(ST_NV12);
        ahcRet = AHC_TRUE;
    }
    else {
        AHC_DBG_ERR(1, FG_RED("[ERR] HostUVC_SetCmitStrmType Not support type [%d]\r\n"), u8CmitStrmType);
        ahcRet = AHC_FALSE;
    }
    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_RegisterMDCBFunc
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_RegisterMDCBFunc(void *pvMDFunc)
{
#if (MOTION_DETECTION_EN)
    MMP_ERR eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_USB_RegUVCMDCallBack(pvMDFunc);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_EnableMDTC
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_EnableMDTC(AHC_BOOL bEnableMD)
{
#if (MOTION_DETECTION_EN)
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    if (bEnableMD) {
        eRetErr = MMPS_USB_EnableUVCMD();
    }
    else {
        eRetErr = MMPS_USB_DisableUVCMD();
    }

    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
#endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_ReadSonixDevReg
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_ReadSonixDevReg(UINT16 u16Addr, UINT8 *pu8Data)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    UINT32      u32DataLength = 0;
    UINT8       u8DataSend[8] = {0};
    UINT8       u8DataRet[8] = {0};

    if (!MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) {/* AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); */return AHC_FALSE;}

    // Switch command
    u8DataSend[0] = u16Addr & 0xFF;         // Tag
    u8DataSend[1] = (u16Addr & 0xFF00)>>8;
    u8DataSend[3] = 0xFF;                   // Dummy

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, XU_SONIX_ASIC_CTRL, 4, u8DataSend);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, XU_SONIX_ASIC_CTRL, 4, &u32DataLength, u8DataRet);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    *pu8Data = u8DataRet[2];

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SonixReverseGearDetection
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SonixReverseGearDetection(void)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;
    UINT16      u16Addr = 0;
    UINT8       u8Data = 0;

    if (!MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) {/* AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);*/ return AHC_FALSE;}

    u16Addr = 0x1005;
    ahcRet = AHC_HostUVC_ReadSonixDevReg(u16Addr, &u8Data);
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

    if (u8Data & 0x01) {
        AHC_DBG_MSG(1, "ISO Reverse Gear\r\n");
        return AHC_TRUE;
    }

    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_GetReversingGearStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_GetReversingGearStatus(void)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubDataLen = 0;
    MMP_UBYTE   ubDataBuf[8] = {0};

    if (MMP_IsUSBCamIsoMode()) {
        return AHC_TRUE;
    }

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if ((eRetErr != MMP_ERR_NONE) || (bUVCStates != MMP_TRUE)) {/* AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);*/ return AHC_FALSE;}

    eRetErr = HUVCSetEU1Cmd(SET_CUR_CMD, EU1_SET_MMP, 8, m_XuCmdMmpx2B);
    eRetErr |= HUVCGetEU1Cmd(GET_CUR_CMD, EU1_GET_MMP_RESULT, 8, &ubDataLen, ubDataBuf);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    if (ubDataBuf[0] == 0x01) {
        AHC_DBG_MSG(1, "BULK Reverse Gear\r\n");
        return AHC_TRUE;
    }

    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_ResetFBMemory
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_ResetFBMemory(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    eRetErr = MMPF_USBH_ResetFBMemory();
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_EnumDevice
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_EnumDevice(AHC_BOOL bUsbDeviceIn)
{
    static AHC_BOOL bUsbBdevEnumed = AHC_FALSE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_UBYTE   ubH264ResolMapCFG;

    if (MMP_IsUSBCamIsoMode())
        memcpy((MMP_UBYTE*)m_stAhcHuvcNaluTBL, (MMP_UBYTE*)m_stAhcHuvcNaluTblISO, sizeof(m_stAhcHuvcNaluTBL));
    else
        memcpy((MMP_UBYTE*)m_stAhcHuvcNaluTBL, (MMP_UBYTE*)m_stAhcHuvcNaluTblBulk, sizeof(m_stAhcHuvcNaluTBL));

    if (bUsbDeviceIn) {

        if (bUsbBdevEnumed == AHC_FALSE) {

            MMPF_USBH_ClrDevCFG();

            // Total count is clear by MMPF_USBH_ClrDevCFG. Set it again.
            MMPS_HUVC_SetDevTotalCount(MMPS_3GPRECD_UVC_CFG_MAX_NUM);

            /* Add dev string/CB/TBL, only once at beginning */
            if (MMP_IsUSBCamIsoMode()) {

                eRetErr = MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[0].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb8437, (void *)AHC_HostUVC_StartUVCCb8437, (void *)&(m_stAhcHuvcNaluTBL[0].mNalu[UVC_H264_RES_1080P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[1].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_6300, (void *)AHC_HostUVC_StartUVCCb_PID_6300, (void *)&(m_stAhcHuvcNaluTBL[1].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[2].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_0210, (void *)AHC_HostUVC_StartUVCCb_PID_0210, (void *)&(m_stAhcHuvcNaluTBL[2].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[3].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_64AB, (void *)AHC_HostUVC_StartUVCCb_PID_64AB, (void *)&(m_stAhcHuvcNaluTBL[3].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[4].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_9230, (void *)AHC_HostUVC_StartUVCCb_PID_9230, (void *)&(m_stAhcHuvcNaluTBL[4].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[5].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_2B95, (void *)AHC_HostUVC_StartUVCCb_PID_2B95, (void *)&(m_stAhcHuvcNaluTBL[5].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[6].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_8301, (void *)AHC_HostUVC_StartUVCCb_PID_8301, (void *)&(m_stAhcHuvcNaluTBL[6].mNalu[UVC_H264_RES_360P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[7].ubDevStrInfo,(void *)AHC_HostUVC_OpenUVCCb8328,(void *)AHC_HostUVC_StartUVCCb8328,(void *)&(m_stAhcHuvcNaluTBL[7].mNalu[UVC_H264_RES_1440P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[8].ubDevStrInfo,(void *)AHC_HostUVC_OpenUVCCb_PID_6366,(void *)AHC_HostUVC_StartUVCCb_PID_6366,(void *)&(m_stAhcHuvcNaluTBL[8].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[9].ubDevStrInfo,(void *)AHC_HostUVC_OpenUVCCb8339,(void *)AHC_HostUVC_StartUVCCb8339,(void *)&(m_stAhcHuvcNaluTBL[9].mNalu[UVC_H264_RES_1080P]));

                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[0].ubDevStrInfo, glUvcGuidEUTblISO[0][0], glUvcGuidEUTblISO[0][1], glUvcGuidEUTblISO[0][2], glUvcGuidEUTblISO[0][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[1].ubDevStrInfo, glUvcGuidEUTblISO[1][0], glUvcGuidEUTblISO[1][1], glUvcGuidEUTblISO[1][2], glUvcGuidEUTblISO[1][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[2].ubDevStrInfo, glUvcGuidEUTblISO[2][0], glUvcGuidEUTblISO[2][1], glUvcGuidEUTblISO[2][2], glUvcGuidEUTblISO[2][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[3].ubDevStrInfo, glUvcGuidEUTblISO[3][0], glUvcGuidEUTblISO[3][1], glUvcGuidEUTblISO[3][2], glUvcGuidEUTblISO[3][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[4].ubDevStrInfo, glUvcGuidEUTblISO[4][0], glUvcGuidEUTblISO[4][1], glUvcGuidEUTblISO[4][2], glUvcGuidEUTblISO[4][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[5].ubDevStrInfo, glUvcGuidEUTblISO[5][0], glUvcGuidEUTblISO[5][1], glUvcGuidEUTblISO[5][2], glUvcGuidEUTblISO[5][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[6].ubDevStrInfo, glUvcGuidEUTblISO[6][0], glUvcGuidEUTblISO[6][1], glUvcGuidEUTblISO[6][2], glUvcGuidEUTblISO[6][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[7].ubDevStrInfo, glUvcGuidEUTblISO[7][0], glUvcGuidEUTblISO[7][1], glUvcGuidEUTblISO[7][2], glUvcGuidEUTblISO[7][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[8].ubDevStrInfo, glUvcGuidEUTblISO[8][0], glUvcGuidEUTblISO[8][1], glUvcGuidEUTblISO[8][2], glUvcGuidEUTblISO[8][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[9].ubDevStrInfo, glUvcGuidEUTblISO[9][0], glUvcGuidEUTblISO[9][1], glUvcGuidEUTblISO[9][2], glUvcGuidEUTblISO[9][3]);
            }
            else {
                eRetErr = MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[0].ubDevStrInfo,  (void *)AHC_HostUVC_OpenUVCCb8437, (void *)AHC_HostUVC_StartUVCCb8437, (void *)&(m_stAhcHuvcNaluTBL[0].mNalu[UVC_H264_RES_1080P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[1].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb8437, (void *)AHC_HostUVC_StartUVCCb8451, (void *)&(m_stAhcHuvcNaluTBL[1].mNalu[UVC_H264_RES_1080P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[2].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_0210, (void *)AHC_HostUVC_StartUVCCb_PID_0210, (void *)&(m_stAhcHuvcNaluTBL[2].mNalu[UVC_H264_RES_1080P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[3].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_64AB, (void *)AHC_HostUVC_StartUVCCb_PID_64AB, (void *)&(m_stAhcHuvcNaluTBL[3].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[4].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_9230, (void *)AHC_HostUVC_StartUVCCb_PID_9230, (void *)&(m_stAhcHuvcNaluTBL[4].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[5].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_2B95, (void *)AHC_HostUVC_StartUVCCb_PID_2B95, (void *)&(m_stAhcHuvcNaluTBL[5].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[6].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_8301, (void *)AHC_HostUVC_StartUVCCb_PID_8301, (void *)&(m_stAhcHuvcNaluTBL[6].mNalu[UVC_H264_RES_360P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[7].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb8328,	(void *)AHC_HostUVC_StartUVCCb8328,(void *)&(m_stAhcHuvcNaluTBL[7].mNalu[UVC_H264_RES_1440P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[8].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb_PID_6366,(void *)AHC_HostUVC_StartUVCCb_PID_6366,(void *)&(m_stAhcHuvcNaluTBL[8].mNalu[UVC_H264_RES_720P]));
                eRetErr |= MMPS_HUVC_AddDevCFG((MMP_UBYTE *)m_stAhcHuvcNaluTBL[9].ubDevStrInfo, (void *)AHC_HostUVC_OpenUVCCb8339,	(void *)AHC_HostUVC_StartUVCCb8339,(void *)&(m_stAhcHuvcNaluTBL[9].mNalu[UVC_H264_RES_1080P]));

                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[0].ubDevStrInfo, glUvcGuidEUTblBulk[0][0], glUvcGuidEUTblBulk[0][1], glUvcGuidEUTblBulk[0][2], glUvcGuidEUTblBulk[0][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[1].ubDevStrInfo, glUvcGuidEUTblBulk[1][0], glUvcGuidEUTblBulk[1][1], glUvcGuidEUTblBulk[1][2], glUvcGuidEUTblBulk[1][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[2].ubDevStrInfo, glUvcGuidEUTblBulk[2][0], glUvcGuidEUTblBulk[2][1], glUvcGuidEUTblBulk[2][2], glUvcGuidEUTblBulk[2][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[3].ubDevStrInfo, glUvcGuidEUTblBulk[3][0], glUvcGuidEUTblBulk[3][1], glUvcGuidEUTblBulk[3][2], glUvcGuidEUTblBulk[3][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[4].ubDevStrInfo, glUvcGuidEUTblBulk[4][0], glUvcGuidEUTblBulk[4][1], glUvcGuidEUTblBulk[4][2], glUvcGuidEUTblBulk[4][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[5].ubDevStrInfo, glUvcGuidEUTblBulk[5][0], glUvcGuidEUTblBulk[5][1], glUvcGuidEUTblBulk[5][2], glUvcGuidEUTblBulk[5][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[6].ubDevStrInfo, glUvcGuidEUTblBulk[6][0], glUvcGuidEUTblBulk[6][1], glUvcGuidEUTblBulk[6][2], glUvcGuidEUTblBulk[6][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[7].ubDevStrInfo, glUvcGuidEUTblBulk[7][0], glUvcGuidEUTblBulk[7][1], glUvcGuidEUTblBulk[7][2], glUvcGuidEUTblBulk[7][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[8].ubDevStrInfo, glUvcGuidEUTblBulk[8][0], glUvcGuidEUTblBulk[8][1], glUvcGuidEUTblBulk[8][2], glUvcGuidEUTblBulk[8][3]);
                eRetErr |= MMPS_HUVC_RegDevAddiCFG(MMP_USBH_REG_TYP_GUID_EU, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[9].ubDevStrInfo, glUvcGuidEUTblBulk[9][0], glUvcGuidEUTblBulk[9][1], glUvcGuidEUTblBulk[9][2], glUvcGuidEUTblBulk[9][3]);

            }

            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

            eRetErr = MMPS_USB_EnumUVC();
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

            bUsbBdevEnumed = AHC_TRUE;

            ahcRet = AHC_HostUVC_GetDevChipInfo((UINT32 *)&gUsbh_UvcDevInfo.ulVIDPID);
            if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE;}

            if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) & VID_RECD_ENCODE_H264) {

                if (!gUsbh_UvcDevInfo.bParseDone) {
                    AHC_DBG_ERR(1, "gUsbh_UvcDevInfo.bParseDone FALSE\r\n");
                    return AHC_FALSE;
                }

                if ((gUsbh_UvcDevInfo.wPrevwMaxWidth == 640) && (gUsbh_UvcDevInfo.wPrevwMaxHeight == 480)) {
                    ubH264ResolMapCFG = UVC_H264_RES_360P; //TBD.  Need to decide 4:3 or 16:9.
                }
                else if ((gUsbh_UvcDevInfo.wPrevwMaxWidth == 720) && (gUsbh_UvcDevInfo.wPrevwMaxHeight == 480)) {
                    ubH264ResolMapCFG = UVC_H264_RES_480P;
                }
                else if ((gUsbh_UvcDevInfo.wPrevwMaxWidth == 1280) && (gUsbh_UvcDevInfo.wPrevwMaxHeight == 720)) {
                    ubH264ResolMapCFG = UVC_H264_RES_720P;
                }
                else if ((gUsbh_UvcDevInfo.wPrevwMaxWidth == 1920) && (gUsbh_UvcDevInfo.wPrevwMaxHeight == 1080)) {
                    ubH264ResolMapCFG = UVC_H264_RES_1080P;
                }
                else {
                    AHC_DBG_ERR(1, "UnSupport H264 Resolution\r\n");
                    return AHC_FALSE;
                }

                eRetErr  = MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[0].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[0].mNalu[ubH264ResolMapCFG]));
                eRetErr |= MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[1].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[1].mNalu[ubH264ResolMapCFG]));
                eRetErr |= MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[2].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[2].mNalu[ubH264ResolMapCFG]));
                eRetErr |= MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[3].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[3].mNalu[ubH264ResolMapCFG]));
                eRetErr |= MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[4].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[4].mNalu[ubH264ResolMapCFG]));
                eRetErr |= MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[5].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[5].mNalu[ubH264ResolMapCFG]));
                eRetErr |= MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[6].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[6].mNalu[ubH264ResolMapCFG]));
                if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

                AHC_DBG_MSG(1, "HUVC Search W [%d] H [%d]\r\n", gUsbh_UvcDevInfo.wPrevwMaxWidth, gUsbh_UvcDevInfo.wPrevwMaxHeight);
            }

            if (MMP_IsUSBCamIsoMode()) {
                if ((gUsbh_UvcDevInfo.ulVIDPID == 0x83011B3F) ||
                    (gUsbh_UvcDevInfo.ulVIDPID == 0x64AB0C45 && gUsbh_UvcDevInfo.wSzConfigDesc == 0x3EE) ||
                    (gUsbh_UvcDevInfo.ulVIDPID == 0x64AB0C45 && gUsbh_UvcDevInfo.wSzConfigDesc == 0x1EE)) {
                    MMPF_USBH_CheckJpegEOIEveryPacketEnable(MMP_TRUE);
                }
                else {
                    MMPF_USBH_CheckJpegEOIEveryPacketEnable(MMP_FALSE);
                }
            }
        }
    }
    else {
        bUsbBdevEnumed = AHC_FALSE;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetIdleStates
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetIdleStates(void)
{
    MMP_BOOL    bUVCStates = MMP_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;

    eRetErr = MMPS_USB_GetDevConnSts(&bUVCStates);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    if (bUVCStates != MMP_TRUE) { return AHC_TRUE;}

    ahcRet = AHC_HostUVC_IsDevEnabled();
    // UVC preview is still working!
    if (ahcRet == AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPF_USBH_StopCheckDevAliveTimer();
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_InitStreamSetting
//  Description : AP set UVC record & preview video setting // CHECK
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_InitStreamSetting(  UVC_H264_RES_IDX       eH264Resol,
                                                UVC_FRAMERATE_INDEX    eFrameRate,
                                                UVC_H264_QUALITY_INDEX eH264Quality,
                                                UINT16                 u16PFrameCnt,
                                                UVC_YUV_RESOL_INDEX    eYUVResol)
{
    MMPS_3GPRECD_PRESET_CFG    *pstVidCfg           = MMPS_3GPRECD_GetPresetCfg();
    MMP_UBYTE                   ubUVCYUVFrmRate     = 30;
    MMP_UBYTE                   ubUVCH264Resol      = VIDRECD_RESOL_1920x1088;
    MMP_UBYTE                   ubUVCH264Quality    = VIDRECD_QUALITY_HIGH;
    MMP_UBYTE                   ubUVCH264FrmRateIdx = VIDRECD_FRAMERATE_30FPS;
    MMP_USHORT                  usBps10k = 0;
    MMP_USHORT                  usW = 0;
    MMP_USHORT                  usH = 0;
    MMP_BOOL                    bStatus = MMP_HIF_ERR_PARAMETER;
    MMP_ERR                     eRetErr = MMP_ERR_NONE;
    AHC_BOOL                    ahcRet = AHC_TRUE;
    MMP_ULONG                   ulMjpgBitrate = INIT_DEV_MJPEG_BITRATE;

	//printc(FG_YELLOW("AHC_HostUVC_InitStreamSetting: %d, %d, %d, %d\r\n"), eH264Resol, eFrameRate, u16PFrameCnt, eYUVResol);

    if (MMP_IsUSBCamIsoMode())
        memcpy((MMP_UBYTE*)m_stAhcHuvcNaluTBL, (MMP_UBYTE*)m_stAhcHuvcNaluTblISO, sizeof(m_stAhcHuvcNaluTBL));
    else
        memcpy((MMP_UBYTE*)m_stAhcHuvcNaluTBL, (MMP_UBYTE*)m_stAhcHuvcNaluTblBulk, sizeof(m_stAhcHuvcNaluTBL));

    eRetErr = MMPS_USB_GetUVCStreamSts(&bStatus);
    if (eRetErr != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "[ERR] USB_GetUVCStreamSts\r\n");
        return AHC_FALSE;
    }
    if (bStatus == MMP_TRUE) {
        AHC_DBG_ERR(1, "[ERR] UVC Stream is ON, Stop record/preview/stream first\r\n");
        return AHC_FALSE;
    }

    m_stAhcHUVCCfg.sH264Resol     = eH264Resol;
    m_stAhcHUVCCfg.sFrameRate     = eFrameRate;
    m_stAhcHUVCCfg.sH264Quality   = eH264Quality;
    m_stAhcHUVCCfg.usPFrameCnt    = u16PFrameCnt;
    m_stAhcHUVCCfg.sYUVResol      = eYUVResol;

    switch(eFrameRate){
    case UVC_FRAMERATE_10FPS:
        ubUVCH264FrmRateIdx = VIDRECD_FRAMERATE_10FPS;
        break;
    case UVC_FRAMERATE_15FPS:
        ubUVCH264FrmRateIdx = VIDRECD_FRAMERATE_15FPS;
        break;
    case UVC_FRAMERATE_20FPS:
        ubUVCH264FrmRateIdx = VIDRECD_FRAMERATE_20FPS;
        break;
    case UVC_FRAMERATE_25FPS:
        ubUVCH264FrmRateIdx = VIDRECD_FRAMERATE_25FPS;
        break;
    case UVC_FRAMERATE_30FPS:
    default:
        ubUVCH264FrmRateIdx = VIDRECD_FRAMERATE_30FPS;
        break;
    }

    /* Configure YUV Stream */
    ubUVCYUVFrmRate = pstVidCfg->stFrameRate[ubUVCH264FrmRateIdx].ulTimeResol / pstVidCfg->stFrameRate[ubUVCH264FrmRateIdx].ulTimeIncre;

    switch(eYUVResol) {
    case UVC_YUV_RESOL_90P:
        m_XuCmdMmpx0B[1] = 0x12;
        usW = 160;
        usH = 90;
        break;
    case UVC_YUV_RESOL_240P:
        m_XuCmdMmpx0B[1] = 0x02;
        usW = 320;
        usH = 240;
        break;
    case UVC_YUV_RESOL_360P:
        m_XuCmdMmpx0B[1] = 0x0D;
        usW = 640;
        usH = 360;
        break;
    case UVC_YUV_RESOL_480P:
        m_XuCmdMmpx0B[1] = 0x03;
        usW = 640;
        usH = 480;
        break;
    case UVC_YUV_RESOL_180P:
    default:
        m_XuCmdMmpx0B[1] = 0x13;
        usW = 320;
        usH = 180;
        break;
    }

#if 1 // For AIT MJPEG+H264 or NV12+H264 format
    MMPS_HUVC_SetPrevwResol(usW, usH);

    /* Configure MJPEG Stream */
    if (m_stAhcHUVCCfg.ubCmitUVCStrmTyp & BM_USB_STRM_MJPEG)
    {
        /* Fill ST_MJPEG (W, H, bps, FPS) instead of YUV if commit */
        m_XuCmdMmpx23_yuv[1] = USB_STRM_ID_MJPEG;
        m_XuCmdMmpx25_yuv[1] = USB_STRM_TYP_MJPEG;

        switch(m_stAhcHUVCCfg.sMjpegResol) {
        case UVC_MJPEG_RESOL_90P:
            m_XuCmdMmpx0B[1] = 0x12;
            usW = 160;
            usH = 90;
            ulMjpgBitrate = 100000;
            break;
        case UVC_MJPEG_RESOL_180P:
            m_XuCmdMmpx0B[1] = 0x13;
            usW = 320;
            usH = 180;
            ulMjpgBitrate = 300000;
            break;
        case UVC_MJPEG_RESOL_360P:
            m_XuCmdMmpx0B[1] = 0x0D;
            usW = 640;
            usH = 360;
            ulMjpgBitrate = 900000;
            break;
        case UVC_MJPEG_RESOL_720P:
        default:
            m_XuCmdMmpx0B[1] = 0x0A;
            usW = 1280;
            usH = 720;
            ulMjpgBitrate = 1000000;
            break;
        }

        if (gUsbh_UvcMjpegWifiCfg.bEnWiFi) { // CHECK

            MMP_ULONG ulFpsx10  = 300;
            MMP_ULONG ulBitRate = 5000000;

            /* TBD: CarDV no such flow, start MJPEG WiFi before start local preview */
            AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_BITRATE, &ulBitRate);
            AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_FRAME_RATEx10, &ulFpsx10);

            ubUVCYUVFrmRate = m_stAhcHUVCCfg.usMjpegFps = ulFpsx10 / 10;
            usBps10k = ulBitRate / 10000;

            /* TBD: 8451 can not assign arbitrary resolution */
            m_XuCmdMmpx0B[1] = 0x0D; /* 360p */
            usW = gUsbh_UvcMjpegWifiCfg.dwTargetWidth;
            usH = gUsbh_UvcMjpegWifiCfg.dwTargetHeight;
        }
        else {
            m_stAhcHUVCCfg.usMjpegFps = INIT_DEV_MJPEG_FPS;
            m_stAhcHUVCCfg.ulMjpegkbps = ulMjpgBitrate/1000;
            usBps10k = ulMjpgBitrate/10000;
        }

        m_XuCmdMmpx0C_8451[1] = 0x8A;
    }

    /* Configure NV12 Stream */
    if (m_stAhcHUVCCfg.ubCmitUVCStrmTyp & BM_USB_STRM_NV12)
    {
        m_XuCmdMmpx23_yuv[1] = USB_STRM_ID_YUV;
        m_XuCmdMmpx25_yuv[1] = USB_STRM_TYP_NV12;

        usBps10k = ((usW*usH*3)>>1)/10000;

        m_XuCmdMmpx0C_8451[1] = 0x87;
    }
#endif

    m_XuCmdMmpx0B[2] = m_XuCmdMmpx25_yuv[2] = usW & 0xFF;
    m_XuCmdMmpx0B[3] = m_XuCmdMmpx25_yuv[3] = (usW >> 8) & 0xFF;
    m_XuCmdMmpx0B[4] = m_XuCmdMmpx25_yuv[4] = usH & 0xFF;
    m_XuCmdMmpx0B[5] = m_XuCmdMmpx25_yuv[5] = (usH >> 8) & 0xFF;
    m_XuCmdMmpx25_yuv[6] = ubUVCYUVFrmRate & 0x1F;
    //m_XuCmdMmpx25_yuv[6] = (ubUVCYUVFrmRate & 0x1F)|((usBps10k<<5) & 0xE0); //For AIT MJ+H264 format
    //m_XuCmdMmpx25_yuv[7] = (usBps10k>>3) & 0xFF;

    eRetErr = MMPS_HUVC_SetPrevwResol(usW, usH);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = MMPS_HUVC_SetPrevwFrameRate(ubUVCYUVFrmRate);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    /* Configure H264 Stream */
    switch(eH264Resol){
    case UVC_H264_RES_360P:
        if (MMP_IsUSBCamIsoMode()) {
            ubUVCH264Resol = VIDRECD_RESOL_640x480; // Force as 4:3.
            usW = 640;
            usH = 480;
        }
        else {
            ubUVCH264Resol = VIDRECD_RESOL_640x368;
            m_VsCommitCtl_8451[3] = 0x07;
            usW = 640;
            usH = 360;
        }
        break;
    case UVC_H264_RES_720P:
        ubUVCH264Resol = VIDRECD_RESOL_1280x720;
        m_VsCommitCtl_8451[3] = 0x01;
        usW = 1280;
        usH = 720;
        break;
    case UVC_H264_RES_1080P:
    default:
        ubUVCH264Resol = VIDRECD_RESOL_1920x1088;
        m_VsCommitCtl_8451[3] = 0x01;
        usW = 1920;
        usH = 1080;
        break;
    }

    switch(eH264Quality){
    case UVC_H264_QUALITY_LOW:
        ubUVCH264Quality = VIDRECD_QUALITY_LOW;
        break;
    case UVC_H264_QUALITY_MID:
        ubUVCH264Quality = VIDRECD_QUALITY_MID;
        break;
    case UVC_H264_QUALITY_HIGH:
    default:
        ubUVCH264Quality = VIDRECD_QUALITY_HIGH;
        break;
    }

    m_XuCmdMmpx25_h264[2] = usW & 0xFF;
    m_XuCmdMmpx25_h264[3] = (usW >> 8) & 0xFF;
    m_XuCmdMmpx25_h264[4] = usH & 0xFF;
    m_XuCmdMmpx25_h264[5] = (usH >> 8) & 0xFF;
    #ifdef AHC_VIDEO_REAR_CAM_BITRATE
    usBps10k = AHC_VIDEO_REAR_CAM_BITRATE/10000;
    #else
    usBps10k = (pstVidCfg->ulFps30BitrateMap[ubUVCH264Resol][ubUVCH264Quality]/10000);
    #endif

    m_XuCmdMmpx25_h264[6] = ((pstVidCfg->stFrameRate[ubUVCH264FrmRateIdx].ulTimeResol /
                              pstVidCfg->stFrameRate[ubUVCH264FrmRateIdx].ulTimeIncre) & 0x1F) | ((usBps10k << 5) & 0xE0);
    m_XuCmdMmpx25_h264[7] = (usBps10k >> 3) & 0xFF;

    m_XuCmdIspx02[1] = ((pstVidCfg->stFrameRate[ubUVCH264FrmRateIdx].ulTimeResol /
                         pstVidCfg->stFrameRate[ubUVCH264FrmRateIdx].ulTimeIncre) & 0xFF);

    m_XuCmdIspx08_8451[2] = (10 * usBps10k)     & 0xFF;
    m_XuCmdIspx08_8451[3] = (10 * usBps10k>>8)  & 0xFF;
    m_XuCmdIspx08_8451[4] = (10 * usBps10k>>16) & 0xFF;
    m_XuCmdIspx08_8451[5] = (10 * usBps10k>>24) & 0xFF;

    m_XuCmdMmpx09_h264[1] = u16PFrameCnt & 0xFF;
    m_XuCmdMmpx09_h264[2] = (u16PFrameCnt>>8) & 0xFF;
    m_XuCmdMmpx09_h264[3] = 0;
    m_XuCmdMmpx09_h264[4] = 0;

    eRetErr = MMPS_HUVC_SetUVCRecdResol(ubUVCH264Resol);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    #ifdef AHC_VIDEO_REAR_CAM_BITRATE
    eRetErr = MMPS_HUVC_SetRecdBitrate(AHC_VIDEO_REAR_CAM_BITRATE);
    #else
    eRetErr = MMPS_HUVC_SetRecdBitrate(pstVidCfg->ulFps30BitrateMap[ubUVCH264Resol][ubUVCH264Quality]);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    #endif

    eRetErr = MMPS_HUVC_SetRecdFrameRate(pstVidCfg->stFrameRate[ubUVCH264FrmRateIdx].ulTimeIncre, pstVidCfg->stFrameRate[ubUVCH264FrmRateIdx].ulTimeResol);
    if( eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = MMPS_HUVC_SetRecdPFrameCount(u16PFrameCnt);
    if (eRetErr != MMP_ERR_NONE ) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    /* Update Start UVC TBL */
    eRetErr = MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[0].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[0].mNalu[eH264Resol]));
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[1].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[1].mNalu[eH264Resol]));
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[2].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[2].mNalu[eH264Resol]));
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_NALU_TBL, (MMP_UBYTE *)m_stAhcHuvcNaluTBL[3].ubDevStrInfo, (void *)&(m_stAhcHuvcNaluTBL[3].mNalu[eH264Resol]));
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    #if (MOTION_DETECTION_EN)
    if (CAM_CHECK_USB(USB_CAM_AIT)) {
        ahcRet = AHC_HostUVC_RegisterMDCBFunc((void *) VRMotionDetectCB);
        if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); }
    }
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetScdRecdSetting
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_SetScdRecdSetting(void)
{
    UINT16                  u16EncW = 1280, u16EncH = 720;
    MMP_USHORT              usResoIdx       = VIDRECD_RESOL_1280x720;
    VIDENC_PROFILE          eProfile        = H264ENC_MAIN_PROFILE;
    MMPS_3GPRECD_FRAMERATE  stSnrFps        = {1001, 30000};
    MMPS_3GPRECD_FRAMERATE  stEncFps        = {1001, 30000};
    MMPS_3GPRECD_FRAMERATE  stMgrFps        = {1001, 30000};
    MMP_USHORT              usQuality       = VIDRECD_QUALITY_HIGH;
    MMP_USHORT              usPFrameCount   = 14, usBFrameCount = 0;
    MMP_UBYTE               ubRecdSel       = MMPS_VR_SCD_RECD;
    UVC_DEVICE_NAME_INDEX   eUVCDevIdx;
    AHC_BOOL                bSlowMotionEn = AHC_FALSE;
    AHC_BOOL                bVideoTimeLapseEn = AHC_FALSE;
    UINT32                  u32SlowMotionTimeIncrement = 0, u32SlowMotionTimeResol = 0;
    UINT32                  u32TimeLapseTimeIncrement = 0, u32TimeLapseTimeResol = 0;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    AHC_BOOL                ahcRet = AHC_TRUE;

    if (!(AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_TRUE) & VID_RECD_ENCODE_H264)) {
        return ahcRet;
    }

    ahcRet = AHC_HostUVC_GetDevChipName(&eUVCDevIdx);
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return ahcRet;}

    if ((gUsbh_UvcDevInfo.wPrevwMaxWidth == 640) && (gUsbh_UvcDevInfo.wPrevwMaxHeight == 480)) {
        u16EncW = 640;
        u16EncH = 480;
    }
    else if ((gUsbh_UvcDevInfo.wPrevwMaxWidth == 720) && (gUsbh_UvcDevInfo.wPrevwMaxHeight == 480)) {
        u16EncW = 720;
        u16EncH = 480;
    }
    else if ((gUsbh_UvcDevInfo.wPrevwMaxWidth == 1280) && (gUsbh_UvcDevInfo.wPrevwMaxHeight == 720)) {
        u16EncW = 1280;
        u16EncH = 720;
    }
    else if ((gUsbh_UvcDevInfo.wPrevwMaxWidth == 1920) && (gUsbh_UvcDevInfo.wPrevwMaxHeight == 1080)) {
        u16EncW = 1920;
        u16EncH = 1080;
    }
    else {
        AHC_DBG_ERR(1, "[ERR] UnSupport HUVC Recd Resolution\r\n");
        return ahcRet;
    }

    AHC_VIDEO_GetSlowMotionFPS(&bSlowMotionEn, &u32SlowMotionTimeIncrement, &u32SlowMotionTimeResol);
#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
    AHC_VIDEO_GetTimeLapseFPS(&bVideoTimeLapseEn, &u32TimeLapseTimeIncrement, &u32TimeLapseTimeResol);
#endif

    switch (MenuSettingConfig()->uiMOVQuality) {
    case QUALITY_SUPER_FINE:
        usQuality = VIDRECD_QUALITY_HIGH;
        break;
    case QUALITY_FINE:
        usQuality = VIDRECD_QUALITY_MID;
        break;
    default:
        usQuality = VIDRECD_QUALITY_HIGH;
        break;
    }

    /* Set Video Record Attribute */
    eRetErr = MMPS_3GPRECD_SetProfile(ubRecdSel, eProfile);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    stSnrFps.ulTimeIncre = 30000 / (10000000 / m_ulFrameInterval);
    stSnrFps.ulTimeResol = 30000;
    stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
    stMgrFps.ulTimeResol = stSnrFps.ulTimeResol;

    if (bSlowMotionEn) {
        // Slow Motion Record
        stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stMgrFps.ulTimeResol = u32SlowMotionTimeResol;
        if ((stSnrFps.ulTimeIncre * stSnrFps.ulTimeResol) < (stMgrFps.ulTimeIncre * stMgrFps.ulTimeResol)){
            AHC_DBG_ERR(1, FG_RED("SlowMotion Error!%d,%d,%d,%d\r\n"),
                        stSnrFps.ulTimeIncre, stSnrFps.ulTimeResol, stMgrFps.ulTimeIncre, stMgrFps.ulTimeResol);
            stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
            stMgrFps.ulTimeResol = stSnrFps.ulTimeResol;
        }
    }
    else {
        // Normal Record (Non-Slow Motion)
        stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stMgrFps.ulTimeResol = stSnrFps.ulTimeResol;
    }

    if (bVideoTimeLapseEn) {
        // Time Lapse Record
        stEncFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stEncFps.ulTimeResol = u32TimeLapseTimeResol;
        if ((stSnrFps.ulTimeIncre * stSnrFps.ulTimeResol) < (stEncFps.ulTimeIncre * stEncFps.ulTimeResol)){
            AHC_DBG_ERR(1, FG_RED("VideoTimeLapse Error!%d,%d,%d,%d\r\n"),
                        stSnrFps.ulTimeIncre, stSnrFps.ulTimeResol, stEncFps.ulTimeIncre, stEncFps.ulTimeResol);
            stEncFps.ulTimeIncre = stSnrFps.ulTimeIncre;
            stEncFps.ulTimeResol = stSnrFps.ulTimeResol;
        }
    }
    else {
        // Normal Record (Non-VideoTimeLapse)
        stEncFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stEncFps.ulTimeResol = stSnrFps.ulTimeResol;
    }

    eRetErr = MMPS_3GPRECD_SetFrameRatePara(ubRecdSel, &stSnrFps, &stEncFps, &stMgrFps);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = MMPS_3GPRECD_SetBitrate(ubRecdSel, MMPS_3GPRECD_GetPresetCfg()->ulFps30BitrateMap[usResoIdx][usQuality]);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = MMPS_3GPRECD_SetPFrameCount(ubRecdSel, usPFrameCount);
    if (eRetErr != MMP_ERR_NONE){  AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    eRetErr = MMPS_3GPRECD_SetBFrameCount(ubRecdSel, usBFrameCount);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

    ahcRet = AHC_VIDEO_SetRecdResol(gsAhcScdSensor, u16EncW, u16EncH);

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_SetDeviceEnable
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_HostUVC_SetDeviceEnable(AHC_BOOL bEnable)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) & VID_RECD_ENCODE_H264) {
        m_bAhcUVCDeviceEnabled = bEnable;
    }
    else if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) == VID_RECD_STORE_FILE) {
        #if (UVC_VIDRECD_SUPPORT)
        if (AHC_TRUE == bEnable) {
            eRetErr = MMPS_HUVC_SetUVCRecdSupport(MMP_TRUE);
        }
        else {
            eRetErr = MMPS_HUVC_SetUVCRecdSupport(MMP_FALSE);
        }
        #endif
    }

    if (eRetErr != MMP_ERR_NONE) {
        AHC_DBG_ERR(1, "[ERR] HostUVC_SetDevEnable\r\n");
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_IsDevEnabled
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_IsDevEnabled(void)
{
    if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) & VID_RECD_ENCODE_H264) {
        return m_bAhcUVCDeviceEnabled;
    }
    else if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) == VID_RECD_STORE_FILE) {
        #if (UVC_VIDRECD_SUPPORT)
        MMP_BOOL bUVCVideoEnable = AHC_FALSE;

        MMPS_HUVC_GetUVCRecdSupport(&bUVCVideoEnable);
        if (bUVCVideoEnable == MMP_FALSE) {
            return AHC_FALSE;
        }
        #endif
        return AHC_TRUE;
    }

    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_RecordStart
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_RecordStart(void)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;

    if (!MMP_IsUSBCamExist()) {
        return AHC_TRUE;
    }

    if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) & VID_RECD_ENCODE_H264) {
        ahcRet = AHC_HostUVC_SetScdRecdSetting();

        eRetErr = MMPS_3GPRECD_StartScdRecd();
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }
    else if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) == VID_RECD_STORE_FILE) {
        #if (UVC_VIDRECD_SUPPORT)
        eRetErr = MMPS_HUVC_EnableRecd();
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        #endif
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_RecordStop
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_RecordStop(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (!MMP_IsUSBCamExist()) {
        return AHC_TRUE;
    }

    if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) & VID_RECD_ENCODE_H264) {
        // NOP, Stop flow is inside MMPS_3GPRECD_StopAllRecord()
    }
    else if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) == VID_RECD_STORE_FILE) {
        #if (UVC_VIDRECD_SUPPORT)
        eRetErr = MMPS_HUVC_StopRecd();
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        /* Close record script */
        CloseScript(COMPO_SCRIPT_VR_USBH_UVC_RECD);
        #endif
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : _AHC_HostUVC_PreviewStart
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL _AHC_HostUVC_PreviewStart(void)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;

    eRetErr = MMPS_HUVC_StartPreview();
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE; }

    #ifdef CUS_CFG_UVC_OSD_TEXT
    ahcRet = AHC_HostUVC_SetOSD(CUS_CFG_UVC_OSD_TEXT, 30, 30, UVC_XU_OSD_TEXT_ENABLE);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return AHC_FALSE; }
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : _AHC_HostUVC_PreviewStop
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL _AHC_HostUVC_PreviewStop(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_HUVC_StopPreview();
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE; }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_PreviewStart
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_PreviewStart(UINT8 u8UiMode, UINT32 ulFlickerMode)
{
#if (UVC_HOST_VIDEO_ENABLE)

    USB_DETECT_PHASE        eUSBCurStates = 0;
    UINT32                  u32USBTimeOut = 80;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    UINT8                   u8UVCPframeCount = 30;
    UINT8                   u8UVCPreviewRes  = UVC_YUV_RESOL_180P;
    AHC_BOOL                ahcRet = AHC_TRUE;
    UVC_DEVICE_NAME_INDEX   eUVCDevIdx = UVC_DEVICE_NAME_NONE;

    if (!MMP_IsUSBCamExist()) {
        return AHC_TRUE;
    }

    #ifdef CUSTOMER_CONFIG_UVC_PFRAME
    u8UVCPframeCount = CUSTOMER_CONFIG_UVC_PFRAME;
    #endif

    #ifdef CUSTOMER_CONFIG_UVC_PREVIEW_RES
    u8UVCPreviewRes = CUSTOMER_CONFIG_UVC_PREVIEW_RES;
    #endif

    /* Wait until rear camera enumerates done */
    do {
        AHC_OS_SleepMs(10);
        AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);
    } while (((eUSBCurStates == USB_DETECT_PHASE_OTG_SESSION) ||
             (eUSBCurStates == USB_DETECT_PHASE_CHECK_CONN)) && (--u32USBTimeOut > 0));

    if (0 == u32USBTimeOut) {
        AHC_DBG_ERR(1, "No UVC device connected [%x]\r\n", eUSBCurStates);
    }

    AHC_USBDetectSetPriority(AHC_FALSE); // Set USB detection as low priority work after first preview.

    if (eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) {

        ahcRet = AHC_HostUVC_SetDeviceEnable(AHC_TRUE);

        ahcRet = AHC_HostUVC_GetDevChipName(&eUVCDevIdx);
        if (ahcRet != AHC_TRUE) {
            AHC_DBG_ERR(1, "ERR : HostUVC_GetDevChipName\r\n");
        }

        /* Initial Stream Type and Setting */
        if (MMP_IsUSBCamIsoMode()) {

            ahcRet = AHC_HostUVC_SetCmitStrmType(BM_USB_STRM_MJPEG);

            if (eUVCDevIdx == UVC_DEVICE_NAME_PID_0210 ||
                eUVCDevIdx == UVC_DEVICE_NAME_PID_64AB ||
                eUVCDevIdx == UVC_DEVICE_NAME_PID_9230 ||
                eUVCDevIdx == UVC_DEVICE_NAME_PID_2B95) {
                AHC_HostUVC_InitStreamSetting(UVC_H264_RES_720P, UVC_FRAMERATE_25FPS, UVC_H264_QUALITY_HIGH, 25, UVC_YUV_RESOL_180P);
            }
            else if (eUVCDevIdx == UVC_DEVICE_NAME_PID_6300 ||
                     eUVCDevIdx == UVC_DEVICE_NAME_PID_8301) {
                AHC_HostUVC_InitStreamSetting(UVC_H264_RES_360P, UVC_FRAMERATE_25FPS, UVC_H264_QUALITY_HIGH, 25, UVC_YUV_RESOL_180P);
            }
            else {
                AHC_HostUVC_SetDeviceEnable(AHC_FALSE);
                AHC_DBG_ERR(1, FG_RED("ERR : Not Support ISO Device\r\n"));
            }
        }
        else {

            if (MMP_GetAitCamStreamType() == AIT_REAR_CAM_STRM_MJPEG_H264) {
                AHC_HostUVC_SetCmitStrmType(BM_USB_STRM_MJPEG | BM_USB_STRM_H264);
            }
            else if (MMP_GetAitCamStreamType() == AIT_REAR_CAM_STRM_NV12_H264) {
                AHC_HostUVC_SetCmitStrmType(BM_USB_STRM_NV12 | BM_USB_STRM_H264);
            }

            if (eUVCDevIdx == UVC_DEVICE_NAME_8437 || eUVCDevIdx == UVC_DEVICE_NAME_PID_8328 || eUVCDevIdx == UVC_DEVICE_NAME_PID_8339) {

                if (AHC_HostUVC_IsDecMjpeg2Prevw()) {
                    if (MMP_GetAitCamStreamType() == AIT_REAR_CAM_STRM_MJPEG_H264) {
                        m_stAhcHUVCCfg.sMjpegResol = UVC_MJPEG_RESOL_720P;
                    }
                }
                else {
                    AHC_HostUVC_SetNV12Mirror(MMP_TRUE);
                }

                if (MMP_GetAitCamStreamType() == AIT_REAR_CAM_STRM_NV12_H264) {
                    AHC_HostUVC_InitStreamSetting(UVC_H264_RES_1080P, UVC_FRAMERATE_30FPS, UVC_H264_QUALITY_HIGH, u8UVCPframeCount, UVC_YUV_RESOL_480P);
                }
                else {
                	if(eUVCDevIdx == UVC_DEVICE_NAME_8437)
                		AHC_HostUVC_InitStreamSetting(UVC_H264_RES_1080P, UVC_FRAMERATE_30FPS, UVC_H264_QUALITY_LOW, u8UVCPframeCount, u8UVCPreviewRes);
                	else if(eUVCDevIdx == UVC_DEVICE_NAME_PID_8328)
                		AHC_HostUVC_InitStreamSetting(UVC_H264_RES_1440P, UVC_FRAMERATE_30FPS, UVC_H264_QUALITY_MID, u8UVCPframeCount, u8UVCPreviewRes);
                	else if(eUVCDevIdx == UVC_DEVICE_NAME_PID_8339)
                		AHC_HostUVC_InitStreamSetting(UVC_H264_RES_1080P, UVC_FRAMERATE_30FPS, UVC_H264_QUALITY_MID, u8UVCPframeCount, u8UVCPreviewRes);
                }
            }
            else if (eUVCDevIdx == UVC_DEVICE_NAME_8451) {
                AHC_HostUVC_InitStreamSetting(UVC_H264_RES_720P, UVC_FRAMERATE_30FPS, UVC_H264_QUALITY_HIGH, u8UVCPframeCount, u8UVCPreviewRes);
            }
            else {
                AHC_HostUVC_SetDeviceEnable(AHC_FALSE);
                AHC_DBG_ERR(1, FG_RED("ERR : Not Support Bulk Device\r\n"));
            }
        }

        if (AHC_TRUE == AHC_HostUVC_IsDevEnabled()) {

            if (COMMON_FLICKER_50HZ == ulFlickerMode)
                AHC_HostUVC_SetFlicker(UVC_FLICKER_50HZ);
            else
                AHC_HostUVC_SetFlicker(UVC_FLICKER_60HZ);

            if (MMP_IsSupportDecMjpegToPreview())
            {
                MMP_USHORT usW = 0, usH = 0;

                eRetErr = MMPS_HUVC_SetDecMjpegToPreviewSrcAttr(gUsbh_UvcDevInfo.wPrevwMaxWidth, gUsbh_UvcDevInfo.wPrevwMaxHeight);
                eRetErr |= MMPS_HUVC_GetDecMjpegToPreviewSrcAttr(&usW, &usH);

                AHC_VIDEO_SetRecdResol(gsAhcScdSensor, usW, usH);
                AHC_Capture_SetImageSize(gsAhcScdSensor, usW, usH);

                if (u8UiMode == AHC_HUVC_UI_MODE_VR) {
                    eRetErr |= MMPS_HUVC_InitVRDecMjpegToPreview(usW, usH);

                    eRetErr |= MMPS_HUVC_VRDecMjpegPreviewStart();
                    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
                }
                else {
                    eRetErr |= MMPS_HUVC_InitDscDecMjpegToPreview(usW, usH);

                    eRetErr |= MMPS_HUVC_DscDecMjpegPreviewStart();
                    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
                }
            }
        }
    }

    AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);

    if ((eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) && (AHC_TRUE == AHC_HostUVC_IsDevEnabled())){

        #if (SUPPORT_PARKINGMODE == PARKINGMODE_NONE)
        if (MenuSettingConfig()->uiMotionDtcSensitivity != MOTION_DTC_SENSITIVITY_OFF)
        #else
        if (uiGetParkingModeEnable() == AHC_TRUE && MenuSettingConfig()->uiMotionDtcSensitivity != MOTION_DTC_SENSITIVITY_OFF)
        #endif
        {
            if (CAM_CHECK_USB(USB_CAM_AIT))
                AHC_HostUVC_EnableMDTC(AHC_TRUE);
            else
                AHC_HostUVC_EnableMDTC(AHC_FALSE);
        }
        else
        {
            AHC_HostUVC_EnableMDTC(AHC_FALSE);
        }

        _AHC_HostUVC_PreviewStart();

        #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        ncam_set_rear_cam_ready(AHC_TRUE);
        #endif
    }
#endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_PreviewStop
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_HostUVC_PreviewStop(UINT8 u8UiMode)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;

#if (UVC_HOST_VIDEO_ENABLE)
    ahcRet = _AHC_HostUVC_PreviewStop();
    ahcRet = AHC_HostUVC_SetDeviceEnable(AHC_FALSE);
#endif

    if (MMP_IsSupportDecMjpegToPreview()) {
        if (u8UiMode == AHC_HUVC_UI_MODE_VR)
            eRetErr = MMPS_HUVC_VRDecMjpegPreviewStop();
        else
            eRetErr = MMPS_HUVC_DscDecMjpegPreviewStop();

        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }

    return ahcRet;
}

#if 0
//------------------------------------------------------------------------------
//  Function    : AHC_HostUVC_USBPathSelect
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Select USB path by USB_PATH pin

 Select USB path by USB_PATH pin.
 Parameters: GPIO_LOW: Device mode, GPIO_HIGH: Host mode
 @param[in] USB_PATH pin
 @retval NONE
*/
void AHC_HostUVC_USBPathSelect(AHC_BOOL ubUsbPath) // TBD
{
#if defined(USB_PATH_SELECT_GPIO)
    if (USB_PATH_SELECT_GPIO != MMP_GPIO_MAX)
    {
        MMPF_PIO_EnableOutputMode(USB_PATH_SELECT_GPIO, MMP_TRUE, MMP_FALSE);
        if (ubUsbPath)
            MMPF_PIO_SetData(USB_PATH_SELECT_GPIO, USB_PATH_SELECT_SET, MMP_TRUE);
        else
            MMPF_PIO_SetData(USB_PATH_SELECT_GPIO, !USB_PATH_SELECT_SET, MMP_TRUE);
    }
#endif
}
#endif

#else   // UVC_HOST_VIDEO_ENABLE

#if 0
void ____Dummy_Function____(){ruturn;} //dummy
#endif

AHC_BOOL AHC_HostUVC_IsDevEnabled(void)
{
    return AHC_FALSE;
}

AHC_BOOL AHC_HostUVC_SetWinAttribute(UINT8 u8WinID, UINT16 usDisplayW, UINT16 usDisplayH, UINT16 usOffsetX, UINT16 usOffsetY, AHC_BOOL bRotate)
{
    return AHC_TRUE;
}

AHC_BOOL AHC_HostUVC_PreviewStart(UINT8 u8UiMode, UINT32 ulFlickerMode)
{
    return AHC_TRUE;
}

AHC_BOOL AHC_HostUVC_PreviewStop(UINT8 u8UiMode)
{
    return AHC_TRUE;
}

AHC_BOOL AHC_HostUVC_RecordStart(void)
{
    return AHC_TRUE;
}

AHC_BOOL AHC_HostUVC_RecordStop(void)
{
    return AHC_TRUE;
}

AHC_BOOL AHC_HostUVC_SetIdleStates(void)
{
    return AHC_TRUE;
}

#endif  // UVC_HOST_VIDEO_ENABLE
