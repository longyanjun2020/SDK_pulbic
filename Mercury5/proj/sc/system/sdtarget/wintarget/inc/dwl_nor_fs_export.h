/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Target downloader                                            */
/*             Software glue to use the NOR File System library                         */
/****************************************************************************/

#ifndef __DWL_NOR_FS_EXPORT_H__
#define __DWL_NOR_FS_EXPORT_H__

/****************************************************************************/
/*  Function: dwl_NorFsProcessInit                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : NOR File System download process initialisation                           */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  o__pp_Handle      |   | X |   |  Unused ptr to ptr                      */
/*  i__u32_Origin     | X |   |   |  Unused                                 */
/*  i__u32_Length     | X |   |   |  Length of the GPS firmware             */
/*  i__pf_TellStatus  | X |   |   |  Reporting function                     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_NorFsProcessInit(void **o__pp_Handle, u32 i__u32_Origin, u32 i__u32_Length, dwl_TellStatus_t i__pf_TellStatus);

/****************************************************************************/
/*  Function: dwl_NorFsProcessData                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : Write a packet of data into the NOR File System                     */
/*                                                                          */
/*                                                                          */
/*  Return    : DWL_BIN_OK or DWL_BIN_FAILED                                */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  io__p_Handle      | X | X |   |  Unused                                 */
/*  i__u32_Size       | X |   |   |  Packet size                            */
/*  i__p_Data         | X |   |   |  Source buffer                          */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_NorFsProcessData (dwl_handle_t io__p_Handle, void *i__p_Data, u32 i__u32_Size);

/****************************************************************************/
/*  Function: dwl_NorFsProcessComplete                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : Completes the NOR File System download process                            */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  io__pp_Handle     | X |   |   |  unused pointer to handle               */
/*  i__pu32_Checksum  | X |   |   |  Pointer to data checksum               */
/*  i__pf_TellStatus  | X |   |   |  Reporting function                     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_NorFsProcessComplete(dwl_handle_t io__pp_Handle, u32 *i__pu32_Checksum, dwl_TellStatus_t i__pf_TellStatus);
/****************************************************************************/
/*  Function: dwl_NorFsProcessInit                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : NOR File System download process initialisation                           */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  o__pp_Handle      |   | X |   |  Unused ptr to ptr                      */
/*  i__u32_Origin     | X |   |   |  Unused                                 */
/*  i__u32_Length     | X |   |   |  Length of the GPS firmware             */
/*  i__pf_TellStatus  | X |   |   |  Reporting function                     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_NorFsRawBinProcessInit(void **o__pp_Handle, u32 i__u32_Origin, u32 i__u32_Length, dwl_TellStatus_t i__pf_TellStatus);

/****************************************************************************/
/*  Function: dwl_NorFsProcessData                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : Write a packet of data into the NOR File System                     */
/*                                                                          */
/*                                                                          */
/*  Return    : DWL_BIN_OK or DWL_BIN_FAILED                                */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  io__p_Handle      | X | X |   |  Unused                                 */
/*  i__u32_Size       | X |   |   |  Packet size                            */
/*  i__p_Data         | X |   |   |  Source buffer                          */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_NorFsRawBinProcessData (dwl_handle_t io__p_Handle, void *i__p_Data, u32 i__u32_Size);

/****************************************************************************/
/*  Function: dwl_NorFsProcessComplete                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : Completes the NOR File System download process                            */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  io__pp_Handle     | X |   |   |  unused pointer to handle               */
/*  i__pu32_Checksum  | X |   |   |  Pointer to data checksum               */
/*  i__pf_TellStatus  | X |   |   |  Reporting function                     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_NorFsRawBinProcessComplete(dwl_handle_t io__pp_Handle, u32 *i__pu32_Checksum, dwl_TellStatus_t i__pf_TellStatus);
/****************************************************************************/
/*  Function: dwl_NorFsProcessInit                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : NOR File System download process initialisation                           */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  o__pp_Handle      |   | X |   |  Unused ptr to ptr                      */
/*  i__u32_Origin     | X |   |   |  Unused                                 */
/*  i__u32_Length     | X |   |   |  Length of the GPS firmware             */
/*  i__pf_TellStatus  | X |   |   |  Reporting function                     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_NorFsHiddenRawBinProcessInit(void **o__pp_Handle, u32 i__u32_Origin, u32 i__u32_Length, dwl_TellStatus_t i__pf_TellStatus);

/****************************************************************************/
/*  Function: dwl_NorFsProcessData                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : Write a packet of data into the NOR File System                     */
/*                                                                          */
/*                                                                          */
/*  Return    : DWL_BIN_OK or DWL_BIN_FAILED                                */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  io__p_Handle      | X | X |   |  Unused                                 */
/*  i__u32_Size       | X |   |   |  Packet size                            */
/*  i__p_Data         | X |   |   |  Source buffer                          */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_NorFsHiddenRawBinProcessData (dwl_handle_t io__p_Handle, void *i__p_Data, u32 i__u32_Size);

/****************************************************************************/
/*  Function: dwl_NorFsProcessComplete                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : Completes the NOR File System download process                            */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  io__pp_Handle     | X |   |   |  unused pointer to handle               */
/*  i__pu32_Checksum  | X |   |   |  Pointer to data checksum               */
/*  i__pf_TellStatus  | X |   |   |  Reporting function                     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_NorFsHiddenRawBinProcessComplete(dwl_handle_t io__pp_Handle, u32 *i__pu32_Checksum, dwl_TellStatus_t i__pf_TellStatus);

#endif // __DWL_NOR_FS_EXPORT_H__
