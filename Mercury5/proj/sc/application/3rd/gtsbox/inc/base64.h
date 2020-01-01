#ifndef __BASE64_H__
#define __BASE64_H__
#include "encryption.h"

BIT8* encode(BIT8 *src,BIT32 srclen);

BIT8* decode(BIT8 *src);

#endif