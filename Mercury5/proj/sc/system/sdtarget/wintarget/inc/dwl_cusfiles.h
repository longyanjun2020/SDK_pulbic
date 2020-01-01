/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Target downloader                                            */
/*             Customisation files download                                 */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef _DWL_CUSFILES_H_
#define _DWL_CUSFILES_H_

#define __SUPPORT_DSP_PATCH_CUS_DOWNLOAD__ 0

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define CUS_SIG_SIZE        0x04
#define CUS_OBJ_STAT_TAG    0xFFFFFFF0
#define CUS_OBJSIG_IDX_MMI  0x00
#define CUS_OBJSIG_IDX_SENS 0x01
#define CUS_OBJSIG_IDX_LCM  0x02
#define CUS_OBJSIG_IDX_DSP  0x03
#define CUS_OBJSIG_IDX_LAST CUS_OBJSIG_IDX_DSP

typedef enum
{
   DWL_TYPE_AD_CUSTO,
   DWL_TYPE_AD_JAVA,
   DWL_TYPE_END_OF_CUSTO,
   DWL_TYPE_HEADER_OF_CUSTO,
   DWL_TYPE_VERIFY_CHKSUM_OF_CUSTO,
   DWL_TYPE_SENSOR_OF_CUSTO,
   DWL_TYPE_LCDTABLE,
#if __SUPPORT_DSP_PATCH_CUS_DOWNLOAD__
   DWL_TYPE_DSP,
#endif
   DWL_TYPE_CUSTOERROR
} dwl_CustoType_e;


//-------------------------------------------------------------------------------------------------
// Extern Variables
//-------------------------------------------------------------------------------------------------
extern  u8 const    gu8volSig[CUS_SIG_SIZE];
extern  u8 const    gu8objSigs[CUS_OBJSIG_IDX_LAST+0x01][CUS_SIG_SIZE];

//-------------------------------------------------------------------------------------------------
// Typedefs
//-------------------------------------------------------------------------------------------------
typedef struct dwl_CustoVolHdr_s
{
    u8      sig[CUS_SIG_SIZE];
    u32     u32addr;
} dwl_CustoVolHdr_t;

typedef struct dwl_CustoObjHdr_s
{
    u32     u32CellSize;
    u8      sig[CUS_SIG_SIZE];
    u32     u32dataSize;
    u32     u32flags;
} dwl_CustoObjHdr_t;

#define LCD_TABLE_ID      0x434D434CUL  // "CMCL" -> revert of "LCMC"
#define SENSOR_TABLE_ID   0x54435344UL
#define DSP_PATCH_ID      0x50505344UL
#ifdef __SDTARGET__
#define FLAT_ID_MEMPRM    0x4D52504DUL  // "MPRM"
#endif

//-------------------------------------------------------------------------------------------------
// Description: Custo download routine
//
// Arguments:   None
//
// Return:      0 if succeeded or failure error code if < 0
//
// Notes:
//-------------------------------------------------------------------------------------------------
s32 dwl_recvCustFiles(void);

#endif  // !_DWL_CUSFILES_H_
