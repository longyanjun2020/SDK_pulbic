/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright VMTS S.A. (c) 2001
*/

/****************************************************************************/
/*  File    : VM_GMASK.HC                                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   : General definition of masks for bit field access              */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Changes     :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/*----------+--------+------+-----------------------------------------------*/
/****************************************************************************/


#ifndef __VM_GMASK_HC__
#define __VM_GMASK_HC__                                                        


/* 
   Definition of different lenght of masks
   from 1 to 8 but possible to extend on more...
*/

#define MASKL1  0x01      /*          1  */
#define MASKL2  0x03      /*         11  */
#define MASKL3  0x07      /*        111  */
#define MASKL4  0x0f      /*       1111  */
#define MASKL5  0x1f      /*      11111  */
#define MASKL6  0x3f      /*     111111  */
#define MASKL7  0x7f      /*    1111111  */
#define MASKL8  0xff      /*   11111111  */


/* 
   Macro to get a value in a byte in accordance with 
      - The lenght in bits of the value 
      - Its position in the Byte
   
*/

#define GETMSK(val, pos, msk)   (((val) & ((msk)<<(pos)) ) >> (pos))

#define GETMSK8(val, pos, msk)  ((u8) ((int)val & ((int)msk<<(int)pos) ) >> (int)pos)




/* Macro to put a value in a byte */

#define PUTMSK(var, val, pos)  (var | (val<<pos))


#endif  /* __VM_GMASK_HC__ */

