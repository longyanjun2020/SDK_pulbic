 /***********************************************************************/
/*  File    : obx_obex.hc				   						             	*/
/*----------------------------------------------------------------------*/
/*  Scope   :	constants and different parameters in OBEX           		*/
/*																	                  	*/
/*  Content :													               		*/
/*																                  		*/
/*----------------------------------------------------------------------*/
/*   Date       | Author |    Err	 |        Modification				*/
/*--------------+--------+-----------+----------------------------------*/
/*  28/07/1999  |  FRK   |           |        Creation					*/
/*--------------+--------+-----------+----------------------------------*/
/*  28/01/2002  |  MPR   |           |	Add a few changes for Debug		*/
/*				|		 |           |	Irda support					*/
/*--------------+--------+-----------+----------------------------------*/
/************************************************************************/
/* $LogWavecom: G:\projet\gsm\pvcsarch\archives\obex\inc\obx_obex.hc-arc $
 * --------------------------------------------------------------------------
 *  Date     | Author | Revision       | Description
 * ----------+--------+----------------+-------------------------------------
 *  23.03.04 | mse    | 1.5.1.15       | .  Resolution for 20149: OBEX heade
 *           |        |                | r decoding problem                 
 * ----------+--------+----------------+-------------------------------------
 *  17.10.03 | mse    | 1.5.1.14       | .  Resolution for 16227: OBEX conte
 *           |        |                | xt released too soon (before receiv
 *           |        |                | ing the media OFF message)  Resolut
 *           |        |                | ion for 16228: OBEX optimization (i
 *           |        |                | ncrease the max OBEX packet size)  
 * ----------+--------+----------------+-------------------------------------
 *  13.10.03 | mse    | 1.5.1.13       | .  Resolution for 16102: Modificati
 *           |        |                | ons for SYNCML over V24 or USB     
 * ----------+--------+----------------+-------------------------------------
 *  23.09.03 | mse    | 1.5.1.12       | . Resolution for 15553: OBEX reset 
 *           |        |                | when sending an unsupported object 
 *           |        |                | to the target                      
 * ----------+--------+----------------+-------------------------------------
 *  15.09.03 | mse    | 1.5.1.11       | For OSS .  Resolution for 15250: OB
 *           |        |                | EX: Added and changed comments for 
 *           |        |                | OSS                                
 * ----------+--------+----------------+-------------------------------------
 *  03.09.03 | mse    | 1.5.1.10       | .  Resolution for 14770: [IrDA] IRD
 *           |        |                | A communication fail between WINDOW
 *           |        |                | 2000 PC and Handset.  Resolution fo
 *           |        |                | r 14929: Obex connect indication si
 *           |        |                | ze field is erroneous  Resolution f
 *           |        |                | or 14930: Obex get indication probl
 *           |        |                | em                                 
 * ----------+--------+----------------+-------------------------------------
 *  11.08.03 | mse    | 1.5.1.9        | . Resolution for 13764: obex proble
 *           |        |                | m in fragmentation  Resolution for 
 *           |        |                | 13977: Obex problem in Get request 
 * ----------+--------+----------------+-------------------------------------
 *  30.07.03 | mpr    | 1.5.1.8        | .  Resolution for 13345: Refonte Ir
 *           |        |                | da + modif Obex sous tâche         
 * ----------+--------+----------------+-------------------------------------
 *  27.06.03 | mse    | 1.5.1.6        | obex as a task  Resolution for 1209
 *           |        |                | 2: OBEX as a task                  
 * ----------+--------+----------------+-------------------------------------
 *  06.05.03 | mse    | 1.5.1.1        | corrected Bug in Connect corrected 
 *           |        |                | Bug in Disconnect one way Get Added
 * ----------+--------+----------------+-------------------------------------
 *  05.05.03 | mse    | 1.5.1.0        | OBEX with a modified interface with
 *           |        |                |  MMT and a new interface with SyncM
 *           |        |                | L                                  
 * ----------+--------+----------------+-------------------------------------
 *  21.08.02 | mpr    | 1.5            | Add Log modification to avoid pbs i
 *           |        |                | n the end of files.                
 * ----------+--------+----------------+-------------------------------------
*/
#ifndef __OBX_OBEX_HC__
#define __OBX_OBEX_HC__

/*** COMMAND ***/
#define OBEX_CONNECT_CMD	   0x80
#define OBEX_PUT_CMD		      0x02
#define OBEX_FINAL_PUT_CMD	   0x82
#define OBEX_DISCONNECT_CMD	0x81
#define OBEX_GET_CMD		      0x03
#define OBEX_FINAL_GET_CMD	   0x83
#define OBEX_ABORT_CMD		   0xFF
#define OBEX_SETPATH_CMD	   0x85

/*** RESPONSE ***/
#define OBEX_CONTINUE_RSP	             0x90
#define OBEX_SUCCESS_RSP	             0xA0
#define OBEX_KO_TOO_LARGE               0xCD
#define OBEX_BAD_REQUEST	             0xC0
#define OBEX_FORBIDDEN                  0xC3
#define OBEX_OBJECTTYPE_NOTSUPPORTED    0xCF
#define OBEX_GET_RSP		                OBEX_CONTINUE_RSP
#define OBEX_CONNECT_FAIL               0xC3
#define OBEX_DISCONNECT_FAIL            0xC3
#define OBEX_ABORT_FAIL                 0xC3
#define OBEX_LENGTH_REQUIRED            0xCB
#define OBEX_INTERNAL_SERVER_ERROR      0xD0
#define OBEX_DATABASE_FULL              0xE0
#define OBEX_DATABASE_LOCKED            0xE1

/*** HEADER ***/
#define OBEX_HI_NAME		       0x01
#define OBEX_HI_LENGTH	       0xC3
#define OBEX_HI_TYPE           0x42
#define OBEX_HI_BODY		       0x48
#define OBEX_HI_BODY_END       0x49
#define OBEX_HI_TARGET         0x46
#define OBEX_HI_WHO            0x4A
#define OBEX_HI_CONNECTION_ID  0xCB

#define OBEX_HI_BITSMASK       0xC0

#define OBEX_HI_BITSMASK_1     0x00
#define OBEX_HI_BITSMASK_2     0x40
#define OBEX_HI_BITSMASK_3     0x80
#define OBEX_HI_BITSMASK_4     0xC0

/*Globale_state*/
#define OBEX_START                  0x09
#define OBEX_CONNECT_OBEX	         0x0A
#define OBEX_CONNECT_APPLI	         0x0B
#define OBEX_CONNECTED              0x0C
#define OBEX_PUT_RSP_REMOTE_PDG     0x0D
#define OBEX_PUT_REQ_APPLI_PDG      0x0E
#define OBEX_PUT_RSP_APPLI_PDG      0x0F
#define OBEX_PUT_REQ_REMOTE_PDG     0x10
#define OBEX_GET_RSP_REMOTE_PDG     0x11
#define OBEX_GET_REQ_APPLI_PDG      0x12
#define OBEX_GET_RSP_APPLI_PDG      0x13
#define OBEX_GET_REQ_REMOTE_PDG     0x14
#define OBEX_DISCONNECT_OBEX		   0x15
#define OBEX_DISCONNECTED_SERVER	   0x16
#define OBEX_DISCONNECT_APPLI       0x17
#define OBEX_DISCONNECTED_CLIENT	   0x18
#define OBEX_ABORT_APPLI_PDG   	   0x19

/* Mandatory Packet Size */
#define OBEX_OBEX_CONNECT_REQ_SIZE     0x07
#define OBEX_OBEX_CONNECT_RSP_SIZE     0x07
#define OBEX_OBEX_PUT_REQ_SIZE         0x03
#define OBEX_OBEX_PUT_RSP_SIZE         0x03
#define OBEX_OBEX_GET_REQ_SIZE         0x03
#define OBEX_OBEX_GET_RSP_SIZE         0x03
#define OBEX_OBEX_DISCONNECT_REQ_SIZE  0x03
#define OBEX_OBEX_DISCONNECT_RSP_SIZE  0x03
#define OBEX_OBEX_ABORT_RSP_SIZE       0x03

/* Header Size  */
#define OBEX_OPCODE_SIZE              0x01
#define OBEX_HEADERSIZE_CONNECTIONID  0x05
#define OBEX_HEADERSIZE_LENGTH        0x05
#define OBEX_HEADERSIZE_GENERAL       0x03

/* Index of Headers in array */

#define OBEX_INDEX_NAME                0
#define OBEX_INDEX_TYPE                1
#define OBEX_INDEX_LENGTH              2
#define OBEX_INDEX_CONNECTIONID        3
#define OBEX_INDEX_BODY                4

/*internal Headers definition */
#define OBEX_OBEX_NOHEADERS           0x00
#define OBEX_OBEX_HEADER_CONNECTIONID 0x01
#define OBEX_OBEX_HEADER_TARGET       0x02
#define OBEX_OBEX_HEADER_NAME         0x04
#define OBEX_OBEX_HEADER_TYPE         0x08
#define OBEX_OBEX_HEADER_LENGTH       0x10
#define OBEX_OBEX_HEADER_BODY         0x20


/* Application requestion to use Obex*/

#define OBEX_APPLI_MMT  0x00
#define OBEX_APPLI_SYNC 0x01
#define OBEX_APPLI_NONE 0xFF

/* OBEX Version */

#define OBEX_VERSION    0x10

/*MISC*/
#define OBEX_RSP		0x0100

#ifdef __DEBUG_IRDA__
#define OBEX_MAX_PACKET_SIZE	310
#else
#define OBEX_MAX_PACKET_SIZE	310
#endif
#define OBEX_MAX_OBJECT_SIZE  512


#define OBEX_APPLI_MEDIA_RSP_SUCCESS          0x01
#define OBEX_APPLI_MEDIA_RSP_FAIL             0x00

#define OBEX_CONNECT_RSP_SUCCESS            0x00
#define OBEX_CONNECT_RSP_FAIL_REMOTE        0x01
#define OBEX_CONNECT_RSP_FAIL_MEDIANOTSETUP 0x02
#define OBEX_CONNECT_RSP_FAIL_PROTOCOLERR   0x03

#define OBEX_PUT_RSP_CONTINUE                 0x00
#define OBEX_PUT_RSP_SUCCESS                  0x01
#define OBEX_PUT_RSP_OBJECT_TOOLARGE          0x02
#define OBEX_PUT_RSP_OBJECT_TYPENOTSUPPORTED  0x03
#define OBEX_PUT_RSP_PACKET_TOOLARGE          0x04
#define OBEX_PUT_RSP_FAIL_PROTOCOLERR         0x05
#define OBEX_PUT_RSP_FAIL_NONAME              0x06
#define OBEX_PUT_RSP_FAIL_NOTYPE              0x07
#define OBEX_PUT_RSP_FAIL_REMOTE_OTHER        0x08
#define OBEX_PUT_RSP_DATABASE_FULL            0x09

#define OBEX_GET_RSP_CONTINUE                 0x00
#define OBEX_GET_RSP_SUCCESS                  0x01
#define OBEX_GET_RSP_BADREQUEST               0x02
#define OBEX_GET_RSP_FORBIDDEN                0x03
#define OBEX_GET_RSP_FAIL_REMOTE_OTHER        0x08

#define OBEX_DISCONNECT_IND_REMOTE            0x00
#define OBEX_DISCONNECT_IND_PROTOCOLERR       0x01

#define OBEX_DISCONNECT_RSP_SUCCESS           0x00
#define OBEX_DISCONNECT_RSP_FAIL              0x01

#define OBEX_ABORT_RSP_SUCCESS                0x00
#define OBEX_ABORT_RSP_FAIL                   0x01

#define OBEX_GET_NOATTRIBUTES                 0x00

#define OBEX_FRAGMENT_SIZE                    64
 
/* contant the UUID*/
#define UUID_SYNCML_SYNC_SIZE       0x0B
#define UUID_SYNCML_DEVM_SIZE       0x0B

             
#define OBEX_WHOLELENGTH_NOTFILLED 0xFFFFFFFF

#define OBEX_NOFLAGS 0x00

/*Media*/

#define OBEX_MEDIA_IRDA      0x00
#define OBEX_MEDIA_BLUETOOTH 0x01
#define OBEX_MEDIA_V24       0x02
#define OBEX_MEDIA_USB       0x03
#define OBEX_MEDIA_AIR       0x04

#define OBEX_MEDIA_NONE      0xFF

#define OBEX_IRDA_MEDIA_IRDA 0x00
#define OBEX_IRDA_MEDIA_V24  0x01
/*********************************************************************/

#define OBEX_IRDA_CONNECT_OK  0x00
#define OBEX_IRDA_CONNECT_NOK 0x01
/*********************************************************************/

#define OBEX_IRDA_PROTOCOL_ERROR			0x20
#define OBEX_IRDA_NORMAL_RELEASE			0x21
#define OBEX_IRDA_OUT_OF_RANGE		   0x30

#define OBEX_IRDA_DISCONNECT_CONNECTERR 0x00


#define OBEX_MAXPACKET_SECURITY_SIZE  60


/* define traces levels */
#define OBX_INT_MESSAGE        _OBX 
#define OBX_EXT_MESSAGE_IN     _OBX 
#define OBX_EXT_MESSAGE_OUT    _OBX                             
#define OBX_DUMP               _OBX 
#define OBX_OTHER              _OBX 
/*
** --------------------------------------------------------------------------
**                       GENERAL PURPOSE MACROS
** --------------------------------------------------------------------------
*/

#define _MIN_(_X_,_Y_)       (((_X_) < (_Y_)) ? (_X_) : (_Y_))
#define _MAX_(_X_,_Y_)       (((_X_) > (_Y_)) ? (_X_) : (_Y_))


/*
** Release Memory
*/
#define Obex_ReleaseMemory(__x__)  _Obex_ReleaseMemory( (void **)(&(__x__)))

#endif /* __OBX_OBEX_HC__ */
