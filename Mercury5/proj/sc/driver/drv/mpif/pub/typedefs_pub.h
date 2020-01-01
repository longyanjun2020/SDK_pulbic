/*.===******************  MODULE   : typedefs.h  **************************
*
* PROJECT: GPS Baseband Receiver
*
*          Copyright 2003, AqTrack Technologies, Inc.
*
=========================================================================
*
* ABSTRACT : General purpose types definitions
*
*            $Id: typedefs.h,v 1.10 2003/11/20 14:57:12 go Exp $
*
*******************************************************************===.*/
#ifndef __typedefs_pub_h
#define __typedefs_pub_h

#ifndef BOOL
//typedef unsigned char BOOL;
#define BOOL unsigned char
#endif

/*- Basic Data Types: --------------------------------------------------------*/
#ifndef BOOLEAN
typedef unsigned char      BOOLEAN;   /* range 0..255                          */
#endif
typedef unsigned char      UINT8;     /* range 0..255                          */
typedef   signed char      INT8;      /* range -128..+127                      */
typedef unsigned char      BIN8;      /* range 0..255                          */
typedef unsigned short     BIN16;     /* range 0..65535                        */
typedef unsigned long int  BIN24;     /* range 0..2^32-1                       */
typedef unsigned long int  BIN32;     /* range 0..2^32-1                       */
typedef unsigned short     UINT16;    /* range 0..65535                        */
typedef   signed short     INT16;     /* range -2^15..2^15-1                   */
typedef   signed long int  INT24;     /* range -2^23..2^23-1                   */
typedef unsigned long int  UINT24;    /* range 0..2^32-1                       */
typedef unsigned int       UINT32;    /* range 0..2^32-1                       */
typedef signed int         INT32;     /* range -2^31..2^31-1                   */
typedef long long          INT64;     /* range -2^63..2^63-1                   */
typedef unsigned long long UINT64;    /* range 0..2^64-1                       */
typedef          float     FP;        /* range -3.4*10^38..3.4*10^38           */
typedef          double    EFP;       /* range -3.4*10^4932..3.4*10^4932       */
#ifndef WINCE_PLATFORM
#define HANDLE UINT32
#define DWORD unsigned long
#define LPVOID void *
#endif
#if 1//defined(WINCE_PLATFORM) || defined(ECOS_PLATFORM)
#define MSTAR_SUCCESS 0
#define MSTAR_FALSE     1
#define uHAL_TRUE 1
#define uHAL_FALSE 0
#ifndef UINT
#define UINT unsigned int
#endif
typedef int ME_STATUS;

typedef UINT32 MSTAR_STATUS;
#define MSTAR_HANDLE HANDLE
#endif

typedef void*             POINTER;
#ifndef NULL
    #define NULL    ((void*)0)
#endif

#ifdef ECOS_PLATFORM
#ifndef SEEK_SET
	#define SEEK_SET 0
	#define SEEK_CUR 1
	#define SEEK_END 2
#endif //SEEK_SET
#endif //ECOS_PLATFORM

#ifndef TRUE
#define TRUE    (1==1)
#endif
#ifndef FALSE
#define FALSE   (!TRUE)
#endif


#if 0
/*- Time Manager Data Types: -------------------------------------------------*/
typedef struct
{
    UINT32 sec;       /* Number of the  seconds  */
    UINT32 ns;        /* Fractional part of the second in ns */
} TIME_PAR;

typedef enum
{
    NOT_INITIALIZED,  /*Time is NOT synchronized*/
    RTC_BASED,        /*Time is NOT synchronized*/
    PVT_INIT_BASED,   /*Time is NOT synchronized*/
    EXT_EV_BASED,     /*Time is NOT synchronized*/
    SV_BASED,         /*Time is synchronized    */
    PPS_BASED,        /*Time is synchronized    */
    TMG_BASED         /*Time is synchronized    */
} TIME_STATUS;

typedef struct
{                                 /* GPStime = internal + reference + integrated corr */
    UINT32      time_pckts;       /* internal time in packets */
    TIME_PAR    internal;         /* internal time            */
    TIME_PAR    reference;        /* reference time           */
    TIME_PAR    integrated_corr;  /* integrated correction    */
    TIME_STATUS tstat;            /* status of internal time  */
}  RECEIVER_TIME;

typedef struct
{
    UINT16   gwk;   /* Number of the weeks since GPS time origin */
    UINT32   gsec;  /* Number of the seconds */
    UINT32   gfsec; /* Fractional part of the second, nsec */
} GPS_TIME_PAR;

/*- Satellite Visibility Data Types: -----------------------------------------*/
typedef struct
{
    EFP         bias;           /* Oscillator bias, meters              */
    FP          bias_uncert;    /* Oscillator bias uncertainty, meters  */
    FP          drift;          /* Oscillator drift,      meters/second */
    FP          uncert;         /* Uncertainty of osc_drift, meters/sec */
    TIME_PAR    osc_ref_time;   /* Reference time for osc data          */
    UINT8       validity;       /* 0x1 - drift is valid, 0x2 - bias is valid */

	////==============Added by Claire==============////
	//Claire,20080821
	//#ifdef ACCURATE_RTC
	#if 1
    	enum
    	{
    		OSC_UNUSED,    /* means the field shouldn't be used (just for compatibility) */
    		OSC_RTC_BASED,
    		OSC_PVT_BASED,
    		OSC_EXT_BASED,
    		OSC_TMG_BASED
    	} init_source;/* indicate data source and affects to uncert model */
	#endif
	////============End of Added by Claire===========////

} OSC_DRIFT;
#define OSC_BIAS_VALID  0x01
#define OSC_DRIFT_VALID 0x02
#endif

#endif /* __typedefs_pub_h */

