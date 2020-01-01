#include "includes_fw.h"
#if BIND_MOTOR_R2A30440NP

#include "mmpf_pio.h"
#include "OS_Wrap.h"
#include "mmp_lib.h"
#include "R2A30440NP.h"
#include "MotorCtrlFunc.h"
#include "mmpf_timingmark.h"
#include "ahc_general.h"
#include "MotorCtrlTask.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================
extern void ZoomMotor_Step_ISR(void);
extern void FocusMotor_Step_ISR(void);
//extern void ZoomMotor_PR_ISR(void);
//extern void FocusMotor_PR_ISR(void);
MMP_UBYTE R2A30440NP_RegRead(MMP_UBYTE ch, MMP_UBYTE reg, MMP_UBYTE ch_rd, MMP_UBYTE BitSize);
void R2A30440NP_RegWrite(MMP_UBYTE ch, MMP_UBYTE reg, MMP_USHORT wdata);
void R2A30440NP_SetPICallBack(MMP_GPIO_PIN piopin, GpioCallBackFunc *CallBackFunc );


//==============================================================================
//
//                              DEFINITION
//
//==============================================================================
#define   MT_SPI_CLK                   LENS_MOTOR_DRV_MT_SPI_CLK 
#define   MT_SPI_DATA                  LENS_MOTOR_DRV_MT_SPI_DATA
#define   MT_SPI_CS                    LENS_MOTOR_DRV_MT_SPI_CS
#define   MT_RESET                     LENS_MOTOR_DRV_MT_RESET   
#define   MT_MOB1                      LENS_MOTOR_DRV_MT_MOB1    
#define   MT_MOB2                      LENS_MOTOR_DRV_MT_MOB2    
#define   MT_EXT1                      LENS_MOTOR_DRV_MT_EXT1
#define   MT_EXT2                      LENS_MOTOR_DRV_MT_EXT2
#define   F_OUT                        LENS_MOTOR_DRV_F_OUT      
#define   Z_OUT                        LENS_MOTOR_DRV_Z_OUT
#if (ENABLE_MOTOR_DRV_POWER_CTRL)
#define   MT_POW_EN                    LENS_MOTOR_DRV_MT_POW_EN
#endif

//#define TH_OUT         MMP_GPIO86
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
MMP_UBYTE   ubZoomDir = DRV_FORWARD;
MMP_UBYTE   ubFocusDir = DRV_FORWARD;
MMP_USHORT  usVal_PSPI = 0;
MMP_UBYTE   ubZoomPower = 0;
MMP_UBYTE   ubFocusPower = 0;
MMP_USHORT  usZoomMaxSpdAcc;

static MMPF_OS_SEMID m_MotorRegSemID = 0xFF;

void R2A30440NP_Wait_ticks(MMP_USHORT usTicks)
{
    while(usTicks--);
}

void R2A30440NP_Reset(void)
{
    MMPF_PIO_SetData(MT_RESET, GPIO_LOW, MMP_TRUE);
    R2A30440NP_Wait_ticks(100);
    MMPF_PIO_SetData(MT_RESET, GPIO_HIGH, MMP_TRUE);
}

void R2A30440NP_GPIO_Setting(void)   
{    
    MMPF_PIO_EnableOutputMode(MT_SPI_CS, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_SPI_CS, GPIO_HIGH, MMP_TRUE);
    
    MMPF_PIO_EnableOutputMode(MT_SPI_CLK, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);
    
    MMPF_PIO_EnableOutputMode(MT_SPI_DATA, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_SPI_DATA, GPIO_LOW, MMP_TRUE);
    
    MMPF_PIO_EnableOutputMode(MT_RESET, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_RESET, GPIO_LOW, MMP_TRUE);
    
    MMPF_PIO_EnableOutputMode(MT_EXT1, MMP_FALSE, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(MT_EXT2, MMP_FALSE, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(F_OUT, MMP_FALSE, MMP_TRUE); 
    MMPF_PIO_EnableOutputMode(Z_OUT, MMP_FALSE, MMP_TRUE); 

//  MMPF_PIO_EnableTrigMode(Z_OUT, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
//  MMPF_PIO_EnableTrigMode(Z_OUT, GPIO_L2H_EDGE_TRIG, MMP_TRUE, MMP_TRUE);

    if ((MT_MOB1 >= MMP_LGPIO0) && (MT_MOB1 <= MMP_LGPIO30))
    {
        MMPF_PIO_EnableOutputMode(MT_MOB1,MMP_FALSE,MMP_TRUE);
    }
  
    MMPF_PIO_EnableTrigMode(MT_MOB1, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_EnableTrigMode(MT_MOB2, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);

#if 0
    MMPF_PIO_EnableTrigMode(MT_MOB2, GPIO_L2H_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_EnableInterrupt(MT_MOB2, MMP_TRUE, 0, (GpioCallBackFunc *)MOB3_Called, MMP_TRUE);
#endif    

    MMPF_PIO_EnableInterrupt(MT_MOB2, MMP_TRUE, 0, (GpioCallBackFunc *)ZoomMotor_Step_ISR, MMP_TRUE);
#if 1
    MMPF_PIO_EnableInterrupt(MT_MOB1, MMP_TRUE, 0, (GpioCallBackFunc *)FocusMotor_Step_ISR, MMP_TRUE);
#else
    MMPF_PIO_EnableInterrupt(MT_MOB2, MMP_TRUE, 0, (GpioCallBackFunc *)MOB2_Called, MMP_TRUE);
    
#endif
//  MMPF_PIO_EnableInterrupt(Z_OUT  , MMP_TRUE, 0, (GpioCallBackFunc *)ZoomMotor_PR_ISR, MMP_TRUE);
//  MMPF_PIO_EnableInterrupt(F_OUT  , MMP_TRUE, 0, (GpioCallBackFunc *)FocusMotor_PR_ISR, MMP_TRUE);



}


MMP_USHORT R2A30440NP_PowerState(MMP_UBYTE ubCh, MMP_BOOL bOnOff)
{
#if 1
    if( MMP_TRUE == bOnOff )
        usVal_PSPI |= DRV_PS_STATE(ubCh);
    else
        usVal_PSPI &= ~(DRV_PS_STATE(ubCh));

    if( 0 == (usVal_PSPI&DRV_PS_STATE(PS_CH12)) &&
		0 == (usVal_PSPI&DRV_PS_STATE(PS_CH34)) )
        usVal_PSPI &= ~(DRV_PS_STATE(PS_EN_IC));
    else
        usVal_PSPI |= DRV_PS_STATE(PS_EN_IC);

#endif
    return usVal_PSPI;
}

MMP_BOOL R2A30440NP_ZoomDetectPR()
{
    MMP_UBYTE  ubVal = 0;
    
    MMPF_PIO_GetData(Z_OUT, &ubVal);

#if MOTOR_PI_INVERT
    if(ubVal) 
		return MMP_FALSE;
    else
        return MMP_TRUE;
#else
    if(ubVal) 
		return MMP_TRUE;
    else
        return MMP_FALSE;
#endif
}

void R2A30440NP_ZoomEnablePR(MMP_BOOL OnOff)
{

    if( MMP_TRUE == OnOff )
        usVal_PSPI |= DRV_PI2_CTRL(DRV_PI_ON);
    else
        usVal_PSPI &= ~(DRV_PI2_CTRL(DRV_PI_ON));

    R2A30440NP_RegWrite(REG_COMMON, REGC_PI_PS_SETUP , usVal_PSPI );
}

void R2A30440NP_ZoomEnableExcite(MMP_BOOL OnOff)
{
    MMP_UBYTE ubOn = OP_DISABLE;

    if( MMP_TRUE == OnOff )
        ubOn = OP_ENABLE;

    R2A30440NP_RegWrite(REG_CH34, REG_OP_CTRL   , OP_CTRL_EN(OP_DISABLE)           |
                                                  OP_CTRL_EXT_EN(ubOn)             | 
                                                  OP_CTRL_CONT_OP(CONT_OP_DISABLE) | 
                                                  OP_CTRL_VD_STOP(OP_DISABLE)      |
                                                  OP_CTRL_DIR(DRV_FORWARD)  );
}

MMP_BOOL R2A30440NP_FocusDetectPR(void)
{
    MMP_UBYTE  ubVal = 0;
    
    MMPF_PIO_GetData(F_OUT, &ubVal);

#if MOTOR_PI_INVERT
    if(ubVal) 
		return MMP_FALSE;
    else
        return MMP_TRUE;
#else

    if(ubVal) 
		return MMP_TRUE;
    else
        return MMP_FALSE;
#endif
}


void R2A30440NP_FocusEnablePR(MMP_BOOL OnOff)
{
    if( MMP_TRUE == OnOff )
        usVal_PSPI |= DRV_PI1_CTRL(DRV_PI_ON);
    else
        usVal_PSPI &= ~(DRV_PI1_CTRL(DRV_PI_ON));

    R2A30440NP_RegWrite(REG_COMMON, REGC_PI_PS_SETUP , usVal_PSPI );
}

void R2A30440NP_FocusEnableExcite(MMP_BOOL OnOff)
{
    MMP_UBYTE ubOn = OP_DISABLE;

    if( MMP_TRUE == OnOff )
        ubOn = OP_ENABLE;

    R2A30440NP_RegWrite(REG_CH12, REG_OP_CTRL   , OP_CTRL_EN(OP_DISABLE)           |
                                                  OP_CTRL_EXT_EN(ubOn)             | 
                                                  OP_CTRL_CONT_OP(CONT_OP_DISABLE) | 
                                                  OP_CTRL_VD_STOP(OP_DISABLE)      |
                                                  OP_CTRL_DIR(DRV_FORWARD)  );

}

void R2A30440NP_SetPICallBack(MMP_GPIO_PIN piopin, GpioCallBackFunc *CallBackFunc )
{
    MMPF_PIO_EnableInterrupt(piopin, MMP_TRUE, 0, (GpioCallBackFunc *)CallBackFunc, MMP_TRUE);
}

void R2A30440NP_Initialize(void)
{
    MMP_USHORT ps_val= 0;
    if( 0xFF == ( m_MotorRegSemID = MMPF_OS_CreateSem(1) ))
    {
        printc("motor sem create error!!\n");
        return;
    }

	#if (USE_PWM_AS_MOTOR_OSC) //PWM (clock for Motor)
    AHC_SetPWMforMotor();
    #endif
	
  #if (ENABLE_MOTOR_DRV_POWER_CTRL)
    MMPF_PIO_EnableOutputMode(MT_POW_EN, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MT_POW_EN, GPIO_HIGH, MMP_TRUE);
  #endif

  // Reset CH1 & CH2 for stepping motor(Zoom)
    R2A30440NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_RST_CH12(RST_OP_INITIALIZE) | 
                                                      DRV_RST_CH34(RST_OP_INITIALIZE) |
                                                      DRV_STOP_CH12(DEC_2_STOP)       |
                                                      DRV_STOP_CH34(DEC_2_STOP)       );

  // Initialize GPIO
    R2A30440NP_GPIO_Setting();

  // Reset CH12-CH34 Power Setting.
    R2A30440NP_RegWrite(REG_COMMON, REGC_PI_PS_SETUP , PS_ALL_STATE);

    R2A30440NP_Reset();

  // Enable Zoom/Focus PR

    ps_val = R2A30440NP_PowerState(PS_CH12, MMP_TRUE);
    ps_val = R2A30440NP_PowerState(PS_CH34, MMP_TRUE);
    R2A30440NP_RegWrite(REG_COMMON, REGC_PI_PS_SETUP , ps_val);

    R2A30440NP_RegWrite(REG_COMMON, REGC_STM12_OP_CTRL2 , DRV_CH12_CALIBRAT(OP_ENABLE));
    MMPF_OS_Sleep(100);
    R2A30440NP_RegWrite(REG_COMMON, REGC_STM12_OP_CTRL2 , DRV_CH34_CALIBRAT(OP_ENABLE));
    MMPF_OS_Sleep(100);

    ps_val = R2A30440NP_PowerState(PS_CH12, MMP_TRUE);
    ps_val = R2A30440NP_PowerState(PS_CH34, MMP_TRUE);
    R2A30440NP_RegWrite(REG_COMMON, REGC_PI_PS_SETUP , ps_val);
    
    #if (DSC_IRIS_ENABLE)
    MMPF_PIO_EnableOutputMode(IRIS_GPIO_PIN_1, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData( IRIS_GPIO_PIN_1, IRIS_GPIO_PIN_1_OFF, MMP_TRUE );
    MMPF_PIO_EnableOutputMode(IRIS_GPIO_PIN_2, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData( IRIS_GPIO_PIN_2, IRIS_GPIO_PIN_2_OFF, MMP_TRUE );
    #endif
    
    #if (DSC_M_SHUTTER_ENABLE)
  	MMPF_PIO_EnableOutputMode(MECHANICAL_SHUTTER_GPIO, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MECHANICAL_SHUTTER_GPIO, MECHANICAL_SHUTTER_GPIO_OFF, MMP_TRUE );
    
    R2A30440NP_MechanicalShutterDirection(MMP_TRUE);
    
  	MMPF_PIO_EnableOutputMode(MECHANICAL_SHUTTER_GPIO, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MECHANICAL_SHUTTER_GPIO, MECHANICAL_SHUTTER_GPIO_ON, MMP_TRUE );
    
    MMPF_OS_Sleep_MS(10);
    
  	MMPF_PIO_EnableOutputMode(MECHANICAL_SHUTTER_GPIO, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(MECHANICAL_SHUTTER_GPIO, MECHANICAL_SHUTTER_GPIO_OFF, MMP_TRUE );
    #endif
}

void R2A30440NP_ZoomPowerOn(MMP_BOOL OnOFF)
{
    MMP_USHORT val = 0;
    val = R2A30440NP_PowerState(PS_CH34, OnOFF );
    R2A30440NP_RegWrite(REG_COMMON, REGC_PI_PS_SETUP , val);
}

MMP_USHORT R2A30440NP_ZoomMoveStepsEsti(MMP_ULONG ulDrivingClkHz, MMP_ULONG ulMoveTime)  // 
{     
	static MMP_ULONG ulMaxPosiDiff = 0;
	static MMP_USHORT usZoomMaxSpdAcc_saved = 0;
	static MMP_ULONG ulMoveTime_saved = 0;

	// condition changed, need to re-calculate
	if((usZoomMaxSpdAcc_saved!= usZoomMaxSpdAcc) || (ulMoveTime_saved != ulMoveTime))
	{
		// ulMoveTime is mini second in us16.16 format
		ulMaxPosiDiff = ((MMP_ULONG)usZoomMaxSpdAcc<<(6+16))/ulMoveTime;
		ulMaxPosiDiff = ulDrivingClkHz / ulMaxPosiDiff/1000;

		usZoomMaxSpdAcc_saved = usZoomMaxSpdAcc;
		ulMoveTime_saved = ulMoveTime;
	}

	return (MMP_USHORT)ulMaxPosiDiff;
}


void R2A30440NP_ZoomSetParam(MMP_UBYTE ubMode, MMP_UBYTE ubDirection, MMP_USHORT ulStep )
{
    MMP_ULONG Drv_step = 0;


    Drv_step = ulStep*32;

    ubZoomDir = ubDirection;

#if 1
    R2A30440NP_RegWrite(REG_COMMON , REGC_ACTUATOR_SEL,  OSCIN_CLK_FREQ(FREQ_1M_6_2M)   |
                                                         CH1234_CARRIES_FREQ(FREQ_400K) |
                                                         CH34_ACTUATOR_SEL(USE_STM2)    );

    R2A30440NP_RegWrite(REG_COMMON , REGC_OUTPUT_SETUP,  DRV_EXT_OUTPUT_SEL(DRV_H_IN_EXCITE) |
                                                         DRV_MOB1_OUTPUT_SEL(DRV_MOB1_MOB12) |
                                                         DRV_MOB2_OUTPUT_SEL(DRV_MOB2_MOB34) |
                                                         DRV_EXT2_SEL(DRV_EXT2_EXT34)        );

    R2A30440NP_RegWrite(REG_COMMON , REGC_STM12_STATUS_FLAG,  STATUS_OUTPUT_SEL(OUTPUT_STM2) |
                                                              STATUS_INFO_SEL(STATUS_OFF) );
#endif
    if( DRV_SPEED_CONST == ubMode )
    {
        R2A30440NP_RegWrite(REG_CH34, REG_DRV_CTRL      , DRV_CTRL_DIR(ubDirection)              | 
                                                          DRV_CTRL_MODE(DRV_MICRO_STEP_256STEP)  |
                                                          DRV_CTRL_SPEED_TYPE(DRV_CTRL_NO_ACC_DEC) );//|
                                                        //DRV_INIT_POS_EXCITE(OP_ENABLE));

        R2A30440NP_RegWrite(REG_CH34, REG_N_PULSE1      , nPULSE1(Drv_step) );

        R2A30440NP_RegWrite(REG_CH34, REG_N_PULSE2      , nPULSE2(Drv_step) );

        R2A30440NP_RegWrite(REG_CH34, REG_nPULSE_RANGE  , PULSE_RATE_RANGE(PULSE_RATE_RANGE_4) |
                                                          SET_STOP_POS(DRV_STOP_INVALID) );

		usZoomMaxSpdAcc = 256;
		R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE0   , PULSE_RATE(usZoomMaxSpdAcc) );
    }
    else if ( DRV_SPEED_ACC_LOW == ubMode )
    {
        R2A30440NP_RegWrite(REG_CH34, REG_DRV_CTRL      , DRV_CTRL_DIR(ubDirection)           | 
                                                          DRV_CTRL_MODE(DRV_MICRO_STEP_256STEP)  | 
                                                          DRV_CTRL_SPEED_TYPE(DRV_CTRL_ACC_DEC)     );  //|
                                                           //DRV_INIT_POS_EXCITE(DRV_ENABLE));

        R2A30440NP_RegWrite(REG_CH34, REG_N_PULSE1      , nPULSE1(Drv_step) );

        R2A30440NP_RegWrite(REG_CH34, REG_N_PULSE2      , nPULSE2(Drv_step) );

        R2A30440NP_RegWrite(REG_CH34, REG_nPULSE_RANGE  , PULSE_RATE_RANGE(PULSE_RATE_RANGE_4) |
                                                          SET_STOP_POS(DRV_STOP_INVALID)  );

        R2A30440NP_RegWrite(REG_CH34, REG_nPULSE_ACC_DEC, nPULSE_ACCDEC(64) );

#if(DRIVE_MOTOR_CLK_HZ == 5000000) // 5MHz clock
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE0   , PULSE_RATE(1023) );

        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE1   , PULSE_RATE(768) );
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE2   , PULSE_RATE(384) );
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE3   , PULSE_RATE(256) );
		usZoomMaxSpdAcc = 225;
#else // 6MMHz clock
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE0    , PULSE_RATE(1023) );

        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE1   , PULSE_RATE(922) );
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE2   , PULSE_RATE(461) );
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE3   , PULSE_RATE(307) );
		usZoomMaxSpdAcc = 270;
#endif
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE4   , PULSE_RATE(usZoomMaxSpdAcc) );
    }
    else if ( DRV_SPEED_ACC_MID == ubMode )
    {
        R2A30440NP_RegWrite(REG_CH34, REG_DRV_CTRL      , DRV_CTRL_DIR(ubDirection)           | 
                                                          DRV_CTRL_MODE(DRV_MICRO_STEP_256STEP)  | 
                                                          DRV_CTRL_SPEED_TYPE(DRV_CTRL_ACC_DEC)     );  //|
                                                           //DRV_INIT_POS_EXCITE(DRV_ENABLE));

        R2A30440NP_RegWrite(REG_CH34, REG_N_PULSE1      , nPULSE1(Drv_step) );

        R2A30440NP_RegWrite(REG_CH34, REG_N_PULSE2      , nPULSE2(Drv_step) );

        R2A30440NP_RegWrite(REG_CH34, REG_nPULSE_RANGE  , PULSE_RATE_RANGE(PULSE_RATE_RANGE_4) |
                                                          SET_STOP_POS(DRV_STOP_INVALID)  );

        R2A30440NP_RegWrite(REG_CH34, REG_nPULSE_ACC_DEC, nPULSE_ACCDEC(64) );

        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE0   , PULSE_RATE(1023) );

        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE1   , PULSE_RATE(768) );
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE2   , PULSE_RATE(384) );
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE3   , PULSE_RATE(128) );
 		usZoomMaxSpdAcc = 100;
        R2A30440NP_RegWrite(REG_CH34, REG_PULSE_RATE4   , PULSE_RATE(usZoomMaxSpdAcc) );
    }
    else if( DRV_SPEED_ACC_HIGH == ubMode )
    {

    }

    ubZoomDir = ubDirection;

}

void R2A30440NP_ZoomDrive()
{
#if 0
    R2A30440NP_RegWrite(REG_COMMON , REGC_ACTUATOR_SEL,  OSCIN_CLK_FREQ(FREQ_1M_6_2M)   |
                                                         CH1234_CARRIES_FREQ(FREQ_400K) |
                                                         CH34_ACTUATOR_SEL(USE_STM2)    );

//    R2A30440NP_RegWrite(REG_COMMON , REGC_BF1_TERMINAL_SETUP,  CH3_CH6_TERM_CTRL_SETUP(0x00110) );

    R2A30440NP_RegWrite(REG_COMMON , REGC_OUTPUT_SETUP,  DRV_EXT_OUTPUT_SEL(DRV_H_IN_EXCITE) |
                                                         DRV_MOB1_OUTPUT_SEL(DRV_MOB1_MOB12) |
                                                         DRV_MOB2_OUTPUT_SEL(DRV_MOB2_MOB34) |
                                                         DRV_EXT2_SEL(DRV_EXT2_EXT34)        );

    R2A30440NP_RegWrite(REG_COMMON , REGC_STM12_STATUS_FLAG,  STATUS_OUTPUT_SEL(OUTPUT_STM1) |
                                                              STATUS_INFO_SEL(STATUS_OFF) );
#endif

    R2A30440NP_RegWrite(REG_CH12, REG_DRV_VOL_VAL   , DRV_VOL_VAL(DRV_VOL_400)  |
		                                              DRV_VOL_GAIN(DRV_GAIN_ONE)|
		                                              DRV_VOL_CHANGE(VOL_CHANGE_IMMEDIATE) );

    R2A30440NP_RegWrite(REG_CH34, REG_OP_CTRL   , OP_CTRL_EN(OP_ENABLE)           |  
                                                  OP_CTRL_EXT_EN(OP_ENABLE)       | 
                                                  OP_CTRL_CONT_OP(CONT_OP_DISABLE)| 
                                                  OP_CTRL_VD_STOP(OP_DISABLE)| 
                                                  OP_CTRL_DIR(ubZoomDir)   );

}

void R2A30440NP_ZoomStop()
{
    R2A30440NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_STOP_CH34(DEC_2_STOP));
}

MMP_BOOL R2A30440NP_ZoomExciteState(void)
{
    MMP_UBYTE  ubVal = 0;

    MMPF_PIO_GetData(MT_EXT2,&ubVal);

    if(ubVal) 
        return MMP_TRUE;
    else
        return MMP_FALSE;
}

MMP_UBYTE R2A30440NP_ZoomDirection(void)
{
    return ubZoomDir;
}

void R2A30440NP_FocusPowerOn(MMP_BOOL OnOFF)
{
    MMP_USHORT val = 0;
    val = R2A30440NP_PowerState(PS_CH12, OnOFF );
    R2A30440NP_RegWrite(REG_COMMON, REGC_PI_PS_SETUP , val);

}

void R2A30440NP_FocusSetParam(MMP_UBYTE ubMode, MMP_UBYTE ubDirection, MMP_USHORT ulStep )
{
    MMP_ULONG Drv_step = 0;
    MMP_USHORT PulseRate0, PulseRate1, PulseRate2, PulseRate3, PulseRate4;

    Drv_step = ulStep*32;

    ubFocusDir = ubDirection;
#if 1
    R2A30440NP_RegWrite(REG_COMMON , REGC_ACTUATOR_SEL,  OSCIN_CLK_FREQ(FREQ_1M_6_2M)   |
                                                         CH1234_CARRIES_FREQ(FREQ_400K) |
                                                         CH34_ACTUATOR_SEL(USE_STM2)    );


    R2A30440NP_RegWrite(REG_COMMON , REGC_BF1_TERMINAL_SETUP,  CH3_CH6_TERM_CTRL_SETUP(0x00110) );

    R2A30440NP_RegWrite(REG_COMMON , REGC_OUTPUT_SETUP,  DRV_EXT_OUTPUT_SEL(DRV_H_IN_EXCITE) |
                                                         DRV_MOB1_OUTPUT_SEL(DRV_MOB1_MOB12) |
                                                         DRV_MOB2_OUTPUT_SEL(DRV_MOB2_MOB34) |
                                                         DRV_EXT1_SEL(DRV_EXT1_EXT12)        );

    R2A30440NP_RegWrite(REG_COMMON , REGC_STM12_STATUS_FLAG,  STATUS_OUTPUT_SEL(OUTPUT_STM1) |
                                                              STATUS_INFO_SEL(STATUS_OFF) );
#endif

    if( DRV_SPEED_CONST == ubMode )
    {
        R2A30440NP_RegWrite(REG_CH12, REG_DRV_CTRL      , DRV_CTRL_DIR(ubDirection)        | 
                                                          DRV_CTRL_MODE(DRV_MICRO_STEP_256STEP)    | 
                                                          DRV_CTRL_SPEED_TYPE(DRV_CTRL_NO_ACC_DEC) ); //|
                                                        //DRV_INIT_POS_EXCITE(OP_ENABLE));

        R2A30440NP_RegWrite(REG_CH12, REG_N_PULSE1      , nPULSE1(Drv_step) );

        R2A30440NP_RegWrite(REG_CH12, REG_N_PULSE2      , nPULSE2(Drv_step) );

        R2A30440NP_RegWrite(REG_CH12, REG_nPULSE_RANGE  , PULSE_RATE_RANGE(PULSE_RATE_RANGE_2) |
                                                          SET_STOP_POS(DRV_STOP_INVALID)  );

        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE0   , PULSE_RATE(320) );
#if 0
      // Set Pulse rate reg 1 ~ 4
        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE1   , PULSE_RATE(512) );
        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE2   , PULSE_RATE(384) );
        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE3   , PULSE_RATE(384) );
        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE4   , PULSE_RATE(384) );
#endif
    }
    else if ( DRV_SPEED_ACC_LOW  == ubMode  ||
              DRV_SPEED_ACC_MID  == ubMode  ||
              DRV_SPEED_ACC_HIGH == ubMode  )
    {
        if( DRV_SPEED_ACC_LOW  == ubMode )
        {
            PulseRate0 = 976;
            PulseRate1 = 500;
            PulseRate2 = 384;
            PulseRate3 = 200;
            PulseRate4 = 173;

        }
        else if( DRV_SPEED_ACC_MID  == ubMode )
        {
            PulseRate0 = 976;
            PulseRate1 = 500;
            PulseRate2 = 384;
            PulseRate3 = 192;
            PulseRate4 = 130;
        }
        else if( DRV_SPEED_ACC_HIGH  == ubMode )
        {
            PulseRate0 = 400; // 976;  
            PulseRate1 = 200; // 500;
            PulseRate2 = 128; // 256;
            PulseRate3 = 100; // 128;
            PulseRate4 = 100;
        }
        else
        {
        }

        R2A30440NP_RegWrite(REG_CH12, REG_DRV_CTRL      , DRV_CTRL_DIR(ubDirection)           | 
                                                          DRV_CTRL_MODE(DRV_MICRO_STEP_256STEP)       | 
                                                          DRV_CTRL_SPEED_TYPE(DRV_CTRL_ACC_DEC)     );  //|
                                                      //  DRV_INIT_POS_EXCITE(DRV_ENABLE));

        R2A30440NP_RegWrite(REG_CH12, REG_N_PULSE1      , nPULSE1(Drv_step) );

        R2A30440NP_RegWrite(REG_CH12, REG_N_PULSE2      , nPULSE2(Drv_step) );

        R2A30440NP_RegWrite(REG_CH12, REG_nPULSE_RANGE  , PULSE_RATE_RANGE(PULSE_RATE_RANGE_2) |
                                                          SET_STOP_POS(DRV_STOP_INVALID)  );

        R2A30440NP_RegWrite(REG_CH12, REG_nPULSE_ACC_DEC, nPULSE_ACCDEC(32) );
        
        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE0   , PULSE_RATE(PulseRate0) );

      // Set Pulse rate reg 1 ~ 4
        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE1   , PULSE_RATE(PulseRate1) );
        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE2   , PULSE_RATE(PulseRate2) );
        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE3   , PULSE_RATE(PulseRate3) );
        R2A30440NP_RegWrite(REG_CH12, REG_PULSE_RATE4   , PULSE_RATE(PulseRate4) );
    }

}

void R2A30440NP_FocusDrive()
{
#if 0
    R2A30440NP_RegWrite(REG_COMMON , REGC_ACTUATOR_SEL,  OSCIN_CLK_FREQ(FREQ_1M_6_2M)   |
                                                         CH1234_CARRIES_FREQ(FREQ_400K) |
                                                         CH34_ACTUATOR_SEL(USE_STM2)    );

 
    R2A30440NP_RegWrite(REG_COMMON , REGC_BF1_TERMINAL_SETUP,  CH3_CH6_TERM_CTRL_SETUP(0x00110) );

    R2A30440NP_RegWrite(REG_COMMON , REGC_OUTPUT_SETUP,  DRV_EXT_OUTPUT_SEL(DRV_H_IN_EXCITE) |
                                                         DRV_MOB1_OUTPUT_SEL(DRV_MOB1_MOB12) |
                                                         DRV_MOB2_OUTPUT_SEL(DRV_MOB2_MOB34) |
                                                         DRV_EXT1_SEL(DRV_EXT1_EXT12)        );

    R2A30440NP_RegWrite(REG_COMMON , REGC_STM12_STATUS_FLAG,  STATUS_OUTPUT_SEL(OUTPUT_STM2) |
                                                              STATUS_INFO_SEL(STATUS_OFF) );
#endif

    R2A30440NP_RegWrite(REG_CH12, REG_DRV_VOL_VAL, DRV_VOL_VAL(DRV_VOL_400)  |
		                                           DRV_VOL_GAIN(DRV_GAIN_ONE)|
		                                           DRV_VOL_CHANGE(VOL_CHANGE_IMMEDIATE) );

    R2A30440NP_RegWrite(REG_CH12, REG_OP_CTRL   , OP_CTRL_EN(OP_ENABLE)           |
                                                  OP_CTRL_EXT_EN(OP_ENABLE)       | 
                                                  OP_CTRL_CONT_OP(CONT_OP_DISABLE)| 
                                                  OP_CTRL_VD_STOP(OP_DISABLE)     |
                                                  OP_CTRL_DIR(ubFocusDir)   );
}

void R2A30440NP_FocusStop()
{
    R2A30440NP_RegWrite(REG_COMMON, REGC_SW_RST     , DRV_STOP_CH12(DEC_2_STOP));
}

MMP_BOOL R2A30440NP_FocusExciteState()
{
    MMP_UBYTE  ubVal = 0;

    MMPF_PIO_GetData(MT_EXT1,&ubVal);

    if(ubVal) 
        return MMP_TRUE;
    else
        return MMP_FALSE;
}

MMP_UBYTE R2A30440NP_FocusDirection(void)
{
    return ubFocusDir;
}

void R2A30440NP_RegWrite(MMP_UBYTE ch, MMP_UBYTE reg, MMP_USHORT wdata)
{
    MMP_UBYTE  i;
    MMP_USHORT data; 


    if(MMPF_OS_AcquireSem(m_MotorRegSemID, 0) != MMPF_OS_ERR_NONE) {
		return;
	}
	/**
	Total    : 16bits
	channel  : bit 15, 14
	register : bit 13, 12, 11, 10
	data     : lower 10 bits
	*/
    data = ch << 14 | reg << 10 | wdata;
    MMPF_PIO_SetData(MT_SPI_CS, GPIO_LOW, MMP_TRUE);

    R2A30440NP_Wait_ticks(1);

    for(i = 0; i < 16; i++)
    {
        MMPF_PIO_SetData(MT_SPI_CLK, GPIO_LOW, MMP_TRUE);
        R2A30440NP_Wait_ticks(3);

        if(((data >> (15 - i)) & 0x01)) 
            MMPF_PIO_SetData(MT_SPI_DATA, GPIO_HIGH, MMP_TRUE);
        else
            MMPF_PIO_SetData(MT_SPI_DATA, GPIO_LOW, MMP_TRUE);
        
        R2A30440NP_Wait_ticks(3);
        MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);
    }
    R2A30440NP_Wait_ticks(1);
    MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);
    R2A30440NP_Wait_ticks(2);
    MMPF_PIO_SetData(MT_SPI_CS, GPIO_HIGH, MMP_TRUE);

    MMPF_OS_ReleaseSem(m_MotorRegSemID);

}

MMP_UBYTE R2A30440NP_RegRead(MMP_UBYTE ch, MMP_UBYTE reg, MMP_UBYTE ch_rd, MMP_UBYTE BitSize)
{
    MMP_UBYTE  i;
    MMP_USHORT sdata;
    MMP_UBYTE  rdata = 0;
    MMP_UBYTE  serial_data; 


    if(MMPF_OS_AcquireSem(m_MotorRegSemID, 0) != MMPF_OS_ERR_NONE) {
		return 0;
	}

    sdata = ch << 14 | reg << 10 | ch_rd << 8;

    MMPF_PIO_SetData(MT_SPI_CS, GPIO_LOW, MMP_TRUE);
    R2A30440NP_Wait_ticks(1);

    for(i = 0; i < 16; i++)
    {
        MMPF_PIO_SetData(MT_SPI_CLK, GPIO_LOW, MMP_TRUE);
        R2A30440NP_Wait_ticks(1);

        if( i < 8)
        {
            if(((sdata >> (15 - i)) & 0x01)) 
                MMPF_PIO_SetData(MT_SPI_DATA, GPIO_HIGH, MMP_TRUE);
            else
                MMPF_PIO_SetData(MT_SPI_DATA, GPIO_LOW, MMP_TRUE);
        }
        else
        {
            if( (15 - i) < BitSize )
            {
                MMPF_PIO_GetData(MT_SPI_DATA, &serial_data);
    
                if( 1 == serial_data )
                rdata |= ( serial_data << (15 - i));
            }
        }

        R2A30440NP_Wait_ticks(1);
        MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);
    }
    
    R2A30440NP_Wait_ticks(1);
    MMPF_PIO_SetData(MT_SPI_CS, GPIO_HIGH, MMP_TRUE);
    MMPF_PIO_SetData(MT_SPI_CLK, GPIO_HIGH, MMP_TRUE);

    MMPF_OS_ReleaseSem(m_MotorRegSemID);

    return rdata;
}


#if (DSC_IRIS_ENABLE)

void R2A30440NP_IrisGPIOPin1(MMP_BOOL bOnOff)
{
	if(bOnOff)
		MMPF_PIO_SetData(IRIS_GPIO_PIN_1, IRIS_GPIO_PIN_1_ON, MMP_TRUE );
	else
		MMPF_PIO_SetData(IRIS_GPIO_PIN_1, IRIS_GPIO_PIN_1_OFF, MMP_TRUE );
}

void R2A30440NP_IrisGPIOPin2(MMP_BOOL bOnOff)
{
	if(bOnOff)
		MMPF_PIO_SetData(IRIS_GPIO_PIN_2, IRIS_GPIO_PIN_2_ON, MMP_TRUE );
	else
		MMPF_PIO_SetData(IRIS_GPIO_PIN_2, IRIS_GPIO_PIN_2_OFF, MMP_TRUE );


}
#endif //< #if (DSC_IRIS_ENABLE)

void R2A30440NP_IrisDirection(MMP_UBYTE ubDirection)
{

	#if (DSC_IRIS_ENABLE)
	
    R2A30440NP_RegWrite( 2, 0xf, 0x0);
    
	if(ubDirection == 0x0){
		R2A30440NP_IrisGPIOPin1(MMP_FALSE);
		R2A30440NP_IrisGPIOPin2(MMP_FALSE);
	}else if(ubDirection == 0x1){
		R2A30440NP_IrisGPIOPin1(MMP_TRUE);
		R2A30440NP_IrisGPIOPin2(MMP_FALSE);
	
	}else if(ubDirection == 0x2){
		R2A30440NP_IrisGPIOPin1(MMP_FALSE);
		R2A30440NP_IrisGPIOPin2(MMP_TRUE);
	
	}else{
		R2A30440NP_IrisGPIOPin1(MMP_TRUE);
		R2A30440NP_IrisGPIOPin2(MMP_TRUE);
	}

    /*
    1. Channel  : Common items, channel 3 & 4 (DC motor / coil Control)
    2. Register : Input terminal setup
    3. Data     : bit9~8 => BF1 control
                  bit7~6 => PI3 VD terminal setting
                  bit5 => PI2 VD terminal setting 
                  bit4~0 => 3~6ch input terminal control setup
    */
    /*
    Common,3,4ch(DC motor/coil control)   
    BF1 Control:Invalid   
    PI3 terminal VD:VD function Invalid   
    PI2 terminal VD:VD function Invalid   
    3-6ch Control input terminal:3ch�F-, 4ch�F-, 5ch�FIN3/IN4, 6ch�FIN5/IN6
    */
    R2A30440NP_RegWrite( 3, 0x1, 0x6);
    /*
    1. Channel  : channel 5, 6 & 7 (Exclusive Control)
    2. Register : 5ch DC motor / coil control
    3. Data     : bit9~6 => Ch5 driving mode,   0000 => 1 line control�@ CC IN/IN
												0001 => 1 line control�@ CC EN/IN
												0010 => Serial control CC
												0011 => 2 line control CC IN/IN
												0100 => 2 line control CC EN/IN
												0101 => 3 line control CC
												0110 => 1 line control�@ FS IN/IN
												0111 => 1 line control�@ FS EN/IN
												1000 => Serial control FS
												1001 => 2 line control FS IN/IN
												1010 => 2 line control FS EN/IN
												1011 => 3 line control FS
												1100 => PWM_IN/IN control
												1101 => PWM_EN/IN control
												1110 => 3 line control CC 1-2 phase (5ch/6ch control)
												1111 => 3 line control FS 1-2 phase (5ch/6ch control)
                  bit4   => Ch5 Rotation direction, 0 => Forward
                                                    1 => Reverse
                  bit3   => Ch5 Disable operation mode, 0 => OFF (High impendace)
                                                        1 => Brake
                  bit2   => Ch5 Outout OFF mode, 0 => OFF (High impendace)
                                                 1 => Brake
                  bit1~0 => Ch5 Serial control, 00 => OFF
                                                10 => Reverse
                                                01 => Forward
                                                11 => Brake
    */
    /*
    0xC0 => b1100 0000
    
    5,6,7ch   
    5ch drive mode             : 2 line control CC IN/IN   why?
    5ch Rotation direction     : Forward   
    5ch Disable operation mode : OFF(Hi-z)   
    5ch Output OFF mode        : OFF(Hi-z)   
    5ch serial                 : OFF
    */
    R2A30440NP_RegWrite( 2, 0x8, 0xc0);
    /*
    1. Channel  : channel 5, 6 & 7 (Exclusive Control)
    2. Register : 5ch DC motor / coil control
    3. Data     : bit9~6 => Ch5 constant current value, 0000->1111 => 310mV->160mV
                  bit4~3 => Ch5 Gain, set up the gain for constant current value, 00 => Gain 1 time
                                                                                  01 => Gain 1/2 time
                                                                                  10 => Gain 1/3 time
    */
    /*
    0x2c0 => b10 1100 0000
    5,6,7ch   
    5ch constant current:200mV   
    5ch Gain:x1
    */
    R2A30440NP_RegWrite( 2, 0x9, 0x2c0);
    
    /*
    1. Channel  : Common items, channel 3 & 4 (DC motor / coil Control)
    2. Register : PI Output control, PowerSave control
    3. Data     : bit9   => PS, Power safe mode ON/OFF setting for entire IC, 0 => Power safe ON
                                                                              1 => Power safe OFF
                  bit8   => PS12, Power safe mode ON/OFF setting for 1/2ch
                  bit7~6 => PS34, Power safe mode ON/OFF setting for 3/4ch
                  bit5   => PS5
                  bit4   => PS6
                  bit3~2 => PI3 control, Setup to change the control of PI3 driver, 00 PI driver OFF
																					01 PI driver ON
																					10 Assigned to BF1 output
																					11 Setting prohibited
                  bit1   => PI2
                  bit0   => PI1

    */
    /*
    0x220 => b10 0010 0000
    Common,3,4ch(DC motor/coil control)   
    PS  :OFF   
    PS12:ON   
    PS34:ON   
    PS5 :OFF   
    PS6 :ON   
    PI3 :PI driver OFF   
    PI2 :OFF   
    PI1 :OFF
    */
//    R2A30440NP_RegWrite( 3, 0x4, 0x220);
    R2A30440NP_RegWrite( 3, 0x4, 0x3E3);
    /*
    1. Channel  : channel 5, 6 & 7 (Exclusive Control)
    2. Register : 5ch/6ch (DC motor / coil control)
                  7ch (Exclusive control) operation control
    3. Data     : bit9~8 => 5ch/6ch/7ch Exclusive control, 00 => No exclusive control
														   01 => 5ch
														   10 => 6ch
														   11 => 7ch
                  bit7~5
                  bit4 => ch7 Enable operation, 0 => Disable operation
                                                1 => Enable operation
                  bit3 => ch6 Rotation direction, 0 => Forward
                                                  1 => Reverse
                  bit2 => ch6 Enable operation
                  bit1 => ch5 Rotation direction
                  bit0 => ch5 Enable operation

    */
    /*
    5,6,7ch   
    5ch/6ch/7ch exclusive control : Without exclusive control   
    7ch Enable operation          : Disable operation   
    6ch Rotation direction        : Forward   
    6ch Enable operation          : Disable operation   
    5ch Rotation direction        : Forward   
    5ch Enable operation          : Enable operation
    */
    R2A30440NP_RegWrite( 2, 0xf, 0x1);
	#endif //< #if (DSC_IRIS_ENABLE)


}






void R2A30440NP_TriggerMechanicalShutter(MMP_BOOL bTrigger)
{
	#if (DSC_M_SHUTTER_ENABLE)
	if(bTrigger){
    	MMPF_PIO_SetData( MECHANICAL_SHUTTER_GPIO, MECHANICAL_SHUTTER_GPIO_ON, MMP_FALSE );
    }else{
	    MMPF_PIO_SetData( MECHANICAL_SHUTTER_GPIO, MECHANICAL_SHUTTER_GPIO_OFF, MMP_FALSE );
    }
    #endif ///< #if (DSC_M_SHUTTER_ENABLE)
}

void R2A30440NP_MechanicalShutterDirection(MMP_BOOL bForwardReverse)
{
	#if (DSC_M_SHUTTER_ENABLE)
    /*
    Common,3,4ch(DC motor/coil control)   
    BF1 Control:Invalid   
    PI3 terminal VD:VD function Invalid   
    PI2 terminal VD:VD function Invalid   
    3-6ch Control input terminal:3ch�F-, 4ch�F-, 5ch�F-, 6ch�FIN6
    */
    R2A30440NP_RegWrite( 3, 0x1, 0x1c);

    /*
    5,6,7ch   
    6ch drive mode             : 1 line control CC IN/IN   
    6ch Rotation direction     : Forward   
    6ch Disable operation mode : OFF(Hi-z)   
    6ch Output OFF mode        : OFF(Hi-z)
    */
    R2A30440NP_RegWrite( 2, 0xb, 0x0);

    //5,6,7ch   6ch constant current:200mV   6ch Gain:x1
    R2A30440NP_RegWrite( 2, 0xc, 0x2c0);

    /*
    Common,3,4ch(DC motor/coil control)   
    PS   : OFF   
    PS12 : ON   
    PS34 : ON   
    PS5  : ON   
    PS6  : OFF   
    PI3 control:PI driver OFF   
    PI2  : OFF   
    PI1  : OFF
    */
//    R2A30440NP_RegWrite( 3, 0x4, 0x210);
    R2A30440NP_RegWrite( 3, 0x4, 0x3D3);    

    if(bForwardReverse){
        /*
	    5,6,7ch   
	    5ch/6ch/7ch exclusive control : Without exclusive control   
	    7ch Enable operation          : Disable operation   
	    6ch Rotation direction        : Forward   
	    6ch Enable operation          : Enable operation   
	    5ch Rotation direction        : Forward   
	    5ch Enable operation          : Disable operation
	    */
    	R2A30440NP_RegWrite( 2, 0xf, 0x4);
    }else{
        /*
	    5,6,7ch   
	    5ch/6ch/7ch exclusive control : Without exclusive control   
	    7ch Enable operation          : Disable operation   
	    6ch Rotation direction        : Reverse   
	    6ch Enable operation          : Enable operation   
	    5ch Rotation direction        : Forward   
	    5ch Enable operation          : Disable operation
	    */
	    R2A30440NP_RegWrite( 2, 0xf, 0xc);
    
    }
    #endif ///< #if (DSC_M_SHUTTER_ENABLE)	

}


#if 1
MotorCtrl_FUNCTIION Motor_R2A30440NP_Func =
{
    R2A30440NP_Initialize,
    R2A30440NP_ZoomPowerOn,
    R2A30440NP_ZoomSetParam,
    R2A30440NP_ZoomDrive,
    R2A30440NP_ZoomStop,
    R2A30440NP_ZoomEnablePR,
    R2A30440NP_ZoomEnableExcite,
    R2A30440NP_ZoomMoveStepsEsti,
    R2A30440NP_ZoomDetectPR,
    R2A30440NP_ZoomExciteState,
    R2A30440NP_ZoomDirection,
    R2A30440NP_FocusPowerOn,
    R2A30440NP_FocusSetParam,
    R2A30440NP_FocusDrive,
    R2A30440NP_FocusStop,
    R2A30440NP_FocusEnablePR,
    R2A30440NP_FocusEnableExcite,
    R2A30440NP_FocusDetectPR,
    R2A30440NP_FocusExciteState,
    R2A30440NP_FocusDirection,
    R2A30440NP_RegWrite,
    R2A30440NP_RegRead,
    R2A30440NP_IrisDirection,
    R2A30440NP_TriggerMechanicalShutter,
    R2A30440NP_MechanicalShutterDirection
};

MotorCtrl_FUNCTIION  *MotorControlModule = &Motor_R2A30440NP_Func;
#endif
#endif

