#ifndef __DES4C_H__
#define __DES4C_H__
#include "encryption.h"

/*!
* @brief		使用DES加密
* @param Out	输出缓冲区
* @param In		输入缓冲区
* @param inlen	输入缓冲区长度
* @param Key	密钥(64bit) 每8位做奇偶校验
* @param keylen	密钥长度
* @param Type	运行类型(ENCRYPT(0)加密，DECRYPT(1)解密)
* @return		成功返回TRUE，否则返回FALSE
* @note			Out 长度 >= ((inlen+7)/8)*8,即比inlen大的且是8的倍数的最小正整数
* @note			当keylen>8时自动使用3次DES加/解密,否则使用标准DES加/解密.超过16字节后只取前16字节
* @sa			OPERATION
*/
BIT8 Des_Ex(BIT8 *Out,BIT8 *In,BIT64 inlen,const BIT8 *Key,BIT32 keylen,OPERATION Type);

#endif