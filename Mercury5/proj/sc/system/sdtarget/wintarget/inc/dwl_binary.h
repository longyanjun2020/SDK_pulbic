///////////////////////////////////////////////////////////////////////////////////////////////////
// @file   dwl_binary.h
// @author MStar Semiconductor Inc.
// @brief  Montage Wintarget binary medium layer header file
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DWL_BINARY_H
#define _DWL_BINARY_H

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "sysunfd.h"
#include "dwl_medium.h"


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Typedefs
//-------------------------------------------------------------------------------------------------
typedef enum
{
   BIN_TYPE_BOOTLDR = 0,
   BIN_TYPE_IMGPRT,
   BIN_TYPE_RAI,
#ifdef __B3_RESTORE__
   BIN_TYPE_FATUSER,
   BIN_TYPE_CUS,
   BIN_TYPE_E2P_RL,
   BIN_TYPE_RAI_RL,
   BIN_TYPE_TRC_RL,
   BIN_TYPE_FATUSER_RL,
   BIN_TYPE_NONE = -1
#else
   BIN_TYPE_NONE = -1
#endif
} dwl_binType_e;

typedef struct dwl_binHandle_s
{
   void const   *label;
   u32      u32highWater;
   u32      u32totLen;
   u32      u32flag;
   dwl_binType_e    etype;
} dwl_binHandle_t;


//-------------------------------------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------------------------------------

#endif  // _DWL_BINARY_H
