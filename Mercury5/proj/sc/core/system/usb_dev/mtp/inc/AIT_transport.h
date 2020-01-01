
/****************************************************************************
 *
 * @module      transport.h
 *
 * @created     11-Februrary-2004
 *
 * @abstract    Interface for the USB transport module
 *
 * @copyright   (C) COPYRIGHT Microsoft Corp, 2005
 *
 ****************************************************************************/


/**
 * This file contains the interface description for the USB transport module.
 * All USB drivers used in conjunction with the MTP stack should utilize this
 * interface.
 */

#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

//#include "datatype.h"
#include "includes_fw.h"

/**
 * USB_STATE
 * 
 * A generic state structure that indicates if the USB module has been
 * initialized.  It also contains a pointer to any state structures that the
 * USB module may need for internal use.
 */
typedef struct usb_struct
{
  MMP_BOOL bInitialized;
  void *pVendorState;
} USB_STATE;


/**
 * USB_TRANSFER
 *
 * An enumerated type used to indicate the beginning, end, or middle of a
 * transfer.  Note that all 3 enumerated values may be logically or'd in order
 * to indicate an isolated transfer.
 */
typedef enum usb_transfer
{
  XFER_START = 1,
  XFER_MIDDLE = 2,
  XFER_END = 4
} USB_TRANSFER;

/**
 * usb_initialize
 *
 * This function initializes the USB module to a known initial state.  This
 * function should normally be called once during the set up of the device.
 *
 * Return Value: This function returns a 0 if successful.  Otherwise, it
 * returns a non-zero value indicating an error.  It is left to the USB module
 * developer to determine if the non-zero values have any meaning besides
 * error.
 */
MMP_USHORT usb_initialize(USB_STATE *pState);


/**
 * usb_reset
 * 
 * This funciton resets the USB module to a known state.  This function should
 * be called during run-time if an unrecoverable error occurs and the USB needs
 * to be reset to a known state.
 *
 * Return Value: This funciton returns a 0 if successful.  Otherwise, it
 * returns a non-zero value indicating an error.
 */
MMP_USHORT usb_reset(USB_STATE *pState);


/**
 * usb_senddata
 *
 * This functions sends data out through the USB module.  If the data needs to
 * be send in multiple chunks, the "state" parameter should be used to indicate
 * which stage of the transfer you are currently in.  For example, a transfer
 * that consists of 3 chunks would involve the following calls:
 *
 * usb_senddata(pState, pBuffer, size, pCount, XFER_START);
 *   [Some code to refresh the buffer here]
 * usb_senddata(pState, pBuffer, size, pCount, XFER_MIDDLE);
 *   [Some code to refresh the buffer here]
 * usb_senddata(pState, pBuffer, size, pCount, XFER_END);
 *
 * For isolated transfers, the call would look like:
 *
 * usb_senddata(pState, pBuffer, size, pCount, XFER_START|XFER_MIDDLE|XFER_END);
 *
 * Return Value: This function returns a 0 if successful.  Otherwise, it
 * returns a non-zero value indicating an error.
 */
MMP_USHORT usb_senddata(USB_STATE *pState, MMP_UBYTE *pBuffer, MMP_ULONG size, 
            MMP_ULONG *pCount, USB_TRANSFER state);

/**
 * usb_checkcommand
 *
 * Checks to see if a USB command is available.  This is a deprecated interface
 * designed for polling implementations.
 *
 * Return Value: This function returns a 1 if a command is available.
 * Otherwise, it returns 0.
 */
MMP_USHORT usb_checkcommand(USB_STATE *pState);


/**
 * usb_receivedata
 *
 * This function receives data through the USB module.  The USB module should
 * be designed so that it can pass chunks of received data to the calling
 * function rather than expecting to pass all the data at once.  The usage of
 * the "state" parameter is similar to the usb_senddata function.  However, in
 * this instance, the USB module sets the flags indicating if there is more
 * data to be processed.  
 *
 * Return Value: This function returns a 0 if successful.  Otherwise, it
 * returns a non-zero value indicating an error.
 */
MMP_USHORT usb_receivedata(USB_STATE *pState, MMP_UBYTE *pBuffer, MMP_ULONG size, 
            MMP_ULONG *pCount, USB_TRANSFER *state);


/**
 * usb_stall
 *
 * This function stalls the USB device while waiting for a response from the
 * host.
 *
 * Return Value: There is no return value for this function.
 */
void usb_stall(USB_STATE *pState);


/**
 * usb_unstall
 *
 * This function unstalls the USB device.
 *
 * Return Value: There is no return value for this function.
 */
void usb_unstall(USB_STATE *pState);


/**
 * usb_disconnect
 *
 * This function disconnects the device from the USB bus.
 *
 * Return Value: This function returns a 0 if successful.  Otherwise, it
 * returns a non-zero value indicating an error.
 */
MMP_USHORT usb_disconnect(USB_STATE *pState);


/**
 * usb_connect
 * 
 * This funciton connects the device to the USB host.
 *
 * Return Value: This function returns a 0 if successful.  Otherwise, it
 * returns a non-zero value indicating an error.
 */
MMP_USHORT usb_connect(USB_STATE *pState);

/**
 * usb_connect
 * 
 * This function determines whether the USB is connected.
 *
 * Return Value: This function returns a 0 if connected.  Otherwise, it
 * returns a non-zero value indicating an error.
 */
MMP_USHORT usb_isconnected(USB_STATE *pState);


/**
 * usb_registerservice
 *
 * This function registers a service with the USB module indicating which
 * commands should be passed to the MTP stack.  The USB modules calls the
 * callback function passed when the indicated command arrives.
 *
 * Return Value: This function returns a 0 if successful.  Otherwise, it
 * returns a non-zero value indicating an error.
 */
MMP_USHORT usb_registerservice(USB_STATE *pState, MMP_UBYTE *pCmdList, MMP_USHORT listSize,
            void (*service)(MMP_UBYTE *pBuffer, MMP_ULONG size));

/**
 * usb_sendevent
 *
 * This function sends a MTP event using the endpoint interrupt.
 *
 * Return Value: This function returns a 0 if successful.  Otherwise, it
 * returns a non-zero value indicating an error.
 */
MMP_USHORT usb_sendevent(USB_STATE *pState, MMP_UBYTE *pBuffer, MMP_ULONG size, 
            MMP_USHORT *count);


#endif /* _TRANSPORT_H_ */

