#ifndef MBS_BMAP_H
#define MBS_BMAP_H

//constant
#define MAX_SUPPORT_CLUT_TABLE 2
#define MAX_SUPPORT_CLUT_TASK  3

// structure
typedef struct stcclutInst
{
    tmInstance_t            mbsInst;
    tmdlMbsModuleHandle_t   clutModuleHandle[MAX_SUPPORT_CLUT_TABLE];
    tmdlMbsTaskHandle_t     cluttaskHandle[MAX_SUPPORT_CLUT_TASK];
    AppSem_Semaphore clutSema;
    AppSem_Semaphore compSema;
    Int comp_done;
} stcclutInst, *pstcclutInst;

// API
tmErrorCode_t mbs_clut_int_init(stcclutInst *pClut);

tmErrorCode_t mbs_clut_int_exec(
    UInt8* dst[3],
    UInt8* src[3],
    int width_y, int height_y, int stride_y,
    int width_c, int height_c, int stride_c,
    tmColor4_t* clutable_y,
    tmColor4_t* clutable_c,
    stcclutInst *pClut, int nrOfTasks);

tmErrorCode_t mbs_clut_sync(stcclutInst *pClut);

tmErrorCode_t mbs_clut_int_fini(stcclutInst *pClut);

#endif
