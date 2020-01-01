/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Target downloader                                            */
/*             Binary files download management                             */
/*             Functions exported to the main function                      */
/*                                                                          */
/****************************************************************************/

#ifndef _48d1560c2685e78639cae85f2157c27d_included_dwl_binary_main_h
#define _48d1560c2685e78639cae85f2157c27d_included_dwl_binary_main_h


/****************************************************************************/
/*  Function: dwl_GetBinary                                                 */
/*--------------------------------------------------------------------------*/
/*  Scope   : Gets a binary file from the remote host                       */
/*            and stores it in the target media                             */
/*                                                                          */
/*  Return    : (s32) 0 for success <0 if error occurred                    */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__ps_BinDesc     | X |   |   |  Binary descriptor                      */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_GetBinary (dwl_BinaryDescriptor_t *i__ps_BinDesc);

/****************************************************************************/
/*  Function: dwl_GetAllBinaries                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : Receives all the binaries and stores them in the              */
/*            adequate media                                                */
/*                                                                          */
/*  Return    : (s32) DWL_BIN_OK / DWL_BIN_FAILED                           */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
s32 dwl_GetAllBinaries(void);



/****************************************************************************/
/*  Function: dwl_GetBinary                                                 */
/*--------------------------------------------------------------------------*/
/*  Scope   : listen mode, pre erase flash, base on original binary         */
/*            on binary descriptor                                          */
/*                                                                          */
/*  Return    : (s32) 0 ( SUCCESS ) / -1 ( FAIL )                           */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__ps_BinDesc     | X |   |   |  Binary descriptor                      */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_pre_erase(dwl_BinaryDescriptor_t *i__ps_BinDesc);


#endif /* ! _48d1560c2685e78639cae85f2157c27d_included_dwl_binary_main_h   */
