/****************************************************************************/ 
/*  File    : v24_ctrl.hc                                                   */ 
/*--------------------------------------------------------------------------*/ 
/*  Scope   : constants for the signal controller                           */ 
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
/* 08/01/04 |  MSE   |      |  Creation                                     */ 
/****************************************************************************/
/*
$LogWavecom: U:\projet\gsm\pvcsarch\archives\v24\inc\v24_ctrl.hc-arc $
 *--------------------------------------------------------------------------
 * Date     | Author | Revision       | Description
 *----------+--------+----------------+-------------------------------------
 * 22.07.05 | mpr    | 1.4            | Resolution for 29434: Code cleaning
 *          |        |                |  : remove obsolete __NEW_V24_CTRL__
 *          |        |                |  flag.  .                          
 *----------+--------+----------------+-------------------------------------
 * 18.03.05 | pmr    | 1.3            | Resolution for 27999: New Contexts 
 *          |        |                | management in V24 (Update necessary
 *          |        |                |  for MUX/WBT purposes)  .          
 *----------+--------+----------------+-------------------------------------
 * 02.02.05 | mpr    | 1.2            | Resolution for 27548: New V24 archi
 *          |        |                | tecture (designed for CMUX and Blue
 *          |        |                | tooth)  .                          
 *----------+--------+----------------+-------------------------------------
 * 24.03.04 | mse    | 1.1            | .  Resolution for 19722: New V24   
 *----------+--------+----------------+-------------------------------------
 * 10.03.04 | mse    | 1.0            | Initial revision.  Resolution for 1
 *          |        |                | 9722: New V24                      
 *----------+--------+----------------+-------------------------------------
*/



#ifndef __SYS_V24_CTRL_HC__
#define __SYS_V24_CTRL_HC__

#define V24_RTS_BIT                         0
#define V24_CTS_BIT                         1
#define V24_DTR_BIT                         2
#define V24_DSR_BIT                         3
//#define V24_RI_BIT                         4
#define V24_DCD_BIT                         5 

#define V24_CHECK_MSC_CHANGE(Msc, Bit, Set) ((Msc & Bit)^  (Set))
#define V24_CHANGE_MSC(Msc, Bit)            ((Msc&Bit) ^= Bit)

#define V24_CTRL_MAX_NB_CTX                 12

#define V24_CTRL_MUX_MAX_NB_CTX             4
#define V24_CTRL_REL_MAX_NB_CTX             2
#define V24_CTRL_PAL_MAX_NB_CTX             3

typedef enum
{
   V24_LAYER_PAL,
   V24_LAYER_REL,
   V24_LAYER_MUX,
   V24_LAYER_HAPC,
   V24_LAYER_HUB,
   V24_LAYER_MAX
}eLayerId_t;

/*
** Lower Layer or Higher Layer
*/
#define V24_LL 0
#define V24_UL 1

#endif
