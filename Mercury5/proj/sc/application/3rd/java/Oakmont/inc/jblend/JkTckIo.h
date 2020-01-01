/**
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTckIo.h
 * Communication for TCK
 */
/**
 * @if DOC_ORGANIZE
 *  @addtogroup TCK_Jsi
 * @else
 *  @addtogroup Module_TCK
 * @endif
 * @{
 */

#ifndef ___SYS_JK_TCKIO_H
#define ___SYS_JK_TCKIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"


/**
 *  Write 1 character to the TCK serial communications device.
 *  @param c
 *        The character to be written. The low 8 bits are valid.
 *  @return
 *        Return one of the following values indicating the processing result.
 *        - 0<br>
 *          if the operation succeeds.
 *        - -1<br>
 *          if writing failed because the device was busy.
 *        - A negative value other than -1<br>
 *          if writing failed because of communication device trouble.
 *        .
 *
 *  Write 1 character (8 bits) to the serial communications device used for the TCK. 
 *
 *  If the communications device is busy (suppressed by flow control, buffer full,
 *  etc.), return -1 indicating the busy state and return immediately to the caller.
 *  <dl>
 *   <dt>Note carefully!</dt>
 *   <dd>
 *    Implement so that no other serial output (#JkTraceLogPutc() log output, etc.)
 *    takes place at the same time.
 *   </dd>
 *  </dl>
 *
 * @see JkTckGetc()
 */
JKSint32 JkTckPutc( JKSint32 c );

/**
 *  Read 1 character from the TCK serial communications device.
 *  @return
 *        Return one of the following values indicating the processing result.
 *        -  A positive value (0 to 255) as the read character<br>
 *           if the read operation succeeds.
 *        - -1 <br>
 *           if there is no character to be read.<br>
 *        - A negative value other than -1<br>
 *           if writing failed because of communication device trouble.
 *        .
 *
 *  Read 1 character (8 bits) from the serial communications device used for the TCK.
 *
 *  If there is no character to be read from the communications device (none in the
 *  receive buffer, etc.) when the read operation is performed, return -1 indicating
 *  no character to be read and return immediately to the caller.
 *
 * @see JkTckPutc()
 */
JKSint32 JkTckGetc( void );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
