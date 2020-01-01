/******************************************************************************/
/* File    : sysunfd.h                                                        */
/*----------------------------------------------------------------------------*/
/* Scope   : System Unified NAND driver header file                           */
/*                                                                            */
/******************************************************************************/
#ifndef __SYSUNFD_H__
#define __SYSUNFD_H__

/******************************************************************************/
/*  Includes                                                                  */
/******************************************************************************/
#define  UNFD_ST_PLAT 0x80000000
#include "../UNFD/inc/drvNAND_err_codes.h"
#include "sysdrvhdr.h"
#include "sysimgprt.h"


/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define NAND_SECTOR_SIZE        0x200
#define MAX_BOOTLDR_TRY_COUNT   10

#ifndef __APCS_RWPI
#define PTR2NANDOPS         ptrNandOps
#else
#define PTR2NANDOPS         (*pptrNandOps)
#endif

#define fpnand_read         PTR2NANDOPS->read
#define fpnand_write        PTR2NANDOPS->write
#define fpnand_getCap       PTR2NANDOPS->getCap
#define fpnand_chkRdy       PTR2NANDOPS->chkRdy

#define fpnand_phyRead      PTR2NANDOPS->phyRead
#define fpnand_phyWrite     PTR2NANDOPS->phyWrite
#define fpnand_eraseBlk     PTR2NANDOPS->eraseBlk
#define fpnand_ejectIns     PTR2NANDOPS->ejectIns
#define fpnand_getInfo      PTR2NANDOPS->getInfo
#define fpnand_setInfo      PTR2NANDOPS->setInfo

#define fpnand_rddWrite(...)
/******************************************************************************/
/* Typedefs                                                                   */
/******************************************************************************/
#if 0
typedef struct diskOpFuncTab_s
{
    Cyg_ErrNo   (*read)(void *, U32, U32);
    Cyg_ErrNo   (*write)(const void *, U32, U32);
    void        (*phyRead)(U32, U8 *, U16);
    U8          (*phyWrite)(U32, U8 *, U16, U8);
    void        (*info)(U8 *);
    U8          (*eraseBlk)(U32);
    void        (*rddWrite)(U8 *, U8);
    void        (*ejectIns)(U8);
    U32         (*getCap)(void);
    U8          (*chkRdy)(void);
} DiskOpFuncTab_t;
#endif


typedef struct diskOpFuncTab_s
{
    int			(*read)(void *, unsigned int, unsigned int);
    int			(*write)(const void *, unsigned int, unsigned int);
    unsigned int         (*getCap)(void);
    u8          (*chkRdy)(void);

#if 0
	void        (*phyRead)(unsigned int, u8 *, u8 *, unsigned int);
	void        (*phyWrite)(unsigned int, u8 *, u8 *, unsigned int);
#else
	void		(*phyRead)(unsigned int, u8 *, u16);
	u8			(*phyWrite)(unsigned int, u8 *, u16, u8);
#endif
    u8          (*eraseBlk)(unsigned int);
    void        (*ejectIns)(u8);
    void        (*getInfo)(u8 *);
    void        (*setInfo)(u8 *);
} DiskOpFuncTab_t;

/******************************************************************************/
/* Global Variable Declarations                                               */
/******************************************************************************/
#ifndef __APCS_RWPI
extern DiskOpFuncTab_t *ptrNandOps;
#else
extern DiskOpFuncTab_t **pptrNandOps;
#endif

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/
unsigned int drvNAND_Init(void);
unsigned int drvNAND_LoadBootLoader(u8 *pu8_DestAddr,
			unsigned int u32_StartSector,
			unsigned int u32_SectorCnt,
			unsigned int u32_LogicIdx);
DiskOpFuncTab_t *drvNAND_SetupFnTbl(DiskOpFuncTab_t *newPtrNandOps);

#endif /* __SYSUNFD_H__ */
