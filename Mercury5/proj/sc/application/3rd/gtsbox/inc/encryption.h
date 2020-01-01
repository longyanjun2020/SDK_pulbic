#ifndef __ENCRYPTION_H__
#define __ENCRYPTION_H__
#include "xlite.h"
#include "gtsbox.h"
#define TRUE	1
#define FALSE	0

#define DES_LENGTH(len) ((((len)+7)<<3)>>3)
#define HOST_TO_BASE64_LENGTH(len) (((len<<2)/3)+1)
#define BASE64_TO_HOST_LENGTH(len) (((len*3)>>2)+1)

typedef xl_char BIT8;
typedef xl_int32  BIT32;
typedef xl_int64  BIT64;

typedef enum
{
	// º”√‹
	ENCRYPT = 0x0,
	// Ω‚√‹
	DECRYPT
}OPERATION;

BIT8* gtsbox_Encryption(BIT8* In,BIT32 inlen,BIT8* Key,BIT32 keylen,OPERATION type);

#endif