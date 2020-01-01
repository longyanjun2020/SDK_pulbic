/*
********************************************************************************
*
*      GSM AMR-NB speech codec   R98   Version 7.6.0   December 12, 2001
*                                R99   Version 3.3.0                
*                                REL-4 Version 4.1.0                
*
********************************************************************************
*
*      File             : typedef.c
*      Purpose          : Basic types.
*
********************************************************************************
*/
#ifndef typedef_h
#define typedef_h "$Id $"


typedef signed char Word8;
typedef unsigned char UWord8;
typedef short Word16;
typedef unsigned short UWord16;
typedef int Word32;
typedef unsigned int UWord32;
typedef int Flag;


#define MMS_IO		// define MMS (RFC3267) format

#define READTABLE	// define build-in input table used

#endif

//#undef WMOPS
#define WMOPS	0

//#define VC_CODE		// define Visual C++ code enable

#define DTX_CODE		// define DTX enable code

#define	FLAT_FOR_LOOP

//#define	CHECK_4_BYTE_ALIGNMENT(addr) {if(((Word32)(addr)) & 0x03){printf("In %s, line=%d, addr=0x%08X(Must be 4 alignment)\r\n", __FILE__, __LINE__, (Word32)addr);}}

