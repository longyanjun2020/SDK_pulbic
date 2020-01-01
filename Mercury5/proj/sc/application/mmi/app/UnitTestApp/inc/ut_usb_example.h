/* ut_usb_example.h */
#ifndef __UT_USB_EXAMPLE_H__
#define __UT_USB_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetUsb_Example(void);
s32  NumUsb_Example(void);
void  ReleaseUsb_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_USB_EXAMPLE_H__ */
