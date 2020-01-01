/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Target downloader                                            */
/*             Download in flash memory using FMS                           */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef _568db6247d776799ed22d4536f846f6e_included_dwl_binary_fms_h
#define _568db6247d776799ed22d4536f846f6e_included_dwl_binary_fms_h


/****************************************************************************/
/*  Function: dwl_FlashEraseProcess                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : Initialisation of the flash memory medium                     */
/*            before a binary file can be downloaded                        */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  o__pp_Handle      |   | X |   |  Ptr to ptr to fms_BinHandle_t          */
/*  i__u32_Origin     | X |   |   |  Origin of the binary                   */
/*  i__u32_Length     | X |   |   |  Length of the binary                   */
/*  i__pf_TellStatus  | X |   |   |  Status reporting callback              */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_FlashEraseProcess(void **o__pp_Handle, u32 i__u32_Origin, u32 i__u32_Length, const dwl_TellStatus_t i__pf_TellStatus);

/****************************************************************************/
/*  Function: dwl_FlashEraseProcess_MultiBin                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : Initialisation of the flash memory medium                     */
/*            before a binary file can be downloaded                        */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  o__pp_Handle      |   | X |   |  Ptr to ptr to fms_BinHandle_t          */
/*  i__u32_Origin     | X |   |   |  Origin of the binary                   */
/*  i__u32_Length     | X |   |   |  Length of the binary                   */
/*  i__pf_TellStatus  | X |   |   |  Status reporting callback              */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_FlashEraseProcess_MultiBin(void *i__ps_Handle, u32 i__u32_Stage, u32 i__u32_TargetCode);


/****************************************************************************/
/*  Function: dwl_CompleteRawBinary                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : Completes the download of a raw (non-compressed) binary       */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__ps_Handle      | X |   |   |  Handle                                 */
/*  i__pu32_Checksum  | X |   |   |  Checksum to verify or NULL             */
/*  i__pf_TellStatus  | X |   |   |  Status reporting callback              */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_CompleteRawBinary(dwl_handle_t i__ps_Handle, u32 *i__pu32_Checksum, const dwl_TellStatus_t i__pf_TellStatus);


/****************************************************************************/
/*  Function: dwl_CompleteBinary                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : Completes the download of a binary                            */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__ps_Handle      | X |   |   |  Handle                                 */
/*  i__pu32_Checksum  | X |   |   |  Checksum to verify or NULL             */
/*  i__pf_TellStatus  | X |   |   |  Status reporting callback              */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_CompleteBinary(dwl_handle_t i__ps_Handle, u32 *i__pu32_Checksum, const dwl_TellStatus_t i__pf_TellStatus);

#endif /* ! _568db6247d776799ed22d4536f846f6e_included_dwl_binary_fms_h   */
