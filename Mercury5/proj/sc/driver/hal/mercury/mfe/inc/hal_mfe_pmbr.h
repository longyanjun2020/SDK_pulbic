
#ifndef _MFE_PMBR_H_
#define _MFE_PMBR_H_

#include "mhve_pmbr_ops.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

// Histogram for perceptual RC tuning
#define LOG2_HIST_SIZE  (PMBR_LOG2_HIST_SIZE)

// Look-up Table Size
#define LUT_SIZE        (PMBR_LUT_SIZE)

// Minimum bin number threshold for perceptual MBR enable
#define PMBR_BIN_THR    (5)

//==============================================================================
//
//                              Structure
//
//==============================================================================

typedef struct _pmbr_frmAttr {
    bool            m_bPercPicEn;
    int             m_nTcHist[1<<LOG2_HIST_SIZE];
    int             m_nPcCntHist[1<<LOG2_HIST_SIZE];
    int             m_nLUTTarget[LUT_SIZE];
    int             m_nLUTQp[LUT_SIZE];
    int             m_nLUTEntryHist[LUT_SIZE];
    int             m_nTcAccum;
    int             m_nPcCntAccum;
    int             m_nOutWeightAccum;
    int             m_nSecStageWghtAccum;
    unsigned char*  m_nPercMBInMapVirt;
    unsigned int    m_nPercMBInMapPhy;
    unsigned char*  m_nPercMBOutMapVirt;
    unsigned int    m_nPercMBOutMapPhy;
} pmbr_frmAttr;

typedef struct _pmbr_gblAttr {
    bool            b_PmbrEnable;
    int             i_mbW;
    int             i_mbH;
    int             i_iupperq;          /* QP Upper Bound */
    int             i_ilowerq;          /* QP Lower Bound */
    int             i_pupperq;          /* QP Upper Bound */
    int             i_plowerq;          /* QP Lower Bound */

    unsigned char*  b_LutAddrVirt;
    unsigned int    i_LutAddrPhy;

    int             i_LutEntryClipRange;
    int             i_TextWeightType;
    int             i_SkinLvShift;
    int             i_WeightOffset;
    int             i_TcOffset;
    int             i_TcToSkinAlpha;
    int             i_TcGradThr;

    int             i_PwYMax;
    int             i_PwYMin;
    int             i_PwCbMax;
    int             i_PwCbMin;
    int             i_PwCrMax;
    int             i_PwCrMin;
    int             i_PwCbPlusCrMin;
    int             i_PwAddConditionEn;
    int             i_PwCrOffset;
    int             i_PwCbCrOffset;
    int             i_PcDeadZone;

    int             i_SmoothEn;
    int             i_SmoothClipMax;
    int             i_SecStgAlpha;
    int             i_SecStgBitWghtOffset;
} pmbr_gblAttr;

typedef struct _mfe6_pmbr
{
    pmbr_ops        pmbr;           /* PMBR Operations */
    pmbr_gblAttr    gblAttr;        /* PMBR Global Attribute */
    pmbr_frmAttr    frmAttr;        /* PMBR Frame Attribute */
} mfe6_pmbr;

//==============================================================================
//
//                              Function Prototype
//
//==============================================================================

void* PmbrAllocate(void);

#endif //_MFE_PMBR_H_
