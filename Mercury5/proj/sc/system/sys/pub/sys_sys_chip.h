/****************************************************************************/
/*  File    : sys_sys_chip.h                                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   :                                                               */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/

#ifndef __SYS_SYS_CHIP_H__
#define __SYS_SYS_CHIP_H__
/****************************************************************************/
/*            Include                                                       */
/****************************************************************************/
//#include "kernel.h"


/******************************************************************************/
/*            Parameters for CHIP ID                                              */
/******************************************************************************/
typedef enum
{
    CHIP_TYPE_G1 = 0x0100,
    CHIP_TYPE_B3 = 0x0400,
    CHIP_TYPE_BRAVO = 0x0500,
    CHIP_TYPE_B5 = 0x0600,
    CHIP_TYPE_BLOSSOM = 0x0a00,
    CHIP_TYPE_I3 = 0x0b00,
    CHIP_TYPE_MV5 = 0x0c00
}sys_ChipType_e;

#define CHIP_ID(_ID_, _REV_)        SYS_CHIP_ID_##_ID_##_##_REV_

typedef enum
{
    /* G1 SYS_CHIP_ID_G1_U0x */
    CHIP_ID(G1, U01) = (CHIP_TYPE_G1|0x01),
    CHIP_ID(G1, U02), 
    CHIP_ID(G1, U03),
    CHIP_ID(G1, U04),
    CHIP_ID(G1, U05),
    CHIP_ID(G1, U06),
    CHIP_ID(G1, U07),
    CHIP_ID(G1, U08),
    CHIP_ID(G1, U09),

    /* B3 */
    CHIP_ID(B3, U01) = (CHIP_TYPE_B3|0x01),
    CHIP_ID(B3, U02), 
    CHIP_ID(B3, U03),
    CHIP_ID(B3, U04),
    CHIP_ID(B3, U05),
    CHIP_ID(B3, U06),
    CHIP_ID(B3, U07),
    CHIP_ID(B3, U08),
    CHIP_ID(B3, U09),

    /* Bravo*/
    CHIP_ID(BRAVO, U01) = (CHIP_TYPE_BRAVO|0x01),
    CHIP_ID(BRAVO, U02), 
    CHIP_ID(BRAVO, U03),
    CHIP_ID(BRAVO, U04),
    CHIP_ID(BRAVO, U05),
    CHIP_ID(BRAVO, U06),
    CHIP_ID(BRAVO, U07),
    CHIP_ID(BRAVO, U08),
    CHIP_ID(BRAVO, U09),

    /* B5 */
    CHIP_ID(B5, U01) = (CHIP_TYPE_B5|0x01),
    CHIP_ID(B5, U02), 
    CHIP_ID(B5, U03),
    CHIP_ID(B5, U04),
    CHIP_ID(B5, U05),
    CHIP_ID(B5, U06),
    CHIP_ID(B5, U07),
    CHIP_ID(B5, U08),
    CHIP_ID(B5, U09),

    /* BLOSSOM */
    CHIP_ID(BLOSSOM, U01) = (CHIP_TYPE_BLOSSOM|0x01),
    
    /* I3 */
    CHIP_ID(I3, U01) = (CHIP_TYPE_I3|0x01),

    /* MV5 */
    CHIP_ID(MV5, U01) = (CHIP_TYPE_MV5|0x01),

    /* Revision Base */
    SYS_CHIP_ID_UNKNOWN = 0,
    SYS_CHIP_REV_U01,
    SYS_CHIP_REV_U02,
    SYS_CHIP_REV_U03,
    SYS_CHIP_REV_U04,
    SYS_CHIP_REV_U05,
    SYS_CHIP_REV_U06,
    SYS_CHIP_REV_U07,
    SYS_CHIP_REV_U08,
    SYS_CHIP_REV_U09,

    /* Other new Chip */

} sys_ChipId_e;

sys_ChipId_e sys_GetChipRevisionId(void);
sys_ChipType_e sys_GetChipType(void);

#define CHIP_ID_UPPER_G1U01 (sys_GetChipRevisionId() >= CHIP_ID(G1, U02))

#endif /* __SYS_SYS_CHIP_H__ */

