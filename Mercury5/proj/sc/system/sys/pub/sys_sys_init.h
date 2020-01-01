/******************************************************************/
/*  File    : sys_sys_init.ho                                                                                       */
/*--------------------------------------------------------------- */
/*  Scope   :  INIT exports                                                                            */
/*                                                                                                               */
/*****************************************************************/

#ifndef __SYS_SYS_INIT_H__
#define __SYS_SYS_INIT_H__

#include "vm_types.ht"


/*********************************************************/
/*                    WARNING  !!!!!                     */
/* if __DUAL_POOL__ flag is activated, pool dimensions   */
/* must be updated.                                      */
/*********************************************************/


/* ================== TARGET =========================== */

#if defined(__TARGET__) || defined(__EMI_POOL_PROTECT__)
#define REDUCE_POOL_SIZE
#endif

#ifndef REDUCE_POOL_SIZE
#define GPRS_NB_CLUST_POOL0        1600 // For EMMI
#define GPRS_SIZE_CLUST_POOL0      24 //MST_CR_6149: for optimal memory usage

#define GPRS_NB_CLUST_POOL1        2500
#define GPRS_SIZE_CLUST_POOL1      84

#define GPRS_NB_CLUST_POOL2        800
#define GPRS_SIZE_CLUST_POOL2      150

#define GPRS_NB_CLUST_POOL3        450
#define GPRS_SIZE_CLUST_POOL3      292

#define GPRS_NB_CLUST_POOL4        100
#ifdef __TARGET__
#define GPRS_SIZE_CLUST_POOL4      602
#else
#define GPRS_SIZE_CLUST_POOL4      768
#endif

// Add Big size pool for pool tuning
#define GPRS_NB_CLUST_POOL5        50
#define GPRS_SIZE_CLUST_POOL5      1100

#define EMI_POOL_GUARD_LEN	4

#else //REDUCE_POOL_SIZE

#define GPRS_NB_CLUST_POOL0        800
#define GPRS_SIZE_CLUST_POOL0      12

#define GPRS_NB_CLUST_POOL1        2000
#define GPRS_SIZE_CLUST_POOL1      44

#define GPRS_NB_CLUST_POOL2        500
#define GPRS_SIZE_CLUST_POOL2      108

#define GPRS_NB_CLUST_POOL3        500
#define GPRS_SIZE_CLUST_POOL3      236

#define GPRS_NB_CLUST_POOL4        80
#define GPRS_SIZE_CLUST_POOL4      492

#define GPRS_NB_CLUST_POOL5        20
#define GPRS_SIZE_CLUST_POOL5      1004

#define EMI_POOL_GUARD_LEN	4

#define EMI_POO_GUARD	0xCD

#endif //REDUCE_POOL_SIZE

#define CUS_COARSE_TIMER_INIT_NB   32


/* ========================= Tasks descriptor ======================== */

typedef struct
{
  char *Name;
  void	(* EntryPoint)(void);
  u8	Priority;
  u16	StackSize;
  u32   TraceElement;
#if defined(__TIME_SLICE_SCHEDULE__)
  u32   TimeSliceMax;
  u32   TimeSliceLeft;
#endif
} cus_InitTask_t;

extern u8 cus_NbTask;
extern const cus_InitTask_t cus_InitTask [];


/* ======================= Mailboxes descriptor ====================== */

typedef struct
{
 char Name[7];
 u8   Number;
} cus_InitMbx_t;

extern const u8 cus_NbMbx;
extern const cus_InitMbx_t cus_InitMbx [];


/* ======================= Semaphores descriptor ====================== */

typedef u8 cus_InitSem_t;

extern const u16 cus_NbSem;
extern const cus_InitSem_t cus_InitSem [];


/* ========================== Pool descriptor ========================= */

typedef struct
{
 u16 NbOfCluster;
 u16 ClusterLength;
 u8 NeedProtect;
} cus_InitPool_t;

extern const u8 cus_NbPool;
extern const cus_InitPool_t cus_InitPool [];

#ifdef __RTK_NEW_HEAP_MANAG__
/* ========================== Free List descriptor ========================= */

typedef struct
{
    u16 BlockLength;
} cus_InitFreeList_t;

extern const u8 cus_NbFreeList;
extern const cus_InitFreeList_t cus_InitFreeList[];
#endif //__RTK_NEW_HEAP_MANAG__

/* ========================== Misc descriptor ========================= */
#ifndef __cplusplus
extern const u16 cus_NbEnv;
extern const u16 cus_NbTimer;
extern const u16 cus_NbCoarseTimer;
extern const u16 cus_MarkerStackSize;
#else
extern "C" const u16 cus_NbEnv;
extern "C" const u16 cus_NbTimer;
extern "C" const u16 cus_NbCoarseTimer;
extern "C" const u16 cus_MarkerStackSize;
extern "C" void * pHeapStart;  /* used to desallocate mem. when exiting Rtk for Windows */
#endif

#undef DefExtern

#endif // __SYS_SYS_INIT_H__
