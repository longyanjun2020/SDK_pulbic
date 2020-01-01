#ifndef __MD5__H
#define __MD5__H

typedef unsigned int u32;
typedef unsigned char u8;

struct __MD5_Context {
	u32 buf[4];
	u32 bits[2];
	u8 in[64];
};

void __MD5_Init(struct __MD5_Context *context);
void __MD5_Update(struct __MD5_Context *context, unsigned char const *buf,
	       unsigned len);
void __MD5_Final(unsigned char digest[16], struct __MD5_Context *context);
void __MD5_Transform(u32 buf[4], u32 const in[16]);

typedef struct __MD5_Context __MD5__CTX;

#endif /* __MD5__H */
