/*
 * Copyright 2005 Aplix Corporation. All rights reserved.
 */

#ifndef KJAVA_SYS_SERIAL_HEADER
#define KJAVA_SYS_SERIAL_HEADER

/**
 * @file kjava_sys_serial.h
 * TCK Serial KSI
 */

#ifdef __cplusplus
extern "C"{
#endif

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/** 
 * @addtogroup kjava_sys_serial
 * An interface for performing serial communication.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface can be called only when ajms_cfg_setHttpImpl() is called 
 * with #AJSC_HTTP_PROFILE_SERIAL prior to starting processing that triggers 
 * an HTTP/HTTPS processing.
 *
 * @par Include file 
 * \#include kjava_sys_serial.h
 * @{
 */

/** The operation processed successfully. */
#define CONST_KJAVA_SERIAL_OK               0

/** The serial device is now busy or no data available for reading. */
#define CONST_KJAVA_SERIAL_NOT_AVAILABLE    -1

/** The serial device reported an error while processing. */
#define CONST_KJAVA_SERIAL_ERROR            -2


/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/
/**
 * Writes 1 character to the TCK serial communications device.
 * @param c
 *        The character to be written. The low 8 bits are valid.
 * @retval #CONST_KJAVA_SERIAL_OK 
 *         if the operation succeeds.
 * @retval #CONST_KJAVA_SERIAL_NOT_AVAILABLE 
 *         if the write operation fails because the device is busy.
 * @retval #CONST_KJAVA_SERIAL_ERROR
 *         if write operation fails because of a communication device trouble.
 *
 * Write 1 character (8 bits) to the serial communications device used for the TCK.
 *
 * If the communications device is busy (suppressed by flow control, buffer full,
 * etc.), return immediately to the caller passing #CONST_KJAVA_SERIAL_NOT_AVAILABLE as the return value.
 *
 * @par Note carefully!
 * Implement so that no other serial output (kjava_sys_log_printOut() log output, etc.)
 * takes place at the same time.
 *
 * @see kjava_serial_getc()
 */
int kjava_serial_putc( int c );

/** 
 * Reads 1 character from the TCK serial communications device.
 * @retval "A value from 0 to 255 representing the read character" 
 *         if the read operation succeeds.
 * @retval #CONST_KJAVA_SERIAL_NOT_AVAILABLE 
 *         if there is no character to be read.
 * @retval #CONST_KJAVA_SERIAL_ERROR 
 *         if read operation fails because of a communication device trouble.
 *
 * Read 1 character (8 bits) from the serial communications device used for the TCK. 
 *
 * If there is no character to be read from the communications device (none in the
 * receive buffer, etc.) when the read operation is performed, 
 * return immediately to the caller passing #CONST_KJAVA_SERIAL_NOT_AVAILABLE as the return value.
 *
 * @see kjava_serial_putc()
 */
int kjava_serial_getc(void);


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_SYS_SERIAL_HEADER */
