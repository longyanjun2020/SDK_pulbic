#ifndef __KERNEL_DMA_H__
#define __KERNEL_DMA_H__

/************************************************/
/* DMA controller                               	*/
/************************************************/

typedef struct W5Dmac_s
{
	u32 u32_DMAH_SAR_l; 	 			// 0x00
	u32 u32_DMAH_SAR_h; 	 			// 0x04
	u32 u32_DMAH_DAR_l; 	 			// 0x08
	u32 u32_DMAH_DAR_h; 	 			// 0x0C
	u32 u32_DMAH_LLP_l; 	 			// 0x10
	u32 u32_DMAH_LLP_h; 	 			// 0x14
	u32 u32_DMAH_CTL_l; 	 			// 0x18
	u32 u32_DMAH_CTL_h; 	 			// 0x1C
	u32 u32_DMAH_SSTAT_l; 	 			// 0x20
	u32 u32_DMAH_SSTAT_h; 	 		// 0x24
	u32 u32_DMAH_DSTAT_l; 	 			// 0x28
	u32 u32_DMAH_DSTAT_h; 	 		// 0x2C
	u32 u32_DMAH_SSTATAR; 	 		// 0x30
	u32 u32_DMAH_SSTATAR_h; 	 		// 0x34
	u32 u32_DMAH_DSTATAR_l; 	 		// 0x38
	u32 u32_DMAH_DSTATAR_h; 	 		// 0x3C
	u32 u32_DMAH_CFG_l; 	 			// 0x40
	u32 u32_DMAH_CFG_h; 	 			// 0x44
	u32 u32_DMAH_SGR_l; 	 			// 0x48
	u32 u32_DMAH_SGR_h; 	 			// 0x4C
	u32 u32_DMAH_DSR_l; 	 			// 0x50
	u32 u32_DMAH_DSR_h; 	 			// 0x54
}  W5Dmac_t ;

/************************************************/
/* Dma                     */
/************************************************/
#define DW_dmac_DMAH_CH0_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x000)
#define DW_dmac_DMAH_CH1_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x058)
#define DW_dmac_DMAH_CH2_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x0b0)
#define DW_dmac_DMAH_CH3_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x108)
#define DW_dmac_DMAH_CH4_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x160)
#define DW_dmac_DMAH_CH5_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x1b8)
#define DW_dmac_DMAH_CH6_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x210)
#define DW_dmac_DMAH_CH7_START_ADDR              (DMAC_CFG_START_ADDRESS + 0x268)
#define DW_dmac_DMAH_COMMON_START_ADDR           (DMAC_CFG_START_ADDRESS + 0x2c0)

typedef struct W5Dma_s
{
	u32 p_sar;
	u32 unused1;
	u32 p_dar;
	u32 unused2;
	u32 p_llp;
	u32 unused3;
	u32 p_ctll;
	u32 p_ctlh;
	u32 p_sstat;
	u32 unused5;
	u32 p_dstat;
	u32 unused6;
	u32 p_sstatar;
	u32 unused7;
	u32 p_dstatar;
	u32 unused8;
	u32 p_cfgl;
	u32 p_cfgh;
	u32 p_sgr;
	u32 unused10;
	u32 p_dsr;
 } W5Dma_t;
 
		

typedef struct W5DmaCfg_s
{
	u32 p_rawftr;
	u32 unused1;
	u32 p_rawblock;
	u32 unused2;
	u32 p_rawsrctran;
	u32 unused3;
	u32 p_rawdsttran;
	u32 unused4;
	u32 p_rawerr;
	u32 unused5;
	u32 p_statustfr;
	u32 unused6;
	u32 p_statusblock;
	u32 unused7;
	u32 p_statussrctran;
	u32 unused8;
	u32 p_statusdsttran;
	u32 unused9;
	u32 p_statuserr;
	u32 unused10;
	u32 p_masktfr;
	u32 unused101;
	u32 p_maskblock;
	u32 unused102;
	u32 p_masksrctran;
	u32 unused103;
	u32 p_maskdsttran;
	u32 unused104;
	u32 p_maskerr;
	u32 unused105;
	u32 p_cleartfr;
	u32 unused11;
	u32 p_clearblock;
	u32 unused12;
	u32 p_clearsrctran;
	u32 unused13;
	u32 p_cleardsttran;
	u32 unused14;
	u32 p_clearerr;
	u32 unused15;
	u32 p_statusint;
	u32 unused16;
	u32 p_reqsrcreg;
	u32 unused17;
	u32 p_reqdstreg;
	u32 unused18;
	u32 p_sglrqsrcreg;
	u32 unused19;
	u32 p_sglrqdstreg;
	u32 unused20;
	u32 p_lstsrcreg;
	u32 unused21;
	u32 p_lstdstreg;
	u32 unused22;
	u32 p_dmacfgreg;
	u32 unused23;
	u32 p_chenreg;
	u32 unused24;
	u32 p_dmaidreg;
	u32 unused25;
	u32 p_dmatestreg;
	u32 unused26;
	u32 p_dmaversionid;
	u32 unused27;
 } W5DmaCfg_t;

extern volatile W5Dmac_t * const g_ptW5Dmac0;
extern volatile W5Dmac_t * const g_ptW5Dmac1;
extern volatile W5Dmac_t * const g_ptW5Dmac2;
extern volatile W5Dmac_t * const g_ptW5Dmac3;
extern volatile W5Dmac_t * const g_ptW5Dmac4;
extern volatile W5Dmac_t * const g_ptW5Dmac5;
extern volatile W5Dmac_t * const g_ptW5Dmac6;
extern volatile W5Dmac_t * const g_ptW5Dmac7;
extern volatile W5Dma_t * const g_ptW5Dma0;
extern volatile W5Dma_t * const g_ptW5Dma1;
extern volatile W5Dma_t * const g_ptW5Dma2;
extern volatile W5Dma_t * const g_ptW5Dma3;
extern volatile W5Dma_t * const g_ptW5Dma4;
extern volatile W5Dma_t * const g_ptW5Dma5;
extern volatile W5Dma_t * const g_ptW5Dma6;
extern volatile W5Dma_t * const g_ptW5Dma7;
extern volatile W5DmaCfg_t * const  g_ptW5DmaCfg;

#endif //__KERNEL_DMA_H__
