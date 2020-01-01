////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_mx_rbuffer.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_RBUFFER_H__
#define __MDL_VDR_MX_RBUFFER_H__

#include <mdl_vdr_rbuffer.h>

/* the interface inhiert from rbuffer in shell\current\include" */

/* direct read/write rouintes & macros */
/* ----------------------- */
/* get address from ring buffer only when buf is NULL*/
/* otherwise, read data ring buffer to buf */
/* get address to read <len> bytes from ring buffer */
/* when the available buffer to read is ring back to head of the buffer */
/* only return bottom block in <actuallen> bytes */
/* actuallen is meaningless when len is equal to 0 */
extern uint8_t * ringbuffer_read_direct(struct ringbuffer *rbuf, uint8_t *buf, uint32_t len, uint32_t *actuallen);
/* get address from ring buffer only when buf is NULL*/
/* otherwise, write data from buf to ring buffer */
/* get address to write <len> bytes to ring buffer */
/* when the free buffer to write is ring back to head of the buffer */
/* only return bottom block in <actuallen> bytes */
extern uint8_t * ringbuffer_write_direct(struct ringbuffer *rbuf, const uint8_t *buf, uint32_t len, uint32_t *actuallen);

extern int32_t ringbuffer_size(struct ringbuffer *rbuf);
#endif // __MDL_VDR_MX_RBUFFER_H__
