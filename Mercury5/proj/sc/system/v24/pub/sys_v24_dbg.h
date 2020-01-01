/****************************************************************************/
/* File    : V24_DBG.H                                                      */
/*--------------------------------------------------------------------------*/
/* Scope   :  serial handler debug facilities                               */
/*                                                                          */
/*----------+---------+-----------------------------------------------------*/
/* Date     | Author  | Modification                                        */
/*----------+---------------------------------------------------------------*/
/* 05/03/96 |  RDO    | Creation                                            */
/*----------+---------------------------------------------------------------*/
/* 09/08/96 |  RDO    | rm_debug.hc -> v24_dbg.hc                           */
/*----------+---------------------------------------------------------------*/
/* 16/06/98 |  RDO    | Add _PULSE macro (fast pulse)                       */
/*          |         | Get rid of debug stuff no more used                 */
/*----------+---------------------------------------------------------------*/
/* 07/09/98 |  RDO    | Add _BYTE0 and _BYTE1 to assert bus to specified val*/
/*----------+---------------------------------------------------------------*/
/* 16/08/99 |  RDO    | Port _BYTE debugging facility to kernel 1C          */
/*----------+---------------------------------------------------------------*/
/* 26/08/99 |  RDO    | include sys_gpio.hp for 1C, add _NIB debug macro    */
/****************************************************************************/
/*$LogWavecom: U:\projet\gsm\pvcsarch\archives\v24\pub\sys_v24_dbg.h-arc $
 * --------------------------------------------------------------------------
 *  Date     | Author | Revision       | Description
 * ----------+--------+----------------+-------------------------------------
 *  05.01.05 | aph    | 3.2            | Resolution for 27275: V24 internal
 *           |        |                | dev synchro step : Monostack report
 *           |        |                |  to new FCM  .
 * ----------+--------+----------------+-------------------------------------
 *
 *    Rev 3.1   Oct 29 2002 17:02:52   sgr
 * Add modifs for What
 *
 *    Rev 3.0   Aug 29 2002 10:48:12   sgr
 * integration dev tf V19
*/
#ifndef __SYS_V24_DBG_H__
#define __SYS_V24_DBG_H__

#include "comdefs.hc"   /* Common define flags */

//#include "kernel.h"

#include "msgtyp.ht"

#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __v24_dbg_c__
#define DefExtern
#else
#define DefExtern extern
#endif

#ifndef __TARGET__
//
// The two following functions are used only for HAPC on PC
//
u16  v24_GetCharFromRxDataBuf(void);
bool v24_RxDataBufNotEmpty(void);
#else
#define FPULSE( NoBit ) /* fast pulse, assume GPIO is set as an output */\
{\
   Gpio->Data |=   1 << NoBit;\
   Gpio->Data &= ~(1 << NoBit);\
}
#endif

#if defined (__WHAT__)

//nothing for the moment

#elif defined (__ONE_C__)
//
// Debug facilities for 1C only.
//

//
// Call this macro once before using following macros.
//
#define _BYTE_INIT( use_gpio )\
{\
   *(volatile u16*)0x4000006 &= ~(0x01 << 7 | 0x01 << 10); /* no view mode & LCDEN */\
   *(volatile u16*)0x4000200 =  1 /* N1 */ | 1 /* N2 */ << 8;\
   if ( use_gpio ) *(volatile u16*)0x4001E02 &= 0xF0FF; /* GPIOs 8..11 as output */\
}

#define _NIBBLE( x ) *(volatile u16*)0x4000300 = (x)
#define _NIB( x )    _NIBBLE( x )

#define _BYTENIB( x ) { _NIBBLE( x ); _NIBBLE( (x) >> 4 ); }

/*
** it asserts the 4 lowest data bus bits to the lower nibble of x and
** GPIOs 8,9,10,11 to the upper nibble of x.
** Note: it assumes GPIOs are already setup as output.
** WARNING: this macro should be interrupts protected, but for efficiency
** purpose it is not!!!
**
** Don't meddle with this macro since it has been finely tuned to be as
** quick as possible.
** First call it is called: 2 us, subsequent consecutive calls: 1 us.
*/
#define _BYTE( x )\
{\
   u32 tmp = *(u16*)0x4001E00;\
   u32 sav = tmp;\
   tmp &= 0xFFFFF0FF;\
   tmp |= ((x) >> 4) << 8;\
   *(u16*)0x4001E00 = tmp;\
   *(volatile u16*)0x4000300 = (x);\
   *(u16*)0x4001E00 = sav;\
}
#else
// Assert the data bus to 'x' and raise LCD_EN.
#define _BYTE0( x )  *(volatile u8*)0x13000000 = x
#define _INT0( x  )  { _BYTE0( x ); _BYTE0( x>>8 ); _BYTE0( x>>16 ); _BYTE0( x>>24 ); }

// Assert the data bus to 'x' and lower /CS_USR2.
#define _BYTE1( x )  *(volatile u8*)0x65000000 = x
#define _INT1( x  )  { _BYTE1( x ); _BYTE1( x>>8 ); _BYTE1( x>>16 ); _BYTE1( x>>24 ); }
#endif

#undef DefExtern
#endif

