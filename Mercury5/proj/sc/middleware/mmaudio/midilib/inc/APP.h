/***********************************************************
          Copyright (c)2007  FAITH,INC.
					        All rights reserved.
***********************************************************/
#ifndef _APP_H
#define _APP_H

#ifdef __cplusplus
extern "C"{
#endif

#include "DEVICE.h"
#include "DRIVER.h"
#include "synthapi.h"

/**************************************************************/
typedef struct _SUZAKUCONTEXT{

	void							*criticalSection;
	PDEVICE_CONTEXT		deviceContext;
	PDRIVER_CONTEXT		driverContext;
	PSYNTHAPI_CONTEXT	apiContext;

} SUZAKUCONTEXT, *PSUZAKUCONTEXT;
/**************************************************************/

void*
SuzakuCreate(void);

void
SuzakuDestroy( void *Context );

//#ifdef WIN32
#if 0
void
SuzakuFrame( void *Context, short *frame );
#else
#define SuzakuFrame(c, f)   DeviceFrame(((PSUZAKUCONTEXT)(c))->deviceContext, (f))
#endif

unsigned short
SuzakuGetFS( void *Context );

unsigned short
SuzakuGetFrameSample( void *Context );

unsigned short
SuzakuGetChannels( void *Context );

void
SuzakuSendShortMsg( void *Context, unsigned long msg );

void
SuzakuSendLongMsg( void *Context, unsigned char *msg, unsigned long len );

void
SuzakuReset( void *Context );

void
SuzakuStart( void *Context );

void
SuzakuStop( void *Context );


#ifdef __cplusplus
}
#endif

#endif
