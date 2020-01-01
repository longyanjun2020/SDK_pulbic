/**
 * @file	mmi_layout_gen_undef.h
 * @brief 
 * @author	
 * @version	
*/

#ifndef __MMI_LAYOUT_GEN_UNDEF_H__
#define __MMI_LAYOUT_GEN_UNDEF_H__

#undef __MMI_LAYOUT_GEN_H__
#undef __MMI_LAYOUT_GEN_L_H__

#if defined(__LCM_QVGA_MMI__)
#include "mmi_layout_qvga_undef.h"
#elif defined(__LCM_WQVGA_240_400_MMI__)
#include "mmi_layout_wqvga_240_400_undef.h"
#elif defined(__LCM_HVGA_320_480_MMI__)
#include "mmi_layout_hvga_320_480_undef.h"
#elif defined(__LCM_WVGA_MMI__)
#include "mmi_layout_wvga_undef.h"
#elif defined(__LCM_LANDSCAPE_WVGA_MMI__)
#include "mmi_layout_landscape_wvga_undef.h"
#elif defined(__LCM_LANDSCAPE_WQVGA_240_400_MMI__)
#include "mmi_layout_landscape_wqvga_240_400_undef.h"
#elif defined(__LCM_LANDSCAPE_QVGA_MMI__)
#include "mmi_layout_landscape_qvga_undef.h"
#elif defined(__LCM_LANDSCAPE_HVGA_MMI__)
#include "mmi_layout_landscape_hvga_undef.h"
#elif defined(__LCM_LANDSCAPE_QCIF_MMI__)
#include "mmi_layout_landscape_qcif_undef.h"
#elif defined(__LCM_QQVGA__)
#include "mmi_layout_qqvga_undef.h"
#else
#include "mmi_layout_qcif_plus_undef.h"
#endif

#endif	/*__MMI_LAYOUT_GEN_UNDEF_H__*/
