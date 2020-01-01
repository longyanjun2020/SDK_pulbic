/****************************************************************************/
/*  $Workfile::   fms_map_common.h                                        $ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  FMS/MAP common routines                                      */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   0.3  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   kod    $         |     $Date::   18 Aug 2004 14:57:38 $     */
/****************************************************************************
 *   $Log:   U:/projet/gsm/pvcsarch/archives/fms/inc/fms_map_common.h-arc  $
 * 
 *    Rev 0.3   18 Aug 2004 14:57:38   kod
 * Resolution for 25570: [FMS] Bad behaviour of scratch mem's write
 * Resolution for 25571: [FMS] WHAT3E support
 * Resolution for 25572: [FMS] Support for ST 128M 1.8V single bit per cell
 * Version v1a15.
 * 
 *    Rev 0.2   Jun 07 2004 10:18:36   kod
 * Version v1a13.
 * Resolution for 21973: ARM exception on double scratch memory close
 * Resolution for 23016: [FMS] Disabling ST flash devices permanent lock feature
 * 
 *    Rev 0.1   Jul 16 2003 09:29:36   kod
 * Common flash mapping utilities. 
 * Resolution for 12748: [FMS] Spreading all over the software
 ****************************************************************************/


#ifndef _8957a5ac3475cf645668c9f69d6cb38a_INCLUDED_FMS_MAP_COMMON_H
#define _8957a5ac3475cf645668c9f69d6cb38a_INCLUDED_FMS_MAP_COMMON_H


u32 *fms_MapCodeChecksumPtr(u32 *i__pu32_Address);
s32 fms_MapSectorsBehind(u32 i__u32_Address, u32 i__u32_Number);
s32 fms_MapSectorsBetween(u32 i__u32_Origin, u32 i__u32_Length);
s32 fms_MapReserveMemoryBehind(fms_Area_e i__e_Area, u32 i__u32_Number, u32 *io__pu32_Address, u32 *o__pu32_Limit);

#endif /* ! _8957a5ac3475cf645668c9f69d6cb38a_INCLUDED_FMS_MAP_COMMON_H  */
