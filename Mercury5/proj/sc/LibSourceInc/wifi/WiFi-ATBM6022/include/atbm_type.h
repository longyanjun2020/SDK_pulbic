#ifndef _ATBM_API_TYPE_H_
#define _ATBM_API_TYPE_H_

//#include <inttypes.h>
//#define jiffies 1000
#define ATBM_ALIGN(a,b)			(((a) + ((b) - 1)) & (~((b)-1)))
/*
;*****************************************************************************************************
;* 描	 述 : 定义系统的数据类型。
;*****************************************************************************************************
;*/
typedef unsigned char ATBM_BOOL;
typedef unsigned char uint8; /* Unsigned  8 bit quantity							*/
typedef signed char int8; /* Signed    8 bit quantity							 */
typedef unsigned short uint16; /* Unsigned 16 bit quantity							  */
typedef signed short int16; /* Signed	16 bit quantity 						   */
typedef unsigned int uint32; /* Unsigned 32 bit quantity							*/
typedef signed int int32; /* Signed   32 bit quantity							 */
typedef float fp32; /* Single precision floating point					   */


typedef unsigned char uint8_t; /* Unsigned  8 bit quantity							*/
typedef signed char int8_t; /* Signed    8 bit quantity							 */
typedef unsigned short uint16_t; /* Unsigned 16 bit quantity							  */
typedef signed short int16_t; /* Signed	16 bit quantity 						   */
typedef unsigned int uint32_t; /* Unsigned 32 bit quantity							*/
typedef signed int int32_t; /* Signed   32 bit quantity							 */


typedef uint32_t   OS_CPU_SR;              /* Define size of CPU status register (PSR = 32 bits) */


typedef uint32_t u32;
typedef uint16 u16;
typedef uint8 u8;
typedef int8 s8;

//typedef uint32_t U32;
//typedef uint16 U16;
typedef uint8 U8;





typedef unsigned short __le16;
typedef unsigned int __le32;
typedef unsigned long long __le64;
typedef unsigned short __be16;
typedef unsigned int __be32;
typedef unsigned short __u16;
typedef unsigned long long u64; //mark 无符号64位


#define  atbm_size_t  int 



//#define ATBM_BOOL	unsigned char
#ifndef FALSE
#define FALSE	0
#define TRUE	1
#endif /*FALSE*/

#define BIT(x)	(1 << (x))
#define NETDEV_ALIGN		32
#define ETHTOOL_BUSINFO_LEN 32

#define false 0
#define true  1

#ifndef min
#define min(_a, _b) 	(((_a) < (_b)) ? (_a) : (_b))
#endif

#ifndef max
#define max(_a, _b) 	(((_a) > (_b)) ? (_a) : (_b))
#endif

#ifndef NULL
#define NULL	((void *)0)
#endif
#define likely(a) (a)
#define unlikely(a) (a)

#define atbm_cpu_to_le16(v16) (v16)
#define atbm_cpu_to_le32(v32) (v32)
#define atbm_cpu_to_le64(v64) (v64)
#define atbm_le16_to_cpu(v16) (v16)
#define atbm_le32_to_cpu(v32) (v32)
#define atbm_le64_to_cpu(v64) (v64)

#define __atbm_cpu_to_le16(v16) (v16)
#define __atbm_cpu_to_le64(v64) (v64)
#define __atbm_le16_to_cpu(v16) (v16)
#define __atbm_le32_to_cpu(v32) (v32)

#define atbm_cpu_to_be16(a) atbm_htons(a)
#define atbm_cpu_to_be32(a) atbm_htonl(a)
#define atbm_be16_to_cpu(a) atbm_ntohs(a)
#define atbm_be32_to_cpu(a) atbm_ntohl(a)


#endif /*_API_TYPE_H_*/
