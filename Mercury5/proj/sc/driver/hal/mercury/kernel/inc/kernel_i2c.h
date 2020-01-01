#ifndef __KERNEL_I2C_H__
#define __KERNEL_I2C_H__

extern volatile u16* const g_ptCLKGEN;
extern volatile u16* const g_ptCHIPTOP;
extern volatile u16* const g_ptI2C0;
extern volatile u16* const g_ptI2C1;
//+++ [MV5]
extern volatile u16* const g_ptI2C2;
extern volatile u16* const g_ptI2C3;
//--- [MV5]
//############################
//
//IP bank address : for pad mux in chiptop
//
//############################
#define CHIP_REG_BASE                  0 //(0x101E00)
#define CHIP_GPIO1_REG_BASE            0 //(0x101A00)

//for port 0
#define CHIP_REG_HWI2C_MIIC0            (CHIP_GPIO1_REG_BASE+ (0x09*2))
    #define CHIP_MIIC0_PAD_0            (0)
    #define CHIP_MIIC0_PAD_1            (__BIT0)
    #define CHIP_MIIC0_PAD_2            (__BIT1)
    #define CHIP_MIIC0_PAD_3            (__BIT0|__BIT1)
    #define CHIP_MIIC0_PAD_MSK          (__BIT0|__BIT1)
#define CHIP_MIIC0_CLK_ADDR             (0x37*2)
    #define CHIP_MIIC0_CLK_OFF           (__BIT0)
    #define CHIP_MIIC0_CLK_ON_72M       (0)
    #define CHIP_MIIC0_CLK_ON_54M       (__BIT2)
    #define CHIP_MIIC0_CLK_ON_12M       (__BIT3)
    #define CHIP_MIIC0_CLK_ON_NCK       (__BIT2|__BIT3)
    #define CHIP_MIIC0_CLK_MSK          (__BIT0|__BIT1|__BIT2|__BIT3)

//for port 1
#define CHIP_REG_HWI2C_MIIC1            (CHIP_REG_BASE+ (0x09*2)) //0x1EDC
    #define CHIP_MIIC1_PAD_0            (0)
    #define CHIP_MIIC1_PAD_1            (__BIT4)
    #define CHIP_MIIC1_PAD_2            (__BIT5)
    #define CHIP_MIIC1_PAD_3            (__BIT4|__BIT5)
    #define CHIP_MIIC1_PAD_MSK          (__BIT4|__BIT5)
#define CHIP_MIIC1_CLK_ADDR             (0x37*2)
    #define CHIP_MIIC1_CLK_OFF          (__BIT8)
    #define CHIP_MIIC1_CLK_ON_72M       (0)
    #define CHIP_MIIC1_CLK_ON_54M       (__BIT10)
    #define CHIP_MIIC1_CLK_ON_12M       (__BIT11)
    #define CHIP_MIIC1_CLK_ON_NCK       (__BIT10|__BIT11)
    #define CHIP_MIIC1_CLK_MSK          (__BIT8|__BIT9|__BIT10|__BIT11)


//for port 2
#define CHIP_REG_HWI2C_MIIC2            (CHIP_REG_BASE+ (0x16*2) + 1) //0x1EDC
    #define CHIP_MIIC2_PAD_0            (0)
    #define CHIP_MIIC2_PAD_1            (__BIT8) >> 8
    #define CHIP_MIIC2_PAD_2            (__BIT9) >> 8
    #define CHIP_MIIC2_PAD_3            (__BIT8|__BIT9) >> 8
    #define CHIP_MIIC2_PAD_MSK          (__BIT8|__BIT9) >> 8
#define CHIP_MIIC2_CLK_ADDR             (0x39*2)
    #define CHIP_MIIC2_CLK_OFF           (__BIT0)
    #define CHIP_MIIC2_CLK_ON_72M       (0)
    #define CHIP_MIIC2_CLK_ON_54M       (__BIT2)
    #define CHIP_MIIC2_CLK_ON_12M       (__BIT3)
    #define CHIP_MIIC2_CLK_ON_NCK       (__BIT2|__BIT3)
    #define CHIP_MIIC2_CLK_MSK          (__BIT0|__BIT1|__BIT2|__BIT3)


//for port 3
#define CHIP_REG_HWI2C_MIIC3            (CHIP_REG_BASE+ (0x16*2) + 1) //0x1EAE
    #define CHIP_MIIC3_PAD_0            (0)
    #define CHIP_MIIC3_PAD_1            (__BIT10) >> 8
    #define CHIP_MIIC3_PAD_2            (__BIT11) >> 8
    #define CHIP_MIIC3_PAD_3            (__BIT10|__BIT11) >> 8    
    #define CHIP_MIIC3_PAD_MSK          (__BIT10|__BIT11) >> 8
#define CHIP_MIIC3_CLK_ADDR             (0x39*2)
    #define CHIP_MIIC3_CLK_OFF          (__BIT8)
    #define CHIP_MIIC3_CLK_ON_72M       (0)
    #define CHIP_MIIC3_CLK_ON_54M       (__BIT10)
    #define CHIP_MIIC3_CLK_ON_12M       (__BIT11)
    #define CHIP_MIIC3_CLK_ON_NCK       (__BIT10|__BIT11)
    #define CHIP_MIIC3_CLK_MSK          (__BIT8|__BIT9|__BIT10|__BIT11)


//pad mux configuration
#define CHIP_REG_ALLPADIN               (CHIP_REG_BASE+0xA0)
    #define CHIP_ALLPAD_IN              (__BIT0)

#define CHIP_REG_DDCRMOD               (CHIP_REG_BASE+0xAE)

#define CHIP_REG_PLCD_IE1               (CHIP_REG_BASE+(0x4A*2))
#define CHIP_REG_PLCD_IE2               (CHIP_REG_BASE+(0x4A*2)+1)
	#define CHIP_PLCD_IE_D14            (__BIT6)
	#define CHIP_PLCD_IE_D15            (__BIT7)
//############################
//
//IP bank address : for independent port
//
//############################
//Standard mode
#define HWI2C_REG_BASE                  0 //(0x111800) //0x1(11800) + offset ==> default set to port 0
#define REG_HWI2C_MIIC_CFG              (HWI2C_REG_BASE+0x00*2)
    #define _MIIC_CFG_RESET             (__BIT0)
    #define _MIIC_CFG_EN_DMA            (__BIT1)
    #define _MIIC_CFG_EN_INT            (__BIT2)
    #define _MIIC_CFG_EN_CLKSTR         (__BIT3)
    #define _MIIC_CFG_EN_TMTINT         (__BIT4)
    #define _MIIC_CFG_EN_FILTER         (__BIT5)
    #define _MIIC_CFG_EN_PUSH1T         (__BIT6)
    #define _MIIC_CFG_RESERVED          (__BIT7)
#define REG_HWI2C_CMD_START             (HWI2C_REG_BASE+0x01*2)
    #define _CMD_START                  (__BIT0)
#define REG_HWI2C_CMD_STOP              (HWI2C_REG_BASE+0x01*2+1)
    #define _CMD_STOP                   (__BIT0)
#define REG_HWI2C_WDATA                 (HWI2C_REG_BASE+0x02*2)
#define REG_HWI2C_WDATA_GET             (HWI2C_REG_BASE+0x02*2+1)
    #define _WDATA_GET_ACKBIT           (__BIT0)
#define REG_HWI2C_RDATA                 (HWI2C_REG_BASE+0x03*2)
#define REG_HWI2C_RDATA_CFG             (HWI2C_REG_BASE+0x03*2+1)
    #define _RDATA_CFG_TRIG             (__BIT0)
    #define _RDATA_CFG_ACKBIT           (__BIT1)
#define REG_HWI2C_INT_CTL               (HWI2C_REG_BASE+0x04*2)
    #define _INT_CTL                    (__BIT0) //write this register to clear int
#define REG_HWI2C_CUR_STATE             (HWI2C_REG_BASE+0x05*2) //For Debug
    #define _CUR_STATE_MSK              (__BIT4|__BIT3|__BIT2|__BIT1|__BIT0)
#define REG_HWI2C_INT_STATUS            (HWI2C_REG_BASE+0x05*2+1) //For Debug
    #define _INT_STARTDET               (__BIT0)
    #define _INT_STOPDET                (__BIT1)
    #define _INT_RXDONE                 (__BIT2)
    #define _INT_TXDONE                 (__BIT3)
    #define _INT_CLKSTR                 (__BIT4)
    #define _INT_SCLERR                 (__BIT5)
    #define _INT_TIMEOUT                (__BIT6)
#define REG_HWI2C_STP_CNT               (HWI2C_REG_BASE+0x08*2)
#define REG_HWI2C_CKH_CNT               (HWI2C_REG_BASE+0x09*2)
#define REG_HWI2C_CKL_CNT               (HWI2C_REG_BASE+0x0A*2)
#define REG_HWI2C_SDA_CNT               (HWI2C_REG_BASE+0x0B*2)
#define REG_HWI2C_STT_CNT               (HWI2C_REG_BASE+0x0C*2)
#define REG_HWI2C_LTH_CNT               (HWI2C_REG_BASE+0x0D*2)
#define REG_HWI2C_TMT_CNT               (HWI2C_REG_BASE+0x0E*2)
#define REG_HWI2C_SCLI_DELAY            (HWI2C_REG_BASE+0x0F*2)
    #define _SCLI_DELAY                 (__BIT2|__BIT1|__BIT0)


//DMA mode
#define REG_HWI2C_DMA_CFG               (HWI2C_REG_BASE+0x20*2)
    #define _DMA_CFG_RESET              (__BIT1)
    #define _DMA_CFG_INTEN              (__BIT2)
    #define _DMA_CFG_MIURST             (__BIT3)
    #define _DMA_CFG_MIUPRI             (__BIT4)
#define REG_HWI2C_DMA_MIU_ADR           (HWI2C_REG_BASE+0x21*2) // 4 bytes
#define REG_HWI2C_DMA_CTL               (HWI2C_REG_BASE+0x23*2)
//    #define _DMA_CTL_TRIG               (__BIT0)
//    #define _DMA_CTL_RETRIG             (__BIT1)
    #define _DMA_CTL_TXNOSTOP           (__BIT5) //miic transfer format, 1: S+data..., 0: S+data...+P
    #define _DMA_CTL_RDWTCMD            (__BIT6) //miic transfer format, 1:read, 0:write
    #define _DMA_CTL_MIUCHSEL           (__BIT7) //0: miu0, 1:miu1
#define REG_HWI2C_DMA_TXR               (HWI2C_REG_BASE+0x24*2)
    #define _DMA_TXR_DONE               (__BIT0)
#define REG_HWI2C_DMA_CMDDAT0           (HWI2C_REG_BASE+0x25*2) // 8 bytes
#define REG_HWI2C_DMA_CMDDAT1           (HWI2C_REG_BASE+0x25*2+1)
#define REG_HWI2C_DMA_CMDDAT2           (HWI2C_REG_BASE+0x26*2)
#define REG_HWI2C_DMA_CMDDAT3           (HWI2C_REG_BASE+0x26*2+1)
#define REG_HWI2C_DMA_CMDDAT4           (HWI2C_REG_BASE+0x27*2)
#define REG_HWI2C_DMA_CMDDAT5           (HWI2C_REG_BASE+0x27*2+1)
#define REG_HWI2C_DMA_CMDDAT6           (HWI2C_REG_BASE+0x28*2)
#define REG_HWI2C_DMA_CMDDAT7           (HWI2C_REG_BASE+0x28*2+1)
#define REG_HWI2C_DMA_CMDLEN            (HWI2C_REG_BASE+0x29*2)
    #define _DMA_CMDLEN_MSK             (__BIT2|__BIT1|__BIT0)
#define REG_HWI2C_DMA_DATLEN            (HWI2C_REG_BASE+0x2A*2) // 4 bytes
#define REG_HWI2C_DMA_TXFRCNT           (HWI2C_REG_BASE+0x2C*2) // 4 bytes
#define REG_HWI2C_DMA_SLVADR            (HWI2C_REG_BASE+0x2E*2)
    #define _DMA_SLVADR_10BIT_MSK       0x3FF //10 bits
    #define _DMA_SLVADR_NORML_MSK       0x7F //7 bits
#define REG_HWI2C_DMA_SLVCFG            (HWI2C_REG_BASE+0x2E*2+1)
    #define _DMA_10BIT_MODE             (__BIT2)
#define REG_HWI2C_DMA_CTL_TRIG          (HWI2C_REG_BASE+0x2F*2)
    #define _DMA_CTL_TRIG               (__BIT0)
#define REG_HWI2C_DMA_CTL_RETRIG        (HWI2C_REG_BASE+0x2F*2+1)
    #define _DMA_CTL_RETRIG             (__BIT0)



#endif /*__KERNEL_I2C_H__*/
