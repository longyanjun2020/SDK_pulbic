/******************************************************************************/
/* File    : sysusbdrv.h                                                      */
/*----------------------------------------------------------------------------*/
/* Scope   : System USB driver header file                                    */
/*                                                                            */
/******************************************************************************/
#ifndef __DUMP_LOG_H__
#define __DUMP_LOG_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#define LOG_BUFFER_LENGTH   (30 * 1024)

#ifdef DUMP_LOG
u8 LogBuffer[LOG_BUFFER_LENGTH];
u32 LogBufferIndex=0;
#else
extern u8 LogBuffer[];
extern u32 LogBufferIndex;
#endif

extern void send_NAK_log(void);

#endif /* __DUMP_LOG_H__ */
