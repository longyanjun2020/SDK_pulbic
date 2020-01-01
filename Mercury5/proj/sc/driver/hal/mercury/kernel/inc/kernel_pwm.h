#ifndef __KERNEL_PWM_H__
#define __KERNEL_PWM_H__

/************************************************/
/* PWM: Pulse Width Modulation Interface        */
/************************************************/

//PWM offset,bank = 0x001A & 0x001B ,R/W 16-bits
#define PWM_CHANNEL_OFFSET 			0x20

#define PWM_REG_SHIFT_L				0x00
#define PWM_REG_SHIFT_H				0x01
#define PWM_REG_DUTY_L				0x02
#define PWM_REG_DUTY_H				0x03
#define PWM_REG_PERIOD_L			0x04
#define PWM_REG_PERIOD_H			0x05
#define PWM_REG_DIV					0x06
#define PWM_REG_VDBEN_SW			0x07
	#define PWM_REG_VDBEN_SW_OFS		0
	#define PWM_REG_VDBEN_SW_MASK		0x01
#define PWM_REG_DBEN				0x07
	#define PWM_REG_DBEN_OFS			1
	#define PWM_REG_DBEN_MASK			0x02
#define PWM_REG_DIFF_P_EN			0x07
	#define PWM_REG_DIFF_P_EN_OFS		2
	#define PWM_REG_DIFF_P_EN_MASK		0x04
#define PWM_REG_SHIFT_GAT			0x07
	#define PWM_REG_SHIFT_GAT_OFS		3
	#define PWM_REG_SHIFT_GAT_MASK		0x08
#define PWM_REG_POLARITY			0x07
	#define PWM_REG_POLARITY_OFS		4
	#define PWM_REG_POLARITY_MASK		0x10
#define PWM_REG_SHIFT2				0x08
#define PWM_REG_DUTY2				0x09
#define PWM_REG_SHIFT3				0x0A
#define PWM_REG_DUTY3				0x0B
#define PWM_REG_SHIFT4				0x0C
#define PWM_REG_DUTY4				0x0D

#define PWM_REG_SW_RST				0x7F	//bit0~7 maps to PWM0~7

#endif /*__KERNEL_PWM_H__*/
