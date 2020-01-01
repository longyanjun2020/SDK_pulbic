#ifndef __HWREG_H__
#define __HWREG_H__

#define REG_OFFSET_SHIFT_BITS    2

#define REG(Reg_Addr)           (*(volatile U16*)(Reg_Addr))
#define GET_REG_ADDR(x, y)      ((x)+((y) << REG_OFFSET_SHIFT_BITS))


#define REG_WRITE_UINT16(reg_addr, val)      REG((reg_addr)) = (val)
#define REG_READ_UINT16(reg_addr, val)       val = REG((reg_addr))
#define REG_SET_BITS_UINT16(reg_addr, val)   REG((reg_addr)) |= (val)
#define REG_CLR_BITS_UINT16(reg_addr, val)   REG((reg_addr)) &= ~(val)
#define REG_W1C_BITS_UINT16(reg_addr, val)   REG_WRITE_UINT16((reg_addr), REG((reg_addr))&(val))


#define RIU_BASE                0x74000000U

// #define REG_BANK_MPLL        0x0980U	// FIXME
#if defined(__MSW8522__) || defined(__MSW8556__)
#define REG_BANK_MPLL           0x1F00U	// FIXME
#define REG_BANK_CHIPTOP        0x0F00U	// FIXME
#define REG_BANK_PADCRTL        0x1980U 
#define REG_BANK_FCIE0          0x1600U
#define REG_BANK_FCIE1          0x1680U
#define REG_BANK_FCIE2          0x1700U
#define REG_BANK_FCIE3          0x1780U
#else
#define REG_BANK_CHIPTOP        0x0F00U	// FIXME
#define REG_BANK_FCIE0          0x1400U
#define REG_BANK_FCIE1          0x1480U
#define REG_BANK_FCIE2          0x1500U
#define REG_BANK_FCIE3          0x1580U
#endif

#define FCIE0_BASE              GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE0) /* 0x74005000 */
#define FCIE1_BASE              GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE1) /* 0x74005200 */
#define FCIE2_BASE              GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE2) /* 0x74005400 */
#define FCIE3_BASE              GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE3) /* 0x74005600 */

#define FCIE_REG_BASE_ADDR      FCIE0_BASE
#define FCIE_REG_BASE1_ADDR     FCIE1_BASE
#define FCIE_NC_CIFD_BASE       FCIE2_BASE

#endif /* __HWREG_H__ */
