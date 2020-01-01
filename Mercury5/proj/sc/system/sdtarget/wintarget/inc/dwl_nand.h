///////////////////////////////////////////////////////////////////////////////////////////////////
// @file   dwl_nand.h
// @author MStar Semiconductor Inc.
// @brief  Montage Wintarget NAND medium layer header file
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DWL_NAND_H
#define _DWL_NAND_H

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "dwl_binary.h"


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Typedefs
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------------------------------------
s32     dwl_binBldrInit(dwl_handle_t *pphandle, u32 u32type, u32 u32len,
                        dwl_TellStatus_t pf_tellStatus);
s32     dwl_binBldrData(dwl_handle_t phandle, void *pdata, u32 u32len);
s32     dwl_binBldrComplete(dwl_handle_t phandle, u32 *pu32chksum,
                            dwl_TellStatus_t pf_tellStatus);
s32     dwl_binPrtInit(dwl_handle_t *pphandle, u32 u32type, u32 u32len,
                       dwl_TellStatus_t pf_tellStatus);
s32     dwl_binPrtData(dwl_handle_t phandle, void *pdata, u32 u32len);
s32     dwl_binPrtComplete(dwl_handle_t phandle, u32 *pu32chksum,
                           dwl_TellStatus_t pf_tellStatus);
bool    dwl_binBldrOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
bool    dwl_binBldrRead(dwl_handle_t phandle, void *pdata, u32 u32len);
bool    dwl_binBldrClose(dwl_handle_t phandle);
bool    dwl_binPrtOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
bool    dwl_binPrtRead(dwl_handle_t phandle, void *pdata, u32 u32len);
bool    dwl_binPrtClose(dwl_handle_t phandle);
bool    dwl_fatUserOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
bool    dwl_fatUserRead(dwl_handle_t phandle, void *pdata, u32 u32len);
bool    dwl_fatUserClose(dwl_handle_t phandle);
bool    dwl_fatUserHiddenOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
bool    dwl_fatUserHiddenRead(dwl_handle_t phandle, void *pdata, u32 u32len);
bool    dwl_fatUserHiddenClose(dwl_handle_t phandle);

#ifdef __B3_UPLOAD_NEW__
bool    dwl_wholeOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
bool    dwl_wholeRead(dwl_handle_t phandle, void *pdata, u32 u32len);
bool    dwl_wholeClose(dwl_handle_t phandle);
#endif

#ifdef __B3_RESTORE__
s32    dwl_e2pRLAllocate(dwl_handle_t *pphandle, u32 u32type, u32 u32len, dwl_TellStatus_t pf_tellStatus);
s32    dwl_e2pRLWrite(dwl_handle_t phandle, void *pdata, u32 u32len);
s32    dwl_e2pRLFinalize(dwl_handle_t phandle, u32 *pu32chksum, dwl_TellStatus_t pf_tellStatus);
s32    dwl_raiRLAllocate(dwl_handle_t *pphandle, u32 u32type, u32 u32len, dwl_TellStatus_t pf_tellStatus);
s32    dwl_raiRLWrite(dwl_handle_t phandle, void *pdata, u32 u32len);
s32    dwl_raiRLFinalize(dwl_handle_t phandle, u32 *pu32chksum, dwl_TellStatus_t pf_tellStatus);
s32    dwl_trcRLAllocate(dwl_handle_t *pphandle, u32 u32type, u32 u32len, dwl_TellStatus_t pf_tellStatus);
s32    dwl_trcRLWrite(dwl_handle_t phandle, void *pdata, u32 u32len);
s32    dwl_trcRLFinalize(dwl_handle_t phandle, u32 *pu32chksum, dwl_TellStatus_t pf_tellStatus);
s32    dwl_binCusInit(dwl_handle_t *pphandle, u32 u32type, u32 u32len, dwl_TellStatus_t pf_tellStatus);
s32    dwl_binCusData(dwl_handle_t phandle, void *pdata, u32 u32len);
s32    dwl_binCusComplete(dwl_handle_t phandle, u32 *pu32chksum, dwl_TellStatus_t pf_tellStatus);
s32    dwl_fatUserRLAllocate(dwl_handle_t *pphandle, u32 u32type, u32 u32len, dwl_TellStatus_t pf_tellStatus);
s32    dwl_fatUserRLWrite(dwl_handle_t phandle, void *pdata, u32 u32len);
s32    dwl_fatUserRLFinalize(dwl_handle_t phandle, u32 *pu32chksum, dwl_TellStatus_t pf_tellStatus);
#endif
s32    dwl_fatUserAllocate(dwl_handle_t *pphandle, u32 u32type, u32 u32len, dwl_TellStatus_t pf_tellStatus);
s32    dwl_fatUserWrite(dwl_handle_t phandle, void *pdata, u32 u32len);
s32    dwl_fatUserFinalize(dwl_handle_t phandle, u32 *pu32chksum, dwl_TellStatus_t pf_tellStatus);
s32    dwl_fatUserHiddenAllocate(dwl_handle_t *pphandle, u32 u32type, u32 u32len, dwl_TellStatus_t pf_tellStatus);
s32    dwl_fatUserHiddenWrite(dwl_handle_t phandle, void *pdata, u32 u32len);
s32    dwl_fatUserHiddenFinalize(dwl_handle_t phandle, u32 *pu32chksum, dwl_TellStatus_t pf_tellStatus);

#endif  // _DWL_NAND_H

