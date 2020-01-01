#ifndef __SG_MD5_H__
#define __SG_MD5_H__
typedef unsigned long UINT4;
typedef unsigned char *POINTER;

/* MD5 context. */
typedef struct {
	/* state (ABCD) */   
	/*四个32bits数，用于存放最终计算得到的消息摘要。当消息长度〉512bits时，也用于存放每个512bits的中间结果*/ 
	UINT4 state[4];   
	
	/* number of bits, modulo 2^64 (lsb first) */    
	/*存储原始信息的bits数长度,不包括填充的bits，最长为 2^64 bits，因为2^64是一个64位数的最大值*/
	UINT4 count[2];
	
	/* input buffer */ 
	/*存放输入的信息的缓冲区，512bits*/
	unsigned char buffer[64];  
} SGMD5_CTX;


// 
typedef void (*pMD5Init)(SGMD5_CTX *);
typedef void (*pMD5Update)(SGMD5_CTX *, unsigned char *, unsigned int);
typedef void (*pMD5Final)(unsigned char [16], SGMD5_CTX *);


void SG_MD5Init (SGMD5_CTX *context);
void SG_MD5Update(SGMD5_CTX *context,unsigned char * input,unsigned int  inputLen);
void SG_MD5Final (unsigned char digest[32],SGMD5_CTX *context);

typedef enum _MD5_FUNCLIST
{
	FUNC_MD5Init=3,
	FUNC_MD5Update,
	FUNC_MD5Final
}MD5_FUNCLIST;


#endif
