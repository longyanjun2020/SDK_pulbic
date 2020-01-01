/****************************************************************************/
/*  File    : sim_glob.h                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : General definitions                                           */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 06.06.98 |   HAZ  |      |  REVERSE_BIT_FIELDS -> REVERSE_BIT_FIELD      */
/* 03.01.95 |   YFE  |      |  Define reverse ordered bit fields            */
/* 02.12.94 |   YFE  |      |  Creation                                     */
/*----------+--------+------+-----------------------------------------------*/
/****************************************************************************/


#ifndef __SIM_GLOB_H__
#define __SIM_GLOB_H__


#include "stdcomp.h" 


#ifndef bit_t
#  define bit_t   u32
#endif


/*
** --------------------------------------------------------------------------
**   Ciphering key (Kc) structure                           
** --------------------------------------------------------------------------
*/

#define MAXKC       8 

typedef struct { u8 Kc[MAXKC]; } Kc_t;


/*
** --------------------------------------------------------------------------
**   Random number (RAND) structure                         
** --------------------------------------------------------------------------
*/

#define MAXRAND     16

typedef struct { u8 Rand[MAXRAND]; } Rand_t;


/*
** --------------------------------------------------------------------------
**   Signature Response (SRES) structure                    
** --------------------------------------------------------------------------
*/

#define MAXSRES     4

typedef struct { u8 Sres[MAXSRES]; } Sres_t;


/*
** --------------------------------------------------------------------------
**   Temporary Mobile Subscriber Identity (TMSI) structure
** --------------------------------------------------------------------------
*/

#define MAXTMSI     4
#define NOTMSI      (u32) 0xFFFFFFFF    /* invalid TMSI                     */

typedef u8 Tmsi_t[ MAXTMSI ];


/*
** --------------------------------------------------------------------------
**   Location Area Identifier (LAI) structure
** --------------------------------------------------------------------------
*/

#define NOLAC1      (u16) 0x0000        /* invalid LAC phase 1              */
#define NOLAC2      (u16) 0xFFFE        /* invalid LAC phase 2              */

#ifdef __PHASE2__
#define NOLAC       NOLAC2
#else
#define NOLAC       NOLAC1
#endif



#define SET_LAC(pt, val)  { pt[ 3 ] = (u8)(val >> 8); pt[ 4 ] = (u8)(val); }
#define GET_LAC(pt)       (u16)((u16)(pt[ 3 ] << 8) | (u16)(pt[ 4 ]))


/*
** --------------------------------------------------------------------------
**   International Mobile Subscriber Identity (IMSI) structure
** --------------------------------------------------------------------------
*/

#define MAXIMSI     8


typedef u8 Imsi_t[ 9 ], Imei_t[ 9 ], ImeiSv_t[ 10 ];

#define POSTMSI     2               /* TMSI pos in Imsi[9]                  */


#define MS_IDENTITY(_p_)     (((u8 *)_p_)[1] & 7)
#define NIBBLE1(_p_)         (((u8 *)_p_)[1] >> 4)


#ifndef __REVERSE_BIT_FIELD__

typedef struct
{
    bit_t   Len    : 8;             /* Identity length                      */

    bit_t   iden   : 3;             /* Identity type                        */
    bit_t   even   : 1;             /* even (TRUE) odd (FALSE)              */
    bit_t   imsi1  : 4; 
    
    bit_t   imsi2  : 4; 
    bit_t   imsi3  : 4; 
    
    bit_t   imsi4  : 4; 
    bit_t   imsi5  : 4; 
    
    bit_t   imsi6  : 4; 
    bit_t   imsi7  : 4; 
    
    bit_t   imsi8  : 4; 
    bit_t   imsi9  : 4; 
    
    bit_t   imsi10 : 4; 
    bit_t   imsi11 : 4; 
    
    bit_t   imsi12 : 4; 
    bit_t   imsi13 : 4; 
    
    bit_t   imsi14 : 4; 
    bit_t   imsi15 : 4; 

} ImsiMask_t; 

#else

typedef struct
{
    bit_t   Len    : 8;             /* Identity length                      */

    bit_t   imsi1  : 4; 
    bit_t   even   : 1;             /* even (TRUE) odd (FALSE)              */
    bit_t   iden   : 3;             /* Identity type                        */
    
    bit_t   imsi3  : 4; 
    bit_t   imsi2  : 4; 
    
    bit_t   imsi5  : 4; 
    bit_t   imsi4  : 4; 
    
    bit_t   imsi7  : 4; 
    bit_t   imsi6  : 4; 
    
    bit_t   imsi9  : 4; 
    bit_t   imsi8  : 4; 
    
    bit_t   imsi11 : 4; 
    bit_t   imsi10 : 4; 
    
    bit_t   imsi13 : 4; 
    bit_t   imsi12 : 4; 
    
    bit_t   imsi15 : 4; 
    bit_t   imsi14 : 4; 

} ImsiMask_t; 

#endif   /* __REVERSE_BIT_FIELDS__ */


/*-- Identity type --*/

#define TYP_NOID    0x00                /* No identity                      */
#define TYP_IMSI    0x01                /* IMSI                             */
#define TYP_IMEI    0x02                /* IMEI                             */
#define TYP_IMEISV  0x03                /* IMEISV                           */
#define TYP_TMSI    0x04                /* TMSI                             */

#define IS_IDENTITY(_Id_) ((_Id_) >= TYP_IMSI && (_Id_) <= TYP_TMSI)


#define ZIMSI(pt, el)        ((ImsiMask_t *)(pt))->el


/*
** --------------------------------------------------------------------------
**   MOBILE STATION CLASSMARK 2 (MSCM2) structure                
** --------------------------------------------------------------------------
*/

typedef struct
{
    s8      Len;                    /* MSCM2 length                         */
    u8      MsCm2[ 3 ];             /* MSCM2                                */

} Mscm2_t;


#ifndef __REVERSE_BIT_FIELDS__

typedef struct
{
    bit_t   rfpow   : 2 ;           /* RF Power Capability                  */
    bit_t   free1   : 1 ;           /* Not used                             */
    bit_t   encrypt : 2 ;           /* Encryption Algorithm                 */
    bit_t   level   : 3 ;           /* Revision Level                       */
    
    bit_t   freq    : 3 ;           /* Frequency Capability                 */
    bit_t   smscap  : 1 ;           /* Short Message Capability             */
    bit_t   free2   : 3 ;           /* Not used                             */
    bit_t   ext1    : 1 ;           /* Extension bit                        */

    bit_t   free3   : 8 ;           /* Not used                             */

} Mscm2Mask_t;

#else

typedef struct
{
    bit_t   level   : 3 ;           /* Revision Level                       */
    bit_t   encrypt : 2 ;           /* Encryption Algorithm                 */
    bit_t   free1   : 1 ;           /* Not used                             */
    bit_t   rfpow   : 2 ;           /* RF Power Capability                  */
    
    bit_t   ext1    : 1 ;           /* Extension bit                        */
    bit_t   free2   : 3 ;           /* Not used                             */
    bit_t   smscap  : 1 ;           /* Short Message Capability             */
    bit_t   freq    : 3 ;           /* Frequency Capability                 */

    bit_t   free3   : 8 ;           /* Not used                             */

} Mscm2Mask_t;

#endif   /* __REVERSE_BIT_FIELDS__ */


/*-- RF power capability --*/

#define RFPOW1          0x00        /* Class 1, vehicle and portable        */
#define RFPOW2          0x01        /* Class 2, portable                    */
#define RFPOW3          0x02        /* Class 3, handheld                    */
#define RFPOW4          0x03        /* Class 4, handheld                    */
#define RFPOW5          0x04        /* Class 5, handheld                    */


/*-- Revision level --*/

#define LEVELP1         0x00        /* Revision level phase 1               */
#define LEVELP2         0x01        /* Revision level phase 2               */


/*-- Encryption algorithm --*/

#define ENCRYPA5        0x00        /* A5 Algorithm supported               */


/*-- Frequency Capability --*/

#define BAND0           0x00        /* Band Number 0                        */
#define BAND1           0x01        /* Band G1 supported                    */


/*-- SMS capability --*/

#define SMSYES          0x00        /* SMS Capability not present           */
#define SMSNO           0x01        /* SMS Capability present               */


#define ZMSCM2(pt, el)          ((Mscm2Mask_t *)(pt))->el
#define ZFMSCM2(pt, el)         ((Mscm2Mask_t far *)(pt))->el


#endif  /* __SIM_GLOB_H__ */


