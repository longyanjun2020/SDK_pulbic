/****************************************************************************/
/*  File    : sys_sys_scf.ho                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Variables definitions for linker                             */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/
#ifndef __SYS_SYS_SCF_HO__
#define __SYS_SYS_SCF_HO__

extern u32 Image$$ROM_BOOT$$Base;
//extern u32 Image$$ROM_BOOT$$Limit;
//extern u32 Image$$ROM_SWINFO$$Base;
//extern u32 Image$$ROM_SWINFO$$Limit;
//extern u32 Image$$ROM$$Base;
//extern u32 Image$$ROM$$Limit;
//extern u32 Image$$RW_STATICBOOT$$Base;
extern u32 Image$$XRAM$$Base;
//extern u32 Image$$XRAM$$Length;
//extern u32 Image$$XRAM_RO_END$$Base;


extern u32 Image$$HEAP_START$$Base;
//extern u32 Image$$IRAM$Heap$Base;

#ifdef __RTK_OVER_R2__
extern u32 iram_lma_end;
#endif

#define Image__RO__Base		Image$$ROM_BOOT$$Base

//#define Image__RO__Limit	Image$$ROM$$Limit

#define Image__RAM__Base  Image$$XRAM$$Base

#define Image__ZI__Limit	Image$$HEAP_START$$Base

extern u32 Load$$IRAM_SECTION2$$Base;
extern u32 Image$$IRAM_SECTION2$$Length;

#ifdef __BLUETOOTH_DRV_MSTAR_ACRUX2__
// declare the BT section symbols
extern u32 Image$$IRAM_SECTION2$$Base;
extern u32 Image$$IRAM_SECTION2$$Limit;

extern u32 Image$$IMI2_HEAP_START$$Base;

#define Image__IRAM_SECTION2_Base	Image$$IRAM_SECTION2$$Base
#define Image__IRAM_SECTION2_Limit	Image$$IRAM_SECTION2$$Limit


#define Image__IRAM_SECTION2_ZI_Limit	Image$$IMI2_HEAP_START$$Base
#endif //__BLUETOOTH_DRV_MSTAR_ACRUX2__

//#define Image__IRAM_Heap_Base   Image$$IRAM$Heap$Base

//define the binary end address
//#define Load_Limit   ((u32)&Load$$IRAM_SECTION2$$Base+(u32)&Image$$IRAM_SECTION2$$Length)


#endif //__SYS_SCF_HO__
