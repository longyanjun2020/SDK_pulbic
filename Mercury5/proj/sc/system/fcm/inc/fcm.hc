/****************************************************************************/
/*  File    : FCM.HC                                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : Definition of FCM  primitive numbers                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*   Date   | Author |  Modification                                        */
/*----------+--------+------------------------------------------------------*/
/* 07.02.01 |  FGA   |  Creation                                            */
/****************************************************************************/
/* 
   $LogWavecom: U:\projet\gsm\pvcsarch\archives\fcm\itf\fcm.hc-arc $
 *--------------------------------------------------------------------------
 * Date     | Author | Revision       | Description
 *----------+--------+----------------+-------------------------------------
 * 28.11.03 | fga    | 1.1            | removed msg prims.  17336 : Resolut
 *          |        |                | ion for FCM: better separation of c
 *          |        |                | onstants in interface              
 *----------+--------+----------------+-------------------------------------
 * 19.11.03 | fga    | 1.1            | added FAL related trace levels  170
 *          |        |                | 46 : Resolution for FCM: create ope
 *          |        |                | n MMI interface - FAL              
 *----------+--------+----------------+-------------------------------------
 * 04.11.03 | fga    | 1.0            | Initial revision.                  
 *----------+--------+----------------+-------------------------------------
*/

#ifndef __FCM_HC__
#define __FCM_HC__

#include "msgofs.hc"

/* TRACE LEVELS */

#define __FCM                       _FCM
#define _FCM_DEBUG                  _FCM | LEVEL_0    /* FCM Debug */
#define _FCM_MSG                    _FCM | LEVEL_7    /* FCM messages and notifications */
#define FCM_LEVEL_DATA_UPLINK       _FCM | LEVEL_2
#define FCM_LEVEL_DATA_DOWNLINK     _FCM | LEVEL_3
#define FCM_LEVEL_V24_AT            _FCM | LEVEL_4

#define _FCM_FAL                    _FCM | LEVEL_5 /* FAL (cus if) traces */


#define _trace                   _TRACE
#define FCM_NO_PARAM             0x08000000
#define FCM_ONE_PARAM            0x10000000
#define FCM_TWO_PARAM            0x18000000
#define FCM_THREE_PARAM          0x20000000
#define FCM_FOUR_PARAM           0x28000000
#define FCM_FIVE_PARAM           0x30000000
#define FCM_SIX_PARAM            0x38000000

#endif
