#ifndef _FILEMGR_H_
#define _FILEMGR_H_
#include <List.h>

typedef enum
{
    FILE_ID_MODULE,
    FILE_ID_IQ, //IQ CFG0
    FILE_ID_IQ_BIN, //IQ BINARY0
#if defined(__RTK_OS__)
    FILE_ID_IQ_API0_BIN,
    FILE_ID_IQ_API1_BIN,
    FILE_ID_IQ_API2_BIN,
    FILE_ID_IQ_API3_BIN,
    FILE_ID_IQ_API4_BIN,
    FILE_ID_IQ_API5_BIN,
#endif
    FILE_ID_LDC_HORZ,
    FILE_ID_LDC_VERT,
    FILE_ID_LDC_DMA,
    FILE_ID_SENSOR_DRV,
    FILE_ID_AWB_TEMP_CFG,
}ISP_FILE_ID;

typedef struct
{
    char file_path[128];
    struct list_head file_list;
}filemgr_handle;

extern filemgr_handle g_file_mgr[4];
#define FILE_MGR_GLOBAL(n) &g_file_mgr[n]
#define DEFAULT_CFG_PATH "SF:1:\\"

int filemgr_init(filemgr_handle *handle);
int filemgr_release(filemgr_handle *handle);
int filemgr_get_file_name(filemgr_handle *handle,ISP_FILE_ID id,char* file_name);
const char* filemgr_get_file_name_ref(filemgr_handle *handle,ISP_FILE_ID id);
int filemgr_get_file_path_name(filemgr_handle *handle,ISP_FILE_ID id,char* path_name);
int filemgr_set_file(filemgr_handle *handle,ISP_FILE_ID id,const char *name);
int filemgr_del_file(filemgr_handle *handle,ISP_FILE_ID id);
int filemgr_set_file_dir(filemgr_handle *handle,const char *path);
const char* filemgr_get_file_dir(filemgr_handle *handle);
int file_checksum(const char *file_name,int *result);
void get_isp_cfg_path(char *cfg_path);
int unmz(const char *src_name,const char *dest_name);
int unmzToMem(const char *src_name, void *buf);
int unmzGetSize(const char *src_name);
#endif
