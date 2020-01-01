/****************************************************************************/
/*  File    : RM_E2P.HC                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Constants used by RM_TOOLS.C to manage E2P messages          */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   3.3  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   lbu    $         |     $Date::   Sep 12 2003 14:18:50 $     */
/****************************************************************************
 * $LogWavecom: G:\projet\gsm\pvcsarch\archives\trc\inc\rm_e2p.hc-arc $
 * --------------------------------------------------------------------------
 *  Date     | Author | Revision       | Description
 * ----------+--------+----------------+-------------------------------------
 *  11.04.03 | lho    | 3.2            | .  Resolution for 9411: compatibili
 *           |        |                | ty with remote task kernel
 * ----------+--------+----------------+-------------------------------------
 *  01.10.02 | ddo    | 3.1            | Add info EEPROM 2
 * ----------+--------+----------------+-------------------------------------
 *  30.08.02 | ddo    | 3.0            | integration dev tf V19
 * ----------+--------+----------------+-------------------------------------
 *
 *   Rev 1.0   Jul 05 2001 15:23:06   ddo
 *Initial revision.
 ****************************************************************************/



#ifndef __RM_E2P_HC__
#define __RM_E2P_HC__


/* INFO_EEPROM --------------------------------------------- */
#define ACTION_EEPROM_MASK  0xF000

// add start for 8k start
#define OFFSET_EEPROM_MASK  0x1FFF
#define OFFSET_EEPROM_MASK_4k  0x0FFF
#define OFFSET_EEPROM_MASK_8k  0x1FFF
#define READ_PARAM   1 << 12
#define WRITE_PARAM  2 << 12
#define READ_OFFSET8k  9 << 12
#define READ_OFFSET4k  3 << 12
#define WRITE_OFFSET8k 5 << 12
#define WRITE_OFFSET4k 4 << 12
#define WRITE_PARAM_CONF   WRITE_PARAM  | 1 << 15
#define WRITE_OFFSET_CONF  WRITE_OFFSET4k | 1 << 15
// add for e2p 8k end


// new protocol for e2p

/* INFO_EEPROM3  --------------------------------------------- */
#define  READ_E2P    0x00
#define  WRITE_E2P  0x01
#define  RSP_READ_E2P    0x80
#define  RSP_WRITE_E2P  0x81

enum { E2P_NORMAL, E2P_ACQ_COMPLETE };

#define OBJ_READ_REQ            0x01
#define OBJ_READ_RSP            0x02
#define OBJ_WRITE_REQ           0x03
#define OBJ_WRITE_RSP           0x04
#define OBJ_ID_LIST_REQ         0x05
#define OBJ_ID_LIST_RSP         0x06
#define OBJ_DELETE_REQ          0x07
#define OBJ_DELETE_RSP          0x08

#define OBJ_REQ_ACK             0x80

#define MAX_OBJECTMSG_LENGTH    256

/* INFO_EEPROM2 -------------------------------------------- */
#define E2P_ADRESS 1 /* not acess by a enumeration */
#define E2P_READ   2 /* not write */
#define E2P_REQUEST_REFUSED 32
#define E2P_REQUEST_RESPONSE 64 /* response to TMT (MOKA) */
#define E2P_REQUEST_ACKNOLEDGE 128 /* data writen */
#define E2P_GET_ADRESS(X) (X & E2P_ADRESS)
#define E2P_GET_READ(X) (X & E2P_READ)






#endif /* __RM_E2P_HC__ not defined   */
