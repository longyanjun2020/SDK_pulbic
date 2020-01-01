#ifndef _LCD_COMMON_H_
#define _LCD_COMMON_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_typedef.h"
#include "mmp_err.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define LCD_WAIT(cnt)          MMPF_OS_Sleep_MS(cnt)
#define LCD_CMD(idx, cmd)      MMPD_LCD_SendIndexCommand(idx, cmd)
#define MAINLCD_CMD(idx)       MMPD_LCD_SendIndex(idx)
#define MAINLCD_DATA(cmd)      MMPD_LCD_SendCommand(cmd)

#define LCD_COMM_TIMEOUT (0x1000000)

//////////////////////////////////////////////////////////////////

#define DSPY_DECL                           AITPS_DSPY pDSPY = AITC_BASE_DSPY
#define DSPY_WR_B(reg, val)                    (*(AIT_REG_B *)((MMP_ULONG)&(pDSPY->##reg))) = ((MMP_UBYTE)(val))
#define DSPY_WR_W(reg, val)                    (*(AIT_REG_W *)((MMP_ULONG)&(pDSPY->##reg))) = ((MMP_USHORT)(val))
#define DSPY_WR_D(reg, val)                    (*(AIT_REG_D *)((MMP_ULONG)&(pDSPY->##reg))) = ((MMP_ULONG)(val))
#define DSPY_WR_OFST_B(reg, ofst, val)        (*(AIT_REG_B *)((MMP_ULONG)&(pDSPY->##reg) + ofst)) = ((MMP_UBYTE)(val))
#define DSPY_WR_OFST_W(reg, ofst, val)        (*(AIT_REG_W *)((MMP_ULONG)&(pDSPY->##reg) + ofst)) = ((MMP_USHORT)(val))
#define DSPY_WR_OFST_D(reg, ofst, val)        (*(AIT_REG_D *)((MMP_ULONG)&(pDSPY->##reg) + ofst)) = ((MMP_ULONG)(val))

#define DSPY_RD_B(reg)                        (MMP_UBYTE) (*(AIT_REG_B *)((MMP_ULONG)&(pDSPY->##reg)))
#define DSPY_RD_W(reg)                        (MMP_USHORT)(*(AIT_REG_W *)((MMP_ULONG)&(pDSPY->##reg)))
#define DSPY_RD_D(reg)                        (MMP_ULONG) (*(AIT_REG_D *)((MMP_ULONG)&(pDSPY->##reg)))
#define DSPY_RD_OFST_B(reg, ofst)            (MMP_UBYTE) (*(AIT_REG_B *)((MMP_ULONG)&(pDSPY->##reg) + ofst))
#define DSPY_RD_OFST_W(reg, ofst)            (MMP_USHORT)(*(AIT_REG_W *)((MMP_ULONG)&(pDSPY->##reg) + ofst))
#define DSPY_RD_OFST_D(reg, ofst)            (MMP_ULONG) (*(AIT_REG_D *)((MMP_ULONG)&(pDSPY->##reg) + ofst))

#define MEM_SET_W(addr, val)                   MMPH_HIF_MemSetW(addr, val)

#define WIN_OPR_OFST(_w)                    ((_w - LCD_DISP_WIN_PIP) * 0x100)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/* LCD Aspect Ratio  */
typedef enum _LCD_ASPECT_RATIO {
    LCD_RATIO_4_3 = 0,
    LCD_RATIO_16_9,
    LCD_RATIO_MAX
} LCD_ASPECT_RATIO;

/* LCD Rotate Direction  */
typedef enum _LCD_DIR {
    LCD_DIR_UPLEFT_DOWNRIGHT = 0,
    LCD_DIR_DOWNLEFT_UPRIGHT,
    LCD_DIR_UPRIGHT_DOWNLEFT,
    LCD_DIR_DOWNRIGHT_UPLEFT
} LCD_DIR;


/* Scan mode */
typedef enum _LCD_SCAN_MODE {
        LCD_SCAN_PROGRESS,
        LCD_SCAN_INTERLACED
} LCD_SCAN_MODE;


/* LCD Interface Type */
typedef enum _LCD_TYPE {
    LCD_TYPE_PLCD,          /// MCU interface
    LCD_TYPE_SLCD,          /// Serial RGB interface (8bit bus)
    LCD_TYPE_PLCD_FLM,      ///
    LCD_TYPE_RGBLCD,        ///Parallel interface
    LCD_TYPE_RGB2LCD,       ///not used
    LCD_TYPE_MIPIDSI,       //MIPI DSI (Display Serial Interface)
    LCD_TYPE_MIPICSI,       //MIPI CSI interface
    LCD_TYPE_CCIR601,       //CCIR601(8bit/16bit bus+Vsync+Hsync+Clock)
    LCD_TYPE_CCIR656,       //CCIR656(8bi)
    LCD_TYPE_MAX
} LCD_TYPE;

/* LCD Controller */
typedef enum _LCD_CONTROLER {
    LCD_PRM_CONTROLER,
    LCD_SCD_CONTROLER
} LCD_CONTROLER;

/* LCD Bus Width */
typedef enum _LCD_BUS_WIDTH {
    LCD_BUS_WIDTH_8,
    LCD_BUS_WIDTH_12,
    LCD_BUS_WIDTH_16,
    LCD_BUS_WIDTH_18,
    LCD_BUS_WIDTH_24
} LCD_BUS_WIDTH;

/* Idle Status */
typedef enum _LCD_POLARITY {
        LCD_POLARITY0,
        LCD_POLARITY1
} LCD_POLARITY;

/* Latch Data Edge */
typedef enum _LCD_PHASE {
        LCD_PHASE0,
        LCD_PHASE1
} LCD_PHASE;

/* MCU I/F system */
typedef enum _LCD_MCU_SYS {

        LCD_MCU_68SYS,
        LCD_MCU_80SYS
} LCD_MCU_SYS;

/* Output RGB Order */
typedef enum _LCD_RGB_ORDER {
        LCD_RGB_ORDER_RGB,
        LCD_RGB_ORDER_BGR
} LCD_RGB_ORDER;

/* Display Window */
typedef enum _LCD_DISP_WIN {

        LCD_DISP_WIN_MAIN = 0,
        LCD_DISP_WIN_PIP  = 1,
        LCD_DISP_WIN_OSD  = 3,
        LCD_DISP_WIN_OVLY = 4
} LCD_DISP_WIN;

/* Signal Polarity */
typedef enum _LCD_SIG_POLARITY {

        LCD_SIG_POLARITY_L,
        LCD_SIG_POLARITY_H
} LCD_SIG_POLARITY;

/* Signal Polarity */
typedef enum _LCD_SPI_PIX_ORDER {
        LCD_SPI_PIX_ORDER_RGB,
        LCD_SPI_PIX_ORDER_RBG,
        LCD_SPI_PIX_ORDER_GRB,
        LCD_SPI_PIX_ORDER_GBR,
        LCD_SPI_PIX_ORDER_BRG,
        LCD_SPI_PIX_ORDER_BGR
} LCD_SPI_PIX_ORDER;

/* Window color format */
typedef enum _LCD_WIN_FMT {
        LCD_WIN_FMT_4BPP,
        LCD_WIN_FMT_8BPP,
        LCD_WIN_FMT_16BPP,
        LCD_WIN_FMT_24BPP,
        LCD_WIN_FMT_YUV420,
        LCD_WIN_FMT_YUV422,
        LCD_WIN_FMT_32BPP
} LCD_WIN_FMT;

/* LCD Bus Width */
typedef enum _LCD_DATABUS_CFG {
        LCD_RGB888,
        LCD_RGB666,
        LCD_RGB565,
        LCD_RGB666_LOOSE_PACKED_MSB_ALIGN,
        LCD_RGB666_LOOSE_PACKED_LSB_ALIGN,
        LCD_RGB332,
        LCD_BGR888,
        LCD_BGR666,
        LCD_BGR565,
        LCD_BGR666_LOOSE_PACKED_MSB_ALIGN,
        LCD_BGR666_LOOSE_PACKED_LSB_ALIGN,
        LCD_BGR332,

        LCD_RGB888_SWAP,    //R7...R0, G7...G0, B7...B0
        LCD_RGB666_SWAP,
        LCD_RGB565_SWAP,
        LCD_RGB666_LOOSE_PACKED_MSB_ALIGN_SWAP,
        LCD_RGB666_LOOSE_PACKED_LSB_ALIGN_SWAP,
        LCD_RGB332_SWAP,
        LCD_BGR888_SWAP,
        LCD_BGR666_SWAP,
        LCD_BGR565_SWAP,
        LCD_BGR666_LOOSE_PACKED_MSB_ALIGN_SWAP,
        LCD_BGR666_LOOSE_PACKED_LSB_ALIGN_SWAP,
        LCD_BGR332_SWAP,
        LCD_SERIAL_RGB,
        /*CCIR 601 out*/
        LCD_YUV422_D16BIT_UY0_VY1,     //16 BIT mode

        LCD_YUV422_D16BIT_VY0_UY1,
        LCD_YUV422_D16BIT_UY1_VY0,
        LCD_YUV422_D16BIT_VY1_UY0,
        LCD_YUV422_D16BIT_Y0U_Y1V,
        LCD_YUV422_D16BIT_Y0V_Y1U,
        LCD_YUV422_D16BIT_Y1U_Y0V,
        LCD_YUV422_D16BIT_Y1V_Y0U,

        LCD_YUV422_UY0VY1,  //8 BIT mode
        LCD_YUV422_VY0UY1,
        LCD_YUV422_UY1VY0,
        LCD_YUV422_VY1UY0,

        LCD_YUV422_Y0UY1V,
        LCD_YUV422_Y0VY1U,
        LCD_YUV422_Y1UY0V,
        LCD_YUV422_Y1VY0U,
} LCD_DATABUS_CFG;

//============================================================================
// MCU DATA BUS LAYOUT
//============================================================================
// 8Bit 565 format (1pixel/2 cycles)
//  ______________2nd transfer_____________ ____________1st transfer_______________
// |______________________________________ |_______________________________________|
// | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
// |____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|
// ________________________________________________________________________________
// | R4 | R3 | R2 | R1 | R0 | G5 | G4 | G3 | G2 | G1 | G0 | B4 | B3 | B2 | B1 | B0 |
// |____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|
//

// 8Bit 332 format (1pixel/1 cycles)
//        ________________________                                              __________
//                                \____________________________________________/
//        ______________       _____      _____      _____      _________________
//                      \_____/     \____/     \____/     \____/
//D[17:8]  ______________<  xxxx   >-<  xxxx  >-<  xxxx  >_______________________________________________
//D[7:5]   ______________<  0000   >-<B1[2:0] >-<B2[2:0] >_______________________________________________
//D[4:2]   ______________<  0000   >-<G1[2:0] >-<G2[2:0] >_______________________________________________
//D[1:0]   ______________<  0000   >-<R1[1:0] >-<R2[1:0] >_______________________________________________

// 8Bit 444 format (2pixel/3 cycles)
//        ________________________                                              __________
//                                \____________________________________________/
//        ______________       _____      _____      _____      _________________
//                      \_____/     \____/     \____/     \____/
//D[17:8]  ______________<  xxxx   >-<  xxxx  >-<  xxxx  >-<  xxxx  >____________________________________
//D[7:4]   ______________<  0000   >-<G1[3:0] >-<R2[3:0] >-<B2[3:0] >____________________________________
//D[3:0]   ______________<  0000   >-<R1[3:0] >-<B1[3:0] >-<G2[3:0] >____________________________________


// 12Bit 444 format
//        ________________________                                              __________
//                                \____________________________________________/
//        ______________       _____      _____      _____      _________________
//                      \_____/     \____/     \____/     \____/
//D[17:12] ______________<  xxxx   >-<  xxxx  >-<  xxxx  >-<  xxxx  >____________________________________
//D[11:8]  ______________<  0000   >-<B1[3:0] >-<B2[3:0] >-<B3[3:0] >____________________________________
//D[7:4]   ______________<  0000   >-<G1[3:0] >-<G2[3:0] >-<G3[3:0] >____________________________________
//D[3:0]   ______________<  0000   >-<R1[3:0] >-<R2[3:0] >-<R3[3:0] >____________________________________

// 16Bit 444 format
//        ________________________                                              __________
//                                \____________________________________________/
//        ______________       _____      _____      _____      _________________
//                      \_____/     \____/     \____/     \____/
//D[17:12] ______________<  xxxx   >-<  xxxx  >-<  xxxx  >-<  xxxx  >____________________________________
//D[11:8]  ______________<  0000   >-<B1[3:0] >-<B2[3:0] >-<B3[3:0] >____________________________________
//D[7:4]   ______________<  0000   >-<G1[3:0] >-<G2[3:0] >-<G3[3:0] >____________________________________
//D[3:0]   ______________<  0000   >-<R1[3:0] >-<R2[3:0] >-<R3[3:0] >____________________________________

// 16Bit 565 format
//        ________________________                                              __________
//                                \____________________________________________/
//        ______________       _____      _____      _____      _________________
//                      \_____/     \____/     \____/     \____/
//D[17:16] ______________<  xxxx   >-<  xxxx  >-<  xxxx  >-<  xxxx  >____________________________________
//D[15:11] ______________<  0000   >-<B1[4:0] >-<B2[4:0] >-<B3[4:0] >____________________________________
//D[10:5]  ______________<  0000   >-<G1[5:0] >-<G2[5:0] >-<G3[5:0] >____________________________________
//D[4:0]   ______________<  0000   >-<R1[4:0] >-<R2[4:0] >-<R3[4:0] >____________________________________

typedef enum _PLCD_DATABUS_CFG {
    PLCD_RGB565_BUS16_CFG,                  //0x0000
    PLCD_RGB444_BUS16_CFG,                  //0x0001
    PLCD_RGB666_BUS16_CFG,                  //0x0002
    PLCD_RGB888_BUS8_CFG,                   //0x0003
    PLCD_RGB332_BUS8_CFG,                   //0x0004
    PLCD_RGB444_BUS8_CFG,                   //0x0005
    PLCD_RGB666_BUS8_CFG,                   //0x0006
    PLCD_RGB565_BUS8_CFG,                   //0x0007
    PLCD_RGB666_BUS18_CFG,                  //0x0008
    PLCD_RGB666_BUS18_9_9_CFG,              //0x0009
    PLCD_RGB666_BUS18_2_16_CFG,             //0x000A
    PLCD_RGB666_BUS18_16_2_CFG,             //0x000B
    PLCD_RGB24_BUS18_16_8_CFG,              //0x000C
    PLCD_RGB24_BUS18_8_16_CFG,              //0x000D
    PLCD_RGB18_BUS8_2_8_8_CFG,              //0x000E
    PLCD_RGB666_BUS8_2_7_CFG,               //
    PLCD_RGB444_B12_EXT_B16_CFG,            //

    PLCD_RGB444_B15_4_CFG,
    PLCD_RGBB9_9_17_CFG
} PLCD_DATABUS_CFG;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef void LcdInitSeqFunc(void);
typedef void LcdInitIdxCmdFunc(MMP_UBYTE);

typedef struct _MMPF_PANEL_ATTR {
    // Panel basic setting
    MMP_USHORT              usPanelW;
    MMP_USHORT              usPanelH;
    LCD_TYPE                ubDevType;
    LCD_CONTROLER           ubController;
    MMP_ULONG               ulBgColor;
    MMP_UBYTE               ubRatio;        ///LCD_ASPECT_RATIO

    //////////////////////////
    // MCU interface
    //////////////////////////
    // Panel initial sequence
    LcdInitSeqFunc*         pInitSeq;

    // Index/Cmd sequence
    LcdInitIdxCmdFunc*      pIdxCmdSeq;
    //////////////////////////
    // MCU interface Timing control
    //////////////////////////
                                                    //I80 Timing diagram (Low for CMD, HIGH for INDEX)

                                                    //============================================================================
                                                    //             _____________                                              __________
                                                    //nCS                       \____________________________________________/
                                                    //             ______________             ___________________________________________
                                                    //RS(A0)                     \___________/
                                                    //             ______________       _____      _____      _____      _________________
                                                    //nWR                        \_____/     \____/     \____/     \____/
                                                    //             _______________________________________________________________________
                                                    //nRD
                                                    //                            ___________  _________  _________
                                                    //Data[0:15]    _____________/   CMD     \/  INDEX  \/  INDEX  \______________________
                                                    //Data[0:8]                  \___________/\_________/\_________/
    LCD_BUS_WIDTH           ubBusWidth;
    LCD_DATABUS_CFG         ubBusCfg;
    LCD_PHASE               ubPhase;
    LCD_POLARITY            ubPolarity;
                                                    //PLCD_WE/PCLD_RD (PHA= ubPhase, POL=ubPolarity)
                                                    //=============================================
                                                    //                     ____      ____      ___
                                                    //PHA=1, POL=0________/    \____/    \____/
                                                    //                          ____      ____
                                                    //PHA=0, POL=0_____________/    \____/    \__
                                                    //            _____________      ____      ___
                                                    //PHA=1, POL=1             \____/    \____/
                                                    //            __________________      ____
                                                    //PHA=0, POL=1                  \____/    \____
    LCD_MCU_SYS             ubMCUSystem;            // I8080 or M8068 system
    MMP_USHORT              usRsLeadCsCnt;          // Cycle count of RS signal lead CS signal
    MMP_USHORT              usCsLeadRwCnt;          // Cycle count of CS signal lead WR/RD signal
    MMP_USHORT              usRwCycCnt;             // Cycle count of WR/RD signal high/low period
    LCD_RGB_ORDER           ubRgbOrder;             //



    //////////////////////////
    // RGB/CCIR interface
    //////////////////////////

    MMP_BOOL                bPartialDisp;           // unsed
    LCD_SIG_POLARITY        ubDclkPor;              //Dot clock polarity
    LCD_SIG_POLARITY        ubHsyncPor;             //Hsync polarity
    LCD_SIG_POLARITY        ubVsyncPor;             //Vsync polarity
    MMP_UBYTE               ubRgbFmt;               //

    MMP_ULONG               ulClkSelect;           //unit: MHz    E_LCD_TOP_CLK_SEL
    MMP_USHORT              usDotClkRatio;        // Stand for [(Lcd Freq / Dot Clock Freq) - 1] only used in MV2
    MMP_ULONG               ulDotClkFreq;          //unit: Hz

    MMP_USHORT              usHBPorch;            // Unit:pixel, Ragne:0~1023
    MMP_USHORT              usHBlanking;          // Unit:pixel, Range:0~1023
    MMP_USHORT              usHSyncW;             // Unit:pixel, Range:0~255
    MMP_USHORT              usVBPorch;            // Unit:line,  Range:0~1023
    MMP_USHORT              usVBlanking;          // Unit:line,  Range:0~1023
    MMP_USHORT              usVSyncW;             // Unit:line,  Range:0~255
    MMP_USHORT              usPRT2HdotClk;        // Unit:Dot Clock, Range:0~255

    //////////////////////////
    // Unused
    //////////////////////////
    MMP_USHORT              usPartStX;
    MMP_USHORT              usPartEndX;
    MMP_USHORT              usPartStY;
    MMP_USHORT              usPartEndY;
    //Serial RGB interface
    MMP_BOOL                bDeltaRBG;
    MMP_BOOL                bDummyRBG;
    LCD_SPI_PIX_ORDER       ubEvenLnOrder;
    LCD_SPI_PIX_ORDER       ubOddLnOrder;


    // RGB SPI interface
    //////////////////////////
    // Unused
    //////////////////////////

    MMP_USHORT              usSpi2MciRatio;        // Stand for [(MCI Freq / SPI Clock Freq) - 1]
    MMP_USHORT              usCsSetupCyc;        // Unit:MCI Clock, Range:0~15
    MMP_USHORT              usCsHoldCyc;        // Unit:MCI Clock, Range:0~15
    MMP_USHORT              usCsHighWidth;        // Unit:MCI Clock, Range:0~255
    MMP_USHORT              usSPIRegBitCnt;

    //////////////////////////
    // Unused
    //////////////////////////
    // Window setting (For drawing test pattern)

    LCD_DISP_WIN            ubDispWinId;
    MMP_USHORT              usWinStX;
    MMP_USHORT              usWinStY;
    MMP_USHORT              usWinW;
    MMP_USHORT              usWinH;
    MMP_USHORT              usWinBPP;
    LCD_WIN_FMT             usWinFmt;
    MMP_ULONG               ulWinAddr;


    // FLM setting
    //MMP_GPIO_PIN        ulFLMGPIO;

    PLCD_DATABUS_CFG        ubPlcdFmt;

    MMP_USHORT              usCCIR656_HBlanking;            // Unit:pixel, Range:0~1023
    MMP_USHORT              usCCIR656_VTopBlank;            // Unit:line,  Range:0~1023
    MMP_USHORT              usCCIR656_VBotBlank;            // Unit:line,  Range:0~1023
    LCD_SCAN_MODE           usCCIR656_Mode;                 // 0: Progress, 1: Interlace
    LCD_SIG_POLARITY        ubCCIR656ClkPor;               // Dot clock polarity
} MMPF_PANEL_ATTR;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

void MMPF_LCD_Write16BitCmd0(MMPF_PANEL_ATTR* pAttr, MMP_USHORT usData);
MMP_ERR MMPF_LCD_InitPanel(MMPF_PANEL_ATTR* pAttr);
MMP_ERR MMPF_LCD_DrawTestPattern(MMPF_PANEL_ATTR* pAttr);
MMP_USHORT MMPF_LCD_GetBestRatioH(MMP_UBYTE ubRatio, MMP_USHORT usWidth);

MMPF_PANEL_ATTR* RTNA_LCD_GetAttr(void);
void RTNA_LCD_Direction(LCD_DIR dir);
void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value);
void RTNA_LCD_GetReg(MMP_ULONG reg, MMP_ULONG *value);
void RTNA_LCD_AdjustBrightness(MMP_UBYTE level);
void RTNA_LCD_AdjustBrightness_R(MMP_UBYTE level);
void RTNA_LCD_AdjustBrightness_B(MMP_UBYTE level);
void RTNA_LCD_AdjustContrast(MMP_UBYTE level);
void RTNA_LCD_AdjustContrast_R(MMP_BYTE level);
void RTNA_LCD_AdjustContrast_B(MMP_BYTE level);

#endif //_LCD_COMMON_H_
