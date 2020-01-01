/****************************************************************************/
/*  $Workfile::   fms_init.h                                              $ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Flash Memory Services                                        */
/*             Initialisation procedures                                    */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   0.5  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   kod    $         |     $Date::   24 Nov 2004 15:52:56 $     */
/****************************************************************************
 *   $Log:   U:/projet/gsm/pvcsarch/archives/fms/inc/fms_init.h-arc  $
 *
 *   Rev 0.5   24 Nov 2004 15:52:56   kod
 *Resolution for 26275: Two allocations with undefined size are allowed
 *Resolution for 26611: [FMS] Xmodem downloader needs some FMS modifications
 *Version v1a18
 *
 *   Rev 0.4   05 Dec 2003 12:00:00   kod
 *New function fms_CoreShutdown.
 *Resolution for 16555: [FMS] Flash driver shutdown function
 *
 *   Rev 0.3   21 Aug 2003 12:00:00   kod
 *New function: fms_MapTailorCustomization.
 *Resolution for 12939: Pb to allocate custo and OpenAT areas in the same time
 *
 *   Rev 0.2   08 Apr 2003 12:00:00   kod
 *Core and Binaries management modifications for xmodem downloader.
 *Resolution for 9256: FMS Core maintenance
 *
 *   Rev 0.1   26 Mar 2003 10:34:30   kod
 *Second release. Works with DwlWin
 ****************************************************************************/



#ifndef _ebabe16d109750fe839a993ea9efdce6_INCLUDED_FMS_INIT_H
#define _ebabe16d109750fe839a993ea9efdce6_INCLUDED_FMS_INIT_H

#include "mdl_fms.h"

#if defined(__FMS_E2P_ON_RAI__)
#ifndef __SDK_SIMULATION__
#include "fms_config.h"
#endif
#include "fms_e2p_on_rai.h"
#endif

#if !defined(__NAND__)
#if defined(__FMS_E2P_ON_RAI__)
#define fms_MapOutMemory()        fms_E2pOnRAI_MapOutMemory()
#define fms_MapInitMainServices() fms_E2pOnRAI_MapInitMainServices()
#else
#define fms_MapOutMemory()        fms_MapOutMemoryExt()
#define fms_MapInitMainServices() fms_MapInitMainServicesExt()
#endif
#endif

/****************************************************************************/
/* INITIALISATION PROCEDURE OF THE FLASH DEVICE DRIVER                      */
/****************************************************************************/

/****************************************************************************/
/*  Function: fms_CoreInit                                                  */
/*--------------------------------------------------------------------------*/
/*  Scope   : FMS core initialisation                                       */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
s32 fms_CoreInit(u32 flash_base_addr);

/****************************************************************************/
/* DE-INITIALISATION OF THE FLASH DRIVER PREVENTING ANY FLASH ACTIVITY      */
/****************************************************************************/

/****************************************************************************/
/*  Function: fms_CoreShutdown                                              */
/*--------------------------------------------------------------------------*/
/*  Scope   : FMS core de-initialisation                                    */
/*            Prevents any further modification of the flash memory         */
/*                                                                          */
/*  Return    : (void)                                                      */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_CoreShutdown(void);

/****************************************************************************/
/* SERVICES MANAGEMENT INITIALISATION ROUTINES                              */
/****************************************************************************/

/****************************************************************************/
/*  Function: fms_MapLocateCode                                             */
/*--------------------------------------------------------------------------*/
/*  Scope   : Locates the code and open at applications in flash.           */
/*                                                                          */
/*  Return    : (void)                                                      */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_MapLocateCode(void);


/****************************************************************************/
/*  Function:  fms_MapOutMemoryExt                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Delineates the areas of the services                         */
/*             (except for TRACES and EEPROM whose areas are fixed)         */
/*                                                                          */
/*             This function needs a working EEPROM service                 */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/****************************************************************************/
s32 fms_MapOutMemoryExt(void);


/****************************************************************************/
/*  Function: fms_MapInitMainServicesExt                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : Initialises and launches the TRACE and EEPROM services        */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/****************************************************************************/
s32 fms_MapInitMainServicesExt(void);

/****************************************************************************/
/*  Function: fms_MapTailorCustomization                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : This function will attempt to re-tailor the customisation     */
/*            files area, so that an Open AT application for example        */
/*            can be installed.                                             */
/*  Return    : (s32) FMS_OK or FMS_OVERFLOW if the supplied address        */
/*                              overlaps the volume's contents              */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_NewBound   | X |   |   |  New bound for the AD/CUSTO volume      */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_MapTailorCustomization(u32 i__u32_NewBound);


/****************************************************************************/
/*  Function: fms_PrePanelInit                                              */
/*--------------------------------------------------------------------------*/
/*  Scope     :  Init fms CUS before panel init                             */
/*  Return    :  NONE                                                       */
/*  Interface :                                                             */
/****************************************************************************/
void fms_PrePanelInit(u32 i__u32_BaseAddr);

#endif /* ! _ebabe16d109750fe839a993ea9efdce6_INCLUDED_FMS_INIT_H   */
