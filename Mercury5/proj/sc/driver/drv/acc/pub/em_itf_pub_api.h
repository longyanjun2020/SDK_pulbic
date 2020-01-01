/****************************************************************************\
  \file     em_itf_pub.h
  \brief    prototype of EM API and other definitions
  \date     2007/10/03
  \version  1.00
  \author   Peterwei Wang
  \warning

--------------------------------------------------------------------------
  Historical :
-----------------------------------------------------------------------------
    Date  | Author  | Err  |  Modification
----------+---------+------+-----------------------------------------------
----------+---------+------+-----------------------------------------------
\****************************************************************************/
#ifndef __EM_ITF_PUB_API_H__
#define __EM_ITF_PUB_API_H__

#include "vm_types.ht"
#include "em_itf_pub_forward.h"
//#include "mdl_bat_pars_pub.h"	//move to em_itf_batt_pub_api.h

//void em_rtcTest(vm_rtcTimeFormat_t *time);
void em_lcdTest(u8 refresh_mmi, LcdTestColor_t color);
bool em_lcdStreamTest(void *pStream);
bool em_lcdRegReadTest(void *pStream,u32 *num,u32 *pArray);
//void em_battData(bat_Data_t *batt_info); //move to em_itf_batt_pub_api.h
void em_adcData(adc_Data_t *adcReading);
void em_abbTest(u8 write, u8 reg_addr, u16 reg_w_value, u32 *reg_r_value);

s32 em_sdMount(void);
s32 em_sdFormat(void);
s32 em_sdGetSpace(u32 * total, u32 * free);
s32 em_sdReadWriteTest(u8 * name);
#ifdef __DUAL_CARD__
s32 em_sd2ReadWriteTest(u8 * name);
#endif
s32 em_sdDirTest(u8 * name);
void em_HandWritingTest(bool enable);

void em_WcustDutKeyRsp_test(u8 row, u8 col);
int em_SD_WRITE_1KB_TEST(void);
int em_SD_WRITE_1MB_TEST (void);
int em_SD_READ_1KB_TEST(void);
int em_SD_READ_1MB_TEST(void);
int em_SD_WRITE_RANDOM_TEST(void);
int em_SD_READ_RANDOM_TEST(void);
int em_READ_SD1_TO_SD2_TEST(void);

#define SIZE_10MB 10485760 // 10*1024*1024 = 10485760
#define SIZE_64KB    65536 //      64*1024 =    65536
#define SIZE_128KB  131072 //     128*1024 =   131072

typedef enum
{
    E_TPR_SUCCESS               = 0,
    E_TPR_MAKE_DIR_FAIL         = 1,
    E_TPR_MEM_ALLOCATE_FAIL     = 2,
    E_TPR_FILE_OPEN_FAIL        = 3,
    E_TPR_FILE_ACCESS_FAIL      = 4,
    E_TPR_FILE_CLOSE_FAIL       = 5,

} E_TEST_PERFORMANCE_RESULT;

typedef enum
{
    E_TP_DIR_R  = 0,
    E_TP_DIR_W  = 1,

} E_TEST_PERFORMANCE_DIR;

typedef enum
{
    E_TP_SEQUENCE  = 0,
    E_TP_RANDOM    = 1,

} E_TEST_PERFORMANCE_TYPE;

typedef struct _PERFORMANCE_TEST
{
    U8  Disk; // select card
    E_TEST_PERFORMANCE_DIR eDir;
    E_TEST_PERFORMANCE_TYPE eType;
    U32 SizeTotal; // total size in byte
    U32 SizeUnit; // access mount in byte per time

    E_TEST_PERFORMANCE_RESULT  eResult; // return
    U32 Speed; // return if success

} PERFORMANCE_TEST;

void em_performance_test(PERFORMANCE_TEST * pPerformanceTest);

#endif//__EM_ITF_PUB_API_H__
