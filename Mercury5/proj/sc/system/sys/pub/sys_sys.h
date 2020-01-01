/**
 * \file SYS_SYS.H
 * \brief System utilities interface
*/
/****************************************************************************/

#ifndef __SYS_SYS_H__
#define __SYS_SYS_H__

#include "stdcomp.h"
#include "msgtyp.ht"
#include "msgofs.hc"

//#include "kernel.h" //don't include hal header here

#include "sys_sys_vm_sys.h"
#include "sys_sys.h"
#include "vm_app.ho"
#include "sys_sys_init.h"
#include "sys_sys_scf.h"
#include "sys_traces.ho"
#ifndef __SDK_SIMULATION__
#include "drv_clkgen_cmu.h"
#include "drv_rtc.h"
#endif//ndef __SDK_SIMULATION__
#include "drv_timer_types.h"
#include "drv_timer_api.h"

/**
 * RAM area macros
 */

#define CUSTOMER_RAM_SIZE_32K      	    0x8000 		/* 32 Kbytes */
#define CUSTOMER_RAM_SIZE_64K           0x10000 	/* 64 Kbytes */
#define CUSTOMER_RAM_SIZE_128K          0x20000 	/* 64 Kbytes */
#define TOTAL_RAM_SIZE_512K             0x80000 	/* 512 Kbytes */

#define RAM_SIZE_2M                     0x40000  	/* 2 Mbits - 256 Kbytes */
#define RAM_SIZE_4M                     0x80000  	/* 4 Mbits - 512 Kbytes */
#define RAM_SIZE_8M                     0x100000 	/* 8 Mbits - 1024 Kbytes */
#define RAM_SIZE_16M                    0x200000 	/* 16 Mbits - 2048 Kbytes */
#define RAM_SIZE_32M                    0x400000 	/* 32 Mbits - 4096 Kbytes */

/**
 * Stack back trace
 */

#define SYS_BACK_TRACE_MAX      	    15
#define SYS_BACK_TRACE_PATTERN  	    0x01060B00
#define SYS_DATATION_PATTERN    	    0x02070C01
#define SYS_MSG_DUMP_PATTERN    	    0x03080D02
#define SYS_INFO_HWL_PATTERN    	    0x04090E03
#define SYS_ADS_BACK_TRACE_PATTERN  	0x050a0f04
#define SYS_INFO_HWL_EXT_PATTERN      0x070c1106


/**
 * Memory protection macros
 */



#define SYS_MEM_PROT_SUSPEND(Space)
#define SYS_MEM_PROT_RESTORE(Space)


#define SYS_MEM_PROT_FLASH_SPACE    	0
#define SYS_MEM_PROT_RTK_AREA_SPACE 	1
#define SYS_MEM_PROT_WAVECOM_RAM    	2
#define SYS_MEM_PROT_FREE_SPACE2    	3

/**
 * ExtendedCapability management
 */

#define EXT_CAP_SIM5V_EXT          	    (1<<0)
#define EXT_CAP_TXP_FOI_BIAS       	    (1<<1)
#define EXT_CAP_DYN_LNA_PAR        	    (1<<2)
#define EXT_CAP_MIRROR             	    (1<<3)
#define EXT_CAP_GAIN_MIC_ONEC_V11  	    (1<<4)
#define EXT_CAP_IMMEDIAT_SUSP      	    (1<<5)
#define EXT_CAP_BATT_ENABLE        	    (1<<6)
#define EXT_CAP_GET_ABNORMAL_RST   	    (1<<7)
#define EXT_CAP_SIM_SHIFT_POLARITY 	    (1<<8)
#define EXT_CAP_FR_ERROR_CORRECTION 	(1<<9)

/**
 * ExtendedCapability management
 */

#define  SYS_SPEED_PROFILE_SLOW   VM_SYS_SPEED_PROFILE_SLOW
#define  SYS_SPEED_PROFILE_MEDIUM VM_SYS_SPEED_PROFILE_MEDIUM
#define  SYS_SPEED_PROFILE_FAST   VM_SYS_SPEED_PROFILE_FAST

#define  SPEED_PROFILE_ID_STACK   VM_SPEED_PROFILE_ID_STACK
#define  SPEED_PROFILE_ID_APPLI   VM_SPEED_PROFILE_ID_APPLI

#define  SPEED_PROFILE_TARGET_CPU VM_SPEED_PROFILE_TARGET_CPU
#define  SPEED_PROFILE_TARGET_DSP VM_SPEED_PROFILE_TARGET_DSP

/**
 * \brief GPRS capabilties
 */
#define EXT_CAP_NO_NEAR_SI_IN_TRANSFER 	(1<<12)
#define EXT_CAP_NO_MAIN_SI_IN_TRANSFER 	(1<<13)

extern u32 sys_ExtendedCapability;

#define SYS_IS_ACTIVATED(x)       	    ((sys_ExtendedCapability & x) != FALSE)

/**
 * \brief macros to get status of SYS INFO listening during TBF in GPRS
 */
#define SYS_NEAR_SI_IN_TRANSFER         (!(sys_ExtendedCapability & EXT_CAP_NO_NEAR_SI_IN_TRANSFER))
#define SYS_MAIN_SI_IN_TRANSFER         (!(sys_ExtendedCapability & EXT_CAP_NO_MAIN_SI_IN_TRANSFER))

/**
 * user defined variables
 */

typedef void (*fct_pointer)(void);

extern fct_pointer NullHandler;


u8   sys_Random(u8 Max);
void sys_DelayWatchDogReset(void);


bool sys_CustomIdleProc(void); //Handle RX cmd only
void sys_CustomIdleProc2(void); //Handle the rest of idle hook functions
void sys_CustomIdleStart(void);
void sys_CustomInitProc(int argc, char **argv);
void sys_CustomFrameIntProc(u16 NbSleepedFrames);



/**
 * primitive of messages
 */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "sys_sys_message_define__.hi"
};

/**
 * Wait loop macros
 */
/**
 * \brief RTC step is 30.5us
 * So unit choosen is us
 * be carefull : value must be at least 30us
 */
#ifdef __TARGET__
#define SYS_UDELAY(T) DrvTimerUdelay(T)
#define SYS_UDELAYCOND(Cond,T) DrvTimerUdelayCond(Cond, T)
#define SYS_GETTICK() RtkGetOsTick()
#else //__TARGET__
#define SYS_UDELAY(T)          	do { u32 rtcTimeOut=T*1000; \
				                while(rtcTimeOut--);} while(0)
#define SYS_UDELAYCOND(Cond,T) 	do { u32 rtcTimeOut=T*1000; \
				                while(rtcTimeOut-- && Cond);} while(0)
#endif //__TARGET__


/**
 * \brief  get MP flag utility func
 */
u8 SysGetMPFlag(void);

/**
 * \brief  add interface for IPCP utility func
 */
void sys_ParseIPCPOpt(u8 *Buf, u16 Len, vm_sys_ipcp_params_t *result);

/**
 * \brief Reversed Byte Table
 */
extern const u8 sys_ReversedByteTable[256];

/**
 * \brief DEFINES
 */
/**
 * \brief sys_OpenFcs() parameters
 */
/**
 * \brief Polynomial Generator
*/
#define SYS_PG_1BBA1B5                    0x00BBA1B5  /* for LLC, RLP...         */
#define SYS_PG_11021                      0x1021      /* for FAX, IRDA, PPP...   */
#define SYS_PG_18005                      0x8005      /* for MNP2...             */
/**
 * \brief Polynomial Generator Degree
 */
#define SYS_DEGREE_PG_1BBA1B5             23
#define SYS_DEGREE_PG_11021               15
#define SYS_DEGREE_PG_18005               15
/**
 * \brief ReverseInputData
 */
#define SYS_DO_NOT_REVERSE_INPUT_DATA     0
#define SYS_REVERSE_INPUT_DATA            1

/**
 * \brief System timer watch dog control length
 */
#define SYS_TIMER_WDOGCTRL_LEN_MAX	0xFFF
#define SYS_TIMER_WDOGCTRL_LEN 		0x800
extern volatile u32 SysTimerWdogctrlLen;

/**
 * \brief PROTOTYPES
 */
u32 sys_ComputeFcs (u8 *, u16, u32, u32, u8, bool);
void sys_OpenFcs (u32, u32, u8, bool);
u32 sys_CloseFcs (void);

/**
 * \brief MACROS
 */
#define SYS_GET_CUS_TASK_ID(CusTaskNumber)  (cus_NbTask - vm_apmNbApplicationTasks + CusTaskNumber - 1)
#define SYS_GET_CUS_TASK_NUMBER(CusTaskId)  (CusTaskId - cus_NbTask + vm_apmNbApplicationTasks + 1)

#endif /* __SYS_HO__ */
#ifdef __LOGIC_ANALYSER__
#define UP_GPIO(X) g_ptKeGpio->u32_DataOut0 = X | g_ptKeGpio->u32_DataIn0;
#define DOWN_GPIO(X) g_ptKeGpio->u32_DataOut0 = ~(X)& g_ptKeGpio->u32_DataIn0;
//warning : GPIO 15 is reserved for IT
#define	NONE			GPIO_DATA0_GPIO0_MSK
#define	MDL_GPIO		NONE					//
#define FMS_W_GPIO  	NONE
#define FINT_GPIO		1//GPIO_DATA0_GPIO16_MSK
#define PRCS_FINT_GPIO	2//GPIO_DATA0_GPIO07_MSK
#define SLEEP_GPIO		GPIO_DATA0_GPIO6_MSK
#define POLLRXTX_GPIO	NONE        //GPIO_DATA0_GPIO7_MSK
#define RTC_INIT_GPIO GPIO_DATA0_GPIO7_MSK
#define RXFULL_GPIO		NONE					//GPIO_DATA0_GPIO8_MSK
#define TXEMPTY_GPIO	NONE					//GPIO_DATA0_GPIO22_MSK
#define V24_ISR_GPIO	GPIO_DATA0_GPIO21_MSK	//GPIO_DATA0_GPIO21_MSK
#define POINT_BLANK_1	NONE
#define POINT_BLANK_2	NONE
#define POINT_BLANK_3	NONE
/**************************************************
 * \brief Put the whole D0-D15 signal down
 * \return nothing
 ****************************************************/
void	sys_reset_all_signal(void);
/**************************************************
 * \brief Put the whole D0-D15 signal high
 * \return nothing
 ****************************************************/
void	sys_set_all_signal(void);
/**************************************************
 * \brief This functions set the GPIO gpio_number while resetting all the
 *          others.
 *\param  number of the signal (from D0 to D15)
 * \return nothing
 ****************************************************/
void	sys_set_only_signal_n(u8);
/**************************************************
 * \brief This functions reset the GPIO gpio_number while resetting all the
 *          others.
 *\param  number of the signal (from D0 to D15)
 * \return nothing
 ****************************************************/
void	sys_reset_only_signal_n(u8);
/**************************************************
 * \brief This functions set the data bit signal_number
  *\param  number of the signal (from D0 to D15)
 * \return nothing
 ****************************************************/
void	sys_set_signal_n(u8);

/**************************************************
 * \brief This functions reset the data bit signal_number
 *\param  number of the signal (from D0 to D15)
 * \return nothing
 ****************************************************/
void	sys_reset_signal_n(u8);
/**************************************************
 * \brief This functions codes a char on the data bus. The first bit is
 *           in start_bit value
 * \ waring : it does not preserve the signal state
 *\param  value to code and first bit's place
 * \return nothing
 ****************************************************/
void	sys_codes_value_on_signal(u8 , u8 );
/**************************************************
 * \brief This functions tests all the signal. when launching, a "pyramid"
 *          Signal should MUST appear on the output
 *\param  nothing
 * \return nothing
 ****************************************************/
void	sys_test_pyramid(void);

#endif  // __SYS_SYS_H__

