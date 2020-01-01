/**
* @file    mmi_srv_emugame.h
* @brief
*
*/

#ifndef __MMI_SRV_EMUGAME_H__
#define __MMI_SRV_EMUGAME_H__


/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_codecsrv.h"

/*=============================================================*/
// Variable Declarations
/*=============================================================*/


/*=============================================================*/
// Private Function Implementations
/*=============================================================*/


/*=============================================================*/
// Public Function Implementations
/*=============================================================*/

/**
SrvEmuGameStart
@brief  This interface is used to start EMU game.

@param[in]      pParam          The parameters of EMU Game such as render type, region and angle.
@param[in]      pfnCodecSrvCB   CodecSrv EmuGame common callback function
 */
MAE_Ret SrvEmuGameStart( CodecSrvEmuGameParam_t *pParam,
                      CodecSrvEmuCmnCb pfnCodecSrvCB);

/**
SrvEmuGameStop
@brief  This interface is used to stop EMU game.

@param[in]      pParam          The parameters of EMU Game such as render type and buffer.
@param[in]      pfnCodecSrvCB   CodecSrv Stop EmuGame callback function
 */
MAE_Ret SrvEmuGameStop( CodecSrvEmuGameStopParam_t *pParam,
                     CodecSrvEmuStopCb pfnCodecSrvCB);

/**
SrvEmuGameSetInput
@brief  This interface is used to set input key.

@param[in]      pParam          The parameters of EMU Game such as render type and Input key.
@param[in]      pfnCodecSrvCB   CodecSrv EmuGame common callback function
 */
MAE_Ret SrvEmuGameSetInput( CodecSrvEmuGameSetInputParam_t *pParam,
                         CodecSrvEmuCmnCb pfnCodecSrvCB);

/**
SrvEmuGameGetInfo
@brief  This interface is used to set info type.

@param[out]     pParam          The parameters of EMU Game such as info type etc..
@param[in]      pfnCodecSrvCB   CodecSrv EmuGame get info callback function
 */
MAE_Ret SrvEmuGameGetInfo( CodecSrvEmuGameGetInfoParam_t *pParam,
                        CodecSrvEmuGetInfoCb pfnCodecSrvCB);

/**
SrvEmuGameCleanUp
@brief  This interface is used to clean up the heap buffer of emulator game status for EMU MDL.

@param[in]      pfnCodecSrvCB   CodecSrv EmuGame common callback function
 */
MAE_Ret SrvEmuGameCleanUp(CodecSrvEmuCmnCb pfnCodecSrvCB);

/**
SrvEmuSetInterruptNotifyCb
@brief  This interface is used to set interrupt callback function.

@param[in]      pfnInterruptNotifyCb    CodecSrv Interrupt notify callback function
 */
MAE_Ret SrvEmuSetInterruptNotifyCb( CodecSrvInterruptNotify pfnInterruptNotifyCb);

/**
SrvEmuOpenSession
@brief  This interface is used to open the session of EMU Game.

 */
MAE_Ret SrvEmuOpenSession(void);

/**
SrvEmuCloseSession
@brief  This interface is used to close the session of EMU Game.

 */
MAE_Ret SrvEmuCloseSession(void);
#endif //__MMI_SRV_EMUGAME_H__
