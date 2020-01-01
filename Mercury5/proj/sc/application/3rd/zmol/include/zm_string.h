#ifndef _ZHANGM_STOCK_STRING_H_
#define _ZHANGM_STOCK_STRING_H_

#include "zm_typedef.h"


//#ifdef _DEBUG
//#define _ZHANGM_MEMORY_DEBUG_
//#endif

#ifdef _ZHANGM_MEMORY_DEBUG_
/*
 *	内存分配
 */
zm_extern zm_void* zm_malloc_debug(zm_int nSize, const zm_int8* file, zm_int line);

/*
 *	释放内存
 */
zm_extern zm_void  zm_free_debug(zm_void* pszMemBlock);

/*
 *	报告内存泄漏
 */
zm_extern zm_void zm_memory_debug_report(zm_void);

/**
 * 内存泄漏检测
 */
#define zm_malloc(a) zm_malloc_debug(a, __FILE__, __LINE__)
#define zm_free(a) zm_free_debug(a)
#else
/*
 *	内存分配
 */
zm_extern zm_void* zm_malloc(zm_int nSize);

/*
 *	释放内存
 */
zm_extern zm_void  zm_free(zm_void* pszMemBlock);
#endif
/*
 *	内存拷贝
 */
zm_extern zm_void  zm_memcpy(zm_void* pszDest, const zm_void* pszSrc, zm_int nSize);

/*
 *	设置内存数据
 */
zm_extern zm_void  zm_memset(zm_void* pszDest, zm_int nC, zm_int nSize);

/*
 * 移动内存
 */
zm_extern zm_void zm_memmove(zm_void* pszDest, const zm_void* pszSrc, zm_int nSize);

/*
 *	内存比较
 */
zm_extern zm_int   zm_memcmp(const zm_void* pBuf1, const zm_void* pBuf2, zm_int nSize);

/*
 *	宽字符串长度
 */
zm_extern zm_int   zm_wstrlen(const zm_int8* pszUniStr);

/*
 *	字符串长度
 */
zm_extern zm_int   zm_strlen(const zm_int8* pszString);

/*
 *	字符串拷贝
 */
zm_extern zm_int8* zm_strcpy(zm_int8* pDest, const zm_int8* pstrSource);

/*
 *	字符串比较
 */
zm_extern zm_int   zm_strcmp(zm_int8*pStr1, zm_int8*pStr2);

/*
 *	连接字符串
 */
zm_extern zm_int8* zm_strcat(zm_int8* pDest, const zm_int8* pstrSource);

/*
 *	子串匹配
 */
zm_extern zm_int8* zm_strstr(const zm_int8* pString, const zm_int8* pFind);

/*
 *	文本数据转换到 long
 */
zm_extern zm_int32 zm_atol(const zm_int8* pString);

/*
 *	lvalue 转换到文本 pBuffer 中
 */
zm_extern zm_void  zm_ltoa(zm_int8* pBuffer, zm_int32 lvalue);

/*
 *	将文本pString中的浮点数转换成 zm_real64 类型
 */
zm_extern zm_real64 zm_atof(const zm_int8* pString);

/*
 *	fvalue 浮点数转换到文本 pBuffer 中, nDecimal 位保留的小数位数
 */
zm_extern zm_void zm_ftoa(zm_int8* pBuffer, zm_real64 fvalue, zm_int nDecimal);

/*
 *	格式化字符串
 */
zm_extern zm_void zm_sprintf_int(zm_int8* pBuffer, const zm_int8* pFormat, zm_int lvalue);
/*
 *	格式化字符串
 */
zm_extern zm_void zm_sprintf_string(zm_int8* pBuffer, const zm_int8*  pFormat, const zm_int8* str);

/**
  * gb2312 转 ucs2
  */
zm_extern zm_void zm_gb_to_ucs2(zm_int8 * src, zm_int8 *dest);

/**
  * ucs2 转 gb2312
  */
zm_extern zm_void zm_ucs2_to_gb(zm_int8 * src, zm_int8 *dest, zm_int  isBigEn);

#endif/*_ZHANGM_STOCK_STRING_H_*/
