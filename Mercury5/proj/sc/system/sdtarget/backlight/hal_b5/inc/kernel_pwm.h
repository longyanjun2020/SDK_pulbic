#ifndef __KERNEL_PWM_H__
#define __KERNEL_PWM_H__

/************************************************/
/* PWM: Pulse Width Modulation Interface                 	*/
/************************************************/	

typedef struct KePwm_s {
    u32 u32_pwm0_cfg0; //
    u32 u32_pwm0_cfg1; //
    u32 u32_pwm1_cfg0; //
    u32 u32_pwm1_cfg1; //
    u32 u32_pwm2_cfg0; //
    u32 u32_pwm2_cfg1; //
    u32 u32_pwm3_cfg0; //
    u32 u32_pwm3_cfg1; //
    u32 u32_spare; //  
} KePwm_t;

#define PWM_CFG0_PWMP_POS 0 ///< 1st prescaler division factor for PWM0  [Fprescaler = F / (PWMP+1)]
#define PWM_CFG0_PWMP_MSK (0xFF<<PWM_CFG0_PWMP_POS)

#define PWM_CFG0_CLKSEL_POS 8 ///< Prescaler input frequency for PWM0, 0 : 13MHz	1 : 32kHz
#define PWM_CFG0_CLKSEL_MSK (1<<PWM_CFG0_CLKSEL_POS)
#define PWM_CFG0_EN_POS 12 ///< PWM0 enable, 0 : disabled	1 : enabled
#define PWM_CFG0_EN_MSK (1<<PWM_CFG0_EN_POS)

#define PWM_CFG1_PERIOD_POS 0 ///< 2nd prescaler division factor for PWM0  [F = Fprescaler/PERIOD](PERIOD = 0 generates no frequency)
#define PWM_CFG1_PERIOD_MSK (0xFF<<PWM_CFG1_PERIOD_POS)
#define PWM_CFG1_RATIO_POS 8 ///< high/low ratio, high level = RATIO/PERIOD, low level = (PERIOD-RATIO)/PERIOD
#define PWM_CFG1_RATIO_MSK (0xFF<<PWM_CFG1_RATIO_POS)
#define PWM_CFG1_CYCLE0_POS 16 ///< number of non inverted cycles
#define PWM_CFG1_CYCLE0_MSK (0xFF<<PWM_CFG1_CYCLE0_POS)
#define PWM_CFG1_CYCLE1_POS 24 ///< number of inverted cycles
#define PWM_CFG1_CYCLE1_MSK (0xFF<<PWM_CFG1_CYCLE1_POS)

extern volatile KePwm_t * const g_ptKePwm;

#endif /*__KERNEL_PWM_H__*/
