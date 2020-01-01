/****************************************************************************/
/*  File    : SYS_FCM.HC                                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   : Definition of FCM  primitive numbers                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*   Date   | Author |  Modification                                        */
/*----------+--------+------------------------------------------------------*/
/* 07.02.01 |  FGA   |  Creation                                            */
/****************************************************************************/
/* $LogWavecom: G:\projet\gsm\pvcsarch\archives\sys\itf\sys_fcm.hc-arc $
 *--------------------------------------------------------------------------
 * Date     | Author | Revision       | Description
 *----------+--------+----------------+-------------------------------------
 * 08.04.05 | jlo    | 1.3.1.0        | Resolution for 28269: [WP3] Deliver
 *          |        |                | y of SYS  .                        
 *----------+--------+----------------+-------------------------------------
 * 03.12.03 | jlo    | 1.4            | .  Resolution for 17407: Flex integ
 *          |        |                | ration                             
 *----------+--------+----------------+-------------------------------------
 * 10.07.03 | jsu    | 1.3            | New traces for FCM  Resolution for 
 *          |        |                | 12629: New traces for FCM          
 *----------+--------+----------------+-------------------------------------
 * 29.10.02 | pci    | 1.2            | Change SYS statuts trace state _SYS
 *          |        |                |  instead of DATA level_20          
 *----------+--------+----------------+-------------------------------------
 * 07.10.02 | pci    | 1.1            | Add __FCM to V24 traces            
 *----------+--------+----------------+-------------------------------------
 * 02.10.02 | ddo    | 1.0            | Initial revision.                  
 *----------+--------+----------------+-------------------------------------
 *
 *   Rev 1.4   Jun 05 2002 18:47:16   apa
 *Correction for a problem in a comm data in nominal mode. FCM was not implemented for treatment of "connect"
 *
 *   Rev 1.3   Jun 05 2002 16:01:46   apa
 *Fix of the display bug of the "connect" in GSM data call in nominal mode 
 *
 *   Rev 1.2   Feb 11 2002 20:19:24   rdo
 *RDO on behalf of FGA: changed __FCM base from _DATA to _SYS.
 *
 *   Rev 1.1   Aug 31 2001 10:50:32   ddo
 *Update define (Lho)
*/

#ifndef __SYS_FCM_HC__
#define __SYS_FCM_HC__

#include "sys_sys_fcm.h"

#endif /* __SYS_FCM_HC__ */
