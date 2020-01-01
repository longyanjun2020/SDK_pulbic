/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Target downloader                                            */
/*             Medium descriptors                                           */
/*                                                                          */
/****************************************************************************/

#ifndef _DWL_MEDIUM_H_
#define _DWL_MEDIUM_H_

#define DWL_BIN_OK          (0)
#define DWL_BIN_FAILED      (-1)

#define WM_TGT_ANY          0x00000000
#define WM_TGT_CIS          0x00000001
#define WM_TGT_ERROR        0x00000002

#define WM_TGT_EXTERNAL     0x01000000
#define WM_TGT_GPS          0x01000001
#define WM_TGT_NANDP3       0x01000002
#define WM_TGT_NOR_FS       0x01000003    ///< FAT File System on NOR (upon RAI)
#define WM_TGT_RAIF         0x01000004    ///< RAI file access
#define WM_TGT_NANDPRT      0x01000005    ///< NAND images partition
#define WM_TGT_NANDE2P      0x01000006    ///< NAND E2P
#define WM_TGT_NANDADF      0x01000007    ///< NAND CUSTO/AD file
#define WM_TGT_NANDADP      0x01000008    ///< NAND CUSTO/AD partition
#define WM_TGT_NANDTRC      0x01000009    ///< NAND backtrace
#define WM_TGT_RAIP         0x0100000A    ///< RAI partition access
#define WM_TGT_NANDFATU     0x0100000B    ///< NAND user FAT
#define WM_TGT_DSPPATCH     0x0100000C    ///< DSP patch file in CUSTO/AD format
#ifdef __B3_RESTORE__
#define WM_TGT_NANDE2P_RL   0x0100000D
#define WM_TGT_NANDRAI_RL   0x0100000E
#define WM_TGT_NANDTRC_RL   0x0100000F
#define WM_TGT_NANDFATU_RL  0x01000010
#define WM_TGT_NANDPRT_RL   0x01000011
#define WM_TGT_NANDBL_RL    0x01000012
#define WM_TGT_NANDCUS_RL   0x01000013
#endif
#ifdef __B3_UPLOAD_NEW__
#define WM_TGT_WHOLE        0x01000014
#endif

#define WM_TGT_NANDFACIMG       0x01000015
#define WM_TGT_NANDFACIMG_TBL   0x01000016

#define WM_TGT_MULTI_BIN_CODE    0x01000023
#define WM_TGT_MULTI_BIN_RAI     0x01000024
#define WM_TGT_MULTI_BIN_E2P     0x01000025

#define WM_TGT_NOR_FS_RAW_BIN       0x01000026    ///< Hidden FAT File System on NOR (upon RAI)
#define WM_TGT_NOR_FS_HIDDEN_RAW_BIN       0x01000027    ///< Hidden FAT File (raw bin)System on NOR (upon RAI)
#define WM_TGT_NANDFATU_HIDDEN     0x01000028     ///< NAND user FAT Hidden Fs

#ifdef __SDTARGET__
#define WM_TGT_MULTI_BIN_CUS     0x01000029
#endif

#define WM_TGT_RAW_BIN      0xFFFFFFFF


/* Status reporting callback type definition */
typedef void (*dwl_TellStatus_t)(u32, ...);

/* Handle seen as a void* pointer by interface functions */
typedef void *dwl_handle_t;


/* Parameter for the status reporting callback */
typedef enum
{
    STAT_DWL_CANCEL,
    STAT_SET_ATOM_NUMBER,
    STAT_NEXT_ATOM_DURATION,
    STAT_ATOM_FAILURE,
    STAT_ATOM_COMPLETE,
    STAT_E2P_INFO,
	STAT_E2P_UPLD,
    STAT_PATCH_INFO,
    STAT_MEDIUM_READY,
    STAT_MEDIUM_NOTREADY,
    STAT_MEDIUM_BYPASS,
    STAT_UPLD_READY,
    STAT_UPLD_FAIL,
} dwl_StatusRequest_e;

typedef s32    (*pf_Setup_t)(dwl_handle_t *, u32, u32, dwl_TellStatus_t);
typedef s32    (*pf_Write_t)(dwl_handle_t, void*, u32);
typedef s32    (*pf_Complete_t)(dwl_handle_t, u32*, const dwl_TellStatus_t);

/* Registering descriptions for the different media */
typedef struct
{
    u32             u32TargetId;
    pf_Setup_t      pf_Setup;
    pf_Write_t      pf_Write;
    pf_Complete_t   pf_Complete;
} dwl_MediumDesc_t;

/****************************************************************************/
/*  Function: dwl_GetMediumDesc                                       */
/*--------------------------------------------------------------------------*/
/*  Scope   : Returns the medium descriptor associated with                 */
/*            the supplied target identifier                                */
/*                                                                          */
/*  Return    : (dwl_MediumDesc_t*) Pointer to medium or NULL               */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_TargetId     | X |   |   |  Identifier of the target               */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
const dwl_MediumDesc_t *dwl_GetMediumDesc(u32 id);

void dwl_ReportStatus(u32 u32code, ...);


/************** Below for NAND **************/
//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define DWL_VALIDATION_BUF_SIZE     0x100000 // the size must be larger than E2P size
#define FAT_CHKSUM_COUNT_PER_MSEC   (2 * 1024 * 1024 / 1000)   /* 2MB per second */
#define BIN_CHKSUM_COUNT_PER_MSEC   (4 * 1024 * 1024 / 1000)   /* 4MB per second */
/************** Above for NAND **************/

#endif /* ! _DWL_MEDIUM_H_  */
