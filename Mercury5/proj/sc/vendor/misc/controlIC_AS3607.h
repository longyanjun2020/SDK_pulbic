#ifndef _CONTROLIC_AS3607_H_
#define _CONTROLIC_AS3607_H_

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define    	AFE_SUB_MASK     	(0x7) /*mask for muxed registers                  */
#define 	IS_SUBREG(x)		((x >= AFE_MUX_PMU_REG1) && (x <= AFE_MUX_PMU_REG5))?1:0
#define    	AFE_PMU_ENABLE   	(0x1C)

//#define PMP_SWI2C_CLK_PIN			MMP_GPIO29
//#define PMP_SWI2C_DAT_PIN			MMP_GPIO30

#define I2C_AFE_SLAVE_ADDR		0x8C
#define PMP_R	1
#define PMP_W	0
#define AFE_SYSTEM       (0x20)
#define	AFE_SUB_BOOST_CTRL1		(0x1)
#define	AFE_SUB_BOOST_CTRL2		(0x2)
#define	AFE_SUB_BOOST_CURR1	(0x3)
#define	AFE_SUB_BOOST_CURR2	(0x4)
#define    AFE_MUX_PMU_REG5 (0x1B)
#define    AFE_MUX_PMU_REG1 (0x17)
#define AS3607_REG_MAX		(0x40)
#define AS3607_SUBREG_MAX	(0x07)

#define IS_SUBREG(x)	((x >= AFE_MUX_PMU_REG1) && (x <= AFE_MUX_PMU_REG5))?1:0
#define    AFE_CVDD         (AFE_MUX_PMU_REG1)
#define    AFE_SUB_DC_CTRL	(0x7)

/* defines for the used registers   */
#define    AFE_OUT_R        (0x02)
#define    AFE_OUT_L        (0x03)
#define    AFE_MIC_R        (0x06)
#define    AFE_MIC_L        (0x07)
#define    AFE_LINE_IN_R    (0x0A)
#define    AFE_LINE_IN_L    (0x0B)
#define    AFE_DAC_R        (0x0E)
#define    AFE_DAC_L        (0x0F)
#define    AFE_ADC_R        (0x10)
#define    AFE_ADC_L        (0x11)
#define    AFE_DAC_IF       (0x12)
#define    AFE_AUDIOSET1    (0x14)
#define    AFE_AUDIOSET2    (0x15)
#define    AFE_AUDIOSET3    (0x16)

// PMU Register

#define    AFE_MUX_PMU_REG2 (0x18)
#define    AFE_LDO          (AFE_MUX_PMU_REG2)
#define    AFE_MUX_PMU_REG3 (0x19)
#define    AFE_MUX_PMU_REG4 (0x1A)


#define	   AFE_PLL			(0x1A)

// System Register

#define    AFE_SUPERVISOR   (0x21)
#define    AFE_RAM_WAKE_UP  (0x22)
#define    AFE_IRQ_ENRD0    (0x23)
#define    AFE_IRQ_ENRD1    (0x24)
#define    AFE_IRQ_ENRD2    (0x25)
#define    AFE_IRQ_ENRD3    (0x26)
#define    AFE_IRQ_ENRD4    (0x27)
#define    AFE_RTC_CNTR     (0x28)
#define    AFE_RTC_TIME     (0x29)
#define    AFE_RTC_0        (0x2A)
#define    AFE_RTC_1        (0x2B)
#define    AFE_RTC_2        (0x2C)
#define    AFE_RTC_3        (0x2D)
#define    AFE_ADC_0        (0x2E)
#define    AFE_ADC_1        (0x2F)

// UID Register
#define    AFE_UID_0        (0x38)
#define    AFE_UID_1        (0x39)
#define    AFE_UID_2        (0x3A)
#define    AFE_UID_3        (0x3B)
#define    AFE_UID_4        (0x3C)
#define    AFE_UID_5        (0x3D)
#define    AFE_UID_6        (0x3E)
#define    AFE_UID_7        (0x3F)

#define    AFE_CHG_VBUS1    AFE_MUX_PMU_REG3
#define    AFE_PMU_MASTER   AFE_PMU_ENABLE

/* sub addresses for mux'ed registers */
#define    AFE_SUB_CVDD1	(0x1)
#define    AFE_SUB_CVDD2	(0x2)

#define    AFE_SUB_PVDD1	(0x1)   /*LDO3                                    */
#define    AFE_SUB_LDO3		(0x1)
#define    AFE_SUB_PVDD2	(0x2)   /*LDO4                                    */
#define    AFE_SUB_LDO4		(0x2)
#define    AFE_SUB_AVDD27	(0x6)   /*LDO2                                    */
#define    AFE_SUB_LDO2		(0x6)
#define    AFE_SUB_AVDD17	(0x7)   /*LDO1                                    */
#define    AFE_SUB_LDO1		(0x7)
#define    AFE_SUB_CHG1 	(0x1)
#define    AFE_SUB_CHG2 	(0x2)
#define    AFE_SUB_OUT1 	(0x1)
#define    AFE_SUB_OUT2 	(0x2)
#define    AFE_SUB_OUT3 	(0x3)
#define    AFE_SUB_DCDC15	(0x1)
#define    AFE_SUB_ISINK1	(0x2)
#define    AFE_SUB_ISINK2	(0x3)
#define    AFE_SUB_HIB  	(0x6)
#define    AFE_SUB_PLL  	(0x7)


#define	AFE_SUB_BOOST_ISINK1	(0x3)
#define	AFE_SUB_BOOST_ISINK2	(0x4)



//======================================================================================================
/* CONFIGURATION SECTION                                                      */

/* masks of level, edge and status change bits, interrupt bits are set to 1   */
#define AFE_IRQ_ENRD0_MASK  (0x0)
#define AFE_IRQ_ENRD1_MASK  (0x0)
#define AFE_IRQ_ENRD2_MASK  (0x97) /*!< bat temp., chg eoc, chg state changed
                                        usb state changed, rvdd low, bvdd low*/
#define AFE_IRQ_ENRD3_MASK  (0xBB) /*!< jtemp high, hp overcurr., i2s status,
                                        i2s changed, mic conn., hp conn     */
#define AFE_IRQ_ENRD4_MASK  (0x07) /*!< adc eoc, rtc update, remote det.    */

#define AFE_IRQ_FIRST   AFE_IRQ_ENRD0
#define AFE_IRQ_LAST    AFE_IRQ_ENRD4

/* the first and the last irq status register (needed by afe base driver)   */
#define AFE_IRQ_STATUS_FIRST    AFE_IRQ_FIRST
#define AFE_IRQ_STATUS_LAST     AFE_IRQ_LAST
/* the first and the last irq mask register (needed by afe base driver)     */
#define AFE_IRQ_MASK_FIRST  	AFE_IRQ_FIRST
#define AFE_IRQ_MASK_LAST   	AFE_IRQ_LAST

/*number of interrupt registers                                              */
#define AFE_INT_REGISTERS_NO            (0x5)

/*define boundary of last shadowed register address                          */
#define     AFE_SHADOWED_BOUNDARY   (AFE_AUDIOSET3 + 1)

/* END OF CONFIGURATION SECTION                                              */



#define ADC_NO_SOURCE		(-1)
#define ADC_SOURCE_NO_LSB	(-2)
#define ADC_INVALID_SOURCE	(-3)
#define ADC_MAX_SOURCES		(0x10)

#define ADC_CFG_SRC_REG         (AFE_ADC_0)
#define ADC_CFG_SRC_LSB         (4)
#define ADC_CFG_SRC_MASK        (0xF << ADC_CFG_SRC_LSB)
#define ADC_CFG_MSB_MASK        (0x3)
#define ADC_CFG_MSB_POS         (8)
#define ADC_CFG_LSB_MASK        (0xFF)
#define ADC_CFG_RES_LSB_REG     (AFE_ADC_1)
#define ADC_CFG_RES_MSB_REG     (AFE_ADC_0)
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef enum
{
    ADC_SRC_ADC_VSUB         	= 0,    
    ADC_SRC_ADC_GPIO3         	= 1, 
    ADC_SRC_ADC_GPIO4         	= 2,  
    ADC_SRC_ADC_VBATSW     		= 3,   
    ADC_SRC_ADC_VUSB     		= 4,   
    ADC_SRC_ADC_DCTEST     		= 5,   
    ADC_SRC_ADC_BATTEMP     	= 6,   
    ADC_SRC_ADC_GPIO1    		= 7,  
    ADC_SRC_ADC_GPIO2    		= 8,   
    ADC_SRC_ADC_PWRUP   		= 9,    
    ADC_SRC_ADC_RESERVED1   	= 10,   
    ADC_SRC_ADC_RESERVED2    	= 11,  
    ADC_SRC_ADC_VBE1UA   		= 12,   
    ADC_SRC_ADC_VBE2UA   		= 13,  
    ADC_SRC_ADC_RESERVED3      	= 14,
    ADC_SRC_ADC_RESERVED4      	= 15
} eAdc_source_t;


//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR adcMeasure(eAdc_source_t src, MMP_USHORT* result);
void afe_system_off(void);
void afe_backlight_off(void);
void afeInitBacklight(void);
void afeSetBacklight(MMP_ULONG level);
void afeInitCharger(void);
void afeAdjustVoltage(void);

#endif