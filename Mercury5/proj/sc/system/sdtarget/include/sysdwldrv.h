/******************************************************************************/
/* File    : sysdwldrv.h                                                      */
/*----------------------------------------------------------------------------*/
/* Scope   : System download driver header file                               */
/*                                                                            */
/******************************************************************************/
#ifndef __SYSDWLDRV_H__
#define __SYSDWLDRV_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "sysdwlcfg.h"


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
/* dwl_port.c */
u8      dwl_getDwldPath(void);
s32     dwl_sendPacket(u8 *databuf, u32 u32len);
s32     dwl_sendPacket_nonBlock(u8 *databuf, u32 u32len);
void    dwl_sendChar(u8 u8char);
s32     dwl_recvPacket(u8 *databuf, u32 u32len);
s32     dwl_recvPacket_nonBlock(u8 *databuf, u32 u32len);
s32     dwl_recvPacket_timeout(u8 *databuf, u32 u32len, u16 msec);
u8      dwl_getChar(void);
s32     dwl_getChar_timeout(u8 *ptrchar, u16 msec);
void dwl_getChar_timeout_shutdown_USB(u8 getbyte);

/* dwl_gpframe.c */
void    dwl_sendGPFrame(void *dataBuf, u32 u32size);
s32     dwl_getGPFrame(void *dataBuf, u32 u32size);

/* dwl_resync.c */
void    dwl_resync(void);

#endif /* __SYSDWLDRV_H__ */
