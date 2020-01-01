#ifndef __MD5__H
#define __MD5__H

typedef unsigned int u32;
typedef unsigned char u8;

struct MD5_Context {
	u32 buf[4];
	u32 bits[2];
	u8 in[64];
};

void MD5Init(struct MD5_Context *context);
void MD5Update(struct MD5_Context *context, unsigned char const *buf,
	       unsigned len);
void MD5Final(unsigned char digest[16], struct MD5_Context *context);
void MD5Transform(u32 buf[4], u32 const in[16]);

typedef struct MD5_Context MD5_CTX;

#endif /* __MD5__H */
