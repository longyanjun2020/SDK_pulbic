/**
 *
 * @file    cus_capability.h
 *
 * @brief   Capability for compiler option
 *
 * @author
 * @version $Id
 *
 */

#ifndef __CUS_CAPABILITY_H__
#define __CUS_CAPABILITY_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef enum
{
    E_OPTION_IP_FCIE_ONLY  = 0,
    E_OPTION_IP_SDIO_ONLY  = 1,
    E_OPTION_IP_FCIE_SDIO  = 2,

} E_OPTION_STG_IP_CFG;

typedef enum
{
    E_OPTION_NOT_SUPPORT_HOT_PLUG  = 0,
    E_OPTION_HOT_PLUG_INSERT_LOW   = 1,
    E_OPTION_HOT_PLUG_INSERT_HIGH  = 2,

} E_OPTION_STG_HOT_PLUG;

typedef enum
{
    E_OPTION_SD1_4_BITS_ONLY_NO_SD2 = 0,
    E_OPTION_SD1_4_BITS_SD2_4_BITS  = 1,
    E_OPTION_SD1_4_BITS_SD2_1_BIT   = 2,
    E_OPTION_SD1_1_BIT_SD2_1_BIT    = 3, // dual 1 bit on sd pad

} E_OPTION_STG_DATA_BUS;

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION PROTOTYPE                                                */
/*--------------------------------------------------------------------------*/

bool CusIsDualCamEnabled(void);
bool CusIsTouchScreenEnabled(void);
bool CusIsVectorFontEnabled(void);
bool CusIsJavaNoPreinstallEnabled(void);
bool CusIsNandEnabled(void);
bool CusIsDbgPortUart2Enabled(void);
bool                    CusStgIfSupportDualCard(void);
E_OPTION_STG_DATA_BUS   CusStgGetDataBusConfig(void);
E_OPTION_STG_HOT_PLUG   CusStgGetHotPlugConfig(u8 u8Disk);
u32                     CusStgGetDowngradeSdClock(void);
u32                     CusStgGetFmrxLimitSdClock(void);
E_OPTION_STG_IP_CFG     CusStgGetIpConfig(void);
bool                    CusStgIfSupportSharePower(void);
bool CusIsA2DPEnabled(void);
bool CusIsLCDTableDRVEnabled(void);
bool CusIsMultipleSensorTableDetectionEnabled(void);
bool CusIsUseReducedDlmInterface(void);
bool CusIsRtkOverArmSysAutoLoadEnabled(void);
bool CusIsRtkOverArmSldlmEnabled(void);
bool CusIsRtkOverArmNandImiSldlmEnabled(void);
bool CusIsSkipDirDotCheck(void);
bool CusIsBootUncompress(void);
bool CusRfIfSupportAUXCLK(void);
bool CusIsSupportRFID(void);
bool CusIsSupportDynamicLoad(void);
bool CusIsSupportSarCaliByEfuse(void);
void CusGetZlibDictAddr(u8 **dictbuf);
void CusGetLZMADictAddr(u8 **dictbuf, u32 *dict_len);
void CusGetLZMABootAddr(u8 **heapbuf, u32 *heap_len, u32 max_size);
void CusGetLZMABoot2Addr(u8 **heapbuf, u32 *heap_len, u32 max_size);

#endif /* __CUS_CAPABILITY_H__ */
