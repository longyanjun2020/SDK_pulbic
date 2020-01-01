/**
 *
 * @file    ema_util.h
 *
 * @brief   This file defines header of EMA utility function
 *
 * @author  Pauli Leong
 * @version $Id: ema_util.h 12522 2008-07-15 03:14:35Z jack.hsieh $
 *
 */
#ifndef __EMA_UTIL_H__
#define __EMA_UTIL_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_UTIL__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/
#ifdef __EMA_DEBUG__
#define EMA_PANIC(s) { for(;;){ MsSleep(100);} }
#define EMA_ASSERT(x)  if ((x)){ EMA_PANIC (x); }
#else
#define EMA_ASSERT(x)
#endif


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*
 * @brief 
 *   
 * @param
 *
 * @return
 */
char * ConvAscToUtf16(char *asc);


/*
 * @brief 
 *   
 * @param
 *
 * @return
 */
char * ConvUtf16ToAsc(char *utf);


/*
 * @brief 
 *   
 * @param
 *
 * @return
 */
u32 MsUTF16ToMsmUTF16(u8 *Msutf16_In, u8 *Msmutf16_out);


/*
 * @brief 
 *   
 * @param
 *
 * @return
 */
void MsmUTF16ToMsUTF16(u8 *Msmutf16_In, u32 Len_In, u8 *Msutf16_Out);


/*
 * @brief 
 *   
 * @param
 *
 * @return
 */
s8 ema_Dbg(u32 level, u8 *pString, ...);

#endif

