/****************************************************************************/
/*  $Workfile::   fms_ad_internal.h                                       $ */
/*--------------------------------------------------------------------------*/
/*  Scope   : Flash Memory Services                                         */
/*            Applications and data storage                                 */
/*                                                                          */
/*            FMS private definitions and declarations                      */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   0.3  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   kod    $         |     $Date::   24 Nov 2004 15:52:54 $     */
/****************************************************************************
 *   $Log:   U:/projet/gsm/pvcsarch/archives/fms/inc/fms_ad_internal.h-arc  $
 *
 *   Rev 0.3   24 Nov 2004 15:52:54   kod
 *Resolution for 26275: Two allocations with undefined size are allowed
 *Resolution for 26611: [FMS] Xmodem downloader needs some FMS modifications
 *Version v1a18
 *
 *   Rev 0.2   21 Aug 2003 12:00:00   kod
 *New function fms_AdShutdownVolume.
 *Resolution for 12939: Pb to allocate custo and OpenAT areas in the same time                           
 *
 *   Rev 0.1   26 Mar 2003 10:35:20   kod
 *Second release. Works with DwlWin
 ****************************************************************************/

#ifndef _e8a7769f2224e61985ee05b91270ee09_INCLUDED_FMS_AD_INTERNAL_H
#define _e8a7769f2224e61985ee05b91270ee09_INCLUDED_FMS_AD_INTERNAL_H


/****************************************************************************/
/*  Function: fms_AdNeedsCompaction                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : This function is used by the FMS services launcher            */
/*            to determine if a spare sector will be needed for             */
/*            an AD volume recompaction.                                    */
/*                                                                          */
/*  Return    : (s32) boolean value, TRUE if a spare sector is needed       */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
s32 fms_AdNeedsCompaction(void);


/****************************************************************************/
/*  Function: fms_AdInit                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : Initialisation of the flat volume                             */
/*                                                                          */
/*                                                                          */
/*  Return    : void                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_Token        | X |   |   |  Token of the volume to use             */
/*  i__u32_Origin     | X |   |   |  Origin of the flat volume              */
/*  i__u32_SectNumber | X |   |   |  Number of allocated sectors            */
/*  i__u32_Size       | X |   |   |  Volume size                            */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void fms_AdInit(fms_AdToken_e i__e_Token, u32 i__u32_Origin, u32 i__u32_SectNumber, u32 i__u32_Size);

/****************************************************************************/
/*  Function: fms_AdShutdownVolume                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : De-initialize the flat volume                                 */
/*            Use with caution                                              */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_Token        | X |   |   |  Token of the volume to use             */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void fms_AdShutdownVolume(fms_AdToken_e i__e_Token);

#endif /* ! _e8a7769f2224e61985ee05b91270ee09_INCLUDED_FMS_AD_INTERNAL_H   */
