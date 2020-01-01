/******************************************************************************/
/* File    : filename..h                                                            */
/*----------------------------------------------------------------------------*/
/* Scope   : File name of SD DL                                               */
/*                                                                            */
/******************************************************************************/
#ifndef __FILENAME_H__
#define __FILENAME_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#if defined (__SDAPPRAM__) || defined (__SDAPPRAM_PI__)
#define SDTARGET_BIN    "SDIMG/SDTARGETBIN"
#endif

#if defined (__SDTARGET__)
// Descriptor
#define MAIN_DES "SDIMG/MAIN0000DES"
#define CODE_DES "SDIMG/CODE0000DES"
#define CUS_DES  "SDIMG/CUS00000DES"
#define RAI0_DES "SDIMG/RAI00000DES"
#define RAI1_DES "SDIMG/RAI00001DES"

//SDI
#define CODE_BIN "SDIMG/CODE0000SDI"
#define CUS_BIN  "SDIMG/CUS00000SDI"
#define RAI0_BIN "SDIMG/RAI00000SDI"
#define RAI1_BIN "SDIMG/RAI00001SDI"
#define E2P_IMG  "SDIMG/E2P00000SDI"

//PAT
#define DSP_PAT  "SDIMG/DSP00000PAT"

//PRM
#define MEM_PRM  "SDIMG/MEM00000PRM"

//LCD CUS
#define LCD_CUS  "SDIMG/LCD00000CUS"
#endif
//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------

#if defined (__SDTARGET__)
#define FILE_INDEX(x) FILE_##x

typedef enum
{
  FILE_MAIN_DES,

  FILE_CODE_DES,
  FILE_CUS_DES,
  FILE_RAI0_DES,
  FILE_RAI1_DES,

  FILE_CODE_BIN,
  FILE_CUS_BIN,
  FILE_RAI0_BIN,
  FILE_RAI1_BIN,
  FILE_E2P_IMG,

  FILE_DSP_PAT,

  FILE_MEM_PRM,
  FILE_LCD_CUS,
  FILE_NUM
}fileIndex_e;

typedef struct
{
  u8         fileName[25];
  u32        fileHandle;
  u32        fileSize;
  u32        fileOffset;
}file_t;
#endif

//------------------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------------------

#if defined (__SDTARGET__)
extern file_t file[FILE_NUM];
extern file_t *curBinFile;
#endif

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

#if defined (__SDTARGET__)
void dwl_fileInit(void);
s8 dwl_setFile(u8 *fileName, fileIndex_e index);
#endif

#endif /* __FILENAME_H__ */
