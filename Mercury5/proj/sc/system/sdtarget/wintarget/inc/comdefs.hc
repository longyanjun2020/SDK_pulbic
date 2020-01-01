/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 1998, 1999, 2000, 2001
*/
/****************************************************************************/
/*  File    : comdefs.hc                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : GSM project common define flags file                          */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Modification                                         */
/*----------+--------+------------------------------------------------------*/
/* 17.04.98 |   PGU  | - Creation                                           */
/*----------+--------+------------------------------------------------------*/
/* 27.05.98 |   PGU  | - LCD_EMULATION and not __LCD_EMULATION__            */
/*----------+--------+------------------------------------------------------*/
/* 04.08.98 |   PGU  | - Add __NEW_SYNTHE... and __USE_HW_WAKE...           */
/*----------+--------+------------------------------------------------------*/
/* 15.04.99 |   ADA  | - Radio 2c management.                               */
/*----------+--------+------------------------------------------------------*/
/* 10.05.00 |MTH-DRC | - OneC V1.2 adaptation                               */
/*----------+--------+------------------------------------------------------*/
/* 10.01.01 |  FRK   | - No more default case                               */
/*----------+--------+------------------------------------------------------*/
/* 02.11.00 |  MTH   | - WHAT2 adaptation                                    */
/****************************************************************************/

#ifndef __COMDEFS_HC__
#define __COMDEFS_HC__

/* ----------------- radio dependent flags ------------------ */

#if defined    (__WISMO_2C_025__)
#define __RADIO_2C__
#define __ONE_C_V12__
#define __WISMO_2C__
#define __L1C_PLL_PWR_CTRL__

#elif defined  (__WISMO3__)
#define __RADIO_WISMO3__
#define __ONE_C_V12__
#define __WISMO_2C__
#define __L1C_PLL_PWR_CTRL__

#elif defined  (__WISMO_2C__)
#define __RADIO_2C__

#elif defined  (__WISMO_5__)
#define __RADIO_2C__
#else
//#error NO WISMO DEFINED
#endif

/* ----------------- WISMO dependent flags ------------------ */

#define __KERNEL32__     /* a garder pour compatibilité ascendante */
#define __KERNEL32A__
#define __KERNEL4__
#define __KERNEL5__
#define __ONE_C__

#define __E2P_NM24C16__  /* voir avec driver e2p ??? */
#define __ALL_PATCHES__  /* inutile dans HWL WHAT, pas de patches */
#define __LARGER_RXEN2__ /* inutile dans HWL WHAT, on a des delais differents  */
#define __UFO__          /* inutilisé */

/* ----------------- miscellaneous flags ------------------ */

#if !defined(__NO_POWER_DOWN__)
#define __HWL_PWDN__        /* (HWL + tasks.c) blocks pwdn */
#define __HWL_VAR_PWDN__    /* inutilisé dans HWL WHAT */
#define __AFC_BAD_SUPPLY__  /* utilisé par L1 et défini dans HWL */
#define __AFC_PWDN__        /* utilisé sur dans hactim.c */
#define __SLEEP_MODE__      /* coupure Fint */
#define __SLEEP_ARM__       /* utilisé dans tasks.c */
#endif

#if defined(__DEBUG__)      /* flags de debug */
#define __ZERO_MEMORY__
#define __DBG_POOL__
#define __DBG_SCR__
#ifdef __FIXME__
#define __WATCH_
#endif
#define __DIAGNOSE__
#define __RTK_DIAGNOSE__
#define __REMOTE_RTK__
#define __CHECK_ACTIVITY__
#define __L1C_WATCH__
#define __HWL_WATCH__
#define __BATT_WATCH__
#define __L1C_CNF__
#define __SPV_DEBUG__
#define LCD_EMULATION
#endif

/* ----------- mandatory flag (to be removed from code) ------------ */

#define __CBCH__              /* flags L1, RR... optionnels */
#define __TEST_TRANSMITTER__
#define __FAST_SCAN__
#define __L1C_USE_DATA_DTX__

#endif /* __COMDEFS_HC__ */


