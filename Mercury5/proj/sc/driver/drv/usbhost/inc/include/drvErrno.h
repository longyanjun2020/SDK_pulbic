//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

#ifndef _ERRNO_H
#define _ERRNO_H

#define  MS_ERR_2BIG      7    /* Argument too long */
#define  MS_ERR_IDRM      43   /* Identifier removed */
#define  MS_ERR_RECEIVE   63   /* Communication error on receive */
#define  MS_ERR_NOLINK    67   /* Link has been severed */
#define  MS_ERR_SEND      70   /* Communication error on send */
#define  MS_ERR_PROTOCAL  71   /* Protocol error */
#define  MS_ERR_OVERFLOW  75   /* Data overflow for defined data type */
#define  MS_ERR_REMOTEIO  121  /* Remote I/O error */

/* RTK */
#define ENOERR           0     /* No error */
#define EPERM            1     /* Not permitted */
#define ENOENT           2     /* No such entity */
#define ESRCH            3     /* No such process */
#define EINTR            4     /* Operation interrupted */
#define EIO              5     /* I/O error */
#define EBADF            9     /* Bad file handle */
#define EAGAIN           11    /* Try again later */
#define EWOULDBLOCK      EAGAIN
#define ENOMEM           12    /* Out of memory */
#define EBUSY            16    /* Resource busy */
#define EXDEV            18    /* Cross-device link */
#define ENODEV           19    /* No such device */
#define ENOTDIR          20    /* Not a directory */
#define EISDIR           21    /* Is a directory */
#define EINVAL           22    /* Invalid argument */
#define ENFILE           23    /* Too many open files in system */
#define EMFILE           24    /* Too many open files */
#define EFBIG            27    /* File too large */
#define ENOSPC           28    /* No space left on device */
#define ESPIPE           29    /* Illegal seek */
#define EROFS            30    /* Read-only file system */
#define EDOM             33    /* Argument to math function outside valid */
                               /* domain */
#define ERANGE           34    /* Math result cannot be represented */
#define EDEADLK          35    /* Resource deadlock would occur */
#define EDEADLOCK        EDEADLK
#define ENOSYS           38    /* Function not implemented */
#define ENOMSG           42    /* No message of desired type */
#define ENAMETOOLONG     60    /* File name too long */
#define ENOTEMPTY        66    /* Directory not empty */
#define EPROTO           71    /* Protocol error */
#define ENOTSUP          95    /* Not supported error */
#define EEOF             200   /* End of file reached */
#define ENOSUPP          201   /* Operation not supported */
#define EDEVNOSUPP       202   /* Device does not support this operation */

/* Additional errors used by networking */
#define ENXIO            300   /* Device not configured */
#define EACCES           301   /* Permission denied */
#define EEXIST           302   /* File exists */
#define ENOTTY           303   /* Inappropriate ioctl for device */
#define EPIPE            304   /* Broken pipe */

/* non-blocking and interrupt i/o */
#define EINPROGRESS      310   /* Operation now in progress */
#define EALREADY         311   /* Operation already in progress */

/* ipc/network software -- argument errors */
#define ENOTSOCK         320   /* Socket operation on non-socket */
#define EDESTADDRREQ     321   /* Destination address required */
#define EMSGSIZE         322   /* Message too long */
#define EPROTOTYPE       323   /* Protocol wrong type for socket */
#define ENOPROTOOPT      324   /* Protocol not available */
#define EPROTONOSUPPORT  325   /* Protocol not supported */
#define ESOCKTNOSUPPORT  326   /* Socket type not supported */
#define EOPNOTSUPP       327   /* Operation not supported */
#define EPFNOSUPPORT     328   /* Protocol family not supported */
#define EAFNOSUPPORT     329   /* Address family not supported by */
                               /* protocol family */
#define EADDRINUSE       330   /* Address already in use */
#define EADDRNOTAVAIL    331   /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define ENETDOWN         350   /* Network is down */
#define ENETUNREACH      351   /* Network is unreachable */
#define ENETRESET        352   /* Network dropped connection on reset */
#define ECONNABORTED     353   /* Software caused connection abort */
#define ECONNRESET       354   /* Connection reset by peer */
#define ENOBUFS          355   /* No buffer space available */
#define EISCONN          356   /* Socket is already connected */
#define ENOTCONN         357   /* Socket is not connected */
#define ESHUTDOWN        358   /* Can't send after socket shutdown */
#define ETOOMANYREFS     359   /* Too many references: can't splice */
#define ETIMEDOUT        360   /* Operation timed out */
#define ECONNREFUSED     361   /* Connection refused */

#define EHOSTDOWN        364   /* Host is down */
#define EHOSTUNREACH     365   /* No route to host */
/* end of RTK */

#endif
