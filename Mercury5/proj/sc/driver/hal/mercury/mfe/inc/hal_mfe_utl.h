
#ifndef _MFE_UTL_H_
#define _MFE_UTL_H_

#ifndef _MAX
#define _MAX(a,b)   ((a)>(b)?(a):(b))
#endif
#ifndef _MIN
#define _MIN(a,b)   ((a)<(b)?(a):(b))
#endif

#if defined(__I_SW__)
#include "sys_sys_math64.h"
#define DIV_S64(n,d)    div64_s64((n), (d))
#else
#include <linux/math64.h>
#define DIV_S64(n,d)    div64_s64((n), (d))
#endif

typedef struct iir_t
{
#define KAPA_ONE        1024
    int i_kapa;
    int i_data;
} iir_t;

inline static int iirInit(iir_t* iir, int data, int kapa)
{
    iir->i_kapa = kapa;
    iir->i_data = data;
    return iir->i_data;
}
inline static int iirPush(iir_t* iir, int data)
{
    int64 calc = (int64)data * iir->i_kapa;
    data = !iir->i_data ? data:iir->i_data;
    calc += (int64)data * (KAPA_ONE-iir->i_kapa);
    iir->i_data = (int)DIV_S64(calc,KAPA_ONE);
    return iir->i_data;
}
inline static int iirData(iir_t* iir)
{
    return iir->i_data;
}

typedef struct acc_t
{
#define ACC_SIZE    (1<<8)
#define ACC_MASK    (ACC_SIZE-1)
    int i_curr;
    int i_data[ACC_SIZE];
} acc_t;

inline static int accInit(acc_t* acc, int data)
{
    int i = ACC_SIZE;
    while (i-- > 0)
        acc->i_data[i] = -i*data;
    acc->i_curr = 0;
    return data;
}
inline static int accPush(acc_t* acc, int data)
{
    int v = data + acc->i_data[ACC_MASK&(acc->i_curr)];
    acc->i_curr--;
    acc->i_data[ACC_MASK&(acc->i_curr)] = v;
    return data;
}
inline static int accCalc(acc_t* acc, int size)
{
    int lead = acc->i_data[ACC_MASK&(acc->i_curr)];
    int tail = acc->i_data[ACC_MASK&(acc->i_curr+size)];
    return (lead-tail);
}

#endif //_MFE_UTL_H_
