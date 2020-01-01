/***********************************************************
		Synthesizer Core API

						Copyright (c)2007  Faith,Inc.
					        All rights reserved.
***********************************************************/
#ifndef _SYNTHWRAPAPI_H
#define _SYNTHWRAPAPI_H

#include "FaithAPI.h"
#include "app.h"

#define FCONFIG_MAX_FMIDIVOICE		FAITHSYNTH_MAXVOICE
#define FCONFIG_STEREOBUFFER			1
#if FCONFIG_STEREOBUFFER
#define FCONFIG_AUDIOBUF_CHANNELS		2
#else
#define FCONFIG_AUDIOBUF_CHANNELS		1
#endif
#define FCONFIG_MAX_FRAMESAMPLES	128

#ifndef NULL
#define NULL 0
#endif

#if 0
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
#endif

typedef struct _ctx505 {
	void* pLockSynth;
	//void* pLockSeq;
	void* pSynth;
} ctx505;

#ifdef __cplusplus
extern "C"{
#endif

// Initialize the core
// return: 0 = failure
void* fsynth_wrap_init(int max_polyphony, int fs);

// Finalize the core
void fsynth_wrap_exit( void *handle );

// Generate a frame of samples
//#ifdef WIN32
#if 0
void fsynth_wrap_proc( void *handle, short *pbuf );
#else
#define fsynth_wrap_proc(h,p) SuzakuFrame(((ctx505*)(h))->pSynth, (p))
#endif

// Send a MIDI message
// return:  0 = pending (call again)
//					1 = success
int fsynth_wrap_shortmsg( void *handle, unsigned long msg );

// Send a MIDI exclusive message
// return:  0 = pending (call again)
//					1 = success
int fsynth_wrap_longmsg( void *handle, void *excmsg, int len );

// ask ch == drumchannel
int fsynth_wrap_isdrumchannel( void *handle, unsigned char ch );

void fsynth_wrap_proc_core( ctx505 *pw, long *lbuf, short *outbuf );


//#ifdef WIN32
#if 0
void* fsynth_lock_init();
void fsynth_lock_exit( void* pLock);
void fsynth_lock( void* pLock );
void fsynth_unlock( void* pLock );
#else
#define fsynth_lock_init()      0
#define fsynth_lock_exit(p)
#define fsynth_lock(p) (p=0)
#define fsynth_unlock(p) (p=0)
#endif

#ifdef __cplusplus
}
#endif

#endif
