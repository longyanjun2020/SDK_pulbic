/****************************************************************************/
/*  File    : RM_E2P.HC                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Constants used by RM_TOOLS.C to manage E2P messages          */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/****************************************************************************/



#ifndef __RM_E2P_HC__
#define __RM_E2P_HC__

#if 0
#define ACTION_EEPROM_MASK  0xF000
#define OFFSET_EEPROM_MASK  0x0FFF
#define READ_PARAM   1 << 12
#define WRITE_PARAM  2 << 12
#define READ_OFFSET  3 << 12
#define WRITE_OFFSET 4 << 12
#define WRITE_PARAM_CONF   WRITE_PARAM  | 1 << 15
#define WRITE_OFFSET_CONF  WRITE_OFFSET | 1 << 15

#endif 

#define ACTION_EEPROM_MASK  0xE000
#define OFFSET_EEPROM_MASK  0x1FFF
#define READ_PARAM   1 << 13
#define WRITE_PARAM  2 << 13
#define READ_OFFSET  3 << 13
#define WRITE_OFFSET 4 << 12
#define WRITE_PARAM_CONF   WRITE_PARAM  | 1 << 15
#define WRITE_OFFSET_CONF  WRITE_OFFSET | 1 << 15

#define WRITE_OFFSET8k     9 << 12
#define WRITE_OFFSET4k     8 << 12



enum { E2P_NORMAL, E2P_ACQ_COMPLETE };

#define OBJ_READ_REQ		0x01
#define OBJ_READ_RSP		0x02
#define OBJ_WRITE_REQ		0x03
#define OBJ_WRITE_RSP		0x04
#define OBJ_ID_LIST_REQ		0x05
#define OBJ_ID_LIST_RSP		0x06
#define OBJ_DELETE_REQ          0x07
#define OBJ_DELETE_RSP          0x08
#define OBJ_REQ_ACK      	0x80

#define MAX_OBJECTMSG_LENGTH	256







#endif /* __RM_E2P_HC__ not defined   */
