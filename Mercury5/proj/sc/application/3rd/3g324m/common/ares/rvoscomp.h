/***********************************************************************
Filename   : rvoscomp.c
Description: Complementary OS functions
************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/

#if (RV_OS_TYPE == RV_OS_TYPE_WIN32)

#define NEED_WIN32_WRITEV

#define IOVEC           WSABUF
#define iov_base        buf
#define iov_len         len

int writev(int s, IOVEC *iov, int iovcnt);

#endif


#if (RV_OS_TYPE == RV_OS_TYPE_SYMBIAN)   || (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS) || \
    (RV_OS_TYPE == RV_OS_TYPE_MOPI)      || (RV_OS_TYPE == RV_OS_TYPE_OSE)     || \
    (RV_OS_TYPE == RV_OS_TYPE_INTEGRITY) || (RV_OS_TYPE == RV_OS_TYPE_PSOS)  || \
    (RV_OS_TYPE == RV_OS_TYPE_WINCE)

#define NEED_MANUAL_WRITEV

#endif

#if (RV_OS_TYPE == RV_OS_TYPE_WIN32)
/* need to be defined only for Studio 6, temporary define always */
#define NEED_MANUAL_WRITEV
#endif


#if (!defined(NEED_WIN32_WRITEV) && !defined(NEED_MANUAL_WRITEV))
#define IOVEC struct iovec
#endif


