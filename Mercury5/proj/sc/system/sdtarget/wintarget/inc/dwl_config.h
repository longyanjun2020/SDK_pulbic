/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Target downloader                                            */
/*             Process configuration                                        */
/****************************************************************************/



#ifndef _7e8e015e0ec223e94f02aa7ec5718d57_included_dwl_config_h
#define _7e8e015e0ec223e94f02aa7ec5718d57_included_dwl_config_h

#include "sysapi.h" // for ExtMem_e

/****************************************************************************/
/* STRUCTURES                                                               */
/****************************************************************************/

typedef struct
{
    u8   u8_BinariesNumber;   /* Number of binary files to download */
    u32  b_EepromStage: 1;    /* 1 if .e2p files must be downloaded */
    u32  b_CustoStage: 1;     /* 1 if .cus files must be downloaded */
    u32  b_EraseCusto: 1;     /* 1 if the existing customisation files must be erased */
    u32  b_EraseObj: 1;       /* 1 if applicative data must be erased */
    u32  b_EraseAll: 1;       /* 1 if the whole flash must be erased */
    u32  b_InitLock: 1;       /* 1 if the locks have to be initialised */
    u32  b_RelayXRAM: 1;      /* 1 if the downloader will just bootstrap a binary in XRAM */
    u32  b_FinalReset: 1;     /* 1 if the downloader will reset the module in nominal mode */
    u32  b_NoTerminalData: 1; /* 1 if nothing has to be appended to downloaded .bin files */
    u32  b_UploadMode: 1;     /* 1 if the user wants to retrieve data from the module */
    u32  b_CustomerLock: 1;   /* 1 if the PC dongle key must be used in lock computations */
    u32  b_NandOnly: 1;       /* 1 if the target based on a solution NAND+XRAM */
    u32  b_EraseBackTrace: 1; /* 1 if the existing BackTrace must be erased */
    u32  b_CISCreate: 1;      /* 1 if NAND CIS create operation is necessary */
    u32  b2_Format: 2;        /* 1 for doing FAT16 and 2 for doing FAT32 formats */
    u32  b_UploadBackTrace: 1; /* 1 if the user wants to retrieve BackTrace from the module */
    u32  b_MultiFLASH: 2;
    u32  b_ListenMode: 1;     /* 1 if the download listen mode is enable */
    u32  b_DownloadPatch: 1;  /* 1 if patch files are selected to be downloaded */
    u32  b_RtcSync: 1;        /* 1 if DWLWin transmit PC clock to device after download */
    u32  b_KeepStateAfterDL: 1; /* 1 if keep current state after DL */
    u32  b_NvramRo: 1;        /* reserved for G1 NVRAM RO */
    u32  b_GetInformationProtocol: 1; /*1 enable GetInformationProtocol*/
    u32  b_NvramRw: 1;        /* reserved for G1 NVRAM RW */
    u32  b_EraseInitFF: 1;    /* 1 Erase E2P in CIS when erase all */
    u32  b_UploadFacImageAfterDwl: 1;   /* Upload flash content for factory flash programmer after download */
    u32  b_Pad_2: 28;
} dwl_MainDescription_t;

typedef struct
{
    u32 b_EraseAll: 1;  /* 1 if the whole flash must be erased */
    u32 b_Pad: 31;
} dwl_Param_t;


typedef struct
{
    u32  u32_TargetCode;      /* TargetId field of a .wpb file */
    u32  u32_Origin;
    u32  u32_Length;
} dwl_BinaryDescriptor_t;


/****************************************************************************/
/* SHARED DATA                                                              */
/****************************************************************************/
#ifdef __DWL_CONFIG_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Global variable:
 * describes the whole download process */
EXTERN dwl_MainDescription_t dwl_s_Config;

/* Global variable:
 * save the parameters in the parameter download process */
EXTERN dwl_Param_t dwl_s_Param;

/* Global variable:
 * array of the descriptors of the binary files to download */
EXTERN dwl_BinaryDescriptor_t *dwl_ps_BinaryCatalog;

/* Global variable:
 * Random data sent by DwlWin */
EXTERN u8 dwl_au8_Crypt[6*32];

/* Global variable:
 * Key to use in lock computations */
EXTERN u32 dwl_u32_PcDongleKey;

/* Global variable:
 * describes the whole download process */
EXTERN bool dwl_usbMode;
EXTERN bool debugMode;
EXTERN u32 dwlwin_ver;
EXTERN bool partialCusDwl;

/* Global variable:
 * 1: Enable Multi-Bin  */
EXTERN bool dwl_b_MultiBin;

#ifdef __SDTARGET__
EXTERN u8   *gu8exteBuf;
EXTERN u32  gu32extSize;
#endif

/****************************************************************************/
/* EXPORTED FUNCTIONS                                                       */
/****************************************************************************/

/****************************************************************************/
/*  Function: dwl_Configure                                                 */
/*--------------------------------------------------------------------------*/
/*  Scope   : Download process configuration.                               */
/*            Retrieves the information from the remote host.               */
/*                                                                          */
/*  Return    : 0 success. < 0 failed                                       */
/*                                                                          */
/*  Interface : void                                                        */
/****************************************************************************/
s32 dwl_Configure(void);

/****************************************************************************/
/*  Function: dwl_GetBinaryDescriptors_phase2                               */
/*--------------------------------------------------------------------------*/
/*  Scope   : Retrieves information about the binary files to download      */
/*                                                                          */
/*  Return    : s32 0 ( SUCCESSFUL ) / -1 ( FAIL )                          */
/*                                                                          */
/*  Interface : (void)                                                      */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  dwl_s_Config      |   |   | X |                                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 dwl_GetBinaryDescriptors_phase2(void);


u32 l__u32_ROMSize(void);

#endif /* ! _7e8e015e0ec223e94f02aa7ec5718d57_included_dwl_config_h   */
