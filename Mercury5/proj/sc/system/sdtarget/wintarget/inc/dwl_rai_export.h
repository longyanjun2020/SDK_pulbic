/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Target downloader                                            */
/*             Software glue to use the NOR File System library                         */
/****************************************************************************/

#ifndef __DWL_RAI_EXPORT_H__
#define __DWL_RAI_EXPORT_H__

/****************************************************************************/
/*  Function: dwl_RaiProcessInit                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   :  RAI direct access download process initialisation            */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  o__pp_Handle      |   | X |   |  Unused ptr to ptr                      */
/*  i__u32_Origin     | X |   |   |  Unused                                 */
/*  i__u32_Length     | X |   |   |  Length (unused)                        */
/*  i__pf_TellStatus  | X |   |   |  Reporting function                     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_RaiProcessInit(void **o__pp_Handle, u32 i__u32_Origin, u32 i__u32_Length, dwl_TellStatus_t i__pf_TellStatus);
/****************************************************************************/
/*  Function: dwl_RaiProcessData                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : Write a packet of data into RAI                               */
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
s32 dwl_RaiProcessData(dwl_handle_t io__p_Handle, void *i__p_Data, u32 i__u32_Size);

/****************************************************************************/
/*  Function: dwl_RaiProcessComplete                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : Completes the RAI direct download process                     */
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
s32 dwl_RaiProcessComplete(dwl_handle_t io__pp_Handle, u32 *i__pu32_Checksum, dwl_TellStatus_t i__pf_TellStatus);


/* NAND RAI upload routines */
bool dwl_raiPartOpen(dwl_handle_t *pphandle, void *parg, u32 *pu32size);
bool dwl_raiPartRead(dwl_handle_t phandle, void *pdata, u32 u32len);
bool dwl_raiPartClose(dwl_handle_t phandle);

#endif // __DWL_RAI_EXPORT_H__

