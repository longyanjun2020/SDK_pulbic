/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  EEPROM download management                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _DWL_EEPROM_H_
#define _DWL_EEPROM_H_

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "dwl_medium.h"

/****************************************************************************/
/*  Function:  dwl_GetEepromParameters                                      */
/*--------------------------------------------------------------------------*/
/*  Scope   :  EEPROM download management                                   */
/*                                                                          */
/*                                                                          */
/*  Return    : (int) TRUE/FALSE                                            */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
s32 dwl_GetEepromParameters(void);
s32 dwl_GetEepromParameters_NAND(void);

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define E2P_SIGNATURE_PATTERN       "E2P"
#define E2PALL_FILE_NAME            "all.E2P"
#define E2PRAW_FILE_NAME            "raw.E2P"

//-------------------------------------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------------------------------------
bool    dwl_e2pChkIntegrity(char const *ptrbuf);
s32     dwl_e2pAllocate(dwl_handle_t *pphandle, u32 u32type, u32 u32len, dwl_TellStatus_t pf_tellStatus);
s32     dwl_e2pWrite(dwl_handle_t phandle, void *pdata, u32 u32len);
s32     dwl_e2pFinalize(dwl_handle_t *phandle, u32 *pu32chksum, dwl_TellStatus_t pf_tellStatus);
bool    dwl_e2pOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
bool    dwl_e2pRead(dwl_handle_t phandle, void *pdata, u32 u32len);
bool    dwl_e2pClose(dwl_handle_t phandle);

#endif  // ! _DWL_EEPROM_H_
