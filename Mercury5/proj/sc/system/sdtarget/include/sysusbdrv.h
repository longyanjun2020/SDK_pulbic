/******************************************************************************/
/* File    : sysusbdrv.h                                                      */
/*----------------------------------------------------------------------------*/
/* Scope   : System USB driver header file                                    */
/*                                                                            */
/******************************************************************************/
#ifndef __SYSUSBDRV_H__
#define __SYSUSBDRV_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "sysdrvhdr.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#ifndef __APCS_RWPI
#define fpUsbCmdLoop        usbDrvFuncTab.loop
#define fpSCSI_vendor       scsiCmdFuncTab.vend
#define fpSCSI_disk         scsiCmdFuncTab.disk
#define fpdisk_rom          diskCmdFuncTab.rom
#define fpdisk_ram          diskCmdFuncTab.ram
#else
#define fpUsbCmdLoop        ptr_usbDrvFuncTab->loop
#define fpSCSI_vendor       ptr_scsiCmdFuncTab->vend
#define fpSCSI_disk         ptr_scsiCmdFuncTab->disk
#define fpdisk_rom          ptr_diskCmdFuncTab->rom
#define fpdisk_ram          ptr_diskCmdFuncTab->ram
#endif


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/* Main USB driver function tables */
typedef void    (*fnUSBCmdOneArg)(void *pUsbStruct);
typedef void    (*fnUSBCmdNoArg)(void);

typedef struct usbDrvFuncTab_s
{
    void        *loop;          /* CmdLoop */
} usbDrvFuncTab_t;


/* SCSI commands function table */
typedef u8  (*fnSCSI_Command)(void *pcbw, void *pcsw, void *pUsbStruct);

typedef struct scsiFuncTab_s
{
    fnSCSI_Command      vend;   /* vendor commands */
    fnSCSI_Command      disk;   /* disk commands */
} SCSIFuncTab_t;


/* SCSI disk command function table */
typedef struct DiskCmdFuncTab_s
{
    fnSCSI_Command      rom;    /* rom disk command */
    fnSCSI_Command      ram;    /* ram disk command */
} DiskCmdFuncTab_t;


//------------------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------------------
#ifndef __APCS_RWPI
extern  usbDrvFuncTab_t     usbDrvFuncTab;
extern  SCSIFuncTab_t       scsiCmdFuncTab;
extern  DiskCmdFuncTab_t    diskCmdFuncTab;
extern  void                *ptrusbStruct;
#define PTR2USBSTRUCT       ptrusbStruct
#else
extern  usbDrvFuncTab_t     *ptr_usbDrvFuncTab;
extern  SCSIFuncTab_t       *ptr_scsiCmdFuncTab;
extern  DiskCmdFuncTab_t    *ptr_diskCmdFuncTab;
extern  void                **pptrusbStruct;
#define PTR2USBSTRUCT       (*pptrusbStruct)
#endif

extern u32	curr_usbvend_buff_size;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
void    MDrv_USB_Init(void);
void    MDrv_USB_Stop(void);
s32     MDrv_USB_Write(u8 *buf, u32 len);
s32     MDrv_USB_Read(u8 *buf, u32 len);
void    MDrv_USB_Flush(void);
void    MDrv_USB_Clean(void);
void    MDrv_USB_Config(u8 *buf);
void    MDrv_USB_ResetDwldState(void);
u8      MDrv_USB_IsDwldEnd(void);
u8      MDrv_USB_IsUpldEnd(void);
void    MDrv_USB_UpdateVendCmdBuf(void *ptrVendBuf);
void    MDrv_USB_UpdateScsiCmdBuf(void *ptrScsiBuf);
void    MDrv_USB_TouchLoop(void);
#if __CHIPVER__ == 1
void    MDrv_USB_CmdLoop(void *pUsbStruct);
#else
void    MDrv_USB_CmdLoop(void);
#endif

void    MDrv_USB_TouchInISR(void);
void    MDrv_USB_Polling(void);

#endif /* __SYSUSBDRV_H__ */
