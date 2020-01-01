#if ! defined( DEVICE_DEVICE_h )
#define DEVICE_DEVICE_h
/*****************************************************************************/
/* DEVICE_DEVICE_h                                                           */
/* DEVICE.h                                                                  */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/
#define DEVICE_SAMPLESPERSEC    32000
#define DEVICE_CHANNELS         2
#define DEVICE_SAMPLESPERFRAME  128//256//128

typedef struct _DEVICE_CONTEXT {

    void *      synthContext;       /* SYNTH_CONTEXT synthContext[ 1 ] */
    void *      waveContext;        /* WAVE_CONTEXT waveContext[ 1 ] */
    void *      textContext;        /* TEXT_CONTEXT textContext[ 1 ] */
    void *      pictContext;        /* PICT_CONTEXT pictContext[ 1 ] */
    void *      ledContext;         /* LED_CONTEXT  ledContext[ 1 ] */
    void *      vibContext;         /* VIB_CONTEXT  vibContext[ 1 ] */
	void *		adpcmContext;
    
    long *		sampleFrame;

} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

/*****************************************************************************/

extern
unsigned long
DeviceSamplePerSec(
    void
);

extern
unsigned char
DeviceChannels(
    void
);

extern
unsigned char
DevicePictLayers(
    void
);

extern
unsigned short
DeviceSamplePerFrame(
    void
);

extern
PDEVICE_CONTEXT
DeviceCreate(
		void
);

extern
void
DeviceDestroy(
    PDEVICE_CONTEXT C
);

extern
void
DeviceFrame(
    PDEVICE_CONTEXT C,
    short *          frame
);

/*****************************************************************************/
#endif  /* ! defined( DEVICE_DEVICE_h ) */
