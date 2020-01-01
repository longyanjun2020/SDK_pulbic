////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mdl_fms_e2p.h
* @version
* @brief
*
*/

#ifndef __MDL_FMS_E2P_H__
#define __MDL_FMS_E2P_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
#ifdef __FMS_E2P_FAC_ITF__

typedef enum
{
    FACTORY_E2P_OK,
    FACTORY_E2P_FAIL,
    FACTORY_E2P_REJECT,
    FACTORY_E2P_TIMEOUT,
    FACOTRY_E2P_UNDEFINED
#ifdef __FMS_E2P_DEBUG__
    , FACTORY_E2P_LD_FAIL
    , FACTORY_E2P_LD_REJECT
    , FACTORY_E2P_LD_TIMEOUT
    , FACTORY_E2P_LD_SIGNERR
    , FACTORY_E2P_LD_CKSMERR
#endif
    ,FACTORY_E2P_SIGNERR
    ,FACTORY_E2P_CKSMERR
    ,FACTORY_E2P_LAST_ENUM
} factory_E2pErrCode;

typedef void (*factory_E2pCb)(factory_E2pErrCode errCode);

#else

typedef enum
{
    FLUSH_E2P_OK,
    FLUSH_E2P_FAIL,
    FLUSH_E2P_REJECT,
    FLUSH_E2P_TIMEOUT,
    FLUSH_E2P_UNDEFINED
#ifdef __FMS_E2P_DEBUG__
    , FLUSH_E2P_LD_FAIL
    , FLUSH_E2P_LD_REJECT
    , FLUSH_E2P_LD_TIMEOUT
    , FLUSH_E2P_LD_SIGNERR
    , FLUSH_E2P_LD_CKSMERR
#endif
} flush_E2pErrCode;

typedef void (*flush_E2pCb)(flush_E2pErrCode errCode);

#endif

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
#ifdef __NAND__
/****************************************************************************/
/*  Function:  fms_E2pMsgPar                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Task for read / write NAND type E2P                          */
/*                                                                          */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* pMsgPass           | X |   |   |  Message                                */
/****************************************************************************/
void fms_E2pMsgPar(void *pMsgPass);
#endif

/****************************************************************************/
/*  Function:  fms_E2pAddParamToContainer                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Appends a parameter in the container list                    */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* i__u32_ParamAddr   | X |   |   |  Parameter offset                       */
/* i__u32_ParamSize   | X |   |   |  Parameter size                         */
/* io__p_Container    | X |   |   |  Container                              */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void fms_E2pAddParamToContainer(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void *io__p_Container);

/****************************************************************************/
/*  Function:  fms_E2pBackup                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Backup E2P to CIS block                                      */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
s32 fms_E2pBackup(void);

/****************************************************************************/
/*  Function:  fms_E2pBackup_Interface                        */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Wrapper of fms_E2pBackup                      */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                    */
/*                                                                          */
/*  Interface : n/a                                                    */
/****************************************************************************/
u32 fms_E2pBackup_Interface(void);

/****************************************************************************/
/*  Function: fms_E2pBuildWmMirror                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : Sets up the Wavecom mirror                                    */
/*                                                                          */
/*                                                                          */
/*  Return    :  (bool) FALSE if the operation failed                       */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
bool fms_E2pBuildWmMirror(void);

/****************************************************************************/
/*  Function  : fms_E2pBuildCusMirror                                       */
/*--------------------------------------------------------------------------*/
/*  Scope     : Build customer mirror                                       */
/*                                                                          */
/*  Return    : Success : TRUE                                              */
/*              Failure : FALSE                                             */
/****************************************************************************/
bool fms_E2pBuildCusMirror(void);

/****************************************************************************/
/*  Function:  fms_E2pCleaner                                               */
/*--------------------------------------------------------------------------*/
/*  Scope   :  EEPROM cleaning process                                      */
/*                                                                          */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_E2pCleaner(void);

/****************************************************************************/
/*  Function:  fms_E2pFlush                                                 */
/*--------------------------------------------------------------------------*/
/*  Scope   :  flush whole e2p parameter to flash                           */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
s32 fms_E2pFlush(void);

/****************************************************************************/
/*  Function:  fms_FlushFlashCache                                                 */
/*--------------------------------------------------------------------------*/
/*  Scope   :  flush flash cache                           */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
s32 fms_FlushFlashCache(void);

/****************************************************************************/
/*  Function:  fms_E2pFlush                                                 */
/*--------------------------------------------------------------------------*/
/*  Scope   :  flush whole e2p parameter to flash (Asynchronous mode)       */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* factoryE2pCb       | X |   |   |  Callback function pointer              */
/* flushE2pCb         | X |   |   |  Callback function pointer              */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
#ifdef __FMS_E2P_FAC_ITF__
s32 fms_E2pFlush_Async(factory_E2pCb factoryE2pCb);
#else
s32 fms_E2pFlush_Async(flush_E2pCb flushE2pCb);
#endif

/****************************************************************************/
/*  Function: fms_E2pInterfaceInit                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : Second phase of the initialisation of the E2P service         */
/*            after the startup of the internal eeprom simulation engine.   */
/*                                                                          */
/*            The internal engine must be correctly initialised,            */
/*            and the consistency of the current active bank checked.       */
/*                                                                          */
/*  Return    : void                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* i__p_Buffer        |   | X |   |  Spare buffer used                      */
/* i__u32_BufferSize  | X |   |   |  Size of the buffer                     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void fms_E2pInterfaceInit(void *i__p_Buffer, u32 i__u32_BufferSize);
void fms_E2pInterfaceInit_fake(void *i__p_Buffer, u32 i__u32_BufferSize);

/****************************************************************************/
/*  Function:  fms_E2pWrite                                                 */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Writes a parameter in EEPROM                                 */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_ParamAddr  | X |   |   |  Address in EEPROM of the parameter     */
/*  i__u32_ParamSize  | X |   |   |  Size of the parameter                  */
/*  i__p_Buffer       | X |   |   |  Source buffer                          */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_E2pWrite(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void *i__p_Buffer);

/****************************************************************************/
/*  Function:  fms_E2pRead                                                  */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Reads a parameter in EEPROM                                  */
/*                                                                          */
/*                                                                          */
/*  Return    :  (s32) FMS_OK or error code                                 */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_ParamAddr  | X |   |   |  Logical E2P address of the parameter   */
/*  i__u32_ParamSize  | X |   |   |  Size of the parameter                  */
/*  o__p_Buffer       |   | X |   |  Output buffer                          */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_E2pRead(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void* o__p_Buffer);

/****************************************************************************/
/*  Function:  fms_E2pReadMirror                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Reads a parameter in EEPROM                                  */
/*                                                                          */
/*                                                                          */
/*  Return    :  (s32) FMS_OK or error code                                 */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_ParamAddr  | X |   |   |  Logical E2P address of the parameter   */
/*  i__u32_ParamSize  | X |   |   |  Size of the parameter                  */
/*  o__p_Buffer       |   | X |   |  Output buffer                          */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_E2pReadMirror(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void* o__p_Buffer);

/****************************************************************************/
/*  Function  : fms_E2pRestoreWavecomMirror                                 */
/*--------------------------------------------------------------------------*/
/*  Scope     : Restores Wavecom Mirror                                     */
/*                                                                          */
/*  Return    : Success : TRUE                                              */
/*              Failure : FALSE                                             */
/****************************************************************************/
bool fms_E2pRestoreWavecomMirror(void);

/****************************************************************************/
/*  Function: fms_E2pSaveOneParameter                                       */
/*--------------------------------------------------------------------------*/
/*  Scope   : Save the specified parameters in the mirrors.                 */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_ParamAddr  | X |   |   |  Address in EEPROM of the parameter     */
/*  i__u32_ParamSize  | X |   |   |  Size of the parameter                  */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_E2pSaveOneParameter(u32 i__u32_ParamAddr, u32 i__u32_ParamSize);

/****************************************************************************/
/*  Function: fms_E2pSaveParameters                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Save the given list of parameters in the mirrors             */
/*                                                                          */
/*                                                                          */
/*  Return    :  (s32) FMS_OK or error code                                 */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__p_Parameters   | X |   |   |  List of parameters to save             */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_E2pSaveParameters(void *i__p_Parameters);

/****************************************************************************/
/*  Function: fms_E2pSetProtection                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : Activates special parameters protection:                      */
/*            recomputes checksum and denies future write attempts on them  */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_E2pSetProtection(void);

/****************************************************************************/
/*  Function: fms_E2pUnsetProtection                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Deactivate special parameters protection:                    */
/*             the whole EEPROM area becomes thus writable                  */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_E2pUnsetProtection(void);

#endif //__MDL_FMS_E2P_H__

