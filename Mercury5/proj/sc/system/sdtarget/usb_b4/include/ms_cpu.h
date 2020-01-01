#ifndef _MS_CPU_H_
#define _MS_CPU_H_
#define _ARM_CPU_

#ifdef _ARM_CPU_
#define DRC_IN8(r)       *((U8 volatile *)(r))
#define DRC_OUT8(r,d)    (*((U8 volatile*)(r)) = (U8)d)

#define DRC_IN16(r)       *((U16 volatile*)(r))
#define DRC_OUT16(r,d)    (*((U16 volatile*)(r)) = (U16)d)
#else
#define DRC_IN8(r)       *((U8 volatile *)(r))
#define DRC_OUT8(r,d)    (*((U8 volatile*)(r)) = (U8 volatile)d)

#define DRC_IN16(r)       *((U16 volatile*)(r))
#define DRC_OUT16(r,d)    (*((U16 volatile*)(r)) = (U16 volatile)d)
#endif

#define FIFO_ADDRESS(e)  (otgRegAddress + (e<<3) + M_FIFO_EP0)
#define FIFO_DATA_PORT  (otgRegAddress+M_REG_FIFO_DATA_PORT)
#ifdef BIG_ENDIAN
#define SWOP(X) ((X) = (((X)<<8)+((X)>>8)))
#define SWAP4(X) ((X) = ((X)<<24) + ((X)>>24) + (((X)>>8)&0x0000FF00) + (((X)<<8)&0x00FF0000) )
#else
#define SWAP4(X) (X = X)
#define SWOP(X)  (X = X)
#endif
#undef _ARM_CPU_
#endif  /* _MS_CPU_H_ */
