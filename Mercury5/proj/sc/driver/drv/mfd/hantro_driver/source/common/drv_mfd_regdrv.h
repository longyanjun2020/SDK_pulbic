/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2006 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Description : 
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: regdrv.h,v $
--  $Revision: 1.6 $
--  $Date: 2007/07/06 09:52:07 $
--
------------------------------------------------------------------------------*/

#ifndef REGDRV_H
#define REGDRV_H

/*------------------------------------------------------------------------------
    Include headers
------------------------------------------------------------------------------*/

#include "drv_mfd_basetype.h"

/*------------------------------------------------------------------------------
    Module defines
------------------------------------------------------------------------------*/

#define DEC_8170_IRQ_RDY            0x01
#define DEC_8170_IRQ_BUS            0x02
#define DEC_8170_IRQ_BUFFER         0x04
#define DEC_8170_IRQ_ASO            0x08
#define DEC_8170_IRQ_ERROR          0x10
#define DEC_8170_IRQ_SLICE          0x20

typedef enum {
/* include script-generated part */
#include "drv_mfd_8170enum.h"
    HWIF_DEC_IRQ_STAT,
    HWIF_PP_IRQ_STAT,
    HWIF_LAST_REG,

    /* aliases */
    HWIF_MPEG4_DC_BASE = HWIF_I4X4_OR_DC_BASE,
    HWIF_INTRA_4X4_BASE = HWIF_I4X4_OR_DC_BASE

} hwIfName_e;

/*------------------------------------------------------------------------------
    Data types
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Function prototypes
------------------------------------------------------------------------------*/

void SetDecRegister(u32 *regBase, u32 id, u32 value);
u32  GetDecRegister(const u32 *regBase, u32 id);

#endif /* #ifndef REGDRV_H */
