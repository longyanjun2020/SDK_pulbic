#ifndef _DRAM_CFG_H_
#define _DRAM_CFG_H_

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

#include "mmpf_dram.h"

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

//Please make sure the mmpf layer library<core.a> use the same DRAM_ID when building 
#if defined (MCR_V2_32MB)      // defined in MCP
    #undef DRAM_ID
    #define DRAM_ID    (DRAM_DDR)
#elif defined (MCR_V2_Q_128MB) // defined in MCP
    #undef DRAM_ID
    #define DRAM_ID    (DRAM_DDR3)
    //if use 8x28Q 8x28G, change to COMMON_DRAM_SIZE_128MB
#else
    #undef DRAM_ID
    #define DRAM_ID    (DRAM_DDR)
#endif

//==============================================================================
//
//                              Definition
//
//==============================================================================

#define INVALIDATEVALUE  (0xFFFFFFFF)

//==============================================================================
//
//                              Extern Variable
//
//==============================================================================

#if (AUTO_DRAM_LOCKCORE)
extern MMP_DRAM_CLK_DLY_SET m_delayTable[17];
extern MMPF_DRAM_DMA_PARAM m_DmaParam;
#endif

extern const MMPF_DRAM_SETTINGS m_DramSettings;

//==============================================================================
//
//                              API Declaration
//
//==============================================================================

void InitializeVariableForDram(void);

#endif //_DRAM_CFG_H_
