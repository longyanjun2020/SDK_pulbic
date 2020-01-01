#ifndef __VEN_DBG_PRIV_H__
#define __VEN_DBG_PRIV_H__
/**
 *
 * @file    ven_dbg_priv.h
 * @brief   This file defines the debug trace interface definition.
 *
 * @author  Ming.Chen
 * @version $Id: ven_dbg.h 24368 2009-03-02 02:52:47Z steve.lee $
 *
 */

/*--------------------------------------------------------------------------*/
/* Include files                                                            */
/*--------------------------------------------------------------------------*/
#include "ven_sdk.h"
#include "ven_dbg.h"
#include "sys_vm_dbg.ho"    //for _CUS7

/*--------------------------------------------------------------------------*/
/* Define                                                                   */
/*--------------------------------------------------------------------------*/
#define DEV_TRACE vm_dbgTrace /**< Make redundant macro expansion to avoid RTPP processing to LOG_TRACEs definitions */
#define DEV_WARN vm_dbgError /**< Make redundant macro expansion to avoid RTPP processing to LOG_TRACEs definitions */

#define _VENSDK             _CUS7               /* Actually SDK is on vendor task   */
#define _VENSDK_STC         _VENSDK | LEVEL_6   /* for State Control                */
#define _VENSDK_OS          _VENSDK | LEVEL_7   /* OS API                           */
#define _VENSDK_NET         _VENSDK | LEVEL_8   /* Network API                      */
#define _VENSDK_SENSOR      _VENSDK | LEVEL_21  /* for Sensors                     */
#define _VENSDK_SET         _VENSDK | LEVEL_22  /* for Settings                     */
#define _VENSDK_TIME        _VENSDK | LEVEL_23  /* for time                         */
#define _VENSDK_CODEC       _VENSDK | LEVEL_24  /* for codec                        */
#define _VENSDK_CAM         _VENSDK | LEVEL_24  /* for camera                       */
#define _VENSDK_COMMON      _VENSDK | LEVEL_25  /* for utility                      */
#define _VENSDK_GRAPHICS    _VENSDK | LEVEL_26  /* for graphics                     */
#define _VENSDK_FONT        _VENSDK | LEVEL_27  /* for font                         */
#define _VENSDK_CLIPBOARD   _VENSDK | LEVEL_28  /* for clipboard                    */
#define _VENSDK_EDITOR      _VENSDK | LEVEL_28  /* for editor                       */
#define _VENSDK_MSG         _VENSDK | LEVEL_29  /* for message                      */
#define _VENSDK_DBGLVL_UI   _VENSDK | LEVEL_30  /* for ui                           */
#define _VENSDK_FILE        _VENSDK | LEVEL_31  /* for file                         */
#define _VENSDK_GPS         _VENSDK | LEVEL_6   /* for GPS                          */

#define _VENSDK_NFC         _VENSDK | LEVEL_6   /* for NFC                          */

#ifdef __SFILE__
/* Use short name if source file defined __SFILE__ */
#define __TARGET_FILE__ __SFILE__
#else
#define __TARGET_FILE__ __FILE__
#endif

//#define VEN_TRACE(_level_, _format_, ...) ven_dbg_internal_trace(_level_, "[TRACE] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
//#define VEN_ERROR(_level_, _format_, ...) ven_dbg_internal_trace(_level_, "[ERROR] %s (%d): " _format_, __TARGET_FILE__, __LINE__, ##__VA_ARGS__)
#define VEN_TRACE(_level_, _format_, ...)  DEV_TRACE(_level_, _format_, ##__VA_ARGS__)
#define VEN_ERROR(_level_, _format_, ...) DEV_WARN(_level_, _format_, ##__VA_ARGS__)

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/
void ven_dbg_internal_trace(u32 level, char *strFormat, ...);

#endif // __VEN_DBG_PRIV_H__

