//------------------------------------------------------------------------------
//
//  File        : fdtc_ctl.h
//  Description : face detection and smile detecton
//  Author      : ChenChu Hsu
//  Revision    : 0.0
//
//------------------------------------------------------------------------------
#ifndef _fdtc_ctl_H_
#define _fdtc_ctl_H_

#include "includes_fw.h"
#include "mmpf_typedef.h"
#include "fdtc.h"

#if FDTC_AIT_SDTC
#include "sdtc.h"
#endif

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
#define MMPS_FDTC_MAX_HORIZONTAL	1280///< the max width of fdtc lib
#define MMPS_FDTC_MAX_VERTICAL		960	///< the max height of fdtc lib
#define MMPS_FDTC_MAX_FACE_NUMBER	15	///< the max number of fdtc lib

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

//fdtc
void FDTC_CTL_Reset(MMP_ULONG fd_img_in_addr,
					MMP_ULONG fd_work_addr,
					MMP_ULONG sd_work_addr,
					MMP_ULONG fd_info_addr,
					MMP_ULONG fd_width,
					MMP_ULONG fd_height,
					MMP_ULONG fd_face_num,
					MMP_UBYTE sd_enable,
					MMP_ULONG sd_sensitivity);

MMP_BOOL FDTC_CTL_CheckResult(void);

MMP_ERR FDTC_CTL_GetFDWorkBufSize(MMP_ULONG ulwidth, MMP_ULONG ulheight, MMP_ULONG ulfacenum, MMP_ULONG *ulsize);
MMP_ERR FDTC_CTL_GetFDInfoBufSize(MMP_ULONG ulfacenum, MMP_ULONG *ulsize);
MMP_ERR FDTC_CTL_GetFDVersion(	MMP_USHORT *puwFdtcMajorVersion,
								MMP_USHORT *puwFdtcMediumVersion,
					            MMP_USHORT *puwFdtcMinorVersion,
					            MMP_BYTE** pszReleaseName );
// sdtc
MMP_ERR FDTC_CTL_SetSmileSensitivity(MMP_ULONG ulSensitivity);
MMP_ERR FDTC_CTL_GetSDWorkBufSize(MMP_ULONG ulwidth, MMP_ULONG ulheight, MMP_ULONG ulfacenum, MMP_ULONG *ulsize);
MMP_ERR FDTC_CTL_GetSDVersion(MMP_USHORT* puwSdtcVersion);
#endif // _fdtc_ctl_H_
