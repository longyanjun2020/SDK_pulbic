/* ut_usb_req.h */
#ifndef __UT_USB_REQ_H__
#define __UT_USB_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getUSB_UT(void);
int   noUSB_UT(void);
void  releaseUSB_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_USB_REQ_H__ */
