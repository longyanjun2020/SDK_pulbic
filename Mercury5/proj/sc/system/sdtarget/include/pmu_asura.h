/******************************************************************************/
/* File    : pmu_asura.h                                                      */
/*----------------------------------------------------------------------------*/
/* Scope   : Asura PMU header file                                            */
/*                                                                            */
/******************************************************************************/
#ifndef __PMU_ASURA_H__
#define __PMU_ASURA_H__

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
/* Asura Efuse RIU fields */
#define ASURA_PMU_BASE              0x2000
#define ASURA_VPER1_2_ADDR          (ASURA_PMU_BASE + (0x05 << 0x01))
#define ASURA_VPER3_4_ADDR          (ASURA_PMU_BASE + (0x06 << 0x01))
#define ASURA_EFUSE0_ADDR           (ASURA_PMU_BASE + (0x1B << 0x01))
#define ASURA_EFUSE1_ADDR           (ASURA_PMU_BASE + (0x1C << 0x01))
#define ASURA_EFUSE2_ADDR           (ASURA_PMU_BASE + (0x1D << 0x01))
#define ASURA_LDO_STAT_ADDR         (ASURA_PMU_BASE + (0x1F << 0x01))
#define ASURA_CHARGER_ADDR20        (ASURA_PMU_BASE + (0x20 << 0x01))
#define ASURA_CHARGER_ADDR21        (ASURA_PMU_BASE + (0x21 << 0x01))

#define VPER2_ACT_MODE_OFF          6
#define VPER2_ACT_MODE_MSK          (0x01 << VPER2_ACT_MODE_OFF)
#define VPER2_STB_MODE_OFF          7
#define VPER2_STB_MODE_MSK          (0x01 << VPER2_STB_MODE_OFF)
#define VPER2_ACT_LQ_OFF            8
#define VPER2_ACT_LQ_MSK            (0x01 << VPER2_ACT_LQ_OFF)

#define EFUSE2_BIG3FIELD0_OFF       1
#define EFUSE2_BIG3FIELD0_COUNT     8
#define CMUEFUSE_FIELD0_OFF         0
#define EFUSE1_BIG3FIELD1_OFF       3
#define EFUSE1_BIG3FIELD1_COUNT     2
#define CMUEFUSE_FIELD1_OFF         8
#define EFUSE1_BIG3FIELD2_OFF       7
#define EFUSE1_BIG3FIELD2_COUNT     4
#define CMUEFUSE_FIELD2_OFF         10

#define VPER2_PG_STAT_OFF           3
#define VPER2_PG_STAT_MSK           (0x01 << VPER2_PG_STAT_OFF)
#define PG_STAT_POLL_COUNT          5
#define PG_STAT_POLL_LAG            1000    /* in uSec */

#define CHARGER_CCTARGET_OFF        11
#define CHARGER_CCTARGET_MSK        (0x07 << CHARGER_CCTARGET_OFF)
#define CHARGER_CCTARGET_400MA      (0x03 << CHARGER_CCTARGET_OFF)
#define CHARGER_CTRL_PULSE_OFF      0
#define CHARGER_CTRL_PULSE_MSK      (0x01 << CHARGER_CTRL_PULSE_OFF)

#endif /* __PMU_ASURA_H__ */
