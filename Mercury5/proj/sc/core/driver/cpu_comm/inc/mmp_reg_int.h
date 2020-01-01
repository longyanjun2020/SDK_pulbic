//==============================================================================
//
//  File        : mmp_register_int.h
//  Description : INCLUDE File for the Retina register map.
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_REG_INT_H_
#define _MMP_REG_INT_H_

/** @addtogroup MMPH_reg
@{
*/

#if (1)
//-----------------------------------------
// HINT structure (0x8000 6800)
//-----------------------------------------
typedef struct _AITS_HINT {
    AIT_REG_W   HINT_CTL;                                               // 0x00
        /*-DEFINE-----------------------------------------------------*/
		#define	HINT_INT_EN				0x01
		#define	HINT_HIGH_ASSERT		0x00
		#define	HINT_LOW_ASSERT			0x02
        /*------------------------------------------------------------*/
    AIT_REG_B  			_0x2[0xE];
    
    AIT_REG_D   HINT_EN;                                              	// 0x10	
        /*-DEFINE-----------------------------------------------------*/
		#define	HINT_VIF_INT			0x00000001
		#define	HINT_COLR_INT			0x00000002
		#define	HINT_JPG_INT			0x00000004
		#define	HINT_SCAL_INT			0x00000008
		#define	HINT_GRA_INT			0x00000010
		#define	HINT_IBC_INT			0x00000020
		#define	HINT_RAW_INT			0x00000040
		#define	HINT_CPU_INT			0x00000080
		
		#define	HINT_UART_INT			0x00000100
		#define	HINT_USB_INT			0x00001000
		#define	HINT_SDRAM_INT 			0x00002000
		#define	HINT_HDMI_PHY_INT 		0x00004000
		#define	HINT_WDA_INT 			0x00008000
		
		#define	HINT_GPIO_INT			0x00010000
		#define	HINT_I2CS_INT			0x00020000
		#define	HINT_SD_INT 			0x00040000
		#define	HINT_CCIR_INT		    0x00080000
		#define	HINT_I2S_TIMER_INT		0x00100000
		#define	HINT_H264_INT			0x00200000
		#define	HINT_AUDIOFIFO_INT		0x00400000
		#define	HINT_I2S_INT			0x00800000
		
		#define	HINT_I2CM_INT	    	0x01000000
		#define	HINT_PSPI_INT			0x02000000
		#define	HINT_IRDA_INT			0x04000000
		#define	HINT_PWM_INT			0x08000000
        #define	HINT_DMA_INT			0x10000000
        #define	HINT_GBL_INT			0x20000000
        #define	HINT_SM_INT 			0x40000000
        #define	HINT_SIF_INT 			0x80000000
        /*------------------------------------------------------------*/
    AIT_REG_D   HINT_SR;                                              	// 0x14
    AIT_REG_D   HINT_EN2;                                              	// 0x18
        /*-DEFINE-----------------------------------------------------*/
        #define	HINT_WDB_INT 			0x00000010
        #define	HINT_MCI_INT 			0x00000040
        #define	HINT_AFE_INT 			0x00000080
        
        #define	HINT_AFE_FIFO_INT 	    0x00000100
        #define	HINT_LCD_INT 			0x00000200
        #define	HINT_USB_EXDMA_INT 		0x00000800
        #define	HINT_CALI_INT 			0x00001000
        /*------------------------------------------------------------*/
    AIT_REG_D   HINT_STAT;                                              // 0x1C
    
    AIT_REG_B   HINT_SET_CPU_INT;                                       // 0x20
    AIT_REG_B   HINT_CLR_CPU_INT;                                       // 0x21       
        /*-DEFINE-----------------------------------------------------*/
        #define HINT_CPU2CPUB_INT       0x10
        #define HINT_CPU2CPUA_INT       0x20
        #define HINT_CPUB2HOST_INT      0x40
        #define HINT_CPUA2HOST_INT      0x80
        /*------------------------------------------------------------*/
} AITS_HINT, *AITPS_HINT;
#endif

/// @}

#endif // _MMP_REG_INT_H_
