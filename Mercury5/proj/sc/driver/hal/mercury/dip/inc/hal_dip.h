#ifndef __HAL_DIP__
#define __HAL_DIP__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "hal_dip_pub.h"
#if defined(__GNUC__)
#include "vm_types.ht"
#endif

/*=============================================================*/
// Macro
/*=============================================================*/

#define DIP_MAX_WIDTH               (2304)
#define DIP_MAX_HEIGTH              (2304)

/* Interrupt */
#define DIP0_INTR_R                 (0x0100)
#define DIP0_INTR_W                 (0x0200)
#define HAL_DIP0_MASK_INTR(intr)    hal_dip_mask_intr(0, intr)

/* DIP module */
#define DIP_HW_SUPPORT_MAX_NUM      (1)
#define RDIP_MAX_NUM                (DIP_HW_SUPPORT_MAX_NUM)

/* Error check */
#define CHECK_ALIGN16(x) \
    do { \
        if ((x)&0xF) { \
            return DIP_RET_FAIL; \
        } \
    } while (0)

#define CHECK_ALIGN32(x) \
do { \
    if ((x)&0x1F) { \
        return DIP_RET_FAIL; \
    } \
} while (0)

#define CHECK_MAX_WIDTH(w)  \
do { \
    if ((w) > DIP_MAX_WIDTH) {  \
        return DIP_RET_FAIL;    \
    }   \
} while (0)

#define CHECK_MAX_HEIGTH(h)	\
do { \
    if ((h) > DIP_MAX_HEIGTH) { \
        return DIP_RET_FAIL;    \
    }   \
} while (0)

/*=============================================================*/
// Structure
/*=============================================================*/	

typedef struct DIPBUFATTR_s
{
    u32             nBaseAddrY; // MIU address.
    u32             nBaseAddrC; // MIU address.
    u32             nWidth;
    u32             nHeight;
    u32             nLineOffset;
    u32             nColorFormat;
    u32             nBufNum;
    u32             nFrameOffsetY;
    u32             nFrameOffsetC;
    u32             nScaleWidth;
    u32             nScaleHeight;
    BOOL            bYCSwap;
    BOOL            bUVSwap;
} DIPBUFATTR_t, *PDIPBUFATTR;

typedef struct DIPATTR_s
{
    DIPBUFATTR_t    tSrcBufAttr;
    DIPBUFATTR_t    tDestBufAttr;
    DIPROTATE_e     eRotateDeg;
    BOOL            bRotateEn;
    BOOL            bHScaleEn;
    BOOL            bVScaleEn;
    BOOL            bOsdbEn;
    BOOL            bFormatConvert;
    BOOL            bHMirror;
    BOOL            bVFlip;
    BOOL            bEfficientRotateEn;
} DIPATTR_t, *PDIPATTR;

/*=============================================================*/
// Enum
/*=============================================================*/

typedef enum {
    DIP0_INTR_R0 = (DIP0_INTR_R | 0x0000),
    DIP0_INTR_R1,
    DIP0_INTR_R2,
    DIP0_INTR_R3,
    DIP0_INTR_R4,
    DIP0_INTR_R5,
    DIP0_INTR_R6,
    DIP0_INTR_R7,
    DIP0_INTR_W0 = (DIP0_INTR_W | 0x0000),
    DIP0_INTR_W1,
    DIP0_INTR_W2,
    DIP0_INTR_W3,
    DIP0_INTR_W4,
    DIP0_INTR_W5,
    DIP0_INTR_W6,
    DIP0_INTR_W7,
    //
    DIP_INTR_MAX
} DIP_INTR_SRC_e;

/*=============================================================*/
// Public function
/*=============================================================*/

s32 hal_dip_init(void);
void hal_dip_mask_intr(u8 nDipMdlID, DIP_INTR_SRC_e intr);
void hal_dip_unmask_intr(u8 nDipMdlID, DIP_INTR_SRC_e intr);
void hal_dip_clr_intr_status(u8 nDipMdlID, DIP_INTR_SRC_e intr);
BOOL hal_dip_get_intr_status(u8 nDipMdlID, DIP_INTR_SRC_e intr);
void hal_dip_sw_reset(u8 nDipMdlID);
s32 hal_dip_set_trigger(u8 nDipMdlID, PDIPATTR pDipAttr);

#endif //__HAL_DIP__
